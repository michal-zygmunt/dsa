/**
 * @file ForwardListShrink.cpp
 * @brief This file tests functions decreasing ForwardList length
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
    std::cout << "Start ForwardListShrink test:\n";

    bool res{};
    std::initializer_list<int> expected{};

    ForwardList<int> l1 = ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
    l1.erase_after(l1.begin()[l1.size() - 2]);
    l1.pop_front();
    auto indexes = { 100, 5, 2, 0, -1 };
    for (const auto& i : indexes)
    {
        l1.erase_after(l1.begin()[i]);
    }
    expected = { 10, 30 };
    res = if_error(l1, expected);
    std::cout << "ForwardList l1:\t" << l1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l2 = ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
    l2.erase_after(l2.begin()[1], l2.begin()[3]);
    expected = { 0, 10, 30, 40, 50 };
    res = if_error(l2, expected);
    std::cout << "ForwardList l2:\t" << l2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l3 = ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
    l3.erase_after(l3.begin()[1]);
    l3.erase_after(l3.begin()[1], l3.begin()[3]);
    expected = { 0, 10, 40, 50 };
    res = if_error(l3, expected);
    std::cout << "ForwardList l3:\t" << l3 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l4 = ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
    l4.erase_after(l4.begin()[1]);
    l4.erase_after(l4.begin()[1], l4.begin()[4]);
    expected = { 0, 10, 50 };
    res = if_error(l4, expected);
    std::cout << "ForwardList l4:\t" << l4 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l5 = ForwardList<int>({ 0, 10, 0, 0, 40, 0 });
    l5.remove(0);
    expected = { 10, 40 };
    res = if_error(l5, expected);
    std::cout << "ForwardList l5:\t" << l5 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l6 = ForwardList<int>({ 0, 0, 0, 0, 0, 0 });
    l6.remove(0);
    expected = { };
    res = if_error(l6, expected);
    std::cout << "ForwardList l6:\t" << l6 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    ForwardList<int> l7 = ForwardList<int>({ 0 });
    res = if_error(l7.empty(), false);
    l7.clear();
    res |= if_error(l7.empty(), true);
    expected = { };
    std::cout << "ForwardList l7:\t" << l7 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}