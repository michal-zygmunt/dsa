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

    ForwardList<int> l1({ 1, 2, 3 });
    ForwardList<int> l2({ 4, 5, 6 });
    std::cout << "ForwardList l1:\t" << l1 << '\n';
    std::cout << "ForwardList l2:\t" << l2 << '\n';

    ForwardList<int> l3(l1 + l2);
    expected = { 1, 2, 3, 4, 5, 6 };
    res = if_error(l3, expected);
    std::cout << "ForwardList l3:\t" << l3 << '\n';
    std::cout << "Expected:\t\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l4(0);
    l4 += l2;
    expected = { 0, 4, 5, 6 };
    res = if_error(l4, expected);
    std::cout << "ForwardList l4:\t" << l4 << '\n';
    std::cout << "Expected:\t\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
