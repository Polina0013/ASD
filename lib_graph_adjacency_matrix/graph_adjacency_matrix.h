// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>
#include <iomanip>

#include "..\lib_tvector\tvector.h"
#include "..\lib_list\list.h"

#define LENGTH_PRINT 4

enum isDirectedAM { directed, undirected };  // ориентированный
enum isWeightedAM { weighted, unweighted };  // взвешенный

template <class T>
class GraphAM {
    TVector<T> _vertexes;
    TVector<TVector<int>> _data;
    isDirectedAM _direct;
    isWeightedAM _weight;
public:
    GraphAM(TVector<std::pair<std::pair<T, T>, int>> vector_of_edges, isDirectedAM direct);
    GraphAM(TVector<std::pair<T, T>> vector_of_edges, isDirectedAM direct);

    void add_vertex(const T& vertex);
    void add_edge(const T& vertex1, const T& vertex2, const int& weigh);
    void add_edge(const T& vertex1, const T& vertex2);
    void delete_vertex(const T& vertex);
    void delete_edge(const T& vertex1, const T& vertex2);
    void print();

    int find_vertex(const T& vertex);
    int find_edge(const T& vertex1, const T& vertex2);
};

template <class T>
GraphAM<T>::GraphAM(TVector<std::pair<std::pair<T, T>, int>> vector_of_edges, isDirectedAM direct) // взвешенное
    : _direct(direct), _weight(weighted) {
    for (int i = 0; i < vector_of_edges.size(); i++) {
        T v1 = vector_of_edges[i].first.first;
        T v2 = vector_of_edges[i].first.second;

        add_vertex(v1);
        add_vertex(v2);

        add_edge(v1, v2, vector_of_edges[i].second);
    }
}

template <class T>
GraphAM<T>::GraphAM(TVector<std::pair<T, T>> vector_of_edges, isDirectedAM direct) { // не взвешенное
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
int GraphAM<T>::find_vertex(const T& vertex) {
    for (int i = 0; i < _vertexes.size(); i++) {
        if (_vertexes[i] == vertex) return i;
    }
    return -1;
}

template <class T>
int GraphAM<T>::find_edge(const T& vertex1, const T& vertex2) {
    int idx1 = find_vertex(vertex1);
    int idx2 = find_vertex(vertex2);

    if (idx1 == -1 || idx2 == -1) return 0;

    return _data[idx1][idx2];
}

template <class T>
void GraphAM<T>::add_vertex(const T& vertex) {
    if (find_vertex(vertex) == -1) {
        _vertexes.push_back(vertex);

        for (int i = 0; i < _data.size(); i++) {
            _data[i].push_back(0);
        }

        TVector<int> new_tvector(_data.size() + 1);
        for (int i = 0; i <= _data.size(); i++) {
            new_tvector[i] = 0;
        }

        _data.push_back(new_tvector);
    }
}

template <class T>
void GraphAM<T>::add_edge(const T& vertex1, const T& vertex2, const int& weigh) {
    if (_weight == unweighted && weigh != 1) throw std::logic_error("The graph is unweighted!");
    
    int idx1 = find_vertex(vertex1);
    int idx2 = find_vertex(vertex2);

    if (idx1 == -1 || idx2 == -1) throw std::logic_error("One or both vertices do not exist!");

    if (_data[idx1][idx2] != 0) throw std::logic_error("The edge already exists!");

    _data[idx1][idx2] = weigh;
    if (_direct == undirected && vertex1 != vertex2) {
        _data[idx2][idx1] = weigh;
    }
}

template <class T>
void GraphAM<T>::add_edge(const T& vertex1, const T& vertex2) {
    add_edge(vertex1, vertex2, 1);
}

template <class T>
void GraphAM<T>::delete_vertex(const T& vertex) {
    int idx = find_vertex(vertex);
    if (idx == -1) throw std::logic_error("The vertex does not exist!");

    for (int i = 0; i < _data.size(); i++) {
        _data[i].erase(idx);
    }

    _data.erase(idx);

    _vertexes.erase(idx);
}

template <class T>
void GraphAM<T>::delete_edge(const T& vertex1, const T& vertex2) {
    int idx1 = find_vertex(vertex1);
    int idx2 = find_vertex(vertex2);

    if (idx1 == -1 || idx2 == -1) throw std::logic_error("One or both vertices do not exist!");

    if (_data[idx1][idx2] == 0) throw std::logic_error("The edge does not exist!");

    _data[idx1][idx2] = 0;
    if (_direct == undirected && vertex1 != vertex2) {
        _data[idx2][idx1] = 0;
    }
}

template <class T>
void GraphAM<T>::print() {
    std::cout << "Vertexes: ";
    for (int i = 0; i < _vertexes.size(); i++) {
        std::cout << _vertexes[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Adjacency matrix: " << std::endl;
    std::string out(LENGTH_PRINT, ' ');
    std::cout << out;
    for (int i = 0; i < _vertexes.size(); i++) {
        std::cout << std::setw(LENGTH_PRINT) << _vertexes[i];
    }
    std::cout << std::endl;

    for (int i = 0; i < _data.size(); i++) {
        std::cout << std::setw(LENGTH_PRINT) << _vertexes[i];
        for (int j = 0; j < _data[i].size(); j++) {
            std::cout << std::setw(LENGTH_PRINT) << _data[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}