#include"tree.h"
#include<list>
#include<cstdarg>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include<map>

#define L __LINE__
#define TCON map
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
void appendcon(hmw::TCON<t, t> &list, int count, ...){
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
template<class t>
void testcon(int line, hmw::TCON<t, t> l, int count, ...){
	va_list vl;
	va_start(vl, count);
	if(!tests_in_block_passed)
		return;

	_test(line, l.size() == count, false);
	
	for(hmw::TCON<t, t>::iterator i = l.begin(); i != l.end(); ++i){
		t x = va_arg(vl, t);
		_test(*i == x, line, false);
	}
	std::cout << "test passed\n";
	va_end(vl);
}

template<class t>
void outcon(hmw::TCON<t, t> l){
	std::cout << "OUT LIST\n"; 
	for(hmw::TCON<t, t>::iterator i = l.begin(); i != l.end(); i++)
		std::cout << *i << " ";
	std::cout << "\n";
}

int main(){
	TEST
      hmw::TCON<int, int> con;
      test(con.size() == 0);
      test(con.empty());
		con.insert(2, 2);
		testcon<int>(L,con , 1, 2);

		con.insert(1, 1);
		testcon<int>(L, con, 2, 1, 2);

		con.insert(3, 3);
		testcon<int>(L, con, 3, 1, 2, 3);

		con.insert(5, 5);
		testcon<int>(L, con, 4, 1, 2, 3, 5);

		con.insert(4, 4);
		testcon<int>(L, con, 5, 1, 2, 3, 4, 5);
	END

   TEST
      hmw::TCON<int, int> con;
      hmw::TCON<int, int>::iterator i;
      
      for(int j = 0; j < 100; j++)
         con.insert(j, j);

      i = con.begin();
      bool fail = false;
      for(int j = 0; j < 100; j++, i++)
         if(*i != j){
            fail = true;
            break;
         }
      test(!fail);

      int j = 0;
      for(i = con.begin(); i != con.end(); i++, j++);
      test(j == 100);
   END

	TEST
      hmw::TCON<int, int> con;
		appendcon<int>(con,7, 7, 8, 3, 5, 4, 2, 9);
		con.erase(con.begin());
		testcon<int>(L, con, 6, 3, 4, 5, 7, 8, 9);

		con.erase(--con.end());
		testcon<int>(L, con, 5, 3, 4, 5, 7, 8);

		con.erase(4);
		testcon<int>(L, con, 4, 3, 5, 7, 8);

		con.erase(7);
		testcon<int>(L, con, 3, 3, 5, 8);

		con.erase(5);
		testcon<int>(L, con, 2, 3, 8);

		con.erase(--con.end());
		testcon<int>(L, con, 1, 3);

		con.erase(con.begin());
		test(con.size() == 0);

		appendcon<int>(con, 7, -7, -8, -3, -5, -4, -2, -9);
		con.erase(con.begin());
		testcon<int>(L, con, 6, -8, -7, -5, -4, -3, -2);

		con.erase(--con.end());
		testcon<int>(L, con, 5, -8, -7, -5, -4, -3);

		con.erase(-4);
		testcon<int>(L, con, 4, -8, -7, -5, -3);

		con.erase(-7);
		testcon<int>(L, con, 3, -8, -5, -3);

		con.erase(-5);
		testcon<int>(L, con, 2, -8, -3);

		con.erase(--con.end());
		testcon<int>(L, con, 1, -8);

		con.erase(con.begin());
		test(con.empty());
	END

	TEST
      hmw::TCON<int, int> con;
		appendcon<int>(con, 6, 0, 1 , 2, 3, 4, 5);

		hmw::TCON<int, int>::iterator iter = con.begin();

		test(*iter == 0);

		for(int i = 0; i < 5; i++)
			iter++;

		test(*iter == 5);

		iter++;
		test(iter == con.end());

		for(int i = 0; i < 6; i++)
			iter--;

		test(iter == con.begin());
		test(*iter == *con.begin());
	END

	TEST
      hmw::TCON<int, int> con;
		appendcon<int>(con ,4, 0, 2, 4, 7);
		hmw::TCON<int, int>::iterator iter = con.end();

		iter--;
		test(*iter == 7);

      iter++;
		test(iter == con.end());

		for(int i = 0; i < 4; i++)
			iter--;

		test(*iter == 0);

      iter++;
      test(*iter == 2);
	END

	TEST
      hmw::TCON<int, int> con;
		appendcon<int>(con, 4, 0, 1, 2, 3);
		hmw::TCON<int, int>::iterator iter = con.begin();

		test(*iter == 0);
		iter.shift(1);
		test(*iter == 1);

      iter.shift(3);
		test(iter == con.end());

      iter.shift(-1);
      test(con.end() == iter);
      test(*iter == 3);
		iter.shift(-3);
		test(*iter == 0);
      
      iter.shift(1);
      iter.shift(2);
      iter.shift(-3);

      test(*iter == 0);
	END

	TEST
      hmw::TCON<int, int> con;
		appendcon<int>(con, 7, 7, 4, 2, 0, 1, 3, 9);

      hmw::TCON<int, int>::iterator iter = con.begin();
      iter.shift(2);

      con.erase(iter);
		testcon<int>(L, con, 6, 0, 1, 3, 4, 7, 9);


		iter = con.find(4);
      
      test(*iter == 4);
		testcon<int>(L, con, 6, 0, 1, 3, 4, 7, 9);

		iter = con.begin();
		con.erase(iter);
		testcon<int>(L, con, 5, 1, 3, 4, 7, 9);

		iter = --con.end();
		con.erase(iter);
      con.erase(con.begin());
		testcon<int>(L, con, 3, 3, 4, 7);

		iter = con.begin();
		iter.shift(1);
		test(*iter == 4);
      
      con.erase(iter);
		testcon<int>(L, con, 2, 3, 7);

		iter = con.find(7);
      iter.shift(1);
      test(iter == con.end());
      iter--;
		con.erase(iter);
		con.erase(con.begin());

		test(con.size() == 0);
      test(con.empty());

		con.insert(6, 6);
      con.erase(con.begin());
		test(con.size() == 0);
	END

	TEST
      hmw::TCON<int, int> con;
      hmw::TCON<int, int>::iterator itr;
      int i = 0;

		for(i = 0; i <= 10000; i++)
			con.insert(i, i);

      bool fail = false;
		for(itr = con.begin(), i = 0; itr != con.end(); i++, itr++)
			if(*itr != i && !fail)
				fail = true;
      test(!fail);
	END

   TEST
      hmw::TCON<int, int> con1;
      appendcon<int>(con1, 2, 1, 2);
      hmw::TCON<int, int> con2(con1);
      hmw::TCON<int, int> con3 = con1, con4 = con2;

      con1.erase(1); con1.erase(2);
      test(con2.size() == 2 && !con2.empty());
      testcon<int>(L, con2, 2, 1, 2);

      con2.erase(1); con2.erase(2);
      test(con3.size() == 2&& con4.size() == 2);
      testcon<int>(L, con3, 2, 1, 2);
      testcon<int>(L, con4, 2, 1, 2);
   END

   TEST
      hmw::TCON<string, int> con;
      string s = "111111";
      con.insert(0, s);
      con.insert(1, "222222");
      s = "33333";
      test("111111" == *con.find(0));
   END

   TEST
      const int count = 10000;
      hmw::TCON<int,int> con;
      std::map<int, int> con2;
      list<int> l;
      clock_t t;
      
      t = clock();
      for(int i = 0; i < count; i++)
         con[i] = i;
      std::cout << "run build MY MAP = " << clock() - t << endl;

      t = clock();
      for(int i = 0; i < count; i++)
         con2[i] = i;
      std::cout << "run build STL MAP = " << clock() - t << endl;
      
      t = clock();
      for(int i = 0; i < count; i++)
         l.push_back(i);
      std::cout << "run build STL LIST = " << clock() - t << endl;
      
      std::cout << "\n";

      t = clock();
      for(hmw::TCON<int, int>::iterator i = con.begin(); i != con.end(); i++);
      std::cout<<"run time MY MAP iterator = " << clock() - t << endl;

      t = clock();
      for(map<int, int>::iterator i = con2.begin(); i != con2.end(); i++);
      std::cout<<"run time STL MAP iterator = " << clock() - t << endl;
      
      t = clock();
      for(list<int>::iterator i = l.begin(); i != l.end(); i++);
      std::cout<<"run time STL LIST iterator = " << clock() - t << endl;

      std::cout << "\n";

      t = clock();
      int x = con[count - 1];
      std::cout << "run time MY MAP find element = " << clock() - t << endl;

      t = clock();
      x = con2[count - 1];
      std::cout << "run time STL MAP find element = " << clock() - t << endl;

      std::cout << "\n";

      t = clock();
      con.clear();
      std::cout << "run time clear MY MAP =" << clock() - t << endl;
      
      t = clock();
      con2.clear();
      std::cout << "run time clear STL MAP = " << clock() - t << endl;
      
      t = clock();
      l.clear();
      std::cout << "run time clear STL LIST = " << clock() - t << endl;
   END

	TEST
		hmw::TCON<hmw::TCON<char, int>, string> con;
      hmw::TCON<hmw::TCON<char, int>, string>::iterator itr;
      hmw::TCON<char, int> *p;
      hmw::TCON<char, int>::iterator itr3;
		std::list<string> keys;
      std::list<string>::iterator itr2;
      const int lenStr = 100;
      const int count = 1000;

		while(con.size() < count)
			if(rand() % 3){
				string key = RandStr(lenStr);
            
            keys.push_back(key);

            p = new hmw::TCON<char, int>;

            for(int i = 0; i < key.size(); i++)
               p->insert(i, key[i]);

            con.insert(key, *p);
            con.find(key);
			}
			else{
				if(!con.size())
					continue;
				int pos = rand() % con.size();
            itr2 = keys.begin();
            for(int i = 0; i < pos; i++, itr2++);
            
            con.erase(*itr2);
            keys.erase(itr2);
			}

      bool fail = false;
      for(itr2 = keys.begin(); itr2 != keys.end(); itr2++){
         *p = (con[*itr2]);
         string key = "";
         for(itr3 = (*p).begin(); itr3 != (*p).end(); itr3++)
            key += *itr3;

         if(key != *itr2){
            fail = true;
            break;
         }
      }
      test(!fail);
	END
   
	std::cout<<"\n\nALL TESTS PASSED";
	getchar();
}
