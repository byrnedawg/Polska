#include <iostream>
#include <cmath>


using namespace std;

class Complex {
private:
	double real, image;
public:
	Complex(double real = 0.0, double image = 0.0) : real(real), image(image) {
		//this.num = num;
	}
//	friend Complex add(Complex a, Complex b);
	
    Complex add(Complex b) const {
		//		this->real, this->image b.real b.image
		return Complex(this->real + b.real, this->image + b.image);
	}
	
	 Complex sub(Complex b) const {
		//		this->real, this->image b.real b.image
		return Complex(this->real - b.real, this->image - b.image);
	}
	Complex mult(Complex b) const {
	    return Complex(this->real * b.real, this->image * b.image);
	}
	
	void print() const {
    	if(image >= 0)
    	{
    		cout << real << "+" << abs(image) <<"i\n";
    	}
    	else
    	{
    	    cout << real << image <<"i\n";
    	}
	}
	
};

//Complex add(Complex a, Complex b) {
	// a.num  a.den  b.num  b.den
	//Complex ans(a.real + b.real, + a.image + b.image);
//	return ans;
//}

int main() {
	const Complex c1; // (real=0, imag =0)
	const Complex c2(1.5);// real=1.5, imag = 0.0
	Complex c3(1.5,-2.25); // real = 1.5, imag=2.25

    c1.print(); // 0+0i
    c2.print(); // 1.5
	c3.print(); // 1.5+2.25i
	Complex c4 = c1.add(c2); // (real=1.5, imag=0.0)
    Complex c5 = c2.sub(c4); // nice but not for the homework
    Complex c6 = c2.mult(c3);
    cout << "add c1 to c2 is = ";
	c4.print();
	cout << "sub c4 from c2 is = ";
	c5.print();
	cout << "mult c2 and c3 is = ";
	c6.print();
}
