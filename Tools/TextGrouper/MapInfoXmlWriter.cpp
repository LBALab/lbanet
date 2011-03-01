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


#include "MapInfoXmlWriter.h"
#include "tinyxml.h"

#include <fstream>


// save world information into file
void MapInfoXmlWriter::SaveTexts(const std::string Filename, const std::map<long, std::string> &txts)
{
	TiXmlDocument doc;
 	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "UTF8", "" );
	doc.LinkEndChild( decl );

	TiXmlElement * root = new TiXmlElement("texts");
	doc.LinkEndChild( root );

	std::map<long, std::string>::const_iterator it = txts.begin();
	std::map<long, std::string>::const_iterator end = txts.end();
	for(; it != end; ++it)
	{
		TiXmlElement * txt = new TiXmlElement( "text" );
		txt->SetAttribute("id", it->first);
		root->LinkEndChild(txt);
		txt->LinkEndChild(new TiXmlText(it->second));
	}


	doc.SaveFile(Filename);
}

