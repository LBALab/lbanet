#ifndef _PHYSX_ERRORSTREAM_H
#define _PHYSX_ERRORSTREAM_H

#include <sstream>
#include "LogHandler.h"

class PhysXErrorStream : public NxUserOutputStream
{
public:
	void reportError(NxErrorCode e, const char* message, const char* file, int line)
	{
		std::stringstream strs;
		strs<<"Error from PhysX - file: " << file <<" line: "<<line<<" -> ";

		switch (e)
		{
			case NXE_INVALID_PARAMETER:
				strs<< "invalid parameter";
				break;
			case NXE_INVALID_OPERATION:
				strs<< "invalid operation";
				break;
			case NXE_OUT_OF_MEMORY:
				strs<< "out of memory";
				break;
			case NXE_DB_INFO:
				strs<< "info";
				break;
			case NXE_DB_WARNING:
				strs<< "warning";
				break;
			default:
				strs<< "unknown error";
		}

		strs<< " : "<<message;
		LogHandler::getInstance()->LogToFile(strs.str(), -10);
	}

	NxAssertResponse reportAssertViolation(const char* message, const char* file, int line)
	{
		std::stringstream strs;
		strs<<"Error from PhysX - file: " << file <<" line: "<<line<<" -> ";
		strs<<"assert violation : "<<message;
		LogHandler::getInstance()->LogToFile(strs.str(), -10);

		return NX_AR_BREAKPOINT;
	}

	void print(const char* message)
	{
		std::stringstream strs;
		strs<<"Message from PhysX -> "<<message;
		LogHandler::getInstance()->LogToFile(strs.str(), 10);
	}
};



#endif
