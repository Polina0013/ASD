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
}