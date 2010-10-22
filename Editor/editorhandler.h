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

#ifndef EDITORHANDLER_H
#define EDITORHANDLER_H

#include <QAbstractTableModel>
#include <QObject>
#include <QStyledItemDelegate>

#include "ui_editor.h"
#include "ui_addtriggerdialog.h"
#include "ui_openworlddialog.h"
#include "ui_addspawning.h"
#include "ui_addaction.h"
#include "ui_addmapdialog.h"
#include "ui_addteleportdialog.h"
#include "ui_addworlddialog.h"
#include "ui_addactordialog.h"

#include "GraphicsWindowQt"
#include "ScriptEnvironmentBase.h"
#include "Lba1ModelMapHandler.h"

#include <LbaTypes.h>
#include <boost/shared_ptr.hpp>

class QTableWidgetItem;
class ServerLuaHandler;
class ActorHandler;


//! used as model for table
class StringTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	//! constructor
	StringTableModel(const QStringList &header, QObject *parent = 0)
	 : QAbstractTableModel(parent), _stringMatrix(header.size()),
		_header(header)
	{}

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation,
					 int role = Qt::DisplayRole) const;

     Qt::ItemFlags flags(const QModelIndex &index) const;
     bool setData(const QModelIndex &index, const QVariant &value,
                  int role = Qt::EditRole);


     bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
     bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

	//! clear the table content
	void Clear();

	//! add a row
	void AddOrUpdateRow(long id, const QStringList &data);

	//! get a string
	QString GetString(const QModelIndex &index);

	//! get the corresponding id
	long GetId(const QModelIndex &index);

	//! get next free id
	long GetNextId();

private:
	std::vector<QStringList>		_stringMatrix;
	std::vector<long>				_ids;
	QStringList						_header;
};





//! used as model for table
class MixedTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	//! constructor
	MixedTableModel(const QStringList &header, QObject *parent = 0)
	 : QAbstractTableModel(parent), _objMatrix(header.size()), _header(header)
	{}

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation,
					 int role = Qt::DisplayRole) const;

     Qt::ItemFlags flags(const QModelIndex &index) const;
     bool setData(const QModelIndex &index, const QVariant &value,
                  int role = Qt::EditRole);


     bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
     bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

	//! clear the table content
	void Clear();

	//! add a row
	void AddRow(const QVariantList &data);

	//! get a string
	QVariant GetData(const QModelIndex &index);

	//! get a string
	QVariant GetData(int col, int row);

	//! set a string
	void SetData(int col, int row, QVariant v);


private:
	std::vector<QVariantList>			_objMatrix;
	QStringList							_header;
};





 class CustomDelegate : public QStyledItemDelegate
 {
     Q_OBJECT

 public:
     CustomDelegate(QObject *parent, QAbstractItemModel * model);

     QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;

     void setEditorData(QWidget *editor, const QModelIndex &index) const;
     void setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const;

     void updateEditorGeometry(QWidget *editor,
         const QStyleOptionViewItem &option, const QModelIndex &index) const;

	 void Clear();

	 void SetCustomIndex(int index, boost::shared_ptr<QStringList> list);

public slots:
		 
	//! data changed in object view
	void objmodified(int flag);

	//! data changed in object view
	void objmodified2(double flag);


 private:
	 std::map<int, boost::shared_ptr<QStringList> >		_customs;
	 QAbstractItemModel *								_model;
 };








//! take care of editor
class EditorHandler : public QMainWindow, public ScriptEnvironmentBase
{
	Q_OBJECT

public:
	//! constructor
	EditorHandler(QWidget *parent = 0, Qt::WindowFlags flags = 0);

	//! constructor
	~EditorHandler();

	//! set the osg window
	void SetOsgWindow(GraphicsWindowQt *osgwindow);

	//! refresh display
	void RefreshDisplay();

	//! refresh gui with map info
	void SetMapInfo(const std::string & mapname);

	//! player moved
	void PlayerMoved(float posx, float posy, float posz);


	// function used by LUA to add actor
	virtual void AddActorObject(boost::shared_ptr<ActorHandler> actor);
					
	// add a trigger of moving type to the map
	virtual void AddTrigger(boost::shared_ptr<TriggerBase> trigger);
					
	// add an action
	virtual void AddAction(boost::shared_ptr<ActionBase> action);

	// teleport an object
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Teleport(int ObjectType, long ObjectId,
						const std::string &NewMapName, 
						long SpawningId,
						float offsetX, float offsetY, float offsetZ);

	// get the action correspondant to the id
	virtual boost::shared_ptr<ActionBase> GetAction(long actionid);


public slots:
	 //! ui button clicked
     void addtrigger_button_clicked();

	 //! ui button clicked
     void removetrigger_button_clicked();

	 //! ui button clicked
     void selecttrigger_button_clicked();


	 //! dialog accepted
     void addtrigger_accepted();


	 //! quit editor
     void quit();

	 //! on new world action
     void NewWorldAction();

	 //! on open world action
     void OpenWorldAction();

	 //! on save world action
     void SaveWorldAction();

	 //! on open world
     void OpenWorld();

	 //! on go tp clicked
     void goto_tp_button_clicked();

	 //! on go map clicked
     void goto_map_button_clicked();

	 //! on go tp clicked
     void goto_tp_double_clicked(const QModelIndex & itm);

	 //! on go map clicked
     void goto_map_double_clicked(const QModelIndex & itm);

	//! on addspawning clicked
	void addspawning_button_clicked();

	//! on removespawning clicked
	void removespawning_button_clicked();

	//! on selectspawning clicked
	void selectspawning_button_clicked();

	 //! on selectspawning clicked
     void selectspawning_double_clicked(const QModelIndex & itm);

	//! on AddSpawning clicked
	void AddSpawning_clicked();

	//! when go button clicked on info part
	void info_go_clicked();

	//! camera type toggled in info
	void info_camera_toggled(bool checked);

	//! data changed in object view
	void objectdatachanged(const QModelIndex &index1, const QModelIndex &index2);

	//! addAction_button_clicked
	void addAction_button_clicked();
	void addAction1_button_clicked();
	void addAction2_button_clicked();
	void addAction3_button_clicked();

	//! removeAction_button_clicked
	void removeAction_button_clicked();

	//! selectAction_button_clicked
	void selectAction_button_clicked();

	//! add action accepted
	void AddActionAccepted();

	 //! on selectaction_double_clicked
     void selectaction_double_clicked(const QModelIndex & itm);

	 //! on selecttrigger_double_clicked
     void selecttrigger_double_clicked(const QModelIndex & itm);

	 //! world description changed
	 void WorldDescriptionChanged();

	 //! worlds news changed
	 void WorldNewsChanged();


	 //! starting map modified
	 void StartingMapModified(int index);

	 //! starting spawn modified
	 void StartingSpawnModified(int index);

	 //! starting life modified
	 void StartingLifeModified(int value);

	 //! starting Outfit modified
	 void StartingOutfitModified(int index);

	 //! starting Weapon modified
	 void StartingWeaponModified(int index);

	 //! starting Mode modified
	 void StartingModeModified(int index);


	 //! ui button clicked
     void addmap_button_clicked();

	 //! ui button clicked
     void removemap_button_clicked();

	 //! dialog accepted
     void addmap_accepted();

	 //! map description changed
	 void MapDescriptionChanged();

	 //! map type changed
	 void MapTypeChanged(int flag);

	 //! map instance changed
	 void MapInstanceChanged(int flag);

	 //! map cam type changed
	 void MapCameraTypeChanged(bool flag);


	//! tp add button push
	 void TpAdd_button();

	//! tp remove button push
	 void TpRemove_button();

	//! tp edit button push
	 void TpEdit_button();

	//! tp add button push
	 void TpAdd_button_accepted();

	//! map changed in tp dialog
	void TpDialogMapChanged(int flag);

	//! add world accepted
	void addworld_accepted();


	//! Actor add button push
	 void ActorAdd_button();

	//! Actor remove button push
	 void ActorRemove_button();

	//! Actor edit button push
	 void ActorSelect_button();

	//! Actor add button push
	 void ActorAdd_button_accepted();

	 //! on selectactor_double_clicked
     void selectactor_double_clicked(const QModelIndex & itm);

protected:
	//! override close event
	virtual void closeEvent(QCloseEvent* event);

	//! Check if we need to save before quit
	bool SaveBeforeQuit();

	//! return true if some changes are not saved
	bool Modified();

	//! set the work as modified
	void SetModified();

	//! set the work as saved
	void SetSaved();

	//! set the work as modified
	void SetMapModified();

	//! Check if we need to save before quit map
	bool SaveMapBeforeQuit(bool alreadychangedmap = false);

	//! refresh gui with world info
	void SetWorldInfo(const std::string & worldname);


	//! reset world display in editor
	void ResetWorld();

	//! reset map display in editor
	void ResetMap();

	//! reset object display in editor
	void ResetObject();


	//! add a spawning to the map
	long AddOrModSpawning(const std::string &mapname,
							const std::string &spawningname,
							float PosX, float PosY, float PosZ,
							float Rotation, bool forcedrotation,
							long modifyid = -1);

	//! remove a spawning from the map
	void RemoveSpawning(const std::string &mapname, long spawningid);


	//! set spawning in the object
	void SelectSpawning(long id, const std::string &spawningname,
							float PosX, float PosY, float PosZ,
							float Rotation, bool forcedrotation);


	//! clear the object displayed if it is the selected one
	void ClearObjectIfSelected(const std::string objecttype, long id);


	//! called when spawning object changed
	void SpawningObjectChanged(long id);


	//! check if a world is opened
	bool IsWorldOpened();

	//! check if a map is opened
	bool IsMapOpened();


	//! add an new action to the list
	void AddNewAction(boost::shared_ptr<ActionBase> action);

	//! remove an action from the list
	void RemoveAction(long id);

	//! add an action name to the name list
	void AddActionName(const std::string & name);

	//! remove an action name to the name list
	void RemoveActionName(const std::string & name);

	//! replace an action name to the name list
	void ReplaceActionName(const std::string & oldname, const std::string & newname);

	//! select an action and display it in object view
	void SelectAction(long id);

	//! add an spawning name to the name list
	void AddSpawningName(const std::string & mapname, const std::string & name);

	//! remove an spawning name to the name list
	void RemoveSpawningName(const std::string & mapname, const std::string & name);

	//! replace an spawning name to the name list
	void ReplaceSpawningName(const std::string & mapname, const std::string & oldname, 
																const std::string & newname);

	//! called when action object changed
	void ActionObjectChanged(long id, const std::string & category);

	//! save global lus file for current world
	void SaveGlobalLua(const std::string & filename);


	//! add an new trigger to the list
	void AddNewTrigger(boost::shared_ptr<TriggerBase> trigger);

	//! get action id from name
	long GetActionId(const std::string & name);

	//! remove trigger
	void RemoveTrigger(long id);

	//! select trigger
	void SelectTrigger(long id);

	//! get action name from id
	std::string GetActionName(long id);

	//! called when trigger object changed
	void TriggerObjectChanged(long id, const std::string & category);

	//! change current map to new map
	void ChangeMap(const std::string & mapname, long spawningid);

	//! save current map to file
	void SaveMap(const std::string & filename);

	// refresh starting info tab
	void RefreshStartingInfo();

	// refresh starting map
	void RefreshStartingMap();

	// refresh starting spawning
	void RefreshStartingSpawning();

	// refresh starting outfit
	void RefreshStartingModelOutfit();

	// refresh starting weapon
	void RefreshStartingModelWeapon();

	// refresh starting mode
	void RefreshStartingModelMode();

	// tp to default spawning of map
	void CreateDefaultSpawningAndTp(const std::string & mapname);

	// update tp list with new span name
	void UpdateTpSpanName(const std::string & mapname, long spwid, const std::string &  spname);

	// remove actor
	void RemoveActor(long id);

	// select actor
	void SelectActor(long id);

	// called when actor object changed
	void ActorObjectChanged(long id);

	//! update editor selected ector display
	void UpdateSelectedActorDisplay(LbaNet::ObjectPhysicDesc desc);

	//! remove current selected display
	void RemoveSelectedActorDislay();


private:
	Ui::EditorClass										_uieditor;

	Ui::AddTriggerDialog								_uiaddtriggerdialog;
	QDialog *											_addtriggerdialog;

	Ui::DialogOpenWorld									_uiopenworlddialog;
	QDialog *											_openworlddialog;

	Ui::DialogNewSpawning								_uiaddspawningdialog;
	QDialog *											_addspawningdialog;

	Ui::DialogAddaction									_ui_addactiondialog;
	QDialog *											_addactiondialog;

	Ui::DialogAddMap									_ui_addmapdialog;
	QDialog *											_addmapdialog;

	Ui::DialogAddTeleport								_ui_addtpdialog;
	QDialog *											_addtpdialog;

	Ui::Dialog_NewWorld									_ui_addworlddialog;
	QDialog *											_addworlddialog;

	Ui::DialogAddActor									_ui_addactordialog;
	QDialog *											_addactordialog;

	StringTableModel *									_maplistmodel;
	StringTableModel *									_tplistmodel;
	StringTableModel *									_mapspawninglistmodel;
	StringTableModel *									_actionlistmodel;
	StringTableModel *									_triggerlistmodel;
	StringTableModel *									_actorlistmodel;


	MixedTableModel *									_objectmodel;
	CustomDelegate *									_objectcustomdelegate;

	boost::shared_ptr<QStringList>						_actionNameList;
	boost::shared_ptr<QStringList>						_mapNameList;
	boost::shared_ptr<QStringList>						_triggerNameList;
	std::map<std::string, boost::shared_ptr<QStringList> >	_mapSpawningList;
	boost::shared_ptr<QStringList>						_actortypeList;
	boost::shared_ptr<QStringList>						_actordtypeList;
	boost::shared_ptr<QStringList>						_actorptypeList;

	GraphicsWindowQt *									_osgwindow;


	bool												_modified;
	bool												_mapmodified;
	LbaNet::WorldInformation							_winfo;


	boost::shared_ptr<ServerLuaHandler>					_luaH;

	std::map<long, boost::shared_ptr<TriggerBase> >		_triggers;
	std::map<long, boost::shared_ptr<ActionBase> >		_actions;
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >	_Actors;

	long												_currspawningidx;
	long												_curractionidx;
	long												_currtriggeridx;
	long												_currteleportidx;
	long												_curractoridx;

	int													_updatetriggerdialogonnewaction;

	float												_posX;
	float												_posY;
	float												_posZ;

	long												_edited_tp;


	std::map<std::string, ModelData>					_lba1Mdata;


	osg::ref_ptr<osg::MatrixTransform>					_actornode;
};

#endif // EDITORHANDLER_H
