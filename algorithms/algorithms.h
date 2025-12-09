// Copyright 2025 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>
#include "..\lib_stack\stack.h"

bool check_breckets(std::string str) {
    Stack<char> stack;

    for (size_t i = 0; i < str.length(); i++) {
        if ((str[i] == '(') || (str[i] == '[') || (str[i] == '{')) {
            stack.push(str[i]);
        }
        else {
            if ((!stack.is_empty()) &&
                ((str[i] == ')') && (stack.top() == '(') ||
                    (str[i] == ']') && (stack.top() == '[') ||
                    (str[i] == '}') && (stack.top() == '{'))) {
                stack.pop();
            }
            else return false;
        }
    }

    if (stack.is_empty()) return true;
    else return false;
}

void read_expression(std::string expression) {
    int size = expression.size();
    Stack<char> breckets_stack;
    Stack<char> operators_and_numbers_stack;

    char variables[3] = { 'x', 'y', 'z' };
    char operators[5] = { '+', '-', '*', '/', '^' };
    char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    std::string expression_without_spaces;

    for (char element : expression) {
        if (element != ' ') {
            expression_without_spaces += element;
        }
    }
    //std::cout << expression_without_spaces << std::endl;



}