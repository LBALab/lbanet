#include "QuestHandler.h"
#include "Quest.h"

QuestHandler* QuestHandler::_Instance = NULL;


/***********************************************************
singleton pattern
***********************************************************/
QuestHandler * QuestHandler::getInstance()
{
    if(!_Instance)
    {
        _Instance = new QuestHandler();
		return _Instance;
    }
    else
    {
		return _Instance;
    }
}



/***********************************************************
add quest
***********************************************************/
void QuestHandler::AddQuest(QuestPtr quest)
{
	Lock sync(*this);
	_quests[quest->GetId()] = quest;
}


/***********************************************************
remove quest
***********************************************************/
void QuestHandler::RemoveQuest(long id)
{
	Lock sync(*this);
	std::map<long, QuestPtr>::iterator it = _quests.find(id);
	if(it != _quests.end())
		_quests.erase(it);
}



/***********************************************************
get quest
***********************************************************/
QuestPtr QuestHandler::GetQuest(long id)
{
	Lock sync(*this);
	std::map<long, QuestPtr>::iterator it = _quests.find(id);
	if(it != _quests.end())
		return it->second;

	return QuestPtr();
}




/***********************************************************
quest list
***********************************************************/
std::map<long, QuestPtr> QuestHandler::GetQuests()
{
	Lock sync(*this);
	return _quests;
}


/***********************************************************
start quest for player
***********************************************************/
bool QuestHandler::StartQuest(ScriptEnvironmentBase * owner, long id, long playerid)
{
	Lock sync(*this);
	std::map<long, QuestPtr>::iterator it = _quests.find(id);
	if(it != _quests.end())
	{
		it->second->StartQuest(owner, playerid);
		return true;
	}

	return false;
}

/***********************************************************
check if quest is done for player
***********************************************************/
bool QuestHandler::QuestFinished(ScriptEnvironmentBase * owner, long id, long playerid)
{
	Lock sync(*this);
	std::map<long, QuestPtr>::iterator it = _quests.find(id);
	if(it != _quests.end())
		return it->second->QuestFinished(owner, playerid);

	return false;
}


/***********************************************************
return quest chapter
***********************************************************/
int QuestHandler::GetQuestChapter(long id)
{
	Lock sync(*this);
	std::map<long, QuestPtr>::iterator it = _quests.find(id);
	if(it != _quests.end())
		return it->second->GetChapter();

	return -1;
}


/***********************************************************
generate quest id
***********************************************************/
long QuestHandler::GenerateQuestid()
{
	Lock sync(*this);
	if(_quests.size() == 0)
		return 1;

	return (_quests.rbegin()->second->GetId() + 1);
}