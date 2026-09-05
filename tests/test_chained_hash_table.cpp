// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\lib_chained_hash_table\chained_hash_table.h"
#include "..\lib_tvector\tvector.h"


//#define TEST_CHAINED_HASH_TABLE
#ifdef TEST_CHAINED_HASH_TABLE

TEST(TestChainedHashTable, check_merging_dictionaries) {
    TVector<std::pair<std::string, int>> dictionary1;
    dictionary1.push_back(std::pair("table", 1349));
    dictionary1.push_back(std::pair("hash", 1985));
    dictionary1.push_back(std::pair("list", 4372));

    TVector<std::pair<std::string, int>> dictionary2;
    dictionary2.push_back(std::pair("massive", 4312));
    dictionary2.push_back(std::pair("list", 5863));
    dictionary2.push_back(std::pair("hash", 4317));
    dictionary2.push_back(std::pair("vector", 2586));

    HashTableC<int> hash_table(20);

    for (int i = 0; i < dictionary1.size(); i++) {
        hash_table.insert(dictionary1[i].first, dictionary1[i].second);
    }

    for (int i = 0; i < dictionary2.size(); i++) {
        try {
            hash_table.insert(dictionary2[i].first, dictionary2[i].second);
        }
        catch (const std::logic_error& ex) {}
    }

    hash_table.print(std::cout);

    //hash_table.erase("massive");
    //hash_table.print(std::cout);
}

TEST(TestChainedHashTable, check_for_a_collision) {
    HashTableC<int> t1(20);

    t1.insert("cat", 0);
    t1.insert("cta", 1);
    t1.insert("tca", 2);
    t1.insert("tac", 3);
    t1.insert("act", 4);
    t1.insert("atc", 5);

    std::cout << t1;

    EXPECT_EQ(t1.find("atc"), 5);
}

TEST(TestChainedHashTable, the_exception_is_when_insert_not_a_unique_key) {
    HashTableC<int> t1(20);

    t1.insert("Third", 3);
    t1.insert("Second", 2);
    t1.insert("First", 1);
    t1.insert("Fourth", 4);
    t1.insert("Fifth", 5);
    t1.insert("Twentieth", 20);
    t1.insert("Thirtieth", 30);

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.insert("Third", 3));
}

TEST(TestChainedHashTable, check_the_insert_after_erase) {
    HashTableC<int> t1(20);

    t1.insert("Third", 3);
    t1.insert("Second", 2);
    t1.insert("First", 1);
    t1.erase("First");
    t1.insert("Fourth", 4);
    t1.insert("Fifth", 5);
    t1.insert("Twentieth", 20);
    t1.insert("Thirtieth", 30);

    //std::cout << t1;

    EXPECT_EQ(t1.find("Thirtieth"), 30);
}

TEST(TestChainedHashTable, check_the_erase) {
    HashTableC<int> t1(20);

    t1.insert("Third", 3);
    t1.insert("Second", 2);
    t1.insert("First", 1);
    t1.insert("Fourth", 4);
    t1.insert("Fifth", 5);
    t1.insert("Twentieth", 20);
    t1.insert("Thirtieth", 30);

    t1.erase("Second");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.find("Second"));
}

TEST(TestChainedHashTable, the_exception_is_when_deleting_by_a_key_that_does_not_exist) {
    HashTableC<int> t1(20);

    t1.insert("Third", 3);
    t1.insert("Second", 2);
    t1.insert("First", 1);
    t1.insert("Fourth", 4);
    t1.insert("Fifth", 5);
    t1.insert("Twentieth", 20);

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.erase("Thirtieth"));
}

TEST(TestChainedHashTable, check_the_key_find) {
    HashTableC<std::string> t1(20);

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    //std::cout << t1;

    EXPECT_EQ(t1.find("r974"), "when");
}

TEST(TestChainedHashTable, the_exception_is_when_the_key_is_not_found) {
    HashTableC<std::string> t1(20);

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");

    //std::cout << t1;

    ASSERT_ANY_THROW(t1.find("r1024"));
}

TEST(TestChainedHashTable, check_an_empty_table) {
    HashTableC<double> t1(20);

    t1.insert("it is double", 1.5);
    t1.insert("it is double too", 3.7);

    EXPECT_FALSE(t1.is_empty());

    t1.erase("it is double");
    t1.erase("it is double too");

    //std::cout << t1;

    EXPECT_TRUE(t1.is_empty());
}

#endif //TEST_CHAINED_HASH_TABLE