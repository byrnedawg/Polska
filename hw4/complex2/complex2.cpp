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
	
	friend Complex add(Complex a, Complex b);
	
	Complex add(Complex b) const {
		//		this->real, this->image b.real b.image
		return Complex(this->real + b.real, this->image + b.image);
	}
	
    friend Complex operator +(Complex a, Complex b) {
	    return Complex(a.real + b.real, a.image + b.image);
	}

	friend Complex operator -(Complex a) {
		return Complex(-a.real, -a.image);
	}
	
	friend Complex operator -(Complex a, Complex b) {
		return Complex(a.real - b.real, a.image - b.image);
	}
	
	friend Complex operator *(Complex a, Complex b) {
		return Complex(a.real * b.real, a.image * b.image);
	}

	// x = 1 + 2 + 3 + 4;
	//cout << "hello" << f1 << "hello";
	friend ostream& operator <<(ostream& s, Complex c) {
  		
  		if(c.image >= 0)
  			return s << c.real << "+" << abs(c.image) <<"i";
  		return s << c.real << c.image <<"i";
	}
	
};



int main() {
	char answer = 'n';
	double x, y;
	do{
		cout << "Enter in the real part of a complex number \n";
		cin >> x;
		cout << "Enter in the imaginary part of a complex number\n";
		cin >> y;
		Complex c0(x, y);
		cout << c0 << endl;
		cout << "Want to enter in another complex number Y or N ?\n";
		cin >> answer;

	}while(answer != 'n');
	
	const Complex c1; // (real=0, imag =0)
	const Complex c2(1.5);// real=1.5, imag = 0.0
	Complex c3(1.5,2.25); // real = 1.5, imag=2.25

    c1.print(); // 0+0i
    c2.print(); // 1.5
	c3.print(); // 1.5+2.25i
	Complex c4 = c1.add(c2); // (real=1.5, imag=0.0)
    Complex c5 = c2 + c3; // nice but not for the homework
	c4.print();
	c5.print();
	cout << c5 << endl;
	cout << c4 << endl;
	Complex c6 = -c3;
	Complex c7 = c2 - c3;
	Complex c8 = c3 * c7;
	cout << '-' << c3 << " = " << c6 << endl;
	cout << "The real way: " << c2 << '-' << c3 << " = " << c7 << endl;
	cout << "Mult is = " << c8;
}
