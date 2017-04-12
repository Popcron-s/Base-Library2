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
	_Graph* ani[8];
	void* pointer[4];

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
		temp.pos = {3.0f, 0.0f, 0.0f};
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

		scr = t_skel.Begin();
		scr.Left(0);
		ani[0] = new _Graph_template<FLOAT>(scr.Data().rot.z,5);	//LU	//-15~30
		pointer[0] = scr;
		scr.Left(0);
		ani[1] = new _Graph_template<FLOAT>(scr.Data().rot.z,3);	//LD	//0~15
		pointer[1] = scr;
		scr.Prev(); scr.Prev(); scr.Right(0);
		ani[2] = new _Graph_template<FLOAT>(scr.Data().rot.z,5);	//RU	//-15~30
		pointer[2] = scr;
		scr.Left(0);
		ani[3] = new _Graph_template<FLOAT>(scr.Data().rot.z,3);	//RD	//0~15
		pointer[3] = scr;

		_Graph_template<FLOAT>* t_ani = (_Graph_template<FLOAT>*)(ani[0]);
		t_ani->SetNode(0, (3.141592f*(-15.0f))/180.0f, _GRAPH::LINEAR,    0);
		t_ani->SetNode(1,							0, _GRAPH::LINEAR,  200);
		t_ani->SetNode(2, (3.141592f*( 45.0f))/180.0f, _GRAPH::LINEAR,  800);
		t_ani->SetNode(3,							0, _GRAPH::LINEAR, 1400);
		t_ani->SetNode(4, (3.141592f*(-15.0f))/180.0f, _GRAPH::LINEAR, 1600);
		t_ani->SetLoop(true);
		t_ani->Play();

		t_ani = (_Graph_template<FLOAT>*)(ani[1]);
		t_ani->SetNode(0,							0, _GRAPH::LINEAR,    0);
		t_ani->SetNode(1, (3.141592f*( 15.0f))/180.0f, _GRAPH::LINEAR,  800);
		t_ani->SetNode(2,							0, _GRAPH::LINEAR, 1600);
		t_ani->SetLoop(true);
		t_ani->Play();

		t_ani = (_Graph_template<FLOAT>*)(ani[2]);
		t_ani->SetNode(0, (3.141592f*( 45.0f))/180.0f, _GRAPH::LINEAR,    0);
		t_ani->SetNode(1,							0, _GRAPH::LINEAR,  600);
		t_ani->SetNode(2, (3.141592f*(-15.0f))/180.0f, _GRAPH::LINEAR,  800);
		t_ani->SetNode(3,							0, _GRAPH::LINEAR, 1000);
		t_ani->SetNode(4, (3.141592f*( 45.0f))/180.0f, _GRAPH::LINEAR, 1600);
		t_ani->SetLoop(true);
		t_ani->Play();

		t_ani = (_Graph_template<FLOAT>*)(ani[3]);
		t_ani->SetNode(0, (3.141592f*( 15.0f))/180.0f, _GRAPH::LINEAR,    0);
		t_ani->SetNode(1,							0, _GRAPH::LINEAR,  800);
		t_ani->SetNode(2, (3.141592f*( 15.0f))/180.0f, _GRAPH::LINEAR, 1600);
		t_ani->SetLoop(true);
		t_ani->Play();

		SetMesh(new MESH);
		MESH& t_mesh = *(GetMesh());
		t_mesh.vtx = new VERTEX[4];
		t_mesh.vtx_num = 4;
		t_mesh.vtx[0] = {{-1.0f, -1.0f, 0.0f},{0.0f, 1.0f, 1.0f, 1.0f},{},{0.0f, 0.0f}};
		t_mesh.vtx[1] = {{ 1.0f, -1.0f, 0.0f},{1.0f, 0.0f, 1.0f, 1.0f},{},{1.0f, 0.0f}};
		t_mesh.vtx[2] = {{-1.0f,  1.0f, 0.0f},{1.0f, 1.0f, 0.0f, 1.0f},{},{0.0f, 1.0f}};
		t_mesh.vtx[3] = {{ 1.0f,  1.0f, 0.0f},{1.0f, 1.0f, 1.0f, 1.0f},{},{1.0f, 1.0f}};
		t_mesh.indexed = nullptr;
		t_mesh.material = nullptr;

		IMAGE img = {};
		UINT size = 0;
		BYTE* buf = nullptr;
		_FileLoader::GetSingleton()->FileLoader("sprites_sample.bmp", &size, &buf);
		BMPDecoder(buf, size, &img);
		_O_Graphics::GetSingleton()->RegisterTexture(&img, (void**)&(t_mesh.material));

		_Graph_template<VECTOR2>* t_ani2 = nullptr;
		ani[4] = new _Graph_template<VECTOR2>(t_mesh.vtx[0].tex, 5);
		t_ani2 = (_Graph_template<VECTOR2>*)(ani[4]);
		t_ani2->SetNode(0, {0.00f, 0.0f}, _GRAPH::POINT,   0);
		t_ani2->SetNode(1, {0.25f, 0.0f}, _GRAPH::POINT, 150);
		t_ani2->SetNode(2, {0.50f, 0.0f}, _GRAPH::POINT, 300);
		t_ani2->SetNode(3, {0.75f, 0.0f}, _GRAPH::POINT, 450);
		t_ani2->SetNode(4, {0.00f, 0.0f}, _GRAPH::POINT, 600);
		t_ani2->SetLoop(true);
		t_ani2->Play();

		ani[5] = new _Graph_template<VECTOR2>(t_mesh.vtx[1].tex, 5);
		t_ani2 = (_Graph_template<VECTOR2>*)(ani[5]);
		t_ani2->SetNode(0, {0.25f, 0.0f}, _GRAPH::POINT,   0);
		t_ani2->SetNode(1, {0.50f, 0.0f}, _GRAPH::POINT, 150);
		t_ani2->SetNode(2, {0.75f, 0.0f}, _GRAPH::POINT, 300);
		t_ani2->SetNode(3, {1.00f, 0.0f}, _GRAPH::POINT, 450);
		t_ani2->SetNode(4, {0.00f, 0.0f}, _GRAPH::POINT, 600);
		t_ani2->SetLoop(true);
		t_ani2->Play();

		ani[6] = new _Graph_template<VECTOR2>(t_mesh.vtx[2].tex, 5);
		t_ani2 = (_Graph_template<VECTOR2>*)(ani[6]);
		t_ani2->SetNode(0, {0.00f, 1.0f}, _GRAPH::POINT,   0);
		t_ani2->SetNode(1, {0.25f, 1.0f}, _GRAPH::POINT, 150);
		t_ani2->SetNode(2, {0.50f, 1.0f}, _GRAPH::POINT, 300);
		t_ani2->SetNode(3, {0.75f, 1.0f}, _GRAPH::POINT, 450);
		t_ani2->SetNode(4, {0.00f, 1.0f}, _GRAPH::POINT, 600);
		t_ani2->SetLoop(true);
		t_ani2->Play();

		ani[7] = new _Graph_template<VECTOR2>(t_mesh.vtx[3].tex, 5);
		t_ani2 = (_Graph_template<VECTOR2>*)(ani[7]);
		t_ani2->SetNode(0, {0.25f, 1.0f}, _GRAPH::POINT,   0);
		t_ani2->SetNode(1, {0.50f, 1.0f}, _GRAPH::POINT, 150);
		t_ani2->SetNode(2, {0.75f, 1.0f}, _GRAPH::POINT, 300);
		t_ani2->SetNode(3, {1.00f, 1.0f}, _GRAPH::POINT, 450);
		t_ani2->SetNode(4, {0.00f, 1.0f}, _GRAPH::POINT, 600);
		t_ani2->SetLoop(true);
		t_ani2->Play();
	}
	~test_obj(){Map::GetSingleton()->GetLayer(0).RemoveObject(this);}
	void update(){
		WLTree<JOINT>::searcher scr;
		for(UINT i = 0 ; i<4 ; ++i){
			(ani[i])->update(MainSystem::GetSingleton()->GetTick());
			scr = pointer[i];
			scr.Prev();
			MATRIX4x4 p = scr.Data().world;
			scr = pointer[i];
			scr.Data().world = Graphic_Renderer::SetWorldMatrix(scr.Data().pos, scr.Data().rot, scr.Data().scl, p);
		}
		for(UINT i = 4 ; i<8 ; ++i){
			(ani[i])->update(MainSystem::GetSingleton()->GetTick());
		}
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