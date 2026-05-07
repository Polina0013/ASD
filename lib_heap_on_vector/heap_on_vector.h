// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_tvector\tvector.h"

template <class T>
class HeapOnVector {
    TVector<T> _data;
public:
    HeapOnVector() = default;
    HeapOnVector(int size);
    ~HeapOnVector() = default;

    int size() const;

    T top() const;
    void push(const T& value);
    void pop();

    bool is_empty() const noexcept;
    void clear() noexcept;

    void print() const noexcept;
    friend TVector<T> pyramid_sort(TVector<T> tvector) {
        TVector<T> sorted;
        HeapOnVector<T> heap;
        for (int i = 0; i < tvector.size(); i++) {
            heap.push(tvector[i]);
        }

        while (!heap.is_empty()) {
            sorted.push_back(heap.top());
            heap.pop();
        }

        return sorted;
    };

private:
    int get_parent(int index);
    int get_left(int index);
    int get_right(int index);

    void sift_up(int i);
    void sift_down(int i);

};
template <class T>
HeapOnVector<T>::HeapOnVector(int size) : _data(size) {};

template <class T>
int HeapOnVector<T>::size() const {
    return _data.size();
}

template <class T>
T HeapOnVector<T>::top() const {
    if (_data.is_empty()) throw std::logic_error("Heap is is_empty");
    return _data[0];
}
template <class T>
void HeapOnVector<T>::push(const T& value) {
    _data.push_back(value);
    if (_data.size() > 1) sift_up(_data.size() - 1);
}
template <class T>
void HeapOnVector<T>::pop() {
    if (_data.is_empty()) throw std::logic_error("Heap is empty!");

    _data[0] = _data.back();
    _data.pop_back();

    if (!_data.is_empty()) sift_down(0);
}

template <class T>
bool HeapOnVector<T>::is_empty() const noexcept {
    return _data.is_empty();
}
template <class T>
void HeapOnVector<T>::clear() noexcept {
    _data.clear();
}

template <class T>
void HeapOnVector<T>::print() const noexcept {
    for (int i = 0; i < _data.size(); i++) {
        std::cout << _data[i] << " ";
    }
    std::cout << std::endl;
}
//template <class T>
//TVector<T> pyramid_sort(TVector<T> tvector) {
//    TVector<T> sorted;
//    HeapOnVector<T> heap;
//    for (int i = 0; i < tvector.size(); i++) {
//        heap.push(tvector[i]);
//    }
//
//    while (!heap.is_empty()) {
//        sorted.push_back(heap.top());
//        heap.pop();
//    }
//
//    return sorted;
//}

template <class T>
int HeapOnVector<T>::get_parent(int i) {
    return (i - 1) / 2;
}
template <class T>
int HeapOnVector<T>::get_left(int i) {
    return 2 * i + 1;
}
template <class T>
int HeapOnVector<T>::get_right(int i) {
    return 2 * i + 2;
}

template <class T>
void HeapOnVector<T>::sift_up(int i) {
    while (i > 0 && _data[i] < _data[get_parent(i)]) {
        std::swap(_data[i], _data[get_parent(i)]);
        i = get_parent(i);
    }
}
template <class T>
void HeapOnVector<T>::sift_down(int i) {
    int size = _data.size();
    while (true) {
        int left = get_left(i);
        int right = get_right(i);
        int smallest = i;

        if (left < size && _data[left] < _data[smallest]) smallest = left;
        if (right < size && _data[right] < _data[smallest]) smallest = right;

        if (smallest == i) break;

        std::swap(_data[i], _data[smallest]);
        i = smallest;
    }
}