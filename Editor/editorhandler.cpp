/*
------------------------[ Lbanet Source ]-------------------------
Copyright (C) 2009
Author: Vivien Delage [Rincevent_123]
Email : vdelage@gmail.com

-------------------------------[ GNU License ]-------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
*/

#include "editorhandler.h"
#include "EventsQueue.h"
#include "ClientExtendedEvents.h"
#include "SynchronizedTimeHandler.h"
#include "DataLoader.h"
#include "SharedDataHandler.h"
#include "ServerLuaHandler.h"
#include "Triggers.h"
#include "StringHelperFuncs.h"
#include "ClientScript.h"
#include "Lba1ModelMapHandler.h"
#include "InventoryItemHandler.h"

#include <qdir.h>
#include <QErrorMessage>
#include <QMessageBox>
#include <QFileDialog>
#include <boost/filesystem.hpp>
#include <QImage>

#include <fstream>
#include <math.h>

#include "OSGHandler.h"
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <osgUtil/SmoothingVisitor>
#include <osg/LineWidth>
#include <osg/PolygonMode>
#include <osgManipulator/TranslateAxisDragger>
#include <osgManipulator/Command>

#ifdef WIN32
#include "windows.h"
#endif

namespace fs = boost::filesystem;

class DraggerCustomCallback : public osgManipulator::DraggerCallback
{
public:
	//! constructor 
	DraggerCustomCallback(int pickedarrow)
		: _pickedarrow(pickedarrow)
	{}


	virtual bool receive(const osgManipulator::MotionCommand& command) 
	{ 
		EventsQueue::getReceiverQueue()->AddEvent(new PickedArrowMovedEvent(_pickedarrow));		
		return true; 
	}


private:
	int					_pickedarrow;
};



/***********************************************************
helper function
***********************************************************/
static void replaceinstr(std::string& target, const std::string oldstr, const std::string newstr) 
{
	unsigned int x;
	while(x = target.find(oldstr), x != std::string::npos) 
	{
		target.erase(x, oldstr.length());
		target.insert(x, newstr);
	}
}


/***********************************************************
add data to the list
***********************************************************/
void CustomStringListModel::AddData(const QString & Data)
{
	int row = rowCount();
	insertRows(row, 1);
	setData(createIndex(row, 0), Data);
}


/***********************************************************
clear the list
***********************************************************/	
void CustomStringListModel::Clear()
{
	setStringList(QStringList());
}


/***********************************************************
remove data of the list if exist
***********************************************************/
void CustomStringListModel::RemoveData(const QString & Data)
{
	int idx = stringList().indexOf(Data);
	if(idx >= 0)
		removeRows(idx, 1);
}


/***********************************************************
remove data of the list if exist
***********************************************************/
void CustomStringListModel::ReplaceData(const QString & OldData, const QString & NewData)
{
	int idx = stringList().indexOf(OldData);
	if(idx >= 0)
		setData(createIndex(idx, 0), NewData);
}


/***********************************************************
check if data present in the list
***********************************************************/
bool CustomStringListModel::DataExist(const QString & Data)
{
	return (stringList().indexOf(Data) >= 0);
}


 
/***********************************************************
get first data of the list
***********************************************************/
QString CustomStringListModel::GetFirstdata()
{
	if(stringList().size() > 0)
		return stringList()[0];

	return QString();
}


/***********************************************************
rowCount
***********************************************************/
int StringTableModel::rowCount(const QModelIndex &parent) const
{
	if(_stringMatrix.size() > 0)
		return _stringMatrix[0].size();

	return 0;
}

/***********************************************************
columnCount
***********************************************************/
int StringTableModel::columnCount(const QModelIndex &parent) const
{
	return _stringMatrix.size();
}

/***********************************************************
data
***********************************************************/
QVariant StringTableModel::data(const QModelIndex &index, int role) const
{
     if (!index.isValid())
         return QVariant();

     if (index.column() >= _stringMatrix.size())
         return QVariant();

     if (index.row() >= _stringMatrix[0].size())
         return QVariant();

     if (role == Qt::DisplayRole/* || role == Qt::EditRole*/)
         return _stringMatrix[index.column()][index.row()];
     else
         return QVariant();

}

/***********************************************************
headerData
***********************************************************/
QVariant StringTableModel::headerData(int section, Qt::Orientation orientation,
											 int role) const
{
     if (role != Qt::DisplayRole)
         return QVariant();

     if (orientation == Qt::Horizontal)
	 {
		 if(section < _header.size())
			return _header[section];
	 }
	 else
	 {
		if(section < _ids.size())
			return _ids[section];	
	 }

	 return QVariant();
}

/***********************************************************
flags
***********************************************************/
Qt::ItemFlags StringTableModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return QAbstractItemModel::flags(index);
}

/***********************************************************
setData
***********************************************************/
bool StringTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (index.isValid() && role == Qt::EditRole) 
	{
		_stringMatrix[index.column()].replace(index.row(), value.toString());
		emit dataChanged(index, index);
		return true;
	}

	return false;
}

/***********************************************************
get a string
***********************************************************/
QString StringTableModel::GetString(const QModelIndex &index)
{
	if (index.isValid()) 
		return _stringMatrix[index.column()][index.row()];

	return QString();
}

/***********************************************************
get the corresponding id
***********************************************************/
long StringTableModel::GetId(const QModelIndex &index)
{
	if (index.isValid()) 
		return _ids[index.row()];

	return -1;
}


/***********************************************************
get next free id
***********************************************************/
long StringTableModel::GetNextId()
{
	if(_ids.size() == 0)
		return 1;

	return _ids[_ids.size()-1] + 1;
}


/***********************************************************
insertRows
***********************************************************/
bool StringTableModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	beginInsertRows(QModelIndex(), position, position+rows-1);

	for (int row = 0; row < rows; ++row) 
	{
		for(size_t i=0; i<_stringMatrix.size(); ++i)
			_stringMatrix[i].insert(position, "");
	}

	endInsertRows();
	return true;
}

/***********************************************************
removeRows
***********************************************************/
bool StringTableModel::removeRows(int position, int rows, const QModelIndex &parent)
{
	beginRemoveRows(QModelIndex(), position, position+rows-1);

	for (int row = 0; row < rows; ++row) 
	{
		_ids.erase(_ids.begin()+position);

		for(size_t i=0; i<_stringMatrix.size(); ++i)
			_stringMatrix[i].removeAt(position);
	}

	endRemoveRows();
	return true;
}


/***********************************************************
clear the table content
***********************************************************/
void StringTableModel::Clear()
{
	if(_ids.size() > 0)
	{
		_ids.clear();

		if(_stringMatrix.size() > 0)
		{
			beginRemoveRows(QModelIndex(), 0, _stringMatrix[0].size()-1);

			for(size_t i=0; i<_stringMatrix.size(); ++i)
				_stringMatrix[i].clear();

			endRemoveRows();
		}

		reset();
	}
}


/***********************************************************
add a row
***********************************************************/
void StringTableModel::AddOrUpdateRow(long id, const QStringList &data)
{
	if(_stringMatrix.size() == data.size())
	{
		for(size_t i=0; i< _ids.size(); ++i)
		{
			if(_ids[i] == id)
			{
				// object already existing - update it
				for(size_t j=0; j< data.size(); ++j)
					_stringMatrix[j].replace(i, data[j]);

				QModelIndex index1 = createIndex(i, 0);
				QModelIndex index2 = createIndex(i, data.size()-1);
				emit dataChanged(index1, index2);
				return;
			}
		}

		// object does not exist - insert it
		beginInsertRows(QModelIndex(), _stringMatrix[0].size(), _stringMatrix[0].size());

		for(size_t i=0; i<_stringMatrix.size(); ++i)
			_stringMatrix[i].push_back(data[i]);

		_ids.push_back(id);

		endInsertRows();
	}
}









/***********************************************************
rowCount
***********************************************************/
int MixedTableModel::rowCount(const QModelIndex &parent) const
{
	if(_objMatrix.size() > 0)
		return _objMatrix[0].size();

	return 0;
}

/***********************************************************
columnCount
***********************************************************/
int MixedTableModel::columnCount(const QModelIndex &parent) const
{
	return _objMatrix.size();
}

/***********************************************************
data
***********************************************************/
QVariant MixedTableModel::data(const QModelIndex &index, int role) const
{
     if (!index.isValid())
         return QVariant();

     if (index.column() >= _objMatrix.size())
         return QVariant();

     if (index.row() >= _objMatrix[0].size())
         return QVariant();

     if (role == Qt::DisplayRole || role == Qt::EditRole)
         return _objMatrix[index.column()][index.row()];
     else
         return QVariant();

}

/***********************************************************
headerData
***********************************************************/
QVariant MixedTableModel::headerData(int section, Qt::Orientation orientation,
											 int role) const
{
     if (role != Qt::DisplayRole)
         return QVariant();

     if (orientation == Qt::Horizontal)
	 {
		 if(section < _header.size())
			return _header[section];
	 }

	 return QVariant();
}

/***********************************************************
flags
***********************************************************/
Qt::ItemFlags MixedTableModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	if(index.column() > 0 && index.row() > 2)
		return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
	else
		return QAbstractItemModel::flags(index);
}

/***********************************************************
setData
***********************************************************/
bool MixedTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (index.isValid() && role == Qt::EditRole) 
	{
		_objMatrix[index.column()][index.row()] = value;
		emit dataChanged(index, index);
		return true;
	}

	return false;
}

/***********************************************************
get a string
***********************************************************/
QVariant MixedTableModel::GetData(const QModelIndex &index)
{
	if (index.isValid()) 
		return _objMatrix[index.column()][index.row()];

	return QVariant();
}

/***********************************************************
get a string
***********************************************************/
QVariant MixedTableModel::GetData(int col, int row)
{
	return _objMatrix[col][row];
}


/***********************************************************
set a string
***********************************************************/
void MixedTableModel::SetData(int col, int row, QVariant v)
{
	_objMatrix[col][row] = v;
	QModelIndex index = createIndex(row, col);
	emit dataChanged(index, index);
}


/***********************************************************
insertRows
***********************************************************/
bool MixedTableModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	beginInsertRows(QModelIndex(), position, position+rows-1);

	for (int row = 0; row < rows; ++row) 
	{
		for(size_t i=0; i<_objMatrix.size(); ++i)
			_objMatrix[i].insert(position, "");
	}

	endInsertRows();
	return true;
}

/***********************************************************
removeRows
***********************************************************/
bool MixedTableModel::removeRows(int position, int rows, const QModelIndex &parent)
{
	beginRemoveRows(QModelIndex(), position, position+rows-1);

	for (int row = 0; row < rows; ++row) 
	{
		for(size_t i=0; i<_objMatrix.size(); ++i)
			_objMatrix[i].removeAt(position);
	}

	endRemoveRows();
	return true;
}


/***********************************************************
clear the table content
***********************************************************/
void MixedTableModel::Clear()
{
	if(_objMatrix.size() > 0 && _objMatrix[0].size() > 0)
	{
		beginRemoveRows(QModelIndex(), 0, _objMatrix[0].size()-1);

		for(size_t i=0; i<_objMatrix.size(); ++i)
			_objMatrix[i].clear();

		endRemoveRows();
	}

	reset();
}


/***********************************************************
add a row
***********************************************************/
void MixedTableModel::AddRow(const QVariantList &data)
{
	if(_objMatrix.size() == data.size())
	{
		// object does not exist - insert it
		beginInsertRows(QModelIndex(), _objMatrix[0].size(), _objMatrix[0].size());

		for(size_t i=0; i<_objMatrix.size(); ++i)
			_objMatrix[i].push_back(data[i]);

		endInsertRows();
	}
}




/***********************************************************
PostManagement
***********************************************************/
QString FileDialogOptionsModel::PostManagement(const QString & selectedfile)
{
	QString outfile;

	// check if choosen file is in the directory data
	if(selectedfile.contains(QDir::currentPath()+"/Data/"))
	{
		outfile = selectedfile;
		outfile = outfile.remove(QDir::currentPath()+"/Data/");
	}
	else
	{
		//copy the file over
		try
		{
			// get all files with same name
			std::vector<std::string> files;
			QString fpath = selectedfile.section('/', 0, -2 );
			{
				QString filenoext = selectedfile.section('/', -1);
				filenoext = filenoext.section('.', 0, 0);


				fs::path full_path( fpath.toAscii().data() );

				if( fs::exists( full_path ) )
				{
					if ( fs::is_directory( full_path ) )
					{
						fs::directory_iterator end_iter;
						for ( fs::directory_iterator dir_itr( full_path ); 
											dir_itr != end_iter; ++dir_itr )
						{
							if ( fs::is_regular_file( dir_itr->status() ) )
							{
								if(dir_itr->path().stem() == filenoext.toAscii().data())
									files.push_back(dir_itr->path().filename());
							}
						}
					}
				}
			}

			for(size_t curs=0; curs<files.size(); ++curs)
			{
				QString tmp = fpath + "/";
				tmp += files[curs].c_str();
				QString tmp2 = StartingDirectory + "/";
				tmp2 += files[curs].c_str();
				boost::filesystem::copy_file(tmp.toAscii().data(), tmp2.toAscii().data());
			}

			QString filename = StartingDirectory + "/" + selectedfile.section('/', -1);
			outfile = filename.section('/', 1);
		}
		catch(...)
		{
			QErrorMessage msgdial;
			msgdial.showMessage ( "Error copying the file to the data directory!" );
			outfile = "";
		}
	}

	return outfile;
}



/***********************************************************
PostManagement
***********************************************************/
QString FileDialogOptionsIcon::PostManagement(const QString & selectedfile)
{
	QString outfile;

	// check if choosen file is in the directory data
	if(selectedfile.contains(QDir::currentPath()+"/Data/"))
	{
		outfile = selectedfile;
		outfile = outfile.remove(QDir::currentPath()+"/Data/");
	}
	else
	{
		//copy the file over and resize it
		try
		{
			QString filename = selectedfile.section('/', -1);
			filename = filename.section('.', 0, 0);

			outfile = OutDirectory + "/" + filename + ".png";
			QString outfile2 = OutDirectory + "/" + filename + "_mini.png";


			QImage image(selectedfile);
			QImage scaledimg = image.scaled(QSize(100, 100), Qt::KeepAspectRatio, Qt::SmoothTransformation );
			scaledimg.save(QDir::currentPath()+"/"+outfile);

			QImage smallscaledimg = image.scaled(QSize(25, 25), Qt::KeepAspectRatio, Qt::SmoothTransformation );
			smallscaledimg.save(QDir::currentPath()+"/"+outfile2);

			outfile = outfile.remove("Data/");
		}
		catch(...)
		{
			QErrorMessage msgdial;
			msgdial.showMessage ( "Error copying the file to the data directory!" );
			outfile = "";
		}
	}

	return outfile;
}



/***********************************************************
Constructor
***********************************************************/
CustomDelegate::CustomDelegate(QObject *parent, QAbstractItemModel * model)
     : QStyledItemDelegate(parent), _model(model), _accepted(false)
{
}


/***********************************************************
Constructor
***********************************************************/
QWidget *CustomDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
											const QModelIndex &index) const
{
	std::map<QModelIndex, boost::shared_ptr<CustomStringListModel> >::const_iterator it = _customs.find(index);
	if(it != _customs.end())
	{
		QComboBox *editor = new QComboBox(parent);
		editor->setModel(it->second.get());
		editor->setEditable(false);

		connect(editor, SIGNAL(	activated(int)) , this, SLOT(objmodified(int)));
		return editor;
	}

	 std::map<QModelIndex, boost::shared_ptr<FileDialogOptionsBase> >::const_iterator itf = _customsfiledialog.find(index);
	if(itf != _customsfiledialog.end())
	{
		QFileDialog *editor = new QFileDialog(parent, itf->second->Title);
		editor->setAcceptMode(QFileDialog::AcceptOpen);
		editor->setFileMode(QFileDialog::ExistingFile);
		editor->setNameFilter(itf->second->FileFilter);
		editor->setViewMode(QFileDialog::List);
		editor->setModal(true);

		connect(editor, SIGNAL(	currentChanged(QString)) , this, SLOT(fileobjmodified(QString)));
		connect(editor, SIGNAL(	fileSelected(QString)) , this, SLOT(fileobjacceptedbegin(QString)));
		connect(editor, SIGNAL(	accepted()) , this, SLOT(fileobjacceptedend()));
		connect(editor, SIGNAL(	rejected()) , this, SLOT(fileobjrejected()));
		

		return editor;
	}

	QVariant data = _model->data(index, Qt::DisplayRole);
	if(data.type() == QVariant::Double)
	{
		QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
		editor->setMinimum(-100000);
		editor->setMaximum(100000);
		editor->setSingleStep(0.1);
		connect(editor, SIGNAL(	valueChanged(double)) , this, SLOT(objmodified2(double)));
		return editor;
	}

	if(data.type() == QVariant::Int)
	{
		QSpinBox *editor = new QSpinBox(parent);
		editor->setMinimum(-1000000);
		editor->setMaximum(1000000);
		editor->setSingleStep(1);
		connect(editor, SIGNAL(	valueChanged(int)) , this, SLOT(objmodified(int)));
		return editor;
	}



	return QStyledItemDelegate::createEditor(parent, option, index);
}


/***********************************************************
Constructor
***********************************************************/
void CustomDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	std::map<QModelIndex, boost::shared_ptr<CustomStringListModel> >::const_iterator it = _customs.find(index);
	if(it != _customs.end())
	{
		 QString value = index.model()->data(index, Qt::DisplayRole).toString();

		 QComboBox *comboBox = static_cast<QComboBox*>(editor);
		 int index = comboBox->findText(value);
		 if(index >= 0)
			comboBox->setCurrentIndex(index);

		 return;
	}

	std::map<QModelIndex, boost::shared_ptr<FileDialogOptionsBase> >::const_iterator itf = _customsfiledialog.find(index);
	if(itf != _customsfiledialog.end())
	{
		QString value = index.model()->data(index, Qt::DisplayRole).toString();
		QFileDialog *dialog = static_cast<QFileDialog*>(editor);
		dialog->setGeometry( 100, 100, 500, 300 );

		if(itf->second->PreviousFile == "")
			itf->second->PreviousFile = value;

		if(value != "")
		{
			dialog->setDirectory( QDir::currentPath()+"/Data/"+value.section('/', 0, -2) );
			dialog->selectFile ( value.section('/', -1) );
		}
		else
		{
			dialog->setDirectory(QDir::currentPath()+"/"+itf->second->StartingDirectory);
		}

		return;
	}


	QVariant data = _model->data(index, Qt::DisplayRole);
	if(data.type() == QVariant::Double)
	{
		 double value = index.model()->data(index, Qt::DisplayRole).toDouble();

		 QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
		 spinBox->setValue(value);

		 return;
	}

	if(data.type() == QVariant::Int)
	{
		 int value = index.model()->data(index, Qt::DisplayRole).toDouble();

		 QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
		 spinBox->setValue(value);

		 return;
	}


	QStyledItemDelegate::setEditorData(editor, index);
}


/***********************************************************
Constructor
***********************************************************/
void CustomDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const
{
	std::map<QModelIndex, boost::shared_ptr<CustomStringListModel> >::const_iterator it = _customs.find(index);
	if(it != _customs.end())
	{
		 QComboBox *comboBox = static_cast<QComboBox*>(editor);
		 QString value = comboBox->currentText();
		 model->setData(index, value);
		
		return;
	}

	std::map<QModelIndex, boost::shared_ptr<FileDialogOptionsBase> >::const_iterator itf = _customsfiledialog.find(index);
	if(itf != _customsfiledialog.end())
	{
		if(_selectedfile != "")
		{
			QString outfile = itf->second->PostManagement(_selectedfile);
			if(outfile != "")
				model->setData(index, outfile);
		}
		else
		{
			if(!_accepted)
			{
				// file rejected - reset to previous
				model->setData(index, itf->second->PreviousFile);
			}

			itf->second->PreviousFile = "";
		}

		return;
	}

	QVariant data = _model->data(index, Qt::DisplayRole);
	if(data.type() == QVariant::Double)
	{
		 QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
		 spinBox->interpretText();
		 double value = spinBox->value();

		 model->setData(index, value);
		
		return;
	}

	if(data.type() == QVariant::Int)
	{
		 QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
		 spinBox->interpretText();
		 int value = spinBox->value();

		 model->setData(index, value);
		
		return;
	}


	
	QStyledItemDelegate::setModelData(editor, model, index);
}


/***********************************************************
Constructor
***********************************************************/
void CustomDelegate::updateEditorGeometry(QWidget *editor,
         const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}



/***********************************************************
Constructor
***********************************************************/
void CustomDelegate::Clear()
{
	_customs.clear();
	_customsfiledialog.clear();
}

/***********************************************************
Constructor
***********************************************************/
void CustomDelegate::SetCustomIndex(QModelIndex index, boost::shared_ptr<CustomStringListModel> list)
{
	_customs[index] = list;
}


/***********************************************************
used in the case of file dialog
***********************************************************/
 void CustomDelegate::SetCustomIndex(QModelIndex index, boost::shared_ptr<FileDialogOptionsBase> filefilter)
{
	_customsfiledialog[index] = filefilter;
}



/***********************************************************
data changed in object view
***********************************************************/
void CustomDelegate::objmodified(int flag)
{
	QWidget *editor = static_cast<QWidget *>(sender());
	emit commitData(editor);
}


/***********************************************************
data changed in object view
***********************************************************/
void CustomDelegate::objmodified2(double flag)
{
	QWidget *editor = static_cast<QWidget *>(sender());
	emit commitData(editor);
}


/***********************************************************
data changed in object view
***********************************************************/
void CustomDelegate::fileobjmodified(QString selectedfile)
{
	if(selectedfile != "" && selectedfile.contains("."))
	{
		_selectedfile = selectedfile;
		QWidget *editor = static_cast<QWidget *>(sender());
		emit commitData(editor);

		_selectedfile = "";
	}
}

/***********************************************************
accept1 signal
***********************************************************/
void CustomDelegate::fileobjacceptedbegin(QString selectedfile)
{
	_accepted = true;
}

/***********************************************************
accept2 signal
***********************************************************/
void CustomDelegate::fileobjacceptedend()
{
	_accepted = false;
}

/***********************************************************
accept2 signal
***********************************************************/
void CustomDelegate::fileobjrejected()
{
	_accepted = false;
}



/***********************************************************
Constructor
***********************************************************/
EditorHandler::EditorHandler(QWidget *parent, Qt::WindowFlags flags)
 : QMainWindow(parent, flags), _modified(false), 
 _mapNameList(new CustomStringListModel()),
 _currspawningidx(0), _currtriggeridx(0),
	_updatetriggerdialogonnewaction(-1), _triggerNameList(new CustomStringListModel()),
	_actortypeList(new CustomStringListModel()), _actordtypeList(new CustomStringListModel()),
	_actorptypeList(new CustomStringListModel()), _cscriptList(new CustomStringListModel()),
	_updateactiondialogonnewscript(-1), _actormodeList(new CustomStringListModel()), 
	_conditiontypeList(new CustomStringListModel()), _cscripttypeList(new CustomStringListModel()),
	_actiontypeList(new CustomStringListModel()), _actorModelNameList(new CustomStringListModel()),
	_actorModelOutfitList(new CustomStringListModel()), _actorModelWeaponList(new CustomStringListModel()),
	_actorModelModeList(new CustomStringListModel()), _currentchoosentext(Localizer::Map),
	_text_mapNameList(new CustomStringListModel()), _text_questNameList(new CustomStringListModel()),
	_text_inventoryNameList(new CustomStringListModel()), _text_nameNameList(new CustomStringListModel()),
	_itemNameList(new CustomStringListModel()), _consumable_itemlistmodel(new CustomStringListModel()),
	_mount_itemlistmodel(new CustomStringListModel()), _special_itemlistmodel(new CustomStringListModel())
{
	QStringList actlist;
	actlist << "Static" << "Scripted" << "Movable";
	_actortypeList->setStringList(actlist);
	QStringList acttypelist;
	acttypelist << "No" << "Osg Model" << "Sprite" << "Lba1 Model" << "Lba2 Model";
	_actordtypeList->setStringList(acttypelist);
	QStringList actptypelist;
	actptypelist << "No Shape" << "Box" << "Capsule" << "Sphere" << "Triangle Mesh";
	_actorptypeList->setStringList(actptypelist);
	QStringList actmodelist;
	actmodelist << "None" << "Normal" << "Sport" << "Angry" << "Discrete" << "Protopack" << "Horse" << "Dinofly";
	_actormodeList->setStringList(actmodelist);


	QStringList condlist;
	condlist << "No" << "AlwaysTrueCondition" << "NegateCondition" << "AndCondition" << "OrCondition";
	_conditiontypeList->setStringList(condlist);
	
	QStringList cslist;
	cslist << "No" << "GoUpLadderScript" << "TakeExitUpScript" << "TakeExitDownScript" << "CustomScript";
	_cscripttypeList->setStringList(cslist);

	QStringList actilist;
	actilist << "No" << "TeleportAction" << "ClientScriptAction" << "CustomAction" 
			<< "DisplayTextAction" << "ConditionalAction";
	_actiontypeList->setStringList(actilist);

	QStringList consu_iteml;
	consu_iteml << "Restore % of Health" << "Restore % of Magic" << "Restore % of Health&Magic" 
			<< "Restore Health" << "Restore Magic" << "Restore Health&Magic";
	_consumable_itemlistmodel->setStringList(consu_iteml);

	QStringList mount_iteml;
	mount_iteml << "Protopack" << "Horse" << "Dinofly";
	_mount_itemlistmodel->setStringList(mount_iteml);

	QStringList special_iteml;
	special_iteml << "Letter writer";
	_special_itemlistmodel->setStringList(special_iteml);

	
	_uieditor.setupUi(this);

	_addtriggerdialog = new QDialog(this);
	_uiaddtriggerdialog.setupUi(_addtriggerdialog);

	_openworlddialog = new QDialog(this);
	_uiopenworlddialog.setupUi(_openworlddialog);

	_addspawningdialog = new QDialog(this);
	_uiaddspawningdialog.setupUi(_addspawningdialog);


	_addmapdialog = new QDialog(this);
	_ui_addmapdialog.setupUi(_addmapdialog);

	_addtpdialog = new QDialog(this);
	_ui_addtpdialog.setupUi(_addtpdialog);

	_addworlddialog = new QDialog(this);
	_ui_addworlddialog.setupUi(_addworlddialog);

	_addactordialog = new QDialog(this);
	_ui_addactordialog.setupUi(_addactordialog);

	_addtextdialog = new QDialog(this);
	_ui_addtextdialog.setupUi(_addtextdialog);

	_additemdialog = new QDialog(this);
	_ui_additemdialog.setupUi(_additemdialog);

	_addstartitemdialog = new QDialog(this);
	_ui_addstartitemdialog.setupUi(_addstartitemdialog);
	_ui_addstartitemdialog.comboBox_itemname->setModel(_itemNameList.get());


	// set model for map list
	{
		 QStringList header;
		 header << "Name" << "Description";
		_maplistmodel = new StringTableModel(header);
		_uieditor.tableView_MapList->setModel(_maplistmodel);
		QHeaderView * mpheaders = _uieditor.tableView_MapList->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
	}

	// set model for tp list
	{
		 QStringList header;
		 header << "Name" << "Map" << "Spawn";
		_tplistmodel = new StringTableModel(header);
		_uieditor.tableView_TeleportList->setModel(_tplistmodel);
		QHeaderView * mpheaders = _uieditor.tableView_TeleportList->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
	}

	// set model for spawninglist
	{
		 QStringList header;
		 header << "Name" << "X" << "Y" << "Z";
		_mapspawninglistmodel = new StringTableModel(header);
		_uieditor.tableView_SpawningList->setModel(_mapspawninglistmodel);
		QHeaderView * mpheaders = _uieditor.tableView_SpawningList->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
	}

	// set model for text list
	{
		 QStringList header;
		 header << "Text";
		_text_maplistmodel = new StringTableModel(header);
		_text_questlistmodel = new StringTableModel(header);
		_text_inventorylistmodel = new StringTableModel(header);
		_text_namelistmodel = new StringTableModel(header);

		_uieditor.tableView_TextList->setModel(_text_maplistmodel);
		QHeaderView * mpheaders = _uieditor.tableView_TextList->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
	}


	// set model for objectmap
	{
		 QVector<QVariant> header;
		 header << "Property" << "Value";
		_objectmodel = new TreeModel(header);
		_uieditor.treeView_object->setModel(_objectmodel);
		QHeaderView * mpheaders = _uieditor.treeView_object->header();
		mpheaders->setResizeMode(QHeaderView::Stretch);

		_objectcustomdelegate = new CustomDelegate(0, _objectmodel);
		_uieditor.treeView_object->setItemDelegate(_objectcustomdelegate);

		_uieditor.treeView_object->setEditTriggers(QAbstractItemView::CurrentChanged | 
													QAbstractItemView::DoubleClicked | 
													QAbstractItemView::SelectedClicked);
	}


	// set model for triggerlist
	{
		 QStringList header;
		 header << "Name" << "Type";
		_triggerlistmodel = new StringTableModel(header);
		_uieditor.tableViewTriggerList->setModel(_triggerlistmodel);
		QHeaderView * mpheaders = _uieditor.tableViewTriggerList->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
	}
		
	
	// set model for spawninglist
	{
		 QStringList header;
		 header << "Name" << "X" << "Y" << "Z";
		_mapspawninglistmodel = new StringTableModel(header);
		_uieditor.tableView_SpawningList->setModel(_mapspawninglistmodel);
		QHeaderView * mpheaders = _uieditor.tableView_SpawningList->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
	}


	// set model for actorlist
	{
		 QStringList header;
		 header << "Name" << "Type" << "DisplayType" << "PhysicalType";
		_actorlistmodel = new StringTableModel(header);
		_uieditor.tableView_ActorList->setModel(_actorlistmodel);
		QHeaderView * mpheaders = _uieditor.tableView_ActorList->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
	}

	// set model for item list
	{
		 QStringList header;
		 header << "Name" << "Type";
		_itemlistmodel = new StringTableModel(header);
		_uieditor.tableView_ItemList->setModel(_itemlistmodel);
		QHeaderView * mpheaders = _uieditor.tableView_ItemList->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
	}	

	// set model for start item
	{
		 QStringList header;
		 header << "Name" << "Number";
		_startitemlistmodel = new StringTableModel(header);
		_uieditor.tableView_ItemList_starting->setModel(_startitemlistmodel);
		QHeaderView * mpheaders = _uieditor.tableView_ItemList_starting->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
	}

	


	// reset world info
	ResetWorld();


	// show myself
	showMaximized();

	// connect signals and slots
	connect(_uieditor.actionQuit, SIGNAL(triggered()), this, SLOT(quit())); 
	connect(_uieditor.actionNew_World, SIGNAL(triggered()), this, SLOT(NewWorldAction())); 
	connect(_uieditor.actionLoad_World, SIGNAL(triggered()), this, SLOT(OpenWorldAction())); 
	connect(_uieditor.actionSave, SIGNAL(triggered()), this, SLOT(SaveWorldAction())); 
	connect(_uieditor.actionCustom_Lua_for_server, SIGNAL(triggered()), this, SLOT(SaveWorldAction())); 
	connect(_uieditor.actionCustom_Lua_for_server, SIGNAL(triggered()), this, SLOT(OpenCustomServerLua())); 
	connect(_uieditor.actionCustom_Lua_for_client, SIGNAL(triggered()), this, SLOT(OpenCustomClientLua())); 
	connect(_uieditor.actionRefresh_client_script, SIGNAL(triggered()), this, SLOT(RefreshClientScript())); 

	connect(_uieditor.pushButton_info_go, SIGNAL(clicked()) , this, SLOT(info_go_clicked()));
	connect(_uieditor.radioButton_info_player, SIGNAL(toggled(bool)) , this, SLOT(info_camera_toggled(bool)));

	connect(_uieditor.pushButton_addTrigger, SIGNAL(clicked()) , this, SLOT(addtrigger_button_clicked()));
	connect(_uieditor.pushButton_removeTrigger, SIGNAL(clicked()) , this, SLOT(removetrigger_button_clicked()));	
	connect(_uieditor.pushButton_selectTrigger, SIGNAL(clicked()) , this, SLOT(selecttrigger_button_clicked()));		

	connect(_uieditor.pushButton_addSpwaning, SIGNAL(clicked()) , this, SLOT(addspawning_button_clicked()));
	connect(_uieditor.pushButton_removeSpwaning, SIGNAL(clicked()) , this, SLOT(removespawning_button_clicked()));	
	connect(_uieditor.pushButton_selectSpwaning, SIGNAL(clicked()) , this, SLOT(selectspawning_button_clicked()));		

	connect(_uieditor.pushButton_addmap, SIGNAL(clicked()) , this, SLOT(addmap_button_clicked()));
	connect(_uieditor.pushButton_removemap, SIGNAL(clicked()) , this, SLOT(removemap_button_clicked()));	

	connect(_uieditor.pushButton_addtp, SIGNAL(clicked()) , this, SLOT(TpAdd_button()));
	connect(_uieditor.pushButton_removetp, SIGNAL(clicked()) , this, SLOT(TpRemove_button()));	
	connect(_uieditor.pushButton_edittp, SIGNAL(clicked()) , this, SLOT(TpEdit_button()));	

	connect(_uieditor.pushButton_addtext, SIGNAL(clicked()) , this, SLOT(TextAdd_button()));
	connect(_uieditor.pushButton_removetext, SIGNAL(clicked()) , this, SLOT(TextRemove_button()));	
	connect(_uieditor.pushButton_edittext, SIGNAL(clicked()) , this, SLOT(TextEdit_button()));	



	connect(_uieditor.pushButton_addActor, SIGNAL(clicked()) , this, SLOT(ActorAdd_button()));
	connect(_uieditor.pushButton_removeActor, SIGNAL(clicked()) , this, SLOT(ActorRemove_button()));	
	connect(_uieditor.pushButton_selectActor, SIGNAL(clicked()) , this, SLOT(ActorSelect_button()));


	connect(_uieditor.pushButton_additem, SIGNAL(clicked()) , this, SLOT(ItemAdd_button()));
	connect(_uieditor.pushButton_removeitem, SIGNAL(clicked()) , this, SLOT(ItemRemove_button()));	
	connect(_uieditor.pushButton_selectitem, SIGNAL(clicked()) , this, SLOT(ItemSelect_button()));

	connect(_uieditor.pushButton_additem_2, SIGNAL(clicked()) , this, SLOT(StartItemAdd_button()));
	connect(_uieditor.pushButton_removeitem_2, SIGNAL(clicked()) , this, SLOT(StartItemRemove_button()));	


	//! Actor add button push
	 void ActorAdd_button_accepted();


	connect(_uieditor.textEdit_worlddescription, SIGNAL(textChanged()) , this, SLOT(WorldDescriptionChanged()));	
	connect(_uieditor.textEdit_worldnews, SIGNAL(textChanged()) , this, SLOT(WorldNewsChanged()));	

	
	connect(_uieditor.pushButton_goto_tp, SIGNAL(clicked()) , this, SLOT(goto_tp_button_clicked()));
	connect(_uieditor.pushButton_goto_map, SIGNAL(clicked()) , this, SLOT(goto_map_button_clicked()));

	connect(_uieditor.tableView_TeleportList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(goto_tp_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_MapList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(goto_map_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_SpawningList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selectspawning_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableViewTriggerList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selecttrigger_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_ActorList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selectactor_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_TextList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selecttext_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_ItemList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selectitem_double_clicked(const QModelIndex&)));


	connect(_objectmodel, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)) , 
								this, SLOT(objectdatachanged(const QModelIndex &, const QModelIndex &)));


	connect(_uiaddtriggerdialog.buttonBox, SIGNAL(accepted()) , this, SLOT(addtrigger_accepted()));
	connect(_uiopenworlddialog.buttonBox, SIGNAL(accepted()) , this, SLOT(OpenWorld()));
	connect(_uiaddspawningdialog.buttonBox, SIGNAL(accepted()) , this, SLOT(AddSpawning_clicked()));
	connect(_ui_addmapdialog.buttonBox, SIGNAL(accepted()) , this, SLOT(addmap_accepted()));
	connect(_ui_addtpdialog.buttonBox, SIGNAL(accepted()) , this, SLOT(TpAdd_button_accepted()));
	connect(_ui_addworlddialog.buttonBox, SIGNAL(accepted()) , this, SLOT(addworld_accepted()));
	connect(_ui_addactordialog.buttonBox, SIGNAL(accepted()) , this, SLOT(ActorAdd_button_accepted()));
	connect(_ui_addtextdialog.buttonBox, SIGNAL(accepted()) , this, SLOT(TextAdd_button_accepted()));
	connect(_ui_additemdialog.buttonBox, SIGNAL(accepted()) , this, SLOT(ItemAdd_button_accepted()));
	connect(_ui_addstartitemdialog.buttonBox, SIGNAL(accepted()) , this, SLOT(StartItemAdd_button_accepted()));

	connect(_uieditor.comboBox_startingmap, SIGNAL(activated(int)) , this, SLOT(StartingMapModified(int)));		
	connect(_uieditor.comboBox_startingspawning, SIGNAL(activated(int)) , this, SLOT(StartingSpawnModified(int)));	
	connect(_uieditor.comboBox_modeloutfit, SIGNAL(activated(int)) , this, SLOT(StartingOutfitModified(int)));		
	connect(_uieditor.comboBox_modelweapon, SIGNAL(activated(int)) , this, SLOT(StartingWeaponModified(int)));	
	connect(_uieditor.comboBox_modelmode, SIGNAL(activated(int)) , this, SLOT(StartingModeModified(int)));		
	connect(_uieditor.spinBox_startinglife, SIGNAL(valueChanged(int)) , this, SLOT(StartingLifeModified(int)));	
	connect(_uieditor.spinBox_startingMana, SIGNAL(valueChanged(int)) , this, SLOT(StartingLifeModified(int)));	

	connect(_ui_addtpdialog.comboBox_map, SIGNAL(activated(int)) , this, SLOT(TpDialogMapChanged(int)));

	connect(_uieditor.textEdit_map_description, SIGNAL(textChanged()) , this, SLOT(MapDescriptionChanged()));
	connect(_uieditor.comboBox_maptype, SIGNAL(activated(int)) , this, SLOT(MapTypeChanged(int)));
	connect(_uieditor.checkBox_map_instancied, SIGNAL(stateChanged(int)) , this, SLOT(MapInstanceChanged(int)));
	connect(_uieditor.radioButton_camtype_ortho, SIGNAL(toggled(bool)) , this, SLOT(MapCameraTypeChanged(bool)));
	connect(_uieditor.radioButton_camtype_persp, SIGNAL(toggled(bool)) , this, SLOT(MapCameraTypeChanged(bool)));
	connect(_uieditor.radioButton_camtype_3d, SIGNAL(toggled(bool)) , this, SLOT(MapCameraTypeChanged(bool)));

	connect(_uieditor.comboBox_choosetexttype, SIGNAL(activated(int)) , this, SLOT(TextTypeModified(int)));	

}

/***********************************************************
Destructor
***********************************************************/
EditorHandler::~EditorHandler()
{
	delete _addtriggerdialog;
}



/***********************************************************
set the osg window
***********************************************************/
void EditorHandler::SetOsgWindow(GraphicsWindowQt *osgwindow)
{
	_osgwindow = osgwindow;
	_uieditor.groupBox_game->layout()->addWidget(_osgwindow->getGraphWidget());
	_osgwindow->getGraphWidget()->show();
}



/***********************************************************
ui button clicked
***********************************************************/
void EditorHandler::addtrigger_button_clicked()
{
	if(!IsMapOpened())
		return;

	//clear data
	_uiaddtriggerdialog.lineEdit_triggername->setText("");
	_addtriggerdialog->show();
}



/***********************************************************
ui button clicked
***********************************************************/
void EditorHandler::removetrigger_button_clicked()
{
	QItemSelectionModel *selectionModel = _uieditor.tableViewTriggerList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();
	if(indexes.size() > 1)
	{
		// inform server
		long id = _triggerlistmodel->GetId(indexes[0]);
		RemoveTrigger(id);

		// remove row from table
		_triggerlistmodel->removeRows(indexes[0].row(), 1);

		// clear object
		ClearObjectIfSelected("Trigger", id);
	}
}


/***********************************************************
on selecttrigger_double_clicked
***********************************************************/
void EditorHandler::selecttrigger_double_clicked(const QModelIndex & itm)
{
	selecttrigger_button_clicked();
}

/***********************************************************
ui button clicked
***********************************************************/
void EditorHandler::selecttrigger_button_clicked()
{
	QItemSelectionModel *selectionModel = _uieditor.tableViewTriggerList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();
	if(indexes.size() > 1)
	{
		long id = _triggerlistmodel->GetId(indexes[0]);
		SelectTrigger(id);
	}
}



/***********************************************************
dialog accepted
***********************************************************/
void EditorHandler::addtrigger_accepted()
{
	QString triggername = _uiaddtriggerdialog.lineEdit_triggername->text();

	// user forgot to set a name
	if(triggername == "")
		return;

	if(_triggerNameList->stringList().contains(triggername))
	{
		QMessageBox::warning(this, tr("Name already used"),
			tr("The name you entered for the trigger is already used. Please enter a unique name."),
			QMessageBox::Ok);
		return;
	}

	_addtriggerdialog->hide();



	long id = _currtriggeridx+1;
	TriggerInfo triggerinf;
	triggerinf.id = id;
	triggerinf.CheckNpcs = true;
	triggerinf.CheckPlayers = true;
	triggerinf.CheckMovableObjects = false;
	triggerinf.name = triggername.toAscii().data();

	switch(_uiaddtriggerdialog.comboBox_type->currentIndex())
	{
		case 0: // zone trigger
		{
			boost::shared_ptr<TriggerBase> trig(new ZoneTrigger(triggerinf, 1, 1, 1, true));
			trig->SetPosition(_posX, _posY, _posZ);
			AddNewTrigger(trig);
		}
		break;

		case 1: // activation trigger
		{
			boost::shared_ptr<TriggerBase> trig(new ActivationTrigger(triggerinf, 1.5, "Normal", "None"));
			trig->SetPosition(_posX, _posY, _posZ);
			AddNewTrigger(trig);
		}
		break;

		case 2: // ZoneActionTrigger
		{
			boost::shared_ptr<TriggerBase> trig(new ZoneActionTrigger(triggerinf, 1, 1, 1, "Normal", "None"));
			trig->SetPosition(_posX, _posY, _posZ);
			AddNewTrigger(trig);
		}
		break;

		case 3: // TimerTrigger
		{
			boost::shared_ptr<TriggerBase> trig(new TimerTrigger(triggerinf, 1000));
			trig->SetPosition(_posX, _posY, _posZ);
			AddNewTrigger(trig);
		}
		break;

	}

	SelectTrigger(id);
}




/***********************************************************
override close event
***********************************************************/
void EditorHandler::closeEvent(QCloseEvent* event)
{
	if(SaveBeforeQuit())
	{
		EventsQueue::getReceiverQueue()->AddEvent(new QuitGameEvent());
	}
	else
	{
		event->ignore();
	}
}


/***********************************************************
refresh display
***********************************************************/
void EditorHandler::RefreshDisplay()
{
	_uieditor.groupBox_game->setMinimumHeight(600);
}

/***********************************************************
quit editor
***********************************************************/
void EditorHandler::quit()
{
	if(SaveBeforeQuit())
	{
		EventsQueue::getReceiverQueue()->AddEvent(new QuitGameEvent());
	}
}


/***********************************************************
NewWorldAction
***********************************************************/
void EditorHandler::NewWorldAction()
{
	if(SaveBeforeQuit())
	{
		_ui_addworlddialog.lineEdit_worldname->setText("");
		_addworlddialog->show();
	}
}


/***********************************************************
OpenWorldAction
***********************************************************/
void EditorHandler::OpenWorldAction()
{
	if(SaveBeforeQuit())
	{
		std::vector<LbaNet::WorldDesc> list;
		DataLoader::getInstance()->GetAvailableWorlds(list);

		_uiopenworlddialog.comboBoxWorldToOpen->clear();

		for(size_t i=0; i<list.size(); ++i)
			_uiopenworlddialog.comboBoxWorldToOpen->addItem(list[i].WorldName.c_str());

		_openworlddialog->show();
	}
}


/***********************************************************
SaveWorldAction
***********************************************************/
void EditorHandler::SaveWorldAction()
{
	if(!IsWorldOpened())
		return;

	if(_modified)
	{
		// save xml file
		DataLoader::getInstance()->SaveWorldInformation(_winfo.Description.WorldName, _winfo);

		// save current map
		std::string mapname = _uieditor.label_mapname->text().toAscii().data();
		if(mapname != "")
			SaveMap("./Data/Worlds/" + _winfo.Description.WorldName + "/Lua/" + mapname + "_server.lua");

		// save text
		Localizer::getInstance()->SaveTexts();

		// save inventory
		InventoryItemHandler::getInstance()->SaveInformation();

		SetSaved();
	}
}



/***********************************************************
Check if we need to save before quit
***********************************************************/
bool EditorHandler::SaveBeforeQuit()
{
	if(Modified())
	{
		int r = QMessageBox::warning(this, tr("Save changes?"),
		tr("Do you want to save your changes before quitting?"),
		QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);

		if(r == QMessageBox::Yes)
		{
			SaveWorldAction();
		}
		else if (r == QMessageBox::Cancel)
		{
			return false;
		}
	}

	return true;
}


/***********************************************************
Check if we need to save before quit map
***********************************************************/
bool EditorHandler::SaveMapBeforeQuit(bool alreadychangedmap)
{
	if(_mapmodified)
	{
		int r = 0;
		if(alreadychangedmap)
		{
			r = QMessageBox::warning(this, tr("Save changes?"),
			tr("Do you want to save your changes for the current map? Else all changes will be lost."),
			QMessageBox::Yes, QMessageBox::No);
		}
		else
		{
			r = QMessageBox::warning(this, tr("Save changes?"),
			tr("Do you want to save your changes for the current map? Else all changes will be lost."),
			QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
		}

		if(r == QMessageBox::Yes)
		{
			SaveWorldAction();
		}
		else if (r == QMessageBox::No)
		{
			_mapmodified = false;
		}
		else if (r == QMessageBox::Cancel)
		{
			return false;
		}
	}

	return true;
}



/***********************************************************
return true if some changes are not saved
***********************************************************/
bool EditorHandler::Modified()
{
	return _modified;
}


/***********************************************************
set the work as modified
***********************************************************/
void EditorHandler::SetModified()
{
	if(!_modified)
	{
		setWindowTitle(windowTitle () + " *");
		_modified = true;
	}
}

/***********************************************************
set the work as saved
***********************************************************/
void EditorHandler::SetSaved()
{
	if(_modified)
	{
		setWindowTitle(windowTitle().remove(windowTitle().size()-2, 2));
		_modified = false;
	}

	_mapmodified = false;
}


/***********************************************************
set the work as modified
***********************************************************/
void EditorHandler::SetMapModified()
{
	SetModified();
	_mapmodified = true;
}



/***********************************************************
on open world
***********************************************************/
void EditorHandler::OpenWorld()
{
	std::string choosenworld = _uiopenworlddialog.comboBoxWorldToOpen->currentText().toAscii().data();
	EventsQueue::getReceiverQueue()->AddEvent(new ChangeWorldEvent(choosenworld));

	ResetWorld();
	SetWorldInfo(choosenworld);

	_openworlddialog->hide();
	SetSaved();
}


/***********************************************************
refresh gui with world info
***********************************************************/
void EditorHandler::SetWorldInfo(const std::string & worldname)
{
	LbaNet::WorldInformation tmpinfo;
	DataLoader::getInstance()->GetWorldInformation(worldname, tmpinfo);
	_winfo = tmpinfo;

	setWindowTitle(("LBANet Editor - " + worldname).c_str());

	_uieditor.label_worldname->setText(_winfo.Description.WorldName.c_str());

	QString descs = QString::fromUtf8(_winfo.Description.Description.c_str());
	descs.replace(QString(" @ "), QString("\n"));
	_uieditor.textEdit_worlddescription->setText(descs);

	QString newss = QString::fromUtf8(_winfo.Description.News.c_str());
	newss.replace(QString(" @ "), QString("\n"));
	_uieditor.textEdit_worldnews->setText(newss);


	// update texts
	{
		Localizer::getInstance()->SetWorldName(worldname);

		_text_maplistmodel->Clear();
		_text_questlistmodel->Clear();
		_text_inventorylistmodel->Clear();
		_text_namelistmodel->Clear();

		_text_mapNameList->Clear();
		_text_questNameList->Clear();
		_text_inventoryNameList->Clear();
		_text_nameNameList->Clear();

		{
			std::map<long, std::string> tmap = Localizer::getInstance()->GetMap(Localizer::Map);
			std::map<long, std::string>::iterator it = tmap.begin();
			std::map<long, std::string>::iterator end = tmap.end();
			for(; it != end; ++it)
			{
				QStringList qlist;
				qlist <<QString::fromUtf8(it->second.c_str());
				_text_maplistmodel->AddOrUpdateRow(it->first, qlist);

				std::stringstream txtwithid;
				txtwithid<<it->first<<": "<<it->second;
				_text_mapNameList->AddData(QString::fromUtf8(txtwithid.str().c_str()));
			}
		}

		{
			std::map<long, std::string> tmap = Localizer::getInstance()->GetMap(Localizer::Quest);
			std::map<long, std::string>::iterator it = tmap.begin();
			std::map<long, std::string>::iterator end = tmap.end();
			for(; it != end; ++it)
			{
				QStringList qlist;
				qlist <<QString::fromUtf8(it->second.c_str());
				_text_questlistmodel->AddOrUpdateRow(it->first, qlist);

				std::stringstream txtwithid;
				txtwithid<<it->first<<": "<<it->second;
				_text_questNameList->AddData(QString::fromUtf8(txtwithid.str().c_str()));
			}
		}

		{
			std::map<long, std::string> tmap = Localizer::getInstance()->GetMap(Localizer::Inventory);
			std::map<long, std::string>::iterator it = tmap.begin();
			std::map<long, std::string>::iterator end = tmap.end();
			for(; it != end; ++it)
			{
				QStringList qlist;
				qlist <<QString::fromUtf8(it->second.c_str());
				_text_inventorylistmodel->AddOrUpdateRow(it->first, qlist);

				std::stringstream txtwithid;
				txtwithid<<it->first<<": "<<it->second;
				_text_inventoryNameList->AddData(QString::fromUtf8(txtwithid.str().c_str()));
			}
		}

		{
			std::map<long, std::string> tmap = Localizer::getInstance()->GetMap(Localizer::Name);
			std::map<long, std::string>::iterator it = tmap.begin();
			std::map<long, std::string>::iterator end = tmap.end();
			for(; it != end; ++it)
			{
				QStringList qlist;
				qlist <<QString::fromUtf8(it->second.c_str());
				_text_namelistmodel->AddOrUpdateRow(it->first, qlist);

				std::stringstream txtwithid;
				txtwithid<<it->first<<": "<<it->second;
				_text_nameNameList->AddData(QString::fromUtf8(txtwithid.str().c_str()));
			}
		}
	}

	// add maps
	{
		_maplistmodel->Clear();
		LbaNet::MapsSeq::const_iterator itm = _winfo.Maps.begin();
		LbaNet::MapsSeq::const_iterator endm = _winfo.Maps.end();
		for(long cc=1; itm != endm; ++itm, ++cc)
		{
			QStringList data;
			data << itm->first.c_str() << itm->second.Description.c_str();
			_maplistmodel->AddOrUpdateRow(cc, data);


			_mapNameList->AddData(itm->first.c_str());

			// add spawning to the list
			_mapSpawningList[itm->first] = boost::shared_ptr<CustomStringListModel>(new CustomStringListModel());
			LbaNet::SpawningsSeq::const_iterator itsp = itm->second.Spawnings.begin();
			LbaNet::SpawningsSeq::const_iterator endsp = itm->second.Spawnings.end();
			for(; itsp != endsp; ++itsp)
				_mapSpawningList[itm->first]->AddData(itsp->second.Name.c_str());
		}
	}

	// add teleport
	{
		_tplistmodel->Clear();
		LbaNet::ServerTeleportsSeq::const_iterator ittp = _winfo.TeleportInfo.begin();
		LbaNet::ServerTeleportsSeq::const_iterator endtp = _winfo.TeleportInfo.end();
		for(long cc=1; ittp != endtp; ++ittp, ++cc)
		{
			std::string spawningname;
			LbaNet::MapsSeq::iterator itmap = _winfo.Maps.find(ittp->second.MapName);
			if(itmap != _winfo.Maps.end())
			{
				LbaNet::SpawningsSeq::iterator it = itmap->second.Spawnings.find(ittp->second.SpawningId);
				if(it != itmap->second.Spawnings.end())
					spawningname = it->second.Name;
			}

			QStringList data;
			data << ittp->second.Name.c_str() << ittp->second.MapName.c_str() << spawningname.c_str();
			_tplistmodel->AddOrUpdateRow(ittp->first, data);

			_currteleportidx = ittp->first;
		}
	}

	// add inventory items
	{
		InventoryItemHandler::getInstance()->SetCurrentWorld(_winfo.Description.WorldName);
		_itemNameList->Clear();
		_itemlistmodel->Clear();

		const std::map<long, LbaNet::ItemInfo> &_inventoryitems = InventoryItemHandler::getInstance()->GetItemMap();
		std::map<long, ItemInfo>::const_iterator itinv = _inventoryitems.begin();
		std::map<long, ItemInfo>::const_iterator endinv = _inventoryitems.end();
		for(; itinv != endinv; ++itinv)
		{
			QStringList data;
			data << itinv->second.Name.c_str();
			data << InventoryItemHandler::getInstance()->GetItemTypeString(itinv->first).c_str();
			_itemlistmodel->AddOrUpdateRow(itinv->first, data);

			std::stringstream txtwithid;
			txtwithid<<itinv->first<<": "<<itinv->second.Name.c_str();
			_itemNameList->AddData(txtwithid.str().c_str());
		}
	}


	//add starting item
	{
		LbaNet::ItemsMap::iterator itm = _winfo.StartingInfo.StartingInventory.begin();
		LbaNet::ItemsMap::iterator endm = _winfo.StartingInfo.StartingInventory.end();
		for(;itm != endm; ++itm)
		{
			QStringList data;
			data << InventoryItemHandler::getInstance()->GetItemInfo(itm->first).Name.c_str();
			std::stringstream tmpstrs;
			tmpstrs<<itm->second.Count;
			data << tmpstrs.str().c_str();
			_startitemlistmodel->AddOrUpdateRow(itm->first, data);
			
		}
		
	}

	// add lua stuff
	std::string luafile = "Worlds/" + _winfo.Description.WorldName + "/Lua/";
	_luaH = boost::shared_ptr<ServerLuaHandler>(new ServerLuaHandler());

	// refresh starting info
	RefreshStartingInfo();
}




/***********************************************************
reset world display in editor
***********************************************************/
void EditorHandler::ResetWorld()
{
	_maplistmodel->Clear();
	_tplistmodel->Clear();
	_mapNameList->Clear();
	_cscriptList->Clear();
	_mapSpawningList.clear();

	_uieditor.label_worldname->setText("");
	_uieditor.textEdit_worlddescription->setText("");
	_uieditor.textEdit_worldnews->setText("");

	_currteleportidx = 0;

	ResetMap();
}


/***********************************************************
reset map display in editor
***********************************************************/
void EditorHandler::ResetMap()
{
	_currspawningidx = 0;
	_currtriggeridx = 0;

	_uieditor.label_mapname->setText("");
	_uieditor.textEdit_map_description->setText("");
	_mapspawninglistmodel->Clear();
	_actorlistmodel->Clear();

	_triggerlistmodel->Clear();
	_triggers.clear();
	_triggerNameList->Clear();
	_Actors.clear();

	ResetObject();
}


/***********************************************************
reset object display in editor
***********************************************************/
void EditorHandler::ResetObject()
{
	_objectcustomdelegate->Clear();
	_objectmodel->Clear();
	_modelidxdatamap.clear();

	RemoveSelectedActorDislay();
	RemoveSelectedScriptDislay();
	RemoveArrows();
}



/***********************************************************
on go tp clicked
***********************************************************/
void EditorHandler::goto_tp_double_clicked(const QModelIndex & itm)
{
	goto_tp_button_clicked();
}


/***********************************************************
on go map clicked
***********************************************************/
void EditorHandler::goto_map_double_clicked(const QModelIndex & itm)
{
	goto_map_button_clicked();
}


/***********************************************************
on go tp clicked
***********************************************************/
void EditorHandler::goto_tp_button_clicked()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_TeleportList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();


	if(indexes.size() > 2)
	{
		std::string mapname = _tplistmodel->GetString(indexes[1]).toAscii().data();
		std::string spawning = _tplistmodel->GetString(indexes[2]).toAscii().data();

		// get id associated to spawning
		long spid = -1;
		if(spawning != "")
		{
			LbaNet::MapsSeq::iterator itmap = _winfo.Maps.find(mapname);
			if(itmap != _winfo.Maps.end())
			{
				LbaNet::SpawningsSeq::iterator it = itmap->second.Spawnings.begin();
				LbaNet::SpawningsSeq::iterator end = itmap->second.Spawnings.end();
				for(;it != end; ++it)
				{
					if(spawning == it->second.Name)
					{
						spid = it->first;
						break;
					}
				}
			}
		}

		if(spid >= 0)
			ChangeMap(mapname, spid);
	}
}

/***********************************************************
on go map clicked
***********************************************************/
void EditorHandler::goto_map_button_clicked()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_MapList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	if(indexes.size() > 0)
	{
		std::string mapname = _maplistmodel->GetString(indexes[0]).toAscii().data();
		
		const LbaNet::MapInfo & mapinfo = _winfo.Maps[mapname];
		if(mapinfo.Spawnings.size() > 0)
		{
			ChangeMap(mapname, mapinfo.Spawnings.begin()->first);
		}
		else
		{
			CreateDefaultSpawningAndTp(mapname);
		}
	}
}



/***********************************************************
refresh gui with map info
***********************************************************/
void EditorHandler::SetMapInfo(const std::string & mapname)
{
	SaveMapBeforeQuit(true);

	ResetMap();

	const LbaNet::MapInfo & mapinfo = _winfo.Maps[mapname];

	_uieditor.label_mapname->setText(mapinfo.Name.c_str());


	QString descs = QString::fromUtf8(mapinfo.Description.c_str());
	descs.replace(QString(" @ "), QString("\n"));
	_uieditor.textEdit_map_description->setText(descs);

	switch(mapinfo.AutoCameraType)
	{
		case 1:
			_uieditor.radioButton_camtype_ortho->setChecked(true);
		break;

		case 2:
			_uieditor.radioButton_camtype_persp->setChecked(true);
		break;

		case 3:
			_uieditor.radioButton_camtype_3d->setChecked(true);
		break;
	}

	if(mapinfo.Type == "exterior")
	{
		_uieditor.comboBox_maptype->setCurrentIndex(0);
	}
	else
	{
		_uieditor.comboBox_maptype->setCurrentIndex(1);
	}

	_uieditor.checkBox_map_instancied->setChecked(mapinfo.IsInstance);


	// add the spawnings
	{
		_mapspawninglistmodel->Clear();
		LbaNet::SpawningsSeq::const_iterator ittp = mapinfo.Spawnings.begin();
		LbaNet::SpawningsSeq::const_iterator endtp = mapinfo.Spawnings.end();
		for(; ittp != endtp; ++ittp)
		{
			QString Xs;
			Xs.setNum (ittp->second.PosX, 'f');
			QString Ys;
			Ys.setNum (ittp->second.PosY, 'f');
			QString Zs;
			Zs.setNum (ittp->second.PosZ, 'f');

			QStringList data;
			data << ittp->second.Name.c_str() << Xs << Ys << Zs;
			_mapspawninglistmodel->AddOrUpdateRow(ittp->first, data);

			_currspawningidx = (ittp->first + 1);
		}
	}


	// add lua stuff
	std::string luafile = "Worlds/" + _winfo.Description.WorldName + "/Lua/";
	luafile += mapname + "_server.lua";
	_luaH = boost::shared_ptr<ServerLuaHandler>(new ServerLuaHandler());
	_luaH->LoadFile(luafile);
	_luaH->CallLua("InitMap", this);

	// resend all actors to server to be in sync
	{
		std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator it =	_Actors.begin();
		std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator end =	_Actors.end();
		for(; it != end; ++it)
		{
			EditorUpdateBasePtr update = new UpdateEditor_AddOrModActor(it->second);
			SharedDataHandler::getInstance()->EditorUpdate(mapname, update);
		}
	}

	// resend all triggers to server to be in sync
	{
		std::map<long, boost::shared_ptr<TriggerBase> >::iterator it =	_triggers.begin();
		std::map<long, boost::shared_ptr<TriggerBase> >::iterator end =	_triggers.end();
		for(; it != end; ++it)
		{
			EditorUpdateBasePtr update = new UpdateEditor_AddOrModTrigger(it->second);
			SharedDataHandler::getInstance()->EditorUpdate(mapname, update);
		}
	}
}





/***********************************************************
on addspawning clicked
***********************************************************/
void EditorHandler::addspawning_button_clicked()
{
	if(!IsMapOpened())
		return;

	//clear old stuff
	_uiaddspawningdialog.lineEdit_name->setText("");
	_uiaddspawningdialog.doubleSpinBox_posx->setValue(_posX);
	_uiaddspawningdialog.doubleSpinBox_posy->setValue(_posY);
	_uiaddspawningdialog.doubleSpinBox_posz->setValue(_posZ);
	_uiaddspawningdialog.doubleSpinBox_rotation->setValue(0);
	_uiaddspawningdialog.checkBox_forcerotation->setChecked(false);

	_addspawningdialog->show();
}

/***********************************************************
on removespawning clicked
***********************************************************/
void EditorHandler::removespawning_button_clicked()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_SpawningList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();
	if(indexes.size() > 2)
	{
		// inform server
		long spawningid = _mapspawninglistmodel->GetId(indexes[0]);
		std::string mapname = _uieditor.label_mapname->text().toAscii().data();
		RemoveSpawning(mapname, spawningid);

		// remove row from table
		_mapspawninglistmodel->removeRows(indexes[0].row(), 1);

		RefreshStartingSpawning();
	}
}


/***********************************************************
on selectspawning clicked
***********************************************************/
void EditorHandler::selectspawning_double_clicked(const QModelIndex & itm)
{
	selectspawning_button_clicked();
}

/***********************************************************
on selectspawning clicked
***********************************************************/
void EditorHandler::selectspawning_button_clicked()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_SpawningList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();
	if(indexes.size() > 2)
	{
		long spawningid = _mapspawninglistmodel->GetId(indexes[0]);
		SelectSpawning(spawningid);
	}
}


/***********************************************************
on AddSpawning clicked
***********************************************************/
void EditorHandler::AddSpawning_clicked()
{
	QString spname = _uiaddspawningdialog.lineEdit_name->text();
	std::string mapname = _uieditor.label_mapname->text().toAscii().data();

	// user forgot to set a name
	if(spname == "")
		return;


	if(_mapSpawningList[mapname]->stringList().contains(spname))
	{
		QMessageBox::warning(this, tr("Name already used"),
			tr("The name you entered for the spawning is already used. Please enter a unique name."),
			QMessageBox::Ok);
		return;
	}


	_addspawningdialog->hide();

	long id = AddOrModSpawning(mapname, spname.toAscii().data(),
				(float)_uiaddspawningdialog.doubleSpinBox_posx->value(), 
				(float)_uiaddspawningdialog.doubleSpinBox_posy->value(), 
				(float)_uiaddspawningdialog.doubleSpinBox_posz->value(),
				(float)_uiaddspawningdialog.doubleSpinBox_rotation->value(), 
				_uiaddspawningdialog.checkBox_forcerotation->isChecked());

	// add name to list
	AddSpawningName(mapname, spname.toAscii().data());

	SelectSpawning(id);

	SetModified();
	RefreshStartingSpawning();
}


/***********************************************************
add a spawning to the map
***********************************************************/
long EditorHandler::AddOrModSpawning(const std::string &mapname,
										const std::string &spawningname,
										float PosX, float PosY, float PosZ,
										float Rotation, bool forcedrotation,
										long modifyid)
{
	// first update the internal info
	LbaNet::SpawningInfo spawn;
	spawn.Id = ((modifyid >= 0)?modifyid:_currspawningidx++);
	spawn.Name = spawningname;
	spawn.PosX = PosX;
	spawn.PosY = PosY;
	spawn.PosZ = PosZ;
	spawn.Rotation = Rotation;
	spawn.ForceRotation = forcedrotation;
	_winfo.Maps[mapname].Spawnings[spawn.Id] = spawn;


	//! add spawning to the list
	{
		QString Xs;
		Xs.setNum (PosX, 'f');
		QString Ys;
		Ys.setNum (PosY, 'f');
		QString Zs;
		Zs.setNum (PosZ, 'f');

		QStringList data;
		data << spawningname.c_str() << Xs << Ys << Zs;
		_mapspawninglistmodel->AddOrUpdateRow(spawn.Id, data);
	}


	// then inform the server
	EditorUpdateBasePtr update = new UpdateEditor_AddOrModSpawning(	spawn.Id,
																	spawningname,
																	PosX, PosY, PosZ,
																	Rotation, forcedrotation);

	SharedDataHandler::getInstance()->EditorUpdate(mapname, update);

	return spawn.Id;
}



/***********************************************************
remove a spawning from the map
***********************************************************/
void EditorHandler::RemoveSpawning(const std::string &mapname, long spawningid)
{
	// first update the internal info
	LbaNet::SpawningsSeq::iterator it = _winfo.Maps[mapname].Spawnings.find(spawningid);
	if(it != _winfo.Maps[mapname].Spawnings.end())
	{
		// remove from text list
		RemoveSpawningName(mapname, it->second.Name);

		// erase from data
		_winfo.Maps[mapname].Spawnings.erase(it);

		// then inform the server
		EditorUpdateBasePtr update = new UpdateEditor_RemoveSpawning(spawningid);
		SharedDataHandler::getInstance()->EditorUpdate(mapname, update);

		ClearObjectIfSelected("Spawn", spawningid);

		SetModified();
	}
}


/***********************************************************
player moved
***********************************************************/
void EditorHandler::PlayerMoved(float posx, float posy, float posz)
{
	_uieditor.doubleSpinBox_info_posx->setValue(posx);
	_uieditor.doubleSpinBox_info_posy->setValue(posy);
	_uieditor.doubleSpinBox_info_posz->setValue(posz);

	_posX = floor(posx*2)/2;
	_posY = floor(posy+0.5);
	_posZ = floor(posz*2)/2;
}



/***********************************************************
when go button clicked on info part
***********************************************************/
void EditorHandler::info_go_clicked()
{
	EventsQueue::getReceiverQueue()->AddEvent(new EditorTeleportEvent(	_uieditor.doubleSpinBox_info_posx->value(),
																		_uieditor.doubleSpinBox_info_posy->value(),
																		_uieditor.doubleSpinBox_info_posz->value()));
}



/***********************************************************
camera type toggled in info
***********************************************************/
void EditorHandler::info_camera_toggled(bool checked)
{
	EventsQueue::getReceiverQueue()->AddEvent(new EditorCameraChangeEvent(!checked));
}



/***********************************************************
set spawning in the object
***********************************************************/
void EditorHandler::SelectSpawning(long id, const QModelIndex &parent)
{
	std::string mapname = _uieditor.label_mapname->text().toAscii().data();
	LbaNet::SpawningsSeq::const_iterator it = _winfo.Maps[mapname].Spawnings.find(id);
	if(it == _winfo.Maps[mapname].Spawnings.end())
		return;

	std::string spawningname = it->second.Name;
	float PosX = it->second.PosX;
	float PosY = it->second.PosY;
	float PosZ = it->second.PosZ;
	float Rotation = it->second.Rotation;
	bool forcedrotation = it->second.ForceRotation;

	if(parent == QModelIndex())
		ResetObject();


	{
		QVector<QVariant> data;
		data<<"Type"<<"Spawn";
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"SubCategory"<<"-";
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"Id"<<id;
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"Name"<<spawningname.c_str();
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"PosX"<<(double)PosX;
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"PosY"<<(double)PosY;
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"PosZ"<<(double)PosZ;
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"Force Rotation"<<forcedrotation;
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"Rotation"<<(double)Rotation;
		_objectmodel->AppendRow(data, parent);
	}
}


/***********************************************************
clear the object displayed if it is the selected one
***********************************************************/
void EditorHandler::ClearObjectIfSelected(const std::string objecttype, long id)
{
	if(_objectmodel->rowCount() > 2)
	{
		QString type = _objectmodel->data(_objectmodel->GetIndex(1, 0)).toString();
		if(objecttype == type.toAscii().data())
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 2)).toString().toLong();	
			if(id == objid)
			{
				ResetObject();
			}
		}
	}
}



/***********************************************************
data changed in object view
***********************************************************/
void EditorHandler::objectdatachanged(const QModelIndex &index1, const QModelIndex &index2)
{
	QModelIndex parentIdx = _objectmodel->parent(index1);

	if(_objectmodel->rowCount() > 2)
	{
		QString type = _objectmodel->data(_objectmodel->GetIndex(1, 0, parentIdx)).toString();
		std::string category = _objectmodel->data(_objectmodel->GetIndex(1, 1, parentIdx)).toString().toAscii().data();


		if(type == "Spawn")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toLong();
			SpawningObjectChanged(objid, parentIdx);
			return;
		}

		if(type == "Trigger")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toLong();
			TriggerObjectChanged(objid, category, parentIdx);
			return;
		}

		if(type == "Actor")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toLong();
			ActorObjectChanged(objid, parentIdx, index1.row());
			return;
		}

		if(type == "Action")
		{
			ActionObjectChanged(category, parentIdx);
			return;
		}

		if(type == "ClientScript")
		{
			CScriptObjectChanged(category, parentIdx);
			return;
		}

		if(type == "Condition")
		{
			ConditionChanged(category, parentIdx);
			return;
		}		

		if(type == "Item")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toLong();
			ItemChanged(objid, category, parentIdx);
			return;
		}	
	}
}


/***********************************************************
called when spawning object changed
***********************************************************/
void EditorHandler::SpawningObjectChanged(long id, const QModelIndex &parentIdx)
{
	if(_objectmodel->rowCount() > 8)
	{
		QString name = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toString();
		float PosX = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toFloat();
		float PosY = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toFloat();
		float PosZ = _objectmodel->data(_objectmodel->GetIndex(1, 6, parentIdx)).toFloat();
		bool forcedrotation = _objectmodel->data(_objectmodel->GetIndex(1, 7, parentIdx)).toBool();
		float Rotation = _objectmodel->data(_objectmodel->GetIndex(1, 8, parentIdx)).toFloat();
		std::string mapname = _uieditor.label_mapname->text().toAscii().data();
		std::string oldname = _winfo.Maps[mapname].Spawnings[id].Name;

		// check if name changed already exist
		if(name != oldname.c_str())
		{
			if(name == "" || _mapSpawningList[mapname]->stringList().contains(name))
			{
				QMessageBox::warning(this, tr("Name already used"),
					tr("The name you entered for the spawning is already used. Please enter a unique name."),
					QMessageBox::Ok);

				_objectmodel->setData(_objectmodel->GetIndex(1, 3, parentIdx), oldname.c_str());
				return;
			}
		}


		ReplaceSpawningName(mapname, oldname, name.toAscii().data());


		AddOrModSpawning(mapname, name.toAscii().data(),
									PosX, PosY, PosZ,
									Rotation, forcedrotation,
									id);

		UpdateTpSpanName(mapname, id, name.toAscii().data());

		SetModified();
		RefreshStartingSpawning();
	}
}


/***********************************************************
check if a world is opened
***********************************************************/
bool EditorHandler::IsWorldOpened()
{
	return (_uieditor.label_worldname->text() != "");
}

/***********************************************************
check if a map is opened
***********************************************************/
bool EditorHandler::IsMapOpened()
{
	return (_uieditor.label_mapname->text() != "");
}



/***********************************************************
function used by LUA to add actor
***********************************************************/
void EditorHandler::AddActorObject(boost::shared_ptr<ActorHandler> actor)
{
	_Actors[actor->GetId()] = actor;

	std::string type;
	switch(actor->GetInfo().PhysicDesc.TypePhysO)
	{
		case LbaNet::StaticAType:
			type = "Static";
		break;

		case LbaNet::KynematicAType:
			type = "Scripted";
		break;

		case LbaNet::CharControlAType:
			type = "Movable";
		break;  
	}


	std::string dtype = "No";
	switch(actor->GetInfo().DisplayDesc.TypeRenderer)
	{
		case LbaNet::RenderOsgModel:
			dtype = "Osg Model";
		break;

		case RenderSprite:
			dtype = "Sprite";
		break;

		case RenderLba1M:
			dtype = "Lba1 Model";
		break;

		case RenderLba2M:
			dtype = "Lba2 Model";
		break;

		case RenderCross:
			dtype = "Cross";
		break;

		case RenderBox:
			dtype = "Box";
		break;

		case RenderCapsule:
			dtype = "Capsule";
		break;
	}

	std::string ptype;
	switch(actor->GetInfo().PhysicDesc.TypeShape)
	{
		case LbaNet::NoShape:
			ptype = "No Shape";
		break;
		case BoxShape:
			ptype = "Box";
		break;
		case CapsuleShape:
			ptype = "Capsule";
		break;
		case SphereShape:
			ptype = "Sphere";
		break;
		case TriangleMeshShape:
			ptype = "Triangle Mesh";
		break;
	}

	ActorObjectInfo & ainfo = actor->GetInfo();
	std::string name = ainfo.ExtraInfo.Name;
	if(name == "")
		name = "-";


	// init color vectors
	{

		Lba1ModelMapHandler::getInstance()->GetModelColor(ainfo.DisplayDesc.ModelName, 
								ainfo.DisplayDesc.Outfit, ainfo.DisplayDesc.Weapon, ainfo.DisplayDesc.Mode, 
										actor->initpolycolors, actor->initspherecolors, actor->initlinecolors);

		actor->currentpolycolors = actor->initpolycolors;
		actor->currentspherecolors = actor->initspherecolors;
		actor->currentlinecolors = actor->initlinecolors;

		LbaNet::Lba1ColorChangeSeq::iterator itsw = ainfo.DisplayDesc.ColorSwaps.begin();
		LbaNet::Lba1ColorChangeSeq::iterator endsw = ainfo.DisplayDesc.ColorSwaps.end();
		for(; itsw != endsw; ++itsw)
		{
			switch(itsw->first.ModelPart)
			{
				case LbaNet::PolygonColor:
				{
					std::vector<int>::iterator itinitc = actor->initpolycolors.begin();
					std::vector<int>::iterator endinitc = actor->initpolycolors.end();
					std::vector<int>::iterator itcirc = actor->currentpolycolors.begin();
					for(; itinitc != endinitc; ++itinitc, ++itcirc)
					{
						if(*itinitc == itsw->first.Color)
							break;
					}

					if(itcirc != actor->currentpolycolors.end())
						*itcirc = itsw->second;
				}
				break;

				case LbaNet::SphereColor:
				{
					std::vector<int>::iterator itinitc = actor->initspherecolors.begin();
					std::vector<int>::iterator endinitc = actor->initspherecolors.end();
					std::vector<int>::iterator itcirc = actor->currentspherecolors.begin();
					for(; itinitc != endinitc; ++itinitc, ++itcirc)
					{
						if(*itinitc == itsw->first.Color)
							break;
					}

					if(itcirc != actor->currentspherecolors.end())
						*itcirc = itsw->second;
				}
				break;

				case LbaNet::LineColor:
				{
					std::vector<int>::iterator itinitc = actor->initlinecolors.begin();
					std::vector<int>::iterator endinitc = actor->initlinecolors.end();
					std::vector<int>::iterator itcirc = actor->currentlinecolors.begin();
					for(; itinitc != endinitc; ++itinitc, ++itcirc)
					{
						if(*itinitc == itsw->first.Color)
							break;
					}

					if(itcirc != actor->currentlinecolors.end())
						*itcirc = itsw->second;
				}
				break;
			}
		}
	}



	QStringList data;
	data << name.c_str()<< type.c_str()  << dtype.c_str() << ptype.c_str();
	_actorlistmodel->AddOrUpdateRow(actor->GetId(), data);

	_curractoridx = actor->GetId();
}

/***********************************************************
add a trigger of moving type to the map
***********************************************************/				
void EditorHandler::AddTrigger(boost::shared_ptr<TriggerBase> trigger)
{
	if(trigger)
	{
		_currtriggeridx = trigger->GetId();

		trigger->SetOwner(this);
		_triggers[_currtriggeridx] = trigger;

		QStringList slist;
		slist << trigger->GetName().c_str() << trigger->GetTypeName().c_str();
		_triggerlistmodel->AddOrUpdateRow(_currtriggeridx, slist);

		_triggerNameList->AddData(trigger->GetName().c_str());
	}
}



/***********************************************************
// teleport an object
// ObjectType ==>
//! 1 -> npc object
//! 2 -> player object
//! 3 -> movable object
***********************************************************/
void EditorHandler::Teleport(int ObjectType, long ObjectId,
								const std::string &NewMapName, 
								long SpawningId,
								float offsetX, float offsetY, float offsetZ)
{
	// nothing to do
}





/***********************************************************
select an action and display it in object view
***********************************************************/
void EditorHandler::SelectAction(ActionBasePtr action, const QModelIndex &parent)
{
	if(parent == QModelIndex())
		ResetObject();

	if(!action)
		return;


	// add pointer for later change
	_modelidxdatamap[parent] = (void*)action.get();


	{
		QVector<QVariant> data;
		data<<"Type"<<"Action";
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"SubCategory"<<action->GetTypeName().c_str();
		_objectmodel->AppendRow(data, parent, true);
	}


	std::string actiontype = action->GetTypeName();
	if(actiontype == "TeleportAction")
	{
		TeleportAction* ptr = static_cast<TeleportAction*>(action.get());
		{
			QVector<QVariant> data;
			data << "NewMap" << ptr->GetMapName().c_str();
			_objectmodel->AppendRow(data, parent);
		}

		{	
			std::string spawningname;
			LbaNet::MapsSeq::iterator itmap = _winfo.Maps.find(ptr->GetMapName());
			if(itmap != _winfo.Maps.end())
			{
				LbaNet::SpawningsSeq::iterator it = itmap->second.Spawnings.find(ptr->GetSpawning());
				if(it != itmap->second.Spawnings.end())
					spawningname = it->second.Name;
			}

			QVector<QVariant> data;
			data << "Spawn" << spawningname.c_str();
			_objectmodel->AppendRow(data, parent);
		}

		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 2, parent), _mapNameList);

		std::map<std::string, boost::shared_ptr<CustomStringListModel> >::iterator it = 
													_mapSpawningList.find(ptr->GetMapName());
		if(it != _mapSpawningList.end())
			_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 3, parent), it->second);

		return;
	}

	if(actiontype == "ClientScriptAction")
	{
		ClientScriptAction* ptr = static_cast<ClientScriptAction*>(action.get());
		{
			ClientScriptBasePtr scriptptr = ptr->GetScript();
			std::string name = GetCScriptType(scriptptr);

			QVector<QVariant> data;
			data << "Script" << name.c_str();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);

			if(scriptptr)
				SelectCScript(scriptptr, idx);
		}

		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 2, parent), _cscripttypeList);

		return;
	}


	if(actiontype == "CustomAction")
	{
		CustomAction* ptr = static_cast<CustomAction*>(action.get());
		{
			QVector<QVariant> data;
			data << "Function name" << ptr->GetLuaFunctionName().c_str();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);

			// add tootlip
			_objectmodel->setTooltip(idx, "the function should be defined in custom server lua file");
			QModelIndex idx2 = _objectmodel->GetIndex(1, idx.row(), idx.parent());
			_objectmodel->setTooltip(idx2, "the function should be defined in custom server lua file");
		}

		return;
	}

	if(actiontype == "DisplayTextAction")
	{
		DisplayTextAction* ptr = static_cast<DisplayTextAction*>(action.get());
		{
			std::string txt = Localizer::getInstance()->GetText(Localizer::Map, ptr->GetTextId());
			std::stringstream txttmp;
			txttmp<<ptr->GetTextId()<<": "<<txt;

			QVector<QVariant> data;
			data << "Text" << QString::fromUtf8(txttmp.str().c_str());
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}

		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 2, parent), _text_mapNameList);

		return;
	}

	if(actiontype == "ConditionalAction")
	{
		ConditionalAction* ptr = static_cast<ConditionalAction*>(action.get());
		{
			// add condition
			{
				std::string condtype = "No";
				ConditionBasePtr condptr = ptr->GetCondition();
				if(condptr)
				{
					condtype = condptr->GetTypeName();
				}

				QVector<QVariant> data;
				data << "Condition" << condtype.c_str();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);

				if(condptr)
					SelectCondition(condptr, idx);
			}


			// add action true
			{
				ActionBasePtr actptr = ptr->GetActionTrue();
				std::string acttype = GetActionType(actptr);

				QVector<QVariant> data;
				data << "Action On True" << acttype.c_str();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);
				
				if(actptr)
					SelectAction(actptr, idx);
			}

			// add action false
			{
				ActionBasePtr actptr = ptr->GetActionFalse();
				std::string acttype = GetActionType(actptr);

				QVector<QVariant> data;
				data << "Action On False" << acttype.c_str();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);
				
				if(actptr)
					SelectAction(actptr, idx);
			}
		}

		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 2, parent), _conditiontypeList);
		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 3, parent), _actiontypeList);
		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _actiontypeList);

		return;
	}

}



/***********************************************************
called when action object changed
***********************************************************/
void EditorHandler::ActionObjectChanged(const std::string & category, const QModelIndex &parentIdx)
{
	std::map<QModelIndex, void *>::iterator it = _modelidxdatamap.find(parentIdx);
	if(it != _modelidxdatamap.end())
	{
		void * ptr = it->second;
		if(ptr)
		{	
			if(category == "TeleportAction")
			{
				TeleportAction* modifiedaction = (TeleportAction*)ptr;

				// get info
				std::string mapname = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();
				std::string spawning = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toString().toAscii().data();

				std::string oldmapname = modifiedaction->GetMapName();


				// get id associated to spawning
				long spid = -1;
				if(spawning != "")
				{
					LbaNet::MapsSeq::iterator itmap = _winfo.Maps.find(mapname);
					if(itmap != _winfo.Maps.end())
					{
						LbaNet::SpawningsSeq::iterator it = itmap->second.Spawnings.begin();
						LbaNet::SpawningsSeq::iterator end = itmap->second.Spawnings.end();
						for(;it != end; ++it)
						{
							if(spawning == it->second.Name)
							{
								spid = it->first;
								break;
							}
						}
					}
				}

				// update action
				modifiedaction->SetMapName(mapname);
				modifiedaction->SetSpawning(spid);


				// need to save as something changed
				SetModified();



				// refresh spawning list for action
				if(oldmapname != mapname)
				{
					std::map<std::string, boost::shared_ptr<CustomStringListModel> >::iterator it = 
						_mapSpawningList.find(mapname);
					if(it != _mapSpawningList.end())
					{
						_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 3, parentIdx), it->second);

						QStringList lst = it->second->stringList();
						if(lst.size() > 0)
							_objectmodel->setData(_objectmodel->GetIndex(1, 3, parentIdx), lst[0]);	
					}
				}


				return;
			}


			if(category == "ClientScriptAction")
			{
				// created modified action and replace old one
				ClientScriptAction* modifiedact = (ClientScriptAction*)ptr;

				// check script part
				{
					std::string script = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();
					std::string currscript = GetCScriptType(modifiedact->GetScript());

					if(script != currscript)
					{
						ClientScriptBasePtr ptrtmp = CreateCscript(script);
						modifiedact->SetScript(ptrtmp);


						QModelIndex curidx = _objectmodel->GetIndex(0, 2, parentIdx);
						_objectmodel->Clear(curidx);
						if(ptrtmp)
						{
							SelectCScript(ptrtmp, curidx);

							_uieditor.treeView_object->setExpanded(curidx, true); // expand 
						}

					}
				}


				// need to save as something changed
				SetModified();

				return;
			}



			if(category == "CustomAction")
			{
				// get info
				std::string scriptname = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();


				// created modified action and replace old one
				CustomAction* modifiedact = (CustomAction*)ptr;
				modifiedact->SetLuaFunctionName(scriptname);

				// need to save as something changed
				SetModified();

				return;
			}


			if(category == "DisplayTextAction")
			{
				// get info
				std::string text = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();
				std::string tmp = text.substr(0, text.find(":"));
				long textid = atol(tmp.c_str());

				// created modified action and replace old one
				DisplayTextAction* modifiedact = (DisplayTextAction*)ptr;
				modifiedact->SetTextId(textid);

				// need to save as something changed
				SetModified();

				return;
			}



			if(category == "ConditionalAction")
			{
				// created modified action and replace old one
				ConditionalAction* modifiedact = (ConditionalAction*)ptr;

				// check condition part
				{
					std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();
					std::string currcond = GetConditionType(modifiedact->GetCondition());

					if(condition != currcond)
					{
						ConditionBasePtr ptrtmp = CreateCondition(condition);
						modifiedact->SetCondition(ptrtmp);

						QModelIndex curidx = _objectmodel->GetIndex(0, 2, parentIdx);
						_objectmodel->Clear(curidx);
						if(ptrtmp)
						{
							SelectCondition(ptrtmp, curidx);

							_uieditor.treeView_object->setExpanded(curidx, true); // expand 
						}

					}
				}


				// get id associated to actions
				std::string action1 = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toString().toAscii().data();
				std::string action2 = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toString().toAscii().data();

				//action 1
				{
					std::string curract = GetActionType(modifiedact->GetActionTrue());

					if(action1 != curract)
					{
						ActionBasePtr ptrtmp = CreateAction(action1);
						modifiedact->SetActionTrue(ptrtmp);

						QModelIndex curidx = _objectmodel->GetIndex(0, 3, parentIdx);
						_objectmodel->Clear(curidx);
						if(ptrtmp)
						{
							SelectAction(ptrtmp, curidx);

							_uieditor.treeView_object->setExpanded(curidx, true); // expand 
						}

					}
				}

				//action 2
				{
					std::string curract = GetActionType(modifiedact->GetActionFalse());

					if(action2 != curract)
					{
						ActionBasePtr ptrtmp = CreateAction(action2);
						modifiedact->SetActionFalse(ptrtmp);

						QModelIndex curidx = _objectmodel->GetIndex(0, 4, parentIdx);
						_objectmodel->Clear(curidx);
						if(ptrtmp)
						{
							SelectAction(ptrtmp, curidx);

							_uieditor.treeView_object->setExpanded(curidx, true); // expand 
						}

					}
				}



				// need to save as something changed
				SetModified();

				return;
			}
		}
	}

}







/***********************************************************
add an spawning name to the name list
***********************************************************/
void EditorHandler::AddSpawningName(const std::string & mapname, const std::string & name)
{
	if(!_mapSpawningList[mapname]->stringList().contains(name.c_str()))
		_mapSpawningList[mapname]->AddData(name.c_str());
}


/***********************************************************
remove an spawning name to the name list
***********************************************************/
void EditorHandler::RemoveSpawningName(const std::string & mapname, const std::string & name)
{
	_mapSpawningList[mapname]->RemoveData(name.c_str());
}


/***********************************************************
replace an spawning name to the name list
***********************************************************/
void EditorHandler::ReplaceSpawningName(const std::string & mapname, const std::string & oldname, 
															const std::string & newname)
{
	_mapSpawningList[mapname]->ReplaceData(oldname.c_str(), newname.c_str());
}


/***********************************************************
add an new trigger to the list
***********************************************************/
void EditorHandler::AddNewTrigger(boost::shared_ptr<TriggerBase> trigger)
{
	if(trigger)
	{
		// add action internally
		AddTrigger(trigger);
		SetMapModified();

		//inform server
		std::string mapname = _uieditor.label_mapname->text().toAscii().data();
		EditorUpdateBasePtr update = new UpdateEditor_AddOrModTrigger(trigger);
		SharedDataHandler::getInstance()->EditorUpdate(mapname, update);
	}
}


/***********************************************************
remove trigger
***********************************************************/
void EditorHandler::RemoveTrigger(long id)
{
	//remove internal trigger
	std::map<long, boost::shared_ptr<TriggerBase> >::iterator it = _triggers.find(id);
	if(it != _triggers.end())
	{
		_triggers.erase(it);
		SetMapModified();

		//inform server
		std::string mapname = _uieditor.label_mapname->text().toAscii().data();
		EditorUpdateBasePtr update = new UpdateEditor_RemoveTrigger(id);
		SharedDataHandler::getInstance()->EditorUpdate(mapname, update);
	}
}


/***********************************************************
select trigger
***********************************************************/
void EditorHandler::SelectTrigger(long id, const QModelIndex &parent)
{
	std::map<long, boost::shared_ptr<TriggerBase> >::iterator it = _triggers.find(id);
	if(it != _triggers.end())
	{
		if(parent == QModelIndex())
			ResetObject();

		{
			QVector<QVariant> data;
			data<<"Type"<<"Trigger";
			_objectmodel->AppendRow(data, parent, true);
		}

		{
			QVector<QVariant> data;
			data<<"SubCategory"<<it->second->GetTypeName().c_str();
			_objectmodel->AppendRow(data, parent, true);
		}

		{
			QVector<QVariant> data;
			data<<"Id"<<id;
			_objectmodel->AppendRow(data, parent, true);
		}

		{
			QVector<QVariant> data;
			data<<"Name"<<it->second->GetName().c_str();
			_objectmodel->AppendRow(data, parent);
		}

		std::string actiontype = it->second->GetTypeName();
		if(actiontype == "ZoneTrigger")
		{
			ZoneTrigger* ptr = static_cast<ZoneTrigger*>(it->second.get());

			//action 1
			{
				ActionBasePtr actptr = ptr->GetAction1();
				std::string acttype = GetActionType(actptr);

				QVector<QVariant> data;
				data << "Action On Enter" << acttype.c_str();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);
				
				if(actptr)
					SelectAction(actptr, idx);
			}

			//action 2
			{
				ActionBasePtr actptr = ptr->GetAction2();
				std::string acttype = GetActionType(actptr);

				QVector<QVariant> data;
				data << "Action On Leave" << acttype.c_str();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);
				
				if(actptr)
					SelectAction(actptr, idx);
			}

			{
				QVector<QVariant> data;
				data << "Trigger on Player" << ptr->CheckPlayer();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Trigger on Npc" << ptr->CheckNpcs();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Trigger on Movable Objects" << ptr->CheckMovableObjects();
				_objectmodel->AppendRow(data, parent);
			}


			{
				QVector<QVariant> data;
				data << "Position X" << (double)ptr->GetPosX();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Position Y" << (double)ptr->GetPosY();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Position Z" << (double)ptr->GetPosZ();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Zone size X" << (double)ptr->GetSizeX();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Zone size Y" << (double)ptr->GetSizeY();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Zone size Z" << (double)ptr->GetSizeZ();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Multi Activation" << ptr->MultiActivation();
				_objectmodel->AppendRow(data, parent);
			}


			_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _actiontypeList);
			_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 5, parent), _actiontypeList);

			UpdateSelectedZoneTriggerDisplay(ptr->GetPosX(), ptr->GetPosY(), ptr->GetPosZ(),
											ptr->GetSizeX(), ptr->GetSizeY(), ptr->GetSizeZ());

			DrawArrows(ptr->GetPosX(), ptr->GetPosY(), ptr->GetPosZ());

			return;
		}

		if(actiontype == "ZoneActionTrigger")
		{
			ZoneActionTrigger* ptr = static_cast<ZoneActionTrigger*>(it->second.get());

			//action 1
			{
				ActionBasePtr actptr = ptr->GetAction1();
				std::string acttype = GetActionType(actptr);

				QVector<QVariant> data;
				data << "Action On Activation" << acttype.c_str();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);
				
				if(actptr)
					SelectAction(actptr, idx);
			}

			{
				QVector<QVariant> data;
				data << "Position X" << (double)ptr->GetPosX();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Position Y" << (double)ptr->GetPosY();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Position Z" << (double)ptr->GetPosZ();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Zone size X" << (double)ptr->GetSizeX();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Zone size Y" << (double)ptr->GetSizeY();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Zone size Z" << (double)ptr->GetSizeZ();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Accepted Mode 1" << ptr->GetAcceptedMode1().c_str();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Accepted Mode 2" << ptr->GetAcceptedMode2().c_str();
				_objectmodel->AppendRow(data, parent);
			}

			_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _actiontypeList);
			_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 11, parent), _actormodeList);
			_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 12, parent), _actormodeList);

			UpdateSelectedZoneTriggerDisplay(ptr->GetPosX(), ptr->GetPosY(), ptr->GetPosZ(),
				ptr->GetSizeX(), ptr->GetSizeY(), ptr->GetSizeZ());

			DrawArrows(ptr->GetPosX(), ptr->GetPosY(), ptr->GetPosZ());

			return;
		}


		if(actiontype == "ActivationTrigger")
		{
			ActivationTrigger* ptr = static_cast<ActivationTrigger*>(it->second.get());
			//action 1
			{
				ActionBasePtr actptr = ptr->GetAction1();
				std::string acttype = GetActionType(actptr);

				QVector<QVariant> data;
				data << "Action On Activation" << acttype.c_str();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);
				
				if(actptr)
					SelectAction(actptr, idx);
			}

			{
				QVector<QVariant> data;
				data << "Position X" << (double)ptr->GetPosX();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Position Y" << (double)ptr->GetPosY();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Position Z" << (double)ptr->GetPosZ();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Activation distance" << (double)ptr->GetDistance();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Accepted Mode 1" << ptr->GetAcceptedMode1().c_str();
				_objectmodel->AppendRow(data, parent);
			}

			{
				QVector<QVariant> data;
				data << "Accepted Mode 2" << ptr->GetAcceptedMode2().c_str();
				_objectmodel->AppendRow(data, parent);
			}

			_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _actiontypeList);
			_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 9, parent), _actormodeList);
			_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 10, parent), _actormodeList);

			UpdateSelectedDistanceTriggerDisplay(ptr->GetPosX(), ptr->GetPosY(), ptr->GetPosZ(),
																					ptr->GetDistance());

			DrawArrows(ptr->GetPosX(), ptr->GetPosY(), ptr->GetPosZ());

			return;
		}



		if(actiontype == "TimerTrigger")
		{
			TimerTrigger* ptr = static_cast<TimerTrigger*>(it->second.get());
			//action 1
			{
				ActionBasePtr actptr = ptr->GetAction1();
				std::string acttype = GetActionType(actptr);

				QVector<QVariant> data;
				data << "Action On Activation" << acttype.c_str();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);
				
				if(actptr)
					SelectAction(actptr, idx);
			}

			{
				QVector<QVariant> data;
				data << "Time in ms" << (int)ptr->GetTimeinMs();
				_objectmodel->AppendRow(data, parent);
			}


			_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _actiontypeList);

			return;
		}
	}
}


/***********************************************************
called when trigger object changed
***********************************************************/
void EditorHandler::TriggerObjectChanged(long id, const std::string & category, const QModelIndex &parentIdx)
{
	TriggerInfo triggerinfo;
	triggerinfo.id = id;
	triggerinfo.name = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toString().toAscii().data();
	std::string oldname = _triggers[id]->GetName();
	std::string mapname = _uieditor.label_mapname->text().toAscii().data();

	// check if name changed already exist
	if(triggerinfo.name != oldname)
	{
		if(triggerinfo.name == "" || _triggerNameList->stringList().contains(triggerinfo.name.c_str()))
		{
			QMessageBox::warning(this, tr("Name already used"),
				tr("The name you entered for the trigger is already used. Please enter a unique name."),
				QMessageBox::Ok);

			_objectmodel->setData(_objectmodel->GetIndex(1, 3, parentIdx), oldname.c_str());
			return;
		}
	}


	if(category == "ZoneTrigger")
	{
		// get info

		std::string action1 = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toString().toAscii().data();
		std::string action2 = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toString().toAscii().data();
		triggerinfo.CheckPlayers = _objectmodel->data(_objectmodel->GetIndex(1, 6, parentIdx)).toBool();
		triggerinfo.CheckNpcs = _objectmodel->data(_objectmodel->GetIndex(1, 7, parentIdx)).toBool();
		triggerinfo.CheckMovableObjects = _objectmodel->data(_objectmodel->GetIndex(1, 8, parentIdx)).toBool();
		float posX = _objectmodel->data(_objectmodel->GetIndex(1, 9, parentIdx)).toFloat();
		float posY = _objectmodel->data(_objectmodel->GetIndex(1, 10, parentIdx)).toFloat();
		float posZ = _objectmodel->data(_objectmodel->GetIndex(1, 11, parentIdx)).toFloat();
		float sizeX = _objectmodel->data(_objectmodel->GetIndex(1, 12, parentIdx)).toFloat();
		float sizeY = _objectmodel->data(_objectmodel->GetIndex(1, 13, parentIdx)).toFloat();
		float sizeZ = _objectmodel->data(_objectmodel->GetIndex(1, 14, parentIdx)).toFloat();
		if(sizeX < 0.0001)
			sizeX = 0.0001;
		if(sizeY < 0.0001)
			sizeY = 0.0001;
		if(sizeZ < 0.0001)
			sizeZ = 0.0001;

		bool multicactiv = _objectmodel->data(_objectmodel->GetIndex(1, 15, parentIdx)).toBool();


		// created modified action and replace old one
		ZoneTrigger* modifiedtrig = (ZoneTrigger*)_triggers[id].get();
		modifiedtrig->SetPosition(posX, posY, posZ);
		modifiedtrig->SetTriggerInfo(triggerinfo);
		modifiedtrig->SetSize(sizeX, sizeY, sizeZ);
		modifiedtrig->SetMultiActivation(multicactiv);


		//action 1
		{
			std::string curract = GetActionType(modifiedtrig->GetAction1());

			if(action1 != curract)
			{
				ActionBasePtr ptrtmp = CreateAction(action1);
				modifiedtrig->SetAction1(ptrtmp);

				QModelIndex curidx = _objectmodel->GetIndex(0, 4, parentIdx);
				_objectmodel->Clear(curidx);
				if(ptrtmp)
				{
					SelectAction(ptrtmp, curidx);

					_uieditor.treeView_object->setExpanded(curidx, true); // expand 
				}

			}
		}

		//action 2
		{
			std::string curract = GetActionType(modifiedtrig->GetAction2());

			if(action2 != curract)
			{
				ActionBasePtr ptrtmp = CreateAction(action2);
				modifiedtrig->SetAction2(ptrtmp);

				QModelIndex curidx = _objectmodel->GetIndex(0, 5, parentIdx);
				_objectmodel->Clear(curidx);
				if(ptrtmp)
				{
					SelectAction(ptrtmp, curidx);

					_uieditor.treeView_object->setExpanded(curidx, true); // expand 
				}

			}
		}





		// update trigger name list
		_triggerNameList->ReplaceData(oldname.c_str(), triggerinfo.name.c_str());


		// update trigger list display
		QStringList slist;
		slist << triggerinfo.name.c_str() << modifiedtrig->GetTypeName().c_str();
		_triggerlistmodel->AddOrUpdateRow(id, slist);



		// need to save as something changed
		SetMapModified();


		//inform server
		EditorUpdateBasePtr update = new UpdateEditor_AddOrModTrigger(_triggers[id]);
		SharedDataHandler::getInstance()->EditorUpdate(mapname, update);


		UpdateSelectedZoneTriggerDisplay(posX, posY, posZ, sizeX, sizeY, sizeZ);

		return;
	}


	if(category == "ZoneActionTrigger")
	{
		// get info

		std::string action1 = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toString().toAscii().data();
		float posX = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toFloat();
		float posY = _objectmodel->data(_objectmodel->GetIndex(1, 6, parentIdx)).toFloat();
		float posZ = _objectmodel->data(_objectmodel->GetIndex(1, 7, parentIdx)).toFloat();
		float sizeX = _objectmodel->data(_objectmodel->GetIndex(1, 8, parentIdx)).toFloat();
		float sizeY = _objectmodel->data(_objectmodel->GetIndex(1, 9, parentIdx)).toFloat();
		float sizeZ = _objectmodel->data(_objectmodel->GetIndex(1, 10, parentIdx)).toFloat();
		triggerinfo.CheckPlayers = true;
		triggerinfo.CheckNpcs = true;
		triggerinfo.CheckMovableObjects = false;

		if(sizeX < 0.0001)
			sizeX = 0.0001;
		if(sizeY < 0.0001)
			sizeY = 0.0001;
		if(sizeZ < 0.0001)
			sizeZ = 0.0001;

		std::string mode1 = _objectmodel->data(_objectmodel->GetIndex(1, 11, parentIdx)).toString().toAscii().data();
		std::string mode2 = _objectmodel->data(_objectmodel->GetIndex(1, 12, parentIdx)).toString().toAscii().data();


		// created modified action and replace old one
		ZoneActionTrigger* modifiedtrig = (ZoneActionTrigger*)_triggers[id].get();
		modifiedtrig->SetPosition(posX, posY, posZ);
		modifiedtrig->SetTriggerInfo(triggerinfo);
		modifiedtrig->SetSize(sizeX, sizeY, sizeZ);
		modifiedtrig->SetMode1(mode1);
		modifiedtrig->SetMode2(mode2);

		//action 1
		{
			std::string curract = GetActionType(modifiedtrig->GetAction1());

			if(action1 != curract)
			{
				ActionBasePtr ptrtmp = CreateAction(action1);
				modifiedtrig->SetAction1(ptrtmp);

				QModelIndex curidx = _objectmodel->GetIndex(0, 4, parentIdx);
				_objectmodel->Clear(curidx);
				if(ptrtmp)
				{
					SelectAction(ptrtmp, curidx);

					_uieditor.treeView_object->setExpanded(curidx, true); // expand 
				}

			}
		}


		// update trigger name list
		_triggerNameList->ReplaceData(oldname.c_str(), triggerinfo.name.c_str());

		// update trigger list display
		QStringList slist;
		slist << triggerinfo.name.c_str() << modifiedtrig->GetTypeName().c_str();
		_triggerlistmodel->AddOrUpdateRow(id, slist);



		// need to save as something changed
		SetMapModified();


		//inform server
		EditorUpdateBasePtr update = new UpdateEditor_AddOrModTrigger(_triggers[id]);
		SharedDataHandler::getInstance()->EditorUpdate(mapname, update);


		UpdateSelectedZoneTriggerDisplay(posX, posY, posZ, sizeX, sizeY, sizeZ);

		return;
	}


	if(category == "ActivationTrigger")
	{
		// get info

		std::string action1 = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toString().toAscii().data();
		float posX = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toFloat();
		float posY = _objectmodel->data(_objectmodel->GetIndex(1, 6, parentIdx)).toFloat();
		float posZ = _objectmodel->data(_objectmodel->GetIndex(1, 7, parentIdx)).toFloat();
		float distance = _objectmodel->data(_objectmodel->GetIndex(1, 8, parentIdx)).toFloat();
		triggerinfo.CheckPlayers = true;
		triggerinfo.CheckNpcs = true;
		triggerinfo.CheckMovableObjects = false;

		if(distance < 0.0001)
			distance = 0.0001;

		std::string mode1 = _objectmodel->data(_objectmodel->GetIndex(1, 9, parentIdx)).toString().toAscii().data();
		std::string mode2 = _objectmodel->data(_objectmodel->GetIndex(1, 10, parentIdx)).toString().toAscii().data();


		// get id associated to actions
		ActivationTrigger* modifiedtrig = (ActivationTrigger*)_triggers[id].get();
		modifiedtrig->SetPosition(posX, posY, posZ);
		modifiedtrig->SetTriggerInfo(triggerinfo);
		modifiedtrig->SetMode1(mode1);
		modifiedtrig->SetMode2(mode2);
		modifiedtrig->SetDistance(distance);


		//action 1
		{
			std::string curract = GetActionType(modifiedtrig->GetAction1());

			if(action1 != curract)
			{
				ActionBasePtr ptrtmp = CreateAction(action1);
				modifiedtrig->SetAction1(ptrtmp);

				QModelIndex curidx = _objectmodel->GetIndex(0, 4, parentIdx);
				_objectmodel->Clear(curidx);
				if(ptrtmp)
				{
					SelectAction(ptrtmp, curidx);

					_uieditor.treeView_object->setExpanded(curidx, true); // expand 
				}

			}
		}


		// update trigger name list
		_triggerNameList->ReplaceData(oldname.c_str(), triggerinfo.name.c_str());


		// update trigger list display
		QStringList slist;
		slist << triggerinfo.name.c_str() << modifiedtrig->GetTypeName().c_str();
		_triggerlistmodel->AddOrUpdateRow(id, slist);



		// need to save as something changed
		SetMapModified();


		//inform server
		EditorUpdateBasePtr update = new UpdateEditor_AddOrModTrigger(_triggers[id]);
		SharedDataHandler::getInstance()->EditorUpdate(mapname, update);


		UpdateSelectedDistanceTriggerDisplay(posX, posY, posZ, distance);

		return;
	}



	if(category == "TimerTrigger")
	{
		// get info

		std::string action1 = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toString().toAscii().data();
		long time = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toInt();
		triggerinfo.CheckPlayers = true;
		triggerinfo.CheckNpcs = true;
		triggerinfo.CheckMovableObjects = false;


		// get id associated to actions
		TimerTrigger* modifiedtrig = (TimerTrigger*)_triggers[id].get();
		modifiedtrig->SetTriggerInfo(triggerinfo);
		modifiedtrig->SetTime(time);



		//action 1
		{
			std::string curract = GetActionType(modifiedtrig->GetAction1());

			if(action1 != curract)
			{
				ActionBasePtr ptrtmp = CreateAction(action1);
				modifiedtrig->SetAction1(ptrtmp);

				QModelIndex curidx = _objectmodel->GetIndex(0, 4, parentIdx);
				_objectmodel->Clear(curidx);
				if(ptrtmp)
				{
					SelectAction(ptrtmp, curidx);

					_uieditor.treeView_object->setExpanded(curidx, true); // expand 
				}

			}
		}


		// update trigger name list
		_triggerNameList->ReplaceData(oldname.c_str(), triggerinfo.name.c_str());


		// update trigger list display
		QStringList slist;
		slist << triggerinfo.name.c_str() << modifiedtrig->GetTypeName().c_str();
		_triggerlistmodel->AddOrUpdateRow(id, slist);



		// need to save as something changed
		SetMapModified();


		//inform server
		EditorUpdateBasePtr update = new UpdateEditor_AddOrModTrigger(_triggers[id]);
		SharedDataHandler::getInstance()->EditorUpdate(mapname, update);



		return;
	}


}



/***********************************************************
change current map to new map
***********************************************************/
void EditorHandler::ChangeMap(const std::string & mapname, long spawningid)
{
	if(SaveMapBeforeQuit())
		SharedDataHandler::getInstance()->ChangeMapPlayer(1, mapname, spawningid);
}



/***********************************************************
save current map to file
***********************************************************/
void EditorHandler::SaveMap(const std::string & filename)
{
	std::ofstream file(filename.c_str());
	file<<"function InitMap(environment)"<<std::endl;

	// save actors
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator ita = _Actors.begin();
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator enda = _Actors.end();
	for(;ita != enda; ++ita)
		ita->second->SaveToLuaFile(file);

	// save triggers
	std::map<long, boost::shared_ptr<TriggerBase> >::iterator itt = _triggers.begin();
	std::map<long, boost::shared_ptr<TriggerBase> >::iterator endt = _triggers.end();
	for(;itt != endt; ++itt)
		itt->second->SaveToLuaFile(file);

	file<<"end"<<std::endl;
}


/***********************************************************
world description changed
***********************************************************/
void EditorHandler::WorldDescriptionChanged()
{
	QString descs = _uieditor.textEdit_worlddescription->toPlainText();
	descs.replace(QString("\n"), QString(" @ "));
	_winfo.Description.Description = descs.toUtf8().data();
	SetModified();
}

/***********************************************************
worlds news changed
***********************************************************/
void EditorHandler::WorldNewsChanged()
{
	QString descs = _uieditor.textEdit_worldnews->toPlainText();
	descs.replace(QString("\n"), QString(" @ "));
	_winfo.Description.News = descs.toUtf8().data();
	SetModified();
}


/***********************************************************
refresh starting info tab
***********************************************************/
void EditorHandler::RefreshStartingInfo()
{
	// map list part
	RefreshStartingMap();

	// spawning part
	RefreshStartingSpawning();

	_uieditor.spinBox_startinglife->setValue(_winfo.StartingInfo.StartingLife);
	_uieditor.spinBox_startingMana->setValue(_winfo.StartingInfo.StartingMana);

	RefreshStartingModelOutfit();
}


/***********************************************************
refresh starting map
***********************************************************/
void EditorHandler::RefreshStartingMap()
{
	_uieditor.comboBox_startingmap->setModel(_mapNameList.get());
	int index = _uieditor.comboBox_startingmap->findText(_winfo.StartingInfo.StartingMap.c_str());
	if(index >= 0)
		_uieditor.comboBox_startingmap->setCurrentIndex(index);
	else
	{
		if(_winfo.Maps.size() > 0)
		{
			_winfo.StartingInfo.StartingMap = _winfo.Maps.begin()->first;
			RefreshStartingMap();
			return;
		}
	}
}

/***********************************************************
refresh starting spawning
***********************************************************/
void EditorHandler::RefreshStartingSpawning()
{
	LbaNet::MapsSeq::iterator itmap = _winfo.Maps.find(_winfo.StartingInfo.StartingMap);
	if(itmap != _winfo.Maps.end())
	{
		std::map<std::string, boost::shared_ptr<CustomStringListModel> >::iterator itsp = 
													_mapSpawningList.find(_winfo.StartingInfo.StartingMap);
		if(itsp != _mapSpawningList.end())
		{
			_uieditor.comboBox_startingspawning->setModel(itsp->second.get());	

			LbaNet::SpawningsSeq::iterator it = itmap->second.Spawnings.find(_winfo.StartingInfo.SpawningId);
			if(it != itmap->second.Spawnings.end())
			{
				int index = _uieditor.comboBox_startingspawning->findText(it->second.Name.c_str());
				if(index >= 0)
					_uieditor.comboBox_startingspawning->setCurrentIndex(index);
			}	
			else
			{
				if(itmap->second.Spawnings.size() > 0)
				{
					_winfo.StartingInfo.SpawningId = itmap->second.Spawnings.begin()->first;
					RefreshStartingSpawning();
					return;
				}
			}
		}
	}
}

/***********************************************************
refresh starting outfit
***********************************************************/
void EditorHandler::RefreshStartingModelOutfit()
{
	_uieditor.comboBox_modeloutfit->clear();

	std::map<std::string, ModelData> & _lba1Mdata =
	Lba1ModelMapHandler::getInstance()->GetData();

	std::map<std::string, OutfitData>::const_iterator it = _lba1Mdata[_winfo.StartingInfo.StartingModel.ModelName].outfits.begin();
	std::map<std::string, OutfitData>::const_iterator end = _lba1Mdata[_winfo.StartingInfo.StartingModel.ModelName].outfits.end();
	for(; it != end; ++it)
		_uieditor.comboBox_modeloutfit->addItem(it->first.c_str());

	int index = _uieditor.comboBox_modeloutfit->findText(_winfo.StartingInfo.StartingModel.Outfit.c_str());
	if(index >= 0)
		_uieditor.comboBox_modeloutfit->setCurrentIndex(index);
	else
	{
		if(_lba1Mdata[_winfo.StartingInfo.StartingModel.ModelName].outfits.size() > 0)
		{
			_winfo.StartingInfo.StartingModel.Outfit = _lba1Mdata[_winfo.StartingInfo.StartingModel.ModelName].outfits.begin()->first;
		
			RefreshStartingModelOutfit();
			return;
		}
	}

	RefreshStartingModelWeapon();
}

/***********************************************************

***********************************************************/
void EditorHandler::RefreshStartingModelWeapon()
{
	_uieditor.comboBox_modelweapon->clear();

	std::map<std::string, ModelData> & _lba1Mdata =
	Lba1ModelMapHandler::getInstance()->GetData();


	std::map<std::string, WeaponData>::const_iterator it = _lba1Mdata[_winfo.StartingInfo.StartingModel.ModelName].
											outfits[_winfo.StartingInfo.StartingModel.Outfit].weapons.begin();
	std::map<std::string, WeaponData>::const_iterator end = _lba1Mdata[_winfo.StartingInfo.StartingModel.ModelName].
											outfits[_winfo.StartingInfo.StartingModel.Outfit].weapons.end();
	for(; it != end; ++it)
		_uieditor.comboBox_modelweapon->addItem(it->first.c_str());

	int index = _uieditor.comboBox_modelweapon->findText(_winfo.StartingInfo.StartingModel.Weapon.c_str());
	if(index >= 0)
		_uieditor.comboBox_modelweapon->setCurrentIndex(index);
	else
	{
		if(_lba1Mdata[_winfo.StartingInfo.StartingModel.ModelName].
			outfits[_winfo.StartingInfo.StartingModel.Outfit].weapons.size() > 0)
		{
			_winfo.StartingInfo.StartingModel.Weapon = _lba1Mdata[_winfo.StartingInfo.StartingModel.ModelName].
											outfits[_winfo.StartingInfo.StartingModel.Outfit].weapons.begin()->first;
		
			RefreshStartingModelWeapon();
			return;
		}
	}

	RefreshStartingModelMode();
}

/***********************************************************
refresh starting mode
***********************************************************/
void EditorHandler::RefreshStartingModelMode()
{
	_uieditor.comboBox_modelmode->clear();

	std::map<std::string, ModelData> & _lba1Mdata =
	Lba1ModelMapHandler::getInstance()->GetData();

	std::map<std::string, ModeData>::const_iterator it = _lba1Mdata[_winfo.StartingInfo.StartingModel.ModelName].
											outfits[_winfo.StartingInfo.StartingModel.Outfit].
											weapons[_winfo.StartingInfo.StartingModel.Weapon].modes.begin();
	std::map<std::string, ModeData>::const_iterator end = _lba1Mdata[_winfo.StartingInfo.StartingModel.ModelName].
											outfits[_winfo.StartingInfo.StartingModel.Outfit].
											weapons[_winfo.StartingInfo.StartingModel.Weapon].modes.end();
	for(; it != end; ++it)
		_uieditor.comboBox_modelmode->addItem(it->first.c_str());

	int index = _uieditor.comboBox_modelmode->findText(_winfo.StartingInfo.StartingModel.Mode.c_str());
	if(index >= 0)
		_uieditor.comboBox_modelmode->setCurrentIndex(index);
	else
	{
		if(_lba1Mdata[_winfo.StartingInfo.StartingModel.ModelName].
			outfits[_winfo.StartingInfo.StartingModel.Outfit].
			weapons[_winfo.StartingInfo.StartingModel.Weapon].modes.size() > 0)
		{
			_winfo.StartingInfo.StartingModel.Mode = _lba1Mdata[_winfo.StartingInfo.StartingModel.ModelName].
											outfits[_winfo.StartingInfo.StartingModel.Outfit].
											weapons[_winfo.StartingInfo.StartingModel.Weapon].modes.begin()->first;
		
			RefreshStartingModelMode();
			return;
		}
	}
}



/***********************************************************
generate list of possible name
***********************************************************/
void EditorHandler::UpdateModelName(boost::shared_ptr<CustomStringListModel> toupdate)
{
	std::map<std::string, ModelData> & _lba1Mdata =
	Lba1ModelMapHandler::getInstance()->GetData();

	QStringList list;
	std::map<std::string, ModelData>::const_iterator it = _lba1Mdata.begin();
	std::map<std::string, ModelData>::const_iterator end = _lba1Mdata.end();
	for(; it != end; ++it)
		list<<it->first.c_str();

	toupdate->Clear();
	toupdate->setStringList(list);
}

/***********************************************************
generate list of possible outfit
***********************************************************/
void EditorHandler::UpdateModelOutfit(const std::string & modelname, 
											   boost::shared_ptr<CustomStringListModel> toupdate)
{
	std::map<std::string, ModelData> & _lba1Mdata =
	Lba1ModelMapHandler::getInstance()->GetData();

	QStringList list;
	std::map<std::string, OutfitData>::const_iterator it = _lba1Mdata[modelname].outfits.begin();
	std::map<std::string, OutfitData>::const_iterator end = _lba1Mdata[modelname].outfits.end();
	for(; it != end; ++it)
		list<<it->first.c_str();

	toupdate->Clear();
	toupdate->setStringList(list);
}


/***********************************************************
generate list of possible 
***********************************************************/
void EditorHandler::UpdateModelWeapon(const std::string & modelname, const std::string & outfit, 
											   boost::shared_ptr<CustomStringListModel> toupdate)
{
	std::map<std::string, ModelData> & _lba1Mdata =
	Lba1ModelMapHandler::getInstance()->GetData();

	QStringList list;
	std::map<std::string, WeaponData>::const_iterator it = _lba1Mdata[modelname].outfits[outfit].weapons.begin();
	std::map<std::string, WeaponData>::const_iterator end = _lba1Mdata[modelname].outfits[outfit].weapons.end();
	for(; it != end; ++it)
		list<<it->first.c_str();

	toupdate->Clear();
	toupdate->setStringList(list);
}



/***********************************************************
generate list of possible mode
***********************************************************/
void EditorHandler::UpdateModelMode(const std::string & modelname, 
											 const std::string & outfit, const std::string & weapon, 
											 boost::shared_ptr<CustomStringListModel> toupdate)
{
	std::map<std::string, ModelData> & _lba1Mdata =
	Lba1ModelMapHandler::getInstance()->GetData();

	QStringList list;
	std::map<std::string, ModeData>::const_iterator it = _lba1Mdata[modelname].outfits[outfit].weapons[weapon].modes.begin();
	std::map<std::string, ModeData>::const_iterator end = _lba1Mdata[modelname].outfits[outfit].weapons[weapon].modes.end();
	for(; it != end; ++it)
		list<<it->first.c_str();

	toupdate->Clear();
	toupdate->setStringList(list);
}



/***********************************************************
refresh Actor Model Name
***********************************************************/
void EditorHandler::RefreshActorModelName(int index, QModelIndex parentIdx, bool resize,
											boost::shared_ptr<ActorHandler> actor)
{
	UpdateModelName(_actorModelNameList);

	std::string modelname = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).
																	toString().toAscii().data();

	if(!_actorModelNameList->DataExist(modelname.c_str()))
	{
		modelname = _actorModelNameList->GetFirstdata().toAscii().data();

		if(resize)
			_objectmodel->setData(_objectmodel->GetIndex(1, index, parentIdx), modelname.c_str());
	}	

	RefreshActorModelOutfit(index+1, parentIdx, modelname, resize, actor);
}


/***********************************************************
refresh Actor Model Outfit
***********************************************************/
void EditorHandler::RefreshActorModelOutfit(int index, QModelIndex parentIdx,
											const std::string & modelname, bool resize,
											boost::shared_ptr<ActorHandler> actor)
{
	UpdateModelOutfit(modelname, _actorModelOutfitList);

	std::string outfit = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).
																	toString().toAscii().data();

	if(!_actorModelOutfitList->DataExist(outfit.c_str()))
	{
		outfit = _actorModelOutfitList->GetFirstdata().toAscii().data();

		if(resize)
			_objectmodel->setData(_objectmodel->GetIndex(1, index, parentIdx), outfit.c_str());
	}


	RefreshActorModelWeapon(index+1, parentIdx, modelname, outfit, resize, actor);
}


/***********************************************************
refresh Actor Model Weapon
***********************************************************/
void EditorHandler::RefreshActorModelWeapon(int index, QModelIndex parentIdx,
									const std::string & modelname, const std::string & outfit, bool resize,
											boost::shared_ptr<ActorHandler> actor)
{
	UpdateModelWeapon(modelname, outfit, _actorModelWeaponList);

	std::string weapon = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).
																	toString().toAscii().data();

	if(!_actorModelWeaponList->DataExist(weapon.c_str()))
	{
		weapon = _actorModelWeaponList->GetFirstdata().toAscii().data();

		if(resize)
			_objectmodel->setData(_objectmodel->GetIndex(1, index, parentIdx), weapon.c_str());
	}


	RefreshActorModelMode(index+1, parentIdx, modelname, outfit, weapon, resize, actor);
}


/***********************************************************
refresh Actor Model Mode
***********************************************************/
void EditorHandler::RefreshActorModelMode(int index, QModelIndex parentIdx,
									const std::string & modelname, const std::string & outfit, 
									const std::string & weapon, bool resize,
									boost::shared_ptr<ActorHandler> actor)
{
	UpdateModelMode(modelname, outfit, weapon, _actorModelModeList);

	// update physics if needed
	if(resize)
	{
		std::string mode = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).
																		toString().toAscii().data();

		if(!_actorModelModeList->DataExist(mode.c_str()))
		{
			mode = _actorModelModeList->GetFirstdata().toAscii().data();
			_objectmodel->setData(_objectmodel->GetIndex(1, index, parentIdx), mode.c_str());
		}


		std::string ptype = _objectmodel->data(_objectmodel->GetIndex(1, 7, parentIdx)).toString().toAscii().data();
		if(ptype == "No Shape") 
		{
			_objectmodel->setData(_objectmodel->GetIndex(1, 7, parentIdx), "Box");
			ptype = "Box";
		}

		if(ptype == "Box")
		{
			int resWeaponType;
			ModelSize size;
			int res = Lba1ModelMapHandler::getInstance()-> GetModelExtraInfo(modelname,
									outfit,	weapon,	mode, resWeaponType, size);

			if(res >= 0)
			{
				float csx = _objectmodel->data(_objectmodel->GetIndex(1, 13, parentIdx)).toFloat();
				float csy = _objectmodel->data(_objectmodel->GetIndex(1, 14, parentIdx)).toFloat();
				float csz = _objectmodel->data(_objectmodel->GetIndex(1, 15, parentIdx)).toFloat();

				if(csx != size.X)
					_objectmodel->setData(_objectmodel->GetIndex(1, 13, parentIdx), size.X);
				
				if(csy != size.Y)
					_objectmodel->setData(_objectmodel->GetIndex(1, 14, parentIdx), size.Y);

				if(csz != size.Z)
					_objectmodel->setData(_objectmodel->GetIndex(1, 15, parentIdx), size.Z);
			}
		}

		//update color
		Lba1ModelMapHandler::getInstance()->GetModelColor(modelname, outfit, weapon, mode, 
										actor->initpolycolors, actor->initspherecolors, actor->initlinecolors);

		actor->currentpolycolors = actor->initpolycolors;
		actor->currentspherecolors = actor->initspherecolors;
		actor->currentlinecolors = actor->initlinecolors;
	}
}




/***********************************************************
StartingMapModified
***********************************************************/
void EditorHandler::StartingMapModified(int index)
{
	_winfo.StartingInfo.StartingMap = _uieditor.comboBox_startingmap->currentText().toAscii().data();

	SetModified();
	RefreshStartingSpawning();
}


/***********************************************************
starting spawn modified
***********************************************************/
void EditorHandler::StartingSpawnModified(int index)
{
	std::string spname = _uieditor.comboBox_startingspawning->currentText().toAscii().data();
	long spid = -1;
	if(spname != "")
	{
		LbaNet::MapsSeq::iterator itmap = _winfo.Maps.find(_winfo.StartingInfo.StartingMap);
		if(itmap != _winfo.Maps.end())
		{
			LbaNet::SpawningsSeq::iterator it = itmap->second.Spawnings.begin();
			LbaNet::SpawningsSeq::iterator end = itmap->second.Spawnings.end();
			for(;it != end; ++it)
			{
				if(spname == it->second.Name)
				{
					spid = it->first;
					break;
				}
			}
		}
	}

	_winfo.StartingInfo.SpawningId = spid;
	SetModified();
}

/***********************************************************
starting life modified
***********************************************************/
void EditorHandler::StartingLifeModified(int value)
{
	_winfo.StartingInfo.StartingLife = _uieditor.spinBox_startinglife->value();
	_winfo.StartingInfo.StartingMana = _uieditor.spinBox_startingMana->value();

	SetModified();
}

/***********************************************************
starting Outfit modified
***********************************************************/
void EditorHandler::StartingOutfitModified(int index)
{
	_winfo.StartingInfo.StartingModel.Outfit = _uieditor.comboBox_modeloutfit->currentText().toAscii().data();

	SetModified();
	RefreshStartingModelWeapon();
}

/***********************************************************
starting Weapon modified
***********************************************************/
void EditorHandler::StartingWeaponModified(int index)
{
	_winfo.StartingInfo.StartingModel.Weapon = _uieditor.comboBox_modelweapon->currentText().toAscii().data();

	SetModified();
	RefreshStartingModelMode();
}

/***********************************************************
starting Mode modified
***********************************************************/
void EditorHandler::StartingModeModified(int index)
{
	_winfo.StartingInfo.StartingModel.Mode = _uieditor.comboBox_modelmode->currentText().toAscii().data();

	SetModified();
}



/***********************************************************
ui button clicked
***********************************************************/
void EditorHandler::addmap_button_clicked()
{
	if(!IsWorldOpened())
		return;

	// clear data
	_ui_addmapdialog.lineEdit_mapname->setText("");
	_ui_addmapdialog.textEdit_map_description->setText("");
	_ui_addmapdialog.radioButton_camtype_ortho->setChecked (true);
	_ui_addmapdialog.checkBox_map_instancied->setChecked (false);
	_addmapdialog->show();
}

/***********************************************************
ui button clicked
***********************************************************/
void EditorHandler::removemap_button_clicked()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_MapList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	if(indexes.size() > 0)
	{
		std::string mapname = _maplistmodel->GetString(indexes[0]).toAscii().data();


		LbaNet::MapsSeq::iterator itm = _winfo.Maps.find(mapname);
		if(itm != _winfo.Maps.end())
		{
			// remove from internal memory
			_winfo.Maps.erase(itm);

			// remove row from table
			_maplistmodel->removeRows(indexes[0].row(), 1);

			// update map list name
			_mapNameList->RemoveData(mapname.c_str());

			//inform server
			EditorUpdateBasePtr update = new UpdateEditor_RemoveMap(mapname);
			SharedDataHandler::getInstance()->EditorUpdate("-", update);

			SetModified();
			RefreshStartingMap();
		}
	}
}


/***********************************************************
dialog accepted
***********************************************************/
void EditorHandler::addmap_accepted()
{
	QString mapname = _ui_addmapdialog.lineEdit_mapname->text();

	// user forgot to set a name
	if(mapname == "")
		return;

	if(_mapNameList->stringList().contains(mapname))
	{
		QMessageBox::warning(this, tr("Name already used"),
			tr("The name you entered for the map is already used. Please enter a unique name."),
			QMessageBox::Ok);
		return;
	}

	_addmapdialog->hide();

	LbaNet::MapInfo newmapinfo;
	newmapinfo.Name = mapname.toAscii().data();

	QString descs = _ui_addmapdialog.textEdit_map_description->toPlainText();
	descs.replace(QString("\n"), QString(" @ "));
	newmapinfo.Description = descs.toUtf8().data();

	newmapinfo.Type = (_ui_addmapdialog.comboBox_maptype->currentIndex() == 0) ? "exterior" : "interior";

	newmapinfo.IsInstance = _ui_addmapdialog.checkBox_map_instancied->isChecked();

	newmapinfo.AutoCameraType = 1;
	if(_ui_addmapdialog.radioButton_camtype_persp->isChecked())
		newmapinfo.AutoCameraType = 2;
	if(_ui_addmapdialog.radioButton_camtype_3d->isChecked())
		newmapinfo.AutoCameraType = 3;

	_winfo.Maps[newmapinfo.Name] = newmapinfo;


	// refresh lists
	QStringList data;
	data << mapname << newmapinfo.Description.c_str();
	_maplistmodel->AddOrUpdateRow(_maplistmodel->GetNextId(), data);

	_mapNameList->AddData(mapname);
	_mapSpawningList[newmapinfo.Name] = boost::shared_ptr<CustomStringListModel>(new CustomStringListModel());


	//inform server
	EditorUpdateBasePtr update = new UpdateEditor_AddOrModMap(newmapinfo);
	SharedDataHandler::getInstance()->EditorUpdate("-", update);
	

	SetModified();
	RefreshStartingMap();
	CreateDefaultSpawningAndTp(newmapinfo.Name);
}



/***********************************************************
tp to default spawning of map
***********************************************************/
void EditorHandler::CreateDefaultSpawningAndTp(const std::string & mapname)
{
	// add a default spawning
	long spid = AddOrModSpawning(mapname, "DefaultSpawning", 0, 0, 0, 0, true, 0);
	AddSpawningName(mapname, "DefaultSpawning");
	ChangeMap(mapname, spid);
	SetModified();
	RefreshStartingSpawning();
}


/***********************************************************
map description changed
***********************************************************/
void EditorHandler::MapDescriptionChanged()
{
	std::string mapname = _uieditor.label_mapname->text().toAscii().data();
	if(mapname != "")
	{
		QString descs = _uieditor.textEdit_map_description->toPlainText();
		descs.replace(QString("\n"), QString(" @ "));
		std::string descstring	= descs.toUtf8().data();

		if(_winfo.Maps[mapname].Description != descstring)
		{
			SetModified();

			//inform server
			EditorUpdateBasePtr update = new UpdateEditor_AddOrModMap(_winfo.Maps[mapname]);
			SharedDataHandler::getInstance()->EditorUpdate("-", update);
		}
	}
}

/***********************************************************
map type changed
***********************************************************/
void EditorHandler::MapTypeChanged(int flag)
{
	std::string mapname = _uieditor.label_mapname->text().toAscii().data();
	if(mapname != "")
	{
		_winfo.Maps[mapname].Type = (_uieditor.comboBox_maptype->currentIndex() == 0) ? "exterior" : "interior";

		SetModified();

		//inform server
		EditorUpdateBasePtr update = new UpdateEditor_AddOrModMap(_winfo.Maps[mapname]);
		SharedDataHandler::getInstance()->EditorUpdate("-", update);
	}
}

/***********************************************************
map instance changed
***********************************************************/
void EditorHandler::MapInstanceChanged(int flag)
{
	std::string mapname = _uieditor.label_mapname->text().toAscii().data();
	if(mapname != "")
	{
		_winfo.Maps[mapname].IsInstance = _uieditor.checkBox_map_instancied->isChecked();

		SetModified();

		//inform server
		EditorUpdateBasePtr update = new UpdateEditor_AddOrModMap(_winfo.Maps[mapname]);
		SharedDataHandler::getInstance()->EditorUpdate("-", update);
	}
}

/***********************************************************
map cam type changed
***********************************************************/
void EditorHandler::MapCameraTypeChanged(bool flag)
{
	std::string mapname = _uieditor.label_mapname->text().toAscii().data();
	if(mapname != "")
	{
		if(flag == true)
		{
			QWidget *sendero = static_cast<QWidget *>(sender());
			if(sendero)
			{
				bool changed = false;

				if(sendero->objectName() == "radioButton_camtype_ortho")
				{
					if(_winfo.Maps[mapname].AutoCameraType != 1)
					{
						_winfo.Maps[mapname].AutoCameraType = 1;
						changed = true;
					}
				}

				if(sendero->objectName() == "radioButton_camtype_persp")
				{
					if(_winfo.Maps[mapname].AutoCameraType != 2)
					{
						_winfo.Maps[mapname].AutoCameraType = 2;
						changed = true;
					}
				}

				if(sendero->objectName() == "radioButton_camtype_3d")
				{
					if(_winfo.Maps[mapname].AutoCameraType != 3)
					{
						_winfo.Maps[mapname].AutoCameraType = 3;
						changed = true;
					}
				}

				if(changed)
				{
					SetModified();

					//inform server
					EditorUpdateBasePtr update = new UpdateEditor_AddOrModMap(_winfo.Maps[mapname]);
					SharedDataHandler::getInstance()->EditorUpdate("-", update);
				}
			}
		}
	}
}



/***********************************************************
tp add button push
***********************************************************/
void EditorHandler::TpAdd_button()
{
	_ui_addtpdialog.lineEdit_tpname->setText("");
	_ui_addtpdialog.comboBox_map->setModel(_mapNameList.get());
	_addtpdialog->setWindowTitle("Add Teleport");
	_edited_tp = -1;

	_addtpdialog->show();
}


/***********************************************************
tp remove button push
***********************************************************/
void EditorHandler::TpRemove_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_TeleportList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	if(indexes.size() > 0)
	{
		long tpid = _tplistmodel->GetId(indexes[0]);

		LbaNet::ServerTeleportsSeq::iterator it = _winfo.TeleportInfo.find(tpid);
		if( it != _winfo.TeleportInfo.end())
		{
			// remove from internal memory
			_winfo.TeleportInfo.erase(it);

			// remove row from table
			_tplistmodel->removeRows(indexes[0].row(), 1);


			//inform server
			EditorUpdateBasePtr update = new UpdateEditor_TeleportListChanged(_winfo.TeleportInfo);
			SharedDataHandler::getInstance()->EditorUpdate("-", update);

			SetModified();
		}
	}
}


/***********************************************************
tp edit button push
***********************************************************/
void EditorHandler::TpEdit_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_TeleportList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	if(indexes.size() > 0)
	{
		long id = _tplistmodel->GetId(indexes[0]);
		std::string name = _tplistmodel->GetString(indexes[0]).toAscii().data();
		_edited_tp = id;

		LbaNet::ServerTeleportsSeq::iterator it = _winfo.TeleportInfo.find(id);
		if( it != _winfo.TeleportInfo.end())
		{
			_ui_addtpdialog.lineEdit_tpname->setText(name.c_str());


			// add map list to combo box
			_ui_addtpdialog.comboBox_map->setModel(_mapNameList.get());

			int index = _ui_addtpdialog.comboBox_map->findText(it->second.MapName.c_str());
			if(index >= 0)
				_ui_addtpdialog.comboBox_map->setCurrentIndex(index);



			// add spawning list to combo box
			std::map<std::string, boost::shared_ptr<CustomStringListModel> >::iterator itsp = 
													_mapSpawningList.find(it->second.MapName.c_str());
			if(itsp != _mapSpawningList.end())
			{
				_ui_addtpdialog.comboBox_spawn->setModel(itsp->second.get());

				// select span in combo box if exist
				LbaNet::MapsSeq::iterator itmap = _winfo.Maps.find(it->second.MapName);
				if(itmap != _winfo.Maps.end())
				{
					LbaNet::SpawningsSeq::iterator itmapsp = itmap->second.Spawnings.find(it->second.SpawningId);
					if(itmapsp != itmap->second.Spawnings.end())
					{
						std::string spname = itmapsp->second.Name;
						int indexsp = _ui_addtpdialog.comboBox_spawn->findText(spname.c_str());
						if(indexsp >= 0)
							_ui_addtpdialog.comboBox_spawn->setCurrentIndex(indexsp);
					}
				}
			}

			std::stringstream strs;
			strs<<"Edit Teleport #"<<id;
			_addtpdialog->setWindowTitle(strs.str().c_str());
			_addtpdialog->show();
		}
	}
}

/***********************************************************
tp add button push
***********************************************************/
void EditorHandler::TpAdd_button_accepted()
{
	std::string tpname = _ui_addtpdialog.lineEdit_tpname->text().toAscii().data();
	if(tpname == "")
		return;

	_addtpdialog->hide();

	std::string mapname = _ui_addtpdialog.comboBox_map->currentText().toAscii().data();
	std::string spawnname = _ui_addtpdialog.comboBox_spawn->currentText().toAscii().data();

	long spid = -1;
	if(spawnname != "")
	{
		LbaNet::MapsSeq::iterator itmap = _winfo.Maps.find(mapname);
		if(itmap != _winfo.Maps.end())
		{
			LbaNet::SpawningsSeq::iterator it = itmap->second.Spawnings.begin();
			LbaNet::SpawningsSeq::iterator end = itmap->second.Spawnings.end();
			for(;it != end; ++it)
			{
				if(spawnname == it->second.Name)
				{
					spid = it->first;
					break;
				}
			}
		}
	}

	long tpid = 0;
	if(_edited_tp >= 0)
		tpid = _edited_tp;
	else
	{
		tpid = (++_currteleportidx);
	}

	QStringList data;
	data << tpname.c_str() << mapname.c_str() << spawnname.c_str();
	_tplistmodel->AddOrUpdateRow(tpid, data);


	_winfo.TeleportInfo[tpid].Name = tpname;
	_winfo.TeleportInfo[tpid].MapName = mapname;
	_winfo.TeleportInfo[tpid].SpawningId = spid;

	//inform server
	EditorUpdateBasePtr update = new UpdateEditor_TeleportListChanged(_winfo.TeleportInfo);
	SharedDataHandler::getInstance()->EditorUpdate("-", update);

	SetModified();
}


/***********************************************************
tp add button push
***********************************************************/
void EditorHandler::TpDialogMapChanged(int flag)
{
	std::string mapname = _ui_addtpdialog.comboBox_map->currentText().toAscii().data();

	std::map<std::string, boost::shared_ptr<CustomStringListModel> >::iterator itsp = 
											_mapSpawningList.find(mapname.c_str());
	if(itsp != _mapSpawningList.end())
	{
		_ui_addtpdialog.comboBox_spawn->setModel(itsp->second.get());

		if(itsp->second->stringList().size() > 0)
			_ui_addtpdialog.comboBox_spawn->setCurrentIndex(0);
	}
}


/***********************************************************
update tp list with new span name
***********************************************************/
void EditorHandler::UpdateTpSpanName(const std::string & mapname, 
									 long spwid, 
									 const std::string &  spname)
{
	LbaNet::ServerTeleportsSeq::iterator it = _winfo.TeleportInfo.begin();
	LbaNet::ServerTeleportsSeq::iterator end = _winfo.TeleportInfo.end();
	for(; it != end; ++it)
	{
		if(it->second.MapName == mapname)
		{
			if(it->second.SpawningId = spwid)
			{
				QStringList data;
				data << it->second.Name.c_str() << mapname.c_str() << spname.c_str();
				_tplistmodel->AddOrUpdateRow(it->first, data);
			}
		}
	}
}


/***********************************************************
add world accepted
***********************************************************/
void EditorHandler::addworld_accepted()
{
	std::string wname = _ui_addworlddialog.lineEdit_worldname->text().toAscii().data();

	if(wname == "")
		return;

	_addworlddialog->hide();
	ResetWorld();

	LbaNet::WorldInformation winfo;
	winfo.Description.WorldName = wname;
	QString descs = _ui_addworlddialog.textEdit_worlddesc->toPlainText();
	descs.replace(QString("\n"), QString(" @ "));
	winfo.Description.Description = descs.toUtf8().data();
	winfo.StartingInfo.InventorySize = 30;
	winfo.StartingInfo.StartingLife = 50;
	winfo.StartingInfo.StartingMana = 50;
	winfo.StartingInfo.StartingModel.TypeRenderer = LbaNet::RenderLba1M;
	winfo.StartingInfo.StartingModel.ModelName = "Twinsen";
	winfo.StartingInfo.StartingModel.Outfit = "Nurse";
	winfo.StartingInfo.StartingModel.Weapon = "No";
	winfo.StartingInfo.StartingModel.Mode = "Normal";
	winfo.StartingInfo.SpawningId = -1;


	//create directories
	try	{boost::filesystem::create_directory( "./Data/Worlds/" + wname );}catch(...){}
	try	{boost::filesystem::create_directory( "./Data/Worlds/" + wname + "/Lua");}catch(...){}
	try	{boost::filesystem::create_directory( "./Data/Worlds/" + wname + "/Models");}catch(...){}
	try	{boost::filesystem::create_directory( "./Data/Worlds/" + wname + "/Texts");}catch(...){}
	try	{boost::filesystem::create_directory( "./Data/Worlds/" + wname + "/InventoryImages");}catch(...){}
	try	{boost::filesystem::create_directory( "./Data/Worlds/" + wname + "/Sprites");}catch(...){}

	
	// save new world
	DataLoader::getInstance()->SaveWorldInformation(wname, winfo);

	//create custom lua files
	{
		std::string path = "Data/Worlds/" + wname + "/Lua/CustomServer.lua";
		std::ofstream filelua(path.c_str());
		filelua<<"-- In this file you can define custom functions to be used on the server side."<<std::endl<<std::endl;
		filelua<<"-- Please note that the changes done on this file will"<<std::endl;
		filelua<<"-- only be reflected on the server when you change map on the editor!"<<std::endl<<std::endl<<std::endl;
		filelua<<"-- A function used as custom action should have the following signature:"<<std::endl;
		filelua<<"-- function Functioname(ObjectType, ObjectId, Arguments, Environment)"<<std::endl<<std::endl;
		filelua<<"-- ObjectType and Objectid will contains the type and id of the object triggering the action"<<std::endl;
		filelua<<"-- Arguments is a virtual class containing possible extra arguments"<<std::endl;
		filelua<<"-- Environment is a pointer used to access the server class (see documentation for further information)"<<std::endl<<std::endl<<std::endl;
		filelua.flush();
		filelua.close();
	}
	
	{
		std::string path = "Data/Worlds/" + wname + "/Lua/CustomClient.lua";
		std::ofstream filelua(path.c_str());
		filelua<<"-- In this file you can define custom functions to be used on the client side."<<std::endl;
		filelua<<"-- It is typically used to define custom client script functions."<<std::endl<<std::endl;
		filelua<<"-- Please note that the changes done on this file will"<<std::endl;
		filelua<<"-- only be reflected once you click the \"Refresh client script\" in the top menu of the editor!"<<std::endl<<std::endl<<std::endl;
		filelua<<"-- A function used as custom clientscript should have the following signature:"<<std::endl;
		filelua<<"-- function Functioname(ScriptId)"<<std::endl<<std::endl;
		filelua<<"-- ScriptId is used by many functions of the client API (see documentation for further information on the API)"<<std::endl<<std::endl<<std::endl;
		filelua.flush();
		filelua.close();
	}


	// reset gui to new world
	ResetWorld();
	SetWorldInfo(wname);

	EventsQueue::getReceiverQueue()->AddEvent(new ChangeWorldEvent(wname));

	_modified = false;
	_mapmodified = false;
}



/***********************************************************
on selectactor_double_clicked
***********************************************************/
void EditorHandler::selectactor_double_clicked(const QModelIndex & itm)
{
	ActorSelect_button();
}

/***********************************************************
Actor add button push
***********************************************************/
void EditorHandler::ActorAdd_button()
{
	_ui_addactordialog.lineEdit_name->setText("");
	_addactordialog->show();
}


/***********************************************************
Actor remove button push
***********************************************************/
void EditorHandler::ActorRemove_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_ActorList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();
	if(indexes.size() > 1)
	{
		// inform server
		long id = _actorlistmodel->GetId(indexes[0]);
		RemoveActor(id);

		// remove row from table
		_actorlistmodel->removeRows(indexes[0].row(), 1);

		// clear object
		ClearObjectIfSelected("Actor", id);
	}
}


/***********************************************************
Actor edit button push
***********************************************************/
void EditorHandler::ActorSelect_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_ActorList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();
	if(indexes.size() > 1)
	{
		long id = _actorlistmodel->GetId(indexes[0]);	
		SelectActor(id);
	}
}


/***********************************************************
Actor add button push
***********************************************************/
void EditorHandler::ActorAdd_button_accepted()
{
	_addactordialog->hide();


	// add the actor to internal
	ActorObjectInfo ainfo(_curractoridx+1);
	ainfo.ExtraInfo.Name = _ui_addactordialog.lineEdit_name->text().toAscii().data();
	ainfo.ExtraInfo.NameColorR = 1.0;
	ainfo.ExtraInfo.NameColorG = 1.0;
	ainfo.ExtraInfo.NameColorB = 1.0;

	switch(_ui_addactordialog.comboBox_dtype->currentIndex())
	{
		case 0:
			ainfo.DisplayDesc.TypeRenderer = LbaNet::NoRender;
		break;
		case 1:
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderOsgModel;
		break;
		case 2:
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderSprite;
		break;
		case 3:
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderLba1M;
		break;
		case 4:
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderLba2M;
		break;
	}

	switch(_ui_addactordialog.comboBox_atype->currentIndex())
	{
		case 0:
			ainfo.PhysicDesc.TypePhysO = LbaNet::StaticAType;
		break;
		case 1:
			ainfo.PhysicDesc.TypePhysO = LbaNet::KynematicAType;
		break;
		case 2:
			ainfo.PhysicDesc.TypePhysO = LbaNet::CharControlAType;
		break;
	}

	switch(_ui_addactordialog.comboBox_ptype->currentIndex())
	{
		case 0:
			ainfo.PhysicDesc.TypeShape = LbaNet::NoShape;
		break;
		case 1:
			ainfo.PhysicDesc.TypeShape = LbaNet::BoxShape;
		break;
		case 2:
			ainfo.PhysicDesc.TypeShape = LbaNet::CapsuleShape;
		break;
		case 3:
			ainfo.PhysicDesc.TypeShape = LbaNet::SphereShape;
		break;
		case 4:
			ainfo.PhysicDesc.TypeShape = LbaNet::TriangleMeshShape;
		break;
	}

	ainfo.DisplayDesc.ModelId = 0;
	ainfo.DisplayDesc.UseLight = true;
	ainfo.DisplayDesc.CastShadow = true;
	ainfo.DisplayDesc.ColorR = 1;
	ainfo.DisplayDesc.ColorG = 1;
	ainfo.DisplayDesc.ColorB = 1;
	ainfo.DisplayDesc.ColorA = 1;
	ainfo.DisplayDesc.TransX = 0;
	ainfo.DisplayDesc.TransY = 0;
	ainfo.DisplayDesc.TransZ = 0;
	ainfo.DisplayDesc.ScaleX = 1;
	ainfo.DisplayDesc.ScaleY = 1;
	ainfo.DisplayDesc.ScaleZ = 1;
	ainfo.DisplayDesc.RotX = 0;
	ainfo.DisplayDesc.RotY = 0;
	ainfo.DisplayDesc.RotZ = 0;
	ainfo.DisplayDesc.State = LbaNet::StNormal;

	ainfo.PhysicDesc.Pos.X = _posX;
	ainfo.PhysicDesc.Pos.Y = _posY;
	ainfo.PhysicDesc.Pos.Z = _posZ;
	ainfo.PhysicDesc.Pos.Rotation = 0;
	ainfo.PhysicDesc.Density = 1;
	ainfo.PhysicDesc.Collidable = true;
	ainfo.PhysicDesc.SizeX = 1;
	ainfo.PhysicDesc.SizeY = 1;
	ainfo.PhysicDesc.SizeZ = 1;

	// set default model
	if(ainfo.DisplayDesc.TypeRenderer == LbaNet::RenderLba1M)
	{
		ainfo.DisplayDesc.ModelName = "Ameba";
		ainfo.DisplayDesc.Weapon = "No";
		ainfo.DisplayDesc.Mode = "Normal";
		ainfo.DisplayDesc.Outfit = "No";

		ainfo.PhysicDesc.TypeShape = LbaNet::BoxShape;
		ainfo.PhysicDesc.SizeX = 2;
		ainfo.PhysicDesc.SizeY = 1;
		ainfo.PhysicDesc.SizeZ = 2.5;
	}

	// set default model
	if(ainfo.DisplayDesc.TypeRenderer == LbaNet::RenderSprite)
	{
		ainfo.DisplayDesc.UseLight = false;
		ainfo.DisplayDesc.CastShadow = false;
	}


	boost::shared_ptr<ActorHandler> act(new ActorHandler(ainfo));

	AddActorObject(act);
	SetMapModified();

	//inform server
	std::string mapname = _uieditor.label_mapname->text().toAscii().data();
	EditorUpdateBasePtr update = new UpdateEditor_AddOrModActor(act);
	SharedDataHandler::getInstance()->EditorUpdate(mapname, update);

	SelectActor(ainfo.ObjectId);
}




/***********************************************************
remove actor
***********************************************************/
void EditorHandler::RemoveActor(long id)
{
	//remove internal trigger
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator it = _Actors.find(id);
	if(it != _Actors.end())
	{
		_Actors.erase(it);
		SetMapModified();

		//inform server
		std::string mapname = _uieditor.label_mapname->text().toAscii().data();
		EditorUpdateBasePtr update = new UpdateEditor_RemoveActor(id);
		SharedDataHandler::getInstance()->EditorUpdate(mapname, update);

		ClearObjectIfSelected("Actor", id);
	}
}



/***********************************************************
select actor
***********************************************************/
void EditorHandler::SelectActor(long id, const QModelIndex &parent)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator it = _Actors.find(id);
	if(it != _Actors.end())
	{
		if(parent == QModelIndex())
			ResetObject();

		const ActorObjectInfo & ainfo = it->second->GetInfo();
		

		{
			QVector<QVariant> data;
			data<<"Type"<<"Actor";
			_objectmodel->AppendRow(data, parent, true);
		}

		{
			QVector<QVariant> data;
			data<<"SubCategory"<<"-";
			_objectmodel->AppendRow(data, parent, true);
		}

		{
			QVector<QVariant> data;
			data<<"Id"<<id;
			_objectmodel->AppendRow(data, parent, true);
		}

		{
			QVector<QVariant> data;
			data<<"Name"<<ainfo.ExtraInfo.Name.c_str();
			_objectmodel->AppendRow(data, parent);
		}


		{
			ConditionBasePtr condptr = ainfo.Condition;

			QVector<QVariant> data;
			data << "Display condition" << GetConditionType(condptr).c_str();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);

			if(condptr)
				SelectCondition(condptr, idx);
		}


		std::string type;
		switch(ainfo.PhysicDesc.TypePhysO)
		{
			case LbaNet::StaticAType:
				type = "Static";
			break;

			case LbaNet::KynematicAType:
				type = "Scripted";
			break;

			case LbaNet::CharControlAType:
				type = "Movable";
			break;  
		}
		{
			QVector<QVariant> data;
			data<<"Type"<<type.c_str();
			_objectmodel->AppendRow(data, parent);
		}

		std::string dtype = "No";
		switch(ainfo.DisplayDesc.TypeRenderer)
		{
			case LbaNet::RenderOsgModel:
				dtype = "Osg Model";
			break;

			case RenderSprite:
				dtype = "Sprite";
			break;

			case RenderLba1M:
				dtype = "Lba1 Model";
			break;

			case RenderLba2M:
				dtype = "Lba2 Model";
			break;

			case RenderCross:
				dtype = "Cross";
			break;

			case RenderBox:
				dtype = "Box";
			break;

			case RenderCapsule:
				dtype = "Capsule";
			break;
		}
		{
			QVector<QVariant> data;
			data<<"Display Type"<<dtype.c_str();
			_objectmodel->AppendRow(data, parent);
		}

		std::string ptype;
		switch(ainfo.PhysicDesc.TypeShape)
		{
			case LbaNet::NoShape:
				ptype = "No Shape";
			break;
			case BoxShape:
				ptype = "Box";
			break;
			case CapsuleShape:
				ptype = "Capsule";
			break;
			case SphereShape:
				ptype = "Sphere";
			break;
			case TriangleMeshShape:
				ptype = "Triangle Mesh";
			break;
		}
		{
			QVector<QVariant> data;
			data<<"Physical Type"<<ptype.c_str();
			_objectmodel->AppendRow(data, parent);
		}

		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _conditiontypeList);
		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 5, parent), _actortypeList);
		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 6, parent), _actordtypeList);
		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 7, parent), _actorptypeList);		


		{
			QVector<QVariant> data;
			data<<"Position X"<<(double)ainfo.PhysicDesc.Pos.X;
			_objectmodel->AppendRow(data, parent);
		}
		{
			QVector<QVariant> data;
			data<<"Position Y"<<(double)ainfo.PhysicDesc.Pos.Y;
			_objectmodel->AppendRow(data, parent);
		}
		{
			QVector<QVariant> data;
			data<<"Position Z"<<(double)ainfo.PhysicDesc.Pos.Z;
			_objectmodel->AppendRow(data, parent);
		}
		{
			QVector<QVariant> data;
			data<<"Rotation"<<(double)ainfo.PhysicDesc.Pos.Rotation;
			_objectmodel->AppendRow(data, parent);
		}

		int index = 12;

		if(ainfo.PhysicDesc.TypeShape != LbaNet::NoShape)
		{
			{
				QVector<QVariant> data;
				data<<"Collidable"<<ainfo.PhysicDesc.Collidable;
				_objectmodel->AppendRow(data, parent);
				++index;
			}

			if(ainfo.PhysicDesc.TypeShape != LbaNet::TriangleMeshShape)
			{
				{
					QVector<QVariant> data;
					data<<"Size X"<<(double)ainfo.PhysicDesc.SizeX;
					_objectmodel->AppendRow(data, parent);
					++index;
				}
				{
					QVector<QVariant> data;
					data<<"Size Y"<<(double)ainfo.PhysicDesc.SizeY;
					_objectmodel->AppendRow(data, parent);
					++index;
				}
				{
					QVector<QVariant> data;
					data<<"Size Z"<<(double)ainfo.PhysicDesc.SizeZ;
					_objectmodel->AppendRow(data, parent);
					++index;
				}
			}
			else
			{
				{
					QVector<QVariant> data;
					data<<"Physic filename"<<ainfo.PhysicDesc.Filename.c_str();
					_objectmodel->AppendRow(data, parent);

					boost::shared_ptr<FileDialogOptionsBase> filefilter(new FileDialogOptionsModel());
					filefilter->Title = "Select physic file";
					filefilter->StartingDirectory = ("Data/Worlds/" + _winfo.Description.WorldName + "/Models").c_str();
					filefilter->FileFilter = "Physic Files (*.phy)";
					_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), filefilter);

					++index;
				}
			}
		}

		if(dtype != "No")
		{
			{
				QVector<QVariant> data;
				data<<"Use Light"<<ainfo.DisplayDesc.UseLight;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
			{
				QVector<QVariant> data;
				data<<"Cast shadow"<<ainfo.DisplayDesc.CastShadow;
				_objectmodel->AppendRow(data, parent);
				++index;
			}

			{
				QVector<QVariant> data;
				data<<"Display translation X"<<(double)ainfo.DisplayDesc.TransX;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
			{
				QVector<QVariant> data;
				data<<"Display translation Y"<<(double)ainfo.DisplayDesc.TransY;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
			{
				QVector<QVariant> data;
				data<<"Display translation Z"<<(double)ainfo.DisplayDesc.TransZ;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
			{
				QVector<QVariant> data;
				data<<"Display rotation X"<<(double)ainfo.DisplayDesc.RotX;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
			{
				QVector<QVariant> data;
				data<<"Display rotation Y"<<(double)ainfo.DisplayDesc.RotY;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
			{
				QVector<QVariant> data;
				data<<"Display rotation Z"<<(double)ainfo.DisplayDesc.RotZ;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
			{
				QVector<QVariant> data;
				data<<"Display scale X"<<(double)ainfo.DisplayDesc.ScaleX;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
			{
				QVector<QVariant> data;
				data<<"Display scale Y"<<(double)ainfo.DisplayDesc.ScaleY;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
			{
				QVector<QVariant> data;
				data<<"Display scale Z"<<(double)ainfo.DisplayDesc.ScaleZ;
				_objectmodel->AppendRow(data, parent);
				++index;
			}


			if(ainfo.DisplayDesc.TypeRenderer == RenderOsgModel )
			{
				QVector<QVariant> data;
				data<<"Display model file"<<ainfo.DisplayDesc.ModelName.c_str();
				_objectmodel->AppendRow(data, parent);

				boost::shared_ptr<FileDialogOptionsBase> filefilter(new FileDialogOptionsModel());
				filefilter->Title = "Select a model file";
				filefilter->StartingDirectory = ("Data/Worlds/" + _winfo.Description.WorldName + "/Models").c_str();;
				filefilter->FileFilter = "Model Files (*.osg *.osgb *.osgt)";
				_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), filefilter);
				++index;
			}

			if(ainfo.DisplayDesc.TypeRenderer == RenderSprite )
			{
				QVector<QVariant> data;
				data<<"Display sprite file"<<ainfo.DisplayDesc.ModelName.c_str();
				_objectmodel->AppendRow(data, parent);

				boost::shared_ptr<FileDialogOptionsBase> filefilter(new FileDialogOptionsModel());
				filefilter->Title = "Select an image";
				filefilter->StartingDirectory = ("Data/Worlds/" + _winfo.Description.WorldName + "/Sprites").c_str();;
				filefilter->FileFilter = "Image Files (*.png *.bmp *.jpg *.gif)";
				_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), filefilter);
				++index;

				{
					QVector<QVariant> data1;
					data1<<"Color R"<<(double)ainfo.DisplayDesc.ColorR;
					_objectmodel->AppendRow(data1, parent);
					++index;
				}
				{
					QVector<QVariant> data1;
					data1<<"Color G"<<(double)ainfo.DisplayDesc.ColorG;
					_objectmodel->AppendRow(data1, parent);
					++index;
				}
				{
					QVector<QVariant> data1;
					data1<<"Color B"<<(double)ainfo.DisplayDesc.ColorB;
					_objectmodel->AppendRow(data1, parent);
					++index;
				}
				{
					QVector<QVariant> data1;
					data1<<"Color A"<<(double)ainfo.DisplayDesc.ColorA;
					_objectmodel->AppendRow(data1, parent);
					++index;
				}
			}

			if(ainfo.DisplayDesc.TypeRenderer == RenderLba1M ||
					ainfo.DisplayDesc.TypeRenderer == RenderLba2M)
			{
				int modelaidx = index;

				QVector<QVariant> data;
				data<<"Display model name"<<ainfo.DisplayDesc.ModelName.c_str();
				_objectmodel->AppendRow(data, parent);

				_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actorModelNameList);
				++index;

				QVector<QVariant> data2;
				data2<<"Display model outfit"<<ainfo.DisplayDesc.Outfit.c_str();
				_objectmodel->AppendRow(data2, parent);
				
				_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actorModelOutfitList);
				++index;

				QVector<QVariant> data3;
				data3<<"Display model weapon"<<ainfo.DisplayDesc.Weapon.c_str();
				_objectmodel->AppendRow(data3, parent);
				
				_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actorModelWeaponList);
				++index;

				QVector<QVariant> data4;
				data4<<"Display model mode"<<ainfo.DisplayDesc.Mode.c_str();
				_objectmodel->AppendRow(data4, parent);
				
				_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actorModelModeList);
				++index;

				const std::vector<int> &currpolyvec = it->second->currentpolycolors;
				const std::vector<int> &currspherevec = it->second->currentspherecolors;
				const std::vector<int> &currlinevec = it->second->currentlinecolors;
				for(size_t cc = 0; cc<currpolyvec.size(); ++cc)
				{
					QVector<QVariant> data4;
					std::stringstream names;
					names<<"Poly color "<<cc+1;
					data4<<names.str().c_str()<<currpolyvec[cc];
					_objectmodel->AppendRow(data4, parent);	
					++index;
				}

				for(size_t cc = 0; cc<currspherevec.size(); ++cc)
				{
					QVector<QVariant> data4;
					std::stringstream names;
					names<<"Sphere color "<<cc+1;
					data4<<names.str().c_str()<<currspherevec[cc];
					_objectmodel->AppendRow(data4, parent);	
					++index;
				}

				for(size_t cc = 0; cc<currlinevec.size(); ++cc)
				{
					QVector<QVariant> data4;
					std::stringstream names;
					names<<"Line color "<<cc+1;
					data4<<names.str().c_str()<<currlinevec[cc];
					_objectmodel->AppendRow(data4, parent);	
					++index;
				}

				RefreshActorModelName(modelaidx, parent, false, it->second);
			}
		}

		UpdateSelectedActorDisplay(ainfo.PhysicDesc);
		osg::Vec3 center = _actornode->computeBound().center();
		DrawArrows(center.x(), center.y(), center.z());
	}
}



/***********************************************************
called when actor object changed
***********************************************************/
void EditorHandler::ActorObjectChanged(long id, const QModelIndex &parentIdx, int updatedrow)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator it = _Actors.find(id);
	if(it != _Actors.end())
	{
		bool updateobj = false;
		ActorObjectInfo & ainfo = it->second->GetInfo();

		ainfo.ExtraInfo.Name = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toString().toAscii().data();

		ainfo.PhysicDesc.Pos.X = _objectmodel->data(_objectmodel->GetIndex(1, 8, parentIdx)).toFloat();
		ainfo.PhysicDesc.Pos.Y = _objectmodel->data(_objectmodel->GetIndex(1, 9, parentIdx)).toFloat();
		ainfo.PhysicDesc.Pos.Z = _objectmodel->data(_objectmodel->GetIndex(1, 10, parentIdx)).toFloat();
		ainfo.PhysicDesc.Pos.Rotation = _objectmodel->data(_objectmodel->GetIndex(1, 11, parentIdx)).toFloat();


		//condition
		{
			std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toString().toAscii().data();
			std::string currcond = GetConditionType(ainfo.Condition);

			if(condition != currcond)
			{
				ConditionBasePtr ptrtmp = CreateCondition(condition);
				ainfo.Condition = ptrtmp;

				QModelIndex curidx = _objectmodel->GetIndex(0, 4, parentIdx);
				_objectmodel->Clear(curidx);
				if(ptrtmp)
				{
					SelectCondition(ptrtmp, curidx);

					_uieditor.treeView_object->setExpanded(curidx, true); // expand 
				}
			}
		}

		int index = 12;

		if(ainfo.PhysicDesc.TypeShape != LbaNet::NoShape)
		{
			ainfo.PhysicDesc.Collidable = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
			++index;

			if(ainfo.PhysicDesc.TypeShape != LbaNet::TriangleMeshShape)
			{
				ainfo.PhysicDesc.SizeX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
				++index;
				ainfo.PhysicDesc.SizeY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
				++index;
				ainfo.PhysicDesc.SizeZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
				++index;
			}
			else
			{
				ainfo.PhysicDesc.Filename = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				++index;
			}
		}

		if(ainfo.DisplayDesc.TypeRenderer != LbaNet::NoRender)
		{
			ainfo.DisplayDesc.UseLight = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
			++index;

			ainfo.DisplayDesc.CastShadow = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
			++index;

			ainfo.DisplayDesc.TransX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			ainfo.DisplayDesc.TransY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			ainfo.DisplayDesc.TransZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;

			ainfo.DisplayDesc.RotX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			ainfo.DisplayDesc.RotY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			ainfo.DisplayDesc.RotZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;

			ainfo.DisplayDesc.ScaleX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			ainfo.DisplayDesc.ScaleY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			ainfo.DisplayDesc.ScaleZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;


			if(ainfo.DisplayDesc.TypeRenderer == RenderOsgModel )
			{
				ainfo.DisplayDesc.ModelName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				++index;
			}

			if(ainfo.DisplayDesc.TypeRenderer == RenderSprite )
			{
				ainfo.DisplayDesc.ModelName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				++index;	

				ainfo.DisplayDesc.ColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;	

				ainfo.DisplayDesc.ColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;		

				ainfo.DisplayDesc.ColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;		

				ainfo.DisplayDesc.ColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;			
			}

			// todo - model needs a slight offset Y
			if(ainfo.DisplayDesc.TypeRenderer == RenderLba1M ||
					ainfo.DisplayDesc.TypeRenderer == RenderLba2M)
			{
				std::string oldmodelname = ainfo.DisplayDesc.ModelName;
				std::string oldmodelOutfit = ainfo.DisplayDesc.Outfit;
				std::string oldmodelWeapon = ainfo.DisplayDesc.Weapon;

				ainfo.DisplayDesc.ModelName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();		
				++index;		

				ainfo.DisplayDesc.Outfit = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				if(ainfo.DisplayDesc.ModelName != oldmodelname)
				{
					RefreshActorModelOutfit(index, parentIdx, ainfo.DisplayDesc.ModelName, true, it->second);

					updateobj = true;
				}
				
				++index;	

				ainfo.DisplayDesc.Weapon = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				if(ainfo.DisplayDesc.Outfit != oldmodelOutfit)
				{
					RefreshActorModelWeapon(index, parentIdx, ainfo.DisplayDesc.ModelName,
																	ainfo.DisplayDesc.Outfit, true, it->second);

					updateobj = true;
				}	
				
				++index;	

				ainfo.DisplayDesc.Mode = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				if(ainfo.DisplayDesc.Weapon != oldmodelWeapon)
				{
					RefreshActorModelMode(index, parentIdx, ainfo.DisplayDesc.ModelName,
																	ainfo.DisplayDesc.Outfit,
																	ainfo.DisplayDesc.Weapon, true, it->second);

					updateobj = true;
				}
				
				++index;

				for(size_t cc = 0; cc<it->second->currentpolycolors.size(); ++cc)
				{
					int color = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();
					if(color < 0)
						color = 0;
					if(color > 255)
						color = 255;

					if((updatedrow == index) && it->second->currentpolycolors[cc] != color)
					{
						it->second->currentpolycolors[cc] = color;

						LbaNet::Lba1ColorIndex idxc;
						idxc.ModelPart = LbaNet::PolygonColor;
						idxc.Color = it->second->initpolycolors[cc];
						ainfo.DisplayDesc.ColorSwaps[idxc] = color;
					}
	
					++index;
				}

				for(size_t cc = 0; cc<it->second->currentspherecolors.size(); ++cc)
				{
					int color = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();
					if(color < 0)
						color = 0;
					if(color > 255)
						color = 255;

					if((updatedrow == index) && it->second->currentspherecolors[cc] != color)
					{
						it->second->currentspherecolors[cc] = color;

						LbaNet::Lba1ColorIndex idxc;
						idxc.ModelPart = LbaNet::SphereColor;
						idxc.Color = it->second->initspherecolors[cc];
						ainfo.DisplayDesc.ColorSwaps[idxc] = color;
					}
	
					++index;
				}

				for(size_t cc = 0; cc<it->second->currentlinecolors.size(); ++cc)
				{
					int color = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();
					if(color < 0)
						color = 0;
					if(color > 255)
						color = 255;

					if((updatedrow == index) && it->second->currentlinecolors[cc] != color)
					{
						it->second->currentlinecolors[cc] = color;

						LbaNet::Lba1ColorIndex idxc;
						idxc.ModelPart = LbaNet::LineColor;
						idxc.Color = it->second->initlinecolors[cc];
						ainfo.DisplayDesc.ColorSwaps[idxc] = color;
					}
	
					++index;
				}
	
			}
		}

		
		{
		LbaNet::PhysicalActorType before = ainfo.PhysicDesc.TypePhysO;
		std::string type = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toString().toAscii().data();
		if(type == "Static") 
			ainfo.PhysicDesc.TypePhysO = LbaNet::StaticAType;
		if(type == "Scripted") 
			ainfo.PhysicDesc.TypePhysO = LbaNet::KynematicAType;
		if(type == "Movable") 
			ainfo.PhysicDesc.TypePhysO = LbaNet::CharControlAType;
		if(before != ainfo.PhysicDesc.TypePhysO)
			updateobj = true;

		LbaNet::RenderTypeEnum befored = ainfo.DisplayDesc.TypeRenderer;
		ainfo.DisplayDesc.TypeRenderer = LbaNet::NoRender;
		
		std::string dtype = _objectmodel->data(_objectmodel->GetIndex(1, 6, parentIdx)).toString().toAscii().data();
		if(dtype == "Osg Model") 
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderOsgModel;
		if(dtype == "Sprite") 
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderSprite;
		if(dtype == "Lba1 Model") 
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderLba1M;
		if(dtype == "Lba2 Model") 
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderLba2M;

		if(befored != ainfo.DisplayDesc.TypeRenderer)
			updateobj = true;

		LbaNet::PhysicalShapeEnum beforep = ainfo.PhysicDesc.TypeShape;
		std::string ptype = _objectmodel->data(_objectmodel->GetIndex(1, 7, parentIdx)).toString().toAscii().data();
		if(ptype == "No Shape") 
			ainfo.PhysicDesc.TypeShape = LbaNet::NoShape;
		if(ptype == "Box") 
			ainfo.PhysicDesc.TypeShape = LbaNet::BoxShape;
		if(ptype == "Capsule") 
			ainfo.PhysicDesc.TypeShape = LbaNet::CapsuleShape;
		if(ptype == "Sphere") 
			ainfo.PhysicDesc.TypeShape = LbaNet::SphereShape;
		if(ptype == "Triangle Mesh") 
			ainfo.PhysicDesc.TypeShape = LbaNet::TriangleMeshShape;
		if(beforep != ainfo.PhysicDesc.TypeShape)
			updateobj = true;
		}


		//inform server
		std::string mapname = _uieditor.label_mapname->text().toAscii().data();
		EditorUpdateBasePtr update = new UpdateEditor_AddOrModActor(it->second);
		SharedDataHandler::getInstance()->EditorUpdate(mapname, update);


		// update list
		{
			std::string type;
			switch(ainfo.PhysicDesc.TypePhysO)
			{
				case LbaNet::StaticAType:
					type = "Static";
				break;

				case LbaNet::KynematicAType:
					type = "Scripted";
				break;

				case LbaNet::CharControlAType:
					type = "Movable";
				break;  
			}


			std::string dtype = "No";
			switch(ainfo.DisplayDesc.TypeRenderer)
			{
				case LbaNet::RenderOsgModel:
					dtype = "Osg Model";
				break;

				case RenderSprite:
					dtype = "Sprite";
				break;

				case RenderLba1M:
					dtype = "Lba1 Model";
				break;

				case RenderLba2M:
					dtype = "Lba2 Model";
				break;

				case RenderCross:
					dtype = "Cross";
				break;

				case RenderBox:
					dtype = "Box";
				break;

				case RenderCapsule:
					dtype = "Capsule";
				break;
			}

			std::string ptype;
			switch(ainfo.PhysicDesc.TypeShape)
			{
				case LbaNet::NoShape:
					ptype = "No Shape";
				break;
				case BoxShape:
					ptype = "Box";
				break;
				case CapsuleShape:
					ptype = "Capsule";
				break;
				case SphereShape:
					ptype = "Sphere";
				break;
				case TriangleMeshShape:
					ptype = "Triangle Mesh";
				break;
			}

			std::string name = ainfo.ExtraInfo.Name;
			if(name == "")
				name = "-";

			QStringList data;
			data << name.c_str()<< type.c_str()  << dtype.c_str() << ptype.c_str();
			_actorlistmodel->AddOrUpdateRow(id, data);
		}



		//refresh object
		if(updateobj)
			SelectActor(id);


		SetMapModified();
		UpdateSelectedActorDisplay(ainfo.PhysicDesc);
	}
}


/***********************************************************
update editor selected ector display
***********************************************************/
void EditorHandler::UpdateSelectedActorDisplay(LbaNet::ObjectPhysicDesc desc)
{
	RemoveSelectedActorDislay();

	_actornode = OsgHandler::getInstance()->AddEmptyActorNode(false);

	osg::Matrixd Trans;
	osg::Matrixd Rotation;
	Trans.makeTranslate(desc.Pos.X, desc.Pos.Y, desc.Pos.Z);
	LbaQuaternion Q(desc.Pos.Rotation, LbaVec3(0,1,0));
	Rotation.makeRotate(osg::Quat(Q.X, Q.Y, Q.Z, Q.W));
	_actornode->setMatrix(Rotation * Trans);

	switch(desc.TypeShape)
	{
		case LbaNet::NoShape:
		{
			osg::Geode* lineGeode = new osg::Geode();
			osg::Geometry* lineGeometry = new osg::Geometry();
			lineGeode->addDrawable(lineGeometry); 

			osg::Vec3Array* lineVertices = new osg::Vec3Array();
			lineVertices->push_back( osg::Vec3( -2, 0, 0) );
			lineVertices->push_back( osg::Vec3(2, 0, 0) );
			lineVertices->push_back( osg::Vec3(0 , 0, -2) );
			lineVertices->push_back( osg::Vec3(0 , 0, 2) );
			lineGeometry->setVertexArray( lineVertices ); 

			osg::Vec4Array* linecolor = new osg::Vec4Array();
			linecolor->push_back( osg::Vec4( 0.2, 0.2, 1.0, 0.5) );
			lineGeometry->setColorArray(linecolor);
			lineGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);

			osg::DrawElementsUInt* dunit = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
			dunit->push_back(0);
			dunit->push_back(1);
			dunit->push_back(2);
			dunit->push_back(3);
			lineGeometry->addPrimitiveSet(dunit); 
			_actornode->addChild(lineGeode);

			osg::StateSet* stateset = lineGeometry->getOrCreateStateSet();
			osg::LineWidth* linewidth = new osg::LineWidth();

			linewidth->setWidth(3.0f);
			stateset->setAttributeAndModes(linewidth,osg::StateAttribute::ON);
			stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
			stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
			stateset->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
			stateset->setRenderBinDetails( 8000, "RenderBin");


		}
		break;
		case LbaNet::BoxShape:
		{
			osg::ref_ptr<osg::Geode> capsuleGeode(new osg::Geode());
			osg::ref_ptr<osg::Box> caps(new osg::Box(osg::Vec3(0,(desc.SizeY/2),0), desc.SizeX, desc.SizeY, desc.SizeZ));
			osg::ref_ptr<osg::ShapeDrawable> capsdraw = new osg::ShapeDrawable(caps);
			capsdraw->setColor(osg::Vec4(0.2, 0.2, 1.0, 0.4));
			capsuleGeode->addDrawable(capsdraw);
			_actornode->addChild(capsuleGeode);

			osg::StateSet* stateset = capsuleGeode->getOrCreateStateSet();
			stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
			stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
			stateset->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
			stateset->setRenderBinDetails( 8000, "RenderBin");	
		}
		break;
		case CapsuleShape:
		{
			osg::ref_ptr<osg::Geode> capsuleGeode(new osg::Geode());
			osg::ref_ptr<osg::Capsule> caps(new osg::Capsule(osg::Vec3(0,desc.SizeY/2,0),desc.SizeX/2,desc.SizeY-desc.SizeX));
			osg::ref_ptr<osg::ShapeDrawable> capsdraw = new osg::ShapeDrawable(caps);
			capsdraw->setColor(osg::Vec4(0.2, 0.2, 1.0, 0.4));
			capsuleGeode->addDrawable(capsdraw);
			_actornode->addChild(capsuleGeode);

			osg::Matrixd RotationC;
			LbaQuaternion QC(90, LbaVec3(1,0,0));
			RotationC.makeRotate(osg::Quat(QC.X, QC.Y, QC.Z, QC.W));
			osg::Quat quatC;
			quatC.set(RotationC);
			caps->setRotation(quatC);

			osg::StateSet* stateset = capsuleGeode->getOrCreateStateSet();
			stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
			stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
			stateset->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
			stateset->setRenderBinDetails( 8000, "RenderBin");	
		}
		break;
		case SphereShape:
		{
			osg::ref_ptr<osg::Geode> capsuleGeode(new osg::Geode());
			osg::ref_ptr<osg::Sphere> caps(new osg::Sphere(osg::Vec3(0,desc.SizeY/2,0),desc.SizeY/2));
			osg::ref_ptr<osg::ShapeDrawable> capsdraw = new osg::ShapeDrawable(caps);
			capsdraw->setColor(osg::Vec4(0.2, 0.2, 1.0, 0.4));
			capsuleGeode->addDrawable(capsdraw);
			_actornode->addChild(capsuleGeode);

			osg::StateSet* stateset = capsuleGeode->getOrCreateStateSet();
			stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
			stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
			stateset->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
			stateset->setRenderBinDetails( 8000, "RenderBin");	
		}
		break;
		case TriangleMeshShape:
		{
			std::ifstream file(("Data/"+desc.Filename).c_str(), std::ifstream::binary);
			if(!file.is_open())
				return;

			unsigned int sizevertex;
			unsigned int sizeindices;
			unsigned int sizematerials;

			file.read((char*)&sizevertex, sizeof(unsigned int));
			file.read((char*)&sizeindices, sizeof(unsigned int));
			file.read((char*)&sizematerials, sizeof(unsigned int));

			float *buffervertex = new float[sizevertex];
			unsigned int *bufferindices = new unsigned int[sizeindices];
			file.read((char*)buffervertex, sizevertex*sizeof(float));
			file.read((char*)bufferindices, sizeindices*sizeof(unsigned int));

			osg::ref_ptr<osg::Geode> myGeode = new osg::Geode();
			_actornode->addChild(myGeode);
			osg::ref_ptr<osg::Geometry> m_myGeometry = new osg::Geometry();
			myGeode->addDrawable(m_myGeometry.get());

			osg::Vec3Array* myVerticesPoly = new osg::Vec3Array;
			for(unsigned int i=0; i<sizevertex; i+=3)
				myVerticesPoly->push_back(osg::Vec3(buffervertex[i], buffervertex[i+1], buffervertex[i+2]));
			m_myGeometry->setVertexArray( myVerticesPoly ); 

			osg::DrawElementsUInt* myprimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
			for(unsigned int i=0; i<sizeindices; ++i)
				myprimitive->push_back(bufferindices[i]);

			m_myGeometry->addPrimitiveSet(myprimitive);

			osgUtil::SmoothingVisitor::smooth(*(m_myGeometry.get()));

			osg::Vec4Array* colors = new osg::Vec4Array;
			colors->push_back(osg::Vec4(0.2, 0.2, 1.0, 0.4));
			m_myGeometry->setColorArray(colors);
			m_myGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);

			delete[] buffervertex;
			delete[] bufferindices;

			osg::StateSet* stateset = myGeode->getOrCreateStateSet();
			stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
			stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
			stateset->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
			stateset->setRenderBinDetails( 8000, "RenderBin");	

		}
		break;
	}


}


/***********************************************************
remove current selected display
***********************************************************/
void EditorHandler::RemoveSelectedActorDislay()
{
	if(_actornode)
		OsgHandler::getInstance()->RemoveActorNode(_actornode, false);

	_actornode = NULL;
}


/***********************************************************
called when an object is picked
***********************************************************/
void EditorHandler::PickedObject(const std::string & name)
{
	if(_draggerX && _draggerX->getDraggerActive())
		return;

	if(_draggerY && _draggerY->getDraggerActive())
		return;

	if(_draggerZ && _draggerZ->getDraggerActive())
		return;

	if(name == "")
	{
		ResetObject();
		return;
	}

	long id = atol(name.substr(2).c_str());


	switch(name[0])
	{
		case 'A':
			SelectActor(id);
		break;
		case 'E':
			if(id > 2000000)
				SelectTrigger(id-2000000);
			else if(id > 1000000)
				SelectSpawning(id-1000000);
		break;
		case 'M':
			ResetObject();
		break;
	}
}


/***********************************************************
update editor selected trigger display
***********************************************************/
void EditorHandler::UpdateSelectedZoneTriggerDisplay(float PosX, float PosY, float PosZ,
													 float SizeX, float SizeY, float SizeZ)
{
	RemoveSelectedActorDislay();

	_actornode = OsgHandler::getInstance()->AddEmptyActorNode(false);

	osg::Matrixd Trans;
	Trans.makeTranslate(PosX, PosY, PosZ);
	_actornode->setMatrix(Trans);


	osg::ref_ptr<osg::Geode> capsuleGeode(new osg::Geode());
	osg::ref_ptr<osg::Box> caps(new osg::Box(osg::Vec3(0,SizeY/2,0), SizeX, SizeY, SizeZ));
	osg::ref_ptr<osg::ShapeDrawable> capsdraw = new osg::ShapeDrawable(caps);
	capsdraw->setColor(osg::Vec4(0.5, 0.0, 0.0, 1.0));
	capsuleGeode->addDrawable(capsdraw);
	_actornode->addChild(capsuleGeode);

	osg::StateSet* stateset = capsuleGeode->getOrCreateStateSet();
	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	stateset->setRenderingHint( osg::StateSet::OPAQUE_BIN );
	stateset->setRenderBinDetails( 9100, "RenderBin");	

	osg::PolygonMode* polymode = new osg::PolygonMode;
	polymode->setMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE);
	stateset->setAttributeAndModes(polymode,osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
}


/***********************************************************
update editor selected trigger display
***********************************************************/
void EditorHandler::UpdateSelectedDistanceTriggerDisplay(float PosX, float PosY, float PosZ, float distance)
{
	RemoveSelectedActorDislay();

	_actornode = OsgHandler::getInstance()->AddEmptyActorNode(false);

	osg::Matrixd Trans;
	Trans.makeTranslate(PosX, PosY, PosZ);
	_actornode->setMatrix(Trans);


	osg::ref_ptr<osg::Geode> capsuleGeode(new osg::Geode());
	osg::ref_ptr<osg::Sphere> caps(new osg::Sphere(osg::Vec3(0,0,0), distance));
	osg::ref_ptr<osg::ShapeDrawable> capsdraw = new osg::ShapeDrawable(caps);
	capsdraw->setColor(osg::Vec4(0.5, 0.0, 0.0, 0.2));
	capsuleGeode->addDrawable(capsdraw);
	_actornode->addChild(capsuleGeode);

	osg::StateSet* stateset = capsuleGeode->getOrCreateStateSet();
	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	stateset->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
	stateset->setRenderBinDetails( 9100, "RenderBin");	
}





/***********************************************************
draw arrow on selected object
***********************************************************/
void EditorHandler::DrawArrows(float PosX, float PosY, float PosZ)
{
	RemoveArrows();

	_arrownode = OsgHandler::getInstance()->AddEmptyActorNode(false);

	osg::ref_ptr<osg::Camera> PostRenderCam = new osg::Camera;
	PostRenderCam->setClearMask(GL_DEPTH_BUFFER_BIT);
	PostRenderCam->setRenderOrder(osg::Camera::POST_RENDER, 90000);
	_arrownode->addChild(PostRenderCam);

	{
		_draggerX = new osgManipulator::Translate1DDragger(osg::Vec3d(0,0,0), osg::Vec3d(1,0,0));
		_draggerX->setCheckForNodeInNodePath(false);

		osg::Matrixd Trans;
		Trans.makeTranslate(PosX, PosY, PosZ);
		osg::Matrixd Scale;
		Scale.makeScale(1, 2, 1);
		_draggerX->setMatrix(Scale*Trans);
		_draggerX->addDraggerCallback(new DraggerCustomCallback(1));
		_draggerX->setHandleEvents(true);
		_draggerX->setColor(osg::Vec4(0.0, 0.8, 0.0, 1.0));
		PostRenderCam->addChild(_draggerX);

		osg::ref_ptr<osg::Geode> myGeode(new osg::Geode());

		osg::ref_ptr<osg::Cylinder> caps(new osg::Cylinder(osg::Vec3(1,0,0), 0.1, 2));
		osg::ref_ptr<osg::ShapeDrawable> capsdraw = new osg::ShapeDrawable(caps);
		myGeode->addDrawable(capsdraw);

		osg::ref_ptr<osg::Cone> caps2(new osg::Cone(osg::Vec3(2,0,0), 0.2, 0.5));
		osg::ref_ptr<osg::ShapeDrawable> capsdraw2 = new osg::ShapeDrawable(caps2);
		myGeode->addDrawable(capsdraw2);

		_draggerX->addChild(myGeode);

		osg::Matrixd RotationC;
		LbaQuaternion QC(90, LbaVec3(0,1,0));
		RotationC.makeRotate(osg::Quat(QC.X, QC.Y, QC.Z, QC.W));
		osg::Quat quatC;
		quatC.set(RotationC);
		caps->setRotation(quatC);
		caps2->setRotation(quatC);
	}


	{
		_draggerY = new osgManipulator::Translate1DDragger(osg::Vec3d(0,0,0), osg::Vec3d(0,1,0));
		_draggerY->setCheckForNodeInNodePath(false);

		osg::Matrixd Trans;
		Trans.makeTranslate(PosX, PosY, PosZ);
		osg::Matrixd Scale;
		Scale.makeScale(1, 2, 1);
		_draggerY->setMatrix(Scale*Trans);
		_draggerY->addDraggerCallback(new DraggerCustomCallback(2));
		_draggerY->setHandleEvents(true);
		_draggerY->setColor(osg::Vec4(0.8, 0.0, 0.0, 1.0));

		PostRenderCam->addChild(_draggerY);


		osg::ref_ptr<osg::Geode> myGeode(new osg::Geode());
		osg::ref_ptr<osg::Cylinder> caps(new osg::Cylinder(osg::Vec3(0,1,0), 0.1, 2));
		osg::ref_ptr<osg::ShapeDrawable> capsdraw = new osg::ShapeDrawable(caps);
		myGeode->addDrawable(capsdraw);

		osg::ref_ptr<osg::Cone> caps2(new osg::Cone(osg::Vec3(0,2,0), 0.2, 0.5));
		osg::ref_ptr<osg::ShapeDrawable> capsdraw2 = new osg::ShapeDrawable(caps2);
		myGeode->addDrawable(capsdraw2);

		_draggerY->addChild(myGeode);


		osg::Matrixd RotationC;
		LbaQuaternion QC(270, LbaVec3(1,0,0));
		RotationC.makeRotate(osg::Quat(QC.X, QC.Y, QC.Z, QC.W));
		osg::Quat quatC;
		quatC.set(RotationC);
		caps->setRotation(quatC);
		caps2->setRotation(quatC);
	}

	{
		_draggerZ = new osgManipulator::Translate1DDragger(osg::Vec3d(0,0,0), osg::Vec3d(0,0,1));
		_draggerZ->setCheckForNodeInNodePath(false);

		osg::Matrixd Trans;
		Trans.makeTranslate(PosX, PosY, PosZ);
		osg::Matrixd Scale;
		Scale.makeScale(1, 2, 1);
		_draggerZ->setMatrix(Scale*Trans);
		_draggerZ->addDraggerCallback(new DraggerCustomCallback(3));
		_draggerZ->setHandleEvents(true);
		_draggerZ->setColor(osg::Vec4(0.0, 0.0, 0.8, 1.0));
		PostRenderCam->addChild(_draggerZ);


		osg::ref_ptr<osg::Geode> myGeode(new osg::Geode());

		osg::ref_ptr<osg::Cylinder> caps(new osg::Cylinder(osg::Vec3(0,0,1), 0.1, 2));
		osg::ref_ptr<osg::ShapeDrawable> capsdraw = new osg::ShapeDrawable(caps);
		myGeode->addDrawable(capsdraw);

		osg::ref_ptr<osg::Cone> caps2(new osg::Cone(osg::Vec3(0,0,2), 0.2, 0.5));
		osg::ref_ptr<osg::ShapeDrawable> capsdraw2 = new osg::ShapeDrawable(caps2);
		myGeode->addDrawable(capsdraw2);

		_draggerZ->addChild(myGeode);
	}

	return;
}



/***********************************************************
when an editor arrow was dragged by mouse
***********************************************************/
void EditorHandler::PickedArrowMoved(int pickedarrow)
{
	if(_objectmodel->rowCount() > 2)
	{
		QString type = _objectmodel->data(_objectmodel->GetIndex(1, 0)).toString();
		std::string category = _objectmodel->data(_objectmodel->GetIndex(1, 1)).toString().toAscii().data();
		long objid = _objectmodel->data(_objectmodel->GetIndex(1, 2)).toString().toLong();


		if(type == "Trigger")
		{
			if(category == "ZoneTrigger")
			{
				if(pickedarrow == 1)
				{
					_objectmodel->setData(_objectmodel->GetIndex(1, 9), floor(_draggerX->getMatrix().getTrans().x()*10)/10);
					_draggerY->setMatrix(_draggerX->getMatrix());
					_draggerZ->setMatrix(_draggerX->getMatrix());
				}

				if(pickedarrow == 2)
				{	
					_objectmodel->setData(_objectmodel->GetIndex(1, 10), floor(_draggerY->getMatrix().getTrans().y()*10)/10);
					_draggerX->setMatrix(_draggerY->getMatrix());
					_draggerZ->setMatrix(_draggerY->getMatrix());
				}

				if(pickedarrow == 3)
				{
					_objectmodel->setData(_objectmodel->GetIndex(1, 11), floor(_draggerZ->getMatrix().getTrans().z()*10)/10);
					_draggerX->setMatrix(_draggerZ->getMatrix());
					_draggerY->setMatrix(_draggerZ->getMatrix());
				}
				
				return;
			}

			if(category == "ActivationTrigger")
			{
				if(pickedarrow == 1)
				{
					_objectmodel->setData(_objectmodel->GetIndex(1, 5), floor(_draggerX->getMatrix().getTrans().x()*10)/10);
					_draggerY->setMatrix(_draggerX->getMatrix());
					_draggerZ->setMatrix(_draggerX->getMatrix());
				}

				if(pickedarrow == 2)
				{	
					_objectmodel->setData(_objectmodel->GetIndex(1, 6), floor(_draggerY->getMatrix().getTrans().y()*10)/10);
					_draggerX->setMatrix(_draggerY->getMatrix());
					_draggerZ->setMatrix(_draggerY->getMatrix());
				}

				if(pickedarrow == 3)
				{
					_objectmodel->setData(_objectmodel->GetIndex(1, 7), floor(_draggerZ->getMatrix().getTrans().z()*10)/10);
					_draggerX->setMatrix(_draggerZ->getMatrix());
					_draggerY->setMatrix(_draggerZ->getMatrix());
				}

				return;
			}

			if(category == "ZoneActionTrigger")
			{
				if(pickedarrow == 1)
				{
					_objectmodel->setData(_objectmodel->GetIndex(1, 5), floor(_draggerX->getMatrix().getTrans().x()*10)/10);
					_draggerY->setMatrix(_draggerX->getMatrix());
					_draggerZ->setMatrix(_draggerX->getMatrix());
				}

				if(pickedarrow == 2)
				{	
					_objectmodel->setData(_objectmodel->GetIndex(1, 6), floor(_draggerY->getMatrix().getTrans().y()*10)/10);
					_draggerX->setMatrix(_draggerY->getMatrix());
					_draggerZ->setMatrix(_draggerY->getMatrix());
				}

				if(pickedarrow == 3)
				{
					_objectmodel->setData(_objectmodel->GetIndex(1, 7), floor(_draggerZ->getMatrix().getTrans().z()*10)/10);
					_draggerX->setMatrix(_draggerZ->getMatrix());
					_draggerY->setMatrix(_draggerZ->getMatrix());
				}

				return;
			}
			return;
		}

		if(type == "Actor")
		{
			osg::Vec3 center = _actornode->computeBound().center();

			if(pickedarrow == 1)
			{
				float nX = _objectmodel->data(_objectmodel->GetIndex(1, 8)).toString().toFloat();
				nX += floor(_draggerX->getMatrix().getTrans().x()*10)/10 - center.x();
				_objectmodel->setData(_objectmodel->GetIndex(1, 8), nX);
				_draggerY->setMatrix(_draggerX->getMatrix());
				_draggerZ->setMatrix(_draggerX->getMatrix());
			}

			if(pickedarrow == 2)
			{	
				float nY = _objectmodel->data(_objectmodel->GetIndex(1, 9)).toString().toFloat();
				nY += floor(_draggerY->getMatrix().getTrans().y()*10)/10 - center.y();
				_objectmodel->setData(_objectmodel->GetIndex(1, 9), nY);
				_draggerX->setMatrix(_draggerY->getMatrix());
				_draggerZ->setMatrix(_draggerY->getMatrix());
			}

			if(pickedarrow == 3)
			{
				float nZ = _objectmodel->data(_objectmodel->GetIndex(1, 10)).toString().toFloat();
				nZ += floor(_draggerZ->getMatrix().getTrans().z()*10)/10 - center.z();
				_objectmodel->setData(_objectmodel->GetIndex(1, 10), nZ);
				_draggerX->setMatrix(_draggerZ->getMatrix());
				_draggerY->setMatrix(_draggerZ->getMatrix());
			}

			return;
		}
	}
}


/***********************************************************
when an editor arrow was dragged by mouse
***********************************************************/
void EditorHandler::RemoveArrows()
{
	if(_arrownode)
	{
		OsgHandler::getInstance()->RemoveActorNode(_arrownode, false);
		_arrownode = NULL;
		_draggerX = NULL;
		_draggerY = NULL;
		_draggerZ = NULL;
	}
}


/***********************************************************
SelectCScript
***********************************************************/
void EditorHandler::SelectCScript(ClientScriptBasePtr script, const QModelIndex &parent)
{

	if(parent == QModelIndex())
		ResetObject();


	// add pointer for later change
	_modelidxdatamap[parent] = (void*)script.get();

	if(!script)
		return;

	{
		QVector<QVariant> data;
		data<<"Type"<<"ClientScript";
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"SubCategory"<<script->GetTypeName().c_str();
		_objectmodel->AppendRow(data, parent, true);
	}

	std::string actiontype = script->GetTypeName();
	if(actiontype == "GoUpLadderScript")
	{
		GoUpLadderScript* ptr = static_cast<GoUpLadderScript*>(script.get());

		{
			QVector<QVariant> data;
			data << "Position X" << (double)ptr->GetLadderPositionX();
			_objectmodel->AppendRow(data, parent);
		}

		{
			QVector<QVariant> data;
			data << "Position Y" << (double)ptr->GetLadderPositionY();
			_objectmodel->AppendRow(data, parent);
		}

		{
			QVector<QVariant> data;
			data << "Position Z" << (double)ptr->GetLadderPositionZ();
			_objectmodel->AppendRow(data, parent);
		}

		{
			QVector<QVariant> data;
			data << "Ladder Height" << (double)ptr->GetLadderHeight();
			_objectmodel->AppendRow(data, parent);
		}

		{
			QVector<QVariant> data;
			data << "Ladder Direction" << ptr->GetLadderDirection();
			_objectmodel->AppendRow(data, parent);
		}

		UpdateSelectedGoUpLadderScriptDisplay(ptr->GetLadderPositionX(), ptr->GetLadderPositionY(), ptr->GetLadderPositionZ(),
												ptr->GetLadderHeight(), ptr->GetLadderDirection());


		return;
	}

	if(actiontype == "TakeExitUpScript")
	{
		TakeExitUpScript* ptr = static_cast<TakeExitUpScript*>(script.get());

		{
			QVector<QVariant> data;
			data << "Position X" << (double)ptr->GetExitPositionX();
			_objectmodel->AppendRow(data, parent);
		}

		{
			QVector<QVariant> data;
			data << "Position Y" << (double)ptr->GetExitPositionY();
			_objectmodel->AppendRow(data, parent);
		}

		{
			QVector<QVariant> data;
			data << "Position Z" << (double)ptr->GetExitPositionZ();
			_objectmodel->AppendRow(data, parent);
		}

		{
			QVector<QVariant> data;
			data << "Exit Direction" << ptr->GetExitDirection();
			_objectmodel->AppendRow(data, parent);
		}

		UpdateSelectedGoUpLadderScriptDisplay(ptr->GetExitPositionX(), ptr->GetExitPositionY(), ptr->GetExitPositionZ(),
													0, ptr->GetExitDirection());


		return;
	}

	if(actiontype == "TakeExitDownScript")
	{
		TakeExitDownScript* ptr = static_cast<TakeExitDownScript*>(script.get());

		{
			QVector<QVariant> data;
			data << "Position X" << (double)ptr->GetExitPositionX();
			_objectmodel->AppendRow(data, parent);
		}

		{
			QVector<QVariant> data;
			data << "Position Y" << (double)ptr->GetExitPositionY();
			_objectmodel->AppendRow(data, parent);
		}

		{
			QVector<QVariant> data;
			data << "Position Z" << (double)ptr->GetExitPositionZ();
			_objectmodel->AppendRow(data, parent);
		}

		{
			QVector<QVariant> data;
			data << "Exit Direction" << ptr->GetExitDirection();
			_objectmodel->AppendRow(data, parent);
		}

		UpdateSelectedGoUpLadderScriptDisplay(ptr->GetExitPositionX(), ptr->GetExitPositionY(), ptr->GetExitPositionZ(),
			0, ptr->GetExitDirection());


		return;
	}

	if(actiontype == "CustomScript")
	{
		CustomScript* ptr = static_cast<CustomScript*>(script.get());

		{
			QVector<QVariant> data;
			data << "Lua function name" << ptr->GetLuaFunctionName().c_str();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);

			
			// add tooltip
			_objectmodel->setTooltip(idx, "the function should be defined in custom client lua file");
			QModelIndex idx2 = _objectmodel->GetIndex(1, idx.row(), idx.parent());
			_objectmodel->setTooltip(idx2, "the function should be defined in custom client lua file");
		}
		return;
	}

}


/***********************************************************
UpdateSelectedGoUpLadderScriptDisplay
***********************************************************/
void EditorHandler::UpdateSelectedGoUpLadderScriptDisplay( float posX, float posY, float posZ, 
															float Height, int Direction )
{
	RemoveSelectedScriptDislay();

	_scriptnode = OsgHandler::getInstance()->AddEmptyActorNode(false);

	osg::Matrixd Trans;
	osg::Matrixd Rotation;
	Trans.makeTranslate(posX, posY, posZ);
	LbaQuaternion Q(Direction+180, LbaVec3(0,1,0));
	Rotation.makeRotate(osg::Quat(Q.X, Q.Y, Q.Z, Q.W));
	_scriptnode->setMatrix(Rotation * Trans);

	osg::Geode* lineGeode = new osg::Geode();
	osg::Geometry* lineGeometry = new osg::Geometry();
	lineGeode->addDrawable(lineGeometry); 

	osg::Vec3Array* lineVertices = new osg::Vec3Array();
	lineVertices->push_back( osg::Vec3( -1, 0, 0) );
	lineVertices->push_back( osg::Vec3(1, 0, 0) );
	lineVertices->push_back( osg::Vec3(0 , 0, -1) );
	lineVertices->push_back( osg::Vec3(0 , 0, 1) );
	lineVertices->push_back( osg::Vec3(0 , 0, 0) );
	lineVertices->push_back( osg::Vec3(0 , Height, 0) );
	lineVertices->push_back( osg::Vec3( -1, Height, 0) );
	lineVertices->push_back( osg::Vec3(1, Height, 0) );
	lineVertices->push_back( osg::Vec3(0 , Height, -1) );
	lineVertices->push_back( osg::Vec3(0 , Height, 1) );

	lineVertices->push_back( osg::Vec3(0 , Height/2, 0) );
	lineVertices->push_back( osg::Vec3(0 , Height/2, 2) );

	lineGeometry->setVertexArray( lineVertices ); 

	osg::Vec4Array* linecolor = new osg::Vec4Array();
	linecolor->push_back( osg::Vec4( 1.0, 1.0, 0.2, 0.8) );
	lineGeometry->setColorArray(linecolor);
	lineGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	osg::DrawElementsUInt* dunit = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
	for(int i=0; i<12; ++i)
		dunit->push_back(i);

	lineGeometry->addPrimitiveSet(dunit); 
	_scriptnode->addChild(lineGeode);

	osg::StateSet* stateset = lineGeometry->getOrCreateStateSet();
	osg::LineWidth* linewidth = new osg::LineWidth();

	linewidth->setWidth(3.0f);
	stateset->setAttributeAndModes(linewidth,osg::StateAttribute::ON);
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	stateset->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
	stateset->setRenderBinDetails( 8000, "RenderBin");

}

/***********************************************************
CScriptObjectChanged
***********************************************************/
void EditorHandler::CScriptObjectChanged( const std::string & category, const QModelIndex &parentIdx )
{
	std::map<QModelIndex, void *>::iterator it = _modelidxdatamap.find(parentIdx);
	if(it != _modelidxdatamap.end())
	{
		void * ptr = it->second;
		if(ptr)
		{	
			if(category == "GoUpLadderScript")
			{
				float posX = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toFloat();
				float posY = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toFloat();
				float posZ = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toFloat();
				float height = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toFloat();
				int direction = _objectmodel->data(_objectmodel->GetIndex(1, 6, parentIdx)).toInt();


				// created modified script and replace old one
				GoUpLadderScript* modifiedscript = (GoUpLadderScript*)ptr;
				modifiedscript->SetLadderPositionX(posX);
				modifiedscript->SetLadderPositionY(posY);
				modifiedscript->SetLadderPositionZ(posZ);
				modifiedscript->SetLadderHeight(height);
				modifiedscript->SetLadderDirection(direction);

				// need to save as something changed
				SetModified();


				// update display
				UpdateSelectedGoUpLadderScriptDisplay(posX, posY, posZ, height, direction);

				return;
			}



			if(category == "TakeExitUpScript")
			{
				float posX = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toFloat();
				float posY = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toFloat();
				float posZ = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toFloat();
				int direction = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toInt();


				// created modified script and replace old one
				TakeExitUpScript* modifiedscript = (TakeExitUpScript*)ptr;
				modifiedscript->SetExitPositionX(posX);
				modifiedscript->SetExitPositionY(posY);
				modifiedscript->SetExitPositionZ(posZ);
				modifiedscript->SetExitDirection(direction);



				// need to save as something changed
				SetModified();


				// update display
				UpdateSelectedGoUpLadderScriptDisplay(posX, posY, posZ, 0, direction);

				return;
			}



			if(category == "TakeExitDownScript")
			{
				float posX = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toFloat();
				float posY = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toFloat();
				float posZ = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toFloat();
				int direction = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toInt();


				// created modified script and replace old one
				TakeExitDownScript* modifiedscript = (TakeExitDownScript*)ptr;
				modifiedscript->SetExitPositionX(posX);
				modifiedscript->SetExitPositionY(posY);
				modifiedscript->SetExitPositionZ(posZ);
				modifiedscript->SetExitDirection(direction);


				// need to save as something changed
				SetModified();


				// update display
				UpdateSelectedGoUpLadderScriptDisplay(posX, posY, posZ, 0, direction);

				return;
			}


			if(category == "CustomScript")
			{
				std::string fctname = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();


				// created modified script and replace old one
				CustomScript* modifiedscript = (CustomScript*)ptr;
				modifiedscript->SetLuaFunctionName(fctname);


				// need to save as something changed
				SetModified();

				return;
			}		
		}
	}
}


/***********************************************************
remove current selected display
***********************************************************/
void EditorHandler::RemoveSelectedScriptDislay()
{
	if(_scriptnode)
		OsgHandler::getInstance()->RemoveActorNode(_scriptnode, false);

	_scriptnode = NULL;
}




/***********************************************************
select a condition
***********************************************************/
void EditorHandler::SelectCondition(ConditionBasePtr cond, const QModelIndex &parent)
{
	if(parent == QModelIndex())
		ResetObject();

	if(!cond)
		return;

	// add pointer for later change
	_modelidxdatamap[parent] = (void*)cond.get();

	{
		QVector<QVariant> data;
		data<<"Type"<<"Condition";
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"SubCategory"<<cond->GetTypeName().c_str();
		_objectmodel->AppendRow(data, parent, true);
	}

	std::string type = cond->GetTypeName();
	if(type == "NegateCondition")
	{
		NegateCondition* ptr = static_cast<NegateCondition*>(cond.get());

		ConditionBasePtr condptr = ptr->GetCondition();

		QVector<QVariant> data;
		data << "Condition to negate" << GetConditionType(condptr).c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		if(condptr)
			SelectCondition(condptr, idx);

		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 2, parent), _conditiontypeList);

		return;
	}

	if(type == "AndCondition")
	{
		AndCondition* ptr = static_cast<AndCondition*>(cond.get());

		{
		ConditionBasePtr condptr = ptr->GetCondition1();

		QVector<QVariant> data;
		data << "Condition 1" << GetConditionType(condptr).c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		if(condptr)
			SelectCondition(condptr, idx);
		}

		{
		ConditionBasePtr condptr = ptr->GetCondition2();
		QVector<QVariant> data2;
		data2 << "Condition 2" << GetConditionType(condptr).c_str();
		QModelIndex idx = _objectmodel->AppendRow(data2, parent);

		if(condptr)
			SelectCondition(condptr, idx);
		}


		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 2, parent), _conditiontypeList);
		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 3, parent), _conditiontypeList);

		return;
	}


	if(type == "OrCondition")
	{
		OrCondition* ptr = static_cast<OrCondition*>(cond.get());
		{
		ConditionBasePtr condptr = ptr->GetCondition1();

		QVector<QVariant> data;
		data << "Condition 1" << GetConditionType(condptr).c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		if(condptr)
			SelectCondition(condptr, idx);
		}

		{
		ConditionBasePtr condptr = ptr->GetCondition2();
		QVector<QVariant> data2;
		data2 << "Condition 2" << GetConditionType(condptr).c_str();
		QModelIndex idx = _objectmodel->AppendRow(data2, parent);

		if(condptr)
			SelectCondition(condptr, idx);
		}

		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 2, parent), _conditiontypeList);
		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, 3, parent), _conditiontypeList);

		return;
	}

}

/***********************************************************
create a new condition
***********************************************************/
ConditionBasePtr EditorHandler::CreateCondition(const std::string & type)
{
	if(type == "AlwaysTrueCondition")
		return ConditionBasePtr(new AlwaysTrueCondition());

	if(type == "NegateCondition")
		return ConditionBasePtr(new NegateCondition());

	if(type == "AndCondition")
		return ConditionBasePtr(new AndCondition());

	if(type == "OrCondition")
		return ConditionBasePtr(new OrCondition());

	return ConditionBasePtr();
}

/***********************************************************
get type of condition
***********************************************************/
std::string EditorHandler::GetConditionType(ConditionBasePtr ptr)
{
	std::string res = "No";
	if(ptr)
		res = ptr->GetTypeName();

	return res;
}

/***********************************************************
called when Condition changed
***********************************************************/
void EditorHandler::ConditionChanged(const std::string & category, const QModelIndex &parentIdx)
{
	std::map<QModelIndex, void *>::iterator it = _modelidxdatamap.find(parentIdx);
	if(it != _modelidxdatamap.end())
	{
		void * ptr = it->second;
		if(ptr)
		{	
			if(category == "NegateCondition")
			{
				NegateCondition* cond = (NegateCondition*)ptr;

				std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();
				std::string currcond = GetConditionType(cond->GetCondition());

				if(condition != currcond)
				{
					ConditionBasePtr ptrtmp = CreateCondition(condition);
					cond->SetCondition(ptrtmp);

					QModelIndex curidx = _objectmodel->GetIndex(0, 2, parentIdx);
					_objectmodel->Clear(curidx);
					if(ptrtmp)
					{
						SelectCondition(ptrtmp, curidx);

						_uieditor.treeView_object->setExpanded(curidx, true); // expand 
					}

					// need to save as something changed
					SetModified();
				}
			}

			if(category == "AndCondition")
			{
				AndCondition* cond = (AndCondition*)ptr;

				//condition 1
				{
					std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();
					std::string currcond = GetConditionType(cond->GetCondition1());

					if(condition != currcond)
					{
						ConditionBasePtr ptrtmp = CreateCondition(condition);
						cond->SetCondition1(ptrtmp);

						QModelIndex curidx = _objectmodel->GetIndex(0, 2, parentIdx);
						_objectmodel->Clear(curidx);
						if(ptrtmp)
						{
							SelectCondition(ptrtmp, curidx);

							_uieditor.treeView_object->setExpanded(curidx, true); // expand 
						}


						// need to save as something changed
						SetModified();
					}
				}

				//condition 2
				{
					std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toString().toAscii().data();
					std::string currcond = GetConditionType(cond->GetCondition2());

					if(condition != currcond)
					{
						ConditionBasePtr ptrtmp = CreateCondition(condition);
						cond->SetCondition2(ptrtmp);

						QModelIndex curidx = _objectmodel->GetIndex(0, 3, parentIdx);
						_objectmodel->Clear(curidx);
						if(ptrtmp)
						{
							SelectCondition(ptrtmp, curidx);

							_uieditor.treeView_object->setExpanded(curidx, true); // expand 
						}

						// need to save as something changed
						SetModified();
					}
				}
			}

			if(category == "OrCondition")	
			{
				OrCondition* cond = (OrCondition*)ptr;

				//condition 1
				{
					std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();
					std::string currcond = GetConditionType(cond->GetCondition1());

					if(condition != currcond)
					{
						ConditionBasePtr ptrtmp = CreateCondition(condition);
						cond->SetCondition1(ptrtmp);

						QModelIndex curidx = _objectmodel->GetIndex(0, 2, parentIdx);
						_objectmodel->Clear(curidx);
						if(ptrtmp)
						{
							SelectCondition(ptrtmp, curidx);

							_uieditor.treeView_object->setExpanded(curidx, true); // expand 
						}

						// need to save as something changed
						SetModified();
					}
				}

				//condition 2
				{
					std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toString().toAscii().data();
					std::string currcond = GetConditionType(cond->GetCondition2());

					if(condition != currcond)
					{
						ConditionBasePtr ptrtmp = CreateCondition(condition);
						cond->SetCondition2(ptrtmp);


						QModelIndex curidx = _objectmodel->GetIndex(0, 3, parentIdx);
						_objectmodel->Clear();
						if(ptrtmp)
						{
							SelectCondition(ptrtmp, curidx);

							_uieditor.treeView_object->setExpanded(curidx, true); // expand 
						}

						// need to save as something changed
						SetModified();
					}
				}
			}
		}
	}
}



/***********************************************************
create a new condition
***********************************************************/
ClientScriptBasePtr EditorHandler::CreateCscript(const std::string & type)
{
	if(type == "GoUpLadderScript")
	{
		GoUpLadderScript * sc = new GoUpLadderScript();
		sc->SetLadderPositionX(_posX);
		sc->SetLadderPositionY(_posY);
		sc->SetLadderPositionZ(_posZ);
		return ClientScriptBasePtr(sc);
	}

	if(type == "TakeExitUpScript")
	{
		TakeExitUpScript * sc = new TakeExitUpScript();
		sc->SetExitPositionX(_posX);
		sc->SetExitPositionY(_posY);
		sc->SetExitPositionZ(_posZ);
		return ClientScriptBasePtr(sc);
	}


	if(type == "TakeExitDownScript")
	{
		TakeExitDownScript * sc = new TakeExitDownScript();
		sc->SetExitPositionX(_posX);
		sc->SetExitPositionY(_posY);
		sc->SetExitPositionZ(_posZ);
		return ClientScriptBasePtr(sc);
	}

	if(type == "CustomScript")
		return ClientScriptBasePtr(new CustomScript());

	return ClientScriptBasePtr();
}

/***********************************************************
get type of condition
***********************************************************/
std::string EditorHandler::GetCScriptType(ClientScriptBasePtr ptr)
{
	std::string res = "No";
	if(ptr)
		res = ptr->GetTypeName();

	return res;
}




/***********************************************************
create a new action
***********************************************************/
ActionBasePtr EditorHandler::CreateAction(const std::string & type)
{
	if(type == "TeleportAction")
		return ActionBasePtr(new TeleportAction());

	if(type == "ClientScriptAction")
		return ActionBasePtr(new ClientScriptAction());

	if(type == "CustomAction")
		return ActionBasePtr(new CustomAction());

	if(type == "DisplayTextAction")
		return ActionBasePtr(new DisplayTextAction());

	if(type == "ConditionalAction")
		return ActionBasePtr(new ConditionalAction());

	return ActionBasePtr();
}


/***********************************************************
get type of action
***********************************************************/
std::string EditorHandler::GetActionType(ActionBasePtr ptr)
{
	std::string res = "No";
	if(ptr)
		res = ptr->GetTypeName();

	return res;
}



/***********************************************************
text type modified
***********************************************************/
void EditorHandler::TextTypeModified(int index)
{
	switch(index)
	{
		case 0:
			_currentchoosentext = Localizer::Map;
			_uieditor.tableView_TextList->setModel(_text_maplistmodel);
		break;
		case 1:
			_currentchoosentext = Localizer::Quest;
			_uieditor.tableView_TextList->setModel(_text_questlistmodel);
		break;
		case 2:
			_currentchoosentext = Localizer::Inventory;
			_uieditor.tableView_TextList->setModel(_text_inventorylistmodel);
		break;
		case 3:
			_currentchoosentext = Localizer::Name;
			_uieditor.tableView_TextList->setModel(_text_namelistmodel);
		break;
	}
}


/***********************************************************
TextAdd_button
***********************************************************/
void EditorHandler::TextAdd_button()
{
	_ui_addtextdialog.lineEdit_id->setText("");
	_ui_addtextdialog.textEdit->setPlainText("");
	_addtextdialog->show();
}


/***********************************************************
TextRemove_button
***********************************************************/
void EditorHandler::TextRemove_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_TextList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	StringTableModel *	model = NULL;
	boost::shared_ptr<CustomStringListModel> modelname;
	switch(_currentchoosentext)
	{
		case Localizer::Map:
			model = _text_maplistmodel;
			modelname = _text_mapNameList;
		break;
		case Localizer::Quest:
			model = _text_questlistmodel;
			modelname = _text_questNameList;
		break;
		case Localizer::Inventory:
			model = _text_inventorylistmodel;
			modelname = _text_inventoryNameList;
		break;
		case Localizer::Name:
			model = _text_namelistmodel;
			modelname = _text_nameNameList;
		break;
	}	


	if(model && indexes.size() > 0)
	{
		long id = model->GetId(indexes[0]);
		std::string txt = Localizer::getInstance()->GetText(_currentchoosentext, id);

		Localizer::getInstance()->RemoveFromMap(_currentchoosentext, id);

		model->removeRows(indexes[0].row(), 1);

		std::stringstream txtwithid;
		txtwithid<<id<<": "<<txt;
		modelname->RemoveData(txtwithid.str().c_str());

		SetModified();
	}
}	


/***********************************************************
TextEdit_button
***********************************************************/
void EditorHandler::TextEdit_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_TextList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	StringTableModel *	model = NULL;
	switch(_currentchoosentext)
	{
		case Localizer::Map:
			model = _text_maplistmodel;
		break;
		case Localizer::Quest:
			model = _text_questlistmodel;
		break;
		case Localizer::Inventory:
			model = _text_inventorylistmodel;
		break;
		case Localizer::Name:
			model = _text_namelistmodel;
		break;
	}	


	if(model && indexes.size() > 0)
	{
		long id = model->GetId(indexes[0]);

		std::string txt = Localizer::getInstance()->GetText(_currentchoosentext, id);
		replaceinstr(txt, " @ ", "\n");


		std::stringstream idtxt;
		idtxt << id;
		_ui_addtextdialog.lineEdit_id->setText(idtxt.str().c_str());
		_ui_addtextdialog.textEdit->setPlainText(QString::fromUtf8(txt.c_str()));
		_addtextdialog->show();
	}
}	



/***********************************************************
TextAdd_button_accepted
***********************************************************/
void EditorHandler::TextAdd_button_accepted()
{
	_addtextdialog->hide();

	std::string txt = _ui_addtextdialog.textEdit->toPlainText().toUtf8().data();
	replaceinstr(txt, "\n", " @ ");

	StringTableModel *	model = NULL;
	boost::shared_ptr<CustomStringListModel> modelname;
	switch(_currentchoosentext)
	{
		case Localizer::Map:
			model = _text_maplistmodel;
			modelname = _text_mapNameList;
		break;
		case Localizer::Quest:
			model = _text_questlistmodel;
			modelname = _text_questNameList;
		break;
		case Localizer::Inventory:
			model = _text_inventorylistmodel;
			modelname = _text_inventoryNameList;
		break;
		case Localizer::Name:
			model = _text_namelistmodel;
			modelname = _text_nameNameList;
		break;
	}	

	if(_ui_addtextdialog.lineEdit_id->text() != "")
	{
		// replace text
		long id = _ui_addtextdialog.lineEdit_id->text().toLong();
		std::string oldtxt = Localizer::getInstance()->GetText(_currentchoosentext, id);

		Localizer::getInstance()->AddToMap(_currentchoosentext, id, txt);	
		QStringList qlist;
		qlist << QString::fromUtf8(txt.c_str());
		model->AddOrUpdateRow(id, qlist);


		std::stringstream oldtxtwithid;
		oldtxtwithid<<id<<": "<<oldtxt;
		std::stringstream txtwithid;
		txtwithid<<id<<": "<<txt;
		modelname->ReplaceData(QString::fromUtf8(oldtxtwithid.str().c_str()), 
									QString::fromUtf8(txtwithid.str().c_str()));

	}
	else
	{
		// new text
		long newid = Localizer::getInstance()->AddToMap(_currentchoosentext, -1, txt);	
		QStringList qlist;
		qlist << QString::fromUtf8(txt.c_str());
		model->AddOrUpdateRow(newid, qlist);

		std::stringstream txtwithid;
		txtwithid<<newid<<": "<<txt;
		modelname->AddData(QString::fromUtf8(txtwithid.str().c_str()));
	}

	SetModified();
}

/***********************************************************
OpenCustomServerLua
***********************************************************/
void EditorHandler::OpenCustomServerLua()
{
	std::string path = QDir::currentPath().toAscii().data();
	path += "/Data/Worlds/" + _winfo.Description.WorldName + "/Lua/CustomServer.lua";

#ifdef WIN32
	ShellExecuteA(NULL, "open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
	//todo - linux version
#endif

}

/***********************************************************
OpenCustomClientLua
***********************************************************/
void EditorHandler::OpenCustomClientLua()
{
	std::string path = QDir::currentPath().toAscii().data();
	path += "/Data/Worlds/" + _winfo.Description.WorldName + "/Lua/CustomClient.lua";

#ifdef WIN32
	ShellExecuteA(NULL, "open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
	//todo - linux version
#endif
}


/***********************************************************
RefreshClientScript
***********************************************************/
void EditorHandler::RefreshClientScript()
{
	EventsQueue::getReceiverQueue()->AddEvent(new RefreshLuaEvent());
}



/***********************************************************
selecttext_double_clicked
***********************************************************/
void EditorHandler::selecttext_double_clicked(const QModelIndex & itm)
{
	TextEdit_button();
}


/***********************************************************
on selectitem_double_clicked
***********************************************************/
void EditorHandler::selectitem_double_clicked(const QModelIndex & itm)
{
	ItemSelect_button();
}


/***********************************************************
ItemAdd_button_accepted
***********************************************************/
void EditorHandler::ItemAdd_button_accepted()
{
	_additemdialog->hide();

	LbaNet::ItemInfo newitem;
	newitem.DescriptionId = 0;
    newitem.Max = 1;
    newitem.Price = 1;
    newitem.Effect = 0;
    newitem.Flag = 0;
    newitem.Ephemere = false;

	newitem.Name = _ui_additemdialog.lineEdit_name->text().toAscii().data();
	switch(_ui_additemdialog.comboBox_atype->currentIndex())
	{
		case 0:
			newitem.Type = 1;
		break;
		case 1:
			newitem.Type = 2;
		break;
		case 2:
			newitem.Type = 3;
		break;
		case 3:
			newitem.Type = 4;
		break;
		case 4:
			newitem.Type = 9;
		break;
		case 5:
			newitem.Type = 5;
		break;
		case 6:
			newitem.Type = 7;
		break;
		case 7:
			newitem.Type = 8;
		break;
		case 8:
			newitem.Type = 6;
		break;
	}

	long idx = InventoryItemHandler::getInstance()->AddOrModItem(-1, newitem);

	QStringList data;
	data << newitem.Name.c_str();
	data << InventoryItemHandler::getInstance()->GetItemTypeString(idx).c_str();
	_itemlistmodel->AddOrUpdateRow(idx, data);

	std::stringstream txtwithid;
	txtwithid<<idx<<": "<<newitem.Name.c_str();
	_itemNameList->AddData(txtwithid.str().c_str());

	SetModified();
	SelectItem(InventoryItemHandler::getInstance()->GetItemInfo(idx));
}

/***********************************************************
ItemAdd_button
***********************************************************/
void EditorHandler::ItemAdd_button()
{
	_ui_additemdialog.lineEdit_name->setText("");
	_additemdialog->show();
}

/***********************************************************
ItemRemove_button
***********************************************************/
void EditorHandler::ItemRemove_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_ItemList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	if(indexes.size() > 0)
	{
		long id = _itemlistmodel->GetId(indexes[0]);
		LbaNet::ItemInfo item = InventoryItemHandler::getInstance()->GetItemInfo(id);

		InventoryItemHandler::getInstance()->RemoveItem(id);

		_itemlistmodel->removeRows(indexes[0].row(), 1);

		std::stringstream txtwithid;
		txtwithid<<id<<": "<<item.Name.c_str();
		_itemNameList->RemoveData(txtwithid.str().c_str());

		SetModified();
	}
}


/***********************************************************
ItemSelect_button
***********************************************************/
void EditorHandler::ItemSelect_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_ItemList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	if(indexes.size() > 0)
	{
		long id = _itemlistmodel->GetId(indexes[0]);
		LbaNet::ItemInfo item = InventoryItemHandler::getInstance()->GetItemInfo(id);
		SelectItem(item);
	}
}


/***********************************************************
set item in the object
***********************************************************/
void EditorHandler::SelectItem(const LbaNet::ItemInfo & item, const QModelIndex &parent)
{
	if(parent == QModelIndex())
		ResetObject();

	{
		QVector<QVariant> data;
		data<<"Type"<<"Item";
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"SubCategory"<<InventoryItemHandler::getInstance()->GetItemTypeString(item.Id).c_str();
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"Id"<<item.Id;
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"Name"<<item.Name.c_str();
		_objectmodel->AppendRow(data, parent);
	}

	int index = 4;

	{
		std::stringstream descstrs;
		descstrs<<item.DescriptionId<<": "<<Localizer::getInstance()->GetText(Localizer::Inventory, item.DescriptionId);
		
		QVector<QVariant> data;
		data<<"Description"<<descstrs.str().c_str();
		_objectmodel->AppendRow(data, parent);

		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _text_inventoryNameList);
		++index;
	}

	{
		QVector<QVariant> data;
		data<<"Icon"<<item.IconName.c_str();
		_objectmodel->AppendRow(data, parent);

		FileDialogOptionsIcon * filterptr = new FileDialogOptionsIcon();
		filterptr->OutDirectory = ("Data/Worlds/" + _winfo.Description.WorldName + "/InventoryImages").c_str();
		boost::shared_ptr<FileDialogOptionsBase> filefilter(filterptr);
		filefilter->Title = "Select an image";
		filefilter->StartingDirectory = "Data/GUI/imagesets/Inventory";
		filefilter->FileFilter = "Images Files (*.png *.bmp *.jpg *.gif)";
		_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), filefilter);


		//todo put file chooser
		++index;
	}

	{
		QVector<QVariant> data;
		data<<"Maximum number"<<item.Max;
		_objectmodel->AppendRow(data, parent);
		++index;
	}

	{
		QVector<QVariant> data;
		data<<"Default price"<<item.Price;
		_objectmodel->AppendRow(data, parent);
		++index;
	}

	{
		QVector<QVariant> data;
		data<<"Ephemere"<<item.Ephemere;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		_objectmodel->setTooltip(idx, "If true the item will disappear when leaving the map");
		QModelIndex idx2 = _objectmodel->GetIndex(1, idx.row(), idx.parent());
		_objectmodel->setTooltip(idx2, "If true the item will disappear when leaving the map");
		++index;
	}

	switch(item.Type)
	{
		case 1: // consummable item
		{
			switch(item.Flag)
			{
				case 1: // life potion
				{
					QVector<QVariant> data;
					data<<"Type"<<"Restore % of Health";
					_objectmodel->AppendRow(data, parent);

					_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _consumable_itemlistmodel);
					++index;

					QVector<QVariant> data2;
					data2<<"Restoration in %"<<item.Effect;
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;
				case 2: // mana potion
				{
					QVector<QVariant> data;
					data<<"Type"<<"Restore % of Magic";
					_objectmodel->AppendRow(data, parent);

					_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _consumable_itemlistmodel);
					++index;

					QVector<QVariant> data2;
					data2<<"Restoration in %"<<item.Effect;
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;
				case 3: // life and mana potion
				{
					QVector<QVariant> data;
					data<<"Type"<<"Restore % of Health&Magic";
					_objectmodel->AppendRow(data, parent);

					_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _consumable_itemlistmodel);
					++index;

					QVector<QVariant> data2;
					data2<<"Restoration in %"<<item.Effect;
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;

				case 4: // life potion
				{
					QVector<QVariant> data;
					data<<"Type"<<"Restore Health";
					_objectmodel->AppendRow(data, parent);

					_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _consumable_itemlistmodel);
					++index;

					QVector<QVariant> data2;
					data2<<"Restoration value"<<item.Effect;
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;
				case 5: // mana potion
				{
					QVector<QVariant> data;
					data<<"Type"<<"Restore Magic";
					_objectmodel->AppendRow(data, parent);

					_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _consumable_itemlistmodel);
					++index;

					QVector<QVariant> data2;
					data2<<"Restoration value"<<item.Effect;
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;
				case 6: // life and mana potion
				{
					QVector<QVariant> data;
					data<<"Type"<<"Restore Health&Magic";
					_objectmodel->AppendRow(data, parent);

					_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _consumable_itemlistmodel);
					++index;

					QVector<QVariant> data2;
					data2<<"Restoration value"<<item.Effect;
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;
			}
		}
		break;

		case 3: // monture item - ride it
		{
			switch(item.Flag)
			{
				case 1:
				{
					QVector<QVariant> data;
					data<<"Type"<<"Protopack";
					_objectmodel->AppendRow(data, parent);

					_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _mount_itemlistmodel);
					++index;
				}
				break;
				case 2:
				{
					QVector<QVariant> data;
					data<<"Type"<<"Horse";
					_objectmodel->AppendRow(data, parent);

					_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _mount_itemlistmodel);
					++index;
				}
				break;
				case 3:
				{
					QVector<QVariant> data;
					data<<"Type"<<"Dinofly";
					_objectmodel->AppendRow(data, parent);

					_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _mount_itemlistmodel);
					++index;
				}
				break;
			}
		}
		break;

		case 4: // weapon item - equip it
		{
			QVector<QVariant> data;
			data<<"Power"<<item.Effect;
			_objectmodel->AppendRow(data, parent);
			++index;

			QVector<QVariant> data2;
			data2<<"Player model"<<item.StringFlag.c_str();
			QModelIndex idx = _objectmodel->AppendRow(data2, parent);

			_objectmodel->setTooltip(idx, "Name of the model used to display the player wearing the weapon (see documentation)");
			QModelIndex idx2 = _objectmodel->GetIndex(1, idx.row(), idx.parent());
			_objectmodel->setTooltip(idx2, "Name of the model used to display the player wearing the weapon (see documentation)");
			++index;
		}
		break;

		case 7: // special usage item
		{
			switch(item.Flag)
			{
				case 1: // letter writter
				{
					QVector<QVariant> data;
					data<<"Type"<<"Letter writer";
					_objectmodel->AppendRow(data, parent);

					_objectcustomdelegate->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _special_itemlistmodel);
					++index;
				}
				break;
			}
		}
		break;

		case 9: // outfit item - equip it
		{
			QVector<QVariant> data;
			data<<"Armor"<<item.Effect;
			_objectmodel->AppendRow(data, parent);
			++index;

			QVector<QVariant> data2;
			data2<<"Player model"<<item.StringFlag.c_str();
			QModelIndex idx = _objectmodel->AppendRow(data2, parent);

			_objectmodel->setTooltip(idx, "Name of the model used to display the player wearing the outfit (see documentation)");
			QModelIndex idx2 = _objectmodel->GetIndex(1, idx.row(), idx.parent());
			_objectmodel->setTooltip(idx2, "Name of the model used to display the player wearing the outfit (see documentation)");
			++index;
		}
		break;
	}


}


/***********************************************************
item object changed
***********************************************************/
void EditorHandler::ItemChanged(long id, const std::string & category, const QModelIndex &parentIdx)
{
	LbaNet::ItemInfo olditeminfo = InventoryItemHandler::getInstance()->GetItemInfo(id);
	
	LbaNet::ItemInfo newiteminfo = olditeminfo;
	newiteminfo.Name = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toString().toAscii().data();

	// check if name changed
	if(newiteminfo.Name != olditeminfo.Name)
	{
		std::stringstream oldtxtwithid;
		oldtxtwithid<<id<<": "<<olditeminfo.Name.c_str();	

		std::stringstream txtwithid;
		txtwithid<<id<<": "<<newiteminfo.Name.c_str();	

		// update trigger name list
		_itemNameList->ReplaceData(oldtxtwithid.str().c_str(), txtwithid.str().c_str());

		// update trigger list display
		QStringList slist;
		slist << newiteminfo.Name.c_str() << InventoryItemHandler::getInstance()->GetItemTypeString(id).c_str();
		_itemlistmodel->AddOrUpdateRow(id, slist);
	}



	int index = 4;

	std::string desc = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
	std::string tmp = desc.substr(0, desc.find(":"));
	newiteminfo.DescriptionId = atol(tmp.c_str());
	++index;

	newiteminfo.IconName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
	++index;

	newiteminfo.Max = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();
	++index;

	newiteminfo.Price = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();
	++index;

	newiteminfo.Ephemere = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
	++index;



	switch(newiteminfo.Type)
	{
		case 1: // consummable item
		{
			std::string flag = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
			if(flag == "Restore % of Health")
				newiteminfo.Flag = 1;
			if(flag == "Restore % of Magic")
				newiteminfo.Flag = 2;
			if(flag == "Restore % of Health&Magic")
				newiteminfo.Flag = 3;
			if(flag == "Restore Health")
				newiteminfo.Flag = 4;
			if(flag == "Restore Magic")
				newiteminfo.Flag = 5;
			if(flag == "Restore Health&Magic")
				newiteminfo.Flag = 6;
			++index;

			newiteminfo.Effect = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
		}
		break;

		case 3: // monture item - ride it
		{
			std::string flag = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
			if(flag == "Protopack")
				newiteminfo.Flag = 1;
			if(flag == "Horse")
				newiteminfo.Flag = 2;
			if(flag == "Dinofly")
				newiteminfo.Flag = 3;

			++index;
		}
		break;

		case 4: // weapon item - equip it
		{
			newiteminfo.Effect = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;

			newiteminfo.StringFlag = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
			++index;
		}
		break;

		case 7: // special usage item
		{
			std::string flag = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
			if(flag == "Letter writer")
				newiteminfo.Flag = 1;

			++index;
		}
		break;

		case 9: // outfit item - equip it
		{
			newiteminfo.Effect = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;

			newiteminfo.StringFlag = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
			++index;
		}
		break;
	}

	InventoryItemHandler::getInstance()->AddOrModItem(id, newiteminfo);
	SetModified();

	if(newiteminfo.Type == 1 && newiteminfo.Flag != olditeminfo.Flag)
		SelectItem(newiteminfo, parentIdx);
}





/***********************************************************
StartItemAdd_button
***********************************************************/
void EditorHandler::StartItemAdd_button()
{
	_ui_addstartitemdialog.spinBox_itemcount->setValue(1);
	_addstartitemdialog->show();
}


/***********************************************************
StartItemRemove_button
***********************************************************/
void EditorHandler::StartItemRemove_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_ItemList_starting->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	if(indexes.size() > 0)
	{
		long id = _startitemlistmodel->GetId(indexes[0]);

		LbaNet::ItemsMap::iterator itm = _winfo.StartingInfo.StartingInventory.find(id);
		if(itm != _winfo.StartingInfo.StartingInventory.end())
			_winfo.StartingInfo.StartingInventory.erase(itm);

		_startitemlistmodel->removeRows(indexes[0].row(), 1);

		SetModified();
	}
}


/***********************************************************
StartItemAdd_button_accepted
***********************************************************/
void EditorHandler::StartItemAdd_button_accepted()
{
	_addstartitemdialog->hide();

	int count = _ui_addstartitemdialog.spinBox_itemcount->value();

	std::string name = _ui_addstartitemdialog.comboBox_itemname->currentText().toAscii().data();
	std::string tmp = name.substr(0, name.find(":"));
	long itemid = atol(tmp.c_str());

	// check if item already exist in starting inventory if so then do nothing
	LbaNet::ItemsMap::iterator itm = _winfo.StartingInfo.StartingInventory.find(itemid);
	if(itm == _winfo.StartingInfo.StartingInventory.end())
	{
		LbaNet::ItemPosInfo newitem;
		newitem.Count = count;
		newitem.Position = -1;
		newitem.Info = InventoryItemHandler::getInstance()->GetItemInfo(itemid);

		_winfo.StartingInfo.StartingInventory[itemid] = newitem;

		QStringList data;
		data << newitem.Info.Name.c_str();
		std::stringstream tmpstrs;
		tmpstrs<<newitem.Count;
		data << tmpstrs.str().c_str();
		_startitemlistmodel->AddOrUpdateRow(itemid, data);

		SetModified();
	}
}