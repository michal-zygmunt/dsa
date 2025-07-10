/**
 * @file ForwardListGrow.cpp
 * @brief This file tests functions swapping ForwardList objects
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
    std::cout << "Start ForwardListSwap test:\n";

    std::initializer_list<int> expected{};
    std::initializer_list<int> expected_1{ 1, 2, 3, 4, 5 };
    std::initializer_list<int> expected_2{ 10, 20, 30, 40, 50 };

    dsa::ForwardList<int> l1 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l2 = dsa::ForwardList<int>(expected_2);
    l1.swap(l2);
    expected = expected_2;
    tests::compare("ForwardList l1", l1, expected);
    expected = expected_1;
    tests::compare("ForwardList l2", l2, expected);

    dsa::ForwardList<int> l3 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l4;
    l3.swap(l4);
    expected = { };
    tests::compare("ForwardList l3", l3, expected);
    expected = expected_1;
    tests::compare("ForwardList l4", l4, expected);

    return tests::failed;
}
