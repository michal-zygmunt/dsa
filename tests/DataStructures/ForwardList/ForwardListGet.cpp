/**
 * @file ForwardListGet.cpp
 * @brief This file tests accessing values of ForwardList Nodes
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
    std::cout << "Start ForwardListGet test:\n";

    bool res{};
    std::initializer_list<int> expected{ 0, 10, 20 };

    ForwardList<int> l1 = ForwardList<int>({ 0, 10, 20 });
    // Try reading some nodes with invalid indexes
    auto indexes = { -1, 0, 1, 2, 100 };
    for (int i = 0; i < indexes.size(); i++)
    {
        auto temp = l1.get(i);
        if (temp)
        {
            res = temp->value() != expected.begin()[i - 1] ? false : true;
        }
    }
    std::cout << "ForwardList:\t" << l1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
