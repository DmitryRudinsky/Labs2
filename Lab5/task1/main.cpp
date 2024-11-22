#include "binary.h"

int main() {
    binary_int a(10), b(3);

    std::cout << "Начальные значения: \n";
    std::cout << "a: " << a << "\nb: " << b << "\n\n";

    std::cout << "Сложение: a + b = " << (a + b) << "\n";
    std::cout << "Вычитание: a - b = " << (a - b) << "\n";

    ++a;
    std::cout << "После префиксного инкремента: a = " << a << "\n";
    a--;
    std::cout << "После постфиксного декремента: a = " << a << "\n";

    a *= b;
    std::cout << "После умножения: a *= b -> a = " << a << "\n";

    auto [upper, lower] = a.split();
    std::cout << "Результат разбиения: \n";
    std::cout << "Верхняя часть: " << upper << "\nНижняя часть: " << lower << "\n";

    return 0;
}
