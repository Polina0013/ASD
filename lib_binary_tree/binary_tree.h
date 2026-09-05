// Copyright 2026 Pozdnova Polina
/*
#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>
#include "..\lib_queue\queue.h"

template <class TKey, class TValue>
struct TNode {
    std::pair<TKey, TValue> data;
    TNode* left;
    TNode* right;

    TNode(const TKey& key, const TValue& value, TNode* left = nullptr, TNode* right = nullptr)
        : data(key, value), left(left), right(right) {}

    ~TNode() {
        delete left;
        delete right;
    }
};

template <class TKey, class TValue>
class BinaryTree {
public:
    BinaryTree() : _root(nullptr) {}
    explicit BinaryTree(const TKey& key, const TValue& value) : _root(new TNode<TKey, TValue>(key, value)) {}
    ~BinaryTree() { clear(); }

    // Копирование
    BinaryTree(const BinaryTree& other) : _root(nullptr) {
        if (other._root) {
            _root = copy_node(other._root);
        }
    }

    // Перемещение
    BinaryTree(BinaryTree&& other) noexcept : _root(other._root) {
        other._root = nullptr;
    }

    // Оператор присваивания копированием
    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            clear();
            if (other._root) {
                _root = copy_node(other._root);
            }
        }
        return *this;
    }

    // Оператор присваивания перемещением
    BinaryTree& operator=(BinaryTree&& other) noexcept {
        if (this != &other) {
            clear();
            _root = other._root;
            other._root = nullptr;
        }
        return *this;
    }

    const TNode<TKey, TValue>* get_root() const noexcept { return _root; }
    TNode<TKey, TValue>* get_root() noexcept { return _root; }

    void insert(const TKey& key, const TValue& value);
    TValue* find(const TKey& key) const;
    void erase(const TKey& key);

    bool is_empty() const noexcept { return _root == nullptr; }
    void clear() noexcept { delete _root; _root = nullptr; }

    void print_W() const;      // обход в ширину (level-order)
    void print_DCLR() const;   // прямой (pre-order)
    void print_DLCR() const;   // симметричный (in-order)
    void print_DLRC() const;   // обратный (post-order)

private:
    TNode<TKey, TValue>* _root;

    static TNode<TKey, TValue>* copy_node(TNode<TKey, TValue>* node) {
        if (!node) return nullptr;
        return new TNode<TKey, TValue>(node->data.first, node->data.second,
            copy_node(node->left), copy_node(node->right));
    }

    void print_DCLR_rec(TNode<TKey, TValue>* node) const;
    void print_DLCR_rec(TNode<TKey, TValue>* node) const;
    void print_DLRC_rec(TNode<TKey, TValue>* node) const;
};

// ---------------------- insert ----------------------
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TNode<TKey, TValue>* node = new TNode<TKey, TValue>(key, value);
    if (is_empty()) {
        _root = node;
        return;
    }

    Queue<TNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        auto* cur = q.head();
        q.pop();

        if (!cur->left) {
            cur->left = node;
            return;
        }
        if (!cur->right) {
            cur->right = node;
            return;
        }
        q.push(cur->left);
        q.push(cur->right);
    }
}

// ---------------------- find ----------------------
template <class TKey, class TValue>
TValue* BinaryTree<TKey, TValue>::find(const TKey& key) const {
    if (is_empty()) return nullptr;

    Queue<TNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        auto* cur = q.head();
        q.pop();

        if (cur->data.first == key)
            return &(cur->data.second);

        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return nullptr;
}

// ---------------------- erase ----------------------
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::erase(const TKey& key) {
    if (is_empty())
        throw std::logic_error("The tree is empty!");

    TNode<TKey, TValue>* erase_node = nullptr;
    TNode<TKey, TValue>* last_parent = nullptr;
    TNode<TKey, TValue>* last = nullptr;

    Queue<TNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        auto* cur = q.head();
        q.pop();

        if (cur->data.first == key)
            erase_node = cur;

        last = cur;

        if (cur->left) {
            q.push(cur->left);
            last_parent = cur;
        }
        if (cur->right) {
            q.push(cur->right);
            last_parent = cur;
        }
    }

    if (!erase_node)
        throw std::logic_error("Key not found for erase!");

    // Если удаляемый узел совпадает с последним узлом
    if (erase_node == last) {
        if (last_parent) {
            if (last_parent->left == last)
                last_parent->left = nullptr;
            else
                last_parent->right = nullptr;
        }
        else {
            _root = nullptr;
        }
        delete last;
        return;
    }

    // Заменяем данные удаляемого узла данными последнего узла
    erase_node->data = last->data;

    // Удаляем последний узел
    if (last_parent->left == last) {
        delete last_parent->left;
        last_parent->left = nullptr;
    }
    else {
        delete last_parent->right;
        last_parent->right = nullptr;
    }
}

// ---------------------- print_W (level-order) ----------------------
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_W() const {
    if (is_empty()) return;

    Queue<TNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        auto* cur = q.head();
        q.pop();

        std::cout << cur->data.first << ":" << cur->data.second << " ";

        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    std::cout << std::endl;
}

// ---------------------- DCLR (pre-order) ----------------------
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DCLR() const {
    print_DCLR_rec(_root);
    std::cout << std::endl;
}

template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DCLR_rec(TNode<TKey, TValue>* node) const {
    if (!node) return;
    std::cout << node->data.first << ":" << node->data.second << " ";
    print_DCLR_rec(node->left);
    print_DCLR_rec(node->right);
}

// ---------------------- DLCR (in-order) ----------------------
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DLCR() const {
    print_DLCR_rec(_root);
    std::cout << std::endl;
}

template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DLCR_rec(TNode<TKey, TValue>* node) const {
    if (!node) return;
    print_DLCR_rec(node->left);
    std::cout << node->data.first << ":" << node->data.second << " ";
    print_DLCR_rec(node->right);
}

// ---------------------- DLRC (post-order) ----------------------
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DLRC() const {
    print_DLRC_rec(_root);
    std::cout << std::endl;
}

template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DLRC_rec(TNode<TKey, TValue>* node) const {
    if (!node) return;
    print_DLRC_rec(node->left);
    print_DLRC_rec(node->right);
    std::cout << node->data.first << ":" << node->data.second << " ";
}
*/




#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_queue\queue.h"

template <class TKey, class TValue>
struct TNode {
    std::pair<TKey, TValue> data;
    TNode *left, *right;

    TNode(const TKey& key, const TValue& value, TNode* left = nullptr, TNode* right = nullptr);
    ~TNode();
};

template <class TKey, class TValue>
TNode<TKey, TValue>::TNode(const TKey& key, const TValue& value, TNode* left, TNode* right)
    : data(key, value), left(left), right(right) {}
template <class TKey, class TValue>
TNode<TKey, TValue>::~TNode() {
    delete left;
    delete right;
}

template <class TKey, class TValue>
class BinaryTree {
    TNode<TKey, TValue>* _root;
public:
    BinaryTree();
    BinaryTree(const TKey& key, const TValue& value);
    ~BinaryTree();

    const TNode<TKey, TValue>* get_root() const noexcept;
    TNode<TKey, TValue>* get_root() noexcept;

    void insert(const TKey& key, const TValue& value) noexcept;
    TValue* find(const TKey& key) const noexcept;
    void erase(const TKey& key);

    bool is_empty() const noexcept;
    void clear() noexcept;

    void print_W() const noexcept;
    void print_DLCR() const noexcept;
    void print_DLRC() const noexcept;
    void print_DCLR() const noexcept;

    void print_DLCR_rec(TNode<TKey, TValue>* node) const;
    void print_DLRC_rec(TNode<TKey, TValue>* node) const;
    void print_DCLR_rec(TNode<TKey, TValue>* node) const;
};

template <class TKey, class TValue>
BinaryTree<TKey, TValue>::BinaryTree() : _root(nullptr) {}
template <class TKey, class TValue>
BinaryTree<TKey, TValue>::BinaryTree(const TKey& key, const TValue& value) : _root(new TNode<TKey, TValue>(key, value)) {}
template <class TKey, class TValue>
BinaryTree<TKey, TValue>::~BinaryTree() {
    clear();
}

template <class TKey, class TValue>
const TNode<TKey, TValue>* BinaryTree<TKey, TValue>::get_root() const noexcept { return _root; }
template <class TKey, class TValue>
TNode<TKey, TValue>* BinaryTree<TKey, TValue>::get_root() noexcept { return _root; }

template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::insert(const TKey& key, const TValue& value) noexcept {
    TNode<TKey, TValue>* node = new TNode<TKey, TValue>(key, value);
    if (is_empty()) { _root = node; return; }

    TNode<TKey, TValue>* cur = nullptr;
    Queue<TNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        cur = q.head();
        q.pop();
        if (!cur->left) { cur->left = node; return; }
        if (!cur->right) { cur->right = node; return; }

        q.push(cur->left);
        q.push(cur->right);
    }
}
template <class TKey, class TValue>
TValue* BinaryTree<TKey, TValue>::find(const TKey& key) const noexcept {
    if (is_empty()) return nullptr;

    TNode<TKey, TValue>* cur = nullptr;
    Queue<TNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        cur = q.head();
        q.pop();

        if (cur->data.first == key) return &(cur->data.second);

        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }

    return nullptr;
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::erase(const TKey& key) {
    if (is_empty()) throw std::logic_error("The tree is empty!");

    TNode<TKey, TValue>* cur = nullptr;

    TNode<TKey, TValue>* erase_node = nullptr;

    TNode<TKey, TValue>* last_parent = nullptr;
    TNode<TKey, TValue>* last = nullptr;

    Queue<TNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        cur = q.head();
        q.pop();

        if (cur->data.first == key) erase_node = cur;
        last = cur;

        if (cur->left) {
            q.push(cur->left);
            last_parent = cur;
        }
        if (cur->right) {
            q.push(cur->right);
            last_parent = cur;
        }
    }

    if (!erase_node) throw std::logic_error("Key not found for erase!");

    if (erase_node == _root && !_root->left && !_root->right) {
        delete _root;
        _root = nullptr;
        return;
    }

    erase_node->data = last->data;

    if (last_parent->left == last) {
        delete last_parent->left;
        last_parent->left = nullptr;
    }
    else if (last_parent->right == last) {
        delete last_parent->right;
        last_parent->right = nullptr;
    }

}

template <class TKey, class TValue>
bool BinaryTree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::clear() noexcept {
    if (is_empty()) return;

    TNode<TKey, TValue>* cur = nullptr;
    Queue<TNode<TKey, TValue>*> q;
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
void BinaryTree<TKey, TValue>::print_W() const noexcept {      // O(N) ; по памяти: O(1/2(N+1)) = O(N)
    if (is_empty()) return;

    Queue<TNode<TKey, TValue>*> q;
    TNode<TKey, TValue>* cur = nullptr;
    q.push(_root);

    while (!q.is_empty()) {
        cur = q.head();
        q.pop();

        std::cout << cur->data.first << ":" << cur->data.second << " ";

        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    std::cout << std::endl;
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DCLR() const noexcept {
    print_DCLR_rec(_root);
    std::cout << std::endl;
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DLCR() const noexcept {
    print_DLCR_rec(_root);
    std::cout << std::endl;
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DLRC() const noexcept {
    print_DLRC_rec(_root);
    std::cout << std::endl;
}

template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DCLR_rec(TNode<TKey, TValue>* node) const {   // O(N) ; по памяти: память на стэке вызовов + O(глубина дерева)=log2(N+1)
    if (node == nullptr) return;

    std::cout << node->data.first << ":" << node->data.second << " ";
    if (node->left) print_DCLR_rec(node->left);
    if (node->right) print_DCLR_rec(node->right);
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DLCR_rec(TNode<TKey, TValue>* node) const {   // O(N) ; по памяти: память на стэке вызовов + O(глубина дерева)=log2(N+1)
    if (node == nullptr) return;

    if (node->left) print_DLCR_rec(node->left);
    std::cout << node->data.first << ":" << node->data.second << " ";
    if (node->right) print_DLCR_rec(node->right);
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DLRC_rec(TNode<TKey, TValue>* node) const {   // O(N) ; по памяти: память на стэке вызовов + O(глубина дерева)=log2(N+1)
    if (node == nullptr) return;

    if (node->left) print_DLRC_rec(node->left);
    if (node->right) print_DLRC_rec(node->right);
    std::cout << node->data.first << ":" << node->data.second << " ";
}