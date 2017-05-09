#pragma once

#include "variable.h"

template <typename T>
class TList{
private:
	struct _node{
		T data;

		_node* next;
		_node* parent;
	}*m_pList, **m_pLast;

	UINT num;

public:
	TList() : m_pList(nullptr), m_pLast(&m_pList), num(0){}
	~TList(){AllReleaseNode();}

	bool CreateNode(T& data, void* parent, INT num = -1){}
	bool ReleaseNode(UINT num = 0){}
	bool AllReleaseNode(){}
	bool SwapNode(){}

	void* Begin(){return (void*)m_pList;}
	void* End(){return (void*)*m_pLast;}

	class iterator{
	private:
		_node* node;
	
	public:
		iterator(void* n = nullptr) : node(n){}
		~iterator(){}

		void*& operator ++(){
			if(this->node == nullptr){return nullptr;} 
			this->node = this->node->next; 
			return (void*)this->node;
		}
		T& operator *(){return this->node->data;}
		operator void*(){return (void*)this->node;}
	};
};