/**
 * @file ListGrow.cpp
 * @brief This file tests functions splicing List objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/List.h"

#include <initializer_list>
#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    std::cout << "Start ListSplice test:\n";

    std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
    std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };

    std::cout << "Testing moving other list\n\n";

    dsa::List<int> list1 = dsa::List<int>(il_1);
    dsa::List<int> list2 = dsa::List<int>(il_2);
    list1.splice(list1.begin(), list2);
    std::initializer_list<int> expected1 = { 10, 20, 30, 40, 50, 1, 2, 3, 4, 5 };
    tests::compare("List1", list1, expected1);
    std::initializer_list<int> expected2 = {};
    tests::compare("List2", list2, expected2);

    dsa::List<int> list3 = dsa::List<int>(il_1);
    dsa::List<int> list4 = dsa::List<int>(il_2);
    list3.splice(list3.begin()[3], list4);
    std::initializer_list<int> expected3 = { 1, 2, 3, 10, 20, 30, 40, 50, 4, 5 };
    tests::compare("List3", list3, expected3);
    std::initializer_list<int> expected4 = {};
    tests::compare("List4", list4, expected4);

    dsa::List<int> list5 = dsa::List<int>(il_1);
    dsa::List<int> list6 = dsa::List<int>(il_2);
    list5.splice(list5.begin()[list5.size() - 1], list6);
    std::initializer_list<int> expected5 = { 1, 2, 3, 4, 10, 20, 30, 40, 50, 5 };
    tests::compare("List5", list5, expected5);
    std::initializer_list<int> expected6 = {};
    tests::compare("List6", list6, expected6);


    std::cout << "Testing moving empty list\n\n";

    dsa::List<int> list7 = dsa::List<int>(il_1);
    dsa::List<int> list8;
    list7.splice(list7.begin()[list7.size() - 1], list8);
    std::initializer_list<int> expected7 = il_1;
    tests::compare("List7", list7, expected7);
    std::initializer_list<int> expected8 = {};
    tests::compare("List8", list8, expected8);


    std::cout << "Testing moving one element from other list\n\n";

    dsa::List<int> list9 = dsa::List<int>(il_1);
    dsa::List<int> list10 = dsa::List<int>(il_2);
    list9.splice(list9.begin(), list10, list10.begin());
    std::initializer_list<int> expected9 = { 10, 1, 2, 3, 4, 5 };
    tests::compare("List9", list9, expected9);
    std::initializer_list<int> expected10 = { 20, 30, 40, 50 };
    tests::compare("List10", list10, expected10);

    dsa::List<int> list11 = dsa::List<int>(il_1);
    dsa::List<int> list12 = dsa::List<int>(il_2);
    list11.splice(list11.begin(), list12, list12.begin()[2]);
    std::initializer_list<int> expected11 = { 30, 1, 2, 3, 4, 5 };
    tests::compare("List11", list11, expected11);
    std::initializer_list<int> expected12 = { 10, 20, 40, 50 };
    tests::compare("List12", list12, expected12);

    dsa::List<int> list13 = dsa::List<int>(il_1);
    dsa::List<int> list14 = dsa::List<int>(il_2);
    list13.splice(list13.begin(), list14, list14.begin()[list14.size() - 2]);
    std::initializer_list<int> expected13 = { 40, 1, 2, 3, 4, 5 };
    tests::compare("List13", list13, expected13);
    std::initializer_list<int> expected14 = { 10, 20, 30, 50 };
    tests::compare("List14", list14, expected14);


    dsa::List<int> list15 = dsa::List<int>(il_1);
    dsa::List<int> list16 = dsa::List<int>(il_2);
    list15.splice(list15.begin()[3], list16, list16.begin());
    std::initializer_list<int> expected15 = { 1, 2, 3, 10, 4, 5 };
    tests::compare("List15", list15, expected15);
    std::initializer_list<int> expected16 = { 20, 30, 40, 50 };
    tests::compare("List16", list16, expected16);

    dsa::List<int> list17 = dsa::List<int>(il_1);
    dsa::List<int> list18 = dsa::List<int>(il_2);
    list17.splice(list17.begin()[3], list18, list18.begin()[2]);
    std::initializer_list<int> expected17 = { 1, 2, 3, 30, 4, 5 };
    tests::compare("List17", list17, expected17);
    std::initializer_list<int> expected18 = { 10, 20, 40, 50 };
    tests::compare("List18", list18, expected18);

    dsa::List<int> list19 = dsa::List<int>(il_1);
    dsa::List<int> list20 = dsa::List<int>(il_2);
    list19.splice(list19.begin()[3], list20, list20.begin()[list20.size() - 2]);
    std::initializer_list<int> expected19 = { 1, 2, 3, 40, 4, 5 };
    tests::compare("List19", list19, expected19);
    std::initializer_list<int> expected20 = { 10, 20, 30, 50 };
    tests::compare("List20", list20, expected20);


    dsa::List<int> list21 = dsa::List<int>(il_1);
    dsa::List<int> list22 = dsa::List<int>(il_2);
    list21.splice(list21.begin()[list21.size() - 1], list22, list22.begin());
    std::initializer_list<int> expected21 = { 1, 2, 3, 4, 10, 5 };
    tests::compare("List21", list21, expected21);
    std::initializer_list<int> expected22 = { 20, 30, 40, 50 };
    tests::compare("List22", list22, expected22);

    dsa::List<int> list23 = dsa::List<int>(il_1);
    dsa::List<int> list24 = dsa::List<int>(il_2);
    list23.splice(list23.begin()[list23.size() - 1], list24, list24.begin()[3]);
    std::initializer_list<int> expected23 = { 1, 2, 3, 4, 40, 5 };
    tests::compare("List23", list23, expected23);
    std::initializer_list<int> expected24 = { 10, 20, 30, 50 };
    tests::compare("List24", list24, expected24);

    dsa::List<int> list25 = dsa::List<int>(il_1);
    dsa::List<int> list26 = dsa::List<int>(il_2);
    list25.splice(list25.begin()[list25.size() - 1], list26, list26.begin()[list26.size() - 2]);
    std::initializer_list<int> expected25 = { 1, 2, 3, 4, 40, 5 };
    tests::compare("List25", list25, expected25);
    std::initializer_list<int> expected26 = { 10, 20, 30, 50 };
    tests::compare("List26", list26, expected26);


    std::cout << "Testing moving range of element from other list\n\n";

    dsa::List<int> list27 = dsa::List<int>(il_1);
    dsa::List<int> list28 = dsa::List<int>(il_2);
    list27.splice(list27.begin(), list28, list28.begin(), list28.begin()[1]);
    std::initializer_list<int> expected27 = { 10, 1, 2, 3, 4, 5 };
    tests::compare("List27", list27, expected27);
    std::initializer_list<int> expected28 = { 20, 30, 40, 50 };
    tests::compare("List28", list28, expected28);

    dsa::List<int> list29 = dsa::List<int>(il_1);
    dsa::List<int> list30 = dsa::List<int>(il_2);
    list29.splice(list29.begin(), list30, list30.begin()[1], list30.begin()[3]);
    std::initializer_list<int> expected29 = { 20, 30, 1, 2, 3, 4, 5 };
    tests::compare("List29", list29, expected29);
    std::initializer_list<int> expected30 = { 10, 40, 50 };
    tests::compare("List30", list30, expected30);

    dsa::List<int> list31 = dsa::List<int>(il_1);
    dsa::List<int> list32 = dsa::List<int>(il_2);
    list31.splice(list31.begin(), list32, list32.begin(), list32.begin()[list32.size() - 1]);
    std::initializer_list<int> expected31 = { 10, 20, 30, 40, 1, 2, 3, 4, 5 };
    tests::compare("List31", list31, expected31);
    std::initializer_list<int> expected32 = { 50 };
    tests::compare("List32", list32, expected32);


    dsa::List<int> list33 = dsa::List<int>(il_1);
    dsa::List<int> list34 = dsa::List<int>(il_2);
    list33.splice(list33.begin()[2], list34, list34.begin(), list34.begin()[1]);
    std::initializer_list<int> expected33 = { 1, 2, 10, 3, 4, 5 };
    tests::compare("List33", list33, expected33);
    std::initializer_list<int> expected34 = { 20, 30, 40, 50 };
    tests::compare("List34", list34, expected34);

    dsa::List<int> list35 = dsa::List<int>(il_1);
    dsa::List<int> list36 = dsa::List<int>(il_2);
    list35.splice(list35.begin()[2], list36, list36.begin()[1], list36.begin()[3]);
    std::initializer_list<int> expected35 = { 1, 2, 20, 30, 3, 4, 5 };
    tests::compare("List35", list35, expected35);
    std::initializer_list<int> expected36 = { 10, 40, 50 };
    tests::compare("List36", list36, expected36);

    dsa::List<int> list37 = dsa::List<int>(il_1);
    dsa::List<int> list38 = dsa::List<int>(il_2);
    list37.splice(list37.begin()[2], list38, list38.begin(), list38.begin()[list38.size() - 1]);
    std::initializer_list<int> expected37 = { 1, 2, 10, 20, 30, 40, 3, 4, 5 };
    tests::compare("List37", list37, expected37);
    std::initializer_list<int> expected38 = { 50 };
    tests::compare("List38", list38, expected38);


    dsa::List<int> list39 = dsa::List<int>(il_1);
    dsa::List<int> list40 = dsa::List<int>(il_2);
    list39.splice(list39.begin()[list39.size() - 1], list40, list40.begin(), list40.begin()[1]);
    std::initializer_list<int> expected39 = { 1, 2, 3, 4, 10, 5 };
    tests::compare("List39", list39, expected39);
    std::initializer_list<int> expected40 = { 20, 30, 40, 50 };
    tests::compare("List40", list40, expected40);

    dsa::List<int> list41 = dsa::List<int>(il_1);
    dsa::List<int> list42 = dsa::List<int>(il_2);
    list41.splice(list41.begin()[list41.size() - 1], list42, list42.begin()[1], list42.begin()[3]);
    std::initializer_list<int> expected41 = { 1, 2, 3, 4, 20, 30, 5 };
    tests::compare("List41", list41, expected41);
    std::initializer_list<int> expected42 = { 10, 40, 50 };
    tests::compare("List42", list42, expected42);

    dsa::List<int> list43 = dsa::List<int>(il_1);
    dsa::List<int> list44 = dsa::List<int>(il_2);
    list43.splice(list43.begin()[list43.size() - 1], list44, list44.begin(), list44.begin()[list44.size() - 1]);
    std::initializer_list<int> expected43 = { 1, 2, 3, 4, 10, 20, 30, 40, 5 };
    tests::compare("List43", list43, expected43);
    std::initializer_list<int> expected44 = { 50 };
    tests::compare("List44", list44, expected44);

    return tests::failed;

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
