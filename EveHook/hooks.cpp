#include "hooks.h"
#include "stdafx.h"
#include <iostream>
#include "memory.h"

extern DWORD global_program_base;

DWORD _stdcall printDialogueLine(DWORD arg_0, DWORD arg_4, DWORD arg_8)
{
	DWORD global_program_base;//calcular la base de vuelta
	std::cout << "arg_0: 0x" << std::hex << arg_0 
			<< " arg_4: 0x" << std::hex << arg_4
			<< " arg_8: 0x" << std::hex << arg_8 << std::endl;
	
	signed int hookAt = global_program_base + 0x5BB7;
	signed int oldFuncAddr = hookAt + 5 + (signed int)0xFFFFFA14;

	std::cout << "oldFuncAddr = " << oldFuncAddr;
	
	DWORD retVal;
	//call the original function
	__asm {
		MOV EDX, arg_8
		PUSH EDX
		MOV EDX, arg_4
		PUSH EDX
		MOV EDX, arg_0
		PUSH EDX
		MOV EBX, [oldFuncAddr]
		CALL EBX
		MOV [retVal], EAX
	}

	return retVal;
}

DWORD hookStringCopy(DWORD newFunc)
{
	DWORD hookAt = (0x400000 + 0x5BB7);//global_program_base
	DWORD newOffset = newFunc - hookAt - 5;
	DWORD oldProtection =
		protectMemory<DWORD>((LPVOID)(hookAt + 1), PAGE_EXECUTE_READWRITE);
	std::cout << "oldProt = " << std::hex << oldProtection << std::endl;
	DWORD originalOffset = readMemory<DWORD>((LPVOID)(hookAt + 1));
	writeMemory<DWORD>((LPVOID)(hookAt + 1), newOffset);
	protectMemory<DWORD>((LPVOID)(hookAt + 1), oldProtection);
	return originalOffset + hookAt + 5;
}