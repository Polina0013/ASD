// Copyright 2026 Polina Pozdnova

#include <gtest/gtest.h>
#include "..\maze_on_dsu\maze_on_dsu.h"

//#define TEST_MAZE_ON_DSU
#ifdef TEST_MAZE_ON_DSU

TEST(TestMazeOnDsu, check_print) {
    //{1, 1, 1, 0},
    //{1, 0, 0, 1},
    //{1, 0, 1, 0},
    //{0, 1, 0, 0},
    //{1, 1, 1, 0};
    int N = 2, M = 3;
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

    mass_the_walls_of_the_maze[1][1] = false;
    mass_the_walls_of_the_maze[1][2] = false;
    mass_the_walls_of_the_maze[2][1] = false;
    mass_the_walls_of_the_maze[3][0] = false;
    mass_the_walls_of_the_maze[3][2] = false;
    mass_the_walls_of_the_maze[3][3] = false;

    print(mass_the_walls_of_the_maze, 2, 3);
}

TEST(TestMazeOnDsu, check_generation1) {
    int X = 0, Y = 9, N = 3, M = 5;
    bool** mass_the_walls_of_the_maze1 = generate(X, Y, N, M).first;
    print(mass_the_walls_of_the_maze1, N, M);

}

TEST(TestMazeOnDsu, check_generation2) {
    bool** mass_the_walls_of_the_maze1 = generate(8, 31, 5, 8).first;
    print(mass_the_walls_of_the_maze1, 5, 8);

}

TEST(TestMazeOnDsu, check_generation3) {
    bool** mass_the_walls_of_the_maze1 = generate(0, 63, 8, 8).first;
    print(mass_the_walls_of_the_maze1, 8, 8);

}
TEST(TestMazeOnDsu, check_generation4) {
    bool** mass_the_walls_of_the_maze1 = generate(0, 23, 3, 8).first;
    print(mass_the_walls_of_the_maze1, 3, 8);

}

TEST(TestMazeOnDsu, checking_the_absence_of_a_wall_at_the_entrance_and_exit) {
    bool** mass_the_walls_of_the_maze1 = generate(0, 8, 3, 3).first;
    print(mass_the_walls_of_the_maze1, 3, 3);
}

#endif // TEST_MAZE_ON_DSU