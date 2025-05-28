/**
 * @file ListReverse.cpp
 * @brief This file tests reversing order of List Nodes
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
    std::cout << "Start ListReverse test:\n";

    bool res{};
    std::initializer_list<int> expected{ 50, 40, 30, 20, 10, 0 };

    List<int> l1 = List<int>({ 0, 10, 20, 30, 40, 50 });
    l1.reverse();

    res = if_error(l1, expected);
    std::cout << "List:\t\t" << l1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}