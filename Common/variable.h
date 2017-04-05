#pragma once

#ifdef _M_X64
typedef __int64				INT;
typedef unsigned __int64	UINT;
typedef double				FLOAT;
#else
typedef int					INT;
typedef unsigned int		UINT;
typedef float				FLOAT;
#endif

typedef unsigned char BYTE;

//default
typedef struct FLOAT2{
	FLOAT x;
	FLOAT y;
}VECTOR2;

typedef struct FLOAT3{
	FLOAT x;
	FLOAT y;
	FLOAT z;
}VECTOR3;

typedef struct FLOAT4{
	FLOAT x;
	FLOAT y;
	FLOAT z;
	FLOAT w;
}VECTOR4;

typedef struct FLOAT2x2{
	FLOAT _11, _12;
	FLOAT _21, _22;
}MATRIX2x2;

typedef struct FLOAT3x3{
	FLOAT _11, _12, _13;
	FLOAT _21, _22, _23;
	FLOAT _31, _32, _33;
}MATRIX3x3;

typedef struct FLOAT4x4{
	FLOAT _11, _12, _13, _14;
	FLOAT _21, _22, _23, _24;
	FLOAT _31, _32, _33, _34;
	FLOAT _41, _42, _43, _44;
}MATRIX4x4;

//Interface
struct MOUSE{
	INT x, y, z;
	BYTE button[8];
};

struct KEYBOARD{
	BYTE KEY[256];
};

//resource
struct IMAGE{
	UINT width;
	UINT height;
	UINT bit_depth;
	bool alpha_able;
	BYTE* buf;
};

struct AUDIO{

};

struct MATERIAL{

};