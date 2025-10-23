/**
 * @file queue_get_test.cpp
 * @brief This file tests accessing values of Queue Nodes
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
        std::cout << "Start queue_get_test:\n";

        const std::initializer_list<int> expected{ 0,10,20 };

        dsa::Queue<int> queue1 = dsa::Queue<int>({ 0,10,20 });
        std::cout << "Queue1:\t";
        for (const auto& item : expected)
        {
            auto temp = queue1.front();
            if (static_cast<bool>(temp))
            {
                std::cout << temp << ' ';
                tests::compare(temp, item);
                queue1.pop();
            }
        }
        std::cout << '\n';
        tests::compare("Queue1", queue1, expected);

        dsa::Queue<int> queue2 = dsa::Queue<int>({ 0,10,20 });
        tests::compare("Queue2 front", queue2.front(), 0);
        tests::compare("Queue2 back", queue2.back(), 20);

        const dsa::Queue<int> queue3 = dsa::Queue<int>({ 0,10,20 });
        tests::compare("Queue3 front", queue3.front(), 0);
        tests::compare("Queue3 back", queue3.back(), 20);


        std::cout << "Compare operations results with std container\n\n";

        const std::queue<int> std_queue1 = std::queue<int>({ 0,10,20 });
        tests::compare("Queue1 vs std", queue1, std_queue1);

        std::queue<int> std_queue2 = std::queue<int>({ 0,10,20 });
        tests::compare("Queue2 front vs std", queue2.front(), std_queue2.front());
        tests::compare("Queue2 back vs std", queue2.back(), std_queue2.back());

        const std::queue<int> std_queue3 = std::queue<int>({ 0,10,20 });
        tests::compare("Queue3 front vs std", queue3.front(), std_queue3.front());
        tests::compare("Queue3 back vs std", queue3.back(), std_queue3.back());


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
