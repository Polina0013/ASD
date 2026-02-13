// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

template <class TKey, class TValue>  // конструкторов нет
class ITable {
public:
    virtual ~ITable() = default;

    virtual void insert(const TKey&, const TValue&) = 0;
    virtual void erase(const TKey&) = 0;
    virtual TValue& find(const TKey&) = 0;
    virtual const TValue& find(const TKey&) const = 0;
    virtual bool is_empty() const noexcept = 0;
    virtual void print(std::ostream& out) const = 0;

    friend std::ostream& operator<<(std::ostream& out, const ITable& table) {
        table.print(out);
        return out;
    }
};