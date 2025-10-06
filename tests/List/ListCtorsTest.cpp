/**
 * @file ListCtors.cpp
 * @brief This file tests List constructors
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/List.h"

#include <initializer_list>
#include <iostream>
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start ListCtors test:\n";

    const std::initializer_list<int> expected{ 0, 10, 20 };

    std::cout << "Default ctor\n";
    dsa::List<int> list1;
    list1.push_front(20);
    list1.push_front(10);
    list1.push_front(0);
    tests::compare("List1", list1, expected);

    std::cout << "Value ctor\n";
    dsa::List<int> list2(1, 20);
    list2.push_front(10);
    list2.insert(list2.cbegin(), 0);
    tests::compare("List2", list2, expected);

    std::cout << "Initializer list ctor\n";
    const dsa::List<int> list3(expected);
    tests::compare("List3", list3, expected);

    std::cout << "Copy ctor\n";
    const dsa::List<int> list4{ list1 };
    tests::compare("List4", list4, expected);

    std::cout << "Copy assignment ctor\n";
    dsa::List<int> list5;
    list5.push_front(5);
    list5.push_front(4);
    list5.push_front(3);
    list5.push_front(2);
    list5.push_front(1);
    list5 = list1;
    tests::compare("List5", list5, expected);

    std::cout << "Move ctor\n";
    dsa::List<int> temp_1(list1);
    const dsa::List<int> list6 = std::move(temp_1);
    tests::compare("List6", list6, expected);

    std::cout << "Move assignment ctor\n";
    dsa::List<int> temp_2(list1);
    dsa::List<int> list7(1, 0);
    list7 = std::move(temp_2);
    tests::compare("List7", list7, expected);

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}