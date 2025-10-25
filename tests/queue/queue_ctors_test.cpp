/**
 * @file queue_ctors_test.cpp
 * @brief This file tests Queue constructors
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
        std::cout << "Start queue_ctors_test:\n";

        const std::initializer_list<int> expected{ 0,10,20 };

        std::cout << "Default ctor\n";
        dsa::Queue<int> queue1;
        queue1.push(0);
        queue1.push(10);
        queue1.push(20);
        tests::compare("Queue1", queue1, expected);

        std::cout << "Value ctor\n";
        dsa::Queue<int> queue2({ 0 });
        queue2.push(10);
        queue2.push(20);
        tests::compare("Queue2", queue2, expected);

        std::cout << "Initializer list ctor\n";
        const dsa::Queue<int> queue3(expected);
        tests::compare("Queue3", queue3, expected);


        std::cout << "Copy ctor\n";
        // intentionally make a copy to test copy constructor
        // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
        const dsa::Queue<int> queue4{ queue1 };
        tests::compare("Queue4", queue4, expected);

        std::cout << "Copy assignment ctor\n";
        dsa::Queue<int> queue5;
        queue5.push(1);
        queue5.push(2);
        queue5.push(3);
        queue5.push(4);
        queue5.push(5);
        queue5 = queue1;
        tests::compare("Queue5", queue5, expected);

        std::cout << "Move ctor\n";
        dsa::Queue<int> temp_1(queue1);
        const dsa::Queue<int> queue6 = std::move(temp_1);
        tests::compare("Queue6", queue6, expected);

        std::cout << "Move assignment ctor\n";
        dsa::Queue<int> temp_2(queue1);
        dsa::Queue<int> queue7;
        queue7.push(0);
        queue7 = std::move(temp_2);
        tests::compare("Queue7", queue7, expected);


        std::cout << "Compare operations results with std container\n\n";

        std::queue<int> std_queue1;
        std_queue1.push(0);
        std_queue1.push(10);
        std_queue1.push(20);
        tests::compare("Queue1 vs std", queue1, std_queue1);

        std::queue<int> std_queue2({ 0 });
        std_queue2.push(10);
        std_queue2.push(20);
        tests::compare("Queue2 vs std", queue2, std_queue2);

        const std::queue<int> std_queue3(expected);
        tests::compare("Queue3 vs std", queue3, std_queue3);

        const std::queue<int> std_queue4{ std_queue1 };
        tests::compare("Queue4 vs std", queue4, expected);

        std::queue<int> std_queue5{ std_queue1 };
        std_queue5.push(1);
        std_queue5.push(2);
        std_queue5.push(3);
        std_queue5.push(4);
        std_queue5.push(5);
        std_queue5 = std_queue1;
        tests::compare("Queue5 vs std", queue5, std_queue5);

        std::queue<int> std_temp_1(std_queue1);
        const std::queue<int> std_queue6 = std::move(std_temp_1);
        tests::compare("Queue6 vs std", queue6, std_queue6);

        std::queue<int> std_temp_2(std_queue1);
        std::queue<int> std_queue7;
        std_queue7.push(0);
        std_queue7 = std::move(std_temp_2);
        tests::compare("Queue7 vs std", queue7, std_queue7);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
