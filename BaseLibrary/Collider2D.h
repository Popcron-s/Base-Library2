#pragma once

#include "..\\Common\\variable.h"
#include "Skeletal.h"

enum class COLLIDER2D : UINT{
	POINT = 0x0,
	LINE = 0x1,
	BOX = 0x2,
	CIRCLE = 0x3,
	POLYGON = 0x100
};

class __declspec(dllexport) COL2D{
public:
	JOINT* joint;
	virtual COLLIDER2D GetType() = 0;
};
/*
struct tPOINT{
	FLOAT x,y,z;
};
*/
class LINE{
public:
	FLOAT3 st, ed;

	FLOAT LengthSq(){
		FLOAT x = ed.x - st.x;
		FLOAT y = ed.y - st.y;
		FLOAT z = ed.z - st.z;

		FLOAT lth = (x*x) + (y*y) + (z*z);
		lth = (lth>=0.0f)?lth:-lth;

		return lth;
	}
	FLOAT Length(){
		FLOAT x = ed.x - st.x;
		FLOAT y = ed.y - st.y;
		FLOAT z = ed.z - st.z;

		FLOAT lth = (x*x) + (y*y) + (z*z);
		lth = (lth>=0.0f)?lth:-lth;

		//sqrt(lth)

		return lth;
	}
};

class __declspec(dllexport) BOX : public COL2D{
public:
	FLOAT3 _1, _2, _3, _4;

	COLLIDER2D GetType(){return COLLIDER2D::BOX;}
};

class __declspec(dllexport) CIRCLE : public COL2D{
public:
	FLOAT3 o;
	FLOAT r;

	COLLIDER2D GetType(){return COLLIDER2D::CIRCLE;}
};

struct POLYGON{
	FLOAT3* p;
	UINT num;
};