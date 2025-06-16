/**
 * @file QueueSet.cpp
 * @brief This file tests setting values of Queue
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
    std::cout << "Start QueueSet test:\n";

    bool res{};
    std::initializer_list<int> expected{ 50,10,20 };

    Queue<int> q1 = Queue<int>({ 0,10,20 });
    q1.front() = 50;
    res = if_error(q1, expected);
    std::cout << "Queue:\t\t" << q1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Queue<int> q2 = Queue<int>({ 0,10,20 });
    Queue<int> q3 = Queue<int>({ 50,10,20 });
    q2.swap(q3);
    res = if_error(q2, expected);
    std::cout << "Queue:\t\t" << q2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Queue<int> q4 = Queue<int>({ 50,10,20 });
    q4.swap(q4);
    res = if_error(q4, expected);
    std::cout << "Queue:\t\t" << q4 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
