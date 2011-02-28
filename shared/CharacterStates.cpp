#include "CharacterStates.h"

#ifndef _LBANET_SERVER_SIDE_
#include "SynchronizedTimeHandler.h"
#include "EventsQueue.h"
#endif

//! tell state that current animation has finished
//! return true if animation should be paused
bool StateDying::AnimationFinished()
{

#ifndef _LBANET_SERVER_SIDE_
	//inform server that dying state should resume
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::RaiseFromDeadEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble()));
#endif

	// pause animation until server force state change in client
	return true;
}