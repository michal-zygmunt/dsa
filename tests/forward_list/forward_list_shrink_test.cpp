/**
 * @file forward_list_shrink_test.cpp
 * @brief This file tests functions decreasing ForwardList length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/forward_list.h"

#include <cstddef>
#include <exception>
#include <forward_list>
#include <initializer_list>
#include <iostream>
#include <iterator>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start forward_list_shrink_test:\n";

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
        list1.erase_after(list1.begin()[list1.size() - 2]);
        list1.pop_front();
        auto indexes = { 100, 5, 2, 0, -1 };
        for (const auto& item : indexes)
        {
            list1.erase_after(list1.begin()[static_cast<size_t>(item)]);
        }
        const std::initializer_list<int> expected1 = { 10, 30 };
        tests::compare("ForwardList1", list1, expected1);

        dsa::ForwardList<int> list2 = dsa::ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
        list2.erase_after(list2.begin()[1], list2.begin()[3]);
        const std::initializer_list<int> expected2 = { 0, 10, 30, 40, 50 };
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
        list3.erase_after(list3.begin()[1]);
        list3.erase_after(list3.begin()[1], list3.begin()[3]);
        const std::initializer_list<int> expected3 = { 0, 10, 40, 50 };
        tests::compare("ForwardList3", list3, expected3);

        dsa::ForwardList<int> list4 = dsa::ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
        list4.erase_after(list4.begin()[1]);
        list4.erase_after(list4.begin()[1], list4.begin()[4]);
        const std::initializer_list<int> expected4 = { 0, 10, 50 };
        tests::compare("ForwardList4", list4, expected4);

        dsa::ForwardList<int> list5 = dsa::ForwardList<int>({ 0, 10, 0, 0, 40, 0 });
        auto cnt5 = list5.remove(0);
        const std::initializer_list<int> expected5 = { 10, 40 };
        tests::compare("ForwardList5", list5, expected5);
        tests::compare("ForwardList5 removed count", cnt5, std::size_t{ 4 });

        dsa::ForwardList<int> list6 = dsa::ForwardList<int>({ 0, 0, 0, 0, 0, 0 });
        auto cnt6 = list6.remove(0);
        const std::initializer_list<int> expected6 = { };
        tests::compare("ForwardList6", list6, expected6);
        tests::compare("ForwardList6 removed count", cnt6, std::size_t{ 6 });

        dsa::ForwardList<int> list7 = dsa::ForwardList<int>({ 0, 10, 0, 0, 40, 0 });
        auto cnt7 = list7.remove_if([](int val) { return val == 0; });
        const std::initializer_list<int> expected7 = { 10, 40 };
        tests::compare("ForwardList7", list7, expected7);
        tests::compare("ForwardList7 removed count", cnt7, std::size_t{ 4 });

        dsa::ForwardList<int> list8 = dsa::ForwardList<int>({ 0, 0, 0, 0, 0, 0 });
        auto cnt8 = list8.remove_if([](int val) { return val == 0; });
        const std::initializer_list<int> expected8 = { };
        tests::compare("ForwardList8", list8, expected8);
        tests::compare("ForwardList8 removed count", cnt8, std::size_t{ 6 });

        dsa::ForwardList<int> list9 = dsa::ForwardList<int>({ 0, 1, 2, 3, 4, 5 });
        auto cnt9 = list9.remove_if([](int val) { return val % 2 == 0; });
        const std::initializer_list<int> expected9 = { 1, 3, 5 };
        tests::compare("ForwardList9", list9, expected9);
        tests::compare("ForwardList9 removed count", cnt9, std::size_t{ 3 });

        dsa::ForwardList<int> list10 = dsa::ForwardList<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt10 = list10.remove_if([](int val) { return val <= 5; });
        const std::initializer_list<int> expected10 = { 10, 7, 9 };
        tests::compare("ForwardList10", list10, expected10);
        tests::compare("ForwardList10 removed count", cnt10, std::size_t{ 3 });

        dsa::ForwardList<int> list11 = dsa::ForwardList<int>({ 0 });
        tests::compare(list11.empty(), false);
        list11.clear();
        tests::compare(list11.empty(), true);
        const std::initializer_list<int> expected11 = { };
        tests::compare("ForwardList11", list11, expected11);

        dsa::ForwardList<int> list12 = dsa::ForwardList<int>({ 10, 20, 30 });
        list12.pop_front();
        list12.pop_front();
        list12.pop_front();
        list12.pop_front();
        const std::initializer_list<int> expected12 = { };
        tests::compare("ForwardList12", list12, expected12);

        dsa::ForwardList<int> list13;
        auto iter13 = list13.erase_after(list13.begin(), list13.end());
        tests::compare("iter13 == nullptr", iter13 == nullptr, true);

        dsa::ForwardList<int> list14 = dsa::ForwardList<int>({ 0, 10, 0, 0, 40, 0 });
        auto cnt14 = dsa::erase(list14, 0);
        const std::initializer_list<int> expected14 = { 10, 40 };
        tests::compare("ForwardList14", list14, expected14);
        tests::compare("ForwardList14 removed count", cnt14, std::size_t{ 4 });

        dsa::ForwardList<int> list15 = dsa::ForwardList<int>({ 0, 0, 0, 0, 0, 0 });
        auto cnt15 = dsa::erase(list15, 0);
        const std::initializer_list<int> expected15 = { };
        tests::compare("ForwardList15", list15, expected15);
        tests::compare("ForwardList15 erase count", cnt15, std::size_t{ 6 });

        dsa::ForwardList<int> list16 = dsa::ForwardList<int>({ 0, 10, 0, 0, 40, 0 });
        auto cnt16 = dsa::erase_if(list16, [](int val) { return val == 0; });
        const std::initializer_list<int> expected16 = { 10, 40 };
        tests::compare("ForwardList16", list16, expected16);
        tests::compare("ForwardList16 erase count", cnt16, std::size_t{ 4 });

        dsa::ForwardList<int> list17 = dsa::ForwardList<int>({ 0, 0, 0, 0, 0, 0 });
        auto cnt17 = dsa::erase_if(list17, [](int val) { return val == 0; });
        const std::initializer_list<int> expected17 = { };
        tests::compare("ForwardList17", list17, expected17);
        tests::compare("ForwardList17 erase_if count", cnt17, std::size_t{ 6 });

        dsa::ForwardList<int> list18 = dsa::ForwardList<int>({ 0, 1, 2, 3, 4, 5 });
        auto cnt18 = dsa::erase_if(list18, [](int val) { return val % 2 == 0; });
        const std::initializer_list<int> expected18 = { 1, 3, 5 };
        tests::compare("ForwardList18", list18, expected18);
        tests::compare("ForwardList18 erase_if count", cnt18, std::size_t{ 3 });

        dsa::ForwardList<int> list19 = dsa::ForwardList<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt19 = dsa::erase_if(list19, [](int val) { return val <= 5; });
        const std::initializer_list<int> expected19 = { 10, 7, 9 };
        tests::compare("ForwardList19", list19, expected19);
        tests::compare("ForwardList19 erase_if count", cnt19, std::size_t{ 3 });


        std::cout << "Compare operations results with std container\n\n";

        std::forward_list<int> std_list2{ 0, 10, 20, 30, 40, 50 };
        auto iter_start_2 = std_list2.begin();
        auto iter_end_2 = std_list2.begin();
        std::advance(iter_start_2, 1);
        std::advance(iter_end_2, 3);
        std_list2.erase_after(iter_start_2, iter_end_2);
        tests::compare("ForwardList2 vs std", list2, std_list2);

        std::forward_list<int> std_list3{ 0, 10, 20, 30, 40, 50 };
        auto iter_start_3 = std_list3.begin();
        auto iter_end_3 = std_list3.begin();
        std::advance(iter_start_3, 1);
        std_list3.erase_after(iter_start_3);
        iter_start_3 = std_list3.begin();
        std::advance(iter_start_3, 1);
        std::advance(iter_end_3, 3);
        std_list3.erase_after(iter_start_3, iter_end_3);
        tests::compare("ForwardList3 vs std", list3, std_list3);

        std::forward_list<int> std_list4{ 0, 10, 20, 30, 40, 50 };
        auto iter_start_4 = std_list4.begin();
        auto iter_end_4 = std_list4.begin();
        std::advance(iter_start_4, 1);
        std_list4.erase_after(iter_start_4);
        iter_start_4 = std_list4.begin();
        iter_end_4 = std_list4.begin();
        std::advance(iter_start_4, 1);
        std::advance(iter_end_4, 4);
        std_list4.erase_after(iter_start_4, iter_end_4);
        tests::compare("ForwardList4 vs std", list4, std_list4);

        std::forward_list<int> std_list5{ 0, 10, 0, 0, 40, 0 };
        auto std_cnt5 = std_list5.remove(0);
        tests::compare("ForwardList5 vs std", list5, std_list5);
        tests::compare("ForwardList5 removed count vs std", cnt5, std_cnt5);

        std::forward_list<int> std_list6{ 0, 0, 0, 0, 0, 0 };
        auto std_cnt6 = std_list6.remove(0);
        tests::compare("ForwardList6 vs std", list6, std_list6);
        tests::compare("ForwardList6 removed count vs std", cnt6, std_cnt6);

        std::forward_list<int> std_list7{ 0, 10, 0, 0, 40, 0 };
        auto std_cnt7 = std_list7.remove_if([](int val) { return val == 0; });
        tests::compare("ForwardList7 vs std", list7, std_list7);
        tests::compare("ForwardList7 removed count vs std", cnt7, std_cnt7);

        std::forward_list<int> std_list8{ 0, 0, 0, 0, 0, 0 };
        auto std_cnt8 = std_list8.remove_if([](int val) { return val == 0; });
        tests::compare("ForwardList8 vs std", list8, std_list8);
        tests::compare("ForwardList8 removed count vs std", cnt8, std_cnt8);

        std::forward_list<int> std_list9{ 0, 1, 2, 3, 4, 5 };
        auto std_cnt9 = std_list9.remove_if([](int val) { return val % 2 == 0; });
        tests::compare("ForwardList9 vs std", list9, std_list9);
        tests::compare("ForwardList9 removed count vs std", cnt9, std_cnt9);

        std::forward_list<int> std_list10{ 0, 10, 2, 5, 7, 9 };
        auto std_cnt10 = std_list10.remove_if([](int val) { return val <= 5; });
        tests::compare("ForwardList10 vs std", list10, std_list10);
        tests::compare("ForwardList10 removed count vs std", cnt10, std_cnt10);

        std::forward_list<int> std_list14{ 0, 10, 0, 0, 40, 0 };
        // Linter do not recognizes that functions std::erase/erase_if are included from std::forward_list in C++20
        // NOLINTNEXTLINE(misc-include-cleaner,-warnings-as-errors)
        auto std_cnt14 = std::erase(std_list14, 0);
        tests::compare("ForwardList14 vs std", list14, expected14);
        tests::compare("ForwardList14 removed count vs std", cnt14, std_cnt14);

        std::forward_list<int> std_list15{ 0, 0, 0, 0, 0, 0 };
        // NOLINTNEXTLINE(misc-include-cleaner,-warnings-as-errors)
        auto std_cnt15 = std::erase(std_list15, 0);
        tests::compare("ForwardList15 vs std", list15, expected15);
        tests::compare("ForwardList15 erase count vs std", cnt15, std_cnt15);

        std::forward_list<int> std_list16{ 0, 10, 0, 0, 40, 0 };
        // NOLINTNEXTLINE(misc-include-cleaner,-warnings-as-errors)
        auto std_cnt16 = std::erase_if(std_list16, [](int val) { return val == 0; });
        tests::compare("ForwardList16 vs std", list16, std_list16);
        tests::compare("ForwardList16 erase count vs std", cnt16, std_cnt16);

        std::forward_list<int> std_list17{ 0, 0, 0, 0, 0, 0 };
        // NOLINTNEXTLINE(misc-include-cleaner,-warnings-as-errors)
        auto std_cnt17 = std::erase_if(std_list17, [](int val) { return val == 0; });
        tests::compare("ForwardList17 vs std", list17, std_list17);
        tests::compare("ForwardList17 erase_if count vs std", cnt17, std_cnt17);

        std::forward_list<int> std_list18{ 0, 1, 2, 3, 4, 5 };
        // NOLINTNEXTLINE(misc-include-cleaner,-warnings-as-errors)
        auto std_cnt18 = std::erase_if(std_list18, [](int val) { return val % 2 == 0; });
        tests::compare("ForwardList18 vs std", list18, std_list18);
        tests::compare("ForwardList18 erase_if count vs std", cnt18, std_cnt18);

        std::forward_list<int> std_list19{ 0, 10, 2, 5, 7, 9 };
        // NOLINTNEXTLINE(misc-include-cleaner,-warnings-as-errors)
        auto std_cnt19 = std::erase_if(std_list19, [](int val) { return val <= 5; });
        tests::compare("ForwardList19 vs std", list19, std_list19);
        tests::compare("ForwardList19 erase_if count vs std", cnt19, std_cnt19);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}