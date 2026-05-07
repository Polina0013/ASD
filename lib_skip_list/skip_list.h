// Copyright 2026 Pozdnova Polina

#include "..\lib_list\list.h"

#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <utility>
#include <iostream>
#include <iomanip>

template <class TKey, class TValue>
struct SkipNode {
    std::pair<TKey, TValue> _data;
    SkipNode** left;

    SkipNode(const TKey& key, const TValue& value, size_t level);
    ~SkipNode();
};

template <class TKey, class TValue>
SkipNode<TKey, TValue>::SkipNode(const TKey& key, const TValue& value, size_t level) {
    _data.first = key;
    _data.second = value;
    _next = new SkipNode * [level + 1];
    for (size_t i = 0; i <= level; i++) {
        _next[i] = nullptr;
    }
}
template <class TKey, class TValue>
SkipNode<TKey, TValue>::~SkipNode() {
    delete[] _next;
}

template <class TKey, class TValue>
class SkipList {
private:
    size_t _max_lvl;     // количество
    size_t _lvls;        // количество
    List<SkipNode<TKey, TValue>*> _heads;


public:
    SkipList();
    SkipList(size_t max_level);
    ~SkipList();

    void insert(const TKey& key, const TValue& value);
    bool is_empty();
    void print();

private:
    size_t flip_coin();
    SkipNode<TKey, TValue>* get_head_at_level(size_t level);
};

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList() : _max_lvl(0), _lvls(1) {
    srand(time(nullptr));

    SkipNode<TKey, TValue>* head = new SkipNode<TKey, TValue>(TKey(), TValue(), 0);
    _heads.push_back(head);
}

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList(size_t max_level) : _max_lvl(max_level), _lvls(1) {
    if (max_level == 0) {
        throw std::invalid_argument("Max level must be greater than 0");
    }
    srand(time(nullptr));

    for (size_t i = 0; i < _max_lvl; i++) {
        SkipNode<TKey, TValue>* head = new SkipNode<TKey, TValue>(TKey(), TValue(), _max_lvl - 1);
        _heads.push_back(head);
    }
}

template <class TKey, class TValue>
SkipList<TKey, TValue>::~SkipList() {
    if (!_heads.is_empty()) {
        SkipNode<TKey, TValue>* current = get_head_at_level(0)->_next[0];
        while (current != nullptr) {
            SkipNode<TKey, TValue>* next = current->_next[0];
            delete current;
            current = next;
        }

        for (auto it = _heads.begin(); it != _heads.end(); ++it) {
            delete* it;
        }
    }
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    SkipNode<TKey, TValue>** update = new SkipNode<TKey, TValue>* [_lvls];

    for (int i = _lvls - 1; i >= 0; i--) {
        SkipNode<TKey, TValue>* current = get_head_at_level(i);

        while (current->_next[i] != nullptr && current->_next[i]->_data.first < key) {
            current = current->_next[i];
        }
        update[i] = current;
    }

    SkipNode<TKey, TValue>* next_node = update[0]->_next[0];
    if (next_node != nullptr && next_node->_data.first == key) {
        delete[] update;
        throw std::invalid_argument("Key already exists in the skip list!");
    }

    size_t new_node_level = flip_coin();  // номер уровня
    std::cout << "flip_coin: " << new_node_level << "\n";

    if (new_node_level + 1 > _lvls) {
        SkipNode<TKey, TValue>** new_update = new SkipNode<TKey, TValue>* [new_node_level + 1];

        for (size_t i = 0; i < _lvls; i++) {
            new_update[i] = update[i];
        }

        for (size_t i = _lvls; i <= new_node_level; i++) {
            SkipNode<TKey, TValue>* new_head = new SkipNode<TKey, TValue>(TKey(), TValue(), i);
            _heads.push_back(new_head);

            new_update[i] = new_head;
        }

        delete[] update;
        update = new_update;
        _lvls = new_node_level + 1;
    }


    SkipNode<TKey, TValue>* new_node = new SkipNode<TKey, TValue>(key, value, new_node_level);

    for (size_t i = 0; i <= new_node_level; i++) {
        new_node->_next[i] = update[i]->_next[i];
        update[i]->_next[i] = new_node;
    }

    delete[] update;
}

template <class TKey, class TValue>
bool SkipList<TKey, TValue>::is_empty() {
    return _heads.is_empty() || get_head_at_level(0)->_next[0] == nullptr;
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::print() {
    SkipNode<TKey, TValue>* current = get_head_at_level(0)->_next[0];
    List<SkipNode<TKey, TValue>*> nodes_in_order;

    while (current != nullptr) {
        nodes_in_order.push_back(current);
        current = current->_next[0];
    }

    for (int i = _lvls - 1; i >= 0; i--) {
        std::cout << "Level " << i << ": ";

        auto it = nodes_in_order.begin();
        while (it != nodes_in_order.end()) {
            SkipNode<TKey, TValue>* node = *it;

            bool node_exists_on_level = false;

            SkipNode<TKey, TValue>* level_current = get_head_at_level(i)->_next[i];
            while (level_current != nullptr) {
                if (level_current == node) {
                    node_exists_on_level = true;
                    break;
                }
                level_current = level_current->_next[i];
            }

            if (node_exists_on_level) {
                std::string output = "(" + std::to_string(node->_data.first) + "," + node->_data.second + ")";
                std::cout << std::setw(12) << output;
            }
            else {
                std::cout << std::setw(12) << " ";
            }

            ++it;
        }
        std::cout << std::endl;
    }
    std::cout << "\n";
}

template <class TKey, class TValue>
size_t SkipList<TKey, TValue>::flip_coin() {
    size_t level = 0;

    if (_max_lvl == 0) {
        while (rand() % 2 == 1) {
            level++;
        }
    }
    else {
        while (level < _max_lvl - 1 && rand() % 2 == 1) {
            level++;
        }
    }
    return level;
}
template <class TKey, class TValue>
SkipNode<TKey, TValue>* SkipList<TKey, TValue>::get_head_at_level(size_t level) {
    if (level >= _lvls) return nullptr;

    auto it = _heads.begin();
    for (size_t i = 0; i < level; i++) {
        ++it;
    }
    return *it;
}
