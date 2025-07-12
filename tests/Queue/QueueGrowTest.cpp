/**
 * @file QueueGrow.cpp
 * @brief This file tests functions increasing Queue length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/Queue.h"

int main()
{
    std::cout << "Start QueueGrow test:\n";

    std::initializer_list<int> expected{ 10, 20, 30, 40 };

    dsa::Queue<int> q1 = dsa::Queue<int>(10);
    q1.push(20);
    q1.push(30);
    q1.push(40);
    tests::compare("Queue q1", q1, expected);

    dsa::Queue<int> q2 = dsa::Queue<int>(10);
    q2.push_range({ 20, 30, 40 });
    tests::compare("Queue q2", q2, expected);

    return tests::failed;
}
