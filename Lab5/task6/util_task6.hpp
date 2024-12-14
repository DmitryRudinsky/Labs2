#ifndef TASK_6
#define TASK_6

#include <compare>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>

class Vector {
   private:
    double* data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t);

   public:
    Vector(size_t, double = 0.0);
    Vector(size_t);
    template <typename Iter>
    Vector(Iter, Iter);
    Vector(std::initializer_list<double>);
    ~Vector();

    double& at(size_t);
    const double& at(size_t) const;

    double& front();
    const double& front() const;

    double& back();
    const double& back() const;

    double* data();
    const double* data() const;

    bool empty() const;
    size_t size() const;
    void reserve(size_t);
    size_t capacity() const;
    void shrink_to_fit();
    void clear();

    void insert(size_t, double);
    void erase(size_t);
    void push_back(double);
    void pop_back();
    void resize(size_t, double);

    std::strong_ordering operator<=>(const Vector&) const;
    bool operator==(const Vector&) const;

    class Iterator {
       private:
        double* ptr;

       public:
       using difference_type = std::ptrdiff_t;
       using value_type = double;
       using pointer = double*;
       using reference = double&;
       using iterator_category = std::random_access_iterator_tag;
       
       
        explicit Iterator(double* ptr);
        double& operator*();
        const double& operator*() const;
        
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        
        
        Iterator operator+(ptrdiff_t) const;
        Iterator operator-(ptrdiff_t) const;
        
        // Iterator operator+(const Iterator&) const;
        ptrdiff_t operator-(const Iterator&) const;
        
        Iterator& operator+=(ptrdiff_t);
        Iterator& operator-=(ptrdiff_t);
        
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;
        
        bool operator<(const Iterator&) const;
        bool operator>(const Iterator&) const;
        
        pointer operator->() { return  ptr; }
        
        double& operator[](ptrdiff_t);
        const double& operator[](ptrdiff_t) const;
    };
    
    Iterator begin();
    const Iterator begin() const;
    Iterator end();
    const Iterator end() const;
};

#endif