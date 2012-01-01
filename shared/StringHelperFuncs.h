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


#ifndef _STRING_HELPER_FUNCTIONS_H__
#define _STRING_HELPER_FUNCTIONS_H__



#include <string>
#include <vector>


class StringHelper
{

public:

	static void StripCharfromString( std::string& s, char c )
	{
		size_t idx(0);
		do
		{
			idx = s.find(c);
			if ( idx != std::string::npos )
			{
				s.erase(idx,1);
			}

		} while( idx != std::string::npos );
	}



	static void Trim(std::string& str)
	{
		std::string::size_type pos = str.find_last_not_of(' ');
		if(pos != std::string::npos)
		{
			str.erase(pos + 1);
			pos = str.find_first_not_of(' ');

			if(pos != std::string::npos)
				str.erase(0, pos);
		}
		else
			str.clear();

	}




	static void Tokenize(const std::string& str,
											std::vector<std::string>& tokens,
											const std::string& delimiters)
	{
		// Skip delimiters at beginning.
		std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
		// Find first "non-delimiter".
		std::string::size_type pos     = str.find_first_of(delimiters, lastPos);



		while (std::string::npos != pos || std::string::npos != lastPos)
		{
			// Found a token, add it to the vector.
			std::string tmp = str.substr(lastPos, pos - lastPos);
			Trim(tmp);
			tokens.push_back(tmp);

			// Skip delimiters.  Note the "not_of"
			//lastPos = str.find_first_not_of(delimiters, pos);
			lastPos = (pos == std::string::npos) ? pos : pos+1;

			// Find next "non-delimiter"
			pos = str.find_first_of(delimiters, lastPos);
		}
	}





	static std::string replaceall(const std::string & str, const std::string & toreplace, const std::string & with)
	{
		std::string res = str;

		int len = toreplace.size(), pos;
		while((pos=res.find(toreplace)) != std::string::npos)
		{
			res=res.substr(0,pos)+with+res.substr(pos+len);
		}

		return res;
	}
};




#endif