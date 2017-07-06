#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <mmsystem.h>
#include "memory.h"
#include "hooks.h"
#include "MsgStruct.h"

extern DWORD global_program_base;

bool g_isSoundPlaying = FALSE;

//fastcall because the function to hook seems to be a thiscall function, thus the second trash parameter (the value of EBX) must be dropped
DWORD __fastcall printDialogueLine(MsgStruct *thisPtr, DWORD trash, DWORD ptr_0, DWORD arg_4, DWORD size_8)
{
	//DWORD global_program_base;//calculate base again
	std::string wavToPlay;
	bool thereIsWav = findWavName(thisPtr, wavToPlay);
	wavToPlay += ".wav";
	std::wstring wwavToPlay = string_to_wstring(wavToPlay);
	if (thereIsWav) {
		PlaySound(wwavToPlay.c_str(), NULL, SND_ASYNC);
		::g_isSoundPlaying = TRUE;
		pollForStopSound();
	}
	
	signed int hookAt = 0x400000 + 0x5BB7; //global_program_base
	signed int oldFuncAddr = hookAt + 5 + (signed int)0xFFFFFA14;

	DWORD(__thiscall *oldFunc)(void*, DWORD, DWORD, DWORD) = 
		(DWORD(__thiscall *)(void*, DWORD, DWORD, DWORD))oldFuncAddr;

	return oldFunc(thisPtr, ptr_0, arg_4, size_8);
}

DWORD hookStringCopy(DWORD newFunc)
{
	DWORD hookAt = (0x400000 + 0x5BB7);//global_program_base
	DWORD newOffset = newFunc - hookAt - 5;
	DWORD oldProtection =
		protectMemory<DWORD>((LPVOID)(hookAt + 1), PAGE_EXECUTE_READWRITE);
	DWORD originalOffset = readMemory<DWORD>((LPVOID)(hookAt + 1));
	writeMemory<DWORD>((LPVOID)(hookAt + 1), newOffset);
	protectMemory<DWORD>((LPVOID)(hookAt + 1), oldProtection);
	return originalOffset + hookAt + 5;
}

bool findWavName(const MsgStruct *msgStruct, std::string& wavNameRet)
{
	bool found = FALSE;
	std::string msgString = msgStruct->getString();
	const size_t wavNamePos = msgString.find('#');
	if (wavNamePos != std::string::npos) {
		wavNameRet = msgString.substr(wavNamePos + 1, msgStruct->getSize() - 2 - wavNamePos); //-2 to crop the quoting marks
		found = TRUE;
	}
	return found;
}

std::wstring string_to_wstring(const std::string& str) {
	return std::wstring(str.begin(), str.end());
}

void pollForStopSound() { //this isn't working
	while (::g_isSoundPlaying) {
		short state = GetAsyncKeyState(VK_LBUTTON);
		std::cout << state << std::endl;
		if (!state) {
			::g_isSoundPlaying = FALSE;
			Sleep(1);
			PlaySound(NULL, NULL, SND_ASYNC);
		}
	}
}