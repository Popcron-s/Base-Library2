#pragma once

#include "..\\Common\\Enum.h"
#include "..\\Common\\Tree.h"
#include "..\\Common\\List.h"
#include "..\\Common\\variable.h"

//object
struct VERTEX{
	FLOAT4 pos;
	FLOAT4 diffuse;
	FLOAT3 normal;
	FLOAT2 tex;
};

struct INDEXED{

};

struct RENDER_OBJECT{
	FLOAT3 position;
	FLOAT3 rotation;
	FLOAT3 scale;
	MATRIX4x4 world;
	VERTEX* vtx;
	UINT vtx_num;
	INDEXED* indexed;
	MATERIAL* material;
	//shader
};

struct SCREEN{
	UINT x,y,width,height;
	MATRIX4x4 view,proj;
};

struct ROOT_OBJECT{
	FLOAT3 position;
	FLOAT3 rotation;
	FLOAT3 scale;
	MATRIX4x4 world;

	BTree<RENDER_OBJECT>* graphic_root;
};