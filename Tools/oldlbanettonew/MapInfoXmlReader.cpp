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

// load a world information into memory
bool MapInfoXmlReader::LoadWorld(const std::string &Filename, WorldInfo & res)
{
	TiXmlDocument doc(Filename);
	if (!doc.LoadFile())
		return false;



	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	// block: world attributes
	{
		pElem=hDoc.FirstChildElement().Element();

		// should always have a valid root but handle gracefully if it does
		if (!pElem)
			return false;

		res.Name = pElem->Attribute("name");
		res.FirstMap = pElem->Attribute("firstmap");
		res.FirstSpawning = pElem->Attribute("firstsparea");

		// save this for later
		hRoot=TiXmlHandle(pElem);
	}

	// block: description
	{
		pElem=hRoot.FirstChild( "description" ).Element();
		if(pElem)
			res.Description=pElem->GetText();
	}

	// block: teleport
	{
		pElem=hRoot.FirstChild( "teleports" ).FirstChild().Element();
		for( pElem; pElem; pElem=pElem->NextSiblingElement())
		{
			TPInfo tp;
			tp.Name=pElem->Attribute("name");
			tp.NewMap=pElem->Attribute("map");
			tp.Spawning=pElem->Attribute("sparea");

			res.Teleports[tp.Name] = tp;
		}
	}
	// block: map
	{
		pElem=hRoot.FirstChild( "maps" ).FirstChild("Map").Element();
		for( pElem; pElem; pElem=pElem->NextSiblingElement())
		{
			MapInfo mi = LoadMap(pElem);
			res.Maps[mi.Name] = mi;
		}
	}

	return true;
}

/*
--------------------------------------------------------------------------------------------------
- load a map into memory
--------------------------------------------------------------------------------------------------
*/
MapInfo MapInfoXmlReader::LoadMap(TiXmlElement* pElem)
{
	MapInfo res;
	res.MusicLoop = 0;
	TiXmlHandle hRoot(0);

	// block: map attributes
	{
		// should always have a valid root but handle gracefully if it does
		if (!pElem)
			return res;

		res.Name = pElem->Attribute("name");
		std::string namem = res.Name;
		if(namem.find("Map") == 0)
		{
			namem = namem.substr(3);
			std::string numstr = namem.substr(0, namem.find("_"));
			std::string rest = namem.substr(namem.find("_"));
			int num = atoi(numstr.c_str());
			std::stringstream mapnamess;
			mapnamess<<"Map";
			if(num < 10)
				mapnamess<<"0";
			if(num < 100)
				mapnamess<<"0";
			mapnamess<<num<<rest;
			res.Name = mapnamess.str();
		}

		res.Type = pElem->Attribute("type");

		res.Music = pElem->Attribute("music");
		int testr = pElem->QueryIntAttribute("repeatmusic", &res.MusicLoop);
		if(testr != TIXML_SUCCESS)
			res.MusicLoop = 0;


		// save this for later
		hRoot=TiXmlHandle(pElem);
	}

	// block: description
	{
		pElem=hRoot.FirstChild( "description" ).Element();
		if(pElem)
			res.Description=pElem->GetText();
	}



	// block: spawning areas
	{
		int counter = 1;
		pElem=hRoot.FirstChild( "spareas" ).FirstChild().Element();
		for( pElem; pElem; pElem=pElem->NextSiblingElement())
		{
			SpawningInfo sp;
			sp.Id = counter++;
			sp.Rotation = 0;
			sp.Name=pElem->Attribute("name");

			pElem->QueryFloatAttribute("posX", &sp.PosX);
			pElem->QueryFloatAttribute("posY", &sp.PosY);
			pElem->QueryFloatAttribute("posZ", &sp.PosZ);
			pElem->QueryIntAttribute("RotationAtArrival", &sp.Rotation);
			if(sp.Rotation < 0)
				sp.Rotation = 0;
			if(sp.Rotation > 360)
				sp.Rotation = 0;

			res.Spawnings[sp.Name] = sp;
		}
	}

	// block: exit areas
	{
		pElem=hRoot.FirstChild( "exits" ).FirstChild().Element();
		for( pElem; pElem; pElem=pElem->NextSiblingElement())
		{
			ExitInfo ex;
			ex.Name=pElem->Attribute("name");
			ex.NewMap=pElem->Attribute("newMap");
			ex.Spawning=pElem->Attribute("spawning");

			pElem->QueryFloatAttribute("TopRightX", &ex.TopRightX);
			pElem->QueryFloatAttribute("TopRightY", &ex.TopRightY);
			pElem->QueryFloatAttribute("TopRightZ", &ex.TopRightZ);

			pElem->QueryFloatAttribute("BottomLeftX", &ex.BottomLeftX);
			pElem->QueryFloatAttribute("BottomLeftY", &ex.BottomLeftY);
			pElem->QueryFloatAttribute("BottomLeftZ", &ex.BottomLeftZ);

			res.Exits[ex.Name] = ex;
		}
	}

	return res;
}


/*
--------------------------------------------------------------------------------------------------
- load map actors into memory
--------------------------------------------------------------------------------------------------
*/
bool MapInfoXmlReader::LoadActors(const std::string &Filename)
{
//	TiXmlDocument doc(Filename);
//	if (!doc.LoadFile())
//		return false;
//
//
//	TiXmlHandle hDoc(&doc);
//	TiXmlElement* pElem;
//
//	// block: actors attributes
//	{
//		pElem=hDoc.FirstChildElement().Element();
//
//		// should always have a valid root but handle gracefully if it does
//		if (!pElem)
//			return false;
//
//
//		// for each actors
//		pElem=pElem->FirstChildElement();
//		for( pElem; pElem; pElem=pElem->NextSiblingElement())
//		{
//			long id=0, type=0;
//			float posX=0, posY=0, posZ=0;
//			float sizeX=0, sizeY=0, sizeZ=0;
//			float offsetsizeY=0;
//			int rotation=0;
//			bool passable = true;
//			bool depthmask = true;
//			bool movable = false;
//			bool collidable = true;
//			bool actif = false;
//			bool allowfreemove = false;
//
//			long renderertype=-1;
//			std::vector<long> renderertarget;
//			D3ObjectRenderer * renderer = NULL;
//			long outputsignal=-1;
//			long attachedsound=-1;
//			std::vector<long> stargets;
//			const char * targetsstring = pElem->Attribute("signaltargets");
//			if(targetsstring)
//			{
//				std::vector<std::string> tokens;
//				StringTokenize(targetsstring, tokens, ",");
//				for(size_t i=0; i<tokens.size(); ++i)
//					stargets.push_back(atol(tokens[i].c_str()));
//			}
//
//			const char * rendertargetsstring = pElem->Attribute("renderertarget");
//			if(rendertargetsstring)
//			{
//				std::vector<std::string> tokens;
//				StringTokenize(rendertargetsstring, tokens, ",");
//				for(size_t i=0; i<tokens.size(); ++i)
//					renderertarget.push_back(atol(tokens[i].c_str()));
//			}
//
//
//
//			pElem->QueryValueAttribute("id", &id);
//			std::stringstream strss;
//			strss<<"Start reading actor id "<<id;
//
//#ifndef _LBANET_SERVER_SIDE_
//			LogHandler::getInstance()->LogToFile(strss.str());
//#endif
//
//			pElem->QueryValueAttribute("type", &type);
//			pElem->QueryFloatAttribute("posX", &posX);
//			pElem->QueryFloatAttribute("posY", &posY);
//			pElem->QueryFloatAttribute("posZ", &posZ);
//			pElem->QueryFloatAttribute("sizeX", &sizeX);
//			pElem->QueryFloatAttribute("sizeY", &sizeY);
//			pElem->QueryFloatAttribute("sizeZ", &sizeZ);
//			pElem->QueryFloatAttribute("offsetsizeY", &offsetsizeY);
//			pElem->QueryIntAttribute("rotation", &rotation);
//			pElem->QueryValueAttribute("passable", &passable);
//			pElem->QueryValueAttribute("depthmask", &depthmask);
//			pElem->QueryValueAttribute("movable", &movable);
//			pElem->QueryValueAttribute("outputsignal", &outputsignal);
//			pElem->QueryValueAttribute("attachedsound", &attachedsound);
//			pElem->QueryValueAttribute("collidable", &collidable);
//			pElem->QueryValueAttribute("actif", &actif);
//			pElem->QueryValueAttribute("allowfreemove", &allowfreemove);
//
//
//			if(pElem->QueryValueAttribute("renderertype", &renderertype) == TIXML_SUCCESS)
//				if(renderertarget.size() > 0)
//				{
//#ifndef _LBANET_SERVER_SIDE_
//					//renderer = new SpriteRenderer();
//					switch(renderertype)
//					{
//						case 0: // sprite renderer
//							{
//								std::vector<SpriteInfo *> vectmp;
//								for(size_t itar = 0; itar<renderertarget.size(); ++itar)
//								{
//									std::map<long, SpriteInfo>::iterator itsp = spinfos.find(renderertarget[itar]);
//									if(itsp != spinfos.end())
//										vectmp.push_back(&itsp->second);
//								}
//
//								if(vectmp.size() > 0)
//								{
//									SpriteRenderer * tmp = new SpriteRenderer();
//									tmp->SetSprites(vectmp);
//									renderer = tmp;
//								}
//							}
//						break;
//						case 1: // video renderer
//							{
//								std::map<long, SpriteInfo>::iterator itsp = vidinfos.find(renderertarget[0]);
//								if(itsp != vidinfos.end())
//								{
//									std::vector<SpriteInfo *> vectmp;
//									vectmp.push_back(&itsp->second);
//									AviVideoRenderer * tmp = new AviVideoRenderer();
//									tmp->SetSprites(vectmp);
//									renderer = tmp;
//								}
//							}
//						break;
//						case 2: // model renderer
//							{
//								std::map<long, ModelInfo>::iterator itsp = modelinfos.find(renderertarget[0]);
//								if(itsp != modelinfos.end())
//								{
//									MS3DModel * tmp = new MS3DModel();
//									tmp->loadModelData( itsp->second.filename );
//									tmp->SetScale(itsp->second.ScaleX, itsp->second.ScaleY, itsp->second.ScaleZ);
//									tmp->SetTranslation(itsp->second.TransX, itsp->second.TransY, itsp->second.TransZ);
//									tmp->SetRotation(itsp->second.RotX, itsp->second.RotY, itsp->second.RotZ);
//
//
//									renderer = tmp;
//								}
//							}
//						break;
//						case 3: // character renderer
//							{
//								if(renderertarget.size() > 1)
//								{
//									CharacterRenderer * tmp = new CharacterRenderer(AnimationSpeed);
//									tmp->changeAnimEntity(renderertarget[0], renderertarget[1]);
//									tmp->setActorAnimation(0);
//									renderer = tmp;
//								}
//							}
//						break;
//					}
//#else
//					if(renderertype == 3)
//					{
//						if(renderertarget.size() > 1)
//						{
//							ServerCharacterRenderer * tmp = new ServerCharacterRenderer(AnimationSpeed);
//							tmp->changeAnimEntity(renderertarget[0], renderertarget[1]);
//							tmp->setActorAnimation(0);
//							renderer = tmp;
//						}
//					}
//#endif
//				}
//
//
//			Actor * act;
//			switch(type)
//			{
//				case 0:	//basic actor class
//					act = new Actor();
//				break;
//				case 1:	//text actor class
//				{
//					long textid=0;
//					float activationdistance;
//					pElem->QueryValueAttribute("activationdistance", &activationdistance);
//					pElem->QueryValueAttribute("textid", &textid);
//					int activationtype=1;
//					pElem->QueryValueAttribute("activationtype", &activationtype);
//					act = new TextActor(activationdistance, textid, activationtype);
//				}
//				break;
//				case 2:	//ladder actor class
//				{
//					float deltaX=0, deltaY=0, deltaZ=0;
//					int direction=0;
//					float activationdistance;
//					pElem->QueryValueAttribute("activationdistance", &activationdistance);
//					pElem->QueryValueAttribute("deltaX", &deltaX);
//					pElem->QueryValueAttribute("deltaY", &deltaY);
//					pElem->QueryValueAttribute("deltaZ", &deltaZ);
//					pElem->QueryValueAttribute("direction", &direction);
//					int activationtype=1;
//					pElem->QueryValueAttribute("activationtype", &activationtype);
//					act = new LadderActor(activationdistance, deltaX, deltaY, deltaZ, direction, activationtype);
//				}
//				break;
//				case 3:	//exit actor class
//				{
//					float deltaX=0, deltaY=0, deltaZ=0;
//					int direction=0;
//					float activationdistance;
//					pElem->QueryValueAttribute("activationdistance", &activationdistance);
//					pElem->QueryValueAttribute("deltaX", &deltaX);
//					pElem->QueryValueAttribute("deltaY", &deltaY);
//					pElem->QueryValueAttribute("deltaZ", &deltaZ);
//					pElem->QueryValueAttribute("direction", &direction);
//					int activationtype=1;
//					pElem->QueryValueAttribute("activationtype", &activationtype);
//					act = new ExitActor(activationdistance, deltaX, deltaY, deltaZ, direction, activationtype);
//				}
//				break;
//
//				case 4:	//door actor class
//				{
//					float zoneSizeX=0, zoneSizeY=0, zoneSizeZ=0;
//					bool locked = false;
//					bool hide = false;
//					long keyid=0;
//					float OpenTransX=0;
//					float OpenTransY=0;
//					float OpenTransZ=0;
//					float OpenTransSpeedX=0;
//					float OpenTransSpeedY=0;
//					float OpenTransSpeedZ=0;
//					bool destroykey = false;
//
//					pElem->QueryValueAttribute("zoneSizeX", &zoneSizeX);
//					pElem->QueryValueAttribute("zoneSizeY", &zoneSizeY);
//					pElem->QueryValueAttribute("zoneSizeZ", &zoneSizeZ);
//					pElem->QueryValueAttribute("locked", &locked);
//					pElem->QueryValueAttribute("keyid", &keyid);
//					pElem->QueryValueAttribute("hide", &hide);
//					pElem->QueryValueAttribute("destroykey", &destroykey);
//
//					pElem->QueryValueAttribute("OpenTransX", &OpenTransX);
//					pElem->QueryValueAttribute("OpenTransY", &OpenTransY);
//					pElem->QueryValueAttribute("OpenTransZ", &OpenTransZ);
//					pElem->QueryValueAttribute("OpenTransSpeedX", &OpenTransSpeedX);
//					pElem->QueryValueAttribute("OpenTransSpeedY", &OpenTransSpeedY);
//					pElem->QueryValueAttribute("OpenTransSpeedZ", &OpenTransSpeedZ);
//
//
//
//					act = new DoorActor(zoneSizeX, zoneSizeY, zoneSizeZ, locked, keyid, hide,
//											OpenTransX, OpenTransY, OpenTransZ,
//											OpenTransSpeedX, OpenTransSpeedY, OpenTransSpeedZ, destroykey);
//					passable = false;
//				}
//				break;
//
//				case 5:	//container actor class
//				{
//					float zoneSizeX=0, zoneSizeY=0, zoneSizeZ=0;
//					pElem->QueryValueAttribute("zonesizeX", &zoneSizeX);
//					pElem->QueryValueAttribute("zonesizeY", &zoneSizeY);
//					pElem->QueryValueAttribute("zonesizeZ", &zoneSizeZ);
//					int activationtype=1;
//					pElem->QueryValueAttribute("activationtype", &activationtype);
//					ContainerActor *tmpC = new ContainerActor(zoneSizeX, zoneSizeY, zoneSizeZ, activationtype);
//
//					// get the contained items
//					std::vector<ItemGroup> items;
//					TiXmlElement* pElemC=pElem->FirstChildElement();
//					for( pElemC; pElemC; pElemC=pElemC->NextSiblingElement())
//					{
//						// for each group of items
//						ItemGroup newGroup;
//						newGroup.lastSpawningTime = 0;
//						newGroup.RespawningTime = 300000; // default = 5min
//						newGroup.currpicked = -1;
//						pElemC->QueryValueAttribute("respawnTimeInMs", &newGroup.RespawningTime);
//
//						TiXmlElement* itemGroup=pElemC->FirstChildElement();
//						for( itemGroup; itemGroup; itemGroup=itemGroup->NextSiblingElement())
//						{
//							ItemGroupElement elem;
//							itemGroup->QueryValueAttribute("id", &elem.id);
//							itemGroup->QueryValueAttribute("number", &elem.number);
//							itemGroup->QueryValueAttribute("probability", &elem.probability);
//							newGroup.groupelements.push_back(elem);
//						}
//						if(newGroup.groupelements.size() > 0)
//							items.push_back(newGroup);
//					}
//					tmpC->SetLootList(items);
//
//					act = tmpC;
//				}
//				break;
//
//				case 6:	//up exit actor class
//				{
//					int direction=0;
//					float activationdistance;
//					pElem->QueryValueAttribute("activationdistance", &activationdistance);
//					pElem->QueryValueAttribute("direction", &direction);
//					int activationtype=1;
//					pElem->QueryValueAttribute("activationtype", &activationtype);
//					act = new UpExitActor(activationdistance, direction, activationtype);
//				}
//				break;
//
//				case 7:	//switch actor class
//				{
//					float activationdistance;
//					pElem->QueryValueAttribute("activationdistance", &activationdistance);
//					int activationtype=1;
//					pElem->QueryValueAttribute("activationtype", &activationtype);
//					act = new SwitchActor(activationdistance, activationtype);
//
//					sizeX=0.4f;
//					sizeY=3.0f;
//					sizeZ=0.4f;
//					offsetsizeY=3.5f;
//					collidable = false;
//				}
//				break;
//
//				case 8:	//area switch actor class
//				{
//					float zoneSizeX=0, zoneSizeY=0, zoneSizeZ=0;
//					long QuestToTriggerEnd = -1;
//					pElem->QueryValueAttribute("zonesizeX", &zoneSizeX);
//					pElem->QueryValueAttribute("zonesizeY", &zoneSizeY);
//					pElem->QueryValueAttribute("zonesizeZ", &zoneSizeZ);
//					pElem->QueryValueAttribute("QuestToTriggerEnd", &QuestToTriggerEnd);
//					act = new AreaSwitch(zoneSizeX, zoneSizeY, zoneSizeZ, QuestToTriggerEnd);
//				}
//				break;
//
//				case 9:	//floor switch actor class
//				{
//					float zoneSizeX=0, zoneSizeY=0, zoneSizeZ=0;
//					pElem->QueryValueAttribute("zonesizeX", &zoneSizeX);
//					pElem->QueryValueAttribute("zonesizeY", &zoneSizeY);
//					pElem->QueryValueAttribute("zonesizeZ", &zoneSizeZ);
//					int activationtype=1;
//					pElem->QueryValueAttribute("activationtype", &activationtype);
//					act = new FloorSwitch(zoneSizeX, zoneSizeY, zoneSizeZ, activationtype);
//				}
//				break;
//
//				case 10:	//lift actor class
//				{
//					bool autoattach = true;
//					pElem->QueryValueAttribute("autoattach", &autoattach);					
//
//					std::vector<PlayerScriptPart> scripts;
//					TiXmlNode* pNode2=pElem->FirstChild("scripts");
//					if(pNode2)
//					{
//						TiXmlElement*pElem2=pNode2->FirstChildElement();
//						for( pElem2; pElem2; pElem2=pElem2->NextSiblingElement())
//						{
//							PlayerScriptPart ps;
//							ps.ValueA = -1;
//							ps.ValueB = -1;
//							ps.ValueC = -1;
//							ps.Sound = -1;
//							ps.SoundNum = -1;
//							ps.Speed = -1;
//							ps.Animation = -1;
//							ps.Flag = true;
//
//							pElem2->QueryValueAttribute("type", &ps.Type);
//							pElem2->QueryValueAttribute("ValueA", &ps.ValueA);
//							pElem2->QueryValueAttribute("ValueB", &ps.ValueB);
//							pElem2->QueryValueAttribute("ValueC", &ps.ValueC);
//							pElem2->QueryValueAttribute("Speed", &ps.Speed);
//							pElem2->QueryValueAttribute("Sound", &ps.Sound);
//							pElem2->QueryValueAttribute("SoundNum", &ps.SoundNum);
//							pElem2->QueryValueAttribute("Animation", &ps.Animation);
//							pElem2->QueryValueAttribute("Flag", &ps.Flag);
//							scripts.push_back(ps);
//						}
//					}
//					act = new ScriptableActor(scripts, autoattach);
//				}
//				break;
//
//				case 11:	//hurt area class
//				{
//					float zoneSizeX=0, zoneSizeY=0, zoneSizeZ=0;
//					int lifetaken=5;
//					pElem->QueryValueAttribute("zonesizeX", &zoneSizeX);
//					pElem->QueryValueAttribute("zonesizeY", &zoneSizeY);
//					pElem->QueryValueAttribute("zonesizeZ", &zoneSizeZ);
//					pElem->QueryValueAttribute("lifetaken", &lifetaken);
//					act = new HurtArea(zoneSizeX, zoneSizeY, zoneSizeZ, lifetaken);
//				}
//				break;
//
//				case 12:	//NPC class
//				{
//					int npctype=1;
//					float activationdistance=10;//6;
//					pElem->QueryValueAttribute("activationdistance", &activationdistance);
//					pElem->QueryValueAttribute("NPCType", &npctype);
//					const char *namea = pElem->Attribute("Name");
//					std::string NameNPC = "NPC";
//					if(namea)
//						NameNPC = namea;
//
//
//					std::vector<PlayerScriptPart> scripts;
//					TiXmlNode* pNode2=pElem->FirstChild("scripts");
//					if(pNode2)
//					{
//						TiXmlElement*pElem2=pNode2->FirstChildElement();
//						for( pElem2; pElem2; pElem2=pElem2->NextSiblingElement())
//						{
//							PlayerScriptPart ps;
//							ps.ValueA = -1;
//							ps.ValueB = -1;
//							ps.ValueC = -1;
//							ps.Sound = -1;
//							ps.Speed = -1;
//							ps.SoundNum = -1;
//							ps.Animation = -1;
//							ps.Flag = true;
//
//							pElem2->QueryValueAttribute("type", &ps.Type);
//							pElem2->QueryValueAttribute("ValueA", &ps.ValueA);
//							pElem2->QueryValueAttribute("ValueB", &ps.ValueB);
//							pElem2->QueryValueAttribute("ValueC", &ps.ValueC);
//							pElem2->QueryValueAttribute("Speed", &ps.Speed);
//							pElem2->QueryValueAttribute("Sound", &ps.Sound);
//							pElem2->QueryValueAttribute("SoundNum", &ps.SoundNum);
//							pElem2->QueryValueAttribute("Animation", &ps.Animation);
//							pElem2->QueryValueAttribute("Flag", &ps.Flag);
//							scripts.push_back(ps);
//						}
//					}
//
//					DialogHandlerPtr dialogptr = DialogHandlerPtr();
//					#ifndef _LBANET_SERVER_SIDE_
//					dialogptr = LoadDialog(pElem->FirstChildElement("Dialog"), invH, qH, actH);
//					#endif
//
//					NPCActor *tmpact = new NPCActor(scripts, false, npctype, activationdistance, NameNPC, 
//													dialogptr);
//
//					if(npctype == 2)
//					{
//						TiXmlNode* itemGroup=pElem->FirstChild("items");
//						if(itemGroup)
//						{
//							std::map<long, TraderItem> items;
//							TiXmlElement*pElem2=itemGroup->FirstChildElement();
//							for( pElem2; pElem2; pElem2=pElem2->NextSiblingElement())
//							{
//								TraderItem itm;
//								itm.id = -1;
//								pElem2->QueryValueAttribute("id", &itm.id);
//								itm.condition = LoadCondition(pElem2->FirstChildElement("Condition"), invH, qH, actH);
//								 
//								items[itm.id] = itm;
//							}
//
//							tmpact->SetItems(items);
//						}
//					}
//
//					act = tmpact;
//				}
//				break;
//
//
//				case 13: //scripted zone actor class
//				{
//					float zoneSizeX=0, zoneSizeY=0, zoneSizeZ=0;
//					pElem->QueryValueAttribute("zonesizeX", &zoneSizeX);
//					pElem->QueryValueAttribute("zonesizeY", &zoneSizeY);
//					pElem->QueryValueAttribute("zonesizeZ", &zoneSizeZ);
//					int activationtype=1;
//					pElem->QueryValueAttribute("activationtype", &activationtype);
//
//					long neededitem=-1;
//					pElem->QueryValueAttribute("neededitem", &neededitem);
//					bool destroyitem = false;
//					pElem->QueryValueAttribute("destroyitem", &destroyitem);
//
//					const char *abortedmessage = pElem->Attribute("abortedmessage");
//					std::string abortedmessages;
//					if(abortedmessage)
//						abortedmessages = abortedmessage;
//
//
//					std::vector<PlayerScriptPart> scripts;
//					TiXmlNode* pNode2=pElem->FirstChild("scripts");
//					if(pNode2)
//					{
//						TiXmlElement*pElem2=pNode2->FirstChildElement();
//						for( pElem2; pElem2; pElem2=pElem2->NextSiblingElement())
//						{
//							PlayerScriptPart ps;
//							ps.ValueA = -1;
//							ps.ValueB = -1;
//							ps.ValueC = -1;
//							ps.Sound = -1;
//							ps.Speed = -1;
//							ps.SoundNum = -1;
//							ps.Animation = -1;
//							ps.Flag = true;
//							pElem2->QueryValueAttribute("type", &ps.Type);
//							pElem2->QueryValueAttribute("ValueA", &ps.ValueA);
//							pElem2->QueryValueAttribute("ValueB", &ps.ValueB);
//							pElem2->QueryValueAttribute("ValueC", &ps.ValueC);
//							pElem2->QueryValueAttribute("Speed", &ps.Speed);
//							pElem2->QueryValueAttribute("Sound", &ps.Sound);
//							pElem2->QueryValueAttribute("SoundNum", &ps.SoundNum);
//							pElem2->QueryValueAttribute("Animation", &ps.Animation);
//							pElem2->QueryValueAttribute("Flag", &ps.Flag);
//
//							const char *newMap = pElem2->Attribute("newMap");
//							if(newMap)
//								ps.NewMap = newMap;
//
//							const char *spawning = pElem2->Attribute("spawning");
//							if(spawning)
//								ps.Spawning = spawning;
//
//							scripts.push_back(ps);
//						}
//					}
//					act = new ScriptedZoneActor(zoneSizeX, zoneSizeY, zoneSizeZ, scripts, 
//												activationtype, neededitem, destroyitem, abortedmessages);
//				}
//				break;
//
//
//				case 14:	//mailbox class
//				{
//					float activationdistance;
//					int activationtype=1;
//					pElem->QueryValueAttribute("activationdistance", &activationdistance);
//					pElem->QueryValueAttribute("activationtype", &activationtype);
//					act = new MailboxActor(activationdistance, activationtype);
//				}
//				break;
//			}
//
//			// add common attributes
//			act->SetId(id);
//			act->SetPosition(posX, posY, posZ);
//			act->SetRotation((float)rotation);
//			act->SetSize(sizeX, sizeY, sizeZ);
//			act->SetOffsetSizeY(offsetsizeY);
//			act->SetPassable(passable);
//			act->SetDepthMask(depthmask);
//			act->SetMovable(movable);
//			act->SetCollidable(collidable);
//			act->SetActif(actif);
//			act->SetAllowFreeMove(allowfreemove);
//			
//			
//
//			act->SetRenderer(renderer);
//
//			act->SetType(type);
//			act->SetOutputSignal(outputsignal, stargets);
//			act->SetRendererType(renderertype, renderertarget);
//			act->SetAttachedSound(attachedsound);
//			act->SetSignaler(signaler);
//
//			// add it to the vector
//			vec[id] = act;
//		}
//	}
//
//#ifndef _LBANET_SERVER_SIDE_
//	LogHandler::getInstance()->LogToFile("Finished reading xml file for actors...");
//#endif

	return true;
}

