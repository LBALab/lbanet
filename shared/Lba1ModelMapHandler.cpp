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

#include "Lba1ModelMapHandler.h"
#include "StringHelperFuncs.h"

#include <fstream>

Lba1ModelMapHandler* Lba1ModelMapHandler::_singletonInstance = NULL;



/***********************************************************
singleton pattern
***********************************************************/
Lba1ModelMapHandler * Lba1ModelMapHandler::getInstance()
{
    if(!_singletonInstance)
    {
        _singletonInstance = new Lba1ModelMapHandler();
		return _singletonInstance;
    }
    else
    {
		return _singletonInstance;
    }
}


/***********************************************************
Constructor
***********************************************************/
Lba1ModelMapHandler::Lba1ModelMapHandler()
{
	// read the file and get data
	std::ifstream file((Lba1ModelDataPath+"lba1_model_animation.csv").c_str());
	if(file.is_open())
	{
		// read first information line
		std::string line;
		std::vector<std::string> infos;

		std::getline(file, line);
		StringHelper::Tokenize(line, infos, ",");

		while(!file.eof())
		{
			std::getline(file, line);
			std::vector<std::string> tokens;
			StringHelper::Tokenize(line, tokens, ",");

			_data[tokens[0]].outfits[tokens[1]].weapons[tokens[2]].modes[tokens[3]].modelnumber = atoi(tokens[4].c_str());
				_data[tokens[0]].outfits[tokens[1]].weapons[tokens[2]].modes[tokens[3]].bodynumber = atoi(tokens[5].c_str());

			for(size_t i=6; i<tokens.size(); ++i)
			{
				std::string anims = tokens[i];
				std::string animstring = infos[i];
				std::vector<std::string> tokens2;
				StringHelper::Tokenize(anims, tokens2, ";");
				std::vector<int> animvec;
				for(size_t j=0; j<tokens2.size(); ++j)
					animvec.push_back(atoi(tokens2[j].c_str()));

				_data[tokens[0]].outfits[tokens[1]].weapons[tokens[2]].modes[tokens[3]].animations[animstring] = animvec;
			}


		}
	}
}


/***********************************************************
Destructor
***********************************************************/
Lba1ModelMapHandler::~Lba1ModelMapHandler()
{

}


/***********************************************************
get model number and body number
***********************************************************/
int Lba1ModelMapHandler::GetModelInfo(	const std::string & modelname,
										const std::string & outfit,
										const std::string & weapon,
										const std::string & mode,
										const std::string & animation,
										int & resmodel,
										int & resbody,
										std::vector<int> & resanimation)
{

	std::map<std::string, std::vector<int> > & anims = 
		_data[modelname].outfits[outfit].weapons[weapon].modes[mode].animations;

	// do first trial with current mode
	{
		std::map<std::string, std::vector<int> >::iterator it = anims.find(animation);
		if(it != anims.end())
		{
			resanimation = it->second;
			if(resanimation.size() > 0)
			{
				// normal case
				if(resanimation[0] >= 0)
				{
					resmodel = _data[modelname].outfits[outfit].weapons[weapon].modes[mode].modelnumber;
					resbody = _data[modelname].outfits[outfit].weapons[weapon].modes[mode].bodynumber;
					return 0;
				}

				// animation forced to no - e.g. cant go backward with dinofly
				if(resanimation[0] == -2) 
					return -1;
			}
		}
	}

	// if no success before - try with default mode
	std::map<std::string, ModeData> & modes = 
		_data[modelname].outfits[outfit].weapons[weapon].modes;

	if(modes.size() > 0)
	{
		ModeData & tmpmodeld = modes.begin()->second;
		std::map<std::string, std::vector<int> >::iterator it = 
		tmpmodeld.animations.find(animation);

		if(it != tmpmodeld.animations.end())
		{
			resanimation = it->second;
			if(resanimation.size() > 0)
				if(resanimation[0] >= 0)
				{
					resmodel = tmpmodeld.modelnumber;
					resbody = tmpmodeld.bodynumber;
					return 0;
				}
		}
	}

	// if still no success then no way
	return -1;
}
