#pragma once

#include <Windows.h>
#include "..\\Common\\variable.h"

#ifdef WIN32_EXPORTS
#define WIN_API __declspec(dllexport)
#else
#define WIN_API __declspec(dllimport)
#pragma comment(lib,"..\\Release\\Win32.lib")
#endif

extern "C"{
	WIN_API void WindowCreate(HINSTANCE hInstance, LPWSTR Title, int *nCmdShow, 
		int x = 1280, int y = 720);
	WIN_API void MainLoop(void (*)());
	//WIN_API void MessageHandler(bool (*MsgHandler)(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lPAram));
	WIN_API void Run();

	WIN_API HWND GetHWND();
}

extern "C"{
	//WIN_API void InitOpenGLwithWin32();
	//WIN_API HDC GetWin32GLBackBuffer();

	WIN_API bool Init();
	WIN_API bool Clear();
	WIN_API bool Start(SCREEN*);
	WIN_API bool RenderObject(RENDER_OBJECT*);
	WIN_API bool End();
	WIN_API bool Present();
	WIN_API void* RegisterTexture(IMAGE*, void**);
	WIN_API bool GetBackBuffer(UINT width, UINT height, UINT* buf);

	WIN_API bool FileLoader(char* name, UINT* size, BYTE** buf);
}