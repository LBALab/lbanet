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


#ifndef _LBA_NET_CHARACTER_MODES_
#define _LBA_NET_CHARACTER_MODES_

#include <LbaTypes.h>


// keep track of the pressed keys
class CharKeyPressed
{
public:

	//! constructor
	CharKeyPressed()
	{
		_keyforward = false;
		_keybackward = false;
		_keyleft = false;
		_keyright = false;
		_keyup = false;
		_keydown = false;
		_keyaction = false;
	}

	bool										_keyforward;
	bool										_keybackward;
	bool										_keyleft;
	bool										_keyright;
	bool										_keyup;
	bool										_keydown;
	bool										_keyaction;
};


//*************************************************************************************************
//*                               class CharacterModeBase
//*************************************************************************************************
/**
* @brief Base class representing a certain mode of a character
*
*/
class CharacterModeBase
{
public:
	CharacterModeBase(void){}
	virtual ~CharacterModeBase(void){}

	// tell if in this mode we need to check for gravity
	virtual bool NeedCheckForGravity(){return true;}

	// tell if in this mode we need to check for water/gaz/fire hazard
	virtual bool NeedCheckForWater(){return true;}

	// tell if in this mode we should display the player as semi transparent (e.g. hidden)
	virtual bool IsSemiTransparent(){return false;}

	// tell if in this mode the character can fly
	virtual bool CanFly(){return false;}

	//! tell the mode that we are moving forward/bakward
	virtual void CharacterMoving(){}

	//! tell the mode that we are moving forward/bakward
	virtual void CharacterStoppedMoving(){}

	//! tell the mode that we are changing state
	virtual void CharacterChangedState(){}

	//! tell if character should use animation speed or not
	virtual bool UseAnimationSpeed(){return true;}

	//! get the speed to add to the X axis
	virtual float GetAddedSpeedX(){return 0;}

	//! check if we should change state when pressing action button on this mode
	virtual bool ChangeState(	LbaNet::ModelState 	currentstate,
								const CharKeyPressed & ButonPressed,
								LbaNet::ModelState & newstate) {return false;}

};

//*************************************************************************************************
//*                               class NormalCharacterMode
//*************************************************************************************************
/**
* @brief Base class representing a certain mode of a character
*
*/
class NormalCharacterMode : public CharacterModeBase
{
public:
	NormalCharacterMode(void){}
	virtual ~NormalCharacterMode(void){}
};

//*************************************************************************************************
//*                               class SportyCharacterMode
//*************************************************************************************************
/**
* @brief Base class representing a certain mode of a character
*
*/
class SportyCharacterMode : public CharacterModeBase
{
public:
	SportyCharacterMode(void){}
	virtual ~SportyCharacterMode(void){}

	//! check if we should change state when pressing action button on this mode
	virtual bool ChangeState(	LbaNet::ModelState 	currentstate,
								const CharKeyPressed & ButonPressed,
								LbaNet::ModelState & newstate)
	{
		if(ButonPressed._keyaction && currentstate != LbaNet::StJumping)
		{
			newstate = LbaNet::StJumping;
			return true;
		}

		if(ButonPressed._keybackward && currentstate == LbaNet::StJumping)
		{
			newstate = LbaNet::StNormal;
			return true;
		}

		return false;
	}

};


//*************************************************************************************************
//*                               class AggresiveCharacterMode
//*************************************************************************************************
/**
* @brief Base class representing a certain mode of a character
*
*/
class AggresiveCharacterMode : public CharacterModeBase
{
public:
	AggresiveCharacterMode(void){}
	virtual ~AggresiveCharacterMode(void){}


	//! check if we should change state when pressing action button on this mode
	virtual bool ChangeState(	LbaNet::ModelState 	currentstate,
								const CharKeyPressed & ButonPressed,
								LbaNet::ModelState & newstate)
	{
		if(ButonPressed._keyaction)
		{
			if(currentstate != LbaNet::StFighting)
			{
				newstate = LbaNet::StFighting;
				return true;
			}
		}
		else
		{
			if(currentstate == LbaNet::StFighting)
			{
				newstate = LbaNet::StNormal;
				return true;
			}
		}

		return false;
	}
};


//*************************************************************************************************
//*                               class DiscreteCharacterMode
//*************************************************************************************************
/**
* @brief Base class representing a certain mode of a character
*
*/
class DiscreteCharacterMode : public CharacterModeBase
{
public:
	DiscreteCharacterMode(void){}
	virtual ~DiscreteCharacterMode(void){}

	// tell if in this mode we should display the player as semi transparent (e.g. hidden)
	virtual bool IsSemiTransparent(){return true;}


	//! check if we should change state when pressing action button on this mode
	virtual bool ChangeState(	LbaNet::ModelState 	currentstate,
								const CharKeyPressed & ButonPressed,
								LbaNet::ModelState & newstate)
	{
		if(ButonPressed._keyaction && currentstate != LbaNet::StHidden)
		{
			newstate = LbaNet::StHidden;
			return true;
		}

		return false;
	}
};


//*************************************************************************************************
//*                               class ProtopackCharacterMode
//*************************************************************************************************
/**
* @brief Base class representing a certain mode of a character
*
*/
class ProtopackCharacterMode : public CharacterModeBase
{
public:
	ProtopackCharacterMode(void);
	virtual ~ProtopackCharacterMode(void);

	// tell if in this mode we need to check for water/gaz/fire hazard
	virtual bool NeedCheckForWater(){return !_moving;}


	//! tell the mode that we are moving forward/bakward
	virtual void CharacterMoving();

	//! tell the mode that we are stopping moving forward/bakward
	virtual void CharacterStoppedMoving();

	//! tell the mode that we are changing state
	virtual void CharacterChangedState();

private:
	bool	_moving;
};

//*************************************************************************************************
//*                               class HorseCharacterMode
//*************************************************************************************************
/**
* @brief Base class representing a certain mode of a character
*
*/
class HorseCharacterMode : public CharacterModeBase
{
public:
	HorseCharacterMode(void){}
	virtual ~HorseCharacterMode(void){}


	//! check if we should change state when pressing action button on this mode
	virtual bool ChangeState(	LbaNet::ModelState 	currentstate,
								const CharKeyPressed & ButonPressed,
								LbaNet::ModelState & newstate)
	{
		if(ButonPressed._keyaction && currentstate != LbaNet::StJumping)
		{
			newstate = LbaNet::StJumping;
			return true;
		}

		return false;
	}
};

//*************************************************************************************************
//*                               class DinoflyCharacterMode
//*************************************************************************************************
/**
* @brief Base class representing a certain mode of a character
*
*/
class DinoflyCharacterMode : public CharacterModeBase
{
public:
	//! constructor
	DinoflyCharacterMode(void);

	//! destructor
	virtual ~DinoflyCharacterMode(void){}

	// tell if in this mode we need to check for gravity
	virtual bool NeedCheckForGravity(){return false;}

	// tell if in this mode we need to check for water/gaz/fire hazard
	virtual bool NeedCheckForWater(){return false;}

	// tell if in this mode the character can fly
	virtual bool CanFly(){return true;}


	//! tell the mode that we are moving forward/bakward
	virtual void CharacterMoving();

	//! tell the mode that we are moving forward/bakward
	virtual void CharacterStoppedMoving();

	//! tell if character should use animation speed or not
	virtual bool UseAnimationSpeed(){return false;}

	//! get the speed to add to the X axis
	virtual float GetAddedSpeedX();

private:
	bool	_moving;
};



#endif