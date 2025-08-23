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
    std::cout << "Start ForwardListCtors test:\n";

    std::initializer_list<int> expected{ 0, 10, 20 };

    std::cout << "Default ctor\n";
    dsa::ForwardList<int> l1;
    l1.push_front(20);
    l1.push_front(10);
    l1.push_front(0);
    tests::compare("ForwardList l1", l1, expected);

    std::cout << "Value ctor\n";
    dsa::ForwardList<int> l2(20);
    l2.push_front(0);
    l2.insert_after(l2.cbegin(), 10);
    tests::compare("ForwardList l2", l2, expected);

    std::cout << "Initializer list ctor\n";
    dsa::ForwardList<int> l3(expected);
    tests::compare("ForwardList l3", l3, expected);

    std::cout << "Copy ctor\n";
    dsa::ForwardList<int> l4{ l1 };
    tests::compare("ForwardList l4", l4, expected);

    std::cout << "Copy assignment ctor\n";
    dsa::ForwardList<int> l5;
    l5.push_front(5);
    l5.push_front(4);
    l5.push_front(3);
    l5.push_front(2);
    l5.push_front(1);
    l5 = l1;
    tests::compare("ForwardList l5", l5, expected);

    std::cout << "Move ctor\n";
    dsa::ForwardList<int> temp_1(l1);
    dsa::ForwardList<int> l6 = std::move(temp_1);
    tests::compare("ForwardList l6", l6, expected);

    std::cout << "Move assignment ctor\n";
    dsa::ForwardList<int> temp_2(l1);
    dsa::ForwardList<int> l7(0);
    l7 = std::move(temp_2);
    tests::compare("ForwardList l7", l7, expected);

    return tests::failed;
}
