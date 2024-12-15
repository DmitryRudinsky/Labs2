#ifndef TASK_7
#define TASK_7
#include <ctime>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Product {
   protected:
    std::string name;
    int id;
    double weight;
    double price;
    int shelfLife;

   public:
    Product(std::string, int, double, double, int);
    virtual ~Product();

    Product(const Product&);
    Product& operator=(const Product&);

    virtual double calculateStorageFee() const;
    virtual void displayInfo() const;

    int getID() const;
};

class PerishableProduct : public Product {
    std::time_t expirationDate;

   public:
    PerishableProduct(std::string, int, double, double, int, std::time_t);

    virtual double calculateStorageFee() const override;
    virtual void displayInfo() const override;

    std::time_t getExpirationDate() const;
};

class ElectronicProduct : public Product {
    int warrantyPeriod;
    double powerRating;

   public:
    ElectronicProduct(std::string, int, double, double, int, int, double);
    virtual void displayInfo() const override;
};

class BuildingMaterial : public Product {
    bool flammability;

   public:
    BuildingMaterial(std::string, int, double, double, int, bool);
    virtual double calculateStorageFee() const override;
};

class Warehouse {
    std::map<int, std::shared_ptr<Product>> inventory;

   public:
    void addProduct(const std::shared_ptr<Product>&);
    void removeProduct(int);
    std::shared_ptr<Product> findProduct(int);

    template <typename T>
    std::vector<std::shared_ptr<T>> findByCategory() const {
        std::vector<std::shared_ptr<T>> result;
        for (const auto& [id, product] : inventory) {
            if (auto specificProduct = std::dynamic_pointer_cast<T>(product)) {
                result.push_back(specificProduct);
            }
        }
        return result;
    }
    double calculateTotalStorageFee() const;
    std::vector<std::shared_ptr<PerishableProduct>> getExpiringProducts(int);
    void displayInventory() const;

    Warehouse& operator+=(const std::shared_ptr<Product>&)&;
    Warehouse& operator-=(int);
    std::shared_ptr<Product> operator[](int);
    friend std::ostream& operator<<(std::ostream&, const Warehouse&);
};



#endif