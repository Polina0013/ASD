// Copyright 2024 Marina Usova

#include <iostream>

//#define EASY_EXAMPLE
#define TVECTOR

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


#ifdef TVECTOR
#include "..\lib_tvector\tvector.h"

int start_menu() {
    std::cout << "Choose a work option:" << std::endl;
    std::cout << "1. Simple matrices" << std::endl;
    std::cout << "2. Triangular matrices" << std::endl;
    int choice;
    std::cin >> choice;
    return choice;
}

int main() {
    while (1) {
        system("cls");

        int choice = start_menu();
        switch (choice)
        {
        case (1):

            break;
        case (2):
            break;
        default:
            break;
        }
    }

}

#endif // TVECTOR
