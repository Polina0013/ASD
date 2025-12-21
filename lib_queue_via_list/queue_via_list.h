// Copyright 2025 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_list\list.h"

#define STANDARD_SIZE 15

template <class T>
class QueueViaList {
    List<T>* _list;
    size_t _size;
    size_t _count;

public:
    QueueViaList();
    QueueViaList(size_t size);
    explicit QueueViaList(std::initializer_list<T> init);
    QueueViaList(const QueueViaList& other);

    // Destructor //
    ~QueueViaList();

    // Functions //
    void push(const T& val);
    void pop();
    T tail() const;
    T head() const;
    bool is_empty() const noexcept;
    bool is_full() const noexcept;
    void clear() noexcept;

    // Operators //
    bool operator==(const QueueViaList& other) const;
    bool operator!=(const QueueViaList& other) const;

    QueueViaList& operator=(const QueueViaList& other);
};

template<class T>
QueueViaList<T>::QueueViaList() : _list(new List<T>()), _size(STANDARD_SIZE), _count(0) {}

template<class T>
QueueViaList<T>::QueueViaList(size_t size) : _list(new List<T>()), _size(size), _count(0) {
    if (size == 0) { throw std::logic_error("Capacity must be positive"); }
}

template<class T>
QueueViaList<T>::QueueViaList(std::initializer_list<T> init) : _list(new List<T>()), _size(init.size()), _count(0) {
    for (const auto& item : init) { push(item); }
}

template<class T>
QueueViaList<T>::QueueViaList(const QueueViaList& other) : _list(new List<T>(*other._list)), _size(other._size), _count(other._count) {}

template<class T>
QueueViaList<T>::~QueueViaList() {
    delete _list;
}

template<class T>
void QueueViaList<T>::push(const T& val) {
    if (is_full()) { throw std::logic_error("Cannot push to full queue"); }
    _list->push_back(val);
    _count++;
}

template<class T>
void QueueViaList<T>::pop() {
    if (is_empty()) { throw std::logic_error("Cannot pop from empty queue"); }
    _list->pop_front();
    _count--;
}

template<class T>
T QueueViaList<T>::tail() const {
    if (is_empty()) { throw std::logic_error("Cannot get tail from empty queue"); }
    return _list->back();  // O(1)
}

template<class T>
T QueueViaList<T>::head() const {
    if (is_empty()) { throw std::logic_error("Cannot get head from empty queue"); }
    return _list->front();  // O(1)
}

template<class T>
bool QueueViaList<T>::is_empty() const noexcept {
    return _list->is_empty();
}

template<class T>
bool QueueViaList<T>::is_full() const noexcept {
    return _count >= _size;
}

template<class T>
void QueueViaList<T>::clear() noexcept {
    while (!_list->is_empty()) {
        _list->pop_front();
    }
    _count = 0;
}

template<class T>
bool QueueViaList<T>::operator==(const QueueViaList& other) const {
    if (_size != other._size || _count != other._count) {
        return false;
    }

    return *_list == *other._list;
}

template<class T>
bool QueueViaList<T>::operator!=(const QueueViaList& other) const {
    return !(*this == other);
}

template<class T>
QueueViaList<T>& QueueViaList<T>::operator=(const QueueViaList& other) {
    if (this != &other) {
        *_list = *other._list;
        _size = other._size;
        _count = other._count;
    }
    return *this;
}