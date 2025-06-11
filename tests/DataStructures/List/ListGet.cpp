/**
 * @file ListGet.cpp
 * @brief This file tests accessing values of List Nodes
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
    std::cout << "Start ListGet test:\n";

    bool res{};
    std::initializer_list<int> expected{};

    List<int> l1 = List<int>({ 0, 10, 20 });
    // Try reading some nodes with invalid indexes
    expected = { 0, 10, 20 };
    auto indexes = { -1, 0, 1, 2, 100 };
    for (int i = 0; i < indexes.size(); i++)
    {
        auto temp = l1.get(i);
        if (temp)
        {
            res = if_error(temp->value(), expected.begin()[i]);
        }
    }
    std::cout << "List l1:\t" << l1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l2 = List<int>({ 20, 10, 0 });
    expected = { 20, 10, 0 };
    for (int i = 0; i < indexes.size(); i++)
    {
        auto temp = l2.get(i);
        if (temp)
        {
            res = if_error(temp->value(), expected.begin()[i]);
        }
    }
    std::cout << "List l2:\t" << l2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}