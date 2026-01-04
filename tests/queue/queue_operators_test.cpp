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
#include "dsa/queue.h"

#include <exception>
#include <iostream>
#include <queue>

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


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
