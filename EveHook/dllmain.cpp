// dllmain.cpp : Defines the entry point for the DLL application.

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <direct.h>
#include "memory.h"
#include "hooks.h"

DWORD WINAPI myMainThread(LPVOID lpParam) {
	//Allocate a console
	AllocConsole();
	//Windows Magic for the stdout to be redirected to the new one:
	freopen("CONOUT$", "w", stdout);
	//hookStringCopy((DWORD)&printDialogueLine);
	DWORD global_program_base = 0x400000;//why doesn't this work?, try with FS:0 : (DWORD)GetModuleHandle(NULL)
	DWORD hookAt = (global_program_base + 0x9526);//global_program_base
	hook((DWORD)&printDialogueLine, hookAt);
	char *path =_getcwd(NULL, 0);
	std::cout << path << std::endl;

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