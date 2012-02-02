#include"vector.h"
#include<cstdarg>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<time.h>
#include<vector>

#define L __LINE__
#define TCON vector
#define TEST start();{
#define END }end_test();
#define test(x) _test(x, __LINE__, true)

#define OUT

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
void testcon(int line, hmw::TCON<t> l, int count, ...){
	va_list vl;
	va_start(vl, count);
	if(!tests_in_block_passed)
		return;

	_test(line, l.size() == count, false);
	
	for(hmw::TCON<t>::iterator i = l.begin(); i != l.end(); ++i){
		t x = va_arg(vl, t);
		_test(*i == x, line, false);
	}
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
		test(con.size() == 1);

		test(con[0] == 1);

		con.push_back(2);
		test(con.size() == 2);
		test(con[0] == 1 && con[1] == 2);

		hmw::TCON<int>::iterator itr;
		itr = con.begin();
		test(itr == con.begin());
		test(*itr == 1);
		
		itr++;
		test(*itr == 2);

		itr++;
		test(itr == con.end());

		itr--;
		test(itr != con.begin());
		test(*itr == 2);
	END

	TEST
		hmw::TCON<int> con;
		test(con.empty());
		appendcon<int>(con, 6, 0, 1, 2, 3, 4, 5);
		test(con.size() == 6);
		testcon<int>(L, con, 6, 0, 1, 2, 3, 4, 5);

		con.pop_back();
		test(con.size() == 5);
		testcon<int>(L, con, 5, 0, 1, 2, 3, 4);
		
		con.pop_back();
		testcon<int>(L, con, 4, 0, 1, 2, 3);
		test(*con.begin() == 0);
		test(con.begin() != con.end());
		test(!con.empty());
	END

	TEST
		hmw::TCON<int> con;
		hmw::TCON<int>::iterator i;
		appendcon<int>(con, 3, 0, 1, 2);
		i = con.end();
		i--;
		test(*i == 2);
		
		i--; i--;
		test(*i == 0);

		i++;
		test(*i == 1);
		con.pop_back();
		con.pop_back();

		testcon<int>(L, con, 1, 0);
		test(con.size() == 1);

		i = con.begin();
		test(*i == --con.end());

		appendcon<int>(con, 3, 1, 2, 3);
		test(con.size() == 4);
		testcon<int>(L, con, 4, 0, 1, 2, 3);

		i = con.pos(2);
		test(*i == 2);
		
		i++;
		test(*i == 3);
		i++;
		test(i == con.end());

		i--;i++;
		test(i == con.end());
		
		i--;
		test(*i == 3);
	END

	TEST
		hmw::TCON<int> con;
		hmw::TCON<int>::iterator i1, i2, i3;
		appendcon<int>(con, 5, 1, 2, 3, 4, 5);

		i1 = con.begin();
		i2 = i1;

		test(i2 == i1++);
		test(i2++ != i1);

		test(i2 == i1);
		test(i2-- == i1--);
		test(i1 == i2);
	END

	TEST
		hmw::TCON<int> con1;
		appendcon<int>(con1, 4, 1, 2, 3, 4);
		hmw::TCON<int> con2(con1);

		testcon<int>(L, con1, 4, 1, 2, 3, 4);
		testcon<int>(L, con2, 4, 1, 2, 3, 4);
		con2.erase(0);

		testcon<int>(L, con1, 4, 1, 2, 3, 4);
		testcon<int>(L, con2, 3, 2, 3, 4);
	END

	TEST
		hmw::TCON<int> con;
		con.reserve(1000);
		test(con.capacity() == 1000);
		for(int i = 0; i < 1000; i++)
			con.push_back(i);
	END
	
	TEST
		hmw::TCON<int> con;
		hmw::TCON<int>::iterator i;
		appendcon<int>(con, 4, 0, 1, 2, 3);

		i = con.begin();
		i++;i++;
		con.insert(i, 15);
		testcon<int>(L, con, 5, 0, 1, 15, 2, 3);
		 
		i = con.end();
		i--;
		test(*i == 3);

		i--;i++;i--;
		test(*i == 2);

		con.erase(i);
		testcon<int>(L, con, 4, 0, 1, 15, 3);
		
		con.erase(2);
		testcon<int>(L, con, 3, 0, 1, 3);

		i = con.pos(2);
		con.insert(i, 2);
		testcon<int>(L, con, 4, 0, 1, 2, 3);

		con.erase(con.begin());
		con.erase(con.begin());
		con.erase(--con.end());
		testcon<int>(L, con, 1, 2);

		con.erase(0);
		test(con.size() == 0);

		test(con.end() == con.begin());
	END

	TEST
		hmw::TCON<int> con;
		appendcon<int>(con, 4, 1, 2, 3, 4);

		test(con.front() == 1);
		test(con.back() == 4);

		con.pop_back();

		test(con.front() == 1);
		test(con.back() == 3);

		con.erase(0);

		test(con.front() == 2);
		test(con.back() == 3);

		con.erase(1);

		test(con.front() == con.back());
		test(con.front() == 2);
		test(con.size() == 1);

		con.pop_back();
		test(con.size() == 0);
		test(con.empty());
	END

	TEST
		hmw::TCON<int> con;
		hmw::TCON<int>::iterator i;

		appendcon<int>(con, 5, 1, 2, 3, 4, 5);
		testcon<int>(L, con, 5, 1, 2, 3, 4, 5);

		con.erase(2);
		testcon<int>(L, con, 4, 1, 2, 4, 5);

		con.clear();
		test(con.size() == 0);
		test(con.empty());

		con.push_back(1);
		con.push_back(2);

		test(con.size() == 2);
		testcon<int>(L, con, 2, 1, 2);

		con.erase(1);
		test(con.front() == 1);
		test(con.size() == 1);

		con.insert(0, 0);
		test(con.front() == 0 && con.back() == 1);

		con.clear();
		test(con.size() == 0);
		test(con.empty());
	END

	TEST
		hmw::TCON<int> con;
		int con2[32768];
		
		for(int i = 0; i < 1000; i++){
			con.push_back(i);
			con2[i] = i;
		}

		for(int i = 0; i < 2000;i++){
			int pos = rand() % 1000;
			con2[pos] = pos / 7;
			con[pos] = pos / 7;
		}

		for(int i = 0; i < 1000; i++)
			if(con[i] != con2[i]){
				test(false);
				break;
			}
	END



	TEST
		hmw::TCON<int> con;	
		con.begin();
		
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
		testcon<int>(L, con, 3, 1, 2, 3);
	END

	TEST
		hmw::TCON<int> con;
		appendcon<int>(con, 7, 1, 2, 3, 4, 5, 6, 7);
		hmw::TCON<int>::iterator itr1, itr2;
		itr1 = con.begin();
		itr2 = --con.end();
		for(i = 0, itr1, itr2; i < 6; i++, ++itr1, --itr2){
			if(i == 3)
				test(itr1 == itr2);
		}
		test(itr1 == (--con.end()));
		test(itr2 == con.begin());
		
		testcon<int>(L, con, 7, 1, 2, 3, 4, 5, 6, 7);
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
		test(itr == con.end());

		appendcon<int>(con, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
		itr = ++con.begin();
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
		std::vector<int> v;

		while(con.size() < 1000)
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
	
	TEST
		hmw::TCON<string> con;	
		con.begin();
		
		test(con.size() == 0);
		con.push_back("aaa");
		
		hmw::TCON<string>::iterator itr;
		test(itr != con.begin());
		test(itr != con.end());
		itr = con.begin();
		test(itr == con.begin());

		test(*itr == "aaa");

		itr++;

		test(itr == con.end());

		con.push_back("bbb");
		con.push_back("ccc");
		test(con.size() == 3);

		test("bbb" == *hmw::TCON<string>::iterator(con.pos(1)));

		testcon<string>(L, con, 3, string("aaa"), string("bbb"), string("ccc"));
		con.clear();
		test(con.empty());
	END
	
	std::cout<<"\n\nALL TESTS PASSED";
	getchar();
}
