#pragma once

#include "Win32_API.h"

#include "Windows.cpp"
#include "OpenGL.cpp"

void WindowCreate(HINSTANCE hInstance, LPWSTR Title, int *nCmdShow, int x, int y){
	return Windows::GetSingleton()->Create(hInstance, Title, nCmdShow, x, y);}
bool Init(_INTERFACE::GRAPHIC type){
	_Win32FileIO::GetSingleton();
	_Win32Timer::GetSingleton();
	_Win32Input::GetSingleton();
	XAudio2::GetSingleton()->Init();
	switch(type){
	case _INTERFACE::GRAPHIC::OpenGL :
		return OpenGL::GetSingleton()->Init();
	case _INTERFACE::GRAPHIC::DX9 :
		return false;
	case _INTERFACE::GRAPHIC::DX11 :
		return false;
	default:
		return false;
	}
}
void MainLoop(void (*loop)()){Windows::GetSingleton()->MainLoop = loop;}
void Run(){return Windows::GetSingleton()->Run();}