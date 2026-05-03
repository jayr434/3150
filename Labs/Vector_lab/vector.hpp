#pragma once
#include <cstddef> //size_t
#include <stdexcept> //std::out_of_range
#include <concepts>

template <typename T>
concept EqualityComparable = requires(const T& a, const T& b)
{
    { a == b } -> std::convertible_to<bool>;
};
template <EqualityComparable T>
class Vector {
private:
    T* data_;  //raw ptr to dynam. alloc. array on heap (template, so any data type can be chosen
    size_t size_;   //number of elements in use in vector
    size_t capacity_; //max size before realloc. (always >=size)

    void resize_capacity(size_t new_capacity){ //function, allocating new block of memory (new_capacity size), move elements over, free old memory, update data_ and capacity_
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; i++)
            new_data[i] = data_[i];
        delete[] data_;
        data_     = new_data;
        capacity_ = new_capacity;
    }     
public:
    class Iterator {
    private:
        T* current_;
    public:
        Iterator(T* ptr) : current_(ptr) {}
 
        T& operator*() { return *current_; }
 
        Iterator& operator++() {
            ++current_;
            return *this;
        }
 
        bool operator!=(const Iterator& other) const {
            return current_ != other.current_;
        }
    };
 
    class ConstIterator {
    private:
        const T* current_;
    public:
        ConstIterator(const T* ptr) : current_(ptr) {}
 
        const T& operator*() const { return *current_; }
 
        ConstIterator& operator++() {
            ++current_;
            return *this;
        }
 
        bool operator!=(const ConstIterator& other) const {
            return current_ != other.current_;
        }
    };
 
    Vector(const Vector&)            = delete;
    Vector& operator=(const Vector&) = delete;
 
    //constructor destructor
 
    Vector() : data_(nullptr), size_(0), capacity_(0) {}
    ~Vector() { delete[] data_; }
 
    //capacity
 
    size_t size()     const { return size_; }
    size_t capacity() const { return capacity_; }
    bool   empty()    const { return size_ == 0; }
 
    //access elements 
 
    T& at(size_t index) {
        if (index >= size_)
            throw std::out_of_range("Vector::at — index " + std::to_string(index) +
                                    " is out of range (size = " + std::to_string(size_) + ")");
        return data_[index];
    }
 
    const T& at(size_t index) const {
        if (index >= size_)
            throw std::out_of_range("Vector::at — index " + std::to_string(index) +
                                    " is out of range (size = " + std::to_string(size_) + ")");
        return data_[index];
    }
 
    //non const
    T& operator[](size_t index) { return data_[index]; }
 
    //const
    const T& operator[](size_t index) const { return data_[index]; }
 
    //pushback
 
    void push_back(const T& value) {
        if (size_ == capacity_)
            resize_capacity(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = value;
    }
 
    //iterators
 
    //non const, non const vectors returns iterator
    Iterator begin() { return Iterator(data_); }
    Iterator end()   { return Iterator(data_ + size_); }
 
    //constiterator for cosnt vectors
    ConstIterator begin() const { return ConstIterator(data_); }
    ConstIterator end()   const { return ConstIterator(data_ + size_); }
 
    //eq
 
    bool operator==(const Vector<T>& other) const {
        if (size_ != other.size_) return false;
        for (size_t i = 0; i < size_; i++)
            if (!(data_[i] == other.data_[i])) return false;
        return true;
    }
};
