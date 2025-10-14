/**
 * @file queue_shrink_test.cpp
 * @brief This file tests functions decreasing Queue length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/queue.h"

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <new>
#include <queue>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start queue_shrink_test:\n";

        dsa::Queue<int> queue1 = dsa::Queue<int>({ 0,10,20,30,40,50 });
        queue1.pop();
        queue1.pop();
        const std::initializer_list<int> expected1 = { 20,30,40,50 };
        tests::compare("Queue1", queue1, expected1);

        dsa::Queue<int> queue2 = dsa::Queue<int>({ 0,10,20 });
        queue2.pop();
        queue2.pop();
        queue2.pop();
        const std::initializer_list<int> expected2 = std::initializer_list<int>{ };
        tests::compare("Queue2", queue2, expected2);

        const dsa::Queue<int> queue3 = dsa::Queue<int>({ 0,10,20 });
        tests::compare("Queue3.size()", queue3.size(), static_cast<size_t>(3));

        dsa::Queue<int> queue4 = dsa::Queue<int>();
        queue4.pop();
        tests::compare("Queue4.size()", queue4.size(), static_cast<size_t>(0));

        const dsa::Queue<int> queue5;
        tests::compare("Queue5.empty()", queue5.empty(), true);


        std::cout << "Compare operations results with std container\n\n";

        std::queue<int> std_queue1 = std::queue<int>({ 0,10,20,30,40,50 });
        std_queue1.pop();
        std_queue1.pop();
        tests::compare("Queue1 vs std", queue1, std_queue1);

        std::queue<int> std_queue2 = std::queue<int>({ 0,10,20 });
        std_queue2.pop();
        std_queue2.pop();
        std_queue2.pop();
        tests::compare("Queue2 vs std", queue2, std_queue2);

        const std::queue<int> std_queue3 = std::queue<int>({ 0,10,20 });
        tests::compare("Queue3.size() vs std", queue3.size(), std_queue3.size());

        const std::queue<int> std_queue4 = std::queue<int>();
        // do not use pop on empty std::queue
        tests::compare("Queue4.size() vs std", queue4.size(), std_queue4.size());

        const std::queue<int> std_queue5;
        tests::compare("Queue5.empty() vs std", queue5.empty(), std_queue5.empty());
    }
    catch (const std::bad_alloc& exception)
    {
        std::cerr << "Caught std::bad_alloc: " << exception.what() << '\n';
        return 1;
    }
    catch (const std::runtime_error& exception)
    {
        std::cerr << "Caught std::runtime_error: " << exception.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unhandled unknown exception\n";
        return 1;
    }

    tests::print_stats();
    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}