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

    List<int> l1({ 1, 2, 3 });
    List<int> l2({ 4, 5, 6 });
    std::cout << "List l1:\t" << l1 << '\n';
    std::cout << "List l2:\t" << l2 << '\n';

    List<int> l3(l1 + l2);
    expected = { 1, 2, 3, 4, 5, 6 };
    res = if_error(l3, expected);
    std::cout << "List l3:\t" << l3 << '\n';
    std::cout << "Expected:\t\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l4(0);
    l4 += l2;
    expected = { 0, 4, 5, 6 };
    res = if_error(l4, expected);
    std::cout << "List l4:\t" << l4 << '\n';
    std::cout << "Expected:\t\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}