// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_queue\queue.h"

template <class TKey, class TValue>
struct AVLNode {
    std::pair<TKey, TValue> data;
    size_t height;
    AVLNode *left, *right, *parent;


    AVLNode(const TKey& key, const TValue& value, const size_t& height = 1, AVLNode* left = nullptr, AVLNode* right = nullptr, AVLNode* parent = nullptr);
    ~AVLNode();
};

template <class TKey, class TValue>
AVLNode<TKey, TValue>::AVLNode(const TKey& key, const TValue& value, const size_t& height, AVLNode* left, AVLNode* right, AVLNode* parent)
    : data(key, value), height(height), left(left), right(right), parent(parent) {}
template <class TKey, class TValue>
AVLNode<TKey, TValue>::~AVLNode() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

// =============================================================

template <class TKey, class TValue>
class AVLTree {
    AVLNode<TKey, TValue>* _root;
public:
    AVLTree();
    AVLTree(const TKey& key, const TValue& value);
    ~AVLTree();

    AVLNode<TKey, TValue>* get_root() const noexcept;
    size_t height(AVLNode<TKey, TValue>* node);

    void insert(const TKey& key, const TValue& value);
    TValue* find(const TKey& key) const noexcept;
    void erase(const TKey& key);

    bool is_empty() const noexcept;
    void clear() noexcept;

    void print() const noexcept;
    void print_DLCR_rec(AVLNode<TKey, TValue>* node) const;

private:
    void left_rotate(AVLNode<TKey, TValue>* node);
    void right_rotate(AVLNode<TKey, TValue>* node);
    void RR(AVLNode<TKey, TValue>* node);
    void LL(AVLNode<TKey, TValue>* node);
    void RL(AVLNode<TKey, TValue>* node);
    void LR(AVLNode<TKey, TValue>* node);
    AVLNode<TKey, TValue>* recover_balance(AVLNode<TKey, TValue>* node);
    void recalc_height(AVLNode<TKey, TValue>* node);
    int calc_balance(AVLNode<TKey, TValue>* node);

    AVLNode<TKey, TValue>* find_node(const TKey& key) const noexcept;

    AVLNode<TKey, TValue>* find_replacing(const TKey& key) const noexcept;
    AVLNode<TKey, TValue>* insert_BST(const TKey& key, const TValue& value);
    AVLNode<TKey, TValue>* erase_BST(const TKey& key);
};

template <class TKey, class TValue>
AVLTree<TKey, TValue>::AVLTree() : _root(nullptr) {}
template <class TKey, class TValue>
AVLTree<TKey, TValue>::AVLTree(const TKey& key, const TValue& value) : _root(new AVLNode<TKey, TValue>(key, value)) {}
template <class TKey, class TValue>
AVLTree<TKey, TValue>::~AVLTree() {
    clear();
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::get_root() const noexcept {
    return _root;
}

template <class TKey, class TValue>
size_t AVLTree<TKey, TValue>::height(AVLNode<TKey, TValue>* node) {
    return node ? node->height : 0;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    AVLNode<TKey, TValue>* inserted_node = insert_BST(key, value);

    if (inserted_node == nullptr) throw std::logic_error("Key already exists!");

    AVLNode<TKey, TValue>* current = inserted_node->parent;
    while (current) {
        recalc_height(current);
        current = recover_balance(current);
    }
}

template <class TKey, class TValue>
TValue* AVLTree<TKey, TValue>::find(const TKey& key) const noexcept {
    AVLNode<TKey, TValue>* node = find_node(key);

    if (node) return &node->data.second;
    return nullptr;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::erase(const TKey& key) {
    AVLNode<TKey, TValue>* current = erase_BST(key);

    while (current) {
        recalc_height(current);
        current = recover_balance(current);
    }

    if (_root) {
        _root->parent = nullptr;
    }
}

template <class TKey, class TValue>
bool AVLTree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::clear() noexcept {
    if (is_empty()) return;

    Queue<AVLNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        AVLNode<TKey, TValue>* cur = q.head();
        q.pop();

        if (cur->left) {
            q.push(cur->left);
            cur->left = nullptr;
        }
        if (cur->right) {
            q.push(cur->right);
            cur->right = nullptr;
        }

        cur->parent = nullptr;
        delete cur;
    }

    _root = nullptr;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::print() const noexcept {
    print_DLCR_rec(_root);
    std::cout << std::endl;
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::print_DLCR_rec(AVLNode<TKey, TValue>* node) const {
    if (node == nullptr) return;

    print_DLCR_rec(node->left);
    std::cout << node->data.first << ":" << node->data.second << " ";
    print_DLCR_rec(node->right);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::right_rotate(AVLNode<TKey, TValue>* node) {
    // LL, (LR)
    //     G              right(G)          P
    //    / \                              / \
	//   P                                C   G
    //  / \                                  / \
    // C   X                                X

    // RL
    //   G                             G           left(G)       C
    //    \                             \                       / \
	//     P       right(P)              C                    G     P
    //    /                             / \                  / \   / \
	//   C                             X   P                    X Y
    //  / \                               / \
    // X   Y                             Y

    // LR
    //   G     left(P)                   G        right(G)       C
    //  /                               /                       / \
	// P                               C                      P     G
    //  \                             / \                    / \   / \
    //   C                           P   Y                      X Y
    //  / \                         / \
    // X   Y                           X


    // для LL и LR
    AVLNode<TKey, TValue>* G = node;
    AVLNode<TKey, TValue>* P = G->left;
    AVLNode<TKey, TValue>* X = P->right;

    AVLNode<TKey, TValue>* parent = G->parent;

    G->left = X;
    if (X) X->parent = G;

    P->right = G;
    G->parent = P;
    P->parent = parent;

    if (parent) {
        if (parent->left == G) parent->left = P;
        else parent->right = P;
    }
    else _root = P;

    recalc_height(G);
    recalc_height(P);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::left_rotate(AVLNode<TKey, TValue>* node) {
    // RR, (RL)
    //  G               left(G)             P
    // / \                                 / \
	//    P                               G   C
    //   / \                             / \
	//  X   C                               X

    // RL
    //   G                             G           left(G)       C
    //    \                             \                       / \
	//     P       right(P)              C                    G     P
    //    /                             / \                  / \   / \
	//   C                             X   P                    X Y
    //  / \                               / \
    // X   Y                             Y

    // LR
    //   G     left(P)                   G        right(G)       C
    //  /                               /                       / \
	// P                               C                      P     G
    //  \                             / \                    / \   / \
    //   C                           P   Y                      X Y
    //  / \                         / \
    // X   Y                           X



    // для RR и RL
    AVLNode<TKey, TValue>* G = node;
    AVLNode<TKey, TValue>* P = G->right;
    AVLNode<TKey, TValue>* X = P->left;

    AVLNode<TKey, TValue>* parent = G->parent;

    G->right = X;
    if (X) X->parent = G;
    
    P->left = G;
    G->parent = P;
    P->parent = parent;

    if (parent) {
        if (parent->left == G) parent->left = P;
        else parent->right = P;
    }
    else _root = P;

    recalc_height(G);
    recalc_height(P);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::RR(AVLNode<TKey, TValue>* node) {
    // RR
    //  G               left(G)             P
    // / \                                 / \
	//    P                               G   C
    //   / \                             / \
	//  X   C                               X

    AVLNode<TKey, TValue>* G = node;
    left_rotate(G);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::LL(AVLNode<TKey, TValue>* node) {
    //     G (+2)     G - сломал баланс     right(G)      P
    //    /                                              / \
	//   P                                              C   G
    //  /
	// C

    AVLNode<TKey, TValue>* G = node;
    right_rotate(G);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::RL(AVLNode<TKey, TValue>* node) {
    // G (+2)                        G           left(G)         C
    //  \                             \                         / \
	//   P      right(P)               C                       G   P
    //  /                               \
	// C                                 P

    AVLNode<TKey, TValue>* G = node;
    AVLNode<TKey, TValue>* P = G->right;
    right_rotate(P);
    left_rotate(G);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::LR(AVLNode<TKey, TValue>* node) {
    //   G (+2)                        G           right(G)         C
    //  /                             /                            / \
	// P          left(P)            C                            P   G
    //  \                           /
	//   C                         P

    AVLNode<TKey, TValue>* G = node;
    AVLNode<TKey, TValue>* P = G->left;
    left_rotate(P);
    right_rotate(G);
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::recover_balance(AVLNode<TKey, TValue>* node) {
    if (!node) return nullptr;
    
    recalc_height(node);
    int balance = calc_balance(node);

    if (balance == 2) {
        if (calc_balance(node->right) < 0) RL(node);
        else RR(node);
        return node->parent ? node->parent->parent : nullptr;
    }
    else if (balance == -2) {
        if (calc_balance(node->left) > 0) LR(node);
        else LL(node);
        return node->parent ? node->parent->parent : nullptr;
    }

    return node->parent;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::recalc_height(AVLNode<TKey, TValue>* node) {
    size_t hl = height(node->left);
    size_t hr = height(node->right);
    node->height = (hl > hr ? hl : hr) + 1;
}

template <class TKey, class TValue>
int AVLTree<TKey, TValue>::calc_balance(AVLNode<TKey, TValue>* node) {
    return height(node->right) - height(node->left);
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find_node(const TKey& key) const noexcept {
    AVLNode<TKey, TValue>* cur = _root;

    while (cur) {
        if (key == cur->data.first) return cur;
        else if (key < cur->data.first) cur = cur->left;
        else cur = cur->right;
    }

    return nullptr;
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find_replacing(const TKey& key) const noexcept {
    AVLNode<TKey, TValue>* cur = find_node(key);
    if (!cur) return nullptr;

    if (cur->left) {
        cur = cur->left;
        while (cur->right) {
            cur = cur->right;
        }
        return cur;
    }

    if (cur->right) {
        cur = cur->right;
        while (cur->left) {
            cur = cur->left;
        }
        return cur;
    }

    return nullptr;  // лист
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::insert_BST(const TKey& key, const TValue& value) {
    if (_root == nullptr) {
        _root = new AVLNode<TKey, TValue>(key, value);
        return _root;
    }

    AVLNode<TKey, TValue>* cur = _root;
    AVLNode<TKey, TValue>* parent = nullptr;

    while (cur) {
        parent = cur;
        if (key < cur->data.first) cur = cur->left;
        else if (key > cur->data.first) cur = cur->right;
        else return nullptr;
    }

    AVLNode<TKey, TValue>* new_node = new AVLNode<TKey, TValue>(key, value);
    new_node->parent = parent;

    if (key < parent->data.first) parent->left = new_node;
    else parent->right = new_node;

    return new_node;
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::erase_BST(const TKey& key) {
    AVLNode<TKey, TValue>* node = find_node(key);
    if (node == nullptr) throw std::logic_error("Key not found for erase!");

    AVLNode<TKey, TValue>* parent_for_balance = nullptr;

    if (node->left == nullptr && node->right == nullptr) {  // лист
        parent_for_balance = node->parent;

        if (node == _root) {
            delete _root;
            _root = nullptr;
        }
        else {
            AVLNode<TKey, TValue>* node_parent = node->parent;
            if (node_parent->left == node) node_parent->left = nullptr;
            else node_parent->right = nullptr;
            delete node;
        }
    }
    else if (node->left == nullptr || node->right == nullptr) {  // один ребенок
        AVLNode<TKey, TValue>* node_child = (node->left != nullptr) ? node->left : node->right;
        parent_for_balance = node->parent;

        if (node == _root) {
            _root = node_child;
            node_child->parent = nullptr;
        }
        else {
            AVLNode<TKey, TValue>* node_parent = node->parent;
            if (node_parent->left == node) node_parent->left = node_child;
            else node_parent->right = node_child;
            node_child->parent = node_parent;
        }

        node->left = node->right = nullptr;
        delete node;
    }
    else {
        AVLNode<TKey, TValue>* replacing = find_replacing(key);
        if (!replacing) return nullptr;

        parent_for_balance = replacing->parent;
        node->data = replacing->data;

        if (replacing->parent->left == replacing) {
            replacing->parent->left = replacing->left;
            if (replacing->left) replacing->left->parent = replacing->parent;
        }
        else {
            replacing->parent->right = replacing->right;
            if (replacing->right) replacing->right->parent = replacing->parent;
        }
        delete replacing;
    }
    return parent_for_balance;
}
