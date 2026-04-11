/**
 * @file list_merge_test.cpp
 * @brief This file tests functions merging List objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/list.h"

#include <exception>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <list>
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start list_merge_test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };
        const std::initializer_list<int> il_3{ 1, 1, 3, 5, 7 };
        const std::initializer_list<int> il_4{ 1, 2, 4, 6, 9 };

        dsa::List<int> list1 = dsa::List<int>(il_1);
        dsa::List<int> list2 = dsa::List<int>(il_2);
        list1.merge(list2);
        const std::initializer_list<int> expected1 = { 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
        tests::compare("List1", list1, expected1);
        const std::initializer_list<int> expected2 = {};
        tests::compare("List2", list2, expected2);

        dsa::List<int> list3 = dsa::List<int>(il_1);
        dsa::List<int> list4;
        list4.merge(list3);
        const std::initializer_list<int> expected3 = { };
        tests::compare("List3", list3, expected3);
        const std::initializer_list<int> expected4 = il_1;
        tests::compare("List4", list4, expected4);

        dsa::List<int> list5 = dsa::List<int>(il_3);
        dsa::List<int> list6 = dsa::List<int>(il_4);
        list5.merge(list6);
        const std::initializer_list<int> expected5 = { 1, 1, 1, 2, 3, 4, 5, 6, 7, 9 };
        tests::compare("List5", list5, expected5);
        const std::initializer_list<int> expected6 = {};
        tests::compare("List6", list6, expected6);

        dsa::List<int> list7 = dsa::List<int>(il_4);
        dsa::List<int> list8 = dsa::List<int>(il_3);
        list7.merge(list8);
        const std::initializer_list<int> expected7 = { 1, 1, 1, 2, 3, 4, 5, 6, 7, 9 };
        tests::compare("List7", list7, expected7);
        const std::initializer_list<int> expected8 = {};
        tests::compare("List8", list8, expected8);

        dsa::List<int> list9 = dsa::List<int>(il_2);
        dsa::List<int> list10 = dsa::List<int>(il_3);
        list9.merge(list10);
        const std::initializer_list<int> expected9 = { 1, 1, 3, 5, 7, 10, 20, 30, 40, 50 };
        tests::compare("List9", list9, expected9);
        const std::initializer_list<int> expected10 = {};
        tests::compare("List10", list10, expected10);

        dsa::List<int> list11 = dsa::List<int>(il_3);
        dsa::List<int> list12 = dsa::List<int>(il_2);
        list11.merge(std::move(list12));
        const std::initializer_list<int> expected11 = { 1, 1, 3, 5, 7, 10, 20, 30, 40, 50 };
        tests::compare("List11", list11, expected11);
        const std::initializer_list<int> expected12 = {};
        // NOLINTNEXTLINE(bugprone-use-after-move)
        tests::compare("List12", list12, expected12);

        // merging using non default compration argument

        dsa::List<int> list13 = dsa::List<int>(il_1);
        dsa::List<int> list14 = dsa::List<int>(il_2);
        list13.sort(std::greater<>());
        list14.sort(std::greater<>());
        list13.merge(list14, std::greater<>());
        const std::initializer_list<int> expected13 = { 50, 40, 30, 20, 10, 5, 4, 3, 2, 1 };
        tests::compare("List13", list13, expected13);
        const std::initializer_list<int> expected14 = {};
        tests::compare("List14", list14, expected14);

        dsa::List<int> list15 = dsa::List<int>(il_1);
        dsa::List<int> list16;
        list15.sort(std::greater<>());
        list16.sort(std::greater<>());
        list16.merge(list15, std::greater<>());
        const std::initializer_list<int> expected15{};
        tests::compare("List15", list15, expected15);
        const std::initializer_list<int> expected16{ 5, 4, 3, 2, 1 };
        tests::compare("List16", list16, expected16);

        dsa::List<int> list17 = dsa::List<int>(il_3);
        dsa::List<int> list18 = dsa::List<int>(il_4);
        list17.sort(std::greater<>());
        list18.sort(std::greater<>());
        list17.merge(list18, std::greater<>());
        const std::initializer_list<int> expected17{ 9, 7, 6, 5, 4, 3, 2, 1, 1, 1 };
        tests::compare("List17", list17, expected17);
        const std::initializer_list<int> expected18{};
        tests::compare("List18", list18, expected18);

        dsa::List<int> list19 = dsa::List<int>(il_4);
        dsa::List<int> list20 = dsa::List<int>(il_3);
        list19.sort(std::greater<>());
        list20.sort(std::greater<>());
        list19.merge(list20, std::greater<>());
        const std::initializer_list<int> expected19{ 9, 7, 6, 5, 4, 3, 2, 1, 1, 1 };
        tests::compare("List19", list19, expected19);
        const std::initializer_list<int> expected20{};
        tests::compare("List20", list20, expected20);

        dsa::List<int> list21 = dsa::List<int>(il_2);
        dsa::List<int> list22 = dsa::List<int>(il_3);
        list21.sort(std::greater<>());
        list22.sort(std::greater<>());
        list21.merge(list22, std::greater<>());
        const std::initializer_list<int> expected21{ 50, 40, 30, 20, 10, 7, 5, 3, 1, 1 };
        tests::compare("List21", list21, expected21);
        const std::initializer_list<int> expected22{};
        tests::compare("List22", list22, expected22);

        dsa::List<int> list23 = dsa::List<int>(il_3);
        dsa::List<int> list24 = dsa::List<int>(il_2);
        list23.sort(std::greater<>());
        list24.sort(std::greater<>());
        list23.merge(std::move(list24), std::greater<>());
        const std::initializer_list<int> expected23{ 50, 40, 30, 20, 10, 7, 5, 3, 1, 1 };
        tests::compare("List23", list23, expected23);
        const std::initializer_list<int> expected24{};
        // NOLINTNEXTLINE(bugprone-use-after-move)
        tests::compare("List24", list24, expected24);

        // self merge
        dsa::List<int> list25{ il_1 };
        list25.merge(list25);
        tests::compare("List25", list25, il_1);

        dsa::List<int> list26;
        list26.merge(list26);
        tests::compare("List26", list26, {});


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list1{ il_1 };
        std::list<int> std_list2{ il_2 };
        std_list1.merge(std_list2);
        tests::compare("List1 vs std", list1, std_list1);
        tests::compare("List2 vs std", list2, std_list2);

        std::list<int> std_list3{ il_1 };
        std::list<int> std_list4;
        std_list4.merge(std_list3);
        tests::compare("List3 vs std", list3, std_list3);
        tests::compare("List4 vs std", list4, std_list4);

        std::list<int> std_list5{ il_3 };
        std::list<int> std_list6{ il_4 };
        std_list5.merge(std_list6);
        tests::compare("List5 vs std", list5, std_list5);
        tests::compare("List6 vs std", list6, std_list6);

        std::list<int> std_list7{ il_4 };
        std::list<int> std_list8{ il_3 };
        std_list7.merge(std_list8);
        tests::compare("List7 vs std", list7, std_list7);
        tests::compare("List8 vs std", list8, std_list8);

        std::list<int> std_list9{ il_2 };
        std::list<int> std_list10{ il_3 };
        std_list9.merge(std_list10);
        tests::compare("List9 vs std", list9, std_list9);
        tests::compare("List10 vs std", list10, std_list10);

        std::list<int> std_list11{ il_3 };
        std::list<int> std_list12{ il_2 };
        std_list11.merge(std::move(std_list12));
        tests::compare("List11 vs std", list11, std_list11);
        // NOLINTNEXTLINE(bugprone-use-after-move)
        tests::compare("List12 vs std", list12, std_list12);

        // merging using non default compration argument

        std::list<int> std_list13{ il_1 };
        std::list<int> std_list14{ il_2 };
        std_list13.sort(std::greater<>());
        std_list14.sort(std::greater<>());
        std_list13.merge(std_list14, std::greater<>());
        tests::compare("List13 vs std", list13, std_list13);
        tests::compare("List14 vs std", list14, std_list14);

        std::list<int> std_list15{ il_1 };
        std::list<int> std_list16;
        std_list15.sort(std::greater<>());
        std_list16.sort(std::greater<>());
        std_list16.merge(std_list15, std::greater<>());
        tests::compare("List15 vs std", list15, std_list15);
        tests::compare("List16 vs std", list16, std_list16);

        std::list<int> std_list17{ il_3 };
        std::list<int> std_list18{ il_4 };
        std_list17.sort(std::greater<>());
        std_list18.sort(std::greater<>());
        std_list17.merge(std_list18, std::greater<>());
        tests::compare("List17 vs std", list17, std_list17);
        tests::compare("List18 vs std", list18, std_list18);

        std::list<int> std_list19{ il_4 };
        std::list<int> std_list20{ il_3 };
        std_list19.sort(std::greater<>());
        std_list20.sort(std::greater<>());
        std_list19.merge(std_list20, std::greater<>());
        tests::compare("List19 vs std", list19, std_list19);
        tests::compare("List20 vs std", list20, std_list20);

        std::list<int> std_list21{ il_2 };
        std::list<int> std_list22{ il_3 };
        std_list21.sort(std::greater<>());
        std_list22.sort(std::greater<>());
        std_list21.merge(std_list22, std::greater<>());
        tests::compare("List21 vs std", list21, std_list21);
        tests::compare("List22 vs std", list22, std_list22);

        std::list<int> std_list23{ il_3 };
        std::list<int> std_list24{ il_2 };
        std_list23.sort(std::greater<>());
        std_list24.sort(std::greater<>());
        std_list23.merge(std::move(std_list24), std::greater<>());
        tests::compare("List23 vs std", list23, std_list23);
        // NOLINTNEXTLINE(bugprone-use-after-move)
        tests::compare("List24 vs std", list24, std_list24);

        // self merge
        std::list<int> std_list25{ il_1 };
        std_list25.merge(std_list25);
        tests::compare("List25 vs std", list25, std_list25);

        std::list<int> std_list26;
        std_list26.merge(std_list26);
        tests::compare("List26 vs std", list26, std_list26);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
