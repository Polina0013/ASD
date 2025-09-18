// Copyright 2024 Marina Usova

#include <iostream>

//#define EASY_EXAMPLE
#define MATRIX_APP

#ifdef EASY_EXAMPLE
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {

    int a, b;
    float result;

    a = 1; b = 4;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (std::exception err) {
        std::cerr << err.what() << std::endl;
    }

    a = 1; b = 0;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (std::exception err) {
        std::cerr << err.what() << std::endl;
    }

  return 0;
}

#endif  // EASY_EXAMPLE


#ifdef MATRIX_APP
#include "..\lib_tvector\tvector.h"
#include "..\lib_mathvector\mathvector.h"
#include "..\lib_matrix\matrix.h"
#include "..\lib_trianglematrix\trianglematrix.h"

int start_menu() {
    std::cout << "**** The location of the output of the two matrices ****" << std::endl;
    std::cout << "Choose a work option:" << std::endl;
    std::cout << "1. Simple matrices" << std::endl;
    std::cout << "2. Triangular matrices" << std::endl;
    std::cout << "0. Exit" << std::endl;
    int choice;
    std::cin >> choice;
    return choice;
}

int matrices_menu() {
    std::cout << "**** The location of the output of the two matrices ****" << std::endl;
    std::cout << "Choose a work option:" << std::endl;
    std::cout << "1. Create the first matrix" << std::endl;
    std::cout << "2. Create the second matrix" << std::endl;
    std::cout << "3. Add" << std::endl;
    std::cout << "4. Subtract" << std::endl;
    std::cout << "5. Multiply" << std::endl;
    std::cout << "6. Back" << std::endl;
    std::cout << "0. Exit" << std::endl;
    int choice;
    std::cin >> choice;
    return choice;
}

int main() {
    while (1) {
        system("cls");

        bool isBack = false;

        int choice = start_menu();
        switch (choice)
        {
        case (1):
            while (isBack == false) {
                system("cls");

                Matrix<int> first_matrix;
                Matrix<int> second_matrix;
                Matrix<int> result_multiply;
                int M1, N1;
                int M2, N2;

                int choice = matrices_menu();
                switch (choice)
                {
                case (1):
                    std::cout << "Enter the size of the first matrix:" << std::endl;
                    std::cin >> M1 >> N1;
                    first_matrix = Matrix<int>(M1, N1);
                    std::cout << "First matrix create!" << std::endl;
                    system("pause");
                    continue;
                case (2):
                    std::cout << "Enter the size of the second matrix:" << std::endl;
                    std::cin >> M2 >> N2;
                    second_matrix = Matrix<int>(M2, N2);
                    std::cout << "Second matrix create!" << std::endl;
                    system("pause");
                    continue;
                case (3):
                    first_matrix = first_matrix.add(second_matrix); //
                    std::cout << "Add" << std::endl;
                    system("pause");
                    continue;
                case (4):
                    first_matrix = first_matrix.sub(second_matrix); //
                    std::cout << "Sub" << std::endl;
                    system("pause");
                    continue;
                case (5):
                    result_multiply = Matrix<int>(M1, N2);              //
                    result_multiply = first_matrix.mult(second_matrix); //
                    std::cout << "Mult" << std::endl;
                    system("pause");
                    continue;
                case (6):
                    isBack = true;
                    break;
                case (0):
                    return 0;
                default:
                    continue;
                }
            }
            break;
        case (2):
            while (isBack == false) {
                system("cls");

                TriangleMatrix<int> first_matrix;
                TriangleMatrix<int> second_matrix;
                TriangleMatrix<int> result_multiply;
                int M1;
                int M2;

                int choice = matrices_menu();
                switch (choice)
                {
                case (1):
                    std::cout << "Enter the size of the first matrix:" << std::endl;
                    std::cin >> M1;
                    first_matrix = TriangleMatrix<int>(M1);
                    std::cout << "First matrix create!" << std::endl;
                    system("pause");
                    continue;
                case (2):
                    std::cout << "Enter the size of the second matrix:" << std::endl;
                    std::cin >> M2;
                    second_matrix = TriangleMatrix<int>(M2);
                    std::cout << "Second matrix create!" << std::endl;
                    system("pause");
                    continue;
                case (3):
                    first_matrix = first_matrix.add(second_matrix); //
                    std::cout << "Add" << std::endl;
                    system("pause");
                    continue;
                case (4):
                    first_matrix = first_matrix.sub(second_matrix); //
                    std::cout << "Sub" << std::endl;
                    system("pause");
                    continue;
                case (5):
                    result_multiply = TriangleMatrix<int>(M1);          //
                    result_multiply = first_matrix.mult(second_matrix); //
                    std::cout << "Mult" << std::endl;
                    system("pause");
                    continue;
                case (6):
                    isBack = true;
                    break;
                case (0):
                    return 0;
                default:
                    continue;
                }
            }
            break;
        case (0):
            return 0;
        default:
            continue;
        }
    }
    return 0;
}

#endif // MATRIX_APP
