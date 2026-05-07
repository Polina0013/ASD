// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include <sstream>
#include "..\lib_binary_tree\binary_tree.h"

//#define TEST_BINARY_TREE
#ifdef TEST_BINARY_TREE

TEST(TestBinaryTree, check_insert_of_multiple_values_using_the_same_key) {
    BinaryTree<int, std::string> tree(1, "1.");
    tree.insert(2, "2.");
    tree.insert(3, "3.");
    tree.insert(4, "4.");
    tree.insert(5, "5.");
    tree.insert(6, "6.");
    tree.erase(6);
    tree.erase(1);
    tree.insert(12, "12.");

    EXPECT_NO_FATAL_FAILURE(tree.insert(12, "Twelve"));

    //tree.print_W();

    std::stringstream buffer_W;
    std::streambuf* old = std::cout.rdbuf(buffer_W.rdbuf());
    tree.print_W();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer_W.str(), "5:5. 2:2. 3:3. 4:4. 12:12. 12:Twelve \n");
}

TEST(TestBinaryTree, check_find) {
    BinaryTree<int, std::string> tree(1, "1.");
    tree.insert(2, "2.");
    tree.insert(3, "3.");
    tree.insert(4, "4.");
    tree.insert(5, "5.");
    tree.insert(6, "6.");
    tree.insert(7, "7.");
    tree.insert(8, "8.");
    tree.insert(9, "9.");
    tree.insert(10, "10.");
    tree.insert(11, "11.");
    tree.erase(6);
    tree.erase(1);
    tree.insert(12, "12.");

    //tree.print_W();

    EXPECT_EQ(*tree.find(11), "11.");
    EXPECT_EQ(tree.find(1), nullptr);
}

TEST(TestBinaryTree, check_erase_leaf) {
    BinaryTree<int, std::string> tree;
    tree.insert(1, "1.");
    tree.insert(2, "2.");
    tree.insert(3, "3.");
    tree.insert(4, "4.");
    tree.insert(5, "5.");
    tree.insert(6, "6.");
    tree.erase(4);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print_W();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "1:1. 2:2. 3:3. 6:6. 5:5. \n");
}

TEST(TestBinaryTree, check_erase_node) {
    BinaryTree<int, std::string> tree;
    tree.insert(1, "1.");
    tree.insert(2, "2.");
    tree.insert(3, "3.");
    tree.insert(4, "4.");
    tree.insert(5, "5.");
    //tree.insert(6, "6.");
    tree.erase(2);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print_W();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "1:1. 5:5. 3:3. 4:4. \n");
}
TEST(TestBinaryTree, check_erase_single_root) {
    BinaryTree<int, std::string> tree;
    tree.insert(1, "1.");
    tree.erase(1);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print_W();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "");
}

TEST(TestBinaryTree, the_exception_is_when_erase_from_empty_tree) {
    BinaryTree<int, std::string> tree;
    ASSERT_ANY_THROW(tree.erase(2));
}

TEST(TestBinaryTree, check_clear) {
    BinaryTree<int, std::string> tree;
    tree.insert(1, "1.");
    tree.insert(2, "2.");
    tree.insert(3, "3.");
    tree.insert(4, "4.");
    tree.insert(5, "5.");
    tree.insert(6, "6.");
    tree.erase(2);
    tree.erase(1);

    tree.clear();

    EXPECT_TRUE(tree.is_empty());

    tree.insert(34, "34.");
    tree.insert(56, "56.");

    EXPECT_FALSE(tree.is_empty());
}

TEST(TestBinaryTree, check_print) {
    BinaryTree<int, std::string> tree(1, "1.");
    tree.insert(2, "2.");
    tree.insert(3, "3.");
    tree.insert(4, "4.");
    tree.insert(5, "5.");
    tree.insert(6, "6.");
    tree.insert(7, "7.");
    tree.insert(8, "8.");
    tree.insert(9, "9.");
    tree.insert(10, "10.");
    tree.insert(11, "11.");

    std::stringstream buffer_W;
    std::streambuf* old = std::cout.rdbuf(buffer_W.rdbuf());
    tree.print_W();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer_W.str(), "1:1. 2:2. 3:3. 4:4. 5:5. 6:6. 7:7. 8:8. 9:9. 10:10. 11:11. \n");

    std::stringstream buffer_DLCR;
    old = std::cout.rdbuf(buffer_DLCR.rdbuf());
    tree.print_DLCR();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer_DLCR.str(), "8:8. 4:4. 9:9. 2:2. 10:10. 5:5. 11:11. 1:1. 6:6. 3:3. 7:7. \n");

    std::stringstream buffer_DLRC;
    old = std::cout.rdbuf(buffer_DLRC.rdbuf());
    tree.print_DLRC();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer_DLRC.str(), "8:8. 9:9. 4:4. 10:10. 11:11. 5:5. 2:2. 6:6. 7:7. 3:3. 1:1. \n");

    std::stringstream buffer_DCLR;
    old = std::cout.rdbuf(buffer_DCLR.rdbuf());
    tree.print_DCLR();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer_DCLR.str(), "1:1. 2:2. 4:4. 8:8. 9:9. 5:5. 10:10. 11:11. 3:3. 6:6. 7:7. \n");
}

//TEST(TestBinaryTree, the_exception_is_when_) {
//    BinaryTree<int, std::string> tree(1, "1.");
//    tree.insert(2, "2.");
//    tree.insert(3, "3.");
//    tree.insert(4, "4.");
//    tree.insert(5, "5.");
//    tree.insert(6, "6.");
//    tree.insert(7, "7.");
//    tree.insert(8, "8.");
//    tree.insert(9, "9.");
//    tree.insert(10, "10.");
//    tree.insert(11, "11.");
//
//    EXPECT_EQ(tree.is_empty(), false);
//
//    tree.print_DLCR();
//    tree.print_DLRC();
//    tree.print_DCLR();
//
//    tree.clear();
//    tree.print_W();
//
//    std::cout << "-" << std::endl;
//
//    EXPECT_EQ(tree.is_empty(), true);
//}

#endif //TEST_BINARY_TREE