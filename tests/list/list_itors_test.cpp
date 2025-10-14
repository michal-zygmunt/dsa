/**
 * @file list_itors_test.cpp
 * @brief This file tests List iterators
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/list.h"

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <list>
#include <new>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start list_itors_test:\n";

        std::cout << "Explicit iterator\n";
        dsa::List<int> list1{ 0, 10, 20 };
        // NOLINTNEXTLINE(modernize-loop-convert)
        for (dsa::List<int>::iterator iterator = list1.begin(); iterator != list1.end(); iterator++)
        {
            *iterator += 100;
            std::cout << *iterator << '\t';
        }
        std::cout << '\n';
        const std::initializer_list<int> expected1 = { 100, 110, 120 };
        tests::compare("List1", list1, expected1);

        std::cout << "Auto iterator\n";
        dsa::List<int> list2{ 0, 25, 50 };
        for (auto& item : list2)
        {
            item += 100;
            std::cout << item << '\t';
        }
        std::cout << '\n';
        const std::initializer_list<int> expected2 = { 100, 125, 150 };
        tests::compare("List2", list2, expected2);

        std::cout << "Explicit const_iterator\n";
        const dsa::List<int> list3{ 0, 10, 20 };
        // NOLINTNEXTLINE(modernize-loop-convert)
        for (dsa::List<int>::const_iterator iterator = list3.cbegin(); iterator != list3.cend(); iterator++)
        {
            std::cout << (*iterator) << '\t';
        }
        std::cout << '\n';
        const std::initializer_list<int> expected3 = { 0, 10, 20 };
        tests::compare("List3", list3, expected3);

        std::cout << "Auto const_iterator\n";
        const dsa::List<int> list4{ 0, 25, 50 };
        for (const auto& item : list4)
        {
            std::cout << item << '\t';
        }
        std::cout << '\n';
        const std::initializer_list<int> expected4 = { 0, 25, 50 };
        tests::compare("List4", list4, expected4);

        // Check iterator of one element
        dsa::List<int> list5 = dsa::List<int>(1, 0);
        auto iterator = list5.insert(list5.cbegin(), 10);
        int val = *iterator;
        const int expectedval5 = 10;
        tests::compare("List5 iterator", val, expectedval5);
        const std::initializer_list<int> expected5 = { 10, 0 };
        tests::compare("List5", list5, expected5);

        // Check iterator after inserting 0 elements
        dsa::List<int> list6 = dsa::List<int>(1, 50);
        list6.push_front(40);
        list6.push_front(30);
        iterator = list6.insert(list6.cbegin(), 0, 5);
        val = *iterator;
        const int expectedval6 = 30;
        tests::compare("List6 iterator", val, expectedval6);
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
        std::cout << "\n\n";

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
        std::cout << "\n\n";

        // std library operation on custom iterators
        dsa::List<int> list9 = dsa::List<int>{ 10, 20, 30, 40, 50 };
        std::fill(list9.begin(), list9.end(), 10);
        const std::initializer_list<int> expected9 = { 10, 10, 10, 10, 10 };
        tests::compare("List9", list9, expected9);

        // check const_iterator for const object
        dsa::List<int> list10 = dsa::List<int>{ 10, 20, 30 };
        auto iter10b = list10.begin();
        tests::compare("iter10b", *iter10b, 10);
        *iter10b = 1;
        auto citer10b = list10.cbegin();
        tests::compare("citer10b", *citer10b, 1);

        auto iter10e = list10.end();
        iter10e--;
        tests::compare("iter10e", *iter10e, 30);

        auto citer10e = list10.cend();
        citer10e--;
        tests::compare("citer10e", *citer10e, 30);

        const dsa::List<int> list11 = dsa::List<int>{ 10, 20, 30 };
        auto iter11b = list11.begin();
        tests::compare("iter11b", *iter11b, 10);

        auto citer11b = list11.cbegin();
        tests::compare("citer11b", *citer11b, 10);

        auto iter11e = list11.end();
        iter11e--;
        tests::compare("iter11e", *iter11e, 30);

        auto citer11e = list11.cend();
        citer11e--;
        tests::compare("citer11e", *citer11e, 30);

        // increment iterator
        dsa::List<int> list12 = dsa::List<int>{ 10, 20, 30 };
        std::cout << "List12\t" << list12 << '\n';
        auto it_12 = list12.begin();
        tests::compare("it_12", *it_12, 10);
        it_12++;
        tests::compare("it_12", *it_12, 20);
        it_12++;
        tests::compare("it_12", *it_12, 30);
        it_12++;
        std::cout << '\n';

        // increment const_iterator
        const dsa::List<int> list13 = dsa::List<int>{ 10, 20, 30 };
        std::cout << "List13\t" << list13 << '\n';

        auto cit_13 = list13.cbegin();
        tests::compare("cit_13", *cit_13, 10);
        cit_13++;
        tests::compare("cit_13", *cit_13, 20);
        cit_13++;
        tests::compare("cit_13", *cit_13, 30);
        cit_13++;
        std::cout << '\n';

        // decrement iterator
        dsa::List<int> list14 = dsa::List<int>{ 10, 20, 30 };
        std::cout << "List14\t" << list14 << '\n';
        auto it_14 = list14.end();
        it_14--;
        tests::compare("it_14", *it_14, 30);
        --it_14;
        tests::compare("it_14", *it_14, 20);
        --it_14;
        tests::compare("it_14", *it_14, 10);
        --it_14;
        std::cout << '\n';

        // decrement const_iterator
        const dsa::List<int> list15 = dsa::List<int>{ 10, 20, 30 };
        std::cout << "List15\t" << list15 << '\n';
        auto cit_15 = list15.cend();
        cit_15--;
        tests::compare("cit_15", *cit_15, 30);
        --cit_15;
        tests::compare("cit_15", *cit_15, 20);
        --cit_15;
        tests::compare("cit_15", *cit_15, 10);
        --cit_15;


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list1{ 0, 10, 20 };
        // NOLINTNEXTLINE(modernize-loop-convert, modernize-use-auto)
        for (std::list<int>::iterator std_iter = std_list1.begin(); std_iter != std_list1.end(); std_iter++)
        {
            *std_iter += 100;
            std::cout << *std_iter << "\t\n";
        }
        tests::compare("List1 vs std", list1, std_list1);

        std::list<int> std_list2{ 0, 25, 50 };
        for (auto& item : std_list2)
        {
            item += 100;
            std::cout << item << "\t\n";
        }
        tests::compare("List2 vs std", list2, std_list2);

        const std::list<int> std_list3{ 0, 10, 20 };
        // NOLINTNEXTLINE(modernize-loop-convert, modernize-use-auto)
        for (std::list<int>::const_iterator std_iter = std_list3.cbegin(); std_iter != std_list3.cend(); std_iter++)
        {
            std::cout << (*std_iter) << '\t';
        }
        std::cout << '\n';
        tests::compare("List3 vs std", list3, std_list3);

        const std::list<int> std_list4{ 0, 25, 50 };
        for (const auto& item : std_list4)
        {
            std::cout << item << '\t';
        }
        std::cout << '\n';
        tests::compare("List4 vs std", list4, std_list4);

        std::list<int> std_list5 = std::list<int>(1, 0);
        auto std_iterator = std_list5.insert(std_list5.cbegin(), 10);
        val = *std_iterator;
        tests::compare("List5 iterator vs std", expectedval5, val);
        tests::compare("List5 vs std", list5, expected5);

        std::list<int>std_list6 = std::list<int>(1, 50);
        std_list6.push_front(40);
        std_list6.push_front(30);
        std_iterator = std_list6.insert(std_list6.cbegin(), 0, 5);
        val = *std_iterator;
        tests::compare("List6 iterator vs std", expectedval6, val);
        tests::compare("List6 vs std", list6, std_list6);

        std::list<int>std_list9 = std::list<int>{ 10, 20, 30, 40, 50 };
        std::fill(std_list9.begin(), std_list9.end(), 10);
        tests::compare("List9 vs std", list9, std_list9);

        std::list<int>std_list10 = std::list<int>{ 10, 20, 30 };
        auto std_iter10b = std_list10.begin();
        *std_iter10b = 1;
        auto std_citer10b = std_list10.cbegin();
        tests::compare("citer10b vs std", *citer10b, *std_citer10b);

        const std::list<int>std_list11 = std::list<int>{ 10, 20, 30 };
        auto std_iter11b = std_list11.begin();
        tests::compare("iter11b vs std", *iter11b, *std_iter11b);

        auto std_citer11b = std_list11.cbegin();
        tests::compare("citer11b vs std", *citer11b, *std_citer11b);
    }
    catch (const std::bad_alloc& exception)
    {
        std::cerr << "Caught std::bad_alloc: " << exception.what() << '\n';
        return 1;
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

    tests::print_stats();
    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
