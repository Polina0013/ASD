// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_table\table.h"
#include "..\lib_rb_tree\rb_tree.h"

template <class TKey, class TValue>
class SortedTableOnRBTree : public Table<TKey, TValue> {
    RBTree<TKey, TValue> _rows;
public:
    SortedTableOnRBTree() = default;
    SortedTableOnRBTree(const SortedTableOnRBTree&) = default;
    ~SortedTableOnRBTree() override = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue& find(const TKey&) override;
    const TValue& find(const TKey&) const override;

    bool is_empty() const noexcept override;
    void print(std::ostream& out) const override;
    void print_rec(RBNode<TKey, TValue>* node, std::ostream& out) const;
};

template <class TKey, class TValue>
void SortedTableOnRBTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    _rows.insert(key, value);
}
template <class TKey, class TValue>
void SortedTableOnRBTree<TKey, TValue>::erase(const TKey& key) {
    _rows.erase(key);
}
template <class TKey, class TValue>
TValue& SortedTableOnRBTree<TKey, TValue>::find(const TKey& key) {
    TValue* found = const_cast<TValue*>(_rows.find(key));
    if (found == nullptr) throw std::logic_error("Key not found!");
    return *found;
}
template <class TKey, class TValue>
const TValue& SortedTableOnRBTree<TKey, TValue>::find(const TKey& key) const {
    const TValue* found = _rows.find(key);
    if (found == nullptr) throw std::logic_error("Key not found!");
    return *found;
}

template <class TKey, class TValue>
bool SortedTableOnRBTree<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableOnRBTree<TKey, TValue>::print(std::ostream& out) const {
    out << "SortedTableOnRBTree: \n";
    if (_rows.is_empty()) return;

    print_rec(_rows.get_root(), out);
}
template <class TKey, class TValue>
void SortedTableOnRBTree<TKey, TValue>::print_rec(RBNode<TKey, TValue>* node, std::ostream& out) const {
    if (!node) return;
    print_rec(node->left, out);
    out << "| " << node->data.first << " | " << node->data.second << " |\n";
    print_rec(node->right, out);
}