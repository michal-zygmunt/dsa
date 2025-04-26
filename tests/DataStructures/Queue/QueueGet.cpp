/**
 * @file QueueGet.cpp
 * @brief This file tests accessing values of Queue Nodes
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "Queue.h"

int main()
{
    std::cout << "Start QueueGet test:\n";

    bool res{};
    std::initializer_list<int> expected{ 0,10,20 };

    Queue<int> q1 = Queue<int>({ 0,10,20 });
    size_t q1_size = q1.size();
    std::cout << "Queue q1:\t";
    for (int i = 0; i < q1_size; i++)
    {
        auto temp = q1.front();
        if (temp)
        {
            std::cout << temp->value() << ' ';
            res = if_error(temp->value(), expected.begin()[i]);
            q1.pop();
        }
    }
    std::cout << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Queue<int> q2 = Queue<int>({ 0,10,20 });
    auto front = q2.front()->value();
    auto back = q2.back()->value();
    res = 0;
    if (if_error(front, 0) || if_error(back, 20))
    {
        res = 1;
    }
    std::cout << "Queue q2 front: " << front << ", back: " << back << '\n';
    std::cout << "Expected front: " << 0 << ", back: " << 20 << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    const Queue<int> q3 = Queue<int>({ 0,10,20 });
    front = q3.front()->value();
    back = q3.back()->value();
    res = 0;
    if (if_error(front, 0) || if_error(back, 20))
    {
        res = 1;
    }
    std::cout << "Queue q3 front: " << front << ", back: " << back << '\n';
    std::cout << "Expected front: " << 0 << ", back: " << 20 << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
