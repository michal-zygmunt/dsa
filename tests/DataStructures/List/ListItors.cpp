/**
 * @file ListCtors.cpp
 * @brief This file tests List iterators
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "List.h"

#include <cstdint>
#include <type_traits>
#include <typeinfo>
#include <xutility>

int main()
{
    std::cout << "Start ListItors test:\n";

    bool res{};
    std::initializer_list<int> expected{};

    std::cout << "Explicit iterator\n";
    List<int> l1{ 0, 10, 20 };
    for (List<int>::iterator it = l1.begin(); it != l1.end(); it++)
    {
        auto& val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    expected = { 100, 110, 120 };
    res = if_error(l1, expected);
    std::cout << "List l1:\t" << l1 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Auto iterator\n";
    List<int> l2{ 0, 25, 50 };
    for (auto it = l2.begin(); it != l2.end(); it++)
    {
        auto& val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    expected = { 100, 125, 150 };
    res = if_error(l2, expected);
    std::cout << "List l2:\t" << l2 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Explicit Const iterator\n";
    List<int> l3{ 0, 10, 20 };
    for (List<int>::const_iterator it = l3.cbegin(); it != l3.cend(); it++)
    {
        //auto& val = *it; // reference generate compilation error
        auto val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    expected = { 0, 10, 20 };
    res = if_error(l3, expected);
    std::cout << "List l3:\t" << l3 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Auto Const iterator\n";
    List<int> l4{ 0, 25, 50 };
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
    std::cout << "List l4:\t" << l4 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    // Check iterator of one element
    List<int> l5 = List<int>(0);
    auto it = l5.insert(l5.cbegin(), 10);
    int val = *it;
    int expected_val = 10;
    res = if_error(val, expected_val);
    std::cout << "List l5:\t" << val << '\n';
    std::cout << "Expected:\t" << expected_val << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    // Check iterator after inserting 0 elements
    List<int> l6 = List<int>(50);
    l6.push_front(40);
    l6.push_front(30);
    it = l6.insert(l6.cbegin(), 0, 5);
    val = *it;
    expected_val = 30;
    res = if_error(val, expected_val);
    std::cout << "List l6:\t" << val << '\n';
    std::cout << "Expected:\t" << expected_val << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    // Range based loop
    expected = { 10, 20, 30, 40, 50 };
    std::initializer_list<int>::iterator il_it;
    List<int> l7 = List<int>{ 10, 20, 30, 40, 50 };
    std::cout << "List l7 vs std::initializer_list:\n";
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
    const List<int> l8 = List<int>{ 10, 20, 30, 40, 50 };
    std::cout << "List l8 vs std::initializer_list:\n";
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
    List<int> l9 = List<int>{ 10, 20, 30, 40, 50 };
    std::fill(l9.begin(), l9.end(), 10);
    expected = { 10, 10, 10, 10, 10 };
    res = if_error(l9, expected);
    std::cout << "List l9:\t" << l9 << '\n';
    std::cout << "Expected:  \t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    // check const_iterator for const object
    List<int> l10 = List<int>{ 10, 20, 30 };
    auto iter10b = l10.begin();
    *iter10b = 1;
    auto citer10b = l10.cbegin();
    //*citer10b = 1; // compilation error
    auto iter10e = l10.end();
    //*iter10e = 1; // runtime error, assignment to memory outside list
    auto citer10e = l10.cend();
    //*citer10e = 1; // compilation error

    const List<int> l11 = List<int>{ 10, 20, 30 };
    auto iter11b = l11.begin();
    //*iter11b = 1; // compilation error
    auto citer11b = l11.cbegin();
    //*citer11b = 1; // compilation error
    auto iter11e = l11.end();
    //*iter11e = 1; // compilation error
    auto citer11e = l11.cend();
    //*citer11e = 1; // compilation error

    // Increment iterator
    List<int> l12 = List<int>{ 10, 20, 30 };
    std::cout << "List l12:\t" << l12 << '\n';
    auto it_12 = l12.begin();
    std::cout << *it_12 << ' ';
    res = if_error(*it_12, 10);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    it_12++;
    std::cout << *it_12 << ' ';
    res = if_error(*it_12, 20);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    it_12++;
    std::cout << *it_12 << ' ';
    res = if_error(*it_12, 30);
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    it_12++;

    // Increment const_iterator
    List<int> l13 = List<int>{ 10, 20, 30 };
    std::cout << "List l13:\t" << l13 << '\n';
    auto cit_13 = l13.cbegin();
    std::cout << *cit_13 << ' ';
    res = if_error(*cit_13, 10);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    cit_13++;
    std::cout << *cit_13 << ' ';
    res = if_error(*cit_13, 20);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    cit_13++;
    std::cout << *cit_13 << ' ';
    res = if_error(*cit_13, 30);
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    cit_13++;

    // Decrement iterator
    List<int> l14 = List<int>{ 10, 20, 30 };
    std::cout << "List l14:\t" << l14 << '\n';
    auto it_14 = l14.end();
    it_14--;
    std::cout << *it_14 << ' ';
    res = if_error(*it_14, 30);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    --it_14;
    std::cout << *it_14 << ' ';
    res = if_error(*it_14, 20);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    --it_14;
    std::cout << *it_14 << ' ';
    res = if_error(*it_14, 10);
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    --it_14;

    // Decrement const_iterator
    List<int> l15 = List<int>{ 10, 20, 30 };
    std::cout << "List l15:\t" << l15 << '\n';
    auto cit_15 = l15.cend();
    cit_15--;
    std::cout << *cit_15 << ' ';
    res = if_error(*cit_15, 30);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    --cit_15;
    std::cout << *cit_15 << ' ';
    res = if_error(*cit_15, 20);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    --cit_15;
    std::cout << *cit_15 << ' ';
    res = if_error(*cit_15, 10);
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    --cit_15;

    return tests::failed;
}
