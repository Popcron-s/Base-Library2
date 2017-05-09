#pragma once

#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#define WS_PCSWINDOW		(WS_OVERLAPPED	| \
                             WS_CAPTION		| \
                             WS_SYSMENU)
#define FRAMESIZE_X	(GetSystemMetrics(SM_CXFIXEDFRAME)*2)
#define FRAMESIZE_Y	((GetSystemMetrics(SM_CYFIXEDFRAME)*2) + GetSystemMetrics(SM_CYCAPTION))

// using WS_THICKFRAME = SM_CXSIZEFRAME / SM_CYSIZEFRAME
// unusing WS_THICKFRAME = SM_CXFIXEDFRAME / SM_CYFIXEDFRAME

class Windows{
private:
	HWND m_hwnd;
	MSG m_msg;
	WNDCLASS m_WndClass;
	HINSTANCE m_hInstance;

	POINT m_WinSize;

	static Windows* m_pSingleton;

	Windows(){}
	~Windows(){}

public:
	static Windows* GetSingleton();
	static void Destroy();

	void Create(HINSTANCE hInstance, LPWSTR Title, int *nCmdShow, int x = 1280, int y = 720);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
		WPARAM wParam, LPARAM lParam);
	void Run();

	POINT GetWindowSize(){return m_WinSize;}
	HWND Gethwnd(){return m_hwnd;}

	//bool (*MessageHandler)(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lPAram);
	bool MessageHandler(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lPAram){
		switch(iMsg){
		case WM_PAINT:
			break;
		default:
			return false;
		}
		return true;
	}
	void (*MainLoop)();
};