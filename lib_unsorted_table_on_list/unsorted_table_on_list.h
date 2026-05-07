// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_table\table.h"
#include "..\lib_list\list.h"

template <class TKey, class TValue>
class UnsortedTableOnList : public Table<TKey, TValue> {
    List<std::pair <TKey, TValue>> _rows;
public:
    UnsortedTableOnList() = default;
    UnsortedTableOnList(const UnsortedTableOnList&) = default;
    ~UnsortedTableOnList() override = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue& find(const TKey&) override;
    const TValue& find(const TKey&) const override;

    bool is_empty() const noexcept override;
    void print(std::ostream& out) const override;

private:
    auto find_position(const TKey& key);
    auto find_position(const TKey& key) const;
};
/*
template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    bool isUnic = true;
    for (auto it = _rows.begin(); it != _rows.end(); it++) {
        if (it->first == key) { isUnic = false; break; }
    }
    if (isUnic) _rows.push_back(std::make_pair(key, value));
    else throw std::logic_error("The key is not unique!");
}

template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::erase(const TKey& key) {
    for (auto it = _rows.begin(); it != _rows.end(); it++) {
        if (it->first == key) {
            _rows.erase(it.get_node());
            return;
        }
    }
    throw std::logic_error("Key not found for erase!");
}

template <class TKey, class TValue>
TValue& UnsortedTableOnList<TKey, TValue>::find(const TKey& key) {
    for (auto it = _rows.begin(); it != _rows.end(); it++) {
        if (it->first == key) {
            return it->second;
        }
    }
    throw std::logic_error("Key not found!");
}

template <class TKey, class TValue>
const TValue& UnsortedTableOnList<TKey, TValue>::find(const TKey& key) const {
    for (auto it = _rows.begin(); it != _rows.end(); it++) {
        if (it->first == key) {
            return it->second;
        }
    }
    throw std::logic_error("Key not found!");
}*/

template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    auto it = find_position(key);
    if (it == _rows.end()) {
        _rows.push_back(std::make_pair(key, value));
    }
    else throw std::logic_error("The key is not unique!");
}

template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::erase(const TKey& key) {
    auto it = find_position(key);
    if (it != _rows.end()) {
        _rows.erase(it.get_node());
    }
    else throw std::logic_error("Key not found for erase!");
}

template <class TKey, class TValue>
TValue& UnsortedTableOnList<TKey, TValue>::find(const TKey& key) {
    auto it = find_position(key);
    if (it != _rows.end()) return it->second;
    throw std::logic_error("Key not found!");
}

template <class TKey, class TValue>
const TValue& UnsortedTableOnList<TKey, TValue>::find(const TKey& key) const {
    auto it = find_position(key);
    if (it != _rows.end()) return it->second;
    throw std::logic_error("Key not found!");
}

template <class TKey, class TValue>
bool UnsortedTableOnList<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::print(std::ostream& out) const {
    out << "UnsortedTableOnList: \n";
    for (auto it = _rows.begin(); it != _rows.end(); it++) {
        out << "| " << it->first << " | " << it->second << " |\n";
    }
}

template <class TKey, class TValue>
auto UnsortedTableOnList<TKey, TValue>::find_position(const TKey& key) {
    for (auto it = _rows.begin(); it != _rows.end(); it++) {
        if (it->first == key) return it;
    }
    return _rows.end();
}

template <class TKey, class TValue>
auto UnsortedTableOnList<TKey, TValue>::find_position(const TKey& key) const {
    for (auto it = _rows.begin(); it != _rows.end(); it++) {
        if (it->first == key) return it;
    }
    return _rows.end();
}