#include "String.h"
#include <cstdlib>


//////////////////PROXY CHAR////////////////////////////

string::ProxyChar::ProxyChar(string *_str, size_t _pos){
	if(_pos < 0 || _pos > _str->size() - 1)
		throw out_of_range();
	pos = _pos;
	ProxyChar::s = _str;
}

void string::ProxyChar::operator= (const char c){
	if(s->buf->countRef == 1){
		s->buf->str[pos] = c;
		return;
	}
	
	s->buf->countRef--;
	s->buf = new string::S_Buf(*s->buf);
	s->buf->str[pos] = c;
}

string::ProxyChar::operator char(){
	return s->buf->str[pos];
}

/////////////////////BUF///////////////////////////
string::S_Buf::S_Buf(){
	countRef = 1;
	str = new char;
	strcpy(str, "");
}

string::S_Buf::S_Buf(const char* _str, const size_t _size, const size_t _count_repeat){
	countRef = 1;
	str = new char[(_size * _count_repeat) + 1];

	for(size_t i = 0; i < _count_repeat; i++)
		strcpy(&(str[_size * i]), _str);
}

string::S_Buf::S_Buf(string::S_Buf& _buf){
	countRef = 1;
	str = new char[strlen(_buf.str) + 1];
	strcpy(str, _buf.str);	
}

string::S_Buf::~S_Buf(){
	delete[] str;		
}

void string::S_Buf::destroy(){
	if(countRef == 1)
		delete[] str;
	str = NULL;
}

/////////////////////STRING///////////////////////////////////////

size_t string::size(){
	return s_size;
}

string string::concat(const char* _str1,const char* _str2){
	char *buf = new char[strlen(_str1) + strlen(_str2) + 1];
	strcpy(buf, _str1);
	strcpy(&(buf[strlen(_str1)]), _str2);
	string *s = new string(buf);
	
	delete[] buf;

	return *s;
}

string::string(){
	buf = new S_Buf;
	s_size = 0;
}

string::string(const char c, size_t _count){
	buf = new S_Buf(&c, 1, _count);
	s_size = _count;
}

string::string(const char* _str){
	buf = new S_Buf(_str, strlen(_str), 1);
	s_size = strlen(_str);
}

string::string(const char* _str, size_t _count){
	buf = new S_Buf(_str, strlen(_str), _count);
	s_size = _count * strlen(_str);
}

string::string(string &_str){
	buf = _str.buf;
	buf->countRef++;
	s_size = _str.s_size;
}

string::~string(){
	if(buf->countRef == 1)
		delete buf;
	else
		buf->countRef--;
}

void string::clear(){
	delete buf;

	buf = new string::S_Buf("", 0, 1);
	s_size = 0;
}

bool string::empty(){
	return s_size == 0;
}

char* string::c_str(){
	if(buf->countRef != 1){
		buf->countRef--;
		buf = new string::S_Buf(*buf);
	}
	return buf->str;
}

string::ProxyChar string::operator[] (size_t _pos){
	return ProxyChar(this, _pos);
}

void string::operator= (const string &_str){
	buf->destroy();
	s_size = _str.s_size;
	buf = _str.buf;
	buf->countRef++;
}

void string::operator= (const char* _str){
	buf->destroy();
	s_size = strlen(_str);
	buf = new string::S_Buf(_str, s_size, 1);
}

void string::operator= (const char c){
	buf->destroy();
	s_size = 1;
	buf = new string::S_Buf(&c, 1, 1);
}

string operator+ (const string& _str1, const string& _str2){
	return string::concat((*_str1.buf).str, (*_str2.buf).str); 
}

string operator+	(const char* _str1, const string& _str2){
	return string::concat(_str1, (*_str2.buf).str);
}

string operator+	(const string& _str1, const char* _str2){
	return string::concat((*_str1.buf).str, _str2);
}

bool operator== (const string& _str1, const string& _str2){
	return strcmp((*_str1.buf).str, (*_str2.buf).str) == 0;
}
bool operator== (const char* _str1, const string& _str2){
	return strcmp(_str1, (*_str2.buf).str) == 0;
}
bool operator== (const string& _str1, const char* _str2){
	return strcmp((*_str1.buf).str, _str2) == 0;
}
bool operator<= (const string& _str1, const string& _str2){
	return strcmp((*_str1.buf).str, (*_str2.buf).str) <= 0;
}
bool operator<= (const char* _str1, const string& _str2){
	return strcmp(_str1, (*_str2.buf).str) <= 0;
}
bool operator<= (const string& _str1, const char* _str2){
	return strcmp((*_str1.buf).str, _str2) <= 0;
}
bool operator>= (const string& _str1, const string& _str2){
	return strcmp((*_str1.buf).str, (*_str2.buf).str) >= 0;
}
bool operator>= (const char* _str1, const string& _str2){
	return strcmp(_str1, (*_str2.buf).str) >= 0;
}
bool operator>= (const string& _str1, const char* _str2){
	return strcmp((*_str1.buf).str, _str2) >= 0;
}
bool operator!= (const string& _str1, const string& _str2){
	return strcmp((*_str1.buf).str, (*_str2.buf).str) != 0;
}
bool operator!= (const char* _str1, const string& _str2){
	return strcmp(_str1, (*_str2.buf).str) != 0;
}
bool operator!= (const string& _str1, const char* _str2){
	return strcmp((*_str1.buf).str, _str2) != 0;
}
bool operator> (const string& _str1, const string& _str2){
	return strcmp((*_str1.buf).str, (*_str2.buf).str) > 0;
}
bool operator> (const char* _str1, const string& _str2){
	return strcmp(_str1, (*_str2.buf).str) > 0;
}
bool operator> (const string& _str1, const char* _str2){
	return strcmp((*_str1.buf).str, _str2) > 0;
}
bool operator< (const string& _str1, const string& _str2){
	return strcmp((*_str1.buf).str, (*_str2.buf).str) < 0;
}
bool operator< (const char* _str1, const string& _str2){
	return strcmp(_str1, (*_str2.buf).str) < 0;
}
bool operator< (const string& _str1, const char* _str2){
	return strcmp((*_str1.buf).str, _str2) < 0;
}

