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
	//! 0 -> no
	//! 1 -> yes
	//! 2 -> yes but no turning animation
	virtual int AllowedRotating(){return 0;}

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
	
	//! check if player is in dead state
	virtual bool IsDead(){return false;}

	//! check if can use weapon in this state
	virtual bool CanUseWeapon(){return false;}
};



//*************************************************************************************************
//*                               class CharacterStateAllowMoving
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateNormal : public CharacterStateBase
{
public:
	//! constructor
	StateNormal(){}

	//! destructor
	virtual ~StateNormal(void){}

	//! ask if we are allowed to move in this mode
	virtual bool AllowedMoving(){return true;}

	//! ask if we are allowed to rotate in this mode
	//! 0 -> no
	//! 1 -> yes
	//! 2 -> yes but no turning animation
	virtual int AllowedRotating(){return 1;}

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

	//! check if can use weapon in this state
	virtual bool CanUseWeapon(){return true;}
};


//*************************************************************************************************
//*                               class StMovingObject
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateMovingObject : public CharacterStateBase
{
public:
	//! constructor
	StateMovingObject(){}

	//! destructor
	virtual ~StateMovingObject(void){}

	//! ask if we are allowed to move in this mode
	virtual bool AllowedMoving(){return true;}

	//! ask if we are allowed to rotate in this mode
	//! 0 -> no
	//! 1 -> yes
	//! 2 -> yes but no turning animation
	virtual int AllowedRotating(){return 1;}

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
class StateRestrictedMovingObject : public CharacterStateBase
{
public:
	//! constructor
	StateRestrictedMovingObject()
	{}

	//! destructor
	virtual ~StateRestrictedMovingObject(void){}

	//! ask if we are allowed to move in this mode
	virtual bool AllowedMoving(){return true;}

	//! ask if we are allowed to rotate in this mode
	//! 0 -> no
	//! 1 -> yes
	//! 2 -> yes but no turning animation
	virtual int AllowedRotating(){return 0;}

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
class StateImmune : public CharacterStateBase
{
public:
	//! constructor
	//! in normal immune can not be hurt or drown either 
	StateImmune()
	{}

	//! destructor
	virtual ~StateImmune(void){}

	//! ask if we are allowed to move in this mode
	virtual bool AllowedMoving(){return true;}

	//! ask if we are allowed to rotate in this mode
	//! 0 -> no
	//! 1 -> yes
	//! 2 -> yes but no turning animation
	virtual int AllowedRotating(){return 1;}

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
class StateProtectedHurt : public CharacterStateBase
{
public:
	//! constructor
	//! in normal immune can not drown either 
	StateProtectedHurt()
	{}

	//! destructor
	virtual ~StateProtectedHurt(void){}

	//! ask if we are allowed to move in this mode
	virtual bool AllowedMoving(){return true;}

	//! ask if we are allowed to rotate in this mode
	//! 0 -> no
	//! 1 -> yes
	//! 2 -> yes but no turning animation
	virtual int AllowedRotating(){return 1;}

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

	//! check if can use weapon in this state
	virtual bool CanUseWeapon(){return true;}
};


//*************************************************************************************************
//*                               class StHidden
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateHidden : public CharacterStateBase
{
public:
	//! constructor
	StateHidden()
		: _switchstate(false)
	{}

	//! destructor
	virtual ~StateHidden(void){}

	//! ask if we are allowed to move in this mode
	virtual bool AllowedMoving(){return true;}

	//! ask if we are allowed to rotate in this mode
	//! 0 -> no
	//! 1 -> yes
	//! 2 -> yes but no turning animation
	virtual int AllowedRotating(){return 2;}

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
//*                               class StateDying
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateDying : public CharacterStateBase
{
public:
	//! constructor
	StateDying(void){}

	//! destructor
	virtual ~StateDying(void){}

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
	
	//! check if player is in dead state
	virtual bool IsDead(){return true;}
};



//*************************************************************************************************
//*                               class StateDrowning
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateDrowning : public StateDying
{
public:
	//! constructor
	StateDrowning(void){}

	//! destructor
	virtual ~StateDrowning(void){}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "Drown";
		return true;
	}
};

//*************************************************************************************************
//*                               class StateDrowningGas
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateDrowningGas : public StateDying
{
public:
	//! constructor
	StateDrowningGas(void){}

	//! destructor
	virtual ~StateDrowningGas(void){}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "DrownGaz";
		return true;
	}
};

//*************************************************************************************************
//*                               class StateBurning
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateBurning : public StateDying
{
public:
	//! constructor
	StateBurning(void){}

	//! destructor
	virtual ~StateBurning(void){}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "DrownFire";
		return true;
	}
};



//*************************************************************************************************
//*                               class StateSmallHurt
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateSmallHurt : public CharacterStateBase
{
public:
	//! constructor
	StateSmallHurt(void)
		: _switchstate(false)
	{}

	//! destructor
	virtual ~StateSmallHurt(void){}


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
//*                               class StateMediumHurt
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateMediumHurt : public StateSmallHurt
{
public:
	//! constructor
	StateMediumHurt(void){}

	//! destructor
	virtual ~StateMediumHurt(void){}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "HurtMedium";
		return true;
	}
};

//*************************************************************************************************
//*                               class StateBigHurt
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateBigHurt : public StateSmallHurt
{
public:
	//! constructor
	StateBigHurt(void){}

	//! destructor
	virtual ~StateBigHurt(void){}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "HurtBig";
		return true;
	}
};

//*************************************************************************************************
//*                               class StateFinishedFall
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateFinishedFall : public StateSmallHurt
{
public:
	//! constructor
	StateFinishedFall(void){}

	//! destructor
	virtual ~StateFinishedFall(void){}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "StopFall";
		return true;
	}
};

//*************************************************************************************************
//*                               class StateHurtFall
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateHurtFall : public StateSmallHurt
{
public:
	//! constructor
	StateHurtFall(void){}

	//! destructor
	virtual ~StateHurtFall(void){}

	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "StopFallHurt";
		return true;
	}
};



//*************************************************************************************************
//*                               class StateFalling
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateFalling : public CharacterStateBase
{
public:
	//! constructor
	StateFalling(void){}

	//! destructor
	virtual ~StateFalling(void){}


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
class StateJumping : public CharacterStateBase
{
public:
	//! constructor
	StateJumping(void)
		: _switchstate(false)
	{}

	//! destructor
	virtual ~StateJumping(void){}


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
class StateUseWeapon: public CharacterStateBase
{
public:
	//! constructor
	StateUseWeapon(void)
		: _switchstate(false)
	{}

	//! destructor
	virtual ~StateUseWeapon(void){}


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
//*                               class StateScripted
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateScripted: public CharacterStateBase
{
public:
	//! constructor
	StateScripted(void){}

	//! destructor
	virtual ~StateScripted(void){}

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
//*                               class StateFighting
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateFighting : public CharacterStateBase
{
public:
	//! constructor
	StateFighting(void){}

	//! destructor
	virtual ~StateFighting(void){}

	//! ask if we are allowed to rotate in this mode
	//! 0 -> no
	//! 1 -> yes
	//! 2 -> yes but no turning animation
	virtual int AllowedRotating(){return 2;}

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


	

//*************************************************************************************************
//*                               class StUseWeapon
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StatePrepareWeapon: public CharacterStateBase
{
public:
	//! constructor
	StatePrepareWeapon(void)
		: _switchstate(false)
	{}

	//! destructor
	virtual ~StatePrepareWeapon(void){}


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
		animstring = "PrepareWeapon";
		return true;
	}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}

private:
	bool	_switchstate;

};			







	

//*************************************************************************************************
//*                               class StateActivateSwitch
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateActivateSwitch: public CharacterStateBase
{
public:
	//! constructor
	StateActivateSwitch(void)
		: _switchstate(false)
	{}

	//! destructor
	virtual ~StateActivateSwitch(void){}


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
		animstring = "ActivateSwitch";
		return true;
	}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}

private:
	bool	_switchstate;

};	



//*************************************************************************************************
//*                               class StateActivateGroundSwitch
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateActivateGroundSwitch: public CharacterStateBase
{
public:
	//! constructor
	StateActivateGroundSwitch(void)
		: _switchstate(false)
	{}

	//! destructor
	virtual ~StateActivateGroundSwitch(void){}


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
		animstring = "ActivateGroundSwitch";
		return true;
	}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}

private:
	bool	_switchstate;

};	




	

//*************************************************************************************************
//*                               class StateHappy
//*************************************************************************************************
/**
* @brief Base class representing a certain state of a character
*
*/
class StateHappy: public CharacterStateBase
{
public:
	//! constructor
	StateHappy(void)
		: _switchstate(false)
	{}

	//! destructor
	virtual ~StateHappy(void){}


	//! ask state if we need to play animation at start
	virtual bool PlayAnimationAtStart(std::string & animstring)
	{
		animstring = "Happy";
		return true;
	}

	//! check if we can change state from this state
	virtual bool ChangeLegal(LbaNet::ModelState NewState){return true;}

private:
	bool	_switchstate;

};	


#endif
