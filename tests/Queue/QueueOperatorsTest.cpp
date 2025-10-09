/**
 * @file QueueOperators.cpp
 * @brief This file tests overloading operators of Queue
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/Queue.h"

#include <iostream>
#include <new>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start QueueOperators test:\n";

        const dsa::Queue<int> queue1({ 1, 2, 3 });
        const dsa::Queue<int> queue2({ 4, 5, 6 });
        const dsa::Queue<int> queue3({ 1, 2, 3, 4 });
        std::cout << "Queue1:\t" << queue1 << '\n';
        std::cout << "Queue2:\t" << queue2 << '\n';
        std::cout << "Queue3:\t" << queue3 << "\n\n";

        std::cout << "Compare operators for objects of the same size\n\n";

        // intentional self-comparison, an object should be equal to itself
        // NOLINTNEXTLINE(misc-redundant-expression)
        tests::compare("Queue1 == queue1", queue1 == queue1, true);

        tests::compare("Queue1 != queue2", queue1 != queue2, true);

        tests::compare("Queue1 < queue2", queue1 < queue2, true);
        tests::compare("Queue2 < queue1", queue2 < queue1, false);

        tests::compare("Queue1 > queue2", queue1 > queue2, false);
        tests::compare("Queue2 > queue1", queue2 > queue1, true);

        tests::compare("Queue1 <= queue2", queue1 <= queue2, true);
        tests::compare("Queue2 <= queue1", queue2 <= queue1, false);

        tests::compare("Queue1 >= queue2", queue1 >= queue2, false);
        tests::compare("Queue2 >= queue1", queue2 >= queue1, true);

        std::cout << "Compare operators for objects of different size\n\n";

        tests::compare("Queue1 == queue3", queue1 == queue3, false);

        tests::compare("Queue1 != queue3", queue1 != queue3, true);

        tests::compare("Queue1 < queue3", queue1 < queue3, true);
        tests::compare("Queue3 < queue1", queue3 < queue1, false);
        tests::compare("Queue2 < queue3", queue2 < queue3, false);
        tests::compare("Queue3 < queue2", queue3 < queue2, true);

        tests::compare("Queue1 > queue3", queue1 > queue3, false);
        tests::compare("Queue3 > queue1", queue3 > queue1, true);
        tests::compare("Queue2 > queue3", queue2 > queue3, true);
        tests::compare("Queue3 > queue2", queue3 > queue2, false);

        tests::compare("Queue1 <= queue3", queue1 <= queue3, true);
        tests::compare("Queue3 <= queue1", queue3 <= queue1, false);
        tests::compare("Queue2 <= queue3", queue2 <= queue3, false);
        tests::compare("Queue3 <= queue2", queue3 <= queue2, true);

        tests::compare("Queue1 >= queue3", queue1 >= queue3, false);
        tests::compare("Queue3 >= queue1", queue3 >= queue1, true);
        tests::compare("Queue2 >= queue3", queue2 >= queue3, true);
        tests::compare("Queue3 >= queue2", queue3 >= queue2, false);

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
