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

#ifndef _NPC_HANDLER_H__
#define _NPC_HANDLER_H__

#include "ActorHandler.h"
#include "DialogPart.h"


/***********************************************************************
class taking care of the maping between lua and the server interfaces
 ***********************************************************************/
class NPCHandler : public ActorHandler
{
public:
	


public:
	//! constructor
	NPCHandler(const ActorObjectInfo & actorinfo);
	
	//! destructor
	virtual ~NPCHandler(void){}

	//! return actor type
	virtual std::string ActorType()
	{ return "Npc";}

	//! get root dialog
	DialogPartPtr GetRootDialog()
	{return _rootdialog;}

	//! set root dialog
	void SetRootDialog(DialogPartPtr root)
	{_rootdialog = root;}


protected:

	//! return the build class
	virtual std::string LuaBuildClass();

	//! write extra lua
	virtual void ExtraLua(std::ofstream & file, const std::string & name);

private:
	DialogPartPtr		_rootdialog;
};

#endif
