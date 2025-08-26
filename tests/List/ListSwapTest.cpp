/**
 * @file ListGrow.cpp
 * @brief This file tests functions swapping List objects
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

    std::cout << "Start ListSwap test:\n";

    const std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
    const std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };

    dsa::List<int> list1 = dsa::List<int>(il_1);
    dsa::List<int> list2 = dsa::List<int>(il_2);
    list1.swap(list2);
    const std::initializer_list<int> expected1 = { 10, 20, 30, 40, 50 };
    tests::compare("List1", list1, expected1);
    const std::initializer_list<int> expected2 = { 1, 2, 3, 4, 5 };
    tests::compare("List2", list2, expected2);

    dsa::List<int> list3 = dsa::List<int>(il_1);
    dsa::List<int> list4;
    list3.swap(list4);
    const std::initializer_list<int> expected3 = { };
    tests::compare("List3", list3, expected3);
    const std::initializer_list<int> expected4 = { 1, 2, 3, 4, 5 };
    tests::compare("List4", list4, expected4);

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
