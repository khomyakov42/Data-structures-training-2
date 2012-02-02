#include"hash_map.h"
#include"algorithm.h"
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
#define TEST start();{val.clear();
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
   hmw::list<t> val;
	if(!tests_in_block_passed)
		return;

   for(int i = 0; i < count; i++)
      val.push_back(va_arg(vl, t));

	_test(line, l.size() == count, false);
	
	for(hmw::TCON<t, t>::iterator i = l.begin(); i != l.end(); ++i){
		t x = *i;
      bool find = false;
      for(hmw::list<t>::iterator itr = val.begin(); itr != val.end(); itr++)
         if(x == *itr){
            find = true;
            val.erase(itr);
            break;
         }
		_test(find, line, false);
	}
	std::cout << "test passed\n";
	va_end(vl);
}

template<class t>
void testcon(int line, hmw::TCON<t, t> l, hmw::list<t> val){
	if(!tests_in_block_passed)
		return;

	_test(line, l.size() == val.size(), false);
	
	for(hmw::TCON<t, t>::iterator i = l.begin(); i != l.end(); ++i){
		t x = *i;
      bool find = false;
      for(hmw::list<t>::iterator itr = val.begin(); itr != val.end(); itr++)
         if(x == *itr){
            find = true;
            val.erase(itr);
            break;
         }
		_test(find, line, false);
	}
	std::cout << "test passed\n";
}

template<class t>
void outcon(hmw::TCON<t, t> l){
	std::cout << "OUT LIST\n"; 
	for(hmw::TCON<t, t>::iterator i = l.begin(); i != l.end(); i++)
		std::cout << *i << " ";
	std::cout << "\n";
}

unsigned char* STRINGstrRep(string str){
   char *s = new char[str.size() + 1];
   strcpy(s, str.c_str());
   return (unsigned char*)(s);
}

size_t STRINGsizeKey(string s){
   return s.size();
}
int main(){
   hmw::list<int> val;
   hmw::list<int>::iterator iterVal;

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
      std::vector<int> val;
      for(int j = 0; j < 1000; j++){
         con.insert(j, j);
         val.push_back(j);
      }

      i = con.begin();
      bool fail = false;
      for(int j = 0; j < 1000; j++, i++){
         fail = true;
         for(int k = 0; k < val.size(); k++)
            if(val[k] == *i)
               fail = false;
         if(fail)
            break;
      }
         
      test(!fail);

      int j = 0;
      for(i = con.begin(); i != con.end(); i++, j++);
      test(j == 1000);
   END

   TEST
      hmw::TCON<int, int> con;
      con[0] = 0;
      con[1] = 1;
      test(con[1] == 1);

      con[1] = 2;
      test(con[1] == 2);

      con[1] = 1;
      con[3] = 3;
      con[4] = 4;

      testcon<int>(L, con, 5, 0, 1, 2, 3, 4);

      hmw::TCON<string, int> con2(&STRINGstrRep, &STRINGsizeKey);
      con2["111"] = 1;
      con2["222"] = 2;

      test(con2["111"] == 1);
      test(con2["222"] == 2);
   END

	TEST
      hmw::TCON<int, int> con;
      insert<hmw::list<int>, int>(val, 7, 7, 8, 3, 5, 4, 2, 9);
		appendcon<int>(con,7, 7, 8, 3, 5, 4, 2, 9);
      testcon<int>(L, con, 7, 7, 8, 3, 5, 4, 2, 9);

      deleteByVal<hmw::list<int>, int>(val, *con.begin());
		con.erase(con.begin());
		testcon<int>(L, con, val);

      deleteByVal<hmw::list<int>, int>(val, *(--con.end()));
		con.erase(--con.end());
		testcon<int>(L, con, val);

      deleteByVal<hmw::list<int>, int>(val, *(--con.end()));
		con.erase(--con.end());
		testcon<int>(L, con, val);

		con.erase(con.begin());
		test(con.size() == 0);
	END

	TEST
      hmw::TCON<int, int> con;
		appendcon<int>(con, 6, 0, 1 , 2, 3, 4, 5);

		hmw::TCON<int, int>::iterator iter = con.begin();

		test(*iter == *con.begin());

		for(int i = 0; i < 5; i++)
			iter++;

		test(*iter == *(--con.end()));

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
		test(*iter == *(--con.end()));

      iter++;
		test(iter == con.end());

		for(int i = 0; i < 4; i++)
			iter--;

		test(*iter == *(con.begin()));
	END

	TEST
      hmw::TCON<int, int> con;
		appendcon<int>(con, 4, 0, 1, 2, 3);
		hmw::TCON<int, int>::iterator iter = con.begin();

      copyContainer<hmw::list<int>, hmw::TCON<int, int>>(val, con);
      iterVal = val.begin();

		test(*iter == *iterVal);
		iter.shift(1);
      iterVal++;
		test(*iter == *iterVal);

      iter.shift(3);
      iterVal++;iterVal++;iterVal++;
		test(iter == con.end());

      iter.shift(-1);
      iterVal--;
      test(--con.end() == iter);
      iter--;iterVal--;
      test(*iter == *iterVal);
		iter.shift(-2);
      iterVal--;iterVal--;
		test(*iter == *iterVal);
      
      iter.shift(1);
      iterVal++;
      iter.shift(2);
      iterVal++;iterVal++;
      iter.shift(-3);
      iterVal--;iterVal--;iterVal--;

      test(*iter == *iterVal);
	END

	TEST
      hmw::TCON<int, int> con;
		appendcon<int>(con, 7, 7, 4, 2, 0, 1, 3, 9);
      insert<hmw::list<int>, int>(val, 7, 7, 4, 2, 0, 1, 3, 9);

      hmw::TCON<int, int>::iterator iter = con.begin();
      iter.shift(2);

      deleteByVal<hmw::list<int>>(val, *iter);
      con.erase(iter);
		testcon<int>(L, con, val);

		iter = con.begin();
      deleteByVal<hmw::list<int>>(val, *iter);
		con.erase(iter);
		testcon<int>(L, con,val);

		iter = --con.end();
      deleteByVal<hmw::list<int>>(val, *iter);
		con.erase(iter);
      deleteByVal<hmw::list<int>>(val, *(con.begin()));
      con.erase(con.begin());
		testcon<int>(L, con, val);

		iter = con.begin();
		iter.shift(1);
      
      deleteByVal<hmw::list<int>>(val, *iter);
      con.erase(iter);
		testcon<int>(L, con, val);

      iter = con.end();
      iter--;
		
      deleteByVal<hmw::list<int>>(val, *iter);
		con.erase(iter);
      deleteByVal<hmw::list<int>>(val, *(con.begin()));
      con.erase(con.begin());
		test(con.size() == 0);
      test(con.empty());
      
		con.insert(6, 6);
      val.push_back(6);
      deleteByVal<hmw::list<int>, int>(val, *(con.begin()));
      con.erase(con.begin());
		test(con.size() == 0);
	END

   TEST
      hmw::TCON<int, string> con;
      string s = "111111";
      con.insert(0, s);
      con.insert(1, "222222");
      s = "33333";
      test("111111" == *con.find(0));
   END

   TEST
      const int count = 1;//20000;
      hmw::TCON<int,int> con;
      std::map<int, int> con2;
      clock_t t;
      
      t = clock();
      for(int i = 0; i < count; i++)
         con[i] = i;
      std::cout << "run build MY MAP = " << clock() - t << endl;

      t = clock();
      for(int i = 0; i < count; i++)
         con2[i] = i;
      std::cout << "run build STL MAP = " << clock() - t << endl;
      
      std::cout << "\n";

      t = clock();
      for(hmw::TCON<int, int>::iterator i = con.begin(); i != con.end(); i++);
      std::cout<<"run time MY MAP iterator = " << clock() - t << endl;

      t = clock();
      for(map<int, int>::iterator i = con2.begin(); i != con2.end(); i++);
      std::cout<<"run time STL MAP iterator = " << clock() - t << endl;
      
      std::cout << "\n";

      t = clock();
      for(int i = 0; i < count; i++)
         con.find(i);
      std::cout << "run time MY MAP find element = " << clock() - t << endl;

      t = clock();
      for(int i = 0; i < count; i++)
         con2.find(i);
      std::cout << "run time STL MAP find element = " << clock() - t << endl;

      std::cout << "\n";
      t = clock();
      con.clear();
      std::cout << "run time clear MY MAP =" << clock() - t << endl;
      
      t = clock();
      con2.clear();
      std::cout << "run time clear STL MAP = " << clock() - t << endl;
   END
   
	TEST
		hmw::TCON<string, hmw::TCON<int, char>> con(&STRINGstrRep, &STRINGsizeKey);
      hmw::TCON<string, hmw::TCON<int, char>>::iterator itr;
      hmw::TCON<int, char> *p;
      hmw::TCON<int, char>::iterator itr3;
		hmw::list<string> keys;
      hmw::list<string>::iterator itr2;
      const int lenStr = 100;
      const int count = 1;

		while(con.size() < count)
			if(rand() % 3){
				string key = RandStr(lenStr);
            
            keys.push_back(key);

            p = new hmw::TCON<int, char>;


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
