// EveHook.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "EveHook.h"


// This is an example of an exported variable
EVEHOOK_API int nEveHook=0;

// This is an example of an exported function.
EVEHOOK_API int fnEveHook(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see EveHook.h for the class definition
CEveHook::CEveHook()
{
    return;
}
