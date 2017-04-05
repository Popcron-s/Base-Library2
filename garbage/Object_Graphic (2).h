#pragma once

#include "Object_Base.h"
#include "Object.h"

class Material{
protected:

public:
	_OBJECT::TYPE GetType(){return _OBJECT::Material;}
};

class Indexed{
private:
	UINT* indexed;
	UINT indexed_num;
};

class Mesh : public baseObject{
protected:
	VERTEX* vertex;
	UINT vertex_num;

	Indexed* indexed;

	Material* material;
public:
	virtual _OBJECT::TYPE GetType(){return _OBJECT::Mesh;}
};

class Animation_Node{
private:
	BYTE* Data;
	UINT Time;
	UINT Inter;	//º¸°£

public:
	template<typename T>
	Animation_Node(T data, UINT time, UINT inter){
		Data = new BYTE[sizeof(T)];
		(T*)*Data = data;
		Time = time;
		Inter = inter;
	}
	~Animation_Node(){
		delete [] Data;
	}
};

class Animation_Graph{
private:
	Animation_Node* m_Node;
	UINT m_Current;

	void* m_Target;
	UINT m_Size;

	UINT m_State;
	UINT m_Time;
	UINT m_Accel;
	bool m_Repeat;

public:
	void update(){

	}
};