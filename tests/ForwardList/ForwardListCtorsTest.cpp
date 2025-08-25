/**
 * @file ForwardListCtors.cpp
 * @brief This file tests ForwardList constructors
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
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start ForwardListCtors test:\n";

    std::initializer_list<int> expected{ 0, 10, 20 };

    std::cout << "Default ctor\n";
    dsa::ForwardList<int> list1;
    list1.push_front(20);
    list1.push_front(10);
    list1.push_front(0);
    tests::compare("ForwardList1", list1, expected);

    std::cout << "Value ctor\n";
    dsa::ForwardList<int> list2(20);
    list2.push_front(0);
    list2.insert_after(list2.cbegin(), 10);
    tests::compare("ForwardList2", list2, expected);

    std::cout << "Initializer list ctor\n";
    dsa::ForwardList<int> list3(expected);
    tests::compare("ForwardList3", list3, expected);

    std::cout << "Copy ctor\n";
    dsa::ForwardList<int> list4{ list1 };
    tests::compare("ForwardList4", list4, expected);

    std::cout << "Copy assignment ctor\n";
    dsa::ForwardList<int> list5;
    list5.push_front(5);
    list5.push_front(4);
    list5.push_front(3);
    list5.push_front(2);
    list5.push_front(1);
    list5 = list1;
    tests::compare("ForwardList5", list5, expected);

    std::cout << "Move ctor\n";
    dsa::ForwardList<int> temp_1(list1);
    dsa::ForwardList<int> list6 = std::move(temp_1);
    tests::compare("ForwardList6", list6, expected);

    std::cout << "Move assignment ctor\n";
    dsa::ForwardList<int> temp_2(list1);
    dsa::ForwardList<int> list7(0);
    list7 = std::move(temp_2);
    tests::compare("ForwardList7", list7, expected);

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
