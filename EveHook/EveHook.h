// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the EVEHOOK_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// EVEHOOK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef EVEHOOK_EXPORTS
#define EVEHOOK_API __declspec(dllexport)
#else
#define EVEHOOK_API __declspec(dllimport)
#endif

// This class is exported from the EveHook.dll
class EVEHOOK_API CEveHook {
public:
	CEveHook(void);
	// TODO: add your methods here.
};

extern EVEHOOK_API int nEveHook;

EVEHOOK_API int fnEveHook(void);
