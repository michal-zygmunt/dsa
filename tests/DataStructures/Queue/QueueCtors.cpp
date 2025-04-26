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
    Queue<int> l1;
    l1.push(0);
    l1.push(10);
    l1.push(20);
    res = if_error(l1, expected);
    std::cout << "Queue l1:\t" << l1 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Value ctor\n";
    Queue<int> l2(0);
    l2.push(10);
    l2.push(20);
    res = if_error(l2, expected);
    std::cout << "Queue l2:\t" << l2 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Initializer list ctor\n";
    Queue<int> l3(expected);
    res = if_error(l3, expected);
    std::cout << "Queue l3:\t" << l3 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Copy ctor\n";
    Queue<int> l4{ l1 };
    res = if_error(l4, expected);
    std::cout << "Queue l4:\t" << l4 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Copy assignment ctor\n";
    Queue<int> l5;
    l5.push(1);
    l5.push(2);
    l5.push(3);
    l5.push(4);
    l5.push(5);
    l5 = l1;
    res = if_error(l5, expected);
    std::cout << "Queue l5:\t" << l5 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Move ctor\n";
    Queue<int> l6 = std::move(Queue<int>(l1));
    res = if_error(l6, expected);
    std::cout << "Queue l6:\t" << l6 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Move assignment ctor\n";
    Queue<int> l7(0);
    l7 = std::move(Queue<int>(l1));
    res = if_error(l7, expected);
    std::cout << "Queue l7:\t" << l7 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
