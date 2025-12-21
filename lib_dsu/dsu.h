// Copyright 2025 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

template <class T>
class DSU {
    T* _parent, * _rank;
    size_t _size;
public:
    explicit DSU(size_t size);
    DSU(const DSU& other);

    ~DSU();

    size_t size() const;

    void union_sets(T x, T y);
    T find(T x);
    T find_rec(T x);   // сжатие пути

    bool same(T x, T y);
    size_t count_sets() const;

    DSU& operator=(const DSU& other);

    void validateIndex(T index) const;
};

template <class T>
DSU<T>::DSU(size_t size) : _size(size) {
    if (size == 0) { throw std::invalid_argument("Size cannot be zero"); }

    _parent = new T[size];
    _rank = new T[size];

    for (size_t i = 0; i < size; i++) {
        _parent[i] = static_cast<T>(i);
        _rank[i] = 0;
    }
}

template <class T>
DSU<T>::DSU(const DSU& other) : _size(other._size) {
    _parent = new T[_size];
    _rank = new T[_size];

    for (size_t i = 0; i < _size; i++) {
        _parent[i] = other._parent[i];
        _rank[i] = other._rank[i];
    }
}

template <class T>
DSU<T>& DSU<T>::operator=(const DSU& other) {
    if (this == &other) {
        return *this;
    }

    if (_size != other._size) {
        delete[] _parent;
        delete[] _rank;

        _size = other._size;
        _parent = new T[_size];
        _rank = new T[_size];
    }

    for (size_t i = 0; i < _size; i++) {
        _parent[i] = other._parent[i];
        _rank[i] = other._rank[i];
    }

    return *this;
}

template <class T>
DSU<T>::~DSU() {
    delete[] _parent;
    delete[] _rank;
}

//template <class T>
//void DSU<T>::union_sets(T x, T y) {
//    if (x >= _size || y >= _size || x < 0 || y < 0) throw ...;
//    if (x == y) return;
//
//    int parent_x = find(x);
//    int parent_y = find(y);
//
//    _parent[parent_y] = parent_x;
//
//
//}  // O(n)

template <class T>
size_t DSU<T>::size() const {
    return _size;
}

template <class T>
void DSU<T>::union_sets(T x, T y) {
    validateIndex(x);
    validateIndex(y);

    if (x == y) return;

    T rootX = find(x);
    T rootY = find(y);

    if (rootX == rootY) return;

    if (_rank[rootX] < _rank[rootY]) {
        _parent[rootX] = rootY;
    }
    else if (_rank[rootX] > _rank[rootY]) {
        _parent[rootY] = rootX;
    }
    else {
        _parent[rootY] = rootX;
        _rank[rootX]++;
    }
}

//template <class T>
//T DSU<T>::find(T x) {
//    if (x >= _size || x < 0) throw ...;
//    while (x != _parent[x]) {
//        x = _parent[x];
//    }
//    return x;
//}  // O(n)
//
//template <class T>
//T DSU<T>::find_rec(T x) {
//    if (_parent[x] == x) {
//        return x;
//    }
//
//    return x=find(_parent[x]);
//}

template <class T>
T DSU<T>::find(T x) {
    validateIndex(x);

    T root = x;
    while (root != _parent[root]) {
        root = _parent[root];
    }

    while (x != root) {
        T next = _parent[x];
        _parent[x] = root;
        x = next;
    }

    return root;
}

template <class T>
T DSU<T>::find_rec(T x) {
    validateIndex(x);

    if (_parent[x] != x) {
        _parent[x] = find_rec(_parent[x]);
    }
    return _parent[x];
}

template <class T>
bool DSU<T>::same(T x, T y) {
    return find(x) == find(y);
}

template <class T>
size_t DSU<T>::count_sets() const {
    size_t count = 0;
    for (size_t i = 0; i < _size; i++) {
        if (_parent[i] == static_cast<T>(i)) {
            count++;
        }
    }
    return count;
}

template <class T>
void DSU<T>::validateIndex(T index) const {
    if (index < 0 || index >= static_cast<T>(_size)) {
        throw std::out_of_range("Index out of bounds");
    }
}