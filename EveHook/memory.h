#pragma once
#include <Windows.h>

template<typename T>
T readMemory(LPVOID addr) {
	return *((T*)addr);
}

template<typename T>
void writeMemory(LPVOID addr, T val) {
	*((T*)addr) = val;
}

template<typename T>
DWORD protectMemory(LPVOID adr, DWORD prot) {
	DWORD oldProt;
	VirtualProtect(adr, sizeof(T), prot, &oldProt);
	return oldProt;
}