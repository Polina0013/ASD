// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_itable\itable.h"

template <class TKey, class TValue>
class Table : public ITable<TKey, TValue>{
public:
    virtual void print(std::ostream& out) const = 0;
};

template <class TKey, class TValue>
std::ostream& operator<<(std::ostream& out, const Table<TKey, TValue>& table) {
    table.print(out);
    return out;
}