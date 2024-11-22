#include "binary.h"

binary_int::binary_int(int v) : value(v) {}

binary_int binary_int::operator-() const {
    return binary_int(~value + 1);
}

binary_int& binary_int::operator++() {
    int carry = 1;
    int temp;
    for (int i = 0; i < sizeof(int) * CHAR_BIT && carry; ++i) {
        temp = value ^ (1 << i);
        carry = (value & (1 << i)) && carry;
        value = temp;
    }
    return *this;
}

binary_int binary_int::operator++(int) {
    binary_int temp = *this;
    ++(*this);
    return temp;
}

binary_int& binary_int::operator--() {
    int borrow = 1;
    int temp;
    for (int i = 0; i < sizeof(int) * CHAR_BIT && borrow; ++i) {
        temp = value ^ (1 << i);
        borrow = !(value & (1 << i)) && borrow;
        value = temp;
    }
    return *this;
}

binary_int binary_int::operator--(int) {
    binary_int temp = *this;
    --(*this);
    return temp;
}

binary_int& binary_int::operator+=(const binary_int& other) {
    int carry = 0;
    int a = value;
    int b = other.value;

    for (int i = 0; i < sizeof(int) * CHAR_BIT; ++i) {
        int bitA = (a >> i) & 1;
        int bitB = (b >> i) & 1;
        int sum = bitA ^ bitB ^ carry;
        carry = (bitA & bitB) | (bitA & carry) | (bitB & carry);
        if (sum) {
            value |= (1 << i);
        } else {
            value &= ~(1 << i);
        }
    }
    return *this;
}

binary_int binary_int::operator+(const binary_int& other) const {
    binary_int temp = *this;
    temp += other;
    return temp;
}

binary_int& binary_int::operator-=(const binary_int& other) {
    *this += -other;
    return *this;
}

binary_int binary_int::operator-(const binary_int& other) const {
    binary_int temp = *this;
    temp -= other;
    return temp;
}

binary_int& binary_int::operator*=(const binary_int& other) {
    binary_int result = 0;
    binary_int temp = *this;
    for (int i = 0; i < sizeof(int) * CHAR_BIT; ++i) {
        if ((other.value >> i) & 1) {
            result += temp;
        }
        temp <<= 1;
    }
    *this = result;
    return *this;
}

binary_int binary_int::operator*(const binary_int& other) const {
    binary_int temp = *this;
    temp *= other;
    return temp;
}

binary_int& binary_int::operator<<=(int shift) {
    value <<= shift;
    return *this;
}

binary_int binary_int::operator<<(int shift) const {
    return binary_int(value << shift);
}

binary_int& binary_int::operator>>=(int shift) {
    value >>= shift;
    return *this;
}

binary_int binary_int::operator>>(int shift) const {
    return binary_int(value >> shift);
}

std::ostream& operator<<(std::ostream& os, const binary_int& bi) {
    os << std::bitset<sizeof(int) * CHAR_BIT>(bi.value);
    return os;
}

std::pair<binary_int, binary_int> binary_int::split() const {
    int half_bits = sizeof(int) * CHAR_BIT / 2;
    int lower_mask = (1 << half_bits) - 1;

    int lower = value & lower_mask;
    int upper = (value >> half_bits) & lower_mask;

    return {binary_int(upper << half_bits), binary_int(lower)};
}
