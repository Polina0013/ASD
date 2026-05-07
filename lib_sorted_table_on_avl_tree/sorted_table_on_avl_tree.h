// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_table\table.h"
#include "..\lib_avl_tree\avl_tree.h"

template <class TKey, class TValue>
class SortedTableOnAVLTree : public Table<TKey, TValue> {
    AVLTree<TKey, TValue> _rows;
public:
    SortedTableOnAVLTree() = default;
    SortedTableOnAVLTree(const SortedTableOnAVLTree&) = default;
    ~SortedTableOnAVLTree() override = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue& find(const TKey&) override;
    const TValue& find(const TKey&) const override;

    bool is_empty() const noexcept override;
    void print(std::ostream& out) const override;
    void print_rec(AVLNode<TKey, TValue>* node, std::ostream& out) const;
};

template <class TKey, class TValue>
void SortedTableOnAVLTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    _rows.insert(key, value);
}
template <class TKey, class TValue>
void SortedTableOnAVLTree<TKey, TValue>::erase(const TKey& key) {
    _rows.erase(key);
}
template <class TKey, class TValue>
TValue& SortedTableOnAVLTree<TKey, TValue>::find(const TKey& key) {
    TValue* found = const_cast<TValue*>(_rows.find(key));
    if (found == nullptr) throw std::logic_error("Key not found!");
    return *found;
}
template <class TKey, class TValue>
const TValue& SortedTableOnAVLTree<TKey, TValue>::find(const TKey& key) const {
    const TValue* found = _rows.find(key);
    if (found == nullptr) throw std::logic_error("Key not found!");
    return *found;
}

template <class TKey, class TValue>
bool SortedTableOnAVLTree<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableOnAVLTree<TKey, TValue>::print(std::ostream& out) const {
    out << "SortedTableOnAVLTree: \n";
    if (_rows.is_empty()) return;

    print_rec(_rows.get_root(), out);
}
template <class TKey, class TValue>
void SortedTableOnAVLTree<TKey, TValue>::print_rec(AVLNode<TKey, TValue>* node, std::ostream& out) const {
    if (!node) return;
    print_rec(node->left, out);
    out << "| " << node->data.first << " | " << node->data.second << " |\n";
    print_rec(node->right, out);
}