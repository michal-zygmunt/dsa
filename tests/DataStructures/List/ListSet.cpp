/**
 * @file ListSet.cpp
 * @brief This file tests setting values of List Nodes
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
    std::cout << "Start ListSet test:\n";

    bool res{};
    std::initializer_list<int> expected{ 0, 50, 20 };

    List<int> l1 = List<int>({ 0, 10, 20 });

    // Try setting values for nodes with invalid indexes
    constexpr int new_value{ 50 };
    bool if_set{};
    if_set |= l1.set(-1, new_value);
    if_set |= l1.set(1, new_value);
    if_set |= l1.set(100, new_value);

    res = if_error(l1, expected);
    std::cout << "List:\t" << l1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}