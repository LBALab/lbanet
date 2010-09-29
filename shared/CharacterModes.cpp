#include "CharacterModes.h"

/***********************************************************
constructor
***********************************************************/
ProtopackCharacterMode::ProtopackCharacterMode(void)
: _moving(false)
{
}

/***********************************************************
destructor
***********************************************************/
ProtopackCharacterMode::~ProtopackCharacterMode(void)
{
	//TODO sound when moving
}


/***********************************************************
tell the mode that we are moving forward/bakward
***********************************************************/
void ProtopackCharacterMode::CharacterMoving()
{
	_moving = true;
	//TODO sound when moving
}


/***********************************************************
tell the mode that we are stopping moving forward/bakward
***********************************************************/
void ProtopackCharacterMode::CharacterStoppedMoving()
{
	_moving = false;
	//TODO sound when moving
}


/***********************************************************
tell the mode that we are changing state
***********************************************************/
void ProtopackCharacterMode::CharacterChangedState()
{
	//TODO sound when moving
}


/***********************************************************
constructor
***********************************************************/
DinoflyCharacterMode::DinoflyCharacterMode(void)
: _moving(false)
{

}

/***********************************************************
tell the mode that we are moving forward/bakward
***********************************************************/
void DinoflyCharacterMode::CharacterMoving()
{
	_moving = true;
}


/***********************************************************
tell the mode that we are stopping moving forward/bakward
***********************************************************/
void DinoflyCharacterMode::CharacterStoppedMoving()
{
	_moving = false;
}


/***********************************************************
get the speed to add to the X axis
***********************************************************/
float DinoflyCharacterMode::GetAddedSpeedX()
{
	if(_moving)
		return 0.03f; // TODO - test dino speed
	else
		return 0;
}
