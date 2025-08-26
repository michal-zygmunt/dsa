/**
 * @file QueueSet.cpp
 * @brief This file tests setting values of Queue
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

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start QueueSet test:\n";

    std::initializer_list<int> expected{ 50,10,20 };

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

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
