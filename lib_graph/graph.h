// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_tvector\tvector.h"
#include "..\lib_list\list.h"

enum isDirected { directed, undirected };  // ориентированный
enum isWeighted { weighted, unweighted };  // взвешенный

template <class T>
class Graph {
    TVector<List<std::pair<T, int>>> _data;
    isDirected _direct;
    isWeighted _weight;
public:
    Graph(TVector<std::pair<std::pair<T, T>, int>> vector_of_edges, isDirected direct);
    Graph(TVector<std::pair<T, T>> vector_of_edges, isDirected direct);

    int get_ver_count() const;
    List<std::pair<T, int>>& get_edges(int index);
    T get_ver_val(int index) const;

    int find_vertex(const T& vertex);
    bool find_edge(const T& vertex1, const T& vertex2);

    void add_vertex(const T& vertex);
    void add_edge(const T& vertex1, const T& vertex2, const int& weigh);
    void add_edge(const T& vertex1, const T& vertex2);
    void delete_vertex(const T& vertex);
    void delete_edge(const T& vertex1, const T& vertex2);
    void print();
private:
    Node<std::pair<T, int>>* find_node(int vertex_idx, const T& target);
};

template <class T>
Graph<T>::Graph(TVector<std::pair<std::pair<T, T>, int>> vector_of_edges, isDirected direct) { // взвешенное
    _direct = direct;
    _weight = weighted;
    for (int i = 0; i < vector_of_edges.size(); i++) {
        T v1 = vector_of_edges[i].first.first;
        T v2 = vector_of_edges[i].first.second;

        add_vertex(v1);
        add_vertex(v2);

        add_edge(v1, v2, vector_of_edges[i].second);
    }
}

template <class T>
Graph<T>::Graph(TVector<std::pair<T, T>> vector_of_edges, isDirected direct) { // не взвешенное
    _direct = direct;
    _weight = unweighted;
    for (int i = 0; i < vector_of_edges.size(); i++) {
        T v1 = vector_of_edges[i].first;
        T v2 = vector_of_edges[i].second;

        add_vertex(v1);
        add_vertex(v2);

        add_edge(v1, v2);
    }
}

template <class T>
int Graph<T>::get_ver_count() const {
    return _data.size();
}

template <class T>
List<std::pair<T, int>>& Graph<T>::get_edges(int index) {
    return _data[index];
}

template <class T>
T Graph<T>::get_ver_val(int index) const {
    return _data[index].front().first;
}

template <class T>
int Graph<T>::find_vertex(const T& vertex) {
    for (int i = 0; i < _data.size(); i++) {
        if (_data[i].front().first == vertex) return i;
    }
    return -1;
}

template <class T>
bool Graph<T>::find_edge(const T& vertex1, const T& vertex2) {
    int idx1 = find_vertex(vertex1);
    int idx2 = find_vertex(vertex2);

    if (idx1 == -1 || idx2 == -1) return false;

    Node<std::pair<T, int>>* found_node = find_node(idx1, vertex2);
    return found_node != nullptr;
}

template <class T>
Node<std::pair<T, int>>* Graph<T>::find_node(int vertex_idx, const T& target) {
    for (auto it = _data[vertex_idx].begin(); it != _data[vertex_idx].end(); it++) {
        if (it->first == target) return it.get_node();
    }
    return nullptr;
}

template <class T>
void Graph<T>::add_vertex(const T& vertex) {
    if (find_vertex(vertex) == -1) {
        List<std::pair<T, int>> new_list;
        new_list.push_back(std::pair<T, int>(vertex, 0));
        _data.push_back(new_list);
    }
}

template <class T>
void Graph<T>::add_edge(const T& vertex1, const T& vertex2, const int& weigh) {
    if (_weight == unweighted && weigh != 1) throw std::logic_error("The graph is unweighted!");
    
    int idx1 = find_vertex(vertex1);
    int idx2 = find_vertex(vertex2);

    if (idx1 == -1 || idx2 == -1) throw std::logic_error("One or both vertices do not exist!");

    for (auto it = _data[idx1].begin(); it != _data[idx1].end(); it++) {
        if (it->first == vertex2) throw std::logic_error("The edge already exists!");
    }

    _data[idx1].push_back(std::pair<T, int>(vertex2, weigh));
    if (_direct == undirected && vertex1 != vertex2) {
        _data[idx2].push_back(std::pair<T, int>(vertex1, weigh));
    }
}

template <class T>
void Graph<T>::add_edge(const T& vertex1, const T& vertex2) {
    add_edge(vertex1, vertex2, 1);
}

template <class T>
void Graph<T>::delete_vertex(const T& vertex) {
    int idx = find_vertex(vertex);
    if (idx == -1) throw std::logic_error("The vertex does not exist!");

    for (int i = 0; i < _data.size(); i++) {
        if (i != idx) {
            Node<std::pair<T, int>>* node = find_node(i, vertex);
            if (node) _data[i].erase(node);
        }
    }

    _data.erase(idx);
}

template <class T>
void Graph<T>::delete_edge(const T& vertex1, const T& vertex2) {
    int idx1 = find_vertex(vertex1);
    int idx2 = find_vertex(vertex2);

    if (idx1 == -1 || idx2 == -1) throw std::logic_error("One or both vertices do not exist!");

    Node<std::pair<T, int>>* edge_node = find_node(idx1, vertex2);
    if (!edge_node) throw std::logic_error("The edge does not exist!");
    _data[idx1].erase(edge_node);

    if (_direct == undirected && vertex1 != vertex2) {
        Node<std::pair<T, int>>* reverse_edge = find_node(idx2, vertex1);
        if (reverse_edge) _data[idx2].erase(reverse_edge);
    }
}

template <class T>
void Graph<T>::print() {
    for (int i = 0; i < _data.size(); i++) {
        if (!_data[i].is_empty()) {
            std::cout << _data[i].front().first << " : ";

            auto it = _data[i].begin();
            it++;

            while (it != _data[i].end()) {
                std::cout << it->first << " (" << it->second << ")";
                it++;
                if (it != _data[i].end()) std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}