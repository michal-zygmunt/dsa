/**
 * @file stack_ctors_test.cpp
 * @brief This file tests Stack constructors
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
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start stack_ctors_test:\n";

        const std::initializer_list<int> expected{ 20,10,0 };

        std::cout << "Default ctor\n";
        dsa::Stack<int> stack1;
        stack1.push(0);
        stack1.push(10);
        stack1.push(20);
        tests::compare("Stack1", stack1, expected);

        std::cout << "Value ctor\n";
        dsa::Stack<int> stack2({ 0 });
        stack2.push(10);
        stack2.push(20);
        tests::compare("Stack2", stack2, expected);

        std::cout << "Initializer list ctor\n";
        const dsa::Stack<int> stack3({ 0, 10, 20 });
        tests::compare("Stack3", stack3, expected);


        std::cout << "Copy ctor\n";
        // intentionally make a copy to test copy constructor
        // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
        const dsa::Stack<int> stack4{ stack1 };
        tests::compare("Stack4", stack4, expected);

        std::cout << "Copy assignment ctor\n";
        dsa::Stack<int> stack5;
        stack5.push(1);
        stack5.push(2);
        stack5.push(3);
        stack5.push(4);
        stack5.push(5);
        stack5 = stack1;
        tests::compare("Stack5", stack5, expected);

        std::cout << "Copy self assignment ctor\n";
        dsa::Stack<int> stack6{ 0, 10, 20 };
        auto* pointer6 = &stack6;
        stack6 = *pointer6;
        tests::compare("Stack6", stack6, expected);

        std::cout << "Move ctor\n";
        dsa::Stack<int> temp_1(stack1);
        const dsa::Stack<int> stack7 = std::move(temp_1);
        tests::compare("Stack7", stack7, expected);

        std::cout << "Move assignment ctor\n";
        dsa::Stack<int> temp_2(stack1);
        dsa::Stack<int> stack8({ 0 });
        stack8 = std::move(temp_2);
        tests::compare("Stack8", stack8, expected);

        std::cout << "Move self assignment ctor\n";
        dsa::Stack<int> stack9{ 0, 10, 20 };
        auto* pointer9 = &stack9;
        stack9 = std::move(*pointer9);
        tests::compare("Stack9", stack9, expected);


        std::cout << "Compare operations results with std container\n\n";

        std::stack<int> std_stack1;
        std_stack1.push(0);
        std_stack1.push(10);
        std_stack1.push(20);
        tests::compare("Stack1 vs std", stack1, std_stack1);

        std::stack<int> std_stack2({ 0 });
        std_stack2.push(10);
        std_stack2.push(20);
        tests::compare("Stack2 vs std", stack2, std_stack2);

        const std::stack<int> std_stack3({ 0, 10, 20 });
        tests::compare("Stack3 vs std", stack3, std_stack3);

        const std::stack<int> std_stack4{ std_stack1 };
        tests::compare("Stack4 vs std", stack4, expected);

        std::stack<int> std_stack5{ std_stack1 };
        std_stack5.push(1);
        std_stack5.push(2);
        std_stack5.push(3);
        std_stack5.push(4);
        std_stack5.push(5);
        std_stack5 = std_stack1;
        tests::compare("Stack5 vs std", stack5, std_stack5);

        std::stack<int> std_temp_1(std_stack1);
        const std::stack<int> std_stack6 = std::move(std_temp_1);
        tests::compare("Stack6 vs std", stack6, std_stack6);

        std::stack<int> std_temp_2(std_stack1);
        std::stack<int> std_stack7;
        std_stack7.push(0);
        std_stack7 = std::move(std_temp_2);
        tests::compare("Stack7 vs std", stack7, std_stack7);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
