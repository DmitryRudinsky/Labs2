#include "util_task6.hpp"

void Vector::reallocate(size_t new_capacity) {
    double* new_data = new double[new_capacity];
    std::copy(data_, data_ + size_, new_data);
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}


Vector::Vector(size_t n, double elem) : size_(n), capacity_(n){
    data_ = new double[capacity_];
    std::fill(data_, data_ + size_, elem);
}

Vector::Vector(size_t n) : Vector(n, 0.0) {}

template <typename Iter>
Vector::Vector(Iter first, Iter last) {
    size_ = std::distance(first, last);
    capacity_ = size_;
    data_ = new double[capacity_];
    std::copy(first, last, data_);
}

Vector::Vector(std::initializer_list<double> list) : size_(list.size()), capacity_(list.size()) {
    data_ = new double[capacity_];
    std::copy(list.begin(), list.end(), data_);
}

Vector::~Vector() {
    delete[] data_;
}


double& Vector::at(size_t index) {
    if (index >= size_) throw std::out_of_range("Index out of range");
    return data_[index];
}

const double& Vector::at(size_t index) const {
    if (index >= size_) throw std::out_of_range("Index out of range");
    return data_[index];
}


double& Vector::front() { return data_[0]; }
const double& Vector::front() const { return data_[0]; }

double& Vector::back() { return data_[size_ - 1]; }
const double& Vector::back() const { return data_[size_ - 1]; }

double* Vector::data() { return data_; }
const double* Vector::data() const { return data_; }

bool Vector::empty() const { return size_ == 0; }
size_t Vector::size() const { return size_; }
void Vector::reserve(size_t num) { if (num > capacity_) reallocate(num); }
size_t Vector::capacity() const { return capacity_; }
void Vector::shrink_to_fit() { if (capacity_ > size_) reallocate(size_); }
void Vector::clear() { size_ = 0; } // clear, reserve ??


void Vector::insert(size_t index, double elem) {
    if (index > size_) throw std::out_of_range("Index is out of range.");
    if (size_ == capacity_) reserve(capacity_ * 2);
    for (size_t i = size_; i > index; i--) {
        data_[i]= data_[i - 1];
    }
    data_[index] = elem;
    ++size_;
}

void Vector::erase(size_t index) {
    if (index >= size_) throw std::out_of_range("Index is out of range.");
    for (size_t i = index; i < size_ - 1; ++i) {
        data_[i] = data_[i + 1];
    }
    --size_;
}

void Vector::push_back(double elem) {
    if (size_ == capacity_) reserve(capacity_ * 2);
    data_[size_++] = elem;
}

void Vector::pop_back() {
    if (size_ > 0) --size_;
}

void Vector::resize(size_t new_size, double elem) {
    if (new_size > size_) {
        if (new_size > capacity_) { reserve(new_size); }
        std::fill(data_ + size_, data_ + new_size, elem);
    }
    size_ = new_size;
}

std::strong_ordering Vector::operator<=>(const Vector& other) const {
    for (size_t i = 0; i < std::min(size_, other.size_); i++) {
        if (data_[i] > other.data_[i]) return std::strong_ordering::greater;
        if (data_[i] < other.data_[i]) return std::strong_ordering::less;
    }
    return size_ <=> other.size_;
}

Vector::Iterator Vector::Iterator::operator+(ptrdiff_t offset) const {
    return Iterator(ptr + offset);
}

Vector::Iterator Vector::Iterator::operator-(ptrdiff_t offset) const {
    return Iterator(ptr - offset);
}

ptrdiff_t Vector::Iterator::operator-(const Vector::Iterator& adr) const {
    return ptr - adr.ptr;
}

// Vector::Iterator Vector::Iterator::operator+(const Vector::Iterator& adr) const {
//     return Iterator(ptr - adr.ptr);
// }

Vector::Iterator& Vector::Iterator::operator+=(ptrdiff_t offset) {
    ptr += offset;
    return *this;
}
Vector::Iterator& Vector::Iterator::operator-=(ptrdiff_t offset) {
    ptr -= offset;
    return *this;
}

bool Vector::operator==(const Vector& other) const {
    return size_ == other.size_ && std::equal(data_, data_ + size_, other.data_);
}

bool Vector::Iterator::operator<(const Vector::Iterator& other) const { return ptr < other.ptr; }
bool Vector::Iterator::operator>(const Vector::Iterator& other) const { return ptr > other.ptr; }

Vector::Iterator::Iterator(double* ptr) : ptr(ptr) {}

double& Vector::Iterator::operator*() { return *ptr; }
const double& Vector::Iterator::operator*() const { return *ptr; }


Vector::Iterator& Vector::Iterator::operator++() {
    ++ptr;
    return *this;
}
Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

Vector::Iterator& Vector::Iterator::operator--() {
    --ptr;
    return *this;
}
Vector::Iterator Vector::Iterator::operator--(int) {
    Iterator tmp = *this;
    --(*this);
    return tmp;
}

bool Vector::Iterator::operator==(const Iterator& other) const {
    return ptr == other.ptr;
}
bool Vector::Iterator::operator!=(const Iterator& other) const {
    return ptr != other.ptr;
}

Vector::Iterator Vector::begin() { return Iterator(data_); }
const Vector::Iterator Vector::begin() const { return Iterator(data_); }

Vector::Iterator Vector::end() { return Iterator(data_ + size_); }
const Vector::Iterator Vector::end() const { return Iterator(data_ + size_); }
