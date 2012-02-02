#include "basic_list.h"

#include<stdlib.h>
#include<assert.h>

void BasicList::init(){
	L_size = 0;
	head = NULL;
	tail = NULL;
}

BasicList::BasicList(){
	init();
}

BasicList::~BasicList(){
	BasicList::BasicNode *node = head;
	while(head != NULL){
		node = head;
		head = head->next;
		delete node;
	}
}

BasicList::BasicIterator BasicList::begin(){
	return pos(0);
}

BasicList::BasicIterator BasicList::end(){
	return pos(L_size);
}

BasicList::BasicIterator BasicList::pos(size_t _pos){
	if(_pos > L_size || _pos < 0)
		return BasicIterator(NULL, BasicList::BasicIterator::OUT, this);
	
	BasicList::BasicNode *node = head;
	for(size_t i = _pos; i > 0; i--)
		node = node->next;
	return BasicIterator(node, node == NULL? BasicList::BasicIterator::PAST_REAR: BasicList::BasicIterator::NORMAL, this);
}

size_t BasicList::size(){
	return L_size;
}

void BasicList::erase(BasicList::BasicIterator _itr){
	assert(_itr.status == BasicList::BasicIterator::NORMAL && L_size != 0);

	if(_itr.node->next == NULL)
		tail = _itr.node->prev;
	else
		_itr.node->next->prev = _itr.node->prev;

	if(_itr.node->prev == NULL)
		head = _itr.node->next;
	else
		_itr.node->prev->next = _itr.node->next;
	
	delete _itr.node;
	_itr.node = NULL;

	L_size--;
}

void BasicList::pop_front(){
	erase(begin());
}
void BasicList::pop_back(){
	erase(end()--);
}

void BasicList::clear(){
	BasicList::~BasicList();
	head = NULL;
	tail = NULL;
	L_size = 0;
}

bool BasicList::empty(){
	return L_size == 0;
}






BasicList::BasicIterator::BasicIterator(BasicList::BasicNode *_node, TBasicIteratorStatus _status, BasicList* _parent){
	node = _node;
	status = _status;
	parent = _parent;
}

BasicList::BasicIterator::BasicIterator(){
	node = NULL;
	status = OUT;
	parent = NULL;
}

BasicList::BasicIterator& BasicList::BasicIterator::operator= (const BasicList::BasicIterator &_itr){
	node = _itr.node;
	status = _itr.status;
	parent = _itr.parent;
	return *this;
}

BasicList::BasicIterator& BasicList::BasicIterator::operator++ (){
	if(status == OUT) 
		throw 666;	

	if(status == PAST_REAR){
		status = OUT;
		return *this;
	}
	if(node == NULL)
		throw 666;
	node = node->next;
	if(node == NULL)
		status = PAST_REAR;
	return *this;
}

BasicList::BasicIterator& BasicList::BasicIterator::operator-- (){
	if(status == OUT)
		throw 666;
	if(status == PAST_REAR){
		status = NORMAL;
		node = parent->tail;
		return *this;
	}
	if(node == NULL)
		throw 666;
	node = node->prev;
	if(node == NULL)
		status = OUT;
	return *this;
}

bool BasicList::BasicIterator::operator== (const BasicList::BasicIterator &_itr) const{
	return (_itr.node == node) && (_itr.status == status);
}

bool BasicList::BasicIterator::operator!= (const BasicList::BasicIterator &_itr) const{
	return !(*this == _itr);
}
