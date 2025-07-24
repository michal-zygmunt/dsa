/**
 * @file ListGet.cpp
 * @brief This file tests accessing values of List Nodes
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/List.h"

int main()
{
    std::cout << "Start ListGet test:\n";

    dsa::List<int> l1 = dsa::List<int>({ 0, 10, 20 });
    // Try reading some nodes with invalid indexes
    std::initializer_list<int> expected_1 = { 0, 10, 20 };
    auto indexes = { -1, 0, 1, 2, 100 };
    for (size_t i = 0; i < indexes.size(); i++)
    {
        auto temp = l1.get(i);
        if (temp)
        {
            tests::compare(temp->value(), expected_1.begin()[i]);
        }
    }
    tests::compare("List l1", l1, expected_1);

    dsa::List<int> l2 = dsa::List<int>({ 20, 10, 0 });
    std::initializer_list<int> expected_2 = { 20, 10, 0 };
    for (size_t i = 0; i < indexes.size(); i++)
    {
        auto temp = l2.get(i);
        if (temp)
        {
            tests::compare(temp->value(), expected_2.begin()[i]);
        }
    }
    tests::compare("List l2", l2, expected_2);

    return tests::failed;
}