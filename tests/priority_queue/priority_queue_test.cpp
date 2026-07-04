/**
 * @file priority_queue_test.cpp
 * @brief This file tests functions swapping PriorityQueue objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2026 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/queue.h"
#include "dsa/vector.h"

#include <cstddef>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <vector>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start priority_queue_test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 5, 4, 3 };

        const std::initializer_list<int> il_1_desc{ 5, 4, 3, 2, 1 };
        const std::initializer_list<int> il_1_asc{ 1, 2, 3, 4, 5 };

        dsa::PriorityQueue<int> priority_queue1;
        tests::compare("PriorityQueue1 empty == true", priority_queue1.empty(), true);
        tests::compare("PriorityQueue1 size == 0", priority_queue1.size(), static_cast<size_t>(0));
        priority_queue1.push(2);
        priority_queue1.push(1);
        priority_queue1.push(3);
        priority_queue1.push(5);
        priority_queue1.push(4);
        tests::compare("PriorityQueue1 empty == false", priority_queue1.empty(), false);
        tests::compare("PriorityQueue1 size == 5", priority_queue1.size(), static_cast<size_t>(5));
        const std::initializer_list<int> expected1 = il_1_desc;
        tests::compare("PriorityQueue1", priority_queue1, expected1);
        tests::compare("PriorityQueue1 top", priority_queue1.top(), 5);

        dsa::PriorityQueue<int> priority_queue2;
        tests::compare("PriorityQueue2 empty == true", priority_queue2.empty(), true);
        tests::compare("PriorityQueue2 size == 0", priority_queue2.size(), static_cast<size_t>(0));
        priority_queue2.emplace(2);
        priority_queue2.emplace(1);
        priority_queue2.emplace(3);
        priority_queue2.emplace(5);
        priority_queue2.emplace(4);
        tests::compare("PriorityQueue2 empty == false", priority_queue2.empty(), false);
        tests::compare("PriorityQueue2 size == 5", priority_queue2.size(), static_cast<size_t>(5));
        const std::initializer_list<int> expected2 = il_1_desc;
        tests::compare("PriorityQueue2", priority_queue2, expected2);
        tests::compare("PriorityQueue2 top", priority_queue2.top(), 5);

        const dsa::PriorityQueue<int> priority_queue3(il_1.begin(), il_1.end());
        const std::initializer_list<int> expected3 = il_1_desc;
        tests::compare("PriorityQueue3", priority_queue3, expected3);
        tests::compare("PriorityQueue3 size == 5", priority_queue3.top(), 5);

        dsa::PriorityQueue<int> priority_queue4{ priority_queue3 };
        const std::initializer_list<int> expected4 = il_1_desc;
        tests::compare("PriorityQueue4", priority_queue4, expected4);
        tests::compare("PriorityQueue4 size == 5", priority_queue4.top(), 5);
        for (const auto& item : il_1_desc)
        {
            tests::compare("PriorityQueue4 top", priority_queue4.top(), item);
            priority_queue4.pop();
        }
        tests::compare("PriorityQueue4 size == 0", priority_queue4.size(), static_cast<size_t>(0));

        dsa::PriorityQueue<int, dsa::Vector<int>, std::greater<>> priority_queue5(il_1.begin(), il_1.end());
        const std::initializer_list<int> expected5 = il_1_asc;
        tests::compare("PriorityQueue5", priority_queue5, expected5);
        tests::compare("PriorityQueue5 size == 5", priority_queue5.size(), static_cast<size_t>(5));
        for (const auto& item : il_1_asc)
        {
            tests::compare("PriorityQueue5 top", priority_queue5.top(), item);
            priority_queue5.pop();
        }
        tests::compare("PriorityQueue5 size == 0", priority_queue5.size(), static_cast<size_t>(0));

        dsa::PriorityQueue<int> priority_queue6(il_1.begin(), il_1.end());
        dsa::PriorityQueue<int, dsa::Vector<int>, std::greater<>> priority_queue7(il_1.begin(), il_1.end());


        std::cout << "Compare operations results with std container\n\n";


        std::priority_queue<int> std_priority_queue1;
        std_priority_queue1.push(2);
        std_priority_queue1.push(1);
        std_priority_queue1.push(3);
        std_priority_queue1.push(5);
        std_priority_queue1.push(4);
        tests::compare("PriorityQueue1 empty vs std", priority_queue1.empty(), std_priority_queue1.empty());
        tests::compare("PriorityQueue1 size vs std", priority_queue1.size(), std_priority_queue1.size());
        tests::compare("PriorityQueue1 vs std", priority_queue1, std_priority_queue1);
        tests::compare("PriorityQueue1 top vs std", priority_queue1.top(), std_priority_queue1.top());

        std::priority_queue<int> std_priority_queue2;
        std_priority_queue2.emplace(2);
        std_priority_queue2.emplace(1);
        std_priority_queue2.emplace(3);
        std_priority_queue2.emplace(5);
        std_priority_queue2.emplace(4);
        tests::compare("PriorityQueue2 empty == false", std_priority_queue2.empty(), std_priority_queue2.empty());
        tests::compare("PriorityQueue2 size == 5", std_priority_queue2.size(), std_priority_queue2.size());
        tests::compare("PriorityQueue2", priority_queue2, std_priority_queue2);
        tests::compare("PriorityQueue2 top", priority_queue2.top(), std_priority_queue2.top());

        const std::priority_queue<int> std_priority_queue3(il_1.begin(), il_1.end());
        tests::compare("PriorityQueue3 vs std", priority_queue3, std_priority_queue3);
        tests::compare("PriorityQueue3 top vs std", priority_queue3.top(), std_priority_queue3.top());

        std::priority_queue<int> std_priority_queue6(il_1.begin(), il_1.end());
        while (!std_priority_queue6.empty())
        {
            tests::compare("PriorityQueue6 top vs std", priority_queue6.top(), std_priority_queue6.top());
            priority_queue6.pop();
            std_priority_queue6.pop();
        }
        tests::compare("PriorityQueue6 vs std", priority_queue6, std_priority_queue6);

        std::priority_queue<int, std::vector<int>, std::greater<>> std_priority_queue7(il_1.begin(), il_1.end());
        while (!std_priority_queue7.empty())
        {
            tests::compare("PriorityQueue6 top vs std", priority_queue7.top(), std_priority_queue7.top());
            priority_queue7.pop();
            std_priority_queue7.pop();
        }
        tests::compare("PriorityQueue7 vs std", priority_queue7, std_priority_queue7);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
