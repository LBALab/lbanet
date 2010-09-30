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


#ifndef _LBA_NET_CHARACTER_STATES_
#define _LBA_NET_CHARACTER_STATES_

#include <LbaTypes.h>



//*************************************************************************************************
//*                               class CharacterStateBase
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class CharacterStateBase
{
public:
	//! constructor
	CharacterStateBase(void){}

	//! destructor
	virtual ~CharacterStateBase(void){}

	//! ask if we are allowed to move in this mode
	virtual bool AllowedMoving(){return false;}

	//! ask if we are allowed to rotate in this mode
	virtual bool AllowedRotating(){return false;}

	//! tell state that current animation has finished
	//! return true if animation should be paused
	virtual bool AnimationFinished(){return false;}

	//! tell if we should play stand anim when iddle on this mode
	virtual bool StandOnIddle(){return false;}
	

	//! tell state that player is moving
	virtual void InformMoving(){}


	//! check if in this state we can play hurt animation
	virtual bool CanPlayHurt(){return true;}

	//! check if in this state we are immune to hurt
	virtual bool IsImmuneHurt(){return false;}

	//! check if in this state we are immune to gravity
	virtual bool IsImmuneGravity(){return false;}

	//! check if in this state we are immune to drowning
	virtual bool IsImmuneDrowning(){return false;}

	//! check if should change to another state
	virtual bool ShouldChangeState(LbaNet::ModelState & newstate){return false;}

	//! ask if char is hidden on screen
	virtual bool IsHidden(){return false;}

	//! ask if we can should make the character blinking on screen
	virtual bool ShouldBlinkOnScreen(){return false;}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring){return false;}

	//! check if we can change mode from this state
	virtual bool AllowChangeMode(){return false;}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return false;}
	

};



//*************************************************************************************************
//*                               class CharacterStateAllowMoving
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StNormal : public CharacterStateBase
{
public:
	//! constructor
	StNormal(){}

	//! destructor
	virtual ~StNormal(void){}

	//! ask if we are allowed to move in this mode
	virtual bool AllowedMoving(){return true;}

	//! ask if we are allowed to rotate in this mode
	virtual bool AllowedRotating(){return true;}

	//! tell if we should play stand anim when iddle on this mode
	virtual bool StandOnIddle(){return true;}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "Stand";
		return true;
	}

	//! check if we can change mode from this state
	virtual bool AllowChangeMode(){return true;}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}
};


//*************************************************************************************************
//*                               class StMovingObject
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StMovingObject : public CharacterStateBase
{
public:
	//! constructor
	StMovingObject(){}

	//! destructor
	virtual ~StMovingObject(void){}

	//! ask if we are allowed to move in this mode
	virtual bool AllowedMoving(){return true;}

	//! ask if we are allowed to rotate in this mode
	virtual bool AllowedRotating(){return true;}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "PushContainer";
		return true;
	}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}
};



//*************************************************************************************************
//*                               class StMovingObject
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StRestrictedMovingObject : public CharacterStateBase
{
public:
	//! constructor
	StRestrictedMovingObject()
	{}

	//! destructor
	virtual ~StRestrictedMovingObject(void){}

	//! ask if we are allowed to move in this mode
	virtual bool AllowedMoving(){return true;}

	//! ask if we are allowed to rotate in this mode
	virtual bool AllowedRotating(){return false;}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "PushContainer";
		return true;
	}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}
};




//*************************************************************************************************
//*                               class StImmune
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StImmune : public CharacterStateBase
{
public:
	//! constructor
	//! in normal immune can not be hurt or drown either 
	StImmune()
	{}

	//! destructor
	virtual ~StImmune(void){}

	//! ask if we are allowed to move in this mode
	virtual bool AllowedMoving(){return true;}

	//! ask if we are allowed to rotate in this mode
	virtual bool AllowedRotating(){return true;}

	//! check if in this state we can play hurt animation
	virtual bool CanPlayHurt(){return false;}

	//! check if in this state we are immune to hurt
	virtual bool IsImmuneHurt(){return true;}

	//! check if in this state we are immune to drowning
	virtual bool IsImmuneDrowning(){return true;}

	//! ask if we can should make the character blinking on screen
	virtual bool ShouldBlinkOnScreen(){return true;}

	//! tell if we should play stand anim when iddle on this mode
	virtual bool StandOnIddle(){return true;}


	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "Stand";
		return true;
	}

	//! check if we can change mode from this state
	virtual bool AllowChangeMode(){return true;}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}
};



//*************************************************************************************************
//*                               class StImmune
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StProtectedHurt : public CharacterStateBase
{
public:
	//! constructor
	//! in normal immune can not be hurt or drown either 
	StProtectedHurt()
	{}

	//! destructor
	virtual ~StProtectedHurt(void){}

	//! ask if we are allowed to move in this mode
	virtual bool AllowedMoving(){return true;}

	//! ask if we are allowed to rotate in this mode
	virtual bool AllowedRotating(){return true;}

	//! check if in this state we can play hurt animation
	virtual bool CanPlayHurt(){return false;}

	//! check if in this state we are immune to hurt
	virtual bool IsImmuneHurt(){return true;}

	//! tell if we should play stand anim when iddle on this mode
	virtual bool StandOnIddle(){return true;}

	//! check if we can change mode from this state
	virtual bool AllowChangeMode(){return true;}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}
};


//*************************************************************************************************
//*                               class StHidden
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StHidden : public CharacterStateBase
{
public:
	//! constructor
	StHidden()
		: _switchstate(false)
	{}

	//! destructor
	virtual ~StHidden(void){}

	//! ask if we are allowed to move in this mode
	virtual bool AllowedMoving(){return true;}

	//! ask if we are allowed to rotate in this mode
	virtual bool AllowedRotating(){return false;}

	//! tell state that player is moving
	virtual void InformMoving()
	{
		_switchstate = true;
	}

	//! check if should change to another state
	virtual bool ShouldChangeState(LbaNet::ModelState & newstate)
	{
		newstate = LbaNet::StNormal;
		return _switchstate;
	}

	//! ask if char is hidden on screen
	virtual bool IsHidden(){return true;}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "DoAction";
		return true;
	}

	//! check if we can change mode from this state
	virtual bool AllowChangeMode(){return true;}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}

private:
	bool	_switchstate;
};




//*************************************************************************************************
//*                               class StDying
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StDying : public CharacterStateBase
{
public:
	//! constructor
	StDying(void){}

	//! destructor
	virtual ~StDying(void){}

	//! tell state that current animation has finished
	//! return true if animation should be paused
	virtual bool AnimationFinished();


	//! check if in this state we can play hurt animation
	virtual bool CanPlayHurt(){return false;}

	//! check if in this state we are immune to hurt
	virtual bool IsImmuneHurt(){return true;}

	//! check if in this state we are immune to gravity
	virtual bool IsImmuneGravity(){return true;}

	//! check if in this state we are immune to drowning
	virtual bool IsImmuneDrowning(){return true;}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "Die";
		return true;
	}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState)
	{
		if(NewState == LbaNet::StNormal)
			return true;

		if(NewState == LbaNet::StImmune)
			return true;

		return false;
	}
};



//*************************************************************************************************
//*                               class StDrowning
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StDrowning : public StDying
{
public:
	//! constructor
	StDrowning(void){}

	//! destructor
	virtual ~StDrowning(void){}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "Drown";
		return true;
	}
};

//*************************************************************************************************
//*                               class StDrowningGas
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StDrowningGas : public StDying
{
public:
	//! constructor
	StDrowningGas(void){}

	//! destructor
	virtual ~StDrowningGas(void){}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "DrownGaz";
		return true;
	}
};

//*************************************************************************************************
//*                               class StBurning
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StBurning : public StDying
{
public:
	//! constructor
	StBurning(void){}

	//! destructor
	virtual ~StBurning(void){}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "DrownFire";
		return true;
	}
};



//*************************************************************************************************
//*                               class StSmallHurt
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StSmallHurt : public CharacterStateBase
{
public:
	//! constructor
	StSmallHurt(void)
		: _switchstate(false)
	{}

	//! destructor
	virtual ~StSmallHurt(void){}


	//! tell state that current animation has finished
	//! return true if animation should be paused
	virtual bool AnimationFinished()
	{
		_switchstate = true;
		return false;
	}

	//! check if in this state we can play hurt animation
	virtual bool CanPlayHurt(){return false;}

	//! check if should change to another state
	virtual bool ShouldChangeState(LbaNet::ModelState & newstate)
	{
		newstate = LbaNet::StNormal;
		return _switchstate;
	}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "HurtSmall";
		return true;
	}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}


private:
	bool	_switchstate;
};


//*************************************************************************************************
//*                               class StMediumHurt
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StMediumHurt : public StSmallHurt
{
public:
	//! constructor
	StMediumHurt(void){}

	//! destructor
	virtual ~StMediumHurt(void){}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "HurtMedium";
		return true;
	}
};

//*************************************************************************************************
//*                               class StBigHurt
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StBigHurt : public StSmallHurt
{
public:
	//! constructor
	StBigHurt(void){}

	//! destructor
	virtual ~StBigHurt(void){}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "HurtBig";
		return true;
	}
};

//*************************************************************************************************
//*                               class StFinishedFall
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StFinishedFall : public StSmallHurt
{
public:
	//! constructor
	StFinishedFall(void){}

	//! destructor
	virtual ~StFinishedFall(void){}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "StopFall";
		return true;
	}
};

//*************************************************************************************************
//*                               class StHurtFall
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StHurtFall : public StSmallHurt
{
public:
	//! constructor
	StHurtFall(void){}

	//! destructor
	virtual ~StHurtFall(void){}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "StopFallHurt";
		return true;
	}
};



//*************************************************************************************************
//*                               class StFalling
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StFalling : public CharacterStateBase
{
public:
	//! constructor
	StFalling(void){}

	//! destructor
	virtual ~StFalling(void){}


	//! check if in this state we can play hurt animation
	virtual bool CanPlayHurt(){return false;}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "Fall";
		return true;
	}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}
};


//*************************************************************************************************
//*                               class CharacterStateBase
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StJumping : public CharacterStateBase
{
public:
	//! constructor
	StJumping(void)
		: _switchstate(false)
	{}

	//! destructor
	virtual ~StJumping(void){}


	//! tell state that current animation has finished
	//! return true if animation should be paused
	virtual bool AnimationFinished()
	{
		_switchstate = true;
		return false;
	}

	//! check if in this state we are immune to gravity
	virtual bool IsImmuneGravity(){return true;}

	//! check if in this state we are immune to drowning
	virtual bool IsImmuneDrowning(){return true;}

	//! check if should change to another state
	virtual bool ShouldChangeState(LbaNet::ModelState & newstate)
	{
		newstate = LbaNet::StNormal;
		return _switchstate;
	}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "DoAction";
		return true;
	}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}

private:
	bool	_switchstate;
};



//*************************************************************************************************
//*                               class StUseWeapon
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StUseWeapon: public CharacterStateBase
{
public:
	//! constructor
	StUseWeapon(void)
		: _switchstate(false)
	{}

	//! destructor
	virtual ~StUseWeapon(void){}


	//! tell state that current animation has finished
	//! return true if animation should be paused
	virtual bool AnimationFinished()
	{
		_switchstate = true;
		return false;
	}


	//! check if should change to another state
	virtual bool ShouldChangeState(LbaNet::ModelState & newstate)
	{
		newstate = LbaNet::StNormal;
		return _switchstate;
	}


	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "UseWeapon";
		return true;
	}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}

private:
	bool	_switchstate;

};



//*************************************************************************************************
//*                               class StScripted
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StScripted: public CharacterStateBase
{
public:
	//! constructor
	StScripted(void){}

	//! destructor
	virtual ~StScripted(void){}

	//! check if in this state we can play hurt animation
	virtual bool CanPlayHurt(){return false;}

	//! check if in this state we are immune to hurt
	virtual bool IsImmuneHurt(){return true;}

	//! check if in this state we are immune to gravity
	virtual bool IsImmuneGravity(){return true;}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}
};




//*************************************************************************************************
//*                               class StFighting
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StFighting : public CharacterStateBase
{
public:
	//! constructor
	StFighting(void){}

	//! destructor
	virtual ~StFighting(void){}

	//! ask if we are allowed to rotate in this mode
	virtual bool AllowedRotating(){return true;}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "DoAction";
		return true;
	}

	//! check if we can change mode from this state
	virtual bool AllowChangeMode(){return true;}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}
	

};


				

#endif
