#include "Vector.h"

Vector::Vector(int n) {
    if (n < 2) {
        _capacity = 2;
    }
    else {
        _capacity = n;
    }
    _resizeFactor = _capacity;
    _size = 0;
    _elements = new int[_capacity];
}

Vector::~Vector() {
    delete[] _elements;
    _elements = nullptr;
}

int Vector::size() const {
    return _size;
}

int Vector::capacity() const {
    return _capacity;
}

int Vector::resizeFactor() const {
    return _resizeFactor;
}

bool Vector::empty() const {
    return _size == 0;
}

void Vector::push_back(const int& val) {
    if (_size >= _capacity) {
        reserve(_capacity + _resizeFactor);
    }
    _elements[_size] = val;
    _size++;
}

int Vector::pop_back() {
    if (empty()) {
        std::cerr << "error: pop from empty vector" << std::endl;
        return -9999;
    }
    _size--;
    return _elements[_size];
}

void Vector::reserve(const int n) {
    if (n <= _capacity) {
        return;
    }

    int newCapacity = _capacity;
    while (newCapacity < n) {
        newCapacity += _resizeFactor;
    }

    int* newElements = new int[newCapacity];
    for (int i = 0; i < _size; i++) {
        newElements[i] = _elements[i];
    }

    delete[] _elements;
    _elements = newElements;
    _capacity = newCapacity;
}

void Vector::resize(const int n) {
    if (n < 0) return;
    if (n > _capacity) {
        reserve(n);
    }
    _size = n;
}

void Vector::resize(const int n, const int& val) {
    int oldSize = _size;
    resize(n);
    for (int i = oldSize; i < _size; i++) {
        _elements[i] = val;
    }
}

void Vector::assign(const int val) {
    for (int i = 0; i < _size; i++) {
        _elements[i] = val;
    }
}

Vector::Vector(const Vector& other) {
    _size = other._size;
    _capacity = other._capacity;
    _resizeFactor = other._resizeFactor;
    _elements = new int[_capacity];
    for (int i = 0; i < _size; i++) {
        _elements[i] = other._elements[i];
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }

    delete[] _elements;

    _size = other._size;
    _capacity = other._capacity;
    _resizeFactor = other._resizeFactor;
    _elements = new int[_capacity];

    for (int i = 0; i < _size; i++) {
        _elements[i] = other._elements[i];
    }

    return *this;
}

int& Vector::operator[](int n) const {
    if (n < 0 || n >= _size) {
        std::cerr << "Error: Index out of bounds!" << std::endl;
        return _elements[0];
    }
    return _elements[n];
}

Vector& Vector::operator+=(const Vector& other) {
    int maxSize = (_size > other._size) ? _size : other._size;
    if (maxSize > _capacity) {
        reserve(maxSize);
    }
    for (int i = 0; i < maxSize; i++) {
        int val2 = (i < other._size) ? other._elements[i] : 0;
        if (i < _size) {
            _elements[i] += val2;
        }
        else {
            _elements[i] = val2;
        }
    }
    _size = maxSize;
    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    int maxSize = (_size > other._size) ? _size : other._size;
    if (maxSize > _capacity) {
        reserve(maxSize);
    }
    for (int i = 0; i < maxSize; i++) {
        int val2 = (i < other._size) ? other._elements[i] : 0;
        if (i < _size) {
            _elements[i] -= val2;
        }
        else {
            _elements[i] = -val2;
        }
    }
    _size = maxSize;
    return *this;
}

Vector Vector::operator+(const Vector& other) const {
    int maxSize = (_size > other._size) ? _size : other._size;
    Vector result(maxSize);
    result.resize(maxSize);
    for (int i = 0; i < maxSize; i++) {
        int val1 = (i < _size) ? _elements[i] : 0;
        int val2 = (i < other._size) ? other._elements[i] : 0;
        result[i] = val1 + val2;
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    int maxSize = (_size > other._size) ? _size : other._size;
    Vector result(maxSize);
    result.resize(maxSize);
    for (int i = 0; i < maxSize; i++) {
        int val1 = (i < _size) ? _elements[i] : 0;
        int val2 = (i < other._size) ? other._elements[i] : 0;
        result[i] = val1 - val2;
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "Vector Info:\n";
    os << "Capacity is " << v._capacity << "\n";
    os << "Size is " << v._size << "\n";
    os << "data is {";
    for (int i = 0; i < v._size; i++) {
        os << v._elements[i];
        if (i < v._size - 1) {
            os << ",";
        }
    }
    os << "}\n";
    return os;
}