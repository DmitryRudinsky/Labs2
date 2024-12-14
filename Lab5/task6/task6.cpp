#include "util_task6.hpp"
#include <algorithm>


int main() {
    Vector v = {1.0, 2.0, 3.0, 4.0, 52.0};
    v.push_back(5.0);
    
    std::sort(v.begin(), v.end());

    std::cout << "Size: " << v.size() << std::endl;
    std::cout << "First element: " << v.front() << std::endl;
    std::cout << "Last element: " << v.back() << std::endl;

    v.insert(2, 6.0);
    std::cout << "Element at index 2: " << v.at(2) << std::endl;

    v.erase(1);
    std::cout << "Element at index 1 after erase: " << v.at(1) << std::endl;

    std::cout << "Vector elements: ";
    for (auto& elem : v) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    Vector v2 = {2.0, 3.0, 4.0};
    std::cout << "vec2 == vec4: " << std::boolalpha << (v == v2) << std::endl;
    auto cmp_result = v <=> v2;
    std::cout << "vec2 <=> vec4: " << (cmp_result == std::strong_ordering::equal ? "equal" : cmp_result == std::strong_ordering::greater ? "greater" : "less" ) << std::endl;
    
    return 0;
}