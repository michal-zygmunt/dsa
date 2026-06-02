/**
 * @file queue_swap_test.cpp
 * @brief This file tests functions swapping Queue objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2026 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/queue.h"

#include <exception>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start queue_swap_test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };

        dsa::Queue<int> queue1 = dsa::Queue<int>(il_1);
        dsa::Queue<int> queue2 = dsa::Queue<int>(il_2);
        queue1.swap(queue2);
        const std::initializer_list<int> expected1 = { 10, 20, 30, 40, 50 };
        tests::compare("Queue1", queue1, expected1);
        const std::initializer_list<int> expected2 = { 1, 2, 3, 4, 5 };
        tests::compare("Queue2", queue2, expected2);

        dsa::Queue<int> queue3 = dsa::Queue<int>(il_1);
        dsa::Queue<int> queue4;
        queue3.swap(queue4);
        const std::initializer_list<int> expected3 = { };
        tests::compare("Queue3", queue3, expected3);
        const std::initializer_list<int> expected4 = { 1, 2, 3, 4, 5 };
        tests::compare("Queue4", queue4, expected4);

        dsa::Queue<int> queue5 = dsa::Queue<int>(il_1);
        dsa::Queue<int> queue6 = dsa::Queue<int>(il_2);
        dsa::swap(queue5, queue6);
        const std::initializer_list<int> expected5 = il_2;
        tests::compare("Queue5", queue5, expected5);
        const std::initializer_list<int> expected6 = il_1;
        tests::compare("Queue6", queue6, expected6);

        dsa::Queue<int> queue7 = dsa::Queue<int>(il_1);
        dsa::Queue<int> queue8;
        dsa::swap(queue7, queue8);
        const std::initializer_list<int> expected7 = { };
        tests::compare("Queue7", queue7, expected7);
        const std::initializer_list<int> expected8 = il_1;
        tests::compare("Queue8", queue8, expected8);

        // swap safe type
        static_assert(noexcept(swap(std::declval<dsa::Queue<int>&>(),
            std::declval<dsa::Queue<int>&>())));
        // swap throwing type
        static_assert(noexcept(swap(std::declval<dsa::Queue<tests::ThrowingType>&>(),
            std::declval<dsa::Queue<tests::ThrowingType>&>())));


        std::cout << "Compare operations results with std container\n\n";

        std::queue<int> std_queue1{ il_1 };
        std::queue<int> std_queue2{ il_2 };
        std_queue1.swap(std_queue2);
        tests::compare("Queue1 vs std", queue1, std_queue1);
        tests::compare("Queue2 vs std", queue2, std_queue2);

        std::queue<int> std_queue3{ il_1 };
        std::queue<int> std_queue4{};
        std_queue3.swap(std_queue4);
        tests::compare("Queue3 vs std", queue3, std_queue3);
        tests::compare("Queue4 vs std", queue4, std_queue4);

        std::queue<int> std_queue5(il_1);
        std::queue<int> std_queue6(il_2);
        std::swap(std_queue5, std_queue6);
        tests::compare("Queue5 vs std", queue5, std_queue5);
        tests::compare("Queue6 vs std", queue6, std_queue6);

        std::queue<int> std_queue7(il_1);
        std::queue<int> std_queue8;
        std::swap(std_queue7, std_queue8);
        tests::compare("Queue7 vs std", queue7, std_queue7);
        tests::compare("Queue8 vs std", queue8, std_queue8);

        // swap safe type
        static_assert(noexcept(swap(std::declval<std::queue<int>&>(),
            std::declval<std::queue<int>&>())));
        // swap throwing type
        static_assert(noexcept(swap(std::declval<std::queue<tests::ThrowingType>&>(),
            std::declval<std::queue<tests::ThrowingType>&>())));


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
