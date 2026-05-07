// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include <sstream>
#include "..\lib_graph_adjacency_matrix\graph_adjacency_matrix.h"
#include "..\lib_tvector\tvector.h"

//#define TEST_GRAPH_AM
#ifdef TEST_GRAPH_AM

//TEST(TestGraphAM, check_adjacency_matrix) {
//    std::pair<std::pair<char, char>, int> p1({ 'A', 'B' }, 1);
//    std::pair<std::pair<char, char>, int> p2({ 'A', 'C' }, 8);
//    std::pair<std::pair<char, char>, int> p3({ 'A', 'D' }, 10);
//    std::pair<std::pair<char, char>, int> p4({ 'B', 'D' }, 2);
//
//
//    TVector<std::pair<std::pair<char, char>, int>> data({ p1, p2, p3, p4 });
//    GraphAM<char> graph(data, undirected);
//
//    graph.print();
//
//    graph.add_edge('D', 'C', 28);
//    //ASSERT_ANY_THROW(graph.add_edge('D', 'A', 28, undirected));
//    graph.print();
//
//    graph.add_vertex('E');
//    graph.print();
//
//    graph.delete_edge('A', 'B');
//    graph.print();
//
//    graph.delete_vertex('A');
//    graph.print();
//}

TEST(TestGraphAM, the_exception_is_when_insert_not_a_unique_edge) {
    std::pair<std::pair<char, char>, int> p1({ 'A', 'B' }, 1);
    std::pair<std::pair<char, char>, int> p2({ 'A', 'C' }, 8);
    std::pair<std::pair<char, char>, int> p3({ 'A', 'D' }, 10);
    std::pair<std::pair<char, char>, int> p4({ 'D', 'B' }, 2);

    TVector<std::pair<std::pair<char, char>, int>> data({ p1, p2, p3, p4 });
    GraphAM<char> graph(data, directed);

    graph.add_vertex('E');
    graph.add_edge('D', 'E', 4);
    graph.add_edge('A', 'E', 20);

    //graph.print();

    ASSERT_ANY_THROW(graph.add_edge('D', 'E', 4));
}

TEST(TestGraphAM, check_the_erase) {
    std::pair<std::pair<char, char>, int> p1({ 'A', 'B' }, 1);
    std::pair<std::pair<char, char>, int> p2({ 'A', 'C' }, 8);
    std::pair<std::pair<char, char>, int> p3({ 'A', 'D' }, 10);
    std::pair<std::pair<char, char>, int> p4({ 'D', 'B' }, 2);

    TVector<std::pair<std::pair<char, char>, int>> data({ p1, p2, p3, p4 });
    GraphAM<char> graph(data, undirected);

    graph.add_vertex('E');
    graph.add_edge('D', 'E', 4);
    graph.add_edge('A', 'E', 20);

    graph.delete_vertex('A');
    graph.delete_edge('D', 'B');

    //graph.print();

    EXPECT_EQ(graph.find_vertex('A'), -1);
    EXPECT_EQ(graph.find_edge('A', 'B'), 0);
    EXPECT_EQ(graph.find_edge('C', 'A'), 0);

    EXPECT_EQ(graph.find_edge('D', 'B'), 0);
}

TEST(TestGraphAM, the_exception_is_when_deleting_that_does_not_exist) {
    std::pair<char, char> p1('A', 'B');
    std::pair<char, char> p2('A', 'C');
    std::pair<char, char> p3('A', 'D');
    std::pair<char, char> p4('D', 'B');

    TVector<std::pair<char, char>> data({ p1, p2, p3, p4 });
    GraphAM<char> graph(data, directed);

    graph.add_vertex('E');
    graph.add_edge('D', 'E');
    graph.add_edge('A', 'E');

    //graph.print();

    ASSERT_ANY_THROW(graph.delete_vertex('Z'));
    ASSERT_ANY_THROW(graph.delete_edge('Z', 'A'));
    ASSERT_ANY_THROW(graph.delete_edge('B', 'C'));
}

TEST(TestGraphAM, the_exception_is_when_a_weighted_edge_is_added_to_an_unweighted_graph) {
    std::pair<char, char> p1('A', 'B');
    std::pair<char, char> p2('A', 'C');
    std::pair<char, char> p3('A', 'D');
    std::pair<char, char> p4('D', 'B');

    TVector<std::pair<char, char>> data({ p1, p2, p3, p4 });
    GraphAM<char> graph(data, undirected);

    graph.add_vertex('E');
    graph.add_edge('D', 'E');

    //graph.print();

    ASSERT_ANY_THROW(graph.add_edge('A', 'E', 567));
}

#endif //TEST_GRAPH_AM