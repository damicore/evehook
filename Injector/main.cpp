#include <iostream>
#include <Windows.h>
#include <direct.h>

using namespace std;

int main() {
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	wchar_t* exeName = L"EVE98.exe"; 
	CreateProcessW(L"EVE98.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
	HANDLE processHandle = pi.hProcess;

	//Write the dll name to the game's memory
	wchar_t* dllName = 
		L"EveHook.dll";
	int namelen = wcslen(dllName);
	LPVOID remoteString =
		VirtualAllocEx(processHandle, NULL, namelen * 2, MEM_COMMIT, PAGE_EXECUTE);
	WriteProcessMemory(processHandle, remoteString, dllName, namelen * 2, NULL);

	//Getting the address of LoadLibraryW()
	HMODULE k32 = GetModuleHandleA("kernel32.dll");
	LPVOID funcAdr = GetProcAddress(k32, "LoadLibraryW");

	//Create the thread to call LoadLibraryW(dllName)
	HANDLE thread =
		CreateRemoteThread(processHandle, NULL, NULL,
		(LPTHREAD_START_ROUTINE)funcAdr,
			remoteString, NULL, NULL);

	WaitForSingleObject(thread, INFINITE);
	CloseHandle(thread);
}

