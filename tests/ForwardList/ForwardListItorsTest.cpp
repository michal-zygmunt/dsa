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
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start ForwardListItors test:\n";

    std::cout << "Explicit iterator\n";
    dsa::ForwardList<int> list1{ 0, 10, 20 };
    for (dsa::ForwardList<int>::iterator iterator = list1.begin(); iterator != list1.end(); iterator++)
    {
        auto& val = *iterator;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    const std::initializer_list<int> expected1 = { 100, 110, 120 };
    tests::compare("ForwardList1", list1, expected1);

    std::cout << "Auto iterator\n";
    dsa::ForwardList<int> list2{ 0, 25, 50 };
    for (auto iterator = list2.begin(); iterator != list2.end(); iterator++)
    {
        auto& val = *iterator;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    const std::initializer_list<int> expected2 = { 100, 125, 150 };
    tests::compare("ForwardList2", list2, expected2);

    std::cout << "Explicit Const iterator\n";
    const dsa::ForwardList<int> list3{ 0, 10, 20 };
    for (dsa::ForwardList<int>::const_iterator iterator = list3.cbegin(); iterator != list3.cend(); iterator++)
    {
        //auto& val = *iterator; // reference generate compilation error
        auto val = *iterator;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    const std::initializer_list<int> expected3 = { 0, 10, 20 };
    tests::compare("ForwardList3", list3, expected3);

    std::cout << "Auto Const iterator\n";
    const dsa::ForwardList<int> list4{ 0, 25, 50 };
    for (auto iterator = list4.cbegin(); iterator != list4.cend(); iterator++)
    {
        //auto& val = *iterator; // reference generate compilation error
        auto val = *iterator;
        std::cout << val << '\t';
        val += 100;
        std::cout << val << '\n';
    }
    const std::initializer_list<int> expected4 = { 0, 25, 50 };
    tests::compare("ForwardList4", list4, expected4);

    // Check iterator of one element
    dsa::ForwardList<int> list5 = dsa::ForwardList<int>(0);
    auto iterator = list5.insert_after(list5.cbegin(), 10);
    int val = *iterator;
    int expectedval = 10;
    tests::compare("ForwardList5 iterator", val, expectedval);
    const std::initializer_list<int> expected5 = { 0, 10 };
    tests::compare("ForwardList5", list5, expected5);

    // Check iterator after inserting 0 elements
    dsa::ForwardList<int> list6 = dsa::ForwardList<int>(50);
    list6.push_front(40);
    list6.push_front(30);
    iterator = list6.insert_after(list6.cbegin(), 0, 5);
    val = *iterator;
    expectedval = 30;
    tests::compare("ForwardList6 iterator", val, expectedval);
    const std::initializer_list<int> expected6 = { 30, 40, 50 };
    tests::compare("ForwardList6", list6, expected6);


    // Range based loop
    const std::initializer_list<int> expected7 = { 10, 20, 30, 40, 50 };
    std::initializer_list<int>::iterator il_iterator{};
    const dsa::ForwardList<int> list7 = dsa::ForwardList<int>{ 10, 20, 30, 40, 50 };
    std::cout << "ForwardList7 vs std::initializer_list:\n";
    il_iterator = expected7.begin();
    for (auto item : list7)
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
    for (const auto item : list7)
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
    const dsa::ForwardList<int> list8 = dsa::ForwardList<int>{ 10, 20, 30, 40, 50 };
    std::cout << "ForwardList8 vs std::initializer_list:\n";
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
    dsa::ForwardList<int> list9 = dsa::ForwardList<int>{ 10, 20, 30, 40, 50 };
    std::fill(list9.begin(), list9.end(), 10);
    const std::initializer_list<int> expected9 = { 10, 10, 10, 10, 10 };
    tests::compare("ForwardList9", list9, expected9);

    // check const_iterator for const object
    dsa::ForwardList<int> list10 = dsa::ForwardList<int>{ 10, 20, 30 };
    auto iter10b = list10.begin();
    *iter10b = 1;
    auto citer10b = list10.cbegin();
    //*citer10b = 1; // compilation error
    auto iter10e = list10.end();
    //*iter10e = 1; // runtime error, assignment to memory outside list
    auto citer10e = list10.cend();
    //*citer10e = 1; // compilation error

    const dsa::ForwardList<int> list11 = dsa::ForwardList<int>{ 10, 20, 30 };
    auto iter11b = list11.begin();
    //*iter11b = 1; // compilation error
    auto citer11b = list11.cbegin();
    //*citer11b = 1; // compilation error
    auto iter11e = list11.end();
    //*iter11e = 1; // compilation error
    auto citer11e = list11.cend();
    //*citer11e = 1; // compilation error

    // Iterate over const_iterator
    const dsa::ForwardList<int> list12 = dsa::ForwardList<int>{ 10, 20, 30 };
    auto cit = list12.cbegin();
    std::cout << *cit << ' ';
    tests::compare(*cit, 10);
    cit++;
    std::cout << *cit << ' ';
    tests::compare(*cit, 20);
    cit++;
    std::cout << *cit << ' ';
    tests::compare(*cit, 30);
    cit++;

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
