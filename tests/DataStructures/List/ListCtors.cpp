/**
 * @file ListCtors.cpp
 * @brief This file tests List constructors
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
    std::cout << "Start ListCtors test:\n";

    bool res{};
    std::initializer_list<int> expected{ 0, 10, 20 };

    std::cout << "Default ctor\n";
    List<int> l1;
    l1.push_back(0);
    l1.push_back(10);
    l1.push_back(20);
    res = if_error(l1, expected);
    std::cout << "List l1:\t" << l1 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Value ctor\n";
    List<int> l2(0);
    l2.push_back(10);
    l2.push_back(20);
    res = if_error(l2, expected);
    std::cout << "List l2:\t" << l2 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Initializer list ctor\n";
    List<int> l3(expected);
    res = if_error(l3, expected);
    std::cout << "List l3:\t" << l3 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Copy ctor\n";
    List<int> l4{ l1 };
    res = if_error(l4, expected);
    std::cout << "List l4:\t" << l4 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Copy assignment ctor\n";
    List<int> l5;
    l5.push_back(1);
    l5.push_back(2);
    l5.push_back(3);
    l5.push_back(4);
    l5.push_back(5);
    l5 = l1;
    res = if_error(l5, expected);
    std::cout << "List l5:\t" << l5 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Move ctor\n";
    List<int> l6 = std::move(List<int>(l1));
    res = if_error(l6, expected);
    std::cout << "List l6:\t" << l6 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Move assignment ctor\n";
    List<int> l7(0);
    l7 = std::move(List<int>(l1));
    res = if_error(l7, expected);
    std::cout << "List l7:\t" << l7 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}