/**
 * @file ListGrow.cpp
 * @brief This file tests functions merging List objects
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
    std::cout << "Start ListMerge test:\n";

    std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
    std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };

    dsa::List<int> l1 = dsa::List<int>(il_1);
    dsa::List<int> l2 = dsa::List<int>(il_2);
    l1.merge(l2);
    std::initializer_list<int> expected_1 = { 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
    tests::compare("ForwardList l1", l1, expected_1);
    std::initializer_list<int> expected_2 = {};
    tests::compare("ForwardList l2", l2, expected_2);

    dsa::List<int> l3 = dsa::List<int>(il_1);
    dsa::List<int> l4;
    l4.merge(l3);
    std::initializer_list<int> expected_3 = { };
    tests::compare("ForwardList l3", l3, expected_3);
    std::initializer_list<int> expected_4 = il_1;
    tests::compare("ForwardList l4", l4, expected_4);

    return tests::failed;
}
