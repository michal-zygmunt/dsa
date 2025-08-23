/**
 * @file StackCtors.cpp
 * @brief This file tests Stack constructors
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/Stack.h"

#include <initializer_list>
#include <iostream>
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    std::cout << "Start StackCtors test:\n";

    std::initializer_list<int> expected{ 20,10,0 };

    std::cout << "Default ctor\n";
    dsa::Stack<int> s1;
    s1.push(0);
    s1.push(10);
    s1.push(20);
    tests::compare("Stack s1", s1, expected);

    std::cout << "Value ctor\n";
    dsa::Stack<int> s2(0);
    s2.push(10);
    s2.push(20);
    tests::compare("Stack s2", s2, expected);

    std::cout << "Initializer list ctor\n";
    dsa::Stack<int> s3({ 0, 10, 20 });
    tests::compare("Stack s3", s3, expected);

    std::cout << "Copy ctor\n";
    dsa::Stack<int> s4{ s1 };
    tests::compare("Stack s4", s4, expected);

    std::cout << "Copy assignment ctor\n";
    dsa::Stack<int> s5;
    s5.push(1);
    s5.push(2);
    s5.push(3);
    s5.push(4);
    s5.push(5);
    s5 = s1;
    tests::compare("Stack s5", s5, expected);

    std::cout << "Move ctor\n";
    dsa::Stack<int> temp_1(s1);
    dsa::Stack<int> s6 = std::move(temp_1);
    tests::compare("Stack s6", s6, expected);

    std::cout << "Move assignment ctor\n";
    dsa::Stack<int> temp_2(s1);
    dsa::Stack<int> s7(0);
    s7 = std::move(temp_2);
    tests::compare("Stack s7", s7, expected);

    return tests::failed;
}
