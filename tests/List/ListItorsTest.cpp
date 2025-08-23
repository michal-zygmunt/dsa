/**
 * @file ListCtors.cpp
 * @brief This file tests List iterators
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/List.h"

#include <algorithm>
#include <initializer_list>
#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start ListItors test:\n";

    bool res{};

    std::cout << "Explicit iterator\n";
    dsa::List<int> l1{ 0, 10, 20 };
    for (dsa::List<int>::iterator it = l1.begin(); it != l1.end(); it++)
    {
        auto& val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    std::initializer_list<int> expected_1 = { 100, 110, 120 };
    tests::compare("List l1", l1, expected_1);

    std::cout << "Auto iterator\n";
    dsa::List<int> l2{ 0, 25, 50 };
    for (auto it = l2.begin(); it != l2.end(); it++)
    {
        auto& val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    std::initializer_list<int> expected_2 = { 100, 125, 150 };
    tests::compare("List l2", l2, expected_2);

    std::cout << "Explicit Const iterator\n";
    dsa::List<int> l3{ 0, 10, 20 };
    for (dsa::List<int>::const_iterator it = l3.cbegin(); it != l3.cend(); it++)
    {
        //auto& val = *it; // reference generate compilation error
        auto val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    std::initializer_list<int> expected_3 = { 0, 10, 20 };
    tests::compare("List l3", l3, expected_3);

    std::cout << "Auto Const iterator\n";
    dsa::List<int> l4{ 0, 25, 50 };
    for (auto it = l4.cbegin(); it != l4.cend(); it++)
    {
        //auto& val = *it; // reference generate compilation error
        auto val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    std::initializer_list<int> expected_4 = { 0, 25, 50 };
    tests::compare("List l4", l4, expected_4);

    // Check iterator of one element
    dsa::List<int> l5 = dsa::List<int>(0);
    auto it = l5.insert(l5.cbegin(), 10);
    int val = *it;
    int expected_val = 10;
    tests::compare("List l5 it", val, expected_val);
    std::initializer_list<int> expected_5 = { 10, 0 };
    tests::compare("List l5", l5, expected_5);

    // Check iterator after inserting 0 elements
    dsa::List<int> l6 = dsa::List<int>(50);
    l6.push_front(40);
    l6.push_front(30);
    it = l6.insert(l6.cbegin(), 0, 5);
    val = *it;
    expected_val = 30;
    tests::compare("List l6 it", val, expected_val);
    std::initializer_list<int> expected_6 = { 30, 40, 50 };
    tests::compare("List l6", l6, expected_6);

    // Range based loop
    std::initializer_list<int> expected_7 = { 10, 20, 30, 40, 50 };
    std::initializer_list<int>::iterator il_it;
    dsa::List<int> l7 = dsa::List<int>{ 10, 20, 30, 40, 50 };
    std::cout << "List l7 vs std::initializer_list:\n";
    il_it = expected_7.begin();
    for (auto i : l7)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = tests::compare(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';
    il_it = expected_7.begin();
    for (auto& i : l7)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = tests::compare(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';
    il_it = expected_7.begin();
    for (const auto i : l7)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = tests::compare(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';
    il_it = expected_7.begin();
    for (const auto& i : l7)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = tests::compare(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';

    // Compare elements based on range loops
    std::initializer_list<int> expected_8 = { 10, 20, 30, 40, 50 };
    const dsa::List<int> l8 = dsa::List<int>{ 10, 20, 30, 40, 50 };
    std::cout << "List l8 vs std::initializer_list:\n";
    il_it = expected_8.begin();
    for (auto i : l8)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = tests::compare(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';
    il_it = expected_8.begin();
    for (auto& i : l8)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = tests::compare(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';
    il_it = expected_8.begin();
    for (const auto i : l8)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = tests::compare(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';
    il_it = expected_8.begin();
    for (const auto& i : l8)
    {
        std::cout << i << ' ' << *il_it << ' ';
        res = tests::compare(i, *(il_it++));
        std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';

    // std library operation on custom iterators
    dsa::List<int> l9 = dsa::List<int>{ 10, 20, 30, 40, 50 };
    std::fill(l9.begin(), l9.end(), 10);
    std::initializer_list<int> expected_9 = { 10, 10, 10, 10, 10 };
    tests::compare("List l9", l9, expected_9);

    // check const_iterator for const object
    dsa::List<int> l10 = dsa::List<int>{ 10, 20, 30 };
    auto iter10b = l10.begin();
    *iter10b = 1;
    auto citer10b = l10.cbegin();
    //*citer10b = 1; // compilation error
    auto iter10e = l10.end();
    //*iter10e = 1; // runtime error, assignment to memory outside list
    auto citer10e = l10.cend();
    //*citer10e = 1; // compilation error

    const dsa::List<int> l11 = dsa::List<int>{ 10, 20, 30 };
    auto iter11b = l11.begin();
    //*iter11b = 1; // compilation error
    auto citer11b = l11.cbegin();
    //*citer11b = 1; // compilation error
    auto iter11e = l11.end();
    //*iter11e = 1; // compilation error
    auto citer11e = l11.cend();
    //*citer11e = 1; // compilation error

    // Increment iterator
    dsa::List<int> l12 = dsa::List<int>{ 10, 20, 30 };
    std::cout << "List l12:\t" << l12 << '\n';
    auto it_12 = l12.begin();
    std::cout << *it_12 << ' ';
    res = tests::compare(*it_12, 10);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    it_12++;
    std::cout << *it_12 << ' ';
    res = tests::compare(*it_12, 20);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    it_12++;
    std::cout << *it_12 << ' ';
    res = tests::compare(*it_12, 30);
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    it_12++;

    // Increment const_iterator
    dsa::List<int> l13 = dsa::List<int>{ 10, 20, 30 };
    std::cout << "List l13:\t" << l13 << '\n';
    auto cit_13 = l13.cbegin();
    std::cout << *cit_13 << ' ';
    res = tests::compare(*cit_13, 10);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    cit_13++;
    std::cout << *cit_13 << ' ';
    res = tests::compare(*cit_13, 20);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    cit_13++;
    std::cout << *cit_13 << ' ';
    res = tests::compare(*cit_13, 30);
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    cit_13++;

    // Decrement iterator
    dsa::List<int> l14 = dsa::List<int>{ 10, 20, 30 };
    std::cout << "List l14:\t" << l14 << '\n';
    auto it_14 = l14.end();
    it_14--;
    std::cout << *it_14 << ' ';
    res = tests::compare(*it_14, 30);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    --it_14;
    std::cout << *it_14 << ' ';
    res = tests::compare(*it_14, 20);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    --it_14;
    std::cout << *it_14 << ' ';
    res = tests::compare(*it_14, 10);
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    --it_14;

    // Decrement const_iterator
    dsa::List<int> l15 = dsa::List<int>{ 10, 20, 30 };
    std::cout << "List l15:\t" << l15 << '\n';
    auto cit_15 = l15.cend();
    cit_15--;
    std::cout << *cit_15 << ' ';
    res = tests::compare(*cit_15, 30);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    --cit_15;
    std::cout << *cit_15 << ' ';
    res = tests::compare(*cit_15, 20);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    --cit_15;
    std::cout << *cit_15 << ' ';
    res = tests::compare(*cit_15, 10);
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    --cit_15;

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
