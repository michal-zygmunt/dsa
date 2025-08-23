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
    std::cout << "Start ListShrink test:\n";

    dsa::List<int> l1 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
    l1.erase(l1.begin()[l1.size() - 1]);
    l1.pop_front();
    auto indexes = { 100, 5, 2, 0, -1 };
    for (const auto& i : indexes)
    {
        l1.erase(l1.begin()[static_cast<size_t>(i)]);
    }
    std::initializer_list<int> expected_1 = { 20, 40 };
    tests::compare("List l1", l1, expected_1);

    dsa::List<int> l2 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
    l2.erase(l2.begin()[1], l2.begin()[3]);
    std::initializer_list<int> expected_2 = { 0, 30, 40, 50 };
    tests::compare("List l2", l2, expected_2);

    dsa::List<int> l3 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
    l3.erase(l3.begin()[1]);
    l3.erase(l3.begin()[1], l3.begin()[3]);
    std::initializer_list<int> expected_3 = { 0, 40, 50 };
    tests::compare("List l3", l3, expected_3);

    return tests::failed;
}