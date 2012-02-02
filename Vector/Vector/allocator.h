#ifndef __ALLOCATOR__
#define __ALLOCATOR__
#include <new>
#include <cstring>
#define CONST_INC 2
#define CONST_DEC 2 / 3

template<class T>
class Allocator{
	private:
		size_t size;
	public:
		virtual size_t getSize();
		virtual void free(T* _pMem);
		virtual T* alloc(size_t sizeMem);
		virtual T* realloc(T* _pMem, size_t newSizeMem);
		virtual void memmove(T* to, T* from, size_t count);
		virtual T* resize(T* _p, size_t _size);
		virtual void memcpy(T* to, T* from, size_t _size);
		Allocator(){size = 0;};
};

template<class T> size_t Allocator<T>::getSize(){
	return size;
}

template<class T> T* Allocator<T>::alloc(size_t sizeMem){
	T *p = new T[sizeMem];
	
	for(size_t i = 0; i < sizeMem; i++)
		operator new(sizeof(T), p + i);
	
	return p;
}

template<class T> void Allocator<T>::free(T* _pMem){
	if(_pMem == NULL)
		return;

	delete[] _pMem;
}

template<class T> T* Allocator<T>::realloc(T* _pMem, size_t newSizeMem){
	T *p = alloc(newSizeMem);
	this->memmove(p, _pMem, min(size, newSizeMem));
	this->free(_pMem);
	/*
	if(newSizeMem < size)
		free(_pMem + newSizeMem - 1);
	else 
		if(newSizeMem > size){ 
			p = alloc(newSizeMem);
			memmove(p, _pMem, size);
			free(_pMem);
		}*/
	return p;
}

template<class T> void Allocator<T>::memmove(T *to, T *from, size_t count){
	if(from == NULL || to == NULL)
		return;

	T *p = alloc(count);
	this->memcpy(p, from, count);
	this->memcpy(to, p, count);
	this->free(p);
}

template<class T> T* Allocator<T>::resize(T* _p, size_t _size){
	if(_size < size * CONST_DEC){
		_p = realloc(_p, size * CONST_DEC);
		size = size * CONST_DEC;
	}
	else if(_size > size){
		size_t c = (_size - size + 1) / CONST_INC; 
		c = c == 0? CONST_INC: CONST_INC * c;
		_p = realloc(_p, c + size);
		size = c + size;
	}
	else if(_size == 0){
		_p = alloc(CONST_INC);
		size = CONST_INC;
	}

	return _p;
}

template<class T> void Allocator<T>::memcpy(T* to, T* from, size_t _size){
	if(from == NULL || to == NULL)
		return;

	for(size_t i = 0; i < _size; i++)
		to[i] = from[i];
}

#endif