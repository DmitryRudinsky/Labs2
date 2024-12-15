#include "options.hpp"
#include <cstddef>
#include <memory>

Product::Product(std::string name, int id, double weigth, double price, int shelfLife)
    : name(std::move(name)), id(id), weight(weigth), price(price), shelfLife(shelfLife) {}

Product::~Product() = default;

Product::Product(const Product &other)
    : name(other.name),
      id(other.id),
      weight(other.weight),
      price(other.price),
      shelfLife(other.shelfLife) {}

Product &Product::operator=(const Product &other)
{
    if (this != &other)
    {
        name = other.name;
        id = other.id;
        weight = other.weight;
        price = other.price;
        shelfLife = other.shelfLife;
    }
    return *this;
}

double Product::calculateStorageFee() const
{
    return weight * 0.2;
}

void Product::displayInfo() const
{
    std::cout << "Name " << name << ", ID: " << id << ", Weigth: " << weight
              << "kg, Price: $" << price << ", Shelf life: " << shelfLife << " days"
              << std::endl;
}

int Product::getID() const
{
    return id;
}

PerishableProduct::PerishableProduct(std::string name, int id, double weight,
                                     double price, int shelfLife,
                                     std::time_t expirationDate)
    : Product(std::move(name), id, weight, price, shelfLife),
      expirationDate(expirationDate) {}

double PerishableProduct::calculateStorageFee() const
{
    std::time_t currentTime = std::time(nullptr);
    double daysToExpire = std::difftime(expirationDate, currentTime) / (60 * 60 * 24);
    double urgency = (daysToExpire < 7) ? 2.0 : 1.0;
    return weight * 0.2 * urgency;
}

void PerishableProduct::displayInfo() const
{
    Product::displayInfo();
    std::cout << "Expiration Date: " << std::asctime(std::localtime(&expirationDate));
}

std::time_t PerishableProduct::getExpirationDate() const
{
    return expirationDate;
}

ElectronicProduct::ElectronicProduct(std::string name, int id, double weight,
                                     double price, int shelfLife, int warrantyPeriod,
                                     double powerRating)
    : Product(name, id, weight, price, shelfLife),
      warrantyPeriod(warrantyPeriod),
      powerRating(powerRating) {}

void ElectronicProduct::displayInfo() const
{
    Product::displayInfo();
    std::cout << "Warranty Period: " << warrantyPeriod
              << " months, Power Rating: " << powerRating << "W" << std::endl;
}

BuildingMaterial::BuildingMaterial(std::string name, int id, double weight, double price,
                                   int shelfLife, bool flammability)
    : Product(name, id, weight, price, shelfLife), flammability(flammability) {}

double BuildingMaterial::calculateStorageFee() const
{
    double flammabilityMult = flammability ? 1.5 : 1.0;
    return weight * 0.2 * flammabilityMult;
}

void Warehouse::addProduct(const std::shared_ptr<Product> &product)
{
    inventory[product->getID()] = product;
}

void Warehouse::removeProduct(int id)
{
    inventory.erase(id);
}

std::shared_ptr<Product> Warehouse::findProduct(int id)
{
    auto it = inventory.find(id);
    return (it != inventory.end()) ? it->second : nullptr;
}

double Warehouse::calculateTotalStorageFee() const
{
    double totalFee = 0.0;
    for (const auto &[_, product] : inventory)
    {
        totalFee += product->calculateStorageFee();
    }
    return totalFee;
}

std::vector<std::shared_ptr<PerishableProduct>> Warehouse::getExpiringProducts(int days)
{
    std::vector<std::shared_ptr<PerishableProduct>> expiringProducts;
    std::time_t curTime = std::time(nullptr);
    for (const auto &[id, product] : inventory)
    {
        auto perishable = std::dynamic_pointer_cast<PerishableProduct>(product);
        if (perishable)
        {
            double daysToExpire = std::difftime(perishable->getExpirationDate(), curTime) / (60 * 60 * 24);
            if (daysToExpire <= days)
            {
                expiringProducts.push_back(perishable);
            }
        }
    }
    return expiringProducts;
}

void Warehouse::displayInventory() const
{
    for (const auto &[id, product] : inventory)
    {
        product->displayInfo();
    }
}

Warehouse &Warehouse::operator+=(const std::shared_ptr<Product> &product) &
{
    addProduct(product);
    return *this;
}

Warehouse &Warehouse::operator-=(int id)
{
    removeProduct(id);
    return *this;
}

std::shared_ptr<Product> Warehouse::operator[](int id)
{
    return findProduct(id);
}

std::ostream &operator<<(std::ostream &os, const Warehouse &warehouse)
{
    os << "Warehouse Inventory: " << std::endl;
    for (const auto &[id, product] : warehouse.inventory)
    {
        product->displayInfo();
    }
    return os;
}