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
#include "dsa/vector.h"

#include <exception>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start priority_queue_ctors_test:\n";

        const std::initializer_list<int> data{ 20, 0, 10 };
        const std::initializer_list<int> expected{ 20, 10, 0 };

        std::cout << "Default ctor\n";
        dsa::PriorityQueue<int> priority_queue1;
        priority_queue1.push(10);
        priority_queue1.push(0);
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
        priority_queue3.push(5);
        priority_queue3.push(4);
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

        std::cout << "Iterator-pair constructor, default compare\n";
        const dsa::PriorityQueue<int> priority_queue6(data.begin(), data.end());
        tests::compare("PriorityQueue6", priority_queue6, expected);

        std::cout << "Iterator-pair constructor, template compare - greater\n";
        const dsa::PriorityQueue<int, dsa::Vector<int>, std::greater<>>
            priority_queue7(data.begin(), data.end(), std::greater<>());
        tests::compare("PriorityQueue7", priority_queue7, std::initializer_list<int>{ 0, 10, 20 });

        std::cout << "Iterator-pair copy constructor, template compare - greater\n";
        const dsa::Vector<int> temp_8({ -1, -2, -3 });
        const dsa::PriorityQueue<int, dsa::Vector<int>, std::greater<>>
            priority_queue8(data.begin(), data.end(), std::greater<>(), temp_8);
        tests::compare("PriorityQueue8", priority_queue8, std::initializer_list<int>{ -3, -2, -1, 0, 10, 20 });

        std::cout << "Iterator-pair move constructor, template compare - greater\n";
        dsa::Vector<int> temp_9({ -1, -2, -3 });
        const dsa::PriorityQueue<int, dsa::Vector<int>, std::greater<>>
            priority_queue9(data.begin(), data.end(), std::greater<>(), std::move(temp_9));
        tests::compare("PriorityQueue9", priority_queue9, std::initializer_list<int>{ -3, -2, -1, 0, 10, 20 });


        std::cout << "Compare operations results with std container\n\n";

        std::priority_queue<int> std_priority_queue1;
        std_priority_queue1.push(10);
        std_priority_queue1.push(0);
        std_priority_queue1.push(20);
        tests::compare("PriorityQueue1 vs std", priority_queue1, std_priority_queue1);

        const std::priority_queue<int> std_priority_queue2{ std_priority_queue1 };
        tests::compare("PriorityQueue2 vs std", priority_queue2, std_priority_queue2);

        std::priority_queue<int> std_priority_queue3{ std_priority_queue1 };
        std_priority_queue3.push(1);
        std_priority_queue3.push(2);
        std_priority_queue3.push(3);
        std_priority_queue3.push(5);
        std_priority_queue3.push(4);
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

        const std::priority_queue<int> std_priority_queue6(data.begin(), data.end());
        tests::compare("PriorityQueue6 vs std", priority_queue6, std_priority_queue6);

        const std::priority_queue<int, std::vector<int>, std::greater<>>
            std_priority_queue7(data.begin(), data.end(), std::greater<>());
        tests::compare("PriorityQueue7 vs std", priority_queue7, std_priority_queue7);

        const std::vector<int> std_temp_8({ -1, -2, -3 });
        const std::priority_queue<int, std::vector<int>, std::greater<>>
            std_priority_queue8(data.begin(), data.end(), std::greater<>(), std_temp_8);
        tests::compare("PriorityQueue8 vs std", priority_queue8, std_priority_queue8);

        std::vector<int> std_temp_9({ -1, -2, -3 });
        const std::priority_queue<int, std::vector<int>, std::greater<>>
            std_priority_queue9(data.begin(), data.end(), std::greater<>(), std::move(std_temp_9));
        tests::compare("PriorityQueue9 vs std", priority_queue9, std_priority_queue9);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
