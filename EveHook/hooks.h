#pragma once
#include <iostream>
#include <Windows.h>
#include <iostream>
#include <string>

#include "MsgStruct.h"
#include "FileStruct.h"


extern DWORD global_program_base;

DWORD __fastcall printDialogueLine(FileStruct *thisPtr, DWORD trash, DlgLnStruct* dlgLnPtr);

//DWORD hookStringCopy(DWORD newFunc);

DWORD hook(DWORD newFunc, DWORD hookAt);

bool findWavNameAndDrop(DlgLnStruct *msgLine, std::string& wavToPlay);

std::wstring string_to_wstring(const std::string& str);

//void pollForStopSound();
