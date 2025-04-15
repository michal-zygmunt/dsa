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
    std::initializer_list<int> expected{ 0, -10, 2, 0, 10, 4, 20, 30, 40 };

    ForwardList<int> l1 = ForwardList<int>(10);
    l1.push_back(20);
    l1.push_back(30);
    l1.push_back(40);

    l1.push_front(0);
    l1.push_front(-10);

    // Try inserting nodes at invalid indexes
    auto indexes = { -1, 0, 4, 2, 100 };
    for (const auto& i : indexes)
    {
        l1.insert(i, i);
    }

    res = if_error(l1, expected);
    std::cout << "ForwardList:\t" << l1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
