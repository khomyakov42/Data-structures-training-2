#include"trie.h"
#include<list>
#include<cstdarg>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include<map>
#include<fstream>
#include<set>

#define L __LINE__
#define TCON hmw::trie
#define TEST start();{
#define END }end_test();
#define test(x) _test(x, __LINE__, true)

#define OUT " Out of range! "
#define NOTDEF " Can't dereference iterator! "

#define st {int i = 0; if(tests_in_block_passed){ try{
#define testitr(T, exc) }catch(hmw::TCON<T>::Exception e){i++;test(e.error == exc);}; if(1 != i)test(false);};};

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

template<class t>
void appendcon(TCON<t, t> &list, int count, ...){
	va_list vl;
   va_start(vl, count);

	if(!tests_in_block_passed)
		return;
	
	for(count; count > 0; count--){
      t x = va_arg(vl, typename t);
		list.insert(x, x);
   }

	va_end(vl);
}
template<class t, class t2>
void testcon(int line, TCON<t, t2> &l, int count, ...){
	va_list vl;
	va_start(vl, count);
	if(!tests_in_block_passed)
		return;

	_test(line, l.size() == count, false);
	
	for(TCON<t, t2>::iterator i = l.begin(); i != l.end(); ++i){
		t2 x = va_arg(vl, t2);
		_test(*i == x, line, false);
	}
	std::cout << "test passed\n";
	va_end(vl);
}

template<class t>
void outcon(TCON<t, t> &l){
	std::cout << "OUT LIST\n"; 
	for(TCON<t, t>::iterator i = l.begin(); i != l.end(); i++)
		std::cout << *i << " ";
	std::cout << "\n";
}

int main(){
	TEST
      TCON<string, int> con;
      con.insert("01", 1);
      con.insert("012", 12);
      testcon<string, int>(L, con, 2, 1, 12);

      con.insert("02", 2);      
      testcon<string, int>(L, con, 3, 1, 12, 2);

      con.insert("022", 22);
      con.insert("0223", 223);
      con.insert("0225", 225);
      con.insert("0224", 224);
      testcon<string, int>(L, con, 7, 1, 12, 2, 22, 223, 224, 225);
   END

   TEST
      TCON<string, int> con;
      
      con.insert("cap", 2);
      con.insert("go", 5);
      con.insert("car", 3);
      con.insert("c", 1);
      con.insert("cdr", 4);
      con.insert("if", 6);
      con.insert("it", 8);
      con.insert("is", 7);
      testcon<string, int>(L, con, 8, 1,2,3,4,5,6,7,8);
     
      con.erase("if");
      
      
      testcon<string, int>(L, con, 7, 1,2,3,4,5,7,8);
      con.erase("cap");
      con.erase("go");
      testcon<string, int>(L, con, 5, 1,3,4,7,8);

      con.erase("it");
      con.erase("is");
      con.erase("c");
      testcon<string, int>(L, con, 2, 3,4);

      con.erase("cdr");
      con.erase("car");
      test(con.size() == 0 && con.empty());
      
      con.insert("cap", 2);
      con.insert("go", 5);
      con.insert("car", 3);
      con.insert("c", 1);
      con.insert("cdr", 4);
      con.insert("if", 6);
      con.insert("it", 8);
      con.insert("is", 7);
      testcon<string, int>(L, con, 8, 1,2,3,4,5,6,7,8);
   END

	TEST
		TCON<string, int> con;
		TCON<string, int>::iterator itr1, itr2, itr3;
      
      con.insert("cap", 2);
      con.insert("go", 5);
      con.insert("car", 3);
      con.insert("c", 1);
      con.insert("cdr", 4);
      con.insert("if", 6);
      con.insert("it", 8);
      con.insert("is", 7);

		itr1 = con.find("is");
		test(*itr1 == 7);
		con.erase(itr1);
		test(con.find("is") == con.end());

		itr1 = con.find("c");
		test(*itr1 == 1);
		con.erase(itr1);
		test(con.find("c") == con.end());

		itr1 = con.find("cdr");
		test(*itr1 == 4);
		con.erase(itr1);
		test(con.find("cdr") == con.end());

		itr1 = con.find("it");
		test(*itr1 == 8);
		con.erase(itr1);
		test(con.find("it") == con.end());

		itr1 = con.end();
		itr2 = con.end();
		test(itr1 == itr2);
	END

   TEST
      TCON<string, int> con;
      TCON<string, int>::iterator itr;
      con.insert("cap", 2);
      con.insert("go", 5);
      con.insert("car", 3);
      con.insert("c", 1);
      con.insert("cdr", 4);
      con.insert("if", 6);
      con.insert("it", 8);
      con.insert("is", 7);

      itr = con.begin();
      for(int i = 0; itr != con.end(); ++i, ++itr)
         if(i + 1 != *itr){
            test(false);
            break;
         }
			else
				printf("%d ", *itr);
   END

   TEST
      TCON<string, int> con;
      vector<pair<string, int>> res;
		int count = 100;
		clock_t t;

      for(int i = 0; i < count; i++){
         string s = RandStr(10);
         int x = rand();
         res.push_back(pair<string, int>(s, x));
      }

		t = clock();
		for(int i = 0; i < count; i++)
			con[res[i].first] = res[i].second;
		cout << "construction took " << clock() - t << "\n";
		 

      for(int i = 0; i < count; i++)
         if(con[res[i].first] != res[i].second){
            test(false);
            break;
         }

		t = clock();
		bool fail = false;
      for(int i = 0; i < count; i++)
         if(*con.find(res[i].first) != res[i].second){
            test(false);
				fail = true;
            break;
         }

		if(!fail){
			test(true);
			cout << "search took " << clock() - t << "\n";
		}
		
		t = clock();
		int i = 0;

		for(TCON<string, int>::iterator itr = con.begin(); itr != con.end(); itr++)
			i++;

		if(i != count)
			test(false);
		else{
			test(true);
			cout << "iteration took " << clock() - t << "\n";
		}
		
		t = clock();
		con.clear();
		cout << "clear took " << clock() - t << "\n";

		test(con.size() == 0);
   END

	TEST
		TCON<string, int> con;
		vector<pair<string, int>> res;

		while(con.size() < 1000)
			if(rand() % 3){
				string s = RandStr(100);
				int x = rand();
				res.push_back(pair<string, int>(s,x));
				con[s] = x;
			}
			else{
				if(!res.size())
					continue;
				
				int pos = rand() % res.size();
				con.erase(con.find((*(res.begin() + pos)).first));
				res.erase(res.begin() + pos);
			}

		bool fail = false;
		for(int i = 0; i < res.size(); i++)
			if(res[i].second != *con.find(res[i].first)){
				test(false);
				fail = true;
				break;
			}

		int i = 0;
		for(TCON<string, int>::iterator itr = con.begin(); itr != con.end(); itr++)
			i++;

		if(!fail && i == res.size())
			test(true);
	END

	std::cout<<"\n\nALL TESTS PASSED";
	getchar();
}
