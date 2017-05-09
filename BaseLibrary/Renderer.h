#pragma once

#include "..\\Common\\Singleton.h"
#include "..\\Common\\List.h"
#include "..\\Interface\\Base_Output_Graphics.h"
#include "..\\Interface\\Base_Output_Sounds.h"

#include "Map.h"

class Graphic_Renderer : public Singleton<Graphic_Renderer>{
private:
	List<SCREEN> m_Screen;//List Screen

public:
	Graphic_Renderer(){}
	~Graphic_Renderer(){
		m_Screen.AllReleaseNode();
	}
	SCREEN& CreateScreen(SCREEN scr){
		return m_Screen.CreateNode(scr);
	}	//Create Screen
	SCREEN* GetScreen(UINT num){
		if(m_Screen.GetNumber() < num){return nullptr;}
		return &(m_Screen.GetData(num));
	}	//GetScreen
	static MATRIX4x4 SetWorldMatrix(FLOAT3 pos, FLOAT3 rot, FLOAT3 scl, MATRIX4x4 p_mat = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1}){
		//scale->rotation->Position
		MATRIX4x4 t_mat = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};

		FLOAT4 q = {
			(sin(rot.x/2)*cos(rot.y/2)*cos(rot.z/2))-(cos(rot.x/2)*sin(rot.y/2)*sin(rot.z/2)),
			(cos(rot.x/2)*sin(rot.y/2)*cos(rot.z/2))+(sin(rot.x/2)*cos(rot.y/2)*sin(rot.z/2)),
			(cos(rot.x/2)*cos(rot.y/2)*sin(rot.z/2))-(sin(rot.x/2)*sin(rot.y/2)*cos(rot.z/2)),
			(cos(rot.x/2)*cos(rot.y/2)*cos(rot.z/2))+(sin(rot.x/2)*sin(rot.y/2)*sin(rot.z/2))
		};

		//1-2yy-2zz , -2wz+2xy , 2wy+2xz
		//2wz+2xy , 1-2xx-2zz , -2wx+2yz
		//-2wy+2xz , 2wx+2yz , 1-2xx-2yy
		MATRIX3x3 t_rot = {
			1-(2*q.y*q.y)-(2*q.z*q.z), (2*q.x*q.y)-(2*q.w*q.z), (2*q.x*q.z)+(2*q.w*q.y),
			(2*q.x*q.y)+(2*q.w*q.z), 1-(2*q.x*q.x)-(2*q.z*q.z), (2*q.y*q.z)-(2*q.w*q.x),
			(2*q.x*q.z)-(2*q.w*q.y), (2*q.y*q.z)+(2*q.w*q.x), 1-(2*q.x*q.x)-(2*q.y*q.y)
		};

		t_mat._11 = scl.x * t_rot._11;
		t_mat._12 = scl.x * t_rot._12;
		t_mat._13 = scl.x * t_rot._13;
		t_mat._14 = 0;

		t_mat._21 = scl.y * t_rot._21;
		t_mat._22 = scl.y * t_rot._22;
		t_mat._23 = scl.y * t_rot._23;
		t_mat._14 = 0;

		t_mat._31 = scl.z * t_rot._31;
		t_mat._32 = scl.z * t_rot._32;
		t_mat._33 = scl.z * t_rot._33;
		t_mat._34 = 0;

		t_mat._41 = pos.x;
		t_mat._42 = pos.y;
		t_mat._43 = pos.z;
		t_mat._44 = 1;

		//parent * me
		MATRIX4x4 r_mat = {};
		
		r_mat._11 = (t_mat._11 * p_mat._11) + (t_mat._12 * p_mat._21) + (t_mat._13 * p_mat._31) + (t_mat._14 * p_mat._41);
		r_mat._12 = (t_mat._11 * p_mat._12) + (t_mat._12 * p_mat._22) + (t_mat._13 * p_mat._32) + (t_mat._14 * p_mat._42);
		r_mat._13 = (t_mat._11 * p_mat._13) + (t_mat._12 * p_mat._23) + (t_mat._13 * p_mat._33) + (t_mat._14 * p_mat._43);
		r_mat._14 = (t_mat._11 * p_mat._14) + (t_mat._12 * p_mat._24) + (t_mat._13 * p_mat._34) + (t_mat._14 * p_mat._44);

		r_mat._21 = (t_mat._21 * p_mat._11) + (t_mat._22 * p_mat._21) + (t_mat._23 * p_mat._31) + (t_mat._24 * p_mat._41);
		r_mat._22 = (t_mat._21 * p_mat._12) + (t_mat._22 * p_mat._22) + (t_mat._23 * p_mat._32) + (t_mat._24 * p_mat._42);
		r_mat._23 = (t_mat._21 * p_mat._13) + (t_mat._22 * p_mat._23) + (t_mat._23 * p_mat._33) + (t_mat._24 * p_mat._43);
		r_mat._24 = (t_mat._21 * p_mat._14) + (t_mat._22 * p_mat._24) + (t_mat._23 * p_mat._34) + (t_mat._24 * p_mat._44);

		r_mat._31 = (t_mat._31 * p_mat._11) + (t_mat._32 * p_mat._21) + (t_mat._33 * p_mat._31) + (t_mat._34 * p_mat._41);
		r_mat._32 = (t_mat._31 * p_mat._12) + (t_mat._32 * p_mat._22) + (t_mat._33 * p_mat._32) + (t_mat._34 * p_mat._42);
		r_mat._33 = (t_mat._31 * p_mat._13) + (t_mat._32 * p_mat._23) + (t_mat._33 * p_mat._33) + (t_mat._34 * p_mat._43);
		r_mat._34 = (t_mat._31 * p_mat._14) + (t_mat._32 * p_mat._24) + (t_mat._33 * p_mat._34) + (t_mat._34 * p_mat._44);

		r_mat._41 = (t_mat._41 * p_mat._11) + (t_mat._42 * p_mat._21) + (t_mat._43 * p_mat._31) + (t_mat._44 * p_mat._41);
		r_mat._42 = (t_mat._41 * p_mat._12) + (t_mat._42 * p_mat._22) + (t_mat._43 * p_mat._32) + (t_mat._44 * p_mat._42);
		r_mat._43 = (t_mat._41 * p_mat._13) + (t_mat._42 * p_mat._23) + (t_mat._43 * p_mat._33) + (t_mat._44 * p_mat._43);
		r_mat._44 = (t_mat._41 * p_mat._14) + (t_mat._42 * p_mat._24) + (t_mat._43 * p_mat._34) + (t_mat._44 * p_mat._44);

		return r_mat;
	}
	static MATRIX4x4 SetViewMatrix(FLOAT3 eye, FLOAT3 lookat, FLOAT3 up){
		//z axis : normalize(eye-lookat)
		FLOAT3 z_axis = {lookat.x-eye.x, lookat.y-eye.y, lookat.z-eye.z};
		FLOAT size = sqrt((z_axis.x*z_axis.x)+(z_axis.y*z_axis.y)+(z_axis.z*z_axis.z));
		z_axis.x /= size; z_axis.y /= size; z_axis.z /= size;
		//x axis : normalize(cross(z_axis, up));
		FLOAT3 x_axis = { (z_axis.y*up.z)-(z_axis.z*up.y),
			(z_axis.z*up.x)-(z_axis.x*up.z),
			(z_axis.x*up.y)-(z_axis.y*up.x)};
		size = sqrt((x_axis.x*x_axis.x)+(x_axis.y*x_axis.y)+(x_axis.z*x_axis.z));
		x_axis.x /= size; x_axis.y /= size; x_axis.z /= size;
		//y axis : normalize(cross(x_axis, z_axis));
		FLOAT3 y_axis = { (x_axis.y*z_axis.z)-(x_axis.z*z_axis.y),
			(x_axis.z*z_axis.x)-(x_axis.x*z_axis.z),
			(x_axis.x*z_axis.y)-(x_axis.y*z_axis.x)};
		size = sqrt((y_axis.x*y_axis.x)+(y_axis.y*y_axis.y)+(y_axis.z*y_axis.z));
		y_axis.x /= size; y_axis.y /= size; y_axis.z /= size;
		//pos : dot(x_axis,eye) dot(y_axis,eye) dot(z_axis,eye)
		FLOAT3 pos = {-((x_axis.x*eye.x)+(x_axis.y*eye.y)+(x_axis.z*eye.z)),
			-((y_axis.x*eye.x)+(y_axis.y*eye.y)+(y_axis.z*eye.z)),
			-((z_axis.x*eye.x)+(z_axis.y*eye.y)+(z_axis.z*eye.z))};

		//setting
		return {  x_axis.x, y_axis.x, z_axis.x, 0,
			x_axis.y, y_axis.y, z_axis.y, 0,
			x_axis.z, y_axis.z, z_axis.z, 0,
			pos.x,    pos.y,    pos.z, 1};
	}	//SetView
	static MATRIX4x4 SetOrthoProjectionMatrix(FLOAT l, FLOAT r, FLOAT t, FLOAT b, FLOAT n, FLOAT f){
		return {
			2/(r-l), 0,0,0,
			0, 2/(b-t),0,0,
			0,0, 2/(f-n),0,
			-((r+l)/(r-l)),-((b+t)/(b-t)),-((f+n)/(f-n)),1
		};
	}	//SetProjection
	static MATRIX4x4 SetPerspectiveProjectionMatrix(FLOAT aspect, FLOAT fovY, FLOAT n, FLOAT f){
		FLOAT y = n*tan(fovY/2);
		FLOAT x = y*aspect;
		FLOAT l = -x, r = x, t = -y, b = y;
		return {
			(2*n)/(r-l),0,0,0,
			0,(2*n)/(b-t),0,0,
			(r+l)/(r-l),(b+t)/(b-t),((f+n)/(f-n)),1,
			0,0,-((2*f*n)/(f-n)),0
		};
	}
	static MATRIX4x4 ReverseViewProjectionMatrix(MATRIX4x4 view, MATRIX4x4 proj){
		MATRIX4x4 r = {};

		r._11 = (view._11*proj._11)+(view._12*proj._21)+(view._13*proj._31)+(view._14*proj._41);
		r._12 = (view._11*proj._12)+(view._12*proj._22)+(view._13*proj._32)+(view._14*proj._42);
		r._13 = (view._11*proj._13)+(view._12*proj._23)+(view._13*proj._33)+(view._14*proj._43);
		r._14 = (view._11*proj._14)+(view._12*proj._24)+(view._13*proj._34)+(view._14*proj._44);

		r._21 = (view._21*proj._11)+(view._22*proj._21)+(view._23*proj._31)+(view._24*proj._41);
		r._22 = (view._21*proj._12)+(view._22*proj._22)+(view._23*proj._32)+(view._24*proj._42);
		r._23 = (view._21*proj._13)+(view._22*proj._23)+(view._23*proj._33)+(view._24*proj._43);
		r._24 = (view._21*proj._14)+(view._22*proj._24)+(view._23*proj._34)+(view._24*proj._44);

		r._31 = (view._31*proj._11)+(view._32*proj._21)+(view._33*proj._31)+(view._34*proj._41);
		r._32 = (view._31*proj._12)+(view._32*proj._22)+(view._33*proj._32)+(view._34*proj._42);
		r._33 = (view._31*proj._13)+(view._32*proj._23)+(view._33*proj._33)+(view._34*proj._43);
		r._34 = (view._31*proj._14)+(view._32*proj._24)+(view._33*proj._34)+(view._34*proj._44);

		r._41 = (view._41*proj._11)+(view._42*proj._21)+(view._43*proj._31)+(view._44*proj._41);
		r._42 = (view._41*proj._12)+(view._42*proj._22)+(view._43*proj._32)+(view._44*proj._42);
		r._43 = (view._41*proj._13)+(view._42*proj._23)+(view._43*proj._33)+(view._44*proj._43);
		r._44 = (view._41*proj._14)+(view._42*proj._24)+(view._43*proj._34)+(view._44*proj._44);

		FLOAT det = 
			(r._11*(
				(r._22*r._33*r._44)-(r._22*r._34*r._43)+
				(r._23*r._34*r._42)-(r._23*r._32*r._44)+
				(r._24*r._32*r._43)-(r._24*r._33*r._42)))-
			(r._12*(
				(r._23*r._34*r._41)-(r._23*r._31*r._44)+
				(r._24*r._31*r._43)-(r._24*r._33*r._41)+
				(r._21*r._33*r._44)-(r._21*r._34*r._43)))+
			(r._13*(
				(r._24*r._31*r._42)-(r._24*r._32*r._41)+
				(r._21*r._32*r._44)-(r._21*r._34*r._42)+
				(r._22*r._34*r._41)-(r._22*r._31*r._44)))-
			(r._14*(
				(r._21*r._32*r._43)-(r._21*r._33*r._42)+
				(r._22*r._33*r._41)-(r._22*r._31*r._43)+
				(r._23*r._31*r._42)-(r._23*r._32*r._41)))
			;

		if(det == 0.0f){return MATRIX4x4::Initialize();}

		MATRIX4x4 adj = {};

		adj._11 = (
			(r._22*r._33*r._44)-(r._22*r._34*r._43)+
			(r._23*r._34*r._42)-(r._23*r._32*r._44)+
			(r._24*r._32*r._43)-(r._24*r._33*r._42));
		adj._21 = -(
			(r._21*r._33*r._44)-(r._21*r._34*r._43)+
			(r._23*r._34*r._41)-(r._23*r._31*r._44)+
			(r._24*r._31*r._43)-(r._24*r._33*r._41));
		adj._31 = (
			(r._21*r._32*r._44)-(r._21*r._34*r._42)+
			(r._22*r._34*r._41)-(r._22*r._31*r._44)+
			(r._24*r._31*r._42)-(r._24*r._32*r._41));
		adj._41 = -(
			(r._21*r._32*r._43)-(r._21*r._33*r._42)+
			(r._22*r._33*r._41)-(r._22*r._31*r._43)+
			(r._23*r._31*r._42)-(r._23*r._32*r._41));

		adj._12 = -(
			(r._12*r._33*r._44)-(r._12*r._34*r._43)+
			(r._13*r._34*r._42)-(r._13*r._32*r._44)+
			(r._14*r._32*r._43)-(r._14*r._33*r._42));
		adj._22 = (
			(r._11*r._33*r._44)-(r._11*r._34*r._43)+
			(r._13*r._34*r._41)-(r._13*r._31*r._44)+
			(r._14*r._31*r._43)-(r._14*r._33*r._41));
		adj._32 = -(
			(r._11*r._32*r._44)-(r._11*r._34*r._42)+
			(r._12*r._34*r._41)-(r._12*r._31*r._44)+
			(r._14*r._31*r._42)-(r._14*r._32*r._41));
		adj._42 = (
			(r._11*r._32*r._43)-(r._11*r._33*r._42)+
			(r._12*r._33*r._41)-(r._12*r._31*r._43)+
			(r._13*r._31*r._42)-(r._13*r._32*r._41));

		adj._13 = (
			(r._12*r._23*r._44)-(r._12*r._24*r._43)+
			(r._13*r._24*r._42)-(r._13*r._22*r._44)+
			(r._14*r._22*r._43)-(r._14*r._23*r._42));
		adj._23 = -(
			(r._11*r._23*r._44)-(r._11*r._24*r._43)+
			(r._13*r._24*r._41)-(r._13*r._21*r._44)+
			(r._14*r._21*r._43)-(r._14*r._23*r._41));
		adj._33 = (
			(r._11*r._22*r._44)-(r._11*r._24*r._42)+
			(r._12*r._24*r._41)-(r._12*r._21*r._44)+
			(r._14*r._21*r._42)-(r._14*r._22*r._41));
		adj._43 = -(
			(r._11*r._22*r._43)-(r._11*r._23*r._42)+
			(r._12*r._23*r._41)-(r._12*r._21*r._43)+
			(r._13*r._21*r._42)-(r._13*r._22*r._41));

		adj._14 = -(
			(r._12*r._23*r._34)-(r._12*r._24*r._33)+
			(r._13*r._24*r._32)-(r._13*r._22*r._34)+
			(r._14*r._22*r._33)-(r._14*r._23*r._32));
		adj._24 = (
			(r._11*r._23*r._34)-(r._11*r._24*r._33)+
			(r._13*r._24*r._31)-(r._13*r._21*r._34)+
			(r._14*r._21*r._33)-(r._14*r._23*r._31));
		adj._34 = -(
			(r._11*r._22*r._34)-(r._11*r._24*r._32)+
			(r._12*r._24*r._31)-(r._12*r._21*r._34)+
			(r._14*r._21*r._32)-(r._14*r._22*r._31));
		adj._44 = (
			(r._11*r._22*r._33)-(r._11*r._23*r._32)+
			(r._12*r._23*r._31)-(r._12*r._21*r._33)+
			(r._13*r._21*r._32)-(r._13*r._22*r._31));

		r._11 = adj._11/det;	r._12 = adj._12/det;	r._13 = adj._13/det;	r._14 = adj._14/det;
		r._21 = adj._21/det;	r._22 = adj._22/det;	r._23 = adj._23/det;	r._24 = adj._24/det;
		r._31 = adj._31/det;	r._32 = adj._32/det;	r._33 = adj._33/det;	r._34 = adj._34/det;
		r._41 = adj._41/det;	r._42 = adj._42/det;	r._43 = adj._43/det;	r._44 = adj._44/det;

		return r;
	}
	static MATRIX4x4 ReverseMatrix(MATRIX4x4 r){
		FLOAT det = 
			(r._11*(
			(r._22*r._33*r._44)-(r._22*r._34*r._43)+
				(r._23*r._34*r._42)-(r._23*r._32*r._44)+
				(r._24*r._32*r._43)-(r._24*r._33*r._42)))-
				(r._12*(
			(r._23*r._34*r._41)-(r._23*r._31*r._44)+
					(r._24*r._31*r._43)-(r._24*r._33*r._41)+
					(r._21*r._33*r._44)-(r._21*r._34*r._43)))+
					(r._13*(
			(r._24*r._31*r._42)-(r._24*r._32*r._41)+
						(r._21*r._32*r._44)-(r._21*r._34*r._42)+
						(r._22*r._34*r._41)-(r._22*r._31*r._44)))-
						(r._14*(
			(r._21*r._32*r._43)-(r._21*r._33*r._42)+
							(r._22*r._33*r._41)-(r._22*r._31*r._43)+
							(r._23*r._31*r._42)-(r._23*r._32*r._41)))
			;

		if(det == 0.0f){return MATRIX4x4::Initialize();}

		MATRIX4x4 adj = {};

		adj._11 = (
			(r._22*r._33*r._44)-(r._22*r._34*r._43)+
			(r._23*r._34*r._42)-(r._23*r._32*r._44)+
			(r._24*r._32*r._43)-(r._24*r._33*r._42));
		adj._21 = -(
			(r._21*r._33*r._44)-(r._21*r._34*r._43)+
			(r._23*r._34*r._41)-(r._23*r._31*r._44)+
			(r._24*r._31*r._43)-(r._24*r._33*r._41));
		adj._31 = (
			(r._21*r._32*r._44)-(r._21*r._34*r._42)+
			(r._22*r._34*r._41)-(r._22*r._31*r._44)+
			(r._24*r._31*r._42)-(r._24*r._32*r._41));
		adj._41 = -(
			(r._21*r._32*r._43)-(r._21*r._33*r._42)+
			(r._22*r._33*r._41)-(r._22*r._31*r._43)+
			(r._23*r._31*r._42)-(r._23*r._32*r._41));

		adj._12 = -(
			(r._12*r._33*r._44)-(r._12*r._34*r._43)+
			(r._13*r._34*r._42)-(r._13*r._32*r._44)+
			(r._14*r._32*r._43)-(r._14*r._33*r._42));
		adj._22 = (
			(r._11*r._33*r._44)-(r._11*r._34*r._43)+
			(r._13*r._34*r._41)-(r._13*r._31*r._44)+
			(r._14*r._31*r._43)-(r._14*r._33*r._41));
		adj._32 = -(
			(r._11*r._32*r._44)-(r._11*r._34*r._42)+
			(r._12*r._34*r._41)-(r._12*r._31*r._44)+
			(r._14*r._31*r._42)-(r._14*r._32*r._41));
		adj._42 = (
			(r._11*r._32*r._43)-(r._11*r._33*r._42)+
			(r._12*r._33*r._41)-(r._12*r._31*r._43)+
			(r._13*r._31*r._42)-(r._13*r._32*r._41));

		adj._13 = (
			(r._12*r._23*r._44)-(r._12*r._24*r._43)+
			(r._13*r._24*r._42)-(r._13*r._22*r._44)+
			(r._14*r._22*r._43)-(r._14*r._23*r._42));
		adj._23 = -(
			(r._11*r._23*r._44)-(r._11*r._24*r._43)+
			(r._13*r._24*r._41)-(r._13*r._21*r._44)+
			(r._14*r._21*r._43)-(r._14*r._23*r._41));
		adj._33 = (
			(r._11*r._22*r._44)-(r._11*r._24*r._42)+
			(r._12*r._24*r._41)-(r._12*r._21*r._44)+
			(r._14*r._21*r._42)-(r._14*r._22*r._41));
		adj._43 = -(
			(r._11*r._22*r._43)-(r._11*r._23*r._42)+
			(r._12*r._23*r._41)-(r._12*r._21*r._43)+
			(r._13*r._21*r._42)-(r._13*r._22*r._41));

		adj._14 = -(
			(r._12*r._23*r._34)-(r._12*r._24*r._33)+
			(r._13*r._24*r._32)-(r._13*r._22*r._34)+
			(r._14*r._22*r._33)-(r._14*r._23*r._32));
		adj._24 = (
			(r._11*r._23*r._34)-(r._11*r._24*r._33)+
			(r._13*r._24*r._31)-(r._13*r._21*r._34)+
			(r._14*r._21*r._33)-(r._14*r._23*r._31));
		adj._34 = -(
			(r._11*r._22*r._34)-(r._11*r._24*r._32)+
			(r._12*r._24*r._31)-(r._12*r._21*r._34)+
			(r._14*r._21*r._32)-(r._14*r._22*r._31));
		adj._44 = (
			(r._11*r._22*r._33)-(r._11*r._23*r._32)+
			(r._12*r._23*r._31)-(r._12*r._21*r._33)+
			(r._13*r._21*r._32)-(r._13*r._22*r._31));

		r._11 = adj._11/det;	r._12 = adj._12/det;	r._13 = adj._13/det;	r._14 = adj._14/det;
		r._21 = adj._21/det;	r._22 = adj._22/det;	r._23 = adj._23/det;	r._24 = adj._24/det;
		r._31 = adj._31/det;	r._32 = adj._32/det;	r._33 = adj._33/det;	r._34 = adj._34/det;
		r._41 = adj._41/det;	r._42 = adj._42/det;	r._43 = adj._43/det;	r._44 = adj._44/det;

		return r;
	}
	static MATRIX4x4 MultipleMatrix(MATRIX4x4 a, MATRIX4x4 b){
		MATRIX4x4 m = {};
		m._11 = (a._11*b._11)+(a._12*b._21)+(a._13*b._31)+(a._14*b._41);
		m._12 = (a._11*b._12)+(a._12*b._22)+(a._13*b._32)+(a._14*b._42);
		m._13 = (a._11*b._13)+(a._12*b._23)+(a._13*b._33)+(a._14*b._43);
		m._14 = (a._11*b._14)+(a._12*b._24)+(a._13*b._34)+(a._14*b._44);
		m._21 = (a._21*b._11)+(a._22*b._21)+(a._23*b._31)+(a._24*b._41);
		m._22 = (a._21*b._12)+(a._22*b._22)+(a._23*b._32)+(a._24*b._42);
		m._23 = (a._21*b._13)+(a._22*b._23)+(a._23*b._33)+(a._24*b._43);
		m._24 = (a._21*b._14)+(a._22*b._24)+(a._23*b._34)+(a._24*b._44);
		m._31 = (a._31*b._11)+(a._32*b._21)+(a._33*b._31)+(a._34*b._41);
		m._32 = (a._31*b._12)+(a._32*b._22)+(a._33*b._32)+(a._34*b._42);
		m._33 = (a._31*b._13)+(a._32*b._23)+(a._33*b._33)+(a._34*b._43);
		m._34 = (a._31*b._14)+(a._32*b._24)+(a._33*b._34)+(a._34*b._44);
		m._41 = (a._41*b._11)+(a._42*b._21)+(a._43*b._31)+(a._44*b._41);
		m._42 = (a._41*b._12)+(a._42*b._22)+(a._43*b._32)+(a._44*b._42);
		m._43 = (a._41*b._13)+(a._42*b._23)+(a._43*b._33)+(a._44*b._43);
		m._44 = (a._41*b._14)+(a._42*b._24)+(a._43*b._34)+(a._44*b._44);
		return m;
	}
	bool ReleaseScreen(UINT num){
		if(m_Screen.GetNumber() < num){return false;}
		return m_Screen.ReleaseNode(num);
	}	//Release Screen
	
	void Render(UINT& tick){
		List<SCREEN>::iterator iter = m_Screen.Begin();
		if(_O_Graphics::GetSingleton() != nullptr){
			_O_Graphics::GetSingleton()->Clear();
			for( ; iter != m_Screen.End() ; ++iter){	//loop for screen num
				_O_Graphics::GetSingleton()->Start(&(*iter));	//start
				UINT num = Map::GetSingleton()->GetLayerNumber();
				for(UINT i = 0 ; i<num ; ++i){
					Map::GetSingleton()->GetLayer(i).GraphicRender(tick);
				}
				_O_Graphics::GetSingleton()->End();	//end
			}
			_O_Graphics::GetSingleton()->Present();	//present
		}
	}
};

class Sound_Renderer : public Singleton<Sound_Renderer>{
public:
	void Render(){
		_O_Sounds::GetSingleton()->Run();
	}
};

class Renderer : public Singleton<Renderer>{
private:

public:
	void Update(){
		UINT num = Map::GetSingleton()->GetLayerNumber();
		for(UINT i = 0 ; i<num ; ++i){
			Map::GetSingleton()->GetLayer(i).ObjectUpdate();
		}
	}
	void Animation(){

	}
	void Render(UINT tick){
		if(Map::GetSingleton()->GetLayerNumber() != 0 && _O_Graphics::GetSingleton() != nullptr){
			Graphic_Renderer::GetSingleton()->Render(tick);
		}
		if(_O_Sounds::GetSingleton() != nullptr){
			Sound_Renderer::GetSingleton()->Render();
		}
	}
};
