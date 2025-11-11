// Copyright 2025 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>
#include "..\lib_tvector\tvector.h"

#define STANDARD_SIZE 15

template<class T>
class Queue {
    T* _data;
    size_t _head;
    size_t _tail;
    size_t _count;
    const size_t _max_size;

public:
    Queue();
    explicit Queue(size_t max_size);
    Queue(std::initializer_list<T> init);
    Queue(const Queue& other);

    size_t get_head() const;
    size_t get_tail() const;
    size_t get_count() const;
    size_t get_max_size() const;

    void push(T val);
    void pop();
    inline T tail() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear() noexcept;
    T head() const;

    bool operator==(const Queue<T>& other) const;
    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other) noexcept;
};

// Constructors //
template<class T>
Queue<T>::Queue() : _head(0), _tail(0), _count(0), _max_size(STANDARD_SIZE) {
    _data = new T[_max_size];
}

template<class T>
Queue<T>::Queue(size_t max_size) : _head(0), _tail(0), _count(0), _max_size(max_size) {
    if (max_size == 0) throw std::logic_error("Capacity must be positive");
    _data = new T[max_size];
}

template<class T>
Queue<T>::Queue(std::initializer_list<T> init) : _head(0), _tail(0), _count(0), _max_size(init.size()) {
    _data = new T[_max_size];

    for (const T& val : init) {
        push(val);
    }
}

template<class T>
Queue<T>::Queue(const Queue& other) : _head(other._head), _tail(other._tail), _count(other._count), _max_size(other._max_size) {
    _data = new T[_max_size];

    for (size_t i = 0; i < _max_size; i++) {
        _data[i] = other._data[i];
    }
}

template<class T>
size_t Queue<T>::get_head() const { return _head; }

template<class T>
size_t Queue<T>::get_tail() const { return _tail; }

template<class T>
size_t Queue<T>::get_count() const { return _count; }

template<class T>
size_t Queue<T>::get_max_size() const { return _max_size; }

// Functions //
template<class T>
void Queue<T>::push(T val) {
    if (is_full()) { throw std::logic_error("Queue is full"); }
    _data[_tail] = val;
    _tail = (_tail + 1) % _max_size;
    _count++;
}

template<class T>
void Queue<T>::pop() {
    if (is_empty()) { throw std::logic_error("Queue is empty"); }
    _head = (_head + 1) % _max_size;
    _count--;
}

template<class T>
inline T Queue<T>::tail() const {
    if (is_empty()) { throw std::logic_error("Queue is empty"); }
    return _data[(_tail - 1) % _max_size];
}

template<class T>
inline bool Queue<T>::is_empty() const noexcept { return _count == 0; }

template<class T>
inline bool Queue<T>::is_full() const noexcept { return _count == _max_size; }

template<class T>
void Queue<T>::clear() noexcept {
    _head = 0;
    _tail = 0;
    _count = 0;
}

template<class T>
T Queue<T>::head() const {
    if (is_empty()) { throw std::logic_error("Queue is empty"); }
    return _data[_head];
}

// Operators //
template<class T>
bool Queue<T>::operator==(const Queue<T>& other) const {
    if (_count != other._count) { return false; }

    for (size_t i = 0; i < _count; ++i) {
        size_t this_index = (_head + i) % _max_size;
        size_t other_index = (other._head + i) % other._max_size;

        if (_data[this_index] != other._data[other_index]) {
            return false;
        }
    }

    return true;
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        if (_max_size != other._max_size) { throw std::logic_error("Cannot assign queues with different capacities"); }

        for (size_t i = 0; i < _max_size; i++) {
            _data[i] = other._data[i];
        }

        _head = other._head;
        _tail = other._tail;
        _count = other._count;
    }
    return *this;
}

template<class T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept {
    if (this != &other) {
        if (_max_size != other._max_size) {
            throw std::logic_error("Cannot assign queues with different capacities");
        }

        delete[] _data;
        _data = other._data;
        _head = other._head;
        _tail = other._tail;
        _count = other._count;

        other._data = nullptr;
        other._head = 0;
        other._tail = 0;
        other._count = 0;
    }
    return *this;
}