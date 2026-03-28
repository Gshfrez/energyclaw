#pragma once
#pragma once
#ifdef NETACCESS_EXPORTS
#define NETACCESS_API				__declspec(dllexport)
#else
#define NETACCESS_API				__declspec(dllimport)
#endif
#include "BaseCore.h"
#include "BASENETH.H"
NETACCESS_API bool Net_Access(int pjnb);
NETACCESS_API const char* NetInfo_ToAI(int pjtNb);