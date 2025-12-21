// Copyright 2025 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_list\list.h"

#define STANDARD_SIZE 15

template <class T>
class StackViaList {
    List<T>* _list;
    size_t _size;

public:
    StackViaList();
    StackViaList(size_t size);
    explicit StackViaList(std::initializer_list<T> init);
    StackViaList(const StackViaList& other);

    // Destructor //
    ~StackViaList();

    // Functions //
    void push(const T& val);                            // O(1)
    void pop();                                         // O(1)
    T top() const;
    bool is_empty() const noexcept;
    bool is_full() const noexcept;
    size_t number_of_filled_items() const noexcept;
    size_t size() const noexcept;
    void clear() noexcept;

    // Operators //
    bool operator==(const StackViaList& other) const;
    bool operator!=(const StackViaList& other) const;

    StackViaList& operator=(const StackViaList& other);
};

template<class T>
StackViaList<T>::StackViaList() : _list(new List<T>()), _size(STANDARD_SIZE) {}

template<class T>
StackViaList<T>::StackViaList(size_t size) : _list(new List<T>()), _size(size) {
    if (size == 0) { throw std::logic_error("Capacity must be positive"); }
}

template<class T>
StackViaList<T>::StackViaList(std::initializer_list<T> init) : _list(new List<T>()), _size(init.size()) {
    for (const auto& item : init) { push(item); }
}

template<class T>
StackViaList<T>::StackViaList(const StackViaList& other)
    : _list(new List<T>(*other._list)), _size(other._size) {}

template<class T>
StackViaList<T>::~StackViaList() {
    delete _list;
}

template<class T>
void StackViaList<T>::push(const T& val) {
    if (is_full()) { throw std::logic_error("Cannot push to full stack"); }
    _list->push_front(val);
}

template<class T>
void StackViaList<T>::pop() {
    if (is_empty()) { throw std::logic_error("Cannot pop from empty stack"); }
    _list->pop_front();
}

template<class T>
T StackViaList<T>::top() const {
    if (is_empty()) { throw std::logic_error("Cannot get top from empty stack"); }

    auto it = _list->begin();
    return *it;
}

template<class T>
bool StackViaList<T>::is_empty() const noexcept {
    return _list->is_empty();
}

template<class T>
bool StackViaList<T>::is_full() const noexcept {
    return number_of_filled_items() >= _size;
}

template<class T>
size_t StackViaList<T>::number_of_filled_items() const noexcept {
    size_t count = 0;
    for (auto it = _list->begin(); it != _list->end(); ++it) {
        ++count;
    }
    return count;
}

template<class T>
size_t StackViaList<T>::size() const noexcept {
    return _size;
}

template<class T>
void StackViaList<T>::clear() noexcept {
    while (!_list->is_empty()) {
        _list->pop_front();
    }
}

template<class T>
bool StackViaList<T>::operator==(const StackViaList& other) const {
    if (_size != other._size) {
        return false;
    }

    return *_list == *other._list;
}

template<class T>
bool StackViaList<T>::operator!=(const StackViaList& other) const {
    return !(*this == other);
}

template<class T>
StackViaList<T>& StackViaList<T>::operator=(const StackViaList& other) {
    if (this != &other) {
        *_list = *other._list;
        _size = other._size;
    }
    return *this;
}