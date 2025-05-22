/**
 * @file ForwardListCtors.cpp
 * @brief This file tests ForwardList iterators
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "ForwardList.h"

#include <cstdint>
#include <type_traits>
#include <typeinfo>
#include <xutility>

int main()
{
    std::cout << "Start ForwardListItors test:\n";

    bool res{};
    std::initializer_list<int> expected{};

    std::cout << "Explicit Iterator\n";
    ForwardList<int> l1{ 0, 10, 20 };
    for (ForwardList<int>::Iterator it = l1.begin(); it != l1.end(); it++)
    {
        auto& val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    expected = { 100, 110, 120 };
    res = if_error(l1, expected);
    std::cout << "ForwardList l1:\t" << l1 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Auto Iterator\n";
    ForwardList<int> l2{ 0, 25, 50 };
    for (auto it = l2.begin(); it != l2.end(); it++)
    {
        auto& val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    expected = { 100, 125, 150 };
    res = if_error(l2, expected);
    std::cout << "ForwardList l2:\t" << l2 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Explicit Const Iterator\n";
    ForwardList<int> l3{ 0, 10, 20 };
    for (ForwardList<int>::Const_Iterator it = l3.cbegin(); it != l3.cend(); it++)
    {
        //auto& val = *it; // reference generate compilation error
        auto val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    expected = { 0, 10, 20 };
    res = if_error(l3, expected);
    std::cout << "ForwardList l3:\t" << l3 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Auto Const Iterator\n";
    ForwardList<int> l4{ 0, 25, 50 };
    for (auto it = l4.cbegin(); it != l4.cend(); it++)
    {
        //auto& val = *it; // reference generate compilation error
        auto val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    expected = { 0, 25, 50 };
    res = if_error(l4, expected);
    std::cout << "ForwardList l4:\t" << l4 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    // Check iterator of one element
    ForwardList<int> l5 = ForwardList<int>(0);
    auto it = l5.insert_after(l5.cbegin(), 10);
    int val = it->operator*();
    int expected_val = 10;
    res = if_error(val, expected_val);
    std::cout << "ForwardList l5:\t" << val << '\n';
    std::cout << "Expected:\t" << expected_val << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    // Check iterator after inserting 0 elements
    ForwardList<int> l6 = ForwardList<int>(50);
    l6.push_front(40);
    l6.push_front(30);
    it = l6.insert_after(l6.cbegin(), 0, 5);
    val = it->operator*();
    expected_val = 30;
    res = if_error(val, expected_val);
    std::cout << "ForwardList l6:\t" << val << '\n';
    std::cout << "Expected:\t" << expected_val << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    // Range based loop
    expected = { 10, 20, 30, 40, 50 };
    std::initializer_list<int>::iterator il_it;
    ForwardList<int> l7 = ForwardList<int>{ 10, 20, 30, 40, 50 };
    std::cout << "ForwardList l7 vs std::initializer_list:\n";
    il_it = expected.begin();
    for (auto i : l7)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = if_error(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';
    il_it = expected.begin();
    for (auto& i : l7)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = if_error(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';
    il_it = expected.begin();
    for (const auto i : l7)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = if_error(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';
    il_it = expected.begin();
    for (const auto& i : l7)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = if_error(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';

    // Compare elements based on range loops
    expected = { 10, 20, 30, 40, 50 };
    const ForwardList<int> l8 = ForwardList<int>{ 10, 20, 30, 40, 50 };
    std::cout << "ForwardList l8 vs std::initializer_list:\n";
    il_it = expected.begin();
    for (auto i : l8)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = if_error(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';
    il_it = expected.begin();
    for (auto& i : l8)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = if_error(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';
    il_it = expected.begin();
    for (const auto i : l8)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = if_error(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';
    il_it = expected.begin();
    for (const auto& i : l8)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = if_error(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';

    // std library operation on custom iterators
    ForwardList<int> l9 = ForwardList<int>{ 10, 20, 30, 40, 50 };
    std::fill(l9.begin(), l9.end(), 10);
    expected = { 10, 10, 10, 10, 10 };
    res = if_error(l9, expected);
    std::cout << "ForwardList l9:\t" << l9 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    // check const_iterator for const object
    ForwardList<int> l10 = ForwardList<int>{ 10, 20, 30 };
    auto iter10b = l10.begin();
    *iter10b = 1;
    auto citer10b = l10.cbegin();
    //*citer10b = 1; // compilation error
    auto iter10e = l10.end();
    //*iter10e = 1; // runtime error, assignment to memory outside list
    auto citer10e = l10.cend();
    //*citer10e = 1; // compilation error

    const ForwardList<int> l11 = ForwardList<int>{ 10, 20, 30 };
    auto iter11b = l11.begin();
    //*iter11b = 1; // compilation error
    auto citer11b = l11.cbegin();
    //*citer11b = 1; // compilation error
    auto iter11e = l11.end();
    //*iter11e = 1; // compilation error
    auto citer11e = l11.cend();
    //*citer11e = 1; // compilation error

    // Iterate over Const_Iterator
    ForwardList<int> l12 = ForwardList<int>{ 10, 20, 30 };
    auto cit = l12.cbegin();
    std::cout << *cit << ' ';
    res = if_error(*cit, 10);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    cit++;
    std::cout << *cit << ' ';
    res = if_error(*cit, 20);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    cit++;
    std::cout << *cit << ' ';
    res = if_error(*cit, 30);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    cit++;

    return tests::failed;
}
