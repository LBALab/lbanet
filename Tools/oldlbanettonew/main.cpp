/*
------------------------[ Lbanet Tool ]-------------------------
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
#include "MapInfoXmlWriter.h"

#include <boost/shared_ptr.hpp>
#include <LbaTypes.h>
#include "Triggers.h"
#include "ActorHandler.h"
#include "Spawn.h"

#include <fstream>
#include <sstream>
#include <math.h>


int main( int argc, char **argv )
{
	WorldInfo winfo;
	MapInfoXmlReader::LoadWorld("Data/Lba1Original.xml", winfo);
	MapInfoXmlWriter::SaveWorld("Data/Worlds/"+winfo.Name+"/WorldDescription.xml", winfo);

	std::map<std::string, long>	textoffsets;
	std::ifstream fileoff("textoffsets.txt");
	if(fileoff.is_open())
	{
		while(!fileoff.eof())
		{
			std::string tmp1;
			long tmp2;
			fileoff>>tmp1;
			fileoff>>tmp2;
			textoffsets[tmp1] = tmp2;
		}
	}


	// modify spawning and exit to fit new style
	{
		std::map<std::string, MapInfo>::iterator itm = winfo.Maps.begin();
		std::map<std::string, MapInfo>::iterator endm = winfo.Maps.end();
		for(; itm != endm; ++itm)
		{
			std::map<std::string, ExitInfo> &Exits = itm->second.Exits;
			std::map<std::string, ExitInfo>::iterator ite = Exits.begin();
			std::map<std::string, ExitInfo>::iterator ende = Exits.end();
			for(; ite != ende; ++ite)
			{
				std::map<std::string, SpawningInfo> & spmap =  winfo.Maps[ite->second.NewMap].Spawnings;
				std::map<std::string, SpawningInfo>::iterator itspm = spmap.begin();
				std::map<std::string, SpawningInfo>::iterator endspm = spmap.end();
				for(; itspm != endspm; ++itspm)
				{
					if(ite->second.Spawning == itspm->second.Name)
					{
						if(ite->second.SizeX > ite->second.SizeZ)
						{
							itspm->second.PosX += ite->second.SizeX/2;

							std::map<std::string, ExitInfo> &Exits2 = winfo.Maps[ite->second.NewMap].Exits;
							std::map<std::string, ExitInfo>::iterator ite2 = Exits2.begin();
							std::map<std::string, ExitInfo>::iterator ende2 = Exits2.end();
							for(; ite2 != ende2; ++ite2)
							{
								
								if( (itspm->second.PosX > (ite2->second.PosX-ite2->second.SizeX-0.1) && itspm->second.PosX < (ite2->second.PosX+ite2->second.SizeX+0.1)) &&
									(itspm->second.PosY > (ite2->second.PosY-0.1)		  && itspm->second.PosY < (ite2->second.PosY+ite2->second.SizeY+0.1)) &&
									(itspm->second.PosZ > (ite2->second.PosZ-ite2->second.SizeZ-0.1) && itspm->second.PosZ < (ite2->second.PosZ+ite2->second.SizeZ+0.1)))
								{
									itspm->second.PosZ += 1;
									break;
								}
							}
						}
						else
						{
							itspm->second.PosZ += ite->second.SizeZ/2;

							std::map<std::string, ExitInfo> &Exits2 = winfo.Maps[ite->second.NewMap].Exits;
							std::map<std::string, ExitInfo>::iterator ite2 = Exits2.begin();
							std::map<std::string, ExitInfo>::iterator ende2 = Exits2.end();
							for(; ite2 != ende2; ++ite2)
							{	
								if( (itspm->second.PosX > (ite2->second.PosX-ite2->second.SizeX-0.1) && itspm->second.PosX < (ite2->second.PosX+ite2->second.SizeX+0.1)) &&
									(itspm->second.PosY > (ite2->second.PosY-0.1)		  && itspm->second.PosY < (ite2->second.PosY+ite2->second.SizeY+0.1)) &&
									(itspm->second.PosZ > (ite2->second.PosZ-ite2->second.SizeZ-0.1) && itspm->second.PosZ < (ite2->second.PosZ+ite2->second.SizeZ+0.1)))
								{
									itspm->second.PosX += 1;
									break;
								}
							}
						}
					}
				}	
			}

		}
	}




	std::map<std::string, MapInfo>::iterator itmap = winfo.Maps.begin();
	std::map<std::string, MapInfo>::iterator endmap = winfo.Maps.end();
	for(; itmap != endmap; ++itmap)
	{
		std::map<long, boost::shared_ptr<TriggerBase> >			_triggers;
		std::map<Ice::Long, boost::shared_ptr<ActorHandler> >	_Actors;
		std::map<long, boost::shared_ptr<Spawn> >				_spawns;

		long triggerid = 1;
		long actorid = 1;

		std::string mapname = itmap->second.Files["Maps"];
		mapname = mapname.substr(mapname.find_last_of("/")+1);
		mapname = mapname.substr(0, mapname.find("."));
		mapname[0] = toupper((unsigned char)mapname[0]);

		// add map actor
		ActorObjectInfo actorinfo(actorid++);
		actorinfo.SetRenderType(1);
		actorinfo.DisplayDesc.ModelName = "Worlds/"+winfo.Name+"/Grids/"+mapname+".osgb";
		actorinfo.DisplayDesc.UseLight = true;
		actorinfo.DisplayDesc.CastShadow = false;
		actorinfo.SetModelState(1);
		actorinfo.PhysicDesc.Pos.X = 0;
		actorinfo.PhysicDesc.Pos.Y = 0;
		actorinfo.PhysicDesc.Pos.Z = 0;
		actorinfo.PhysicDesc.Pos.Rotation = 0;
		actorinfo.SetPhysicalActorType(1);
		actorinfo.SetPhysicalShape(5);
		actorinfo.PhysicDesc.Collidable = true;
		actorinfo.PhysicDesc.Filename = "Worlds/"+winfo.Name+"/Grids/"+mapname+".phy";
		actorinfo.ExtraInfo.Name = "Map";
		boost::shared_ptr<ActorHandler> act(new ActorHandler(actorinfo));
		_Actors[act->GetId()] = act;




		// add spawns
		std::map<std::string, SpawningInfo>::iterator itsp = itmap->second.Spawnings.begin();
		std::map<std::string, SpawningInfo>::iterator endsp = itmap->second.Spawnings.end();
		for(; itsp != endsp; ++itsp)
		{
			boost::shared_ptr<Spawn> newsp(new Spawn(itsp->second.Id));
			newsp->SetPosX(itsp->second.PosX);
			newsp->SetPosY(itsp->second.PosY);
			newsp->SetPosZ(itsp->second.PosZ);
			newsp->SetForceRotation(false);
			newsp->SetName(itsp->first);
			_spawns[newsp->GetId()] = newsp;
		}



		//add exits
		std::map<std::string, ExitInfo>::iterator itex = itmap->second.Exits.begin();
		std::map<std::string, ExitInfo>::iterator endex = itmap->second.Exits.end();
		for(; itex != endex; ++itex)
		{
			TriggerInfo triinfo;
			triinfo.id = triggerid++;
			triinfo.CheckPlayers = true;
			triinfo.CheckMovableObjects = false;
			triinfo.CheckNpcs = false;
			triinfo.name = itex->first;
			boost::shared_ptr<TriggerBase> newtri(new ZoneTrigger(triinfo, itex->second.SizeX, itex->second.SizeY, itex->second.SizeZ, true));
			newtri->SetPosition(itex->second.PosX, itex->second.PosY, itex->second.PosZ);

			TeleportAction * act = new TeleportAction();
			act->SetMapName(itex->second.NewMap);
			act->SetSpawning(winfo.Maps[itex->second.NewMap].Spawnings[itex->second.Spawning].Id);
			newtri->SetAction1(ActionBasePtr(act));

			_triggers[newtri->GetId()] = newtri;
		}

		std::string textfile = itmap->second.Files["Texts"];
		textfile.substr(textfile.find("/")+1);
		long txtoffeset = textoffsets[textfile];


		// add actors
		MapInfoXmlReader::LoadActors("Data/"+itmap->second.Files["LocalActors"], _triggers, _Actors, triggerid, actorid, txtoffeset);
		MapInfoXmlReader::LoadActors("Data/"+itmap->second.Files["ExternalActors"], _triggers, _Actors, triggerid, actorid, txtoffeset);


		// save to files
		{
			std::stringstream filenames;
			filenames<<"Data/Worlds/"<<winfo.Name<<"/Lua/"<<itmap->first<<"_server.lua";
			std::ofstream file(filenames.str().c_str());
			file<<"function InitMap(environment)"<<std::endl;

			// save spawns
			std::map<long, boost::shared_ptr<Spawn> >::iterator its= _spawns.begin();
			std::map<long, boost::shared_ptr<Spawn> >::iterator ends = _spawns.end();
			for(;its != ends; ++its)
				its->second->SaveToLuaFile(file);
			

			// save actors
			std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator ita = _Actors.begin();
			std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator enda = _Actors.end();
			for(;ita != enda; ++ita)
				ita->second->SaveToLuaFile(file);

			// save triggers
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator itt = _triggers.begin();
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator endt = _triggers.end();
			for(;itt != endt; ++itt)
				itt->second->SaveToLuaFile(file);

			file<<"end"<<std::endl;
		}
	}

	return 0;
}


