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
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start StackShrink test:\n";

    dsa::Stack<int> stack1 = dsa::Stack<int>({ 0,10,20,30,40,50 });
    stack1.pop();
    stack1.pop();
    std::initializer_list<int> expected1 = { 30,20,10,0 };
    tests::compare("Stack1", stack1, expected1);

    dsa::Stack<int> stack2 = dsa::Stack<int>({ 0,10,20 });
    stack2.pop();
    stack2.pop();
    stack2.pop();
    std::initializer_list<int> expected2 = std::initializer_list<int>{ };
    tests::compare("Stack2", stack2, expected2);

    dsa::Stack<int> stack3 = dsa::Stack<int>({ 0,10,20 });
    tests::compare("stack3.size()", stack3.size(), static_cast<size_t>(3));

    dsa::Stack<int> stack4 = dsa::Stack<int>();
    stack4.pop();
    tests::compare("stack4.size()", stack4.size(), static_cast<size_t>(0));

    dsa::Stack<int> stack5;
    tests::compare("stack5.size()", stack5.size(), static_cast<size_t>(0));

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}