// Copyright 2025 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

template <class T>
struct Node {
public:
    T value;
    Node<T>* next;
    Node<T>* prev;

    Node(T value, Node<T>* next = nullptr, Node<T>* prev = nullptr) : value(value), next(next), prev(prev) {}
};


template <class T>
class DoublyLinkedList {
    Node<T>* _head, * _tail;

public:
    // Doubly_Linked_List //
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList<T>& );

    ~DoublyLinkedList();

    bool is_empty();
    void push_front(const T&);
    void push_back(const T&);
    void insert_after(size_t, const T&);
    void insert_before(size_t, const T&);
    void insert(Node<T>*, const T&);
    void pop_front();
    void pop_back();
    void erase(size_t);
    void erase(Node<T>*);

    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
    bool operator==(const DoublyLinkedList<T>&) const;
    bool operator!=(const DoublyLinkedList<T>&) const;

    // Bidirectional_Iterator //
    class Iterator {
        Node<T>* _current;
        Node<T>* _tail;

    public:
        Iterator() : _current(nullptr), _tail(nullptr) {}
        Iterator(Node<T>* node, Node<T>* tail = nullptr) : _current(node), _tail(tail) {}

        Iterator& operator=(const Iterator& other) noexcept {
            _current = other._current;
            _tail = other._tail;
            return *this;
        }

        Iterator& operator++() {
            if (_current != nullptr) {
                _current = _current->next;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() {
            if (_current == nullptr) {
                _current = _tail;
            }
            else {
                _current = _current->prev;
            }
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const noexcept {
            return _current == other._current;
        }

        bool operator!=(const Iterator& other) const noexcept {
            return _current != other._current;
        }

        T& operator*() {
            if (_current == nullptr) throw std::logic_error("Dereferencing end iterator");
            return _current->value;
        }

        const T& operator*() const {
            if (_current == nullptr) throw std::logic_error("Dereferencing end iterator");
            return _current->value;
        }

        T* operator->() {
            if (_current == nullptr) throw std::logic_error("Accessing end iterator");
            return &(_current->value);
        }

        const T* operator->() const {
            if (_current == nullptr) throw std::logic_error("Accessing end iterator");
            return &(_current->value);
        }

        Iterator& operator+=(size_t n) {
            for (size_t i = 0; i < n && _current != nullptr; ++i) {
                _current = _current->next;
            }
            return *this;
        }

        Iterator& operator-=(size_t n) {
            for (size_t i = 0; i < n; ++i) {
                if (_current == nullptr) {
                    _current = _tail;
                }
                else {
                    _current = _current->prev;
                }
                if (_current == nullptr) break; 
            }
            return *this;
        }

        //Node<T>* node() const { return _current; }
        //Node<T>* get_tail() const { return _tail; }
    };

    Iterator begin() { return Iterator(_head, _tail); }
    Iterator end() { return Iterator(nullptr, _tail); }

    Iterator begin() const { return Iterator(_head, _tail); }
    Iterator end() const { return Iterator(nullptr, _tail); }

    Iterator rbegin() { return Iterator(_tail, _tail); }
    Iterator rend() { return Iterator(nullptr, _tail); }

};

template<class T>
DoublyLinkedList<T>::DoublyLinkedList() : _head(nullptr), _tail(nullptr) {}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : _head(nullptr), _tail(nullptr) {
    Node<T>* cur = other._head;
    while (cur != nullptr) {
        push_back(cur->value);
        cur = cur->next;
    }
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList() { while (!is_empty()) pop_front(); }

template<class T>
bool DoublyLinkedList<T>::is_empty() { return _head == nullptr; }

template<class T>
void DoublyLinkedList<T>::push_front(const T& value) {
    Node<T>* node = new Node<T>(value, _head, nullptr);
    if (_head != nullptr) {
        _head->prev = node;
    }
    _head = node;
    if (_tail == nullptr) {
        _tail = node;
    }
}

template<class T>
void DoublyLinkedList<T>::push_back(const T& value) {
    Node<T>* node = new Node<T>(value, nullptr, _tail);
    if (_tail != nullptr) {
        _tail->next = node;
    }
    _tail = node;
    if (_head == nullptr) {
        _head = node;
    }
}

template<class T>
void DoublyLinkedList<T>::insert_after(size_t pos, const T& value) {
    if (is_empty()) {
        if (pos == 0) push_front(value);
        else { throw std::logic_error("Position out of range"); }
        return;
    }

    Node<T>* cur = _head;
    size_t cur_pos = 0;

    while (cur != nullptr && cur_pos < pos) {
        cur_pos++;
        cur = cur->next;
    }

    if (cur == nullptr) { throw std::logic_error("Position out of range"); }

    insert(cur, value);
}

template<class T>
void DoublyLinkedList<T>::insert_before(size_t pos, const T& value) {
    if (pos == 0) {
        push_front(value);
        return;
    }

    if (is_empty()) { throw std::logic_error("Position out of range"); }

    Node<T>* prev_node = _head;
    size_t cur_pos = 0;

    while (prev_node != nullptr && cur_pos < pos - 1) {
        cur_pos++;
        prev_node = prev_node->next;
    }

    if (prev_node == nullptr) { throw std::logic_error("Position out of range"); }

    insert(prev_node, value);
}

template <class T>
void DoublyLinkedList<T>::insert(Node<T>* node, const T& val) {
    if (node == nullptr || is_empty()) { throw std::logic_error( "Invalid node or empty list"); }

    Node* new_node = new Node(val, node->next, node);
    node->next = new_node;

    if (new_node->next != nullptr) {
        new_node->next->prev = new_node;
    }

    if (node == _tail) {
        _tail = new_node;
    }
}

template<class T>
void DoublyLinkedList<T>::pop_front() {
    if (is_empty()) { throw std::logic_error("List is empty"); }

    Node* old_head = _head;
    _head = _head->next;
    if (_head != nullptr) {
        _head->prev = nullptr;
    }
    else {
        _tail = nullptr;
    }
    delete old_head;
}

template<class T>
void DoublyLinkedList<T>::pop_back() {
    if (is_empty()) { throw std::logic_error("List is empty"); }

    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        return;
    }

    Node* old_tail = _tail;
    _tail = _tail->prev;
    if (_tail != nullptr) {
        _tail->next = nullptr;
    }
    delete old_tail;
}

template<class T>
void DoublyLinkedList<T>::erase(size_t pos) {
    if (is_empty()) { throw std::logic_error("List is empty"); }

    if (pos == 0) {
        pop_front();
        return;
    }

    Node* current = _head;
    for (size_t i = 0; i < pos && current != nullptr; i++) {
        current = current->next;
    }

    if (current == nullptr) { throw std::logic_error("Position out of range"); }

    //if (current->prev != nullptr) { current->prev->next = current->next; }
    //if (current->next != nullptr) { current->next->prev = current->prev; }

    //if (current == _head) { _head = current->next; }
    //if (current == _tail) { _tail = current->prev; }

    //delete current;

    erase(current);
}

template<class T>
void DoublyLinkedList<T>::erase(Node<T>* node) {
    if (is_empty() || node == nullptr) { throw std::logic_error("Invalid arguments"); }

    if (node->prev != nullptr) { node->prev->next = node->next; }
    if (node->next != nullptr) { node->next->prev = node->prev; }

    if (node == _head) { _head = node->next; }
    if (node == _tail) { _tail = node->prev; }

    delete node;
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    if (this != &other) {
        while (!is_empty()) {
            pop_front();
        }

        Node<T>* cur = other._head;
        while (cur != nullptr) {
            push_back(cur->value);
            cur = cur->next;
        }
    }
    return *this;
}

template<class T>
bool DoublyLinkedList<T>::operator==(const DoublyLinkedList<T>& other) const {
    if (_head == nullptr && other._head == nullptr) {
        return true;
    }

    Node<T>* cur1 = _head;
    Node<T>* cur2 = other._head;

    while (cur1 != nullptr && cur2 != nullptr) {
        if (!(cur1->value == cur2->value)) {
            return false;
        }
        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    return cur1 == nullptr && cur2 == nullptr;
}

template<class T>
bool DoublyLinkedList<T>::operator!=(const DoublyLinkedList<T>& other) const {
    return !(*this == other);
}