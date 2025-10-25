/**
 * @file stack_grow_test.cpp
 * @brief This file tests functions increasing Stack length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/stack.h"

#include <exception>
#include <initializer_list>
#include <iostream>
#include <stack>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start stack_grow_test:\n";

        const std::initializer_list<int> expected{ 10, 20, 30, 40 };

        dsa::Stack<int> stack1 = dsa::Stack<int>({ 40 });
        stack1.push(30);
        stack1.push(20);
        stack1.push(10);
        tests::compare("Stack1", stack1, expected);


        std::cout << "Compare operations results with std container\n\n";

        std::stack<int> std_stack1 = std::stack<int>({ 40 });
        std_stack1.push(30);
        std_stack1.push(20);
        std_stack1.push(10);
        tests::compare("Stack1 vs std", stack1, std_stack1);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
