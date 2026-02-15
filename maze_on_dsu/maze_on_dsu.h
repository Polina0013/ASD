// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>
#include <stdlib.h>     // srand
#include <time.h>       // time
#include <Windows.h>

#include "..\lib_dsu\dsu.h"



bool** generate(int X, int Y, int N, int M) {
    if ((N < 2) || (M < 2)) { throw std::invalid_argument("Wrong size!"); }

    int size_maze = N * M;
    DSU<int> maze(size_maze);

    int new_N = N * 2 + 1, new_M = M + 1, size_walls = new_N * new_M;
    bool** mass_the_walls_of_the_maze = new bool* [new_N];
    for (int i = 0; i < new_N; i++) {
        mass_the_walls_of_the_maze[i] = new bool[new_M];
    }

    for (int i = 0; i < new_N; i++) {
        for (int j = 0; j < new_M; j++) {
            if ((i % 2 == 0) && (j == M)) mass_the_walls_of_the_maze[i][j] = false;
            else mass_the_walls_of_the_maze[i][j] = true;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int random_on_the_right = rand() % 2;
            int random_on_the_bottom = rand() % 2;
            if ((random_on_the_right == 0) && (j != (M - 1)) && (maze.find_rec(i * M + j) != maze.find_rec(i * M + j + 1))) {   // + проверка на состояние в dsu, тогда не нужно убирать стену
                maze.union_sets(i * M + j, i * M + j + 1);
                mass_the_walls_of_the_maze[i * 2 + 1][j + 1] = false;
            }
            if ((random_on_the_bottom == 0) && (i != (N - 1)) && (maze.find_rec(i * M + j) != maze.find_rec(i * M + j + M))) {   // + проверка на состояние в dsu, тогда не нужно убирать стену
                maze.union_sets(i * M + j, i * M + j + M);
                mass_the_walls_of_the_maze[i * 2 + 2][j] = false;
            }
        }
    }

    int i_x = X / M, j_x = X % M, i_y = Y / M, j_y = Y % M;
    if (i_x == 0) mass_the_walls_of_the_maze[0][j_x] = false;
    else if (i_x == N - 1) mass_the_walls_of_the_maze[new_N - 1][j_x] = false;
    else if (j_x == 0) mass_the_walls_of_the_maze[i_x * 2 + 1][0] = false;
    else if (j_x == M - 1) mass_the_walls_of_the_maze[i_x * 2 + 1][new_M - 1] = false;

    if (i_y == 0) mass_the_walls_of_the_maze[0][j_y] = false;
    else if (i_y == N - 1) mass_the_walls_of_the_maze[new_N - 1][j_y] = false;
    else if (j_y == 0) mass_the_walls_of_the_maze[i_y * 2 + 1][0] = false;
    else if (j_y == M - 1) mass_the_walls_of_the_maze[i_y * 2 + 1][new_M - 1] = false;

    if (maze.find_rec(X) == maze.find_rec(Y)) return mass_the_walls_of_the_maze;
    else {
        for (int i = 0; i < new_N; i++) {
            delete[] mass_the_walls_of_the_maze[i];
        }
        delete[] mass_the_walls_of_the_maze;

        return generate(X, Y, N, M);
    }
}

void print(bool** labirint, int N, int M) {
    int new_N = N * 2 + 1, new_M = M + 1;
    for (int i = 0; i < new_N; i++) {
        for (int j = 0; j < new_M; j++) {
            if (i % 2 == 0) {
                //std::cout << " ";
                if (labirint[i][j] == true) std::cout << " --";
                else std::cout << "   ";
            }
            else {
                if (labirint[i][j] == true) std::cout << "|  ";
                else std::cout << "   ";
            }
        }
        std::cout << "\n";
    }

    //for (int i = 0; i < new_N; i++) {
    //    for (int j = 0; j < new_M; j++) {
    //        if (i % 2 == 0) {
    //            //std::cout << " ";
    //            if (labirint[i][j] == true) std::cout << " 1 ";
    //            else std::cout << " 0 ";
    //        }
    //        else {
    //            if (labirint[i][j] == true) std::cout << " 1 ";
    //            else std::cout << " 0 ";
    //        }
    //    }
    //    std::cout << "\n";
    //}
}