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

template <class TKey, class TValue>
void SortedTableOnVector<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    int left = 0;
    int right = _rows.size() - 1;
    int insert_pos = 0;

    if (_rows.is_empty()) {
        _rows.insert(0, std::make_pair(key, value));
        return;
    }

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (_rows[middle].first == key) {
            throw std::logic_error("The key is not unique!");
        }
        else if (_rows[middle].first < key) {
            left = middle + 1;
            insert_pos = left;
        }
        else {
            right = middle - 1;
            insert_pos = middle;
        }
    }

    _rows.insert(insert_pos, std::make_pair(key, value));
}

template <class TKey, class TValue>
void SortedTableOnVector<TKey, TValue>::erase(const TKey& key) {
    int left = 0;
    int right = _rows.size() - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (_rows[middle].first == key) { _rows.erase(middle); return; }
        else if (_rows[middle].first < key) left = middle + 1;
        else right = middle - 1;
    }

    throw std::logic_error("Key not found for erase!");
}

template <class TKey, class TValue>
TValue& SortedTableOnVector<TKey, TValue>::find(const TKey& key) {
        int left = 0;
        int right = _rows.size() - 1;

        while (left <= right) {
            int middle = left + (right - left) / 2;

            if (_rows[middle].first == key) return _rows[middle].second;
            else if (_rows[middle].first < key) left = middle + 1;
            else right = middle - 1;
        }

        throw std::logic_error("Key not found!");
    }

template <class TKey, class TValue>
const TValue& SortedTableOnVector<TKey, TValue>::find(const TKey& key) const {
    int left = 0;
    int right = _rows.size() - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (_rows[middle].first == key) return _rows[middle].second;
        else if (_rows[middle].first < key) left = middle + 1;
        else right = middle - 1;
    }

    throw std::logic_error("Key not found!");
}

template <class TKey, class TValue>
bool SortedTableOnVector<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableOnVector<TKey, TValue>::print(std::ostream& out) const {
    out << "SortedTableOnVector: \n";
    for (int i = 0; i < _rows.size(); i++) {
        out << "| " << _rows[i].first << " | " << _rows[i].second << " |\n";
    }
}
