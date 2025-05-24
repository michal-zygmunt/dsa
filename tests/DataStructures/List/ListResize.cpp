/**
 * @file ListGrow.cpp
 * @brief This file tests functions resizing List objects
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
    std::cout << "Start ListResize test:\n";

    bool res{};
    std::initializer_list<int> expected{};

    List<int> l1 = List<int>({ 1, 2, 3, 4, 5 });
    l1.resize(3);
    expected = { 1, 2, 3 };
    res = if_error(l1, expected);
    std::cout << "List l1:\t" << l1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l2 = List<int>({ 1, 2, 3, 4, 5 });
    l2.resize(5);
    expected = { 1, 2, 3, 4, 5 };
    res = if_error(l2, expected);
    std::cout << "List l2:\t" << l2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l3 = List<int>({ 1, 2, 3, 4, 5 });
    l3.resize(8);
    expected = { 1, 2, 3, 4, 5, 0, 0, 0 };
    res = if_error(l3, expected);
    std::cout << "List l3:\t" << l3 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l4;
    l4.resize(5);
    expected = { 0, 0, 0, 0, 0 };
    res = if_error(l4, expected);
    std::cout << "List l4:\t" << l4 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l5 = List<int>({ 1, 2, 3, 4, 5 });
    l5.resize(3, 10);
    expected = { 1, 2, 3 };
    res = if_error(l5, expected);
    std::cout << "List l5:\t" << l5 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l6 = List<int>({ 1, 2, 3, 4, 5 });
    l6.resize(5, 10);
    expected = { 1, 2, 3, 4, 5 };
    res = if_error(l6, expected);
    std::cout << "List l6:\t" << l6 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l7 = List<int>({ 1, 2, 3, 4, 5 });
    l7.resize(8, 10);
    expected = { 1, 2, 3, 4, 5, 10, 10, 10 };
    res = if_error(l7, expected);
    std::cout << "List l7:\t" << l7 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l8;
    l8.resize(5, 10);
    expected = { 10, 10, 10, 10, 10 };
    res = if_error(l8, expected);
    std::cout << "List l8:\t" << l8 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l9;
    res = if_error(l9.max_size(), UINTMAX_MAX);
    std::cout << "max_size():\t" << l9.max_size() << '\n';
    std::cout << "Expected:\t" << UINTMAX_MAX << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
