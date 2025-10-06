/**
 * @file StackCtors.cpp
 * @brief This file tests Stack constructors
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
#include <stdexcept>
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start StackCtors test:\n";

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

    try
    {
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

        std::cout << "Move ctor\n";
        dsa::Stack<int> temp_1(stack1);
        const dsa::Stack<int> stack6 = std::move(temp_1);
        tests::compare("Stack6", stack6, expected);

        std::cout << "Move assignment ctor\n";
        dsa::Stack<int> temp_2(stack1);
        dsa::Stack<int> stack7({ 0 });
        stack7 = std::move(temp_2);
        tests::compare("Stack7", stack7, expected);
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

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
