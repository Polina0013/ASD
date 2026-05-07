// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_table\table.h"
#include "..\lib_binary_tree\binary_tree.h"
#include "..\lib_queue\queue.h"

template <class TKey, class TValue>
class UnsortedTableOnBinaryTree : public Table<TKey, TValue> {
    BinaryTree<TKey, TValue> _rows;
public:
    UnsortedTableOnBinaryTree() = default;
    UnsortedTableOnBinaryTree(const UnsortedTableOnBinaryTree&) = default;
    ~UnsortedTableOnBinaryTree() override = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue& find(const TKey&) override;
    const TValue& find(const TKey&) const override;

    bool is_empty() const noexcept override;
    void print(std::ostream& out) const override;
};

template <class TKey, class TValue>
void UnsortedTableOnBinaryTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TValue* is_exist = _rows.find(key);
    if (is_exist != nullptr) throw std::logic_error("The key is not unique!");
    _rows.insert(key, value);
}
template <class TKey, class TValue>
void UnsortedTableOnBinaryTree<TKey, TValue>::erase(const TKey& key) {
    _rows.erase(key);
}
template <class TKey, class TValue>
TValue& UnsortedTableOnBinaryTree<TKey, TValue>::find(const TKey& key) {
    TValue* found = const_cast<TValue*>(_rows.find(key));
    if (found == nullptr) throw std::logic_error("Key not found!");
    return *found;
}
template <class TKey, class TValue>
const TValue& UnsortedTableOnBinaryTree<TKey, TValue>::find(const TKey& key) const {
    const TValue* found = _rows.find(key);
    if (found == nullptr) throw std::logic_error("Key not found!");
    return *found;
}

template <class TKey, class TValue>
bool UnsortedTableOnBinaryTree<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableOnBinaryTree<TKey, TValue>::print(std::ostream& out) const {
    out << "UnsortedTableOnBinaryTree: \n";

    if (_rows.is_empty()) return;

    Queue<TNode<TKey, TValue>*> q;
    q.push(const_cast<TNode<TKey, TValue>*>(_rows.get_root()));

    /*Queue<const TNode<TKey, TValue>*> q;
    q.push(_rows.get_root());*/

    while (!q.is_empty()) {
        TNode<TKey, TValue>* current = q.head();
        q.pop();

        out << "| " << current->data.first << " | " << current->data.second << " |\n";

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}