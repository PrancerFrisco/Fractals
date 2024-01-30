#pragma once
#include <cmath>


class Complex {
public:
	double real, imag;

	Complex(double real, double imag=0) {
		this->real = real;
		this->imag = imag;
	}




	Complex conjugate() const {
		return { real, -imag };
	}
	double prod_conjugates() const {
		return this->real * this->real + this->imag * this->imag;
	}

	Complex c_floor(const Complex& num) const {
		return { floor(num.real), floor(num.imag) };
	}

	Complex operator+(const Complex& other) const {
		return { real + other.real, imag + other.imag };
	}
	Complex& operator+=(const Complex& other) {
		*this = { real + other.real, imag + other.imag };
		return *this;
	}
	Complex operator-(const Complex& other) const {
		return { real - other.real, imag - other.imag };
	}
	Complex& operator-=(const Complex& other) {
		*this = { real - other.real, imag - other.imag };
		return *this;
	}
	Complex operator*(const Complex& other) const {
		if (other.imag == 0) return { real * other.real, imag * other.real };
		else if (imag == 0) return { real * other.real, real * other.imag };
		return { real * other.real - imag * other.imag, imag * other.real + real * other.imag };
	}
	Complex& operator*=(const Complex& other) {
		if (other.imag == 0) *this = { real * other.real, imag * other.real };
		else if (imag == 0) *this = { real * other.real, real * other.imag };
		else *this = { real * other.real - imag * other.imag, imag * other.real + real * other.imag };
		return *this;
	}
	Complex operator/(const Complex& other) const {
		Complex num = *this * other.conjugate();
		double D = other.prod_conjugates();
		return { num.real / D, num.imag / D };
	}
	Complex& operator/=(const Complex& other) {
		*this *= other.conjugate();
		double D = other.prod_conjugates();
		*this = { real / D, imag / D };
		return *this;
	}
};






Complex c_squared(const Complex& num) {
	double a = num.real;
	double b = num.imag;
	return { a * a - b * b, 2 * a * b };
}
Complex c_cubed(const Complex& num) {
	double a = num.real;
	double b = num.imag;
	return { a * (a * a - 3 * b * b), b * (3 * a * a - b * b) }; 
}




Complex c_log(const Complex& num) {
	double arg;
	if (num.real > 0) {
		arg = atan(num.imag / num.real);
	}
	else if (num.real < 0) {
		arg = atan(num.imag / num.real) + 3.14159265358979323846264338;
	}
	else {
		arg = 1.570796326794896619231321691;
	}
	double modulus = sqrt(num.prod_conjugates());
	return { log(modulus), arg };
}

Complex c_root_real(const Complex& num, double root) {
	double r = sqrt(num.real * num.real + num.imag * num.imag);
	double theta;
	if (num.real == 0) {
		theta = 1.570796326794896619231321691 / root;
	}
	else
		theta = atan(num.imag / num.real) / root;
	r = pow(r, 1.0 / root);
	return Complex(r * cos(theta), r * sin(theta));
}



Complex c_exp(const Complex& num) {
	return Complex(exp(num.real), 0) * Complex(cos(num.imag), sin(num.imag));
}
Complex c_exp_imag(double num) {
	return Complex(cos(num), sin(num));
}

Complex c_cos(const Complex& num) {
	return Complex(0.5) * (c_exp(Complex(-num.imag, num.real)) + c_exp(Complex(num.imag, -num.real)));
}
Complex c_acos(const Complex& num) {
	return Complex(1.570796326794896619231321691) + Complex(0, 1) * c_log(Complex(0, 1) * num + c_root_real(Complex(1) - num * num, 2));
}
Complex c_sin(const Complex& num) {
	return Complex(0, -0.5) * (c_exp(Complex(-num.imag, num.real)) - c_exp(Complex(num.imag, -num.real)));
}
Complex c_asin(const Complex& num) {
	return Complex(0, -1) * c_log(Complex(0, 1) * num + c_root_real(Complex(1) - num * num, 2));
}
Complex c_tan(const Complex& num) {
	return c_sin(num) / c_cos(num);
}
Complex c_atan(const Complex& num) {
	Complex leftPart = Complex(0, 0.5) * c_log(Complex(1) - Complex(0, 1) * num);
	Complex rightPart = Complex(0, 0.5) * c_log(Complex(1) + Complex(0, 1) * num);
	return leftPart - rightPart;
}
Complex c_cot(const Complex& num) {
	return c_cos(num) / c_sin(num);
}
Complex c_acot(const Complex& num) {
	Complex leftPart = Complex(0, 0.5) * c_log(Complex(1) - Complex(0, 1) / num);
	Complex rightPart = Complex(0, 0.5) * c_log(Complex(1) + Complex(0, 1) / num);
	return leftPart - rightPart;
}
Complex c_sec(const Complex& num) {
	return Complex(1) / c_cos(num);
}
Complex c_asec(const Complex& num) {
	return Complex(1.570796326794896619231321691) + Complex(0, 1) * c_log(c_root_real(Complex(1) - Complex(1) / (num * num), 2) + Complex(0, 1) / num);
}
Complex c_csc(const Complex& num) {
	return Complex(1) / c_sin(num);
}
Complex c_acsc(const Complex& num) {
	return Complex(0, -1) * c_log(c_root_real(Complex(1) - Complex(1) / (num * num), 2) + Complex(0, 1) / num);
}




Complex c_cosh(const Complex& num) {
	return Complex(0.5) * (c_exp(Complex(0) - num) + c_exp(num));
}
Complex c_sinh(const Complex& num) {
	return Complex(0.5) * (c_exp(num) - c_exp(Complex(0) - num));
}
Complex c_tanh(const Complex& num) {
	return c_sinh(num) / c_cosh(num);
}
Complex c_coth(const Complex& num) {
	return c_cosh(num) / c_sinh(num);
}
Complex c_sech(const Complex& num) {
	return Complex(1) / c_cosh(num);
}
Complex c_csch(const Complex& num) {
	return Complex(1) / c_sinh(num);
}











Complex c_pow(const Complex& num, const Complex& expo) {
	double r = sqrt(num.real * num.real + num.imag * num.imag);
	double theta;
	if (num.real == 0) {
		theta = 1.570796326794896619231321691;
	}
	else
		theta = atan(num.imag / num.real);
	Complex toRaise = Complex(log(r), 0) * expo + Complex(0, theta) * expo;
	return c_exp(toRaise);
}
Complex c_pow_real(const Complex& num, double expo) {
	double r = pow(sqrt(num.prod_conjugates()), expo);
	double theta;
	if (num.real == 0) {
		theta = expo * 1.570796326794896619231321691;
	}
	else
		theta = expo * atan(num.imag / num.real);
	return { r * cos(theta), r * sin(theta) };
}




Complex c_root(const Complex& num, const Complex& root) {
	Complex toRaise = c_log(num) / root;
	return c_exp(toRaise);
}
