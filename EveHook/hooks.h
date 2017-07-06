#pragma once
#include <iostream>
#include <Windows.h>
#include <iostream>
#include <string>

#include "MsgStruct.h"


extern DWORD global_program_base;

DWORD __fastcall printDialogueLine(MsgStruct *thisPtr, DWORD trash, DWORD ptr_0, DWORD arg_4, DWORD arg_8);

DWORD hookStringCopy(DWORD newFunc);

bool findWavName(const MsgStruct *msgLine, std::string& wavToPlay);

std::wstring string_to_wstring(const std::string& str);

void pollForStopSound();
