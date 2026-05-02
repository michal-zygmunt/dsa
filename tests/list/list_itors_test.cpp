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
#include <exception>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
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
        // use classic iterator based algorithms, separate test was added to test std::ranges based algorithms
        // NOLINTNEXTLINE(modernize-use-ranges)
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
        dsa::List<int> list12a = dsa::List<int>{ 10, 20, 30 };
        std::cout << "List12a\t" << list12a << '\n';
        auto it_12a = list12a.begin();
        tests::compare("it_12", *it_12a, 10);
        ++it_12a;
        tests::compare("it_12a", *it_12a, 20);
        ++it_12a;
        tests::compare("it_12a", *it_12a, 30);
        ++it_12a;
        ++it_12a;
        std::cout << '\n';

        dsa::List<int> list12b = dsa::List<int>{ 10, 20, 30 };
        std::cout << "List12b\t" << list12b << '\n';
        auto it_12b = list12b.begin();
        tests::compare("it_12b", *it_12b, 10);
        it_12b++;
        tests::compare("it_12", *it_12b, 20);
        it_12b++;
        tests::compare("it_12", *it_12b, 30);
        it_12b++;
        it_12b++;
        std::cout << '\n';

        // increment const_iterator
        const dsa::List<int> list13a = dsa::List<int>{ 10, 20, 30 };
        std::cout << "List13a\t" << list13a << '\n';
        auto cit_13a = list13a.cbegin();
        tests::compare("cit_13a", *cit_13a, 10);
        ++cit_13a;
        tests::compare("cit_13a", *cit_13a, 20);
        ++cit_13a;
        tests::compare("cit_13a", *cit_13a, 30);
        ++cit_13a;
        ++cit_13a;
        std::cout << '\n';

        const dsa::List<int> list13b = dsa::List<int>{ 10, 20, 30 };
        std::cout << "List13b\t" << list13b << '\n';
        auto cit_13b = list13b.cbegin();
        tests::compare("cit_13b", *cit_13b, 10);
        cit_13b++;
        tests::compare("cit_13b", *cit_13b, 20);
        cit_13b++;
        tests::compare("cit_13b", *cit_13b, 30);
        cit_13b++;
        cit_13b++;
        std::cout << '\n';

        // decrement iterator
        dsa::List<int> list14a = dsa::List<int>{ 10, 20, 30 };
        std::cout << "List14a\t" << list14a << '\n';
        auto it_14a = list14a.end();
        --it_14a;
        tests::compare("it_14a", *it_14a, 30);
        --it_14a;
        tests::compare("it_14a", *it_14a, 20);
        --it_14a;
        tests::compare("it_14a", *it_14a, 10);
        --it_14a;
        --it_14a;
        std::cout << '\n';

        dsa::List<int> list14b = dsa::List<int>{ 10, 20, 30 };
        std::cout << "List14b\t" << list14b << '\n';
        auto it_14b = list14b.end();
        it_14b--;
        tests::compare("it_14b", *it_14b, 30);
        it_14b--;
        tests::compare("it_14b", *it_14b, 20);
        it_14b--;
        tests::compare("it_14b", *it_14b, 10);
        it_14b--;
        it_14b--;
        std::cout << '\n';

        // decrement const_iterator
        const dsa::List<int> list15a = dsa::List<int>{ 10, 20, 30 };
        std::cout << "List15a\t" << list15a << '\n';
        auto cit_15a = list15a.cend();
        --cit_15a;
        tests::compare("cit_15a", *cit_15a, 30);
        --cit_15a;
        tests::compare("cit_15a", *cit_15a, 20);
        --cit_15a;
        tests::compare("cit_15a", *cit_15a, 10);
        --cit_15a;
        --cit_15a;

        const dsa::List<int> list15b = dsa::List<int>{ 10, 20, 30 };
        std::cout << "List15b\t" << list15b << '\n';
        auto cit_15b = list15b.cend();
        cit_15b--;
        tests::compare("cit_15b", *cit_15b, 30);
        cit_15b--;
        tests::compare("cit_15b", *cit_15b, 20);
        cit_15b--;
        tests::compare("cit_15b", *cit_15b, 10);
        cit_15b--;
        cit_15b--;

        // test throwing 'runtime_error' exception from dereferencing invalid iterator
        try
        {
            const dsa::List<int> list16a;
            std::cout << *list16a.begin();

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error&)
        {
            std::cout << "list16a runtime error exception handled correctly\n\n";
        }

        try
        {
            const dsa::List<int> list16b;
            std::cout << *list16b.rbegin();

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error&)
        {
            std::cout << "list16b runtime error exception handled correctly\n\n";
        }

        try
        {
            const dsa::List<int> list16c;
            std::cout << *list16c.rend();

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error&)
        {
            std::cout << "list16c runtime error exception handled correctly\n\n";
        }

        try
        {
            const dsa::List<int> list16d;
            std::cout << *list16d.crbegin();

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error&)
        {
            std::cout << "list16d runtime error exception handled correctly\n\n";
        }

        try
        {
            const dsa::List<int> list16e;
            std::cout << *list16e.crend();

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error&)
        {
            std::cout << "list16e runtime error exception handled correctly\n\n";
        }

        try
        {
            const dsa::List<int> list17{ 1, 2, 3 };
            std::cout << list17.begin().operator->() << '\n';
            std::cout << list17.end().operator->() << '\n';

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error&)
        {
            std::cout << "list17 runtime error exception handled correctly\n\n";
        }

        try
        {
            dsa::List<int> list18 = dsa::List<int>{};
            auto it18 = list18.begin();
            std::advance(it18, 5);
            std::cout << *it18;

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error&)
        {
            std::cout << "list18 runtime error exception handled correctly\n\n";
        }

        try
        {
            const dsa::List<int> list19{};
            std::cout << list19.front();
            std::cout << list19.back();

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error&)
        {
            std::cout << "list19 runtime error exception handled correctly\n\n";
        }

        const dsa::List<int> list20;
        auto iter20 = list20.begin();
        std::advance(iter20, 1);
        tests::compare("iter20 == nullptr", iter20 == nullptr, true);

        // test iterators traversal
        dsa::List<int> list21 = { 0, 10, 20, 30, 40 };
        const std::list<int> temp21(list21.begin(), list21.end());
        tests::compare("list21 begin()", *list21.begin(), 0);
        auto iter21 = list21.begin();
        std::advance(iter21, 1);
        tests::compare("list21 begin()++", *iter21, 10);
        iter21 = list21.end();
        std::advance(iter21, -1);
        tests::compare("list21 end()--", *iter21, 40);
        tests::compare("list21 end()-- == back()", *iter21, list21.back());
        tests::compare("list21 iter", list21, temp21);

        // test const iterator traversal
        const auto& list22 = list21;
        const std::list<int> temp22(list22.cbegin(), list22.cend());
        tests::compare("list22 cbegin()", *list22.cbegin(), 0);
        auto citer22 = list22.cbegin();
        std::advance(citer22, 1);
        tests::compare("list22 cbegin()++", *citer22, 10);
        citer22 = list22.cend();
        std::advance(citer22, -1);
        tests::compare("list22 cend()--", *citer22, 40);
        tests::compare("list22 cend() == back()", *citer22, list22.back());
        tests::compare("list22 const iter", list22, temp22);

        // test reverse iterator traversal
        dsa::List<int> list23{ 0, 1, 2, 3, 4 };
        auto iter23 = list23.rend();
        std::advance(iter23, -1);
        tests::compare("list23 rend()--", *iter23, 0);
        iter23 = list23.rbegin();
        std::advance(iter23, 1);
        tests::compare("list23 rbegin()++", *iter23, 3);
        const std::list<int> temp23(list23.rbegin(), list23.rend());
        const dsa::List<int> reversed23{ 4, 3, 2, 1, 0 };
        tests::compare("list23 reverse iter", reversed23, temp23);


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
        // use classic iterator based algorithms, separate test was added to test std::ranges based algorithms
        // NOLINTNEXTLINE(modernize-use-ranges)
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


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
