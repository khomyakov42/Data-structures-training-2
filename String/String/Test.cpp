#include "String.h"
#define test(x) _test(x, __LINE__) 
   
unsigned long int number_test = 0;

void _test(bool x, unsigned long int line){
	number_test++;
	if(x)
		std::cout << "line " << line << " test " << number_test << " passed\n";
	else
		std::cout << "line " << line << " test fail " << number_test << "\n";
}


int main(){
	{
	string s;
	test(s == "");
	test(s.empty());
	test(s.size() == 0);

	s = "123";
	test(s == "123");

	s.clear();
	test(s.size() == 0);
	test(s.empty());
	test(s == "");
	
	s = "000";	
	test(s == "000");
	test(s.size() == 3);
	test(s.empty() == false);

	s = "";
	test(s == "");
	test(s.size() == 0);
	test(s.empty());

	s = s + "111";
	test(s == "111");
	test(s.size() == 3);
	test(s.empty() == false);

	s = s + "222" + "333";
	test(s == "111222333");
	test(s.size() == 9);
	
	s.clear();
	test(s.size() == 0);
	test(s.empty());
	test(s == "");

	string s2 = "qwerty";
	test(s2 == "qwerty");
	test(s2.size() == 6);
	test(s2.empty() == false);

	s = s + s2;
	test(s == "qwerty");
	test(s2 == "qwerty");
	test(s.size() == 6);
	test(s.empty() == false);
	
	s = s2 + s2 + s;
	test(s == "qwertyqwertyqwerty");
	test(s.size() == 18);
	test(s2 == "qwerty");
	test(s2.size() == 6);

	s2.clear();
	test(s2 == "");
	test(s2.size() == 0);
	test(s2.empty());
	test(s == "qwertyqwertyqwerty");
	test(s.size() == 18);

	s.clear();
	test(s == "");
	
	s = s + s2;
	test(s == "");
	test(s.size() == 0);
	}
	
	{
	string s = "123";
	string s2(s);
	string s3(s);
	string s4(s2);

	test(s == "123");
	test(s2 == "123");
	test(s3 == "123");
	test(s4 == "123");

	s[1] = '0';
	
	test(s == "103");
	test(s2 == "123");
	test(s3 == "123");
	test(s4 == "123");

	s4[1] = '3';
	test(s == "103");
	test(s2 == "123");
	test(s3 == "123");
	test(s4 == "133");

	s2[1] = '1';
	test(s == "103");
	test(s2 == "113");
	test(s3 == "123");
	test(s4 == "133");

	string s5(s + s2 + s3 + s4);

	test(s5 == "103113123133");
	test(s5.size() == 12);
	for(int i = 0; i < 12; i++)
		s5[i] = 'i';

	test(s5 == "iiiiiiiiiiii");
	test(s == "103");
	test(s2 == "113");
	test(s3 == "123");
	test(s4 == "133");///тлько ты
	
	for(int i = s.size() - 1; i >= 0; i--)
			s[i] = 'U';
	test(s5 == "iiiiiiiiiiii");
	test(s == "UUU");
	test(s2 == "113");
	test(s3 == "123");
	test(s4 == "133");

	}


	test(string("asa") == string("asa"));
	test("asa" == string("asa"));
	test(string("asa") == "asa");

	test(string("a") != string("b"));
	test("a" != string("b"));
	test(string("a") != "b");

	test(string("a") < string("b"));
	test("a" < string("b"));
	test(string("a") < "b");

	test(string("d") > string("c"));
	test("d" > string("c"));
	test(string("d") > "c");

	test(string("aba") <= string("aca"));
	test("aba" <= string("aca"));
	test(string("aba") <= "aca");

	test(string("aca") >= string("aba"));
	test("aca" >= string("aba"));
	test(string("aca") >= "aba");  

	try{
		string()[0] == '0';
	}catch(string::out_of_range){
		test(true);
	}
	getchar();
}