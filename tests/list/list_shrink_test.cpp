/**
 * @file list_shrink_test.cpp
 * @brief This file tests functions decreasing List length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/list.h"

#include <cstddef>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start list_shrink_test:\n";

        dsa::List<int> list1 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
        auto iter1 = list1.erase(std::next(list1.begin(), static_cast<ptrdiff_t>(list1.size() - 1)));
        tests::compare("List1 iter", iter1 == list1.end(), true);
        list1.pop_front();
        auto indexes = { 100, 5, 2, 0 };
        for (const auto& idx : indexes)
        {
            list1.erase(std::next(list1.begin(), static_cast<ptrdiff_t>(idx)));
        }
        const std::initializer_list<int> expected1 = { 20, 40 };
        tests::compare("List1", list1, expected1);

        dsa::List<int> list2 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
        auto iter2 = list2.erase(std::next(list2.begin(), 1), std::next(list2.begin(), 3));
        tests::compare("List2 iter", iter2 == std::next(list2.begin(), 1), true);
        const std::initializer_list<int> expected2 = { 0, 30, 40, 50 };
        tests::compare("List2", list2, expected2);

        dsa::List<int> list3 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
        auto iter3 = list3.erase(std::next(list3.begin(), 1));
        tests::compare("List3 iter", iter3 == std::next(list3.begin(), 1), true);
        iter3 = list3.erase(std::next(list3.begin(), 1), std::next(list3.begin(), 3));
        const std::initializer_list<int> expected3 = { 0, 40, 50 };
        tests::compare("List3", list3, expected3);

        dsa::List<int> list4 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
        list4.erase(std::next(list4.begin(), 1));
        auto iter4 = list4.erase(std::next(list4.begin(), 1), std::next(list4.begin(), 4));
        tests::compare("List4 iter", iter4 == std::next(list4.begin(), 1), true);
        const std::initializer_list<int> expected4 = { 0, 50 };
        tests::compare("List4", list4, expected4);

        dsa::List<int> list5;
        auto iter5 = list5.begin();
        std::advance(iter5, 1);
        iter5 = list5.erase(iter5, iter5);
        tests::compare("iter5 == nullptr", iter5 == nullptr, true);

        dsa::List<int> list6;
        auto iter6 = list6.end();
        std::advance(iter6, 1);
        iter6 = list5.erase(iter6, iter6);
        tests::compare("iter6 == nullptr", iter6 == nullptr, true);

        dsa::List<int> list7{ 1, 2, 3 };
        auto iter7 = list7.erase(list7.end(), list7.end());
        tests::compare("iter7 == end()", iter7 == list7.end(), true);

        dsa::List<int> list8 = dsa::List<int>({ 0, 10, 0, 0, 40, 0 });
        list8.remove(0);
        const std::initializer_list<int> expected8 = { 10, 40 };
        tests::compare("List8", list8, expected8);

        dsa::List<int> list9 = dsa::List<int>({ 0, 0, 0, 0, 0, 0 });
        list9.remove(0);
        const std::initializer_list<int> expected9 = { };
        tests::compare("List9", list9, expected9);

        dsa::List<int> list10 = dsa::List<int>({ 0, 10, 0, 0, 40, 0 });
        auto cnt10 = list10.remove_if([](int val) { return val == 0; });
        const std::initializer_list<int> expected10 = { 10, 40 };
        tests::compare("List10", list10, expected10);
        tests::compare("List10 removed count", cnt10, std::size_t{ 4 });

        dsa::List<int> list11 = dsa::List<int>({ 0, 0, 0, 0, 0, 0 });
        auto cnt11 = list11.remove_if([](int val) { return val == 0; });
        const std::initializer_list<int> expected11 = { };
        tests::compare("List11", list11, expected11);
        tests::compare("List11 removed count", cnt11, std::size_t{ 6 });

        dsa::List<int> list12 = dsa::List<int>({ 0, 1, 2, 3, 4, 5 });
        auto cnt12 = list12.remove_if([](int val) { return val % 2 == 0; });
        const std::initializer_list<int> expected12 = { 1, 3, 5 };
        tests::compare("List12", list12, expected12);
        tests::compare("List12 removed count", cnt12, std::size_t{ 3 });

        dsa::List<int> list13 = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt13 = list13.remove_if([](int val) { return val <= 5; });
        const std::initializer_list<int> expected13 = { 10, 7, 9 };
        tests::compare("List13", list13, expected13);
        tests::compare("List13 removed count", cnt13, std::size_t{ 3 });

        dsa::List<int> list14 = dsa::List<int>({ 0 });
        tests::compare(list14.empty(), false);
        list14.clear();
        tests::compare(list14.empty(), true);
        const std::initializer_list<int> expected14 = { };
        tests::compare("List14", list14, expected14);

        dsa::List<int> list15 = dsa::List<int>({ 10, 20, 30 });
        list15.pop_front();
        list15.pop_front();
        list15.pop_front();
        list15.pop_front();
        const std::initializer_list<int> expected15 = { };
        tests::compare("List15", list15, expected15);

        dsa::List<int> list16 = dsa::List<int>({ 10, 20, 30 });
        list16.pop_back();
        list16.pop_back();
        list16.pop_back();
        list16.pop_back();
        const std::initializer_list<int> expected16 = { };
        tests::compare("List16", list16, expected16);

        dsa::List<int> list17 = dsa::List<int>({ 0, 10, 0, 0, 40, 0 });
        auto cnt17 = dsa::erase(list17, 0);
        const std::initializer_list<int> expected17 = { 10, 40 };
        tests::compare("List17", list17, expected17);
        tests::compare("List17 removed count", cnt17, std::size_t{ 4 });

        dsa::List<int> list18 = dsa::List<int>({ 0, 0, 0, 0, 0, 0 });
        auto cnt18 = dsa::erase(list18, 0);
        const std::initializer_list<int> expected18 = { };
        tests::compare("List18", list18, expected18);
        tests::compare("List18 erase count", cnt18, std::size_t{ 6 });

        dsa::List<int> list19 = dsa::List<int>({ 0, 10, 0, 0, 40, 0 });
        auto cnt19 = dsa::erase_if(list19, [](int val) { return val == 0; });
        const std::initializer_list<int> expected19 = { 10, 40 };
        tests::compare("List19", list19, expected19);
        tests::compare("List19 erase count", cnt19, std::size_t{ 4 });

        dsa::List<int> list20 = dsa::List<int>({ 0, 0, 0, 0, 0, 0 });
        auto cnt20 = dsa::erase_if(list20, [](int val) { return val == 0; });
        const std::initializer_list<int> expected20 = { };
        tests::compare("List20", list20, expected20);
        tests::compare("List20 erase_if count", cnt20, std::size_t{ 6 });

        dsa::List<int> list21 = dsa::List<int>({ 0, 1, 2, 3, 4, 5 });
        auto cnt21 = dsa::erase_if(list21, [](int val) { return val % 2 == 0; });
        const std::initializer_list<int> expected21 = { 1, 3, 5 };
        tests::compare("List21", list21, expected21);
        tests::compare("List21 erase_if count", cnt21, std::size_t{ 3 });

        dsa::List<int> list22a = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt22a = dsa::erase_if(list22a, [](int val) { return val == 5; });
        const std::initializer_list<int> expected22a = { 0, 10, 2, 7, 9 };
        tests::compare("List22a", list22a, expected22a);
        tests::compare("List22a erase_if count", cnt22a, std::size_t{ 1 });

        dsa::List<int> list22b = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt22b = dsa::erase_if(list22b, [](int val) { return val != 5; });
        const std::initializer_list<int> expected22b = { 5 };
        tests::compare("List22b", list22b, expected22b);
        tests::compare("List22b erase_if count", cnt22b, std::size_t{ 5 });

        dsa::List<int> list22c = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt22c = dsa::erase_if(list22c, [](int val) { return val < 5; });
        const std::initializer_list<int> expected22c = { 10, 5, 7, 9 };
        tests::compare("List22c", list22c, expected22c);
        tests::compare("List22c erase_if count", cnt22c, std::size_t{ 2 });

        dsa::List<int> list22d = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt22d = dsa::erase_if(list22d, [](int val) { return val > 5; });
        const std::initializer_list<int> expected22d = { 0, 2, 5 };
        tests::compare("List22d", list22d, expected22d);
        tests::compare("List22d erase_if count", cnt22d, std::size_t{ 3 });

        dsa::List<int> list22e = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt22e = dsa::erase_if(list22e, [](int val) { return val <= 5; });
        const std::initializer_list<int> expected22e = { 10, 7, 9 };
        tests::compare("List22e", list22e, expected22e);
        tests::compare("List22e erase_if count", cnt22e, std::size_t{ 3 });

        dsa::List<int> list22f = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt22f = dsa::erase_if(list22f, [](int val) { return val >= 5; });
        const std::initializer_list<int> expected22f = { 0, 2 };
        tests::compare("List22f", list22f, expected22f);
        tests::compare("List22f erase_if count", cnt22f, std::size_t{ 4 });

        dsa::List<int> list22g = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt22g = dsa::erase_if(list22g, [](int val) { return val < (-5); });
        const std::initializer_list<int> expected22g = { 0, 10, 2, 5, 7, 9 };
        tests::compare("List22g", list22g, expected22g);
        tests::compare("List22g erase_if count", cnt22g, std::size_t{ 0 });

        dsa::List<int> list22h = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt22h = dsa::erase_if(list22h, [](int val) { return val > (-5); });
        const std::initializer_list<int> expected22h = { };
        tests::compare("List22h", list22h, expected22h);
        tests::compare("List22h erase_if count", cnt22h, std::size_t{ 6 });

        dsa::List<int> list22i = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt22i = dsa::erase_if(list22i, [](int val) { return val <= (-5); });
        const std::initializer_list<int> expected22i = { 0, 10, 2, 5, 7, 9 };
        tests::compare("List22i", list22i, expected22i);
        tests::compare("List22i erase_if count", cnt22i, std::size_t{ 0 });

        dsa::List<int> list22j = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt22j = dsa::erase_if(list22j, [](int val) { return val >= (-5); });
        const std::initializer_list<int> expected22j = { };
        tests::compare("List22j", list22j, expected22j);
        tests::compare("List22j erase_if count", cnt22j, std::size_t{ 6 });

        dsa::List<int> list22k = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt22k = dsa::erase_if(list22k, [](int val) { return val < 100; });
        const std::initializer_list<int> expected22k = { };
        tests::compare("List22k", list22k, expected22k);
        tests::compare("List22k erase_if count", cnt22k, std::size_t{ 6 });

        dsa::List<int> list22l = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt22l = dsa::erase_if(list22l, [](int val) { return val > 100; });
        const std::initializer_list<int> expected22l = { 0, 10, 2, 5, 7, 9 };
        tests::compare("List22l", list22l, expected22l);
        tests::compare("List22l erase_if count", cnt22l, std::size_t{ 0 });

        dsa::List<int> list22m = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt22m = dsa::erase_if(list22m, [](int val) { return val <= 100; });
        const std::initializer_list<int> expected22m = { };
        tests::compare("List22m", list22m, expected22m);
        tests::compare("List22m erase_if count", cnt22m, std::size_t{ 6 });

        dsa::List<int> list22n = dsa::List<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt22n = dsa::erase_if(list22n, [](int val) { return val >= 100; });
        const std::initializer_list<int> expected22n = { 0, 10, 2, 5, 7, 9 };
        tests::compare("List22n", list22n, expected22n);
        tests::compare("List22n erase_if count", cnt22n, std::size_t{ 0 });

        dsa::List<int> list23a{};
        auto cnt23a = list23a.remove_if([](int val) { return val == 0; });
        const std::initializer_list<int> expected23a = { };
        tests::compare("List23a", list23a, expected23a);
        tests::compare("List23a removed count", cnt23a, std::size_t{ 0 });

        dsa::List<int> list23b{};
        auto cnt23b = list23b.remove_if([](int val) { return val != 0; });
        const std::initializer_list<int> expected23b = { };
        tests::compare("List23b", list23b, expected23b);
        tests::compare("List23b removed count", cnt23b, std::size_t{ 0 });

        dsa::List<int> list23c{};
        auto cnt23c = list23c.remove_if([](int val) { return val < 0; });
        const std::initializer_list<int> expected23c = { };
        tests::compare("List23c", list23c, expected23c);
        tests::compare("List23c removed count", cnt23c, std::size_t{ 0 });

        dsa::List<int> list23d{};
        auto cnt23d = list23d.remove_if([](int val) { return val > 0; });
        const std::initializer_list<int> expected23d = { };
        tests::compare("List23d", list23d, expected23d);
        tests::compare("List23d removed count", cnt23d, std::size_t{ 0 });

        dsa::List<int> list23e{};
        auto cnt23e = list23e.remove_if([](int val) { return val <= 0; });
        const std::initializer_list<int> expected23e = { };
        tests::compare("List23e", list23e, expected23e);
        tests::compare("List23e removed count", cnt23e, std::size_t{ 0 });

        dsa::List<int> list23f{};
        auto cnt23f = list23f.remove_if([](int val) { return val >= 0; });
        const std::initializer_list<int> expected23f = { };
        tests::compare("List23f", list23f, expected23f);
        tests::compare("List23f removed count", cnt23f, std::size_t{ 0 });

        dsa::List<int> list24{ 0, 1, 2, 3, 4, 5 };
        auto iter24 = list24.erase(std::next(list24.end()), std::next(list24.end()));
        tests::compare("iter24 == nullptr", iter24 == nullptr, true);
        iter24 = list24.erase(list24.begin(), std::next(list24.end()));
        tests::compare("iter24 == nullptr", iter24 == nullptr, true);


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list2{ 0, 10, 20, 30, 40, 50 };
        auto iter_start_2 = std_list2.begin();
        auto iter_end_2 = std_list2.begin();
        std::advance(iter_start_2, 1);
        std::advance(iter_end_2, 3);
        auto std_iter2 = std_list2.erase(iter_start_2, iter_end_2);
        tests::compare("List2 vs std", list2, std_list2);
        tests::compare("List2 iter vs std", *iter2, *std_iter2);

        std::list<int> std_list3{ 0, 10, 20, 30, 40, 50 };
        auto iter_start_3 = std_list3.begin();
        auto iter_end_3 = std_list3.begin();
        std::advance(iter_start_3, 1);
        std_list3.erase(iter_start_3);
        iter_start_3 = std_list3.begin();
        std::advance(iter_start_3, 1);
        std::advance(iter_end_3, 3);
        auto std_iter3 = std_list3.erase(iter_start_3, iter_end_3);
        tests::compare("List3 vs std", list3, std_list3);
        tests::compare("List3 iter vs std", *iter3 == *std_iter3, true);

        std::list<int> std_list4{ 0, 10, 20, 30, 40, 50 };
        auto iter_start_4 = std_list4.begin();
        auto iter_end_4 = std_list4.begin();
        std::advance(iter_start_4, 1);
        std_list4.erase(iter_start_4);
        iter_start_4 = std_list4.begin();
        iter_end_4 = std_list4.begin();
        std::advance(iter_start_4, 1);
        std::advance(iter_end_4, 4);
        auto std_iter4 = std_list4.erase(iter_start_4, iter_end_4);
        tests::compare("List4 vs std", list4, std_list4);
        tests::compare("List4 iter vs std", *iter4, *std_iter4);

        std::list<int> std_list8{ 0, 10, 0, 0, 40, 0 };
        std_list8.remove(0);
        tests::compare("List8 vs std", list8, std_list8);

        std::list<int> std_list9{ 0, 0, 0, 0, 0, 0 };
        std_list9.remove(0);
        tests::compare("List9 vs std", list9, std_list9);

        std::list<int> std_list10{ 0, 10, 0, 0, 40, 0 };
        auto std_cnt10 = std_list10.remove_if([](int val) { return val == 0; });
        tests::compare("List10 vs std", list10, std_list10);
        tests::compare("List10 removed count vs std", cnt10, std_cnt10);

        std::list<int> std_list11{ 0, 0, 0, 0, 0, 0 };
        auto std_cnt11 = std_list11.remove_if([](int val) { return val == 0; });
        tests::compare("List11 vs std", list11, std_list11);
        tests::compare("List11 removed count vs std", cnt11, std_cnt11);

        std::list<int> std_list12{ 0, 1, 2, 3, 4, 5 };
        auto std_cnt12 = std_list12.remove_if([](int val) { return val % 2 == 0; });
        tests::compare("List12 vs std", list12, std_list12);
        tests::compare("List12 removed count vs std", cnt12, std_cnt12);

        std::list<int> std_list13{ 0, 10, 2, 5, 7, 9 };
        auto std_cnt13 = std_list13.remove_if([](int val) { return val <= 5; });
        tests::compare("List13 vs std", list13, std_list13);
        tests::compare("List13 removed count vs std", cnt13, std_cnt13);

        std::list<int> std_list17{ 0, 10, 0, 0, 40, 0 };
        // Linter do not recognizes that functions std::erase/erase_if are included from std::list in C++20
        // NOLINTNEXTLINE(misc-include-cleaner,-warnings-as-errors)
        auto std_cnt17 = std::erase(std_list17, 0);
        tests::compare("List17 vs std", list17, std_list17);
        tests::compare("List17 removed count vs std", cnt17, std_cnt17);

        std::list<int> std_list18{ 0, 0, 0, 0, 0, 0 };
        // NOLINTNEXTLINE(misc-include-cleaner,-warnings-as-errors)
        auto std_cnt18 = std::erase(std_list18, 0);
        tests::compare("List18 vs std", list18, std_list18);
        tests::compare("List18 erase count vs std", cnt18, std_cnt18);

        std::list<int> std_list19{ 0, 10, 0, 0, 40, 0 };
        // NOLINTNEXTLINE(misc-include-cleaner,-warnings-as-errors)
        auto std_cnt19 = std::erase_if(std_list19, [](int val) { return val == 0; });
        tests::compare("List19 vs std", list19, std_list19);
        tests::compare("List19 erase count vs std", cnt19, std_cnt19);

        std::list<int> std_list20{ 0, 0, 0, 0, 0, 0 };
        // NOLINTNEXTLINE(misc-include-cleaner,-warnings-as-errors)
        auto std_cnt20 = std::erase_if(std_list20, [](int val) { return val == 0; });
        tests::compare("List20 vs std", list20, std_list20);
        tests::compare("List20 erase_if count vs std", cnt20, std_cnt20);

        std::list<int> std_list21{ 0, 1, 2, 3, 4, 5 };
        // NOLINTNEXTLINE(misc-include-cleaner,-warnings-as-errors)
        auto std_cnt21 = std::erase_if(std_list21, [](int val) { return val % 2 == 0; });
        tests::compare("List21 vs std", list21, std_list21);
        tests::compare("List21 erase_if count vs std", cnt21, std_cnt21);

        std::list<int> std_list22e{ 0, 10, 2, 5, 7, 9 };
        // NOLINTNEXTLINE(misc-include-cleaner,-warnings-as-errors)
        auto std_cnt22e = std::erase_if(std_list22e, [](int val) { return val <= 5; });
        tests::compare("List22e vs std", list22e, std_list22e);
        tests::compare("List22e erase_if count vs std", cnt22e, std_cnt22e);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}