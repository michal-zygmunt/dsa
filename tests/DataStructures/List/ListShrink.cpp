/**
 * @file ListShrink.cpp
 * @brief This file tests functions decreasing List length
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
    std::cout << "Start ListShrink test:\n";

    bool res{};
    std::initializer_list<int> expected{};

    List<int> l1 = List<int>({ 0, 10, 20, 30, 40, 50 });
    l1.erase(l1.begin()[l1.size() - 1]);
    l1.pop_front();
    auto indexes = { 100, 5, 2, 0, -1 };
    for (const auto& i : indexes)
    {
        l1.erase(l1.begin()[i]);
    }
    expected = { 20, 40 };
    res = if_error(l1, expected);
    std::cout << "List l1:\t" << l1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l2 = List<int>({ 0, 10, 20, 30, 40, 50 });
    l2.erase(l2.begin()[1], l2.begin()[3]);
    expected = { 0, 30, 40, 50 };
    res = if_error(l2, expected);
    std::cout << "List l2:\t" << l2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l3 = List<int>({ 0, 10, 20, 30, 40, 50 });
    l3.erase(l3.begin()[1]);
    l3.erase(l3.begin()[1], l3.begin()[3]);
    expected = { 0, 40, 50 };
    res = if_error(l3, expected);
    std::cout << "List l3:\t" << l3 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}