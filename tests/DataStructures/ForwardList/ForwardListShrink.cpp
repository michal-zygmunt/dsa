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

    l1.pop_back();
    l1.pop_front();

    auto indexes = { 100, 5, 2, 0, -1 };
    for (const auto& i : indexes)
    {
        l1.erase(i);
    }

    expected = { 20, 40 };
    res = if_error(l1, expected);
    std::cout << "ForwardList:\t" << l1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}