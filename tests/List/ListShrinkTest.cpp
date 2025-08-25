/**
 * @file ListShrink.cpp
 * @brief This file tests functions decreasing List length
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

    std::cout << "Start ListShrink test:\n";

    dsa::List<int> list1 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
    list1.erase(list1.begin()[list1.size() - 1]);
    list1.pop_front();
    auto indexes = { 100, 5, 2, 0 };
    for (const auto& idx : indexes)
    {
        list1.erase(list1.begin()[static_cast<size_t>(idx)]);
    }
    std::initializer_list<int> expected1 = { 20, 40 };
    tests::compare("List1", list1, expected1);

    dsa::List<int> list2 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
    list2.erase(list2.begin()[1], list2.begin()[3]);
    std::initializer_list<int> expected2 = { 0, 30, 40, 50 };
    tests::compare("List2", list2, expected2);

    dsa::List<int> list3 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
    list3.erase(list3.begin()[1]);
    list3.erase(list3.begin()[1], list3.begin()[3]);
    std::initializer_list<int> expected3 = { 0, 40, 50 };
    tests::compare("List3", list3, expected3);

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}