// Copyright 2025 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>
#include "..\lib_tvector\tvector.h"

template<class T>
class Stack {
    TVector<T> _data;

public:
    // Constructors //
    Stack();
    Stack(std::initializer_list<T> init);
    Stack(const Stack& other);

    // Destructor //
    ~Stack();

    // Functions //
    void push(const T& val);
    void pop();
    inline T top() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear() noexcept;

    // Operators //
    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;
};

// Constructors //
template<class T>
Stack<T>::Stack() : _data() {}

template<class T>
Stack<T>::Stack(std::initializer_list<T> init) {
    for (const auto& item : init) {
        _data.push_back(item);
    }
}

template<class T>
Stack<T>::Stack(const Stack& other) : _data(other._data) {}

// Destructor //
template<class T>
Stack<T>::~Stack() {}

// Functions //
template<class T>
void Stack<T>::push(const T& val) {
    if (is_full()) { throw std::logic_error("Cannot push to full stack"); }
    _data.push_back(val);
}

template<class T>
void Stack<T>::pop() {
    if (is_empty()) { throw std::logic_error("Cannot pop from empty stack"); }
    _data.pop_back();
}

template<class T>
inline T Stack<T>::top() const {
    if (is_empty()) { throw std::logic_error("Cannot get top from empty stack"); }
    return _data.back();
}

template<class T>
inline bool Stack<T>::is_empty() const noexcept {
    return _data.is_empty();
}

template<class T>
inline bool Stack<T>::is_full() const noexcept {
    return _data.is_full();
}

template<class T>
void Stack<T>::clear() noexcept {
    _data.clear();
}

// Operators //
template<class T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this != &other) {
        _data = other._data;
    }
    return *this;
}

template<class T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept {
    if (this != &other) {
        _data = std::move(other._data);
    }
    return *this;
}

template<class T>
bool Stack<T>::operator==(const Stack& other) const {
    return _data == other._data;
}

template<class T>
bool Stack<T>::operator!=(const Stack& other) const {
    return !(*this == other);
}