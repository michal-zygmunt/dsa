/**
 * @file priority_queue_ctors_test.cpp
 * @brief This file tests PriorityQueue constructors
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
        std::cout << "Start priority_queue_ctors_test:\n";

        const std::initializer_list<int> expected{ 20, 10, 0 };

        std::cout << "Default ctor\n";
        dsa::PriorityQueue<int> priority_queue1;
        priority_queue1.push(0);
        priority_queue1.push(10);
        priority_queue1.push(20);
        tests::compare("PriorityQueue1", priority_queue1, expected);

        std::cout << "Copy ctor\n";
        const dsa::PriorityQueue<int> priority_queue2{ priority_queue1 };
        tests::compare("PriorityQueue2", priority_queue2, expected);

        std::cout << "Copy assignment ctor\n";
        dsa::PriorityQueue<int> priority_queue3;
        priority_queue3.push(1);
        priority_queue3.push(2);
        priority_queue3.push(3);
        priority_queue3.push(4);
        priority_queue3.push(5);
        priority_queue3 = priority_queue1;
        tests::compare("PriorityQueue3", priority_queue3, expected);

        std::cout << "Move ctor\n";
        dsa::PriorityQueue<int> temp_4(priority_queue1);
        const dsa::PriorityQueue<int> priority_queue4 = std::move(temp_4);
        tests::compare("PriorityQueue4", priority_queue4, expected);

        std::cout << "Move assignment ctor\n";
        dsa::PriorityQueue<int> temp_5(priority_queue1);
        dsa::PriorityQueue<int> priority_queue5;
        priority_queue5.push(0);
        priority_queue5 = std::move(temp_5);
        tests::compare("PriorityQueue5", priority_queue5, expected);


        std::cout << "Compare operations results with std container\n\n";

        std::priority_queue<int> std_priority_queue1;
        std_priority_queue1.push(0);
        std_priority_queue1.push(10);
        std_priority_queue1.push(20);
        tests::compare("PriorityQueue1 vs std", priority_queue1, std_priority_queue1);

        const std::priority_queue<int> std_priority_queue2{ std_priority_queue1 };
        tests::compare("PriorityQueue2 vs std", priority_queue2, std_priority_queue2);

        std::priority_queue<int> std_priority_queue3{ std_priority_queue1 };
        std_priority_queue3.push(1);
        std_priority_queue3.push(2);
        std_priority_queue3.push(3);
        std_priority_queue3.push(4);
        std_priority_queue3.push(5);
        std_priority_queue3 = std_priority_queue1;
        tests::compare("PriorityQueue3 vs std", priority_queue3, std_priority_queue3);

        std::priority_queue<int> std_temp_4(std_priority_queue1);
        const std::priority_queue<int> std_priority_queue4 = std::move(std_temp_4);
        tests::compare("PriorityQueue4 vs std", priority_queue4, std_priority_queue4);

        std::priority_queue<int> std_temp_5(std_priority_queue1);
        std::priority_queue<int> std_priority_queue5;
        std_priority_queue5.push(0);
        std_priority_queue5 = std::move(std_temp_5);
        tests::compare("PriorityQueue5 vs std", priority_queue5, std_priority_queue5);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
