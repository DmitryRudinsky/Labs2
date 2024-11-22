#ifndef COMPLEXNUM_H
#define COMPLEXNUM_H

#include <iostream>
#include <string>

class complexNum {
   private:
	double realPart;
	double imaginaryPart;

   public:
	complexNum();
	complexNum(double a, double b);
	complexNum operator+(const complexNum& other) const;
	complexNum operator-(const complexNum& other) const;
	complexNum operator*(const complexNum& other) const;
	complexNum operator/(const complexNum& other) const;
	double modComplex() const;
	double argComplex() const;

	friend std::ostream& operator<<(std::ostream& out, const complexNum& num);
};

#endif