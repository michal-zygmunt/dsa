/**
 * @file StackOperators.cpp
 * @brief This file tests overloading operators of Stack
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/Stack.h"

#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start StackOperators test:\n";

    const dsa::Stack<int> stack1({ 1,2,3 });
    const dsa::Stack<int> stack2({ 4,5,6 });
    const dsa::Stack<int> stack3({ 1, 2, 3, 4 });
    std::cout << "Stack1:\t" << stack1 << '\n';
    std::cout << "Stack2:\t" << stack2 << '\n';
    std::cout << "Stack3:\t" << stack3 << "\n\n";

    std::cout << "Compare operators for objects of the same size\n\n";

    // intentional self-comparison, an object should be equal to itself
    // NOLINTNEXTLINE(misc-redundant-expression)
    tests::compare("Operator ==", stack1 == stack1, true);

    tests::compare("Operator !=", stack1 != stack2, true);

    tests::compare("Operator <", stack1 < stack2, true);

    tests::compare("Operator >", stack2 > stack1, true);

    tests::compare("Operator <=", stack1 <= stack2, true);

    tests::compare("Operator >=", stack2 >= stack1, true);

    std::cout << "Compare operators for objects of different size\n\n";

    tests::compare("Operator ==", stack1 == stack3, false);

    tests::compare("Operator !=", stack1 != stack3, true);

    tests::compare("Operator <", stack3 < stack2, true);

    tests::compare("Operator >", stack3 > stack1, true);

    tests::compare("Operator <=", stack1 <= stack3, true);

    tests::compare("Operator >=", stack2 >= stack3, true);

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
