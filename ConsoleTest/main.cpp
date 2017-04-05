#include <iostream>
#include "..\\Win32\\Win32_API.h"
#include "..\\Win32\\Win32_API.cpp"

#include "..\\Coder\\BMPDecoder.h"
#include "..\\Coder\\BMPEncoder.h"

#include <io.h>
#include <fcntl.h>
#include <share.h>
#include <sys\\stat.h>

#include "..\\BaseLibrary\\MainSystem.h"
#include "..\\BaseLibrary\\Map.h"
#include "..\\BaseLibrary\\Object.h"

#include "..\\Common\\Tree.h"

class test_obj : public OBJECT{
private:
	float f;
	bool turn;

public:
	test_obj(){
		Map::GetSingleton()->RegistObject(this, 0);

		SetPosition({0.0f, 0.0f, 0.0f});
		SetRotation({0.0f, 0.0f, 0.0f});
		SetScale({1.0f, 1.0f, 1.0f});
		SetWorld();
		
		SetSkeletal(new SKELETAL);
		WLTree<JOINT>& t_skel = GetSkeletal()->skeletal;

		JOINT temp = {};
		temp.pos = {1.0f, 0.0f, 0.0f};
		temp.rot = {0.0f, 0.0f, 0.0f};
		temp.scl = {0.6f, 1.0f, 1.0f};
		temp.world = Graphic_Renderer::SetWorldMatrix(temp.pos, temp.rot, temp.scl, GetWorld());
		temp.mesh.vtx = new VERTEX[4];
		temp.mesh.vtx[0] = {{-1.0f, -1.0f, 0.0f},{0.0f, 1.0f, 1.0f, 1.0f},{},{0.0f, 0.0f}};
		temp.mesh.vtx[1] = {{ 1.0f, -1.0f, 0.0f},{1.0f, 0.0f, 1.0f, 1.0f},{},{1.0f, 0.0f}};
		temp.mesh.vtx[2] = {{-1.0f,  1.0f, 0.0f},{1.0f, 1.0f, 0.0f, 1.0f},{},{0.0f, 1.0f}};
		temp.mesh.vtx[3] = {{ 1.0f,  1.0f, 0.0f},{1.0f, 1.0f, 1.0f, 1.0f},{},{1.0f, 1.0f}};
		temp.mesh.vtx_num = 4;

		t_skel.CreateRoot(temp);

		WLTree<JOINT>::searcher scr = t_skel.Begin();

		temp.pos = { 1.0f,-0.5f, 0.0f};
		temp.rot = { 0.0f, 0.0f, 0.0f};
		temp.scl = { 0.3f, 0.5f, 1.0f};
		temp.world = Graphic_Renderer::SetWorldMatrix(temp.pos, temp.rot, temp.scl, scr.Data().world);
		t_skel.Create(scr, LEFT, temp);
		temp.pos = {-1.0f,-0.5f, 0.0f};
		temp.rot = { 0.0f, 0.0f, 0.0f};
		temp.scl = { 0.3f, 0.5f, 1.0f};
		temp.world = Graphic_Renderer::SetWorldMatrix(temp.pos, temp.rot, temp.scl, scr.Data().world);
		t_skel.Create(scr, RIGHT, temp);
		
		scr.Left(0);

		temp.pos = {0.0f, 2.0f, 0.0f};
		temp.rot = {0.0f, 0.0f, 0.0f};
		temp.scl = {1.0f, 1.0f, 1.0f};
		temp.world = Graphic_Renderer::SetWorldMatrix(temp.pos, temp.rot, temp.scl, scr.Data().world);
		t_skel.Create(scr, LEFT, temp);

		scr.Prev(); scr.Right(0);

		temp.pos = {0.0f, 2.0f, 0.0f};
		temp.rot = {0.0f, 0.0f, 0.0f};
		temp.scl = {1.0f, 1.0f, 1.0f};
		temp.world = Graphic_Renderer::SetWorldMatrix(temp.pos, temp.rot, temp.scl, scr.Data().world);
		t_skel.Create(scr, LEFT, temp);

		f = 0.0f;
		turn = false;
	}
	~test_obj(){Map::GetSingleton()->GetLayer(0).RemoveObject(this);}
	void update(){
		(turn)?f+=0.5f:f-=0.5f;
		std::cout<< f <<std::endl;
		WLTree<JOINT>::searcher scr = GetSkeletal()->skeletal.Begin();
		MATRIX4x4 p = scr.Data().world;
		scr.Left(0);
		scr.Data().rot = {0.0f, 0.0f, (3.141592f*((f*3.0f)-15.0f))/180.0f};
		scr.Data().world = Graphic_Renderer::SetWorldMatrix(scr.Data().pos, scr.Data().rot, scr.Data().scl, p);
		p = scr.Data().world;

		scr.Left(0);
		scr.Data().rot = {0.0f, 0.0f, (3.141592f*f)/180.0f};
		scr.Data().world = Graphic_Renderer::SetWorldMatrix(scr.Data().pos, scr.Data().rot, scr.Data().scl, p);
		
		scr.Prev(); scr.Prev(); p = scr.Data().world; scr.Right(0);
		scr.Data().rot = {0.0f, 0.0f, (3.141592f*((-f*3.0f)+30.0f))/180.0f};
		scr.Data().world = Graphic_Renderer::SetWorldMatrix(scr.Data().pos, scr.Data().rot, scr.Data().scl, p);
		p = scr.Data().world;

		scr.Left(0);
		scr.Data().rot = {0.0f, 0.0f, (3.141592f*(-f+15.0f))/180.0f};
		scr.Data().world = Graphic_Renderer::SetWorldMatrix(scr.Data().pos, scr.Data().rot, scr.Data().scl, p);
		
		if(f >= 15.0f){turn = false;}
		else if(f <= 0.0f){turn = true;}
	}
};

void main(){
	HINSTANCE hInst=GetModuleHandle(NULL);
	int CmdShow = SW_SHOW;
	WindowCreate(hInst, L"Console In Test", &CmdShow);
	Init(_INTERFACE::GRAPHIC::OpenGL);

	Graphic_Renderer::SetOrthoProjectionMatrix(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	Graphic_Renderer::GetSingleton()->CreateScreen(
		{0,0,1280,720,
		Graphic_Renderer::SetViewMatrix({0.0f, 0.0f, -10.0f},{0.0f, 0.0f, 0.0f},{0.0f, -1.0f, 0.0f}),
		Graphic_Renderer::SetPerspectiveProjectionMatrix(1280.0f/720.0f, 3.141592f/4.0f, 1.0f, 10000.0f)});
	Map::GetSingleton()->CreateLayer(1);

	test_obj test;

	MainLoop(&(MainSystem::Render));
	Render();

	return;
}