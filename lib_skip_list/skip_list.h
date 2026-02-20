// Copyright 2026 Pozdnova Polina

//#pragma once
//
//#include <iostream>
//#include <stdexcept>
//
////#include "..\lib_list\list.h"
//
//template <class TKey, class TValue>
//struct Node {
//    std::pair <TKey, TValue> _data;
//    Node** _next;
//public:
//    // конструкторы
//    ~Node();
//};
//
//
//class SkipList {      // не забыть указатели на nullptr в конце 
//    size_t _max_lvl;  // если пользователь задал макс уровень, то он есть; если нет, то кол-во уровней бесконечно
//    size_t _lvls;
//    List<Node*> _heads; // список указателей на Node (список односвязный)
//public:
//    // конструкторы
//    void insert(const TKey&, const TValue&);
//    void print() const noexept;
//protected:
//    size_t flip_coin() const noexept; // подбрасывание монетки
//    Node<TKey, TValue>* find_nearest(const TKey&) const noexept; // для вставки
//
//    // нет обычного поиска и удаления (реализовывать не нужно)
//}
