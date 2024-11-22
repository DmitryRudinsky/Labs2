#ifndef BINARY_H
#define BINARY_H

#include <iostream>
#include <bitset>
#include <utility>
#include <climits>

class binary_int {
private:
    int value;

public:
    binary_int(int v = 0);

    // Унарный минус
    binary_int operator-() const;

    // Префиксный и постфиксный инкременты
    binary_int& operator++();
    binary_int operator++(int);

    // Префиксный и постфиксный декременты
    binary_int& operator--();
    binary_int operator--(int);

    // Арифметические операторы
    binary_int& operator+=(const binary_int& other);
    binary_int operator+(const binary_int& other) const;
    binary_int& operator-=(const binary_int& other);
    binary_int operator-(const binary_int& other) const;
    binary_int& operator*=(const binary_int& other);
    binary_int operator*(const binary_int& other) const;

    // Побитовые операторы сдвига
    binary_int& operator<<=(int shift);
    binary_int operator<<(int shift) const;
    binary_int& operator>>=(int shift);
    binary_int operator>>(int shift) const;

    // Вставка в поток
    friend std::ostream& operator<<(std::ostream& os, const binary_int& bi);

    // Метод для разделения на старшую и младшую половины
    std::pair<binary_int, binary_int> split() const;
};

#endif // BINARY_H
