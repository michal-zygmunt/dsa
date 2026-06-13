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
#include "dsa/list.h"
#include "dsa/stack.h"

#include <cassert>
#include <compare>
#include <deque>
#include <exception>
#include <iostream>
#include <limits>
#include <stack>
#include <type_traits>

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

        // test three way comparison

        tests::compare("Stack1 <=> stack2 !=", (stack1 <=> stack2) != 0, (stack1 <=> stack2) != 0);
        tests::compare("Stack1 <=> stack2 <", (stack1 <=> stack2) < 0, (stack1 <=> stack2) < 0);
        tests::compare("Stack1 <=> stack2 >", (stack1 <=> stack2) > 0, (stack1 <=> stack2) > 0);
        tests::compare("Stack1 <=> stack2 <=", (stack1 <=> stack2) <= 0, (stack1 <=> stack2) <= 0);
        tests::compare("Stack1 <=> stack2 >=", (stack1 <=> stack2) >= 0, (stack1 <=> stack2) >= 0);

        tests::compare("Stack1 <=> stack2 <", (stack1 <=> stack2) == std::weak_ordering::less, true);
        tests::compare("Stack1 <=> stack2 <>", (stack1 <=> stack2) != std::weak_ordering::equivalent, true);
        tests::compare("Stack1 <=> stack2 <=", (stack1 <=> stack2) != std::weak_ordering::greater, true);

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

        // test three way comparison

        tests::compare("Stack1 <=> stack3 ==", (stack1 <=> stack3) == 0, false);
        tests::compare("Stack1 <=> stack3 <", (stack1 <=> stack3) < 0, true);
        tests::compare("Stack1 <=> stack3 >", (stack1 <=> stack3) > 0, false);
        tests::compare("Stack1 <=> stack3 <=", (stack1 <=> stack3) <= 0, true);
        tests::compare("Stack1 <=> stack3 >=", (stack1 <=> stack3) >= 0, false);

        tests::compare("Stack1 <=> stack3 >=", (stack1 <=> stack3) != std::weak_ordering::less, false);
        tests::compare("Stack1 <=> stack3 ==", (stack1 <=> stack3) == std::weak_ordering::equivalent, false);
        tests::compare("Stack1 <=> stack3 <=", (stack1 <=> stack3) != std::weak_ordering::greater, true);

        // test comparison categories
        static_assert(std::is_same_v<std::compare_three_way_result_t<dsa::Stack<int>>, std::strong_ordering>,
            "Int stack should support strong ordering");

        static_assert(std::is_same_v<std::compare_three_way_result_t<dsa::Stack<double>>, std::partial_ordering>,
            "Double stack should support strong ordering");

        // test partial ordering
        const dsa::Stack<double> stack7{ dsa::List<double>{1.0, 2.0, 3.0} };
        const dsa::Stack<double> stack8{ dsa::List<double>{1.0, 2.0, std::numeric_limits<double>::quiet_NaN()} };
        assert((stack7 <=> stack8) == std::partial_ordering::unordered);
        tests::compare("Stack7 <=> stack8 weak ordering", (stack7 <=> stack8) != std::weak_ordering::less, true);

        // test noexcept

        // operators
        static_assert(!noexcept(
            dsa::Stack<tests::ThrowingType>{dsa::List<tests::ThrowingType>(1)} ==
            dsa::Stack<tests::ThrowingType>{dsa::List<tests::ThrowingType>(1)}));
        static_assert(!noexcept(
            dsa::Stack<tests::ThrowingType>{dsa::List<tests::ThrowingType>(1)} <=>
            dsa::Stack<tests::ThrowingType>{dsa::List<tests::ThrowingType>(1)}));


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

        // test three way comparison

        tests::compare("Stack1 <=> stack2 vs std !=", (stack1 <=> stack2) != 0, (std_stack1 <=> std_stack2) != 0);
        tests::compare("Stack1 <=> stack2 vs std <", (stack1 <=> stack2) < 0, (std_stack1 <=> std_stack2) < 0);
        tests::compare("Stack1 <=> stack2 vs std >", (stack1 <=> stack2) > 0, (std_stack1 <=> std_stack2) > 0);
        tests::compare("Stack1 <=> stack2 vs std <=", (stack1 <=> stack2) <= 0, (std_stack1 <=> std_stack2) <= 0);
        tests::compare("Stack1 <=> stack2 vs std >=", (stack1 <=> stack2) >= 0, (std_stack1 <=> std_stack2) >= 0);

        tests::compare("Stack1 <=> stack2 vs std <",
            (stack1 <=> stack2) == std::weak_ordering::less, (std_stack1 <=> std_stack2) == std::weak_ordering::less);
        tests::compare("Stack1 <=> stack2 vs std <>",
            (stack1 <=> stack2) != std::weak_ordering::equivalent, (std_stack1 <=> std_stack2) != std::weak_ordering::equivalent);
        tests::compare("Stack1 <=> stack2 vs std <=",
            (stack1 <=> stack2) != std::weak_ordering::greater, (std_stack1 <=> std_stack2) != std::weak_ordering::greater);

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

        // test three way comparison

        tests::compare("Stack1 <=> stack3 vs std ==", (stack1 <=> stack3) == 0, (std_stack1 <=> std_stack3) == 0);
        tests::compare("Stack1 <=> stack3 vs std <", (stack1 <=> stack3) < 0, (std_stack1 <=> std_stack3) < 0);
        tests::compare("Stack1 <=> stack3 vs std >", (stack1 <=> stack3) > 0, (std_stack1 <=> std_stack3) > 0);
        tests::compare("Stack1 <=> stack3 vs std <=", (stack1 <=> stack3) <= 0, (std_stack1 <=> std_stack3) <= 0);
        tests::compare("Stack1 <=> stack3 vs std >=", (stack1 <=> stack3) >= 0, (std_stack1 <=> std_stack3) >= 0);

        tests::compare("Stack1 <=> stack3 vs std >=",
            (stack1 <=> stack3) != std::weak_ordering::less, (std_stack1 <=> std_stack3) != std::weak_ordering::less);
        tests::compare("Stack1 <=> stack3 vs std ==",
            (stack1 <=> stack3) == std::weak_ordering::equivalent, (std_stack1 <=> std_stack3) == std::weak_ordering::equivalent);
        tests::compare("Stack1 <=> stack3 vs std <= ",
            (stack1 <=> stack3) != std::weak_ordering::greater, (std_stack1 <=> std_stack3) != std::weak_ordering::greater);

        // test comparison categories
        static_assert(std::is_same_v<std::compare_three_way_result_t<std::stack<int>>, std::strong_ordering>,
            "Int stack should support strong ordering");

        static_assert(std::is_same_v<std::compare_three_way_result_t<std::stack<double>>, std::partial_ordering>,
            "Double stack should support strong ordering");

        // test partial ordering
        const std::stack<double> std_stack7{ std::deque<double>{1.0, 2.0, 3.0} };
        const std::stack<double> std_stack8{ std::deque<double>{1.0, 2.0, std::numeric_limits<double>::quiet_NaN()} };
        assert((std_stack7 <=> std_stack8) == std::partial_ordering::unordered);
        assert((stack7 <=> stack8) == (std_stack7 <=> std_stack8));
        tests::compare("std_stack7 <=> std_stack8 weak ordering",
            (std_stack7 <=> std_stack8) == std::partial_ordering::unordered, true);
        tests::compare("(stack7 <=> stack8) == (std_stack7 <=> std_stack8)",
            (stack7 <=> stack8) == (std_stack7 <=> std_stack8), true);

        // test noexcept

        // operators
        static_assert(!noexcept(
            std::stack<tests::ThrowingType>{std::deque<tests::ThrowingType>(1)} ==
            std::stack<tests::ThrowingType>{std::deque<tests::ThrowingType>(1)}));
        static_assert(!noexcept(
            std::stack<tests::ThrowingType>{std::deque < tests::ThrowingType>(1)} <=>
            std::stack<tests::ThrowingType>{std::deque < tests::ThrowingType>(1)}));


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
