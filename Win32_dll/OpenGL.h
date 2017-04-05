#pragma once

#include <Windows.h>
#include "Windows.h"
#include "..\\Interface\\Base_Output_Graphics.h"

class OpenGL : public _O_Graphics{
private:
	HDC m_hdc;
	HGLRC m_hrc;

	OpenGL();
	~OpenGL();

public:
	static _O_Graphics* GetSingleton();
	
	//void Init();
	//HDC GetBackBuffer();

	_INTERFACE::GRAPHIC::TYPE GetType();

	bool Init();
	bool Clear();
	bool Start(SCREEN*);
	bool RenderObject(RENDER_OBJECT*);
	bool End();
	bool Present();

	void* RegisterTexture(IMAGE*, void** material);
	bool GetBackBuffer(UINT width, UINT height, UINT* Color);
};