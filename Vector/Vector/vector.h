#ifndef __VECTOR__
#define __VECTOR__

#include "allocator.h"

namespace hmw{

template<class T, class A = Allocator<T>>
class vector{
	public:
		class OutOfRange{};

		class iterator{
			private:
				friend class vector<T, A>;
				size_t itr;
				vector<T, A> *parent;
				iterator(size_t _pos, vector<T, A>* _parent);
			public:
				iterator();
				iterator(const size_t pos);
				iterator(const iterator &_itr);
				iterator& operator= (const iterator &_itr);
				iterator& operator= (const size_t _itr);
				iterator& operator++(int);
				iterator& operator++ ();
				iterator& operator-- (int);
				iterator& operator-- ();
				iterator& operator+ (const iterator &_itr);
				iterator& operator+ (const size_t _itr);
				iterator& operator- (const iterator &_itr);
				iterator& operator- (const size_t _itr);
				T& operator* ();

				operator int();
		};

	private:
		friend typename A;
		T* a;
		size_t v_size;
		A allocator;

	public:
		vector();
		vector(const vector<T, A> &_vector);
		~vector();
		
		T& operator[] (size_t _pos);
		vector& operator= (const vector<T, A> &_vector);
		iterator begin();
		iterator end();
		iterator pos(const size_t pos);
		
		size_t size(); 
		void resize(const size_t _size, const T &_val);
		size_t capacity();///текущий физический размер
		void reserve(size_t n);//просит что бы контейнер содержал минимум н элементов
		
		T front();
		T back();
		void push_back(const T &_val);
		void pop_back();

		void insert(const iterator _itr, const T &_val);
		void erase(const iterator _itr);
		void clear();
		bool empty();
};

//////////////////////////////ITERATOR//////////////////////////////
template<class T, class A> vector<T, A>::iterator::iterator(size_t _pos, vector<T, A>* _parent){
	parent = _parent;
	itr = _pos;
}

template<class T, class A> vector<T, A>::iterator::iterator(){
	itr = -1;
	parent = NULL;
}

template<class T, class A> vector<T, A>::iterator::iterator(const size_t pos){
	itr = pos;
	parent = NULL;
}

template<class T, class A> vector<T, A>::iterator::iterator(const iterator &_itr){
	itr = _itr.itr;
	parent = _itr.parent;
}

template<class T, class A> typename vector<T, A>::iterator& vector<T, A>::iterator::operator= (const iterator &_itr){
	itr = _itr.itr;
	parent = _itr.parent;
	return *this;
}

template<class T, class A> typename vector<T, A>::iterator& vector<T, A>::iterator::operator= (const size_t _itr){
	itr = _itr;
	parent = NULL;
	return *this;
}

template<class T, class A> typename vector<T, A>::iterator& vector<T, A>::iterator::operator++ (){
	itr++;
	return *this;
}

template<class T, class A> typename vector<T, A>::iterator& vector<T, A>::iterator::operator++ (int){
	iterator itr(*this);
	++(*this);
	return itr;
}

template<class T, class A> typename vector<T, A>::iterator& vector<T, A>::iterator::operator-- (){
	itr--;
	return *this;
}

template<class T, class A> typename vector<T, A>::iterator& vector<T, A>::iterator::operator-- (int){
	iterator itr(*this);
	--(*this);
	return itr;
}

template<class T, class A> typename vector<T, A>::iterator& vector<T, A>::iterator::operator+ (const iterator &_itr){
	itr += _itr.itr;
}

template<class T, class A> typename vector<T, A>::iterator& vector<T, A>::iterator::operator+ (const size_t _itr){
	itr += _itr;
}

template<class T, class A> typename vector<T, A>::iterator& vector<T, A>::iterator::operator- (const iterator &_itr){
	itr -= _itr.itr;
}

template<class T, class A> typename vector<T, A>::iterator& vector<T, A>::iterator::operator- (const size_t _itr){
	itr -= _itr;
}

template<class T, class A> T& vector<T, A>::iterator::operator* (){
	if(parent == NULL || (parent != NULL && (itr < 0 || itr > parent->v_size)))
		throw OutOfRange();
	return parent->a[itr];
}

template<class T, class A> vector<T, A>::iterator::operator int(){
	return itr;
}

///////////////////////////////VECTOR////////////////////////////////
template<class T, class A> vector<T, A>::vector(){
	a = allocator.resize(NULL, 0);
	v_size = 0;
}

template<class T, class A> vector<T, A>::vector(const vector<T, A> &_vector){
	a = allocator.resize(NULL, _vector.v_size);
	allocator.memcpy(a, _vector.a, _vector.v_size);
	v_size = _vector.v_size;
}

template<class T, class A> vector<T, A>::~vector(){
	allocator.free(a);
}

template<class T, class A> T& vector<T, A>::operator[] (size_t _pos){
	if(_pos < 0 || _pos >= v_size)
		throw OutOfRange();
	return a[_pos];
}

template<class T, class A> typename vector<T, A>& vector<T, A>::operator= (const vector<T, A> &_vector){
	a = allocator.resize(a, _vector.v_size);
	v_size = _vector.v_size;
	for(iterator i = begin(); i != end(); i++)
		a[i] = _vector[i];
}

template<class T, class A> typename vector<T, A>::iterator vector<T, A>::pos(const size_t pos){
	return iterator(pos, this);
}

template<class T, class A> typename vector<T, A>::iterator vector<T, A>::begin(){
	return pos(0);
}

template<class T, class A> typename vector<T, A>::iterator vector<T, A>::end(){
	return pos(v_size);
}

template<class T, class A> size_t vector<T, A>::size(){
	return v_size;
}

template<class T, class A> void vector<T, A>::resize(const size_t _size, const T &_val){
	a = allocator.resize(a, _size);
	if(v_size < _size)
		for(iterator i = v_size; i != end(); i++)
			a[i] = _val;
	v_size = _size;
}

template<class T, class A> size_t vector<T, A>::capacity(){
	return allocator.getSize();
}

template<class T, class A> void vector<T, A>::reserve(const size_t n){
	a = allocator.resize(a, n);
}

template<class T, class A> T vector<T, A>::front(){
	return *begin();
}

template<class T, class A> T vector<T, A>::back(){
	return *(--end());
}

template<class T, class A> void vector<T, A>::push_back(const T &_val){
	insert(iterator(v_size, this), _val);
}

template<class T, class A> void vector<T, A>::pop_back(){
	erase(iterator(v_size - 1, this));
}

template<class T, class A> void vector<T, A>::insert(const iterator _itr, const T &_val){
	if(_itr.itr < 0 || _itr.itr > v_size)
		throw OutOfRange();

	a = allocator.resize(a, v_size + 1);
	v_size += 1;
	allocator.memmove(&a[_itr.itr + 1], &a[_itr.itr], v_size - _itr.itr - 1);
	a[_itr.itr] = _val;
}

template<class T, class A> void vector<T, A>::erase(const iterator _itr){
	if(_itr.itr < 0 || _itr.itr > v_size)
		throw OutOfRange();
	
	allocator.memmove(&a[_itr.itr], &a[_itr.itr + 1], v_size - _itr.itr - 1);
	a = allocator.resize(a, v_size - 1);
	v_size -= 1;
}

template<class T, class A> void vector<T, A>::clear(){
	vector<T, A>::~vector();
	v_size = 0;
	a = NULL;
}

template<class T, class A> bool vector<T, A>::empty(){
	return v_size == 0;
}

};
#endif