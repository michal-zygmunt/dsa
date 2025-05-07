/**
 * @file ForwardListOperators.cpp
 * @brief This file tests overloading operators of ForwardList
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "ForwardList.h"

int main()
{
    std::cout << "Start ForwardListOperators test:\n";

    bool res{};
    std::initializer_list<int> expected{};

    ForwardList<int> l1({ 1,2,3 });
    ForwardList<int> l2({ 4,5,6 });
    ForwardList<int> l3({ 1, 2, 3, 4 });
    std::cout << "ForwardList l1:\t" << l1 << '\n';
    std::cout << "ForwardList l2:\t" << l2 << '\n';
    std::cout << "ForwardList l3:\t" << l3 << "\n\n";

    ForwardList<int> l4(l1 + l2);
    expected = { 1,2,3,4,5,6 };
    res = if_error(l4, expected);
    std::cout << "ForwardList l4:\t" << l4 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l5(0);
    l5 += l2;
    expected = { 0,4,5,6 };
    res = if_error(l5, expected);
    std::cout << "ForwardList l5:\t" << l5 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l6(0);
    l6 += { 4, 5, 6 };
    expected = { 0,4,5,6 };
    res = if_error(l6, expected);
    std::cout << "ForwardList l6:\t" << l6 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Compare operators for objects of the same size\n\n";

    res = if_error(l1 == l1, true);
    std::cout << "Operator ==\t" << res << '\n';
    std::cout << "Expected:\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(l1 != l2, true);
    std::cout << "Operator !=\t" << res << '\n';
    std::cout << "Expected:\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(l1 < l2, true);
    std::cout << "Operator <\t" << res << '\n';
    std::cout << "Expected:\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(l2 > l1, true);
    std::cout << "Operator >\t" << res << '\n';
    std::cout << "Expected:\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(l1 <= l2, true);
    std::cout << "Operator <=\t" << res << '\n';
    std::cout << "Expected:\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(l2 >= l1, true);
    std::cout << "Operator <=\t" << res << '\n';
    std::cout << "Expected:\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Compare operators for objects of different size\n\n";

    res = if_error(l1 == l3, false);
    std::cout << "Operator ==\t" << res << '\n';
    std::cout << "Expected:\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(l1 != l3, true);
    std::cout << "Operator !=\t" << res << '\n';
    std::cout << "Expected:\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(l3 < l2, true);
    std::cout << "Operator <\t" << res << '\n';
    std::cout << "Expected:\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(l3 > l1, false);
    std::cout << "Operator >\t" << res << '\n';
    std::cout << "Expected:\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(l1 <= l3, true);
    std::cout << "Operator <=\t" << res << '\n';
    std::cout << "Expected:\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    res = if_error(l2 >= l3, true);
    std::cout << "Operator >=\t" << res << '\n';
    std::cout << "Expected:\t" << false << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
