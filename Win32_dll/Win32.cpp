#include "Win32.h"
#include "Windows.h"
#include "OpenGL.h"
#include "FileLoader.h"

void WindowCreate(HINSTANCE hInstance, LPWSTR Title, int *nCmdShow, int x, int y){
	return Windows::GetSingleton()->Create(hInstance, Title, nCmdShow, x, y);
}
void MainLoop(void (*render)()){
	Windows::GetSingleton()->Render = render;
}

void MessageHandler(bool (*MsgHandler)(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lPAram)){
	::MessageBox(NULL, L"",L"",MB_OK);
	//Windows::GetSingleton()->MessageHandler = MsgHandler;
}

void Run(){
	return Windows::GetSingleton()->Run();
}

HWND GetHWND(){return Windows::GetSingleton()->Gethwnd();}

//void InitOpenGLwithWin32(){return OpenGL::GetSingleton()->Init();}

//HDC GetWin32GLBackBuffer(){return OpenGL::GetSingleton()->GetBackBuffer();}

bool Init(){return OpenGL::GetSingleton()->Init();}
bool Clear(){return OpenGL::GetSingleton()->Clear();}
bool Start(SCREEN* scr){return OpenGL::GetSingleton()->Start(scr);}
bool RenderObject(RENDER_OBJECT* r_obj){return OpenGL::GetSingleton()->RenderObject(r_obj);}
bool End(){return OpenGL::GetSingleton()->End();}
bool Present(){return OpenGL::GetSingleton()->Present();}
void* RegisterTexture(IMAGE* img, void** mtr){
	return OpenGL::GetSingleton()->RegisterTexture(img, mtr);}
bool GetBackBuffer(UINT width, UINT height, UINT* buf){
	return OpenGL::GetSingleton()->GetBackBuffer(width, height, buf);}

bool FileLoader(char* name, UINT* size, BYTE** buf){return _Win32FileLoader::GetSingleton()->FileLoader(name, size, buf);}