#include "DoorHandler.h"
#include <math.h>

/***********************************************************
update position of the script
***********************************************************/
DoorHandler::DoorHandler(const ActorObjectInfo & actorinfo, int otype, 
					int odirection, float openingvalue, float openingspeed,
					bool Refreshscript)
	: ActorHandler(actorinfo), _otype(otype), _odirection(odirection),
		_openingvalue(openingvalue), _openingspeed(openingspeed), _openingcounter(0)
{
	if(Refreshscript)
		RefreshScript();
}

/***********************************************************
update position of the script
***********************************************************/
void DoorHandler::SendSignal(int Signalnumber)
{
	if(Signalnumber == 10)	// opening
	{
		++_openingcounter;
		if(_openingcounter == 1)
		{
			ActorHandler::SendSignal(1);
			return;
		}
	}

	if(Signalnumber == 11)	// closing
	{
		--_openingcounter;
		if(_openingcounter < 0)
			_openingcounter = 0;
		else if(_openingcounter == 0)
		{
			ActorHandler::SendSignal(2);
			return;
		}
	}


	ActorHandler::SendSignal(Signalnumber);
}



/***********************************************************
refresh door script
***********************************************************/
void DoorHandler::RefreshScript()
{
	ClearRunningScript();
	m_script.clear();

	bool Xdoor = m_actorinfo.PhysicDesc.SizeX > m_actorinfo.PhysicDesc.SizeZ;

	// create the script depending of the type
	switch(_otype)
	{
		case 0: // translation
		{
			// wait for opening signal
			AddScriptPart(ActorScriptPartBasePtr(new ActorScriptPart_WaitForSignal(1)));

			//translate
			float addX=0, addY=0, addZ = 0;
			switch(_odirection)
			{
				case 0:	// right
				{
					if(Xdoor)
						addX -= fabs(_openingvalue);
					else
						addZ -= fabs(_openingvalue);
				}
				break;
				case 1:	// left
				{
					if(Xdoor)
						addX += fabs(_openingvalue);
					else
						addZ += fabs(_openingvalue);
				}
				break;
				case 2:	// top
				{
					addY += fabs(_openingvalue);
				}
				break;
				case 3:	// bottom
				{
					addY -= fabs(_openingvalue);
				}
				break;
			}
			AddScriptPart(ActorScriptPartBasePtr(new ActorScriptPart_GoTo(m_actorinfo.PhysicDesc.Pos.X+addX, 
													m_actorinfo.PhysicDesc.Pos.Y+addY, 
													m_actorinfo.PhysicDesc.Pos.Z+addZ, 
													_openingspeed)));

			//wait for closing signal
			AddScriptPart(ActorScriptPartBasePtr(new ActorScriptPart_WaitForSignal(2)));

			//translate back
			AddScriptPart(ActorScriptPartBasePtr(new ActorScriptPart_GoTo(m_actorinfo.PhysicDesc.Pos.X, 
													m_actorinfo.PhysicDesc.Pos.Y, 
													m_actorinfo.PhysicDesc.Pos.Z, 
													_openingspeed)));
		}
		break;

		case 1:	// rotation
		{
		// wait for opening signal
			AddScriptPart(ActorScriptPartBasePtr(new ActorScriptPart_WaitForSignal(1)));

			float doorrY = m_actorinfo.PhysicDesc.Pos.Rotation;

			//translate
			float addX=0, addY=0, addZ = 0;
			switch(_odirection)
			{
				case 0:	// right
				{
					if(Xdoor)
						addX -= m_actorinfo.PhysicDesc.SizeX/2;
					else
						addZ -= m_actorinfo.PhysicDesc.SizeZ/2;
				}
				break;
				case 1:	// left
				{
					if(Xdoor)
						addX += m_actorinfo.PhysicDesc.SizeX/2;
					else
						addZ += m_actorinfo.PhysicDesc.SizeZ/2;
				}
				break;

			}
			AddScriptPart(ActorScriptPartBasePtr(new ActorScriptPart_RotateFromPoint(doorrY+_openingvalue,
													m_actorinfo.PhysicDesc.Pos.X+addX, 
													m_actorinfo.PhysicDesc.Pos.Y+addY, 
													m_actorinfo.PhysicDesc.Pos.Z+addZ, 
													_openingspeed)));

			//wait for closing signal
			AddScriptPart(ActorScriptPartBasePtr(new ActorScriptPart_WaitForSignal(2)));

			//translate back
			AddScriptPart(ActorScriptPartBasePtr(new ActorScriptPart_RotateFromPoint(doorrY,
													m_actorinfo.PhysicDesc.Pos.X+addX,  
													m_actorinfo.PhysicDesc.Pos.Y+addY,  
													m_actorinfo.PhysicDesc.Pos.Z+addZ,  
													_openingspeed)));
		}
		break;
	}
}


/***********************************************************
return the build class
***********************************************************/
std::string DoorHandler::LuaBuildClass()
{
	std::stringstream res;
	res<<"DoorHandler(Actor_"<<m_actorinfo.ObjectId<<","<<_otype
		<<","<<_odirection<<","<<_openingvalue<<","<<_openingspeed<<",false)";

	return res.str();
}




/***********************************************************
return opening type
***********************************************************/
std::string DoorHandler::GetOpeningType()
{
	switch(_otype)
	{
		case 0:
			return "translation";
		case 1:
			return "rotation";
	}


	return "";
}


/***********************************************************
return opening direction
***********************************************************/
std::string DoorHandler::GetOpeningDirection()
{
	switch(_odirection)
	{
		case 0:
			return "right";
		case 1:
			return "left";
		case 2:
			return "top";
		case 3:
			return "bottom";
	}

	return "";
}



/***********************************************************
return opening type
***********************************************************/
void DoorHandler::SetOpeningType(const std::string & type)
{
	if(type == "translation")
		_otype = 0;
	if(type == "rotation")
		_otype = 1;

	RefreshScript();
}

/***********************************************************
return opening direction
***********************************************************/
void DoorHandler::SetOpeningDirection(const std::string & direction)
{
	if(direction == "right")
		_odirection = 0;
	if(direction == "left")
		_odirection = 1;
	if(direction == "top")
		_odirection = 2;
	if(direction == "bottom")
		_odirection = 3;

	RefreshScript();
}

/***********************************************************
accessor
***********************************************************/
void DoorHandler::SetOpeningValue(float value)
{
	_openingvalue = value;
	RefreshScript();
}

/***********************************************************
accessor
***********************************************************/
void DoorHandler::SetOpeningSpeed(float value)
{
	_openingspeed = value;
	RefreshScript();
}