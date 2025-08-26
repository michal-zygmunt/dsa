/**
 * @file ForwardListOperators.cpp
 * @brief This file tests overloading operators of ForwardList
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/ForwardList.h"

#include <initializer_list>
#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start ForwardListOperators test:\n";

    const dsa::ForwardList<int> list1({ 1,2,3 });
    const dsa::ForwardList<int> list2({ 4,5,6 });
    const dsa::ForwardList<int> list3({ 1, 2, 3, 4 });
    std::cout << "ForwardList1:\t" << list1 << '\n';
    std::cout << "ForwardList2:\t" << list2 << '\n';
    std::cout << "ForwardList3:\t" << list3 << "\n\n";

    const dsa::ForwardList<int> list4(list1 + list2);
    const std::initializer_list<int> expected4 = { 1,2,3,4,5,6 };
    tests::compare("ForwardList4", list4, expected4);

    dsa::ForwardList<int> list5(0);
    list5 += list2;
    const std::initializer_list<int> expected5 = { 0,4,5,6 };
    tests::compare("ForwardList5", list5, expected5);

    dsa::ForwardList<int> list6(0);
    list6 += { 4, 5, 6 };
    const std::initializer_list<int> expected6 = { 0,4,5,6 };
    tests::compare("ForwardList6", list6, expected6);

    std::cout << "Compare operators for objects of the same size\n\n";

    tests::compare("Operator ==", list1 == list1, true);

    tests::compare("Operator !=", list1 != list2, true);

    tests::compare("Operator <", list1 < list2, true);

    tests::compare("Operator >", list2 > list1, true);

    tests::compare("Operator <=", list1 <= list2, true);

    tests::compare("Operator <=", list2 >= list1, true);

    std::cout << "Compare operators for objects of different size\n\n";

    tests::compare("Operator ==", list1 == list3, false);

    tests::compare("Operator !=", list1 != list3, true);

    tests::compare("Operator <", list3 < list2, true);

    tests::compare("Operator >", list3 > list1, false);

    tests::compare("Operator <=", list1 <= list3, true);

    tests::compare("Operator >=", list2 >= list3, true);

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
