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

int select_data_type() {
    std::cout << "Select the data type:" << std::endl;
    std::cout << "1. int" << std::endl;
    std::cout << "2. float" << std::endl;
    //std::cout << "3. double" << std::endl;
    std::cout << "0. Exit" << std::endl;
    int choice;
    std::cin >> choice;
    return choice;
}

int start_menu() {
    std::cout << "Choose a work option:" << std::endl;
    std::cout << "1. Simple matrices" << std::endl;
    std::cout << "2. Triangular matrices" << std::endl;
    std::cout << "0. Exit" << std::endl;
    int choice;
    std::cin >> choice;
    return choice;
}

int simple_matrices_menu() {
    std::cout << "Choose a work option:" << std::endl;
    std::cout << "1. Create the first matrix" << std::endl;
    std::cout << "2. Create the second matrix" << std::endl;
    std::cout << "3. Add" << std::endl;
    std::cout << "4. Subtract" << std::endl;
    std::cout << "5. Multiply" << std::endl;
    std::cout << "6. Multiply by number" << std::endl;
    std::cout << "7. Divide by number" << std::endl;
    std::cout << "8. Back" << std::endl;
    std::cout << "0. Exit" << std::endl;
    int choice;
    std::cin >> choice;
    return choice;
}


int main() {
    while (1) {
        system("cls");
        int data_type = select_data_type();
        switch (data_type)
        {
        case (1): // int




            continue;
        case (2): // float

            continue;
        /*case (3): // double
            continue;*/
        default:
            continue;
        }

        Matrix<int> first_simple_matrix;
        Matrix<int> second_simple_matrix;
        Matrix<int> result;
        int rows_of_first_mat, cols_of_first_mat;
        int rows_of_second_mat, cols_of_second_mat;

        bool isBack = false;

        int choice = start_menu();
        switch (choice)
        {
        case (1):

            while (isBack == false) {
                system("cls");

                std::cout << first_simple_matrix << "\n";
                std::cout << second_simple_matrix << "\n";

                int choice = simple_matrices_menu();
                switch (choice)
                {
                case (1):
                    std::cout << "Enter the size of the first matrix (rows and columns): ";
                    std::cin >> rows_of_first_mat >> cols_of_first_mat;
                    first_simple_matrix = Matrix<int>(rows_of_first_mat, cols_of_first_mat);

                    std::cin >> first_simple_matrix;

                    std::cout << "First matrix created successfully!\n";
                    system("pause");
                    continue;
                case (2):
                    std::cout << "Enter the size of the second matrix (rows and columns): ";
                    std::cin >> rows_of_second_mat >> cols_of_second_mat;
                    first_simple_matrix = Matrix<int>(rows_of_second_mat, cols_of_second_mat);

                    std::cin >> second_simple_matrix;

                    std::cout << "Second matrix created successfully!\n";
                    system("pause");
                    continue;
                case (3):
                    //first_simple_matrix = first_simple_matrix.add(second_simple_matrix); //
                    //std::cout << "Add" << std::endl;
                    //system("pause");
                    continue;
                case (4):
                    //first_simple_matrix = first_simple_matrix.sub(second_simple_matrix); //
                    //std::cout << "Sub" << std::endl;
                    //system("pause");
                    continue;
                case (5):
                    //result = Matrix<int>(rows_of_first_mat, cols_of_second_mat);              //
                    //result = first_simple_matrix.mult(second_simple_matrix); //
                    //std::cout << "Mult" << std::endl;
                    //system("pause");
                    continue;
                case (6):
                    //result = Matrix<int>(rows_of_first_mat, cols_of_second_mat);              //
                    //result = first_simple_matrix.mult(second_simple_matrix); //
                    //std::cout << "Mult" << std::endl;
                    //system("pause");
                    continue;
                case (7):
                    //result = Matrix<int>(rows_of_first_mat, cols_of_second_mat);              //
                    //result = first_simple_matrix.mult(second_simple_matrix); //
                    //std::cout << "Mult" << std::endl;
                    //system("pause");
                    continue;
                case (8):
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
            //while (isBack == false) {
            //    system("cls");

            //    TriangleMatrix<int> first_simple_matrix;
            //    TriangleMatrix<int> second_simple_matrix;
            //    TriangleMatrix<int> result_multiply;
            //    int rows_of_first_mat;
            //    int rows_of_second_mat;

            //    int choice = simple_matrices_menu();
            //    switch (choice)
            //    {
            //    case (1):
            //        std::cout << "Enter the size of the first matrix:" << std::endl;
            //        std::cin >> rows_of_first_mat;
            //        first_simple_matrix = TriangleMatrix<int>(rows_of_first_mat);
            //        std::cout << "First matrix create!" << std::endl;
            //        system("pause");
            //        continue;
            //    case (2):
            //        std::cout << "Enter the size of the second matrix:" << std::endl;
            //        std::cin >> rows_of_second_mat;
            //        second_simple_matrix = TriangleMatrix<int>(rows_of_second_mat);
            //        std::cout << "Second matrix create!" << std::endl;
            //        system("pause");
            //        continue;
            //    case (3):
            //        first_simple_matrix = first_simple_matrix.add(second_simple_matrix); //
            //        std::cout << "Add" << std::endl;
            //        system("pause");
            //        continue;
            //    case (4):
            //        first_simple_matrix = first_simple_matrix.sub(second_simple_matrix); //
            //        std::cout << "Sub" << std::endl;
            //        system("pause");
            //        continue;
            //    case (5):
            //        result_multiply = TriangleMatrix<int>(rows_of_first_mat);          //
            //        result_multiply = first_simple_matrix.mult(second_simple_matrix); //
            //        std::cout << "Mult" << std::endl;
            //        system("pause");
            //        continue;
            //    case (6):
            //        isBack = true;
            //        break;
            //    case (0):
            //        return 0;
            //    default:
            //        continue;
            //    }
            //}
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
