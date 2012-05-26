/*
--------------------------------[ FONT8FONT.h ]---------------------------------

Author: David Glass
Info: Modified by Rincevent_123 to fit lbanet

-------------------------------[ GNU License ]-------------------------------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

-----------------------------------------------------------------------------
*/


#include <vector>
using namespace std;


class FONT_GLYPH
{
public:
	//! constructor
	FONT_GLYPH()
	{
		dx=0;
		width=0;
		mapx=0;
		mapy=0;
		advance=0;
	}

	int dx;
	int width;
	int mapx;
	int mapy;
	int advance;
};


class FONT_FONT
{
public:
	//! constructor
	FONT_FONT()
	{
		name="";
		char_height=0;
		average_advance=0;
		origin=0;
	}

	string name;
	int char_height;
	int average_advance;
	int origin;
	vector<char> map;
	vector<FONT_GLYPH> glyph;
};





