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
#include "List.h"

int main()
{
    std::cout << "Start ListGrow test:\n";

    bool res{};
    std::initializer_list<int> expected{ -10, 0, 0, 2, 10, 20, 4, 30, 40 };

    List<int> l1 = List<int>(40);
    auto it = l1.insert(l1.cbegin(), 30);
    l1.insert(*it, { 10, 20 });
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
    res = if_error(l1, expected);
    std::cout << "List l1:\t" << l1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l2 = List<int>(50);
    l2.push_front(40);
    l2.push_front(30);
    l2.push_front(20);
    l2.push_front(10);
    l2.insert(l2.cbegin(), 5, 5);
    expected = { 5, 5, 5, 5, 5, 10, 20, 30, 40, 50 };
    res = if_error(l2, expected);
    std::cout << "List l2:\t" << l2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l3 = List<int>(50);
    l3.push_front(40);
    l3.push_front(30);
    l3.push_front(20);
    it = l3.insert(l3.cbegin(), 10);
    l3.insert(*it, { 1, 2, 3 });
    l3.insert(l3.cbegin()[l3.size() - 1], 60);
    expected = { 1, 2, 3, 10, 20, 30, 40, 60, 50 };
    res = if_error(l3, expected);
    std::cout << "List l3:\t" << l3 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l4;
    l4.push_back(20);
    l4.push_back(30);
    l4.push_back(40);
    it = l4.insert(l4.cbegin(), 10);
    expected = { 10, 20, 30, 40 };
    res = if_error(l4, expected);
    std::cout << "List l4:\t" << l4 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l5{ 10, 20, 30 };
    l5.insert(l5.end(), 40);
    expected = { 10, 20, 30, 40 };
    res = if_error(l5, expected);
    std::cout << "List l5:\t" << l5 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l6{ 10, 20, 30 };
    l6.insert(l6.end(), { 40, 50, 60 });
    expected = { 10, 20, 30, 40, 50, 60 };
    res = if_error(l6, expected);
    std::cout << "List l6:\t" << l6 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}