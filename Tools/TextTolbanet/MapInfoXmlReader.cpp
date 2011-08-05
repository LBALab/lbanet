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


#include "MapInfoXmlReader.h"
#include "tinyxml.h"
#include <vector>

// string helper function
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

// string helper function
static void StringTokenize(const std::string& str,
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
		lastPos = str.find_first_not_of(delimiters, pos);

		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

/*
--------------------------------------------------------------------------------------------------
- get a text from file
--------------------------------------------------------------------------------------------------
*/
std::map<long, std::string> MapInfoXmlReader::LoadTextFile(const std::string &Filename)
{
	std::map<long, std::string> res;

	TiXmlDocument doc(Filename);
	if (!doc.LoadFile())
		return res;

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;

	// block: text attributes
	{
		pElem=hDoc.FirstChildElement().Element();

		// should always have a valid root but handle gracefully if it does
		if (!pElem)
			return res;


		// for each text
		pElem=pElem->FirstChildElement("quotes");
		pElem=pElem->FirstChildElement();
		for(;pElem; pElem=pElem->NextSiblingElement())
		{
			long ctid = -1;
			pElem->QueryValueAttribute("id", &ctid);

			if(pElem->FirstChild())
				res[ctid] = pElem->FirstChild()->Value();
		}
	}

	return res;
}


/*
--------------------------------------------------------------------------------------------------
- get a text from file
--------------------------------------------------------------------------------------------------
*/
std::map<long, std::string> MapInfoXmlReader::LoadTextFileN(const std::string &Filename)
{
	std::map<long, std::string> res;

	TiXmlDocument doc(Filename);
	if (!doc.LoadFile())
		return res;

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;

	// block: text attributes
	{
		pElem=hDoc.FirstChildElement().Element();

		// should always have a valid root but handle gracefully if it does
		if (!pElem)
			return res;


		// for each text
		pElem=pElem->FirstChildElement();
		for(;pElem; pElem=pElem->NextSiblingElement())
		{
			long ctid = -1;
			pElem->QueryValueAttribute("id", &ctid);

			if(pElem->FirstChild())
				res[ctid] = pElem->FirstChild()->Value();
		}
	}

	return res;
}


