/**
 * @file ForwardListGrow.cpp
 * @brief This file tests functions resizing ForwardList objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/ForwardList.h"

#include <cstdint>
#include <initializer_list>
#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start ForwardListResize test:\n";

    dsa::ForwardList<int> list1 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
    list1.resize(3);
    const std::initializer_list<int> expected1 = { 1, 2, 3 };
    tests::compare("ForwardList1", list1, expected1);

    dsa::ForwardList<int> list2 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
    list2.resize(5);
    const std::initializer_list<int> expected2 = { 1, 2, 3, 4, 5 };
    tests::compare("ForwardList2", list2, expected2);

    dsa::ForwardList<int> list3 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
    list3.resize(8);
    const std::initializer_list<int> expected3 = { 1, 2, 3, 4, 5, 0, 0, 0 };
    tests::compare("ForwardList3", list3, expected3);

    dsa::ForwardList<int> list4;
    list4.resize(5);
    const std::initializer_list<int> expected4 = { 0, 0, 0, 0, 0 };
    tests::compare("ForwardList4", list4, expected4);

    dsa::ForwardList<int> list5 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
    list5.resize(3, 10);
    const std::initializer_list<int> expected5 = { 1, 2, 3 };
    tests::compare("ForwardList5", list5, expected5);

    dsa::ForwardList<int> list6 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
    list6.resize(5, 10);
    const std::initializer_list<int> expected6 = { 1, 2, 3, 4, 5 };
    tests::compare("ForwardList6", list6, expected6);

    dsa::ForwardList<int> list7 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
    list7.resize(8, 10);
    const std::initializer_list<int> expected7 = { 1, 2, 3, 4, 5, 10, 10, 10 };
    tests::compare("ForwardList7", list7, expected7);

    dsa::ForwardList<int> list8;
    list8.resize(5, 10);
    const std::initializer_list<int> expected8 = { 10, 10, 10, 10, 10 };
    tests::compare("ForwardList8", list8, expected8);

    const dsa::ForwardList<int> list9;
    tests::compare("max_size()", list9.max_size(), UINTMAX_MAX);

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
