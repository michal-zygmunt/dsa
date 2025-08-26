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

    std::cout << "Explicit iterator\n";
    dsa::List<int> list1{ 0, 10, 20 };
    for (dsa::List<int>::iterator iterator = list1.begin(); iterator != list1.end(); iterator++)
    {
        auto& val = *iterator;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    const std::initializer_list<int> expected1 = { 100, 110, 120 };
    tests::compare("List1", list1, expected1);

    std::cout << "Auto iterator\n";
    dsa::List<int> list2{ 0, 25, 50 };
    for (auto iterator = list2.begin(); iterator != list2.end(); iterator++)
    {
        auto& val = *iterator;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    const std::initializer_list<int> expected2 = { 100, 125, 150 };
    tests::compare("List2", list2, expected2);

    std::cout << "Explicit Const iterator\n";
    const dsa::List<int> list3{ 0, 10, 20 };
    for (dsa::List<int>::const_iterator iterator = list3.cbegin(); iterator != list3.cend(); iterator++)
    {
        //auto& val = *iterator; // reference generate compilation error
        auto val = *iterator;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    const std::initializer_list<int> expected3 = { 0, 10, 20 };
    tests::compare("List3", list3, expected3);

    std::cout << "Auto Const iterator\n";
    const dsa::List<int> list4{ 0, 25, 50 };
    for (auto iterator = list4.cbegin(); iterator != list4.cend(); iterator++)
    {
        //auto& val = *iterator; // reference generate compilation error
        auto val = *iterator;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    const std::initializer_list<int> expected4 = { 0, 25, 50 };
    tests::compare("List4", list4, expected4);

    // Check iterator of one element
    dsa::List<int> list5 = dsa::List<int>(0);
    auto iterator = list5.insert(list5.cbegin(), 10);
    int val = *iterator;
    int expectedval = 10;
    tests::compare("List5 iterator", val, expectedval);
    const std::initializer_list<int> expected5 = { 10, 0 };
    tests::compare("List5", list5, expected5);

    // Check iterator after inserting 0 elements
    dsa::List<int> list6 = dsa::List<int>(50);
    list6.push_front(40);
    list6.push_front(30);
    iterator = list6.insert(list6.cbegin(), 0, 5);
    val = *iterator;
    expectedval = 30;
    tests::compare("List6 iterator", val, expectedval);
    const std::initializer_list<int> expected6 = { 30, 40, 50 };
    tests::compare("List6", list6, expected6);

    // Range based loop
    const std::initializer_list<int> expected7 = { 10, 20, 30, 40, 50 };
    std::initializer_list<int>::iterator il_iterator{};
    const dsa::List<int> list7 = dsa::List<int>{ 10, 20, 30, 40, 50 };
    std::cout << "List7 vs std::initializer_list:\n";
    il_iterator = expected7.begin();
    for (const auto& item : list7)
    {
        std::cout << item << ' ' << *il_iterator << ' ';
        tests::compare(item, *(il_iterator++));
    }
    std::cout << '\n';
    il_iterator = expected7.begin();
    for (const auto& item : list7)
    {
        std::cout << item << ' ' << *il_iterator << ' ';
        tests::compare(item, *(il_iterator++));
    }
    std::cout << '\n';
    il_iterator = expected7.begin();
    for (const auto& item : list7)
    {
        std::cout << item << ' ' << *il_iterator << ' ';
        tests::compare(item, *(il_iterator++));
    }
    std::cout << '\n';
    il_iterator = expected7.begin();
    for (const auto& item : list7)
    {
        std::cout << item << ' ' << *il_iterator << ' ';
        tests::compare(item, *(il_iterator++));
    }
    std::cout << '\n';

    // Compare elements based on range loops
    const std::initializer_list<int> expected8 = { 10, 20, 30, 40, 50 };
    const dsa::List<int> list8 = dsa::List<int>{ 10, 20, 30, 40, 50 };
    std::cout << "List8 vs std::initializer_list:\n";
    il_iterator = expected8.begin();
    for (const auto& item : list8)
    {
        std::cout << item << ' ' << *il_iterator << ' ';
        tests::compare(item, *(il_iterator++));
    }
    std::cout << '\n';
    il_iterator = expected8.begin();
    for (const auto& item : list8)
    {
        std::cout << item << ' ' << *il_iterator << ' ';
        tests::compare(item, *(il_iterator++));
    }
    std::cout << '\n';
    il_iterator = expected8.begin();
    for (const auto& item : list8)
    {
        std::cout << item << ' ' << *il_iterator << ' ';
        tests::compare(item, *(il_iterator++));
    }
    std::cout << '\n';
    il_iterator = expected8.begin();
    for (const auto& item : list8)
    {
        std::cout << item << ' ' << *il_iterator << ' ';
        tests::compare(item, *(il_iterator++));
    }
    std::cout << '\n';

    // std library operation on custom iterators
    dsa::List<int> list9 = dsa::List<int>{ 10, 20, 30, 40, 50 };
    std::fill(list9.begin(), list9.end(), 10);
    const std::initializer_list<int> expected9 = { 10, 10, 10, 10, 10 };
    tests::compare("List9", list9, expected9);

    // check const_iterator for const object
    dsa::List<int> list10 = dsa::List<int>{ 10, 20, 30 };
    auto iter10b = list10.begin();
    *iter10b = 1;
    auto citer10b = list10.cbegin();
    //*citer10b = 1; // compilation error
    auto iter10e = list10.end();
    //*iter10e = 1; // runtime error, assignment to memory outside list
    auto citer10e = list10.cend();
    //*citer10e = 1; // compilation error

    const dsa::List<int> list11 = dsa::List<int>{ 10, 20, 30 };
    auto iter11b = list11.begin();
    //*iter11b = 1; // compilation error
    auto citer11b = list11.cbegin();
    //*citer11b = 1; // compilation error
    auto iter11e = list11.end();
    //*iter11e = 1; // compilation error
    auto citer11e = list11.cend();
    //*citer11e = 1; // compilation error

    // Increment iterator
    dsa::List<int> list12 = dsa::List<int>{ 10, 20, 30 };
    std::cout << "List12:\t" << list12 << '\n';
    auto it_12 = list12.begin();
    std::cout << *it_12 << ' ';
    tests::compare(*it_12, 10);
    it_12++;
    std::cout << *it_12 << ' ';
    tests::compare(*it_12, 20);
    it_12++;
    std::cout << *it_12 << ' ';
    tests::compare(*it_12, 30);
    it_12++;

    // Increment const_iterator
    const dsa::List<int> list13 = dsa::List<int>{ 10, 20, 30 };
    std::cout << "List13:\t" << list13 << '\n';
    auto cit_13 = list13.cbegin();
    std::cout << *cit_13 << ' ';
    tests::compare(*cit_13, 10);
    cit_13++;
    std::cout << *cit_13 << ' ';
    tests::compare(*cit_13, 20);
    cit_13++;
    std::cout << *cit_13 << ' ';
    tests::compare(*cit_13, 30);
    cit_13++;

    // Decrement iterator
    dsa::List<int> list14 = dsa::List<int>{ 10, 20, 30 };
    std::cout << "List14:\t" << list14 << '\n';
    auto it_14 = list14.end();
    it_14--;
    std::cout << *it_14 << ' ';
    tests::compare(*it_14, 30);
    --it_14;
    std::cout << *it_14 << ' ';
    tests::compare(*it_14, 20);
    --it_14;
    std::cout << *it_14 << ' ';
    tests::compare(*it_14, 10);
    --it_14;

    // Decrement const_iterator
    const dsa::List<int> list15 = dsa::List<int>{ 10, 20, 30 };
    std::cout << "List15:\t" << list15 << '\n';
    auto cit_15 = list15.cend();
    cit_15--;
    std::cout << *cit_15 << ' ';
    tests::compare(*cit_15, 30);
    --cit_15;
    std::cout << *cit_15 << ' ';
    tests::compare(*cit_15, 20);
    --cit_15;
    std::cout << *cit_15 << ' ';
    tests::compare(*cit_15, 10);
    --cit_15;

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
