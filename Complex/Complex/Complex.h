
#include<iostream>
#include<math.h>

class Complex{
	private:
		double real, image;
	public:
		Complex(){
			real = 0;
			image = 0;
		};

		Complex(double r){
			real = r;
			image = 0;
		};

		Complex(double r, double i){
			real = r;
			image = i;
		};

		Complex(const Complex &v){
			real = v.real;
			image = v.image;
		};

		~Complex(){
		};
		
		inline const double& get_image(){
			return this->image;
		}

		inline const double& get_real(){
			return this->real;
		}

		Complex operator = (const Complex &v);
		Complex operator += (const Complex &v);
		Complex operator -= (const Complex &v);
		Complex operator *= (const Complex &v);
		Complex operator /= (const Complex &v);

		const bool operator == (const Complex &v) const;
		const bool operator != (const Complex &v) const;
		
		const Complex operator + (const Complex &v) const;
		const Complex operator - (const Complex &v) const;
		const Complex operator * (const Complex &v) const;
		const Complex operator / (const Complex &v) const;

		friend std::ostream &operator << (std::ostream &fo, Complex &v);
		friend std::istream &operator >> (std::istream &fi, Complex &v);
};

//Complex abs(Complex v);

