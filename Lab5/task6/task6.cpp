#include <iostream>
#include "util_task6.hpp"

int main() {
    // Создание векторов
    Vector v1(3, 5.0);
    Vector v2 = {1.0, 2.0, 3.0};
    Vector v3(2, 0.0);

    // Вывод размера и вместимости
    std::cout << "v1 size: " << v1.size() << ", capacity: " << v1.capacity() << std::endl;
    std::cout << "v2 size: " << v2.size() << ", capacity: " << v2.capacity() << std::endl;
    std::cout << "v3 size: " << v3.size() << ", capacity: " << v3.capacity() << std::endl;

    // Доступ к элементам
    std::cout << "v1[0]: " << v1.at(0) << std::endl;
    std::cout << "v2[2]: " << v2.at(2) << std::endl;
    std::cout << "v3.front(): " << v3.front() << std::endl;
    std::cout << "v3.back(): " << v3.back() << std::endl;

    // Изменение размера
    v3.resize(5, 10.0);
    std::cout << "v3 after resize: ";
    for (size_t i = 0; i < v3.size(); ++i) {
        std::cout << v3.at(i) << " ";
    }
    std::cout << std::endl;

    // Добавление и удаление элементов
    v2.push_back(4.0);
    v2.pop_back();
    v2.insert(1, 1.5);
    v2.erase(2);

    std::cout << "v2 after modifications: ";
    for (size_t i = 0; i < v2.size(); ++i) {
        std::cout << v2.at(i) << " ";
    }
    std::cout << std::endl;

    // Сравнение векторов
    Vector v4 = {1.0, 1.5, 3.0};
    std::cout << "v2 == v4: " << (v2 == v4) << std::endl;
    std::cout << "v2 < v4: " << (v2 < v4) << std::endl;

    // Итераторы
    std::cout << "v4 using iterators: ";
    for (auto it = v4.begin(); it != v4.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Очистка и уменьшение вместимости
    v4.clear();
    v4.shrink_to_fit();
    std::cout << "v4 after clear: size = " << v4.size() << ", capacity = " << v4.capacity() << std::endl;

    return 0;
}