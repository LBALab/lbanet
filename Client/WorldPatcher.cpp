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


#include "WorldPatcher.h"
#include "LogHandler.h"
#include "FileUtil.h"

#include <IcePatch2/ClientUtil.h>

#include <fstream>

class TextPatcherFeedback : public IcePatch2::PatcherFeedback
{
public:

	TextPatcherFeedback(const std::string & logpath) :
	  _pressAnyKeyMessage(false), logfile(logpath.c_str())
    {
#ifndef _WIN32
        tcgetattr(0, &_savedTerm);
        _savedFlags = fcntl(0, F_GETFL);
        _block = true;
#endif
    }

    virtual ~TextPatcherFeedback()
    {
#ifndef _WIN32
        tcsetattr(0, TCSANOW, &_savedTerm);
        fcntl(0, F_SETFL, _savedFlags);
#endif
    }

	virtual bool noFileSummary(const std::string& reason)
    {
        logfile << "Cannot load file summary:\n" << reason << std::endl;
		logfile << "Starting a thorough patch..." << std::endl;
        return true;
    }

    virtual bool checksumStart()
    {
        return true;
    }

    virtual bool checksumProgress(const std::string& path)
    {
        logfile << "Calculating checksum for " << path << std::endl;
        return true;
    }

    virtual bool checksumEnd()
    {
        return true;
    }

    virtual bool fileListStart()
    {
        _lastProgress = "0%";
        logfile << "Getting list of files to patch: " << _lastProgress << std::flush;
        return true;
    }

	virtual bool fileListProgress(Ice::Int percent)
    {
        for(unsigned int i = 0; i < _lastProgress.size(); ++i)
        {
            logfile << '\b';
        }
        std::ostringstream s;
        s << percent << '%';
        _lastProgress = s.str();
        logfile << _lastProgress << std::flush;
        return true;
    }

    virtual bool fileListEnd()
    {
        logfile << std::endl;
        return true;
    }

	virtual bool patchStart(const std::string& path, Ice::Long size, Ice::Long totalProgress, Ice::Long totalSize)
    {
        std::ostringstream s;
        s << "0/" << size << " (" << totalProgress << '/' << totalSize << ')';
        _lastProgress = s.str();
        logfile << path << ' ' << _lastProgress << std::flush;
        return true;
    }

    virtual bool patchProgress(Ice::Long progress, Ice::Long size, Ice::Long totalProgress, Ice::Long totalSize)
    {
        for(unsigned int i = 0; i < _lastProgress.size(); ++i)
        {
            logfile << '\b';
        }
        std::ostringstream s;
        s << progress << '/' << size << " (" << totalProgress << '/' << totalSize << ')';
        _lastProgress = s.str();
        logfile << _lastProgress << std::flush;
        return true;
    }

    virtual bool patchEnd()
    {
        logfile << std::endl;
        return true;
    }

private:

	std::string _lastProgress;
    bool _pressAnyKeyMessage;
	std::ofstream logfile;
};


bool WorldPatcher::PatchWorld(const std::string & worldname, const std::string & directory, 
							IcePatch2::FileServerPrx patcherserver)
{
	// first make sure that the directory exist
	FileUtil::CreateNewDirectory(directory);

	IcePatch2::PatcherFeedbackPtr feedback = new TextPatcherFeedback(worldname+"_patch.log");
	IcePatch2::PatcherPtr patcher = 
		new IcePatch2::Patcher(patcherserver, feedback, directory, false, 100, 0);

	try 
	{
		LogHandler::getInstance()->LogToFile("Start pathing for world: " + directory, 1);
		bool aborted = !patcher->prepare();
		if(!aborted)
			aborted = !patcher->patch("");
		if(!aborted)
			patcher->finish();

		if(aborted)
			LogHandler::getInstance()->LogToFile("Pathing aborted.", -1);
		else
			LogHandler::getInstance()->LogToFile("Pathing terminated successfully.", 1);

		return !aborted;
	} 
	catch(const std::string& reason) 
	{
		LogHandler::getInstance()->LogToFile("Pathing error: "+reason, -1);
	}

	return false;
}
