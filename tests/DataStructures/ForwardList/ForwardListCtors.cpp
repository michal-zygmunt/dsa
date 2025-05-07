/**
 * @file ForwardListCtors.cpp
 * @brief This file tests ForwardList constructors
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
    std::cout << "Start ForwardListCtors test:\n";

    bool res{};
    std::initializer_list<int> expected{ 0, 10, 20 };

    std::cout << "Default ctor\n";
    ForwardList<int> l1;
    l1.push_front(20);
    l1.push_front(10);
    l1.push_front(0);
    res = if_error(l1, expected);
    std::cout << "ForwardList l1:\t" << l1 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Value ctor\n";
    ForwardList<int> l2(0);
    l2.insert_after(l2.size() - 1, 10);
    l2.insert_after(l2.size() - 1, 20);
    res = if_error(l2, expected);
    std::cout << "ForwardList l2:\t" << l2 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Initializer list ctor\n";
    ForwardList<int> l3(expected);
    res = if_error(l3, expected);
    std::cout << "ForwardList l3:\t" << l3 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Copy ctor\n";
    ForwardList<int> l4{ l1 };
    res = if_error(l4, expected);
    std::cout << "ForwardList l4:\t" << l4 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Copy assignment ctor\n";
    ForwardList<int> l5;
    l5.push_front(5);
    l5.push_front(4);
    l5.push_front(3);
    l5.push_front(2);
    l5.push_front(1);
    l5 = l1;
    res = if_error(l5, expected);
    std::cout << "ForwardList l5:\t" << l5 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Move ctor\n";
    ForwardList<int> l6 = std::move(ForwardList<int>(l1));
    res = if_error(l6, expected);
    std::cout << "ForwardList l6:\t" << l6 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Move assignment ctor\n";
    ForwardList<int> l7(0);
    l7 = std::move(ForwardList<int>(l1));
    res = if_error(l7, expected);
    std::cout << "ForwardList l7:\t" << l7 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
