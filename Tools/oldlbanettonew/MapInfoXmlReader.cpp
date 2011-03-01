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
#include <math.h>
#include "Lba1ModelMapHandler.h"


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
		{
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


	// block: files
	{
		pElem=hRoot.FirstChild( "files" ).FirstChild().Element();
		for( pElem; pElem; pElem=pElem->NextSiblingElement())
		{
			res.Files[pElem->Attribute("name")] = pElem->Attribute("path");
		}

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

			{
				std::string nmnamem = ex.NewMap;
				if(nmnamem.find("Map") == 0)
				{
					nmnamem = nmnamem.substr(3);
					std::string numstr = nmnamem.substr(0, nmnamem.find("_"));
					std::string rest = nmnamem.substr(nmnamem.find("_"));
					int num = atoi(numstr.c_str());
					std::stringstream mapnamess;
					mapnamess<<"Map";
					if(num < 10)
						mapnamess<<"0";
					if(num < 100)
						mapnamess<<"0";
					mapnamess<<num<<rest;
					ex.NewMap = mapnamess.str();
				}
			}

			pElem->QueryFloatAttribute("TopRightX", &ex.TopRightX);
			pElem->QueryFloatAttribute("TopRightY", &ex.TopRightY);
			pElem->QueryFloatAttribute("TopRightZ", &ex.TopRightZ);

			pElem->QueryFloatAttribute("BottomLeftX", &ex.BottomLeftX);
			pElem->QueryFloatAttribute("BottomLeftY", &ex.BottomLeftY);
			pElem->QueryFloatAttribute("BottomLeftZ", &ex.BottomLeftZ);

			ex.SizeX = floor(ex.TopRightX + 0.5f) - floor(ex.BottomLeftX + 0.5f);
			ex.SizeY = ((floor(ex.TopRightY + 0.5f) - floor(ex.BottomLeftY + 0.5f)) / 2) + 1;
			ex.SizeZ = floor(ex.TopRightZ + 0.5f) - floor(ex.BottomLeftZ + 0.5f);

			ex.PosX = floor(ex.BottomLeftX + 0.5f) + (ex.SizeX / 2);
			ex.PosY = floor(ex.BottomLeftY + 0.5f);
			ex.PosZ = floor(ex.BottomLeftZ + 0.5f) + (ex.SizeZ / 2);

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
bool MapInfoXmlReader::LoadActors(const std::string &Filename,
							std::map<long, boost::shared_ptr<TriggerBase> >	&triggers,
							std::map<Ice::Long, boost::shared_ptr<ActorHandler> >	&Actors,
							long &triggerid, long &actorid, long textoffset)
{
	TiXmlDocument doc(Filename);
	if (!doc.LoadFile())
		return false;


	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;

	// block: actors attributes
	{
		pElem=hDoc.FirstChildElement().Element();

		// should always have a valid root but handle gracefully if it does
		if (!pElem)
			return false;


		// for each actors
		pElem=pElem->FirstChildElement();
		for( pElem; pElem; pElem=pElem->NextSiblingElement())
		{
			long id=0, type=0;
			float posX=0, posY=0, posZ=0;
			float sizeX=0, sizeY=0, sizeZ=0;
			float offsetsizeY=0;
			int rotation=0;
			bool passable = true;
			bool depthmask = true;
			bool movable = false;
			bool collidable = true;
			bool actif = false;
			bool allowfreemove = false;

			long renderertype=-1;
			std::vector<long> renderertarget;
			//D3ObjectRenderer * renderer = NULL;
			long outputsignal=-1;
			long attachedsound=-1;
			std::vector<long> stargets;
			const char * targetsstring = pElem->Attribute("signaltargets");
			if(targetsstring)
			{
				std::vector<std::string> tokens;
				StringTokenize(targetsstring, tokens, ",");
				for(size_t i=0; i<tokens.size(); ++i)
					stargets.push_back(atol(tokens[i].c_str()));
			}

			const char * rendertargetsstring = pElem->Attribute("renderertarget");
			if(rendertargetsstring)
			{
				std::vector<std::string> tokens;
				StringTokenize(rendertargetsstring, tokens, ",");
				for(size_t i=0; i<tokens.size(); ++i)
					renderertarget.push_back(atol(tokens[i].c_str()));
			}



			pElem->QueryValueAttribute("id", &id);
			std::stringstream strss;
			strss<<"Start reading actor id "<<id;



			pElem->QueryValueAttribute("type", &type);
			pElem->QueryFloatAttribute("posX", &posX);
			pElem->QueryFloatAttribute("posY", &posY);
			pElem->QueryFloatAttribute("posZ", &posZ);
			pElem->QueryFloatAttribute("sizeX", &sizeX);
			pElem->QueryFloatAttribute("sizeY", &sizeY);
			pElem->QueryFloatAttribute("sizeZ", &sizeZ);
			pElem->QueryFloatAttribute("offsetsizeY", &offsetsizeY);
			pElem->QueryIntAttribute("rotation", &rotation);
			pElem->QueryValueAttribute("passable", &passable);
			pElem->QueryValueAttribute("depthmask", &depthmask);
			pElem->QueryValueAttribute("movable", &movable);
			pElem->QueryValueAttribute("outputsignal", &outputsignal);
			pElem->QueryValueAttribute("attachedsound", &attachedsound);
			pElem->QueryValueAttribute("collidable", &collidable);
			pElem->QueryValueAttribute("actif", &actif);
			pElem->QueryValueAttribute("allowfreemove", &allowfreemove);


			if(pElem->QueryValueAttribute("renderertype", &renderertype) == TIXML_SUCCESS)
			{
				if(renderertype == 1)
					continue;
				if(renderertype == 2)
					continue;
			}


			//Actor * act;
			switch(type)
			{
				case 1:	//text actor class
				{
					long textid=0;
					float activationdistance;
					pElem->QueryValueAttribute("activationdistance", &activationdistance);
					pElem->QueryValueAttribute("textid", &textid);
					int activationtype=1;
					pElem->QueryValueAttribute("activationtype", &activationtype);
					textid+=textoffset;

					TriggerInfo triinfo;
					triinfo.id = triggerid++;
					triinfo.CheckPlayers = true;
					triinfo.CheckMovableObjects = false;
					triinfo.CheckNpcs = false;
					std::stringstream triname;
					triname<<"TextTri_"<<triinfo.id;
					triinfo.name = triname.str();
					boost::shared_ptr<TriggerBase> newtri(new ActivationTrigger(triinfo, activationdistance/2, "Normal", ""));
					newtri->SetPosition(posX, posY, posZ);

					DisplayTextAction * act = new DisplayTextAction();
					act->SetTextId(textid);
					newtri->SetAction1(ActionBasePtr(act));

					triggers[newtri->GetId()] = newtri;
				}
				break;
				case 2:	//ladder actor class
				{
					float deltaX=0, deltaY=0, deltaZ=0;
					int direction=0;
					float activationdistance;
					pElem->QueryValueAttribute("activationdistance", &activationdistance);
					pElem->QueryValueAttribute("deltaX", &deltaX);
					pElem->QueryValueAttribute("deltaY", &deltaY);
					pElem->QueryValueAttribute("deltaZ", &deltaZ);
					pElem->QueryValueAttribute("direction", &direction);
					int activationtype=1;
					pElem->QueryValueAttribute("activationtype", &activationtype);

					TriggerInfo triinfo;
					triinfo.id = triggerid++;
					triinfo.CheckPlayers = true;
					triinfo.CheckMovableObjects = false;
					triinfo.CheckNpcs = false;
					std::stringstream triname;
					triname<<"LadderTri_"<<triinfo.id;
					triinfo.name = triname.str();
					boost::shared_ptr<TriggerBase> newtri(new ActivationTrigger(triinfo, activationdistance/2, "Normal", ""));
					newtri->SetPosition(posX, posY, posZ);

					GoUpLadderScript * goupl = new GoUpLadderScript();
					goupl->SetLadderDirection(direction);
					goupl->SetLadderHeight(deltaY);
					goupl->SetLadderPositionX(posX);
					goupl->SetLadderPositionY(posY);
					goupl->SetLadderPositionZ(posZ);

					ClientScriptAction * act = new ClientScriptAction();
					act->SetScript(ClientScriptBasePtr(goupl));
					newtri->SetAction1(ActionBasePtr(act));

					triggers[newtri->GetId()] = newtri;
				}
				break;
				case 3:	//exit actor class
				{
					float deltaX=0, deltaY=0, deltaZ=0;
					int direction=0;
					float activationdistance;
					pElem->QueryValueAttribute("activationdistance", &activationdistance);
					pElem->QueryValueAttribute("deltaX", &deltaX);
					pElem->QueryValueAttribute("deltaY", &deltaY);
					pElem->QueryValueAttribute("deltaZ", &deltaZ);
					pElem->QueryValueAttribute("direction", &direction);
					int activationtype=1;
					pElem->QueryValueAttribute("activationtype", &activationtype);

					TriggerInfo triinfo;
					triinfo.id = triggerid++;
					triinfo.CheckPlayers = true;
					triinfo.CheckMovableObjects = false;
					triinfo.CheckNpcs = false;
					std::stringstream triname;
					triname<<"ExitDownTri_"<<triinfo.id;
					triinfo.name = triname.str();
					boost::shared_ptr<TriggerBase> newtri(new ActivationTrigger(triinfo, activationdistance/2, "Normal", ""));
					newtri->SetPosition(posX, posY, posZ);

					TakeExitDownScript * goupl = new TakeExitDownScript();
					goupl->SetExitDirection(direction);
					goupl->SetExitPositionX(posX);
					goupl->SetExitPositionY(posY);
					goupl->SetExitPositionZ(posZ);

					ClientScriptAction * act = new ClientScriptAction();
					act->SetScript(ClientScriptBasePtr(goupl));
					newtri->SetAction1(ActionBasePtr(act));

					triggers[newtri->GetId()] = newtri;
				}
				break;

				case 4:	//door actor class
				{
					float zoneSizeX=0, zoneSizeY=0, zoneSizeZ=0;
					bool locked = false;
					bool hide = false;
					long keyid=0;
					float OpenTransX=0;
					float OpenTransY=0;
					float OpenTransZ=0;
					float OpenTransSpeedX=0;
					float OpenTransSpeedY=0;
					float OpenTransSpeedZ=0;
					bool destroykey = false;

					pElem->QueryValueAttribute("zoneSizeX", &zoneSizeX);
					pElem->QueryValueAttribute("zoneSizeY", &zoneSizeY);
					pElem->QueryValueAttribute("zoneSizeZ", &zoneSizeZ);
					pElem->QueryValueAttribute("locked", &locked);
					pElem->QueryValueAttribute("keyid", &keyid);
					pElem->QueryValueAttribute("hide", &hide);
					pElem->QueryValueAttribute("destroykey", &destroykey);

					pElem->QueryValueAttribute("OpenTransX", &OpenTransX);
					pElem->QueryValueAttribute("OpenTransY", &OpenTransY);
					pElem->QueryValueAttribute("OpenTransZ", &OpenTransZ);
					pElem->QueryValueAttribute("OpenTransSpeedX", &OpenTransSpeedX);
					pElem->QueryValueAttribute("OpenTransSpeedY", &OpenTransSpeedY);
					pElem->QueryValueAttribute("OpenTransSpeedZ", &OpenTransSpeedZ);

					std::stringstream sprnames;
					sprnames<<"sprite";
					if(renderertarget[0] < 10)
						sprnames<<"0";
					if(renderertarget[0] < 100)
						sprnames<<"0";
					sprnames<<renderertarget[0]<<".osgb";

					ActorObjectInfo actorinfo(actorid++);
					actorinfo.SetRenderType(1);
					actorinfo.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/"+sprnames.str();
					actorinfo.DisplayDesc.UseLight = true;
					actorinfo.DisplayDesc.CastShadow = false;
					actorinfo.SetModelState(1);
					actorinfo.PhysicDesc.Pos.X = posX;
					actorinfo.PhysicDesc.Pos.Y = posY;
					actorinfo.PhysicDesc.Pos.Z = posZ;
					actorinfo.PhysicDesc.Pos.Rotation = 0;
					actorinfo.SetPhysicalActorType(2);
					actorinfo.SetPhysicalShape(2);
					actorinfo.PhysicDesc.Collidable = true;
					actorinfo.PhysicDesc.SizeX = sizeX;
					actorinfo.PhysicDesc.SizeY = sizeY;
					actorinfo.PhysicDesc.SizeZ = sizeZ;
					boost::shared_ptr<ActorHandler> act(new DoorHandler(actorinfo, 0, 0,
															OpenTransX+OpenTransY+OpenTransZ, 
															OpenTransSpeedX+OpenTransSpeedY+OpenTransSpeedZ, true));

					Actors[act->GetId()] = act;

					TriggerInfo triinfo;
					triinfo.id = triggerid++;
					triinfo.CheckPlayers = true;
					triinfo.CheckMovableObjects = false;
					triinfo.CheckNpcs = false;
					std::stringstream triname;
					triname<<"DoorTri_"<<triinfo.id;
					triinfo.name = triname.str();
					boost::shared_ptr<TriggerBase> newtri(new ZoneTrigger(triinfo, zoneSizeX, zoneSizeY, zoneSizeZ, true));
					newtri->SetPosition(posX, posY, posZ);

					OpenDoorAction * actio = new OpenDoorAction();
					actio->SetActorId(act->GetId());
					newtri->SetAction1(ActionBasePtr(actio));

					triggers[newtri->GetId()] = newtri;
				}
				break;

				case 5:	//container actor class
				{
					float zoneSizeX=0, zoneSizeY=0, zoneSizeZ=0;
					pElem->QueryValueAttribute("zonesizeX", &zoneSizeX);
					pElem->QueryValueAttribute("zonesizeY", &zoneSizeY);
					pElem->QueryValueAttribute("zonesizeZ", &zoneSizeZ);
					int activationtype=1;
					pElem->QueryValueAttribute("activationtype", &activationtype);

					TriggerInfo triinfo;
					triinfo.id = triggerid++;
					triinfo.CheckPlayers = true;
					triinfo.CheckMovableObjects = false;
					triinfo.CheckNpcs = false;
					std::stringstream triname;
					triname<<"ContainerTri_"<<triinfo.id;
					triinfo.name = triname.str();
					boost::shared_ptr<ZoneActionTrigger> newtri(new ZoneActionTrigger(triinfo, zoneSizeX, zoneSizeY, zoneSizeZ, "Normal", ""));
					newtri->SetPosition(posX, posY, posZ);
					newtri->SetPlayAnimation(true);

					OpenContainerAction * act = new OpenContainerAction();
					act->SetTimeToReset(300);
					newtri->SetAction1(ActionBasePtr(act));

					triggers[newtri->GetId()] = newtri;


					// get the contained items
					TiXmlElement* pElemC=pElem->FirstChildElement();
					int itgroupidx = 1;
					for( pElemC; pElemC; pElemC=pElemC->NextSiblingElement(), ++itgroupidx)
					{
						TiXmlElement* itemGroup=pElemC->FirstChildElement();
						for( itemGroup; itemGroup; itemGroup=itemGroup->NextSiblingElement())
						{
							long itid;
							int itnumber;
							float itproba;

							itemGroup->QueryValueAttribute("id", &itid);
							itemGroup->QueryValueAttribute("number", &itnumber);
							itemGroup->QueryValueAttribute("probability", &itproba);

							act->AddItem(ContainerItemGroupElement(itid, itnumber, itnumber, itproba, itgroupidx));
						}
					}
					if(act->GetItems().size() == 0)
					{
						act->AddItem(ContainerItemGroupElement(1, 1, 1, 0.3f, itgroupidx));
						act->AddItem(ContainerItemGroupElement(2, 1, 1, 0.3f, itgroupidx));
						act->AddItem(ContainerItemGroupElement(8, 2, 2, 0.35f, itgroupidx));
						act->AddItem(ContainerItemGroupElement(3, 1, 1, 0.05f, itgroupidx));
					}
				}
				break;

				case 6:	//up exit actor class
				{
					int direction=0;
					float activationdistance;
					pElem->QueryValueAttribute("activationdistance", &activationdistance);
					pElem->QueryValueAttribute("direction", &direction);
					int activationtype=1;
					pElem->QueryValueAttribute("activationtype", &activationtype);

					TriggerInfo triinfo;
					triinfo.id = triggerid++;
					triinfo.CheckPlayers = true;
					triinfo.CheckMovableObjects = false;
					triinfo.CheckNpcs = false;
					std::stringstream triname;
					triname<<"ExitUpTri_"<<triinfo.id;
					triinfo.name = triname.str();
					boost::shared_ptr<TriggerBase> newtri(new ActivationTrigger(triinfo, activationdistance/2, "Normal", ""));
					newtri->SetPosition(posX, posY, posZ);

					TakeExitUpScript * goupl = new TakeExitUpScript();
					goupl->SetExitDirection(direction);
					goupl->SetExitPositionX(posX);
					goupl->SetExitPositionY(posY);
					goupl->SetExitPositionZ(posZ);

					ClientScriptAction * act = new ClientScriptAction();
					act->SetScript(ClientScriptBasePtr(goupl));
					newtri->SetAction1(ActionBasePtr(act));

					triggers[newtri->GetId()] = newtri;
				}
				break;

				case 7:	//switch actor class
				{
					float activationdistance;
					pElem->QueryValueAttribute("activationdistance", &activationdistance);
					int activationtype=1;
					pElem->QueryValueAttribute("activationtype", &activationtype);
					//act = new SwitchActor(activationdistance, activationtype);


					std::stringstream sprnames;
					sprnames<<"sprite";
					if(renderertarget[0] < 10)
						sprnames<<"0";
					if(renderertarget[0] < 100)
						sprnames<<"0";
					sprnames<<renderertarget[0]<<".osgb";

					ActorObjectInfo actorinfo(actorid++);
					actorinfo.SetRenderType(1);
					actorinfo.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/"+sprnames.str();
					actorinfo.DisplayDesc.UseLight = true;
					actorinfo.DisplayDesc.CastShadow = false;
					actorinfo.DisplayDesc.TransY=-3.5f;
					actorinfo.SetModelState(1);
					actorinfo.PhysicDesc.Pos.X = posX;
					actorinfo.PhysicDesc.Pos.Y = posY+3.5f;
					actorinfo.PhysicDesc.Pos.Z = posZ;
					actorinfo.PhysicDesc.Pos.Rotation = 0;
					actorinfo.SetPhysicalActorType(1);
					actorinfo.SetPhysicalShape(2);
					actorinfo.PhysicDesc.Collidable = false;
					actorinfo.PhysicDesc.SizeX = 0.4f;
					actorinfo.PhysicDesc.SizeY = 3.0f;
					actorinfo.PhysicDesc.SizeZ = 0.4f;
					boost::shared_ptr<ActorHandler> act(new ActorHandler(actorinfo));

					Actors[act->GetId()] = act;


					TriggerInfo triinfo;
					triinfo.id = triggerid++;
					triinfo.CheckPlayers = true;
					triinfo.CheckMovableObjects = false;
					triinfo.CheckNpcs = false;
					std::stringstream triname;
					triname<<"SwitchTri_"<<triinfo.id;
					triinfo.name = triname.str();
					boost::shared_ptr<ActivationTrigger> newtri(new ActivationTrigger(triinfo, activationdistance/2, "Normal", ""));
					newtri->SetPosition(posX, posY, posZ);
					newtri->SetPlayAnimation(true);

					SwitchAction * action = new SwitchAction();
					action->SetActorId(act->GetId());

					if(renderertarget.size() > 1)
					{
						std::stringstream sprnames2;
						sprnames2<<"sprite";
						if(renderertarget[1] < 10)
							sprnames2<<"0";
						if(renderertarget[1] < 100)
							sprnames2<<"0";
						sprnames2<<renderertarget[1]<<".osgb";
						action->SetSwitchModel("Worlds/Lba1Original/Sprites/"+sprnames2.str());
					}

					newtri->SetAction1(ActionBasePtr(action));

					triggers[newtri->GetId()] = newtri;
				}
				break;

				case 8:	//area switch actor class
				{
					//float zoneSizeX=0, zoneSizeY=0, zoneSizeZ=0;
					//long QuestToTriggerEnd = -1;
					//pElem->QueryValueAttribute("zonesizeX", &zoneSizeX);
					//pElem->QueryValueAttribute("zonesizeY", &zoneSizeY);
					//pElem->QueryValueAttribute("zonesizeZ", &zoneSizeZ);
					//pElem->QueryValueAttribute("QuestToTriggerEnd", &QuestToTriggerEnd);
					//act = new AreaSwitch(zoneSizeX, zoneSizeY, zoneSizeZ, QuestToTriggerEnd);
				}
				break;

				case 9:	//floor switch actor class
				{
					float zoneSizeX=0, zoneSizeY=0, zoneSizeZ=0;
					pElem->QueryValueAttribute("zonesizeX", &zoneSizeX);
					pElem->QueryValueAttribute("zonesizeY", &zoneSizeY);
					pElem->QueryValueAttribute("zonesizeZ", &zoneSizeZ);
					int activationtype=1;
					pElem->QueryValueAttribute("activationtype", &activationtype);


					TriggerInfo triinfo;
					triinfo.id = triggerid++;
					triinfo.CheckPlayers = true;
					triinfo.CheckMovableObjects = false;
					triinfo.CheckNpcs = false;
					std::stringstream triname;
					triname<<"FloorSwitchTri_"<<triinfo.id;
					triinfo.name = triname.str();
					boost::shared_ptr<ZoneActionTrigger> newtri(new ZoneActionTrigger(triinfo, zoneSizeX, zoneSizeY, zoneSizeZ, "Normal", ""));
					newtri->SetPosition(posX, posY, posZ);
					newtri->SetPlayAnimation(true);

					SendSignalAction * act = new SendSignalAction();
					act->SetSignal(outputsignal);
					act->SetActorId(-1);
					newtri->SetAction1(ActionBasePtr(act));

					triggers[newtri->GetId()] = newtri;
				}
				break;

				case 10:	//lift actor class
				{

					std::stringstream sprnames;
					sprnames<<"sprite";
					if(renderertarget[0] < 10)
						sprnames<<"0";
					if(renderertarget[0] < 100)
						sprnames<<"0";
					sprnames<<renderertarget[0]<<".osgb";

					ActorObjectInfo actorinfo(actorid++);
					actorinfo.SetRenderType(1);
					actorinfo.DisplayDesc.ModelName = "Worlds/Lba1Original/Sprites/"+sprnames.str();
					actorinfo.DisplayDesc.UseLight = true;
					actorinfo.DisplayDesc.CastShadow = false;
					actorinfo.SetModelState(1);
					actorinfo.PhysicDesc.Pos.X = posX;
					actorinfo.PhysicDesc.Pos.Y = posY;
					actorinfo.PhysicDesc.Pos.Z = posZ;
					actorinfo.PhysicDesc.Pos.Rotation = 0;
					actorinfo.SetPhysicalActorType(2);
					actorinfo.SetPhysicalShape(2);
					actorinfo.PhysicDesc.Collidable = true;
					actorinfo.PhysicDesc.SizeX = sizeX;
					actorinfo.PhysicDesc.SizeY = sizeY;
					actorinfo.PhysicDesc.SizeZ = sizeZ;
					boost::shared_ptr<ActorHandler> act(new ActorHandler(actorinfo));

					Actors[act->GetId()] = act;



					//bool autoattach = true;
					//pElem->QueryValueAttribute("autoattach", &autoattach);					

					//std::vector<PlayerScriptPart> scripts;
					//TiXmlNode* pNode2=pElem->FirstChild("scripts");
					//if(pNode2)
					//{
					//	TiXmlElement*pElem2=pNode2->FirstChildElement();
					//	for( pElem2; pElem2; pElem2=pElem2->NextSiblingElement())
					//	{
					//		PlayerScriptPart ps;
					//		ps.ValueA = -1;
					//		ps.ValueB = -1;
					//		ps.ValueC = -1;
					//		ps.Sound = -1;
					//		ps.SoundNum = -1;
					//		ps.Speed = -1;
					//		ps.Animation = -1;
					//		ps.Flag = true;

					//		pElem2->QueryValueAttribute("type", &ps.Type);
					//		pElem2->QueryValueAttribute("ValueA", &ps.ValueA);
					//		pElem2->QueryValueAttribute("ValueB", &ps.ValueB);
					//		pElem2->QueryValueAttribute("ValueC", &ps.ValueC);
					//		pElem2->QueryValueAttribute("Speed", &ps.Speed);
					//		pElem2->QueryValueAttribute("Sound", &ps.Sound);
					//		pElem2->QueryValueAttribute("SoundNum", &ps.SoundNum);
					//		pElem2->QueryValueAttribute("Animation", &ps.Animation);
					//		pElem2->QueryValueAttribute("Flag", &ps.Flag);
					//		scripts.push_back(ps);
					//	}
					//}
					//act = new ScriptableActor(scripts, autoattach);
				}
				break;

				case 11:	//hurt area class
				{
					float zoneSizeX=0, zoneSizeY=0, zoneSizeZ=0;
					int lifetaken=5;
					pElem->QueryValueAttribute("zonesizeX", &zoneSizeX);
					pElem->QueryValueAttribute("zonesizeY", &zoneSizeY);
					pElem->QueryValueAttribute("zonesizeZ", &zoneSizeZ);
					pElem->QueryValueAttribute("lifetaken", &lifetaken);

					TriggerInfo triinfo;
					triinfo.id = triggerid++;
					triinfo.CheckPlayers = true;
					triinfo.CheckMovableObjects = false;
					triinfo.CheckNpcs = false;
					std::stringstream triname;
					triname<<"HurtTri_"<<triinfo.id;
					triinfo.name = triname.str();
					boost::shared_ptr<ZoneTrigger> newtri(new ZoneTrigger(triinfo, zoneSizeX, zoneSizeY, zoneSizeZ, true));
					newtri->SetPosition(posX, posY, posZ);

					HurtAction * act = new HurtAction();
					act->HurtLifeOrMana(true);
					act->SetHurtValue((float)lifetaken);
					newtri->SetAction1(ActionBasePtr(act));

					triggers[newtri->GetId()] = newtri;
				}
				break;

				case 12:	//NPC class
				{
					int npctype=1;
					float activationdistance=10;//6;
					pElem->QueryValueAttribute("activationdistance", &activationdistance);
					pElem->QueryValueAttribute("NPCType", &npctype);
					const char *namea = pElem->Attribute("Name");
					std::string NameNPC = "";
					if(namea)
						NameNPC = namea;


					bool mfound = false;
					std::string ModelName;
					std::string Outfit;
					std::string Weapon;
					std::string Mode;
					std::map<std::string, ModelData> &models = Lba1ModelMapHandler::getInstance()->GetData();
					std::map<std::string, ModelData>::iterator itm = models.begin();
					std::map<std::string, ModelData>::iterator endm = models.end();
					for(; itm != endm && !mfound; ++itm)
					{
						std::map<std::string, OutfitData>::iterator itm2 = itm->second.outfits.begin();
						std::map<std::string, OutfitData>::iterator endm2 = itm->second.outfits.end();
						for(; itm2 != endm2 && !mfound; ++itm2)
						{
							std::map<std::string, WeaponData>::iterator itm3 = itm2->second.weapons.begin();
							std::map<std::string, WeaponData>::iterator endm3 = itm2->second.weapons.end();
							for(; itm3 != endm3 && !mfound; ++itm3)
							{
								std::map<std::string, ModeData>::iterator itm4 = itm3->second.modes.begin();
								std::map<std::string, ModeData>::iterator endm4 = itm3->second.modes.end();
								for(; itm4 != endm4 && !mfound; ++itm4)
								{
									if(itm4->second.modelnumber == renderertarget[0] &&
											itm4->second.bodynumber == renderertarget[1])
									{
										mfound = true;
										ModelName = itm->first;
										Outfit = itm2->first;
										Weapon = itm3->first;
										Mode = itm4->first;
									}
								}							
							}						
						}		
					}
					

					// add map actor
					ActorObjectInfo actorinfo(actorid++);
					actorinfo.SetRenderType(3);
					actorinfo.DisplayDesc.ModelName = ModelName;
					actorinfo.DisplayDesc.Outfit = Outfit;
					actorinfo.DisplayDesc.Weapon = Weapon;
					actorinfo.DisplayDesc.Mode = Mode;
					actorinfo.DisplayDesc.UseLight = true;
					actorinfo.DisplayDesc.CastShadow = true;
					actorinfo.SetModelState(1);
					actorinfo.PhysicDesc.Pos.X = posX;
					actorinfo.PhysicDesc.Pos.Y = posY;
					actorinfo.PhysicDesc.Pos.Z = posZ;
					actorinfo.PhysicDesc.Pos.Rotation = (float)rotation;
					actorinfo.SetPhysicalActorType(2);
					actorinfo.SetPhysicalShape(2);
					actorinfo.PhysicDesc.Collidable = true;

					int resWeaponType;
					ModelSize size;
					int res = Lba1ModelMapHandler::getInstance()-> GetModelExtraInfo(ModelName,
																	Outfit,	Weapon,	Mode, resWeaponType, size);
					actorinfo.PhysicDesc.SizeX = size.X;
					actorinfo.PhysicDesc.SizeY = size.Y;
					actorinfo.PhysicDesc.SizeZ = size.Z;

					actorinfo.ExtraInfo.Name = NameNPC;
					boost::shared_ptr<ActorHandler> act(new NPCHandler(actorinfo));
					Actors[act->GetId()] = act;


					//std::vector<PlayerScriptPart> scripts;
					//TiXmlNode* pNode2=pElem->FirstChild("scripts");
					//if(pNode2)
					//{
					//	TiXmlElement*pElem2=pNode2->FirstChildElement();
					//	for( pElem2; pElem2; pElem2=pElem2->NextSiblingElement())
					//	{
					//		PlayerScriptPart ps;
					//		ps.ValueA = -1;
					//		ps.ValueB = -1;
					//		ps.ValueC = -1;
					//		ps.Sound = -1;
					//		ps.Speed = -1;
					//		ps.SoundNum = -1;
					//		ps.Animation = -1;
					//		ps.Flag = true;

					//		pElem2->QueryValueAttribute("type", &ps.Type);
					//		pElem2->QueryValueAttribute("ValueA", &ps.ValueA);
					//		pElem2->QueryValueAttribute("ValueB", &ps.ValueB);
					//		pElem2->QueryValueAttribute("ValueC", &ps.ValueC);
					//		pElem2->QueryValueAttribute("Speed", &ps.Speed);
					//		pElem2->QueryValueAttribute("Sound", &ps.Sound);
					//		pElem2->QueryValueAttribute("SoundNum", &ps.SoundNum);
					//		pElem2->QueryValueAttribute("Animation", &ps.Animation);
					//		pElem2->QueryValueAttribute("Flag", &ps.Flag);
					//		scripts.push_back(ps);
					//	}
					//}

					//DialogHandlerPtr dialogptr = DialogHandlerPtr();
					//#ifndef _LBANET_SERVER_SIDE_
					//dialogptr = LoadDialog(pElem->FirstChildElement("Dialog"), invH, qH, actH);
					//#endif

					//NPCActor *tmpact = new NPCActor(scripts, false, npctype, activationdistance, NameNPC, 
					//								dialogptr);

					//if(npctype == 2)
					//{
					//	TiXmlNode* itemGroup=pElem->FirstChild("items");
					//	if(itemGroup)
					//	{
					//		std::map<long, TraderItem> items;
					//		TiXmlElement*pElem2=itemGroup->FirstChildElement();
					//		for( pElem2; pElem2; pElem2=pElem2->NextSiblingElement())
					//		{
					//			TraderItem itm;
					//			itm.id = -1;
					//			pElem2->QueryValueAttribute("id", &itm.id);
					//			itm.condition = LoadCondition(pElem2->FirstChildElement("Condition"), invH, qH, actH);
					//			 
					//			items[itm.id] = itm;
					//		}

					//		tmpact->SetItems(items);
					//	}
					//}

					//act = tmpact;
				}
				break;


				case 13: //scripted zone actor class
				{
					//float zoneSizeX=0, zoneSizeY=0, zoneSizeZ=0;
					//pElem->QueryValueAttribute("zonesizeX", &zoneSizeX);
					//pElem->QueryValueAttribute("zonesizeY", &zoneSizeY);
					//pElem->QueryValueAttribute("zonesizeZ", &zoneSizeZ);
					//int activationtype=1;
					//pElem->QueryValueAttribute("activationtype", &activationtype);

					//long neededitem=-1;
					//pElem->QueryValueAttribute("neededitem", &neededitem);
					//bool destroyitem = false;
					//pElem->QueryValueAttribute("destroyitem", &destroyitem);

					//const char *abortedmessage = pElem->Attribute("abortedmessage");
					//std::string abortedmessages;
					//if(abortedmessage)
					//	abortedmessages = abortedmessage;


					//std::vector<PlayerScriptPart> scripts;
					//TiXmlNode* pNode2=pElem->FirstChild("scripts");
					//if(pNode2)
					//{
					//	TiXmlElement*pElem2=pNode2->FirstChildElement();
					//	for( pElem2; pElem2; pElem2=pElem2->NextSiblingElement())
					//	{
					//		PlayerScriptPart ps;
					//		ps.ValueA = -1;
					//		ps.ValueB = -1;
					//		ps.ValueC = -1;
					//		ps.Sound = -1;
					//		ps.Speed = -1;
					//		ps.SoundNum = -1;
					//		ps.Animation = -1;
					//		ps.Flag = true;
					//		pElem2->QueryValueAttribute("type", &ps.Type);
					//		pElem2->QueryValueAttribute("ValueA", &ps.ValueA);
					//		pElem2->QueryValueAttribute("ValueB", &ps.ValueB);
					//		pElem2->QueryValueAttribute("ValueC", &ps.ValueC);
					//		pElem2->QueryValueAttribute("Speed", &ps.Speed);
					//		pElem2->QueryValueAttribute("Sound", &ps.Sound);
					//		pElem2->QueryValueAttribute("SoundNum", &ps.SoundNum);
					//		pElem2->QueryValueAttribute("Animation", &ps.Animation);
					//		pElem2->QueryValueAttribute("Flag", &ps.Flag);

					//		const char *newMap = pElem2->Attribute("newMap");
					//		if(newMap)
					//			ps.NewMap = newMap;

					//		const char *spawning = pElem2->Attribute("spawning");
					//		if(spawning)
					//			ps.Spawning = spawning;

					//		scripts.push_back(ps);
					//	}
					//}
					//act = new ScriptedZoneActor(zoneSizeX, zoneSizeY, zoneSizeZ, scripts, 
					//							activationtype, neededitem, destroyitem, abortedmessages);
				}
				break;


				case 14:	//mailbox class
				{
					//float activationdistance;
					//int activationtype=1;
					//pElem->QueryValueAttribute("activationdistance", &activationdistance);
					//pElem->QueryValueAttribute("activationtype", &activationtype);
					//act = new MailboxActor(activationdistance, activationtype);
				}
				break;
			}
		}
	}


	return true;
}

