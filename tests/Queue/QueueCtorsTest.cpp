/**
 * @file QueueCtors.cpp
 * @brief This file tests Queue constructors
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
#include <stdexcept>
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start QueueCtors test:\n";

    const std::initializer_list<int> expected{ 0,10,20 };

    std::cout << "Default ctor\n";
    dsa::Queue<int> queue1;
    queue1.push(0);
    queue1.push(10);
    queue1.push(20);
    tests::compare("Queue1", queue1, expected);

    std::cout << "Value ctor\n";
    dsa::Queue<int> queue2(0);
    queue2.push(10);
    queue2.push(20);
    tests::compare("Queue2", queue2, expected);

    std::cout << "Initializer list ctor\n";
    const dsa::Queue<int> queue3(expected);
    tests::compare("Queue3", queue3, expected);

    try
    {
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
        dsa::Queue<int> queue7(0);
        queue7 = std::move(temp_2);
        tests::compare("Queue7", queue7, expected);
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
