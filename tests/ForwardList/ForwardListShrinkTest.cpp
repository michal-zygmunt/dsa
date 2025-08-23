/**
 * @file ForwardListShrink.cpp
 * @brief This file tests functions decreasing ForwardList length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/ForwardList.h"

#include <cstddef>
#include <initializer_list>
#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    std::cout << "Start ForwardListShrink test:\n";

    dsa::ForwardList<int> l1 = dsa::ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
    l1.erase_after(l1.begin()[l1.size() - 2]);
    l1.pop_front();
    auto indexes = { 100, 5, 2, 0, -1 };
    for (const auto& i : indexes)
    {
        l1.erase_after(l1.begin()[static_cast<size_t>(i)]);
    }
    std::initializer_list<int> expected_1 = { 10, 30 };
    tests::compare("ForwardList l1", l1, expected_1);

    dsa::ForwardList<int> l2 = dsa::ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
    l2.erase_after(l2.begin()[1], l2.begin()[3]);
    std::initializer_list<int> expected_2 = { 0, 10, 30, 40, 50 };
    tests::compare("ForwardList l2", l2, expected_2);

    dsa::ForwardList<int> l3 = dsa::ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
    l3.erase_after(l3.begin()[1]);
    l3.erase_after(l3.begin()[1], l3.begin()[3]);
    std::initializer_list<int> expected_3 = { 0, 10, 40, 50 };
    tests::compare("ForwardList l3", l3, expected_3);

    dsa::ForwardList<int> l4 = dsa::ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
    l4.erase_after(l4.begin()[1]);
    l4.erase_after(l4.begin()[1], l4.begin()[4]);
    std::initializer_list<int> expected_4 = { 0, 10, 50 };
    tests::compare("ForwardList l4", l4, expected_4);

    dsa::ForwardList<int> l5 = dsa::ForwardList<int>({ 0, 10, 0, 0, 40, 0 });
    l5.remove(0);
    std::initializer_list<int> expected_5 = { 10, 40 };
    tests::compare("ForwardList l5", l5, expected_5);

    dsa::ForwardList<int> l6 = dsa::ForwardList<int>({ 0, 0, 0, 0, 0, 0 });
    l6.remove(0);
    std::initializer_list<int> expected_6 = { };
    tests::compare("ForwardList l6", l6, expected_6);

    dsa::ForwardList<int> l7 = dsa::ForwardList<int>({ 0 });
    tests::compare(l7.empty(), false);
    l7.clear();
    tests::compare(l7.empty(), true);
    std::initializer_list<int> expected_7 = { };
    tests::compare("ForwardList l7", l7, expected_7);

    dsa::ForwardList<int> l8 = dsa::ForwardList<int>({ 10, 20, 30 });
    l8.pop_front();
    l8.pop_front();
    l8.pop_front();
    l8.pop_front();
    std::initializer_list<int> expected_8 = { };
    tests::compare("ForwardList l8", l8, expected_8);

    return tests::failed;
}