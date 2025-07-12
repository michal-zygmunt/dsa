/**
 * @file QueueCtors.cpp
 * @brief This file tests Queue constructors
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
    std::cout << "Start QueueCtors test:\n";

    std::initializer_list<int> expected{ 0,10,20 };

    std::cout << "Default ctor\n";
    dsa::Queue<int> q1;
    q1.push(0);
    q1.push(10);
    q1.push(20);
    tests::compare("Queue q1", q1, expected);

    std::cout << "Value ctor\n";
    dsa::Queue<int> q2(0);
    q2.push(10);
    q2.push(20);
    tests::compare("Queue q2", q2, expected);

    std::cout << "Initializer list ctor\n";
    dsa::Queue<int> q3(expected);
    tests::compare("Queue q3", q3, expected);

    std::cout << "Copy ctor\n";
    dsa::Queue<int> q4{ q1 };
    tests::compare("Queue q4", q4, expected);

    std::cout << "Copy assignment ctor\n";
    dsa::Queue<int> q5;
    q5.push(1);
    q5.push(2);
    q5.push(3);
    q5.push(4);
    q5.push(5);
    q5 = q1;
    tests::compare("Queue q5", q5, expected);

    std::cout << "Move ctor\n";
    dsa::Queue<int> temp_1(q1);
    dsa::Queue<int> q6 = std::move(temp_1);
    tests::compare("Queue q6", q6, expected);

    std::cout << "Move assignment ctor\n";
    dsa::Queue<int> temp_2(q1);
    dsa::Queue<int> q7(0);
    q7 = std::move(temp_2);
    tests::compare("Queue q7", q7, expected);

    return tests::failed;
}
