#include <iostream>
#include "Complex_trigonometry.h"
//#include "Complex.h"

#define TEST(x) test(x , __LINE__)

using namespace std;
int numberTest = 0;

void test(bool x, signed line){
	numberTest++;
	cout << "\ntest " << numberTest;
	if(x)
		 cout << " passed";
	else
		cout << " fail in line " << line;
}
int main(){
	Complex x(1, 2);
	Complex y(2, 3);
	Complex z(3, 5);

	cout << x << "\n";
	cout << y << "\n";
	cout << z << "\n";
	TEST(z == x + y);

	TEST(!(z != x + y));
	
	z = x + y;
	z = z - y;
	TEST(z == x);
		
	z = 0;
	z += x;
	z -= x;
	TEST(z == 0);

	z += 0;
	TEST(z == 0);

	z += 4;
	TEST(z == Complex(4, 0));

	Complex r(1,3);
	Complex res(5, 15);
	x = 5;
	z = x * r;
	TEST(z == res);
	
	x = z;
	TEST(x == z);

	z *= 16.0;
	TEST(z == Complex(80, 240));

	z = z / 16.0;
	TEST(z == x);

	z /= 5;
	res = Complex(1, 3);
	TEST(res == z);

	z = Complex(1.25, 5.65);
	z += 0.75;
	TEST(z == Complex(2.0, 5.65));
	
	z -= Complex(1.25, 4.90);
	TEST(z == Complex(0.75, 0.75));

	x = Complex(0.25, 0.25);
	res = z / x;
	TEST(res == 3);

	x = Complex(1, 2);
	y = Complex(2, 3);
	z = x * y;

	
	cout << "\n";
	cin >> x;
	cout << "You enter complex namber:" << x;
}