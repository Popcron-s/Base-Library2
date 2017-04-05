#pragma once

#include <Windows.h>
#include "..\\Common\\variable.h"

extern "C"{
	void WindowCreate(HINSTANCE hInstance, LPWSTR Title, int *nCmdShow, 
		int x = 1280, int y = 720);
	void MainLoop(void (*)());
	//WIN_API void MessageHandler(bool (*MsgHandler)(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lPAram));
	void Run();

	HWND GetHWND();
}

extern "C"{
	//WIN_API void InitOpenGLwithWin32();
	//WIN_API HDC GetWin32GLBackBuffer();

	bool Init();
	bool Clear();
	bool Start(SCREEN*);
	bool RenderObject(RENDER_OBJECT*);
	bool End();
	bool Present();
	void* RegisterTexture(IMAGE*, void**);
	bool GetBackBuffer(UINT width, UINT height, UINT* buf);

	bool FileLoader(char* name, UINT* size, BYTE** buf);
}