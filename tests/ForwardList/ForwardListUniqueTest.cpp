/**
 * @file ForwardListGrow.cpp
 * @brief This file tests functions checking values of ForwardList objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/ForwardList.h"

int main()
{
    std::cout << "Start ForwardListUnique test:\n";

    std::initializer_list<int> expected{};

    dsa::ForwardList<int> l1 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
    l1.unique();
    expected = { 1, 2, 3, 4, 5 };
    tests::compare("ForwardList l1", l1, expected);

    dsa::ForwardList<int> l2 = dsa::ForwardList<int>({ 1, 4, 2, 3, 2, 4, 3, 5, 1 });
    l2.unique();
    expected = { 1, 4, 2, 3, 5 };
    tests::compare("ForwardList l2", l2, expected);

    dsa::ForwardList<int> l3 = dsa::ForwardList<int>({ 1, 1, 2, 4, 2, 1, 3, 1, 1 });
    l3.unique();
    expected = { 1, 2, 4, 3 };
    tests::compare("ForwardList l3", l3, expected);

    dsa::ForwardList<int> l4 = dsa::ForwardList<int>({ 1, 1, 1, 2, 2, 2, 1, 1, 1 });
    l4.unique();
    expected = { 1, 2 };
    tests::compare("ForwardList l4", l4, expected);

    dsa::ForwardList<int> l5 = dsa::ForwardList<int>({ 0, 0, 0, 0, 0, 0 });
    l5.unique();
    expected = { 0 };
    tests::compare("ForwardList l5", l5, expected);

    dsa::ForwardList<int> l6 = dsa::ForwardList<int>();
    l6.unique();
    expected = { };
    tests::compare("ForwardList l6", l6, expected);

    dsa::ForwardList<int> l7;
    l7.unique();
    expected = {};
    tests::compare("ForwardList l7", l7, expected);

    return tests::failed;
}
