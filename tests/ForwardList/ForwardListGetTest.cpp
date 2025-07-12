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
#include "dsa/ForwardList.h"

int main()
{
    std::cout << "Start ForwardListGet test:\n";

    std::initializer_list<int> expected{};

    dsa::ForwardList<int> l1 = dsa::ForwardList<int>({ 0, 10, 20 });
    // Try reading some nodes with invalid indexes
    expected = { 0, 10, 20 };
    auto indexes = { -1, 0, 1, 2, 100 };
    for (int i = 0; i < indexes.size(); i++)
    {
        auto temp = l1.get(i);
        if (temp)
        {
            tests::compare(temp->value(), expected.begin()[i]);
        }
    }
    tests::compare("ForwardList l1", l1, expected);

    dsa::ForwardList<int> l2 = dsa::ForwardList<int>({ 20, 10, 0 });
    expected = { 20, 10, 0 };
    for (int i = 0; i < indexes.size(); i++)
    {
        auto temp = l2.get(i);
        if (temp)
        {
            tests::compare(temp->value(), expected.begin()[i]);
        }
    }
    tests::compare("ForwardList l2", l2, expected);

    return tests::failed;
}
