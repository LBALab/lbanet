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


#include "XmlReader.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/detail/xml_parser_writer_settings.hpp>




/***********************************************************
get a text from file
***********************************************************/
std::map<long, std::string> XmlReader::LoadTextFile(const std::string &Filename)
{
	std::map<long, std::string> res;


	// Create an empty property tree object
	using boost::property_tree::wptree;
	wptree pt;

	// Load the XML file into the property tree
	try
	{
		read_xml(Filename, pt);
	}
	catch(...)
	{
		return res;
	}

	// get text info
	try
	{
		BOOST_FOREACH(wptree::value_type &v, pt.get_child(L"texts"))
		{
			long Id = v.second.get<long>(L"<xmlattr>.id");
			std::wstring text = v.second.data();
			std::string conv(text.begin(), text.end());
			res[Id] = conv;
		}
	}
	catch(...){} // no text


	return res;
}



/***********************************************************
save text in file
***********************************************************/
void XmlReader::SaveTextFile(const std::string &Filename, const std::map<long, std::string> &text)
{
	// Create an empty property tree object
	using boost::property_tree::ptree;
	ptree pt;

	typedef std::map<long, std::string> textseq;

	// get teleport info
    BOOST_FOREACH(const textseq::value_type &txt, text)
	{
		ptree &tmp = pt.add("texts.text", txt.second);
		tmp.put("<xmlattr>.id", txt.first);
	}


	// Write the property tree into the XML file 
	try
	{
		const boost::property_tree::xml_parser::xml_writer_settings<char> settings('	', 1);
		write_xml(Filename, pt, std::locale(), settings);
	}
	catch(...)
	{
	}
}

