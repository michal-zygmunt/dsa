/**
 * @file ForwardListGrow.cpp
 * @brief This file tests functions increasing ForwardList length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "ForwardList.h"

int main()
{
    std::cout << "Start ForwardListGrow test:\n";

    std::initializer_list<int> expected{ -10, 0, 0, 2, 10, 20, 4, 30, 40 };

    ForwardList<int> l1 = ForwardList<int>(10);
    auto it = l1.insert_after(l1.cbegin(), 20);
    l1.insert_after(it, { 30, 40 });
    l1.push_front(0);
    l1.push_front(-10);
    // Try inserting nodes at invalid indexes
    auto indexes = { -1, 0, 4, 2, 100 };
    for (int i = 0; i < indexes.size(); i++)
    {
        int idx_val = indexes.begin()[i];
        l1.insert_after(l1.cbegin()[idx_val], idx_val);
    }
    tests::compare("ForwardList l1", l1, expected);

    ForwardList<int> l2 = ForwardList<int>(50);
    l2.push_front(40);
    l2.push_front(30);
    l2.push_front(20);
    l2.push_front(10);
    l2.insert_after(l2.cbegin(), 5, 5);
    expected = { 10, 5, 5, 5, 5, 5, 20, 30, 40, 50 };
    tests::compare("ForwardList l2", l2, expected);

    ForwardList<int> l3 = ForwardList<int>(50);
    l3.push_front(40);
    l3.push_front(30);
    l3.push_front(10);
    it = l3.insert_after(l3.cbegin(), 20);
    l3.insert_after(it, { 1, 2, 3 });
    l3.insert_after(l3.cbegin()[l3.size() - 1], 60);
    expected = { 10, 20, 1, 2, 3, 30, 40, 50, 60 };
    tests::compare("ForwardList l3", l3, expected);

    ForwardList<int> l4;
    l4.push_front(40);
    l4.push_front(30);
    l4.push_front(10);
    it = l4.insert_after(l4.cbegin(), 20);
    expected = { 10, 20, 30, 40 };
    tests::compare("ForwardList l4", l4, expected);

    ForwardList<int> l5;
    l5.insert_after(l5.before_begin(), 40);
    l5.insert_after(l5.before_begin(), 30);
    l5.insert_after(l5.cbefore_begin(), 20);
    l5.insert_after(l5.cbefore_begin(), 10);
    expected = { 10, 20, 30, 40 };
    tests::compare("ForwardList l5", l5, expected);

    ForwardList<int> l6{ 40 };
    l6.insert_after(l6.before_begin(), 30);
    l6.insert_after(l6.before_begin(), 20);
    l6.insert_after(l6.before_begin(), 10);
    expected = { 10, 20, 30, 40 };
    tests::compare("ForwardList l6", l6, expected);

    return tests::failed;
}
