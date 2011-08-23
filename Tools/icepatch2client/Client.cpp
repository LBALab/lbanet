// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/Options.h>
#include <IceUtil/StringUtil.h>
#include <Ice/Application.h>
#include "Util.h"
#include <IcePatch2/ClientUtil.h>

#include <fstream>

#ifdef _WIN32
#   include <conio.h>
#else
#   include <fcntl.h>
#   include <termios.h>
#endif

using namespace std;
using namespace Ice;
using namespace IcePatch2;

class TextPatcherFeedback : public PatcherFeedback
{
public:

    TextPatcherFeedback() :
        _pressAnyKeyMessage(false), logfile("patching.log")
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

    virtual bool noFileSummary(const string& reason)
    {
        logfile << "Cannot load file summary:\n" << reason << endl;
		logfile << "Starting a thorough patch..." << endl;
        return true;
    }

    virtual bool checksumStart()
    {
        return true;
    }

    virtual bool checksumProgress(const string& path)
    {
        logfile << "Calculating checksum for " << getBasename(path) << endl;
        return true;
    }

    virtual bool checksumEnd()
    {
        return true;
    }

    virtual bool fileListStart()
    {
        _lastProgress = "0%";
        logfile << "Getting list of files to patch: " << _lastProgress << flush;
        return true;
    }

    virtual bool fileListProgress(Int percent)
    {
        for(unsigned int i = 0; i < _lastProgress.size(); ++i)
        {
            logfile << '\b';
        }
        ostringstream s;
        s << percent << '%';
        _lastProgress = s.str();
        logfile << _lastProgress << flush;
        return true;
    }

    virtual bool fileListEnd()
    {
        logfile << endl;
        return true;
    }

    virtual bool patchStart(const string& path, Long size, Long totalProgress, Long totalSize)
    {
        ostringstream s;
        s << "0/" << size << " (" << totalProgress << '/' << totalSize << ')';
        _lastProgress = s.str();
        logfile << getBasename(path) << ' ' << _lastProgress << flush;
        return true;
    }

    virtual bool patchProgress(Long progress, Long size, Long totalProgress, Long totalSize)
    {
        for(unsigned int i = 0; i < _lastProgress.size(); ++i)
        {
            logfile << '\b';
        }
        ostringstream s;
        s << progress << '/' << size << " (" << totalProgress << '/' << totalSize << ')';
        _lastProgress = s.str();
        logfile << _lastProgress << flush;
        return true;
    }

    virtual bool patchEnd()
    {
        logfile << endl;
        return true;
    }

private:

	string _lastProgress;
    bool _pressAnyKeyMessage;
	std::ofstream logfile;
};


class Client : public Application
{
public:

    virtual int run(int, char*[]);

private:

    void usage(const std::string&);
};

int
Client::run(int argc, char* argv[])
{
    PropertiesPtr properties = communicator()->getProperties();

    IceUtilInternal::Options opts;
    opts.addOpt("h", "help");
    opts.addOpt("v", "version");
    opts.addOpt("t", "thorough");
    
    vector<string> args;
    try
    {
#if defined(__BCPLUSPLUS__) && (__BCPLUSPLUS__ >= 0x0600)
        IceUtil::DummyBCC dummy;
#endif
        args = opts.parse(argc, (const char**)argv);
    }
    catch(const IceUtilInternal::BadOptException& e)
    {
        cerr << e.reason << endl;
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    if(opts.isSet("help"))
    {
        usage(argv[0]);
        return EXIT_SUCCESS;
    }
    if(opts.isSet("version"))
    {
        cout << ICE_STRING_VERSION << endl;
        return EXIT_SUCCESS;
    }
    if(opts.isSet("thorough"))
    {
        properties->setProperty("IcePatch2.Thorough", "1");
    }

    if(args.size() > 1)
    {
        cerr << argv[0] << ": too many arguments" << endl;
        usage(argv[0]);
        return EXIT_FAILURE;
    }
    if(args.size() == 1)
    {
        properties->setProperty("IcePatch2.Directory", simplify(args[0]));
    }

    bool aborted = false;

    try
    {
        PatcherFeedbackPtr feedback = new TextPatcherFeedback;
        PatcherPtr patcher = new Patcher(communicator(), feedback);

        aborted = !patcher->prepare();

        if(!aborted)
        {
            aborted = !patcher->patch("");
        }

        if(!aborted)
        {
            patcher->finish();
        }
    }
    catch(const string& ex)
    {
        cerr << argv[0] << ": " << ex << endl;
        return EXIT_FAILURE;
    }

    if(aborted)
    {
        cout << "\n[Aborted]" << endl;
        return EXIT_FAILURE;
    }
    else
    {
        return EXIT_SUCCESS;
    }
}


void Client::usage(const string& appName)
{
    string options =
        "Options:\n"
        "-h, --help           Show this message.\n"
        "-v, --version        Display the Ice version.\n"
        "-t, --thorough       Recalculate all checksums.";

    cerr << "Usage: " << appName << " [options] [DIR]" << endl;
    cerr << options << endl;
}


int main(int argc, char* argv[])
{
    Client app;
    return app.main(argc, argv);
}
