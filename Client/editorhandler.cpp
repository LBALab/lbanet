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
#include "DoorHandler.h"
#include "NpcHandler.h"
#include "Teleport.h"
#include "QuestHandler.h"
#include "Quest.h"
#include "Spawn.h"
#include "MusicHandler.h"
#include "ConfigurationManager.h"
#include "NaviMeshHandler.h"
#include "FileUtil.h"
#include "XmlReader.h"
#include "EditorSharedData.h"
#include "Holomap.h"
#include "HolomapHandler.h"

#include <qdir.h>
#include <QErrorMessage>
#include <QMessageBox>
#include <QFileDialog>
#include <QImage>
#include <QClipboard>
#include <QSignalMapper>

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
#include <osg/AutoTransform>
#include <osgText/Text>


#ifdef WIN32
#include "windows.h"
#endif


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
	TreeModel* Tmodel = static_cast<TreeModel*>(_model);
    boost::shared_ptr<CustomStringListModel> custom = Tmodel->CustomIndex(index);
    boost::shared_ptr<FileDialogOptionsBase> customf = Tmodel->CustomIndexFile(index);
    boost::shared_ptr<int> customi = Tmodel->CustomIndexNumber(index);


	if(custom)
	{
		QComboBox *editor = new QComboBox(parent);
		editor->setModel(custom.get());
		editor->setEditable(false);

		connect(editor, SIGNAL(	currentIndexChanged(int)) , this, SLOT(objmodified(int)));
		return editor;
	}

	if(customi)
	{
		QComboBox *editor = new QComboBox(parent);
		editor->addItem("Remove");
		for(int i=0; i< *customi; ++i)
		{
			std::stringstream strs;
			strs<<i;
			editor->addItem(strs.str().c_str());
		}
		editor->setEditable(false);

		connect(editor, SIGNAL(	currentIndexChanged(int)) , this, SLOT(objmodified(int)));
		return editor;
	}

	if(customf)
	{
		QFileDialog *editor = new QFileDialog(parent, customf->Title);
		editor->setAcceptMode(QFileDialog::AcceptOpen);
		editor->setFileMode(QFileDialog::ExistingFile);
		editor->setNameFilter(customf->FileFilter);
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
		editor->setDecimals(4);
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
	TreeModel* Tmodel = static_cast<TreeModel*>(_model);
    boost::shared_ptr<CustomStringListModel> custom = Tmodel->CustomIndex(index);
    boost::shared_ptr<FileDialogOptionsBase> customf = Tmodel->CustomIndexFile(index);
    boost::shared_ptr<int> customi = Tmodel->CustomIndexNumber(index);


	if(custom)
	{
		 QString value = index.model()->data(index, Qt::DisplayRole).toString();

		QComboBox *comboBox = static_cast<QComboBox*>(editor);
		 int index = comboBox->findText(value);
		 if(index >= 0)
			comboBox->setCurrentIndex(index);
		 else
		 {
			value = value.right(value.size()-2);
			index = comboBox->findText(value);
			 if(index >= 0)
				comboBox->setCurrentIndex(index);
			 else
			 {
				value = value.right(value.size()-1);
				index = comboBox->findText(value);
				 if(index >= 0)
					comboBox->setCurrentIndex(index);
			 }
		 }

		 comboBox->blockSignals( false );
		 return;
	}


	if(customi)
	{
		 QString value = index.model()->data(index, Qt::DisplayRole).toString();

		QComboBox *comboBox = static_cast<QComboBox*>(editor);
		 int index = comboBox->findText(value);
		 if(index >= 0)
			comboBox->setCurrentIndex(index);
		 else
		 {
			value = value.right(value.size()-2);
			index = comboBox->findText(value);
			 if(index >= 0)
				comboBox->setCurrentIndex(index);
			 else
			 {
				value = value.right(value.size()-1);
				index = comboBox->findText(value);
				 if(index >= 0)
					comboBox->setCurrentIndex(index);
			 }
		 }

		 comboBox->blockSignals( false );
		 return;
	}


	if(customf)
	{
		QString value = index.model()->data(index, Qt::DisplayRole).toString();
		QFileDialog *dialog = static_cast<QFileDialog*>(editor);
		dialog->setGeometry( 100, 100, 500, 300 );


		if(customf->PreviousFile == "")
			customf->PreviousFile = value;

		if(value != "")
		{
			dialog->setDirectory( QDir::currentPath()+"/Data/"+value.section('/', 0, -2) );
			dialog->selectFile ( value.section('/', -1) );
		}
		else
		{
			dialog->setDirectory(QDir::currentPath()+"/"+customf->StartingDirectory);
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
	TreeModel* Tmodel = static_cast<TreeModel*>(_model);
    boost::shared_ptr<CustomStringListModel> custom = Tmodel->CustomIndex(index);
    boost::shared_ptr<FileDialogOptionsBase> customf = Tmodel->CustomIndexFile(index);
    boost::shared_ptr<int> customi = Tmodel->CustomIndexNumber(index);

	if(custom)
	{
		QComboBox *comboBox = static_cast<QComboBox*>(editor);
		comboBox->blockSignals( true );

		QString value = comboBox->currentText();
		model->setData(index, value);			

		comboBox->blockSignals( false );
		return;
	}

	if(customi)
	{
		QComboBox *comboBox = static_cast<QComboBox*>(editor);
		comboBox->blockSignals( true );

		QString value = comboBox->currentText();
		model->setData(index, value);			

		comboBox->blockSignals( false );
		return;
	}

	if(customf)
	{
		if(_selectedfile != "")
		{
			QString outfile = customf->PostManagement(_selectedfile);
			if(outfile != "")
				model->setData(index, outfile);
		}
		else
		{
			if(!_accepted)
			{
				// file rejected - reset to previous
				model->setData(index, customf->PreviousFile);
			}

			customf->PreviousFile = "";
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
	_mount_itemlistmodel(new CustomStringListModel()), _special_itemlistmodel(new CustomStringListModel()),
	_actorscriptparttypeList(new CustomStringListModel()),_dorropeningtypeList(new CustomStringListModel()),
	_dorropeningdirectionList(new CustomStringListModel()), _hurtanimationList(new CustomStringListModel()),
	_iteminformclientList(new CustomStringListModel()), _addList(new CustomStringListModel()),
	_removeList(new CustomStringListModel()), _materialtypeList(new CustomStringListModel()),
	_pickfindpathstarted(false), _selectedid(-1), _weapontypeList(new CustomStringListModel())
{	
	_navimesh = boost::shared_ptr<NaviMeshHandler>(new NaviMeshHandler());

	QStringList actlist;
	actlist << "Static" << "Scripted" << "Door" << "Npc" <<"Movable";
	_actortypeList->setStringList(actlist);
	QStringList acttypelist;
	acttypelist << "No" << "Osg Model" << "Sprite" << "Lba1 Model" << "Lba2 Model" << "Sphere" << "Capsule" << "Box" << "BGImage";
	_actordtypeList->setStringList(acttypelist);
	QStringList actptypelist;
	actptypelist << "No Shape" << "Box" << "Capsule" << "Sphere" << "Triangle Mesh";
	_actorptypeList->setStringList(actptypelist);
	QStringList actmodelist;
	actmodelist << "None" << "Normal" << "Sport" << "Angry" << "Discrete" << "Protopack" << "Horse" << "Dinofly";
	_actormodeList->setStringList(actmodelist);

	QStringList materiallist;
	materiallist << "Off" << "Ambient" << "Diffuse" << "Specular" << "Emission" << "Ambient_And_Diffuse";
	_materialtypeList->setStringList(materiallist);
	
	QStringList weaponlist;
	weaponlist << "No" << "Contact" << "Distance";
	_weapontypeList->setStringList(weaponlist);


	QStringList addrlist;
	addrlist << "" << "Add";
	_addList->setStringList(addrlist);

	QStringList remrlist;
	remrlist << "" << "Remove";
	_removeList->setStringList(remrlist);


	QStringList condlist;
	condlist << "No" << "AlwaysTrueCondition" << "NegateCondition" << "AndCondition" << "OrCondition" 
				<< "ItemInInventoryCondition" << "QuestStartedCondition" << "QuestFinishedCondition"
				<< "QuestAvailableCondition" << "ChapterStartedCondition" << "ActorMovingCondition"
				<< "CheckFlagCondition" << "CustomCondition";
	_conditiontypeList->setStringList(condlist);
	
	QStringList cslist;
	cslist << "No" << "GoUpLadderScript" << "TakeExitUpScript" << "TakeExitDownScript" << "CustomScript";
	_cscripttypeList->setStringList(cslist);

	QStringList actilist;
	actilist << "No" << "TeleportAction" << "ClientScriptAction" << "CustomAction" 
			<< "DisplayTextAction" << "ConditionalAction" << "OpenContainerAction" << "SendSignalAction"
			<< "OpenDoorAction" << "CloseDoorAction" << "AddRemoveItemAction" << "HurtAction"
			 << "KillAction"  << "MultiAction" << "SwitchAction" << "StartQuestAction" << "FinishQuestAction"
			 << "OpenShopAction"<< "CutMapAction"<< "OpenLetterWritterAction"<< "OpenMailboxAction"
			 << "PlaySoundAction" << "SetFlagAction" << "ShoutTextAction" << "RandomAction" << "DisplayHolomapAction";

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

	QStringList scptypel;
	scptypel << "Remove" << "ASPGoTo" << "ASPWalkStraightTo" << "ASPTeleportTo"
			<< "ASPRotate" << "ASPSetRotation" << "ASPPlayAnimation" << "ASPRotateFromPoint"
			<< "ASPStartWaypoint" << "ASPFollowWaypoint"
			<< "ASPChangeAnimation" << "ASPChangeModel" << "ASPChangeOutfit" << "ASPChangeWeapon" 
			<< "ASPChangeMode" << "ASPWaitForSignal" << "ASPSendSignal"  
			<< "ASPShowHide" << "ASPCustom" << "ASPAttachToActor" << "ASPDetachFromActor"
			 << "ASPPlaySound" << "ASPStopSound" << "ASPPauseSound" << "ASPResumeSound";


	_actorscriptparttypeList->setStringList(scptypel);

	QStringList dorr_opentl;
	dorr_opentl << "translation" << "rotation";
	_dorropeningtypeList->setStringList(dorr_opentl);

	QStringList dorr_opendl;
	dorr_opendl << "right" << "left" << "top" << "bottom";
	_dorropeningdirectionList->setStringList(dorr_opendl);

	QStringList hurtaniml;
	hurtaniml << "No" << "SmallHurt" << "MediumHurt" << "BigHurt";
	_hurtanimationList->setStringList(hurtaniml);
	
	QStringList itinformcll;
	itinformcll << "No" << "Chat" << "Happy";
	_iteminformclientList->setStringList(itinformcll);
	


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

	_NavMeshdialog = new QDialog(this);
	_ui_NavMeshDialog.setupUi(_NavMeshdialog);

	_addtemplatedialog = new QDialog(this);
	_ui_addtemplateDialog.setupUi(_addtemplatedialog);

	_edittemplatedialog = new QDialog(this);
	_ui_edittemplateDialog.setupUi(_edittemplatedialog);


	_signalMapper = new QSignalMapper(this);
	 connect(_signalMapper, SIGNAL(mapped(int)), this, SLOT(TemplateMenuClicked(int)));



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

	// set model for quest
	{
		 QStringList header;
		 header << "Location" << "Title";
		_questlistmodel = new StringTableModel(header);
		_uieditor.tableView_QuestList->setModel(_questlistmodel);
		QHeaderView * mpheaders = _uieditor.tableView_QuestList->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
	}
	
	// set model for templates
	{
		 QStringList header;
		 header << "Type" << "Category" << "Name";
		_templatelistmodel = new StringTableModel(header);
		_ui_edittemplateDialog.tableView->setModel(_templatelistmodel);
		QHeaderView * mpheaders = _ui_edittemplateDialog.tableView->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
	}
	

	// set model for holomap
	{
		 QStringList header;
		 header << "Name";
		_holomaplistmodel = new StringTableModel(header);
		_uieditor.tableView_HolomapList->setModel(_holomaplistmodel);
		QHeaderView * mpheaders = _uieditor.tableView_HolomapList->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
	}

	// set model for holomap
	{
		 QStringList header;
		 header << "Name";
		_holomaploclistmodel = new StringTableModel(header);
		_uieditor.tableView_HolomapList_2->setModel(_holomaploclistmodel);
		QHeaderView * mpheaders = _uieditor.tableView_HolomapList_2->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
	}

	// set model for holomap
	{
		 QStringList header;
		 header << "Name";
		_holomappathlistmodel = new StringTableModel(header);
		_uieditor.tableView_HolomapList_3->setModel(_holomappathlistmodel);
		QHeaderView * mpheaders = _uieditor.tableView_HolomapList_3->horizontalHeader();
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
	connect(_uieditor.actionCustom_Lua_for_server, SIGNAL(triggered()), this, SLOT(OpenCustomServerLua())); 
	connect(_uieditor.actionCustom_Lua_for_client, SIGNAL(triggered()), this, SLOT(OpenCustomClientLua())); 
	connect(_uieditor.actionRefresh_client_script, SIGNAL(triggered()), this, SLOT(RefreshClientScript())); 
	connect(_uieditor.actionGenerate_navimesh, SIGNAL(triggered()), this, SLOT(GenerateNavimesh())); 
	connect(_uieditor.actionDisplay_Navimesh, SIGNAL(triggered()), this, SLOT(ToggleNavimeshDisplay())); 
	connect(_uieditor.actionNavimesh_Generation_Options, SIGNAL(triggered()), this, SLOT(OptionNavimesh())); 
	connect(_uieditor.actionTest_Find_Path, SIGNAL(triggered()), this, SLOT(TestFindPath())); 
	connect(_uieditor.actionNPC_attack_player, SIGNAL(triggered()), this, SLOT(TestNPCAttack())); 
	connect(_uieditor.actionNPC_stop_attack, SIGNAL(triggered()), this, SLOT(TestNPCStopAttack())); 

	connect(_uieditor.actionCopy, SIGNAL(triggered()), this, SLOT(CopyObjectClicked())); 
	connect(_uieditor.actionPaste, SIGNAL(triggered()), this, SLOT(PasteObjectClicked())); 
	connect(_uieditor.actionCut, SIGNAL(triggered()), this, SLOT(CutObjectClicked())); 
	connect(_uieditor.actionDelete, SIGNAL(triggered()), this, SLOT(DeleteObjectClicked())); 

	connect(_uieditor.actionAdd_selected_as_template, SIGNAL(triggered()), this, SLOT(AddTemplateObject())); 
	connect(_uieditor.actionEdit_existing_templates, SIGNAL(triggered()), this, SLOT(EditTemplates())); 


	connect(_uieditor.pushButton_info_go, SIGNAL(clicked()) , this, SLOT(info_go_clicked()));
	connect(_uieditor.radioButton_info_player, SIGNAL(toggled(bool)) , this, SLOT(info_camera_toggled(bool)));
	connect(_uieditor.radioButton_info_fly, SIGNAL(toggled(bool)) , this, SLOT(info_camera_toggled(bool)));
	connect(_uieditor.radioButton_info_free, SIGNAL(toggled(bool)) , this, SLOT(info_camera_toggled(bool)));

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
	connect(_uieditor.pushButton_play, SIGNAL(clicked()) , this, SLOT(TextPlay_button()));	

	


	connect(_uieditor.pushButton_addActor, SIGNAL(clicked()) , this, SLOT(ActorAdd_button()));
	connect(_uieditor.pushButton_removeActor, SIGNAL(clicked()) , this, SLOT(ActorRemove_button()));	
	connect(_uieditor.pushButton_selectActor, SIGNAL(clicked()) , this, SLOT(ActorSelect_button()));


	connect(_uieditor.pushButton_additem, SIGNAL(clicked()) , this, SLOT(ItemAdd_button()));
	connect(_uieditor.pushButton_removeitem, SIGNAL(clicked()) , this, SLOT(ItemRemove_button()));	
	connect(_uieditor.pushButton_selectitem, SIGNAL(clicked()) , this, SLOT(ItemSelect_button()));

	connect(_uieditor.pushButton_additem_2, SIGNAL(clicked()) , this, SLOT(StartItemAdd_button()));
	connect(_uieditor.pushButton_removeitem_2, SIGNAL(clicked()) , this, SLOT(StartItemRemove_button()));	



	connect(_uieditor.pushButton_addquest, SIGNAL(clicked()) , this, SLOT(QuestAdd_button()));
	connect(_uieditor.pushButton_removequest, SIGNAL(clicked()) , this, SLOT(QuestRemove_button()));	
	connect(_uieditor.pushButton_selectquest, SIGNAL(clicked()) , this, SLOT(QuestSelect_button()));


	connect(_uieditor.pushButton_addholo, SIGNAL(clicked()) , this, SLOT(HoloAdd_button()));
	connect(_uieditor.pushButton_removeholo, SIGNAL(clicked()) , this, SLOT(HoloRemove_button()));	
	connect(_uieditor.pushButton_goto_holo, SIGNAL(clicked()) , this, SLOT(HoloSelect_button()));



	
	connect(_uieditor.textEdit_worlddescription, SIGNAL(textChanged()) , this, SLOT(WorldDescriptionChanged()));	
	connect(_uieditor.textEdit_worldnews, SIGNAL(textChanged()) , this, SLOT(WorldNewsChanged()));	
	connect(_uieditor.lineEdit_startingscript, SIGNAL(textChanged()) , this, SLOT(WorldStartingScriptChanged()));	
	

	connect(_uieditor.pushButton_goto_tp, SIGNAL(clicked()) , this, SLOT(goto_tp_button_clicked()));
	connect(_uieditor.pushButton_goto_map, SIGNAL(clicked()) , this, SLOT(goto_map_button_clicked()));

	connect(_uieditor.tableView_TeleportList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(goto_tp_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_MapList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(goto_map_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_SpawningList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selectspawning_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableViewTriggerList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selecttrigger_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_ActorList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selectactor_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_TextList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selecttext_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_ItemList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selectitem_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_QuestList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selectquest_double_clicked(const QModelIndex&)));

	connect(_uieditor.tableView_HolomapList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selectholomap_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_HolomapList_2, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selectholomaploc_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_HolomapList_3, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selectholomappath_double_clicked(const QModelIndex&)));

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

	connect(_ui_addtextdialog.pushButton_addvoice, SIGNAL(clicked()) , this, SLOT(VoicemAdd_button()));
	connect(_ui_addtextdialog.pushButton_removevoice, SIGNAL(clicked()) , this, SLOT(VoicemRem_button()));


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
	connect(_uieditor.spinBox_lhololocid, SIGNAL(valueChanged(int)) , this, SLOT(MapInstanceChanged(int)));	



	connect(_uieditor.comboBox_choosetexttype, SIGNAL(activated(int)) , this, SLOT(TextTypeModified(int)));	
	connect(_uieditor.comboBox_chooselang, SIGNAL(activated(int)) , this, SLOT(TextLangModified(int)));	

	connect(_uieditor.lineEdit_mapmusic, SIGNAL(textChanged(QString)) , this, SLOT(MapMusicChanged(QString)));
	connect(_uieditor.comboBox_mapmusicrepeat, SIGNAL(activated(int)) , this, SLOT(MapMusicRepeatChanged(int)));
	connect(_uieditor.pushButto_mapmusic, SIGNAL(clicked()) , this, SLOT(MapMusicFile_clicked()));

	connect(_uieditor.spinBox_cskin, SIGNAL(valueChanged(int)) , this, SLOT(colorModified(int)));	
	connect(_uieditor.spinBox_ceyes, SIGNAL(valueChanged(int)) , this, SLOT(colorModified(int)));	
	connect(_uieditor.spinBox_chair, SIGNAL(valueChanged(int)) , this, SLOT(colorModified(int)));	
	connect(_uieditor.spinBox_coutfit, SIGNAL(valueChanged(int)) , this, SLOT(colorModified(int)));	
	connect(_uieditor.spinBox_cweapon, SIGNAL(valueChanged(int)) , this, SLOT(colorModified(int)));	
	connect(_uieditor.spinBox_cmount, SIGNAL(valueChanged(int)) , this, SLOT(colorModified(int)));	
	connect(_uieditor.spinBox_cmount2, SIGNAL(valueChanged(int)) , this, SLOT(colorModified(int)));	
	
	connect(_ui_edittemplateDialog.pushButton_delete, SIGNAL(clicked()) , this, SLOT(TemplateRemove_button()));


	// read notice
	int read = 0;
	ConfigurationManager::GetInstance()->GetInt("Options.Editor.NoticeAccepted", read);
	if(read == 0)
	{
		_NoticeDialogdialog = new QDialog(this);
		_ui_NoticeDialog.setupUi(_NoticeDialogdialog);
		_NoticeDialogdialog->setModal(true);
		_NoticeDialogdialog->show();

		
		connect(_ui_NoticeDialog.buttonBox, SIGNAL(accepted()) , this, SLOT(Notice_accepted()));
		connect(_ui_NoticeDialog.buttonBox, SIGNAL(rejected()) , this, SLOT(Notice_rejected()));
		connect(_NoticeDialogdialog, SIGNAL(finished(int)) , this, SLOT(Notice_closed(int)));

	}
}




/***********************************************************
Destructor
***********************************************************/
EditorHandler::~EditorHandler()
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator it = _Actors.begin();
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator end = _Actors.end();
	for(; it != end; ++it)
		it->second->SetScriptHandler(NULL);

	_triggers.clear();
	_Actors.clear();
	_spawns.clear();

	delete _addtriggerdialog;
}



/***********************************************************
set the osg window
***********************************************************/
void EditorHandler::SetOsgWindow(QWidget *osgwindow)
{
	_uieditor.groupBox_game->layout()->addWidget(osgwindow);
	osgwindow->show();
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
void EditorHandler::SaveWorldAction(std::string mapname)
{
	if(!IsWorldOpened())
		return;

	if(_modified)
	{
		// save xml file
		DataLoader::getInstance()->SaveWorldInformation(_winfo.Description.WorldName, _winfo);

		// save current map
		if(mapname == "")
			mapname = _uieditor.label_mapname->text().toAscii().data();

		if(mapname != "")
			SaveMap("./Data/Worlds/" + _winfo.Description.WorldName + "/Lua/" + mapname + "_server.lua");

		// save text
		Localizer::getInstance()->SaveTexts();

		// save general
		SharedDataHandler::getInstance()->SaveToLua();

		// save templates
		XmlReader::SaveObjectTemplateFile("./Data/Worlds/" + _winfo.Description.WorldName + "/Editorconfig.xml", _objecttemplates);

		// save holomap
		SaveHoloMap("./Data/Worlds/" + _winfo.Description.WorldName + "/Lua/Holomap.lua");



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
	_firstmapofworld = true;

	setWindowTitle(("LBANet Editor - " + worldname).c_str());

	_uieditor.label_worldname->setText(_winfo.Description.WorldName.c_str());

	QString descs = QString::fromUtf8(_winfo.Description.Description.c_str());
	descs.replace(QString(" @ "), QString("\n"));
	_uieditor.textEdit_worlddescription->setText(descs);

	QString newss = QString::fromUtf8(_winfo.Description.News.c_str());
	newss.replace(QString(" @ "), QString("\n"));
	_uieditor.textEdit_worldnews->setText(newss);

	QString startingscript = QString::fromUtf8(_winfo.StartingInfo.StartingScript.c_str());
	_uieditor.lineEdit_startingscript->setText(startingscript);


	_objectmodel->SetWorldName(worldname);


	// update texts
	{
		Localizer::getInstance()->SetWorldName(worldname);

		//add language to combobox
		_currentchoosenlang = "";
		{
			_uieditor.comboBox_chooselang->clear();
			int idxlang = 0;

			std::vector<std::string> langs = Localizer::getInstance()->GetLanguages();
			if(langs.size() > 0)
				_currentchoosenlang = langs[0];

			for(size_t ll=0; ll<langs.size(); ++ll)
			{
				_uieditor.comboBox_chooselang->addItem (langs[ll].c_str());
				if(langs[ll] == "en")
				{
					_uieditor.comboBox_chooselang->setCurrentIndex(ll);
					idxlang = ll;
				}
			}
		
			// add text
			TextLangModified(idxlang);
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
		}
	}

	// add lua stuff
	_luaH = boost::shared_ptr<ServerLuaHandler>(new ServerLuaHandler());


	// add templates
	std::string templatefile = "Data/Worlds/" + _winfo.Description.WorldName + "/Editorconfig.xml";
	std::vector<EditorTemplateObject> temps = XmlReader::LoadObjectTemplateFile(templatefile);
	for(size_t i=0; i< temps.size(); ++i)
		AddNewTemplate(temps[i]);
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
	_uieditor.lineEdit_startingscript->setText("");

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
	_spawns.clear();

	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator it = _Actors.begin();
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator end = _Actors.end();
	for(; it != end; ++it)
		it->second->SetScriptHandler(NULL);

	_Actors.clear();

	ResetObject();

	_navimesh->Reset();
	HideStartPath();
	HideEndPath();
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

	_selectedid = -1;
}



/***********************************************************
on go tp clicked
***********************************************************/
void EditorHandler::goto_tp_double_clicked(const QModelIndex & itm)
{
	//goto_tp_button_clicked();
	TpEdit_button();
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
		ChangeMap(mapname, spawning);
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
		long spid = SharedDataHandler::getInstance()->GetSpawnId(mapname, "");	
		if(spid >= 0)
		{
			ChangeMap(mapname, spid);
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

	_uieditor.spinBox_lhololocid->setValue((int)mapinfo.LinkedHoloLocation);

	//music part
	_uieditor.lineEdit_mapmusic->setText(mapinfo.Music.c_str());
	_uieditor.comboBox_mapmusicrepeat->setCurrentIndex((mapinfo.Repeat == 0)?1:0);

	if(_firstmapofworld)
	{
		_firstmapofworld = false;


		// add spawns
		{
			LbaNet::MapsSeq::const_iterator itm = _winfo.Maps.begin();
			LbaNet::MapsSeq::const_iterator endm = _winfo.Maps.end();
			for(long cc=1; itm != endm; ++itm, ++cc)
			{
				// add spawning to the list
				_mapSpawningList[itm->first] = boost::shared_ptr<CustomStringListModel>(new CustomStringListModel());
			
				std::map<long, boost::shared_ptr<Spawn> > spwns = SharedDataHandler::getInstance()->GetSpawns(itm->first);
				std::map<long, boost::shared_ptr<Spawn> >::iterator itsp = spwns.begin();
				std::map<long, boost::shared_ptr<Spawn> >::iterator endsp = spwns.end();
				for(; itsp != endsp; ++itsp)
					AddSpawningName(itm->first, itsp->second->GetName());
			}
		}

		// refresh starting info
		RefreshStartingInfo();



		// add teleport
		{
			_tplistmodel->Clear();

			const std::map<long, boost::shared_ptr<TeleportDef> > &tpseq = SharedDataHandler::getInstance()->GetTpList();
			std::map<long, boost::shared_ptr<TeleportDef> >::const_iterator ittp = tpseq.begin();
			std::map<long, boost::shared_ptr<TeleportDef> >::const_iterator endtp = tpseq.end();
			for(long cc=1; ittp != endtp; ++ittp, ++cc)
			{
				std::string spawningname;

				boost::shared_ptr<Spawn> spwn = SharedDataHandler::getInstance()->GetSpawn(ittp->second->GetMapName(), ittp->second->GetSpawn());
				if(spwn)
					spawningname = spwn->GetName();

				QStringList data;
				data << ittp->second->GetName().c_str() << ittp->second->GetMapName().c_str() << spawningname.c_str();
				_tplistmodel->AddOrUpdateRow(ittp->first, data);

				_currteleportidx = ittp->first;
			}
		}


		// add quest
		{
			_questlistmodel->Clear();

			std::map<long, QuestPtr> &tpseq = QuestHandler::getInstance()->GetQuests();
			std::map<long, QuestPtr>::const_iterator ittp = tpseq.begin();
			std::map<long, QuestPtr>::const_iterator endtp = tpseq.end();
			for(; ittp != endtp; ++ittp)
			{
				long tid = ittp->second->GetLocationTextId();
				std::string txt = Localizer::getInstance()->GetText(Localizer::Quest, tid);
				std::stringstream txttmp;
				txttmp<<tid<<": "<<txt;
				long tid2 = ittp->second->GetTitleTextId();
				std::string txt2 = Localizer::getInstance()->GetText(Localizer::Quest, tid2);
				std::stringstream txttmp2;
				txttmp2<<tid2<<": "<<txt2;

				QStringList data;
				data << txttmp.str().c_str() << txttmp2.str().c_str();
				_questlistmodel->AddOrUpdateRow(ittp->first, data);
			}
		}


		// add holomap
		{
			_holomaplistmodel->Clear();
			_holomaploclistmodel->Clear();
			_holomappathlistmodel->Clear();

			{
				std::map<long, HolomapPtr> &tpseq = HolomapHandler::getInstance()->GetHolomaps();
				std::map<long, HolomapPtr>::const_iterator ittp = tpseq.begin();
				std::map<long, HolomapPtr>::const_iterator endtp = tpseq.end();
				for(; ittp != endtp; ++ittp)
				{
					QStringList data;
					data << ittp->second->GetName().c_str();
					_holomaplistmodel->AddOrUpdateRow(ittp->first, data);
				}
			}

			{
				std::map<long, HolomapLocationPtr> &tpseq = HolomapHandler::getInstance()->GetHolomapLocs();
				std::map<long, HolomapLocationPtr>::const_iterator ittp = tpseq.begin();
				std::map<long, HolomapLocationPtr>::const_iterator endtp = tpseq.end();
				for(; ittp != endtp; ++ittp)
				{
					QStringList data;
					data << ittp->second->GetName().c_str();
					_holomaploclistmodel->AddOrUpdateRow(ittp->first, data);
				}
			}

			{
				std::map<long, HolomapTravelPathPtr> &tpseq = HolomapHandler::getInstance()->GetHolomapPaths();
				std::map<long, HolomapTravelPathPtr>::const_iterator ittp = tpseq.begin();
				std::map<long, HolomapTravelPathPtr>::const_iterator endtp = tpseq.end();
				for(; ittp != endtp; ++ittp)
				{
					QStringList data;
					data << ittp->second->GetName().c_str();
					_holomappathlistmodel->AddOrUpdateRow(ittp->first, data);
				}
			}
		}


		// add inventory items
		{
			_itemNameList->Clear();
			_itemlistmodel->Clear();
			_itemNameList->AddData("No item");

			const std::map<long, InventoryItemDefPtr> &_inventoryitems = InventoryItemHandler::getInstance()->GetItemMap();
			std::map<long, InventoryItemDefPtr>::const_iterator itinv = _inventoryitems.begin();
			std::map<long, InventoryItemDefPtr>::const_iterator endinv = _inventoryitems.end();
			for(; itinv != endinv; ++itinv)
			{
				QStringList data;
				data << itinv->second->GetName().c_str();
				data << InventoryItemHandler::getInstance()->GetItemTypeString(itinv->first).c_str();
				_itemlistmodel->AddOrUpdateRow(itinv->first, data);

				std::stringstream txtwithid;
				txtwithid<<itinv->first<<": "<<itinv->second->GetName().c_str();
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

	std::string navimeshfile = "./Data/Worlds/" + _winfo.Description.WorldName + "/AI/" + mapname + ".nmesh";
	if(FileUtil::FileExist(navimeshfile, false))
	{
		_navimesh->LoadFromFile(navimeshfile);
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
				_uiaddspawningdialog.checkBox_forcerotation->isChecked(),
				ActionBasePtr());



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
										ActionBasePtr actionatarrival,
										long modifyid)
{

	long spid = ((modifyid >= 0)?modifyid:_currspawningidx);
	boost::shared_ptr<Spawn> newspawn(new Spawn(spid));
	newspawn->SetName(spawningname);
	newspawn->SetPosX(PosX);
	newspawn->SetPosY(PosY);
	newspawn->SetPosZ(PosZ);
	newspawn->SetRotation(Rotation);
	newspawn->SetForceRotation(forcedrotation);
	newspawn->SetActionAtArrival(actionatarrival);


	QString currmap = _uieditor.label_mapname->text();
	_uieditor.label_mapname->setText(mapname.c_str());
	AddSpawn(newspawn);
	_uieditor.label_mapname->setText(currmap);


	// then inform the server
	EditorUpdateBasePtr update = new UpdateEditor_AddOrModSpawning(newspawn);

	SharedDataHandler::getInstance()->EditorUpdate(mapname, update);

	return spid;
}



/***********************************************************
remove a spawning from the map
***********************************************************/
void EditorHandler::RemoveSpawning(const std::string &mapname, long spawningid)
{
	// first update the internal info
	std::map<long, boost::shared_ptr<Spawn> >::iterator it = _spawns.find(spawningid);
	if(it != _spawns.end())
	{
		// remove from text list
		RemoveSpawningName(mapname, it->second->GetName());

		// erase from data
		_spawns.erase(it);

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
	bool changecam = _uieditor.radioButton_info_free->isChecked();
	bool fly = _uieditor.radioButton_info_fly->isChecked();

	EventsQueue::getReceiverQueue()->AddEvent(new EditorCameraChangeEvent(changecam));
	EditorSharedData::GetInstance()->SetFly(fly);
}



/***********************************************************
set spawning in the object
***********************************************************/
void EditorHandler::SelectSpawning(long id, const QModelIndex &parent)
{
	std::string mapname = _uieditor.label_mapname->text().toAscii().data();
	std::map<long, boost::shared_ptr<Spawn> >::iterator it = _spawns.find(id);
	if(it == _spawns.end())
		return;

	std::string spawningname = it->second->GetName();
	float PosX = it->second->GetPosX();
	float PosY = it->second->GetPosY();
	float PosZ = it->second->GetPosZ();
	float Rotation = it->second->GetRotation();
	bool forcedrotation = it->second->GetForceRotation();
	ActionBasePtr actptr = it->second->GetActionAtArrival();

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

	// add action 
	{
		std::string acttype = GetActionType(actptr);

		QVector<QVariant> data;
		data << "Action On Arrival" << acttype.c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		
		if(actptr)
			SelectAction(actptr.get(), idx);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _actiontypeList);
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
		int updatedrow = index1.row();
		// go to parents until we find good one
		while(_objectmodel->data(_objectmodel->GetIndex(0, 0, parentIdx)).toString() != "Type")
		{
			parentIdx = _objectmodel->parent(parentIdx);
			updatedrow = -1;
		}

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
			ActorObjectChanged(objid, parentIdx, updatedrow);
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

		if(type == "Dialog")
		{
			DialogChanged(parentIdx);
			return;
		}	

		if(type == "Teleport")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toLong();
			TeleportChanged(objid, parentIdx);
			return;
		}	

		if(type == "Quest")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toLong();
			QuestChanged(objid, parentIdx);
			return;
		}

		if(type == "Projectile")
		{
			ProjectileChanged(parentIdx);
			return;
		}

		if(type == "Holomap")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 1, parentIdx)).toString().toLong();
			HolomapChanged(objid, parentIdx);
			return;
		}	
		if(type == "HolomapLoc")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 1, parentIdx)).toString().toLong();
			HolomapLocChanged(objid, parentIdx);
			return;
		}	
		if(type == "HolomapPath")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 1, parentIdx)).toString().toLong();
			HolomapPathChanged(objid, parentIdx);
			return;
		}
	}
}


/***********************************************************
called when spawning object changed
***********************************************************/
void EditorHandler::SpawningObjectChanged(long id, const QModelIndex &parentIdx)
{
	std::map<long, boost::shared_ptr<Spawn> >::iterator it = _spawns.find(id);
	if(it == _spawns.end())	
		return;

	boost::shared_ptr<Spawn> oldspawn = it->second;
	if(!oldspawn)
		return;

	if(_objectmodel->rowCount() > 9)
	{
		QString name = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toString();
		float PosX = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toFloat();
		float PosY = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toFloat();
		float PosZ = _objectmodel->data(_objectmodel->GetIndex(1, 6, parentIdx)).toFloat();
		bool forcedrotation = _objectmodel->data(_objectmodel->GetIndex(1, 7, parentIdx)).toBool();
		float Rotation = _objectmodel->data(_objectmodel->GetIndex(1, 8, parentIdx)).toFloat();
		std::string mapname = _uieditor.label_mapname->text().toAscii().data();
		std::string oldname = oldspawn->GetName();

		//action
		ActionBasePtr spawnaction = oldspawn->GetActionAtArrival();
		std::string action = _objectmodel->data(_objectmodel->GetIndex(1, 9, parentIdx)).toString().toAscii().data();
		{
			std::string curract = GetActionType(spawnaction);
			if(action != curract)
			{
				//create new action
				spawnaction = CreateAction(action);

				QModelIndex curidx = _objectmodel->GetIndex(0, 9, parentIdx);
				_objectmodel->Clear(curidx);
				if(spawnaction)
				{
					SelectAction(spawnaction.get(), curidx);
					_uieditor.treeView_object->setExpanded(curidx, true); // expand 
				}
			}
		}


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
									spawnaction, id);

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
	switch(actor->GetActorInfo().PhysicDesc.TypePhysO)
	{
		case LbaNet::StaticAType:
			type = "Static";
		break;

		case LbaNet::KynematicAType:
			type = actor->ActorType();
		break;

		case LbaNet::CharControlAType:
			type = "Movable";
		break;  
	}


	std::string dtype = "No";
	switch(actor->GetActorInfo().DisplayDesc.TypeRenderer)
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
	switch(actor->GetActorInfo().PhysicDesc.TypeShape)
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

	const ActorObjectInfo & ainfo = actor->GetActorInfo();
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

		LbaNet::Lba1ColorChangeSeq::const_iterator itsw = ainfo.DisplayDesc.ColorSwaps.begin();
		LbaNet::Lba1ColorChangeSeq::const_iterator endsw = ainfo.DisplayDesc.ColorSwaps.end();
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
add spawn
***********************************************************/	
void EditorHandler::AddSpawn(boost::shared_ptr<Spawn> spawn)
{
	if(spawn)
	{
		_spawns[spawn->GetId()] = spawn;

		QString Xs;
		Xs.setNum(spawn->GetPosX(), 'f');
		QString Ys;
		Ys.setNum(spawn->GetPosY(), 'f');
		QString Zs;
		Zs.setNum(spawn->GetPosZ(), 'f');

		QStringList data;
		data << spawn->GetName().c_str() << Xs << Ys << Zs;
		_mapspawninglistmodel->AddOrUpdateRow(spawn->GetId(), data);

		_currspawningidx = (_spawns.rbegin()->second->GetId() + 1);


		std::string mapname = _uieditor.label_mapname->text().toAscii().data();

		// add name to list
		if(mapname != "")
			AddSpawningName(mapname, spawn->GetName());
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
void EditorHandler::SelectAction(ActionBase* action, const QModelIndex &parent)
{
	if(parent == QModelIndex())
		ResetObject();

	if(!action)
		return;


	// add pointer for later change
	_modelidxdatamap[parent] = (void*)action;


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
		TeleportAction* ptr = static_cast<TeleportAction*>(action);
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
				boost::shared_ptr<Spawn> spwn = SharedDataHandler::getInstance()->GetSpawn(ptr->GetMapName(), ptr->GetSpawning());
				if(spwn)
					spawningname = spwn->GetName();
			}

			QVector<QVariant> data;
			data << "Spawn" << spawningname.c_str();
			_objectmodel->AppendRow(data, parent);
		}

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 2, parent), _mapNameList);

		std::map<std::string, boost::shared_ptr<CustomStringListModel> >::iterator it = 
													_mapSpawningList.find(ptr->GetMapName());
		if(it != _mapSpawningList.end())
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 3, parent), it->second);

		return;
	}

	if(actiontype == "ClientScriptAction")
	{
		ClientScriptAction* ptr = static_cast<ClientScriptAction*>(action);
		{
			ClientScriptBasePtr scriptptr = ptr->GetScript();
			std::string name = GetCScriptType(scriptptr);

			QVector<QVariant> data;
			data << "Script" << name.c_str();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);

			if(scriptptr)
				SelectCScript(scriptptr, idx);
		}

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 2, parent), _cscripttypeList);

		return;
	}


	if(actiontype == "CustomAction")
	{
		CustomAction* ptr = static_cast<CustomAction*>(action);
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
		DisplayTextAction* ptr = static_cast<DisplayTextAction*>(action);
		{
			std::string txt = Localizer::getInstance()->GetText(Localizer::Map, ptr->GetTextId());
			std::stringstream txttmp;
			txttmp<<ptr->GetTextId()<<": "<<txt;

			QVector<QVariant> data;
			data << "Text" << QString::fromUtf8(txttmp.str().c_str());
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 2, parent), _text_mapNameList);

		return;
	}

	if(actiontype == "ConditionalAction")
	{
		ConditionalAction* ptr = static_cast<ConditionalAction*>(action);
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
					SelectAction(actptr.get(), idx);
			}

			// add action false
			{
				ActionBasePtr actptr = ptr->GetActionFalse();
				std::string acttype = GetActionType(actptr);

				QVector<QVariant> data;
				data << "Action On False" << acttype.c_str();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);
				
				if(actptr)
					SelectAction(actptr.get(), idx);
			}
		}

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 2, parent), _conditiontypeList);
		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 3, parent), _actiontypeList);
		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _actiontypeList);

		return;
	}



	if(actiontype == "OpenContainerAction")
	{
		OpenContainerAction* ptr = static_cast<OpenContainerAction*>(action);
		{
			// add TimeToReset
			{
				QVector<QVariant> data;
				data << "TimeToReset (in sec)" << ptr->GetTimeToReset();
				_objectmodel->AppendRow(data, parent);
			}

			// add items
			{
				QVector<QVariant> data;
				data << "Item list" << "";
				QModelIndex idx = _objectmodel->AppendRow(data, parent, true);	

				const std::vector<ContainerItemGroupElement> & items = ptr->GetItems();
				for(size_t i=0; i<items.size(); ++i)
				{
					std::stringstream txtwithid;
					txtwithid<<items[i].Id<<": "<<InventoryItemHandler::getInstance()->GetItemInfo(items[i].Id).Name;

					QVector<QVariant> datait;
					datait << "Item" << txtwithid.str().c_str();
					QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	

					//add min
					{
						QVector<QVariant> datachild;
						datachild << "Min" << items[i].Min;
						QModelIndex idx1 = _objectmodel->AppendRow(datachild, idxit);	

						// add tooltip
						_objectmodel->setTooltip(idx1, "Minimum number of item to spawn");
						QModelIndex idx2 = _objectmodel->GetIndex(1, idx1.row(), idx1.parent());
						_objectmodel->setTooltip(idx2, "Minimum number of item to spawn");
					}

					//add max
					{
						QVector<QVariant> datachild;
						datachild << "Max" << items[i].Max;
						QModelIndex idx1 = _objectmodel->AppendRow(datachild, idxit);		

						// add tooltip
						_objectmodel->setTooltip(idx1, "Maximum number of item to spawn");
						QModelIndex idx2 = _objectmodel->GetIndex(1, idx1.row(), idx1.parent());
						_objectmodel->setTooltip(idx2, "Maximum number of item to spawn");
					}

					//add probability
					{
						QVector<QVariant> datachild;
						datachild << "Probability" << (double)items[i].Probability;
						QModelIndex idx1 = _objectmodel->AppendRow(datachild, idxit);			

						// add tooltip
						_objectmodel->setTooltip(idx1, "Probability of the item to spawn (1 = 100%)");
						QModelIndex idx2 = _objectmodel->GetIndex(1, idx1.row(), idx1.parent());
						_objectmodel->setTooltip(idx2, "Probability of the item to spawn (1 = 100%)");
					}

					//add group
					{
						QVector<QVariant> datachild;
						datachild << "Group" << items[i].Group;
						QModelIndex idx1 = _objectmodel->AppendRow(datachild, idxit);				

						// add tooltip
						_objectmodel->setTooltip(idx1, "The items part of the same group are mutually exclusive");
						QModelIndex idx2 = _objectmodel->GetIndex(1, idx1.row(), idx1.parent());
						_objectmodel->setTooltip(idx2, "The items part of the same group are mutually exclusive");
					}

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _itemNameList);	
				}

				// add new item
				QVector<QVariant> datait;
				datait << "Item" << "Add item...";
				QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	
				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _itemNameList);	
			
			
				_uieditor.treeView_object->setExpanded(idx, true); // expand 
			}

		}
		return;
	}
	


	if(actiontype == "SendSignalAction")
	{
		SendSignalAction* ptr = static_cast<SendSignalAction*>(action);
		{
			QVector<QVariant> data;
			data << "ActorId" << (int)ptr->GetActorId();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		{
			QVector<QVariant> data;
			data << "Signal" << ptr->GetSignal();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}

		return;
	}

	if(actiontype == "OpenDoorAction")
	{
		SendSignalAction* ptr = static_cast<SendSignalAction*>(action);
		{
			QVector<QVariant> data;
			data << "ActorId" << (int)ptr->GetActorId();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}

		return;
	}

	if(actiontype == "CloseDoorAction")
	{
		SendSignalAction* ptr = static_cast<SendSignalAction*>(action);
		{
			QVector<QVariant> data;
			data << "ActorId" << (int)ptr->GetActorId();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}

		return;
	}

	if(actiontype == "AddRemoveItemAction")
	{
		AddRemoveItemAction* ptr = static_cast<AddRemoveItemAction*>(action);
		{
			long id = ptr->GetItemId();
			std::stringstream txtwithid;
			txtwithid<<id<<": "<<InventoryItemHandler::getInstance()->GetItemInfo(id).Name;
			QVector<QVariant> data;
			data << "Item Id" << txtwithid.str().c_str();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 2, parent), _itemNameList);
		}
		{
			QVector<QVariant> data;
			data << "Update Number" << ptr->GetNumber();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		{
			QVector<QVariant> data;
			data << "Inform Client" << ptr->GetInformClientTypeString().c_str();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _iteminformclientList);
		}
		
		return;
	}


	if(actiontype == "HurtAction")
	{
		HurtAction* ptr = static_cast<HurtAction*>(action);
		{
			QVector<QVariant> data;
			data << "Hurt Value" << (double)ptr->GetHurtValue();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		{
			QVector<QVariant> data;
			data << "Hurt life?" << ptr->HurtLife();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		{
			QVector<QVariant> data;
			data << "Play animation" << ptr->GetPlayAnimationString().c_str();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _hurtanimationList);
		}
		return;
	}

	if(actiontype == "MultiAction")
	{
		MultiAction* ptr = static_cast<MultiAction*>(action);

		// add actions
		{
			QVector<QVariant> data;
			data << "Actions" << "";
			QModelIndex idx = _objectmodel->AppendRow(data, parent, true);	

			const std::vector<ActionBasePtr> & items = ptr->GetActions();
			for(size_t i=0; i<items.size(); ++i)
			{
				QVector<QVariant> data;
				data << "Action" << items[i]->GetTypeName().c_str();
				QModelIndex idxchild = _objectmodel->AppendRow(data, idx);
				
				SelectAction(items[i].get(), idxchild);

				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxchild.row(), idx), _actiontypeList);
			}

			// add new item
			QVector<QVariant> datait;
			datait << "Action" << "Add new...";
			QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idx), _actiontypeList);	
		
		
			_uieditor.treeView_object->setExpanded(idx, true); // expand 
		}

		return;
	}

	if(actiontype == "RandomAction")
	{
		RandomAction* ptr = static_cast<RandomAction*>(action);

		// add actions
		{
			QVector<QVariant> data;
			data << "Actions" << "";
			QModelIndex idx = _objectmodel->AppendRow(data, parent, true);	

			const std::vector<ActionBasePtr> & items = ptr->GetActions();
			for(size_t i=0; i<items.size(); ++i)
			{
				QVector<QVariant> data;
				data << "Action" << items[i]->GetTypeName().c_str();
				QModelIndex idxchild = _objectmodel->AppendRow(data, idx);
				
				SelectAction(items[i].get(), idxchild);

				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxchild.row(), idx), _actiontypeList);
			}

			// add new item
			QVector<QVariant> datait;
			datait << "Action" << "Add new...";
			QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idx), _actiontypeList);	
		
		
			_uieditor.treeView_object->setExpanded(idx, true); // expand 
		}

		return;
	}


	if(actiontype == "SwitchAction")
	{
		SwitchAction* ptr = static_cast<SwitchAction*>(action);
		{
			// add actor id
			{
				QVector<QVariant> data;
				data << "Updated Actor" <<  (int)ptr->GetActorId();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);
			}

			// add actor model
			{
				QVector<QVariant> data;
				data << "New Model" <<  ptr->GetSwitchModel().c_str();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);


				std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator ita = _Actors.find(ptr->GetActorId());
				if(ita != _Actors.end() && ita->second->GetActorInfo().DisplayDesc.TypeRenderer == RenderSprite)
					_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, idx.row(), parent), "Select an image", "Sprites", "Image Files (*.png *.bmp *.jpg *.gif)");
				else
					_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, idx.row(), parent), "Select a model file", "Models", "Model Files (*.osg *.osgb *.osgt)");
			}


			// add action On
			{
				ActionBasePtr actptr = ptr->GetActionTrue();
				std::string acttype = GetActionType(actptr);

				QVector<QVariant> data;
				data << "Action On" << acttype.c_str();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);
				
				if(actptr)
					SelectAction(actptr.get(), idx);
			}

			// add action Off
			{
				ActionBasePtr actptr = ptr->GetActionFalse();
				std::string acttype = GetActionType(actptr);

				QVector<QVariant> data;
				data << "Action Off" << acttype.c_str();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);
				
				if(actptr)
					SelectAction(actptr.get(), idx);
			}
		}

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _actiontypeList);
		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 5, parent), _actiontypeList);

		return;
	}


	if(actiontype == "StartQuestAction")
	{
		StartQuestAction* ptr = static_cast<StartQuestAction*>(action);
		{
			QVector<QVariant> data;
			data << "QuestId" << (int)ptr->GetQuestId();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		return;
	}

	if(actiontype == "FinishQuestAction")
	{
		FinishQuestAction* ptr = static_cast<FinishQuestAction*>(action);
		{
			QVector<QVariant> data;
			data << "QuestId" << (int)ptr->GetQuestId();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		return;
	}

	if(actiontype == "OpenShopAction")
	{
		OpenShopAction* ptr = static_cast<OpenShopAction*>(action);
		{
			{
			std::stringstream txtwithid;
			txtwithid<<ptr->GetCurrencyItem()<<": "<<InventoryItemHandler::getInstance()->
													GetItemInfo(ptr->GetCurrencyItem()).Name;

			QVector<QVariant> data;
			data << "Currency Item" << txtwithid.str().c_str();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), idx.parent()), _itemNameList);	

			}


			// add items
			{
				QVector<QVariant> data;
				data << "Item list" << "";
				QModelIndex idx = _objectmodel->AppendRow(data, parent, true);	

				const LbaNet::ItemsMap & itemsM = ptr->GetItems();
				LbaNet::ItemsMap::const_iterator ititem = itemsM.begin();
				LbaNet::ItemsMap::const_iterator enditem = itemsM.end();
				for(; ititem != enditem; ++ititem)
				{
					std::stringstream txtwithid;
					txtwithid<<ititem->second.Info.Id<<": "
						<<InventoryItemHandler::getInstance()->GetItemInfo(ititem->second.Info.Id).Name;

					QVector<QVariant> datait;
					datait << "Item" << txtwithid.str().c_str();
					QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	

					//add price
					{
						QVector<QVariant> datachild;
						datachild << "Price" << ititem->second.Info.BuyPrice;
						QModelIndex idx1 = _objectmodel->AppendRow(datachild, idxit);	
					}

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _itemNameList);	
				}

				// add new item
				QVector<QVariant> datait;
				datait << "Item" << "Add item...";
				QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	
				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _itemNameList);	
			
			
				_uieditor.treeView_object->setExpanded(idx, true); // expand 
			}
		}
		return;
	}

	
	if(actiontype == "CutMapAction")
	{
		CutMapAction* ptr = static_cast<CutMapAction*>(action);
		{
			QVector<QVariant> data;
			data << "Y" << (double)ptr->GetY();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		return;
	}
		
	if(actiontype == "PlaySoundAction")
	{
		PlaySoundAction* ptr = static_cast<PlaySoundAction*>(action);
		{
			QVector<QVariant> data;
			data << "Sound path" << ptr->GetSoundPath().c_str();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
			_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, idx.row(), parent), "Select an sound file", "Sound", "Sound Files (*.mp3 *.midi *.Ogg)");
		}

		{
			QVector<QVariant> data;
			data << "play to everyone" << ptr->GetToEveryone();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		return;
	}
		
	if(actiontype == "SetFlagAction")
	{
		SetFlagAction* ptr = static_cast<SetFlagAction*>(action);
		{
			QVector<QVariant> data;
			data << "Flag name" << ptr->GetFlagName().c_str();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		{
			QVector<QVariant> data;
			data << "Value" << ptr->GetValue();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		return;
	}
		
	if(actiontype == "ShoutTextAction")
	{
		ShoutTextAction* ptr = static_cast<ShoutTextAction*>(action);
		{
			std::string txt = Localizer::getInstance()->GetText(Localizer::Map, ptr->GetTextId());
			std::stringstream txttmp;
			txttmp<<ptr->GetTextId()<<": "<<txt;

			QVector<QVariant> data;
			data << "Text" << QString::fromUtf8(txttmp.str().c_str());
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 2, parent), _text_mapNameList);

		{
			QVector<QVariant> data;
			data << "Text size" << (double)ptr->GetTextSize();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		{
			QVector<QVariant> data;
			data << "Text colorR" << (double)ptr->GetColorR();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		{
			QVector<QVariant> data;
			data << "Text colorG" << (double)ptr->GetColorG();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		{
			QVector<QVariant> data;
			data << "Text colorB" << (double)ptr->GetColorB();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		return;
	}
	
	if(actiontype == "PlayVideoAction")
	{
		PlayVideoAction* ptr = static_cast<PlayVideoAction*>(action);
		{
			QVector<QVariant> data;
			data << "Video path" << ptr->GetVideoPath().c_str();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
			_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, idx.row(), parent), "Select an video file", "Video", "Video Files (*.avi *.mkv *.mpg *.mpeg *.wmv)");

		}
		return;
	}
	
	if(actiontype == "DisplayHolomapAction")
	{
		DisplayHolomapAction* ptr = static_cast<DisplayHolomapAction*>(action);
		{
			QVector<QVariant> data;
			data << "Mode" << (int)ptr->GetMode();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}
		{
			QVector<QVariant> data;
			data << "HoloId" << (int)ptr->GetHolomapId();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}

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
				long spid = SharedDataHandler::getInstance()->GetSpawnId(mapname, spawning);


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
						_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 3, parentIdx), it->second);

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
							SelectAction(ptrtmp.get(), curidx);

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
							SelectAction(ptrtmp.get(), curidx);

							_uieditor.treeView_object->setExpanded(curidx, true); // expand 
						}

					}
				}



				// need to save as something changed
				SetModified();

				return;
			}


			if(category == "OpenContainerAction")
			{
				// get info
				long timer = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toFloat();

				// created modified action and replace old one
				OpenContainerAction* modifiedact = (OpenContainerAction*)ptr;
				modifiedact->SetTimeToReset(timer);


				QModelIndex itemparent = _objectmodel->GetIndex(0, 3, parentIdx);
				int curridx = 0;

				//take care of the items
				std::vector<ContainerItemGroupElement> &items = modifiedact->GetItems();
				std::vector<ContainerItemGroupElement>::iterator itit = items.begin();
				for(;itit != items.end(); ++itit)
				{
					QModelIndex childidx = _objectmodel->GetIndex(0, curridx, itemparent);
					std::string id = _objectmodel->data(_objectmodel->GetIndex(1, curridx, itemparent))
																			.toString().toAscii().data();
					++curridx;

					// need to save as something changed
					SetModified();


					if(id == "No item")
					{
						// need to remove the item
						items.erase(itit);

						_objectmodel->Clear(parentIdx);
						SelectAction(modifiedact, parentIdx);
						return;
					}

					std::string tmp = id.substr(0, id.find(":"));
					itit->Id = atol(tmp.c_str());
					itit->Min = _objectmodel->data(_objectmodel->GetIndex(1, 0, childidx)).toInt();
					itit->Max = _objectmodel->data(_objectmodel->GetIndex(1, 1, childidx)).toInt();
					itit->Probability = _objectmodel->data(_objectmodel->GetIndex(1, 2, childidx)).toFloat();
					itit->Group = _objectmodel->data(_objectmodel->GetIndex(1, 3, childidx)).toInt();
				}

				QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent);
				std::string id = _objectmodel->data(childidx).toString().toAscii().data();
				if(id != "Add item...")
				{
					if(id == "No item")
					{
						_objectmodel->setData(childidx, "Add item...");
						return;
					}
					else
					{
						// add new item
						std::string tmp = id.substr(0, id.find(":"));
						long itmid = atol(tmp.c_str());

						// cant add 2 times the same item
						if(modifiedact->ItemExist(itmid))
						{
							_objectmodel->setData(childidx, "Add item...");
							return;
						}
						else
						{
							ContainerItemGroupElement newitem(itmid, 1, 1, 1, -1);
							items.push_back(newitem);

							_objectmodel->Clear(parentIdx);
							SelectAction(modifiedact, parentIdx);

							// need to save as something changed
							SetModified();
						}
					}
				}

				return;
			}


			if(category == "SendSignalAction")
			{
				// get info
				long aid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toInt();
				int signal = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toInt();

				// created modified action and replace old one
				SendSignalAction* modifiedact = (SendSignalAction*)ptr;
				modifiedact->SetActorId(aid);
				modifiedact->SetSignal(signal);


				// need to save as something changed
				SetModified();

				return;
			}


			if(category == "OpenDoorAction")
			{
				// get info
				long aid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toInt();

				// created modified action and replace old one
				SendSignalAction* modifiedact = (SendSignalAction*)ptr;
				modifiedact->SetActorId(aid);

				// need to save as something changed
				SetModified();

				return;
			}


			if(category == "CloseDoorAction")
			{
				// get info
				long aid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toInt();

				// created modified action and replace old one
				SendSignalAction* modifiedact = (SendSignalAction*)ptr;
				modifiedact->SetActorId(aid);

				// need to save as something changed
				SetModified();

				return;
			}

			if(category == "AddRemoveItemAction")
			{
				// get info
				std::string itid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();
				itid = itid.substr(0, itid.find(":"));
				long id = atol(itid.c_str());
				
				int number = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toInt();
				std::string informtype = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toString().toAscii().data();

				// created modified action and replace old one
				AddRemoveItemAction* modifiedact = (AddRemoveItemAction*)ptr;
				modifiedact->SetItemId(id);
				modifiedact->SetNumber(number);
				modifiedact->SetInformClientTypeString(informtype);

				// need to save as something changed
				SetModified();

				return;
			}


			if(category == "HurtAction")
			{		
				float value = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toFloat();
				bool life = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toBool();

				// created modified action and replace old one
				HurtAction* modifiedact = (HurtAction*)ptr;
				modifiedact->SetHurtValue(value);
				modifiedact->HurtLifeOrMana(life);
				modifiedact->SetAnimationString(_objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toString().toAscii().data());

				// need to save as something changed
				SetModified();

				return;
			}

			if(category == "MultiAction")
			{	
				MultiAction* modifiedact = (MultiAction*)ptr;

				QModelIndex itemparent = _objectmodel->GetIndex(0, 2, parentIdx);
				int curridx = 0;

				//take care of the items
				std::vector<ActionBasePtr> &items = modifiedact->GetActions();
				std::vector<ActionBasePtr>::iterator itit = items.begin();
				for(;itit != items.end(); ++itit)
				{
					std::string oldaction = GetActionType(*itit);

					std::string action = _objectmodel->data(_objectmodel->GetIndex(1, curridx, itemparent)).toString().toAscii().data();

					if(oldaction != action)
					{
						if(action == "No")
						{
							modifiedact->RemoveAction(*itit);

							_objectmodel->Clear(parentIdx);
							SelectAction(modifiedact, parentIdx);
						}
						else
						{
							ActionBasePtr ptrtmp = CreateAction(action);
							modifiedact->ReplaceAction(*itit, ptrtmp);

							QModelIndex curidx = _objectmodel->GetIndex(0, curridx, itemparent);
							_objectmodel->Clear(curidx);
							if(ptrtmp)
							{
								SelectAction(ptrtmp.get(), curidx);
								_uieditor.treeView_object->setExpanded(curidx, true); // expand 
							}
						}
					}

					++curridx;
				}

				QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent);
				std::string action = _objectmodel->data(childidx).toString().toAscii().data();
				if(action != "Add new...")
				{
					if(action == "No")
					{
						_objectmodel->setData(childidx, "Add new...");
						return;
					}
					else
					{
						ActionBasePtr ptrtmp = CreateAction(action);
						if(ptrtmp)
						{
							modifiedact->AddAction(ptrtmp);

							//QModelIndex curidx = _objectmodel->GetIndex(0, curridx, itemparent);
							//SelectAction(ptrtmp.get(), curidx);
							//_uieditor.treeView_object->setExpanded(curidx, true); // expand 

							_objectmodel->Clear(parentIdx);
							SelectAction(modifiedact, parentIdx);
						}
						else
						{
							_objectmodel->setData(childidx, "Add new...");
							return;
						}
					}
				}


				// need to save as something changed
				SetModified();

				return;
			}

			if(category == "RandomAction")
			{	
				RandomAction* modifiedact = (RandomAction*)ptr;

				QModelIndex itemparent = _objectmodel->GetIndex(0, 2, parentIdx);
				int curridx = 0;

				//take care of the items
				std::vector<ActionBasePtr> &items = modifiedact->GetActions();
				std::vector<ActionBasePtr>::iterator itit = items.begin();
				for(;itit != items.end(); ++itit)
				{
					std::string oldaction = GetActionType(*itit);

					std::string action = _objectmodel->data(_objectmodel->GetIndex(1, curridx, itemparent)).toString().toAscii().data();

					if(oldaction != action)
					{
						if(action == "No")
						{
							modifiedact->RemoveAction(*itit);

							_objectmodel->Clear(parentIdx);
							SelectAction(modifiedact, parentIdx);
						}
						else
						{
							ActionBasePtr ptrtmp = CreateAction(action);
							modifiedact->ReplaceAction(*itit, ptrtmp);

							QModelIndex curidx = _objectmodel->GetIndex(0, curridx, itemparent);
							_objectmodel->Clear(curidx);
							if(ptrtmp)
							{
								SelectAction(ptrtmp.get(), curidx);
								_uieditor.treeView_object->setExpanded(curidx, true); // expand 
							}
						}
					}

					++curridx;
				}

				QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent);
				std::string action = _objectmodel->data(childidx).toString().toAscii().data();
				if(action != "Add new...")
				{
					if(action == "No")
					{
						_objectmodel->setData(childidx, "Add new...");
						return;
					}
					else
					{
						ActionBasePtr ptrtmp = CreateAction(action);
						if(ptrtmp)
						{
							modifiedact->AddAction(ptrtmp);

							//QModelIndex curidx = _objectmodel->GetIndex(0, curridx, itemparent);
							//SelectAction(ptrtmp.get(), curidx);
							//_uieditor.treeView_object->setExpanded(curidx, true); // expand 

							_objectmodel->Clear(parentIdx);
							SelectAction(modifiedact, parentIdx);
						}
						else
						{
							_objectmodel->setData(childidx, "Add new...");
							return;
						}
					}
				}


				// need to save as something changed
				SetModified();

				return;
			}




			if(category == "SwitchAction")
			{
				// created modified action and replace old one
				SwitchAction* modifiedact = (SwitchAction*)ptr;

				// check actor part
				{
					long actor = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toInt();
					std::string model = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toString().toAscii().data();

					modifiedact->SetSwitchModel(model);

					long oldactid = modifiedact->GetActorId();
					if(oldactid != actor)
					{
						modifiedact->SetActorId(actor);

						std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator ita = _Actors.find(actor);
						if(ita != _Actors.end() && ita->second->GetActorInfo().DisplayDesc.TypeRenderer == RenderSprite)
						{
							_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, 3, parentIdx), "Select an image", "Sprites", "Image Files (*.png *.bmp *.jpg *.gif)");
						}
						else
						{
							_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, 3, parentIdx), "Select a model file", "Models", "Model Files (*.osg *.osgb *.osgt)");
						}
					}

				}


				// get id associated to actions
				std::string action1 = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toString().toAscii().data();
				std::string action2 = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toString().toAscii().data();

				//action 1
				{
					std::string curract = GetActionType(modifiedact->GetActionTrue());

					if(action1 != curract)
					{
						ActionBasePtr ptrtmp = CreateAction(action1);
						modifiedact->SetActionTrue(ptrtmp);

						QModelIndex curidx = _objectmodel->GetIndex(0, 4, parentIdx);
						_objectmodel->Clear(curidx);
						if(ptrtmp)
						{
							SelectAction(ptrtmp.get(), curidx);

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

						QModelIndex curidx = _objectmodel->GetIndex(0, 5, parentIdx);
						_objectmodel->Clear(curidx);
						if(ptrtmp)
						{
							SelectAction(ptrtmp.get(), curidx);

							_uieditor.treeView_object->setExpanded(curidx, true); // expand 
						}

					}
				}



				// need to save as something changed
				SetModified();

				return;
			}


			if(category == "StartQuestAction")
			{
				// get info
				long qid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toInt();

				// created modified action and replace old one
				StartQuestAction* modifiedact = (StartQuestAction*)ptr;
				modifiedact->SetQuestId(qid);

				// need to save as something changed
				SetModified();

				return;
			}

			if(category == "FinishQuestAction")
			{
				// get info
				long qid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toInt();

				// created modified action and replace old one
				FinishQuestAction* modifiedact = (FinishQuestAction*)ptr;
				modifiedact->SetQuestId(qid);

				// need to save as something changed
				SetModified();

				return;
			}


			if(category == "OpenShopAction")
			{
				// get info
				std::string curidstr =_objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();
				curidstr = curidstr.substr(0, curidstr.find(":"));

				// created modified action and replace old one
				OpenShopAction* modifiedact = (OpenShopAction*)ptr;
				modifiedact->SetCurrencyItem(atol(curidstr.c_str()));

				// need to save as something changed
				SetModified();

				QModelIndex itemparent = _objectmodel->GetIndex(0, 3, parentIdx);
				int curridx = 0;

				//take care of the items
				const LbaNet::ItemsMap &items = modifiedact->GetItems();
				LbaNet::ItemsMap::const_iterator itit = items.begin();
				for(;itit != items.end(); ++itit)
				{
					QModelIndex childidx = _objectmodel->GetIndex(0, curridx, itemparent);
					std::string id = _objectmodel->data(_objectmodel->GetIndex(1, curridx, itemparent))
																			.toString().toAscii().data();
					++curridx;

					if(id == "No item")
					{
						// need to remove the item
						modifiedact->RemoveItem(itit->first);

						_objectmodel->Clear(parentIdx);
						SelectAction(modifiedact, parentIdx);
						return;
					}

					std::string tmp = id.substr(0, id.find(":"));
					long itmId = atol(tmp.c_str());
					int price = _objectmodel->data(_objectmodel->GetIndex(1, 0, childidx)).toInt();
					modifiedact->AddItem(itmId, price);
				}

				QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent);
				QModelIndex childidx0 = _objectmodel->GetIndex(0, curridx, itemparent);
				std::string id = _objectmodel->data(childidx).toString().toAscii().data();
				if(id != "Add item...")
				{
					if(id == "No item")
					{
						_objectmodel->setData(childidx, "Add item...");
						return;
					}
					else
					{
						// add new item
						std::string tmp = id.substr(0, id.find(":"));
						LbaNet::ItemInfo iteminfo = modifiedact->AddItemR(atol(tmp.c_str()), -1);

						//add price
						{
							QVector<QVariant> datachild;
							datachild << "Price" << iteminfo.BuyPrice;
							_objectmodel->AppendRow(datachild, childidx0);	
						}

						// add new item
						QVector<QVariant> datait;
						datait << "Item" << "Add item...";
						QModelIndex idxit = _objectmodel->AppendRow(datait, itemparent);	
						_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _itemNameList);	
					}
				}

				return;
			}


			if(category == "CutMapAction")
			{
				// get info
				float Y = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toFloat();

				// created modified action and replace old one
				CutMapAction* modifiedact = (CutMapAction*)ptr;
				modifiedact->SetY(Y);

				// need to save as something changed
				SetModified();

				return;
			}

			if(category == "PlaySoundAction")
			{
				// get info
				std::string spath = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();
				bool everyone = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toFloat();

				// created modified action and replace old one
				PlaySoundAction* modifiedact = (PlaySoundAction*)ptr;
				modifiedact->SetSoundPath(spath);
				modifiedact->SetToEveryone(everyone);

				// need to save as something changed
				SetModified();

				return;
			}

			if(category == "SetFlagAction")
			{
				// get info
				std::string flagn = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();
				int value = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toInt();

				// created modified action and replace old one
				SetFlagAction* modifiedact = (SetFlagAction*)ptr;
				modifiedact->SetFlagName(flagn);
				modifiedact->SetValue(value);

				// need to save as something changed
				SetModified();

				return;
			}

			if(category == "ShoutTextAction")
			{
				// get info
				std::string text = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();
				std::string tmp = text.substr(0, text.find(":"));
				long textid = atol(tmp.c_str());

				float tsize = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toFloat();
				float colorR = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toFloat();
				float colorG = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toFloat();
				float colorB = _objectmodel->data(_objectmodel->GetIndex(1, 6, parentIdx)).toFloat();

				// created modified action and replace old one
				ShoutTextAction* modifiedact = (ShoutTextAction*)ptr;
				modifiedact->SetTextId(textid);
				modifiedact->SetTextSize(tsize);
				modifiedact->SetColorR(colorR);
				modifiedact->SetColorG(colorG);
				modifiedact->SetColorB(colorB);


				// need to save as something changed
				SetModified();

				return;
			}

			if(category == "PlayVideoAction")
			{
				// get info
				std::string spath = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();

				// created modified action and replace old one
				PlayVideoAction* modifiedact = (PlayVideoAction*)ptr;
				modifiedact->SetVideoPath(spath);


				// need to save as something changed
				SetModified();

				return;
			}
			
		
			if(category == "DisplayHolomapAction")
			{
				// get info
				int mode = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toFloat();
				long holoid = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toFloat();

				// created modified action and replace old one
				DisplayHolomapAction* modifiedact = (DisplayHolomapAction*)ptr;
				modifiedact->SetMode(mode);
				modifiedact->SetHolomapId(holoid);


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
		// remove from list
		_triggerNameList->RemoveData(it->second->GetName().c_str());

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
					SelectAction(actptr.get(), idx);
			}

			//action 2
			{
				ActionBasePtr actptr = ptr->GetAction2();
				std::string acttype = GetActionType(actptr);

				QVector<QVariant> data;
				data << "Action On Leave" << acttype.c_str();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);
				
				if(actptr)
					SelectAction(actptr.get(), idx);
			}

			//action 3
			{
				ActionBasePtr actptr = ptr->GetAction3();
				std::string acttype = GetActionType(actptr);

				QVector<QVariant> data;
				data << "Action On Stay" << acttype.c_str();
				QModelIndex idx = _objectmodel->AppendRow(data, parent);
				
				if(actptr)
					SelectAction(actptr.get(), idx);
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

			{
				QVector<QVariant> data;
				data << "Activation Frequency (sec)" << ptr-> GetStayUpdateFrequency();
				QModelIndex idx2 = _objectmodel->AppendRow(data, parent);

				// add tootlip
				_objectmodel->setTooltip(idx2, "Frequency in second the Action on Stay is executed");
			}

			{
				QVector<QVariant> data;
				data << "Activate On Jump" << ptr->GetActivateOnJump();
				_objectmodel->AppendRow(data, parent);
			}

			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _actiontypeList);
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 5, parent), _actiontypeList);
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 6, parent), _actiontypeList);


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
					SelectAction(actptr.get(), idx);
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

			{
				QVector<QVariant> data;
				data << "Play animation" << ptr->GetPlayAnimation();
				_objectmodel->AppendRow(data, parent);
			}

			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _actiontypeList);
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 11, parent), _actormodeList);
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 12, parent), _actormodeList);

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
					SelectAction(actptr.get(), idx);
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

			{
				QVector<QVariant> data;
				data << "Play animation" << ptr->GetPlayAnimation();
				_objectmodel->AppendRow(data, parent);
			}

			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _actiontypeList);
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 9, parent), _actormodeList);
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 10, parent), _actormodeList);

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
					SelectAction(actptr.get(), idx);
			}

			{
				QVector<QVariant> data;
				data << "Time in ms" << (int)ptr->GetTimeinMs();
				_objectmodel->AppendRow(data, parent);
			}


			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _actiontypeList);

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
		std::string action3 = _objectmodel->data(_objectmodel->GetIndex(1, 6, parentIdx)).toString().toAscii().data();
		
		triggerinfo.CheckPlayers = _objectmodel->data(_objectmodel->GetIndex(1, 7, parentIdx)).toBool();
		triggerinfo.CheckNpcs = _objectmodel->data(_objectmodel->GetIndex(1, 8, parentIdx)).toBool();
		triggerinfo.CheckMovableObjects = _objectmodel->data(_objectmodel->GetIndex(1, 9, parentIdx)).toBool();
		float posX = _objectmodel->data(_objectmodel->GetIndex(1, 10, parentIdx)).toFloat();
		float posY = _objectmodel->data(_objectmodel->GetIndex(1, 11, parentIdx)).toFloat();
		float posZ = _objectmodel->data(_objectmodel->GetIndex(1, 12, parentIdx)).toFloat();
		float sizeX = _objectmodel->data(_objectmodel->GetIndex(1, 13, parentIdx)).toFloat();
		float sizeY = _objectmodel->data(_objectmodel->GetIndex(1, 14, parentIdx)).toFloat();
		float sizeZ = _objectmodel->data(_objectmodel->GetIndex(1, 15, parentIdx)).toFloat();
		if(sizeX < 0.0001)
			sizeX = 0.0001;
		if(sizeY < 0.0001)
			sizeY = 0.0001;
		if(sizeZ < 0.0001)
			sizeZ = 0.0001;

		bool multicactiv = _objectmodel->data(_objectmodel->GetIndex(1, 16, parentIdx)).toBool();
		double frequency = _objectmodel->data(_objectmodel->GetIndex(1, 17, parentIdx)).toDouble();
		bool activjump = _objectmodel->data(_objectmodel->GetIndex(1, 18, parentIdx)).toBool();


		// created modified action and replace old one
		ZoneTrigger* modifiedtrig = (ZoneTrigger*)_triggers[id].get();
		modifiedtrig->SetPosition(posX, posY, posZ);
		modifiedtrig->SetTriggerInfo(triggerinfo);
		modifiedtrig->SetSize(sizeX, sizeY, sizeZ);
		modifiedtrig->SetMultiActivation(multicactiv);
		modifiedtrig->SetStayUpdateFrequency(frequency);
		modifiedtrig->SetActivateOnJump(activjump);

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
					SelectAction(ptrtmp.get(), curidx);

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
					SelectAction(ptrtmp.get(), curidx);

					_uieditor.treeView_object->setExpanded(curidx, true); // expand 
				}

			}
		}

		//action 3
		{
			std::string curract = GetActionType(modifiedtrig->GetAction3());

			if(action3 != curract)
			{
				ActionBasePtr ptrtmp = CreateAction(action3);
				modifiedtrig->SetAction3(ptrtmp);

				QModelIndex curidx = _objectmodel->GetIndex(0, 6, parentIdx);
				_objectmodel->Clear(curidx);
				if(ptrtmp)
				{
					SelectAction(ptrtmp.get(), curidx);

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

		modifiedtrig->SetPlayAnimation(_objectmodel->data(_objectmodel->GetIndex(1, 13, parentIdx)).toBool());

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
					SelectAction(ptrtmp.get(), curidx);

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

		modifiedtrig->SetPlayAnimation(_objectmodel->data(_objectmodel->GetIndex(1, 11, parentIdx)).toBool());

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
					SelectAction(ptrtmp.get(), curidx);

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
					SelectAction(ptrtmp.get(), curidx);

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
	{
		ShowHideMapInfo(true);
		LbaNet::PlayerPosition ppos = SharedDataHandler::getInstance()->GetSpawnPos(mapname, spawningid, 0);
		EditorUpdateBasePtr update = new EditorTeleportPlayerEvent(1, ppos);
		SharedDataHandler::getInstance()->EditorUpdate(_uieditor.label_mapname->text().toAscii().data(), update);
	}
}

/***********************************************************
change current map to new map
***********************************************************/
void EditorHandler::ChangeMap(const std::string & mapname, const std::string SpawnName)
{
	if(SaveMapBeforeQuit())
	{
		ShowHideMapInfo(true);
		LbaNet::PlayerPosition ppos = SharedDataHandler::getInstance()->GetSpawnPos(mapname, SpawnName, 0);
		EditorUpdateBasePtr update = new EditorTeleportPlayerEvent(1, ppos);
		SharedDataHandler::getInstance()->EditorUpdate(_uieditor.label_mapname->text().toAscii().data(), update);
	}
}


/***********************************************************
save current map to file
***********************************************************/
void EditorHandler::SaveMap(const std::string & filename)
{
	std::ofstream file(filename.c_str());
	file<<"function InitMap(environment)"<<std::endl;

	// save spawns
	std::map<long, boost::shared_ptr<Spawn> >::iterator its= _spawns.begin();
	std::map<long, boost::shared_ptr<Spawn> >::iterator ends = _spawns.end();
	for(;its != ends; ++its)
		its->second->SaveToLuaFile(file);
	

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
save holomap to file
***********************************************************/
void EditorHandler::SaveHoloMap(const std::string & filename)
{
	std::ofstream file(filename.c_str());
	file<<"function InitHolomap(environment)"<<std::endl;

	// save holomaps
	{
		std::map<long, HolomapPtr> &_holomapptr = HolomapHandler::getInstance()->GetHolomaps();
		std::map<long, HolomapPtr>::iterator itt = _holomapptr.begin();
		std::map<long, HolomapPtr>::iterator endt = _holomapptr.end();
		for(;itt != endt; ++itt)
			itt->second->SaveToLuaFile(file);
	}
	file<<std::endl<<std::endl;

	// save holomaps locations
	{
		std::map<long, HolomapLocationPtr> &_holomapptr = HolomapHandler::getInstance()->GetHolomapLocs();
		std::map<long, HolomapLocationPtr>::iterator itt = _holomapptr.begin();
		std::map<long, HolomapLocationPtr>::iterator endt = _holomapptr.end();
		for(;itt != endt; ++itt)
			itt->second->SaveToLuaFile(file);
	}
	file<<std::endl<<std::endl;

	// save holomaps paths
	{
		std::map<long, HolomapTravelPathPtr> &_holomapptr = HolomapHandler::getInstance()->GetHolomapPaths();
		std::map<long, HolomapTravelPathPtr>::iterator itt = _holomapptr.begin();
		std::map<long, HolomapTravelPathPtr>::iterator endt = _holomapptr.end();
		for(;itt != endt; ++itt)
			itt->second->SaveToLuaFile(file);
	}

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
WorldStartingScriptChanged
***********************************************************/
void EditorHandler::WorldStartingScriptChanged()
{
	QString descs = _uieditor.lineEdit_startingscript->text();
	_winfo.StartingInfo.StartingScript = descs.toUtf8().data();
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

			boost::shared_ptr<Spawn> spwn = SharedDataHandler::getInstance()->GetSpawn(_winfo.StartingInfo.StartingMap, _winfo.StartingInfo.SpawningId);
			if(spwn)
			{
				int index = _uieditor.comboBox_startingspawning->findText(spwn->GetName().c_str());
				if(index >= 0)
					_uieditor.comboBox_startingspawning->setCurrentIndex(index);
			}	
			else
			{
				spwn = SharedDataHandler::getInstance()->GetSpawn(_winfo.StartingInfo.StartingMap, -1);
				if(spwn)
				{
					_winfo.StartingInfo.SpawningId = spwn->GetId();
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
void EditorHandler::RefreshSimpleActorModelName(LbaNet::ModelInfo & dinfo)
{
	UpdateModelName(_actorModelNameList);
	if(!_actorModelNameList->DataExist(dinfo.ModelName.c_str()))
		dinfo.ModelName = _actorModelNameList->GetFirstdata().toAscii().data();

	RefreshSimpleActorModelOutfit(dinfo);
}
void EditorHandler::RefreshSimpleActorModelOutfit(LbaNet::ModelInfo & dinfo)
{
	UpdateModelOutfit(dinfo.ModelName, _actorModelOutfitList);
	if(!_actorModelOutfitList->DataExist(dinfo.Outfit.c_str()))
		dinfo.Outfit = _actorModelOutfitList->GetFirstdata().toAscii().data();

	RefreshSimpleActorModelWeapon(dinfo);
}
void EditorHandler::RefreshSimpleActorModelWeapon(LbaNet::ModelInfo & dinfo)
{
	UpdateModelWeapon(dinfo.ModelName, dinfo.Outfit, _actorModelWeaponList);
	if(!_actorModelWeaponList->DataExist(dinfo.Weapon.c_str()))
		dinfo.Weapon = _actorModelWeaponList->GetFirstdata().toAscii().data();

	RefreshSimpleActorModelMode(dinfo);
}
void EditorHandler::RefreshSimpleActorModelMode(LbaNet::ModelInfo & dinfo)
{
	UpdateModelMode(dinfo.ModelName, dinfo.Outfit, dinfo.Weapon, _actorModelModeList);
	if(!_actorModelModeList->DataExist(dinfo.Mode.c_str()))
		dinfo.Mode = _actorModelModeList->GetFirstdata().toAscii().data();
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


		if(actor)
		{
			std::string ptype = _objectmodel->data(_objectmodel->GetIndex(1, 6, parentIdx)).toString().toAscii().data();
			if(ptype == "Box")
			{
				int resWeaponType;
				ModelSize size;
				int res = Lba1ModelMapHandler::getInstance()-> GetModelExtraInfo(modelname,
										outfit,	weapon,	mode, resWeaponType, size);

				if(res >= 0)
				{
					float csx = _objectmodel->data(_objectmodel->GetIndex(1, 14, parentIdx)).toFloat();
					float csy = _objectmodel->data(_objectmodel->GetIndex(1, 15, parentIdx)).toFloat();
					float csz = _objectmodel->data(_objectmodel->GetIndex(1, 16, parentIdx)).toFloat();

					if(csx != size.X)
						_objectmodel->setData(_objectmodel->GetIndex(1, 14, parentIdx), size.X);
					
					if(csy != size.Y)
						_objectmodel->setData(_objectmodel->GetIndex(1, 15, parentIdx), size.Y);

					if(csz != size.Z)
						_objectmodel->setData(_objectmodel->GetIndex(1, 16, parentIdx), size.Z);
				}
			}

			//update color
			Lba1ModelMapHandler::getInstance()->GetModelColor(modelname, outfit, weapon, mode, 
											actor->initpolycolors, actor->initspherecolors, actor->initlinecolors);

			actor->currentpolycolors = actor->initpolycolors;
			actor->currentspherecolors = actor->initspherecolors;
			actor->currentlinecolors = actor->initlinecolors;

			actor->ClearColorSwap();
		}
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
	long spid = SharedDataHandler::getInstance()->GetSpawnId(_winfo.StartingInfo.StartingMap, spname);

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
	newmapinfo.Repeat = 0;
	newmapinfo.HurtFallFactor = 2;

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
	boost::shared_ptr<Spawn> newspawn(new Spawn(0));
	newspawn->SetName("DefaultSpawn");
	newspawn->SetPosX(0);
	newspawn->SetPosY(0);
	newspawn->SetPosZ(0);
	newspawn->SetRotation(0);
	newspawn->SetForceRotation(true);
	newspawn->SetActionAtArrival(ActionBasePtr());

	// then inform the server
	EditorUpdateBasePtr update = new UpdateEditor_AddOrModSpawning(newspawn);
	SharedDataHandler::getInstance()->EditorUpdate(mapname, update);

	// add name to list
	AddSpawningName(mapname, "DefaultSpawn");

	// save map file with new spawning
	{
	std::ofstream file(("./Data/Worlds/" + _winfo.Description.WorldName + "/Lua/" + mapname + "_server.lua").c_str());
	file<<"function InitMap(environment)"<<std::endl;
	newspawn->SaveToLuaFile(file);
	file<<"end"<<std::endl;
	file.close();
	}

	// add a default spawning
	//long spid = AddOrModSpawning(mapname, , 0, 0, 0, 0, true, ActionBasePtr(), 0);
	//SaveWorldAction(mapname);
	ChangeMap(mapname, 0);
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
			_winfo.Maps[mapname].Description = descstring;

			//QStringList data;
			//data << mapname.c_str() << descstring.c_str();
			//_maplistmodel->AddOrUpdateRow(_currmapidx, data);



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
		_winfo.Maps[mapname].LinkedHoloLocation = _uieditor.spinBox_lhololocid->value();

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
	TpDialogMapChanged(0);
	_addtpdialog->setWindowTitle("Add Teleport");
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

		if(SharedDataHandler::getInstance()->RemoveTeleport(tpid))
		{
			// remove row from table
			_tplistmodel->removeRows(indexes[0].row(), 1);

			SetModified();
			ClearObjectIfSelected("Teleport", tpid);
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
		SelectTeleport(id);
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

	long spid = SharedDataHandler::getInstance()->GetSpawnId(mapname, spawnname);
	long tpid = (++_currteleportidx);


	QStringList data;
	data << tpname.c_str() << mapname.c_str() << spawnname.c_str();
	_tplistmodel->AddOrUpdateRow(tpid, data);


	boost::shared_ptr<TeleportDef> newtp(new TeleportDef(tpid));
	newtp->SetName(tpname);
	newtp->SetMapName(mapname);
	newtp->SetSpawn(spid);
	SharedDataHandler::getInstance()->AddTeleport(newtp);

	SetModified();
	SelectTeleport(tpid);
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
	const std::map<long, boost::shared_ptr<TeleportDef> > &tpseq = SharedDataHandler::getInstance()->GetTpList();
	std::map<long, boost::shared_ptr<TeleportDef> >::const_iterator it = tpseq.begin();
	std::map<long, boost::shared_ptr<TeleportDef> >::const_iterator end = tpseq.end();
	for(; it != end; ++it)
	{
		if(it->second->GetMapName() == mapname)
		{
			if(it->second->GetSpawn() == spwid)
			{
				QStringList data;
				data << it->second->GetName().c_str() << mapname.c_str() << spname.c_str();
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
	FileUtil::CreateNewDirectory("./Data/Worlds/" + wname);
	FileUtil::CreateNewDirectory("./Data/Worlds/" + wname + "/Lua");
	FileUtil::CreateNewDirectory("./Data/Worlds/" + wname + "/Models");
	FileUtil::CreateNewDirectory("./Data/Worlds/" + wname + "/Texts");
	FileUtil::CreateNewDirectory("./Data/Worlds/" + wname + "/Voices");
	FileUtil::CreateNewDirectory("./Data/Worlds/" + wname + "/InventoryImages");
	FileUtil::CreateNewDirectory("./Data/Worlds/" + wname + "/Sprites");
	FileUtil::CreateNewDirectory("./Data/Worlds/" + wname + "/Music");
	FileUtil::CreateNewDirectory("./Data/Worlds/" + wname + "/Grid");
	FileUtil::CreateNewDirectory("./Data/Worlds/" + wname + "/AI");
	FileUtil::CreateNewDirectory("./Data/Worlds/" + wname + "/Sound");
	FileUtil::CreateNewDirectory("./Data/Worlds/" + wname + "/Video");

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
		filelua<<"-- Environment is a pointer used to access the server class (see documentation for further information)"<<std::endl<<std::endl;

		filelua<<"function ExampleServerFct(ObjectType, ObjectId, Arguments, Environment)"<<std::endl;
		filelua<<"	Environment:DisplayTextAction(ObjectType, ObjectId, 0)"<<std::endl;
		filelua<<"end"<<std::endl<<std::endl<<std::endl;
		
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
		filelua<<"-- Environment is a pointer used to access the server class (see documentation for further information)"<<std::endl<<std::endl;

		filelua<<"function ExampleClientFct(ScriptId, Environment)"<<std::endl;
		filelua<<"	LadderPos = LbaVec3(42, 7, 9)"<<std::endl;
		filelua<<"	ActorGoUpLadder(ScriptId, -1, LadderPos, 10, 0, Environment)"<<std::endl;
		filelua<<"end"<<std::endl<<std::endl<<std::endl;
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
	ainfo.ExcludeFromNavMesh = false;
	ainfo.ExtraInfo.Name = "";
	ainfo.ExtraInfo.NameColorR = 1.0;
	ainfo.ExtraInfo.NameColorG = 1.0;
	ainfo.ExtraInfo.NameColorB = 1.0;

	bool door = false;
	bool npc = false;


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
			ainfo.PhysicDesc.TypePhysO = LbaNet::KynematicAType;
			door = true;
		break;
		case 3:
			ainfo.PhysicDesc.TypePhysO = LbaNet::KynematicAType;
			npc = true;
		break;
		case 4:
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

	ainfo.HitPowerOnTouch = -1;
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
	ainfo.DisplayDesc.UseTransparentMaterial = false;
	ainfo.DisplayDesc.MatAlpha = 1;

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
		ainfo.DisplayDesc.ColorMaterialType = 4;
		ainfo.DisplayDesc.MatAmbientColorR = -0.2;
		ainfo.DisplayDesc.MatAmbientColorG = -0.2;
		ainfo.DisplayDesc.MatAmbientColorB = -0.2;
		ainfo.DisplayDesc.MatDiffuseColorR = 0.4;
		ainfo.DisplayDesc.MatDiffuseColorG = 0.4;
		ainfo.DisplayDesc.MatDiffuseColorB = 0.4;


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


	boost::shared_ptr<ActorHandler> act;
	if(door)
		act = boost::shared_ptr<ActorHandler>(new DoorHandler(ainfo, 0, 0, 0, 0.01, true));
	else
		if(npc)
			act = boost::shared_ptr<ActorHandler>(new NPCHandler(ainfo));
		else
			act = boost::shared_ptr<ActorHandler>(new ActorHandler(ainfo));

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

		_selectedid = id;

		const ActorObjectInfo & ainfo = it->second->GetActorInfo();
		

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
			ConditionBasePtr condptr = ainfo.Condition;

			QVector<QVariant> data;
			data << "Display condition" << GetConditionType(condptr).c_str();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);

			if(condptr)
				SelectCondition(condptr, idx);

			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _conditiontypeList);
		}


		std::string type;
		switch(ainfo.PhysicDesc.TypePhysO)
		{
			case LbaNet::StaticAType:
				type = "Static";
			break;

			case LbaNet::KynematicAType:
				type = it->second->ActorType();
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

			case RenderSphere:
				dtype = "Sphere";
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

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 3, parent), _conditiontypeList);
		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _actortypeList);
		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 5, parent), _actordtypeList);
		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 6, parent), _actorptypeList);		


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

		int index = 11;

		if(ainfo.PhysicDesc.TypeShape != LbaNet::NoShape)
		{
			{
				QVector<QVariant> data;
				data<<"Collidable"<<ainfo.PhysicDesc.Collidable;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
			{
				QVector<QVariant> data;
				data<<"Exclude from Navmesh"<<ainfo.ExcludeFromNavMesh;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
			{
				QVector<QVariant> data;
				data<<"Hurt life on hit"<<(double)ainfo.HitPowerOnTouch;
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

					_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, index, parent), "Select physic file", "Models", "Physic Files (*.phy)");
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

				_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, index, parent), "Select a model file", "Models", "Model Files (*.osg *.osgb *.osgt)");
				++index;
			}

			if(ainfo.DisplayDesc.TypeRenderer == RenderSprite )
			{
				QVector<QVariant> data;
				data<<"Display sprite file"<<ainfo.DisplayDesc.ModelName.c_str();
				_objectmodel->AppendRow(data, parent);
				
				_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, index, parent), "Select an image", "Sprites", "Image Files (*.png *.bmp *.jpg *.gif)");
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
				{
					QVector<QVariant> data1;
					data1<<"Use Billboard"<<ainfo.DisplayDesc.UseBillboard;
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

				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actorModelNameList);
				++index;

				QVector<QVariant> data2;
				data2<<"Display model outfit"<<ainfo.DisplayDesc.Outfit.c_str();
				_objectmodel->AppendRow(data2, parent);
				
				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actorModelOutfitList);
				++index;

				QVector<QVariant> data3;
				data3<<"Display model weapon"<<ainfo.DisplayDesc.Weapon.c_str();
				_objectmodel->AppendRow(data3, parent);
				
				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actorModelWeaponList);
				++index;

				QVector<QVariant> data4;
				data4<<"Display model mode"<<ainfo.DisplayDesc.Mode.c_str();
				_objectmodel->AppendRow(data4, parent);
				
				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actorModelModeList);
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

			// add materials
			{
				QVector<QVariant> data;
				data<<"Use alpha material"<<ainfo.DisplayDesc.UseTransparentMaterial;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
			{
				QVector<QVariant> data;
				data<<"Alpha"<<(double)ainfo.DisplayDesc.MatAlpha;
				_objectmodel->AppendRow(data, parent);
				++index;
			}

			int matcolortype = ainfo.DisplayDesc.ColorMaterialType;
			{
				std::string mattypestring = "Off";
				switch(matcolortype)
				{
					case 1:
						mattypestring = "Ambient";
					break;
					case 2:
						mattypestring = "Diffuse";
					break;
					case 3:
						mattypestring = "Specular";
					break;
					case 4:
						mattypestring = "Emission";
					break;
					case 5:
						mattypestring = "Ambient_And_Diffuse";
					break;
				}
				QVector<QVariant> data;
				data<<"Color material type"<<mattypestring.c_str();
				_objectmodel->AppendRow(data, parent);
					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _materialtypeList);
				++index;	
			}

			if(matcolortype > 0)
			{
				{
				QVector<QVariant> data;
				data<<"Mat Ambient ColorR"<<(double)ainfo.DisplayDesc.MatAmbientColorR;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}
				{
				QVector<QVariant> data;
				data<<"Mat Ambient ColorG"<<(double)ainfo.DisplayDesc.MatAmbientColorG;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}
				{
				QVector<QVariant> data;
				data<<"Mat Ambient ColorB"<<(double)ainfo.DisplayDesc.MatAmbientColorB;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}
				{
				QVector<QVariant> data;
				data<<"Mat Ambient ColorA"<<(double)ainfo.DisplayDesc.MatAmbientColorA;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}

				{
				QVector<QVariant> data;
				data<<"Mat Diffuse ColorR"<<(double)ainfo.DisplayDesc.MatDiffuseColorR;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}
				{
				QVector<QVariant> data;
				data<<"Mat Diffuse ColorG"<<(double)ainfo.DisplayDesc.MatDiffuseColorG;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}
				{
				QVector<QVariant> data;
				data<<"Mat Diffuse ColorB"<<(double)ainfo.DisplayDesc.MatDiffuseColorB;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}
				{
				QVector<QVariant> data;
				data<<"Mat Diffuse ColorA"<<(double)ainfo.DisplayDesc.MatDiffuseColorA;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}

				{
				QVector<QVariant> data;
				data<<"Mat Specular ColorR"<<(double)ainfo.DisplayDesc.MatSpecularColorR;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}
				{
				QVector<QVariant> data;
				data<<"Mat Specular ColorG"<<(double)ainfo.DisplayDesc.MatSpecularColorG;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}
				{
				QVector<QVariant> data;
				data<<"Mat Specular ColorB"<<(double)ainfo.DisplayDesc.MatSpecularColorB;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}
				{
				QVector<QVariant> data;
				data<<"Mat Specular ColorA"<<(double)ainfo.DisplayDesc.MatSpecularColorA;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}

				{
				QVector<QVariant> data;
				data<<"Mat Emission ColorR"<<(double)ainfo.DisplayDesc.MatEmissionColorR;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}
				{
				QVector<QVariant> data;
				data<<"Mat Emission ColorG"<<(double)ainfo.DisplayDesc.MatEmissionColorG;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}
				{
				QVector<QVariant> data;
				data<<"Mat Emission ColorB"<<(double)ainfo.DisplayDesc.MatEmissionColorB;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}
				{
				QVector<QVariant> data;
				data<<"Mat Emission ColorA"<<(double)ainfo.DisplayDesc.MatEmissionColorA;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}
				{
				QVector<QVariant> data;
				data<<"Mat Shininess"<<(double)ainfo.DisplayDesc.MatShininess;
				_objectmodel->AppendRow(data, parent);
				++index;	
				}
			}	
		}


		// add script
		if(ainfo.PhysicDesc.TypePhysO == LbaNet::KynematicAType)
		{
			if(type == "Door")
			{
				DoorHandler* actorh = static_cast<DoorHandler*>(it->second.get());
				{
					QVector<QVariant> data;
					data<<"Opening type"<<actorh->GetOpeningType().c_str();
					_objectmodel->AppendRow(data, parent);
					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _dorropeningtypeList);
					++index;
				}

				{
					QVector<QVariant> data;
					data<<"Opening direction"<<actorh->GetOpeningDirection().c_str();
					_objectmodel->AppendRow(data, parent);
					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _dorropeningdirectionList);
					++index;
				}

				{
					QVector<QVariant> data;
					data<<"Moving value"<<(double)actorh->GetOpeningValue();
					_objectmodel->AppendRow(data, parent);
					++index;
				}

				{
					QVector<QVariant> data;
					data<<"Moving speed"<<(double)actorh->GetOpeningSpeed();
					_objectmodel->AppendRow(data, parent);
					++index;
				}
			}
			else
			{
				QVector<QVariant> data;
				data << "Script" << "";
				QModelIndex idx = _objectmodel->AppendRow(data, parent, true);	

				const std::vector<ActorScriptPartBasePtr> & items = it->second->GetScript();
				for(size_t i=0; i<items.size(); ++i)
				{
					ActorScriptPartBasePtr scpart = items[i];

					std::stringstream nametxt;
					nametxt << i <<"-" << scpart->GetTypeName();
					QVector<QVariant> datait;
					datait << "Script part" << nametxt.str().c_str();
					QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	

					//add position
					{
						QVector<QVariant> datachild;
						datachild << "Position in Script" << (int)i;
						QModelIndex idx1 = _objectmodel->AppendRow(datachild, idxit);	
					}

					scpart->WriteToQt(_objectmodel, idxit);

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _actorscriptparttypeList);	
				}

				// add new item
				QVector<QVariant> datait;
				datait << "Script part" << "Add new...";
				QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	
				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _actorscriptparttypeList);	
			
			
				_uieditor.treeView_object->setExpanded(idx, true); // expand 
			}
		}

		if(type == "Npc")
		{
			NPCHandler* actorh = static_cast<NPCHandler*>(it->second.get());

			// npc name
			{
				std::string txt = Localizer::getInstance()->GetText(Localizer::Name, actorh->GetNpcName());
				std::stringstream txttmp;
				if(txt != "")
					txttmp<<actorh->GetNpcName()<<": "<<txt;
				else
					txttmp<<"No";

				QVector<QVariant> data;
				data<<"Npc name"<<QString::fromUtf8(txttmp.str().c_str());
				QModelIndex idx = _objectmodel->AppendRow(data, parent);

				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _text_nameNameList);
				++index;
			}

			// extended dialog
			{

				QVector<QVariant> data;
				data<<"Extended dialog"<<!actorh->GetSimpleDialog();
				_objectmodel->AppendRow(data, parent);

				++index;
			}

			//add dialogs
			{

				QVector<QVariant> data;
				data<<"Dialogs"<<"";
				QModelIndex idx = _objectmodel->AppendRow(data, parent, true);
				++index;

				DialogPartPtr dialptr = actorh->GetRootDialog();
				if(dialptr)
				{
					std::vector<DialogPartPtr> childs = dialptr->GetChilds();
					for(size_t gg=0; gg< childs.size(); ++gg)
					{
						QVector<QVariant> datait;
						datait << "Dialog" << gg;
						QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	
						_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), dialptr->GetChildSize());

						SelectDialog(childs[gg].get(), idxit);
					}
				}

				// add new item
				QVector<QVariant> datait;
				datait << "Dialog" << "Add new...";
				QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	
				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _addList);	
			
			
				_uieditor.treeView_object->setExpanded(idx, true); // expand 
			}

			//add aggresive
			bool aggresive = actorh->GetAggresive();
			{
				QVector<QVariant> data;
				data<<"Aggresive"<<aggresive;
				_objectmodel->AppendRow(data, parent);
				++index;
			}

			if(aggresive)
			{
				{
					QVector<QVariant> data;
					data<<"Life"<<(double)actorh->GetLife();
					_objectmodel->AppendRow(data, parent);
					++index;
				}
				{
					QVector<QVariant> data;
					data<<"Mana"<<(double)actorh->GetMana();
					_objectmodel->AppendRow(data, parent);
					++index;
				}
				{
					QVector<QVariant> data;
					data<<"Armor"<<(double)actorh->GetArmor();
					_objectmodel->AppendRow(data, parent);
					++index;
				}
				{
					QVector<QVariant> data;
					data<<"Attack script"<<actorh->GetAttackFunction().c_str();
					_objectmodel->AppendRow(data, parent);
					++index;
				}
				{
					QVector<QVariant> data;
					data<<"Prepare weapon"<<actorh->GetWeaponAnimAtStart();
					_objectmodel->AppendRow(data, parent);
					++index;
				}

				int weapon1Type = actorh->GetWeapon1Type();
				{
					std::string weapontypestring = "No";
					switch(weapon1Type)
					{
						case 1:
							weapontypestring = "Contact";
						break;
						case 2:
							weapontypestring = "Distance";
						break;
					}

					QVector<QVariant> data;
					data<<"Weapon 1 Type"<<weapontypestring.c_str();
					QModelIndex idx = _objectmodel->AppendRow(data, parent);
					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _weapontypeList);
					++index;

					if(weapon1Type > 0)
					{
						int internindex = 0;

						{
							QVector<QVariant> data;
							data<<"Weapon 1 Power"<<(double)actorh->GetWeapon1Power();
							_objectmodel->AppendRow(data, idx);
							++internindex;
						}
						{
							QVector<QVariant> data;
							data<<"Weapon 1 Range"<<(double)actorh->GetWeapon1ReachDistance();
							_objectmodel->AppendRow(data, idx);
							++internindex;
						}
						{
							QVector<QVariant> data;
							data<<"Weapon 1 Animation"<<actorh->Getuseweapon1animation().c_str();
							_objectmodel->AppendRow(data, idx);
							++internindex;
						}

		
						// add projectiles
						{
							QVector<QVariant> data;
							data << "Projectiles" << "";
							QModelIndex idx2 = _objectmodel->AppendRow(data, idx, true);	
							++index;

							std::vector<ProjectileObjectDefPtr> & projs = actorh->GetProjectilesWeapon1();
							for(size_t p=0; p< projs.size(); ++p)
							{
								{
									QVector<QVariant> datait;
									datait << "Projectile" << "";
									QModelIndex idxit = _objectmodel->AppendRow(datait, idx2);	
									_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _removeList);

									SelectProjectile(projs[p].get(), idxit);
								}
							}

							// add new item
							QVector<QVariant> datait;
							datait << "Projectile" << "Add new...";
							QModelIndex idxit = _objectmodel->AppendRow(datait, idx2);	
							_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _addList);	
						}
					}
				}

				int weapon2Type = actorh->GetWeapon2Type();
				{
					std::string weapontypestring = "No";
					switch(weapon2Type)
					{
						case 1:
							weapontypestring = "Contact";
						break;
						case 2:
							weapontypestring = "Distance";
						break;
					}

					QVector<QVariant> data;
					data<<"Weapon 2 Type"<<weapontypestring.c_str();
					QModelIndex idx = _objectmodel->AppendRow(data, parent);
					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _weapontypeList);
					++index;
				

					if(weapon2Type > 0)
					{
						int internindex = 0;

						{
							QVector<QVariant> data;
							data<<"Weapon 2 Power"<<(double)actorh->GetWeapon2Power();
							_objectmodel->AppendRow(data, idx);
							++internindex;
						}
						{
							QVector<QVariant> data;
							data<<"Weapon 2 Range"<<(double)actorh->GetWeapon2ReachDistance();
							_objectmodel->AppendRow(data, idx);
							++internindex;
						}
						{
							QVector<QVariant> data;
							data<<"Weapon 2 Animation"<<actorh->Getuseweapon2animation().c_str();
							_objectmodel->AppendRow(data, idx);
							++internindex;
						}
		
						// add projectiles
						{
							QVector<QVariant> data;
							data << "Projectiles" << "";
							QModelIndex idx2 = _objectmodel->AppendRow(data, idx, true);	
							++index;

							std::vector<ProjectileObjectDefPtr> & projs = actorh->GetProjectilesWeapon2();
							for(size_t p=0; p< projs.size(); ++p)
							{
								{
									QVector<QVariant> datait;
									datait << "Projectile" << "";
									QModelIndex idxit = _objectmodel->AppendRow(datait, idx2);	
									_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _removeList);

									SelectProjectile(projs[p].get(), idxit);
								}
							}

							// add new item
							QVector<QVariant> datait;
							datait << "Projectile" << "Add new...";
							QModelIndex idxit = _objectmodel->AppendRow(datait, idx2);	
							_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _addList);	
						}
					}
				}


				{
					QVector<QVariant> data;
					data<<"Chassing start distance"<<(double)actorh->GetAttackActiDist();
					_objectmodel->AppendRow(data, parent);
					++index;
				}
				{
					QVector<QVariant> data;
					data<<"Chassing start distance - discrete"<<(double)actorh->GetAttackActiDistDiscrete();
					_objectmodel->AppendRow(data, parent);
					++index;
				}
				{
					QVector<QVariant> data;
					data<<"Chassing start distance - hidden"<<(double)actorh->GetAttackActiDistHidden();
					_objectmodel->AppendRow(data, parent);
					++index;
				}
				{
					QVector<QVariant> data;
					data<<"Chassing stop distance"<<(double)actorh->GetAttackStopDist();
					_objectmodel->AppendRow(data, parent);
					++index;
				}
				{
					QVector<QVariant> data;
					data<<"Chassing animation"<<actorh->Getchasinganimation().c_str();
					_objectmodel->AppendRow(data, parent);
					++index;
				}

				{
					QVector<QVariant> data;
					data<<"Respawn time (seconds)"<<(double)actorh->GetRespawnTimeInSec();
					_objectmodel->AppendRow(data, parent);
					++index;
				}
				{
					ConditionBasePtr condptr = actorh->GetAttackActivationCondition();

					QVector<QVariant> data;
					data << "Attack condition" << GetConditionType(condptr).c_str();
					QModelIndex idx = _objectmodel->AppendRow(data, parent);

					if(condptr)
						SelectCondition(condptr, idx);

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _conditiontypeList);
					++index;
				}

				// add action 
				{
					ActionBasePtr actptr = actorh->GetActionOnAttackActivation();
					std::string acttype = GetActionType(actptr);

					QVector<QVariant> data;
					data << "Action On Attack" << acttype.c_str();
					QModelIndex idx = _objectmodel->AppendRow(data, parent);
					
					if(actptr)
						SelectAction(actptr.get(), idx);

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _actiontypeList);
					++index;
				}

				// add items
				{
					QVector<QVariant> data;
					data << "Given Item list" << "";
					QModelIndex idx = _objectmodel->AppendRow(data, parent, true);	

					const std::vector<LbaNet::ItemGroupElement> & items = actorh->GetGivenItemList();
					for(size_t i=0; i<items.size(); ++i)
					{
						std::stringstream txtwithid;
						txtwithid<<items[i].Id<<": "<<InventoryItemHandler::getInstance()->GetItemInfo(items[i].Id).Name;

						QVector<QVariant> datait;
						datait << "Item" << txtwithid.str().c_str();
						QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	

						//add min
						{
							QVector<QVariant> datachild;
							datachild << "Min" << items[i].Min;
							QModelIndex idx1 = _objectmodel->AppendRow(datachild, idxit);	

							// add tooltip
							_objectmodel->setTooltip(idx1, "Minimum number of item to spawn");
							QModelIndex idx2 = _objectmodel->GetIndex(1, idx1.row(), idx1.parent());
							_objectmodel->setTooltip(idx2, "Minimum number of item to spawn");
						}

						//add max
						{
							QVector<QVariant> datachild;
							datachild << "Max" << items[i].Max;
							QModelIndex idx1 = _objectmodel->AppendRow(datachild, idxit);		

							// add tooltip
							_objectmodel->setTooltip(idx1, "Maximum number of item to spawn");
							QModelIndex idx2 = _objectmodel->GetIndex(1, idx1.row(), idx1.parent());
							_objectmodel->setTooltip(idx2, "Maximum number of item to spawn");
						}

						//add probability
						{
							QVector<QVariant> datachild;
							datachild << "Probability" << (double)items[i].Probability;
							QModelIndex idx1 = _objectmodel->AppendRow(datachild, idxit);			

							// add tooltip
							_objectmodel->setTooltip(idx1, "Probability of the item to spawn (1 = 100%)");
							QModelIndex idx2 = _objectmodel->GetIndex(1, idx1.row(), idx1.parent());
							_objectmodel->setTooltip(idx2, "Probability of the item to spawn (1 = 100%)");
						}

						//add group
						{
							QVector<QVariant> datachild;
							datachild << "Group" << items[i].Group;
							QModelIndex idx1 = _objectmodel->AppendRow(datachild, idxit);				

							// add tooltip
							_objectmodel->setTooltip(idx1, "The items part of the same group are mutually exclusive");
							QModelIndex idx2 = _objectmodel->GetIndex(1, idx1.row(), idx1.parent());
							_objectmodel->setTooltip(idx2, "The items part of the same group are mutually exclusive");
						}

						_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _itemNameList);	
					}

					// add new item
					QVector<QVariant> datait;
					datait << "Item" << "Add item...";
					QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	
					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _itemNameList);	
						
					_uieditor.treeView_object->setExpanded(idx, true); // expand 
				}	

			}
		}


		if(type == "Movable")
		{
			// free move
			{

				QVector<QVariant> data;
				data<<"Free move"<<it->second->GetActorInfo().PhysicDesc.AllowFreeMove;
				_objectmodel->AppendRow(data, parent);

				++index;
			}
		}


		UpdateSelectedActorDisplay(ainfo.PhysicDesc, it->second);
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
		ActorObjectInfo &ainfo = it->second->GetEditorActorInfo();

		ainfo.PhysicDesc.Pos.X = _objectmodel->data(_objectmodel->GetIndex(1, 7, parentIdx)).toFloat();
		ainfo.PhysicDesc.Pos.Y = _objectmodel->data(_objectmodel->GetIndex(1, 8, parentIdx)).toFloat();
		ainfo.PhysicDesc.Pos.Z = _objectmodel->data(_objectmodel->GetIndex(1, 9, parentIdx)).toFloat();
		ainfo.PhysicDesc.Pos.Rotation = _objectmodel->data(_objectmodel->GetIndex(1, 10, parentIdx)).toFloat();


		//condition
		{
			QModelIndex curidx = _objectmodel->GetIndex(0, 3, parentIdx);
			std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toString().toAscii().data();
			std::string currcond = GetConditionType(ainfo.Condition);

			if(condition != currcond)
			{
				ConditionBasePtr ptrtmp = CreateCondition(condition);
				ainfo.Condition = ptrtmp;

				_objectmodel->Clear(curidx);
				if(ptrtmp)
				{
					SelectCondition(ptrtmp, curidx);

					_uieditor.treeView_object->setExpanded(curidx, true); // expand 
				}
			}
		}

		int index = 11;

		if(ainfo.PhysicDesc.TypeShape != LbaNet::NoShape)
		{
			if(updatedrow == index)
				ainfo.PhysicDesc.Collidable = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
			++index;

			if(updatedrow == index)
				ainfo.ExcludeFromNavMesh = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
			++index;

			if(updatedrow == index)
				ainfo.HitPowerOnTouch = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
			++index;


			if(ainfo.PhysicDesc.TypeShape != LbaNet::TriangleMeshShape)
			{
				if(updatedrow == index)
					ainfo.PhysicDesc.SizeX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
				++index;
				if(updatedrow == index)
					ainfo.PhysicDesc.SizeY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
				++index;
				if(updatedrow == index)
					ainfo.PhysicDesc.SizeZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
				++index;
			}
			else
			{
				if(updatedrow == index)
					ainfo.PhysicDesc.Filename = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				++index;
			}
		}

		if(ainfo.DisplayDesc.TypeRenderer != LbaNet::NoRender)
		{
			if(updatedrow == index)
				ainfo.DisplayDesc.UseLight = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
			++index;

			if(updatedrow == index)
				ainfo.DisplayDesc.CastShadow = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
			++index;

			if(updatedrow == index)
				ainfo.DisplayDesc.TransX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			if(updatedrow == index)
				ainfo.DisplayDesc.TransY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			if(updatedrow == index)
				ainfo.DisplayDesc.TransZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;

			if(updatedrow == index)
				ainfo.DisplayDesc.RotX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			if(updatedrow == index)
				ainfo.DisplayDesc.RotY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			if(updatedrow == index)
				ainfo.DisplayDesc.RotZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;

			if(updatedrow == index)
				ainfo.DisplayDesc.ScaleX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			if(updatedrow == index)
				ainfo.DisplayDesc.ScaleY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			if(updatedrow == index)
				ainfo.DisplayDesc.ScaleZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;


			if(ainfo.DisplayDesc.TypeRenderer == RenderOsgModel )
			{
				if(updatedrow == index)
					ainfo.DisplayDesc.ModelName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				++index;
			}

			if(ainfo.DisplayDesc.TypeRenderer == RenderSprite )
			{
				if(updatedrow == index)
					ainfo.DisplayDesc.ModelName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				++index;	

				if(updatedrow == index)
					ainfo.DisplayDesc.ColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;	

				if(updatedrow == index)
					ainfo.DisplayDesc.ColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;		

				if(updatedrow == index)
					ainfo.DisplayDesc.ColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;		

				if(updatedrow == index)
					ainfo.DisplayDesc.ColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;

				if(updatedrow == index)
					ainfo.DisplayDesc.UseBillboard = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
				++index;
			}

			if(ainfo.DisplayDesc.TypeRenderer == RenderLba1M ||
					ainfo.DisplayDesc.TypeRenderer == RenderLba2M)
			{
				std::string oldmodelname = ainfo.DisplayDesc.ModelName;
				std::string oldmodelOutfit = ainfo.DisplayDesc.Outfit;
				std::string oldmodelWeapon = ainfo.DisplayDesc.Weapon;

				if(updatedrow == index)
					ainfo.DisplayDesc.ModelName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();		
	
				++index;		

				if(updatedrow == index)
					ainfo.DisplayDesc.Outfit = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();		

				if(ainfo.DisplayDesc.ModelName != oldmodelname)
				{
					RefreshActorModelOutfit(index, parentIdx, ainfo.DisplayDesc.ModelName, true, it->second);

					updateobj = true;
				}
				
				++index;	

				if(updatedrow == index)
					ainfo.DisplayDesc.Weapon = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();		

				if(ainfo.DisplayDesc.Outfit != oldmodelOutfit)
				{
					RefreshActorModelWeapon(index, parentIdx, ainfo.DisplayDesc.ModelName,
																	ainfo.DisplayDesc.Outfit, true, it->second);

					updateobj = true;
				}	
				
				++index;	

				if(updatedrow == index)
				{
					ainfo.DisplayDesc.Mode = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();		

					//update colors
					Lba1ModelMapHandler::getInstance()->GetModelColor(ainfo.DisplayDesc.ModelName,
																	ainfo.DisplayDesc.Outfit,
																	ainfo.DisplayDesc.Weapon, 
																	ainfo.DisplayDesc.Mode, 
																	it->second->initpolycolors, 
																	it->second->initspherecolors, 
																	it->second->initlinecolors);

					it->second->currentpolycolors = it->second->initpolycolors;
					it->second->currentspherecolors = it->second->initspherecolors;
					it->second->currentlinecolors = it->second->initlinecolors;

					it->second->ClearColorSwap();
					updateobj = true;
				}


				if(ainfo.DisplayDesc.Weapon != oldmodelWeapon)
				{
					RefreshActorModelMode(index, parentIdx, ainfo.DisplayDesc.ModelName,
																	ainfo.DisplayDesc.Outfit,
																	ainfo.DisplayDesc.Weapon, true, it->second);

					updateobj = true;
				}
				
				++index;

				if(!updateobj)
				{
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

			// check materials
			if(!updateobj)
			{
				ainfo.DisplayDesc.UseTransparentMaterial = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();		
				++index;
				ainfo.DisplayDesc.MatAlpha = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		
				++index;

				int oldmatcolortype = ainfo.DisplayDesc.ColorMaterialType;

				std::string matstringtype = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();	
				++index;

				ainfo.DisplayDesc.ColorMaterialType = 0;
				if(matstringtype == "Ambient")
					ainfo.DisplayDesc.ColorMaterialType = 1;
				if(matstringtype == "Diffuse")
					ainfo.DisplayDesc.ColorMaterialType = 2;
				if(matstringtype == "Specular")
					ainfo.DisplayDesc.ColorMaterialType = 3;
				if(matstringtype == "Emission")
					ainfo.DisplayDesc.ColorMaterialType = 4;
				if(matstringtype == "Ambient_And_Diffuse")
					ainfo.DisplayDesc.ColorMaterialType = 5;

				if(ainfo.DisplayDesc.ColorMaterialType != oldmatcolortype)
					updateobj = true;

		
				if(oldmatcolortype > 0)
				{
					ainfo.DisplayDesc.MatAmbientColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;			
					ainfo.DisplayDesc.MatAmbientColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;			
					ainfo.DisplayDesc.MatAmbientColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;			
					ainfo.DisplayDesc.MatAmbientColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;			
					ainfo.DisplayDesc.MatDiffuseColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;			
					ainfo.DisplayDesc.MatDiffuseColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;			
					ainfo.DisplayDesc.MatDiffuseColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;			
					ainfo.DisplayDesc.MatDiffuseColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;			
					ainfo.DisplayDesc.MatSpecularColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;			
					ainfo.DisplayDesc.MatSpecularColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;			
					ainfo.DisplayDesc.MatSpecularColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;			
					ainfo.DisplayDesc.MatSpecularColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;	
					ainfo.DisplayDesc.MatEmissionColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;			
					ainfo.DisplayDesc.MatEmissionColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;			
					ainfo.DisplayDesc.MatEmissionColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;			
					ainfo.DisplayDesc.MatEmissionColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;	
					ainfo.DisplayDesc.MatShininess = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
					++index;				
				}
			}

		}

		if(!updateobj)
		{
			//update scripts
			if(ainfo.PhysicDesc.TypePhysO == LbaNet::KynematicAType)
			{
				if(it->second->ActorType() == "Door")
				{
					DoorHandler* actorh = static_cast<DoorHandler*>(it->second.get());

					if(updatedrow == index)
						actorh->SetOpeningType(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data());
					++index;	

					if(updatedrow == index)
						actorh->SetOpeningDirection(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data());
					++index;	

					if(updatedrow == index)
						actorh->SetOpeningValue(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat());
					++index;	

					if(updatedrow == index)
						actorh->SetOpeningSpeed(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat());
					++index;	
				}
				else
				{

					QModelIndex itemparent = _objectmodel->GetIndex(0, index, parentIdx);
					int curridx = 0;
					++index;

					//take care of the items
					const std::vector<ActorScriptPartBasePtr> & items = it->second->GetScript();
					std::vector<ActorScriptPartBasePtr>::const_iterator itit = items.begin();
					for(int cc=0; itit != items.end(); ++itit, ++cc)
					{
						QModelIndex childidx = _objectmodel->GetIndex(0, curridx, itemparent);
						QModelIndex childidx1 = _objectmodel->GetIndex(1, curridx, itemparent);
						std::string type = _objectmodel->data(childidx1).toString().toAscii().data();
						
						bool numbered = false;
						int pos = type.find_first_of("-");
						if(pos != std::string::npos)
						{
							type = type.substr(pos+1);
							numbered = true;
						}

						++curridx;
						if(type != (*itit)->GetTypeName())
						{
							if(type == "Remove")
							{
								it->second->RemoveScriptPart(*itit);
								//_objectmodel->Clear(childidx);
								//_objectmodel->removeRows(curridx-1, 1, itemparent);
								updateobj = true;
								//return;
								break;
							}
							else
							{
								ActorScriptPartBasePtr newsp = ActorScriptPartBase::BuildScriptPart(type, _posX, _posY, _posZ);
								if(newsp)
								{
									it->second->ReplaceScriptPart(*itit, newsp);

									// refresh tree
									int position = _objectmodel->data(_objectmodel->GetIndex(1, 0, childidx)).toInt();
									_objectmodel->Clear(childidx);

									//add position
									{
										QVector<QVariant> datachild;
										datachild << "Position in Script" << position;
										QModelIndex idx1 = _objectmodel->AppendRow(datachild, childidx);	
									}

									newsp->WriteToQt(_objectmodel, childidx);

									std::stringstream nametxt;
									nametxt << position <<"-" << type;
									_objectmodel->setData(childidx1, nametxt.str().c_str());

									_uieditor.treeView_object->setExpanded(childidx, true); // expand 
								}
							}

							return;
						}
						else
						{
							int position = _objectmodel->data(_objectmodel->GetIndex(1, 0, childidx)).toInt();
							if(position < 0)
								position = 0;
							if(position >= (int)items.size())
								position = (int)items.size()-1;

							if(position != cc)
							{
								it->second->UpdateScriptPosition(*itit, position);
								updateobj = true;
								break;
							}
							else
							{
								(*itit)->UpdateFromQt(_objectmodel, childidx, 1);

								if(!numbered)
								{
									std::stringstream nametxt;
									nametxt << position <<"-" << type;
									_objectmodel->setData(childidx1, nametxt.str().c_str());
									return;
								}
							}
						}
					}

					if(!updateobj)
					{
						QModelIndex childidx = _objectmodel->GetIndex(0, curridx, itemparent);
						QModelIndex childidx1 = _objectmodel->GetIndex(1, curridx, itemparent);
						std::string type = _objectmodel->data(childidx1).toString().toAscii().data();
						++curridx;

						if(type != "Add new...")
						{
							if(type == "Remove")
							{
								_objectmodel->setData(childidx1, "Add new...");
								return;
							}
							else
							{
								//build new script part
								ActorScriptPartBasePtr newsp = ActorScriptPartBase::BuildScriptPart(type, _posX, _posY, _posZ);
								if(newsp)
								{
									int position = it->second->AddScriptPart(newsp);

									//refresh tree
									{
										QVector<QVariant> datachild;
										datachild << "Position in Script" << position;
										QModelIndex idx1 = _objectmodel->AppendRow(datachild, childidx);	
									}

									newsp->WriteToQt(_objectmodel, childidx);


									// add new item
									QVector<QVariant> datait;
									datait << "Script part" << "Add new...";
									QModelIndex idxit = _objectmodel->AppendRow(datait, itemparent);	
									_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), 
																				_actorscriptparttypeList);	
								

									std::stringstream nametxt;
									nametxt << position <<"-" << type;
									_objectmodel->setData(childidx1, nametxt.str().c_str());

									_uieditor.treeView_object->setExpanded(childidx, true); // expand 	

									return;
								}
								else
								{
									_objectmodel->setData(childidx1, "Add new...");
									return;
								}
							}
						}
					}
				}
			}

			if(it->second->ActorType() == "Movable")
			{
				// free move
				{
					ainfo.PhysicDesc.AllowFreeMove = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
					++index;
				}
			}

			if(it->second->ActorType() == "Npc")
			{
				NPCHandler* actorh = static_cast<NPCHandler*>(it->second.get());

				// npc name
				{
					std::string name = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
					name = name.substr(0, name.find(":"));
					if(name != "")
					{
						long textid = atol(name.c_str());
						std::stringstream namestr;
						if(name == "No")
							textid = -1;
						else
							namestr<<"#"<<textid;

						ainfo.ExtraInfo.Name = namestr.str();
						actorh->SetNpcName(textid);
					}
					++index;
				}

				// extended dialog
				{

					actorh->SetSimpleDialog(!_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool());
					++index;
				}



				// dialog info
				{
					QModelIndex itemparent = _objectmodel->GetIndex(0, index, parentIdx);
					int curridx = 0;
					++index;

					DialogPartPtr dialptr = actorh->GetRootDialog();
					if(dialptr)
					{
						std::vector<DialogPartPtr> childs = dialptr->GetChilds();
						for(size_t gg=0; gg< childs.size(); ++gg)
						{
							QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent);
							std::string check = _objectmodel->data(childidx).toString().toAscii().data();
							++curridx;

							if(check == "Remove")
							{
								dialptr->RemoveChild(childs[gg]);

								updateobj = true;
								break;
							}
							else
							{
								if(check == "")
								{
									std::stringstream strsnum;
									strsnum<<gg;
									_objectmodel->setData(childidx, strsnum.str().c_str());	
								}
								else
								{
									long idxnow = atol(check.c_str());
									if(idxnow != gg)
									{
										dialptr->UpdateChildPosition(childs[gg], idxnow);
										updateobj = true;
										break;
									}
								}
							}
						}

						if(!updateobj)
						{
							QModelIndex childidx0 = _objectmodel->GetIndex(0, curridx, itemparent);
							QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent);
							std::string check = _objectmodel->data(childidx).toString().toAscii().data();
							++curridx;
							if(check == "Add")
							{
								DialogPartPtr newd(new DialogPart());
								int indexcc = dialptr->AddChild(newd);

								{
								// add new item
								QVector<QVariant> datait;
								datait << "Dialog" << "Add new...";
								QModelIndex idxit = _objectmodel->AppendRow(datait, itemparent);	
								_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _addList);	
								}

								{
								std::stringstream strsnum;
								strsnum<<indexcc;
								SelectDialog(newd.get(), childidx0);
								_objectmodel->SetCustomIndex(childidx, dialptr->GetChildSize());
								_objectmodel->setData(childidx, strsnum.str().c_str());
								_uieditor.treeView_object->setExpanded(childidx0, true); // expand 
								}

								return;
							}
						}
					}
				}

				// aggresive
				bool wasaggresive = actorh->GetAggresive();
				bool aggresive = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
				++index;

				if(wasaggresive)
				{
					actorh->SetLife(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat());
					++index;

					actorh->SetMana(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat());
					++index;

					actorh->SetArmor(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat());
					++index;

					actorh->SetAttackFunction(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data());
					++index;

					actorh->SetWeaponAnimAtStart(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool());
					++index;

					int lastweapon1type = actorh->GetWeapon1Type();
					int currentweapon1type = -1;
					std::string weapon1typestr = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
					if(weapon1typestr == "Contact")
						currentweapon1type = 1;
					if(weapon1typestr == "Distance")
						currentweapon1type = 2;

					{
						QModelIndex itemparent = _objectmodel->GetIndex(0, index, parentIdx);
						int curridx1 = 0;
						++index;

						if(lastweapon1type > 0)
						{
							actorh->SetWeapon1Power(_objectmodel->data(_objectmodel->GetIndex(1, curridx1, itemparent)).toString().toFloat());
							++curridx1;
							actorh->SetWeapon1ReachDistance(_objectmodel->data(_objectmodel->GetIndex(1, curridx1, itemparent)).toString().toFloat());
							++curridx1;
							actorh->Setuseweapon1animation(_objectmodel->data(_objectmodel->GetIndex(1, curridx1, itemparent)).toString().toAscii().data());
							++curridx1;


							// projectiles
							{
								QModelIndex itemparent2 = _objectmodel->GetIndex(0, curridx1, itemparent);
								++curridx1;
								int curridx = 0;

								std::vector<ProjectileObjectDefPtr> & childs = actorh->GetProjectilesWeapon1();
								for(size_t gg=0; gg< childs.size(); ++gg)
								{
									QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent2);
									std::string check = _objectmodel->data(childidx).toString().toAscii().data();
									++curridx;

									if(check == "Remove")
									{
										actorh->RemoveProjectileWeapon1(childs[gg]);
										updateobj = true;
										break;
									}
								}

								if(!updateobj)
								{
									QModelIndex childidx0 = _objectmodel->GetIndex(0, curridx, itemparent2);
									QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent2);
									std::string check = _objectmodel->data(childidx).toString().toAscii().data();
									if(check == "Add")
									{
										ProjectileObjectDefPtr newd(new ProjectileObjectDef());
										actorh->AddProjectileWeapon1(newd);

										{
										// add new item
										QVector<QVariant> datait;
										datait << "Projectile" << "Add new...";
										QModelIndex idxit = _objectmodel->AppendRow(datait, itemparent2);	
										_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _addList);	
										}

										{
										SelectProjectile(newd.get(), childidx0);
										_objectmodel->SetCustomIndex(childidx, _removeList);
										_objectmodel->setData(childidx, "");
										_uieditor.treeView_object->setExpanded(childidx0, true); // expand 
										}
									}
								}
							}
						}
					}

					int lastweapon2type = actorh->GetWeapon2Type();
					int currentweapon2type = -1;
					std::string weapon2typestr = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
					if(weapon2typestr == "Contact")
						currentweapon2type = 1;
					if(weapon2typestr == "Distance")
						currentweapon2type = 2;		

					{
						QModelIndex itemparent = _objectmodel->GetIndex(0, index, parentIdx);
						int curridx1 = 0;
						++index;

						if(lastweapon2type > 0)
						{
							actorh->SetWeapon2Power(_objectmodel->data(_objectmodel->GetIndex(1, curridx1, itemparent)).toString().toFloat());
							++curridx1;
							actorh->SetWeapon2ReachDistance(_objectmodel->data(_objectmodel->GetIndex(1, curridx1, itemparent)).toString().toFloat());
							++curridx1;
							actorh->Setuseweapon2animation(_objectmodel->data(_objectmodel->GetIndex(1, curridx1, itemparent)).toString().toAscii().data());
							++curridx1;

							// projectiles
							{
								QModelIndex itemparent2 = _objectmodel->GetIndex(0, curridx1, itemparent);
								++curridx1;
								int curridx = 0;

								std::vector<ProjectileObjectDefPtr> & childs = actorh->GetProjectilesWeapon2();
								for(size_t gg=0; gg< childs.size(); ++gg)
								{
									QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent2);
									std::string check = _objectmodel->data(childidx).toString().toAscii().data();
									++curridx;

									if(check == "Remove")
									{
										actorh->RemoveProjectileWeapon2(childs[gg]);
										updateobj = true;
										break;
									}
								}

								if(!updateobj)
								{
									QModelIndex childidx0 = _objectmodel->GetIndex(0, curridx, itemparent2);
									QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent2);
									std::string check = _objectmodel->data(childidx).toString().toAscii().data();
									if(check == "Add")
									{
										ProjectileObjectDefPtr newd(new ProjectileObjectDef());
										actorh->AddProjectileWeapon2(newd);

										{
										// add new item
										QVector<QVariant> datait;
										datait << "Projectile" << "Add new...";
										QModelIndex idxit = _objectmodel->AppendRow(datait, itemparent2);	
										_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _addList);	
										}

										{
										SelectProjectile(newd.get(), childidx0);
										_objectmodel->SetCustomIndex(childidx, _removeList);
										_objectmodel->setData(childidx, "");
										_uieditor.treeView_object->setExpanded(childidx0, true); // expand 
										}
									}
								}
							}
						}
					}

					if(!updateobj)
					{
						actorh->SetAttackActiDist(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat());
						++index;

						actorh->SetAttackActiDistDiscrete(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat());
						++index;

						actorh->SetAttackActiDistHidden(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat());
						++index;

						actorh->SetAttackStopDist(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat());
						++index;

						actorh->Setchasinganimation(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data());
						++index;

						actorh->SetRespawnTimeInSec(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat());
						++index;

						// check condition part
						{
							std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
							std::string currcond = GetConditionType(actorh->GetAttackActivationCondition());

							if(condition != currcond)
							{
								ConditionBasePtr ptrtmp = CreateCondition(condition);
								actorh->SetAttackActivationCondition(ptrtmp);

								QModelIndex curidx = _objectmodel->GetIndex(0, index, parentIdx);
								_objectmodel->Clear(curidx);
								if(ptrtmp)
								{
									SelectCondition(ptrtmp, curidx);
									_uieditor.treeView_object->setExpanded(curidx, true); // expand 
								}

							}

							++index;
						}

						// check action part
						{
							std::string action1 = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
							std::string curract = GetActionType(actorh->GetActionOnAttackActivation());

							if(action1 != curract)
							{
								ActionBasePtr ptrtmp = CreateAction(action1);
								actorh->SetActionOnAttackActivation(ptrtmp);

								QModelIndex curidx = _objectmodel->GetIndex(0, index, parentIdx);
								_objectmodel->Clear(curidx);
								if(ptrtmp)
								{
									SelectAction(ptrtmp.get(), curidx);
									_uieditor.treeView_object->setExpanded(curidx, true); // expand 
								}

							}

							++index;
						}

						// take care of items
						{
							QModelIndex itemparent = _objectmodel->GetIndex(0, index, parentIdx);
							int curridx = 0;

							//take care of the items
							std::vector<LbaNet::ItemGroupElement> &items = actorh->GetGivenItemList();
							std::vector<LbaNet::ItemGroupElement>::iterator itit = items.begin();
							for(;itit != items.end(); ++itit)
							{
								QModelIndex childidx = _objectmodel->GetIndex(0, curridx, itemparent);
								std::string id = _objectmodel->data(_objectmodel->GetIndex(1, curridx, itemparent))
																						.toString().toAscii().data();
								++curridx;

								if(id == "No item")
								{
									// need to remove the item
									items.erase(itit);

									updateobj = true;
									break;
								}

								std::string tmp = id.substr(0, id.find(":"));
								itit->Id = atol(tmp.c_str());
								itit->Min = _objectmodel->data(_objectmodel->GetIndex(1, 0, childidx)).toInt();
								itit->Max = _objectmodel->data(_objectmodel->GetIndex(1, 1, childidx)).toInt();
								itit->Probability = _objectmodel->data(_objectmodel->GetIndex(1, 2, childidx)).toFloat();
								itit->Group = _objectmodel->data(_objectmodel->GetIndex(1, 3, childidx)).toInt();
							}

							QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent);
							std::string id = _objectmodel->data(childidx).toString().toAscii().data();
							if(id != "Add item...")
							{
								if(id == "No item")
								{
									_objectmodel->setData(childidx, "Add item...");
								}
								else
								{
									// add new item
									std::string tmp = id.substr(0, id.find(":"));
									long itmid = atol(tmp.c_str());

									LbaNet::ItemGroupElement newitem;
									newitem.Id = itmid;
									newitem.Min = 1;
									newitem.Max = 1;
									newitem.Probability = 1;
									newitem.Group = -1;
									items.push_back(newitem);

									updateobj = true;
								}
							}

						}
					}


					if(lastweapon1type != currentweapon1type)
					{
						actorh->SetWeapon1Type(currentweapon1type);
						updateobj = true;
					}
					if(lastweapon2type != currentweapon2type)
					{
						actorh->SetWeapon2Type(currentweapon2type);
						updateobj = true;
					}
				}

				if(aggresive != wasaggresive)
				{
					actorh->SetAggresive(aggresive);
					updateobj = true;
				}
			}
		}


		{
		LbaNet::PhysicalActorType before = ainfo.PhysicDesc.TypePhysO;
		std::string type = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toString().toAscii().data();
		if(type == "Static") 
			ainfo.PhysicDesc.TypePhysO = LbaNet::StaticAType;
		if(type == "Scripted") 
			ainfo.PhysicDesc.TypePhysO = LbaNet::KynematicAType;
		if(type == "Door") 
		{
			ainfo.PhysicDesc.TypePhysO = LbaNet::KynematicAType;
			if(it->second->ActorType() != "Door")
			{
				it->second = boost::shared_ptr<ActorHandler>(new DoorHandler(ainfo, 0, 0, 3, 0.01,	true));
				updateobj = true;
			}
		}
		if(type == "Npc") 
		{
			ainfo.PhysicDesc.TypePhysO = LbaNet::KynematicAType;
			if(it->second->ActorType() != "Npc")
			{
				it->second = boost::shared_ptr<ActorHandler>(new NPCHandler(ainfo));
				updateobj = true;
			}
		}
		if(type == "Movable") 
			ainfo.PhysicDesc.TypePhysO = LbaNet::CharControlAType;
		if(before != ainfo.PhysicDesc.TypePhysO)
			updateobj = true;

		LbaNet::RenderTypeEnum befored = ainfo.DisplayDesc.TypeRenderer;
		ainfo.DisplayDesc.TypeRenderer = LbaNet::NoRender;
		
		std::string dtype = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toString().toAscii().data();
		if(dtype == "Osg Model") 
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderOsgModel;
		if(dtype == "Sprite") 
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderSprite;
		if(dtype == "Lba1 Model") 
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderLba1M;
		if(dtype == "Lba2 Model") 
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderLba2M;
		if(dtype == "Box") 
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderBox;
		if(dtype == "Sphere") 
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderSphere;
		if(dtype == "Capsule") 
			ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderCapsule;

		if(befored != ainfo.DisplayDesc.TypeRenderer)
			updateobj = true;

		LbaNet::PhysicalShapeEnum beforep = ainfo.PhysicDesc.TypeShape;
		std::string ptype = _objectmodel->data(_objectmodel->GetIndex(1, 6, parentIdx)).toString().toAscii().data();
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
		it->second->Refresh();
		it->second->ClearRunningScript();
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
					type = it->second->ActorType();
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
		UpdateSelectedActorDisplay(ainfo.PhysicDesc, it->second);
	}
}


/***********************************************************
update editor selected ector display
***********************************************************/
void EditorHandler::UpdateSelectedActorDisplay(LbaNet::ObjectPhysicDesc desc,
											   boost::shared_ptr<ActorHandler> actor)
{
	RemoveSelectedActorDislay();



	_actornode = OsgHandler::getInstance()->AddEmptyActorNode(0, false);

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
			stateset->setRenderBinDetails( 50, "DepthSortedBin");


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
			stateset->setRenderBinDetails( 50, "DepthSortedBin");	
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
			stateset->setRenderBinDetails( 50, "DepthSortedBin");	
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
			stateset->setRenderBinDetails( 50, "DepthSortedBin");	
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
			stateset->setRenderBinDetails( 50, "DepthSortedBin");	

		}
		break;
	}


	// create script objects
	std::vector<ActorScriptPartBasePtr> scripts = actor->GetScript();
	std::vector<ActorScriptPartBasePtr>::iterator it = scripts.begin();
	std::vector<ActorScriptPartBasePtr>::iterator end = scripts.end();
	for(int cc=0; it != end; ++it, ++cc)
	{
		ActorObjectInfo ainfo = (*it)->GetEditorObject(actor->GetActorInfo().ObjectId, cc);
		if(ainfo.ObjectId >= 0)
		{
			_editorObjects[ainfo.ObjectId] = ainfo;

			EventsQueue::getReceiverQueue()->AddEvent(
					new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
					4, ainfo.ObjectId, -1, ainfo.DisplayDesc, ainfo.PhysicDesc, ainfo.LifeInfo, 
					ainfo.ExtraInfo));
		}
	}
	
}


/***********************************************************
remove current selected display
***********************************************************/
void EditorHandler::RemoveSelectedActorDislay()
{
	if(_actornode)
		OsgHandler::getInstance()->RemoveActorNode(0, _actornode, false);

	_actornode = NULL;


	std::map<Ice::Long, ActorObjectInfo >::iterator it = _editorObjects.begin();
	std::map<Ice::Long, ActorObjectInfo >::iterator end = _editorObjects.end();
	for(; it != end; ++it)
	{
		EventsQueue::getReceiverQueue()->AddEvent(
			new RemoveObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													4, it->first));
	}

	_editorObjects.clear();

}


/***********************************************************
called when an object is picked
***********************************************************/
void EditorHandler::PickedObject(const std::string & name, float px, float py, float pz)
{
	if(_draggerX && _draggerX->getDraggerActive())
		return;

	if(_draggerY && _draggerY->getDraggerActive())
		return;

	if(_draggerZ && _draggerZ->getDraggerActive())
		return;


	if(_pickfindpathstarted)
	{
		if(!_startpathpicked)
		{
			_startpath.x = px;
			_startpath.y = py;
			_startpath.z = pz;
			_startpathpicked = true;
			DisplayStartPath(_startpath);
			return;
		}
		else
		{
			LbaVec3	endpath;
			endpath.x = px;
			endpath.y = py;
			endpath.z = pz;
			DisplayEndPath(endpath);

			if(_navimesh->CalculatePath(_startpath, endpath))
				_navimesh->DrawLastPath();

			_pickfindpathstarted = false;
			return;
		}
	}




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

	_actornode = OsgHandler::getInstance()->AddEmptyActorNode(0, false);

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
	stateset->setRenderBinDetails( 50, "DepthSortedBin");	

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

	_actornode = OsgHandler::getInstance()->AddEmptyActorNode(0, false);

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
	stateset->setRenderBinDetails( 50, "DepthSortedBin");	
}





/***********************************************************
draw arrow on selected object
***********************************************************/
void EditorHandler::DrawArrows(float PosX, float PosY, float PosZ)
{
	RemoveArrows();

	_arrownode = OsgHandler::getInstance()->AddEmptyActorNode(0, false);

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
					_objectmodel->setData(_objectmodel->GetIndex(1, 10), floor(_draggerX->getMatrix().getTrans().x()*10.0)/10.0);
					_draggerY->setMatrix(_draggerX->getMatrix());
					_draggerZ->setMatrix(_draggerX->getMatrix());
				}

				if(pickedarrow == 2)
				{	
					_objectmodel->setData(_objectmodel->GetIndex(1, 11), floor(_draggerY->getMatrix().getTrans().y()*10.0)/10.0);
					_draggerX->setMatrix(_draggerY->getMatrix());
					_draggerZ->setMatrix(_draggerY->getMatrix());
				}

				if(pickedarrow == 3)
				{
					_objectmodel->setData(_objectmodel->GetIndex(1, 12), floor(_draggerZ->getMatrix().getTrans().z()*10.0)/10.0);
					_draggerX->setMatrix(_draggerZ->getMatrix());
					_draggerY->setMatrix(_draggerZ->getMatrix());
				}
				
				return;
			}

			if(category == "ActivationTrigger")
			{
				if(pickedarrow == 1)
				{
					_objectmodel->setData(_objectmodel->GetIndex(1, 5), floor(_draggerX->getMatrix().getTrans().x()*10.0)/10.0);
					_draggerY->setMatrix(_draggerX->getMatrix());
					_draggerZ->setMatrix(_draggerX->getMatrix());
				}

				if(pickedarrow == 2)
				{	
					_objectmodel->setData(_objectmodel->GetIndex(1, 6), floor(_draggerY->getMatrix().getTrans().y()*10.0)/10.0);
					_draggerX->setMatrix(_draggerY->getMatrix());
					_draggerZ->setMatrix(_draggerY->getMatrix());
				}

				if(pickedarrow == 3)
				{
					_objectmodel->setData(_objectmodel->GetIndex(1, 7), floor(_draggerZ->getMatrix().getTrans().z()*10.0)/10.0);
					_draggerX->setMatrix(_draggerZ->getMatrix());
					_draggerY->setMatrix(_draggerZ->getMatrix());
				}

				return;
			}

			if(category == "ZoneActionTrigger")
			{
				if(pickedarrow == 1)
				{
					_objectmodel->setData(_objectmodel->GetIndex(1, 5), floor(_draggerX->getMatrix().getTrans().x()*10.0)/10.0);
					_draggerY->setMatrix(_draggerX->getMatrix());
					_draggerZ->setMatrix(_draggerX->getMatrix());
				}

				if(pickedarrow == 2)
				{	
					_objectmodel->setData(_objectmodel->GetIndex(1, 6), floor(_draggerY->getMatrix().getTrans().y()*10.0)/10.0);
					_draggerX->setMatrix(_draggerY->getMatrix());
					_draggerZ->setMatrix(_draggerY->getMatrix());
				}

				if(pickedarrow == 3)
				{
					_objectmodel->setData(_objectmodel->GetIndex(1, 7), floor(_draggerZ->getMatrix().getTrans().z()*10.0)/10.0);
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
				float nX = _objectmodel->data(_objectmodel->GetIndex(1, 7)).toString().toFloat();
				nX += floor(_draggerX->getMatrix().getTrans().x()*10)/10 - center.x();
				_objectmodel->setData(_objectmodel->GetIndex(1, 7), (double)nX);
				_draggerY->setMatrix(_draggerX->getMatrix());
				_draggerZ->setMatrix(_draggerX->getMatrix());
			}

			if(pickedarrow == 2)
			{	
				float nY = _objectmodel->data(_objectmodel->GetIndex(1, 8)).toString().toFloat();
				nY += floor(_draggerY->getMatrix().getTrans().y()*10)/10 - center.y();
				_objectmodel->setData(_objectmodel->GetIndex(1, 8), (double)nY);
				_draggerX->setMatrix(_draggerY->getMatrix());
				_draggerZ->setMatrix(_draggerY->getMatrix());
			}

			if(pickedarrow == 3)
			{
				float nZ = _objectmodel->data(_objectmodel->GetIndex(1, 9)).toString().toFloat();
				nZ += floor(_draggerZ->getMatrix().getTrans().z()*10)/10 - center.z();
				_objectmodel->setData(_objectmodel->GetIndex(1, 9), (double)nZ);
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
		OsgHandler::getInstance()->RemoveActorNode(0, _arrownode, false);
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

	_scriptnode = OsgHandler::getInstance()->AddEmptyActorNode(0, false);

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
	stateset->setRenderBinDetails( 50, "DepthSortedBin");

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
		OsgHandler::getInstance()->RemoveActorNode(0, _scriptnode, false);

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


	// text id
	{
		long tid = cond->GetTextid();
		std::string txt = Localizer::getInstance()->GetText(Localizer::Quest, tid);
		std::stringstream txttmp;
		txttmp<<tid<<": "<<txt;

		QVector<QVariant> data;
		data<<"Associated Text"<<QString::fromUtf8(txttmp.str().c_str());
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _text_questNameList);
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

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 3, parent), _conditiontypeList);

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


		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 3, parent), _conditiontypeList);
		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _conditiontypeList);

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

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 3, parent), _conditiontypeList);
		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 4, parent), _conditiontypeList);

		return;
	}



	if(type == "ItemInInventoryCondition")
	{
		ItemInInventoryCondition* ptr = static_cast<ItemInInventoryCondition*>(cond.get());

		{
		long id = ptr->GetItemId();
		std::stringstream txtwithid;
		txtwithid<<id<<": "<<InventoryItemHandler::getInstance()->GetItemInfo(id).Name;
		QVector<QVariant> data;
		data << "Item Id" << txtwithid.str().c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}

		{
		QVector<QVariant> data2;
		data2 << "Item number" << ptr->GetItemNumber();
		QModelIndex idx = _objectmodel->AppendRow(data2, parent);
		}

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 3, parent), _itemNameList);

		return;
	}


	if(type == "QuestStartedCondition")
	{
		QuestStartedCondition* ptr = static_cast<QuestStartedCondition*>(cond.get());

		{
		QVector<QVariant> data;
		data << "Quest Id" << (int)ptr->GetQuestId();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}

		return;
	}


	if(type == "QuestFinishedCondition")
	{
		QuestFinishedCondition* ptr = static_cast<QuestFinishedCondition*>(cond.get());

		{
		QVector<QVariant> data;
		data << "Quest Id" << (int)ptr->GetQuestId();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}

		return;
	}


	if(type == "ChapterStartedCondition")
	{
		ChapterStartedCondition* ptr = static_cast<ChapterStartedCondition*>(cond.get());

		{
		QVector<QVariant> data;
		data << "Chapter number" << ptr->GetChapter();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}

		return;
	}

	if(type == "QuestAvailableCondition")
	{
		QuestAvailableCondition* ptr = static_cast<QuestAvailableCondition*>(cond.get());

		{
		QVector<QVariant> data;
		data << "Quest Id" << (int)ptr->GetQuestId();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}

		return;
	}

	if(type == "CustomCondition")
	{
		CustomCondition* ptr = static_cast<CustomCondition*>(cond.get());

		{
		QVector<QVariant> data;
		data << "Lua function" << ptr->GetLuaFunction().c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}

		return;
	}

	if(type == "CheckFlagCondition")
	{
		CheckFlagCondition* ptr = static_cast<CheckFlagCondition*>(cond.get());

		{
		QVector<QVariant> data;
		data << "Flag name" << ptr->GetFlagName().c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}

		{
		QVector<QVariant> data;
		data << "Value" << ptr->GetValue();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		}

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

	if(type == "ItemInInventoryCondition")
		return ConditionBasePtr(new ItemInInventoryCondition());

	if(type == "QuestStartedCondition")
		return ConditionBasePtr(new QuestStartedCondition());

	if(type == "QuestFinishedCondition")
		return ConditionBasePtr(new QuestFinishedCondition());

	if(type == "QuestAvailableCondition")
		return ConditionBasePtr(new QuestAvailableCondition());

	if(type == "ChapterStartedCondition")
		return ConditionBasePtr(new ChapterStartedCondition());

	if(type == "CustomCondition")
		return ConditionBasePtr(new CustomCondition());	

	if(type == "ActorMovingCondition")
		return ConditionBasePtr(new ActorMovingCondition());	

	if(type == "CheckFlagCondition")
		return ConditionBasePtr(new CheckFlagCondition());	


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
			// get text
			{
			std::string text = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();		
			text = text.substr(0, text.find(":"));
			long textid = atol(text.c_str());
			ConditionBase* cond = static_cast<ConditionBase*>(ptr);
			cond->SetTextid(textid);
			}
		
			int index = 3;

			if(category == "NegateCondition")
			{
				NegateCondition* cond = static_cast<NegateCondition*>(ptr);


				std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				std::string currcond = GetConditionType(cond->GetCondition());

				if(condition != currcond)
				{
					ConditionBasePtr ptrtmp = CreateCondition(condition);
					cond->SetCondition(ptrtmp);

					QModelIndex curidx = _objectmodel->GetIndex(0, index, parentIdx);
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
				AndCondition* cond = static_cast<AndCondition*>(ptr);

				//condition 1
				{
					std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
					std::string currcond = GetConditionType(cond->GetCondition1());

					if(condition != currcond)
					{
						ConditionBasePtr ptrtmp = CreateCondition(condition);
						cond->SetCondition1(ptrtmp);

						QModelIndex curidx = _objectmodel->GetIndex(0, index, parentIdx);
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

				++index;

				//condition 2
				{
					std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
					std::string currcond = GetConditionType(cond->GetCondition2());

					if(condition != currcond)
					{
						ConditionBasePtr ptrtmp = CreateCondition(condition);
						cond->SetCondition2(ptrtmp);

						QModelIndex curidx = _objectmodel->GetIndex(0, index, parentIdx);
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
				OrCondition* cond = static_cast<OrCondition*>(ptr);

				//condition 1
				{
					std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
					std::string currcond = GetConditionType(cond->GetCondition1());

					if(condition != currcond)
					{
						ConditionBasePtr ptrtmp = CreateCondition(condition);
						cond->SetCondition1(ptrtmp);

						QModelIndex curidx = _objectmodel->GetIndex(0, index, parentIdx);
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

				++index;

				//condition 2
				{
					std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
					std::string currcond = GetConditionType(cond->GetCondition2());

					if(condition != currcond)
					{
						ConditionBasePtr ptrtmp = CreateCondition(condition);
						cond->SetCondition2(ptrtmp);


						QModelIndex curidx = _objectmodel->GetIndex(0, index, parentIdx);
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

			if(category == "ItemInInventoryCondition")
			{
				ItemInInventoryCondition* cond = static_cast<ItemInInventoryCondition*>(ptr);
				
				std::string itid = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				itid = itid.substr(0, itid.find(":"));
				long id = atol(itid.c_str());
				cond->SetItemId(id);	

				++index;
				cond->SetItemNumber(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt());

				// need to save as something changed
				SetModified();
			}

			if(category == "QuestStartedCondition")
			{
				QuestStartedCondition* cond = static_cast<QuestStartedCondition*>(ptr);
				
				long id = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();
				cond->SetQuestId(id);		

				// need to save as something changed
				SetModified();		
			}

			if(category == "QuestFinishedCondition")
			{
				QuestFinishedCondition* cond = static_cast<QuestFinishedCondition*>(ptr);
				
				long id = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();
				cond->SetQuestId(id);

				// need to save as something changed
				SetModified();				
			}

			if(category == "ChapterStartedCondition")
			{
				ChapterStartedCondition* cond = static_cast<ChapterStartedCondition*>(ptr);
				
				int id = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();
				cond->SetChapter(id);		

				// need to save as something changed
				SetModified();		
			}

			if(category == "QuestAvailableCondition")
			{
				QuestAvailableCondition* cond = static_cast<QuestAvailableCondition*>(ptr);
				
				long id = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();
				cond->SetQuestId(id);	

				// need to save as something changed
				SetModified();			
			}

			if(category == "CustomCondition")
			{
				CustomCondition* cond = static_cast<CustomCondition*>(ptr);
				
				std::string fct = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				cond->SetLuaFunction(fct);	

				// need to save as something changed
				SetModified();			
			}

			if(category == "CheckFlagCondition")
			{
				CheckFlagCondition* cond = static_cast<CheckFlagCondition*>(ptr);
				
				std::string fct = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				cond->SetFlagName(fct);	
				++index;

				long value = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();
				cond->SetValue(value);

				// need to save as something changed
				SetModified();			
			}

			
			SetModified();
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

	if(type == "OpenContainerAction")
		return ActionBasePtr(new OpenContainerAction());

	if(type == "SendSignalAction")
		return ActionBasePtr(new SendSignalAction());

	if(type == "OpenDoorAction")
		return ActionBasePtr(new OpenDoorAction());

	if(type == "CloseDoorAction")
		return ActionBasePtr(new CloseDoorAction());

	if(type == "AddRemoveItemAction")
		return ActionBasePtr(new AddRemoveItemAction());

	if(type == "HurtAction")
		return ActionBasePtr(new HurtAction());

	if(type == "KillAction")
		return ActionBasePtr(new KillAction());

	if(type == "MultiAction")
		return ActionBasePtr(new MultiAction());

	if(type == "SwitchAction")
		return ActionBasePtr(new SwitchAction());

	if(type == "StartQuestAction")
		return ActionBasePtr(new StartQuestAction());

	if(type == "FinishQuestAction")
		return ActionBasePtr(new FinishQuestAction());

	if(type == "OpenShopAction")
		return ActionBasePtr(new OpenShopAction());

	if(type == "CutMapAction")
		return ActionBasePtr(new CutMapAction());

	if(type == "OpenLetterWritterAction")
		return ActionBasePtr(new OpenLetterWritterAction());
	
	if(type == "OpenMailboxAction")
		return ActionBasePtr(new OpenMailboxAction());
	
	if(type == "PlaySoundAction")
		return ActionBasePtr(new PlaySoundAction());
	
	if(type == "SetFlagAction")
		return ActionBasePtr(new SetFlagAction());
		
	if(type == "ShoutTextAction")
		return ActionBasePtr(new ShoutTextAction());
			
	if(type == "PlayVideoAction")
		return ActionBasePtr(new PlayVideoAction());
			
	if(type == "RandomAction")
		return ActionBasePtr(new RandomAction());
			
	if(type == "DisplayHolomapAction")
		return ActionBasePtr(new DisplayHolomapAction());

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
text lang modified
***********************************************************/
void EditorHandler::TextLangModified(int index)
{
	_currentchoosenlang = _uieditor.comboBox_chooselang->itemText(index).toAscii().data();

	_text_maplistmodel->Clear();
	_text_questlistmodel->Clear();
	_text_inventorylistmodel->Clear();
	_text_namelistmodel->Clear();

	_text_mapNameList->Clear();
	_text_questNameList->Clear();
	_text_inventoryNameList->Clear();
	_text_nameNameList->Clear();
	_text_nameNameList->AddData("No");

	{
		std::map<long, std::string> tmap = Localizer::getInstance()->GetMap(Localizer::Map, _currentchoosenlang);
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
		std::map<long, std::string> tmap = Localizer::getInstance()->GetMap(Localizer::Quest, _currentchoosenlang);
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
		std::map<long, std::string> tmap = Localizer::getInstance()->GetMap(Localizer::Inventory, _currentchoosenlang);
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
		std::map<long, std::string> tmap = Localizer::getInstance()->GetMap(Localizer::Name, _currentchoosenlang);
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

	TextTypeModified(_uieditor.comboBox_choosetexttype->currentIndex ());
}




/***********************************************************
VoicemAdd_button
***********************************************************/
void EditorHandler::VoicemAdd_button()
{
	QString currpath = Localizer::getInstance()->GetVoiceDirPath(_currentchoosenlang).c_str();

	QStringList selectedfile = 
		QFileDialog::getOpenFileNames (this, "Select a sound file", currpath, 
										"Sound (*.mp3 *.wav *.Ogg)");

	if(selectedfile.size() > 0)
	{
		QString selected = 	selectedfile[0];
		selected.replace("\\", "/");

		// check if choosen file is in the directory data
		if(selected.contains(QDir::currentPath()+"/Data/"))
		{
			selected = selected.remove(QDir::currentPath()+"/Data/");
		}
		else
		{
			//copy the file over
			try
			{
				QString newfilename = currpath;
				newfilename	+= "/" + selected.section('/', -1);
				FileUtil::MakeFileCopy(selected.toAscii().data(), newfilename.toAscii().data());

				selected = newfilename.section('/', 1);
			}
			catch(...)
			{
				QErrorMessage msgdial;
				msgdial.showMessage ( "Error copying the file to the data directory!" );
				selected = "";
			}
		}

		_ui_addtextdialog.listWidget_voice->addItem(selected);
	}
}



/***********************************************************
VoicemRem_button
***********************************************************/
void EditorHandler::VoicemRem_button()
{
	int checkc = _ui_addtextdialog.listWidget_voice->count();

	QList<QListWidgetItem *> items = _ui_addtextdialog.listWidget_voice->selectedItems();
	if(items.size() > 0)
		delete items[0];

	int checkc2 = _ui_addtextdialog.listWidget_voice->count();
}



/***********************************************************
TextAdd_button
***********************************************************/
void EditorHandler::TextAdd_button()
{
	_ui_addtextdialog.lineEdit_id->setText("");
	_ui_addtextdialog.textEdit->setPlainText("");
	_ui_addtextdialog.listWidget_voice->clear();
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

		Localizer::getInstance()->RemoveFromMap(_currentchoosentext, id, _currentchoosenlang);
		Localizer::getInstance()->RemoveFromMapVoice(_currentchoosentext, id, _currentchoosenlang);

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

		std::string txt = Localizer::getInstance()->GetText(_currentchoosentext, id, _currentchoosenlang);
		replaceinstr(txt, " @ ", "\n");


		std::stringstream idtxt;
		idtxt << id;
		_ui_addtextdialog.lineEdit_id->setText(idtxt.str().c_str());
		_ui_addtextdialog.textEdit->setPlainText(QString::fromUtf8(txt.c_str()));

		_ui_addtextdialog.listWidget_voice->clear();
		std::vector<std::string> voices = Localizer::getInstance()->GetVoices(_currentchoosentext, id, _currentchoosenlang);
		for(size_t vv=0; vv<voices.size(); ++vv)
			_ui_addtextdialog.listWidget_voice->addItem(voices[vv].c_str());

		_addtextdialog->show();
	}
}	



/***********************************************************
TextEdit_button
***********************************************************/
void EditorHandler::TextPlay_button()
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

		std::vector<std::string> voices = 
			Localizer::getInstance()->GetVoices(_currentchoosentext, id, _currentchoosenlang);
		if(voices.size() > 0)
		{
			for(size_t vv=0; vv< voices.size(); ++vv)
				voices[vv] = "Data/" + voices[vv];

			MusicHandler::getInstance()->PlayVoice(voices);
		}
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

	std::vector<std::string> voices;
	for(int ii=0; ii<_ui_addtextdialog.listWidget_voice->count(); ++ii)
		voices.push_back(_ui_addtextdialog.listWidget_voice->item(ii)->text().toAscii().data());


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

		Localizer::getInstance()->AddToMap(_currentchoosentext, id, txt, _currentchoosenlang);	
		Localizer::getInstance()->AddToMapVoice(_currentchoosentext, id, voices, _currentchoosenlang);	


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
		long newid = Localizer::getInstance()->AddToMap(_currentchoosentext, -1, txt, _currentchoosenlang);	
		Localizer::getInstance()->AddToMapVoice(_currentchoosentext, newid, voices, _currentchoosenlang);	

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
	SharedDataHandler::getInstance()->EditorUpdate("", new UpdateEditor_Refreshscript());
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
	newitem.NameTextId = 0;
	newitem.DescriptionId = 0;
	newitem.LongDescriptionId = -1;
    newitem.Max = 1;
    newitem.BuyPrice = 1;
    newitem.SellPrice = 1;
    newitem.Effect = 0;
    newitem.Effect2 = 0;
    newitem.Flag = 1;
    newitem.Ephemere = false;
	newitem.Color1 = -1;
	newitem.Color2 = -1;
	newitem.ReplaceItem = -1;



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
		case 9:
			newitem.Type = 10;
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
	SelectItem(InventoryItemHandler::getInstance()->GetItem(idx));
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
		ShowHideMapInfo(false);
		SelectItem(InventoryItemHandler::getInstance()->GetItem(id));
	}
}


/***********************************************************
set item in the object
***********************************************************/
void EditorHandler::SelectItem(boost::shared_ptr<InventoryItemDef> item, const QModelIndex &parent)
{
	if(parent == QModelIndex())
		ResetObject();

	if(!item)
		return;

	{
		QVector<QVariant> data;
		data<<"Type"<<"Item";
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"SubCategory"<<InventoryItemHandler::getInstance()->GetItemTypeString(item->GetId()).c_str();
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"Id"<<item->GetId();
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"Name"<<item->GetName().c_str();
		_objectmodel->AppendRow(data, parent);
	}

	int index = 4;
	{
		std::stringstream descstrs;
		descstrs<<item->GetNameTextId()<<": "<<Localizer::getInstance()->GetText(Localizer::Inventory, item->GetNameTextId());
		
		QVector<QVariant> data;
		data<<"Name text"<<descstrs.str().c_str();
		_objectmodel->AppendRow(data, parent);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _text_inventoryNameList);
		++index;
	}

	{
		std::stringstream descstrs;
		descstrs<<item->GetDescriptionId()<<": "<<Localizer::getInstance()->GetText(Localizer::Inventory, 
							item->GetDescriptionId());
		
		QVector<QVariant> data;
		data<<"Description"<<descstrs.str().c_str();
		_objectmodel->AppendRow(data, parent);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _text_inventoryNameList);
		++index;
	}

	{
		std::stringstream descstrs;
		descstrs<<item->GetLongDescriptionId()<<": "
			<<Localizer::getInstance()->GetText(Localizer::Inventory, item->GetLongDescriptionId());
		
		QVector<QVariant> data;
		data<<"Long Description"<<descstrs.str().c_str();
		_objectmodel->AppendRow(data, parent);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _text_inventoryNameList);
		++index;
	}

	{
		QVector<QVariant> data;
		data<<"Icon"<<item->GetIconName().c_str();
		_objectmodel->AppendRow(data, parent);

		FileDialogOptionsIcon * filterptr = new FileDialogOptionsIcon();
		filterptr->OutDirectory = ("Data/Worlds/" + _winfo.Description.WorldName + "/InventoryImages").c_str();
		boost::shared_ptr<FileDialogOptionsBase> filefilter(filterptr);
		filefilter->Title = "Select an image";
		filefilter->StartingDirectory = "Data/GUI/imagesets/Inventory";
		filefilter->FileFilter = "Images Files (*.png *.bmp *.jpg *.gif)";
		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), filefilter);


		//todo put file chooser
		++index;
	}

	{
		QVector<QVariant> data;
		data<<"Maximum number"<<item->GetMax();
		_objectmodel->AppendRow(data, parent);
		++index;
	}

	{
		QVector<QVariant> data;
		data<<"Buy price"<<item->GetBuyPrice();
		_objectmodel->AppendRow(data, parent);
		++index;
	}

	{
		QVector<QVariant> data;
		data<<"Sell price"<<item->GetSellPrice();
		_objectmodel->AppendRow(data, parent);
		++index;
	}

	{
		QVector<QVariant> data;
		data<<"Ephemere"<<item->GetEphemere();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		_objectmodel->setTooltip(idx, "If true the item will disappear when leaving the map");
		QModelIndex idx2 = _objectmodel->GetIndex(1, idx.row(), idx.parent());
		_objectmodel->setTooltip(idx2, "If true the item will disappear when leaving the map");
		++index;
	}

	{
		std::stringstream txtwithid;
		txtwithid<<item->GetReplacedItem()<<": "<<InventoryItemHandler::getInstance()->GetItemInfo(item->GetReplacedItem()).Name;

		QVector<QVariant> data;
		data<<"Replace item"<<txtwithid.str().c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), idx.parent()), _itemNameList);	

		_objectmodel->setTooltip(idx, "If item is in inventory when new item is given it will be replaced");
		QModelIndex idx2 = _objectmodel->GetIndex(1, idx.row(), idx.parent());
		_objectmodel->setTooltip(idx2, "If item is in inventory when new item is given it will be replaced");
		++index;
	}

	switch(item->GetType())
	{
		case 1: // consummable item
		{
			switch(item->GetFlag())
			{
				case 1: // life potion
				{
					QVector<QVariant> data;
					data<<"Type"<<"Restore % of Health";
					_objectmodel->AppendRow(data, parent);

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _consumable_itemlistmodel);
					++index;

					QVector<QVariant> data2;
					data2<<"Restoration in %"<<(double)item->GetEffect();
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;
				case 2: // mana potion
				{
					QVector<QVariant> data;
					data<<"Type"<<"Restore % of Magic";
					_objectmodel->AppendRow(data, parent);

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _consumable_itemlistmodel);
					++index;

					QVector<QVariant> data2;
					data2<<"Restoration in %"<<(double)item->GetEffect();
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;
				case 3: // life and mana potion
				{
					QVector<QVariant> data;
					data<<"Type"<<"Restore % of Health&Magic";
					_objectmodel->AppendRow(data, parent);

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _consumable_itemlistmodel);
					++index;

					QVector<QVariant> data2;
					data2<<"Restoration in %"<<(double)item->GetEffect();
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;

				case 4: // life potion
				{
					QVector<QVariant> data;
					data<<"Type"<<"Restore Health";
					_objectmodel->AppendRow(data, parent);

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _consumable_itemlistmodel);
					++index;

					QVector<QVariant> data2;
					data2<<"Restoration value"<<(double)item->GetEffect();
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;
				case 5: // mana potion
				{
					QVector<QVariant> data;
					data<<"Type"<<"Restore Magic";
					_objectmodel->AppendRow(data, parent);

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _consumable_itemlistmodel);
					++index;

					QVector<QVariant> data2;
					data2<<"Restoration value"<<(double)item->GetEffect();
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;
				case 6: // life and mana potion
				{
					QVector<QVariant> data;
					data<<"Type"<<"Restore Health&Magic";
					_objectmodel->AppendRow(data, parent);

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _consumable_itemlistmodel);
					++index;

					QVector<QVariant> data2;
					data2<<"Restoration value"<<(double)item->GetEffect();
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;
			}
		}
		break;

		case 3: // monture item - ride it
		{
			switch(item->GetFlag())
			{
				case 1:
				{
					QVector<QVariant> data;
					data<<"Type"<<"Protopack";
					_objectmodel->AppendRow(data, parent);

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _mount_itemlistmodel);
					++index;

					QVector<QVariant> data1;
					data1<<"Skin color"<<item->GetColor1();
					_objectmodel->AppendRow(data1, parent);
					++index;

					QVector<QVariant> data2;
					data2<<"Hair color"<<item->GetColor2();
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;
				case 2:
				{
					QVector<QVariant> data;
					data<<"Type"<<"Horse";
					_objectmodel->AppendRow(data, parent);

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _mount_itemlistmodel);
					++index;

					QVector<QVariant> data1;
					data1<<"Skin color"<<item->GetColor1();
					_objectmodel->AppendRow(data1, parent);
					++index;

					QVector<QVariant> data2;
					data2<<"Hair color"<<item->GetColor2();
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;
				case 3:
				{
					QVector<QVariant> data;
					data<<"Type"<<"Dinofly";
					_objectmodel->AppendRow(data, parent);

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _mount_itemlistmodel);
					++index;

					QVector<QVariant> data1;
					data1<<"Skin color"<<item->GetColor1();
					_objectmodel->AppendRow(data1, parent);
					++index;

					QVector<QVariant> data2;
					data2<<"Hair color"<<item->GetColor2();
					_objectmodel->AppendRow(data2, parent);
					++index;
				}
				break;
			}
		}
		break;

		case 4: // weapon item - equip it
		{
			QVector<QVariant> data;
			data<<"Power"<<(double)item->GetEffect();
			_objectmodel->AppendRow(data, parent);
			++index;

			QVector<QVariant> data2;
			data2<<"Player model"<<item->GetStringFlag().c_str();
			QModelIndex idx = _objectmodel->AppendRow(data2, parent);

			_objectmodel->setTooltip(idx, "Name of the model used to display the player wearing the weapon (see documentation)");
			QModelIndex idx2 = _objectmodel->GetIndex(1, idx.row(), idx.parent());
			_objectmodel->setTooltip(idx2, "Name of the model used to display the player wearing the weapon (see documentation)");
			++index;

			QVector<QVariant> data1;
			data1<<"Weapon color"<<item->GetColor1();
			_objectmodel->AppendRow(data1, parent);
			++index;
		
			// add projectiles
			{
				QVector<QVariant> data;
				data << "Projectiles" << "";
				QModelIndex idx = _objectmodel->AppendRow(data, parent, true);	
				++index;

				std::vector<ProjectileObjectDefPtr> & projs = item->GetProjectiles();
				for(size_t p=0; p< projs.size(); ++p)
				{
					{
						QVector<QVariant> datait;
						datait << "Projectile" << "";
						QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	
						_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _removeList);

						SelectProjectile(projs[p].get(), idxit);
					}
				}

				// add new item
				QVector<QVariant> datait;
				datait << "Projectile" << "Add new...";
				QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	
				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _addList);	
			}
		}
		break;

		case 7: // Actionable item
		{

			ActionBasePtr actptr = item->GetAction();
			std::string acttype = GetActionType(actptr);

			QVector<QVariant> data;
			data << "Action" << acttype.c_str();
			QModelIndex idx = _objectmodel->AppendRow(data, parent);
			
			if(actptr)
				SelectAction(actptr.get(), idx);

			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actiontypeList);

			++index;
		}
		break;

		case 9: // outfit item - equip it
		{
			QVector<QVariant> data;
			data<<"Armor"<<(double)item->GetEffect();
			_objectmodel->AppendRow(data, parent);
			++index;

			QVector<QVariant> dataX;
			dataX<<"Fist power"<<(double)item->GetEffect2();
			_objectmodel->AppendRow(dataX, parent);
			++index;

			QVector<QVariant> data2;
			data2<<"Player model"<<item->GetStringFlag().c_str();
			QModelIndex idx = _objectmodel->AppendRow(data2, parent);

			_objectmodel->setTooltip(idx, "Name of the model used to display the player wearing the outfit (see documentation)");
			QModelIndex idx2 = _objectmodel->GetIndex(1, idx.row(), idx.parent());
			_objectmodel->setTooltip(idx2, "Name of the model used to display the player wearing the outfit (see documentation)");
			++index;

			QVector<QVariant> data1;
			data1<<"Outfit color"<<item->GetColor1();
			_objectmodel->AppendRow(data1, parent);
			++index;
		}
		break;

		case 10: // container item
		{
			// add items
			{
				QVector<QVariant> data;
				data << "Item list" << "";
				QModelIndex idx = _objectmodel->AppendRow(data, parent, true);	
				++index;

				const std::vector<LbaNet::ItemGroupElement> & items = item->GetContainedItemList();
				for(size_t i=0; i<items.size(); ++i)
				{
					std::stringstream txtwithid;
					txtwithid<<items[i].Id<<": "<<InventoryItemHandler::getInstance()->GetItemInfo(items[i].Id).Name;

					QVector<QVariant> datait;
					datait << "Item" << txtwithid.str().c_str();
					QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	

					//add min
					{
						QVector<QVariant> datachild;
						datachild << "Min" << items[i].Min;
						QModelIndex idx1 = _objectmodel->AppendRow(datachild, idxit);	

						// add tooltip
						_objectmodel->setTooltip(idx1, "Minimum number of item to spawn");
						QModelIndex idx2 = _objectmodel->GetIndex(1, idx1.row(), idx1.parent());
						_objectmodel->setTooltip(idx2, "Minimum number of item to spawn");
					}

					//add max
					{
						QVector<QVariant> datachild;
						datachild << "Max" << items[i].Max;
						QModelIndex idx1 = _objectmodel->AppendRow(datachild, idxit);		

						// add tooltip
						_objectmodel->setTooltip(idx1, "Maximum number of item to spawn");
						QModelIndex idx2 = _objectmodel->GetIndex(1, idx1.row(), idx1.parent());
						_objectmodel->setTooltip(idx2, "Maximum number of item to spawn");
					}

					//add probability
					{
						QVector<QVariant> datachild;
						datachild << "Probability" << (double)items[i].Probability;
						QModelIndex idx1 = _objectmodel->AppendRow(datachild, idxit);			

						// add tooltip
						_objectmodel->setTooltip(idx1, "Probability of the item to spawn (1 = 100%)");
						QModelIndex idx2 = _objectmodel->GetIndex(1, idx1.row(), idx1.parent());
						_objectmodel->setTooltip(idx2, "Probability of the item to spawn (1 = 100%)");
					}

					//add group
					{
						QVector<QVariant> datachild;
						datachild << "Group" << items[i].Group;
						QModelIndex idx1 = _objectmodel->AppendRow(datachild, idxit);				

						// add tooltip
						_objectmodel->setTooltip(idx1, "The items part of the same group are mutually exclusive");
						QModelIndex idx2 = _objectmodel->GetIndex(1, idx1.row(), idx1.parent());
						_objectmodel->setTooltip(idx2, "The items part of the same group are mutually exclusive");
					}

					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _itemNameList);	
				}

				// add new item
				QVector<QVariant> datait;
				datait << "Item" << "Add item...";
				QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	
				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _itemNameList);	
					
				_uieditor.treeView_object->setExpanded(idx, true); // expand 
			}	
		}
		break;
	}

	const LbaNet::ModelInfo &mdisinfo = item->GetDisplayInfo();
	std::string dtype = "No";
	switch(mdisinfo.TypeRenderer)
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
		data<<"Map Display Type"<<dtype.c_str();
		_objectmodel->AppendRow(data, parent);
		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actordtypeList);
		++index;
	}
	

	if(dtype != "No")
	{
		{
			QVector<QVariant> data;
			data<<"Use Light"<<mdisinfo.UseLight;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Cast shadow"<<mdisinfo.CastShadow;
			_objectmodel->AppendRow(data, parent);
			++index;
		}

		{
			QVector<QVariant> data;
			data<<"Display translation X"<<(double)mdisinfo.TransX;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display translation Y"<<(double)mdisinfo.TransY;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display translation Z"<<(double)mdisinfo.TransZ;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display rotation X"<<(double)mdisinfo.RotX;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display rotation Y"<<(double)mdisinfo.RotY;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display rotation Z"<<(double)mdisinfo.RotZ;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display scale X"<<(double)mdisinfo.ScaleX;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display scale Y"<<(double)mdisinfo.ScaleY;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display scale Z"<<(double)mdisinfo.ScaleZ;
			_objectmodel->AppendRow(data, parent);
			++index;
		}


		if(mdisinfo.TypeRenderer == RenderOsgModel )
		{
			QVector<QVariant> data;
			data<<"Display model file"<<mdisinfo.ModelName.c_str();
			_objectmodel->AppendRow(data, parent);

			_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, index, parent), "Select a model file", "Models", "Model Files (*.osg *.osgb *.osgt)");
			++index;
		}

		if(mdisinfo.TypeRenderer == RenderSprite )
		{
			QVector<QVariant> data;
			data<<"Display sprite file"<<mdisinfo.ModelName.c_str();
			_objectmodel->AppendRow(data, parent);

			_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, index, parent), "Select an image", "Sprites", "Image Files (*.png *.bmp *.jpg *.gif)");
			++index;

			{
				QVector<QVariant> data1;
				data1<<"Color R"<<(double)mdisinfo.ColorR;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color G"<<(double)mdisinfo.ColorG;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color B"<<(double)mdisinfo.ColorB;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color A"<<(double)mdisinfo.ColorA;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Use Billboard"<<mdisinfo.UseBillboard;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
		}

		// add materials
		{
			QVector<QVariant> data;
			data<<"Use alpha material"<<mdisinfo.UseTransparentMaterial;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Alpha"<<(double)mdisinfo.MatAlpha;
			_objectmodel->AppendRow(data, parent);
			++index;
		}

		int matcolortype = mdisinfo.ColorMaterialType;
		{
			std::string mattypestring = "Off";
			switch(matcolortype)
			{
				case 1:
					mattypestring = "Ambient";
				break;
				case 2:
					mattypestring = "Diffuse";
				break;
				case 3:
					mattypestring = "Specular";
				break;
				case 4:
					mattypestring = "Emission";
				break;
				case 5:
					mattypestring = "Ambient_And_Diffuse";
				break;
			}
			QVector<QVariant> data;
			data<<"Color material type"<<mattypestring.c_str();
			_objectmodel->AppendRow(data, parent);
				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _materialtypeList);
			++index;	
		}

		if(matcolortype > 0)
		{
			{
			QVector<QVariant> data;
			data<<"Mat Ambient ColorR"<<(double)mdisinfo.MatAmbientColorR;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Ambient ColorG"<<(double)mdisinfo.MatAmbientColorG;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Ambient ColorB"<<(double)mdisinfo.MatAmbientColorB;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Ambient ColorA"<<(double)mdisinfo.MatAmbientColorA;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}

			{
			QVector<QVariant> data;
			data<<"Mat Diffuse ColorR"<<(double)mdisinfo.MatDiffuseColorR;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Diffuse ColorG"<<(double)mdisinfo.MatDiffuseColorG;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Diffuse ColorB"<<(double)mdisinfo.MatDiffuseColorB;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Diffuse ColorA"<<(double)mdisinfo.MatDiffuseColorA;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}

			{
			QVector<QVariant> data;
			data<<"Mat Specular ColorR"<<(double)mdisinfo.MatSpecularColorR;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Specular ColorG"<<(double)mdisinfo.MatSpecularColorG;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Specular ColorB"<<(double)mdisinfo.MatSpecularColorB;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Specular ColorA"<<(double)mdisinfo.MatSpecularColorA;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}

			{
			QVector<QVariant> data;
			data<<"Mat Emission ColorR"<<(double)mdisinfo.MatEmissionColorR;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Emission ColorG"<<(double)mdisinfo.MatEmissionColorG;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Emission ColorB"<<(double)mdisinfo.MatEmissionColorB;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Emission ColorA"<<(double)mdisinfo.MatEmissionColorA;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Shininess"<<(double)mdisinfo.MatShininess;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
		}	
	}

}


/***********************************************************
item object changed
***********************************************************/
void EditorHandler::ItemChanged(long id, const std::string & category, const QModelIndex &parentIdx)
{
	SetModified();

	LbaNet::ItemInfo olditeminfo = InventoryItemHandler::getInstance()->GetItemInfo(id);
	InventoryItemDefPtr olditem = InventoryItemHandler::getInstance()->GetItem(id);

	
	InventoryItemDefPtr newiteminfo(new InventoryItemDef(olditeminfo));
	newiteminfo->SetAction(InventoryItemHandler::getInstance()->GetItemAction(id));
	newiteminfo->SetName(_objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toString().toAscii().data());
	newiteminfo->GetProjectiles().swap(olditem->GetProjectiles());


	// check if name changed
	if(newiteminfo->GetName() != olditeminfo.Name)
	{
		std::stringstream oldtxtwithid;
		oldtxtwithid<<id<<": "<<olditeminfo.Name.c_str();	

		std::stringstream txtwithid;
		txtwithid<<id<<": "<<newiteminfo->GetName().c_str();	

		// update trigger name list
		_itemNameList->ReplaceData(oldtxtwithid.str().c_str(), txtwithid.str().c_str());

		// update trigger list display
		QStringList slist;
		slist << newiteminfo->GetName().c_str() << InventoryItemHandler::getInstance()->GetItemTypeString(id).c_str();
		_itemlistmodel->AddOrUpdateRow(id, slist);
	}



	int index = 4;
	{
	std::string desc = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
	std::string tmp = desc.substr(0, desc.find(":"));
	newiteminfo->SetNameTextId(atol(tmp.c_str()));
	++index;
	}
	{
	std::string desc = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
	std::string tmp = desc.substr(0, desc.find(":"));
	newiteminfo->SetDescriptionId(atol(tmp.c_str()));
	++index;
	}
	{
	std::string desc = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
	std::string tmp = desc.substr(0, desc.find(":"));
	newiteminfo->SetLongDescriptionId(atol(tmp.c_str()));
	++index;
	}

	newiteminfo->SetIconName(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data());
	++index;

	newiteminfo->SetMax(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt());
	++index;

	newiteminfo->SetBuyPrice(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt());
	++index;

	newiteminfo->SetSellPrice(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt());
	++index;

	newiteminfo->SetEphemere(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool());
	++index;


	std::string replacedid = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
	if(replacedid == "No item")
		newiteminfo->SetReplacedItem(-1);
	else
	{
		std::string tmp = replacedid.substr(0, replacedid.find(":"));
		newiteminfo->SetReplacedItem(atol(tmp.c_str()));
	}
	++index;


	bool refresh = false;
	switch(newiteminfo->GetType())
	{
		case 1: // consummable item
		{
			std::string flag = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
			if(flag == "Restore % of Health")
				newiteminfo->SetFlag(1);
			if(flag == "Restore % of Magic")
				newiteminfo->SetFlag(2);
			if(flag == "Restore % of Health&Magic")
				newiteminfo->SetFlag(3);
			if(flag == "Restore Health")
				newiteminfo->SetFlag(4);
			if(flag == "Restore Magic")
				newiteminfo->SetFlag(5);
			if(flag == "Restore Health&Magic")
				newiteminfo->SetFlag(6);
			++index;

			newiteminfo->SetEffect(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat());
			++index;
		}
		break;

		case 3: // monture item - ride it
		{
			std::string flag = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
			if(flag == "Protopack")
				newiteminfo->SetFlag(1);
			if(flag == "Horse")
				newiteminfo->SetFlag(2);
			if(flag == "Dinofly")
				newiteminfo->SetFlag(3);
			++index;

			newiteminfo->SetColor1(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt());
			++index;
			newiteminfo->SetColor2(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt());
			++index;
		}
		break;

		case 4: // weapon item - equip it
		{
			newiteminfo->SetEffect(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat());
			++index;

			newiteminfo->SetStringFlag(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data());
			++index;

			newiteminfo->SetColor1(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt());
			++index;


			// projectiles
			{
				QModelIndex itemparent = _objectmodel->GetIndex(0, index, parentIdx);
				++index;
				int curridx = 0;

				std::vector<ProjectileObjectDefPtr> & childs = newiteminfo->GetProjectiles();
				for(size_t gg=0; gg< childs.size(); ++gg)
				{
					QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent);
					std::string check = _objectmodel->data(childidx).toString().toAscii().data();
					++curridx;

					if(check == "Remove")
					{
						newiteminfo->RemoveProjectile(childs[gg]);
						refresh = true;
						break;
					}
				}

				if(!refresh)
				{
					QModelIndex childidx0 = _objectmodel->GetIndex(0, curridx, itemparent);
					QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent);
					std::string check = _objectmodel->data(childidx).toString().toAscii().data();
					if(check == "Add")
					{
						ProjectileObjectDefPtr newd(new ProjectileObjectDef());
						newiteminfo->AddProjectile(newd);

						{
						// add new item
						QVector<QVariant> datait;
						datait << "Projectile" << "Add new...";
						QModelIndex idxit = _objectmodel->AppendRow(datait, itemparent);	
						_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _addList);	
						}

						{
						SelectProjectile(newd.get(), childidx0);
						_objectmodel->SetCustomIndex(childidx, _removeList);
						_objectmodel->setData(childidx, "");
						_uieditor.treeView_object->setExpanded(childidx0, true); // expand 
						}
					}
				}
			}
		}
		break;

		case 7: // actionable item
		{
			std::string curract = GetActionType(newiteminfo->GetAction());
			std::string action1 = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
	
			if(action1 != curract)
			{
				ActionBasePtr ptrtmp = CreateAction(action1);
				newiteminfo->SetAction(ptrtmp);

				QModelIndex curidx = _objectmodel->GetIndex(0, index, parentIdx);
				_objectmodel->Clear(curidx);
				if(ptrtmp)
				{
					SelectAction(ptrtmp.get(), curidx);

					_uieditor.treeView_object->setExpanded(curidx, true); // expand 
				}
			}

			++index;
		}
		break;

		case 9: // outfit item - equip it
		{
			newiteminfo->SetEffect(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat());
			++index;

			newiteminfo->SetEffect2(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat());
			++index;

			newiteminfo->SetStringFlag(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data());
			++index;

			newiteminfo->SetColor1(_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt());
			++index;
		}
		break;

		case 10: // container item
		{
			QModelIndex itemparent = _objectmodel->GetIndex(0, index, parentIdx);
			int curridx = 0;
			++index;

			//take care of the items
			std::vector<LbaNet::ItemGroupElement> &items = newiteminfo->GetContainedItemList();
			std::vector<LbaNet::ItemGroupElement>::iterator itit = items.begin();
			for(;itit != items.end(); ++itit)
			{
				QModelIndex childidx = _objectmodel->GetIndex(0, curridx, itemparent);
				std::string id = _objectmodel->data(_objectmodel->GetIndex(1, curridx, itemparent))
																		.toString().toAscii().data();
				++curridx;

				if(id == "No item")
				{
					// need to remove the item
					items.erase(itit);

					_objectmodel->Clear(parentIdx);
					refresh = true;
					break;
				}

				std::string tmp = id.substr(0, id.find(":"));
				itit->Id = atol(tmp.c_str());
				itit->Min = _objectmodel->data(_objectmodel->GetIndex(1, 0, childidx)).toInt();
				itit->Max = _objectmodel->data(_objectmodel->GetIndex(1, 1, childidx)).toInt();
				itit->Probability = _objectmodel->data(_objectmodel->GetIndex(1, 2, childidx)).toFloat();
				itit->Group = _objectmodel->data(_objectmodel->GetIndex(1, 3, childidx)).toInt();
			}

			QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent);
			std::string id = _objectmodel->data(childidx).toString().toAscii().data();
			if(id != "Add item...")
			{
				if(id == "No item")
				{
					_objectmodel->setData(childidx, "Add item...");
				}
				else
				{
					// add new item
					std::string tmp = id.substr(0, id.find(":"));
					long itmid = atol(tmp.c_str());

					LbaNet::ItemGroupElement newitem;
					newitem.Id = itmid;
					newitem.Min = 1;
					newitem.Max = 1;
					newitem.Probability = 1;
					newitem.Group = -1;
					items.push_back(newitem);

					_objectmodel->Clear(parentIdx);
					refresh = true;
				}
			}

		}
		break;
	}

	LbaNet::ModelInfo & olddisinfo = olditem->GetDisplayInfo();
	LbaNet::ModelInfo & newdisinfo = newiteminfo->GetDisplayInfo();

	std::string dtype = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
	++index;
	if(dtype == "Osg Model") 
		newdisinfo.TypeRenderer = LbaNet::RenderOsgModel;
	if(dtype == "Sprite") 
		newdisinfo.TypeRenderer = LbaNet::RenderSprite;
	if(dtype == "Lba1 Model") 
		newdisinfo.TypeRenderer = LbaNet::RenderLba1M;
	if(dtype == "Lba2 Model") 
		newdisinfo.TypeRenderer = LbaNet::RenderLba2M;

	if(olddisinfo.TypeRenderer != newdisinfo.TypeRenderer)
		refresh = true;


	if(!refresh)	
	{
		if(olddisinfo.TypeRenderer != LbaNet::NoRender)
		{
			newdisinfo.UseLight = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
			++index;
			newdisinfo.CastShadow = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
			++index;

			newdisinfo.TransX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			newdisinfo.TransY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			newdisinfo.TransZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;

			newdisinfo.RotX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			newdisinfo.RotY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			newdisinfo.RotZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;

			newdisinfo.ScaleX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			newdisinfo.ScaleY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			newdisinfo.ScaleZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;


			if(olddisinfo.TypeRenderer == RenderOsgModel )
			{
				newdisinfo.ModelName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				++index;
			}

			if(olddisinfo.TypeRenderer == RenderSprite )
			{
				newdisinfo.ModelName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				++index;	

				newdisinfo.ColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;	

				newdisinfo.ColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;		

				newdisinfo.ColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;		

				newdisinfo.ColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;	

				newdisinfo.UseBillboard = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
				++index;	
			}

			// check materials
			newdisinfo.UseTransparentMaterial = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();		
			++index;
			newdisinfo.MatAlpha = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		
			++index;

			int oldmatcolortype = olddisinfo.ColorMaterialType;

			std::string matstringtype = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();	
			++index;

			newdisinfo.ColorMaterialType = 0;
			if(matstringtype == "Ambient")
				newdisinfo.ColorMaterialType = 1;
			if(matstringtype == "Diffuse")
				newdisinfo.ColorMaterialType = 2;
			if(matstringtype == "Specular")
				newdisinfo.ColorMaterialType = 3;
			if(matstringtype == "Emission")
				newdisinfo.ColorMaterialType = 4;
			if(matstringtype == "Ambient_And_Diffuse")
				newdisinfo.ColorMaterialType = 5;

			if(newdisinfo.ColorMaterialType != oldmatcolortype)
				refresh = true;


			if(oldmatcolortype > 0)
			{
				newdisinfo.MatAmbientColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatAmbientColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatAmbientColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatAmbientColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatDiffuseColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatDiffuseColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatDiffuseColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatDiffuseColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatSpecularColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatSpecularColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatSpecularColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatSpecularColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;	
				newdisinfo.MatEmissionColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatEmissionColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatEmissionColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatEmissionColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;	
				newdisinfo.MatShininess = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;				
			}	
		}
	}


	InventoryItemHandler::getInstance()->SetItem(newiteminfo);

	if(refresh || ((newiteminfo->GetType() == 1) && (newiteminfo->GetFlag() != olditeminfo.Flag)))
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
	if(name == "No item")
		return;

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

/***********************************************************
player colors modified
***********************************************************/
void EditorHandler::colorModified(int v)
{
	int cskin = _uieditor.spinBox_cskin->value();	
	int ceyes = _uieditor.spinBox_ceyes->value();	
	int chair = _uieditor.spinBox_chair->value();		
	int coutfit = _uieditor.spinBox_coutfit->value();	
	int cweapon = _uieditor.spinBox_cweapon->value();		
	int cmount = _uieditor.spinBox_cmount->value();	
	int cmount2 = _uieditor.spinBox_cmount2->value();	


	EditorUpdateBasePtr update = new ChangeColorEvent(cskin, ceyes, chair, coutfit, cweapon, cmount, cmount2);

	SharedDataHandler::getInstance()->EditorUpdate(_uieditor.label_mapname->text().toAscii().data(), update);

}	



/***********************************************************
select dialog and put info in object list
***********************************************************/
void EditorHandler::SelectDialog(DialogPart* dialog, const QModelIndex &parent)
{
	if(parent == QModelIndex())
		ResetObject();

	if(!dialog)
		return;

	// add pointer for later change
	_modelidxdatamap[parent] = (void*)dialog;

	{
		QVector<QVariant> data;
		data<<"Type"<<"Dialog";
		_objectmodel->AppendRow(data, parent, true);
	}

	// add condition
	{
		ConditionBasePtr condptr = dialog->GetCondition();

		QVector<QVariant> data;
		data << "Display condition" << GetConditionType(condptr).c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		if(condptr)
			SelectCondition(condptr, idx);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _conditiontypeList);
	}

	// add action
	{
		ActionBasePtr actptr = dialog->GetAction();
		std::string acttype = GetActionType(actptr);

		QVector<QVariant> data;
		data << "Associated action" << acttype.c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		
		if(actptr)
			SelectAction(actptr.get(), idx);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _actiontypeList);
	}	

	// text
	{
		long tid = -1;
		std::set<long> tlist = dialog->GetTextList();
		if(tlist.size() > 0)
			tid = *(tlist.begin());

		std::string txt = Localizer::getInstance()->GetText(Localizer::Map, tid);
		std::stringstream txttmp;
		txttmp<<tid<<": "<<txt;

		QVector<QVariant> data;
		data<<"Text"<<QString::fromUtf8(txttmp.str().c_str());
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _text_mapNameList);
	}

	{
		QVector<QVariant> data;
		data<<"Reset dialog"<<dialog->ResetDialog();
		_objectmodel->AppendRow(data, parent);
	}

	// add child dialogs
	{

		QVector<QVariant> data;
		data<<"Child Dialogs"<<"";
		QModelIndex idx = _objectmodel->AppendRow(data, parent, true);


		std::vector<DialogPartPtr> childs = dialog->GetChilds();
		for(size_t gg=0; gg< childs.size(); ++gg)
		{
			QVector<QVariant> datait;
			datait << "Dialog" << gg;
			QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), dialog->GetChildSize());	

			SelectDialog(childs[gg].get(), idxit);
		}


		// add new item
		QVector<QVariant> datait;
		datait << "Dialog" << "Add new...";
		QModelIndex idxit = _objectmodel->AppendRow(datait, idx);	
		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _addList);	
	
	
		_uieditor.treeView_object->setExpanded(idx, true); // expand 
	}
}


/***********************************************************
called when dialog changed
***********************************************************/
void EditorHandler::DialogChanged(const QModelIndex &parentIdx)
{
	std::map<QModelIndex, void *>::iterator it = _modelidxdatamap.find(parentIdx);
	if(it != _modelidxdatamap.end())
	{
		DialogPart * ptr = (DialogPart*)it->second;
		if(ptr)
		{	
			// need to save as something changed
			SetModified();

			//get condition info
			{
				std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, 1, parentIdx)).toString().toAscii().data();
				std::string currcond = GetConditionType(ptr->GetCondition());

				if(condition != currcond)
				{
					ConditionBasePtr ptrtmp = CreateCondition(condition);
					ptr->Setcondition(ptrtmp);

					QModelIndex curidx = _objectmodel->GetIndex(0, 1, parentIdx);
					_objectmodel->Clear(curidx);
					if(ptrtmp)
					{
						SelectCondition(ptrtmp, curidx);

						_uieditor.treeView_object->setExpanded(curidx, true); // expand 
					}
				}
			}

			// get action info
			{
				std::string action = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();
				std::string curract = GetActionType(ptr->GetAction());

				if(action != curract)
				{
					ActionBasePtr ptrtmp = CreateAction(action);
					ptr->SetAction(ptrtmp);

					QModelIndex curidx = _objectmodel->GetIndex(0, 2, parentIdx);
					_objectmodel->Clear(curidx);
					if(ptrtmp)
					{
						SelectAction(ptrtmp.get(), curidx);

						_uieditor.treeView_object->setExpanded(curidx, true); // expand 
					}

				}
			}

			// get text info
			{
				std::string text = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toString().toAscii().data();		
				text = text.substr(0, text.find(":"));
				long textid = atol(text.c_str());
				ptr->SetText(textid);
			}

			// reset dialog
			{
				bool reset = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toBool();		
				ptr->SetResetDialog(reset);
			}


			// get child dialog info
			{
				QModelIndex itemparent = _objectmodel->GetIndex(0, 5, parentIdx);
				int curridx = 0;

				std::vector<DialogPartPtr> childs = ptr->GetChilds();
				for(size_t gg=0; gg< childs.size(); ++gg)
				{
					QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent);
					std::string check = _objectmodel->data(childidx).toString().toAscii().data();
					++curridx;

					if(check == "Remove")
					{
						ptr->RemoveChild(childs[gg]);

						_objectmodel->Clear(parentIdx);
						SelectDialog(ptr, parentIdx);
						return;
					}
					else
					{
						if(check == "")
						{
							std::stringstream strsnum;
							strsnum<<gg;
							_objectmodel->setData(childidx, strsnum.str().c_str());	
						}
						else
						{
							long idxnow = atol(check.c_str());
							if(idxnow != gg)
							{
								ptr->UpdateChildPosition(childs[gg], idxnow);
								_objectmodel->Clear(parentIdx);
								SelectDialog(ptr, parentIdx);
								return;
							}
						}
					}
				}

				QModelIndex childidx0 = _objectmodel->GetIndex(0, curridx, itemparent);
				QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent);
				std::string check = _objectmodel->data(childidx).toString().toAscii().data();
				if(check == "Add")
				{
					DialogPartPtr newd(new DialogPart());
					int indexcc = ptr->AddChild(newd);

					{
					// add new item
					QVector<QVariant> datait;
					datait << "Dialog" << "Add new...";
					QModelIndex idxit = _objectmodel->AppendRow(datait, itemparent);	
					_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _addList);	
					}

					{
					std::stringstream strnum;
					strnum<<indexcc;
					SelectDialog(newd.get(), childidx0);
					_objectmodel->SetCustomIndex(childidx, ptr->GetChildSize());
					_objectmodel->setData(childidx, strnum.str().c_str());
					_uieditor.treeView_object->setExpanded(childidx0, true); // expand 
					}

					return;
				}
			}
		}
	}
}


/***********************************************************
set teleport in the object
***********************************************************/
void EditorHandler::SelectTeleport(long id, const QModelIndex &parent)
{
	boost::shared_ptr<TeleportDef> tp = SharedDataHandler::getInstance()->GetTeleport(id);
	if(!tp)
		return;

	if(parent == QModelIndex())
		ResetObject();


	{
		QVector<QVariant> data;
		data<<"Type"<<"Teleport";
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
		data<<"Name"<<tp->GetName().c_str();
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"Map name"<<tp->GetMapName().c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _mapNameList);
	}

	{	
		std::string spawningname;
		LbaNet::MapsSeq::iterator itmap = _winfo.Maps.find(tp->GetMapName());
		if(itmap != _winfo.Maps.end())
		{
			boost::shared_ptr<Spawn> spwn = SharedDataHandler::getInstance()->GetSpawn(tp->GetMapName(), tp->GetSpawn());
			if(spwn)
				spawningname = spwn->GetName();
		}

		QVector<QVariant> data;
		data << "Spawn" << spawningname.c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		std::map<std::string, boost::shared_ptr<CustomStringListModel> >::iterator it = 
													_mapSpawningList.find(tp->GetMapName());
		if(it != _mapSpawningList.end())
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), it->second);
	}



	// add condition
	{
		std::string condtype = "No";
		ConditionBasePtr condptr = tp->GetCondition();
		if(condptr)
		{
			condtype = condptr->GetTypeName();
		}

		QVector<QVariant> data;
		data << "Condition" << condtype.c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _conditiontypeList);

		if(condptr)
			SelectCondition(condptr, idx);
	}

}


/***********************************************************
called when teleport object changed
***********************************************************/
void EditorHandler::TeleportChanged(long id, const QModelIndex &parentIdx)
{
	boost::shared_ptr<TeleportDef> tp = SharedDataHandler::getInstance()->GetTeleport(id);
	if(!tp)
		return;

	// get info
	std::string name = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toString().toAscii().data();
	std::string mapname = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toString().toAscii().data();
	std::string spawning = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toString().toAscii().data();

	std::string oldmapname = tp->GetMapName();


	// get id associated to spawning
	long spid = SharedDataHandler::getInstance()->GetSpawnId(mapname, spawning);

	// update action
	tp->SetName(name);
	tp->SetMapName(mapname);
	tp->SetSpawn(spid);


	// refresh spawning list for teleport
	if(oldmapname != mapname)
	{
		std::map<std::string, boost::shared_ptr<CustomStringListModel> >::iterator it = 
			_mapSpawningList.find(mapname);
		if(it != _mapSpawningList.end())
		{
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 5, parentIdx), it->second);

			spawning = "";
			QStringList lst = it->second->stringList();
			if(lst.size() > 0)
			{
				_objectmodel->setData(_objectmodel->GetIndex(1, 5, parentIdx), lst[0]);	
				spawning = lst[0].toAscii().data();
			}
		}
	}


	// refresh list
	{
	QStringList data;
	data << name.c_str() << mapname.c_str() << spawning.c_str();
	_tplistmodel->AddOrUpdateRow(id, data);
	}



	// check condition part
	{
		std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, 6, parentIdx)).toString().toAscii().data();
		std::string currcond = GetConditionType(tp->GetCondition());

		if(condition != currcond)
		{
			ConditionBasePtr ptrtmp = CreateCondition(condition);
			tp->SetCondition(ptrtmp);

			QModelIndex curidx = _objectmodel->GetIndex(0, 6, parentIdx);
			_objectmodel->Clear(curidx);
			if(ptrtmp)
			{
				SelectCondition(ptrtmp, curidx);

				_uieditor.treeView_object->setExpanded(curidx, true); // expand 
			}

		}
	}



	// need to save as something changed
	SetModified();
}



/***********************************************************
QuestAdd_button
***********************************************************/
void EditorHandler::QuestAdd_button()
{
	long qid = QuestHandler::getInstance()->GenerateQuestid();
	QuestPtr newQuest(new Quest(qid));
	QuestHandler::getInstance()->AddQuest(newQuest);

	QStringList data;
	data << "-1" << "-1";
	_questlistmodel->AddOrUpdateRow(qid, data);

	SetModified();
	SelectQuest(qid);
}


/***********************************************************
QuestRemove_button
***********************************************************/
void EditorHandler::QuestRemove_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_QuestList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	if(indexes.size() > 0)
	{
		long id = _questlistmodel->GetId(indexes[0]);
		QuestHandler::getInstance()->RemoveQuest(id);

		_questlistmodel->removeRows(indexes[0].row(), 1);

		SetModified();
	}
}


/***********************************************************
QuestSelect_button
***********************************************************/
void EditorHandler::QuestSelect_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_QuestList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	if(indexes.size() > 0)
	{
		long id = _questlistmodel->GetId(indexes[0]);
		ShowHideMapInfo(false);
		SelectQuest(id);
	}
}

/***********************************************************
on selectitem_double_clicked
***********************************************************/
void EditorHandler::selectquest_double_clicked(const QModelIndex & itm)
{
	QuestSelect_button();		
}



/***********************************************************
set Quest in the object
***********************************************************/
void EditorHandler::SelectQuest(long id, const QModelIndex &parent)
{
	QuestPtr qu = QuestHandler::getInstance()->GetQuest(id);
	if(!qu)
		return;

	if(parent == QModelIndex())
		ResetObject();


	{
		QVector<QVariant> data;
		data<<"Type"<<"Quest";
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
		data<<"Chapter"<<qu->GetChapter();
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"Visible"<<qu->GetVisible();
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"Holomap LocId"<<qu->GetLinkedHoloLocId();
		_objectmodel->AppendRow(data, parent);
	}

	// location
	{
		long tid = qu->GetLocationTextId();
		std::string txt = Localizer::getInstance()->GetText(Localizer::Quest, tid);
		std::stringstream txttmp;
		txttmp<<tid<<": "<<txt;

		QVector<QVariant> data;
		data<<"Location"<<QString::fromUtf8(txttmp.str().c_str());
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _text_questNameList);
	}

	// title
	{
		long tid = qu->GetTitleTextId();
		std::string txt = Localizer::getInstance()->GetText(Localizer::Quest, tid);
		std::stringstream txttmp;
		txttmp<<tid<<": "<<txt;

		QVector<QVariant> data;
		data<<"Title"<<QString::fromUtf8(txttmp.str().c_str());
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _text_questNameList);
	}

	// description
	{
		long tid = qu->GetDescriptionTextId();
		std::string txt = Localizer::getInstance()->GetText(Localizer::Quest, tid);
		std::stringstream txttmp;
		txttmp<<tid<<": "<<txt;

		QVector<QVariant> data;
		data<<"Description"<<QString::fromUtf8(txttmp.str().c_str());
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _text_questNameList);
	}


	// action at start
	{
		ActionBasePtr actptr = qu->GetActionAtStart();
		std::string acttype = GetActionType(actptr);

		QVector<QVariant> data;
		data << "Action at start" << acttype.c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		
		if(actptr)
			SelectAction(actptr.get(), idx);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _actiontypeList);
	}	

	// action at end
	{
		ActionBasePtr actptr = qu->GetActionAtComplete();
		std::string acttype = GetActionType(actptr);

		QVector<QVariant> data;
		data << "Action at end" << acttype.c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		
		if(actptr)
			SelectAction(actptr.get(), idx);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _actiontypeList);
	}


	// add conditions
	{

		QVector<QVariant> data;
		data<<"Conditions"<<"";
		QModelIndex idx = _objectmodel->AppendRow(data, parent, true);
		DisplayConditions(qu->GetConditions(), idx);
	}
}


/***********************************************************
display conditions
***********************************************************/
void EditorHandler::DisplayConditions(std::vector<ConditionBasePtr> conds, const QModelIndex &parent)
{
	_objectmodel->Clear(parent);

	for(size_t gg=0; gg< conds.size(); ++gg)
	{
		std::string condtype = "No";
		ConditionBasePtr condptr = conds[gg];
		if(condptr)
			condtype = condptr->GetTypeName();

		QVector<QVariant> data;
		data << "Condition" << condtype.c_str();
		QModelIndex idxit = _objectmodel->AppendRow(data, parent);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), parent), _conditiontypeList);

		if(condptr)
			SelectCondition(condptr, idxit);
	}

	// add new item
	QVector<QVariant> datait;
	datait << "Condition" << "Add new...";
	QModelIndex idxit = _objectmodel->AppendRow(datait, parent);	
	_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _conditiontypeList);	


	_uieditor.treeView_object->setExpanded(parent, true); // expand 
}


/***********************************************************
called when Quest object changed
***********************************************************/
void EditorHandler::QuestChanged(long id, const QModelIndex &parentIdx)
{
	QuestPtr qu = QuestHandler::getInstance()->GetQuest(id);
	if(!qu)
		return;

	// get info
	int chapter = _objectmodel->data(_objectmodel->GetIndex(1, 3, parentIdx)).toInt();
	bool visible = _objectmodel->data(_objectmodel->GetIndex(1, 4, parentIdx)).toBool();
	qu->SetChapter(chapter);
	qu->SetVisible(visible);

	long hololocid = _objectmodel->data(_objectmodel->GetIndex(1, 5, parentIdx)).toInt();
	qu->SetLinkedHoloLocId(hololocid);

	SetModified();



	// get text
	QString txtLoc; 
	{
		txtLoc =_objectmodel->data(_objectmodel->GetIndex(1, 6, parentIdx)).toString();
		std::string text = txtLoc.toAscii().data();
		text = text.substr(0, text.find(":"));
		long textid = atol(text.c_str());
		qu->SetLocationTextId(textid);
	}
	// get text
	{
		QString txt = _objectmodel->data(_objectmodel->GetIndex(1, 7, parentIdx)).toString();
		std::string text = txt.toAscii().data();		
		text = text.substr(0, text.find(":"));
		long textid = atol(text.c_str());
		qu->SetTitleTextId(textid);

		// refresh list
		QStringList data;
		data<< txtLoc << txt;
		_questlistmodel->AddOrUpdateRow(id, data);
	}
	// get text
	{
		std::string text = _objectmodel->data(_objectmodel->GetIndex(1, 8, parentIdx)).toString().toAscii().data();		
		text = text.substr(0, text.find(":"));
		long textid = atol(text.c_str());
		qu->SetDescriptionTextId(textid);
	}


	// get action info
	{
		std::string action = _objectmodel->data(_objectmodel->GetIndex(1, 9, parentIdx)).toString().toAscii().data();
		std::string curract = GetActionType(qu->GetActionAtStart());

		if(action != curract)
		{
			ActionBasePtr ptrtmp = CreateAction(action);
			qu->SetActionAtStart(ptrtmp);

			QModelIndex curidx = _objectmodel->GetIndex(0, 9, parentIdx);
			_objectmodel->Clear(curidx);
			if(ptrtmp)
			{
				SelectAction(ptrtmp.get(), curidx);
				_uieditor.treeView_object->setExpanded(curidx, true); // expand 
			}

		}
	}
	// get action info
	{
		std::string action = _objectmodel->data(_objectmodel->GetIndex(1, 10, parentIdx)).toString().toAscii().data();
		std::string curract = GetActionType(qu->GetActionAtComplete());

		if(action != curract)
		{
			ActionBasePtr ptrtmp = CreateAction(action);
			qu->SetActionAtComplete(ptrtmp);

			QModelIndex curidx = _objectmodel->GetIndex(0, 10, parentIdx);
			_objectmodel->Clear(curidx);
			if(ptrtmp)
			{
				SelectAction(ptrtmp.get(), curidx);
				_uieditor.treeView_object->setExpanded(curidx, true); // expand 
			}

		}
	}


	// get child conditions info
	{
		QModelIndex itemparent = _objectmodel->GetIndex(0, 11, parentIdx);
		int curridx = 0;

		std::vector<ConditionBasePtr> childs = qu->GetConditions();
		for(size_t gg=0; gg< childs.size(); ++gg)
		{
			std::string condition = _objectmodel->data(_objectmodel->GetIndex(1, curridx, itemparent)).toString().toAscii().data();
			std::string currcond = GetConditionType(childs[gg]);

			if(condition != currcond)
			{
				if(condition == "No")
				{
					qu->RemoveCondition(childs[gg]);
					DisplayConditions(qu->GetConditions(), itemparent);
					return;
				}
				else
				{
					ConditionBasePtr ptrtmp = CreateCondition(condition);
					qu->ReplaceCondition(childs[gg], ptrtmp);

					QModelIndex curidx = _objectmodel->GetIndex(0, curridx, itemparent);
					_objectmodel->Clear(curidx);
					if(ptrtmp)
					{
						SelectCondition(ptrtmp, curidx);

						_uieditor.treeView_object->setExpanded(curidx, true); // expand 
					}
				}
			}
			++curridx;
		}

		QModelIndex childidx0 = _objectmodel->GetIndex(0, curridx, itemparent);
		QModelIndex childidx = _objectmodel->GetIndex(1, curridx, itemparent);
		std::string check = _objectmodel->data(childidx).toString().toAscii().data();
		if(check != "No")
		{
			if(check != "Add new...")
			{
				ConditionBasePtr ptrtmp = CreateCondition(check);
				qu->AddCondition(ptrtmp);

				_objectmodel->Clear(childidx0);
				if(ptrtmp)
				{
					SelectCondition(ptrtmp, childidx0);
					_uieditor.treeView_object->setExpanded(childidx0, true); // expand 
				}

				{
				// add new item
				QVector<QVariant> datait;
				datait << "Condition" << "Add new...";
				QModelIndex idxit = _objectmodel->AppendRow(datait, itemparent);	
				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idxit.row(), idxit.parent()), _conditiontypeList);	
				}

			}
		}
		else
		{
			_objectmodel->setData(childidx, "Add new...");
		}
	}
}




/***********************************************************
map music changed
***********************************************************/
void EditorHandler::MapMusicChanged(const QString & text)
{
	std::string mapname = _uieditor.label_mapname->text().toAscii().data();
	if(mapname != "")
	{
		std::string newv = _uieditor.lineEdit_mapmusic->text().toAscii().data();
		if(newv != _winfo.Maps[mapname].Music)
		{
			_winfo.Maps[mapname].Music = newv;
			SetModified();

			MusicHandler::getInstance()->PlayMusic("Data/"+_winfo.Maps[mapname].Music, _winfo.Maps[mapname].Repeat);
		}
	}

}

/***********************************************************
map music repeat changed
***********************************************************/
void EditorHandler::MapMusicRepeatChanged(int newvalue)
{
	std::string mapname = _uieditor.label_mapname->text().toAscii().data();
	if(mapname != "")
	{
		int newv = (_uieditor.comboBox_mapmusicrepeat->currentIndex() == 0)?1:0;
		if(newv != _winfo.Maps[mapname].Repeat)
		{
			_winfo.Maps[mapname].Repeat = newv;
			SetModified();

			MusicHandler::getInstance()->PlayMusic("Data/"+_winfo.Maps[mapname].Music, _winfo.Maps[mapname].Repeat);
		}
	}
}

/***********************************************************
map music file clicked
***********************************************************/
void EditorHandler::MapMusicFile_clicked()
{
	QString currfile = _uieditor.lineEdit_mapmusic->text();
	if(currfile != "")
		currfile = "Data/" + currfile;

	QStringList selectedfile = 
		QFileDialog::getOpenFileNames (this, "Select a music file", currfile, 
										"Sound (*.mp3 *.midi *.Ogg)");

	if(selectedfile.size() > 0)
	{
		QString selected = 	selectedfile[0];
		selected.replace("\\", "/");

		// check if choosen file is in the directory data
		if(selected.contains(QDir::currentPath()+"/Data/"))
		{
			selected = selected.remove(QDir::currentPath()+"/Data/");
		}
		else
		{
			//copy the file over
			try
			{
				QString newfilename = "Data/Worlds/";
				newfilename += _winfo.Description.WorldName.c_str(); 
				newfilename	+= "/Music/" + selected.section('/', -1);
				FileUtil::MakeFileCopy(selected.toAscii().data(), newfilename.toAscii().data());

				selected = newfilename.section('/', 1);
			}
			catch(...)
			{
				QErrorMessage msgdial;
				msgdial.showMessage ( "Error copying the file to the data directory!" );
				selected = "";
			}
		}

		_uieditor.lineEdit_mapmusic->setText(selected);
	}
}


/***********************************************************
Notice_accepted
***********************************************************/
void EditorHandler::Notice_accepted()
{
	_NoticeDialogdialog->hide();
	int read = 1;
	ConfigurationManager::GetInstance()->SetInt("Options.Editor.NoticeAccepted", read);
}

/***********************************************************
Notice_rejected
***********************************************************/
void EditorHandler::Notice_rejected()
{
		_NoticeDialogdialog->hide();
		quit();
}

	
/***********************************************************
Notice_closed
***********************************************************/
void EditorHandler::Notice_closed(int v)
{
	if(v == 0)
		Notice_rejected();
}
	

	
/***********************************************************
GenerateNavimesh
***********************************************************/
void EditorHandler::GenerateNavimesh()
{
	_navimesh->Reset();
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator ita = _Actors.begin();	
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator enda = _Actors.end();	
	for(; ita != enda; ++ita)
	{
		const ActorObjectInfo & ainfo = ita->second->GetActorInfo();
		// only add static type to mesh - dynamic actors are handled differently
		if(ainfo.PhysicDesc.TypePhysO == LbaNet::StaticAType) 
			_navimesh->AddActor(ainfo.PhysicDesc);
	}

	std::string mapname = _uieditor.label_mapname->text().toAscii().data();

	_navimesh->GenerateMesh();
	_navimesh->SaveToFile("./Data/Worlds/" + _winfo.Description.WorldName + "/AI/" 
											+ mapname + ".nmesh");

	RefreshNaviMeshDisplay();

	// refresh server
	SharedDataHandler::getInstance()->EditorUpdate(mapname, new UpdateEditor_RefreshNavMesh());
}
	
/***********************************************************
ToggleNavimeshDisplay
***********************************************************/
void EditorHandler::ToggleNavimeshDisplay()
{
	RefreshNaviMeshDisplay();
} 

	
/***********************************************************
refresh navimeshdisplay
***********************************************************/
void EditorHandler::RefreshNaviMeshDisplay()
{
	//! toogle debug display
	_navimesh->ToogleDebugDisplay(_uieditor.actionDisplay_Navimesh->isChecked());
}

/***********************************************************
inform that map Finished Loaded()
***********************************************************/
void EditorHandler::MapFinishedLoaded()
{
	RefreshNaviMeshDisplay();
}


/***********************************************************
option navimesh
***********************************************************/
void EditorHandler::OptionNavimesh()
{
	NavMeshConfig nvc = _navimesh->GetConfig();

	_ui_NavMeshDialog.sp_cellSize->setValue(nvc.m_cellSize);
	_ui_NavMeshDialog.sp_cellHeight->setValue(nvc.m_cellHeight);
	_ui_NavMeshDialog.sp_agentHeight->setValue(nvc.m_agentHeight);
	_ui_NavMeshDialog.sp_agentRadius->setValue(nvc.m_agentRadius);
	_ui_NavMeshDialog.sp_agentMaxClimb->setValue(nvc.m_agentMaxClimb);
	_ui_NavMeshDialog.sp_agentMaxSlope->setValue(nvc.m_agentMaxSlope);
	_ui_NavMeshDialog.sp_regionMinSize->setValue(nvc.m_regionMinSize);
	_ui_NavMeshDialog.sp_regionMergeSize->setValue(nvc.m_regionMergeSize);
	_ui_NavMeshDialog.cb_monotonePartitioning->setChecked (nvc.m_monotonePartitioning);
	_ui_NavMeshDialog.sp_edgeMaxLen->setValue(nvc.m_edgeMaxLen);
	_ui_NavMeshDialog.sp_edgeMaxError->setValue(nvc.m_edgeMaxError);
	_ui_NavMeshDialog.sp_vertsPerPoly->setValue(nvc.m_vertsPerPoly);
	_ui_NavMeshDialog.sp_detailSampleDist->setValue(nvc.m_detailSampleDist);
	_ui_NavMeshDialog.sp_detailSampleMaxError->setValue(nvc.m_detailSampleMaxError);
	

	int result = _NavMeshdialog->exec();
	if(result == QDialog::Accepted)
	{
		nvc.m_cellSize = _ui_NavMeshDialog.sp_cellSize->value();
		nvc.m_cellHeight = _ui_NavMeshDialog.sp_cellHeight->value();
		nvc.m_agentHeight = _ui_NavMeshDialog.sp_agentHeight->value();
		nvc.m_agentRadius = _ui_NavMeshDialog.sp_agentRadius->value();
		nvc.m_agentMaxClimb = _ui_NavMeshDialog.sp_agentMaxClimb->value();
		nvc.m_agentMaxSlope = _ui_NavMeshDialog.sp_agentMaxSlope->value();
		nvc.m_regionMinSize = _ui_NavMeshDialog.sp_regionMinSize->value();
		nvc.m_regionMergeSize = _ui_NavMeshDialog.sp_regionMergeSize->value();
		nvc.m_monotonePartitioning = _ui_NavMeshDialog.cb_monotonePartitioning->isChecked();
		nvc.m_edgeMaxLen = _ui_NavMeshDialog.sp_edgeMaxLen->value();
		nvc.m_edgeMaxError = _ui_NavMeshDialog.sp_edgeMaxError->value();
		nvc.m_vertsPerPoly = _ui_NavMeshDialog.sp_vertsPerPoly->value();
		nvc.m_detailSampleDist = _ui_NavMeshDialog.sp_detailSampleDist->value();
		nvc.m_detailSampleMaxError = _ui_NavMeshDialog.sp_detailSampleMaxError->value();	

		_navimesh->SetConfig(nvc);
	}
}


/***********************************************************
test find path
***********************************************************/
void EditorHandler::TestFindPath()
{
	if(!_pickfindpathstarted)
	{
		_pickfindpathstarted = true;
		_startpathpicked = false;
	}
}

/***********************************************************
display start path
***********************************************************/
void EditorHandler::DisplayStartPath(const LbaVec3 & position)
{
	HideStartPath();

	_startpathO = OsgHandler::getInstance()->AddEmptyActorNode(0, false);
	osg::Matrixd Trans;
	osg::Matrixd Rotation;
	Trans.makeTranslate(position.x, position.y, position.z);
	LbaQuaternion Q(0, LbaVec3(0,1,0));
	Rotation.makeRotate(osg::Quat(Q.X, Q.Y, Q.Z, Q.W));
	_startpathO->setMatrix(Rotation * Trans);


	{
	// create orientation line
	osg::Geode* lineGeode = new osg::Geode();
	osg::Geometry* lineGeometry = new osg::Geometry();
	lineGeode->addDrawable(lineGeometry); 

	float size = 2;
	osg::Vec3Array* lineVertices = new osg::Vec3Array();
	lineVertices->push_back( osg::Vec3( -size/2, 0, 0) );
	lineVertices->push_back( osg::Vec3(size/2, 0, 0) );
	lineVertices->push_back( osg::Vec3(0 , 0, -size/2) );
	lineVertices->push_back( osg::Vec3(0 , 0, size/2) );
	lineGeometry->setVertexArray( lineVertices ); 

	osg::Vec4Array* linecolor = new osg::Vec4Array();
	linecolor->push_back( osg::Vec4( 200/255.0f,48/255.0f,64/255.0f, 1) );
	lineGeometry->setColorArray(linecolor);
	lineGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	osg::DrawElementsUInt* dunit = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
	dunit->push_back(0);
	dunit->push_back(1);
	dunit->push_back(2);
	dunit->push_back(3);
	lineGeometry->addPrimitiveSet(dunit); 


    osg::StateSet* stateset = lineGeometry->getOrCreateStateSet();
    osg::LineWidth* linewidth = new osg::LineWidth();

    linewidth->setWidth(5.0f);
    stateset->setAttributeAndModes(linewidth,osg::StateAttribute::ON);
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	stateset->setRenderBinDetails( 50, "RenderBin");

	_startpathO->addChild(lineGeode);
	}


	{
	osg::Vec3 posT(0, 3, 0);
	 osg::AutoTransform *_textgroup = new osg::AutoTransform();
	_textgroup->setPosition(posT);
	_textgroup->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
	_textgroup->setMinimumScale(0.01);
	_textgroup->setMaximumScale(0.5);
	_textgroup->setAutoScaleToScreen(true);

	osg::ref_ptr<osg::Geode> _textgeode = new osg::Geode();
	osg::ref_ptr<osgText::Text> textd = new osgText::Text();
	textd->setText("Start");
	textd->setColor(osg::Vec4(200/255.0f,48/255.0f,64/255.0f, 1));
	textd->setCharacterSize(/*0.4f*/10);
	textd->setFont("Tahoma.ttf");
	textd->setAlignment(osgText::Text::CENTER_CENTER);



	textd->setBackdropColor(osg::Vec4(0, 0, 0, 1));
	textd->setBackdropType(osgText::Text::OUTLINE);
	textd->setBackdropImplementation(osgText::Text::NO_DEPTH_BUFFER);
	textd->setBackdropOffset(0.1f);

	_textgeode->addDrawable(textd);

	osg::StateSet* stateSet = _textgeode->getOrCreateStateSet();
	stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
	stateSet->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
	stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
	stateSet->setRenderBinDetails( 500, "SpecialBin");

	_textgroup->addChild(_textgeode);
	_startpathO->addChild(_textgroup);
	}

}

/***********************************************************
display end path
***********************************************************/
void EditorHandler::DisplayEndPath(const LbaVec3 & position)
{
	HideEndPath();

	_endpathO = OsgHandler::getInstance()->AddEmptyActorNode(0, false);
	osg::Matrixd Trans;
	osg::Matrixd Rotation;
	Trans.makeTranslate(position.x, position.y, position.z);
	LbaQuaternion Q(0, LbaVec3(0,1,0));
	Rotation.makeRotate(osg::Quat(Q.X, Q.Y, Q.Z, Q.W));
	_endpathO->setMatrix(Rotation * Trans);


	{
	// create orientation line
	osg::Geode* lineGeode = new osg::Geode();
	osg::Geometry* lineGeometry = new osg::Geometry();
	lineGeode->addDrawable(lineGeometry); 

	float size = 2;
	osg::Vec3Array* lineVertices = new osg::Vec3Array();
	lineVertices->push_back( osg::Vec3( -size/2, 0, 0) );
	lineVertices->push_back( osg::Vec3(size/2, 0, 0) );
	lineVertices->push_back( osg::Vec3(0 , 0, -size/2) );
	lineVertices->push_back( osg::Vec3(0 , 0, size/2) );
	lineGeometry->setVertexArray( lineVertices ); 

	osg::Vec4Array* linecolor = new osg::Vec4Array();
	linecolor->push_back( osg::Vec4(200/255.0f,48/255.0f,64/255.0f, 1) );
	lineGeometry->setColorArray(linecolor);
	lineGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	osg::DrawElementsUInt* dunit = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
	dunit->push_back(0);
	dunit->push_back(1);
	dunit->push_back(2);
	dunit->push_back(3);
	lineGeometry->addPrimitiveSet(dunit); 


    osg::StateSet* stateset = lineGeometry->getOrCreateStateSet();
    osg::LineWidth* linewidth = new osg::LineWidth();

    linewidth->setWidth(5.0f);
    stateset->setAttributeAndModes(linewidth,osg::StateAttribute::ON);
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	stateset->setRenderBinDetails( 50, "RenderBin");

	_endpathO->addChild(lineGeode);
	}


	{
	osg::Vec3 posT(0, 3, 0);
	 osg::AutoTransform* _textgroup = new osg::AutoTransform();
	_textgroup->setPosition(posT);
	_textgroup->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
	_textgroup->setMinimumScale(0.01);
	_textgroup->setMaximumScale(0.5);
	_textgroup->setAutoScaleToScreen(true);

	osg::ref_ptr<osg::Geode> _textgeode = new osg::Geode();
	osg::ref_ptr<osgText::Text> textd = new osgText::Text();
	textd->setText("End");
	textd->setColor(osg::Vec4(200/255.0f,48/255.0f,64/255.0f, 1));
	textd->setCharacterSize(/*0.4f*/10);
	textd->setFont("Tahoma.ttf");
	textd->setAlignment(osgText::Text::CENTER_CENTER);



	textd->setBackdropColor(osg::Vec4(0, 0, 0, 1));
	textd->setBackdropType(osgText::Text::OUTLINE);
	textd->setBackdropImplementation(osgText::Text::NO_DEPTH_BUFFER);
	textd->setBackdropOffset(0.1f);

	_textgeode->addDrawable(textd);

	osg::StateSet* stateSet = _textgeode->getOrCreateStateSet();
	stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
	stateSet->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
	stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
	stateSet->setRenderBinDetails( 500, "SpecialBin");

	_textgroup->addChild(_textgeode);
	_endpathO->addChild(_textgroup);
	}
}

/***********************************************************
hide start path
***********************************************************/
void EditorHandler::HideStartPath()
{
	if(_startpathO)
	{
		OsgHandler::getInstance()->RemoveActorNode(0, _startpathO, false);
		_startpathO = 0;
	}
}

/***********************************************************
hide end path
***********************************************************/
void EditorHandler::HideEndPath()
{
	if(_endpathO)
	{
		OsgHandler::getInstance()->RemoveActorNode(0, _endpathO, false);
		_endpathO = 0;
	}
}


/***********************************************************
TestNPCAttack
***********************************************************/
void EditorHandler::TestNPCAttack()
{
	std::string mapname = _uieditor.label_mapname->text().toAscii().data();

	// refresh server
	if(_selectedid >= 0)
		SharedDataHandler::getInstance()->EditorUpdate(mapname, new UpdateEditor_NPCAttack(true, _selectedid, 1));
}

/***********************************************************
TestNPCStopAttack
***********************************************************/
void EditorHandler::TestNPCStopAttack()
{
	std::string mapname = _uieditor.label_mapname->text().toAscii().data();

	// refresh server
	if(_selectedid >= 0)
		SharedDataHandler::getInstance()->EditorUpdate(mapname, new UpdateEditor_NPCAttack(false, _selectedid, 1));
}


/***********************************************************
select a Projectile
***********************************************************/
void EditorHandler::SelectProjectile(ProjectileObjectDef* cond, const QModelIndex &parent)
{
	if(parent == QModelIndex())
		ResetObject();

	if(!cond)
		return;

	// add pointer for later change
	_modelidxdatamap[parent] = (void*)cond;

	{
		QVector<QVariant> data;
		data<<"Type"<<"Projectile";
		_objectmodel->AppendRow(data, parent, true);
	}



	std::string dtype = "No";
	switch(cond->DisplayDesc.TypeRenderer)
	{
		case LbaNet::RenderOsgModel:
			dtype = "Osg Model";
		break;

		case RenderSprite:
			dtype = "Sprite";
		break;

		case RenderCross:
			dtype = "Cross";
		break;

		case RenderBox:
			dtype = "Box";
		break;

		case RenderSphere:
			dtype = "Sphere";
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
	switch(cond->PhysicDesc.TypeShape)
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


	_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 1, parent), _actordtypeList);
	_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, 2, parent), _actorptypeList);		

	int index = 3;

	if(cond->PhysicDesc.TypeShape != LbaNet::NoShape)
	{
		if(cond->PhysicDesc.TypeShape != LbaNet::TriangleMeshShape)
		{
			{
				QVector<QVariant> data;
				data<<"Size X"<<(double)cond->PhysicDesc.SizeX;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
			{
				QVector<QVariant> data;
				data<<"Size Y"<<(double)cond->PhysicDesc.SizeY;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
			{
				QVector<QVariant> data;
				data<<"Size Z"<<(double)cond->PhysicDesc.SizeZ;
				_objectmodel->AppendRow(data, parent);
				++index;
			}
		}
		else
		{
			{
				QVector<QVariant> data;
				data<<"Physic filename"<<cond->PhysicDesc.Filename.c_str();
				_objectmodel->AppendRow(data, parent);

				_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, index, parent), "Select physic file", "Models", "Physic Files (*.phy)");
				++index;
			}
		}

		{
			QVector<QVariant> data;
			data<<"Density"<<(double)cond->PhysicDesc.Density;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
	}

	if(dtype != "No")
	{
		{
			QVector<QVariant> data;
			data<<"Use Light"<<cond->DisplayDesc.UseLight;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Cast shadow"<<cond->DisplayDesc.CastShadow;
			_objectmodel->AppendRow(data, parent);
			++index;
		}

		{
			QVector<QVariant> data;
			data<<"Display translation X"<<(double)cond->DisplayDesc.TransX;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display translation Y"<<(double)cond->DisplayDesc.TransY;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display translation Z"<<(double)cond->DisplayDesc.TransZ;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display rotation X"<<(double)cond->DisplayDesc.RotX;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display rotation Y"<<(double)cond->DisplayDesc.RotY;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display rotation Z"<<(double)cond->DisplayDesc.RotZ;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display scale X"<<(double)cond->DisplayDesc.ScaleX;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display scale Y"<<(double)cond->DisplayDesc.ScaleY;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display scale Z"<<(double)cond->DisplayDesc.ScaleZ;
			_objectmodel->AppendRow(data, parent);
			++index;
		}


		if(cond->DisplayDesc.TypeRenderer == RenderOsgModel )
		{
			QVector<QVariant> data;
			data<<"Display model file"<<cond->DisplayDesc.ModelName.c_str();
			_objectmodel->AppendRow(data, parent);

			_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, index, parent), "Select a model file", "Models", "Model Files (*.osg *.osgb *.osgt)");
			++index;
		}

		if(cond->DisplayDesc.TypeRenderer == RenderSprite )
		{
			QVector<QVariant> data;
			data<<"Display sprite file"<<cond->DisplayDesc.ModelName.c_str();
			_objectmodel->AppendRow(data, parent);

			_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, index, parent), "Select an image", "Sprites", "Image Files (*.png *.bmp *.jpg *.gif)");
			++index;

			{
				QVector<QVariant> data1;
				data1<<"Color R"<<(double)cond->DisplayDesc.ColorR;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color G"<<(double)cond->DisplayDesc.ColorG;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color B"<<(double)cond->DisplayDesc.ColorB;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color A"<<(double)cond->DisplayDesc.ColorA;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Use Billboard"<<cond->DisplayDesc.UseBillboard;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
		}

 
		if(cond->DisplayDesc.TypeRenderer == RenderBox
			|| cond->DisplayDesc.TypeRenderer == RenderCapsule
			|| cond->DisplayDesc.TypeRenderer == RenderSphere)
		{
			{
				QVector<QVariant> data1;
				data1<<"Color R"<<(double)cond->DisplayDesc.ColorR;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color G"<<(double)cond->DisplayDesc.ColorG;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color B"<<(double)cond->DisplayDesc.ColorB;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color A"<<(double)cond->DisplayDesc.ColorA;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
		}


		// add materials
		{
			QVector<QVariant> data;
			data<<"Use alpha material"<<cond->DisplayDesc.UseTransparentMaterial;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Alpha"<<(double)cond->DisplayDesc.MatAlpha;
			_objectmodel->AppendRow(data, parent);
			++index;
		}

		int matcolortype = cond->DisplayDesc.ColorMaterialType;
		{
			std::string mattypestring = "Off";
			switch(matcolortype)
			{
				case 1:
					mattypestring = "Ambient";
				break;
				case 2:
					mattypestring = "Diffuse";
				break;
				case 3:
					mattypestring = "Specular";
				break;
				case 4:
					mattypestring = "Emission";
				break;
				case 5:
					mattypestring = "Ambient_And_Diffuse";
				break;
			}
			QVector<QVariant> data;
			data<<"Color material type"<<mattypestring.c_str();
			_objectmodel->AppendRow(data, parent);
				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _materialtypeList);
			++index;	
		}

		if(matcolortype > 0)
		{
			{
			QVector<QVariant> data;
			data<<"Mat Ambient ColorR"<<(double)cond->DisplayDesc.MatAmbientColorR;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Ambient ColorG"<<(double)cond->DisplayDesc.MatAmbientColorG;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Ambient ColorB"<<(double)cond->DisplayDesc.MatAmbientColorB;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Ambient ColorA"<<(double)cond->DisplayDesc.MatAmbientColorA;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}

			{
			QVector<QVariant> data;
			data<<"Mat Diffuse ColorR"<<(double)cond->DisplayDesc.MatDiffuseColorR;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Diffuse ColorG"<<(double)cond->DisplayDesc.MatDiffuseColorG;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Diffuse ColorB"<<(double)cond->DisplayDesc.MatDiffuseColorB;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Diffuse ColorA"<<(double)cond->DisplayDesc.MatDiffuseColorA;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}

			{
			QVector<QVariant> data;
			data<<"Mat Specular ColorR"<<(double)cond->DisplayDesc.MatSpecularColorR;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Specular ColorG"<<(double)cond->DisplayDesc.MatSpecularColorG;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Specular ColorB"<<(double)cond->DisplayDesc.MatSpecularColorB;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Specular ColorA"<<(double)cond->DisplayDesc.MatSpecularColorA;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}

			{
			QVector<QVariant> data;
			data<<"Mat Emission ColorR"<<(double)cond->DisplayDesc.MatEmissionColorR;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Emission ColorG"<<(double)cond->DisplayDesc.MatEmissionColorG;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Emission ColorB"<<(double)cond->DisplayDesc.MatEmissionColorB;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Emission ColorA"<<(double)cond->DisplayDesc.MatEmissionColorA;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Shininess"<<(double)cond->DisplayDesc.MatShininess;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
		}	
	}


	{
		QVector<QVariant> data;
		data<<"Usable Mode"<<cond->UsableMode.c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;	
	}
	{
		QVector<QVariant> data;
		data<<"Power"<<(double)cond->Power;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}
	{
		QVector<QVariant> data;
		data<<"Mana used"<<(double)cond->UseMana;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}		
	{
		QVector<QVariant> data;
		data<<"OffsetX"<<(double)cond->OffsetX;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}	
	{
		QVector<QVariant> data;
		data<<"OffsetY"<<(double)cond->OffsetY;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}
	{
		QVector<QVariant> data;
		data<<"OffsetZ"<<(double)cond->OffsetZ;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}
	{
		QVector<QVariant> data;
		data<<"ForceX"<<(double)cond->ForceX;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}
	{
		QVector<QVariant> data;
		data<<"ForceY"<<(double)cond->ForceY;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}
	{
		QVector<QVariant> data;
		data<<"ForceYOnImpact"<<(double)cond->ForceYOnImpact;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}
	{
		QVector<QVariant> data;
		data<<"Number of bounce"<<cond->NbBounce;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}
	{
		QVector<QVariant> data;
		data<<"Ignore gravity"<<cond->IgnoreGravity;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}
	{
		QVector<QVariant> data;
		data<<"Life time (seconds)"<<(double)cond->LifeTime;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}
	{
		QVector<QVariant> data;
		data<<"Projectile come back"<<cond->Comeback;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}
	{
		QVector<QVariant> data;
		data<<"Launch anim keyframe "<<cond->StartAnimFrame;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}
	{
		QVector<QVariant> data;
		data<<"Fire on Timer"<<cond->UseTimer;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}
	{
		QVector<QVariant> data;
		data<<"Fire frequency (seconds)"<<(double)cond->Frequency;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}	
	{
		QVector<QVariant> data;
		data<<"Angle offset"<<(double)cond->AngleOffset;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}	
	{
		QVector<QVariant> data;
		data<<"Sound At Start"<<cond->SoundAtStart.c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;

		_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, idx.row(), parent), "Select an sound file", "Sound", "Sound Files (*.mp3 *.midi *.Ogg)");
	}	
	{
		QVector<QVariant> data;
		data<<"Sound On Bounce"<<cond->SoundOnBounce.c_str();
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;

		_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, idx.row(), parent), "Select an sound file", "Sound", "Sound Files (*.mp3 *.midi *.Ogg)");
	}
	{
		QVector<QVariant> data;
		data<<"Force loose life"<<cond->ForceHurt;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}
	{
		QVector<QVariant> data;
		data<<"Follow Target"<<cond->FollowTarget;
		QModelIndex idx = _objectmodel->AppendRow(data, parent);
		++index;
	}
}

/***********************************************************
called when Projectile changed
***********************************************************/
void EditorHandler::ProjectileChanged(const QModelIndex &parentIdx)
{
	std::map<QModelIndex, void *>::iterator it = _modelidxdatamap.find(parentIdx);
	if(it == _modelidxdatamap.end())
		return;

	ProjectileObjectDef * ptr = static_cast<ProjectileObjectDef*>(it->second);
	if(!ptr)
		return;

	bool updateobj = false;
	int index = 3;

	if(ptr->PhysicDesc.TypeShape != LbaNet::NoShape)
	{
		if(ptr->PhysicDesc.TypeShape != LbaNet::TriangleMeshShape)
		{
	
			ptr->PhysicDesc.SizeX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
	
			ptr->PhysicDesc.SizeY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
	
			ptr->PhysicDesc.SizeZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
		}
		else
		{
	
			ptr->PhysicDesc.Filename = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
			++index;
		}

		ptr->PhysicDesc.Density = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
		++index;
	}

	if(ptr->DisplayDesc.TypeRenderer != LbaNet::NoRender)
	{

			ptr->DisplayDesc.UseLight = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
		++index;


			ptr->DisplayDesc.CastShadow = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
		++index;


			ptr->DisplayDesc.TransX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
		++index;

			ptr->DisplayDesc.TransY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
		++index;

			ptr->DisplayDesc.TransZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
		++index;


			ptr->DisplayDesc.RotX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
		++index;

			ptr->DisplayDesc.RotY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
		++index;

			ptr->DisplayDesc.RotZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
		++index;


			ptr->DisplayDesc.ScaleX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
		++index;

			ptr->DisplayDesc.ScaleY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
		++index;

			ptr->DisplayDesc.ScaleZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
		++index;


		if(ptr->DisplayDesc.TypeRenderer == RenderOsgModel )
		{
	
				ptr->DisplayDesc.ModelName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
			++index;
		}

		if(ptr->DisplayDesc.TypeRenderer == RenderSprite )
		{
	
				ptr->DisplayDesc.ModelName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
			++index;	

	
				ptr->DisplayDesc.ColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
			++index;	

	
				ptr->DisplayDesc.ColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
			++index;		

	
				ptr->DisplayDesc.ColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
			++index;		

	
				ptr->DisplayDesc.ColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
			++index;

	
				ptr->DisplayDesc.UseBillboard = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
			++index;
		}
 
		if(ptr->DisplayDesc.TypeRenderer == RenderBox
			|| ptr->DisplayDesc.TypeRenderer == RenderCapsule
			|| ptr->DisplayDesc.TypeRenderer == RenderSphere)
		{

			ptr->DisplayDesc.ColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
			++index;	

			ptr->DisplayDesc.ColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
			++index;		

			ptr->DisplayDesc.ColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
			++index;		

			ptr->DisplayDesc.ColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
			++index;
		}


		// check materials
		if(!updateobj)
		{
			ptr->DisplayDesc.UseTransparentMaterial = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();		
			++index;
			ptr->DisplayDesc.MatAlpha = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		
			++index;

			int oldmatcolortype = ptr->DisplayDesc.ColorMaterialType;

			std::string matstringtype = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();	
			++index;

			ptr->DisplayDesc.ColorMaterialType = 0;
			if(matstringtype == "Ambient")
				ptr->DisplayDesc.ColorMaterialType = 1;
			if(matstringtype == "Diffuse")
				ptr->DisplayDesc.ColorMaterialType = 2;
			if(matstringtype == "Specular")
				ptr->DisplayDesc.ColorMaterialType = 3;
			if(matstringtype == "Emission")
				ptr->DisplayDesc.ColorMaterialType = 4;
			if(matstringtype == "Ambient_And_Diffuse")
				ptr->DisplayDesc.ColorMaterialType = 5;

			if(ptr->DisplayDesc.ColorMaterialType != oldmatcolortype)
				updateobj = true;

	
			if(oldmatcolortype > 0)
			{
				ptr->DisplayDesc.MatAmbientColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				ptr->DisplayDesc.MatAmbientColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				ptr->DisplayDesc.MatAmbientColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				ptr->DisplayDesc.MatAmbientColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				ptr->DisplayDesc.MatDiffuseColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				ptr->DisplayDesc.MatDiffuseColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				ptr->DisplayDesc.MatDiffuseColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				ptr->DisplayDesc.MatDiffuseColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				ptr->DisplayDesc.MatSpecularColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				ptr->DisplayDesc.MatSpecularColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				ptr->DisplayDesc.MatSpecularColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				ptr->DisplayDesc.MatSpecularColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;	
				ptr->DisplayDesc.MatEmissionColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				ptr->DisplayDesc.MatEmissionColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				ptr->DisplayDesc.MatEmissionColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				ptr->DisplayDesc.MatEmissionColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;	
				ptr->DisplayDesc.MatShininess = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;				
			}
		}

	}


	ptr->UsableMode = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data(); 
	++index;	

	ptr->Power = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
	++index;	

	ptr->UseMana = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
	++index;	

	ptr->OffsetX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
	++index;	

	ptr->OffsetY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
	++index;	

	ptr->OffsetZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
	++index;

	ptr->ForceX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
	++index;	

	ptr->ForceY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
	++index;	

	ptr->ForceYOnImpact = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
	++index;	

	ptr->NbBounce = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();		 
	++index;	

	ptr->IgnoreGravity = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();		 
	++index;	

	ptr->LifeTime = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
	++index;	

	ptr->Comeback = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();		 
	++index;	

	ptr->StartAnimFrame = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();		 
	++index;	

	ptr->UseTimer = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();		 
	++index;	

	ptr->Frequency = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
	++index;		

	ptr->AngleOffset = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
	++index;		

	ptr->SoundAtStart = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data(); 
	++index;	

	ptr->SoundOnBounce = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data(); 
	++index;	

	ptr->ForceHurt = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();		 
	++index;

	ptr->FollowTarget = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();		 
	++index;

	SetMapModified();


	{
		LbaNet::RenderTypeEnum befored = ptr->DisplayDesc.TypeRenderer;
		ptr->DisplayDesc.TypeRenderer = LbaNet::NoRender;
		
		std::string dtype = _objectmodel->data(_objectmodel->GetIndex(1, 1, parentIdx)).toString().toAscii().data();
		if(dtype == "Osg Model") 
			ptr->DisplayDesc.TypeRenderer = LbaNet::RenderOsgModel;
		if(dtype == "Sprite") 
			ptr->DisplayDesc.TypeRenderer = LbaNet::RenderSprite;
		if(dtype == "Sphere") 
			ptr->DisplayDesc.TypeRenderer = LbaNet::RenderSphere;
		if(dtype == "Capsule") 
			ptr->DisplayDesc.TypeRenderer = LbaNet::RenderCapsule;
		if(dtype == "Box") 
			ptr->DisplayDesc.TypeRenderer = LbaNet::RenderBox;

		if(befored != ptr->DisplayDesc.TypeRenderer)
			updateobj = true;

		LbaNet::PhysicalShapeEnum beforep = ptr->PhysicDesc.TypeShape;
		std::string ptype = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toAscii().data();
		if(ptype == "No Shape") 
			ptr->PhysicDesc.TypeShape = LbaNet::NoShape;
		if(ptype == "Box") 
			ptr->PhysicDesc.TypeShape = LbaNet::BoxShape;
		if(ptype == "Capsule") 
			ptr->PhysicDesc.TypeShape = LbaNet::CapsuleShape;
		if(ptype == "Sphere") 
			ptr->PhysicDesc.TypeShape = LbaNet::SphereShape;
		if(ptype == "Triangle Mesh") 
			ptr->PhysicDesc.TypeShape = LbaNet::TriangleMeshShape;

		if(beforep != ptr->PhysicDesc.TypeShape)
			updateobj = true;
	}


	//refresh object
	if(updateobj)
	{
		_objectmodel->Clear(parentIdx);
		SelectProjectile(ptr, parentIdx);
	}
}


/***********************************************************
edition slots
***********************************************************/
void EditorHandler::CopyObjectClicked()
{
	EditSelectedObject(EditObjCopy);
}

/***********************************************************
edition slots
***********************************************************/
void EditorHandler::PasteObjectClicked()
{
	QClipboard * clipboard = QApplication::clipboard();
	const QMimeData * mdata = clipboard->mimeData();
	if(mdata)
	{
		if(mdata->hasFormat("lbanet/actor"))
		{
			QByteArray data = mdata->data("lbanet/actor");
			std::string scriptobj(data.constData());
			if(scriptobj != "")
				PasteActor(scriptobj);
		}

		if(mdata->hasFormat("lbanet/spawn"))
		{
			QByteArray data = mdata->data("lbanet/spawn");
			std::string scriptobj(data.constData());
			if(scriptobj != "")
				PasteSpawn(scriptobj);
		}

		if(mdata->hasFormat("lbanet/trigger"))
		{
			QByteArray data = mdata->data("lbanet/trigger");
			std::string scriptobj(data.constData());
			if(scriptobj != "")
				PasteTrigger(scriptobj);
		}
	}
}
 
/***********************************************************
edition slots
***********************************************************/
void EditorHandler::CutObjectClicked()
{
	EditSelectedObject(EditObjCut);
}
 
/***********************************************************
edition slots
***********************************************************/
void EditorHandler::DeleteObjectClicked()
{
	EditSelectedObject(EditObjDelete);
}


/***********************************************************
edition slots
***********************************************************/
void EditorHandler::EditSelectedObject(ObjectEditType edittype)
{
	QModelIndex parentIdx = QModelIndex();

	if(_objectmodel->rowCount() > 2)
	{
		// only interested in parent objects
		if(_objectmodel->data(_objectmodel->GetIndex(0, 0, parentIdx)).toString() != "Type")
			return;

		std::string tocopy;
		std::string copytype;

		QString type = _objectmodel->data(_objectmodel->GetIndex(1, 0, parentIdx)).toString();
		if(type == "Spawn")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toLong();
			std::map<long, boost::shared_ptr<Spawn> >::iterator it = _spawns.find(objid);
			if(it != _spawns.end())	
			{
				if(edittype == EditObjCut ||  edittype == EditObjCopy)
				{
					//copy object to clipboard
					std::stringstream objcontent;
					it->second->SaveToLuaFile(objcontent, "%##%");
					tocopy = objcontent.str();

					copytype = "lbanet/spawn";
				}

				if(edittype == EditObjCut ||  edittype == EditObjDelete)
				{
					std::string mapname = _uieditor.label_mapname->text().toAscii().data();
					RemoveSpawning(mapname, objid);
				}
			}
		}

		if(type == "Trigger")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toLong();
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator it = _triggers.find(objid);
			if(it != _triggers.end())	
			{
				if(edittype == EditObjCut ||  edittype == EditObjCopy)
				{
					//copy object to clipboard
					std::stringstream objcontent;
					it->second->SaveToLuaFile(objcontent, "%##%");
					tocopy = objcontent.str();

					copytype = "lbanet/trigger";
				}

				if(edittype == EditObjCut ||  edittype == EditObjDelete)
					RemoveTrigger(objid);
			}
		}

		if(type == "Actor")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toLong();
			std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator it = _Actors.find(objid);
			if(it != _Actors.end())
			{
				if(edittype == EditObjCut ||  edittype == EditObjCopy)
				{
					//copy object to clipboard
					std::stringstream objcontent;
					it->second->SaveToLuaFile(objcontent, "%##%");
					tocopy = objcontent.str();

					copytype = "lbanet/actor";
				}

				if(edittype == EditObjCut ||  edittype == EditObjDelete)
					RemoveActor(objid);	
			}
		}

		if(tocopy != "")
		{
			QMimeData *mimeData = new QMimeData;
			QByteArray output(tocopy.c_str());
			mimeData->setData(copytype.c_str(), output);

			QClipboard * clipboard = QApplication::clipboard();
			clipboard->setMimeData(mimeData);
		}
	}
}


/***********************************************************
add template object
***********************************************************/
void EditorHandler::AddTemplateObject()
{
	QModelIndex parentIdx = QModelIndex();

	if(_objectmodel->rowCount() > 2)
	{
		// only interested in parent objects
		if(_objectmodel->data(_objectmodel->GetIndex(0, 0, parentIdx)).toString() != "Type")
			return;

		std::string tocopy;
		std::string copytype;

		QString type = _objectmodel->data(_objectmodel->GetIndex(1, 0, parentIdx)).toString();
		if(type == "Spawn")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toLong();
			std::map<long, boost::shared_ptr<Spawn> >::iterator it = _spawns.find(objid);
			if(it != _spawns.end())	
			{
				std::stringstream objcontent;
				it->second->SaveToLuaFile(objcontent, "%##%");
				tocopy = objcontent.str();

				copytype = "Spawn";
			}
		}

		if(type == "Trigger")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toLong();
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator it = _triggers.find(objid);
			if(it != _triggers.end())	
			{
				std::stringstream objcontent;
				it->second->SaveToLuaFile(objcontent, "%##%");
				tocopy = objcontent.str();

				copytype = "Trigger";
			}
		}

		if(type == "Actor")
		{
			long objid = _objectmodel->data(_objectmodel->GetIndex(1, 2, parentIdx)).toString().toLong();
			std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator it = _Actors.find(objid);
			if(it != _Actors.end())
			{
				std::stringstream objcontent;
				it->second->SaveToLuaFile(objcontent, "%##%");
				tocopy = objcontent.str();

				copytype = "Actor";
			}
		}

		if(tocopy != "")
		{
			_ui_addtemplateDialog.lineEdit_template_name->setText("");
			_ui_addtemplateDialog.lineEdit_template_category->setText("");
			if(_addtemplatedialog->exec() == QDialog::Accepted)
			{
				EditorTemplateObject tmpobj;
				tmpobj.type = copytype;
				tmpobj.category = _ui_addtemplateDialog.lineEdit_template_category->text().toAscii().data();
				tmpobj.name = _ui_addtemplateDialog.lineEdit_template_name->text().toAscii().data();
				tmpobj.content = tocopy;

				if(tmpobj.category == "")
					tmpobj.category = "No category";

				tmpobj.id = 0;
				if(_objecttemplates.size() > 0)
					tmpobj.id = (_objecttemplates.rbegin()->first + 1);

				AddNewTemplate(tmpobj);
				SetModified();
			}
		}
	}
}


/***********************************************************
add template object
***********************************************************/
void EditorHandler::AddNewTemplate(const EditorTemplateObject & templ)
{
	// add to list
	_objecttemplates[templ.id] = templ;


	// add to menu
	QMenu * parentmenu = NULL;

	if(templ.type == "Spawn")
		parentmenu = _uieditor.menuSpawns;
	if(templ.type == "Actor")
		parentmenu = _uieditor.menuActors;
	if(templ.type == "Trigger")
		parentmenu = _uieditor.menuTriggers;	

	if(parentmenu)
	{
		QMenu * categorymenu = NULL;

		//check if category menu is already created
		QList<QAction *> lactions = parentmenu->actions();
		for (int i = 0; i < lactions.size(); ++i)
		{
			QAction * tmpa = lactions[i];
			QMenu * tmpmenu = tmpa->menu();
			if(tmpmenu && tmpmenu->title() == templ.category.c_str())
			{
				categorymenu = tmpmenu;
				break;
			}
		}

		if(!categorymenu)
			categorymenu = 	parentmenu->addMenu(templ.category.c_str());

		//add action to menu
		if(categorymenu)
		{
			std::stringstream stractname;
			stractname<<templ.id<<": "<<templ.name;
			QAction * act = categorymenu->addAction(stractname.str().c_str());

			_signalMapper->setMapping(act, templ.id);
			connect(act, SIGNAL(triggered()), _signalMapper, SLOT(map()));

			_objecttemplates[templ.id].associatedaction = act;
		}
	}
}


/***********************************************************
template object clicked
***********************************************************/
void EditorHandler::TemplateMenuClicked(int templateid)
{
	std::map<int, EditorTemplateObject>::iterator it = _objecttemplates.find(templateid);
	if(it != _objecttemplates.end())
	{
		std::string type = it->second.type;

		if(type == "Actor")
			PasteActor(it->second.content);

		if(type == "Spawn")
			PasteSpawn(it->second.content);

		if(type == "Trigger")
			PasteTrigger(it->second.content);
	}
}


/***********************************************************
paste spawn
***********************************************************/
void EditorHandler::PasteSpawn(std::string content)
{
	long actid = _currspawningidx+1;

	std::stringstream strsid;
	strsid<<actid;

	content = StringHelper::replaceall(content, "%##%", strsid.str());

	// paste copied object
	content = "function PasteObject(environment) \n" + content + "end";
	_luaH->ExecuteScriptString(content);
	_luaH->CallLua("PasteObject", this);

	std::map<long, boost::shared_ptr<Spawn> >::iterator it = _spawns.find(actid);
	if(it != _spawns.end())
	{
		//move actor to player position
		boost::shared_ptr<Spawn> newspawn = it->second;
		newspawn->SetPosX(_posX);
		newspawn->SetPosY(_posY);
		newspawn->SetPosZ(_posZ);

		//inform server
		std::string mapname = _uieditor.label_mapname->text().toAscii().data();
		EditorUpdateBasePtr update = new UpdateEditor_AddOrModSpawning(newspawn);

		SharedDataHandler::getInstance()->EditorUpdate(mapname, update);
	}

	//select spawn
	SelectSpawning(actid);

	SetMapModified();
}


/***********************************************************
paste actor
***********************************************************/
void EditorHandler::PasteActor(std::string content)
{
	long actid = _curractoridx+1;

	std::stringstream strsid;
	strsid<<actid;

	content = StringHelper::replaceall(content, "%##%", strsid.str());

	// paste copied object
	content = "function PasteObject(environment) \n" + content + "end";
	_luaH->ExecuteScriptString(content);
	_luaH->CallLua("PasteObject", this);

	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator it = _Actors.find(actid);
	if(it != _Actors.end())
	{
		//move actor to player position
		ActorObjectInfo ainfo = it->second->GetActorInfo();
		ainfo.PhysicDesc.Pos.X = _posX;
		ainfo.PhysicDesc.Pos.Y = _posY;
		ainfo.PhysicDesc.Pos.Z = _posZ;
		it->second->SetActorInfo(ainfo);

		//inform server
		std::string mapname = _uieditor.label_mapname->text().toAscii().data();
		EditorUpdateBasePtr update = new UpdateEditor_AddOrModActor(it->second);
		SharedDataHandler::getInstance()->EditorUpdate(mapname, update);

	}

	//select actor
	SelectActor(actid);

	SetMapModified();
}


/***********************************************************
paste trigger
***********************************************************/
void EditorHandler::PasteTrigger(std::string content)
{
	long actid = _currtriggeridx+1;

	std::stringstream strsid;
	strsid<<actid;

	content = StringHelper::replaceall(content, "%##%", strsid.str());

	// paste copied object
	content = "function PasteObject(environment) \n" + content + "end";
	_luaH->ExecuteScriptString(content);
	_luaH->CallLua("PasteObject", this);

	std::map<long, boost::shared_ptr<TriggerBase> >::iterator it = _triggers.find(actid);
	if(it != _triggers.end())
	{
		//move actor to player position
		it->second->SetPosition(_posX, _posY, _posZ);

		//inform server
		std::string mapname = _uieditor.label_mapname->text().toAscii().data();
		EditorUpdateBasePtr update = new UpdateEditor_AddOrModTrigger(it->second);
		SharedDataHandler::getInstance()->EditorUpdate(mapname, update);
	}

	//select spawn
	SelectTrigger(actid);

	SetMapModified();
}


/***********************************************************
edit templates
***********************************************************/
void EditorHandler::EditTemplates()
{
	_templatelistmodel->Clear();

	std::map<int, EditorTemplateObject>::iterator it = _objecttemplates.begin();
	std::map<int, EditorTemplateObject>::iterator end = _objecttemplates.end();
	for(; it != end; ++it)
	{
		QStringList data;
		data<<it->second.type.c_str()<<it->second.category.c_str()<<it->second.name.c_str();
		_templatelistmodel->AddOrUpdateRow(it->first, data);
	}

	_edittemplatedialog->exec();
}


/***********************************************************
TemplateRemove_button
***********************************************************/
void EditorHandler::TemplateRemove_button()
{
	QItemSelectionModel *selectionModel = _ui_edittemplateDialog.tableView->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();
	if(indexes.size() > 2)
	{
		// remove template from menu
		long id = _templatelistmodel->GetId(indexes[0]);
		RemoveTemplate(id);


		// remove row from table
		_templatelistmodel->removeRows(indexes[0].row(), 1);
	}
}


/***********************************************************
remove template
***********************************************************/
void EditorHandler::RemoveTemplate(int id)
{
	std::map<int, EditorTemplateObject>::iterator it = _objecttemplates.find(id);
	if(it != _objecttemplates.end())
	{
		//remove from menu
		QAction* acttmp = it->second.associatedaction;
		if(acttmp)
			acttmp->parentWidget()->removeAction(acttmp);

		//remove from map
		_objecttemplates.erase(it);

		SetModified();
	}
}

/***********************************************************
show hide map info
***********************************************************/
void EditorHandler::ShowHideMapInfo(bool Show)
{
	//if(Show)
	//	_uieditor.widget_map->show();
	//else
	//	_uieditor.widget_map->hide();
}




/***********************************************************
HoloAdd_button
***********************************************************/
void EditorHandler::HoloAdd_button()
{
	switch(_uieditor.tabWidget_holo->currentIndex())
	{
		case 0:
		{
			long id = HolomapHandler::getInstance()->GenerateHolomapId();
			HolomapPtr newHolo(new Holomap(id));
			HolomapHandler::getInstance()->AddHolomap(newHolo);

			QStringList data;
			data << "";
			_holomaplistmodel->AddOrUpdateRow(id, data);

			SetModified();
			SelectHolomap(id);
		}
		break;
		case 1:
			HoloLocAdd_button();
		break;
		case 2:
			HoloPathAdd_button();
		break;
	}


}

/***********************************************************
HoloRemove_button
***********************************************************/
void EditorHandler::HoloRemove_button()
{
	switch(_uieditor.tabWidget_holo->currentIndex())
	{
		case 0:
		{
			QItemSelectionModel *selectionModel = _uieditor.tableView_HolomapList->selectionModel();
			QModelIndexList indexes = selectionModel->selectedIndexes();

			if(indexes.size() > 0)
			{
				long id = _holomaplistmodel->GetId(indexes[0]);
				HolomapHandler::getInstance()->RemoveHolomap(id);

				_holomaplistmodel->removeRows(indexes[0].row(), 1);

				SetModified();
			}
		}
		break;
		case 1:
			HoloLocRemove_button();
		break;
		case 2:
			HoloPathRemove_button();
		break;
	}
}

/***********************************************************
HoloSelect_button
***********************************************************/
void EditorHandler::HoloSelect_button()
{
	switch(_uieditor.tabWidget_holo->currentIndex())
	{
		case 0:
		{
			QItemSelectionModel *selectionModel = _uieditor.tableView_HolomapList->selectionModel();
			QModelIndexList indexes = selectionModel->selectedIndexes();

			if(indexes.size() > 0)
			{
				long id = _holomaplistmodel->GetId(indexes[0]);
				SelectHolomap(id);
			}

			ShowHideMapInfo(false);
		}
		break;
		case 1:
			HoloLocSelect_button();
		break;
		case 2:
			HoloPathSelect_button();
		break;
	}
}


/***********************************************************
HoloAdd_button
***********************************************************/
void EditorHandler::HoloLocAdd_button()
{
	long id = HolomapHandler::getInstance()->GenerateHolomapLocId();
	HolomapLocationPtr newHolo(new HolomapLocation(id));
	HolomapHandler::getInstance()->AddHolomapLoc(newHolo);

	QStringList data;
	data << "";
	_holomaploclistmodel->AddOrUpdateRow(id, data);

	SetModified();
	SelectHolomapLoc(id);
}

/***********************************************************
HoloRemove_button
***********************************************************/
void EditorHandler::HoloLocRemove_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_HolomapList_2->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	if(indexes.size() > 0)
	{
		long id = _holomaploclistmodel->GetId(indexes[0]);
		HolomapHandler::getInstance()->RemoveHolomapLoc(id);

		_holomaploclistmodel->removeRows(indexes[0].row(), 1);

		SetModified();
	}
}

/***********************************************************
HoloSelect_button
***********************************************************/
void EditorHandler::HoloLocSelect_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_HolomapList_2->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	if(indexes.size() > 0)
	{
		long id = _holomaploclistmodel->GetId(indexes[0]);
		SelectHolomapLoc(id);
	}

	ShowHideMapInfo(false);
}


/***********************************************************
HoloAdd_button
***********************************************************/
void EditorHandler::HoloPathAdd_button()
{
	long id = HolomapHandler::getInstance()->GenerateHolomapPathId();
	HolomapTravelPathPtr newHolo(new HolomapTravelPath(id));
	HolomapHandler::getInstance()->AddHolomapPath(newHolo);

	QStringList data;
	data << "";
	_holomappathlistmodel->AddOrUpdateRow(id, data);

	SetModified();
	SelectHolomapPath(id);
}

/***********************************************************
HoloRemove_button
***********************************************************/
void EditorHandler::HoloPathRemove_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_HolomapList_3->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	if(indexes.size() > 0)
	{
		long id = _holomappathlistmodel->GetId(indexes[0]);
		HolomapHandler::getInstance()->RemoveHolomapPath(id);

		_holomappathlistmodel->removeRows(indexes[0].row(), 1);

		SetModified();
	}
}

/***********************************************************
HoloSelect_button
***********************************************************/
void EditorHandler::HoloPathSelect_button()
{
	QItemSelectionModel *selectionModel = _uieditor.tableView_HolomapList_3->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();

	if(indexes.size() > 0)
	{
		long id = _holomappathlistmodel->GetId(indexes[0]);
		SelectHolomapPath(id);	
	}

	ShowHideMapInfo(false);
}

/***********************************************************
on selectholomap_double_clicked
***********************************************************/
void EditorHandler::selectholomap_double_clicked(const QModelIndex & itm)
{
	HoloSelect_button();		
}
/***********************************************************
on selectholomap_double_clicked
***********************************************************/
void EditorHandler::selectholomaploc_double_clicked(const QModelIndex & itm)
{
	HoloLocSelect_button();		
}
/***********************************************************
on selectholomap_double_clicked
***********************************************************/
void EditorHandler::selectholomappath_double_clicked(const QModelIndex & itm)
{
	HoloPathSelect_button();		
}




/***********************************************************
set Holomap in the object
***********************************************************/
void EditorHandler::SelectDisplayInfo(const LbaNet::ModelInfo &mdisinfo, const QModelIndex &parent)
{
	int index = 0;

	std::string dtype = "No";
	switch(mdisinfo.TypeRenderer)
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

		case RenderSphere:
			dtype = "Sphere";
		break;

		case RenderBGImage:
			dtype = "BGImage";
		break;
	}
	{
		QVector<QVariant> data;
		data<<"Display Type"<<dtype.c_str();
		_objectmodel->AppendRow(data, parent);
		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actordtypeList);
		++index;
	}
	

	if(dtype != "No")
	{
		{
			QVector<QVariant> data;
			data<<"Use Light"<<mdisinfo.UseLight;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Cast shadow"<<mdisinfo.CastShadow;
			_objectmodel->AppendRow(data, parent);
			++index;
		}

		{
			QVector<QVariant> data;
			data<<"Display translation X"<<(double)mdisinfo.TransX;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display translation Y"<<(double)mdisinfo.TransY;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display translation Z"<<(double)mdisinfo.TransZ;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display rotation X"<<(double)mdisinfo.RotX;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display rotation Y"<<(double)mdisinfo.RotY;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display rotation Z"<<(double)mdisinfo.RotZ;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display scale X"<<(double)mdisinfo.ScaleX;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display scale Y"<<(double)mdisinfo.ScaleY;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Display scale Z"<<(double)mdisinfo.ScaleZ;
			_objectmodel->AppendRow(data, parent);
			++index;
		}


		if(mdisinfo.TypeRenderer == RenderOsgModel )
		{
			QVector<QVariant> data;
			data<<"Display model file"<<mdisinfo.ModelName.c_str();
			_objectmodel->AppendRow(data, parent);

			_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, index, parent), "Select a model file", "Models", "Model Files (*.osg *.osgb *.osgt)");
			++index;
		}

		if(mdisinfo.TypeRenderer == RenderSprite )
		{
			QVector<QVariant> data;
			data<<"Display sprite file"<<mdisinfo.ModelName.c_str();
			_objectmodel->AppendRow(data, parent);

			_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, index, parent), "Select an image", "Sprites", "Image Files (*.png *.bmp *.jpg *.gif)");
			++index;

			{
				QVector<QVariant> data1;
				data1<<"Color R"<<(double)mdisinfo.ColorR;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color G"<<(double)mdisinfo.ColorG;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color B"<<(double)mdisinfo.ColorB;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color A"<<(double)mdisinfo.ColorA;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Use Billboard"<<mdisinfo.UseBillboard;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
		}

		if(mdisinfo.TypeRenderer == RenderBGImage )
		{
			QVector<QVariant> data;
			data<<"Image file"<<mdisinfo.ModelName.c_str();
			_objectmodel->AppendRow(data, parent);

			_objectmodel->SetCustomFileDialog(_objectmodel->GetIndex(1, index, parent), "Select an image", "Sprites", "Image Files (*.png *.bmp *.jpg *.gif)");
			++index;

			{
				QVector<QVariant> data1;
				data1<<"Color R"<<(double)mdisinfo.ColorR;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color G"<<(double)mdisinfo.ColorG;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color B"<<(double)mdisinfo.ColorB;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color A"<<(double)mdisinfo.ColorA;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
		}


		if(mdisinfo.TypeRenderer == RenderLba1M ||
				mdisinfo.TypeRenderer == RenderLba2M)
		{
			int modelaidx = index;

			QVector<QVariant> data;
			data<<"Display model name"<<mdisinfo.ModelName.c_str();
			_objectmodel->AppendRow(data, parent);

			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actorModelNameList);
			++index;

			QVector<QVariant> data2;
			data2<<"Display model outfit"<<mdisinfo.Outfit.c_str();
			_objectmodel->AppendRow(data2, parent);
			
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actorModelOutfitList);
			++index;

			QVector<QVariant> data3;
			data3<<"Display model weapon"<<mdisinfo.Weapon.c_str();
			_objectmodel->AppendRow(data3, parent);
			
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actorModelWeaponList);
			++index;

			QVector<QVariant> data4;
			data4<<"Display model mode"<<mdisinfo.Mode.c_str();
			_objectmodel->AppendRow(data4, parent);
			
			_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _actorModelModeList);
			++index;


			RefreshActorModelName(modelaidx, parent, false, boost::shared_ptr<ActorHandler>());
		}

		if(mdisinfo.TypeRenderer == RenderSphere ||
				mdisinfo.TypeRenderer == RenderCapsule ||
				mdisinfo.TypeRenderer == RenderBox)
		{

			{
				QVector<QVariant> data1;
				data1<<"Color R"<<(double)mdisinfo.ColorR;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color G"<<(double)mdisinfo.ColorG;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color B"<<(double)mdisinfo.ColorB;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
			{
				QVector<QVariant> data1;
				data1<<"Color A"<<(double)mdisinfo.ColorA;
				_objectmodel->AppendRow(data1, parent);
				++index;
			}
		}
 


		// add materials
		{
			QVector<QVariant> data;
			data<<"Use alpha material"<<mdisinfo.UseTransparentMaterial;
			_objectmodel->AppendRow(data, parent);
			++index;
		}
		{
			QVector<QVariant> data;
			data<<"Alpha"<<(double)mdisinfo.MatAlpha;
			_objectmodel->AppendRow(data, parent);
			++index;
		}

		int matcolortype = mdisinfo.ColorMaterialType;
		{
			std::string mattypestring = "Off";
			switch(matcolortype)
			{
				case 1:
					mattypestring = "Ambient";
				break;
				case 2:
					mattypestring = "Diffuse";
				break;
				case 3:
					mattypestring = "Specular";
				break;
				case 4:
					mattypestring = "Emission";
				break;
				case 5:
					mattypestring = "Ambient_And_Diffuse";
				break;
			}
			QVector<QVariant> data;
			data<<"Color material type"<<mattypestring.c_str();
			_objectmodel->AppendRow(data, parent);
				_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, index, parent), _materialtypeList);
			++index;	
		}

		if(matcolortype > 0)
		{
			{
			QVector<QVariant> data;
			data<<"Mat Ambient ColorR"<<(double)mdisinfo.MatAmbientColorR;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Ambient ColorG"<<(double)mdisinfo.MatAmbientColorG;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Ambient ColorB"<<(double)mdisinfo.MatAmbientColorB;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Ambient ColorA"<<(double)mdisinfo.MatAmbientColorA;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}

			{
			QVector<QVariant> data;
			data<<"Mat Diffuse ColorR"<<(double)mdisinfo.MatDiffuseColorR;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Diffuse ColorG"<<(double)mdisinfo.MatDiffuseColorG;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Diffuse ColorB"<<(double)mdisinfo.MatDiffuseColorB;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Diffuse ColorA"<<(double)mdisinfo.MatDiffuseColorA;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}

			{
			QVector<QVariant> data;
			data<<"Mat Specular ColorR"<<(double)mdisinfo.MatSpecularColorR;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Specular ColorG"<<(double)mdisinfo.MatSpecularColorG;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Specular ColorB"<<(double)mdisinfo.MatSpecularColorB;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Specular ColorA"<<(double)mdisinfo.MatSpecularColorA;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}

			{
			QVector<QVariant> data;
			data<<"Mat Emission ColorR"<<(double)mdisinfo.MatEmissionColorR;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Emission ColorG"<<(double)mdisinfo.MatEmissionColorG;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Emission ColorB"<<(double)mdisinfo.MatEmissionColorB;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Emission ColorA"<<(double)mdisinfo.MatEmissionColorA;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
			{
			QVector<QVariant> data;
			data<<"Mat Shininess"<<(double)mdisinfo.MatShininess;
			_objectmodel->AppendRow(data, parent);
			++index;	
			}
		}	
	}
}

/***********************************************************
select coordinate info
***********************************************************/
void EditorHandler::SelectHoloCoordinate(const HoloCoordinate &coordinate, const QModelIndex &parent)
{
	{
		QVector<QVariant> data;
		data<<"polar coordinate"<<coordinate.polarcoords;
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"X"<<(double)coordinate.posX;
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"Y"<<(double)coordinate.posY;
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"Z"<<(double)coordinate.posZ;
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<(coordinate.polarcoords?"CenterX":"DirectionX")<<(double)coordinate.dir_cen_X;
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<(coordinate.polarcoords?"CenterY":"DirectionY")<<(double)coordinate.dir_cen_Y;
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<(coordinate.polarcoords?"CenterZ":"DirectionZ")<<(double)coordinate.dir_cen_Z;
		_objectmodel->AppendRow(data, parent);
	}
}

/***********************************************************
set Holomap in the object
***********************************************************/
void EditorHandler::SelectHolomap(long id, const QModelIndex &parent)
{
	HolomapPtr ho = HolomapHandler::getInstance()->GetHolomap(id);
	if(!ho)
		return;

	if(parent == QModelIndex())
		ResetObject();

	{
		QVector<QVariant> data;
		data<<"Type"<<"Holomap";
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"Id"<<ho->GetId();
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"Name"<<ho->GetName().c_str();
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"Use Map coordinate"<<ho->GetUsePCoordinates();
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"3D view"<<ho->Get3DMap();
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"3D coordinate scale X"<<(double)ho->Get3DCoordinateScaleX();
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"3D coordinate scale Y"<<(double)ho->Get3DCoordinateScaleY();
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"3D coordinate scale Z"<<(double)ho->Get3DCoordinateScaleZ();
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"Map model"<<"";
		QModelIndex p = _objectmodel->AppendRow(data, parent, true);
		SelectDisplayInfo(ho->GetMapModel(), p);
	}

	{
		QVector<QVariant> data;
		data<<"Arrow model"<<"";
		QModelIndex p = _objectmodel->AppendRow(data, parent, true);
		SelectDisplayInfo(ho->GetArrowModel(), p);
	}

	{
		QVector<QVariant> data;
		data<<"Player model"<<"";
		QModelIndex p = _objectmodel->AppendRow(data, parent, true);
		SelectDisplayInfo(ho->GetPlayerModel(), p);
	}

	{
		QVector<QVariant> data;
		data<<"ArrowPlayer model"<<"";
		QModelIndex p = _objectmodel->AppendRow(data, parent, true);
		SelectDisplayInfo(ho->GetArrowPlayerModel(), p);
	}

	{
		QVector<QVariant> data;
		data<<"Path Dot model"<<"";
		QModelIndex p = _objectmodel->AppendRow(data, parent, true);
		SelectDisplayInfo(ho->GetTravelDotModel(), p);
	}


	// display holomap on screen
	EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::DisplayHolomapEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(),     
						0, id, LbaNet::HoloIdSeq()));
}

/***********************************************************
set Holomap in the object
***********************************************************/
void EditorHandler::SelectHolomapLoc(long id, const QModelIndex &parent)
{
	HolomapLocationPtr ho = HolomapHandler::getInstance()->GetHolomapLoc(id);
	if(!ho)
		return;

	if(parent == QModelIndex())
		ResetObject();

	{
		QVector<QVariant> data;
		data<<"Type"<<"HolomapLoc";
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"Id"<<ho->GetId();
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"Name"<<ho->GetName().c_str();
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"Coordinate"<<"";
		QModelIndex p = _objectmodel->AppendRow(data, parent, true);
		SelectHoloCoordinate(ho->GetCoordinate(), p);
	}


	// text id
	{
		long tid = ho->GetTextId();
		std::string txt = Localizer::getInstance()->GetText(Localizer::Map, tid);
		std::stringstream txttmp;
		txttmp<<tid<<": "<<txt;

		QVector<QVariant> data;
		data<<"Associated Text"<<QString::fromUtf8(txttmp.str().c_str());
		QModelIndex idx = _objectmodel->AppendRow(data, parent);

		_objectmodel->SetCustomIndex(_objectmodel->GetIndex(1, idx.row(), parent), _text_mapNameList);
	}

	{
		QVector<QVariant> data;
		data<<"Linked holomap"<<(int)ho->GetParentHoloId();
		_objectmodel->AppendRow(data, parent);
	}
	{
		QVector<QVariant> data;
		data<<"Parent location"<<(int)ho->GetParentLocId();
		_objectmodel->AppendRow(data, parent);
	}
	{
		QVector<QVariant> data;
		data<<"Child holomap"<<(int)ho->GetChildHoloId();
		_objectmodel->AppendRow(data, parent);
	}

	// display holomap on screen
	EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::DisplayHolomapEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(),     
						3, id, LbaNet::HoloIdSeq()));
}

/***********************************************************
set Holomap in the object
***********************************************************/
void EditorHandler::SelectHolomapPath(long id, const QModelIndex &parent)
{
	HolomapTravelPathPtr ho = HolomapHandler::getInstance()->GetHolomapPath(id);
	if(!ho)
		return;

	if(parent == QModelIndex())
		ResetObject();

	{
		QVector<QVariant> data;
		data<<"Type"<<"HolomapPath";
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"Id"<<ho->GetId();
		_objectmodel->AppendRow(data, parent, true);
	}

	{
		QVector<QVariant> data;
		data<<"Name"<<ho->GetName().c_str();
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"Linked holomap"<<(int)ho->GetParentHoloId();
		_objectmodel->AppendRow(data, parent);
	}

	{
		QVector<QVariant> data;
		data<<"Vehicle model"<<"";
		QModelIndex p = _objectmodel->AppendRow(data, parent, true);
		SelectDisplayInfo(ho->GetVehicleModel(), p);
	}

	const std::vector<HoloCoordinate> & _coordinates = ho->GetCoordinates();
	QVector<QVariant> data;
	data<<"Path coordinates"<<"";
	QModelIndex coordparent = _objectmodel->AppendRow(data, parent, true);
	for(size_t i=0; i< _coordinates.size(); ++i)
	{
		QVector<QVariant> data;
		data<<"Coordinate"<<i;
		QModelIndex p = _objectmodel->AppendRow(data, parent);
		SelectHoloCoordinate(_coordinates[i], p);
	}

	// add new item
	QVector<QVariant> datait;
	datait << "Coordinate" << "Add new...";
	QModelIndex idxit = _objectmodel->AppendRow(datait, coordparent);	


	// display holomap on screen
	EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::DisplayHolomapEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(),     
						4, id, LbaNet::HoloIdSeq()));
}



/***********************************************************
called when DisplayInfoChanged
***********************************************************/
void EditorHandler::DisplayInfoChanged(const QModelIndex &parentIdx, LbaNet::ModelInfo & dmodel)
{
	int index = 0;
	bool refresh = false;

	LbaNet::ModelInfo olddisinfo = dmodel; // copy
	LbaNet::ModelInfo & newdisinfo(dmodel);

	std::string dtype = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
	++index;
	if(dtype == "Osg Model") 
		newdisinfo.TypeRenderer = LbaNet::RenderOsgModel;
	if(dtype == "Sprite") 
		newdisinfo.TypeRenderer = LbaNet::RenderSprite;
	if(dtype == "Lba1 Model") 
		newdisinfo.TypeRenderer = LbaNet::RenderLba1M;
	if(dtype == "Lba2 Model") 
		newdisinfo.TypeRenderer = LbaNet::RenderLba2M;
	if(dtype == "Box") 
		newdisinfo.TypeRenderer = LbaNet::RenderBox;
	if(dtype == "Sphere") 
		newdisinfo.TypeRenderer = LbaNet::RenderSphere;
	if(dtype == "Capsule") 
		newdisinfo.TypeRenderer = LbaNet::RenderCapsule;
	if(dtype == "Cross") 
		newdisinfo.TypeRenderer = LbaNet::RenderCross;
	if(dtype == "BGImage") 
		newdisinfo.TypeRenderer = LbaNet::RenderBGImage;

	if(dtype == "No") 
		newdisinfo.TypeRenderer = LbaNet::NoRender;

	if(olddisinfo.TypeRenderer != newdisinfo.TypeRenderer)
	{
		refresh = true;

		if(newdisinfo.TypeRenderer == LbaNet::RenderLba1M)
		{
			newdisinfo.ModelName = "Ameba";
			newdisinfo.Weapon = "No";
			newdisinfo.Mode = "Normal";
			newdisinfo.Outfit = "No";
			newdisinfo.ColorMaterialType = 4;
			newdisinfo.MatAmbientColorR = -0.2;
			newdisinfo.MatAmbientColorG = -0.2;
			newdisinfo.MatAmbientColorB = -0.2;
			newdisinfo.MatDiffuseColorR = 0.4;
			newdisinfo.MatDiffuseColorG = 0.4;
			newdisinfo.MatDiffuseColorB = 0.4;
		}
	}

	if(!refresh)	
	{
		if(olddisinfo.TypeRenderer != LbaNet::NoRender)
		{
			newdisinfo.UseLight = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
			++index;
			newdisinfo.CastShadow = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
			++index;

			newdisinfo.TransX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			newdisinfo.TransY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			newdisinfo.TransZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;

			newdisinfo.RotX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			newdisinfo.RotY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			newdisinfo.RotZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;

			newdisinfo.ScaleX = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			newdisinfo.ScaleY = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;
			newdisinfo.ScaleZ = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toFloat();
			++index;


			if(olddisinfo.TypeRenderer == RenderOsgModel )
			{
				newdisinfo.ModelName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				++index;
			}

			if(olddisinfo.TypeRenderer == RenderSprite )
			{
				newdisinfo.ModelName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				++index;	

				newdisinfo.ColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;	

				newdisinfo.ColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;		

				newdisinfo.ColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;		

				newdisinfo.ColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;	

				newdisinfo.UseBillboard = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
				++index;	
			}

			if(olddisinfo.TypeRenderer == RenderSphere ||
					olddisinfo.TypeRenderer == RenderCapsule ||
					olddisinfo.TypeRenderer == RenderBox)
			{
				newdisinfo.ColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;	

				newdisinfo.ColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;		

				newdisinfo.ColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;		

				newdisinfo.ColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;	
			}

			if(newdisinfo.TypeRenderer == RenderLba1M ||
					newdisinfo.TypeRenderer == RenderLba2M)
			{
				std::string oldmodelname = newdisinfo.ModelName;
				std::string oldmodelOutfit = newdisinfo.Outfit;
				std::string oldmodelWeapon = newdisinfo.Weapon;

				newdisinfo.ModelName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				++index;		

				newdisinfo.Outfit = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();		
				++index;	

				newdisinfo.Weapon = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();		
				++index;	

				newdisinfo.Mode = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();		
				++index;

				if(newdisinfo.ModelName != oldmodelname)
				{
					RefreshSimpleActorModelName(newdisinfo);
					refresh = true;
				}
				else if(newdisinfo.Outfit != oldmodelOutfit)
				{
					RefreshSimpleActorModelWeapon(newdisinfo);
					refresh = true;
				}	
				else if(newdisinfo.Weapon != oldmodelWeapon)
				{
					RefreshSimpleActorModelMode(newdisinfo);
					refresh = true;
				}	
			}

			if(olddisinfo.TypeRenderer == RenderBGImage )
			{
				newdisinfo.ModelName = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
				++index;	

				newdisinfo.ColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;	

				newdisinfo.ColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;		

				newdisinfo.ColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;		

				newdisinfo.ColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toFloat();
				++index;	
			}


			// check materials
			newdisinfo.UseTransparentMaterial = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();		
			++index;
			newdisinfo.MatAlpha = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		
			++index;

			int oldmatcolortype = olddisinfo.ColorMaterialType;

			std::string matstringtype = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();	
			++index;

			newdisinfo.ColorMaterialType = 0;
			if(matstringtype == "Ambient")
				newdisinfo.ColorMaterialType = 1;
			if(matstringtype == "Diffuse")
				newdisinfo.ColorMaterialType = 2;
			if(matstringtype == "Specular")
				newdisinfo.ColorMaterialType = 3;
			if(matstringtype == "Emission")
				newdisinfo.ColorMaterialType = 4;
			if(matstringtype == "Ambient_And_Diffuse")
				newdisinfo.ColorMaterialType = 5;

			if(newdisinfo.ColorMaterialType != oldmatcolortype)
				refresh = true;


			if(oldmatcolortype > 0)
			{
				newdisinfo.MatAmbientColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatAmbientColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatAmbientColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatAmbientColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatDiffuseColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatDiffuseColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatDiffuseColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatDiffuseColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatSpecularColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatSpecularColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatSpecularColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatSpecularColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;	
				newdisinfo.MatEmissionColorR = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatEmissionColorG = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatEmissionColorB = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;			
				newdisinfo.MatEmissionColorA = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;	
				newdisinfo.MatShininess = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();		 
				++index;				
			}	
		}
	}

	if(refresh)
	{
		_objectmodel->Clear(parentIdx);
		SelectDisplayInfo(newdisinfo, parentIdx);
	}
}

/***********************************************************
select coordinate info
***********************************************************/
void EditorHandler::HoloCoordinateChanged(HoloCoordinate &coordinate, const QModelIndex &parentIdx)
{
	int index = 0;

	coordinate.polarcoords = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
	++index;

	coordinate.posX = (float)_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();
	++index;

	coordinate.posY = (float)_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();
	++index;

	coordinate.posZ = (float)_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();
	++index;

	coordinate.dir_cen_X = (float)_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();
	++index;

	coordinate.dir_cen_Y = (float)_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();
	++index;

	coordinate.dir_cen_Z = (float)_objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();
	++index;
}

/***********************************************************
called when Holomap object changed
***********************************************************/
void EditorHandler::HolomapChanged(long id, const QModelIndex &parentIdx)
{
	SetModified();
	int index = 2;

	HolomapPtr holo = HolomapHandler::getInstance()->GetHolomap(id);

	{
	std::string name = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
	holo->SetName(name);
	++index;
	}

	{
		bool mapcood = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
		holo->SetUsePCoordinates(mapcood);
		++index;
	}

	{
		bool d3vie = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toBool();
		holo->Set3DMap(d3vie);
		++index;
	}

	{
		float v = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();
		holo->Set3DCoordinateScaleX(v);
		++index;
	}

	{
		float v = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();
		holo->Set3DCoordinateScaleY(v);
		++index;
	}

	{
		float v = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toDouble();
		holo->Set3DCoordinateScaleZ(v);
		++index;
	}

	{
		QModelIndex itemparent = _objectmodel->GetIndex(0, index, parentIdx);
		DisplayInfoHandler newmodel;
		newmodel.Dinfo = holo->GetMapModel();
		DisplayInfoChanged(itemparent, newmodel.Dinfo);

		holo->SetMapModel(newmodel);
		++index;
	}

	{
		QModelIndex itemparent = _objectmodel->GetIndex(0, index, parentIdx);
		DisplayInfoHandler newmodel;
		newmodel.Dinfo = holo->GetArrowModel();
		DisplayInfoChanged(itemparent, newmodel.Dinfo);
		holo->SetArrowModel(newmodel);
		++index;
	}

	{
		QModelIndex itemparent = _objectmodel->GetIndex(0, index, parentIdx);
		DisplayInfoHandler newmodel;
		newmodel.Dinfo = holo->GetPlayerModel();
		DisplayInfoChanged(itemparent, newmodel.Dinfo);
		holo->SetPlayerModel(newmodel);
		++index;
	}

	{
		QModelIndex itemparent = _objectmodel->GetIndex(0, index, parentIdx);
		DisplayInfoHandler newmodel;
		newmodel.Dinfo = holo->GetArrowPlayerModel();
		DisplayInfoChanged(itemparent, newmodel.Dinfo);
		holo->SetArrowPlayerModel(newmodel);
		++index;
	}

	{
		QModelIndex itemparent = _objectmodel->GetIndex(0, index, parentIdx);
		DisplayInfoHandler newmodel;
		newmodel.Dinfo = holo->GetTravelDotModel();
		DisplayInfoChanged(itemparent, newmodel.Dinfo);
		holo->SetTravelDotModel(newmodel);
		++index;
	}

	// display holomap on screen
	EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::DisplayHolomapEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(),     
						0, id, LbaNet::HoloIdSeq()));
}

/***********************************************************
called when Holomap object changed
***********************************************************/
void EditorHandler::HolomapLocChanged(long id, const QModelIndex &parentIdx)
{
	SetModified();
	int index = 2;

	HolomapLocationPtr holo = HolomapHandler::getInstance()->GetHolomapLoc(id);

	{
	std::string name = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
	holo->SetName(name);
	++index;
	}

	{
		QModelIndex itemparent = _objectmodel->GetIndex(0, index, parentIdx);
		HoloCoordinate newcoord;
		HoloCoordinateChanged(newcoord, itemparent);
		holo->SetCoordinate(newcoord);
		++index;
	}


	// text id
	{
		std::string text = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toString().toAscii().data();
		text = text.substr(0, text.find(":"));
		long textid = atol(text.c_str());
		holo->SetTextId(textid);
		++index;
	}

	{
		long id = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();
		holo->SetParentHoloId(id);
		++index;
	}

	{
		long id = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();
		holo->SetParentLocId(id);
		++index;
	}

	{
		long id = _objectmodel->data(_objectmodel->GetIndex(1, index, parentIdx)).toInt();
		holo->SetChildHoloId(id);
		++index;
	}


	// display holomap on screen
	EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::DisplayHolomapEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(),     
						3, id, LbaNet::HoloIdSeq()));
}

/***********************************************************
called when Holomap object changed
***********************************************************/
void EditorHandler::HolomapPathChanged(long id, const QModelIndex &parentIdx)
{

}