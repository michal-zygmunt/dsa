/**
 * @file QueueGrow.cpp
 * @brief This file tests functions increasing Queue length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/Queue.h"

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
        std::cout << "Start QueueGrow test:\n";

        const std::initializer_list<int> expected{ 10, 20, 30, 40 };

        dsa::Queue<int> queue1 = dsa::Queue<int>({ 10 });
        queue1.push(20);
        queue1.push(30);
        queue1.push(40);
        tests::compare("Queue1", queue1, expected);


        std::cout << "Compare operations results with std container\n\n";

        std::queue<int> std_queue1 = std::queue<int>({ 10 });
        std_queue1.push(20);
        std_queue1.push(30);
        std_queue1.push(40);
        tests::compare("Queue1 vs std", queue1, std_queue1);
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

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
