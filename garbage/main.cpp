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

#include "test_walker.h"

void ScreenShot(){
	MainSystem::Render();
	IMAGE screenshot = {1280,720,0,true,new BYTE[1280*720*4]};
	OpenGL::GetSingleton()->GetBackBuffer(screenshot.width, screenshot.height, (UINT*)screenshot.buf);

	BYTE* en_buf = nullptr;
	UINT en_size = 0;
	int t_handle = 0;
	BMPEncoder(&en_buf,&en_size,&screenshot);

	_sopen_s(&t_handle, "test_save4.bmp", _O_WRONLY | _O_BINARY | _O_CREAT, _SH_DENYRD, _S_IWRITE);
	_write(t_handle, en_buf, en_size);
	_close(t_handle);

	delete [] screenshot.buf;
	delete [] en_buf;
}

void* material = nullptr;

void material_test(){
	UINT size = 0;
	BYTE* buf = nullptr;

	IMAGE image = {0,0,0,false,nullptr};
	if(_Win32FileLoader::GetSingleton()->FileLoader("test_24.bmp", &size, &buf)){
		std::cout<< size <<std::endl;
		/*char* str = new char[size];
		for(UINT i = 0 ; i<size ; ++i){
		str[i] = buf[i];
		}
		std::cout<< str <<std::endl;
		delete [] str;*/
		if(BMPDecoder(buf,size, &image)){
			HWND myconsole = GetConsoleWindow();
			HDC mydc = GetDC(myconsole);

			/*UINT i = 0;
			for(UINT y = 0 ; y<image.height ; ++y){
			for(UINT x = 0 ; x<image.width ; ++x){
			SetPixel(mydc, x, y, RGB(image.buf[i],image.buf[i+1],image.buf[i+2]));
			i+=3;
			}
			}*/

			std::cout<< _O_Graphics::GetSingleton()->RegisterTexture(&image, &material) <<std::endl;

			ReleaseDC(myconsole, mydc);
		}
	}

	delete [] image.buf;
	delete [] buf;
}

void object_test(){
	RENDER_OBJECT render_obj = {
		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 0.0f},
		{1.0f, 1.0f, 1.0f},
		{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},
		new VERTEX[4], 4, nullptr, (MATERIAL*)material
	};

	std::cout<<material<<std::endl;

	render_obj.vtx[0] = {{-1.0f,-1.0f,0.0f,1.0f},{1.0f,1.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f}};
	render_obj.vtx[1] = {{ 1.0f,-1.0f,0.0f,1.0f},{0.0f,1.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{1.0f,0.0f}};
	render_obj.vtx[2] = {{-1.0f, 1.0f,0.0f,1.0f},{1.0f,0.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{0.0f,1.0f}};
	render_obj.vtx[3] = {{ 1.0f, 1.0f,0.0f,1.0f},{1.0f,1.0f,0.0f,1.0f},{0.0f,0.0f,1.0f},{1.0f,1.0f}};

	ROOT_OBJECT* root_obj = new ROOT_OBJECT;
	root_obj->position = {0.0f, 0.0f, 0.0f};
	root_obj->rotation = {0.0f, 0.0f, 0.0f};
	root_obj->scale = {1.0f, 1.0f, 1.0f};
	root_obj->world = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	root_obj->graphic_root = new BTree<RENDER_OBJECT>(render_obj, nullptr);

	BTree<RENDER_OBJECT>* temp = (BTree<RENDER_OBJECT>*)(root_obj->graphic_root);
	
	Map::GetSingleton()->RegistObject(root_obj, 0);
}

objWalker* walker = new objWalker;

void loop(){
	walker->update();
	MainSystem::Render();
}

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
	//Graphic_Renderer::GetSingleton()->CreateScreen({100,100,1000,400,{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},{1,0,0,0,0,1,0,0,0,0,-1,0,0,0,0,1}});
	Map::GetSingleton()->CreateLayer(1);

	material_test();
	//object_test();
	//ScreenShot();

	walker->init();

	//MainLoop(&(MainSystem::Render));
	MainLoop(&loop);
	Render();

	delete walker;

	return;
}