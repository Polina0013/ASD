// Copyright 2025 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>


template <class T>
struct Node {
public:
    T value;
    Node<T>* next;

    Node(T value, Node<T>* next = nullptr) : value(value), next(next) {}
};


template <class T>
class List {
    Node<T>* _head, * _tail;

public:
    // List //
    List();
    List(const List<T>& );

    ~List();

    T& front();
    T& back();
    bool is_empty();
    bool is_empty() const;
    void push_front(const T&);
    void push_back(const T&);
    void insert_after(size_t, const T&);
    void insert(Node<T>*, const T&);
    void pop_front();
    void pop_back();
    void erase(size_t);
    void erase(Node<T>*);

    List<T>& operator=(const List<T>& other);
    bool operator==(const List<T>&) const;
    bool operator!=(const List<T>&) const;

    // Iterator //
    class Iterator {
        Node<T>* _current;

    public:
        Iterator() : _current(nullptr) {}
        Iterator(Node<T>* node) : _current(node) {}

        Node<T>* get_node() const {
            return _current;
        }

        Iterator& operator=(const Iterator& other) noexcept {
            _current = other._current;
            return *this;
        }

        Iterator& operator++() noexcept {
            if (_current != nullptr) {
                _current = _current->next;
            }
            return *this;
        }

        Iterator operator++(int) noexcept {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        bool operator==(const Iterator& other) const noexcept {
            return _current == other._current;
        }

        bool operator!=(const Iterator& other) const noexcept {
            return _current != other._current;
        }

        T& operator*() {
            if (_current == nullptr) { throw std::logic_error("Dereferencing end iterator"); }
            return _current->value;
        }

        T* operator->() {
            if (_current == nullptr) { throw std::logic_error("Accessing end iterator"); }
            return &(_current->value);
        }

        Iterator& operator+=(size_t n) {
            for (size_t i = 0; i < n && _current != nullptr; ++i) {
                _current = _current->next;
            }
            return *this;
        }
    };

    Iterator begin() { return Iterator(_head); }
    Iterator end() { return Iterator(nullptr); }

    Iterator begin() const { return Iterator(_head); }
    Iterator end() const { return Iterator(nullptr); }

};

template<class T>
List<T>::List() : _head(nullptr), _tail(nullptr) {}

template<class T>
List<T>::List(const List<T>& other) : _head(nullptr), _tail(nullptr) {
    Node<T>* cur = other._head;
    while (cur != nullptr) {
        push_back(cur->value);
        cur = cur->next;
    }
}

template<class T>
List<T>::~List() { while (!is_empty()) pop_front(); }

template<class T>
T& List<T>::front() {
    if (is_empty()) throw std::logic_error("List is empty");
    return _head->value;
}

template<class T>
T& List<T>::back() {
    if (is_empty()) throw std::logic_error("List is empty");
    return _tail->value;
}

template<class T>
bool List<T>::is_empty() { return _head == nullptr; }

template<class T>
bool List<T>::is_empty() const { return _head == nullptr; }

template<class T>
void List<T>::push_front(const T& value) {
    Node<T>* node = new Node<T>(value);
    if (is_empty()) {
        _head = node;
        _tail = node;
        return;
    }
    node->next = _head;
    _head = node;
}

template<class T>
void List<T>::push_back(const T& value) {
    Node<T>* node = new Node<T>(value);
    if (is_empty()) {
        _head = node;
        _tail = node;
        return;
    }
    _tail->next = node;
    _tail = node;
}

template<class T>
void List<T>::insert_after(size_t pos, const T& value) {
    if (is_empty()) {
        if (pos == 0) push_front(value);
        else throw std::logic_error("Position out of range");
        return;
    }

    Node<T>* cur = _head;
    size_t cur_pos = 0;
    while (cur != nullptr && cur_pos < pos) {
        cur_pos++;
        cur = cur->next;
    }

    if (cur == nullptr) {
        throw std::logic_error("Position out of range");
    }

    insert(cur, value);
}

template<class T>
void List<T>::insert(Node<T>* node, const T& value) {
    if (node == nullptr || is_empty()) {
        throw std::logic_error("Invalid node");
    }
    Node<T>* new_node = new Node<T>(value);
    new_node->next = node->next;
    node->next = new_node;
    if (node == _tail) {
        _tail = new_node;
    }
}

template<class T>
void List<T>::pop_front() {
    if (is_empty()) { throw std::logic_error("List is empty"); }
    Node<T>* temp = _head;
    _head = _head->next;
    delete temp;
    if (_head == nullptr) {
        _tail = nullptr;
    }
}

template<class T>
void List<T>::pop_back() {
    if (is_empty()) { throw std::logic_error("List is empty"); }
    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        return;
    }

    Node<T>* cur = _head;
    while (cur->next != _tail) {
        cur = cur->next;
    }

    delete _tail;
    cur->next = nullptr;
    _tail = cur;
}

template<class T>
void List<T>::erase(size_t pos) {
    if (pos == 0) {
        pop_front();
        return;
    }

    Node<T>* cur = _head;
    size_t cur_pos = 0;
    while (cur != nullptr && cur_pos < pos - 1) {
        cur_pos++;
        cur = cur->next;
    }

    if (cur == nullptr || cur->next == nullptr) { throw std::logic_error("Position out of range"); }

    Node<T>* node_to_delete = cur->next;
    cur->next = node_to_delete->next;
    if (node_to_delete == _tail) {
        _tail = cur;
    }
    delete node_to_delete;
}

template<class T>
void List<T>::erase(Node<T>* node) {
    if (node == nullptr || is_empty()) { throw std::logic_error("Invalid node"); }

    if (node == _head) {
        pop_front();
        return;
    }

    Node<T>* cur = _head;
    while (cur->next != node) {
        if (cur->next == nullptr) { throw std::logic_error("Node not found in list"); }
        cur = cur->next;
    }

    cur->next = node->next;
    if (node == _tail) {
        _tail = cur;
    }
    delete node;
}

template<class T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this == &other) {
        return *this;
    }

    while (!is_empty()) { pop_front(); }

    Node<T>* cur = other._head;
    while (cur != nullptr) {
        push_back(cur->value);
        cur = cur->next;
    }

    return *this;
}

template<class T>
bool List<T>::operator==(const List<T>& other) const {
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
bool List<T>::operator!=(const List<T>& other) const {
    return !(*this == other);
}