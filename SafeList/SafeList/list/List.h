#ifndef _LIST_
#define _LIST_

#include<stdlib.h>
#include<assert.h>

namespace hmw{
template<class T> class list{
	public:
		class Exception: public std::exception{
			public:
				char* error;
			protected:
				void initExcep(char *s){error = s;}
			public:
				Exception(char* s){initExcep(s);}
				Exception(){};
				virtual const char* what() const throw(){
					return error;
				}
		};
	private:
		class ECannotDereference: public Exception{
			public:
				ECannotDereference(){initExcep(" Can't dereference iterator! ");}
		};

		class EOutOfRange: public Exception{
			public:
				EOutOfRange(){initExcep(" Out of range! ");}
		};
	public:
		class iterator{
			protected:
				friend class list<T>;
				typename list<T>::Node *node;
				list<T> *parent;

				typedef enum{
					NORMAL,
					PAST_REAR,
					OUT
				}TIteratorStatus;

				TIteratorStatus status;
				iterator(typename list<T>::Node *_node, TIteratorStatus _status, list<T>* _parent);
			public:
				iterator();

				iterator& operator= (const iterator &_itr);
				iterator& operator++ ();
				iterator& operator-- ();
				T& operator* ();
				bool operator== (const iterator &_itr) const;
				bool operator!= (const iterator &_itr) const;
		};
	protected:
		class Node{
				friend class list<T>;
				Node(Node *_node1, Node *_node2, const T &_value);
				Node *prev, *next;
				T value;
		};
		
		size_t l_size;
		Node *head, *tail;

		Node* insert(Node* _node1, Node* _node2, const T &_value);
		void init();
	public:
		inline list();
		inline list(list<T>& _l);
		inline ~list();
		
		list<T>& operator= (const list<T>& _list);

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
template<class T> list<T>::iterator::iterator(typename list<T>::Node* _node, TIteratorStatus _status, list<T>* _parent){
	node = _node;
	status = _status;
	parent = _parent;
}

template<class T> list<T>::iterator::iterator(){
	node = NULL;
	status = OUT;
	parent = NULL;
}

template<class T> typename list<T>::iterator&  list<T>::iterator::operator= (const iterator &_itr){
	node = _itr.node;
	status = _itr.status;
	parent = _itr.parent;
	return *this;
}

template<class T> typename list<T>::iterator& list<T>::iterator::operator++ (){
	if(status == OUT || (status == PAST_REAR && (this->parent == NULL || this->parent->l_size == 0))) 
		throw EOutOfRange();	

	if(status == PAST_REAR){
		status = OUT;
		return *this;
	}
	if(node == NULL)
		throw EOutOfRange();
	node = node->next;
	if(node == NULL)
		status = PAST_REAR;
	return *this;
}

template<class T> typename list<T>::iterator& list<T>::iterator::operator-- (){
	if(status == OUT || (status == PAST_REAR && (this->parent == NULL || this->parent->l_size == 0)))
		throw EOutOfRange();
	if(status == PAST_REAR){
		status = NORMAL;
		node = parent->tail;
		return *this;
	}
	if(node == NULL)
		throw EOutOfRange();
	node = node->prev;
	if(node == NULL)
		status = OUT;
	return *this;
}

template<class T> T& list<T>::iterator::operator* (){
	if(status != NORMAL)
		throw ECannotDereference();
	return node->value;
}

template<class T> bool list<T>::iterator::operator== (const typename list<T>::iterator &_itr) const{
	return (_itr.node == node) && (_itr.status == status);
}

template<class T> bool list<T>::iterator::operator!= (const typename list<T>::iterator &_itr) const{
	return !(*this == _itr);
}

////////////////////////NODE///////////////////////

template<class T>  list<T>::Node::Node(Node *_node1, Node *_node2, const T &_value){
	value = _value;
	prev = _node1;
	next = _node2;
}

///////////////////////LIST////////////////////////

template<class T> void list<T>::insert(iterator _itr, const T &_value){
	assert(_itr.status == list<T>::iterator::NORMAL);

	if(_itr.node == NULL)
		insert(head, tail, _value);
	else
		insert(_itr.node->prev, _itr.node, _value);
}

template<class T> void list<T>::init(){
	l_size = 0;
	head = NULL;
	tail = NULL;
}

template<class T> list<T>::list(){
	init();
}

template<class T> list<T>::list(list<T>& _l){
	init();
	for(list<T>::iterator itr = _l.begin(); itr != _l.end(); itr++)
		push_back(*itr);
	l_size = _l.l_size;	
}

template<class T> list<T>::~list(){
	list<T>::Node *node = head;
	while(head != NULL){
		node = head;
		head = head->next;
		delete node;
	}
}

template<class T> list<T>& list<T>::operator= (const list<T>& _list){
	init();
	for(list<T>::iterator itr = _list.begin(); itr != _list.end(); itr++)
		push_back(*itr);
	l_size = _list.size();	
	return *this;
}

template<class T> typename list<T>::iterator list<T>::begin(){
	return pos(0);
}

template<class T> typename list<T>::iterator list<T>::end(){
	return pos(l_size);
}

template<class T> typename list<T>::iterator list<T>::pos(size_t _pos){
	if(_pos > l_size || _pos < 0)
		return iterator(NULL, list<T>::iterator::OUT, this);
	
	list<T>::Node *node = head;
	for(size_t i = 0; i < _pos; i++)
		node = node->next;
	return iterator(node, node == NULL? list<T>::iterator::PAST_REAR: list<T>::iterator::NORMAL, this);
}

template<class T> const T& list<T>::front(){
	return *(begin());
}

template<class T> const T& list<T>::back(){
	return *(end()--);
}

template<class T> size_t list<T>::size(){
	return l_size;
}

template<class T> void list<T>::assign(typename list<T>::iterator _itr, const T &_value){
	if(_itr.status != list<T>::iterator::NORMAL || l_size == 0) 
		throw EOutOfRange();
	_itr.node->value = _value; 
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
	
	l_size++;	
	return node;
}

template<class T> void list<T>::erase(iterator _itr){
	if(_itr.status == list<T>::iterator::NORMAL && l_size != 0)
		throw EOutOfRange();
	if(_itr.node->next == NULL)
		tail = _itr.node->prev;
	else
		_itr.node->next->prev = _itr.node->prev;

	if(_itr.node->prev == NULL)
		head = _itr.node->next;
	else
		_itr.node->prev->next = _itr.node->next;
	
	l_size--;
}

template<class T> void list<T>::push_front(const T &_value){
	insert(NULL, head, _value);
}

template<class T> void list<T>::push_back(const T &_value){
	insert(tail, NULL, _value);
}

template<class T> void list<T>::pop_front(){
	erase(begin());
}

template<class T> void list<T>::pop_back(){
	erase(end()--);
}

template<class T> void list<T>::clear(){
	list<T>::~list();
	head = NULL;
	tail = NULL;
	l_size = 0;
}

template<class T> bool list<T>::empty(){
	return l_size == 0;
}
};
#endif