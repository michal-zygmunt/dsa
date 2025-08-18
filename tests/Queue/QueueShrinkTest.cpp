/**
 * @file QueueShrink.cpp
 * @brief This file tests functions decreasing Queue length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/Queue.h"

#include <cstddef>
#include <initializer_list>
#include <iostream>

int main()
{
    std::cout << "Start QueueShrink test:\n";

    dsa::Queue<int> q1 = dsa::Queue<int>({ 0,10,20,30,40,50 });
    q1.pop();
    q1.pop();
    std::initializer_list<int> expected_1 = { 20,30,40,50 };
    tests::compare("Queue q1", q1, expected_1);

    dsa::Queue<int> q2 = dsa::Queue<int>({ 0,10,20 });
    q2.pop();
    q2.pop();
    q2.pop();
    std::initializer_list<int> expected_2 = std::initializer_list<int>{ };
    tests::compare("Queue q2", q2, expected_2);

    dsa::Queue<int> q3 = dsa::Queue<int>({ 0,10,20 });
    tests::compare("q3.size()", q3.size(), static_cast<size_t>(3));

    dsa::Queue<int> q4 = dsa::Queue<int>();
    q4.pop();
    tests::compare("q4.size()", q4.size(), static_cast<size_t>(0));

    dsa::Queue<int> q5;
    tests::compare("q5.empty()", q5.empty(), true);

    return tests::failed;
}