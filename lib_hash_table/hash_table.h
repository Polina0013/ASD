// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <iomanip>

#include "..\lib_table\table.h"
#include "..\lib_tvector\tvector.h"


#define SIZE 100
#define SHIFT 7

enum status { empty_, busy_, deleted_ };

template <class TValue>
struct HashData {
    status _state;
    std::string _key;
    TValue _value;

    HashData() : _state(empty_), _key(""), _value(TValue{}) {}
    HashData(const std::string& key, const TValue& value) : _state(busy_), _key(key), _value(value) {}
    HashData(status state, const std::string& key) : _state(state), _key(key), _value(TValue{}) {}
    HashData(const HashData& other) = default;
    HashData& operator=(const HashData& other) = default;
};

template <class TValue>
class HashTableA : public Table<std::string, TValue> {
    TVector<HashData<TValue>> _rows;
    size_t _size;  // размер
    size_t _count; // заполненные
    size_t _shift;

public:

    HashTableA();
    HashTableA(size_t size);

    void insert(const std::string& key, const TValue& value) override;
    void erase(const std::string& key) override;
    TValue& find(const std::string& key) override;
    const TValue& find(const std::string& key) const override;

    bool is_empty() const noexcept override;
    bool is_full() const noexcept;
    void print(std::ostream& out) const override;

private:
    size_t h(const std::string& key) const noexcept;
    size_t hh(size_t hash) const noexcept;
    bool are_coprime(int a, int b);

    int find_key_index(const std::string& key) const;
};

template <class TValue>
bool HashTableA<TValue>::are_coprime(int a, int b) {
    return std::gcd(a, b) == 1;
}

template <class TValue>
HashTableA<TValue>::HashTableA() : _size(SIZE), _count(0), _shift(SHIFT) {
    for (size_t i = 0; i < _size; i++) _rows.push_back(HashData<TValue>());
}

template <class TValue>
HashTableA<TValue>::HashTableA(size_t size) : _size(size), _count(0), _shift(3) {
    for (size_t i = 0; i < _size; i++) _rows.push_back(HashData<TValue>());

    bool found = false;
    for (size_t i = std::max(static_cast <size_t>(2), size / 15); i < size; i++) {
        if (are_coprime(i, size)) { _shift = i; found = true; break; }
    }
}

template <class TValue>
bool HashTableA<TValue>::is_empty() const noexcept {
    return _count == 0;
}

template <class TValue>
bool HashTableA<TValue>::is_full() const noexcept {
    return _size == _count;
}

template <class TValue>
void HashTableA<TValue>::insert(const std::string& key, const TValue& value) {
    if (is_full()) throw std::logic_error("Hash table is full!");

    size_t hash = h(key);
    //size_t first_hash = hash;

    while (1) {
        if (_rows[hash]._state != busy_) {
            _rows[hash] = HashData<TValue>(key, value);
            _count++;
            return;
        }
        if (_rows[hash]._key == key) throw std::logic_error("Key already exist!");

        hash = hh(hash);
        //if (hash == first_hash) break;
    }
    //throw std::logic_error("Hash table is full!");
}

template <class TValue>
void HashTableA<TValue>::erase(const std::string& key) {
    int index = find_key_index(key);

    if (index == -1) throw std::logic_error("Key not found!");

    _rows[index]._state = deleted_;
    _count--;
}
template <class TValue>
TValue& HashTableA<TValue>::find(const std::string& key) {
    int index = find_key_index(key);

    if (index == -1) throw std::logic_error("Key not found!");

    return _rows[index]._value;
}
template <class TValue>
const TValue& HashTableA<TValue>::find(const std::string& key) const {
    int index = find_key_index(key);

    if (index == -1) throw std::logic_error("Key not found!");


    return _rows[index]._value;
}

template <class TValue>
size_t HashTableA<TValue>::h(const std::string& key) const noexcept {
    size_t hash = 0;
    for (size_t i = 0; i < key.length(); i++) {
        hash += key[i];
    }
    hash %= _size;
    return hash;
}

template <class TValue>
size_t HashTableA<TValue>::hh(size_t hash) const noexcept {
    return (hash + _shift) % _size;
}

template <class TValue>
void HashTableA<TValue>::print(std::ostream& out) const {
    out << "HashTableA: \n";

    if (_count == 0) {
        out << "  (empty)\n";
        return;
    }

    for (size_t i = 0; i < _size; i++) {
        if (_rows[i]._state == busy_) {
            out << "| " << std::setw(10) << _rows[i]._key << " | " << std::setw(6) << _rows[i]._value << " |\n";
        }
    }
}

template <class TValue>
int HashTableA<TValue>::find_key_index(const std::string& key) const { // find & erase
    if (is_empty()) return -1;

    size_t hash = h(key);
    size_t first_hash = hash;

    while (1) {
        if (_rows[hash]._state == empty_) break;

        if (_rows[hash]._state == busy_ && _rows[hash]._key == key) {
            return static_cast<int>(hash);
        }

        hash = hh(hash);
        if (hash == first_hash) break;
    }
    return -1;
}