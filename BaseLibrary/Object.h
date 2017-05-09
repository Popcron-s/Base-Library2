#pragma once

#include "..\\Common\\Enum.h"
#include "..\\Common\\Tree.h"
#include "..\\Common\\List.h"
#include "..\\Common\\variable.h"

#include "Skeletal.h"
#include "Mesh.h"
#include "Collider2D.h"
#include "Animation.h"

#include <cmath>

#define GetSetVariable(type,name,var) 		\
private:									\
type var;									\
public:									\
void Set##name(type _##var){var = _##var;}	\
type Get##name(){return var;}

#define SKEL_SEARCHER(n) Tree<JOINT>::searcher n = GetSkeletal().Begin()

class __declspec(dllexport) OBJECT{
public:
	virtual void update() = 0;

	//default
	GetSetVariable(FLOAT3, Position, m_pos)
	GetSetVariable(FLOAT3, Rotation, m_rot);
	GetSetVariable(FLOAT3, Scale, m_scl);

private:
	MATRIX4x4 m_world;

private:
	MATRIX4x4 SetWorld(VECTOR3 pos, VECTOR3 rot, VECTOR3 scl, MATRIX4x4 p_mat = MATRIX4x4::Initialize()){
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
	void SetWorld(MATRIX4x4 p_mat = MATRIX4x4::Initialize()){
		//scale->rotation->Position
		MATRIX4x4 t_mat = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};

		FLOAT4 q = {
			(sin(m_rot.x/2)*cos(m_rot.y/2)*cos(m_rot.z/2))-(cos(m_rot.x/2)*sin(m_rot.y/2)*sin(m_rot.z/2)),
			(cos(m_rot.x/2)*sin(m_rot.y/2)*cos(m_rot.z/2))+(sin(m_rot.x/2)*cos(m_rot.y/2)*sin(m_rot.z/2)),
			(cos(m_rot.x/2)*cos(m_rot.y/2)*sin(m_rot.z/2))-(sin(m_rot.x/2)*sin(m_rot.y/2)*cos(m_rot.z/2)),
			(cos(m_rot.x/2)*cos(m_rot.y/2)*cos(m_rot.z/2))+(sin(m_rot.x/2)*sin(m_rot.y/2)*sin(m_rot.z/2))
		};

		//1-2yy-2zz , -2wz+2xy , 2wy+2xz
		//2wz+2xy , 1-2xx-2zz , -2wx+2yz
		//-2wy+2xz , 2wx+2yz , 1-2xx-2yy
		MATRIX3x3 t_rot = {
			1-(2*q.y*q.y)-(2*q.z*q.z), (2*q.x*q.y)-(2*q.w*q.z), (2*q.x*q.z)+(2*q.w*q.y),
			(2*q.x*q.y)+(2*q.w*q.z), 1-(2*q.x*q.x)-(2*q.z*q.z), (2*q.y*q.z)-(2*q.w*q.x),
			(2*q.x*q.z)-(2*q.w*q.y), (2*q.y*q.z)+(2*q.w*q.x), 1-(2*q.x*q.x)-(2*q.y*q.y)
		};

		t_mat._11 = m_scl.x * t_rot._11;
		t_mat._12 = m_scl.x * t_rot._12;
		t_mat._13 = m_scl.x * t_rot._13;
		t_mat._14 = 0;

		t_mat._21 = m_scl.y * t_rot._21;
		t_mat._22 = m_scl.y * t_rot._22;
		t_mat._23 = m_scl.y * t_rot._23;
		t_mat._14 = 0;

		t_mat._31 = m_scl.z * t_rot._31;
		t_mat._32 = m_scl.z * t_rot._32;
		t_mat._33 = m_scl.z * t_rot._33;
		t_mat._34 = 0;

		t_mat._41 = m_pos.x;
		t_mat._42 = m_pos.y;
		t_mat._43 = m_pos.z;
		t_mat._44 = 1;

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
		
		m_world = r_mat;
	}
public:
	MATRIX4x4 GetWorld(){return m_world;}

private:
	Tree<JOINT> m_skeletal;
	List<MESH> m_mesh;
	List<COL2D*> m_col2d;
	ANIMATION* m_ani;

public:
	Tree<JOINT>& GetSkeletal(){return m_skeletal;}
	List<MESH>& GetMesh(){return m_mesh;}
	List<COL2D*>& GetCollider2D(){return m_col2d;}
	void CreateAnimation(UINT num){
		if(m_ani != nullptr){
			delete m_ani;
		}
		m_ani = new ANIMATION((void*&)*this, num);
	}
	void DestroyAnimation(){
		if(m_ani != nullptr){
			delete m_ani;
			m_ani = nullptr;
		}
	}
	ANIMATION& GetAnimation(){return *m_ani;}

private:
	//module
	//GetSetVariable(Tree<JOINT>, Skeletal, m_skeletal);
	//GetSetVariable(List<MESH>, Mesh, m_mesh);
	//COLLISION
	//SOUND
	//GetSetVariable(ANIMATION*, Animation, m_ani);

public:
	OBJECT() : 
		m_pos({}), m_rot({}), m_scl({1.0f, 1.0f, 1.0f}), m_world(MATRIX4x4::Initialize()), 
		m_ani(nullptr)
	{}
	~OBJECT(){
		DestroyAnimation();
		m_mesh.AllReleaseNode();
		m_col2d.AllReleaseNode();
		m_skeletal.AllRelease();
	}

	void WorldUpdate(){
		SetWorld();
		if(m_skeletal.GetNumber() == 0){return;}
		Tree<JOINT>::iterator iter = m_skeletal.Begin();
		iter->world = SetWorld(iter->pos, iter->rot, iter->scl, m_world); ++iter;
		for( ; !iter.isLast() ; ++iter){
			Tree<JOINT>::searcher scr = iter;
			iter->world = SetWorld(iter->pos, iter->rot, iter->scl, scr.GetParent().world);
		}
	}
	void ActAnimation(UINT tick){
		if(m_ani == nullptr){return;}
		m_ani->update(tick);
	}
};

#undef GetSetVariable