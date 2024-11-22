#include <cmath>

#include "complexNum.h"

complexNum::complexNum() : realPart(0), imaginaryPart(0) {}

complexNum::complexNum(double a, double b) : realPart(a), imaginaryPart(b) {}

complexNum complexNum::operator+(const complexNum& other) const {
	complexNum res;
	res.realPart = this->realPart + other.realPart;
	res.imaginaryPart = this->imaginaryPart + other.imaginaryPart;
	return res;
}

complexNum complexNum::operator-(const complexNum& other) const {
	complexNum res;
	res.realPart = this->realPart - other.realPart;
	res.imaginaryPart = this->imaginaryPart - other.imaginaryPart;
	return res;
}

complexNum complexNum::operator*(const complexNum& other) const {
	complexNum res;
	res.realPart = this->realPart * other.realPart - this->imaginaryPart * other.imaginaryPart;
	res.imaginaryPart = this->realPart * other.imaginaryPart + this->imaginaryPart * other.realPart;
	return res;
}

complexNum complexNum::operator/(const complexNum& other) const {
	complexNum res;
	double denominator = other.realPart * other.realPart + other.imaginaryPart * other.imaginaryPart;
	res.realPart = (this->realPart * other.realPart + this->imaginaryPart * other.imaginaryPart) / denominator;
	res.imaginaryPart = (this->imaginaryPart * other.realPart - this->realPart * other.imaginaryPart) / denominator;
	return res;
}

double complexNum::modComplex() const { return sqrt(realPart * realPart + imaginaryPart * imaginaryPart); }

double complexNum::argComplex() const { return atan2(imaginaryPart, realPart); }

std::ostream& operator<<(std::ostream& out, const complexNum& num) {
	if (num.imaginaryPart >= 0) {
		out << num.realPart << "+" << num.imaginaryPart << "i";
	} else {
		out << num.realPart << num.imaginaryPart << "i";
	}
	return out;
}