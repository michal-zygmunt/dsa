/**
 * @file QueueShrink.cpp
 * @brief This file tests functions decreasing Queue length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "Queue.h"

#include <initializer_list>

int main()
{
    std::cout << "Start QueueShrink test:\n";

    bool res{};
    std::initializer_list<int> expected{};

    Queue<int> q1 = Queue<int>({ 0,10,20,30,40,50 });
    q1.pop();
    q1.pop();
    expected = { 20,30,40,50 };
    res = if_error(q1, expected);
    std::cout << "Queue:\t\t" << q1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Queue<int> q2 = Queue<int>({ 0,10,20 });
    q2.pop();
    q2.pop();
    q2.pop();
    expected = std::initializer_list<int>{ };
    res = if_error(q2, expected);
    std::cout << "Queue:\t" << q2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Queue<int> q3 = Queue<int>({ 0,10,20 });
    res = if_error(static_cast<int>(q3.size()), 3);
    std::cout << "Queue size:\t" << q2.size() << '\n';
    std::cout << "Expected:\t" << 0 << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Queue<int> q4 = Queue<int>();
    q4.pop();
    res = if_error(static_cast<int>(q4.size()), 0);
    std::cout << "Queue size:\t" << q4.size() << '\n';
    std::cout << "Expected:\t" << 0 << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Queue<int> q5;
    res = if_error(q5.empty(), true);
    std::cout << "Queue size:\t" << q5.size() << '\n';
    std::cout << "Expected:\t" << 0 << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}