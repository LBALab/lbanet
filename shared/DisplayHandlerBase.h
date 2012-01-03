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


#ifndef _LBANET_DISPLAY_HANDLER_BASE_H_
#define _LBANET_DISPLAY_HANDLER_BASE_H_

class DisplayObjectHandlerBase;
class DisplayTransformation;

namespace LbaNet
{
	struct ObjectExtraInfo;
	struct LifeManaInfo;
}

#include <string>


//*************************************************************************************************
//*                               class DisplayHandlerBase
//*************************************************************************************************
/**
* @brief Base class for component taking care of the display
*
*/
class DisplayHandlerBase
{
public:

	//! constructor
	DisplayHandlerBase(){}


	//! destructor
	virtual ~DisplayHandlerBase(){}

	// create sprite object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateSpriteObject(int sceneidx, const std::string & spritefile, 
															float colorR, float colorG, float colorB, float colorA,
															boost::shared_ptr<DisplayTransformation> Tr,
															bool UseLight, bool CastShadow,
															const LbaNet::ObjectExtraInfo &extrainfo,
															const LbaNet::LifeManaInfo &lifeinfo,
															bool UseBillboard) = 0;

	//! create simple display object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateSimpleObject(int sceneidx, const std::string & filename,
															boost::shared_ptr<DisplayTransformation> Tr,
															bool UseLight, bool CastShadow,
															const LbaNet::ObjectExtraInfo &extrainfo,
															const LbaNet::LifeManaInfo &lifeinfo) = 0;

	//! create sphere object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateSphereObject(int sceneidx, float radius, 
															float colorR, float colorG, float colorB, float colorA,
															boost::shared_ptr<DisplayTransformation> Tr,
															const LbaNet::ObjectExtraInfo &extrainfo,
															const LbaNet::LifeManaInfo &lifeinfo) = 0;

	//! create capsule object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateCapsuleObject(int sceneidx, float radius, float height, 
															float colorR, float colorG, float colorB, float colorA,
															boost::shared_ptr<DisplayTransformation> Tr,
															const LbaNet::ObjectExtraInfo &extrainfo,
															const LbaNet::LifeManaInfo &lifeinfo) = 0;

	//! create box object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateBoxObject(int sceneidx, float sizex, float sizey, float sizez, 
															float colorR, float colorG, float colorB, float colorA,
															boost::shared_ptr<DisplayTransformation> Tr,
															const LbaNet::ObjectExtraInfo &extrainfo,
															const LbaNet::LifeManaInfo &lifeinfo) = 0;

	//! create cross object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateCrossObject(int sceneidx, float size,
															float colorR, float colorG, float colorB, float colorA,
															boost::shared_ptr<DisplayTransformation> Tr,
															const LbaNet::ObjectExtraInfo &extrainfo,
															const LbaNet::LifeManaInfo &lifeinfo) = 0;
};


#endif
