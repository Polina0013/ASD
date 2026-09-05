// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_queue\queue.h"

enum Colour { red, black };

template <class TKey, class TValue>
struct RBNode {
    std::pair<TKey, TValue> data;
    RBNode *left, *right, *parent;
    Colour colour;

    RBNode();
    RBNode(const TKey& key, const TValue& value, RBNode* left = nullptr, RBNode* right = nullptr, RBNode* parent = nullptr, Colour colour = red);
    ~RBNode();
};

template <class TKey, class TValue>
RBNode<TKey, TValue>::RBNode() : left(nullptr), right(nullptr), parent(nullptr), colour(red) {}

template <class TKey, class TValue>
RBNode<TKey, TValue>::RBNode(const TKey& key, const TValue& value, RBNode* left, RBNode* right, RBNode* parent, Colour colour)
    : data(key, value), left(left), right(right), parent(parent), colour(colour) {}
template <class TKey, class TValue>
RBNode<TKey, TValue>::~RBNode() {}

// =============================================================

template <class TKey, class TValue>
class RBTree {
    RBNode<TKey, TValue>* _root;
public:
    RBTree();
    RBTree(const TKey& key, const TValue& value);
    ~RBTree();

    RBNode<TKey, TValue>* get_root() const noexcept;

    void insert(const TKey& key, const TValue& value);
    TValue* find(const TKey& key) const noexcept;
    void erase(const TKey& key);

    bool is_empty() const noexcept;
    void clear() noexcept;

    void print() const noexcept;
    void print_DLCR_rec(RBNode<TKey, TValue>* node) const;

private:
    void insert_case1(RBNode<TKey, TValue>* node);
    void insert_case2(RBNode<TKey, TValue>* node);
    void insert_case3(RBNode<TKey, TValue>* node);
    void insert_case4(RBNode<TKey, TValue>* node);
    void insert_case5(RBNode<TKey, TValue>* node);

    void fix_delete(RBNode<TKey, TValue>* node, RBNode<TKey, TValue>* parent, bool was_left);

    bool is_red(RBNode<TKey, TValue>* node) const noexcept;
    bool is_black(RBNode<TKey, TValue>* node) const noexcept;

    RBNode<TKey, TValue>* get_parent(RBNode<TKey, TValue>* node) const noexcept;
    RBNode<TKey, TValue>* get_uncle(RBNode<TKey, TValue>* node) const noexcept;
    RBNode<TKey, TValue>* get_grandparent(RBNode<TKey, TValue>* node) const noexcept;
    RBNode<TKey, TValue>* get_sibling(RBNode<TKey, TValue>* node) const noexcept;

    void left_rotate(RBNode<TKey, TValue>* node);
    void right_rotate(RBNode<TKey, TValue>* node);

    RBNode<TKey, TValue>* find_node(const TKey& key) const noexcept;
    RBNode<TKey, TValue>* find_replacing(const TKey& key) const noexcept;

    void replace_node(RBNode<TKey, TValue>* old_node, RBNode<TKey, TValue>* new_node);

    RBNode<TKey, TValue>* insert_BST(const TKey& key, const TValue& value);
    void clear_recursive(RBNode<TKey, TValue>* node) noexcept;
};

template <class TKey, class TValue>
RBTree<TKey, TValue>::RBTree() : _root(nullptr) {}
template <class TKey, class TValue>
RBTree<TKey, TValue>::RBTree(const TKey& key, const TValue& value)
    : _root(new RBNode<TKey, TValue>(key, value, nullptr, nullptr, nullptr, black)) {}
template <class TKey, class TValue>
RBTree<TKey, TValue>::~RBTree() {
    clear();
}

template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::get_root() const noexcept {
    return _root;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    RBNode<TKey, TValue>* inserted_node = insert_BST(key, value);

    if (inserted_node == nullptr) throw std::logic_error("Key already exists!");

    insert_case1(inserted_node);
}
template <class TKey, class TValue>
TValue* RBTree<TKey, TValue>::find(const TKey& key) const noexcept {
    if (is_empty()) return nullptr;
    
    RBNode<TKey, TValue>* node = find_node(key);

    if (node) return &node->data.second;
    return nullptr;
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::erase(const TKey& key) {
    RBNode<TKey, TValue>* node = find_node(key);
    if (node == nullptr) throw std::logic_error("Key not found for erase!");
    
    RBNode<TKey, TValue>* y = node;
    RBNode<TKey, TValue>* x = nullptr;
    bool y_original_colour = y->colour;

    RBNode<TKey, TValue>* parent_of_removed = nullptr;
    bool was_left = false;

    // 0 или 1 ребенок
    if (node->left == nullptr) {
        parent_of_removed = node->parent;
        was_left = (parent_of_removed != nullptr && parent_of_removed->left == node);

        x = node->right;
        replace_node(node, node->right);
    }
    else if (node->right == nullptr) {
        parent_of_removed = node->parent;
        was_left = (parent_of_removed != nullptr && parent_of_removed->left == node);

        x = node->left;
        replace_node(node, node->left);
    }
    // 2 ребенка
    else {
        y = find_replacing(node->data.first);

        parent_of_removed = y->parent;
        was_left = (parent_of_removed != nullptr && parent_of_removed->left == y);

        y_original_colour = y->colour;
        x = y->left;
        if (y->parent == node) {
            if (x != nullptr) x->parent = y;
        }
        else {
            replace_node(y, y->left);
            y->left = node->left;
            if (y->left) y->left->parent = y;
        }
        replace_node(node, y);
        y->right = node->right;
        if (y->right) y->right->parent = y;
        y->colour = node->colour;
    }

    RBNode<TKey, TValue>* fix_parent = nullptr;

    if (x != nullptr) fix_parent = x->parent;
    else fix_parent = parent_of_removed;

    delete node;

    if (y_original_colour == black) fix_delete(x, fix_parent, was_left);

    if (_root != nullptr) _root->colour = black;

    //// два ребенка
    //if (node->left != nullptr && node->right != nullptr) {
    //    RBNode<TKey, TValue>* replacing = find_replacing(key);
    //    node->data = replacing->data;
    //    node = replacing;
    //}

    //// только 0 или 1 ребенок
    //RBNode<TKey, TValue>* child = (node->left != nullptr) ? node->left : node->right;
    //RBNode<TKey, TValue>* parent = node->parent;
    //bool node_is_black = is_black(node);
    //bool was_left = (parent != nullptr && parent->left == node);

    //if (node_is_black && child == nullptr && parent != nullptr) {
    //    // черный лист
    //    delete_case1(node);

    //    if (was_left) parent->left = nullptr;
    //    else parent->right = nullptr;
    //    delete node;
    //}
    //else {
    //    replace_node(node, child);

    //    if (node_is_black) {
    //        if (child != nullptr && is_red(child)) {
    //            child->colour = black;
    //        }
    //        else if (child != nullptr) {
    //            delete_case1(child);
    //        }
    //    }

    //    delete node;
    //}

    //replace_node(node, child);

    //if (node_is_black) {                              // d
    //    if (child != nullptr && is_red(child)) {
    //        child->colour = black;
    //    }
    //    else if (child != nullptr) {
    //        delete_case1(child);
    //    }
    //    else if (parent != nullptr) {
    //        RBNode<TKey, TValue>* dummy = new RBNode<TKey, TValue>(key, TValue());
    //        dummy->colour = black;
    //        dummy->parent = parent;

    //        if (was_left) {
    //            parent->left = dummy;
    //        }
    //        else {
    //            parent->right = dummy;
    //        }

    //        delete_case1(dummy);

    //        if (dummy->parent) {
    //            if (dummy->parent->left == dummy) {
    //                dummy->parent->left = nullptr;
    //            }
    //            else {
    //                dummy->parent->right = nullptr;
    //            }
    //        }

    //        delete dummy;
    //    }
    //    
    //}
    //
    //delete node;

    //if (_root != nullptr) _root->colour = black;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::fix_delete(RBNode<TKey, TValue>* node, RBNode<TKey, TValue>* parent, bool was_left) {
    while (node != _root && is_black(node)) {
        bool isLeft;

        if (node != nullptr) {
            parent = get_parent(node);
            if (parent == nullptr) break;
            isLeft = (node == parent->left);
        }
        else {
            if (parent == nullptr) break;
            isLeft = was_left;
        }

        RBNode<TKey, TValue>* sibling = isLeft ? parent->right : parent->left;

        // Case 1: брат красный
        if (is_red(sibling)) {
            sibling->colour = black;
            parent->colour = red;

            if (isLeft) left_rotate(parent);
            else right_rotate(parent);

            sibling = isLeft ? parent->right : parent->left;
        }

        // Case 2: брат черный и оба племянника черные
        if (is_black(sibling ? sibling->left : nullptr) && is_black(sibling ? sibling->right : nullptr)) {
            if (sibling != nullptr) sibling->colour = red;

            node = parent;
            parent = get_parent(node);

            if (parent != nullptr) was_left = (node == parent->left);
            continue;
        }

        // Case 3: внешний племянник черный, внутренний красный
        if (isLeft) {
            if (is_black(sibling ? sibling->right : nullptr)) {
                if (sibling && sibling->left) sibling->left->colour = black;
                if (sibling) sibling->colour = red;

                if (sibling) right_rotate(sibling);

                sibling = parent->right;
            }
        }
        else {
            if (is_black(sibling ? sibling->left : nullptr)) {
                if (sibling && sibling->right) sibling->right->colour = black;
                if (sibling) sibling->colour = red;

                if (sibling) left_rotate(sibling);

                sibling = parent->left;
            }
        }

        // Case 4: внешний племянник красный
        if (sibling) sibling->colour = parent->colour;
        parent->colour = black;

        if (isLeft) {
            if (sibling && sibling->right) sibling->right->colour = black;
            left_rotate(parent);
        }
        else {
            if (sibling && sibling->left) sibling->left->colour = black;
            right_rotate(parent);
        }

        node = _root;
    }

    if (node != nullptr) node->colour = black;

    if (_root != nullptr) _root->colour = black;
}

template <class TKey, class TValue>
bool RBTree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}
//template <class TKey, class TValue>
//void RBTree<TKey, TValue>::clear() noexcept {
//    if (is_empty()) return;
//
//    Queue<RBNode<TKey, TValue>*> q;
//    q.push(_root);
//
//    while (!q.is_empty()) {
//        RBNode<TKey, TValue>* cur = q.head();
//        q.pop();
//
//        if (cur->left) {
//            q.push(cur->left);
//            cur->left = nullptr;
//        }
//        if (cur->right) {
//            q.push(cur->right);
//            cur->right = nullptr;
//        }
//
//        cur->parent = nullptr;
//        delete cur;
//    }
//
//    _root = nullptr;
//}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::clear() noexcept {
    clear_recursive(_root);
    _root = nullptr;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::clear_recursive(RBNode<TKey, TValue>* node) noexcept {
    if (node == nullptr) return;

    clear_recursive(node->left);
    clear_recursive(node->right);

    delete node;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::print() const noexcept {
    print_DLCR_rec(_root);
    std::cout << std::endl;
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::print_DLCR_rec(RBNode<TKey, TValue>* node) const {
    if (node == nullptr) return;

    print_DLCR_rec(node->left);
    std::cout << node->data.first << ":" << node->data.second;
    
    std::cout << "(";
    if (is_red(node)) std::cout << "R";
    else std::cout << "B";
    std::cout << ") ";
    print_DLCR_rec(node->right);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::insert_case1(RBNode<TKey, TValue>* node) {
    // Если узел это корень, то красим в черный
    if (node->parent == nullptr) {
        node->colour = black;
        _root = node;
    }
    else insert_case2(node);
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::insert_case2(RBNode<TKey, TValue>* node) {
    // Если родитель черный, то ок
    if (is_black(node->parent)) {
        return;
    }
    else insert_case3(node);
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::insert_case3(RBNode<TKey, TValue>* node) {
    // Если P и U красные, а G черный
    //                            /(...)  (балансируем, так как дед мог сломать)
    //     G                     G*
    //    / \                   / \
    //   P*  U*       ->       P   U
    //  /                     /
    // N*                    N*

    RBNode<TKey, TValue>* uncle = get_uncle(node);
    RBNode<TKey, TValue>* grandparent = get_grandparent(node);

    if (is_red(uncle)) {
        node->parent->colour = black;
        uncle->colour = black;
        grandparent->colour = red;

        insert_case1(grandparent);
    }
    else insert_case4(node);
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::insert_case4(RBNode<TKey, TValue>* node) {
    // Если P красный, G черный, U черный, а N внутренний ребенок
    //     G                     G
    //    / \                   / \
    //   P*  U        ->       N*  U
    //    \                   /
    //     N*                P*

    RBNode<TKey, TValue>* parent = node->parent;
    RBNode<TKey, TValue>* grandparent = get_grandparent(node);

    if (node == parent->right && parent == grandparent->left) {
        left_rotate(parent);
        node = node->left;
    }
    else if (node == parent->left && parent == grandparent->right) {
        right_rotate(parent);
        node = node->right;
    }

    insert_case5(node);
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::insert_case5(RBNode<TKey, TValue>* node) {
    // Если P красный, G черный, U черный, а N внешний ребенок
    //     G                     P
    //    / \                   / \
    //   P*  U        ->       N*  G*
    //  /                           \
    // N*                            U

    RBNode<TKey, TValue>* parent = node->parent;
    RBNode<TKey, TValue>* grandparent = get_grandparent(node);

    parent->colour = black;
    grandparent->colour = red;

    if (node == parent->left) right_rotate(grandparent);
    else left_rotate(grandparent);
}

//template <class TKey, class TValue>
//void RBTree<TKey, TValue>::delete_case1(RBNode<TKey, TValue>* node) {
//    // Если узел это корень, от только удаляем
//    if (node == nullptr || node->parent == nullptr) {
//        if (node != nullptr) node->colour = black;
//        return;
//    }
//
//    delete_case2(node);
//}
//template <class TKey, class TValue>
//void RBTree<TKey, TValue>::delete_case2(RBNode<TKey, TValue>* node) {
//    // Если S красный, то P и S меняют цвета и поворот P
//    RBNode<TKey, TValue>* sibling = get_sibling(node);
//
//    if (sibling != nullptr && is_red(sibling)) {
//        sibling->colour = black;
//        node->parent->colour = red;
//
//        if (node == node->parent->left) left_rotate(node->parent);
//        else right_rotate(node->parent);
//    }
//
//    delete_case3(node);
//}
//template <class TKey, class TValue>
//void RBTree<TKey, TValue>::delete_case3(RBNode<TKey, TValue>* node) {
//    // Если P, S, SL, SR черные, то перекрасить S в красный
//    RBNode<TKey, TValue>* sibling = get_sibling(node);
//
//    if (sibling != nullptr &&
//        is_black(node->parent) &&
//        is_black(sibling) &&
//        is_black(sibling->left) &&
//        is_black(sibling->right)) {
//
//        sibling->colour = red;
//
//        delete_case1(node->parent);
//    }
//    else {
//        delete_case4(node);
//    }
//}
//template <class TKey, class TValue>
//void RBTree<TKey, TValue>::delete_case4(RBNode<TKey, TValue>* node) {
//    // Если S, SL, SR черные, а P красный, то перекрасить P и S
//    RBNode<TKey, TValue>* sibling = get_sibling(node);
//
//    if (sibling != nullptr &&
//        is_red(node->parent) &&
//        is_black(sibling) &&
//        is_black(sibling->left) &&
//        is_black(sibling->right)) {
//
//        node->parent->colour = black;
//        sibling->colour = red;
//
//        return;
//    }
//    else {
//        delete_case5(node);
//    }
//}
//template <class TKey, class TValue>
//void RBTree<TKey, TValue>::delete_case5(RBNode<TKey, TValue>* node) {
//    // Если S черный, а внутр. племянник красный, то вращаем S и S и внутр. племянник меняют цвет
//    RBNode<TKey, TValue>* sibling = get_sibling(node);
//
//    if (sibling != nullptr && is_black(sibling)) {
//        if (node == node->parent->left &&
//            is_black(sibling->right) &&
//            is_red(sibling->left)) {
//
//            sibling->left->colour = black;
//            sibling->colour = red;
//
//            right_rotate(sibling);
//        }
//        else if (node == node->parent->right &&
//            is_black(sibling->left) &&
//            is_red(sibling->right)) {
//
//            sibling->right->colour = black;
//            sibling->colour = red;
//
//            left_rotate(sibling);
//        }
//    }
//
//    delete_case6(node);
//}
//template <class TKey, class TValue>
//void RBTree<TKey, TValue>::delete_case6(RBNode<TKey, TValue>* node) {
//    // Если S черный, а внеш. племянник красный, то вращаем P; P и S меняются цветами; перекрасить внеш. племянника в красный
//    RBNode<TKey, TValue>* sibling = get_sibling(node);
//
//    if (sibling != nullptr && is_black(sibling)) {
//        sibling->colour = node->parent->colour;
//        node->parent->colour = black;
//
//        if (node == node->parent->left) {
//            sibling->right->colour = black;
//            left_rotate(node->parent);
//        }
//        else {
//            sibling->left->colour = black;
//            right_rotate(node->parent);
//        }
//    }
//}

template <class TKey, class TValue>
bool RBTree<TKey, TValue>::is_red(RBNode<TKey, TValue>* node) const noexcept {
    return node != nullptr && node->colour == red;
}
template <class TKey, class TValue>
bool RBTree<TKey, TValue>::is_black(RBNode<TKey, TValue>* node) const noexcept {
    return node == nullptr || node->colour == black;
}

template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::get_parent(RBNode<TKey, TValue>* node) const noexcept {
    return (node != nullptr) ? node->parent : nullptr;
}
template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::get_grandparent(RBNode<TKey, TValue>* node) const noexcept {
    if (node && node->parent) return node->parent->parent;
    return nullptr;
}
template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::get_uncle(RBNode<TKey, TValue>* node) const noexcept {
    RBNode<TKey, TValue>* grandparent = get_grandparent(node);
    if (grandparent == nullptr) return nullptr;

    if (node->parent == grandparent->left) return grandparent->right;
    else return grandparent->left;
}
template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::get_sibling(RBNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr || node->parent == nullptr) return nullptr;

    if (node == node->parent->left) return node->parent->right;
    else return node->parent->left;
}


template <class TKey, class TValue>
void RBTree<TKey, TValue>::right_rotate(RBNode<TKey, TValue>* node) {
    //     G              right(G)          P
    //    / \                              / \
	//   P                                C   G
    //  / \                                  / \
    // C   X                                X

    RBNode<TKey, TValue>* G = node;
    RBNode<TKey, TValue>* P = G->left;
    RBNode<TKey, TValue>* X = P->right;

    RBNode<TKey, TValue>* parent = G->parent;

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
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::left_rotate(RBNode<TKey, TValue>* node) {
    //  G               left(G)             P
    // / \                                 / \
	//    P                               G   C
    //   / \                             / \
	//  X   C                               X

    RBNode<TKey, TValue>* G = node;
    RBNode<TKey, TValue>* P = G->right;
    RBNode<TKey, TValue>* X = P->left;

    RBNode<TKey, TValue>* parent = G->parent;

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
}

template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::find_node(const TKey& key) const noexcept {
    RBNode<TKey, TValue>* cur = _root;

    while (cur) {
        if (key == cur->data.first) return cur;
        else if (key < cur->data.first) cur = cur->left;
        else cur = cur->right;
    }

    return nullptr;
}
template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::find_replacing(const TKey& key) const noexcept {
    RBNode<TKey, TValue>* cur = find_node(key);
    if (!cur) return nullptr;

    if (cur->left) {
        cur = cur->left;
        while (cur->right) {
            cur = cur->right;
        }
        return cur;
    }

    return nullptr;  // лист
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::replace_node(RBNode<TKey, TValue>* old_node, RBNode<TKey, TValue>* new_node) {
    if (old_node->parent == nullptr) _root = new_node;
    else {
        if (old_node->parent->left == old_node) old_node->parent->left = new_node;
        else old_node->parent->right = new_node;
    }

    if (new_node != nullptr) new_node->parent = old_node->parent;
}

template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::insert_BST(const TKey& key, const TValue& value) {
    if (_root == nullptr) {
        _root = new RBNode<TKey, TValue>(key, value);
        _root->colour = black;
        return _root;
    }

    RBNode<TKey, TValue>* cur = _root;
    RBNode<TKey, TValue>* parent = nullptr;

    while (cur) {
        parent = cur;
        if (key < cur->data.first) cur = cur->left;
        else if (key > cur->data.first) cur = cur->right;
        else return nullptr;
    }

    RBNode<TKey, TValue>* new_node = new RBNode<TKey, TValue>(key, value);
    new_node->parent = parent;

    if (key < parent->data.first) parent->left = new_node;
    else parent->right = new_node;

    return new_node;
}