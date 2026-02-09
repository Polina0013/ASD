// Copyright 2025 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>
#include <unordered_set>

#include "..\lib_stack\stack.h"
#include "..\lib_list\list.h"

bool check_breckets(std::string str) {
    Stack<char> stack(str.length());

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

//bool is_in_mass(const char element, char arr[], int size) {
//    for (int i = 0; i < size; i++) {
//        if (element == arr[i]) {
//            return true;
//        }
//    }
//    return false;
//}
//
//void read_expression(std::string expression) {
//    int size = expression.size();
//    Stack<char> breckets_stack;
//    Stack<char> operators_and_numbers_stack;
//
//    char variables[3] = { 'x', 'y', 'z' };
//    char operators[5] = { '+', '-', '*', '/', '^' };
//    char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
//
//    std::string expression_without_spaces;
//
//    for (char element : expression) {
//        if (element != ' ') {
//            expression_without_spaces += element;
//        }
//    }
//    //std::cout << expression_without_spaces << std::endl;
//}



bool is_in_mass(char element, const char arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (element == arr[i]) {
            return true;
        }
    }
    return false;
}

void read_expression(std::string expression) {
    Stack<char> brackets_stack;

    const char variables[3] = { 'x', 'y', 'z' };
    const char operators[5] = { '+', '-', '*', '/', '^' };
    const char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    const char open_brackets[3] = { '(', '[', '{' };
    const char close_brackets[3] = { ')', ']', '}' };

    std::string expression_without_spaces;
    for (char ch : expression) {
        if (ch != ' ') {
            expression_without_spaces += ch;
        }
    }

    for (size_t i = 0; i < expression_without_spaces.length(); i++) {
        char current = expression_without_spaces[i];
        char prev = (i > 0) ? expression_without_spaces[i - 1] : '\0';
        char next = (i < expression_without_spaces.length() - 1) ? expression_without_spaces[i + 1] : '\0';

        if (!is_in_mass(current, variables, 3) &&
            !is_in_mass(current, operators, 5) &&
            !is_in_mass(current, numbers, 10) &&
            !is_in_mass(current, open_brackets, 3) &&
            !is_in_mass(current, close_brackets, 3)) {
            throw std::logic_error("Invalid character!");
        }

        if (is_in_mass(current, open_brackets, 3)) {
            brackets_stack.push(current);
        }
        else if (is_in_mass(current, close_brackets, 3)) {
            if (brackets_stack.is_empty()) { throw std::logic_error("Missing opened bracket!"); }

            char top_bracket = brackets_stack.top();
            int open_index = -1, close_index = -1;

            // Находим индексы скобок
            for (int j = 0; j < 3; j++) {
                if (top_bracket == open_brackets[j]) open_index = j;
                if (current == close_brackets[j]) close_index = j;
            }

            if (open_index != close_index) {
                throw std::logic_error("Bracket mismatch: " + std::string(1, top_bracket) +
                    " and " + std::string(1, current));
            }

            brackets_stack.pop();
        }

        // 3. Проверка операторов
        if (is_in_mass(current, operators, 5)) {
            // Оператор не может быть первым символом (кроме унарного минуса)
            if (i == 0 && current != '-') {
                throw std::logic_error("Missing first operand for operator: " + std::string(1, current));
            }

            // Оператор не может быть последним символом
            if (i == expression_without_spaces.length() - 1) {
                throw std::logic_error("Missing second operand for operator: " + std::string(1, current));
            }

            // После оператора не может быть другого оператора или закрывающей скобки
            if (is_in_mass(next, operators, 5) || is_in_mass(next, close_brackets, 3)) {
                throw std::logic_error("Missing operand after operator: " + std::string(1, current));
            }

            // Перед оператором не может быть другого оператора или открывающей скобки (кроме унарного минуса)
            if (i > 0 && is_in_mass(prev, operators, 5) && current != '-') {
                throw std::logic_error("Missing operation between operands");
            }
        }

        // 4. Проверка операндов (переменных и чисел)
        if (is_in_mass(current, variables, 3) || is_in_mass(current, numbers, 10)) {
            // Если после операнда идет другой операнд или открывающая скобка - пропущена операция
            if (next != '\0' &&
                (is_in_mass(next, variables, 3) ||
                    is_in_mass(next, numbers, 10) ||
                    is_in_mass(next, open_brackets, 3))) {
                throw std::logic_error("Missing operation between: " +
                    std::string(1, current) + " and " + std::string(1, next));
            }

            // Если это число, проверяем что оно не заканчивается оператором '^'
            if (is_in_mass(current, numbers, 10) && prev == '^') {
                // '^' требует второго операнда
            }
        }

        // 5. Специальная проверка для оператора '^'
        if (current == '^') {
            // После '^' должен быть операнд (число или переменная)
            if (next == '\0' ||
                (!is_in_mass(next, variables, 3) && !is_in_mass(next, numbers, 10))) {
                throw std::logic_error("Missing second operand for operator ^");
            }

            // Перед '^' должен быть операнд
            if (i == 0 ||
                (!is_in_mass(prev, variables, 3) && !is_in_mass(prev, numbers, 10) &&
                    prev != ')')) {
                throw std::logic_error("Missing first operand for operator ^");
            }
        }

        // 6. Проверка для унарного минуса
        if (current == '-' && i > 0) {
            // Унарный минус разрешен только после открывающей скобки или оператора
            bool is_unary_allowed = (is_in_mass(prev, open_brackets, 3) ||
                is_in_mass(prev, operators, 5) ||
                i == 0);

            if (!is_unary_allowed &&
                !is_in_mass(prev, variables, 3) &&
                !is_in_mass(prev, numbers, 10) &&
                prev != ')') {
                // Это не унарный минус, проверяем как обычный оператор
            }
        }
    }

    // 7. Проверка оставшихся скобок
    if (!brackets_stack.is_empty()) {
        throw std::logic_error("Missing closed bracket");
    }

    // 8. Дополнительная проверка: выражение не должно быть пустым
    if (expression_without_spaces.empty()) {
        throw std::logic_error("Empty expression");
    }

    // 9. Проверка на минимальную длину (хотя бы один операнд)
    bool has_operand = false;
    for (char ch : expression_without_spaces) {
        if (is_in_mass(ch, variables, 3) || is_in_mass(ch, numbers, 10)) {
            has_operand = true;
            break;
        }
    }

    if (!has_operand) {
        throw std::logic_error("Expression has no operands");
    }
}






















// 1. Алгоритм "Зайца и черепахи"
template <class T>
bool is_looped_floyd(List<T>& list) {
    if (list.is_empty()) return false;

    auto it_begin = list.begin();
    if (it_begin == list.end()) return false;

    Node<T>* slow = it_begin._current;  // черепаха
    Node<T>* fast = it_begin._current;  // заяц

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

// 2. Алгоритм с разворотом указателей (с копированием списка)
template <class T>
bool is_looped_reverse_copy(List<T> list) {
    if (list.is_empty()) return false;

    auto it_begin = list.begin();
    if (it_begin == list.end()) return false;

    Node<T>* current = it_begin._current;
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;
    Node<T>* start = it_begin._current;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;

        prev = current;
        current = next;

        if (current == start) {
            return true;
        }
    }

    return false;
}

// 3. Нахождение начала цикла (если есть)
template <class T>
Node<T>* find_loop(List<T>& list) {
    if (list.is_empty()) return nullptr;

    auto it_begin = list.begin();
    if (it_begin == list.end()) return nullptr;

    Node<T>* slow = it_begin._current;
    Node<T>* fast = it_begin._current;

    bool has_cycle = false;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            has_cycle = true;
            break;
        }
    }

    if (!has_cycle) return nullptr;

    slow = it_begin._current;

    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}