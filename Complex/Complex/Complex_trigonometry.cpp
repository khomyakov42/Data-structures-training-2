#include "Complex_trigonometry.h"
#define Pi asin(1.0)*2
#define ACCURACY 0.00001

Complex Complex::operator = (const Complex &v){
	r = v.r;
	fi = v.fi;
	return *this;
}
Complex Complex::operator += (const Complex &v){
	return *this = *this + v;	
}
Complex Complex::operator -= (const Complex &v){
	return *this = *this - v;
}
Complex Complex::operator *= (const Complex &v){
	return *this = *this * v;
}
Complex Complex::operator /= (const Complex &v){
	return *this = *this / v;
}

const bool Complex::operator == (const Complex &v) const{
	if(undefine || v.undefine)
		return true;

	for(int i = 1; i <= 9; i++){
		double fi1, fi2;
		if(i <= 3) fi1 = fi;
		else if(i <= 6) fi1 = fi + Pi;
		else fi1 = fi - Pi;

		if(i % 3 == 0) fi2 = v.fi - Pi;
		else if(i % 2 == 0) fi2 = v.fi + Pi;
		else fi2 = v.fi;
				
		double real1 = r * cos(fi1);
		double real2 = v.r * cos(fi2);
		double image1 = r * sin(fi1);
		double image2 = v.r * sin(fi2);
		
		if(abs(real1 - real2) < ACCURACY && abs(image1 - image2) < ACCURACY)
			return true;
	}

	return false;
}
const bool Complex::operator != (const Complex &v) const{
	return(!(v == *this));
}

const Complex Complex::operator + (const Complex &v) const{
	return Complex(r * cos(fi) + v.r * cos(v.fi), r * sin(fi) + v.r * sin(v.fi)); 
}
const Complex Complex::operator - (const Complex &v) const{
	return Complex(r * cos(fi) - v.r * cos(v.fi), r * sin(fi) - v.r * sin(v.fi));
}
const Complex Complex::operator * (const Complex &v) const{
	Complex res;
	res.fi = fi + v.fi;
	res.r = r * v.r;
	return res;		 
}
const Complex Complex::operator / (const Complex &v) const{
	Complex res;
	res.fi = fi - v.fi;
	res.r = r / v.r;
	return res;
}

std::ostream &operator << (std::ostream &fo, Complex &v){
	fo << v.r << "*(cos(" << v.fi << ")" << (sin(v.fi) < 0? "": "+") << "i*sin(" << v.fi << "))"; 
	return fo;
}
std::istream &operator >> (std::istream &fi, Complex &v){
	double real, image;
	std::cout << "Enter real part.\n";
	fi >> real;
	std::cout << "\n" << "Enter image part.\n";
	fi >> image;
	std::cout << "\n";

	v.fi = atan(image / real);
	v.r = sqrt(image * image + real * real);
	return fi;
}