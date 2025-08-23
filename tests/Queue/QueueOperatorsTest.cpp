/**
 * @file QueueOperators.cpp
 * @brief This file tests overloading operators of Queue
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/Queue.h"

#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    std::cout << "Start QueueOperators test:\n";

    dsa::Queue<int> q1({ 1,2,3 });
    dsa::Queue<int> q2({ 4,5,6 });
    dsa::Queue<int> q3({ 1, 2, 3, 4 });
    std::cout << "Queue q1:\t" << q1 << '\n';
    std::cout << "Queue q2:\t" << q2 << '\n';
    std::cout << "Queue q3:\t" << q3 << "\n\n";

    std::cout << "Compare operators for objects of the same size\n\n";

    tests::compare("Operator ==", q1 == q1, true);

    tests::compare("Operator !=", q1 != q2, true);

    tests::compare("Operator <", q1 < q2, true);

    tests::compare("Operator >", q2 > q1, true);

    tests::compare("Operator <=", q1 <= q2, true);

    tests::compare("Operator <=", q2 >= q1, true);

    std::cout << "Compare operators for objects of different size\n\n";

    tests::compare("Operator == ", q1 == q3, false);

    tests::compare("Operator !=", q1 != q3, true);

    tests::compare("Operator <", q3 < q2, true);

    tests::compare("Operator >", q3 > q1, false);

    tests::compare("Operator <=", q1 <= q3, true);

    tests::compare("Operator >=", q2 >= q3, true);

    return tests::failed;
}
