// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>
#include <iomanip>

#include "..\lib_table\table.h"
#include "..\lib_tvector\tvector.h"
#include "..\lib_list\list.h"

#define SIZE 10

template <class TValue>
struct HashNode {
    std::string _key;
    TValue _value;

    HashNode() : _key(""), _value(TValue{}) {}
    HashNode(const std::string& key, const TValue& value) : _key(key), _value(value) {}
    
    HashNode(const HashNode& other) = default;
    HashNode& operator=(const HashNode& other) = default;
};

template <class TValue>
class HashTableC : public Table<std::string, TValue> {
    TVector<List<HashNode<TValue>>> _rows;
    size_t _size;
    size_t _count;

public:
    HashTableC();
    HashTableC(size_t size);

    void insert(const std::string& key, const TValue& value) override;
    void erase(const std::string& key) override;
    TValue& find(const std::string& key) override;
    const TValue& find(const std::string& key) const override;

    bool is_empty() const noexcept override;
    bool is_full() const noexcept;
    void print(std::ostream& out) const override;

private:
    size_t h(const std::string& key) const noexcept;

    auto find_node(const std::string& key, size_t hash);
    auto find_node(const std::string& key, size_t hash) const;
};

template <class TValue>
HashTableC<TValue>::HashTableC() : _size(SIZE), _count(0) {
    _rows.resize(_size);
}

template <class TValue>
HashTableC<TValue>::HashTableC(size_t size) : _size(size), _count(0) {
    if (_size <= 0) _size = 1;
    _rows.resize(_size);
}

template <class TValue>
bool HashTableC<TValue>::is_empty() const noexcept {
    return _count == 0;
}

template <class TValue>
bool HashTableC<TValue>::is_full() const noexcept {
    return false;
}

template <class TValue>
void HashTableC<TValue>::insert(const std::string& key, const TValue& value) {
    size_t hash = h(key);

    auto it = find_node(key, hash);
    if (it != _rows[hash].end()) throw std::logic_error("Key already exists!");

    _rows[hash].push_back(HashNode<TValue>(key, value));
    _count++;
}

template <class TValue>
void HashTableC<TValue>::erase(const std::string& key) {
    size_t hash = h(key);

    auto it = find_node(key, hash);
    if (it == _rows[hash].end()) throw std::logic_error("Key not found!");

    _rows[hash].erase(it.get_node());
    _count--;
}

template <class TValue>
TValue& HashTableC<TValue>::find(const std::string& key) {
    size_t hash = h(key);
    auto it = find_node(key, hash);
    if (it == _rows[hash].end()) throw std::logic_error("Key not found!");
    return it->_value;
}
template <class TValue>
const TValue& HashTableC<TValue>::find(const std::string& key) const {
    size_t hash = h(key);
    auto it = find_node(key, hash);
    if (it == _rows[hash].end()) throw std::logic_error("Key not found!");
    return it->_value;
}

template <class TValue>
size_t HashTableC<TValue>::h(const std::string& key) const noexcept {
    size_t hash = 0;
    for (size_t i = 0; i < key.length(); i++) {
        hash += key[i];
    }
    hash %= _size;
    return hash;
}

template <class TValue>
void HashTableC<TValue>::print(std::ostream& out) const {
    out << "HashTableC: \n";

    if (_count == 0) {
        out << "  (empty)\n";
        return;
    }

    for (size_t i = 0; i < _size; i++) {
        for (auto it = _rows[i].begin(); it != _rows[i].end(); it++) {
            out << "| " << std::setw(8) << it->_key << " | " << std::setw(6) << it->_value << " |\n";
        }
    }
}

template <class TValue>
auto HashTableC<TValue>::find_node(const std::string& key, size_t hash) {
    for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
        if (it->_key == key) return it;
    }
    return _rows[hash].end();
}

template <class TValue>
auto HashTableC<TValue>::find_node(const std::string& key, size_t hash) const {
    for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
        if (it->_key == key) return it;
    }
    return _rows[hash].end();
}