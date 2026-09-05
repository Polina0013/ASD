// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include <sstream>
#include <random>
#include <string>

#include "..\lib_heap_on_vector\heap_on_vector.h"

//#define TEST_HEAP_ON_VECTOR
#ifdef TEST_HEAP_ON_VECTOR

TEST(TestHeapOnVector, check_push) {
    HeapOnVector<int> heap;
    heap.push(7);
    heap.push(6);
    heap.push(5);
    heap.push(4);
    heap.push(3);
    heap.push(3);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    heap.print();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "3 4 3 7 5 6 \n");
}

TEST(TestHeapOnVector, check_push_with_random_generation) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);   // от 1 до 100

    TVector<int> vec1;

    for (int i = 0; i < 10; i++) {
        int random_num = dist(gen);
        vec1.push_back(random_num);
        //std::cout << "Push: " << random_num << std::endl;
    }

    TVector<int> vec = pyramid_sort(vec1);

    bool is_sorted = true;
    for (int i = 0; i < vec.size() - 1; i++) {
        if (vec[i] > vec[i + 1]) { is_sorted = false; break; }
    }

    EXPECT_TRUE(is_sorted);

    std::string s;
    for (int i = 0; i < vec.size(); i++) {
        s += std::to_string(vec[i]);
        if (i < vec.size() - 1) s += " ";
    }

    //std::cout << "Sorted values: " << s << std::endl;
}

TEST(TestHeapOnVector, check_pop) {
    HeapOnVector<int> heap;
    heap.push(7);
    heap.push(6);
    heap.push(5);
    heap.push(4);
    heap.push(3);
    heap.push(3);

    heap.pop();
    std::stringstream buffer1;
    std::streambuf* old = std::cout.rdbuf(buffer1.rdbuf());
    heap.print();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer1.str(), "3 4 6 7 5 \n");

    heap.pop();
    std::stringstream buffer2;
    old = std::cout.rdbuf(buffer2.rdbuf());
    heap.print();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer2.str(), "4 5 6 7 \n");
}

TEST(TestHeapOnVector, the_exception_is_when_pop_from_empty_heap) {
    HeapOnVector<int> heap;
    ASSERT_ANY_THROW(heap.pop(););
}

TEST(TestHeapOnVector, check_pyramid_sort) {
    TVector<int> vec1({7, 6, 5, 4, 8, 1});
    //heap.push(7);
    //heap.push(6);
    //heap.push(5);
    //heap.push(4);
    //heap.push(3);
    //heap.push(3);
    //heap.push(8);

    /*heap.pop();
    heap.pop();
    heap.push(1);*/
    TVector<int> vec = pyramid_sort(vec1);
    std::string s;
    for (int i = 0; i < vec.size(); i++) {
        s+= std::to_string(vec[i]) + " ";
    }

    EXPECT_EQ(s, "1 4 5 6 7 8 ");
}

TEST(TestHeapOnVector, check_clear_and_is_empty) {
    HeapOnVector<int> heap;
    heap.push(7);
    heap.push(6);
    heap.push(5);
    heap.push(4);
    heap.push(3);
    heap.push(3);
    heap.push(8);

    EXPECT_FALSE(heap.is_empty());

    heap.clear();
    EXPECT_TRUE(heap.is_empty());
}

#endif //TEST_HEAP_ON_VECTOR