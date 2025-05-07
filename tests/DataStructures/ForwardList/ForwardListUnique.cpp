/**
 * @file ForwardListGrow.cpp
 * @brief This file tests functions checking values of ForwardList objects
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
    std::cout << "Start ForwardListUnique test:\n";

    bool res{};
    std::initializer_list<int> expected{};

    ForwardList<int> l1 = ForwardList<int>({ 1, 2, 3, 4, 5 });
    l1.unique();
    expected = { 1, 2, 3, 4, 5 };
    res = if_error(l1, expected);
    std::cout << "ForwardList l1:\t" << l1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l2 = ForwardList<int>({ 1, 4, 2, 3, 2, 4, 3, 5, 1 });
    l2.unique();
    expected = { 1, 4, 2, 3, 5 };
    res = if_error(l2, expected);
    std::cout << "ForwardList l2:\t" << l2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l3 = ForwardList<int>({ 1, 1, 2, 4, 2, 1, 3, 1, 1 });
    l3.unique();
    expected = { 1, 2, 4, 3 };
    res = if_error(l3, expected);
    std::cout << "ForwardList l3:\t" << l3 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l4 = ForwardList<int>({ 1, 1, 1, 2, 2, 2, 1, 1, 1 });
    l4.unique();
    expected = { 1, 2 };
    res = if_error(l4, expected);
    std::cout << "ForwardList l4:\t" << l4 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l5 = ForwardList<int>({ 0, 0, 0, 0, 0, 0 });
    l5.unique();
    expected = { 0 };
    res = if_error(l5, expected);
    std::cout << "ForwardList l5:\t" << l5 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l6 = ForwardList<int>();
    l6.unique();
    expected = { };
    res = if_error(l6, expected);
    std::cout << "ForwardList l6:\t" << l6 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l7;
    l7.unique();
    expected = {};
    res = if_error(l7, expected);
    std::cout << "ForwardList l7:\t" << l7 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
