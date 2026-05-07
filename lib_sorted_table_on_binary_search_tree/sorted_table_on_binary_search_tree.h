// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_table\table.h"
#include "..\lib_binary_search_tree\binary_search_tree.h"

template <class TKey, class TValue>
class SortedTableOnBinarySearchTree : public Table<TKey, TValue> {
    BinarySearchTree<TKey, TValue> _rows;
public:
    SortedTableOnBinarySearchTree() = default;
    SortedTableOnBinarySearchTree(const SortedTableOnBinarySearchTree&) = default;
    ~SortedTableOnBinarySearchTree() override = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue& find(const TKey&) override;
    const TValue& find(const TKey&) const override;

    bool is_empty() const noexcept override;
    void print(std::ostream& out) const override;
    void print_rec(BSTNode<TKey, TValue>* node, std::ostream& out) const;
};

template <class TKey, class TValue>
void SortedTableOnBinarySearchTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    _rows.insert(key, value);
}
template <class TKey, class TValue>
void SortedTableOnBinarySearchTree<TKey, TValue>::erase(const TKey& key) {
    _rows.erase(key);
}
template <class TKey, class TValue>
TValue& SortedTableOnBinarySearchTree<TKey, TValue>::find(const TKey& key) {
    TValue* found = const_cast<TValue*>(_rows.find(key));
    if (found == nullptr) throw std::logic_error("Key not found!");
    return *found;
}
template <class TKey, class TValue>
const TValue& SortedTableOnBinarySearchTree<TKey, TValue>::find(const TKey& key) const {
    const TValue* found = _rows.find(key);
    if (found == nullptr) throw std::logic_error("Key not found!");
    return *found;
}

template <class TKey, class TValue>
bool SortedTableOnBinarySearchTree<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableOnBinarySearchTree<TKey, TValue>::print(std::ostream& out) const {
    out << "SortedTableOnBinarySearchTree: \n";
    if (_rows.is_empty()) return;

    print_rec(_rows.get_root(), out);
}
template <class TKey, class TValue>
void SortedTableOnBinarySearchTree<TKey, TValue>::print_rec(BSTNode<TKey, TValue>* node, std::ostream& out) const {
    if (!node) return;
    print_rec(node->left, out);
    out << "| " << node->data.first << " | " << node->data.second << " |\n";
    print_rec(node->right, out);
}