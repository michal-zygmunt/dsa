/**
 * @file ForwardListCtors.cpp
 * @brief This file tests ForwardList iterators
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/ForwardList.h"

#include <algorithm>
#include <initializer_list>
#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    std::cout << "Start ForwardListItors test:\n";

    bool res{};

    std::cout << "Explicit iterator\n";
    dsa::ForwardList<int> l1{ 0, 10, 20 };
    for (dsa::ForwardList<int>::iterator it = l1.begin(); it != l1.end(); it++)
    {
        auto& val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    std::initializer_list<int> expected_1 = { 100, 110, 120 };
    tests::compare("ForwardList l1", l1, expected_1);

    std::cout << "Auto iterator\n";
    dsa::ForwardList<int> l2{ 0, 25, 50 };
    for (auto it = l2.begin(); it != l2.end(); it++)
    {
        auto& val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    std::initializer_list<int> expected_2 = { 100, 125, 150 };
    tests::compare("ForwardList l2", l2, expected_2);

    std::cout << "Explicit Const iterator\n";
    dsa::ForwardList<int> l3{ 0, 10, 20 };
    for (dsa::ForwardList<int>::const_iterator it = l3.cbegin(); it != l3.cend(); it++)
    {
        //auto& val = *it; // reference generate compilation error
        auto val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    std::initializer_list<int> expected_3 = { 0, 10, 20 };
    tests::compare("ForwardList l3", l3, expected_3);

    std::cout << "Auto Const iterator\n";
    dsa::ForwardList<int> l4{ 0, 25, 50 };
    for (auto it = l4.cbegin(); it != l4.cend(); it++)
    {
        //auto& val = *it; // reference generate compilation error
        auto val = *it;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    std::initializer_list<int> expected_4 = { 0, 25, 50 };
    tests::compare("ForwardList l4", l4, expected_4);

    // Check iterator of one element
    dsa::ForwardList<int> l5 = dsa::ForwardList<int>(0);
    auto it = l5.insert_after(l5.cbegin(), 10);
    int val = *it;
    int expected_val = 10;
    //res = if_error(val, expected_val);
    tests::compare("ForwardList l5 it", val, expected_val);
    std::initializer_list<int> expected_5 = { 0, 10 };
    tests::compare("ForwardList l5", l5, expected_5);

    // Check iterator after inserting 0 elements
    dsa::ForwardList<int> l6 = dsa::ForwardList<int>(50);
    l6.push_front(40);
    l6.push_front(30);
    it = l6.insert_after(l6.cbegin(), 0, 5);
    val = *it;
    expected_val = 30;
    //res = if_error(val, expected_val);
    tests::compare("ForwardList l6 it", val, expected_val);
    std::initializer_list<int> expected_6 = { 30, 40, 50 };
    tests::compare("ForwardList l6", l6, expected_6);


    // Range based loop
    std::initializer_list<int> expected_7 = { 10, 20, 30, 40, 50 };
    std::initializer_list<int>::iterator il_it;
    dsa::ForwardList<int> l7 = dsa::ForwardList<int>{ 10, 20, 30, 40, 50 };
    std::cout << "ForwardList l7 vs std::initializer_list:\n";
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
    const dsa::ForwardList<int> l8 = dsa::ForwardList<int>{ 10, 20, 30, 40, 50 };
    std::cout << "ForwardList l8 vs std::initializer_list:\n";
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
    dsa::ForwardList<int> l9 = dsa::ForwardList<int>{ 10, 20, 30, 40, 50 };
    std::fill(l9.begin(), l9.end(), 10);
    std::initializer_list<int> expected_9 = { 10, 10, 10, 10, 10 };
    tests::compare("ForwardList l9", l9, expected_9);

    // check const_iterator for const object
    dsa::ForwardList<int> l10 = dsa::ForwardList<int>{ 10, 20, 30 };
    auto iter10b = l10.begin();
    *iter10b = 1;
    auto citer10b = l10.cbegin();
    //*citer10b = 1; // compilation error
    auto iter10e = l10.end();
    //*iter10e = 1; // runtime error, assignment to memory outside list
    auto citer10e = l10.cend();
    //*citer10e = 1; // compilation error

    const dsa::ForwardList<int> l11 = dsa::ForwardList<int>{ 10, 20, 30 };
    auto iter11b = l11.begin();
    //*iter11b = 1; // compilation error
    auto citer11b = l11.cbegin();
    //*citer11b = 1; // compilation error
    auto iter11e = l11.end();
    //*iter11e = 1; // compilation error
    auto citer11e = l11.cend();
    //*citer11e = 1; // compilation error

    // Iterate over const_iterator
    dsa::ForwardList<int> l12 = dsa::ForwardList<int>{ 10, 20, 30 };
    auto cit = l12.cbegin();
    std::cout << *cit << ' ';
    res = tests::compare(*cit, 10);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    cit++;
    std::cout << *cit << ' ';
    res = tests::compare(*cit, 20);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    cit++;
    std::cout << *cit << ' ';
    res = tests::compare(*cit, 30);
    std::cout << (res == 0 ? "PASS" : "FAIL") << '\n';
    cit++;

    return tests::failed;
}
