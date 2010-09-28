#include "CharacterStates.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"

//! tell state that current animation has finished
//! return true if animation should be paused
bool StDying::AnimationFinished()
{
	//inform server that dying state should resume
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateStateEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), LbaNet::StNormal, 0));

	// pause animation until server force state change in client
	return true;
}