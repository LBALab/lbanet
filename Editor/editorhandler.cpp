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

#include <QMessageBox>


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
	if(_stringMatrix.size() > 0)
	{
		beginRemoveRows(QModelIndex(), 0, _stringMatrix.size());

		for(size_t i=0; i<_stringMatrix.size(); ++i)
			_stringMatrix[i].clear();

		endRemoveRows();
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
Constructor
***********************************************************/
EditorHandler::EditorHandler(QWidget *parent, Qt::WindowFlags flags)
 : QMainWindow(parent, flags), _modified(false)
{
	_uieditor.setupUi(this);

	_addtriggerdialog = new QDialog(this);
	_uiaddtriggerdialog.setupUi(_addtriggerdialog);

	_openworlddialog = new QDialog(this);
	_uiopenworlddialog.setupUi(_openworlddialog);

	_addspawningdialog = new QDialog(this);
	_uiaddspawningdialog.setupUi(_addspawningdialog);


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
		 header << "Name" << "Map" << "SpawningId";
		_tplistmodel = new StringTableModel(header);
		_uieditor.tableView_TeleportList->setModel(_tplistmodel);
		QHeaderView * mpheaders = _uieditor.tableView_TeleportList->horizontalHeader();
		mpheaders->setResizeMode(QHeaderView::Stretch);
	}

	// set model for spawninglist
	{
		 QStringList header;
		 header << "Name" << "X" << "Y" << "Z" << "Rot" << "F";
		_mapspawninglistmodel = new StringTableModel(header);
		_uieditor.tableView_SpawningList->setModel(_mapspawninglistmodel);
		QHeaderView * mpheaders = _uieditor.tableView_SpawningList->horizontalHeader();
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
	connect(_uieditor.pushButton_addTrigger, SIGNAL(clicked()) , this, SLOT(addtrigger_button_clicked()));
	//connect(_uieditor.tableView_MapList->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), 
	//				this, SLOT(map_selected(QModelIndex,QModelIndex)));
	
	connect(_uieditor.pushButton_addSpwaning, SIGNAL(clicked()) , this, SLOT(addspawning_button_clicked()));
	connect(_uieditor.pushButton_removeSpwaning, SIGNAL(clicked()) , this, SLOT(removespawning_button_clicked()));	
	connect(_uieditor.pushButton_selectSpwaning, SIGNAL(clicked()) , this, SLOT(selectspawning_button_clicked()));		


	connect(_uieditor.pushButton_goto_tp, SIGNAL(clicked()) , this, SLOT(goto_tp_button_clicked()));
	connect(_uieditor.pushButton_goto_map, SIGNAL(clicked()) , this, SLOT(goto_map_button_clicked()));

	connect(_uieditor.pushButton_goto_tp, SIGNAL(itemDoubleClicked(QTableWidgetItem)) , this, SLOT(goto_tp_button_clicked()));
	connect(_uieditor.pushButton_goto_map, SIGNAL(itemDoubleClicked(QTableWidgetItem)) , this, SLOT(goto_map_button_clicked()));


	connect(_uiaddtriggerdialog.buttonBox, SIGNAL(accepted()) , this, SLOT(addtrigger_accepted()));
	connect(_uiaddtriggerdialog.buttonBox, SIGNAL(cancelled()) , this, SLOT(addtrigger_cancelled()));

	connect(_uiopenworlddialog.buttonBox, SIGNAL(accepted()) , this, SLOT(OpenWorld()));

	connect(_uiaddspawningdialog.buttonBox, SIGNAL(accepted()) , this, SLOT(AddSpawning_clicked()));




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
	_addtriggerdialog->show();
}



/***********************************************************
dialog accepted
***********************************************************/
void EditorHandler::addtrigger_accepted()
{
	_addtriggerdialog->hide();
}




/***********************************************************
dialog cancelled
***********************************************************/
void EditorHandler::addtrigger_cancelled()
{
	_addtriggerdialog->hide();
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
	_uieditor.groupBox_game->setMinimumWidth(600);
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
	//TODO - ResetWorld
}


/***********************************************************
OpenWorldAction
***********************************************************/
void EditorHandler::OpenWorldAction()
{
	std::vector<LbaNet::WorldDesc> list;
	DataLoader::getInstance()->GetAvailableWorlds(list);

	_uiopenworlddialog.comboBoxWorldToOpen->clear();

	for(size_t i=0; i<list.size(); ++i)
		_uiopenworlddialog.comboBoxWorldToOpen->addItem(list[i].WorldName.c_str());

	_openworlddialog->show();
}


/***********************************************************
SaveWorldAction
***********************************************************/
void EditorHandler::SaveWorldAction()
{
	SetSaved();
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
	_modified = true;
}

/***********************************************************
set the work as saved
***********************************************************/
void EditorHandler::SetSaved()
{
	_modified = false;
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
		}
	}

	// add teleport
	{
		_tplistmodel->Clear();
		LbaNet::ServerTeleportsSeq::const_iterator ittp = _winfo.TeleportInfo.begin();
		LbaNet::ServerTeleportsSeq::const_iterator endtp = _winfo.TeleportInfo.end();
		for(long cc=1; ittp != endtp; ++ittp, ++cc)
		{
			QString spid;
			spid.setNum (ittp->second.SpawningId);	

			QStringList data;
			data << ittp->first.c_str() << ittp->second.MapName.c_str() << spid;
			_tplistmodel->AddOrUpdateRow(cc, data);
		}
	}
}




/***********************************************************
reset world display in editor
***********************************************************/
void EditorHandler::ResetWorld()
{
	_maplistmodel->Clear();
	_tplistmodel->Clear();

	_uieditor.label_worldname->setText("");
	_uieditor.textEdit_worlddescription->setText("");
	_uieditor.textEdit_worldnews->setText("");

	ResetMap();
}


/***********************************************************
reset map display in editor
***********************************************************/
void EditorHandler::ResetMap()
{
	_currspawningidx = 0;

	ResetObject();
}


/***********************************************************
reset object display in editor
***********************************************************/
void EditorHandler::ResetObject()
{

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
		long spawningid = _tplistmodel->GetString(indexes[2]).toLong();
		
		SharedDataHandler::getInstance()->ChangeMapPlayer(1, mapname, spawningid);
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
			SharedDataHandler::getInstance()->ChangeMapPlayer(1, mapname, 
												mapinfo.Spawnings.begin()->first);
		}
		else
		{
			// add a default spawning
			long spid = AddOrModSpawning(mapname, "DefaultSpawning", 0, 0, 0, 0, true);
			SharedDataHandler::getInstance()->ChangeMapPlayer(1, mapname, spid);
		}
	}
}



/***********************************************************
refresh gui with map info
***********************************************************/
void EditorHandler::SetMapInfo(const std::string & mapname)
{
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
			QString Rots;
			Rots.setNum (ittp->second.Rotation, 'f');


			QStringList data;
			data << ittp->second.Name.c_str() << Xs << Ys << Zs << Rots << (ittp->second.ForceRotation ? "Y" : "N");
			_mapspawninglistmodel->AddOrUpdateRow(ittp->first, data);

			_currspawningidx = (ittp->first + 1);
		}
	}
}





/***********************************************************
on addspawning clicked
***********************************************************/
void EditorHandler::addspawning_button_clicked()
{
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
void EditorHandler::selectspawning_button_clicked()
{

}


/***********************************************************
on AddSpawning clicked
***********************************************************/
void EditorHandler::AddSpawning_clicked()
{
	_addspawningdialog->hide();

	AddOrModSpawning(_uieditor.label_mapname->text().toAscii().data(),
				_uiaddspawningdialog.lineEdit_name->text().toAscii().data(),
				(float)_uiaddspawningdialog.doubleSpinBox_posx->value(), 
				(float)_uiaddspawningdialog.doubleSpinBox_posy->value(), 
				(float)_uiaddspawningdialog.doubleSpinBox_posz->value(),
				(float)_uiaddspawningdialog.doubleSpinBox_rotation->value(), 
				_uiaddspawningdialog.checkBox_forcerotation->isChecked());

}


/***********************************************************
add a spawning to the map
***********************************************************/
long EditorHandler::AddOrModSpawning(const std::string &mapname,
										const std::string &spawningname,
										float PosX, float PosY, float PosZ,
										float Rotation, bool forcedrotation)
{
	// first update the internal info
	LbaNet::SpawningInfo spawn;
	spawn.Id = _currspawningidx++;
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
		QString Rots;
		Rots.setNum(Rotation, 'f');

		QStringList data;
		data << spawningname.c_str() << Xs << Ys << Zs << Rots << (forcedrotation ? "Y" : "N");
		_mapspawninglistmodel->AddOrUpdateRow(spawn.Id, data);
	}


	// then inform the server
	boost::shared_ptr<EditorUpdateBase> update(new UpdateEditor_AddOrModSpawning(spawn.Id,
																					spawningname,
																					PosX, PosY, PosZ,
																					Rotation, forcedrotation));

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
		// erase from data
		_winfo.Maps[mapname].Spawnings.erase(it);

		// then inform the server
		boost::shared_ptr<EditorUpdateBase> update(new UpdateEditor_RemoveSpawning(spawningid));
		SharedDataHandler::getInstance()->EditorUpdate(mapname, update);
	}
}