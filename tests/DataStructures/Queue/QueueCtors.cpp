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
#include "Queue.h"

int main()
{
    std::cout << "Start QueueCtors test:\n";

    bool res{};
    std::initializer_list<int> expected{ 0,10,20 };

    std::cout << "Default ctor\n";
    Queue<int> q1;
    q1.push(0);
    q1.push(10);
    q1.push(20);
    res = if_error(q1, expected);
    std::cout << "Queue q1:\t" << q1 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Value ctor\n";
    Queue<int> q2(0);
    q2.push(10);
    q2.push(20);
    res = if_error(q2, expected);
    std::cout << "Queue q2:\t" << q2 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Initializer list ctor\n";
    Queue<int> q3(expected);
    res = if_error(q3, expected);
    std::cout << "Queue q3:\t" << q3 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Copy ctor\n";
    Queue<int> q4{ q1 };
    res = if_error(q4, expected);
    std::cout << "Queue q4:\t" << q4 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Copy assignment ctor\n";
    Queue<int> q5;
    q5.push(1);
    q5.push(2);
    q5.push(3);
    q5.push(4);
    q5.push(5);
    q5 = q1;
    res = if_error(q5, expected);
    std::cout << "Queue q5:\t" << q5 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Move ctor\n";
    Queue<int> q6 = std::move(Queue<int>(q1));
    res = if_error(q6, expected);
    std::cout << "Queue q6:\t" << q6 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Move assignment ctor\n";
    Queue<int> q7(0);
    q7 = std::move(Queue<int>(q1));
    res = if_error(q7, expected);
    std::cout << "Queue q7:\t" << q7 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
