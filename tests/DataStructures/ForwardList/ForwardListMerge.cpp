/**
 * @file ForwardListGrow.cpp
 * @brief This file tests functions merging ForwardList objects
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
    std::cout << "Start ForwardListMerge test:\n";

    bool res{};
    std::initializer_list<int> expected{};
    std::initializer_list<int> expected_1{ 1, 2, 3, 4, 5 };
    std::initializer_list<int> expected_2{ 10, 20, 30, 40, 50 };

    ForwardList<int> l1 = ForwardList<int>(expected_1);
    ForwardList<int> l2 = ForwardList<int>(expected_2);
    l1.merge(l2);
    expected = { 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
    res = if_error(l1, expected);
    std::cout << "ForwardList l1:\t" << l1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = {};
    res = if_error(l2, expected);
    std::cout << "ForwardList l2:\t" << l2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l3 = ForwardList<int>(expected_1);
    ForwardList<int> l4;
    l4.merge(l3);
    expected = { };
    res = if_error(l3, expected);
    std::cout << "ForwardList l3:\t" << l3 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = expected_1;
    res = if_error(l4, expected);
    std::cout << "ForwardList l4:\t" << l4 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
