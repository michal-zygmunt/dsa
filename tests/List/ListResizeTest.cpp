/**
 * @file ListGrow.cpp
 * @brief This file tests functions resizing List objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/List.h"

#include <cstdint>

int main()
{
    std::cout << "Start ListResize test:\n";

    dsa::List<int> l1 = dsa::List<int>({ 1, 2, 3, 4, 5 });
    l1.resize(3);
    std::initializer_list<int> expected_1 = { 1, 2, 3 };
    tests::compare("List l1", l1, expected_1);

    dsa::List<int> l2 = dsa::List<int>({ 1, 2, 3, 4, 5 });
    l2.resize(5);
    std::initializer_list<int> expected_2 = { 1, 2, 3, 4, 5 };
    tests::compare("List l2", l2, expected_2);

    dsa::List<int> l3 = dsa::List<int>({ 1, 2, 3, 4, 5 });
    l3.resize(8);
    std::initializer_list<int> expected_3 = { 1, 2, 3, 4, 5, 0, 0, 0 };
    tests::compare("List l3", l3, expected_3);

    dsa::List<int> l4;
    l4.resize(5);
    std::initializer_list<int> expected_4 = { 0, 0, 0, 0, 0 };
    tests::compare("List l4", l4, expected_4);

    dsa::List<int> l5 = dsa::List<int>({ 1, 2, 3, 4, 5 });
    l5.resize(3, 10);
    std::initializer_list<int> expected_5 = { 1, 2, 3 };
    tests::compare("List l5", l5, expected_5);

    dsa::List<int> l6 = dsa::List<int>({ 1, 2, 3, 4, 5 });
    l6.resize(5, 10);
    std::initializer_list<int> expected_6 = { 1, 2, 3, 4, 5 };
    tests::compare("List l6", l6, expected_6);

    dsa::List<int> l7 = dsa::List<int>({ 1, 2, 3, 4, 5 });
    l7.resize(8, 10);
    std::initializer_list<int> expected_7 = { 1, 2, 3, 4, 5, 10, 10, 10 };
    tests::compare("List l7", l7, expected_7);

    dsa::List<int> l8;
    l8.resize(5, 10);
    std::initializer_list<int> expected_8 = { 10, 10, 10, 10, 10 };
    tests::compare("List l8", l8, expected_8);

    dsa::List<int> l9;
    tests::compare("max_size()", l9.max_size(), UINTMAX_MAX);

    return tests::failed;
}
