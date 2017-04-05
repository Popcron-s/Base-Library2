#pragma once

#include "variable.h"

template <class T>
class List{
private:
	struct node{
		T data;
		node* next;
	}*m_pList, **last;
	UINT m_Num;

public:
	List() : m_pList(0x00), m_Num(0), last(&m_pList){}
	~List(){}
	T& CreateNode(T data){
		node* t_node = new node;
		*last = t_node;
		t_node->data = data;
		t_node->next = 0x00;
		last = &(t_node->next);
		++m_Num;
		return t_node->data;
	}
	bool ReleaseNode(T* data){
		node** t_node = &m_pList;
		while(&((*t_node)->data) != data){
			t_node = &((*t_node)->next);
			if(*t_node == 0x00){return false;}
		}
		if(last == &((*t_node)->next)){
			last = t_node;
		}
		node* d_node = *t_node;
		*t_node = d_node->next;
		delete d_node;
		--m_Num;
		return true;
	}
	bool ReleaseNode(UINT id){
		if(id >= m_Num){return false;}
		node** t_node = &m_pList;
		for(UINT i = 0 ; i<id ; ++i){
			t_node = &((*t_node)->next);
		}
		if(last == &((*t_node)->next)){
			last = t_node;
		}
		node* d_node = *t_node;
		*t_node = d_node->next;
		delete d_node;
		--m_Num;
		return true;
	}
	void AllReleaseNode(){
		node* d_node = 0x00;
		while(m_pList != 0x00){
			d_node = m_pList;
			m_pList = m_pList->next;
			delete d_node;
		}
		last = &m_pList;
		m_Num = 0;
		return;
	}
	bool SwapNode(T* data, INT order){
		if(order == -1){order = m_Num;}
		if(order > m_Num){return false;}
		node** t_node = &m_pList;
		node** order_node = &m_pList;
		while((order > 0) || (&((*t_node)->data) != data)){
			if(&((*t_node)->data) != data){t_node = &((*t_node)->next);}
			if(order > 0){
				--order;
				order_node = &((*order_node)->next);
			}
			if(*t_node == 0x00){return false;}
		}
		if(last == &((*t_node)->next)){
			last = t_node;
		}
		node* c_node = *t_node;
		*t_node = (*t_node)->next;
		c_node->next = *order_node;
		*order_node = c_node;
		if(*last != 0x00){
			last = &((*last)->next);
		}
		return true;
	}
	bool SwapNode(UINT id, INT order){
		if(order == -1){order = m_Num;}
		if(order >= m_Num || id >= m_Num){return false;}
		node** t_node = &m_pList;
		node** order_node = &m_pList;
		while((order > 0) || (id > 0)){
			if(id > 0){
				--id;
				t_node = &((*t_node)->next);
				if(id == 0){order_node = &((*order_node)->next);}
			}
			if(order > 0){
				--order;
				order_node = &((*order_node)->next);
			}
			//if(*t_node == 0x00){return false;}
		}
		if(last == &((*t_node)->next)){
			last = t_node;
		}
		node* c_node = *t_node;
		*t_node = (*t_node)->next;
		c_node->next = *order_node;
		*order_node = c_node;
		if(*last != 0x00){
			last = &((*last)->next);
		}
		return true;
	}

	UINT GetNumber(){return m_Num;}
	T& GetData(UINT id){
		if(id >= m_Num){abort();}
		node* t_node = m_pList;
		for(UINT i = 0 ; i<id ; ++i){t_node = t_node->next;}
		return t_node->data;
	}
	T** GetArray(T** arr){
		if(arr == 0x00){return 0x00;}
		node* t_node = m_pList;
		for(UINT i = 0 ; i<m_Num ; ++i){
			arr[i] = &(t_node->data);
			t_node = t_node->next;
		}
		return arr;
	}
};

template <class T>
class Singleton_List : public List<T>{
private:
	static Singleton_List<T>* m_pSingleton;

	Singleton_List<T>(){}
	~Singleton_List<T>(){AllReleaseNode();}

public:
	static Singleton_List<T>* GetSingleton(){
		if(m_pSingleton == 0x00){
			m_pSingleton = new Singleton_List<T>;
		}
		return m_pSingleton;
	}
	static void Destroy(){
		if(m_pSingleton != 0x00){
			delete m_pSingleton;
			m_pSingleton = 0x00;
		}
	}
};

template <class T> 
Singleton_List<T>* Singleton_List<T>::m_pSingleton = 0x00;