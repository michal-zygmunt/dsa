/**
 * @file StackSet.cpp
 * @brief This file tests setting values of Stack
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

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start StackSet test:\n";

    const std::initializer_list<int> expected{ 50,10,0 };

    dsa::Stack<int> stack1 = dsa::Stack<int>({ 0,10,20 });
    stack1.top() = 50;
    tests::compare("Stack1", stack1, expected);

    dsa::Stack<int> stack2 = dsa::Stack<int>({ 0,10,20 });
    dsa::Stack<int> stack3 = dsa::Stack<int>({ 0,10,50 });
    stack2.swap(stack3);
    tests::compare("Stack2", stack2, { 50,10,0 });
    tests::compare("Stack3", stack3, { 20,10,0 });

    dsa::Stack<int> stack4 = dsa::Stack<int>({ 0,10,50 });
    stack4.swap(stack4);
    tests::compare("Stack4", stack4, expected);

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
