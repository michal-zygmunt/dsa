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

    dsa::List<int> l1 = dsa::List<int>({ 1, 2, 3, 4, 5 });
    l1.unique();
    std::initializer_list<int> expected_1 = { 1, 2, 3, 4, 5 };
    tests::compare("List l1", l1, expected_1);

    dsa::List<int> l2 = dsa::List<int>({ 1, 4, 2, 3, 2, 4, 3, 5, 1 });
    l2.unique();
    std::initializer_list<int> expected_2 = { 1, 4, 2, 3, 5 };
    tests::compare("List l2", l2, expected_2);

    dsa::List<int> l3 = dsa::List<int>({ 1, 1, 2, 4, 2, 1, 3, 1, 1 });
    l3.unique();
    std::initializer_list<int> expected_3 = { 1, 2, 4, 3 };
    tests::compare("List l3", l3, expected_3);

    dsa::List<int> l4 = dsa::List<int>({ 1, 1, 1, 2, 2, 2, 1, 1, 1 });
    l4.unique();
    std::initializer_list<int> expected_4 = { 1, 2 };
    tests::compare("List l4", l4, expected_4);

    dsa::List<int> l5 = dsa::List<int>({ 0, 0, 0, 0, 0, 0 });
    l5.unique();
    std::initializer_list<int> expected_5 = { 0 };
    tests::compare("List l5", l5, expected_5);

    dsa::List<int> l6 = dsa::List<int>();
    l6.unique();
    std::initializer_list<int> expected_6 = { };
    tests::compare("List l6", l6, expected_6);

    dsa::List<int> l7;
    l7.unique();
    std::initializer_list<int> expected_7 = {};
    tests::compare("List l7", l7, expected_7);

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
