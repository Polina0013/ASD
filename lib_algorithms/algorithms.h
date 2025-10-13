// Copyright 2025 Pozdnova Polina

#pragma once

#include <iostream>
#include <initializer_list>
#include <stdexcept>

#include "../lib_algorithms/algorithms.h"
#include "../lib_matrix/matrix.h"

template<class T>
T find_local_minimum_of_the_matrix(Matrix<T>& square_matrix, int row, int column) { // отсчет с 0
    int size = square_matrix.get_rows();

    if (row < 0 || row >= size || column < 0 || column >= size) throw std::logic_error("Index out of range in find_local_minimum_of_the_matrix");

    T local_minimum = square_matrix[row][column];
    int l_row = row, l_column = column;

    T min_value = local_minimum;
    int min_row = row, min_col = column;

    // вверх
    if (row > 0 && square_matrix[row - 1][column] < min_value) {
        min_value = square_matrix[row - 1][column];
        min_row = row - 1;
        min_col = column;
    }

    // вниз
    if (row < size - 1 && square_matrix[row + 1][column] < min_value) {
        min_value = square_matrix[row + 1][column];
        min_row = row + 1;
        min_col = column;
    }

    // влево
    if (column > 0 && square_matrix[row][column - 1] < min_value) {
        min_value = square_matrix[row][column - 1];
        min_row = row;
        min_col = column - 1;
    }

    // вправо
    if (column < size - 1 && square_matrix[row][column + 1] < min_value) {
        min_value = square_matrix[row][column + 1];
        min_row = row;
        min_col = column + 1;
    }

    if (min_value == local_minimum) return local_minimum;
    return find_local_minimum_of_the_matrix(square_matrix, min_row, min_col);
}
