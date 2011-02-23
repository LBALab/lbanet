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

