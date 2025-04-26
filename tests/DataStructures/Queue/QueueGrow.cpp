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
#include "Queue.h"

int main()
{
    std::cout << "Start QueueGrow test:\n";

    bool res{};
    std::initializer_list<int> expected{ 10, 20, 30, 40 };

    Queue<int> q1 = Queue<int>(10);
    q1.push(20);
    q1.push(30);
    q1.push(40);
    res = if_error(q1, expected);
    std::cout << "Queue:\t\t" << q1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Queue<int> q2 = Queue<int>(10);
    q2.push_range({ 20, 30, 40 });
    res = if_error(q2, expected);
    std::cout << "Queue:\t\t" << q2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
