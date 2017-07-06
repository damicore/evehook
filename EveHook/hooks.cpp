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
	bool thereIsWav = findWavNameAndDrop(thisPtr, wavToPlay);
	wavToPlay += ".wav";
	std::wstring wwavToPlay = string_to_wstring(wavToPlay);
	if (thereIsWav) {
		PlaySound(wwavToPlay.c_str(), NULL, SND_ASYNC);
		size_8 = size_8 - (wavToPlay.size() - 5);
	}
	else {
		PlaySound(NULL, NULL, SND_ASYNC);
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

//Find the wavName, crop it from the name and return a bool. Populate wavNameRet with the wav name minus ".wav"
bool findWavNameAndDrop(MsgStruct *msgStruct, std::string& wavNameRet)
{
	std::cout << "--------------------" << std::endl;
	std::cout << msgStruct->getSize() << std::endl;
	std::cout << msgStruct->getString() << std::endl;
	std::cout << "--------------------" << std::endl;
	bool found = FALSE;
	std::string msgString = msgStruct->getString();
	const size_t wavNamePos = msgString.find('#');
	if (wavNamePos != std::string::npos) {
		wavNameRet = msgString.substr(wavNamePos + 1, msgStruct->getSize() - 2 - wavNamePos); //-2 to crop the quoting marks
		msgString.erase(wavNamePos, wavNameRet.size() + 1);
		//msgString.append("\"");
		msgStruct->setStr(msgString);
		found = TRUE;
	}
	std::cout << msgStruct->getSize()<< std::endl;
	std::cout << msgStruct->getString() << std::endl;
	std::cout << wavNameRet << std::endl;
	std::cout << "--------------------" << std::endl;
	return found;
}

std::wstring string_to_wstring(const std::string& str) {
	return std::wstring(str.begin(), str.end());
}
/*
void pollForStopSound() { //this isn't working
	while (::g_isSoundPlaying) {
		short state = GetAsyncKeyState(VK_LBUTTON);
		std::cout << state << std::endl;
		if (state) {
			::g_isSoundPlaying = FALSE;
			Sleep(500);
			PlaySound(NULL, NULL, SND_ASYNC);
		}
	}
}*/