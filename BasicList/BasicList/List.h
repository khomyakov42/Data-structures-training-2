#ifndef _LIST_
#define _LIST_
#include "basic_list.h"
#include<stdlib.h>
#include<assert.h>
#include<iostream>

namespace hmw{
template<class T> class list:public BasicList{
	public:
		class iterator:public BasicIterator{
			private:
				friend class list<T>;
			public:
				iterator(): BasicIterator(){};
				iterator(const BasicIterator &_itr);
				T& operator* ();
		};

	private:
		class Node: public BasicNode{
				friend class list<T>;
				Node(Node *_node1, Node *_node2, const T &_value);
				T *value;
			public:
				Node(): BasicNode(){};
				~Node();
		};

		Node* insert(Node* _node1, Node* _node2, const T &_value);
	public:
		list():BasicList(){};
		inline list(list<T>& _l);
		~list(){};

		list<T>& operator= (const list<T>& _list);

		const T& front();
		const T& back();

		void assign(iterator _itr, const T &_value);
		void insert(iterator _itr, const T &_value);
		void push_front(const T &_value);
		void push_back(const T &_value);
};
template<class T> list<T>::iterator::iterator(const BasicIterator &_itr){
	node = _itr.node;
	status = _itr.status;
	parent = _itr.parent;
}

template<class T> T& list<T>::iterator::operator* (){
	if(status != NORMAL)
		throw 666;
	return *((static_cast<list<T>::Node*>(node))->value);
}

template<class T>  list<T>::Node::Node(Node *_node1, Node *_node2, const T &_value){
	value = new T;
	*value = _value;
	prev = _node1;
	next = _node2;
}

template<class T> list<T>::Node::~Node(){
	std::cout << "I am 'Node' destructor. -> ";
	delete value;
}

template<class T> list<T>::list(list<T>& _l){
	init();
	for(list<T>::iterator itr = _l.begin(); itr != _l.end(); itr++)
		push_back(*itr);
}

template<class T> list<T>& list<T>::operator= (const list<T>& _list){
	init();
	for(list<T>::iterator itr = _list.begin(); itr != _list.end(); itr++)
		push_back(*itr);
	L_size = _list.size();	
	return *this;
}

template<class T> const T& list<T>::front(){
	return *(static_cast<iterator>(begin()));
}

template<class T> const T& list<T>::back(){
	return *(static_cast<iterator>(end()--));
}

template<class T> void list<T>::insert(iterator _itr, const T &_value){
	assert(_itr.status == list<T>::iterator::NORMAL);

	if(_itr.node == NULL)
		insert(head, tail, _value);
	else
		insert(_itr.node->prev, _itr.node, _value);
}

template<class T> void list<T>::assign(typename list<T>::iterator _itr, const T &_value){
	if(_itr.status != list<T>::iterator::NORMAL || L_size == 0) throw 666;
	*(static_cast<Node*>(_itr.node)->value) = _value; 
}

template<class T> typename list<T>::Node* list<T>::insert(typename list<T>::Node* _node1, typename list<T>::Node* _node2, const T &_value){
	Node *node = new Node(_node1, _node2, _value);

	if(_node1 == NULL)
		head = node;
	else
		_node1->next = node;
	
	if(_node2 == NULL)
		tail = node;
	else
		_node2->prev = node;
	
	L_size++;	
	return node;
}

template<class T> void list<T>::push_front(const T &_value){
	insert(NULL, static_cast<Node*>(head), _value);
}

template<class T> void list<T>::push_back(const T &_value){
	insert(static_cast<Node*>(tail), NULL, _value);
}

};
#endif