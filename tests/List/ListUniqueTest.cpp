/**
 * @file ListGrow.cpp
 * @brief This file tests functions checking values of List objects
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

    std::cout << "Start ListUnique test:\n";

    dsa::List<int> list1 = dsa::List<int>({ 1, 2, 3, 4, 5 });
    list1.unique();
    const std::initializer_list<int> expected1 = { 1, 2, 3, 4, 5 };
    tests::compare("List1", list1, expected1);

    dsa::List<int> list2 = dsa::List<int>({ 1, 4, 2, 3, 2, 4, 3, 5, 1 });
    list2.unique();
    const std::initializer_list<int> expected2 = { 1, 4, 2, 3, 5 };
    tests::compare("List2", list2, expected2);

    dsa::List<int> list3 = dsa::List<int>({ 1, 1, 2, 4, 2, 1, 3, 1, 1 });
    list3.unique();
    const std::initializer_list<int> expected3 = { 1, 2, 4, 3 };
    tests::compare("List3", list3, expected3);

    dsa::List<int> list4 = dsa::List<int>({ 1, 1, 1, 2, 2, 2, 1, 1, 1 });
    list4.unique();
    const std::initializer_list<int> expected4 = { 1, 2 };
    tests::compare("List4", list4, expected4);

    dsa::List<int> list5 = dsa::List<int>({ 0, 0, 0, 0, 0, 0 });
    list5.unique();
    const std::initializer_list<int> expected5 = { 0 };
    tests::compare("List5", list5, expected5);

    dsa::List<int> list6 = dsa::List<int>();
    list6.unique();
    const std::initializer_list<int> expected6 = { };
    tests::compare("List6", list6, expected6);

    dsa::List<int> list7;
    list7.unique();
    const std::initializer_list<int> expected7 = {};
    tests::compare("List7", list7, expected7);

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
