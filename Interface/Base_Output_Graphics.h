#pragma once

#include "..\\BaseLibrary\\Object.h"
#include "..\\Common\\variable.h"
#include "..\\Common\\Enum.h"

#include "InterfaceSingleton.h"

class _O_Graphics : public InterfaceSingleton<_O_Graphics>{
public:
	_O_Graphics(){}
	~_O_Graphics(){}

	virtual _INTERFACE::GRAPHIC::TYPE GetType() = 0;

	virtual bool Init() = 0;
	virtual bool Clear() = 0;
	virtual bool Start(SCREEN*) = 0;
	virtual bool RenderObject(RENDER_OBJECT*) = 0;
	virtual bool End() = 0;
	virtual bool Present() = 0;

	virtual void* RegisterTexture(IMAGE*, void** material) = 0;
	virtual bool GetBackBuffer(UINT width, UINT height, UINT* Color) = 0;
};