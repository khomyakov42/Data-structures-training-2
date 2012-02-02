#include "Complex.h"

Complex Complex::operator = (const Complex &v){
	real = v.real;
	image = v.image;
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
	return(real == v.real && image == v.image);
}

const bool Complex::operator != (const Complex &v) const{
	return(real != v.real || image != v.image);
}

const Complex Complex::operator + (const Complex &v) const{
	Complex res;
	res.real = real + v.real;
	res.image = image + v.image;
	return res;
}

const Complex Complex::operator - (const Complex &v) const{
	Complex res;
	res.real = real - v.real;
	res.image = image - v.image;
	return res;
}

const Complex Complex::operator * (const Complex &v) const{
	Complex res;
	res.real = (real * v.real) - (image * v.image);
	res.image = (real * v.image) + (image * v.real);
	return res;
}

const Complex Complex::operator / (const Complex &v) const{
	Complex res;
		res.real = ((v.real * real) + (image * v.image)) / ((v.real * v.real) + (v.image * v.image));
		res.image = ((v.real * image) - (real * v.image)) / ((v.real * v.real) + (v.image * v.image));
	return res;
}



std::ostream &operator << (std::ostream &fo, Complex &v){
	fo << v.real << (v.image > 0? "+": "") << v.image << "i";
	return fo;	
}

std::istream &operator >> (std::istream &fi, Complex &v){
	std::cout << "Enter real part.\n";
	fi >> v.real;
	std::cout << "\n" << "Enter image part.\n";
	fi >> v.image;
	std::cout << "\n";
	return fi;
}

Complex abs(Complex &v){
	return sqrt(v.get_image() * v.get_image() + v.get_real() * v.get_real());
}
