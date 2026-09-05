// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include <sstream>
#include "..\lib_rb_tree\rb_tree.h"

//#define TEST_RB_TREE
#ifdef TEST_RB_TREE

TEST(TestRBTree, the_exception_is_when_insert_of_multiple_values_using_the_same_key) {
    RBTree<int, std::string> tree(15, "15.");
    tree.insert(5, "5.");
    tree.insert(30, "30.");
    tree.insert(35, "35.");
    tree.insert(16, "16.");
    tree.insert(7, "7.");
    tree.insert(3, "3.");
    tree.insert(1, "1.");
    tree.insert(9, "9.");
    tree.insert(40, "40.");
    tree.insert(6, "6.");
    tree.erase(6);
    tree.erase(1);

    //tree.print();

    ASSERT_ANY_THROW(tree.insert(16, "Twelve"));

    std::stringstream buffer_W;
    std::streambuf* old = std::cout.rdbuf(buffer_W.rdbuf());
    tree.print();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer_W.str(), "3:3.(B) 5:5.(R) 7:7.(B) 9:9.(R) 15:15.(B) 16:16.(B) 30:30.(R) 35:35.(B) 40:40.(R) \n");
}

TEST(TestRBTree, check_find) {
    RBTree<int, std::string> tree;
    tree.insert(15, "15.");
    tree.insert(5, "5.");
    tree.insert(30, "30.");
    tree.insert(35, "35.");
    tree.insert(16, "16.");
    tree.insert(7, "7.");
    tree.insert(3, "3.");
    tree.insert(1, "1.");
    tree.insert(9, "9.");
    tree.insert(40, "40.");
    tree.insert(6, "6.");
    tree.erase(6);
    tree.erase(1);
    tree.insert(12, "12.");

    //tree.print();

    EXPECT_EQ(*tree.find(12), "12.");
    EXPECT_EQ(tree.find(1), nullptr);
}

TEST(TestRBTree, check_erase_leaf) {
    RBTree<int, std::string> tree;
    tree.insert(15, "15.");
    tree.insert(5, "5.");
    tree.insert(30, "30.");
    tree.insert(35, "35.");
    tree.insert(16, "16.");
    tree.insert(7, "7.");
    tree.insert(3, "3.");
    tree.insert(1, "1.");
    tree.insert(9, "9.");
    tree.insert(40, "40.");
    tree.insert(6, "6.");
    tree.erase(1);
    tree.erase(40);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "3:3.(B) 5:5.(R) 6:6.(R) 7:7.(B) 9:9.(R) 15:15.(B) 16:16.(B) 30:30.(R) 35:35.(B) \n");
}

TEST(TestRBTree, check_erase_node) {
    RBTree<int, std::string> tree;
    tree.insert(15, "15.");
    tree.insert(5, "5.");
    tree.insert(30, "30.");
    tree.insert(35, "35.");
    tree.insert(18, "18.");
    tree.insert(7, "7.");
    tree.insert(3, "3.");
    tree.insert(1, "1.");
    tree.insert(9, "9.");
    tree.insert(40, "40.");
    tree.insert(6, "6.");
    tree.insert(17, "17.");
    tree.insert(19, "19.");
    tree.erase(30);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "1:1.(R) 3:3.(B) 5:5.(R) 6:6.(R) 7:7.(B) 9:9.(R) 15:15.(B) 17:17.(R) 18:18.(B) 19:19.(R) 35:35.(B) 40:40.(R) \n");
}

TEST(TestRBTree, check_erase_node_with_one_child) {
    RBTree<int, std::string> tree;
    tree.insert(15, "15.");
    tree.insert(5, "5.");
    tree.insert(30, "30.");
    tree.insert(35, "35.");
    tree.insert(18, "18.");
    tree.insert(7, "7.");
    tree.insert(3, "3.");
    tree.insert(1, "1.");
    tree.insert(9, "9.");
    tree.insert(40, "40.");
    tree.insert(6, "6.");
    tree.insert(17, "17.");
    tree.insert(19, "19.");
    tree.erase(35);
    tree.erase(3);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "1:1.(B) 5:5.(R) 6:6.(R) 7:7.(B) 9:9.(R) 15:15.(B) 17:17.(R) 18:18.(B) 19:19.(R) 30:30.(R) 40:40.(B) \n");
}

TEST(TestRBTree, check_erase_single_root) {
    RBTree<int, std::string> tree;
    tree.insert(1, "1.");
    tree.erase(1);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "\n");
}

TEST(TestRBTree, the_exception_is_when_erase_from_empty_tree) {
    RBTree<int, std::string> tree;
    ASSERT_ANY_THROW(tree.erase(2));
}

TEST(TestRBTree, check_clear) {
    RBTree<int, std::string> tree;
    tree.insert(15, "15.");
    tree.insert(5, "5.");
    tree.insert(30, "30.");
    tree.insert(35, "35.");
    tree.insert(18, "18.");
    tree.insert(7, "7.");
    tree.insert(3, "3.");
    tree.insert(1, "1.");
    tree.insert(9, "9.");
    tree.insert(40, "40.");
    tree.insert(6, "6.");
    tree.insert(17, "17.");
    tree.insert(19, "19.");
    tree.erase(15);
    tree.erase(18);

    tree.clear();

    EXPECT_TRUE(tree.is_empty());

    tree.insert(34, "34.");
    tree.insert(56, "56.");

    EXPECT_FALSE(tree.is_empty());
}

TEST(TestRBTree, check_insert_balance_case_2) {
    // Случай 2
    RBTree<int, std::string> tree;
    tree.insert(10, "10.");
    tree.insert(5, "5.");
    tree.insert(15, "15.");
    tree.insert(3, "3.");
    tree.insert(7, "7.");

    tree.erase(15);

    tree.insert(4, "4.");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "3:3.(B) 4:4.(R) 5:5.(B) 7:7.(R) 10:10.(B) \n");
}

TEST(TestRBTree, check_insert_balance_case_3) {
    // Случай 3
    RBTree<int, std::string> tree;
    tree.insert(10, "10.");
    tree.insert(5, "5.");
    tree.insert(15, "15.");
    tree.insert(3, "3.");
    tree.insert(7, "7.");

    tree.insert(1, "1.");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "1:1.(R) 3:3.(B) 5:5.(R) 7:7.(B) 10:10.(B) 15:15.(B) \n");
}

TEST(TestRBTree, check_insert_balance_case_4) {
    // Случай 4
    RBTree<int, std::string> tree;
    tree.insert(10, "10.");
    tree.insert(5, "5.");
    tree.insert(15, "15.");
    tree.insert(3, "3.");
    tree.insert(7, "7.");

    tree.erase(15);

    tree.insert(8, "8.");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "3:3.(B) 5:5.(B) 7:7.(R) 8:8.(B) 10:10.(R) \n");
    EXPECT_EQ(tree.get_root()->data.first, 5);
}

TEST(TestRBTree, check_insert_balance_case_5) {
    // Случай 5
    RBTree<int, std::string> tree;
    tree.insert(10, "10.");
    tree.insert(5, "5.");
    tree.insert(15, "15.");
    tree.insert(3, "3.");
    tree.insert(7, "7.");

    tree.erase(15);

    tree.insert(6, "6.");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "3:3.(B) 5:5.(B) 6:6.(R) 7:7.(B) 10:10.(R) \n");
    EXPECT_EQ(tree.get_root()->data.first, 5);
}

TEST(TestRBTree, check_erase_red_leaf) {
    RBTree<int, std::string> tree;

    tree.insert(10, "10.");
    tree.insert(5, "5.");
    tree.insert(15, "15.");

    tree.erase(15);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "5:5.(R) 10:10.(B) \n");
}

TEST(TestRBTree, check_erase_root) {
    RBTree<int, std::string> tree;

    tree.insert(10, "10.");

    tree.erase(10);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "\n");
}

TEST(TestRBTree, check_erase_black_with_red_child) {
    RBTree<int, std::string> tree;

    tree.insert(10, "10.");
    tree.insert(5, "5.");
    tree.insert(1, "1.");

    EXPECT_EQ(tree.get_root()->data.first, 5);

    tree.erase(5);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "1:1.(B) 10:10.(R) \n");
}

TEST(TestRBTree, check_erase_two_children) {
    RBTree<int, std::string> tree;

    tree.insert(20, "20.");
    tree.insert(10, "10.");
    tree.insert(30, "30.");
    tree.insert(5, "5.");
    tree.insert(15, "15.");

    tree.erase(20);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "5:5.(R) 10:10.(B) 15:15.(B) 30:30.(B) \n");
    EXPECT_EQ(tree.get_root()->data.first, 15);
}

TEST(TestRBTree, check_erase_double_rotation) {
    RBTree<int, std::string> tree;

    tree.insert(20, "20.");
    tree.insert(10, "10.");
    tree.insert(30, "30.");
    tree.insert(25, "25.");
    tree.insert(40, "40.");
    tree.insert(22, "22.");
    EXPECT_EQ(tree.get_root()->data.first, 20);

    tree.erase(10);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ( buffer.str(), "20:20.(B) 22:22.(R) 25:25.(B) 30:30.(B) 40:40.(B) \n" );
    EXPECT_EQ(tree.get_root()->data.first, 30);
}

TEST(TestRBTree, check_erase_many) {
    RBTree<int, std::string> tree;

    for (int i = 1; i <= 20; i++) tree.insert(i, std::to_string(i));

    for (int i = 1; i <= 20; i++) tree.erase(i);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "\n");
}

TEST(TestRBTree, check_erase_case2) {
    RBTree<int, std::string> tree;

    tree.insert(50, "50.");
    tree.insert(30, "30.");
    tree.insert(80, "80.");
    tree.insert(10, "10.");
    tree.insert(40, "40.");
    tree.insert(60, "60.");
    tree.insert(100, "100.");

    tree.erase(10);
    tree.erase(40);
    tree.erase(60);
    tree.erase(100);

    tree.print();

    tree.erase(30);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "5:5.(R) 10:10.(B) 15:15.(B) 30:30.(B) \n");
    EXPECT_EQ(tree.get_root()->data.first, 15);
}
#endif //TEST_RB_TREE