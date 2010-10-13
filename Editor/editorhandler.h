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
#include "ui_editor.h"
#include "ui_addtriggerdialog.h"
#include "ui_openworlddialog.h"
#include "GraphicsWindowQt"

#include <LbaTypes.h>


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
	void AddRow(long id, const QStringList &data);

	//! get a string
	QString GetString(const QModelIndex &index);

private:
	std::vector<QStringList>		_stringMatrix;
	std::vector<long>				_ids;
	QStringList						_header;
};



//! take care of editor
class EditorHandler : public QMainWindow
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


public slots:
	 //! ui button clicked
     void addtrigger_button_clicked();

	 //! dialog accepted
     void addtrigger_accepted();

	 //! dialog cancelled
     void addtrigger_cancelled();

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

	//! called when map selected in the list
	void map_selected(const QModelIndex & idx1, const QModelIndex & idx2);


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

	//! refresh gui with world info
	void SetWorldInfo(const std::string & worldname);

	//! refresh gui with map info
	void SetMapInfo(const std::string & mapname);

	//! reset world display in editor
	void ResetWorld();

	//! reset map display in editor
	void ResetMap();

	//! reset object display in editor
	void ResetObject();



private:
	Ui::EditorClass			_uieditor;

	Ui::AddTriggerDialog	_uiaddtriggerdialog;
	QDialog *				_addtriggerdialog;

	Ui::DialogOpenWorld		_uiopenworlddialog;
	QDialog *				_openworlddialog;


	StringTableModel *		_maplistmodel;
	StringTableModel *		_tplistmodel;

	GraphicsWindowQt *		_osgwindow;


	bool					_modified;
	LbaNet::WorldInformation _winfo;
};

#endif // EDITORHANDLER_H
