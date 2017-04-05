#include <Windows.h>
#include "Windows.h"
#include "OpenGL.h"
#include "FileLoader.h"

bool WINAPI DllMain(HINSTANCE hInstace, DWORD fdwReason, LPVOID lpReserved) {
	if(fdwReason == DLL_PROCESS_ATTACH){
		_Win32FileLoader::GetSingleton();
	}
	if(fdwReason == DLL_PROCESS_DETACH){
		OpenGL::Destroy();
		Windows::Destroy();
	}
	return true;
}