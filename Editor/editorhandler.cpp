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
#include "DataLoader.h"
#include "SharedDataHandler.h"
#include "ServerLuaHandler.h"
#include "Triggers.h"

#include <QMessageBox>

#include <fstream>

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
	_ids.clear();

	if(_stringMatrix.size() > 0)
	{
		beginRemoveRows(QModelIndex(), 0, _stringMatrix.size()-1);

		for(size_t i=0; i<_stringMatrix.size(); ++i)
			_stringMatrix[i].clear();

		endRemoveRows();
	}

	reset();
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
	QModelIndex index = createIndex(col, row);
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
	if(_objMatrix.size() > 0)
	{
		beginRemoveRows(QModelIndex(), 0, _objMatrix.size()-1);

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
CustomDelegate::CustomDelegate(QObject *parent)
     : QStyledItemDelegate(parent)
{
}


/***********************************************************
Constructor
***********************************************************/
QWidget *CustomDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
	std::map<int, boost::shared_ptr<QStringList> >::const_iterator it = _customs.find(index.row());
	if(it != _customs.end())
	{
		 QComboBox *editor = new QComboBox(parent);
		 editor->insertItems(0, *(it->second));
		 editor->setEditable(false);
		 return editor;
	}

	return QStyledItemDelegate::createEditor(parent, option, index);
}


/***********************************************************
Constructor
***********************************************************/
void CustomDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	std::map<int, boost::shared_ptr<QStringList> >::const_iterator it = _customs.find(index.row());
	if(it != _customs.end())
	{
		 QString value = index.model()->data(index, Qt::DisplayRole).toString();

		 QComboBox *comboBox = static_cast<QComboBox*>(editor);
		 int index = comboBox->findText(value);
		 if(index >= 0)
			comboBox->setCurrentIndex(index);
	}

	QStyledItemDelegate::setEditorData(editor, index);
}


/***********************************************************
Constructor
***********************************************************/
void CustomDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const
{
	std::map<int, boost::shared_ptr<QStringList> >::const_iterator it = _customs.find(index.row());
	if(it != _customs.end())
	{
		 QComboBox *comboBox = static_cast<QComboBox*>(editor);
		 QString value = comboBox->currentText();
		 model->setData(index, value);
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
}

/***********************************************************
Constructor
***********************************************************/
void CustomDelegate::SetCustomIndex(int index, boost::shared_ptr<QStringList> list)
{
	_customs[index] = list;
}









/***********************************************************
Constructor
***********************************************************/
EditorHandler::EditorHandler(QWidget *parent, Qt::WindowFlags flags)
 : QMainWindow(parent, flags), _modified(false), 
 _actionNameList(new QStringList()), _mapNameList(new QStringList()),
 _curractionidx(0), _currspawningidx(0), _currtriggeridx(0),
	_updatetriggerdialogonnewaction(-1), _triggerNameList(new QStringList())
{
	_uieditor.setupUi(this);

	_addtriggerdialog = new QDialog(this);
	_uiaddtriggerdialog.setupUi(_addtriggerdialog);

	_openworlddialog = new QDialog(this);
	_uiopenworlddialog.setupUi(_openworlddialog);

	_addspawningdialog = new QDialog(this);
	_uiaddspawningdialog.setupUi(_addspawningdialog);

	_addactiondialog = new QDialog(this);
	_ui_addactiondialog.setupUi(_addactiondialog);
	


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
		 header << "Name" << "Map" << "Spawning";
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

	// set model for objectmap
	{
		 QStringList header;
		 header << "Property" << "Value";
		_objectmodel = new MixedTableModel(header);
		_uieditor.tableView_object->setModel(_objectmodel);
		QHeaderView * mpheaders = _uieditor.tableView_object->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);

		_objectcustomdelegate = new CustomDelegate();
		_uieditor.tableView_object->setItemDelegate(_objectcustomdelegate);

		_uieditor.tableView_object->setEditTriggers(QAbstractItemView::CurrentChanged | 
													QAbstractItemView::DoubleClicked | 
													QAbstractItemView::SelectedClicked);
	}


	// set model for actionlist
	{
		 QStringList header;
		 header << "Name" << "Type";
		_actionlistmodel = new StringTableModel(header);
		_uieditor.tableViewActionList->setModel(_actionlistmodel);
		QHeaderView * mpheaders = _uieditor.tableViewActionList->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
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
		
	

	// reset world info
	ResetWorld();


	// show myself
	showMaximized();

	// connect signals and slots
	connect(_uieditor.actionQuit, SIGNAL(triggered()), this, SLOT(quit())); 
	connect(_uieditor.actionNew_World, SIGNAL(triggered()), this, SLOT(NewWorldAction())); 
	connect(_uieditor.actionLoad_World, SIGNAL(triggered()), this, SLOT(OpenWorldAction())); 
	connect(_uieditor.actionSave, SIGNAL(triggered()), this, SLOT(SaveWorldAction())); 
	connect(_uieditor.pushButton_info_go, SIGNAL(clicked()) , this, SLOT(info_go_clicked()));
	connect(_uieditor.radioButton_info_player, SIGNAL(toggled(bool)) , this, SLOT(info_camera_toggled(bool)));

	connect(_uieditor.pushButton_addTrigger, SIGNAL(clicked()) , this, SLOT(addtrigger_button_clicked()));
	connect(_uieditor.pushButton_removeTrigger, SIGNAL(clicked()) , this, SLOT(removetrigger_button_clicked()));	
	connect(_uieditor.pushButton_selectTrigger, SIGNAL(clicked()) , this, SLOT(selecttrigger_button_clicked()));		

	connect(_uieditor.pushButton_addSpwaning, SIGNAL(clicked()) , this, SLOT(addspawning_button_clicked()));
	connect(_uieditor.pushButton_removeSpwaning, SIGNAL(clicked()) , this, SLOT(removespawning_button_clicked()));	
	connect(_uieditor.pushButton_selectSpwaning, SIGNAL(clicked()) , this, SLOT(selectspawning_button_clicked()));		

	connect(_uieditor.pushButton_addAction, SIGNAL(clicked()) , this, SLOT(addAction_button_clicked()));
	connect(_uieditor.pushButton_removeAction, SIGNAL(clicked()) , this, SLOT(removeAction_button_clicked()));	
	connect(_uieditor.pushButton_selectAction, SIGNAL(clicked()) , this, SLOT(selectAction_button_clicked()));		

	connect(_uiaddtriggerdialog.pushButton_addact1, SIGNAL(clicked()) , this, SLOT(addAction1_button_clicked()));
	connect(_uiaddtriggerdialog.pushButton_addact2, SIGNAL(clicked()) , this, SLOT(addAction2_button_clicked()));
	connect(_uiaddtriggerdialog.pushButton_addact3, SIGNAL(clicked()) , this, SLOT(addAction3_button_clicked()));
	
	connect(_uieditor.pushButton_goto_tp, SIGNAL(clicked()) , this, SLOT(goto_tp_button_clicked()));
	connect(_uieditor.pushButton_goto_map, SIGNAL(clicked()) , this, SLOT(goto_map_button_clicked()));

	connect(_uieditor.tableView_TeleportList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(goto_tp_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_MapList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(goto_map_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableView_SpawningList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selectspawning_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableViewActionList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selectaction_double_clicked(const QModelIndex&)));
	connect(_uieditor.tableViewTriggerList, SIGNAL(doubleClicked(const QModelIndex&)) , this, SLOT(selecttrigger_double_clicked(const QModelIndex&)));



	connect(_objectmodel, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)) , 
								this, SLOT(objectdatachanged(const QModelIndex &, const QModelIndex &)));


	connect(_uiaddtriggerdialog.buttonBox, SIGNAL(accepted()) , this, SLOT(addtrigger_accepted()));
	connect(_uiopenworlddialog.buttonBox, SIGNAL(accepted()) , this, SLOT(OpenWorld()));
	connect(_uiaddspawningdialog.buttonBox, SIGNAL(accepted()) , this, SLOT(AddSpawning_clicked()));
	connect(_ui_addactiondialog.buttonBox, SIGNAL(accepted()) , this, SLOT(AddActionAccepted()));

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
	_uiaddtriggerdialog.comboBox_action1->clear();
	_uiaddtriggerdialog.comboBox_action1->insertItems(0, *_actionNameList);
	_uiaddtriggerdialog.comboBox_action2->clear();
	_uiaddtriggerdialog.comboBox_action2->insertItems(0, *_actionNameList);
	_uiaddtriggerdialog.comboBox_action3->clear();
	_uiaddtriggerdialog.comboBox_action3->insertItems(0, *_actionNameList);
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

	if(_triggerNameList->contains(triggername))
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
			trig->SetAction1(GetActionId(_uiaddtriggerdialog.comboBox_action1->currentText().toAscii().data()));
			trig->SetAction2(GetActionId(_uiaddtriggerdialog.comboBox_action2->currentText().toAscii().data()));
			trig->SetAction3(GetActionId(_uiaddtriggerdialog.comboBox_action3->currentText().toAscii().data()));
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
		//TODO - ResetWorld
		//TODO - set saved
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
	if(_modified)
	{
		// save xml file
		DataLoader::getInstance()->SaveWorldInformation(_winfo.Description.WorldName, _winfo);

		// save global lua file
		SaveGlobalLua("./Data/Worlds/" + _winfo.Description.WorldName + "/Lua/global_server.lua");

		// save current map
		std::string mapname = _uieditor.label_mapname->text().toAscii().data();
		SaveMap("./Data/Worlds/" + _winfo.Description.WorldName + "/Lua/" + mapname + "_server.lua");

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
	DataLoader::getInstance()->GetWorldInformation(worldname, _winfo);

	setWindowTitle(("LBANet Editor - " + worldname).c_str());

	_uieditor.label_worldname->setText(_winfo.Description.WorldName.c_str());

	_uieditor.textEdit_worlddescription->setText(_winfo.Description.Description.c_str());

	_uieditor.textEdit_worldnews->setText(_winfo.Description.News.c_str());


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

			(*_mapNameList) << itm->first.c_str();

			// add spawning to the list
			_mapSpawningList[itm->first] = boost::shared_ptr<QStringList>(new QStringList());
			LbaNet::SpawningsSeq::const_iterator itsp = itm->second.Spawnings.begin();
			LbaNet::SpawningsSeq::const_iterator endsp = itm->second.Spawnings.end();
			for(; itsp != endsp; ++itsp)
			{
				*(_mapSpawningList[itm->first]) << itsp->second.Name.c_str();
			}
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
			data << ittp->first.c_str() << ittp->second.MapName.c_str() << spawningname.c_str();
			_tplistmodel->AddOrUpdateRow(cc, data);
		}
	}



	// add lua stuff
	std::string luafile = "Worlds/" + _winfo.Description.WorldName + "/Lua/";
	std::string globalluafile = luafile + "global_server.lua";
	_luaH = boost::shared_ptr<ServerLuaHandler>(new ServerLuaHandler());
	_luaH->LoadFile(globalluafile);
	_luaH->CallLua("InitGlobal", this);
}




/***********************************************************
reset world display in editor
***********************************************************/
void EditorHandler::ResetWorld()
{
	_maplistmodel->Clear();
	_tplistmodel->Clear();
	_actionlistmodel->Clear();
	_actionNameList->clear();
	*_actionNameList << "None";
	_mapNameList->clear();

	_uieditor.label_worldname->setText("");
	_uieditor.textEdit_worlddescription->setText("");
	_uieditor.textEdit_worldnews->setText("");

	_curractionidx = 0;

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

	_triggerlistmodel->Clear();
	_triggers.clear();
	_triggerNameList->clear();
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
			// add a default spawning
			long spid = AddOrModSpawning(mapname, "DefaultSpawning", 0, 0, 0, 0, true, 0);
			AddSpawningName(mapname, "DefaultSpawning");
			ChangeMap(mapname, spid);
			SetModified();
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
	_uieditor.textEdit_map_description->setText(mapinfo.Description.c_str());

	switch(mapinfo.AutoCameraType)
	{
		case 1:
			_uieditor.radioButton_camtype_ortho->setDown(true);
		break;

		case 2:
			_uieditor.radioButton_camtype_persp->setDown(true);
		break;

		case 3:
			_uieditor.radioButton_camtype_3d->setDown(true);
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
	std::string globalluafile = luafile + "global_server.lua";
	luafile += mapname + "_server.lua";
	_luaH = boost::shared_ptr<ServerLuaHandler>(new ServerLuaHandler());
	_luaH->LoadFile(globalluafile);
	_luaH->LoadFile(luafile);
	_luaH->CallLua("InitMap", this);
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
	_uiaddspawningdialog.doubleSpinBox_posx->setValue(0);
	_uiaddspawningdialog.doubleSpinBox_posy->setValue(0);
	_uiaddspawningdialog.doubleSpinBox_posz->setValue(0);
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
		std::string mapname = _uieditor.label_mapname->text().toAscii().data();
		LbaNet::SpawningsSeq::const_iterator it = _winfo.Maps[mapname].Spawnings.find(spawningid);
		if(it != _winfo.Maps[mapname].Spawnings.end())
		{
			SelectSpawning(spawningid, it->second.Name,
									it->second.PosX, it->second.PosY, it->second.PosZ,
									it->second.Rotation, it->second.ForceRotation);
		}
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


	if(_mapSpawningList[mapname]->contains(spname))
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

	SelectSpawning(id, spname.toAscii().data(),
				(float)_uiaddspawningdialog.doubleSpinBox_posx->value(), 
				(float)_uiaddspawningdialog.doubleSpinBox_posy->value(), 
				(float)_uiaddspawningdialog.doubleSpinBox_posz->value(),
				(float)_uiaddspawningdialog.doubleSpinBox_rotation->value(), 
				_uiaddspawningdialog.checkBox_forcerotation->isChecked());

	SetModified();
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

		ClearObjectIfSelected("Spawning", spawningid);

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
void EditorHandler::SelectSpawning(long id, const std::string &spawningname,
						float PosX, float PosY, float PosZ,
						float Rotation, bool forcedrotation)
{
	ResetObject();


	{
		QVariantList data;
		data<<"Type"<<"Spawning";
		_objectmodel->AddRow(data);
	}

	{
		QVariantList data;
		data<<"SubCategory"<<"-";
		_objectmodel->AddRow(data);
	}

	{
		QVariantList data;
		data<<"Id"<<id;
		_objectmodel->AddRow(data);
	}

	{
		QVariantList data;
		data<<"Name"<<spawningname.c_str();
		_objectmodel->AddRow(data);
	}

	{
		QVariantList data;
		data<<"PosX"<<(double)PosX;
		_objectmodel->AddRow(data);
	}

	{
		QVariantList data;
		data<<"PosY"<<(double)PosY;
		_objectmodel->AddRow(data);
	}

	{
		QVariantList data;
		data<<"PosZ"<<(double)PosZ;
		_objectmodel->AddRow(data);
	}

	{
		QVariantList data;
		data<<"Force Rotation"<<forcedrotation;
		_objectmodel->AddRow(data);
	}

	{
		QVariantList data;
		data<<"Rotation"<<(double)Rotation;
		_objectmodel->AddRow(data);
	}
}


/***********************************************************
clear the object displayed if it is the selected one
***********************************************************/
void EditorHandler::ClearObjectIfSelected(const std::string objecttype, long id)
{
	if(_objectmodel->rowCount() > 2)
	{
		QString type = _objectmodel->GetData(1, 0).toString();
		if(objecttype == type.toAscii().data())
		{
			long objid = _objectmodel->GetData(1, 2).toString().toLong();	
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
	if(_objectmodel->rowCount() > 2)
	{
		QString type = _objectmodel->GetData(1, 0).toString();
		std::string category = _objectmodel->GetData(1, 1).toString().toAscii().data();
		long objid = _objectmodel->GetData(1, 2).toString().toLong();

		if(type == "Spawning")
		{
			SpawningObjectChanged(objid);
			return;
		}

		if(type == "Action")
		{
			ActionObjectChanged(objid, category);
			return;
		}

		if(type == "Trigger")
		{
			TriggerObjectChanged(objid, category);
			return;
		}
	}
}


/***********************************************************
called when spawning object changed
***********************************************************/
void EditorHandler::SpawningObjectChanged(long id)
{
	if(_objectmodel->rowCount() > 8)
	{
		QString name = _objectmodel->GetData(1, 3).toString();
		float PosX = _objectmodel->GetData(1, 4).toFloat();
		float PosY = _objectmodel->GetData(1, 5).toFloat();
		float PosZ = _objectmodel->GetData(1, 6).toFloat();
		bool forcedrotation = _objectmodel->GetData(1, 7).toBool();
		float Rotation = _objectmodel->GetData(1, 8).toFloat();
		std::string mapname = _uieditor.label_mapname->text().toAscii().data();
		std::string oldname = _winfo.Maps[mapname].Spawnings[id].Name;

		// check if name changed already exist
		if(name != oldname.c_str())
		{
			if(name == "" || _mapSpawningList[mapname]->contains(name))
			{
				QMessageBox::warning(this, tr("Name already used"),
					tr("The name you entered for the spawning is already used. Please enter a unique name."),
					QMessageBox::Ok);

				_objectmodel->SetData(1, 3, oldname.c_str());
				return;
			}
		}


		ReplaceSpawningName(mapname, oldname, name.toAscii().data());


		AddOrModSpawning(mapname, name.toAscii().data(),
									PosX, PosY, PosZ,
									Rotation, forcedrotation,
									id);

		SetModified();
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

		*_triggerNameList << trigger->GetName().c_str();
	}
}

/***********************************************************
add an action
***********************************************************/				
void EditorHandler::AddAction(boost::shared_ptr<ActionBase> action)
{
	if(action)
	{
		_curractionidx = action->GetId();

		_actions[_curractionidx] = action;

		QStringList slist;
		slist << action->GetName().c_str() << action->GetTypeName().c_str();
		_actionlistmodel->AddOrUpdateRow(_curractionidx, slist);

		AddActionName(action->GetName());
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
get the action correspondant to the id
***********************************************************/				
boost::shared_ptr<ActionBase> EditorHandler::GetAction(long actionid)
{
	std::map<long, boost::shared_ptr<ActionBase> >::iterator it = _actions.find(actionid);
	if(it != _actions.end())
		return it->second;

	return boost::shared_ptr<ActionBase>();
}



/***********************************************************
add an new action to the list
***********************************************************/	
void EditorHandler::AddNewAction(boost::shared_ptr<ActionBase> action)
{
	if(action)
	{
		// add action internally
		AddAction(action);
		SetModified();

		//inform server
		EditorUpdateBasePtr update = new UpdateEditor_AddOrModAction(action);
		SharedDataHandler::getInstance()->EditorUpdate("", update);

		// update add trigger dialog if opened
		if(_updatetriggerdialogonnewaction>=0)
		{
			int index1 = _uiaddtriggerdialog.comboBox_action1->currentIndex();
			int index2 = _uiaddtriggerdialog.comboBox_action2->currentIndex();
			int index3 = _uiaddtriggerdialog.comboBox_action3->currentIndex();

			_uiaddtriggerdialog.comboBox_action1->clear();
			_uiaddtriggerdialog.comboBox_action1->insertItems(0, *_actionNameList);
			_uiaddtriggerdialog.comboBox_action2->clear();
			_uiaddtriggerdialog.comboBox_action2->insertItems(0, *_actionNameList);
			_uiaddtriggerdialog.comboBox_action3->clear();
			_uiaddtriggerdialog.comboBox_action3->insertItems(0, *_actionNameList);

			_uiaddtriggerdialog.comboBox_action1->setCurrentIndex(index1);
			_uiaddtriggerdialog.comboBox_action2->setCurrentIndex(index2);
			_uiaddtriggerdialog.comboBox_action3->setCurrentIndex(index3);

			switch(_updatetriggerdialogonnewaction)
			{
				case 1:
				{
					 int index = _uiaddtriggerdialog.comboBox_action1->findText(action->GetName().c_str());
					 if(index >= 0)
						_uiaddtriggerdialog.comboBox_action1->setCurrentIndex(index);
				}
				break;

				case 2:
				{
					 int index = _uiaddtriggerdialog.comboBox_action2->findText(action->GetName().c_str());
					 if(index >= 0)
						_uiaddtriggerdialog.comboBox_action2->setCurrentIndex(index);
				}
				break;

				case 3:
				{
					 int index = _uiaddtriggerdialog.comboBox_action3->findText(action->GetName().c_str());
					 if(index >= 0)
						_uiaddtriggerdialog.comboBox_action3->setCurrentIndex(index);
				}
				break;
			}

			_updatetriggerdialogonnewaction = -1;
		}
	}
}

/***********************************************************
remove an action from the list
***********************************************************/	
void EditorHandler::RemoveAction(long id)
{
	//remove internal action
	std::map<long, boost::shared_ptr<ActionBase> >::iterator it = _actions.find(id);
	if(it != _actions.end())
	{
		RemoveActionName(it->second->GetName());
		_actions.erase(it);
		SetModified();


		//inform server
		EditorUpdateBasePtr update = new UpdateEditor_RemoveAction(id);
		SharedDataHandler::getInstance()->EditorUpdate("", update);
	}
}


/***********************************************************
add an action name to the name list
***********************************************************/
void EditorHandler::AddActionName(const std::string & name)
{
	if(!_actionNameList->contains(name.c_str()))
		(*_actionNameList) << name.c_str();
}


/***********************************************************
remove an action name to the name list
***********************************************************/
void EditorHandler::RemoveActionName(const std::string & name)
{
	QStringList::iterator it = std::find(_actionNameList->begin(), _actionNameList->end(), name.c_str());
	if(it != _actionNameList->end())
		_actionNameList->erase(it);
}


/***********************************************************
replace an action name to the name list
***********************************************************/
void EditorHandler::ReplaceActionName(const std::string & oldname, const std::string & newname)
{
	QStringList::iterator it = std::find(_actionNameList->begin(), _actionNameList->end(), oldname.c_str());
	if(it != _actionNameList->end())
		*it = newname.c_str();
}


/***********************************************************
addAction_button_clicked
***********************************************************/
void EditorHandler::addAction1_button_clicked()
{
	_updatetriggerdialogonnewaction = 1;
	addAction_button_clicked();
}

/***********************************************************
addAction_button_clicked
***********************************************************/
void EditorHandler::addAction2_button_clicked()
{
	_updatetriggerdialogonnewaction = 2;
	addAction_button_clicked();
}

/***********************************************************
addAction_button_clicked
***********************************************************/
void EditorHandler::addAction3_button_clicked()
{
	_updatetriggerdialogonnewaction = 3;
	addAction_button_clicked();
}

/***********************************************************
addAction_button_clicked
***********************************************************/
void EditorHandler::addAction_button_clicked()
{
	if(!IsWorldOpened())
		return;

	// clear data
	_ui_addactiondialog.lineEdit_actionname->setText("");

	_addactiondialog->show();
}



/***********************************************************
removeAction_button_clicked
***********************************************************/
void EditorHandler::removeAction_button_clicked()
{
	QItemSelectionModel *selectionModel = _uieditor.tableViewActionList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();
	if(indexes.size() > 1)
	{
		// inform server
		long id = _actionlistmodel->GetId(indexes[0]);
		RemoveAction(id);

		// remove row from table
		_actionlistmodel->removeRows(indexes[0].row(), 1);

		// clear object
		ClearObjectIfSelected("Action", id);
	}
}


/***********************************************************
selectAction_button_clicked
***********************************************************/
void EditorHandler::selectaction_double_clicked(const QModelIndex & itm)
{
	selectAction_button_clicked();
}

/***********************************************************
selectAction_button_clicked
***********************************************************/
void EditorHandler::selectAction_button_clicked()
{
	QItemSelectionModel *selectionModel = _uieditor.tableViewActionList->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();
	if(indexes.size() > 1)
	{
		long id = _actionlistmodel->GetId(indexes[0]);
		SelectAction(id);
	}
}


/***********************************************************
add action accepted
***********************************************************/
void EditorHandler::AddActionAccepted()
{
	QString actname = _ui_addactiondialog.lineEdit_actionname->text();

	if(actname == "" || actname == "None")
		return;

	if(_actionNameList->contains(actname))
	{
		QMessageBox::warning(this, tr("Name already used"),
			tr("The name you entered for the action is already used. Please enter a unique name."),
			QMessageBox::Ok);
		return;
	}

	_addactiondialog->hide();
	long id = _curractionidx+1;

	switch(_ui_addactiondialog.comboBox_actiontype->currentIndex())
	{
		case 0: // teleport
		{
			AddNewAction(boost::shared_ptr<ActionBase>
				(new TeleportAction(id,	actname.toAscii().data(), "", -1)));
		}
		break;
	}

	SelectAction(id);
}

/***********************************************************
select an action and display it in object view
***********************************************************/
void EditorHandler::SelectAction(long id)
{
	std::map<long, boost::shared_ptr<ActionBase> >::iterator it = _actions.find(id);
	if(it != _actions.end())
	{
		ResetObject();

		{
			QVariantList data;
			data<<"Type"<<"Action";
			_objectmodel->AddRow(data);
		}

		{
			QVariantList data;
			data<<"SubCategory"<<it->second->GetTypeName().c_str();
			_objectmodel->AddRow(data);
		}

		{
			QVariantList data;
			data<<"Id"<<id;
			_objectmodel->AddRow(data);
		}

		{
			QVariantList data;
			data<<"Name"<<it->second->GetName().c_str();
			_objectmodel->AddRow(data);
		}

		std::string actiontype = it->second->GetTypeName();
		if(actiontype == "TeleportAction")
		{
			TeleportAction* ptr = static_cast<TeleportAction*>(it->second.get());
			{
				QVariantList data;
				data << "NewMap" << ptr->GetMapName().c_str();
				_objectmodel->AddRow(data);
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

				QVariantList data;
				data << "Spawning" << spawningname.c_str();
				_objectmodel->AddRow(data);
			}

			_objectcustomdelegate->SetCustomIndex(4, _mapNameList);

			std::map<std::string, boost::shared_ptr<QStringList> >::iterator it = _mapSpawningList.find(ptr->GetMapName());
			if(it != _mapSpawningList.end())
				_objectcustomdelegate->SetCustomIndex(5, it->second);

			return;
		}
	}
}




/***********************************************************
add an spawning name to the name list
***********************************************************/
void EditorHandler::AddSpawningName(const std::string & mapname, const std::string & name)
{
	if(!_mapSpawningList[mapname]->contains(name.c_str()))
		(*_mapSpawningList[mapname]) << name.c_str();
}


/***********************************************************
remove an spawning name to the name list
***********************************************************/
void EditorHandler::RemoveSpawningName(const std::string & mapname, const std::string & name)
{
	// remove from text list
	QStringList::iterator it = std::find(_mapSpawningList[mapname]->begin(), 
											_mapSpawningList[mapname]->end(), name.c_str());
	if(it != _mapSpawningList[mapname]->end())
		_mapSpawningList[mapname]->erase(it);
}


/***********************************************************
replace an spawning name to the name list
***********************************************************/
void EditorHandler::ReplaceSpawningName(const std::string & mapname, const std::string & oldname, 
															const std::string & newname)
{
	QStringList::iterator it = std::find(_mapSpawningList[mapname]->begin(), 
											_mapSpawningList[mapname]->end(), oldname.c_str());
	if(it != _mapSpawningList[mapname]->end())
		*it = newname.c_str();
}


/***********************************************************
called when action object changed
***********************************************************/
void EditorHandler::ActionObjectChanged(long id, const std::string & category)
{
	std::string oldname = _actions[id]->GetName();
	QString name = _objectmodel->GetData(1, 3).toString();

	// check if name changed already exist
	if(name != oldname.c_str())
	{
		if(name == "" || _actionNameList->contains(name))
		{
			QMessageBox::warning(this, tr("Name already used"),
				tr("The name you entered for the action is already used. Please enter a unique name."),
				QMessageBox::Ok);

			_objectmodel->SetData(1, 3, oldname.c_str());
			return;
		}
	}


	if(category == "TeleportAction")
	{
		// get info
		std::string mapname = _objectmodel->GetData(1, 4).toString().toAscii().data();
		std::string spawning = _objectmodel->GetData(1, 5).toString().toAscii().data();


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


		// created modified action and replace old one
		boost::shared_ptr<ActionBase> modifiedact(new TeleportAction(id,
											name.toAscii().data(), mapname, spid));

		ReplaceActionName(oldname, modifiedact->GetName());
		_actions[id] = modifiedact;



		// update action list display
		QStringList slist;
		slist << name << modifiedact->GetTypeName().c_str();
		_actionlistmodel->AddOrUpdateRow(id, slist);


		// need to save as something changed
		SetModified();


		//inform server
		EditorUpdateBasePtr update = new UpdateEditor_AddOrModAction(modifiedact);
		SharedDataHandler::getInstance()->EditorUpdate("", update);

		// refresh spawning list for action
		std::map<std::string, boost::shared_ptr<QStringList> >::iterator it = _mapSpawningList.find(mapname);
		if(it != _mapSpawningList.end())
			_objectcustomdelegate->SetCustomIndex(5, it->second);

		return;
	}
}


/***********************************************************
save global lus file for current world
***********************************************************/
void EditorHandler::SaveGlobalLua(const std::string & filename)
{
	std::ofstream file(filename.c_str());
	file<<"function InitGlobal(environment)"<<std::endl;

	std::map<long, boost::shared_ptr<ActionBase> >::const_iterator it = _actions.begin();
	std::map<long, boost::shared_ptr<ActionBase> >::const_iterator end = _actions.end();
	for(; it != end; ++it)
		it->second->SaveToLuaFile(file);


	file<<"end"<<std::endl;
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
get action id from name
***********************************************************/
long EditorHandler::GetActionId(const std::string & name)
{
	long id = -1;
	if(name != "" && name != "None")
	{
		std::map<long, boost::shared_ptr<ActionBase> >::iterator it = _actions.begin();
		std::map<long, boost::shared_ptr<ActionBase> >::iterator end = _actions.end();
		for(;it != end; ++it)
		{
			if(name == it->second->GetName())
			{
				id = it->first;
				break;
			}
		}
	}

	return id;
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
void EditorHandler::SelectTrigger(long id)
{
	std::map<long, boost::shared_ptr<TriggerBase> >::iterator it = _triggers.find(id);
	if(it != _triggers.end())
	{
		ResetObject();

		{
			QVariantList data;
			data<<"Type"<<"Trigger";
			_objectmodel->AddRow(data);
		}

		{
			QVariantList data;
			data<<"SubCategory"<<it->second->GetTypeName().c_str();
			_objectmodel->AddRow(data);
		}

		{
			QVariantList data;
			data<<"Id"<<id;
			_objectmodel->AddRow(data);
		}

		{
			QVariantList data;
			data<<"Name"<<it->second->GetName().c_str();
			_objectmodel->AddRow(data);
		}

		std::string actiontype = it->second->GetTypeName();
		if(actiontype == "ZoneTrigger")
		{
			ZoneTrigger* ptr = static_cast<ZoneTrigger*>(it->second.get());
			{
				QVariantList data;
				data << "Action On Enter" << GetActionName(ptr->GetAction1()).c_str();
				_objectmodel->AddRow(data);
			}
			{
				QVariantList data;
				data << "Action On Leave" << GetActionName(ptr->GetAction2()).c_str();
				_objectmodel->AddRow(data);
			}

			{
				QVariantList data;
				data << "Trigger on Player" << ptr->CheckPlayer();
				_objectmodel->AddRow(data);
			}

			{
				QVariantList data;
				data << "Trigger on Npc" << ptr->CheckNpcs();
				_objectmodel->AddRow(data);
			}

			{
				QVariantList data;
				data << "Trigger on Movable Objects" << ptr->CheckMovableObjects();
				_objectmodel->AddRow(data);
			}


			{
				QVariantList data;
				data << "Position X" << (double)ptr->GetPosX();
				_objectmodel->AddRow(data);
			}

			{
				QVariantList data;
				data << "Position Y" << (double)ptr->GetPosY();
				_objectmodel->AddRow(data);
			}

			{
				QVariantList data;
				data << "Position Z" << (double)ptr->GetPosZ();
				_objectmodel->AddRow(data);
			}

			{
				QVariantList data;
				data << "Zone size X" << (double)ptr->GetSizeX();
				_objectmodel->AddRow(data);
			}

			{
				QVariantList data;
				data << "Zone size Y" << (double)ptr->GetSizeY();
				_objectmodel->AddRow(data);
			}

			{
				QVariantList data;
				data << "Zone size Z" << (double)ptr->GetSizeZ();
				_objectmodel->AddRow(data);
			}

			{
				QVariantList data;
				data << "Multi Activation" << ptr->MultiActivation();
				_objectmodel->AddRow(data);
			}


			_objectcustomdelegate->SetCustomIndex(4, _actionNameList);
			_objectcustomdelegate->SetCustomIndex(5, _actionNameList);

			return;
		}
	}
}


/***********************************************************
get action name from id
***********************************************************/
std::string  EditorHandler::GetActionName(long id)
{
	std::string name = "None";

	std::map<long, boost::shared_ptr<ActionBase> >::iterator it = _actions.find(id);
	if(it != _actions.end())
		return it->second->GetName();

	return name;
}


/***********************************************************
called when trigger object changed
***********************************************************/
void EditorHandler::TriggerObjectChanged(long id, const std::string & category)
{
	TriggerInfo triggerinfo;
	triggerinfo.id = id;
	triggerinfo.name = _objectmodel->GetData(1, 3).toString().toAscii().data();
	std::string oldname = _triggers[id]->GetName();
	std::string mapname = _uieditor.label_mapname->text().toAscii().data();

	// check if name changed already exist
	if(triggerinfo.name != oldname)
	{
		if(triggerinfo.name == "" || _triggerNameList->contains(triggerinfo.name.c_str()))
		{
			QMessageBox::warning(this, tr("Name already used"),
				tr("The name you entered for the trigger is already used. Please enter a unique name."),
				QMessageBox::Ok);

			_objectmodel->SetData(1, 3, oldname.c_str());
			return;
		}
	}


	if(category == "ZoneTrigger")
	{
		// get info

		std::string action1 = _objectmodel->GetData(1, 4).toString().toAscii().data();
		std::string action2 = _objectmodel->GetData(1, 5).toString().toAscii().data();
		triggerinfo.CheckPlayers = _objectmodel->GetData(1, 6).toBool();
		triggerinfo.CheckNpcs = _objectmodel->GetData(1, 7).toBool();
		triggerinfo.CheckMovableObjects = _objectmodel->GetData(1, 8).toBool();
		float posX = _objectmodel->GetData(1, 9).toFloat();
		float posY = _objectmodel->GetData(1, 10).toFloat();
		float posZ = _objectmodel->GetData(1, 11).toFloat();
		float sizeX = _objectmodel->GetData(1, 12).toFloat();
		float sizeY = _objectmodel->GetData(1, 13).toFloat();
		float sizeZ = _objectmodel->GetData(1, 14).toFloat();
		if(sizeX < 0.0001)
			sizeX = 0.0001;
		if(sizeY < 0.0001)
			sizeY = 0.0001;
		if(sizeZ < 0.0001)
			sizeZ = 0.0001;

		bool multicactiv = _objectmodel->GetData(1, 15).toBool();

		// get id associated to actions
		long act1id = GetActionId(action1);
		long act2id = GetActionId(action2);


		// created modified action and replace old one

		boost::shared_ptr<TriggerBase> modifiedtrig(new ZoneTrigger(triggerinfo, sizeX, sizeY, sizeZ, multicactiv));
		modifiedtrig->SetPosition(posX, posY, posZ);
		modifiedtrig->SetAction1(act1id);
		modifiedtrig->SetAction2(act2id);



		// update trigger name list
		QStringList::iterator it = std::find(_triggerNameList->begin(), _triggerNameList->end(), oldname.c_str());
		if(it != _triggerNameList->end())
			*it = triggerinfo.name.c_str();


		_triggers[id] = modifiedtrig;


		// update trigger list display
		QStringList slist;
		slist << triggerinfo.name.c_str() << modifiedtrig->GetTypeName().c_str();
		_triggerlistmodel->AddOrUpdateRow(id, slist);



		// need to save as something changed
		SetMapModified();


		//inform server
		EditorUpdateBasePtr update = new UpdateEditor_AddOrModTrigger(modifiedtrig);
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