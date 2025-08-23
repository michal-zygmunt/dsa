/**
 * @file StackShrink.cpp
 * @brief This file tests functions decreasing Stack length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/Stack.h"

#include <cstddef>
#include <initializer_list>
#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    std::cout << "Start StackShrink test:\n";

    dsa::Stack<int> s1 = dsa::Stack<int>({ 0,10,20,30,40,50 });
    s1.pop();
    s1.pop();
    std::initializer_list<int> expected_1 = { 30,20,10,0 };
    tests::compare("Stack s1", s1, expected_1);

    dsa::Stack<int> s2 = dsa::Stack<int>({ 0,10,20 });
    s2.pop();
    s2.pop();
    s2.pop();
    std::initializer_list<int> expected_2 = std::initializer_list<int>{ };
    tests::compare("Stack s2", s2, expected_2);

    dsa::Stack<int> s3 = dsa::Stack<int>({ 0,10,20 });
    tests::compare("s3.size()", s3.size(), static_cast<size_t>(3));

    dsa::Stack<int> s4 = dsa::Stack<int>();
    s4.pop();
    tests::compare("s4.size()", s4.size(), static_cast<size_t>(0));

    dsa::Stack<int> s5;
    tests::compare("s5.size()", s5.size(), static_cast<size_t>(0));

    return tests::failed;
}