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


#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>



#if !defined(__LbaNetModel_1_Randomizer_h)
#define __LbaNetModel_1_Randomizer_h


/***********************************************************************
 * Module:  Randomizer.h
 * Author:  vivien
 * Modified: lundi 27 juillet 2009 14:53:50
 * Purpose: Declaration of the class Randomizer
 *********************************************************************/
class Randomizer
{
public:

	// singleton pattern
   static Randomizer * getInstance();

	//! give a number between 0 and 1
	double Rand();

	//! give a integer number between 0 and max
	int RandInt(int max);

	//! give a integer number between min and max
	int RandInt(int min, int max);

protected:
	//! construtor
	Randomizer();
	Randomizer(const Randomizer &);
	const Randomizer & operator=(const Randomizer &);


private:
	boost::mt19937									_engine;
	boost::uniform_01<boost::mt19937>				_generator;

	static Randomizer *								_singletonInstance;
};

#endif