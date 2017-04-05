#pragma once

#include "..\\Common\\variable.h"
#include "..\\Common\\Enum.h"

class baseObject{
protected:
	FLOAT3 position;
	FLOAT3 rotation;
	FLOAT3 scale;
	MATRIX4x4 world;

public:
	//virtual _OBJECT::TYPE GetType(){return _OBJECT::NONE;}
	//virtual void render() = 0;
	//static UINT Size(){return sizeof(baseObject);}
};