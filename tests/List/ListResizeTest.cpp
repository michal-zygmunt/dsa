/**
 * @file ListGrow.cpp
 * @brief This file tests functions resizing List objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/List.h"

#include <cstdint>
#include <initializer_list>
#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start ListResize test:\n";

    dsa::List<int> list1 = dsa::List<int>({ 1, 2, 3, 4, 5 });
    list1.resize(3);
    std::initializer_list<int> expected1 = { 1, 2, 3 };
    tests::compare("List1", list1, expected1);

    dsa::List<int> list2 = dsa::List<int>({ 1, 2, 3, 4, 5 });
    list2.resize(5);
    std::initializer_list<int> expected2 = { 1, 2, 3, 4, 5 };
    tests::compare("List2", list2, expected2);

    dsa::List<int> list3 = dsa::List<int>({ 1, 2, 3, 4, 5 });
    list3.resize(8);
    std::initializer_list<int> expected3 = { 1, 2, 3, 4, 5, 0, 0, 0 };
    tests::compare("List3", list3, expected3);

    dsa::List<int> list4;
    list4.resize(5);
    std::initializer_list<int> expected4 = { 0, 0, 0, 0, 0 };
    tests::compare("List4", list4, expected4);

    dsa::List<int> list5 = dsa::List<int>({ 1, 2, 3, 4, 5 });
    list5.resize(3, 10);
    std::initializer_list<int> expected5 = { 1, 2, 3 };
    tests::compare("List5", list5, expected5);

    dsa::List<int> list6 = dsa::List<int>({ 1, 2, 3, 4, 5 });
    list6.resize(5, 10);
    std::initializer_list<int> expected6 = { 1, 2, 3, 4, 5 };
    tests::compare("List6", list6, expected6);

    dsa::List<int> list7 = dsa::List<int>({ 1, 2, 3, 4, 5 });
    list7.resize(8, 10);
    std::initializer_list<int> expected7 = { 1, 2, 3, 4, 5, 10, 10, 10 };
    tests::compare("List7", list7, expected7);

    dsa::List<int> list8;
    list8.resize(5, 10);
    std::initializer_list<int> expected8 = { 10, 10, 10, 10, 10 };
    tests::compare("List8", list8, expected8);

    dsa::List<int> list9;
    tests::compare("max_size()", list9.max_size(), UINTMAX_MAX);

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
