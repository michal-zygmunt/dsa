/**
 * @file QueueGet.cpp
 * @brief This file tests accessing values of Queue Nodes
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

int main() // NOLINT(modernize-use-trailing-return-type)
{
    std::cout << "Start QueueGet test:\n";

    std::initializer_list<int> expected{ 0,10,20 };

    dsa::Queue<int> q1 = dsa::Queue<int>({ 0,10,20 });
    size_t q1_size = q1.size();
    std::cout << "Queue q1:\t";
    for (size_t i = 0; i < q1_size; i++)
    {
        auto temp = q1.front();
        if (temp)
        {
            std::cout << temp << ' ';
            tests::compare(temp, expected.begin()[i]);
            q1.pop();
        }
    }
    std::cout << '\n';
    tests::compare("Queue q1", q1, expected);

    dsa::Queue<int> q2 = dsa::Queue<int>({ 0,10,20 });
    auto front = q2.front();
    auto back = q2.back();
    tests::compare(front, 0) || tests::compare(back, 20);
    std::cout << "Queue q2 front: " << front << ", back: " << back << '\n';
    tests::compare("Queue q2", q2, expected);

    const dsa::Queue<int> q3 = dsa::Queue<int>({ 0,10,20 });
    front = q3.front();
    back = q3.back();
    tests::compare(front, 0) || tests::compare(back, 20);
    std::cout << "Queue q3 front: " << front << ", back: " << back << '\n';
    tests::compare("Queue q3", q3, expected);

    return tests::failed;
}
