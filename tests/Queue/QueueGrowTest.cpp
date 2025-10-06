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

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start QueueGrow test:\n";

    const std::initializer_list<int> expected{ 10, 20, 30, 40 };

    dsa::Queue<int> queue1 = dsa::Queue<int>({ 10 });
    queue1.push(20);
    queue1.push(30);
    queue1.push(40);
    tests::compare("Queue1", queue1, expected);

    dsa::Queue<int> queue2 = dsa::Queue<int>({ 10 });
    queue2.push_range({ 20, 30, 40 });
    tests::compare("Queue2", queue2, expected);

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
