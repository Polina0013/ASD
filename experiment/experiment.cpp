// Copyright 2026 Pozdnova Polina

#include <unordered_set>
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

#include "..\lib_unsorted_table_on_vector\unsorted_table_on_vector.h"
#include "..\lib_sorted_table_on_vector\sorted_table_on_vector.h"
#include "..\lib_unsorted_table_on_list\unsorted_table_on_list.h"
#include "..\lib_unsorted_table_on_binary_tree\unsorted_table_on_binary_tree.h"
#include "..\lib_sorted_table_on_binary_search_tree\sorted_table_on_binary_search_tree.h"
#include "..\lib_sorted_table_on_avl_tree\sorted_table_on_avl_tree.h"
#include "..\lib_sorted_table_on_rb_tree\sorted_table_on_rb_tree.h"
#include "..\lib_hash_table\hash_table.h"
#include "..\lib_chained_hash_table\chained_hash_table.h"

#include "..\lib_polynom\polynom.h"

#define SIZE 100

#define INSERT
#define FIND
#define ERASE

using namespace std;
using namespace chrono;

random_device rd;
mt19937 gen(rd());

//std::string generatePolynomName() {
//    static std::random_device rd;
//    static std::mt19937 gen(rd());
//    static std::uniform_int_distribution<> digitDist(0, 9);
//
//    std::string name = "P";
//    for (int i = 0; i < 6; ++i) {
//        name += std::to_string(digitDist(gen));
//    }
//    return name;
//}

// ============================================================================
// RANDOM POLYNOMIAL - 3 monomials with random coefficients and powers
// ============================================================================

std::string generateUniquePolynomName(std::unordered_set<std::string>& usedNames) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> digitDist(0, 9);

    std::string name;
    do {
        name = "P";
        for (int i = 0; i < 6; ++i) {
            name += std::to_string(digitDist(gen));
        }
    } while (usedNames.find(name) != usedNames.end());

    usedNames.insert(name);
    return name;
}

TVector<Polynom> generateTestData(int size) {
    TVector<Polynom> data;
    data.reserve(size + 10);

    std::unordered_set<std::string> usedNames;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    uniform_real_distribution<> coeffDist(-10.0, 10.0);  // coefficient from -10 to 10
    uniform_int_distribution<> powDist(0, 5);            // power from 0 to 5
    uniform_int_distribution<> termCount(1, 5);          // 1 to 5 monomials per polynomial

    for (int i = 0; i < size + 10; ++i) {
        Polynom p;

        int numTerms = termCount(gen);

        for (int i = 0; i < numTerms; ++i) {
            // Generate coefficient (skip near-zero values)
            double coeff = coeffDist(gen);
            while (abs(coeff) < 0.01) {
                coeff = coeffDist(gen);
            }

            // Generate powers for x, y, z
            int powers[3] = {
                powDist(gen),  // x^power
                powDist(gen),  // y^power
                powDist(gen)   // z^power
            };

            // Create monomial and add to polynomial
            Monom m(coeff, powers);
            p = p + m;
        }



        p.set_name(generateUniquePolynomName(usedNames));
        //std::cout << p.get_name();
        data.push_back(p);
    }

    //for (int i = 0; i < size * 10; ++i) {
    //    std::cout << data[i].get_name() << " ";
    //}

    return data;
}

Polynom makePolynom(int id) {
    Polynom p;

    uniform_real_distribution<> coeffDist(-10.0, 10.0);  // coefficient from -10 to 10
    uniform_int_distribution<> powDist(0, 5);            // power from 0 to 5
    uniform_int_distribution<> termCount(1, 5);          // 1 to 5 monomials per polynomial

    int numTerms = termCount(gen);

    for (int i = 0; i < numTerms; ++i) {
        // Generate coefficient (skip near-zero values)
        double coeff = coeffDist(gen);
        while (abs(coeff) < 0.01) {
            coeff = coeffDist(gen);
        }

        // Generate powers for x, y, z
        int powers[3] = {
            powDist(gen),  // x^power
            powDist(gen),  // y^power
            powDist(gen)   // z^power
        };

        // Create monomial and add to polynomial
        Monom m(coeff, powers);
        p = p + m;
    }

    // If polynomial is empty (should not happen), add constant 1
    if (p.is_zero()) {
        Monom m(1.0);
        p = p + m;
        p.set_name("P" + to_string(id));
    }
 

    p.set_name("P" + to_string(id));

    return p;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    TVector<Polynom> testdata = generateTestData(SIZE);
    cout << "Test data is generated.\n";

    cout << "\n========================================\n";
    cout << "  TABLE PERFORMANCE TEST\n";
    cout << "========================================\n\n";

    //UnsortedTableOnBinaryTree<string, Polynom> table;
    //SortedTableOnRBTree<string, Polynom> table;
    //HashTableC<Polynom> table(100020);

    cout << "Start data insert...\n";
    auto startdata = high_resolution_clock::now();

    HashTableA<Polynom> table(100020, 17);

    for (int i = 0; i < SIZE; i++) {
        table.insert(testdata[i].get_name(), testdata[i]);
    }

    auto enddata = high_resolution_clock::now();

    cout << "Finish data insert.\n";
    auto durationdata = duration_cast<microseconds>(enddata - startdata);
    cout << "========================================\n";
    cout << "Time insert: " << durationdata.count() << " mics\n";
    cout << "or: " << durationdata.count() / 1000000.0 << " s\n";
    cout << "for 1: " << durationdata.count() / 1000000.0 / 10.0 << " s\n";
    cout << "========================================\n";

    cout << "Table is created.\n";
    cout << "Test data is copied.\n";
    cout << "SIZE:" << SIZE << "\n";

#ifdef INSERT

    cout << "Start insert...\n";
    auto start = high_resolution_clock::now();


    for (int i = 0; i < 10; i++) {
        table.insert(testdata[SIZE + i].get_name(), testdata[SIZE + i]);
    }


    auto end = high_resolution_clock::now();

    cout << "Finish insert.\n";
    auto duration = duration_cast<microseconds>(end - start);

    cout << "\n";
    cout << "========================================\n";
    cout << "Time insert: " << duration.count() << " mics\n";
    cout << "or: " << duration.count() / 1000000.0 << " s\n";
    cout << "for 1: " << duration.count() / 1000000.0 / 10.0 << " s\n";
    cout << "========================================\n";

#endif // INSERT

#ifdef FIND

    cout << "Start find...\n";
    auto start2 = high_resolution_clock::now();


    int startIndex2 = SIZE / 2;  // середина (например, 5000 при SIZE=10000)
    for (int j = 0; j < 10; ++j) {
        int idx = startIndex2 + j * 5;   // индексы: 5000, 5005, 5010, ..., 5045
        if (idx >= SIZE) break;         // защита от выхода за границы
        table.find(testdata[idx].get_name());
    }


    auto end2 = high_resolution_clock::now();

    cout << "Finish find.\n";
    auto duration2 = duration_cast<microseconds>(end2 - start2);

    cout << "\n";
    cout << "========================================\n";
    cout << "Time find: " << duration2.count() << " mics\n";
    cout << "or: " << duration2.count() / 1000000.0 << " s\n";
    cout << "for 1: " << duration2.count() / 1000000.0 / 10.0 << " s\n";
    cout << "========================================\n";

#endif // FIND

#ifdef ERASE

    cout << "Start erase...\n";
    auto start3 = high_resolution_clock::now();


    int startIndex3 = SIZE / 2;  // середина (например, 5000 при SIZE=10000)
    for (int j = 0; j < 10; ++j) {
        int idx = startIndex3 + j * 5;   // индексы: 5000, 5005, 5010, ..., 5045
        if (idx >= SIZE) break;         // защита от выхода за границы
        table.erase(testdata[idx].get_name());
    }


    auto end3 = high_resolution_clock::now();

    cout << "Finish erase.\n";
    auto duration3 = duration_cast<microseconds>(end3 - start3);

    cout << "\n";
    cout << "========================================\n";
    cout << "Time erase: " << duration3.count() << " mics\n";
    cout << "or: " << duration3.count() / 1000000.0 << " s\n";
    cout << "for 1: " << duration3.count() / 1000000.0 / 10.0 << " s\n";
    cout << "========================================\n";


#endif // ERASE


    return 0;
}