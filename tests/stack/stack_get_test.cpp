/**
 * @file stack_get_test.cpp
 * @brief This file tests accessing values of Stack Nodes
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
#include <new>
#include <stack>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start stack_get_test:\n";

        const std::initializer_list<int> expected{ 0,10,20 };

        dsa::Stack<int> stack1 = dsa::Stack<int>({ 20, 10, 0 });
        tests::compare("Stack1 top", stack1.top(), *expected.begin());

        dsa::Stack<int> stack2 = dsa::Stack<int>({ 20, 10, 0 });
        tests::compare("Stack2 top", stack2.top(), *expected.begin());

        const dsa::Stack<int> stack3 = dsa::Stack<int>({ 20, 10, 0 });
        tests::compare("Stack3 top", stack3.top(), *expected.begin());


        std::cout << "Compare operations results with std container\n\n";

        const std::stack<int> std_stack1 = std::stack<int>({ 20, 10, 0 });
        tests::compare("Stack1 vs std", stack1, std_stack1);

        std::stack<int> std_stack2 = std::stack<int>({ 20, 10, 0 });
        tests::compare("Stack2 top vs std", stack2.top(), std_stack2.top());

        const std::stack<int> std_stack3 = std::stack<int>({ 20, 10, 0 });
        tests::compare("Stack3 top vs std", stack3.top(), std_stack3.top());


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
