/**
 * @file stack_shrink_test.cpp
 * @brief This file tests functions decreasing Stack length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/stack.h"

#include <cstddef>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <new>
#include <stack>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start stack_shrink_test:\n";

        dsa::Stack<int> stack1 = dsa::Stack<int>({ 0,10,20,30,40,50 });
        stack1.pop();
        stack1.pop();
        const std::initializer_list<int> expected1 = { 30,20,10,0 };
        tests::compare("Stack1", stack1, expected1);

        dsa::Stack<int> stack2 = dsa::Stack<int>({ 0,10,20 });
        stack2.pop();
        stack2.pop();
        stack2.pop();
        const std::initializer_list<int> expected2 = std::initializer_list<int>{ };
        tests::compare("Stack2", stack2, expected2);

        const dsa::Stack<int> stack3 = dsa::Stack<int>({ 0,10,20 });
        tests::compare("Stack3.size()", stack3.size(), static_cast<size_t>(3));

        dsa::Stack<int> stack4 = dsa::Stack<int>();
        stack4.pop();
        tests::compare("Stack4.size()", stack4.size(), static_cast<size_t>(0));

        const dsa::Stack<int> stack5;
        tests::compare("Stack5.size()", stack5.size(), static_cast<size_t>(0));


        std::cout << "Compare operations results with std container\n\n";

        std::stack<int> std_stack1 = std::stack<int>({ 0,10,20,30,40,50 });
        std_stack1.pop();
        std_stack1.pop();
        tests::compare("Stack1 vs std", stack1, std_stack1);

        std::stack<int> std_stack2 = std::stack<int>({ 0,10,20 });
        std_stack2.pop();
        std_stack2.pop();
        std_stack2.pop();
        tests::compare("Stack2 vs std", stack2, std_stack2);

        const std::stack<int> std_stack3 = std::stack<int>({ 0,10,20 });
        tests::compare("Stack3.size() vs std", stack3.size(), std_stack3.size());

        const std::stack<int> std_stack4 = std::stack<int>();
        // do not use pop on empty std::stack
        tests::compare("Stack4.size() vs std", stack4.size(), std_stack4.size());

        const std::stack<int> std_stack5;
        tests::compare("Stack5.empty() vs std", stack5.empty(), std_stack5.empty());


        tests::print_stats();
    }
    catch (const std::bad_alloc& exception)
    {
        tests::print_err_msg("Caught std::bad_alloc: ", &exception);
        return 1;
    }
    catch (const std::runtime_error& exception)
    {
        tests::print_err_msg("Caught std::runtime_error: ", &exception);
        return 2;
    }
    catch (const std::exception& exception)
    {
        tests::print_err_msg("Caught exception: ", &exception);
        return 3;
    }
    catch (...)
    {
        tests::print_err_msg("Unhandled unknown exception");
        return 4;
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}