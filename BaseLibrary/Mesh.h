#pragma once

#include "..\\Common\\variable.h"

#include "Skeletal.h"

struct SCREEN{
	UINT x,y,width,height;
	MATRIX4x4 view,proj;
};

struct VERTEX{
	FLOAT4 pos;
	FLOAT4 diffuse;
	FLOAT3 normal;
	FLOAT2 tex;
};

struct INDEXED{
	struct _node{
		UINT _1,_2,_3;
	}*node;
	UINT m_num;
};

struct RENDER_OBJECT{
	MATRIX4x4 world;
	VERTEX* vtx;
	UINT vtx_num;
	INDEXED* indexed;
	MATERIAL* material;
	//shader
};

class __declspec(dllexport) MESH{
public:
	JOINT* joint;
	VERTEX* vtx;
	UINT vtx_num;
	INDEXED* indexed;
	MATERIAL* material;
	//shader

	RENDER_OBJECT GetGraphics(){
		return {
			joint->world, vtx, vtx_num, indexed, material
		};
	}
};