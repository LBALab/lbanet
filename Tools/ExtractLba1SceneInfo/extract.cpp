extern "C" {
#include "scene.h"
}

#include <fstream>
#include "StringHelperFuncs.h"
#include "Entities.h"
#include "ActorHandler.h"
#include "Spawn.h"
#include "PointFlag.h"
#include "Triggers.h"
#include "Actions.h"
#include "NpcHandler.h"

#include <map>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <boost/assign/list_of.hpp>
#include <boost/assign/std/vector.hpp>

#include <math.h>


using namespace boost::assign;

double roundNB( double f )
{   
	return floor((f * 100 ) + 0.5) / 100;
}
float roundNB( float f )
{   
	return floor((f * 100 ) + 0.5f) / 100;
}
float roundNB5( float f )
{   
	return floor((f * 5 ) + 0.5f) / 5;
}

/** Script condition operators */
enum LifeScriptOperators {
	/*==*/ kEqualTo = 0,
	/*> */ kGreaterThan = 1,
	/*< */ kLessThan = 2,
	/*>=*/ kGreaterThanOrEqualTo = 3,
	/*<=*/ kLessThanOrEqualTo = 4,
	/*!=*/ kNotEqualTo = 5
};

/** Script condition command opcodes */
enum LifeScriptConditions {
	/*0x00*/ kcCOL = 0,
	/*0x01*/ kcCOL_OBJ = 1,
	/*0x02*/ kcDISTANCE = 2,
	/*0x03*/ kcZONE = 3,
	/*0x04*/ kcZONE_OBJ = 4,
	/*0x05*/ kcBODY = 5,
	/*0x06*/ kcBODY_OBJ = 6,
	/*0x07*/ kcANIM = 7,
	/*0x08*/ kcANIM_OBJ = 8,
	/*0x09*/ kcL_TRACK = 9,
	/*0x0A*/ kcL_TRACK_OBJ = 10,
	/*0x0B*/ kcFLAG_CUBE = 11,
	/*0x0C*/ kcCONE_VIEW = 12,
	/*0x0D*/ kcHIT_BY = 13,
	/*0x0E*/ kcACTION = 14,
	/*0x0F*/ kcFLAG_GAME = 15,
	/*0x10*/ kcLIFE_POINT = 16,
	/*0x11*/ kcLIFE_POINT_OBJ = 17,
	/*0x12*/ kcNUM_LITTLE_KEYS = 18,
	/*0x13*/ kcNUM_GOLD_PIECES = 19,
	/*0x14*/ kcBEHAVIOUR = 20,
	/*0x15*/ kcCHAPTER = 21,
	/*0x16*/ kcDISTANCE_3D = 22,
	/*0x17 - 23 unused */
	/*0x18 - 24 unused */
	/*0x19*/ kcUSE_INVENTORY = 25,
	/*0x1A*/ kcCHOICE= 26,
	/*0x1B*/ kcFUEL = 27,
	/*0x1C*/ kcCARRIED_BY = 28,
	/*0x1D*/ kcCDROM = 29
};

struct ModelInfo
{
	int modelnumber;
	int bodynumber;
	std::string name;
	std::string outfit;
	std::string weapon;
	std::string mode;
	std::map<std::string, std::vector<int> > animations;

	float sX;
	float sY;
	float sZ;
};


// read the file and get data
std::vector<ModelInfo> readModelFile()
{
	std::vector<ModelInfo> res;
	std::ifstream file("lba1_model_animation.csv");
	if(file.is_open())
	{
		// read first information line
		std::string line;
		std::vector<std::string> infos;

		std::getline(file, line);
		StringHelper::Tokenize(line, infos, ",");

		while(!file.eof())
		{
			std::getline(file, line);
			std::vector<std::string> tokens;
			StringHelper::Tokenize(line, tokens, ",");

			if(tokens.size() > 12)
			{
				ModelInfo mi;
				mi.name = tokens[0];
				mi.outfit = tokens[1];
				mi.weapon = tokens[2];
				mi.mode = tokens[3];
				mi.modelnumber = atoi(tokens[4].c_str());
				mi.bodynumber = atoi(tokens[5].c_str());
				mi.sX = (float)atof(tokens[7].c_str());
				mi.sY = (float)atof(tokens[8].c_str());
				mi.sZ = (float)atof(tokens[9].c_str());

				for(size_t i=10; i<tokens.size(); ++i)
				{
					std::string anims = tokens[i];
					std::string animstring = infos[i];
					std::vector<std::string> tokens2;
					StringHelper::Tokenize(anims, tokens2, ";");
					std::vector<int> animvec;
					for(size_t j=0; j<tokens2.size(); ++j)
						animvec.push_back(atoi(tokens2[j].c_str()));

					mi.animations[animstring] = animvec;
				}
				res.push_back(mi);
			}
		}
	}
	return res;
}

int findBodyIndex(entitiesTableStruct* entityS, int entity, int body)
{
	if (entityS->numOfEntities <= entity)
		return -1;

	for (int cc2 = 0; cc2 < entityS->entitiesTable[entity].numOfBody; ++cc2)
	{
		if ((int)entityS->entitiesTable[entity].bodyList[cc2].body == body)
			return cc2;
	}
	return -1;
}

bool findModel(entitiesTableStruct* entityS, const std::vector<ModelInfo>& modelInfo, ModelInfo& res, int model, int body, bool& isDisapear)
{
	int bodyIdx = 0;
	if (body == 255)
	{
		isDisapear = true;
	}
	else
	{
		isDisapear = false;
		bodyIdx = findBodyIndex(entityS, model, body);
	}

	if (bodyIdx < 0)
		return false;

	for (std::vector<ModelInfo>::const_iterator it = modelInfo.begin(), end = modelInfo.end(); it != end; ++it)
	{
		if (it->modelnumber == model && it->bodynumber == bodyIdx)
		{
			res = *it;
			return true;
		}
	}

	return false;
}

int findAnimIndex(entitiesTableStruct* entityS, int entity, int anim)
{
	for (int cc2 = 0; cc2 < entityS->entitiesTable[entity].numOfAnims; ++cc2)
	{
		if (entityS->entitiesTable[entity].animList[cc2].anim == anim)
			return cc2;
	}
	return -1;
}


int32 getTextIndex(int32 originalIndex, const std::vector<int>& offsetText, std::map<int, std::vector<int> >& missingTextsIdx)
{
	int remOffset = 0;
	for (size_t ll=0; ll < missingTextsIdx[sceneTextBank].size(); ++ll)
	{
		if (originalIndex >= missingTextsIdx[sceneTextBank][ll])
			++remOffset;
	}
	originalIndex -= remOffset;

	return offsetText[sceneTextBank]+originalIndex;
}


void extractInfo()
{
	std::ofstream diafile("checkdialog.txt");

	std::vector<int> offsetText;
	offsetText.push_back(170);
	offsetText.push_back(361);
	offsetText.push_back(629);
	offsetText.push_back(673);
	offsetText.push_back(791);
	offsetText.push_back(825);
	offsetText.push_back(869);
	offsetText.push_back(908);
	offsetText.push_back(974);
	offsetText.push_back(992);
	offsetText.push_back(1028);
	
	std::map<int, std::vector<int> > missingTextsIdx;
	{
		std::vector<int> v0;
		v0 += 11,19,41,43,44,45,73,148,183;
		missingTextsIdx[0] = v0;

		std::vector<int> v1;
		v1 += 25,51,52,53,54,56,59,67,101,116,149,150,152,192,193,194,196,197;
		missingTextsIdx[1] = v1;

		std::vector<int> v2;
		v2.push_back(2);
		missingTextsIdx[2] = v2;

		std::vector<int> v3;
		v3.push_back(41);
		missingTextsIdx[2] = v3;

		std::vector<int> v4;
		v4 += 6,16,30;
		missingTextsIdx[4] = v4;

		std::vector<int> v5;
		v5 += 18,26;
		missingTextsIdx[5] = v5;

		std::vector<int> v7;
		v7 += 12,15,16,18,20,21,24,53;
		missingTextsIdx[7] = v7;

		std::vector<int> v9;
		v9 += 19,20;
		missingTextsIdx[9] = v9;
	}



	const int nbScenes = 119;
	entitiesTableStruct* entityS = parseEntities("FILE3D.HQR");
	//std::ofstream fileE("checkEntity.txt");
	//for (int cc = 0; cc < entityS->numOfEntities; ++cc)
	//{
	//	for (int cc2 = 0; cc2 < entityS->entitiesTable[cc].numOfAnims; ++cc2)
	//	{
	//		fileE << "Entity" << cc << "-anim: " << cc2 << " " << entityS->entitiesTable[cc].animList[cc2].anim << " " << entityS->entitiesTable[cc].animList[cc2].index << std::endl;
	//	}	
	//	for (int cc2 = 0; cc2 < entityS->entitiesTable[cc].numOfBody; ++cc2)
	//	{
	//		fileE << "Entity" << cc << "-body: " << cc2 << " " << (short)entityS->entitiesTable[cc].bodyList[cc2].body << " " << entityS->entitiesTable[cc].bodyList[cc2].index << std::endl;
	//	}	
	//}
	//fileE.close();

	std::vector<ModelInfo> modelInfo = readModelFile();
	{
		std::ofstream file("Lua/CustomServer.lua");

		file << "function PlaySoundOnActor(Environment, ScriptId, ActorId, SoundId, NbRepeat, RandomPitch)" << std::endl;
		file << "\tlocal sampleStr = \"Worlds/Lba1Original/Sound/SAMPLES\" .. string.format(\"%03d\", SoundId) .. \".wav\"" << std::endl;
		file << "\tlocal channel = gActorsMap[ActorId][\"Channel\"]" << std::endl;
		file << "\tif channel == nil then channel = 0 end" << std::endl;
		file << "\tEnvironment:ActorStartSound(ScriptId, ActorId, channel % 5, sampleStr, NbRepeat, RandomPitch)" << std::endl;
		file << "\tgPlayingSoundActor[SoundId] = ActorId" << std::endl;
		file << "\tgPlayingSoundChannel[SoundId] = channel" << std::endl;
		file << "\tgActorsMap[ActorId][\"Channel\"] = channel + 1" << std::endl;
		file << "end\n\n\n";

		file << "function StopSoundOnActor(Environment, ScriptId, ActorId, SoundId)" << std::endl;
		file << "\tlocal soundActor = gPlayingSoundActor[SoundId]" << std::endl;
		file << "\tlocal soundChannel = gPlayingSoundChannel[SoundId]" << std::endl;
		file << "\tif soundActor ~= nil and soundChannel ~= nil then" << std::endl;
		file << "\t\tEnvironment:ActorStopSound(ScriptId, soundActor, soundChannel)" << std::endl;
		file << "\tend" << std::endl;
		file << "end\n\n\n";

		file << "function RotateActorTo(Environment, ScriptId, ActorId, angle, rotSpeed)\n";
		file << "\tlocal curAngle = Environment:GetActorRotation(ScriptId, ActorId)\n";
		file << "\tlocal diffAngle = angle - curAngle\n";
		file << "\twhile diffAngle < -180 do\n";
		file << "\t\tdiffAngle = diffAngle + 360\n";
		file << "\tend\n";
		file << "\twhile diffAngle > 180 do\n";
		file << "\t\tdiffAngle = diffAngle - 360\n";
		file << "\tend\n";
		file << "\tEnvironment:ActorRotate(ScriptId, ActorId, diffAngle, rotSpeed, false)\n"; 
		file << "end\n\n\n";

		file << "function SetActorMovementScript(ActorId, FunctionName, Override)" << std::endl;
		file << "\tif Override == true or gActorsMap[ActorId][\"MoveScript\"] == nil then" << std::endl;
		file << "\t\tgActorsMap[ActorId][\"MoveScript\"] = FunctionName" << std::endl;
		file << "\tend" << std::endl;
		file << "end\n\n\n";

		file << "function RunMovementScript(ScriptId, ActorId, Environment)" << std::endl;
		file << "\twhile true do" << std::endl;
		file << "\t\tlocal moveScName = gActorsMap[ActorId][\"MoveScript\"]" << std::endl;
		file << "\t\tif moveScName ~= nil then" << std::endl;
		file << "\t\t\tgActorsMap[ActorId][\"MoveScript\"] = nil" << std::endl;
		file << "\t\t\t-- call function in the global lua space" << std::endl;
		file << "\t\t\t_G[moveScName](ScriptId, ActorId, Environment)" << std::endl;
		file << "\t\tend" << std::endl;
		file << "\tEnvironment:WaitOneCycle(ScriptId)"<<std::endl;
		file << "\tend" << std::endl;
		file << "end\n\n\n";

		file.close();
	}

	// precalculate the spawn and exits
	std::map<int, std::vector<boost::shared_ptr<Spawn> > > spawns;
	std::map<int, std::vector<boost::shared_ptr<TriggerBase> > > triggers;
	for (int j = 0; j < nbScenes; j++)
	{
		diafile << std::endl << std::endl;
		needChangeScene = j;
		changeScene();

		for (int i = 0; i < sceneNumZones; i++)
		{
			ZoneStruct *zone = &sceneZones[i];
			if (zone->type == kCube)
			{
				float zoneSX = abs(zone->topRight.X - zone->bottomLeft.X) / 512.f;
				float zoneSY = abs(zone->topRight.Y - zone->bottomLeft.Y) / 256.f;
				float zoneSZ = abs(zone->topRight.Z - zone->bottomLeft.Z) / 512.f;
				float offsetX = (zoneSX > zoneSZ) ? 0.5f : 0;
				float offsetZ = (zoneSX > zoneSZ) ? 0 : 0.5f;

				boost::shared_ptr<Spawn> spawn(new Spawn(spawns[zone->infoData.ChangeScene.newSceneIdx].size()+1));
				spawn->SetName("spawning" + boost::lexical_cast<std::string>(spawn->GetId()));
				spawn->SetPosX(roundNB((zone->infoData.ChangeScene.X / 512.f) + (zoneSX/2) + offsetX));
				spawn->SetPosY(roundNB((zone->infoData.ChangeScene.Y / 256.f) - 0.99f));
				spawn->SetPosZ(roundNB((zone->infoData.ChangeScene.Z / 512.f) + (zoneSZ/2) + offsetZ));
				spawns[zone->infoData.ChangeScene.newSceneIdx].push_back(spawn);

				TriggerInfo tinfo(i, "exit" + boost::lexical_cast<std::string>(i), true, false, false);
				boost::shared_ptr<ZoneTrigger> tri = boost::make_shared<ZoneTrigger>(tinfo, roundNB(zoneSX), roundNB(zoneSY), roundNB(zoneSZ), true);
				tri->SetPosition(roundNB((zone->bottomLeft.X / 512.f + zoneSX/2) + 0.5f), roundNB((zone->bottomLeft.Y / 256.f) - 1), roundNB((zone->bottomLeft.Z / 512.f) + zoneSZ/2 + 0.5f));
				tri->SetStayUpdateFrequency(-1);
				tri->SetActivateOnJump(true);
				boost::shared_ptr<TeleportAction> act = boost::make_shared<TeleportAction>();
				std::stringstream strName;
				strName << "Map" << std::setw(3) << std::setfill('0') << zone->infoData.ChangeScene.newSceneIdx << "_1";
				act->SetMapName(strName.str());
				act->SetSpawning(spawn->GetId());
				tri->SetAction1(act);
				triggers[j].push_back(tri);
			}
		}

		// try to life script for dialog
		{
			uint8 *scriptPtr = sceneActors[0].lifeScript;
			short opCode = (short)*scriptPtr++;

			// try to find SWIF ACTION = 1
			bool found = false;
			while(opCode != 0) // until script end
			{
				if (opCode == 0x0D)//"SWIF"
				{
					int32 conditionOpcode = *(scriptPtr++);
					if (conditionOpcode == kcACTION)
					{
						int32 operatorCode = *(scriptPtr++);
						if (operatorCode == kEqualTo)
						{
							int32 conditionValue = *(scriptPtr++);
							if (conditionValue == 1)
							{
								found = true;
								break; // yeah we found it!
							}
						}
					}
				}
				opCode = (short)*scriptPtr++;
			}	

			if (found)
			{
				// now go over all actors the hero can talk to
				opCode = (short)*scriptPtr++;
				while(opCode != 0x10) // ENDIF
				{
					if (opCode == 0x0C)//"IF"
					{
						int32 conditionOpcode = *(scriptPtr++);
						if (conditionOpcode == kcDISTANCE)
						{
							int32 actorIdx = *(scriptPtr++);
							int32 operatorCode = *(scriptPtr++);
							if (operatorCode == kLessThan)
							{
								int32 conditionValue = *((int16 *)scriptPtr);
								scriptPtr += 2;
								
								DialogPartPtr dialogRoot = boost::make_shared<DialogPart>();
								ConditionBasePtr condRoot;
								ConditionBasePtr* condRef = &condRoot;
								while(opCode != 0x10) // ENDIF
								{
									if (opCode == 0x37) // OR_IF
									{
										conditionOpcode = *(scriptPtr++);
										if (conditionOpcode == kcCHAPTER)
										{
											int32 operatorCode = *(scriptPtr++);
											int32 expectedChapter = *(scriptPtr++);

											OrCondition* orCond = new OrCondition();
											CheckFlagCondition* flagCond = new CheckFlagCondition();
											flagCond->SetFlagName("Chapter");
											flagCond->SetValue(expectedChapter);
											flagCond->SetOperator(operatorCode);
											orCond->SetCondition1(ConditionBasePtr(flagCond));
											*condRef = ConditionBasePtr(orCond);
											condRef = &(orCond->GetCondition2());
										}
										else
										{

											diafile << "scene " << j << " script line " << (scriptPtr-sceneActors[0].lifeScript) << " - conditionOpcode not expected - should be OR_IF CHAPTER == value: " << conditionOpcode << std::endl;
										}
									}
									else if (opCode == 0x0C)//"IF"
									{
										conditionOpcode = *(scriptPtr++);
										if (conditionOpcode == kcCHAPTER)
										{
											int32 operatorCode = *(scriptPtr++);
											int32 expectedChapter = *(scriptPtr++);

											CheckFlagCondition* flagCond = new CheckFlagCondition();
											flagCond->SetFlagName("Chapter");
											flagCond->SetValue(expectedChapter);
											flagCond->SetOperator(operatorCode);
											*condRef = ConditionBasePtr(flagCond);

											// get what is inside the if
											opCode = (short)*scriptPtr++;
											if (opCode == 0x19)//"MESSAGE"
											{
												int32 textIdx = *((int16 *)scriptPtr);
												scriptPtr += 2;
												textIdx = getTextIndex(textIdx, offsetText, missingTextsIdx);

												DialogPartPtr startDial = boost::make_shared<DialogPart>();
												startDial->SetText(textIdx);
												startDial->Setcondition(condRoot);
												dialogRoot->AddChild(startDial);


												opCode = (short)*scriptPtr++;
												if(opCode != 0x10) // ENDIF
												{
													diafile << "scene " << j << " script line " << (scriptPtr-sceneActors[0].lifeScript) << " - opCode not expected after IF CHAPTER - should be ENDIF: " << opCode << std::endl;
												}
											}
											else
											{
												diafile << "scene " << j << " script line " << (scriptPtr-sceneActors[0].lifeScript) << " - opCode not expected after IF CHAPTER - should be MESSAGE value: " << opCode << std::endl;
											}
										}
										else if (conditionOpcode == kcLIFE_POINT_OBJ)
										{
											int32 actorIdx = *(scriptPtr++);
											int32 operatorCode = *(scriptPtr++);
											int32 expectedValue = *(scriptPtr++);

											opCode = (short)*scriptPtr++;
											if (opCode == 0x22) // SET_COMPORTEMENT_OBJ
											{
												int32 otherActorIdx = *(scriptPtr++);
												int16 newPosInScript = *((int16 *)scriptPtr);
												scriptPtr += 2;
											}
											else
											{
												diafile << "scene " << j << " script line " << (scriptPtr-sceneActors[0].lifeScript) << " - opCode not expected after IF LIFE_POINT_OBJ - should be SET_COMPORTEMENT_OBJ: " << opCode <<std::endl;
											}

											opCode = (short)*scriptPtr++;
											if(opCode != 0x10) // ENDIF
											{
												diafile << "scene " << j << " script line " << (scriptPtr-sceneActors[0].lifeScript) << " - opCode not expected after IF LIFE_POINT_OBJ - should be ENDIF: " << opCode << std::endl;
											}
										}
										else
										{
											diafile << "scene " << j << " script line " << (scriptPtr-sceneActors[0].lifeScript) << " - conditionOpcode not expected - should be IF CHAPTER == value: " << conditionOpcode << std::endl;
										}
									}
									else if (opCode == 0x22) // SET_COMPORTEMENT_OBJ
									{
										int32 otherActorIdx = *(scriptPtr++);
										int16 newPosInScript = *((int16 *)scriptPtr);
										scriptPtr += 2;
									}
									else
									{
										diafile << "scene " << j << " script line " << (scriptPtr-sceneActors[0].lifeScript) << " - operatorCode not expected: " << opCode << std::endl;
									}

									opCode = (short)*scriptPtr++;
								}
							}
							else
							{
								diafile << "scene " << j << " script line " << (scriptPtr-sceneActors[0].lifeScript) << " - operatorCode not expected - should be IF DISTANCE ActorID < value" << std::endl;
							}
						}
						else
						{
							diafile << "scene " << j << " script line " << (scriptPtr-sceneActors[0].lifeScript) << " - conditionOpcode not expected - should be IF DISTANCE ActorID < value" << std::endl;
						}
					}
					else
					{
						diafile << "scene " << j << " script line " << (scriptPtr-sceneActors[0].lifeScript) << " - opCode not expected - should be IF DISTANCE ActorID < value" << std::endl;
					}
					opCode = (short)*scriptPtr++;
				}
			}
		}
	}




	for (int j = 0; j < nbScenes; j++)
	{
		// offset spawns so that it does not touch exits
		for (size_t i = 0; i < spawns[j].size(); i++)
		{
			boost::shared_ptr<Spawn> sp = spawns[j][i];
			for (size_t k = 0; k < triggers[j].size(); k++)
			{
				boost::shared_ptr<TriggerBase> tr = triggers[j][k];
				if (tr->GetTypeName() == "ZoneTrigger")
				{
					boost::shared_ptr<ZoneTrigger> trCasted = boost::dynamic_pointer_cast<ZoneTrigger>(tr);
					if( (sp->GetPosX() > tr->GetPosX()-0.6) && (sp->GetPosX()  < (tr->GetPosX()+0.6)) &&
						(sp->GetPosY()  > (tr->GetPosY()-0.1)) && (sp->GetPosY()  < (tr->GetPosY()+0.1)) &&
						(sp->GetPosZ()  > tr->GetPosZ()-0.6) && (sp->GetPosZ()  < (tr->GetPosZ()+0.6)))
					{
						if (trCasted->GetSizeX() < trCasted->GetSizeZ())
							sp->SetPosX(sp->GetPosX()+1);
						else
							sp->SetPosZ(sp->GetPosZ()+1);

						break;
					}
				}
			}	
		}


		needChangeScene = j;
		changeScene();


		std::stringstream strfile;
		strfile << "Lua/Map" << std::setw(3) << std::setfill('0') << j;
		std::ofstream fileActor((strfile.str() + "_1_server.lua").c_str());
		std::ofstream file((strfile.str() + "_1_server_extra.lua").c_str());

		fileActor << "function InitMap(environment)" << std::endl;
		fileActor << "local lmap = {}" << std::endl;


		for (int i = 0; i < sceneNumZones; i++)
		{
			ZoneStruct *zone = &sceneZones[i];
			float zoneSX = abs(zone->topRight.X - zone->bottomLeft.X) / 512.f;
			float zoneSY = abs(zone->topRight.Y - zone->bottomLeft.Y) / 256.f;
			float zoneSZ = abs(zone->topRight.Z - zone->bottomLeft.Z) / 512.f;
			switch (zone->type) 
			{
				case kObject:
				{
					TriggerInfo tinfo(i, "container" + boost::lexical_cast<std::string>(i), true, false, false);
					boost::shared_ptr<ZoneActionTrigger> tri = boost::make_shared<ZoneActionTrigger>(tinfo, roundNB(zoneSX), roundNB(zoneSY), roundNB(zoneSZ), "Normal", "");
					tri->SetPosition(roundNB((zone->bottomLeft.X / 512.f + zoneSX/2) + 0.5f), roundNB((zone->bottomLeft.Y / 256.f) - 1), roundNB((zone->bottomLeft.Z / 512.f) + zoneSZ/2 + 0.5f));
					boost::shared_ptr<OpenContainerAction> act = boost::make_shared<OpenContainerAction>();
					act->SetTimeToReset(300);

					int nbElem = zone->infoData.generic.info2;
					std::vector<ContainerItemGroupElement> elems;
					for (int a = 0; a < 5; a++) 
					{
						if (zone->infoData.generic.info1 & (1 << (a + 4)))
						{
							ContainerItemGroupElement cont (28 + a, nbElem, nbElem, 1, 1);
							elems.push_back(cont);
						}
					}
					for (size_t a = 0; a < elems.size(); a++)
					{
						elems[a].Probability = 1.0f / elems.size();
						act->AddItem(elems[a]);
					}

					tri->SetPlayAnimation(true);
					tri->SetAction1(act);
					triggers[j].push_back(tri);
				}
				break;

				case kLadder:
				{
					TriggerInfo tinfo(i, "ladder" + boost::lexical_cast<std::string>(i), true, false, false);
					boost::shared_ptr<ActivationTrigger> tri = boost::make_shared<ActivationTrigger>(tinfo, 2.0f, "Normal", "");
					tri->SetPosition(roundNB((zone->bottomLeft.X / 512.f + zoneSX/2) + 0.5f),
									 roundNB((zone->bottomLeft.Y / 256.f) - 1),
									 roundNB((zone->bottomLeft.Z / 512.f) + zoneSZ/2 + 0.5f));
					boost::shared_ptr<ClientScriptAction> act = boost::make_shared<ClientScriptAction>();
					boost::shared_ptr<GoUpLadderScript> cs = boost::make_shared<GoUpLadderScript>();
					cs->SetLadderPositionX(roundNB((zone->bottomLeft.X / 512.f + zoneSX/2) + 0.5f));
					cs->SetLadderPositionY(roundNB((zone->bottomLeft.Y / 256.f) - 1));
					cs->SetLadderPositionZ(roundNB((zone->bottomLeft.Z / 512.f) + zoneSZ/2 + 0.5f));
					cs->SetLadderHeight(roundNB5((zone->topRight.Y - zone->bottomLeft.Y) / 512.f) + 4.5f);

					if (zoneSZ > zoneSX)
					{
						cs->SetLadderDirection(270);
					}
					else
					{
						cs->SetLadderDirection(180);
					}

					// exceptions
					{
						if (j == 51)
						{
							if (i == 15 || i == 21 || i == 22)
							{
								cs->SetLadderDirection(270);
							}
						}
						if (j == 75)
						{
							cs->SetLadderDirection(180);
						}
						if (j == 79 && i == 4)
						{
							cs->SetLadderDirection(180);
						}
						if (j == 86)
						{
							cs->SetLadderDirection(270);
						}
					}

					act->SetScript(cs);
					tri->SetAction1(act);
					tri->SetPlayAnimation(false);
					triggers[j].push_back(tri);
				}
				break;

				case kText:
				{
					// move index along missing text entries
					int32 txtIdx = zone->infoData.DisplayText.textIdx;
					txtIdx = getTextIndex(txtIdx, offsetText, missingTextsIdx);

					TriggerInfo tinfo(i, "text" + boost::lexical_cast<std::string>(i), true, false, false);
					boost::shared_ptr<ActivationTrigger> tri = boost::make_shared<ActivationTrigger>(tinfo, 2.0f, "Normal", "");
					tri->SetPosition(roundNB((zone->bottomLeft.X / 512.f + zoneSX/2) + 0.5f),
						roundNB((zone->bottomLeft.Y / 256.f) - 1),
						roundNB((zone->bottomLeft.Z / 512.f) + zoneSZ/2 + 0.5f));	
					tri->SetPlayAnimation(false);
					boost::shared_ptr<DisplayTextAction> act = boost::make_shared<DisplayTextAction>();
					act->SetTextId(txtIdx);
					tri->SetAction1(act);
					triggers[j].push_back(tri);
				}
				break;
			}
		}



		// save spawns
		for (size_t i = 0; i < spawns[j].size(); i++)
		{
			spawns[j][i]->SaveToLuaFile(fileActor);
		}

		// save points
		for (int i = 0; i < sceneNumTracks; i++)
		{
			PointFlag pf(i);
			pf.SetPosX(roundNB(sceneTracks[i].X/512.f));
			pf.SetPosY(roundNB((sceneTracks[i].Y/256.f) - 1));
			pf.SetPosZ(roundNB(sceneTracks[i].Z/512.f));
			pf.SetName("point-" + boost::lexical_cast<std::string>(pf.GetId()));
			pf.SaveToLuaFile(fileActor);
		}

		// add map actor
		{
			ActorObjectInfo ai(0);
			ai.SetModelState(1);
			ai.PhysicDesc.Pos.X = 0;
			ai.PhysicDesc.Pos.Y = 0;
			ai.PhysicDesc.Pos.Z = 0;
			ai.PhysicDesc.Pos.Rotation = 0;
			ai.PhysicDesc.AllowFreeMove = false;
			ai.PhysicDesc.TypePhysO = LbaNet::StaticAType;
			ai.PhysicDesc.TypeShape = LbaNet::TriangleMeshShape;
			ai.PhysicDesc.Filename = "Worlds/Lba1Original/Grids/Map" + boost::lexical_cast<std::string>(j) + ".phy";

			ai.DisplayDesc.TypeRenderer = LbaNet::RenderOsgModel;
			ai.DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/Map" + boost::lexical_cast<std::string>(j) + ".osgb";
			ai.DisplayDesc.CastShadow = false;

			ActorHandler ah(ai);
			ah.setAppearDisapear(true);
			ah.SaveToLuaFile(fileActor);
		}


		//file << "Scene %i ************************************** \n",j);
		file << "gPlayingSoundActor = {}" << std::endl;
		file << "gPlayingSoundActor[-1] = -1" << std::endl;
		file << "gPlayingSoundChannel = {}" << std::endl;
		file << "gPlayingSoundChannel[-1] = -1" << std::endl;
		file << "gActorsMap = {}" << std::endl;
		for (int i = 1; i < sceneNumActors; i++)
		{
			file << "gActorsMap[" << i << "] = {}" << std::endl;
			file << "gActorsMap[" << i << "][\"RotationSpeed\"] = " << (sceneActors[i].speed  * 360.0f / 1024.0f)  << std::endl;
			file << "gActorsMap[" << i << "][\"MoveSpeed\"] = " << 0  << std::endl;


			// check if there is a default track
			{
				uint8 *scriptPtr = sceneActors[i].lifeScript;
				short opCode = (short)*scriptPtr++;
				if (opCode == 0x17)
				{
					int16 movePos = *((int16 *)scriptPtr);
					if (movePos >= 0)
					{
						scriptPtr = sceneActors[i].moveScript + movePos;
						opCode = (short)*scriptPtr++;
						if (opCode == 9)
						{
							int label = (int)(*scriptPtr);
							file << "gActorsMap["<<i<<"][\"MoveScript\"] = \"" << "Scene"<< j << "_Actor" << i <<"_Label" << label << "\"" << std::endl;
						}
					}
				}
			}
		}
		file << std::endl << std::endl;

		for (int i = 1; i < sceneNumActors; i++)
		{
			//save actor
			ActorObjectInfo ai(i);
			{
				ai.SetModelState(1);
				ai.PhysicDesc.Pos.X = roundNB(sceneActors[i].X / 512.f);
				ai.PhysicDesc.Pos.Y = roundNB((sceneActors[i].Y / 256.f) - 1);
				ai.PhysicDesc.Pos.Z = roundNB(sceneActors[i].Z / 512.f);
				ai.PhysicDesc.Pos.Rotation = roundNB((sceneActors[i].angle % 1024) * 360.0f / 1024.0f);
				ai.PhysicDesc.AllowFreeMove = false;
				ai.PhysicDesc.TypePhysO = LbaNet::KynematicAType;
				ai.PhysicDesc.TypeShape = LbaNet::BoxShape;

				ModelInfo currModel;
				bool diseapear;
				if (findModel(entityS, modelInfo, currModel, sceneActors[i].entity, sceneActors[i].body, diseapear))
				{
					ai.PhysicDesc.SizeX = currModel.sX;
					ai.PhysicDesc.SizeY = currModel.sY;
					ai.PhysicDesc.SizeZ = currModel.sZ;
					ai.PhysicDesc.Pos.X += ai.PhysicDesc.SizeX/2;
					ai.PhysicDesc.Pos.Z += ai.PhysicDesc.SizeZ/2;

					ai.DisplayDesc.TypeRenderer = LbaNet::RenderLba1M;
					ai.DisplayDesc.ModelName = currModel.name;
					ai.DisplayDesc.Outfit = currModel.outfit;
					ai.DisplayDesc.Weapon = currModel.weapon;
					ai.DisplayDesc.Mode = currModel.mode;
					ai.DisplayDesc.ColorMaterialType = 4;
					ai.DisplayDesc.MatAmbientColorR = -0.2f;
					ai.DisplayDesc.MatAmbientColorG = -0.2f;
					ai.DisplayDesc.MatAmbientColorB = -0.2f;
					ai.DisplayDesc.MatAmbientColorA = 1;
					ai.DisplayDesc.MatDiffuseColorR = 0.4f;
					ai.DisplayDesc.MatDiffuseColorG = 0.4f;
					ai.DisplayDesc.MatDiffuseColorB = 0.4f;
					ai.DisplayDesc.MatDiffuseColorA = 1;
					ai.DisplayDesc.MatSpecularColorR = 0;
					ai.DisplayDesc.MatSpecularColorG = 0;
					ai.DisplayDesc.MatSpecularColorB = 0;
					ai.DisplayDesc.MatSpecularColorA = 1;
					ai.DisplayDesc.MatEmissionColorR = 0;
					ai.DisplayDesc.MatEmissionColorG = 0;
					ai.DisplayDesc.MatEmissionColorB = 0;
					ai.DisplayDesc.MatEmissionColorA = 1;
					ai.DisplayDesc.MatShininess = 0;
					ai.DisplayDesc.CastShadow = true;

					NPCHandler ah(ai);
					ah.setAppearDisapear(!diseapear);
					ah.SetAggresive(false);
					ah.SetLife((float)(sceneActors[i].life));
					ah.SetArmor((float)(sceneActors[i].armor));
					ah.SetSimpleDialog(true);

					ah.SetMovementStartScript("RunMovementScript");
					ah.SaveToLuaFile(fileActor);
				}
				else
				{
					ai.DisplayDesc.TypeRenderer = LbaNet::RenderOsgModel;

					std::stringstream strname;
					strname << "Worlds/Lba1Original/Sprites/sprite" << std::setw(3) << std::setfill('0') << sceneActors[i].sprite << ".osgb";
					ai.DisplayDesc.ModelName = strname.str();
					ai.DisplayDesc.CastShadow = false;

					ActorHandler ah(ai);
					ah.setAppearDisapear(!diseapear);

					ah.SetMovementStartScript("RunMovementScript");
					ah.SaveToLuaFile(fileActor);
				}

			}

			// save script
			{
				int32 scriptOpcode;
				uint8 *scriptPtr;
				int inFunction = 0;
				float angle = 0;
				short pointId = 0;
				int16 repeatSample = 1;
				float move = 0;
				scriptPtr = sceneActors[i].moveScript;

				ModelInfo currModel;
				bool diseapear;
				findModel(entityS, modelInfo, currModel, sceneActors[i].entity, sceneActors[i].body, diseapear);
				do 
				{
					scriptOpcode = *(scriptPtr++);

					switch(scriptOpcode)
					{
					case 0:
						if (inFunction)
							file << "end\n\n";
						inFunction = 1; 
						break;//MAPFUNC("END", mEND),
					case 1:
						file << "\t-- NOP" << std::endl; 
						break;//MAPFUNC("NOP", mNOP),
					case 2:
						{
							ModelInfo newModel;
							int newbody = (int)(*scriptPtr++);
							if (findModel(entityS, modelInfo, newModel, sceneActors[i].entity, newbody, diseapear))
							{
								if (diseapear)
								{
									file << "\tEnvironment:ActorAppearDisappear(ScriptId, ActorId, false)" << std::endl;
								}
								else
								{
									file << "\tEnvironment:ActorAppearDisappear(ScriptId, ActorId, true)" << std::endl;
									if (newModel.name != currModel.name)
										file << "\tEnvironment:UpdateActorModel(ScriptId, ActorId, \""<< newModel.name<<"\")" << std::endl;
									if (newModel.outfit != currModel.outfit)
										file << "\tEnvironment:UpdateActorOutfit(ScriptId, ActorId, \""<< newModel.outfit<<"\")" << std::endl;
									if (newModel.weapon != currModel.weapon)
										file << "\tEnvironment:UpdateActorWeapon(ScriptId, ActorId, \""<< newModel.weapon<<"\")" << std::endl;
									if (newModel.mode != currModel.mode)
										file << "\tEnvironment:UpdateActorMode(ScriptId, ActorId, \""<< newModel.mode<<"\")" << std::endl;
								}
							}
							else
								file << "\t-- BODY not found (" << sceneActors[i].entity << ", "<< newbody << ")"<< std::endl; 
						}
						break;//MAPFUNC("BODY", mBODY),
					case 3:
						{
							int anim = (int)(*scriptPtr++);
							int animIdx = findAnimIndex(entityS, sceneActors[i].entity, anim);
							if (animIdx >= 0)
								file << "\tEnvironment:UpdateActorAnimation(ScriptId, ActorId, \"#"<< animIdx <<"\")\n"; 
							else
								file << "\tEnvironment:UpdateActorAnimation(ScriptId, ActorId, \"#"<< 0 <<"\") -- can not find anim " << anim << std::endl; 
						}
						break;//MAPFUNC("ANIM", mANIM),
					case 4:
						ai.PhysicDesc.Pos.Z += ai.PhysicDesc.SizeZ/2;
						pointId = *scriptPtr++;
						file << "\tlocal GotoPosition = LbaVec3()\n";
						file << "\t\tGotoPosition.x = "<< roundNB((sceneTracks[pointId].X/512.f)) << std::endl; 
						file << "\t\tGotoPosition.y = "<< roundNB((sceneTracks[pointId].Y/256.f)-1) << std::endl; 
						file << "\t\tGotoPosition.z = "<< roundNB((sceneTracks[pointId].Z/512.f)) << std::endl; 
						file << "\tlocal rotSpeed = gActorsMap[ActorId][\"RotationSpeed\"]\n";	
						file << "\tEnvironment:ActorWalkToPoint(ScriptId, ActorId, GotoPosition, rotSpeed, true)\n"; 
						break;//MAPFUNC("GOTO_POINT", mGOTO_POINT),
					case 5:
						file << "\tEnvironment:ActorAnimate(ScriptId, ActorId, true, 1)\n"; 
						break;//MAPFUNC("WAIT_ANIM", mWAIT_ANIM),
					case 6: file << "LOOP \n"; 
						break;//MAPFUNC("LOOP", mLOOP),
					case 7: 
						angle = ((*(int16*)scriptPtr)%1024) * 360.0f / 1024.0f;
						file << "\tlocal rotSpeed = gActorsMap[ActorId][\"RotationSpeed\"]\n";
						file << "\tRotateActorTo(Environment, ScriptId, ActorId, "<< angle <<", rotSpeed)\n"; 
						scriptPtr+=2; 
						break;//MAPFUNC("ANGLE", mANGLE),
					case 8:
						pointId = *scriptPtr++;
						file << "\tlocal GotoPosition = LbaVec3()\n";
						file << "\t\tGotoPosition.x = "<< roundNB((sceneTracks[pointId].X/512.f)) << std::endl; 
						file << "\t\tGotoPosition.y = "<< roundNB((sceneTracks[pointId].Y/256.f)-1) << std::endl; 
						file << "\t\tGotoPosition.z = "<< roundNB((sceneTracks[pointId].Z/512.f)) << std::endl; 	
						file << "\tEnvironment:TeleportActorTo(ScriptId, ActorId, GotoPosition)\n"; 
						break;//MAPFUNC("POS_POINT", mPOS_POINT),
					case 9: 
						if (inFunction)
						{
							file << "\tSetActorMovementScript(ActorId, \"Scene"<< j <<"_Actor"<< i <<"_Label"<< (int)(*scriptPtr) <<"\", false)\n"; 
							file << "end\n\n";
						}
						file <<  "function Scene"<< j <<"_Actor"<< i <<"_Label"<< (int)(*scriptPtr++) <<"(ScriptId, ActorId, Environment)\n";
						inFunction = 1; 
						break;//MAPFUNC("LABEL", mLABEL),
					case 10: 

						{
							uint8 * gotoPtr = sceneActors[i].moveScript + *((int16 *)scriptPtr);
							int32 opCode = (short)*gotoPtr++;
							if (opCode == 9)
							{
								int label = (int)(*gotoPtr);
								file << "\tSetActorMovementScript(ActorId, \"Scene"<< j <<"_Actor"<< i <<"_Label"<< label <<"\", false)\n"; 
							}
							else
							{
								file << "\t --GOTO end" << std::endl;
							}
							file << "end\n\n";
							inFunction = 0; 
							scriptPtr+=2; 
						}

						break;//MAPFUNC("GOTO", mGOTO),
					case 11: 
						if (inFunction)
						{
							if (*scriptPtr != 9 && *scriptPtr != 0)
							{
								file << "\tEnvironment:ActorWaitForResume(ScriptId, ActorId)\n"; 
							}
							else
							{
								file << "end\n\n"; 
								inFunction = 0; 
							}
						}
						break;//MAPFUNC("STOP", mSTOP),
					case 0x0C:
						pointId = *scriptPtr++;
						file << "\tlocal GotoPosition = LbaVec3()\n";
						file << "\t\tGotoPosition.x = "<< roundNB((sceneTracks[pointId].X/512.f)) << std::endl;
						file << "\t\tGotoPosition.y = "<< roundNB((sceneTracks[pointId].Y/256.f)-1) << std::endl;
						file << "\t\tGotoPosition.z = "<< roundNB((sceneTracks[pointId].Z/512.f)) << std::endl;
						file << "\tlocal rotSpeed = gActorsMap[ActorId][\"RotationSpeed\"]\n";	
						file << "\tEnvironment:ActorWalkToPoint(ScriptId, ActorId, GotoPosition, rotSpeed, false)\n"; 
						break;//MAPFUNC("GOTO_SYM_POINT", mGOTO_SYM_POINT),
					case 0x0D: 
						file << "\tEnvironment:ActorAnimate(ScriptId, ActorId, true, "<< (int)(*scriptPtr) <<")\n"; 
						scriptPtr+=2; 
						break;//MAPFUNC("WAIT_NUM_ANIM", mWAIT_NUM_ANIM),
					case 0x0E:
						file << "\tPlaySoundOnActor(Environment, ScriptId, ActorId, "<< *(int16*)scriptPtr <<", 1, false)\n";
						scriptPtr+=2; 
						break;//MAPFUNC("SAMPLE", mSAMPLE),
					case 0x0F:
						pointId = *scriptPtr++;
						file << "\tlocal GotoPosition = LbaVec3()\n";
						file << "\t\tGotoPosition.x = "<< roundNB((sceneTracks[pointId].X/512.f)) << std::endl;
						file << "\t\tGotoPosition.y = "<< roundNB((sceneTracks[pointId].Y/256.f)-1) << std::endl;
						file << "\t\tGotoPosition.z = "<< roundNB((sceneTracks[pointId].Z/512.f)) << std::endl;
						file << "\tlocal movSpeed = gActorsMap[ActorId][\"MoveSpeed\"]\n";	
						file << "\tEnvironment:ActorGoTo(ScriptId, ActorId, GotoPosition, movSpeed)\n";
						break;//MAPFUNC("GOTO_POINT_3D", mGOTO_POINT_3D),
					case 0x10:
						file << "\tgActorsMap[ActorId][\"MoveSpeed\"] = " << *(int16*)scriptPtr/512.f << std::endl; 		
						scriptPtr+=2; 
						break;//MAPFUNC("SPEED", mSPEED),
					case 0x11:
						file << "\t-- BACKGROUND " << (int)(*scriptPtr++) << std::endl; 	
						break;//MAPFUNC("BACKGROUND", mBACKGROUND),
					case 0x12: 
						file << "\tEnvironment:ActorSleep(ScriptId, ActorId, "<< (int)(*scriptPtr) * 1000 <<")\n";	
						scriptPtr+=5; 
						break;//MAPFUNC("WAIT_NUM_SECOND", mWAIT_NUM_SECOND),
					case 0x13:
						file << "\tEnvironment:ActorAppearDisappear(ScriptId, ActorId, false)" << std::endl;
						break;//MAPFUNC("NO_BODY", mNO_BODY),
					case 0x14:
						angle = ((*(int16*)scriptPtr)%1024) * 360.0f / 1024.0f;
						file << "\tEnvironment:SetActorRotation(ScriptId, ActorId, "<< angle <<")\n"; 
						scriptPtr+=2; 
						break;//MAPFUNC("BETA", mBETA),
					case 0x15:
						move = *(int16 *)scriptPtr/-512.f;
						file << "\tlocal position = Environment:GetActorPosition(ScriptId, ActorId)\n";
						file << "\tposition.z = position.z + "<< move <<"\n";
						file << "\tlocal movSpeed = gActorsMap[ActorId][\"MoveSpeed\"]\n";	
						file << "\tgActorsMap[ActorId][CloseX] = 0\n";
						file << "\tgActorsMap[ActorId][CloseZ] = "<< -move <<"\n";
						file << "\tgActorsMap[ActorId][AsyncID] = Environment:Async_ActorGoTo(ScriptId, ActorId, position, movSpeed)\n";
						scriptPtr+=2; 
						break;//MAPFUNC("OPEN_LEFT", mOPEN_LEFT),
					case 0x16:
						move = *(int16 *)scriptPtr/512.f;
						file << "\tlocal position = Environment:GetActorPosition(ScriptId, ActorId)\n";
						file << "\tposition.z = position.z + "<< move <<"\n";
						file << "\tlocal movSpeed = gActorsMap[ActorId][\"MoveSpeed\"]\n";	
						file << "\tgActorsMap[ActorId][CloseX] = 0\n";
						file << "\tgActorsMap[ActorId][CloseZ] = "<< -move <<"\n";
						file << "\tgActorsMap[ActorId][AsyncID] = Environment:Async_ActorGoTo(ScriptId, ActorId, position, movSpeed)\n";
						scriptPtr+=2; 
						break;//MAPFUNC("OPEN_RIGHT", mOPEN_RIGHT),
					case 0x17:
						move = *(int16 *)scriptPtr/-512.f;
						file << "\tlocal position = Environment:GetActorPosition(ScriptId, ActorId)\n";
						file << "\tposition.x = position.x + "<< move <<"\n";
						file << "\tlocal movSpeed = gActorsMap[ActorId][\"MoveSpeed\"]\n";	
						file << "\tgActorsMap[ActorId][CloseX] = "<< -move <<"\n";
						file << "\tgActorsMap[ActorId][CloseZ] = 0\n";
						file << "\tgActorsMap[ActorId][AsyncID] = Environment:Async_ActorGoTo(ScriptId, ActorId, position, movSpeed)\n";
						scriptPtr+=2;
						break;//MAPFUNC("OPEN_UP", mOPEN_UP),
					case 0x18:
						move = *(int16 *)scriptPtr/512.f;
						file << "\tlocal position = Environment:GetActorPosition(ScriptId, ActorId)\n";
						file << "\tposition.x = position.x + "<< move <<"\n";
						file << "\tlocal movSpeed = gActorsMap[ActorId][\"MoveSpeed\"]\n";	
						file << "\tgActorsMap[ActorId][CloseX] = "<< -move <<"\n";
						file << "\tgActorsMap[ActorId][CloseZ] = 0\n";
						file << "\tgActorsMap[ActorId][AsyncID] = Environment:Async_ActorGoTo(ScriptId, ActorId, position, movSpeed)\n";
						scriptPtr+=2;
						break;//MAPFUNC("OPEN_DOWN", mOPEN_DOWN),
					case 0x19:
						file << "\tlocal position = Environment:GetActorPosition(ScriptId, ActorId)\n";
						file << "\tposition.x = position.x + gActorsMap[ActorId][CloseX]\n";
						file << "\tposition.z = position.z + gActorsMap[ActorId][CloseZ]\n";
						file << "\tlocal movSpeed = gActorsMap[ActorId][\"MoveSpeed\"]\n";	
						file << "\tgActorsMap[ActorId][CloseX] = 0\n";
						file << "\tgActorsMap[ActorId][CloseZ] = 0\n";
						file << "\tgActorsMap[ActorId][AsyncID] = Environment:Async_ActorGoTo(ScriptId, ActorId, position, movSpeed)\n";
						break;//MAPFUNC("CLOSE", mCLOSE),
					case 0x1A:
						file << "\tlocal syncId = gActorsMap[ActorId][AsyncID]\n";
						file << "\tif syncId and syncId >= 0 then\n";
						file << "\t\tEnvironment:WaitForAsyncScript(ScriptId, syncId)\n";
						file << "\t\tgActorsMap[ActorId][AsyncID] = -1\n";
						file << "\tend\n";
						break;//MAPFUNC("WAIT_DOOR", mWAIT_DOOR),
					case 0x1B:
						file << "\tPlaySoundOnActor(Environment, ScriptId, ActorId, "<< *(int16*)scriptPtr <<", 1, true)\n";
						scriptPtr+=2; 
						break;//MAPFUNC("SAMPLE_RND", mSAMPLE_RND),
					case 0x1C: 
						file << "\tPlaySoundOnActor(Environment, ScriptId, ActorId, "<< *(int16*)scriptPtr <<", -1, false)\n";
						scriptPtr+=2; 
						break;//MAPFUNC("SAMPLE_ALWAYS", mSAMPLE_ALWAYS),
					case 0x1D: 
						file << "\tStopSoundOnActor(Environment, ScriptId, ActorId, "<< *(int16*)scriptPtr <<")\n";
						scriptPtr+=2; 
						break;//MAPFUNC("SAMPLE_STOP", mSAMPLE_STOP),
					case 0x1E:
						file << "\t-- PLAY_FLA" << std::endl;
						break;//MAPFUNC("PLAY_FLA", mPLAY_FLA),
					case 0x1F: 
						repeatSample = *(int16 *)scriptPtr;
						scriptPtr+=2; 
						break;//MAPFUNC("REPEAT_SAMPLE", mREPEAT_SAMPLE),
					case 0x20: 
						file << "\tPlaySoundOnActor(Environment, ScriptId, ActorId, "<< *(int16*)scriptPtr <<", "<< repeatSample <<", true)\n";
						repeatSample = 1;
						scriptPtr+=2; 
						break;//MAPFUNC("SIMPLE_SAMPLE", mSIMPLE_SAMPLE),
					case 0x21: 
						file << "\t-- FACE_HERO" << std::endl; 
						scriptPtr+=2; 
						break;//MAPFUNC("FACE_HERO", mFACE_HERO),
					case 0x22:
						angle = ((*(int16*)scriptPtr)%1024) * 360.0f / 1024.0f;
						file << "\tlocal rndAngle = math.random()\n";
						file << "\trndAngle = rndV - 0.5\n";
						file << "\trndAngle = 90 + rndAngle * "<< angle <<"\n";
						file << "\tlocal rotSpeed = gActorsMap[ActorId][\"RotationSpeed\"]\n";
						file << "\tRotateActorTo(Environment, ScriptId, ActorId, rndAngle, rotSpeed)\n";
						scriptPtr+=4;
						break;//MAPFUNC("ANGLE_RND", mANGLE_RND)
					}
				} while (scriptPtr != (sceneActors[i].moveScript + sceneActors[i].movingScriptSize));
			}
		}


		// save triggers
		for (size_t i = 0; i < triggers[j].size(); i++)
		{
			triggers[j][i]->SaveToLuaFile(fileActor);
		}

		fileActor << "end" << std::endl;
		file.close();
		fileActor.close();
	}
}




int main(int argc, char *argv[]) {

	sceneHero = &sceneActors[0];

	extractInfo();
	return 0;
}