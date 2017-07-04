// dllmain.cpp : Defines the entry point for the DLL application.

#include "stdafx.h"
#include <iostream>
#include <stdio.h>

#include "memory.h"
#include "hooks.h"

DWORD WINAPI myMainThread(LPVOID lpParam) {
	//Allocate a console
	AllocConsole();
	//Windows Magic for the stdout to be redirected to the new one:
	freopen("CONOUT$", "w", stdout);
	DWORD global_program_base = 0x400000;//why doesn't this work?, try with FS:0 : (DWORD)GetModuleHandle(NULL)
	std::wcout << "Attached. Base is at 0x" << std::hex << global_program_base << std::endl;
	hookStringCopy((DWORD)&printDialogueLine);
	return 1;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		auto thread = CreateThread(NULL, 0, &myMainThread, NULL, 0, NULL);
		CloseHandle(thread);
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}