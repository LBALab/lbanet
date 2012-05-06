#include "AvailableWorldsHandler.h"


AvailableWorldsHandler* AvailableWorldsHandler::_singletoninstance = NULL;
 
/***********************************************************
constructor
***********************************************************/	
AvailableWorldsHandler::AvailableWorldsHandler(void)
{
}
 
/***********************************************************
destructor
***********************************************************/	
AvailableWorldsHandler::~AvailableWorldsHandler(void)
{

}

 
/***********************************************************
singleton pattern
***********************************************************/
AvailableWorldsHandler * AvailableWorldsHandler::getInstance()
{
    if(!_singletoninstance)
    {
        _singletoninstance = new AvailableWorldsHandler();
		return _singletoninstance;
    }
    else
    {
		return _singletoninstance;
    }
}

 
/***********************************************************
add a world to the list
***********************************************************/
void AvailableWorldsHandler::AddWorld(const WorldDesc &desc, const WorldServerInterfacePrx & proxy,
										const LbaNet::MaintenanceInterfacePrx& mproxy)
{
	IceUtil::Mutex::Lock lock(_mutex);
	_worldsinfo[desc.WorldName] = desc;

	WorldProxies prox;
	prox.proxy = proxy;
	prox.maintenance = mproxy;
	_worldsproxy[desc.WorldName] = prox;
}
 
/***********************************************************
remove a world from list
***********************************************************/
void AvailableWorldsHandler::RemoveWorld(const std::string worldname)
{
	IceUtil::Mutex::Lock lock(_mutex);
	std::map<std::string, WorldDesc>::iterator iti = _worldsinfo.find(worldname);
	if(iti != _worldsinfo.end())
		_worldsinfo.erase(iti);


	std::map<std::string, WorldProxies>::iterator itp = _worldsproxy.find(worldname);
	if(itp != _worldsproxy.end())
		_worldsproxy.erase(itp);
}
 
/***********************************************************
get list of worlds
***********************************************************/
WorldsSeq AvailableWorldsHandler::GetWorldList()
{
	IceUtil::Mutex::Lock lock(_mutex);
	WorldsSeq res;

	std::map<std::string, WorldDesc>::iterator it =	_worldsinfo.begin();
	std::map<std::string, WorldDesc>::iterator end = _worldsinfo.end();
	for(; it != end; ++it)
		res.push_back(it->second);

	return res;
}
 
/***********************************************************
get proxy to a specific world - NULL if not existing
***********************************************************/
WorldServerInterfacePrx AvailableWorldsHandler::GetWorldProxy(const std::string &worldname)
{
	IceUtil::Mutex::Lock lock(_mutex);
	std::map<std::string, WorldProxies>::iterator itp = _worldsproxy.find(worldname);
	if(itp != _worldsproxy.end())
		return itp->second.proxy;

	return NULL;
}
 
/***********************************************************
shutdown server
***********************************************************/
bool AvailableWorldsHandler::ShutdownWorldServer(const std::string &worldname)
{
	IceUtil::Mutex::Lock lock(_mutex);
	std::map<std::string, WorldProxies>::iterator itp = _worldsproxy.find(worldname);
	if(itp != _worldsproxy.end())
	{
		try
		{
			itp->second.maintenance->Shutdown();
			return true;
		}
		catch(...){}
	}

	return false;
}

 
/***********************************************************
check if server is started
***********************************************************/
bool AvailableWorldsHandler::ServerStarted(const std::string &worldname)
{
	IceUtil::Mutex::Lock lock(_mutex);
	std::map<std::string, WorldProxies>::iterator itp = _worldsproxy.find(worldname);
	return (itp != _worldsproxy.end());
}
