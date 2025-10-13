/**
 * @file StackGet.cpp
 * @brief This file tests accessing values of Stack Nodes
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
#include <new>
#include <stack>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start StackGet test:\n";

        const std::initializer_list<int> expected{ 0,10,20 };

        dsa::Stack<int> stack1 = dsa::Stack<int>({ 20, 10, 0 });
        tests::compare("Stack1 top", stack1.top(), expected.begin()[0]);

        dsa::Stack<int> stack2 = dsa::Stack<int>({ 20, 10, 0 });
        tests::compare("Stack2 top", stack2.top(), expected.begin()[0]);

        const dsa::Stack<int> stack3 = dsa::Stack<int>({ 20, 10, 0 });
        tests::compare("Stack3 top", stack3.top(), expected.begin()[0]);


        std::cout << "Compare operations results with std container\n\n";

        const std::stack<int> std_stack1 = std::stack<int>({ 20, 10, 0 });
        tests::compare("Stack1 vs std", stack1, std_stack1);

        std::stack<int> std_stack2 = std::stack<int>({ 20, 10, 0 });
        tests::compare("Stack2 top vs std", stack2.top(), std_stack2.top());

        const std::stack<int> std_stack3 = std::stack<int>({ 20, 10, 0 });
        tests::compare("Stack3 top vs std", stack3.top(), std_stack3.top());
    }
    catch (const std::bad_alloc& exception)
    {
        std::cerr << "Caught std::bad_alloc: " << exception.what() << '\n';
        return 1;
    }
    catch (const std::runtime_error& exception)
    {
        std::cerr << "Caught std::runtime_error: " << exception.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unhandled unknown exception\n";
        return 1;
    }

    tests::print_stats();
    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
