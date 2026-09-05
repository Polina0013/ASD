// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include <sstream>
#include "..\lib_avl_tree\avl_tree.h"

//#define TEST_AVL_TREE
#ifdef TEST_AVL_TREE

TEST(TestAVLTree, the_exception_is_when_insert_of_multiple_values_using_the_same_key) {
    AVLTree<int, std::string> tree(15, "15.");
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
    EXPECT_EQ(buffer_W.str(), "3:3. 5:5. 7:7. 9:9. 15:15. 16:16. 30:30. 35:35. 40:40. \n");
}

TEST(TestAVLTree, check_find) {
    AVLTree<int, std::string> tree;
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
TEST(TestAVLTree, check_big_tree) {
    AVLTree<int, std::string> tree;
    tree.insert(60, "15.");
    tree.insert(30, "5.");
    tree.insert(80, "30.");
    tree.insert(10, "35.");
    tree.insert(50, "16.");
    tree.insert(70, "7.");
    tree.insert(90, "3.");
    tree.insert(5, "1.");
    tree.insert(20, "9.");
    tree.insert(40, "40.");
    tree.insert(55, "6.");

    tree.insert(3, "12.");

    tree.print();

    EXPECT_EQ(tree.get_root()->data.first, 30);
    EXPECT_EQ(tree.get_root()->right->data.first, 60);
    EXPECT_EQ(tree.get_root()->left->data.first, 10);
}

TEST(TestAVLTree, check_erase_leaf) {
    AVLTree<int, std::string> tree;
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

    EXPECT_EQ(buffer.str(), "3:3. 5:5. 6:6. 7:7. 9:9. 15:15. 16:16. 30:30. 35:35. \n");
}

TEST(TestAVLTree, check_erase_node) {
    AVLTree<int, std::string> tree;
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

    EXPECT_EQ(buffer.str(), "1:1. 3:3. 5:5. 6:6. 7:7. 9:9. 15:15. 17:17. 18:18. 19:19. 35:35. 40:40. \n");
}

TEST(TestAVLTree, check_erase_node_with_one_child) {
    AVLTree<int, std::string> tree;
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

    EXPECT_EQ(buffer.str(), "1:1. 5:5. 6:6. 7:7. 9:9. 15:15. 17:17. 18:18. 19:19. 30:30. 40:40. \n");
}

TEST(TestAVLTree, check_erase_with_two_rotate) {
    AVLTree<int, std::string> tree;
    tree.insert(15, "15.");
    tree.insert(5, "5.");
    tree.insert(30, "30.");
    tree.insert(35, "35.");
    tree.insert(18, "18.");
    tree.insert(7, "7.");
    tree.insert(3, "3.");
    tree.insert(1, "1.");
    tree.insert(40, "40.");
    tree.insert(17, "17.");
    tree.insert(19, "19.");
    tree.insert(20, "20.");

    tree.print();
    tree.erase(7);
    tree.print();

    EXPECT_EQ(tree.get_root()->data.first, 18);
    //std::stringstream buffer;
    //std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    //tree.print();
    //std::cout.rdbuf(old);

    //EXPECT_EQ(buffer.str(), "1:1. 5:5. 6:6. 7:7. 9:9. 15:15. 17:17. 18:18. 19:19. 30:30. 40:40. \n");
}

TEST(TestAVLTree, check_erase_single_root) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "1.");
    tree.erase(1);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.print();
    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "\n");
}

TEST(TestAVLTree, the_exception_is_when_erase_from_empty_tree) {
    AVLTree<int, std::string> tree;
    ASSERT_ANY_THROW(tree.erase(2));
}

TEST(TestAVLTree, check_clear) {
    AVLTree<int, std::string> tree;
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

#endif //TEST_AVL_TREE