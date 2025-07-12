/**
 * @file ListGrow.cpp
 * @brief This file tests functions increasing List length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/List.h"

int main()
{
    std::cout << "Start ListGrow test:\n";

    std::initializer_list<int> expected{ -10, 0, 0, 2, 10, 20, 4, 30, 40 };

    dsa::List<int> l1 = dsa::List<int>(40);
    auto it = l1.insert(l1.cbegin(), 30);
    l1.insert(it, { 10, 20 });
    l1.push_front(0);
    l1.push_front(-10);
    // Try inserting nodes at invalid indexes
    auto indexes = { -1, 0, 4, 2, 100 };
    for (int i = 0; i < indexes.size(); i++)
    {
        int idx_val = indexes.begin()[i];
        l1.insert(l1.cbegin()[idx_val], idx_val);
    }
    expected = { 0, -10, 2, 0, 10, 4, 20, 30, 40 };
    tests::compare("List l1", l1, expected);

    dsa::List<int> l2 = dsa::List<int>(50);
    l2.push_front(40);
    l2.push_front(30);
    l2.push_front(20);
    l2.push_front(10);
    l2.insert(l2.cbegin(), 5, 5);
    expected = { 5, 5, 5, 5, 5, 10, 20, 30, 40, 50 };
    tests::compare("List l2", l2, expected);

    dsa::List<int> l3 = dsa::List<int>(50);
    l3.push_front(40);
    l3.push_front(30);
    l3.push_front(20);
    it = l3.insert(l3.cbegin(), 10);
    l3.insert(it, { 1, 2, 3 });
    l3.insert(l3.cbegin()[l3.size() - 1], 60);
    expected = { 1, 2, 3, 10, 20, 30, 40, 60, 50 };
    tests::compare("List l3", l3, expected);

    dsa::List<int> l4;
    l4.push_back(20);
    l4.push_back(30);
    l4.push_back(40);
    it = l4.insert(l4.cbegin(), 10);
    expected = { 10, 20, 30, 40 };
    tests::compare("List l4", l4, expected);

    dsa::List<int> l5{ 10, 20, 30 };
    l5.insert(l5.end(), 40);
    expected = { 10, 20, 30, 40 };
    tests::compare("List l5", l5, expected);

    dsa::List<int> l6{ 10, 20, 30 };
    l6.insert(l6.end(), { 40, 50, 60 });
    expected = { 10, 20, 30, 40, 50, 60 };
    tests::compare("List l6", l6, expected);

    return tests::failed;
}