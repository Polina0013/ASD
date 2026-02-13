// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_itable\itable.h"
#include "..\lib_tvector\tvector.h"

template <class TKey, class TValue>
class UnsortedTableOnArr : public ITable<TKey, TValue> {
    TVector <std::pair <TKey, TValue>> _rows;
public:
    UnsortedTableOnArr() = default;
    UnsortedTableOnArr(const UnsortedTableOnArr&) = default;
    ~UnsortedTableOnArr() override = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;             // проверить std::pair на удаление по ключу использу€ == (адаптировать по надобности), если нет то писать TPair
    TValue& find(const TKey&) override;
    const TValue& find(const TKey&) const override;

    bool is_empty() const noexcept override;
    void print(std::ostream& out) const override;

    bool operator==(const UnsortedTableOnArr&) const;
};

template <class TKey, class TValue>
void UnsortedTableOnArr<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    _rows.push_back(std::make_pair(key, value));
}

template <class TKey, class TValue>
void UnsortedTableOnArr<TKey, TValue>::erase(const TKey& key) {
    for (int i = 0; i < _rows.size(); i++) {
        if (_rows[i].first == key) {
            _rows.erase(i);
            return;
        }
    }
    throw std::logic_error("Key not found for erase!");
}

template <class TKey, class TValue>
TValue& UnsortedTableOnArr<TKey, TValue>::find(const TKey& key) {
    for (int i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == key) {
            return _rows[i].second;
        }
    }
    throw std::logic_error("Key not found!");
}

template <class TKey, class TValue>
const TValue& UnsortedTableOnArr<TKey, TValue>::find(const TKey& key) const {
    for (int i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == key) {
            return _rows[i].second;
        }
    }
    throw std::logic_error("Key not found!");
}

template <class TKey, class TValue>
bool UnsortedTableOnArr<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableOnArr<TKey, TValue>::print(std::ostream& out) const {
    out << "UnsortedTableOnArr: \n";
    for (int i = 0; i < _rows.size(); i++) {
        out << "| " << _rows[i].first << " | " << _rows[i].second << " |\n";
    }
}

template <class TKey, class TValue>
bool UnsortedTableOnArr<TKey, TValue>::operator==(const UnsortedTableOnArr& other) const {
    if (_rows.size() != other._rows.size()) return false;

    for (const auto& pair : _rows) {
        bool found = false;
        for (const auto& other_pair : other._rows) {
            if (pair.first == other_pair.first) {
                if (pair.second != other_pair.second) return false;
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}