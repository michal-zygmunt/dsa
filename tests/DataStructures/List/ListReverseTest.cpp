/**
 * @file ListReverse.cpp
 * @brief This file tests reversing order of List Nodes
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
    std::cout << "Start ListReverse test:\n";

    std::initializer_list<int> expected{ 50, 40, 30, 20, 10, 0 };

    List<int> l1 = List<int>({ 0, 10, 20, 30, 40, 50 });
    l1.reverse();
    tests::compare("List l1", l1, expected);

    return tests::failed;
}