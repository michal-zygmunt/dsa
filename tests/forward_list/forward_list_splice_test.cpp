/**
 * @file forward_list_splice_test.cpp
 * @brief This file tests functions splicing ForwardList objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/forward_list.h"

#include <exception>
#include <forward_list>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <new>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start forward_list_splice_test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };

        std::cout << "Testing moving other list\n\n";

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list2 = dsa::ForwardList<int>(il_2);
        list1.splice_after(list1.begin(), list2);
        const std::initializer_list<int> expected1 = { 1, 10, 20, 30, 40, 50, 2, 3, 4, 5 };
        tests::compare("ForwardList1", list1, expected1);
        const std::initializer_list<int> expected2 = {};
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list4 = dsa::ForwardList<int>(il_2);
        list3.splice_after(list3.begin()[3], list4);
        const std::initializer_list<int> expected3 = { 1, 2, 3, 4, 10, 20, 30, 40, 50, 5 };
        tests::compare("ForwardList3", list3, expected3);
        const std::initializer_list<int> expected4 = {};
        tests::compare("ForwardList4", list4, expected4);

        dsa::ForwardList<int> list5 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list6 = dsa::ForwardList<int>(il_2);
        list5.splice_after(list5.begin()[list5.size() - 1], list6);
        const std::initializer_list<int> expected5 = { 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
        tests::compare("ForwardList5", list5, expected5);
        const std::initializer_list<int> expected6 = {};
        tests::compare("ForwardList6", list6, expected6);

        std::cout << "Testing moving empty list\n\n";

        dsa::ForwardList<int> list7 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list8;
        list7.splice_after(list7.begin()[list7.size() - 1], list8);
        const std::initializer_list<int> expected7 = il_1;
        tests::compare("ForwardList7", list7, expected7);
        const std::initializer_list<int> expected8 = {};
        tests::compare("ForwardList8", list8, expected8);

        std::cout << "Testing moving one element from other list\n\n";

        dsa::ForwardList<int> list9 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list10 = dsa::ForwardList<int>(il_2);
        list9.splice_after(list9.begin(), list10, list10.begin());
        const std::initializer_list<int> expected9 = { 1, 20, 2, 3, 4, 5 };
        tests::compare("ForwardList9", list9, expected9);
        const std::initializer_list<int> expected10 = { 10, 30, 40, 50 };
        tests::compare("ForwardList10", list10, expected10);

        dsa::ForwardList<int> list11 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list12 = dsa::ForwardList<int>(il_2);
        list11.splice_after(list11.begin(), list12, list12.begin()[2]);
        const std::initializer_list<int> expected11 = { 1, 40, 2, 3, 4, 5 };
        tests::compare("ForwardList11", list11, expected11);
        const std::initializer_list<int> expected12 = { 10, 20, 30, 50 };
        tests::compare("ForwardList12", list12, expected12);

        dsa::ForwardList<int> list13 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list14 = dsa::ForwardList<int>(il_2);
        list13.splice_after(list13.begin(), list14, list14.begin()[list14.size() - 2]);
        const std::initializer_list<int> expected13 = { 1, 50, 2, 3, 4, 5 };
        tests::compare("ForwardList13", list13, expected13);
        const std::initializer_list<int> expected14 = { 10, 20, 30, 40 };
        tests::compare("ForwardList14", list14, expected14);

        dsa::ForwardList<int> list15 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list16 = dsa::ForwardList<int>(il_2);
        list15.splice_after(list15.begin()[3], list16, list16.begin());
        const std::initializer_list<int> expected15 = { 1, 2, 3, 4, 20, 5 };
        tests::compare("ForwardList15", list15, expected15);
        const std::initializer_list<int> expected16 = { 10, 30, 40, 50 };
        tests::compare("ForwardList16", list16, expected16);

        dsa::ForwardList<int> list17 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list18 = dsa::ForwardList<int>(il_2);
        list17.splice_after(list17.begin()[3], list18, list18.begin()[2]);
        const std::initializer_list<int> expected17 = { 1, 2, 3, 4, 40, 5 };
        tests::compare("ForwardList17", list17, expected17);
        const std::initializer_list<int> expected18 = { 10, 20, 30, 50 };
        tests::compare("ForwardList18", list18, expected18);

        dsa::ForwardList<int> list19 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list20 = dsa::ForwardList<int>(il_2);
        list19.splice_after(list19.begin()[3], list20, list20.begin()[list20.size() - 2]);
        const std::initializer_list<int> expected19 = { 1, 2, 3, 4, 50, 5 };
        tests::compare("ForwardList19", list19, expected19);
        const std::initializer_list<int> expected20 = { 10, 20, 30, 40 };
        tests::compare("ForwardList20", list20, expected20);


        dsa::ForwardList<int> list21 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list22 = dsa::ForwardList<int>(il_2);
        list21.splice_after(list21.begin()[list21.size() - 1], list22, list22.begin());
        const std::initializer_list<int> expected21 = { 1, 2, 3, 4, 5, 20 };
        tests::compare("ForwardList21", list21, expected21);
        const std::initializer_list<int> expected22 = { 10, 30, 40, 50 };
        tests::compare("ForwardList22", list22, expected22);

        dsa::ForwardList<int> list23 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list24 = dsa::ForwardList<int>(il_2);
        list23.splice_after(list23.begin()[list23.size() - 1], list24, list24.begin()[3]);
        const std::initializer_list<int> expected23 = { 1, 2, 3, 4, 5, 50 };
        tests::compare("ForwardList23", list23, expected23);
        const std::initializer_list<int> expected24 = { 10, 20, 30, 40 };
        tests::compare("ForwardList24", list24, expected24);

        dsa::ForwardList<int> list25 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list26 = dsa::ForwardList<int>(il_2);
        list25.splice_after(list25.begin()[list25.size() - 1], list26, list26.begin()[list26.size() - 2]);
        const std::initializer_list<int> expected25 = { 1, 2, 3, 4, 5, 50 };
        tests::compare("ForwardList25", list25, expected25);
        const std::initializer_list<int> expected26 = { 10, 20, 30, 40 };
        tests::compare("ForwardList26", list26, expected26);


        std::cout << "Testing moving range of element from other list\n\n";

        dsa::ForwardList<int> list27 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list28 = dsa::ForwardList<int>(il_2);
        list27.splice_after(list27.begin(), list28, list28.begin(), list28.begin()[1]);
        const std::initializer_list<int> expected27 = { 1, 2, 3, 4, 5 };
        tests::compare("ForwardList27", list27, expected27);
        const std::initializer_list<int> expected28 = { 10, 20, 30, 40, 50 };
        tests::compare("ForwardList28", list28, expected28);

        dsa::ForwardList<int> list29 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list30 = dsa::ForwardList<int>(il_2);
        list29.splice_after(list29.begin(), list30, list30.begin()[1], list30.begin()[3]);
        const std::initializer_list<int> expected29 = { 1, 30, 2, 3, 4, 5 };
        tests::compare("ForwardList29", list29, expected29);
        const std::initializer_list<int> expected30 = { 10, 20, 40, 50 };
        tests::compare("ForwardList30", list30, expected30);

        dsa::ForwardList<int> list31 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list32 = dsa::ForwardList<int>(il_2);
        list31.splice_after(list31.begin(), list32, list32.begin(), list32.begin()[list32.size() - 1]);
        const std::initializer_list<int> expected31 = { 1, 20, 30, 40, 2, 3, 4, 5 };
        tests::compare("ForwardList31", list31, expected31);
        const std::initializer_list<int> expected32 = { 10, 50 };
        tests::compare("ForwardList32", list32, expected32);


        dsa::ForwardList<int> list33 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list34 = dsa::ForwardList<int>(il_2);
        list33.splice_after(list33.begin()[2], list34, list34.begin(), list34.begin()[1]);
        const std::initializer_list<int> expected33 = { 1, 2, 3, 4, 5 };
        tests::compare("ForwardList33", list33, expected33);
        const std::initializer_list<int> expected34 = { 10, 20, 30, 40, 50 };
        tests::compare("ForwardList34", list34, expected34);

        dsa::ForwardList<int> list35 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list36 = dsa::ForwardList<int>(il_2);
        list35.splice_after(list35.begin()[2], list36, list36.begin()[1], list36.begin()[3]);
        const std::initializer_list<int> expected35 = { 1, 2, 3, 30, 4, 5 };
        tests::compare("ForwardList35", list35, expected35);
        const std::initializer_list<int> expected36 = { 10, 20, 40, 50 };
        tests::compare("ForwardList36", list36, expected36);

        dsa::ForwardList<int> list37 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list38 = dsa::ForwardList<int>(il_2);
        list37.splice_after(list37.begin()[2], list38, list38.begin(), list38.begin()[list38.size() - 1]);
        const std::initializer_list<int> expected37 = { 1, 2, 3, 20, 30, 40, 4, 5 };
        tests::compare("ForwardList37", list37, expected37);
        const std::initializer_list<int> expected38 = { 10, 50 };
        tests::compare("ForwardList38", list38, expected38);


        dsa::ForwardList<int> list39 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list40 = dsa::ForwardList<int>(il_2);
        list39.splice_after(list39.begin()[list39.size() - 1], list40, list40.begin(), list40.begin()[1]);
        const std::initializer_list<int> expected39 = { 1, 2, 3, 4, 5 };
        tests::compare("ForwardList39", list39, expected39);
        const std::initializer_list<int> expected40 = { 10, 20, 30, 40, 50 };
        tests::compare("ForwardList40", list40, expected40);

        dsa::ForwardList<int> list41 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list42 = dsa::ForwardList<int>(il_2);
        list41.splice_after(list41.begin()[list41.size() - 1], list42, list42.begin()[1], list42.begin()[3]);
        const std::initializer_list<int> expected41 = { 1, 2, 3, 4, 5, 30 };
        tests::compare("ForwardList41", list41, expected41);
        const std::initializer_list<int> expected42 = { 10, 20, 40, 50 };
        tests::compare("ForwardList42", list42, expected42);

        dsa::ForwardList<int> list43 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list44 = dsa::ForwardList<int>(il_2);
        list43.splice_after(list43.begin()[list43.size() - 1], list44, list44.begin(), list44.begin()[list44.size() - 1]);
        const std::initializer_list<int> expected43 = { 1, 2, 3, 4, 5, 20, 30, 40 };
        tests::compare("ForwardList43", list43, expected43);
        const std::initializer_list<int> expected44 = { 10, 50 };
        tests::compare("ForwardList44", list44, expected44);


        dsa::ForwardList<int> list45 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list46 = dsa::ForwardList<int>(il_2);
        list45.splice_after(list45.before_begin(), list46, list46.begin(), list46.begin()[list46.size() - 1]);
        const std::initializer_list<int> expected45 = { 20, 30, 40, 1, 2, 3, 4, 5 };
        tests::compare("ForwardList45", list45, expected45);
        const std::initializer_list<int> expected46 = { 10, 50 };
        tests::compare("ForwardList46", list46, expected46);

        dsa::ForwardList<int> list47 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list48 = dsa::ForwardList<int>(il_2);
        list47.splice_after(list47.before_begin()[list47.size() - 1], list48, list48.begin(), list48.end());
        const std::initializer_list<int> expected47 = { 1, 2, 3, 4, 20, 30, 40, 50, 5 };
        tests::compare("ForwardList47", list47, expected47);
        const std::initializer_list<int> expected48 = { 10 };
        tests::compare("ForwardList48", list48, expected48);

        dsa::ForwardList<int> list49 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list50 = dsa::ForwardList<int>(il_2);
        list49.splice_after(list49.before_begin()[list49.size()], list50, list50.before_begin(), list50.end());
        const std::initializer_list<int> expected49 = { 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
        tests::compare("ForwardList49", list49, expected49);
        const std::initializer_list<int> expected50 = {};
        tests::compare("ForwardList50", list50, expected50);


        std::cout << "Compare operations results with std container\n\n";

        dsa::ForwardList<int> list51{ il_1 };
        dsa::ForwardList<int> list52{ il_2 };
        list51.splice_after(list51.begin(), list52, list52.begin(), list52.end());
        std::forward_list<int> expected51{ il_1 };
        std::forward_list<int> expected52{ il_2 };
        expected51.splice_after(expected51.begin(), expected52, expected52.begin(), expected52.end());
        tests::compare("ForwardList51 vs std", list51, expected51);
        tests::compare("ForwardList52 vs std", list52, expected52);

        dsa::ForwardList<int> list53{ il_1 };
        dsa::ForwardList<int> list54{ il_2 };
        list53.splice_after(list53.begin(), list54, list54.before_begin(), list54.end());
        std::forward_list<int> expected53{ il_1 };
        std::forward_list<int> expected54{ il_2 };
        expected53.splice_after(expected53.begin(), expected54, expected54.before_begin(), expected54.end());
        tests::compare("ForwardList53 vs std", list53, expected53);
        tests::compare("ForwardList54 vs std", list54, expected54);

        dsa::ForwardList<int> list55{ il_1 };
        dsa::ForwardList<int> list56{ il_2 };
        list55.splice_after(list55.before_begin(), list56, list56.before_begin(), list56.end());
        std::forward_list<int> expected55{ il_1 };
        std::forward_list<int> expected56{ il_2 };
        expected55.splice_after(expected55.before_begin(), expected56, expected56.before_begin(), expected56.end());
        tests::compare("ForwardList55 vs std", list55, expected55);
        tests::compare("ForwardList56 vs std", list56, expected56);

        dsa::ForwardList<int> list57{ il_1 };
        dsa::ForwardList<int> list58{ il_2 };
        constexpr int dist = 3;
        auto iter_list58 = list58.begin();
        std::advance(iter_list58, dist);
        list57.splice_after(list57.begin(), list58, list58.begin(), iter_list58);
        std::forward_list<int> expected57{ il_1 };
        std::forward_list<int> expected58{ il_2 };
        auto iter_expected57 = expected58.begin();
        std::advance(iter_expected57, dist);
        expected57.splice_after(expected57.begin(), expected58, expected58.begin(), iter_expected57);
        tests::compare("ForwardList57 vs std", list57, expected57);
        tests::compare("ForwardList58 vs std", list58, expected58);

        dsa::ForwardList<int> list59{ il_1 };
        dsa::ForwardList<int> list60{ il_2 };
        auto iter_list59 = list59.begin();
        std::advance(iter_list59, dist);
        auto iter_list60 = list60.begin();
        std::advance(iter_list60, dist);
        list59.splice_after(iter_list59, list60, list60.begin(), iter_list60);
        std::forward_list<int> expected59{ il_1 };
        std::forward_list<int> expected60{ il_2 };
        auto iter_expected59 = expected59.begin();
        std::advance(iter_expected59, dist);
        auto iter_expected60 = expected60.begin();
        std::advance(iter_expected60, dist);
        expected59.splice_after(iter_expected59, expected60, expected60.begin(), iter_expected60);
        tests::compare("ForwardList59 vs std", list59, expected59);
        tests::compare("ForwardList60 vs std", list60, expected60);


        tests::print_stats();
    }
    catch (const std::bad_alloc& exception)
    {
        tests::print_err_msg("Caught std::bad_alloc: ", &exception);
        return 1;
    }
    catch (const std::runtime_error& exception)
    {
        tests::print_err_msg("Caught std::runtime_error: ", &exception);
        return 2;
    }
    catch (const std::exception& exception)
    {
        tests::print_err_msg("Caught exception: ", &exception);
        return 3;
    }
    catch (...)
    {
        tests::print_err_msg("Unhandled unknown exception");
        return 4;
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
