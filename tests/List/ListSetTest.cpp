/**
 * @file ListSet.cpp
 * @brief This file tests setting values of List Nodes
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/List.h"

#include <cstddef>
#include <initializer_list>
#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start ListSet test:\n";

    dsa::List<int> list1 = dsa::List<int>({ 0, 10, 20 });
    // Try setting values for nodes with invalid indexes
    constexpr int new_value{ 50 };
    list1.set(static_cast<size_t>(-1), new_value);
    list1.set(1, new_value);
    list1.set(100, new_value);
    const std::initializer_list<int> expected1{ 0, 50, 20 };
    tests::compare("List1", list1, expected1);

    dsa::List<int> list2 = dsa::List<int>({ 0, 10, 20 });
    list2.assign(4, 1);
    const std::initializer_list<int> expected2 = { 1, 1, 1, 1 };
    tests::compare("List2", list2, expected2);

    dsa::List<int> list3 = dsa::List<int>({ 0, 10, 20 });
    const std::initializer_list<int> expected3 = { 1, 2, 3, 4 };
    list3.assign(expected3);
    tests::compare("List3", list3, expected3);

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}