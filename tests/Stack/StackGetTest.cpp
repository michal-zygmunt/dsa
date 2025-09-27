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
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start StackGet test:\n";

    const std::initializer_list<int> expected{ 0,10,20 };

    try
    {
        dsa::Stack<int> stack1 = dsa::Stack<int>({ 20, 10, 0 });
        auto top = stack1.top();
        tests::compare("Stack1 top", top, expected.begin()[0]);
        tests::compare("Stack1", stack1, expected);

        dsa::Stack<int> stack2 = dsa::Stack<int>({ 20, 10, 0 });
        top = stack2.top();
        tests::compare("Stack2 top", top, expected.begin()[0]);
        tests::compare("Stack2", stack2, expected);

        const dsa::Stack<int> stack3 = dsa::Stack<int>({ 20, 10, 0 });
        top = stack3.top();
        tests::compare("Stack3 top", top, expected.begin()[0]);
        tests::compare("Stack3", stack3, expected);
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
