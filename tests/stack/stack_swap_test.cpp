/**
 * @file stack_swap_test.cpp
 * @brief This file tests functions swapping Stack objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2026 Michal Zygmunt
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
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start stack_swap_test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };

        dsa::Stack<int> stack1 = dsa::Stack<int>(il_1);
        dsa::Stack<int> stack2 = dsa::Stack<int>(il_2);
        stack1.swap(stack2);
        const std::initializer_list<int> expected1 = { 50, 40, 30, 20, 10 };
        tests::compare("Stack1", stack1, expected1);
        const std::initializer_list<int> expected2 = { 5, 4, 3, 2, 1 };
        tests::compare("Stack2", stack2, expected2);

        dsa::Stack<int> stack3 = dsa::Stack<int>(il_1);
        dsa::Stack<int> stack4;
        stack3.swap(stack4);
        const std::initializer_list<int> expected3 = { };
        tests::compare("Stack3", stack3, expected3);
        const std::initializer_list<int> expected4 = { 5, 4, 3, 2, 1 };
        tests::compare("Stack4", stack4, expected4);

        dsa::Stack<int> stack5 = dsa::Stack<int>(il_1);
        dsa::Stack<int> stack6 = dsa::Stack<int>(il_2);
        dsa::swap(stack5, stack6);
        const std::initializer_list<int> expected5 = { 50, 40, 30, 20, 10 };
        tests::compare("Stack5", stack5, expected5);
        const std::initializer_list<int> expected6 = { 5, 4, 3, 2, 1 };
        tests::compare("Stack6", stack6, expected6);

        dsa::Stack<int> stack7 = dsa::Stack<int>(il_1);
        dsa::Stack<int> stack8;
        dsa::swap(stack7, stack8);
        const std::initializer_list<int> expected7 = { };
        tests::compare("Stack7", stack7, expected7);
        const std::initializer_list<int> expected8 = { 5, 4, 3, 2, 1 };
        tests::compare("Stack8", stack8, expected8);

        // swap safe type
        static_assert(noexcept(swap(std::declval<dsa::Stack<int>&>(),
            std::declval<dsa::Stack<int>&>())));
        // swap throwing type
        static_assert(noexcept(swap(std::declval<dsa::Stack<tests::ThrowingType>&>(),
            std::declval<dsa::Stack<tests::ThrowingType>&>())));


        std::cout << "Compare operations results with std container\n\n";

        std::stack<int> std_stack1{ il_1 };
        std::stack<int> std_stack2{ il_2 };
        std_stack1.swap(std_stack2);
        tests::compare("Stack1 vs std", stack1, std_stack1);
        tests::compare("Stack2 vs std", stack2, std_stack2);

        std::stack<int> std_stack3{ il_1 };
        std::stack<int> std_stack4{};
        std_stack3.swap(std_stack4);
        tests::compare("Stack3 vs std", stack3, std_stack3);
        tests::compare("Stack4 vs std", stack4, std_stack4);

        std::stack<int> std_stack5(il_1);
        std::stack<int> std_stack6(il_2);
        std::swap(std_stack5, std_stack6);
        tests::compare("Stack5 vs std", stack5, std_stack5);
        tests::compare("Stack6 vs std", stack6, std_stack6);

        std::stack<int> std_stack7(il_1);
        std::stack<int> std_stack8;
        std::swap(std_stack7, std_stack8);
        tests::compare("Stack7 vs std", stack7, std_stack7);
        tests::compare("Stack8 vs std", stack8, std_stack8);

        // swap safe type
        static_assert(noexcept(swap(std::declval<std::stack<int>&>(),
            std::declval<std::stack<int>&>())));
        // swap throwing type
        static_assert(noexcept(swap(std::declval<std::stack<tests::ThrowingType>&>(),
            std::declval<std::stack<tests::ThrowingType>&>())));


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
