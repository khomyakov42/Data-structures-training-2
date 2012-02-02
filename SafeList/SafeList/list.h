#ifndef __LIST__H
#define __LIST__H

#include<stdlib.h>
#include<assert.h>
#include<cstdlib>
#include<exception>
#include"list\List.h"
#define TListIters hmw::list<typename hmw::safe_list<T>::iterator*>

namespace hmw{
template<class T> class safe_list{

	public:
		class iterator{
			private:
				friend class safe_list<T>;
				typename safe_list<T>::Node *node;
				safe_list<T> *parent;
				

				typedef enum{
					NORMAL,
					PAST_REAR,
					OUT
				}TIteratorStatus;

				TIteratorStatus status;
				iterator(typename safe_list<T>::Node *_node, TIteratorStatus _status, safe_list<T>* _parent);
			public:
				iterator();
				~iterator();

				iterator& operator= (const iterator &_itr);
				T& operator* ();
				bool operator== (const iterator &_itr) const;
				bool operator!= (const iterator &_itr) const;
		};
	private:
		class Node{
				friend class safe_list<T>;
				Node(Node *_node1, Node *_node2, const T &_value);
				Node *prev, *next;
				T value;
		};
		
		size_t l_size;
		Node *head, *tail;
		TListIters iters;

		Node* insert(Node* _node1, Node* _node2, const T &_value);
		void init();
		void UpdateValidateIterators(typename safe_list<T>::Node* _node);
	public:
		inline safe_list();
		inline safe_list(safe_list<T>& _l);
		inline ~safe_list();
		
		safe_list<T>& operator= (const safe_list<T>& _list);

		iterator begin();
		iterator end();
		iterator pos(size_t _pos);

		const T& front();
		const T& back();

		size_t size();
		void assign(iterator _itr, const T &_value);
		void insert(iterator _itr, const T &_value);
		void erase(iterator _itr);
		void push_front(const T &_value);
		void push_back(const T &_value);
		void pop_front();
		void pop_back();
		void clear();
		bool empty();
};

/////////////////////////ITERATOR///////////////////////////////
template<class T> safe_list<T>::iterator::iterator(typename safe_list<T>::Node* _node, TIteratorStatus _status, safe_list<T>* _parent){
	node = _node;
	status = _status;
	parent = _parent;
}

template<class T> safe_list<T>::iterator::iterator(){
	node = NULL;
	status = OUT;
	parent = NULL;
}

template<class T> safe_list<T>::iterator::~iterator(){
	if(this->parent == NULL)
		return;
	for(TListIters::iterator i = this->parent->iters.begin(); i != this->parent->iters.end(); i++)
		if(*i == this){
			this->parent->iters.erase(i);
			return;
		}
}

template<class T> typename safe_list<T>::iterator&  safe_list<T>::iterator::operator= (const iterator &_itr){
	node = _itr.node;
	status = _itr.status;
	
	if(parent == NULL || (_itr.parent != NULL && parent != _itr.parent))
		(*_itr.parent).iters.push_back(this);

	parent = _itr.parent;

	return *this;
}

/*
template<class T> typename safe_list<T>::iterator& safe_list<T>::iterator::operator-- (int){
	--(*this);
	return ++(*this);
}*/

template<class T> T& safe_list<T>::iterator::operator* (){
	if(status != NORMAL)
		throw ECannotDereference();
	return node->value;
}

template<class T> bool safe_list<T>::iterator::operator== (const typename safe_list<T>::iterator &_itr) const{
	return (_itr.node == node) && (_itr.status == status);
}

template<class T> bool safe_list<T>::iterator::operator!= (const typename safe_list<T>::iterator &_itr) const{
	return !(*this == _itr);
}

////////////////////////NODE///////////////////////

template<class T>  safe_list<T>::Node::Node(Node *_node1, Node *_node2, const T &_value){
	value = _value;
	prev = _node1;
	next = _node2;
}

///////////////////////LIST////////////////////////

template<class T> void safe_list<T>::insert(iterator _itr, const T &_value){
	if(_itr.status != safe_list<T>::iterator::NORMAL)
		throw EOutOfRange();

	if(_itr.node == NULL)
		insert(head, tail, _value);
	else
		insert(_itr.node->prev, _itr.node, _value);
}

template<class T> void safe_list<T>::init(){
	l_size = 0;
	head = NULL;
	tail = NULL;
}

template<class T> void safe_list<T>::UpdateValidateIterators(typename safe_list<T>::Node* _node){
	for(TListIters::iterator i = iters.begin(); i != iters.end(); i++)
		if((**i).node == _node)
			(**i).status = safe_list<T>::iterator::OUT;
}

template<class T> safe_list<T>::safe_list(){
	init();
}

template<class T> safe_list<T>::safe_list(safe_list<T>& _l){
	init();
	for(safe_list<T>::iterator itr = _l.begin(); itr != _l.end(); itr++)
		push_back(*itr);
	l_size = _l.l_size;	
}

template<class T> safe_list<T>::~safe_list(){
	safe_list<T>::Node *node = head;
	while(head != NULL){
		node = head;
		head = head->next;
		delete node;
	}
}

template<class T> safe_list<T>& safe_list<T>::operator= (const safe_list<T>& _list){
	init();
	for(safe_list<T>::iterator itr = _list.begin(); itr != _list.end(); itr++)
		push_back(*itr);
	l_size = _list.size();	
	return *this;
}

template<class T> typename safe_list<T>::iterator safe_list<T>::begin(){
	return pos(0);
}

template<class T> typename safe_list<T>::iterator safe_list<T>::end(){
	return pos(l_size);
}

template<class T> typename safe_list<T>::iterator safe_list<T>::pos(size_t _pos){
	if(_pos > l_size || _pos < 0)
		return iterator(NULL, safe_list<T>::iterator::OUT, this);
	
	safe_list<T>::Node *node = head;
	for(size_t i = _pos; i > 0; i--)
		node = node->next;
	return iterator(node, node == NULL? safe_list<T>::iterator::PAST_REAR: safe_list<T>::iterator::NORMAL, this);
}

template<class T> const T& safe_list<T>::front(){
	return *(begin());
}

template<class T> const T& safe_list<T>::back(){
	return *(end()--);
}

template<class T> size_t safe_list<T>::size(){
	return l_size;
}

template<class T> void safe_list<T>::assign(typename safe_list<T>::iterator _itr, const T &_value){
	if(_itr.status != safe_list<T>::iterator::NORMAL || l_size == 0) 
		throw EOutOfRange();
	_itr.node->value = _value; 
}

template<class T> typename safe_list<T>::Node* safe_list<T>::insert(typename safe_list<T>::Node* _node1, typename safe_list<T>::Node* _node2, const T &_value){
	Node *node = new Node(_node1, _node2, _value);

	if(_node1 == NULL)
		head = node;
	else
		_node1->next = node;
	
	if(_node2 == NULL)
		tail = node;
	else
		_node2->prev = node;
	
	l_size++;	
	return node;
}

template<class T> void safe_list<T>::erase(iterator _itr){
	if(_itr.status != safe_list<T>::iterator::NORMAL || l_size == 0)
		throw EOutOfRange();

	if(_itr.node->next == NULL)
		tail = _itr.node->prev;
	else
		_itr.node->next->prev = _itr.node->prev;

	if(_itr.node->prev == NULL)
		head = _itr.node->next;
	else
		_itr.node->prev->next = _itr.node->next;

	UpdateValidateIterators(_itr.node);
	delete _itr.node;
	
	l_size--;
}

template<class T> void safe_list<T>::push_front(const T &_value){
	insert(NULL, head, _value);
}

template<class T> void safe_list<T>::push_back(const T &_value){
	insert(tail, NULL, _value);
}


template<class T> void safe_list<T>::pop_front(){
	erase(begin());
}

template<class T> void safe_list<T>::pop_back(){
	erase(end()--);
}

template<class T> void safe_list<T>::clear(){
	safe_list<T>::~safe_list();
	iters.clear();
	head = NULL;
	tail = NULL;
	l_size = 0;
}

template<class T> bool safe_list<T>::empty(){
	return l_size == 0;
}

};
#endif