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



//! get a string
QString StringTableModel::GetString(const QModelIndex &index)
{
	if (index.isValid()) 
		return _stringMatrix[index.column()][index.row()];

	return QString();
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
void StringTableModel::AddRow(long id, const QStringList &data)
{
	if(_stringMatrix.size() == data.size())
	{
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
	


	connect(_uieditor.pushButton_goto_tp, SIGNAL(clicked()) , this, SLOT(goto_tp_button_clicked()));
	connect(_uieditor.pushButton_goto_map, SIGNAL(clicked()) , this, SLOT(goto_map_button_clicked()));



	connect(_uiaddtriggerdialog.buttonBox, SIGNAL(accepted()) , this, SLOT(addtrigger_accepted()));
	connect(_uiaddtriggerdialog.buttonBox, SIGNAL(cancelled()) , this, SLOT(addtrigger_cancelled()));

	connect(_uiopenworlddialog.buttonBox, SIGNAL(accepted()) , this, SLOT(OpenWorld()));




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
			_maplistmodel->AddRow(cc, data);
		}
	}

	// add teleport
	{
		_tplistmodel->Clear();
		LbaNet::ServerTeleportsSeq::const_iterator ittp = _winfo.TeleportInfo.begin();
		LbaNet::ServerTeleportsSeq::const_iterator endtp = _winfo.TeleportInfo.end();
		for(long cc=1; ittp != endtp; ++ittp, ++cc)
		{
			QStringList data;
			data << ittp->first.c_str() << ittp->second.MapName.c_str() << ittp->second.SpawningName.c_str();
			_tplistmodel->AddRow(cc, data);
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
		std::string spawning = _tplistmodel->GetString(indexes[2]).toAscii().data();
		
		SharedDataHandler::getInstance()->ChangeMapPlayer(1, mapname, spawning);
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
			// TODO - replace by adding a default spawning
			QMessageBox::warning(this, tr("No Spawning"),
			tr("You need at least one spawning in the map to be able to go there."),
			QMessageBox::Ok);
		}
	}
}



/***********************************************************
refresh gui with map info
***********************************************************/
void EditorHandler::SetMapInfo(const std::string & mapname)
{
	ResetMap();
}


/***********************************************************
called when map selected in the list
***********************************************************/
void EditorHandler::map_selected(const QModelIndex & idx1, const QModelIndex & idx2)
{
	//QItemSelectionModel *selectionModel = _uieditor.tableView_MapList->selectionModel();
	//QModelIndexList indexes = selectionModel->selectedIndexes();

	//if(indexes.size() > 0)
	//{
	//	std::string mapname = _maplistmodel->GetString(indexes[0]).toAscii().data();
	//	SetMapInfo(mapname);
	//}
}