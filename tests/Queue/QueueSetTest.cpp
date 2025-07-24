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

int main()
{
    std::cout << "Start QueueSet test:\n";

    std::initializer_list<int> expected{ 50,10,20 };

    dsa::Queue<int> q1 = dsa::Queue<int>({ 0,10,20 });
    q1.front() = 50;
    tests::compare("Queue q1", q1, expected);

    dsa::Queue<int> q2 = dsa::Queue<int>({ 0,10,20 });
    dsa::Queue<int> q3 = dsa::Queue<int>({ 50,10,20 });
    q2.swap(q3);
    tests::compare("Queue q2", q2, { 50, 10, 20 });
    tests::compare("Queue q3", q3, { 0, 10, 20 });

    dsa::Queue<int> q4 = dsa::Queue<int>({ 50,10,20 });
    q4.swap(q4);
    tests::compare("Queue q4", q4, expected);

    return tests::failed;
}
