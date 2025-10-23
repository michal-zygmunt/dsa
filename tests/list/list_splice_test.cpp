/**
 * @file list_splice_test.cpp
 * @brief This file tests functions splicing List objects
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
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <new>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start list_splice_test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };

        std::cout << "Testing moving other list\n\n";

        dsa::List<int> list1 = dsa::List<int>(il_1);
        dsa::List<int> list2 = dsa::List<int>(il_2);
        list1.splice(list1.begin(), list2);
        const std::initializer_list<int> expected1 = { 10, 20, 30, 40, 50, 1, 2, 3, 4, 5 };
        tests::compare("List1", list1, expected1);
        const std::initializer_list<int> expected2 = {};
        tests::compare("List2", list2, expected2);

        dsa::List<int> list3 = dsa::List<int>(il_1);
        dsa::List<int> list4 = dsa::List<int>(il_2);
        list3.splice(list3.begin()[3], list4);
        const std::initializer_list<int> expected3 = { 1, 2, 3, 10, 20, 30, 40, 50, 4, 5 };
        tests::compare("List3", list3, expected3);
        const std::initializer_list<int> expected4 = {};
        tests::compare("List4", list4, expected4);

        dsa::List<int> list5 = dsa::List<int>(il_1);
        dsa::List<int> list6 = dsa::List<int>(il_2);
        list5.splice(list5.begin()[list5.size() - 1], list6);
        const std::initializer_list<int> expected5 = { 1, 2, 3, 4, 10, 20, 30, 40, 50, 5 };
        tests::compare("List5", list5, expected5);
        const std::initializer_list<int> expected6 = {};
        tests::compare("List6", list6, expected6);


        std::cout << "Testing moving empty list\n\n";

        dsa::List<int> list7 = dsa::List<int>(il_1);
        dsa::List<int> list8;
        list7.splice(list7.begin()[list7.size() - 1], list8);
        const std::initializer_list<int> expected7 = il_1;
        tests::compare("List7", list7, expected7);
        const std::initializer_list<int> expected8 = {};
        tests::compare("List8", list8, expected8);


        std::cout << "Testing moving one element from other list\n\n";

        dsa::List<int> list9 = dsa::List<int>(il_1);
        dsa::List<int> list10 = dsa::List<int>(il_2);
        list9.splice(list9.begin(), list10, list10.begin());
        const std::initializer_list<int> expected9 = { 10, 1, 2, 3, 4, 5 };
        tests::compare("List9", list9, expected9);
        const std::initializer_list<int> expected10 = { 20, 30, 40, 50 };
        tests::compare("List10", list10, expected10);

        dsa::List<int> list11 = dsa::List<int>(il_1);
        dsa::List<int> list12 = dsa::List<int>(il_2);
        list11.splice(list11.begin(), list12, list12.begin()[2]);
        const std::initializer_list<int> expected11 = { 30, 1, 2, 3, 4, 5 };
        tests::compare("List11", list11, expected11);
        const std::initializer_list<int> expected12 = { 10, 20, 40, 50 };
        tests::compare("List12", list12, expected12);

        dsa::List<int> list13 = dsa::List<int>(il_1);
        dsa::List<int> list14 = dsa::List<int>(il_2);
        list13.splice(list13.begin(), list14, list14.begin()[list14.size() - 2]);
        const std::initializer_list<int> expected13 = { 40, 1, 2, 3, 4, 5 };
        tests::compare("List13", list13, expected13);
        const std::initializer_list<int> expected14 = { 10, 20, 30, 50 };
        tests::compare("List14", list14, expected14);


        dsa::List<int> list15 = dsa::List<int>(il_1);
        dsa::List<int> list16 = dsa::List<int>(il_2);
        list15.splice(list15.begin()[3], list16, list16.begin());
        const std::initializer_list<int> expected15 = { 1, 2, 3, 10, 4, 5 };
        tests::compare("List15", list15, expected15);
        const std::initializer_list<int> expected16 = { 20, 30, 40, 50 };
        tests::compare("List16", list16, expected16);

        dsa::List<int> list17 = dsa::List<int>(il_1);
        dsa::List<int> list18 = dsa::List<int>(il_2);
        list17.splice(list17.begin()[3], list18, list18.begin()[2]);
        const std::initializer_list<int> expected17 = { 1, 2, 3, 30, 4, 5 };
        tests::compare("List17", list17, expected17);
        const std::initializer_list<int> expected18 = { 10, 20, 40, 50 };
        tests::compare("List18", list18, expected18);

        dsa::List<int> list19 = dsa::List<int>(il_1);
        dsa::List<int> list20 = dsa::List<int>(il_2);
        list19.splice(list19.begin()[3], list20, list20.begin()[list20.size() - 2]);
        const std::initializer_list<int> expected19 = { 1, 2, 3, 40, 4, 5 };
        tests::compare("List19", list19, expected19);
        const std::initializer_list<int> expected20 = { 10, 20, 30, 50 };
        tests::compare("List20", list20, expected20);


        dsa::List<int> list21 = dsa::List<int>(il_1);
        dsa::List<int> list22 = dsa::List<int>(il_2);
        list21.splice(list21.begin()[list21.size() - 1], list22, list22.begin());
        const std::initializer_list<int> expected21 = { 1, 2, 3, 4, 10, 5 };
        tests::compare("List21", list21, expected21);
        const std::initializer_list<int> expected22 = { 20, 30, 40, 50 };
        tests::compare("List22", list22, expected22);

        dsa::List<int> list23 = dsa::List<int>(il_1);
        dsa::List<int> list24 = dsa::List<int>(il_2);
        list23.splice(list23.begin()[list23.size() - 1], list24, list24.begin()[3]);
        const std::initializer_list<int> expected23 = { 1, 2, 3, 4, 40, 5 };
        tests::compare("List23", list23, expected23);
        const std::initializer_list<int> expected24 = { 10, 20, 30, 50 };
        tests::compare("List24", list24, expected24);

        dsa::List<int> list25 = dsa::List<int>(il_1);
        dsa::List<int> list26 = dsa::List<int>(il_2);
        list25.splice(list25.begin()[list25.size() - 1], list26, list26.begin()[list26.size() - 2]);
        const std::initializer_list<int> expected25 = { 1, 2, 3, 4, 40, 5 };
        tests::compare("List25", list25, expected25);
        const std::initializer_list<int> expected26 = { 10, 20, 30, 50 };
        tests::compare("List26", list26, expected26);


        std::cout << "Testing moving range of element from other list\n\n";

        dsa::List<int> list27 = dsa::List<int>(il_1);
        dsa::List<int> list28 = dsa::List<int>(il_2);
        list27.splice(list27.begin(), list28, list28.begin(), list28.begin()[1]);
        const std::initializer_list<int> expected27 = { 10, 1, 2, 3, 4, 5 };
        tests::compare("List27", list27, expected27);
        const std::initializer_list<int> expected28 = { 20, 30, 40, 50 };
        tests::compare("List28", list28, expected28);

        dsa::List<int> list29 = dsa::List<int>(il_1);
        dsa::List<int> list30 = dsa::List<int>(il_2);
        list29.splice(list29.begin(), list30, list30.begin()[1], list30.begin()[3]);
        const std::initializer_list<int> expected29 = { 20, 30, 1, 2, 3, 4, 5 };
        tests::compare("List29", list29, expected29);
        const std::initializer_list<int> expected30 = { 10, 40, 50 };
        tests::compare("List30", list30, expected30);

        dsa::List<int> list31 = dsa::List<int>(il_1);
        dsa::List<int> list32 = dsa::List<int>(il_2);
        list31.splice(list31.begin(), list32, list32.begin(), list32.begin()[list32.size() - 1]);
        const std::initializer_list<int> expected31 = { 10, 20, 30, 40, 1, 2, 3, 4, 5 };
        tests::compare("List31", list31, expected31);
        const std::initializer_list<int> expected32 = { 50 };
        tests::compare("List32", list32, expected32);


        dsa::List<int> list33 = dsa::List<int>(il_1);
        dsa::List<int> list34 = dsa::List<int>(il_2);
        list33.splice(list33.begin()[2], list34, list34.begin(), list34.begin()[1]);
        const std::initializer_list<int> expected33 = { 1, 2, 10, 3, 4, 5 };
        tests::compare("List33", list33, expected33);
        const std::initializer_list<int> expected34 = { 20, 30, 40, 50 };
        tests::compare("List34", list34, expected34);

        dsa::List<int> list35 = dsa::List<int>(il_1);
        dsa::List<int> list36 = dsa::List<int>(il_2);
        list35.splice(list35.begin()[2], list36, list36.begin()[1], list36.begin()[3]);
        const std::initializer_list<int> expected35 = { 1, 2, 20, 30, 3, 4, 5 };
        tests::compare("List35", list35, expected35);
        const std::initializer_list<int> expected36 = { 10, 40, 50 };
        tests::compare("List36", list36, expected36);

        dsa::List<int> list37 = dsa::List<int>(il_1);
        dsa::List<int> list38 = dsa::List<int>(il_2);
        list37.splice(list37.begin()[2], list38, list38.begin(), list38.begin()[list38.size() - 1]);
        const std::initializer_list<int> expected37 = { 1, 2, 10, 20, 30, 40, 3, 4, 5 };
        tests::compare("List37", list37, expected37);
        const std::initializer_list<int> expected38 = { 50 };
        tests::compare("List38", list38, expected38);


        dsa::List<int> list39 = dsa::List<int>(il_1);
        dsa::List<int> list40 = dsa::List<int>(il_2);
        list39.splice(list39.begin()[list39.size() - 1], list40, list40.begin(), list40.begin()[1]);
        const std::initializer_list<int> expected39 = { 1, 2, 3, 4, 10, 5 };
        tests::compare("List39", list39, expected39);
        const std::initializer_list<int> expected40 = { 20, 30, 40, 50 };
        tests::compare("List40", list40, expected40);

        dsa::List<int> list41 = dsa::List<int>(il_1);
        dsa::List<int> list42 = dsa::List<int>(il_2);
        list41.splice(list41.begin()[list41.size() - 1], list42, list42.begin()[1], list42.begin()[3]);
        const std::initializer_list<int> expected41 = { 1, 2, 3, 4, 20, 30, 5 };
        tests::compare("List41", list41, expected41);
        const std::initializer_list<int> expected42 = { 10, 40, 50 };
        tests::compare("List42", list42, expected42);

        dsa::List<int> list43 = dsa::List<int>(il_1);
        dsa::List<int> list44 = dsa::List<int>(il_2);
        list43.splice(list43.begin()[list43.size() - 1], list44, list44.begin(), list44.begin()[list44.size() - 1]);
        const std::initializer_list<int> expected43 = { 1, 2, 3, 4, 10, 20, 30, 40, 5 };
        tests::compare("List43", list43, expected43);
        const std::initializer_list<int> expected44 = { 50 };
        tests::compare("List44", list44, expected44);

        dsa::List<int> list45 = dsa::List<int>(il_1);
        dsa::List<int> list46 = dsa::List<int>(il_2);
        list45.splice(list45.begin()[list45.size()], list46, list46.begin(), list46.begin()[list46.size() - 1]);
        const std::initializer_list<int> expected45 = { 1, 2, 3, 4, 5, 10, 20, 30, 40 };
        tests::compare("List45", list45, expected45);
        const std::initializer_list<int> expected46 = { 50 };
        tests::compare("List46", list46, expected46);

        dsa::List<int> list47 = dsa::List<int>(il_1);
        dsa::List<int> list48 = dsa::List<int>(il_2);
        list47.splice(list47.begin()[list47.size() - 1], list48, list48.begin(), list48.begin()[list48.size()]);
        const std::initializer_list<int> expected47 = { 1, 2, 3, 4, 10, 20, 30, 40, 50, 5 };
        tests::compare("List47", list47, expected47);
        const std::initializer_list<int> expected48 = {};
        tests::compare("List48", list48, expected48);

        dsa::List<int> list49 = dsa::List<int>(il_1);
        dsa::List<int> list50 = dsa::List<int>(il_2);
        list49.splice(list49.begin()[list49.size()], list50, list50.begin(), list50.begin()[list50.size()]);
        const std::initializer_list<int> expected49 = { 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
        tests::compare("List49", list49, expected49);
        const std::initializer_list<int> expected50 = {};
        tests::compare("List50", list50, expected50);


        std::cout << "Compare operations results with std container\n\n";

        dsa::List<int> list51{ il_1 };
        dsa::List<int> list52{ il_2 };
        list51.splice(list51.begin(), list52, list52.begin(), list52.end());
        std::list<int> expected51{ il_1 };
        std::list<int> expected52{ il_2 };
        expected51.splice(expected51.begin(), expected52, expected52.begin(), expected52.end());
        tests::compare("List51 vs std", list51, expected51);
        tests::compare("List52 vs std", list52, expected52);

        dsa::List<int> list53{ il_1 };
        dsa::List<int> list54{ il_2 };
        list53.splice(list53.end(), list54, list54.begin(), list54.end());
        std::list<int> expected53{ il_1 };
        std::list<int> expected54{ il_2 };
        expected53.splice(expected53.end(), expected54, expected54.begin(), expected54.end());
        tests::compare("List53 vs std", list53, expected53);
        tests::compare("List54 vs std", list54, expected54);

        dsa::List<int> list55{ il_1 };
        dsa::List<int> list56{ il_2 };
        constexpr int dist = 3;
        auto iter_list55 = list55.begin();
        std::advance(iter_list55, dist);
        list55.splice(iter_list55, list56, list56.begin(), list56.end());
        std::list<int> expected55{ il_1 };
        std::list<int> expected56{ il_2 };
        auto iter_expected55 = expected55.begin();
        std::advance(iter_expected55, dist);
        expected55.splice(iter_expected55, expected56, expected56.begin(), expected56.end());
        tests::compare("List55 vs std", list55, expected55);
        tests::compare("List56 vs std", list56, expected56);

        dsa::List<int> list57{ il_1 };
        dsa::List<int> list58{ il_2 };
        auto iter_list58 = list58.begin();
        std::advance(iter_list58, dist);
        list57.splice(list57.begin(), list58, list58.begin(), iter_list58);
        std::list<int> expected57{ il_1 };
        std::list<int> expected58{ il_2 };
        auto std_iter = expected58.begin();
        std::advance(std_iter, dist);
        expected57.splice(expected57.begin(), expected58, expected58.begin(), std_iter);
        tests::compare("List57 vs std", list57, expected57);
        tests::compare("List58 vs std", list58, expected58);

        dsa::List<int> list59{ il_1 };
        dsa::List<int> list60{ il_2 };
        auto iter_list59 = list59.begin();
        std::advance(iter_list59, dist);
        auto iter_list60 = list60.begin();
        std::advance(iter_list60, dist);
        list59.splice(iter_list59, list60, list60.begin(), iter_list60);
        std::list<int> expected59{ il_1 };
        std::list<int> expected60{ il_2 };
        auto iter_expected59 = expected59.begin();
        std::advance(iter_expected59, dist);
        auto iter_expected60 = expected60.begin();
        std::advance(iter_expected60, dist);
        expected59.splice(iter_expected59, expected60, expected60.begin(), iter_expected60);
        tests::compare("List59 vs std", list59, expected59);
        tests::compare("List60 vs std", list60, expected60);


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
