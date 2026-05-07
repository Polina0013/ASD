// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\dijkstras_algorithm_with_vector\dijkstras_algorithm_with_vector.h"
#include "..\lib_graph\graph.h"
#include "..\lib_tvector\tvector.h"

//#define TEST_DIJKSTRAS_ALGORITHM_WITH_VECTOR
#ifdef TEST_DIJKSTRAS_ALGORITHM_WITH_VECTOR

TEST(TestDijkstrasAlgorithm, check_dijkstras_algorithm_on_directed) {
    std::pair<std::pair<char, char>, int> p1({ 'A', 'B' }, 1);
    std::pair<std::pair<char, char>, int> p2({ 'A', 'C' }, 8);
    std::pair<std::pair<char, char>, int> p3({ 'A', 'D' }, 10);
    std::pair<std::pair<char, char>, int> p4({ 'D', 'B' }, 2);

    TVector<std::pair<std::pair<char, char>, int>> data({ p1, p2, p3, p4 });
    Graph<char> graph(data, directed);

    graph.add_vertex('E');
    graph.add_edge('D', 'E', 4);
    graph.add_edge('A', 'E', 20);

    std::pair<TVector<char>, int> path = dijkstras_algorithm_with_vector(graph, 'A', 'E');

    //graph.print();
    //print_dijkstras_algorithm(path);

    TVector<char> expected_result({'A', 'D', 'E'});

    EXPECT_EQ(path.second, 14);
    for (int i = 0; i < path.first.size(); i++) {
        EXPECT_EQ(path.first[i], expected_result[i]);
    }
}

TEST(TestDijkstrasAlgorithm, check_dijkstras_algorithm_on_undirected) {
    std::pair<char, char> p1('A', 'B');
    std::pair<char, char> p2('A', 'C');
    std::pair<char, char> p3('C', 'B');
    std::pair<char, char> p4('A', 'D');
    std::pair<char, char> p5('E', 'D');
    std::pair<char, char> p6('E', 'F');
    std::pair<char, char> p7('C', 'F');

    TVector<std::pair<char, char>> data({ p1, p2, p3, p4, p5, p6, p7 });
    Graph<char> graph(data, undirected);

    graph.add_vertex('G');
    graph.add_vertex('H');
    graph.add_vertex('I');
    graph.add_edge('C', 'G');
    graph.add_edge('C', 'H');
    graph.add_edge('G', 'H');
    graph.add_edge('F', 'I');

    std::pair<TVector<char>, int> path = dijkstras_algorithm_with_vector(graph, 'A', 'I');

    //graph.print();
    //print_dijkstras_algorithm(path);

    TVector<char> expected_result({ 'A', 'C', 'F', 'I' });

    EXPECT_EQ(path.second, 3);
    for (int i = 0; i < path.first.size(); i++) {
        EXPECT_EQ(path.first[i], expected_result[i]);
    }
}

#endif //TEST_DIJKSTRAS_ALGORITHM_WITH_VECTOR