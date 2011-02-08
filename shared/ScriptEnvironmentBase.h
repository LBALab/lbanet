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


#ifndef _LBANET_SCRIPT_ENV_BASE_H_
#define _LBANET_SCRIPT_ENV_BASE_H_


class ActorHandler;
class TriggerBase;
class ActionBase;
class ClientScriptBase;
class ActionArgumentBase;
class ContainerSharedInfo;

#include <boost/shared_ptr.hpp>


//*************************************************************************************************
//*                               class ScriptEnvironmentBase
//*************************************************************************************************
/**
* @brief Base class for lua script environment
*
*/
class ScriptEnvironmentBase
{
public:

	//! constructor
	ScriptEnvironmentBase(){}


	//! destructor
	virtual ~ScriptEnvironmentBase(){}


	// function used by LUA to add actor
	virtual void AddActorObject(boost::shared_ptr<ActorHandler> actor) = 0;

	// add a trigger 
	virtual void AddTrigger(boost::shared_ptr<TriggerBase> trigger) = 0;


	// teleport an object
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Teleport(int ObjectType, long ObjectId,
							const std::string &NewMapName, 
							long SpawningId,
							float offsetX, float offsetY, float offsetZ) = 0;


	// execute client script - does not work on npc objects
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ExecuteClientScript(int ObjectType, long ObjectId,
										const std::string & ScriptName,
										bool InlineFunction) = 0;


	// execute custom lua function
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ExecuteCustomAction(int ObjectType, long ObjectId,
										const std::string & FunctionName,
										ActionArgumentBase * args) = 0;


	// display text to client window
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void DisplayTxtAction(int ObjectType, long ObjectId,
										long TextId) = 0;



	// send error message to client
	virtual void SendErrorMessage(long clientid, const std::string & messagetitle, 
											const std::string &  messagecontent) = 0;

	// open container on client side
	virtual void OpenContainer(long clientid, boost::shared_ptr<ContainerSharedInfo> sharedinfo) = 0;
};


#endif
