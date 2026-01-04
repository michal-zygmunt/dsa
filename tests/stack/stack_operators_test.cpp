/**
 * @file stack_operators_test.cpp
 * @brief This file tests overloading operators of Stack
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
#include <iostream>
#include <stack>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start stack_operators_test:\n";

        const dsa::Stack<int> stack1({ 1, 2, 3 });
        const dsa::Stack<int> stack2({ 1, 2, 6 });
        const dsa::Stack<int> stack3({ 1, 2, 3, 4 });
        std::cout << "Stack1:\t" << stack1 << '\n';
        std::cout << "Stack2:\t" << stack2 << '\n';
        std::cout << "Stack3:\t" << stack3 << "\n\n";

        std::cout << "Compare operators for objects of the same size\n\n";

        // intentional self-comparison, an object should be equal to itself
        // NOLINTNEXTLINE(misc-redundant-expression)
        tests::compare("Stack1 == stack1", stack1 == stack1, true);

        tests::compare("Stack1 != stack2", stack1 != stack2, true);

        tests::compare("Stack1 < stack2", stack1 < stack2, true);
        tests::compare("Stack2 < stack1", stack2 < stack1, false);

        tests::compare("Stack1 > stack2", stack1 > stack2, false);
        tests::compare("Stack2 > stack1", stack2 > stack1, true);

        tests::compare("Stack1 <= stack2", stack1 <= stack2, true);
        tests::compare("Stack2 <= stack1", stack2 <= stack1, false);

        tests::compare("Stack1 >= stack2", stack1 >= stack2, false);
        tests::compare("Stack2 >= stack1", stack2 >= stack1, true);

        std::cout << "Compare operators for objects of different size\n\n";

        tests::compare("Stack1 == stack3", stack1 == stack3, false);

        tests::compare("Stack1 != stack3", stack1 != stack3, true);

        tests::compare("Stack1 < stack3", stack1 < stack3, true);
        tests::compare("Stack3 < stack1", stack3 < stack1, false);
        tests::compare("Stack2 < stack3", stack2 < stack3, false);
        tests::compare("Stack3 < stack2", stack3 < stack2, true);

        tests::compare("Stack1 > stack3", stack1 > stack3, false);
        tests::compare("Stack3 > stack1", stack3 > stack1, true);
        tests::compare("Stack2 > stack3", stack2 > stack3, true);
        tests::compare("Stack3 > stack2", stack3 > stack2, false);

        tests::compare("Stack1 <= stack3", stack1 <= stack3, true);
        tests::compare("Stack3 <= stack1", stack3 <= stack1, false);
        tests::compare("Stack2 <= stack3", stack2 <= stack3, false);
        tests::compare("Stack3 <= stack2", stack3 <= stack2, true);

        tests::compare("Stack1 >= stack3", stack1 >= stack3, false);
        tests::compare("Stack3 >= stack1", stack3 >= stack1, true);
        tests::compare("Stack2 >= stack3", stack2 >= stack3, true);
        tests::compare("Stack3 >= stack2", stack3 >= stack2, false);


        std::cout << "Compare operations results with std container\n\n";

        const std::stack<int> std_stack1({ 1, 2, 3 });
        const std::stack<int> std_stack2({ 1, 2, 6 });
        const std::stack<int> std_stack3({ 1, 2, 3, 4 });

        // intentional self-comparison, an object should be equal to itself
        // NOLINTNEXTLINE(misc-redundant-expression)
        tests::compare("Stack1 == stack1 vs std", stack1 == stack1, std_stack1 == std_stack1);

        tests::compare("Stack1 != stack2 vs std", stack1 != stack2, std_stack1 != std_stack2);

        tests::compare("Stack1 < stack2 vs std", stack1 < stack2, std_stack1 < std_stack2);
        tests::compare("Stack2 < stack1 vs std", stack2 < stack1, std_stack2 < std_stack1);

        tests::compare("Stack1 > stack2 vs std", stack1 > stack2, std_stack1 > std_stack2);
        tests::compare("Stack2 > stack1 vs std", stack2 > stack1, std_stack2 > std_stack1);

        tests::compare("Stack1 <= stack2 vs std", stack1 <= stack2, std_stack1 <= std_stack2);
        tests::compare("Stack2 <= stack1 vs std", stack2 <= stack1, std_stack2 <= std_stack1);

        tests::compare("Stack1 >= stack2 vs std", stack1 >= stack2, std_stack1 >= std_stack2);
        tests::compare("Stack2 >= stack1 vs std", stack2 >= stack1, std_stack2 >= std_stack1);

        std::cout << "Compare operators for objects of different size\n\n";

        tests::compare("Stack1 == stack3 vs std", stack1 == stack3, std_stack1 == std_stack3);

        tests::compare("Stack1 != stack3 vs std", stack1 != stack3, std_stack1 != std_stack3);

        tests::compare("Stack1 < stack3 vs std", stack1 < stack3, std_stack1 < std_stack3);
        tests::compare("Stack3 < stack1 vs std", stack3 < stack1, std_stack3 < std_stack1);
        tests::compare("Stack2 < stack3 vs std", stack2 < stack3, std_stack2 < std_stack3);
        tests::compare("Stack3 < stack2 vs std", stack3 < stack2, std_stack3 < std_stack2);

        tests::compare("Stack1 > stack3 vs std", stack1 > stack3, std_stack1 > std_stack3);
        tests::compare("Stack3 > stack1 vs std", stack3 > stack1, std_stack3 > std_stack1);
        tests::compare("Stack2 > stack3 vs std", stack2 > stack3, std_stack2 > std_stack3);
        tests::compare("Stack3 > stack2 vs std", stack3 > stack2, std_stack3 > std_stack2);

        tests::compare("Stack1 <= stack3 vs std", stack1 <= stack3, std_stack1 <= std_stack3);
        tests::compare("Stack3 <= stack1 vs std", stack3 <= stack1, std_stack3 <= std_stack1);
        tests::compare("Stack2 <= stack3 vs std", stack2 <= stack3, std_stack2 <= std_stack3);
        tests::compare("Stack3 <= stack2 vs std", stack3 <= stack2, std_stack3 <= std_stack2);

        tests::compare("Stack1 >= stack3 vs std", stack1 >= stack3, std_stack1 >= std_stack3);
        tests::compare("Stack3 >= stack1 vs std", stack3 >= stack1, std_stack3 >= std_stack1);
        tests::compare("Stack2 >= stack3 vs std", stack2 >= stack3, std_stack2 >= std_stack3);
        tests::compare("Stack3 >= stack2 vs std", stack3 >= stack2, std_stack3 >= std_stack2);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
