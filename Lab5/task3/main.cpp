#include <iostream>
#include <bitset>
#include <cstring>

class LogicalValuesArray {
private:
    unsigned int value;

public:
    unsigned int getValue() const {
        return value;
    }

    void setValue(unsigned int newValue) {
        value = newValue;
    }

    LogicalValuesArray(unsigned int initialValue = 0) : value(initialValue) {}

    LogicalValuesArray invert() const {
        return LogicalValuesArray(~value);
    }

    LogicalValuesArray conjunction(const LogicalValuesArray& other) const {
        return LogicalValuesArray(value & other.value);
    }

    LogicalValuesArray disjunction(const LogicalValuesArray& other) const {
        return LogicalValuesArray(value | other.value);
    }

    LogicalValuesArray implication(const LogicalValuesArray& other) const {
        return LogicalValuesArray(~value | other.value);
    }

    LogicalValuesArray coimplication(const LogicalValuesArray& other) const {
        return LogicalValuesArray(~(value ^ other.value));
    }

    LogicalValuesArray xorOperation(const LogicalValuesArray& other) const {
        return LogicalValuesArray(value ^ other.value);
    }

    LogicalValuesArray equivalence(const LogicalValuesArray& other) const {
        return coimplication(other);
    }

    LogicalValuesArray pierceArrow(const LogicalValuesArray& other) const {
        return LogicalValuesArray(~(value | other.value));
    }

    LogicalValuesArray shefferStroke(const LogicalValuesArray& other) const {
        return LogicalValuesArray(~(value & other.value));
    }

    static bool equals(const LogicalValuesArray& a, const LogicalValuesArray& b) {
        return a.value == b.value;
    }

    bool getBit(size_t position) const {
        return (value >> position) & 1U;
    }

    void toBinaryString(char* buffer, size_t bufferSize) const {
        if (bufferSize < 33) {
            throw std::invalid_argument("Buffer size is too small.");
        }
        std::bitset<32> binary(value);
        std::strncpy(buffer, binary.to_string().c_str(), bufferSize - 1);
        buffer[bufferSize - 1] = '\0';
    }
};

int main() {
    LogicalValuesArray a(1);
    LogicalValuesArray b(0);

    std::cout << "Value of a: " << a.getValue() << std::endl;
    std::cout << "Value of b: " << b.getValue() << std::endl;

    std::cout << "Inversion of a: " << a.invert().getValue() << std::endl;
    std::cout << "Conjunction of a and b: " << a.conjunction(b).getValue() << std::endl;
    std::cout << "Disjunction of a and b: " << a.disjunction(b).getValue() << std::endl;
    std::cout << "Implication of a to b: " << a.implication(b).getValue() << std::endl;
    std::cout << "Coimplication of a and b: " << a.coimplication(b).getValue() << std::endl;
    std::cout << "XOR of a and b: " << a.xorOperation(b).getValue() << std::endl;
    std::cout << "Equivalence of a and b: " << a.equivalence(b).getValue() << std::endl;
    std::cout << "Pierce Arrow of a and b: " << a.pierceArrow(b).getValue() << std::endl;
    std::cout << "Sheffer Stroke of a and b: " << a.shefferStroke(b).getValue() << std::endl;

    std::cout << "Are a and b equal? " << (LogicalValuesArray::equals(a, b) ? "Yes" : "No") << std::endl;

    for (size_t i = 0; i < 32; ++i) {
        std::cout << "Bit at position " << i << " in a: " << a.getBit(i) << std::endl;
    }

    char buffer[33];
    a.toBinaryString(buffer, sizeof(buffer));
    std::cout << "Binary representation of a: " << buffer << std::endl;

    b.toBinaryString(buffer, sizeof(buffer));
    std::cout << "Binary representation of b: " << buffer << std::endl;

    return 0;
}
