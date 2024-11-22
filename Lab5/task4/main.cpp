#include <iostream>

#include "complexNum.h"

using namespace std;

int main() {
	complexNum num1(3, 4);
	complexNum num2(1, -2);

	complexNum sum = num1 + num2;
	cout << "Сумма: " << sum << endl;

	complexNum diff = num1 - num2;
	cout << "Разность: " << diff << endl;

	complexNum product = num1 * num2;
	cout << "Произведение: " << product << endl;

	complexNum quotient = num1 / num2;
	cout << "Частное: " << quotient << endl;

	double mod1 = num1.modComplex();
	cout << "Модуль первого числа: " << mod1 << endl;

	double arg1 = num1.argComplex();
	cout << "Аргумент первого числа: " << arg1 << " радиан" << endl;

	return 0;
}