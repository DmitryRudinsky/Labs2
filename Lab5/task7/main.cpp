#include "options.hpp"
#include <iostream>
#include <ctime>

Warehouse f()
{
    return {};
}

int main()
{
    Warehouse warehouse;

    auto apple = std::make_shared<PerishableProduct>(
        "Apple", 1, 0.2, 1.0, 10, std::time(nullptr) + 3 * 24 * 60 * 60);
    auto milk = std::make_shared<PerishableProduct>(
        "Milk", 2, 1.0, 1.5, 7, std::time(nullptr) + 1 * 24 * 60 * 60);
    auto tv = std::make_shared<ElectronicProduct>(
        "TV", 3, 10.0, 500.0, 365, 24, 100);
    auto laptop = std::make_shared<ElectronicProduct>(
        "Laptop", 4, 2.5, 1500.0, 730, 12, 65);
    auto cement = std::make_shared<BuildingMaterial>(
        "Cement", 5, 25.0, 100.0, 730, false);
    auto paint = std::make_shared<BuildingMaterial>(
        "Paint", 6, 15.0, 50.0, 365, true);

    Warehouse tempWarehouse = f();
    auto &r = tempWarehouse += apple;

    warehouse += apple;
    warehouse += milk;
    warehouse += tv;
    warehouse += laptop;
    warehouse += cement;
    warehouse += paint;

    std::cout << "Initial Warehouse Inventory:" << std::endl;
    std::cout << warehouse;

    warehouse -= 3;
    std::cout << "\nAfter removing TV:" << std::endl;
    std::cout << warehouse;

    std::cout << "\nSearching for Perishable Products:" << std::endl;
    auto perishableProducts = warehouse.findByCategory<PerishableProduct>();
    for (const auto &product : perishableProducts)
    {
        product->displayInfo();
    }

    std::cout << "\nSearching for Electronic Products:" << std::endl;
    auto electronicProducts = warehouse.findByCategory<ElectronicProduct>();
    for (const auto &product : electronicProducts)
    {
        product->displayInfo();
    }

    std::cout << "\nPerishable products expiring in 2 days:" << std::endl;
    auto expiringProducts = warehouse.getExpiringProducts(2);
    for (const auto &product : expiringProducts)
    {
        product->displayInfo();
    }

    double totalStorageFee = warehouse.calculateTotalStorageFee();
    std::cout << "\nTotal storage fee for all products: $" << totalStorageFee << std::endl;

    int productId = 5;
    auto product = warehouse[productId];
    if (product)
    {
        std::cout << "\nProduct with ID " << productId << ":" << std::endl;
        product->displayInfo();
    }
    else
    {
        std::cout << "\nProduct with ID " << productId << " not found." << std::endl;
    }

    auto chair = std::make_shared<BuildingMaterial>(
        "Chair", 7, 5.0, 30.0, 365, false);
    warehouse += chair;
    std::cout << "\nAfter adding Chair:" << std::endl;
    std::cout << warehouse;

    return 0;
}