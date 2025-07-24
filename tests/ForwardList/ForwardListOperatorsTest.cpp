/**
 * @file ForwardListOperators.cpp
 * @brief This file tests overloading operators of ForwardList
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/ForwardList.h"

int main()
{
    std::cout << "Start ForwardListOperators test:\n";

    dsa::ForwardList<int> l1({ 1,2,3 });
    dsa::ForwardList<int> l2({ 4,5,6 });
    dsa::ForwardList<int> l3({ 1, 2, 3, 4 });
    std::cout << "ForwardList l1:\t" << l1 << '\n';
    std::cout << "ForwardList l2:\t" << l2 << '\n';
    std::cout << "ForwardList l3:\t" << l3 << "\n\n";

    dsa::ForwardList<int> l4(l1 + l2);
    std::initializer_list<int> expected_4 = { 1,2,3,4,5,6 };
    tests::compare("ForwardList l4", l4, expected_4);

    dsa::ForwardList<int> l5(0);
    l5 += l2;
    std::initializer_list<int> expected_5 = { 0,4,5,6 };
    tests::compare("ForwardList l5", l5, expected_5);

    dsa::ForwardList<int> l6(0);
    l6 += { 4, 5, 6 };
    std::initializer_list<int> expected_6 = { 0,4,5,6 };
    tests::compare("ForwardList l6", l6, expected_6);

    std::cout << "Compare operators for objects of the same size\n\n";

    tests::compare("Operator ==", l1 == l1, true);

    tests::compare("Operator !=", l1 != l2, true);

    tests::compare("Operator <", l1 < l2, true);

    tests::compare("Operator >", l2 > l1, true);

    tests::compare("Operator <=", l1 <= l2, true);

    tests::compare("Operator <=", l2 >= l1, true);

    std::cout << "Compare operators for objects of different size\n\n";

    tests::compare("Operator ==", l1 == l3, false);

    tests::compare("Operator !=", l1 != l3, true);

    tests::compare("Operator <", l3 < l2, true);

    tests::compare("Operator >", l3 > l1, false);

    tests::compare("Operator <=", l1 <= l3, true);

    tests::compare("Operator >=", l2 >= l3, true);

    return tests::failed;
}
