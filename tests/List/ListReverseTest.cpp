/**
 * @file ListReverse.cpp
 * @brief This file tests reversing order of List Nodes
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/List.h"

#include <initializer_list>
#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start ListReverse test:\n";

    dsa::List<int> list1 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
    list1.reverse();
    const std::initializer_list<int> expected1 = { 50, 40, 30, 20, 10, 0 };
    tests::compare("List1", list1, expected1);

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}