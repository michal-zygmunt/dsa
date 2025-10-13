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
#include <new>
#include <stack>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start StackGrow test:\n";

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
