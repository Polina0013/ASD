// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>
#include <climits>

#include "..\lib_tvector\tvector.h"
#include "..\lib_graph\graph.h"

template <class T>
std::pair<TVector<T>, int> dijkstras_algorithm_with_vector(Graph<T>& graph, const T& start, const T& end) {
    //int size = graph._data.size();
    int size = graph.get_ver_count();

    TVector<int> dist(size);
    TVector<bool> visited(size);
    TVector<int> prev(size);    // для пути

    for (int i = 0; i < size; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        prev[i] = -1;
    }

    int start_idx = graph.find_vertex(start);
    int end_idx = graph.find_vertex(end);

    if (start_idx == -1 || end_idx == -1) throw std::logic_error("One or both vertices were not found!");
    
    dist[start_idx] = 0;
    for (int i = 0; i < size-1; i++) {
        int min_dist = INT_MAX;
        int found_ver = -1;

        for (int j = 0; j < size; j++) {    // поиск минимума
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                found_ver = j;
            }
        }

        if (found_ver == -1) break;
        visited[found_ver] = true;

        // проверка всех путей из вершины
        //auto& list = graph._data[found_ver];
        auto& list = graph.get_edges(found_ver);
        auto it = list.begin();
        it++;

        while (it != list.end()) {
            T next_ver = it->first;
            int weight = it->second;

            int idx_next = graph.find_vertex(next_ver);

            if (!visited[idx_next] && dist[found_ver] != INT_MAX && dist[found_ver] + weight < dist[idx_next]) {
                dist[idx_next] = dist[found_ver] + weight;
                prev[idx_next] = found_ver;  // запоминаем, откуда пришли
            }
            it++;
        }
    }

    if (dist[end_idx] == INT_MAX) return { TVector<T>(), -1 }; // пути нет

    TVector<int> reverse_path_idx;
    for (int i = end_idx; i != -1; i = prev[i]) {
        reverse_path_idx.push_back(i);
    }

    TVector<T> path;
    for (int i = reverse_path_idx.size() - 1; i >= 0; i--) {
        //T vertex = graph._data[reverse_path_idx[i]].front().first;
        T vertex = graph.get_ver_val(reverse_path_idx[i]);
        path.push_back(vertex);
    }

    return { path, dist[end_idx] };
}

template <class T>
void print_dijkstras_algorithm(std::pair<TVector<T>, int> res_alg) {
    std::cout << "(" << res_alg.second << ")" << std::endl;

    std::cout << res_alg.first[0];

    for (int i = 1; i < res_alg.first.size(); i++) {
        std::cout << " -> " << res_alg.first[i];
    }

    std::cout << std::endl;
}