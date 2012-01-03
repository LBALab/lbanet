#include "HolomapHandler.h"
#include "Holomap.h"

HolomapHandler* HolomapHandler::_Instance = NULL;


/***********************************************************
singleton pattern
***********************************************************/
HolomapHandler * HolomapHandler::getInstance()
{
    if(!_Instance)
    {
        _Instance = new HolomapHandler();
		return _Instance;
    }
    else
    {
		return _Instance;
    }
}



/***********************************************************
add holomap
***********************************************************/
void HolomapHandler::AddHolomap(HolomapPtr holo)
{
	_holomaps[holo->GetId()] = holo;
}


/***********************************************************
remove holomap
***********************************************************/
void HolomapHandler::RemoveHolomap(long id)
{
	std::map<long, HolomapPtr>::iterator it = _holomaps.find(id);
	if(it != _holomaps.end())
		_holomaps.erase(it);
}



/***********************************************************
get holomap
***********************************************************/
HolomapPtr HolomapHandler::GetHolomap(long id)
{
	std::map<long, HolomapPtr>::iterator it = _holomaps.find(id);
	if(it != _holomaps.end())
		return it->second;

	return HolomapPtr();
}





/***********************************************************
add holomap
***********************************************************/
void HolomapHandler::AddHolomapLoc(HolomapLocationPtr holo)
{
	_holomaplocs[holo->GetId()] = holo;
}


/***********************************************************
remove holomap
***********************************************************/
void HolomapHandler::RemoveHolomapLoc(long id)
{
	std::map<long, HolomapLocationPtr>::iterator it = _holomaplocs.find(id);
	if(it != _holomaplocs.end())
		_holomaplocs.erase(it);
}



/***********************************************************
get holomap
***********************************************************/
HolomapLocationPtr HolomapHandler::GetHolomapLoc(long id)
{
	std::map<long, HolomapLocationPtr>::iterator it = _holomaplocs.find(id);
	if(it != _holomaplocs.end())
		return it->second;

	return HolomapLocationPtr();
}





/***********************************************************
add holomap
***********************************************************/
void HolomapHandler::AddHolomapPath(HolomapTravelPathPtr holo)
{
	_holomappaths[holo->GetId()] = holo;
}


/***********************************************************
remove holomap
***********************************************************/
void HolomapHandler::RemoveHolomapPath(long id)
{
	std::map<long, HolomapTravelPathPtr>::iterator it = _holomappaths.find(id);
	if(it != _holomappaths.end())
		_holomappaths.erase(it);
}



/***********************************************************
get holomap
***********************************************************/
HolomapTravelPathPtr HolomapHandler::GetHolomapPath(long id)
{
	std::map<long, HolomapTravelPathPtr>::iterator it = _holomappaths.find(id);
	if(it != _holomappaths.end())
		return it->second;

	return HolomapTravelPathPtr();
}