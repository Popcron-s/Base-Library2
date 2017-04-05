#include "OpenGL.h"

#include <gl\GL.h>
#pragma comment (lib, "OpenGL32.lib")

#define __OPERATOR_MATRIX(m) {m._11, m._12, m._13, m._14, m._21, m._22, m._23, m._24, \
						m._31, m._32, m._33, m._34, m._41, m._42, m._43, m._44}

_O_Graphics* OpenGL::GetSingleton(){
	if(m_pSingleton == nullptr){
		m_pSingleton = new OpenGL;
	}
	return m_pSingleton;
}

OpenGL::OpenGL(){
	if(m_hdc){DeleteDC(m_hdc);}
}
OpenGL::~OpenGL(){
	wglDeleteContext(m_hrc);
	DeleteDC(m_hdc);
}

_INTERFACE::GRAPHIC::TYPE OpenGL::GetType(){return _INTERFACE::GRAPHIC::OpenGL;}

bool OpenGL::Init(){
	PIXELFORMATDESCRIPTOR pfd =                             // 픽셀 포맷 설정 구조체
	{
		sizeof(PIXELFORMATDESCRIPTOR),                          // 사이즈
		1,                                                      // 버전 숫자
		PFD_DRAW_TO_WINDOW |                                    // 윈도우를 지원
		PFD_SUPPORT_OPENGL |                                    // GL을 지원
		PFD_DOUBLEBUFFER,                                       // 더블 버퍼링 사용
		PFD_TYPE_RGBA,                                          // RGBA 포맷 사용
		24,                                                     // 색상 비트 수
		8, 0, 8, 0, 8, 0, 										// 컬러 비트 무시
		8, 0,													// Alpha bit
		0,                                                      // Accumulation Buffer 사용하지 않음
		0, 0, 0, 0,                                             // Accumulation Bits 무시
		32,                                                     // 16Bit Z-Buffer 사용 
		0,                                                      // Stencil Buffer 사용하지 않음
		0,                                                      // Auxiliary Buffer 사용하지 않음
		PFD_MAIN_PLANE,                                         // 메인 드로잉 레이어
		0,                                                      // 무시
		0, 0, 0                                                 // Layer Masks 무시
	};

	m_hdc = GetDC(Windows::GetSingleton()->Gethwnd());                                  // DC 획득
	unsigned int PixelFormat = ChoosePixelFormat(m_hdc, &pfd);        // pfd와 DC를 통해 픽셀포맷 설정
	SetPixelFormat(m_hdc, PixelFormat, &pfd);                 // PixelFormat값을 통해 픽셀포맷 설정

	m_hrc = wglCreateContext(m_hdc);                        // RC 획득
	wglMakeCurrent(m_hdc, m_hrc);                            // GL측에서 RC 지정

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClearDepth(1.0f);
	//glDepthFunc(GL_LESS);
	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

bool OpenGL::Clear(){glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); return true;}
bool OpenGL::Start(SCREEN* scr){
	glViewport(scr->x,scr->y,scr->width,scr->height);
	GLfloat view_mat[16] = __OPERATOR_MATRIX(scr->view);
	GLfloat proj_mat[16] = __OPERATOR_MATRIX(scr->proj);
	
	glLoadMatrixf(view_mat);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(proj_mat);
	glMatrixMode(GL_MODELVIEW);
	return true;
}
bool OpenGL::RenderObject(RENDER_OBJECT* r_obj){
	GLfloat world[16] = __OPERATOR_MATRIX(r_obj->world);
	glLoadIdentity();
	glPopMatrix();
	glPushMatrix();
	glMultMatrixf(world);

	if(r_obj->material != nullptr){
		glBindTexture(GL_TEXTURE_2D, (GLuint)r_obj->material);
		glEnable(GL_TEXTURE_2D);
	}
	else{glDisable(GL_TEXTURE_2D);}

	glBegin(GL_TRIANGLE_STRIP);
	for(UINT i = 0; i<r_obj->vtx_num ; ++i){
		glNormal3f(r_obj->vtx[i].normal.x,r_obj->vtx[i].normal.y,r_obj->vtx[i].normal.z);
		glColor4f(r_obj->vtx[i].diffuse.x, r_obj->vtx[i].diffuse.y, r_obj->vtx[i].diffuse.z, r_obj->vtx[i].diffuse.w);
		glTexCoord2f(r_obj->vtx[i].tex.x, r_obj->vtx[i].tex.y);
		glVertex3f(r_obj->vtx[i].pos.x,r_obj->vtx[i].pos.y,r_obj->vtx[i].pos.z);
	}
	glEnd();
	return true;
}
bool OpenGL::End(){
	glFlush();
	return true;
}
bool OpenGL::Present(){SwapBuffers(m_hdc); return true;}

bool OpenGL::GetBackBuffer(UINT width, UINT height, UINT* Color){
	if(Color == nullptr){return false;}
	glReadBuffer(GL_FRONT);
	glReadPixels(0,0,width,height,GL_RGBA,GL_UNSIGNED_BYTE,Color);
	glReadBuffer(GL_BACK);
	return true;
}

void* OpenGL::RegisterTexture(IMAGE* img, void** material){
	glGenTextures(1, (GLuint*)material);
	glBindTexture(GL_TEXTURE_2D, (GLuint)*material);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	if(img->alpha_able){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->buf);
	}
	else
	{
		UINT t_size = img->width*img->height*4;
		BYTE* t_buf = new BYTE[t_size];
		for(UINT i = 0 ; i<t_size ; ++i){
			if(i%4 == 3){t_buf[i] = 0xFF;}
			else{t_buf[i] = img->buf[i-(i/4)];}
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, t_buf);
		delete [] t_buf;
	}
	return *material;
}