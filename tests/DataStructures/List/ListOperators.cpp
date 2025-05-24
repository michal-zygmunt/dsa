/**
 * @file ListOperators.cpp
 * @brief This file tests overloading operators of List
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */


#include "common.h"
#include "List.h"

int main()
{
    std::cout << "Start ListOperators test:\n";

    bool res{};
    std::initializer_list<int> expected{};

    List<int> l1({ 1,2,3 });
    List<int> l2({ 4,5,6 });
    List<int> l3({ 1, 2, 3, 4 });
    std::cout << "List l1:\t" << l1 << '\n';
    std::cout << "List l2:\t" << l2 << '\n';
    std::cout << "List l3:\t" << l3 << "\n\n";

    List<int> l4(l1 + l2);
    expected = { 1,2,3,4,5,6 };
    res = if_error(l4, expected);
    std::cout << "List l4:\t" << l4 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l5(0);
    l5 += l2;
    expected = { 0,4,5,6 };
    res = if_error(l5, expected);
    std::cout << "List l5:\t" << l5 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l6(0);
    l6 += { 4, 5, 6 };
    expected = { 0,4,5,6 };
    res = if_error(l6, expected);
    std::cout << "List l6:\t" << l6 << '\n';
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