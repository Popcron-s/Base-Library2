#include "Header.h"

#include "..\\Win32\\Win32_API.h"
#include "..\\Win32\\Win32_API.cpp"

#include "..\\BaseLibrary\\MainSystem.h"
#include "..\\BaseLibrary\\Collision2D.h"

#include "..\\Coder\Coder.h"

void Start(HINSTANCE hInst, LPWSTR name, int& CmdShow, void (*cf)(), UINT x, UINT y){
	MainSystem::CommonUpdate = cf;
	FLOAT fx = x;	FLOAT fy = y;	fx /= 2.0f;	fy /= 2.0f;
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	WindowCreate(hInst, L"Console In Test", &CmdShow, x+10, y+10);
	Init(_INTERFACE::GRAPHIC::OpenGL);
	MainSystem::GetSingleton()->SetScreen(x, y);
	Graphic_Renderer::GetSingleton()->CreateScreen(
	{0,0,x,y,
		Graphic_Renderer::SetViewMatrix({0.0f, 0.0f, -10.0f},{0.0f, 0.0f, 0.0f},{0.0f, -1.0f, 0.0f}),
		Graphic_Renderer::SetOrthoProjectionMatrix(-fx, fx, -fy, fy, -50.0f, 50.0f)
	});
	MainLoop(&(MainSystem::MainLoop));
	Run();
	CoUninitialize();
}

void CreateLayer(UINT num){Map::GetSingleton()->CreateLayer(num);}
void DestroyLayer(){Map::GetSingleton()->DestroyLayer();}

void RegistObject(void* target, UINT layer){Map::GetSingleton()->RegistObject((OBJECT*)target, layer);}
void RemoveObject(void* target, UINT layer){Map::GetSingleton()->RemoveObject((OBJECT*)target, layer);}

void* RegistTexture(IMAGE& i, void*& texture){
	return _O_Graphics::GetSingleton()->RegistTexture(i, texture);}
bool ScreenShot(char* name){
	IMAGE i = {};
	i.width = MainSystem::GetSingleton()->GetScreenX();
	i.height = MainSystem::GetSingleton()->GetScreenY();
	i.buf = new BYTE[(i.width)*(i.height)*4];
	i.alpha_able = true;
	i.bit_depth = 24; 
	_O_Graphics::GetSingleton()->GetBackBuffer(i.width, i.height, (UINT*)i.buf);
	BYTE* buf = nullptr;
	UINT buf_size = 0;
	if(!BMPEncoder(buf, buf_size, i)){return false;}
	if(!_FileIO::GetSingleton()->FileWrite(name, buf_size, buf)){delete [] buf; return false;}
	delete [] buf;
	delete [] i.buf;
}

bool RegistSound(SOUND s, UINT loop){return _O_Sounds::GetSingleton()->RegistGraph(s, loop);}
bool AllRemoveSound(){return false;}

void Move2DCamera(FLOAT3 v){
	Graphic_Renderer::GetSingleton()->GetScreen(0)->view = 
		Graphic_Renderer::SetViewMatrix({v.x, v.y, -10.0f}, {v.x, v.y, 0.0f}, {0.0f, -1.0f, 0.0f});
}

UINT GetTick(){return MainSystem::GetSingleton()->GetTick();}
KEYBOARD* GetKeyboard(){return MainSystem::GetSingleton()->GetKeyboard();}
MOUSE* GetMouse(){return MainSystem::GetSingleton()->GetMouse();}
FLOAT2 ClickOrtho(){
	return MainSystem::GetSingleton()->ClickOrtho(
		MainSystem::GetSingleton()->GetMouse()->x, 
		MainSystem::GetSingleton()->GetMouse()->y);
}

bool CheckCollision2D(COL2D& base, COL2D& target){
	return Collision2D::GetSingleton()->Collision(base, target);}
bool CheckCollision2D(FLOAT2 mouse_pos, COL2D& target){
	return Collision2D::GetSingleton()->Raycast(mouse_pos.x, mouse_pos.y ,target);}

bool LoadBMP(char* name, IMAGE& g){
	BYTE* buf = nullptr;
	UINT buf_size = 0;
	if(!_FileIO::GetSingleton()->FileRead(name, buf_size, buf)){return false;}
	if(!BMPDecoder(buf, buf_size, g)){delete [] buf; return false;}
	delete [] buf;
	return true;
}
bool SaveBMP(char* name, IMAGE& g){
	BYTE* buf = nullptr;
	UINT buf_size = 0;
	if(!BMPEncoder(buf, buf_size, g)){return false;}
	if(!_FileIO::GetSingleton()->FileWrite(name, buf_size, buf)){delete [] buf; return false;}
	delete [] buf;
	return true;
}
bool LoadPNG(char* name, IMAGE& g){
	BYTE* buf = nullptr;
	UINT buf_size = 0;
	if(!_FileIO::GetSingleton()->FileRead(name, buf_size, buf)){return false;}
	if(!PNGDecoder(buf, buf_size, g)){delete [] buf; return false;}
	delete [] buf;
	return true;
}
bool LoadWAV(char* name, SOUND& s){
	BYTE* buf = nullptr;
	UINT buf_size = 0;
	if(!_FileIO::GetSingleton()->FileRead(name, buf_size, buf)){return false;}
	if(!WAVDecoder(buf, buf_size, s)){delete [] buf; return false;}
	delete [] buf;
	return true;
}