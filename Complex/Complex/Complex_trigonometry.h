#include<iostream>
#include<math.h>

class Complex{
	private:
		double r, fi;
		bool undefine;
	public:
		Complex(){
			undefine = false;
		};

		Complex(double real){
			fi = 0;
			r = real;			
			undefine = false;
		};

		Complex(double real, double image){
			if(image == 0.0 || real == 0.0){
				undefine = true;
				fi = 0;
			}
			else{
				undefine = false;
				fi = atan2(image, real);
			}
			r = sqrt(real*real + image*image);
		};

		Complex(const Complex &v){
			fi = v.fi;
			r = v.r;
			undefine = v.undefine;
		};

		~Complex(){
		};
		
		inline const double& get_r(){
			return this->r;
		}

		inline const double& get_arg(){
			return this->fi;
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