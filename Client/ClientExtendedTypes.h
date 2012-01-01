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


#if !defined(__LbaNetModel_ClientExtendedTypes_h)
#define __LbaNetModel_ClientExtendedTypes_h

#include <LbaTypes.h>

struct AnimationFrameData;


/*
************************************************************************************************************************
*                                                  class AddWhisperChanelUpdate
*
*	class used when chatbox need to add a whisper channel
************************************************************************************************************************
*/
class AddWhisperChanelUpdate : public LbaNet::GuiUpdateBase
{
public:
	//! constructor
	AddWhisperChanelUpdate(const std::string &Name)
		: _Name(Name)
	{
	}

	std::string _Name;
};


/*
************************************************************************************************************************
*                                                  class RefreshSoundButtonUpdate
*
*	class used to refresh gui sound button
************************************************************************************************************************
*/
class RefreshSoundButtonUpdate : public LbaNet::GuiUpdateBase
{
public:
	//! constructor
	RefreshSoundButtonUpdate()
	{
	}

};


/*
************************************************************************************************************************
*                                                  class SetPlayerNameUpdate
*
*	class used when engine want to set player name in the gui
************************************************************************************************************************
*/
class SetPlayerNameUpdate : public LbaNet::GuiUpdateBase
{
public:
	//! constructor
	SetPlayerNameUpdate(const std::string &Name)
		: _Name(Name)
	{
	}

	std::string _Name;
};


/*
************************************************************************************************************************
*                                                  class UsedShorcutUpdate
*
*	class used when player used a key shortcut
************************************************************************************************************************
*/
class UsedShorcutUpdate : public LbaNet::GuiUpdateBase
{
public:
	//! constructor
	UsedShorcutUpdate(int shortcutid)
		: _shortcutid(shortcutid)
	{
	}

	int _shortcutid;
};



/*
************************************************************************************************************************
*                                                  class ChatWorldNameUpdate
*
*	inform chat when world name has changed
************************************************************************************************************************
*/
class ChatWorldNameUpdate : public LbaNet::GuiUpdateBase
{
public:
	//! constructor
	ChatWorldNameUpdate(const std::string &name)
		: _name(name)
	{
	}

	std::string _name;
};



/*
************************************************************************************************************************
*                                                  class ChatMapNameUpdate
*
*	inform chat when map name has changed
************************************************************************************************************************
*/
class ChatMapNameUpdate : public LbaNet::GuiUpdateBase
{
public:
	//! constructor
	ChatMapNameUpdate(const std::string &name)
		: _name(name)
	{
	}

	std::string _name;
};


/*
************************************************************************************************************************
*                                                  class RefreshCharPortraitUpdate
*
*	inform gui that char portrait changed
************************************************************************************************************************
*/
class RefreshCharPortraitUpdate : public LbaNet::GuiUpdateBase
{
public:
	//! constructor
	RefreshCharPortraitUpdate()
	{
	}
};


/*
************************************************************************************************************************
*                                                  class AnimationObserverBase
*
*	register an observer for object animation
************************************************************************************************************************
*/
class AnimationObserverBase
{
public:
	//! constructor
	AnimationObserverBase()
	{
	}

	//! destructor
	virtual ~AnimationObserverBase()
	{
	}

	//! update the number of keyframe in the anim
	virtual void UpdateNumberKeyframe(int nb) = 0;

	//! update the current keyframe
	virtual void UpdateCurrentKeyframe(int keyframe) = 0;
};



/*
************************************************************************************************************************
*                                                  class RegisterAnimationObserver
*
*	register an observer for object animation
************************************************************************************************************************
*/
class RegisterAnimationObserver : public LbaNet::DisplayObjectUpdateBase
{
public:
	//! constructor
	RegisterAnimationObserver(AnimationObserverBase * observer)
		: _observer(observer)
	{
	}

	AnimationObserverBase * _observer;
};


/*
************************************************************************************************************************
*                                                  class SetAnimationKeyframe
*
*	set animation current keyframe
************************************************************************************************************************
*/
class SetAnimationKeyframe : public LbaNet::DisplayObjectUpdateBase
{
public:
	//! constructor
	SetAnimationKeyframe(int keyframe)
		: _keyframe(keyframe)
	{
	}

	int		_keyframe;
};


/*
************************************************************************************************************************
*                                                  class UpdateAnimationKeyframeInfo
*
*	set animation keyframe info
************************************************************************************************************************
*/
class UpdateAnimationKeyframeInfo : public LbaNet::DisplayObjectUpdateBase
{
public:
	//! constructor
	UpdateAnimationKeyframeInfo(int frameid, AnimationFrameData * afd)
		: _frameid(frameid), _afd(afd)
	{
	}

	int						_frameid; 
	AnimationFrameData *	_afd;
};
#endif