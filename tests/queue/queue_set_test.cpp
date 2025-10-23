/**
 * @file queue_set_test.cpp
 * @brief This file tests setting values of Queue
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
#include <new>
#include <queue>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start queue_set_test:\n";

        const std::initializer_list<int> expected{ 50,10,20 };

        dsa::Queue<int> queue1 = dsa::Queue<int>({ 0,10,20 });
        queue1.front() = 50;
        tests::compare("Queue1", queue1, expected);

        dsa::Queue<int> queue2 = dsa::Queue<int>({ 0,10,20 });
        dsa::Queue<int> queue3 = dsa::Queue<int>({ 50,10,20 });
        queue2.swap(queue3);
        tests::compare("Queue2", queue2, { 50, 10, 20 });
        tests::compare("Queue3", queue3, { 0, 10, 20 });

        dsa::Queue<int> queue4 = dsa::Queue<int>({ 50,10,20 });
        queue4.swap(queue4);
        tests::compare("Queue4", queue4, expected);


        std::cout << "Compare operations results with std container\n\n";

        std::queue<int> std_queue1;
        std_queue1.push(0);
        std_queue1.push(10);
        std_queue1.push(20);
        std_queue1.front() = 50;
        tests::compare("Queue1 vs std", queue1, std_queue1);

        std::queue<int> std_queue2;
        std_queue2.push(0);
        std_queue2.push(10);
        std_queue2.push(20);
        std::queue<int> std_queue3;
        std_queue3.push(50);
        std_queue3.push(10);
        std_queue3.push(20);
        std_queue2.swap(std_queue3);
        tests::compare("Queue2 vs std", queue2, std_queue2);
        tests::compare("Queue3 vs std", queue3, std_queue3);

        std::queue<int> std_queue4;
        std_queue4.push(50);
        std_queue4.push(10);
        std_queue4.push(20);
        std_queue4.swap(std_queue4);
        tests::compare("Queue4 vs std", queue4, std_queue4);


        tests::print_stats();
    }
    catch (const std::bad_alloc& exception)
    {
        tests::print_err_msg("Caught std::bad_alloc: ", &exception);
        return 1;
    }
    catch (const std::runtime_error& exception)
    {
        tests::print_err_msg("Caught std::runtime_error: ", &exception);
        return 2;
    }
    catch (const std::exception& exception)
    {
        tests::print_err_msg("Caught exception: ", &exception);
        return 3;
    }
    catch (...)
    {
        tests::print_err_msg("Unhandled unknown exception");
        return 4;
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
