#include "..\..\List\List\List.h"
#include "..\..\Vector\Vector\vector.h"
#include "..\..\tree_map\tree_map\tree.h"
#include "algorithm.h"
#include<cstdarg>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<time.h>

#define L __LINE__
#define TCON list
#define TEST start();{ hmw::list<int> l; hmw::vector<int> v; hmw::map<int, int> m; 
#define END }end_test();
#define test(x) _test(x, __LINE__, true)

using namespace std;
int number_block_test = 0;
bool tests_in_block_passed = true;

string RandStr(int size){
	std::string s;
	for (int i = 0; i < size; i++) 
		s += ' ' + rand() % 96;
	return s;
}

void end_test(){
	std::cout << "BLOCK TEST "<< number_block_test;
	if(tests_in_block_passed)
		 std::cout << " PASSED\n";
	else
		std::cout << " FAIL\n";
		
}

void start(){
	tests_in_block_passed = true;
	number_block_test++;
	std::cout << "\nSTART BLOCK TEST " << number_block_test << "\n";
}

void test_fail(int line){
	if(!tests_in_block_passed)
		return;
	std::cout << "test fail in line " << line << "\n"; 
	tests_in_block_passed = false;
}

void _test(bool x, int line, bool iswrite){
	if(!tests_in_block_passed)
		return;

	if(!x)
		test_fail(line);
	else
		if(iswrite)
			std::cout << "test passed\n";
}

void appendcon(hmw::list<int> &l, hmw::vector<int> &v, hmw::map<int, int> &m, int count, ...){
	va_list vl;
   va_start(vl, count);

	if(!tests_in_block_passed)
		return;
	
	for(count; count > 0; count--){
      int x = va_arg(vl, int);
		l.push_back(x);
      v.push_back(x);
      m.insert(x, x);
   }

	va_end(vl);
}

void testcon(int line, hmw::list<int> &l, hmw::vector<int> &v, hmw::map<int, int> &m, int count, ...){
	va_list vl;
	va_start(vl, count);
	if(!tests_in_block_passed)
		return;

	_test(line, l.size() != v.size() || v.size() != m.size(), false);
	
   hmw::list<int>::iterator itr_l = l.begin();
   hmw::vector<int>::iterator itr_v = v.begin();
   hmw::map<int, int>::iterator itr_m = m.begin();

   for(int i = count; i > 0; i--, itr_l++, itr_v++, itr_m++){
		int x = va_arg(vl, int);
		_test(*itr_l == x && *itr_v == x && *itr_m == x , line, false);
	}

	std::cout << "test passed\n";
	va_end(vl);
}

template<class c>
void outcon(c l){
	std::cout << "OUTPUT " << typeid(l).name() << endl; 
	for(c::iterator i = l.begin(); i != l.end(); i++)
		std::cout << *i << " ";
	std::cout << "\n";
}

template<class T>
bool Comp(T x, T y){
   return x < y;
}

int main(){

   TEST
      appendcon(l, v, m, 5, 0, 1, 2, 3, 4);
      testcon(L, l, v, m, 5, 0, 1, 2, 3, 4);
      
      deleteByVal<hmw::list<int>, int>(l, 0);
      deleteByVal<hmw::map<int, int>, int>(m, 0);
      deleteByVal<hmw::vector<int>, int>(v, 0);
      testcon(L, l, v, m, 4, 1, 2, 3, 4);

      deleteByVal<hmw::list<int>, int>(l, 2);
      deleteByVal<hmw::map<int, int>, int>(m, 2);
      deleteByVal<hmw::vector<int>, int>(v, 2);

      deleteByVal<hmw::list<int>, int>(l, 4);
      deleteByVal<hmw::map<int, int>, int>(m, 4);
      deleteByVal<hmw::vector<int>, int>(v, 4);
      testcon(L, l, v, m, 2, 1, 3);

      deleteByVal<hmw::list<int>, int>(l, 1);
      deleteByVal<hmw::map<int, int>, int>(m, 1);
      deleteByVal<hmw::vector<int>, int>(v, 1);
      testcon(L, l, v, m, 1, 3);

      deleteByVal<hmw::list<int>, int>(l, 3);
      deleteByVal<hmw::map<int, int>, int>(m, 3);
      deleteByVal<hmw::vector<int>, int>(v, 3);

      testcon(L, l, v, m, 0);
   END

   TEST
      appendcon(l, v, m, 4, 0, 1, 2, 3);
      hmw::list<int>::iterator i1 = getIterByVal<hmw::list<int>, int>(l, 1);
      hmw::vector<int>::iterator i2 = getIterByVal<hmw::vector<int>, int>(v, 2);
      hmw::map<int, int>::iterator i3 = getIterByVal<hmw::map<int, int>, int>(m, 3);
      test(*i1 == 1 && *i2 == 2 && *i3 == 3);

      i1 = getIterByVal<hmw::list<int>, int>(l, 0);
      i2 = getIterByVal<hmw::vector<int>, int>(v, 0);
      i3 = getIterByVal<hmw::map<int, int>, int>(m, 0);
      l.erase(i1);
      v.erase(i2);
      m.erase(i3);

      testcon(L, l, v, m, 3, 1, 2, 3);

      i1 = getIterByVal<hmw::list<int>, int>(l, 3);
      i2 = getIterByVal<hmw::vector<int>, int>(v, 3);
      i3 = getIterByVal<hmw::map<int, int>, int>(m, 3);
      l.erase(i1);
      v.erase(i2);
      m.erase(i3);
      testcon(L, l, v, m, 2, 1, 2);

      i1 = getIterByVal<hmw::list<int>, int>(l, 1);
      i2 = getIterByVal<hmw::vector<int>, int>(v, 1);
      i3 = getIterByVal<hmw::map<int, int>, int>(m, 1);
      l.erase(i1);
      v.erase(i2);
      m.erase(i3);
      testcon(L, l, v, m, 1, 2);

      i1 = getIterByVal<hmw::list<int>, int>(l, 1);
      i2 = getIterByVal<hmw::vector<int>, int>(v, 1);
      i3 = getIterByVal<hmw::map<int, int>, int>(m, 1);
      test(i1 == l.end() && i2 == v.end() && i3 == m.end());
   END

   TEST
      appendcon(l, v, m, 5, 3, 1, -1, 100, -4);
      int x = min<hmw::list<int>, int>(l);
      test(x == -4);

      x = min<hmw::vector<int>, int>(v);
      test(x == -4);

      x = min<hmw::map<int, int>, int>(m);
      test(x == -4);
      
      hmw::list<int>::iterator i1 = getIterByVal<hmw::list<int>, int>(l, -4);
      hmw::vector<int>::iterator i2 = getIterByVal<hmw::vector<int>, int>(v, -4);
      hmw::map<int, int>::iterator i3 = getIterByVal<hmw::map<int, int>, int>(m, -4);
      l.erase(i1);
      v.erase(i2);
      m.erase(i3);

      x = min<hmw::list<int>, int>(l);
      test(x == -1);

      x = min<hmw::vector<int>, int>(v);
      test(x == -1);

      x = min<hmw::map<int, int>, int>(m);
      test(x == -1);

      l.erase(l.pos(2));
      v.erase(2);
      m.erase(-1);
      
      x = min<hmw::list<int>, int>(l);
      test(x == 1);

      x = min<hmw::vector<int>, int>(v);
      test(x == 1);

      x = min<hmw::map<int, int>, int>(m);
      test(x == 1);
   END

   TEST
      appendcon(l, v, m, 5, -3, -1, 1, -100, 4);
      int x = max<hmw::list<int>, int>(l);
      test(x == 4);

      x = max<hmw::vector<int>, int>(v);
      test(x == 4);

      x = max<hmw::map<int, int>, int>(m);
      test(x == 4);
      
      hmw::list<int>::iterator i1 = getIterByVal<hmw::list<int>, int>(l, 4);
      hmw::vector<int>::iterator i2 = getIterByVal<hmw::vector<int>, int>(v, 4);
      hmw::map<int, int>::iterator i3 = getIterByVal<hmw::map<int, int>, int>(m, 4);
      l.erase(i1);
      v.erase(i2);
      m.erase(i3);

      x = max<hmw::list<int>, int>(l);
      test(x == 1);

      x = max<hmw::vector<int>, int>(v);
      test(x == 1);

      x = max<hmw::map<int, int>, int>(m);
      test(x == 1);

      l.erase(l.pos(2));
      v.erase(2);
      m.erase(1);
      
      x = max<hmw::list<int>, int>(l);
      test(x == -1);

      x = max<hmw::vector<int>, int>(v);
      test(x == -1);

      x = max<hmw::map<int, int>, int>(m);
      test(x == -1);
   END

   TEST
      appendcon(l, v, m, 5, 0, 1, 2, 3, 4);
      turn<hmw::list<int>, int>(l);
      turn<hmw::vector<int>, int>(v);
      turn<hmw::map<int, int>, int>(m);
      testcon(L, l, v, m, 5, 4, 3, 2, 1, 0);

      turn<hmw::list<int>, int>(l);
      turn<hmw::vector<int>, int>(v);
      turn<hmw::map<int, int>, int>(m);
      testcon(L, l, v, m, 5, 0, 1, 2, 3, 4);

      l.push_back(5);
      v.push_back(5);
      m.insert(5, 5);
      turn<hmw::list<int>, int>(l);
      turn<hmw::vector<int>, int>(v);
      turn<hmw::map<int, int>, int>(m);
      testcon(L, l, v, m, 6, 5, 4, 3, 2, 1, 0);

      turn<hmw::list<int>, int>(l);
      turn<hmw::vector<int>, int>(v);
      turn<hmw::map<int, int>, int>(m);
      testcon(L, l, v, m, 5, 0, 1, 2, 3, 4, 5);
   END

   TEST
      appendcon(l, v, m, 10, 1, 5, -3, 7, 2, -1, 9, 3, 8, 0);

      sort<hmw::list<int>, int>(l, &(Comp<int>));
      sort<hmw::vector<int>, int>(v, &(Comp<int>));
      sort<hmw::map<int, int>, int>(m, &(Comp<int>));
      testcon(L, l, v, m, 10, -3, -1, 0, 1, 2, 3, 5, 7, 8, 9);

      sort<hmw::list<int>, int>(l, &(Comp<int>));
      sort<hmw::vector<int>, int>(v, &(Comp<int>));
      sort<hmw::map<int, int>, int>(m, &(Comp<int>));
      testcon(L, l, v, m, 10,  -3, -1, 0, 1, 2, 3, 5, 7, 8, 9);

      l.erase(l.pos(5));
      v.erase(5);
      m.erase(m.find(3));
      sort<hmw::list<int>, int>(l, &(Comp<int>));
      sort<hmw::vector<int>, int>(v, &(Comp<int>));
      sort<hmw::map<int, int>, int>(m, &(Comp<int>));
      testcon(L, l, v, m, 9,  -3, -1, 0, 1, 2, 5, 7, 8, 9);
   END
   
   TEST
      insertRandVal<hmw::list<int>, int>(l, 5, &rand);
      insertRandVal<hmw::vector<int>, int>(v, 5, &rand);
      insertRandVal<hmw::map<int, int>, int, int>(m, 5, &rand, &rand);
      outcon<hmw::list<int>>(l);
      outcon<hmw::vector<int>>(v);
      outcon<hmw::map<int, int>>(m);

      test(l.size() == m.size() && v.size() == m.size());

      insertRandVal<hmw::list<int>, int>(l, 5, &rand);
      insertRandVal<hmw::vector<int>, int>(v, 5, &rand);
      insertRandVal<hmw::map<int, int>, int, int>(m, 5, &rand, &rand);
      outcon<hmw::list<int>>(l);
      outcon<hmw::vector<int>>(v);
      outcon<hmw::map<int, int>>(m);
      test(l.size() == m.size() && v.size() == m.size() && v.size() == 10);
   END
   std::cout << "\n\nALL TEST PASSED" << endl;
   getchar(); 
}