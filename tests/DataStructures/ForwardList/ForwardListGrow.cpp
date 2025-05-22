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

    bool res{};
    std::initializer_list<int> expected{ -10, 0, 0, 2, 10, 20, 4, 30, 40 };

    ForwardList<int> l1 = ForwardList<int>(10);
    auto it = l1.insert_after(l1.cbegin(), 20);
    l1.insert_after(*it, { 30, 40 });
    l1.push_front(0);
    l1.push_front(-10);
    // Try inserting nodes at invalid indexes
    auto indexes = { -1, 0, 4, 2, 100 };
    for (int i = 0; i < indexes.size(); i++)
    {
        int idx_val = indexes.begin()[i];
        l1.insert_after(l1.cbegin()[idx_val], idx_val);
    }
    res = if_error(l1, expected);
    std::cout << "ForwardList l1:\t" << l1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l2 = ForwardList<int>(50);
    l2.push_front(40);
    l2.push_front(30);
    l2.push_front(20);
    l2.push_front(10);
    l2.insert_after(l2.cbegin(), 5, 5);
    expected = { 10, 5, 5, 5, 5, 5, 20, 30, 40, 50 };
    res = if_error(l2, expected);
    std::cout << "ForwardList l2:\t" << l2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l3 = ForwardList<int>(50);
    l3.push_front(40);
    l3.push_front(30);
    l3.push_front(10);
    it = l3.insert_after(l3.cbegin(), 20);
    l3.insert_after(*it, { 1, 2, 3 });
    l3.insert_after(l3.cbegin()[l3.size() - 1], 60);
    expected = { 10, 20, 1, 2, 3, 30, 40, 50, 60 };
    res = if_error(l3, expected);
    std::cout << "ForwardList l3:\t" << l3 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
