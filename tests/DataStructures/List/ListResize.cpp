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
#include "List.h"

int main()
{
    std::cout << "Start ListResize test:\n";

    std::initializer_list<int> expected{};

    List<int> l1 = List<int>({ 1, 2, 3, 4, 5 });
    l1.resize(3);
    expected = { 1, 2, 3 };
    tests::compare("List l1", l1, expected);

    List<int> l2 = List<int>({ 1, 2, 3, 4, 5 });
    l2.resize(5);
    expected = { 1, 2, 3, 4, 5 };
    tests::compare("List l2", l2, expected);

    List<int> l3 = List<int>({ 1, 2, 3, 4, 5 });
    l3.resize(8);
    expected = { 1, 2, 3, 4, 5, 0, 0, 0 };
    tests::compare("List l3", l3, expected);

    List<int> l4;
    l4.resize(5);
    expected = { 0, 0, 0, 0, 0 };
    tests::compare("List l4", l4, expected);

    List<int> l5 = List<int>({ 1, 2, 3, 4, 5 });
    l5.resize(3, 10);
    expected = { 1, 2, 3 };
    tests::compare("List l5", l5, expected);

    List<int> l6 = List<int>({ 1, 2, 3, 4, 5 });
    l6.resize(5, 10);
    expected = { 1, 2, 3, 4, 5 };
    tests::compare("List l6", l6, expected);

    List<int> l7 = List<int>({ 1, 2, 3, 4, 5 });
    l7.resize(8, 10);
    expected = { 1, 2, 3, 4, 5, 10, 10, 10 };
    tests::compare("List l7", l7, expected);

    List<int> l8;
    l8.resize(5, 10);
    expected = { 10, 10, 10, 10, 10 };
    tests::compare("List l8", l8, expected);

    List<int> l9;
    tests::compare("max_size()", l9.max_size(), UINTMAX_MAX);

    return tests::failed;
}
