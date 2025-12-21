// Copyright 2025 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#define STANDARD_SIZE 15

template<class T>
class Stack {
    T* _data;
    int _size;
    int _top;

public:
    // Constructors //
    Stack();
    explicit Stack(int);
    Stack(std::initializer_list<T>);
    Stack(const Stack&);

    // Destructor //
    ~Stack();

    // Functions //
    void push(const T& val);
    void pop();
    inline T top() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    inline int number_of_filled_items() const noexcept;
    inline int size() const noexcept;
    void clear() noexcept;

    // Operators //
    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;

    Stack& operator=(const Stack& other);
};

// Constructors //
template<class T>
Stack<T>::Stack() : _size(STANDARD_SIZE), _top(-1) {
    _data = new T[_size];
}

template<class T>
Stack<T>::Stack(int max_size) : _size(max_size), _top(-1) {
    if (max_size <= 0) throw std::logic_error("Capacity must be positive");
    _data = new T[_size];
}

template<class T>
Stack<T>::Stack(std::initializer_list<T> init) : _size(init.size() > STANDARD_SIZE ? init.size() : STANDARD_SIZE), _top(-1) {
    _data = new T[_size];
    for (const auto& item : init) {
        push(item);
    }
}

template<class T>
Stack<T>::Stack(const Stack& other) : _size(other._size), _top(other._top) {
    _data = new T[_size];
    for (int i = 0; i <= _top; i++) {
        _data[i] = other._data[i];
    }
}

// Destructor //
template<class T>
Stack<T>::~Stack() {
    delete[] _data;
}

// Functions //
template<class T>
void Stack<T>::push(const T& val) {
    if (is_full()) throw std::logic_error("Cannot push to full stack");
    _top++;
    _data[_top] = val;
}

template<class T>
void Stack<T>::pop() {
    if (is_empty()) throw std::logic_error("Cannot pop from empty stack");
    _top--;
}

template<class T>
inline T Stack<T>::top() const {
    if (is_empty()) throw std::logic_error("Cannot get top from empty stack");
    return _data[_top];
}

template<class T>
inline bool Stack<T>::is_empty() const noexcept {
    return _top < 0;
}

template<class T>
inline bool Stack<T>::is_full() const noexcept {
    return _top >= _size - 1;
}

template<class T>
inline int Stack<T>::number_of_filled_items() const noexcept {
    return _top + 1;
}

template<class T>
inline int Stack<T>::size() const noexcept {
    return _size;
}

template<class T>
void Stack<T>::clear() noexcept {
    _top = -1;
}

// Operators //
template<class T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this != &other) {
        delete[] _data;

        _size = other._size;
        _top = other._top;

        _data = new T[_size];
        for (int i = 0; i <= _top; i++) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

template<class T>
bool Stack<T>::operator==(const Stack& other) const {
    if (_top != other._top) return false;

    for (int i = 0; i <= _top; i++) {
        if (_data[i] != other._data[i]) return false;
    }
    return true;
}

template<class T>
bool Stack<T>::operator!=(const Stack& other) const {
    return !(*this == other);
}