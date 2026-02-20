// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_table\table.h"
#include "..\lib_tvector\tvector.h"

template <class TKey, class TValue>
class SortedTableOnVector : public Table<TKey, TValue> {
    TVector <std::pair <TKey, TValue>> _rows;
public:
    SortedTableOnVector() = default;
    SortedTableOnVector(const SortedTableOnVector&) = default;
    ~SortedTableOnVector() override = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue& find(const TKey&) override;
    const TValue& find(const TKey&) const override;

    bool is_empty() const noexcept override;
    void print(std::ostream& out) const override;
};
/*
template <class TKey, class TValue>
void UnsortedTableOnVector<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    bool isUnic = true;
    for (int i = 0; i < _rows.size(); i++) {
        if (_rows[i].first == key) isUnic = false;
    }
    if (isUnic) _rows.push_back(std::make_pair(key, value));
    else throw std::logic_error("The key is not unique!");
}

template <class TKey, class TValue>
void UnsortedTableOnVector<TKey, TValue>::erase(const TKey& key) {
    for (int i = 0; i < _rows.size(); i++) {
        if (_rows[i].first == key) {
            _rows.erase(i);
            return;
        }
    }
    throw std::logic_error("Key not found for erase!");
}

template <class TKey, class TValue>
TValue& UnsortedTableOnVector<TKey, TValue>::find(const TKey& key) {
    for (int i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == key) {
            return _rows[i].second;
        }
    }
    throw std::logic_error("Key not found!");
}

template <class TKey, class TValue>
const TValue& UnsortedTableOnVector<TKey, TValue>::find(const TKey& key) const {
    for (int i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == key) {
            return _rows[i].second;
        }
    }
    throw std::logic_error("Key not found!");
}

template <class TKey, class TValue>
bool UnsortedTableOnVector<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableOnVector<TKey, TValue>::print(std::ostream& out) const {
    out << "UnsortedTableOnVector: \n";
    for (int i = 0; i < _rows.size(); i++) {
        out << "| " << _rows[i].first << " | " << _rows[i].second << " |\n";
    }
}
*/