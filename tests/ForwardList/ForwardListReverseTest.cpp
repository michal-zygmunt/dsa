/**
 * @file ForwardListReverse.cpp
 * @brief This file tests reversing order of ForwardList Nodes
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
    std::cout << "Start ForwardListReverse test:\n";

    dsa::ForwardList<int> l1 = dsa::ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
    l1.reverse();
    std::initializer_list<int> expected_1{ 50, 40, 30, 20, 10, 0 };
    tests::compare("ForwardList l1", l1, expected_1);

    return tests::failed;
}
