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


#include "Randomizer.h"
#include <ctime>


Randomizer* Randomizer::_singletonInstance = NULL;



/***********************************************************
	singleton pattern
***********************************************************/
Randomizer * Randomizer::getInstance()
{
    if(!_singletonInstance)
    {
        _singletonInstance = new Randomizer();
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
Randomizer::Randomizer()
: _engine(clock()), _generator(_engine)
{

}


/***********************************************************
give a number between 0 and 1
***********************************************************/
double Randomizer::Rand()
{
	return _generator();
}



/***********************************************************
give a integer number between 0 and max
***********************************************************/
int Randomizer::RandInt(int max)
{
	return (int)(_generator() * max);
}

/***********************************************************
give a integer number between min and max
***********************************************************/
int Randomizer::RandInt(int min, int max)
{
	return (int)(_generator() * (max-min)) + min;
}