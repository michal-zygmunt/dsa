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
#include "dsa/List.h"

int main()
{
    std::cout << "Start ListSet test:\n";

    dsa::List<int> l1 = dsa::List<int>({ 0, 10, 20 });
    // Try setting values for nodes with invalid indexes
    constexpr int new_value{ 50 };
    l1.set(static_cast<size_t>(-1), new_value);
    l1.set(1, new_value);
    l1.set(100, new_value);
    std::initializer_list<int> expected_1{ 0, 50, 20 };
    tests::compare("List l1", l1, expected_1);

    dsa::List<int> l2 = dsa::List<int>({ 0, 10, 20 });
    l2.assign(4, 1);
    std::initializer_list<int> expected_2 = { 1, 1, 1, 1 };
    tests::compare("List l2", l2, expected_2);

    dsa::List<int> l3 = dsa::List<int>({ 0, 10, 20 });
    std::initializer_list<int> expected_3 = { 1, 2, 3, 4 };
    l3.assign(expected_3);
    tests::compare("List l3", l3, expected_3);

    return tests::failed;
}