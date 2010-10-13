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

/***********************************************************
Constructor
***********************************************************/
EditorHandler::EditorHandler(QObject *parent, GraphicsWindowQt *osgwindow)
	: QObject(parent), _osgwindow(osgwindow)
{
	_editorwindow = new QMainWindow();
	_uieditor.setupUi(_editorwindow);

	_addtriggerdialog = new QDialog();
	_uiaddtriggerdialog.setupUi(_addtriggerdialog);

	_osgwindow->getGraphWidget()->setParent(_uieditor.groupBox_game);
	_osgwindow->getGraphWidget()->show();

	_editorwindow->show();


	// connect signals and slots
	connect(_uieditor.pushButton_addTrigger, SIGNAL(clicked()) , this, SLOT(addtrigger_button_clicked()));
	connect(_uiaddtriggerdialog.buttonBox, SIGNAL(accepted()) , this, SLOT(addtrigger_accepted()));
}

/***********************************************************
Destructor
***********************************************************/
EditorHandler::~EditorHandler()
{
	delete _editorwindow;
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

}