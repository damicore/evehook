#pragma once
#include <iostream>
#include <Windows.h>
#include <iostream>

extern DWORD global_program_base;

DWORD _stdcall printDialogueLine(DWORD arg_0, DWORD arg_4, DWORD arg_8);

DWORD hookStringCopy(DWORD newFunc);