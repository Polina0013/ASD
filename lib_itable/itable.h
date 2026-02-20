// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

template <class TKey, class TValue>
class ITable {
public:
    virtual ~ITable() = default;

    virtual void insert(const TKey&, const TValue&) = 0;
    virtual void erase(const TKey&) = 0;
    virtual TValue& find(const TKey&) = 0;
    virtual const TValue& find(const TKey&) const = 0;
    virtual bool is_empty() const noexcept = 0;
};