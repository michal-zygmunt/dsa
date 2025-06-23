/**
 * @file ListGrow.cpp
 * @brief This file tests functions checking values of List objects
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
    std::cout << "Start ListUnique test:\n";

    std::initializer_list<int> expected{};

    List<int> l1 = List<int>({ 1, 2, 3, 4, 5 });
    l1.unique();
    expected = { 1, 2, 3, 4, 5 };
    tests::compare("List l1", l1, expected);

    List<int> l2 = List<int>({ 1, 4, 2, 3, 2, 4, 3, 5, 1 });
    l2.unique();
    expected = { 1, 4, 2, 3, 5 };
    tests::compare("List l2", l2, expected);

    List<int> l3 = List<int>({ 1, 1, 2, 4, 2, 1, 3, 1, 1 });
    l3.unique();
    expected = { 1, 2, 4, 3 };
    tests::compare("List l3", l3, expected);

    List<int> l4 = List<int>({ 1, 1, 1, 2, 2, 2, 1, 1, 1 });
    l4.unique();
    expected = { 1, 2 };
    tests::compare("List l4", l4, expected);

    List<int> l5 = List<int>({ 0, 0, 0, 0, 0, 0 });
    l5.unique();
    expected = { 0 };
    tests::compare("List l5", l5, expected);

    List<int> l6 = List<int>();
    l6.unique();
    expected = { };
    tests::compare("List l6", l6, expected);

    List<int> l7;
    l7.unique();
    expected = {};
    tests::compare("List l7", l7, expected);

    return tests::failed;
}
