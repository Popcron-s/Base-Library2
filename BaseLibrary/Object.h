#pragma once

#include "..\\Common\\Enum.h"
#include "..\\Common\\Tree.h"
#include "..\\Common\\List.h"
#include "..\\Common\\variable.h"

struct VERTEX{
	FLOAT4 pos;
	FLOAT4 diffuse;
	FLOAT3 normal;
	FLOAT2 tex;
};

struct INDEXED{
	struct _node{
		UINT _1,_2,_3;
	}*node;
	UINT m_num;
};

struct MESH{
	VERTEX* vtx;
	UINT vtx_num;
	INDEXED* indexed;
	MATERIAL* material;
	//shader
};

struct JOINT{
	//축, 위치, 방향, 크기
	VECTOR3 pos, rot, scl;
	MATRIX4x4 world;
	MESH mesh;
};

struct SKELETAL{
	WLTree<JOINT> skeletal;
};

struct RENDER_OBJECT{
	MATRIX4x4 world;
	VERTEX* vtx;
	UINT vtx_num;
	INDEXED* indexed;
	MATERIAL* material;
	//shader
};

struct SCREEN{
	UINT x,y,width,height;
	MATRIX4x4 view,proj;
};

class _Graph{
protected:
	_GRAPH::TYPE type;
	UINT time;
	bool Loop;
	bool Auto;

public:
	_Graph() : type(_GRAPH::STOP), time(0), Loop(false), Auto(false){}
	~_Graph(){}

	void SetLoop(bool b){Loop = b;}
	bool IsLoop(){return Loop;}

	void SetAuto(bool b){Auto = b;}
	bool IsAuto(){return Auto;}

	void Play(){type = _GRAPH::PLAY;}
	void Stop(){type = _GRAPH::STOP;}
	void Pause(){type = _GRAPH::PAUSE;}

	virtual void update(UINT tick) = 0;
};

template <typename T>
class _Graph_template : public _Graph{
private:
	T& target;
	struct _node{
		T value;
		_GRAPH::INTERPOLATION infor;
		UINT time;
	}*arr;
	const UINT arr_num;
	UINT cur;

public:
	_Graph_template(T& t, UINT n) : _Graph(), target(t), arr(new _node[n]), arr_num(n), cur(0){}
	_Graph_template(){delete [] arr;}

	//_node& operator [](UINT num){return arr[num];}

	void SetNode(UINT n, T v, _GRAPH::INTERPOLATION i, UINT t){
		arr[n] = {v,i,t};
	}

	void Interpolation(T prev, T next, FLOAT weight){
		target = prev + ((next-prev)*weight);
		std::cout<< target <<std::endl;
		return;
	}

	void update(UINT tick){
		if(type != _GRAPH::PLAY){return;}
		time += tick;
		while(true){
			if(cur == arr_num-1){
				if(Loop){
					time -= arr[cur-1].time;
					cur = 0;
				}
				else{
					time = 0;
					target = arr[cur-1].value;
					cur = 0;
					return;
				}
			}
			if(time < arr[cur+1].time){
				FLOAT w = (FLOAT)(time - arr[cur].time)/(FLOAT)(arr[cur+1].time - arr[cur].time);
				return Interpolation(arr[cur].value, arr[cur+1].value, w);
			}
			++cur;
		}
	}
};

class ANIMATION{
public:
	virtual void update() = 0;
};

#define GetSetVariable(type,name,var) 		\
private:									\
type var;									\
public:									\
void Set##name(type _##var){var = _##var;}	\
type Get##name(){return var;}

class OBJECT{
public:
	virtual void update() = 0;

	//default
	GetSetVariable(FLOAT3, Position, m_pos)
	GetSetVariable(FLOAT3, Rotation, m_rot);
	GetSetVariable(FLOAT3, Scale, m_scl);

private:
	MATRIX4x4 m_world;

public:
	void SetWorld(){
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
		/*if(GetParent() != nullptr){
			//parent * me
			MATRIX4x4 p_mat = GetParent()->GetData()->GetWorld();

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
		}
		else{r_mat = t_mat;}
		m_world = r_mat;*/
		m_world = t_mat;
	}
	MATRIX4x4 GetWorld(){return m_world;}

private:
	//module
	GetSetVariable(MESH*, Mesh, m_mesh);
	GetSetVariable(SKELETAL*, Skeletal, m_skeletal);
	//COLLISION
	//SOUND
	GetSetVariable(ANIMATION*, Animation, m_ani);

public:
	OBJECT() : 
		m_pos({}), m_rot({}), m_scl({}), m_world({}), 
		m_mesh(nullptr), m_ani(nullptr)
	{}
	~OBJECT(){}

	RENDER_OBJECT GetGraphics(){
		if(m_mesh == nullptr){return {{},nullptr,0,nullptr,nullptr};}
		return {
			m_world, m_mesh->vtx, m_mesh->vtx_num,  m_mesh->indexed, m_mesh->material
		};
	}
	RENDER_OBJECT GetGraphics(void* node){
		if(node == nullptr){return {{},nullptr,0,nullptr,nullptr};}
		WLTree<JOINT>::searcher scr = node;
		return {
			scr.Data().world, 
			scr.Data().mesh.vtx, scr.Data().mesh.vtx_num,  
			scr.Data().mesh.indexed, scr.Data().mesh.material
		};
	}

	void ActAnimation(){if(m_ani != nullptr){m_ani->update();}}
};

#undef GetSetVariable