// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_queue\queue.h"

template <class TKey, class TValue>
struct BSTNode {
    std::pair<TKey, TValue> data;
    BSTNode *left, *right;

    BSTNode(const TKey& key, const TValue& value, BSTNode* left = nullptr, BSTNode* right = nullptr);
    ~BSTNode();
};

template <class TKey, class TValue>
BSTNode<TKey, TValue>::BSTNode(const TKey& key, const TValue& value, BSTNode* left, BSTNode* right)
    : data(key, value), left(left), right(right) {}
template <class TKey, class TValue>
BSTNode<TKey, TValue>::~BSTNode() {
    delete left;
    delete right;
}

template <class TKey, class TValue>
class BinarySearchTree {
    BSTNode<TKey, TValue>* _root;
public:
    BinarySearchTree();
    BinarySearchTree(const TKey& key, const TValue& value);
    ~BinarySearchTree();

    BSTNode<TKey, TValue>* get_root() const noexcept;

    void insert(const TKey& key, const TValue& value);
    TValue* find(const TKey& key) const noexcept;
    void erase(const TKey& key);

    bool is_empty() const noexcept;
    void clear() noexcept;

    void print() const noexcept;
    void print_DLCR_rec(BSTNode<TKey, TValue>* node) const;

private:
    BSTNode<TKey, TValue>* find_node(const TKey& key) const noexcept;
    BSTNode<TKey, TValue>* find_parent(const TKey& key) const noexcept;
    BSTNode<TKey, TValue>* find_replacing(const TKey& key) const noexcept;
};

template <class TKey, class TValue>
BinarySearchTree<TKey, TValue>::BinarySearchTree() : _root(nullptr) {}
template <class TKey, class TValue>
BinarySearchTree<TKey, TValue>::BinarySearchTree(const TKey& key, const TValue& value) : _root(new BSTNode<TKey, TValue>(key, value)) {}
template <class TKey, class TValue>
BinarySearchTree<TKey, TValue>::~BinarySearchTree() {
    clear();
}

template <class TKey, class TValue>
BSTNode<TKey, TValue>* BinarySearchTree<TKey, TValue>::get_root() const noexcept {
    return _root;
}

template <class TKey, class TValue>
void BinarySearchTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    BSTNode<TKey, TValue>* parent = find_parent(key);

    if (!parent) { _root = new BSTNode<TKey, TValue>(key, value); return; }

    if (parent == _root && _root->data.first == key) throw std::logic_error("Key already exists!");
    if (parent->left && parent->left->data.first == key) throw std::logic_error("Key already exists!");
    if (parent->right && parent->right->data.first == key) throw std::logic_error("Key already exists!");

    if (parent->data.first < key && !parent->right) { parent->right = new BSTNode<TKey, TValue>(key, value); return; }
    if (parent->data.first > key && !parent->left) { parent->left = new BSTNode<TKey, TValue>(key, value); return; }
}

template <class TKey, class TValue>
TValue* BinarySearchTree<TKey, TValue>::find(const TKey& key) const noexcept {
    BSTNode<TKey, TValue>* node = find_node(key);

    if (node) return &node->data.second;
    else return nullptr;
}
template <class TKey, class TValue>
void BinarySearchTree<TKey, TValue>::erase(const TKey& key) {
    BSTNode<TKey, TValue>* node = find_node(key);
    if (node == nullptr) throw std::logic_error("Key not found for erase!");

    if (node->left == nullptr && node->right == nullptr) {  // лист
        if (node == _root) {
            delete _root;
            _root = nullptr;
        }
        else {
            BSTNode<TKey, TValue>* node_parent = find_parent(key);
            if (node_parent->left == node) node_parent->left = nullptr;
            else node_parent->right = nullptr;
            delete node;
        }
    }
    else if (node->left == nullptr || node->right == nullptr) {  // один ребенок
        BSTNode<TKey, TValue>* node_child = (node->left != nullptr) ? node->left : node->right;
        if (node == _root) {
            _root = node_child;
        }
        else {
            BSTNode<TKey, TValue>* node_parent = find_parent(key);
            if (node_parent->left == node) node_parent->left = node_child;
            else node_parent->right = node_child;
        }

        node->left = node->right = nullptr;
        delete node;
    }
    else {
        BSTNode<TKey, TValue>* min_max_node = find_replacing(key);
        BSTNode<TKey, TValue>* min_max_node_parent = find_parent(min_max_node->data.first);

        node->data = min_max_node->data;

        if (min_max_node_parent->left == min_max_node) {
            if (min_max_node->left != nullptr) min_max_node_parent->left = min_max_node->left;
            else min_max_node_parent->left = min_max_node->right;
        }
        else if (min_max_node_parent->right == min_max_node) {
            if (min_max_node->left != nullptr) min_max_node_parent->right = min_max_node->left;
            else min_max_node_parent->right = min_max_node->right;
        }

        if (min_max_node->left) min_max_node->left = nullptr;
        if (min_max_node->right) min_max_node->right = nullptr;

        delete min_max_node;
    }
}

template <class TKey, class TValue>
bool BinarySearchTree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}
template <class TKey, class TValue>
void BinarySearchTree<TKey, TValue>::clear() noexcept {
    if (is_empty()) return;

    BSTNode<TKey, TValue>* cur = nullptr;
    Queue<BSTNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        cur = q.head();
        q.pop();

        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);

        cur->left = nullptr;
        cur->right = nullptr;
        delete cur;
    }

    _root = nullptr;
}

template <class TKey, class TValue>
void BinarySearchTree<TKey, TValue>::print() const noexcept {
    print_DLCR_rec(_root);
    std::cout << std::endl;
}
template <class TKey, class TValue>
void BinarySearchTree<TKey, TValue>::print_DLCR_rec(BSTNode<TKey, TValue>* node) const {   // O(N) ; по памяти: память на стэке вызовов + O(глубина дерева)=log2(N+1)
    if (node == nullptr) return;

    if (node->left) print_DLCR_rec(node->left);
    std::cout << node->data.first << ":" << node->data.second << " ";
    if (node->right) print_DLCR_rec(node->right);
}

template <class TKey, class TValue>
BSTNode<TKey, TValue>* BinarySearchTree<TKey, TValue>::find_node(const TKey& key) const noexcept {
    BSTNode<TKey, TValue>* cur = _root;

    while (cur) {
        if (key == cur->data.first) return cur;
        else if (key < cur->data.first) cur = cur->left;
        else cur = cur->right;
    }

    return nullptr;
}
template <class TKey, class TValue>
BSTNode<TKey, TValue>* BinarySearchTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
    if (is_empty()) return nullptr;

    if (_root->data.first == key) return _root;

    BSTNode<TKey, TValue>* cur = _root;

    while (1) {
        if (cur->data.first > key) {
            if (!cur->left) return cur;   // parent insert
            if (cur->left->data.first == key) return cur;   // parent find_elem, erase
            cur = cur->left;
        }
        else {
            if (!cur->right) return cur;
            if (cur->right->data.first == key) return cur;
            cur = cur->right;
        }
    }
}
template <class TKey, class TValue>
BSTNode<TKey, TValue>* BinarySearchTree<TKey, TValue>::find_replacing(const TKey& key) const noexcept {
    BSTNode<TKey, TValue>* cur = find_node(key);
    if (!cur) return nullptr;

    if (cur->left) {
        cur = cur->left;
        while (cur->right) cur = cur->right;
        return cur;
    }
    //else if (cur->right) {
    //    cur = cur->right;
    //    while (cur->left) cur = cur->left;
    //    return cur;
    //}

    return nullptr;  // лист
}