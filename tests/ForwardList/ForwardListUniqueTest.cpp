/**
 * @file ForwardListGrow.cpp
 * @brief This file tests functions checking values of ForwardList objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/ForwardList.h"

#include <initializer_list>
#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    std::cout << "Start ForwardListUnique test:\n";

    dsa::ForwardList<int> l1 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
    l1.unique();
    std::initializer_list<int> expected_1 = { 1, 2, 3, 4, 5 };
    tests::compare("ForwardList l1", l1, expected_1);

    dsa::ForwardList<int> l2 = dsa::ForwardList<int>({ 1, 4, 2, 3, 2, 4, 3, 5, 1 });
    l2.unique();
    std::initializer_list<int> expected_2 = { 1, 4, 2, 3, 5 };
    tests::compare("ForwardList l2", l2, expected_2);

    dsa::ForwardList<int> l3 = dsa::ForwardList<int>({ 1, 1, 2, 4, 2, 1, 3, 1, 1 });
    l3.unique();
    std::initializer_list<int> expected_3 = { 1, 2, 4, 3 };
    tests::compare("ForwardList l3", l3, expected_3);

    dsa::ForwardList<int> l4 = dsa::ForwardList<int>({ 1, 1, 1, 2, 2, 2, 1, 1, 1 });
    l4.unique();
    std::initializer_list<int> expected_4 = { 1, 2 };
    tests::compare("ForwardList l4", l4, expected_4);

    dsa::ForwardList<int> l5 = dsa::ForwardList<int>({ 0, 0, 0, 0, 0, 0 });
    l5.unique();
    std::initializer_list<int> expected_5 = { 0 };
    tests::compare("ForwardList l5", l5, expected_5);

    dsa::ForwardList<int> l6 = dsa::ForwardList<int>();
    l6.unique();
    std::initializer_list<int> expected_6 = { };
    tests::compare("ForwardList l6", l6, expected_6);

    dsa::ForwardList<int> l7;
    l7.unique();
    std::initializer_list<int> expected_7 = {};
    tests::compare("ForwardList l7", l7, expected_7);

    return tests::failed;
}
