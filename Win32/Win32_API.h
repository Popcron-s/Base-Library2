#pragma once

#include "Windows.h"
#include "OpenGL.h"
#include "FileLoader.h"
#include "Timer.h"
#include "WinInput.h"

void WindowCreate(HINSTANCE hInstance, LPWSTR Title, int *nCmdShow, int x = 1280, int y = 720);
bool Init(_INTERFACE::GRAPHIC::TYPE type);
void MainLoop(void (*render)());
void Render();