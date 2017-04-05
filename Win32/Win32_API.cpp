#pragma once

#include "Win32_API.h"

#include "Windows.cpp"
#include "OpenGL.cpp"

void WindowCreate(HINSTANCE hInstance, LPWSTR Title, int *nCmdShow, int x, int y){
	return Windows::GetSingleton()->Create(hInstance, Title, nCmdShow, x, y);}
bool Init(_INTERFACE::GRAPHIC::TYPE type){
	_Win32FileLoader::GetSingleton();
	_Win32Timer::GetSingleton();
	_Win32Input::GetSingleton();
	switch(type){
	case _INTERFACE::GRAPHIC::OpenGL :
		return OpenGL::GetSingleton()->Init();
	case _INTERFACE::GRAPHIC::DX9 :
		return false;
	case _INTERFACE::GRAPHIC::DX11 :
		return false;
	}
}
void MainLoop(void (*render)()){Windows::GetSingleton()->Render = render;}
void Render(){return Windows::GetSingleton()->Run();}