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
	// only used when moving - if character stand then it will anyway drown
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
	ProtopackCharacterMode(void); //TODO sound when moving
	virtual ~ProtopackCharacterMode(void);

	// tell if in this mode we need to check for water/gaz/fire hazard
	virtual bool NeedCheckForWater(){return false;}


	//! tell the mode that we are moving forward/bakward
	virtual void CharacterMoving();

	//! tell the mode that we are stopping moving forward/bakward
	virtual void CharacterStoppedMoving();

	//! tell the mode that we are changing state
	virtual void CharacterChangedState();
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
	DinoflyCharacterMode(void){}
	virtual ~DinoflyCharacterMode(void){}

	// tell if in this mode we need to check for gravity
	virtual bool NeedCheckForGravity(){return false;}

	// tell if in this mode we need to check for water/gaz/fire hazard
	virtual bool NeedCheckForWater(){return false;}

	// tell if in this mode the character can fly
	virtual bool CanFly(){return true;}
};



#endif