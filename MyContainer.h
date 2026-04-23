#ifndef MYCONTAINER_H
#define MYCONTAINER_H

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <algorithm>

template <typename T>
class MyContainer {
private:
    T* data;
    size_t capacity;
    size_t count;

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < count; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    class Iterator {
    private:
        T* ptr;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(T* p = nullptr) : ptr(p) {}

        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }

        Iterator& operator++() { ++ptr; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++ptr; return tmp; }
        Iterator& operator--() { --ptr; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --ptr; return tmp; }

        Iterator operator+(difference_type n) const { return Iterator(ptr + n); }
        Iterator operator-(difference_type n) const { return Iterator(ptr - n); }
        difference_type operator-(const Iterator& other) const { return ptr - other.ptr; }

        Iterator& operator+=(difference_type n) { ptr += n; return *this; }
        Iterator& operator-=(difference_type n) { ptr -= n; return *this; }

        reference operator[](difference_type n) const { return *(ptr + n); }

        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        bool operator<(const Iterator& other) const { return ptr < other.ptr; }
        bool operator>(const Iterator& other) const { return ptr > other.ptr; }
        bool operator<=(const Iterator& other) const { return ptr <= other.ptr; }
        bool operator>=(const Iterator& other) const { return ptr >= other.ptr; }
    };

    class ConstIterator {
    private:
        const T* ptr;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        ConstIterator(const T* p = nullptr) : ptr(p) {}

        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }

        ConstIterator& operator++() { ++ptr; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp = *this; ++ptr; return tmp; }
        ConstIterator& operator--() { --ptr; return *this; }
        ConstIterator operator--(int) { ConstIterator tmp = *this; --ptr; return tmp; }

        bool operator==(const ConstIterator& other) const { return ptr == other.ptr; }
        bool operator!=(const ConstIterator& other) const { return ptr != other.ptr; }
    };

    MyContainer() : data(nullptr), capacity(0), count(0) {}

    explicit MyContainer(size_t initialCapacity) 
        : data(new T[initialCapacity]), capacity(initialCapacity), count(0) {}

    MyContainer(const MyContainer& other) 
        : data(new T[other.capacity]), capacity(other.capacity), count(other.count) {
        for (size_t i = 0; i < count; ++i) {
            data[i] = other.data[i];
        }
    }

    MyContainer& operator=(const MyContainer& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            count = other.count;
            data = new T[capacity];
            for (size_t i = 0; i < count; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~MyContainer() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (count >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[count++] = value;
    }

    void pop_back() {
        if (count > 0) {
            --count;
        }
    }

    T& operator[](size_t index) {
        if (index >= count) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= count) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t size() const { return count; }
    size_t getCapacity() const { return capacity; }
    bool empty() const { return count == 0; }

    void clear() {
        count = 0;
    }

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + count); }
    
    ConstIterator begin() const { return ConstIterator(data); }
    ConstIterator end() const { return ConstIterator(data + count); }
    ConstIterator cbegin() const { return ConstIterator(data); }
    ConstIterator cend() const { return ConstIterator(data + count); }
};

#endif