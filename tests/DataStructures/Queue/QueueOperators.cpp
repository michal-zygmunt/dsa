/**
 * @file QueueOperators.cpp
 * @brief This file tests overloading operators of Queue
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
    std::cout << "Start QueueOperators test:\n";

    bool res{};
    std::initializer_list<int> expected{};

    Queue<int> q1({ 1,2,3 });
    Queue<int> q2({ 4,5,6 });
    Queue<int> q3({ 1, 2, 3, 4 });
    std::cout << "Queue q1:\t" << q1 << '\n';
    std::cout << "Queue q2:\t" << q2 << '\n';
    std::cout << "Queue q3:\t" << q3 << "\n\n";

    Queue<int> q4(q1 + q2);
    expected = { 1,2,3,4,5,6 };
    res = if_error(q4, expected);
    std::cout << "Queue q4:\t" << q4 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Queue<int> q5(0);
    q5 += q2;
    expected = { 0,4,5,6 };
    res = if_error(q5, expected);
    std::cout << "Queue q5:\t" << q5 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Queue<int> q6(0);
    q6 += { 4, 5, 6 };
    expected = { 0,4,5,6 };
    res = if_error(q6, expected);
    std::cout << "Queue q6:\t" << q6 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Compare operators for objects of the same size\n\n";

    res = if_error(q1 == q1, true);
    std::cout << "Operator ==:\t" << res << '\n';
    std::cout << "Expected:\t\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(q1 != q2, true);
    std::cout << "Operator !=:\t" << res << '\n';
    std::cout << "Expected:\t\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(q1 < q2, true);
    std::cout << "Operator <:\t\t" << res << '\n';
    std::cout << "Expected:\t\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(q2 > q1, true);
    std::cout << "Operator >:\t\t" << res << '\n';
    std::cout << "Expected:\t\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(q1 <= q2, true);
    std::cout << "Operator <=:\t" << res << '\n';
    std::cout << "Expected:\t\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(q2 >= q1, true);
    std::cout << "Operator <=:\t" << res << '\n';
    std::cout << "Expected:\t\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Compare operators for objects of different size\n\n";

    res = if_error(q1 == q3, false);
    std::cout << "Operator ==:\t" << res << '\n';
    std::cout << "Expected:\t\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(q1 != q3, true);
    std::cout << "Operator !=:\t" << res << '\n';
    std::cout << "Expected:\t\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(q3 < q2, true);
    std::cout << "Operator <:\t\t" << res << '\n';
    std::cout << "Expected:\t\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(q3 > q1, false);
    std::cout << "Operator >:\t\t" << res << '\n';
    std::cout << "Expected:\t\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(q1 <= q3, true);
    std::cout << "Operator <=:\t" << res << '\n';
    std::cout << "Expected:\t\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(q2 >= q3, true);
    std::cout << "Operator >=:\t" << res << '\n';
    std::cout << "Expected:\t\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
