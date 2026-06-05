/**
 * @file queue_operators_test.cpp
 * @brief This file tests overloading operators of Queue
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/list.h"
#include "dsa/queue.h"

#include <cassert>
#include <compare>
#include <deque>
#include <exception>
#include <iostream>
#include <limits>
#include <queue>
#include <type_traits>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start queue_operators_test:\n";

        const dsa::Queue<int> queue1({ 1, 2, 3 });
        const dsa::Queue<int> queue2({ 1, 2, 6 });
        const dsa::Queue<int> queue3({ 1, 2, 3, 4 });
        std::cout << "Queue1:\t" << queue1 << '\n';
        std::cout << "Queue2:\t" << queue2 << '\n';
        std::cout << "Queue3:\t" << queue3 << "\n\n";

        std::cout << "Compare operators for objects of the same size\n\n";

        // intentional self-comparison, an object should be equal to itself
        // NOLINTNEXTLINE(misc-redundant-expression)
        tests::compare("Queue1 == queue1", queue1 == queue1, true);

        tests::compare("Queue1 != queue2", queue1 != queue2, true);

        tests::compare("Queue1 < queue2", queue1 < queue2, true);
        tests::compare("Queue2 < queue1", queue2 < queue1, false);

        tests::compare("Queue1 > queue2", queue1 > queue2, false);
        tests::compare("Queue2 > queue1", queue2 > queue1, true);

        tests::compare("Queue1 <= queue2", queue1 <= queue2, true);
        tests::compare("Queue2 <= queue1", queue2 <= queue1, false);

        tests::compare("Queue1 >= queue2", queue1 >= queue2, false);
        tests::compare("Queue2 >= queue1", queue2 >= queue1, true);

        // test three way comparison

        tests::compare("Queue1 <=> queue2 !=", (queue1 <=> queue2) != 0, (queue1 <=> queue2) != 0);
        tests::compare("Queue1 <=> queue2 <", (queue1 <=> queue2) < 0, (queue1 <=> queue2) < 0);
        tests::compare("Queue1 <=> queue2 >", (queue1 <=> queue2) > 0, (queue1 <=> queue2) > 0);
        tests::compare("Queue1 <=> queue2 <=", (queue1 <=> queue2) <= 0, (queue1 <=> queue2) <= 0);
        tests::compare("Queue1 <=> queue2 >=", (queue1 <=> queue2) >= 0, (queue1 <=> queue2) >= 0);

        tests::compare("Queue1 <=> queue2 <", (queue1 <=> queue2) == std::weak_ordering::less, true);
        tests::compare("Queue1 <=> queue2 <>", (queue1 <=> queue2) != std::weak_ordering::equivalent, true);
        tests::compare("Queue1 <=> queue2 <=", (queue1 <=> queue2) != std::weak_ordering::greater, true);

        std::cout << "Compare operators for objects of different size\n\n";

        tests::compare("Queue1 == queue3", queue1 == queue3, false);

        tests::compare("Queue1 != queue3", queue1 != queue3, true);

        tests::compare("Queue1 < queue3", queue1 < queue3, true);
        tests::compare("Queue3 < queue1", queue3 < queue1, false);
        tests::compare("Queue2 < queue3", queue2 < queue3, false);
        tests::compare("Queue3 < queue2", queue3 < queue2, true);

        tests::compare("Queue1 > queue3", queue1 > queue3, false);
        tests::compare("Queue3 > queue1", queue3 > queue1, true);
        tests::compare("Queue2 > queue3", queue2 > queue3, true);
        tests::compare("Queue3 > queue2", queue3 > queue2, false);

        tests::compare("Queue1 <= queue3", queue1 <= queue3, true);
        tests::compare("Queue3 <= queue1", queue3 <= queue1, false);
        tests::compare("Queue2 <= queue3", queue2 <= queue3, false);
        tests::compare("Queue3 <= queue2", queue3 <= queue2, true);

        tests::compare("Queue1 >= queue3", queue1 >= queue3, false);
        tests::compare("Queue3 >= queue1", queue3 >= queue1, true);
        tests::compare("Queue2 >= queue3", queue2 >= queue3, true);
        tests::compare("Queue3 >= queue2", queue3 >= queue2, false);

        // test three way comparison

        tests::compare("Queue1 <=> queue3 ==", (queue1 <=> queue3) == 0, false);
        tests::compare("Queue1 <=> queue3 <", (queue1 <=> queue3) < 0, true);
        tests::compare("Queue1 <=> queue3 >", (queue1 <=> queue3) > 0, false);
        tests::compare("Queue1 <=> queue3 <=", (queue1 <=> queue3) <= 0, true);
        tests::compare("Queue1 <=> queue3 >=", (queue1 <=> queue3) >= 0, false);

        tests::compare("Queue1 <=> queue3 >=", (queue1 <=> queue3) != std::weak_ordering::less, false);
        tests::compare("Queue1 <=> queue3 ==", (queue1 <=> queue3) == std::weak_ordering::equivalent, false);
        tests::compare("Queue1 <=> queue3 <=", (queue1 <=> queue3) != std::weak_ordering::greater, true);

        // test comparison categories
        static_assert(std::is_same_v<std::compare_three_way_result_t<dsa::Queue<int>>, std::strong_ordering>,
            "Int queue should support strong ordering");

        static_assert(std::is_same_v<std::compare_three_way_result_t<dsa::Queue<double>>, std::partial_ordering>,
            "Double queue should support strong ordering");

        // test partial ordering
        const dsa::Queue<double> queue7{ dsa::List<double>{1.0, 2.0, 3.0} };
        const dsa::Queue<double> queue8{ dsa::List<double>{1.0, 2.0, std::numeric_limits<double>::quiet_NaN()} };
        assert((queue7 <=> queue8) == std::partial_ordering::unordered);
        tests::compare("Queue7 <=> queue8 weak ordering", (queue7 <=> queue8) != std::weak_ordering::less, true);

        // test noexcept

        // operators
        static_assert(!noexcept(
            dsa::Queue<tests::ThrowingType>{dsa::List<tests::ThrowingType>(1)} ==
            dsa::Queue<tests::ThrowingType>{dsa::List<tests::ThrowingType>(1)}));
        static_assert(!noexcept(
            dsa::Queue<tests::ThrowingType>{dsa::List<tests::ThrowingType>(1)} <=>
            dsa::Queue<tests::ThrowingType>{dsa::List<tests::ThrowingType>(1)}));


        std::cout << "Compare operations results with std container\n\n";

        const std::queue<int> std_queue1({ 1, 2, 3 });
        const std::queue<int> std_queue2({ 1, 2, 6 });
        const std::queue<int> std_queue3({ 1, 2, 3, 4 });

        // intentional self-comparison, an object should be equal to itself
        // NOLINTNEXTLINE(misc-redundant-expression)
        tests::compare("Queue1 == queue1 vs std", queue1 == queue1, std_queue1 == std_queue1);

        tests::compare("Queue1 != queue2 vs std", queue1 != queue2, std_queue1 != std_queue2);

        tests::compare("Queue1 < queue2 vs std", queue1 < queue2, std_queue1 < std_queue2);
        tests::compare("Queue2 < queue1 vs std", queue2 < queue1, std_queue2 < std_queue1);

        tests::compare("Queue1 > queue2 vs std", queue1 > queue2, std_queue1 > std_queue2);
        tests::compare("Queue2 > queue1 vs std", queue2 > queue1, std_queue2 > std_queue1);

        tests::compare("Queue1 <= queue2 vs std", queue1 <= queue2, std_queue1 <= std_queue2);
        tests::compare("Queue2 <= queue1 vs std", queue2 <= queue1, std_queue2 <= std_queue1);

        tests::compare("Queue1 >= queue2 vs std", queue1 >= queue2, std_queue1 >= std_queue2);
        tests::compare("Queue2 >= queue1 vs std", queue2 >= queue1, std_queue2 >= std_queue1);

        // test three way comparison

        tests::compare("Queue1 <=> queue2 vs std !=", (queue1 <=> queue2) != 0, (std_queue1 <=> std_queue2) != 0);
        tests::compare("Queue1 <=> queue2 vs std <", (queue1 <=> queue2) < 0, (std_queue1 <=> std_queue2) < 0);
        tests::compare("Queue1 <=> queue2 vs std >", (queue1 <=> queue2) > 0, (std_queue1 <=> std_queue2) > 0);
        tests::compare("Queue1 <=> queue2 vs std <=", (queue1 <=> queue2) <= 0, (std_queue1 <=> std_queue2) <= 0);
        tests::compare("Queue1 <=> queue2 vs std >=", (queue1 <=> queue2) >= 0, (std_queue1 <=> std_queue2) >= 0);

        tests::compare("Queue1 <=> queue2 vs std <",
            (queue1 <=> queue2) == std::weak_ordering::less, (std_queue1 <=> std_queue2) == std::weak_ordering::less);
        tests::compare("Queue1 <=> queue2 vs std <>",
            (queue1 <=> queue2) != std::weak_ordering::equivalent, (std_queue1 <=> std_queue2) != std::weak_ordering::equivalent);
        tests::compare("Queue1 <=> queue2 vs std <=",
            (queue1 <=> queue2) != std::weak_ordering::greater, (std_queue1 <=> std_queue2) != std::weak_ordering::greater);

        std::cout << "Compare operators for objects of different size\n\n";

        tests::compare("Queue1 == queue3 vs std", queue1 == queue3, std_queue1 == std_queue3);

        tests::compare("Queue1 != queue3 vs std", queue1 != queue3, std_queue1 != std_queue3);

        tests::compare("Queue1 < queue3 vs std", queue1 < queue3, std_queue1 < std_queue3);
        tests::compare("Queue3 < queue1 vs std", queue3 < queue1, std_queue3 < std_queue1);
        tests::compare("Queue2 < queue3 vs std", queue2 < queue3, std_queue2 < std_queue3);
        tests::compare("Queue3 < queue2 vs std", queue3 < queue2, std_queue3 < std_queue2);

        tests::compare("Queue1 > queue3 vs std", queue1 > queue3, std_queue1 > std_queue3);
        tests::compare("Queue3 > queue1 vs std", queue3 > queue1, std_queue3 > std_queue1);
        tests::compare("Queue2 > queue3 vs std", queue2 > queue3, std_queue2 > std_queue3);
        tests::compare("Queue3 > queue2 vs std", queue3 > queue2, std_queue3 > std_queue2);

        tests::compare("Queue1 <= queue3 vs std", queue1 <= queue3, std_queue1 <= std_queue3);
        tests::compare("Queue3 <= queue1 vs std", queue3 <= queue1, std_queue3 <= std_queue1);
        tests::compare("Queue2 <= queue3 vs std", queue2 <= queue3, std_queue2 <= std_queue3);
        tests::compare("Queue3 <= queue2 vs std", queue3 <= queue2, std_queue3 <= std_queue2);

        tests::compare("Queue1 >= queue3 vs std", queue1 >= queue3, std_queue1 >= std_queue3);
        tests::compare("Queue3 >= queue1 vs std", queue3 >= queue1, std_queue3 >= std_queue1);
        tests::compare("Queue2 >= queue3 vs std", queue2 >= queue3, std_queue2 >= std_queue3);
        tests::compare("Queue3 >= queue2 vs std", queue3 >= queue2, std_queue3 >= std_queue2);

        // test three way comparison

        tests::compare("Queue1 <=> queue3 vs std ==", (queue1 <=> queue3) == 0, (std_queue1 <=> std_queue3) == 0);
        tests::compare("Queue1 <=> queue3 vs std <", (queue1 <=> queue3) < 0, (std_queue1 <=> std_queue3) < 0);
        tests::compare("Queue1 <=> queue3 vs std >", (queue1 <=> queue3) > 0, (std_queue1 <=> std_queue3) > 0);
        tests::compare("Queue1 <=> queue3 vs std <=", (queue1 <=> queue3) <= 0, (std_queue1 <=> std_queue3) <= 0);
        tests::compare("Queue1 <=> queue3 vs std >=", (queue1 <=> queue3) >= 0, (std_queue1 <=> std_queue3) >= 0);

        tests::compare("Queue1 <=> queue3 vs std >=",
            (queue1 <=> queue3) != std::weak_ordering::less, (std_queue1 <=> std_queue3) != std::weak_ordering::less);
        tests::compare("Queue1 <=> queue3 vs std ==",
            (queue1 <=> queue3) == std::weak_ordering::equivalent, (std_queue1 <=> std_queue3) == std::weak_ordering::equivalent);
        tests::compare("Queue1 <=> queue3 vs std <= ",
            (queue1 <=> queue3) != std::weak_ordering::greater, (std_queue1 <=> std_queue3) != std::weak_ordering::greater);

        // test comparison categories
        static_assert(std::is_same_v<std::compare_three_way_result_t<std::queue<int>>, std::strong_ordering>,
            "Int queue should support strong ordering");

        static_assert(std::is_same_v<std::compare_three_way_result_t<std::queue<double>>, std::partial_ordering>,
            "Double queue should support strong ordering");

        // test partial ordering
        const std::queue<double> std_queue7{ std::deque<double>{1.0, 2.0, 3.0} };
        const std::queue<double> std_queue8{ std::deque<double>{1.0, 2.0, std::numeric_limits<double>::quiet_NaN()} };
        assert((std_queue7 <=> std_queue8) == std::partial_ordering::unordered);
        assert((queue7 <=> queue8) == (std_queue7 <=> std_queue8));
        tests::compare("std_queue7 <=> std_queue8 weak ordering",
            (std_queue7 <=> std_queue8) == std::partial_ordering::unordered, true);
        tests::compare("(queue7 <=> queue8) == (std_queue7 <=> std_queue8)",
            (queue7 <=> queue8) == (std_queue7 <=> std_queue8), true);

        // test noexcept

        // operators
        static_assert(!noexcept(
            std::queue<tests::ThrowingType>{std::deque<tests::ThrowingType>(1)} ==
            std::queue<tests::ThrowingType>{std::deque<tests::ThrowingType>(1)}));
        static_assert(!noexcept(
            std::queue<tests::ThrowingType>{std::deque < tests::ThrowingType>(1)} <=>
            std::queue<tests::ThrowingType>{std::deque < tests::ThrowingType>(1)}));


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
