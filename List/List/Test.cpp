#include"List.h"
#include<cstdarg>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<time.h>

#define L __LINE__
#define TCON list
#define TEST start();{
#define END }end_test();
#define test(x) _test(x, __LINE__, true)

using namespace std;
int number_block_test = 0;
bool tests_in_block_passed = true;

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
void appendcon(hmw::TCON<t> &list, int count, ...){
	va_list vl;
   va_start(vl, count);

	if(!tests_in_block_passed)
		return;
	
	for(count; count > 0; count--)
		list.push_back(va_arg(vl, typename t));

	va_end(vl);
}
template<class t>
void testcon(int line, hmw::TCON<t> list, int count, ...){
	va_list vl;
	va_start(vl, count);
	if(!tests_in_block_passed)
		return;

	_test(line, list.size() == count, false);
	
	for(hmw::list<t>::iterator i = list.begin(); i != list.end(); ++i)
		_test(line, (*i) != va_arg(vl, t), false);
	std::cout << "test passed\n";
	va_end(vl);
}

template<class t>
void outcon(hmw::TCON<t> l){
	std::cout << "OUT LIST\n"; 
	for(hmw::TCON<t>::iterator i = l.begin(); i != l.end(); i++)
		std::cout << *i << " ";
	std::cout << "\n";
}


int main(){
	
	int i, j;
	
	TEST
		hmw::TCON<int> con;	
		test(con.size() == 0);
		con.push_back(1);
		
		hmw::TCON<int>::iterator itr;
		test(itr != con.begin());
		test(itr != con.end());
		itr = con.begin();
		test(itr == con.begin());

		test(*itr == 1);

		itr++;

		test(itr == con.end());

		con.push_back(2);
		con.push_back(3);
		test(con.size() == 3);

		for(itr = con.begin(), i = 0; itr != con.end(); itr++, i++)
			test(*itr == i + 1);

		test(i == con.size());
		con.clear();
		test(con.size() == 0);
	END

	TEST
		hmw::TCON<int> con;
		appendcon<int>(con, 5, 1, 2, 3, 4, 5);
		testcon<int>(L, con, 5, 1, 2, 3, 4, 5);
		con.pop_front();
		testcon<int>(L, con, 4, 2, 3, 4, 5);
		
		con.pop_front();
		testcon<int>(L, con, 3, 3, 4, 5);

		con.pop_back();
		testcon<int>(L, con, 2, 3, 4);
		
		con.pop_back();
		testcon<int>(L, con, 1, 3);

		con.pop_back();
		test(con.size() == 0);
	END

	TEST
		hmw::TCON<int> con;
		
		con.push_front(1);
		con.push_front(2);
		testcon<int>(L, con, 2, 2, 1);
		test(con.size() == 2);

		for(i = 0; i < 3; i++)
			con.push_front(i + 3);
		appendcon<int>(con, 5, 1, 2, 3, 4, 5);
		testcon<int>(L, con, 10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5);
		
		for(i = 0; i < 2; i++){
			con.pop_front();
			con.pop_back();		
		}

		testcon<int>(L, con, 6, 3, 2, 1, 1, 2, 3);
		con.clear();
		test(con.size() == 0);
	END

	TEST
		hmw::TCON<int> con;
		appendcon<int>(con, 5, 1, 2, 3, 4, 5);
		hmw::TCON<int>::iterator itr = con.begin();
		test(*itr == 1);
		test(*itr == *(con.begin()));
		test(*itr == con.front());

		itr = con.end();
		itr--;

		test(*itr == 5);
		test(*itr == con.back());

		con.pop_front();
		itr = con.begin();
		test(*itr == 2);
		test(*itr == *(con.begin()));
		test(*itr == con.front());

		con.pop_back();
		itr = con.end()--;
		test(*itr == 4);
		test(*itr == con.back());
		
		test(con.size() == 3);
	END

	TEST
		hmw::TCON<int> con;
		appendcon<int>(con, 7, 1, 2, 3, 4, 5, 6, 7);
		hmw::TCON<int>::iterator itr1, itr2;
		itr1 = con.begin();
		itr2 = con.end()--;
		for(i = 0, itr1, itr2; i < 6; i++, itr1++, itr2--){
			if(i == 3)
				test(itr1 == itr2);
		}
		test(itr1 == (con.end()--));
		test(itr2 == con.begin());
		
		testcon(L, con, 7, 1, 2, 3, 4, 5, 6, 7);
		test(*itr1 == 7);
		test(*itr2 == 1);

		itr1 = itr2;
		itr1++;
		test(itr1 != itr2);
		test(*itr1 == 2);
		test(*itr2 == 1);

		itr2--;
		test(itr1 != itr2);
		test(*itr1 == 2);

		itr1 = con.end();
		itr1--;
		itr1++;
		test(itr1 == con.end());
	END

	TEST
		hmw::TCON<int> con;
		hmw::TCON<int>::iterator itr = con.begin();
		test(itr == con.begin());
		test(itr == (con.end()));

		appendcon<int>(con, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
		itr = con.begin()++;
		con.erase(itr);
		testcon<int>(L, con, 9, 0, 2, 3, 4 , 5, 6 ,7, 8, 9);
		
		itr = con.pos(4);
		test(*itr == 5);
		con.erase(itr);
		testcon<int>(L, con, 8, 0, 2, 3, 4, 6, 7, 8, 9);
		
		for(i = 0; i < 8; i++)
			con.erase(con.pos(8 - (i + 1)));
		
		test(con.size() == 0);
		con.clear();
		test(con.size() == 0);
	END

	TEST
		hmw::TCON<int> con;
		hmw::TCON<int>::iterator itr;

		for(i = 0; i < 10; i++)
			if(i % 2)
				con.push_back(i);
			else
				con.push_front(i);
		testcon(L, con, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9);

		for(i = 0; i < 10; i++)
			if(i % 2)
				con.assign(con.pos(i), 0);
			else
				con.assign(con.pos(i), 1);
		testcon(L, con, 10, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0);
	END

	TEST
		hmw::TCON<int> con;
		appendcon<int>(con, 7, 0, 1, 2, 3, 4, 5, 6);
		hmw::TCON<int> con2(con);
		testcon<int>(L, con2, 7, 0, 1, 2, 3, 4, 5, 6);

		con.pop_back();
		con.pop_front();
		test(con.size() == 5);
		test(con2.size() == 7);
		test(*(con.begin()) == 1);
		test(*(con2.begin()) == 0);
	END

	TEST
		hmw::TCON<int> con;
		std::vector<int> v;

		while(con.size() < 10000)
			if(rand() % 3){
				int x = rand();
				v.push_back(x);
				con.push_back(x);
			}
			else{
				if(!con.size())
					continue;
				int x = rand() % con.size();
				con.erase(con.pos(x));
				std::vector<int>::iterator itr(v.begin());
				itr = itr + x;
				v.erase(itr);
			}
		hmw::TCON<int>::iterator citr = con.begin();
		std::vector<int>::iterator vitr(v.begin());
		for(citr, vitr; citr != con.end(); vitr++, citr++)
			if(*vitr != *citr)
				test_fail(L);
	END

	std::cout<<"\n\nALL TESTS PASSED";
	getchar();
}
