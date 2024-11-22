#include "binary.h"

int main() {
    binary_int a(10), b(3);

    std::cout << "Initial values: \n";
    std::cout << "a: " << a << "\nb: " << b << "\n\n";

    std::cout << "Addition: a + b = " << (a + b) << "\n";
    std::cout << "Subtraction: a - b = " << (a - b) << "\n";

    ++a;
    std::cout << "After prefix increment: a = " << a << "\n";
    a--;
    std::cout << "After postfix decrement: a = " << a << "\n";

    a *= b;
    std::cout << "After multiplication: a *= b -> a = " << a << "\n";

    auto [upper, lower] = a.split();
    std::cout << "Split result: \n";
    std::cout << "Upper: " << upper << "\nLower: " << lower << "\n";

    return 0;
}
