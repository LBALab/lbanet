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

#ifndef _QUEST_HANDLER_H__
#define _QUEST_HANDLER_H__

#include <map>
#include <boost/shared_ptr.hpp>
#include <IceUtil/Mutex.h>

class ScriptEnvironmentBase;
class Quest;
typedef boost::shared_ptr<Quest>	QuestPtr;


//! take care of shared data between process
class QuestHandler : public IceUtil::Mutex
{
public:
	// singleton pattern
	static QuestHandler * getInstance();

	//! destructor
	~QuestHandler(void){}


	//! add quest
	void AddQuest(QuestPtr quest);

	//! remove quest
	void RemoveQuest(long id);

	//! get quest
	QuestPtr GetQuest(long id);

	//! quest list
	std::map<long, QuestPtr> GetQuests();

	//! start quest for player
	bool StartQuest(ScriptEnvironmentBase * owner, long id, long playerid);

	//! check if quest is done for player
	bool QuestFinished(ScriptEnvironmentBase * owner, long id, long playerid);

	//! return quest chapter
	int GetQuestChapter(long id);

	//! generate quest id
	long GenerateQuestid();

protected:
	//! constructor
	QuestHandler(void){}

private:
	static QuestHandler *						_Instance;
	
	std::map<long, QuestPtr>					_quests;
};

#endif
