/**
 * @file StackGrow.cpp
 * @brief This file tests functions increasing Stack length
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

    std::cout << "Start StackGrow test:\n";

    std::initializer_list<int> expected{ 10, 20, 30, 40 };

    dsa::Stack<int> s1 = dsa::Stack<int>(40);
    s1.push(30);
    s1.push(20);
    s1.push(10);
    tests::compare("Stack s1", s1, expected);

    dsa::Stack<int> s2 = dsa::Stack<int>(40);
    s2.push_range({ 30, 20, 10 });
    tests::compare("Stack s2", s2, expected);

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
