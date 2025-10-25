/**
 * @file stack_set_test.cpp
 * @brief This file tests setting values of Stack
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
        std::cout << "Start stack_set_test:\n";

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


        std::cout << "Compare operations results with std container\n\n";

        std::stack<int> std_stack1;
        std_stack1.push(0);
        std_stack1.push(10);
        std_stack1.push(20);
        std_stack1.top() = 50;
        tests::compare("Stack1 vs std", stack1, std_stack1);

        std::stack<int> std_stack2;
        std_stack2.push(0);
        std_stack2.push(10);
        std_stack2.push(20);
        std::stack<int> std_stack3;
        std_stack3.push(0);
        std_stack3.push(10);
        std_stack3.push(50);
        std_stack2.swap(std_stack3);
        tests::compare("Stack2 vs std", stack2, std_stack2);
        tests::compare("Stack3 vs std", stack3, std_stack3);

        std::stack<int> std_stack4;
        std_stack4.push(0);
        std_stack4.push(10);
        std_stack4.push(50);
        std_stack4.swap(std_stack4);
        tests::compare("Stack4 vs std", stack4, std_stack4);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
