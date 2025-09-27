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
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start ForwardListItors test:\n";

    try
    {
        std::cout << "Explicit iterator\n";
        dsa::ForwardList<int> list1{ 0, 10, 20 };
        // NOLINTNEXTLINE(modernize-loop-convert)
        for (dsa::ForwardList<int>::iterator iterator = list1.begin(); iterator != list1.end(); iterator++)
        {
            *iterator += 100;
            std::cout << *iterator << '\t';
        }
        std::cout << '\n';
        const std::initializer_list<int> expected1 = { 100, 110, 120 };
        tests::compare("ForwardList1", list1, expected1);

        std::cout << "Auto iterator\n";
        dsa::ForwardList<int> list2{ 0, 25, 50 };
        for (auto& item : list2)
        {
            item += 100;
            std::cout << item << '\t';
        }
        std::cout << '\n';
        const std::initializer_list<int> expected2 = { 100, 125, 150 };
        tests::compare("ForwardList2", list2, expected2);

        std::cout << "Explicit const_iterator\n";
        const dsa::ForwardList<int> list3{ 0, 10, 20 };
        // NOLINTNEXTLINE(modernize-loop-convert)
        for (dsa::ForwardList<int>::const_iterator iterator = list3.cbegin(); iterator != list3.cend(); iterator++)
        {
            std::cout << (*iterator) << '\t';
        }
        std::cout << '\n';
        const std::initializer_list<int> expected3 = { 0, 10, 20 };
        tests::compare("ForwardList3", list3, expected3);

        std::cout << "Auto const_iterator\n";
        const dsa::ForwardList<int> list4{ 0, 25, 50 };
        for (const auto& item : list4)
        {
            std::cout << item << '\t';
        }
        std::cout << '\n';
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

        auto iter10bb = list10.before_begin();
        iter10bb++;
        tests::compare("iter10bb", *iter10bb, 10);

        auto citer10bb = list10.cbefore_begin();
        citer10bb++;
        tests::compare("iter10bb", *citer10bb, 10);

        auto iter10b = list10.begin();
        tests::compare("iter10b", *iter10b, 10);
        *iter10b = 1;
        auto citer10b = list10.cbegin();
        tests::compare("citer10b", *citer10b, 1);

        auto iter10e = list10.end();
        tests::compare("iter10e", iter10e == dsa::ForwardList<int>::iterator(nullptr), true);

        auto citer10e = list10.cend();
        tests::compare("citer10e", citer10e == dsa::ForwardList<int>::const_iterator(nullptr), true);
    }
    catch (const std::runtime_error& exception)
    {
        std::cerr << "Caught std::runtime_error: " << exception.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unhandled unknown exception\n";
        return 1;
    }

    const dsa::ForwardList<int> list11 = dsa::ForwardList<int>{ 10, 20, 30 };
    auto iter11b = list11.begin();
    tests::compare("iter11b", *iter11b, 10);

    auto citer11b = list11.cbegin();
    tests::compare("citer11b", *citer11b, 10);

    auto iter11e = list11.end();
    tests::compare("iter11e", iter11e == dsa::ForwardList<int>::const_iterator(nullptr), true);

    auto citer11e = list11.cend();
    tests::compare("citer11e", citer11e == dsa::ForwardList<int>::const_iterator(nullptr), true);

    // increment iterator
    dsa::ForwardList<int> list12 = dsa::ForwardList<int>{ 10, 20, 30 };
    std::cout << "ForwardList12\t" << list12 << '\n';
    auto it_12 = list12.begin();
    tests::compare("it_12", *it_12, 10);
    it_12++;
    tests::compare("it_12", *it_12, 20);
    it_12++;
    tests::compare("it_12", *it_12, 30);
    it_12++;
    std::cout << '\n';

    // increment const_iterator
    const dsa::ForwardList<int> list13 = dsa::ForwardList<int>{ 10, 20, 30 };
    std::cout << "ForwardList13\t" << list13 << '\n';

    auto cit_13 = list13.cbegin();
    tests::compare("cit_13", *cit_13, 10);
    cit_13++;
    tests::compare("cit_13", *cit_13, 20);
    cit_13++;
    tests::compare("cit_13", *cit_13, 30);
    cit_13++;
    std::cout << '\n';

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
