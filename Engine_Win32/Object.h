#pragma once

#ifdef ENGINE_WIN32_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#include "..\\BaseLibrary\\Object.h"
#include "..\\BaseLibrary\\Skeletal.h"
#include "..\\BaseLibrary\\Mesh.h"
#include "..\\BaseLibrary\\Animation.h"
#include "..\\BaseLibrary\\Collider2D.h"
/*
struct DLL_API JOINT;
struct DLL_API SCREEN;
struct DLL_API VERTEX;
struct DLL_API INDEXED;
struct DLL_API RENDER_OBJECT;*/
class DLL_API MESH;
class DLL_API COL2D;
class DLL_API BOX;
class DLL_API CIRCLE;
class DLL_API _Graph;
class DLL_API ANIMATION;
class DLL_API OBJECT;