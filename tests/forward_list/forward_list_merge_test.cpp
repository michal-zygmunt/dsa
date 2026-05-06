/**
 * @file forward_list_merge_test.cpp
 * @brief This file tests functions merging ForwardList objects
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
#include <functional>
#include <initializer_list>
#include <iostream>
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start forward_list_merge_test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };
        const std::initializer_list<int> il_3{ 1, 1, 3, 5, 7 };
        const std::initializer_list<int> il_4{ 1, 2, 4, 6, 9 };

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list2 = dsa::ForwardList<int>(il_2);
        list1.merge(list2);
        const std::initializer_list<int> expected1 = { 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
        tests::compare("ForwardList1", list1, expected1);
        const std::initializer_list<int> expected2 = {};
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list4;
        list4.merge(list3);
        const std::initializer_list<int> expected3 = { };
        tests::compare("ForwardList3", list3, expected3);
        const std::initializer_list<int> expected4 = il_1;
        tests::compare("ForwardList4", list4, expected4);

        dsa::ForwardList<int> list5 = dsa::ForwardList<int>(il_3);
        dsa::ForwardList<int> list6 = dsa::ForwardList<int>(il_4);
        list5.merge(list6);
        const std::initializer_list<int> expected5 = { 1, 1, 1, 2, 3, 4, 5, 6, 7, 9 };
        tests::compare("ForwardList5", list5, expected5);
        const std::initializer_list<int> expected6 = {};
        tests::compare("ForwardList6", list6, expected6);

        dsa::ForwardList<int> list7 = dsa::ForwardList<int>(il_4);
        dsa::ForwardList<int> list8 = dsa::ForwardList<int>(il_3);
        list7.merge(list8);
        const std::initializer_list<int> expected7 = { 1, 1, 1, 2, 3, 4, 5, 6, 7, 9 };
        tests::compare("ForwardList7", list7, expected7);
        const std::initializer_list<int> expected8 = {};
        tests::compare("ForwardList8", list8, expected8);

        dsa::ForwardList<int> list9 = dsa::ForwardList<int>(il_2);
        dsa::ForwardList<int> list10 = dsa::ForwardList<int>(il_3);
        list9.merge(list10);
        const std::initializer_list<int> expected9 = { 1, 1, 3, 5, 7, 10, 20, 30, 40, 50 };
        tests::compare("ForwardList9", list9, expected9);
        const std::initializer_list<int> expected10 = {};
        tests::compare("ForwardList10", list10, expected10);

        dsa::ForwardList<int> list11 = dsa::ForwardList<int>(il_3);
        dsa::ForwardList<int> list12 = dsa::ForwardList<int>(il_2);
        list11.merge(std::move(list12));
        const std::initializer_list<int> expected11 = { 1, 1, 3, 5, 7, 10, 20, 30, 40, 50 };
        tests::compare("ForwardList11", list11, expected11);
        const std::initializer_list<int> expected12 = {};
        // NOLINTNEXTLINE(bugprone-use-after-move)
        tests::compare("ForwardList12", list12, expected12);

        // merging using non default compration argument

        dsa::ForwardList<int> list13 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list14 = dsa::ForwardList<int>(il_2);
        list13.sort(std::greater<>());
        list14.sort(std::greater<>());
        list13.merge(list14, std::greater<>());
        const std::initializer_list<int> expected13 = { 50, 40, 30, 20, 10, 5, 4, 3, 2, 1 };
        tests::compare("ForwardList13", list13, expected13);
        const std::initializer_list<int> expected14 = {};
        tests::compare("ForwardList14", list14, expected14);

        dsa::ForwardList<int> list15 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list16;
        list15.sort(std::greater<>());
        list16.sort(std::greater<>());
        list16.merge(list15, std::greater<>());
        const std::initializer_list<int> expected15{};
        tests::compare("ForwardList15", list15, expected15);
        const std::initializer_list<int> expected16{ 5, 4, 3, 2, 1 };
        tests::compare("ForwardList16", list16, expected16);

        dsa::ForwardList<int> list17 = dsa::ForwardList<int>(il_3);
        dsa::ForwardList<int> list18 = dsa::ForwardList<int>(il_4);
        list17.sort(std::greater<>());
        list18.sort(std::greater<>());
        list17.merge(list18, std::greater<>());
        const std::initializer_list<int> expected17{ 9, 7, 6, 5, 4, 3, 2, 1, 1, 1 };
        tests::compare("ForwardList17", list17, expected17);
        const std::initializer_list<int> expected18{};
        tests::compare("ForwardList18", list18, expected18);

        dsa::ForwardList<int> list19 = dsa::ForwardList<int>(il_4);
        dsa::ForwardList<int> list20 = dsa::ForwardList<int>(il_3);
        list19.sort(std::greater<>());
        list20.sort(std::greater<>());
        list19.merge(list20, std::greater<>());
        const std::initializer_list<int> expected19{ 9, 7, 6, 5, 4, 3, 2, 1, 1, 1 };
        tests::compare("ForwardList19", list19, expected19);
        const std::initializer_list<int> expected20{};
        tests::compare("ForwardList20", list20, expected20);

        dsa::ForwardList<int> list21 = dsa::ForwardList<int>(il_2);
        dsa::ForwardList<int> list22 = dsa::ForwardList<int>(il_3);
        list21.sort(std::greater<>());
        list22.sort(std::greater<>());
        list21.merge(list22, std::greater<>());
        const std::initializer_list<int> expected21{ 50, 40, 30, 20, 10, 7, 5, 3, 1, 1 };
        tests::compare("ForwardList21", list21, expected21);
        const std::initializer_list<int> expected22{};
        tests::compare("ForwardList22", list22, expected22);

        dsa::ForwardList<int> list23 = dsa::ForwardList<int>(il_3);
        dsa::ForwardList<int> list24 = dsa::ForwardList<int>(il_2);
        list23.sort(std::greater<>());
        list24.sort(std::greater<>());
        list23.merge(std::move(list24), std::greater<>());
        const std::initializer_list<int> expected23{ 50, 40, 30, 20, 10, 7, 5, 3, 1, 1 };
        tests::compare("ForwardList23", list23, expected23);
        const std::initializer_list<int> expected24{};
        // NOLINTNEXTLINE(bugprone-use-after-move)
        tests::compare("ForwardList24", list24, expected24);

        // self merge
        dsa::ForwardList<int> list25{ il_1 };
        list25.merge(list25);
        tests::compare("ForwardList25", list25, il_1);

        dsa::ForwardList<int> list26;
        list26.merge(list26);
        tests::compare("ForwardList26", list26, {});

        // self merge with move semantics should be aborted
        // compare result with initial input
        dsa::ForwardList<int> list27{ il_1 };
        list27.merge(std::move(list27));
        // intentional use of moved object
        // NOLINTNEXTLINE(bugprone-use-after-move)
        tests::compare("ForwardList27", list27, il_1);

        // self merge with move semantics should be aborted
        // compare result with initial input
        dsa::ForwardList<int> list28{ il_1 };
        list28.merge(std::move(list28), std::greater<>());
        // intentional use of moved object
        // NOLINTNEXTLINE(bugprone-use-after-move)
        tests::compare("ForwardList28", list28, il_1);

        dsa::ForwardList<std::string> list29{ "1a", "1b", "2a" };
        dsa::ForwardList<std::string> list30{ "2b", "1c", "1d" };
        list29.sort();
        list30.sort();
        list29.merge(list30);
        const std::initializer_list<std::string> expected29{ "1a", "1b", "1c", "1d", "2a", "2b" };
        tests::compare("ForwardList29", list29, expected29);
        const std::initializer_list<std::string> expected30{};
        tests::compare("ForwardList30", list30, expected30);

        dsa::ForwardList<std::string> list31{ "1a", "1b", "2a" };
        dsa::ForwardList<std::string> list32{ "2b", "1c", "1d" };
        list31.sort(std::less<>());
        list32.sort(std::less<>());
        list31.merge(list32, std::less<>());
        const std::initializer_list<std::string> expected31{ "1a", "1b", "1c", "1d", "2a", "2b" };
        tests::compare("ForwardList31", list31, expected31);
        const std::initializer_list<std::string> expected32{};
        tests::compare("ForwardList32", list32, expected32);

        dsa::ForwardList<std::string> list33{ "1a", "1b", "2a" };
        dsa::ForwardList<std::string> list34{ "2b", "1c", "1d" };
        list33.sort(std::greater<>());
        list34.sort(std::greater<>());
        list33.merge(list34, std::greater<>());
        const std::initializer_list<std::string> expected33{ "2b", "2a", "1d", "1c", "1b", "1a" };
        tests::compare("ForwardList33", list33, expected33);
        const std::initializer_list<std::string> expected34{};
        tests::compare("ForwardList34", list34, expected34);

        dsa::ForwardList<std::string> list35{ "2a", "1a", "1b" };
        dsa::ForwardList<std::string> list36{};
        list35.sort(std::less<>());
        list36.sort(std::less<>());
        list35.merge(list36, std::less<>());
        const std::initializer_list<std::string> expected35{ "1a", "1b", "2a" };
        tests::compare("ForwardList35", list35, expected35);
        const std::initializer_list<std::string> expected36{};
        tests::compare("ForwardList36", list36, expected36);

        dsa::ForwardList<std::string> list37{};
        dsa::ForwardList<std::string> list38{ "2a", "1a", "1b" };
        list37.sort(std::less<>());
        list38.sort(std::less<>());
        list37.merge(list38, std::less<>());
        const std::initializer_list<std::string> expected37{ "1a", "1b", "2a" };
        tests::compare("ForwardList37", list37, expected37);
        const std::initializer_list<std::string> expected38{};
        tests::compare("ForwardList38", list38, expected38);

        dsa::ForwardList<std::string> list39{ "1a", "1b", "2a" };
        dsa::ForwardList<std::string> list40{};
        list39.sort(std::greater<>());
        list40.sort(std::greater<>());
        list40.merge(list39, std::greater<>());
        const std::initializer_list<std::string> expected39{};
        tests::compare("ForwardList39", list39, expected39);
        const std::initializer_list<std::string> expected40{ "2a", "1b", "1a" };
        tests::compare("ForwardList40", list40, expected40);

        dsa::ForwardList<std::string> list41{};
        dsa::ForwardList<std::string> list42{ "1a", "1b", "2a" };
        list41.sort(std::greater<>());
        list42.sort(std::greater<>());
        list42.merge(list41, std::greater<>());
        const std::initializer_list<std::string> expected41{};
        tests::compare("ForwardList41", list41, expected41);
        const std::initializer_list<std::string> expected42{ "2a", "1b", "1a" };
        tests::compare("ForwardList42", list42, expected42);


        std::cout << "Compare operations results with std container\n\n";

        std::forward_list<int> std_list1{ il_1 };
        std::forward_list<int> std_list2{ il_2 };
        std_list1.merge(std_list2);
        tests::compare("ForwardList1 vs std", list1, std_list1);
        tests::compare("ForwardList2 vs std", list2, std_list2);

        std::forward_list<int> std_list3{ il_1 };
        std::forward_list<int> std_list4;
        std_list4.merge(std_list3);
        tests::compare("ForwardList3 vs std", list3, std_list3);
        tests::compare("ForwardList4 vs std", list4, std_list4);

        std::forward_list<int> std_list5{ il_3 };
        std::forward_list<int> std_list6{ il_4 };
        std_list5.merge(std_list6);
        tests::compare("ForwardList5 vs std", list5, std_list5);
        tests::compare("ForwardList6 vs std", list6, std_list6);

        std::forward_list<int> std_list7{ il_4 };
        std::forward_list<int> std_list8{ il_3 };
        std_list7.merge(std_list8);
        tests::compare("ForwardList7 vs std", list7, std_list7);
        tests::compare("ForwardList8 vs std", list8, std_list8);

        std::forward_list<int> std_list9{ il_2 };
        std::forward_list<int> std_list10{ il_3 };
        std_list9.merge(std_list10);
        tests::compare("ForwardList9 vs std", list9, std_list9);
        tests::compare("ForwardList10 vs std", list10, std_list10);

        std::forward_list<int> std_list11{ il_3 };
        std::forward_list<int> std_list12{ il_2 };
        std_list11.merge(std::move(std_list12));
        tests::compare("ForwardList11 vs std", list11, std_list11);
        // NOLINTNEXTLINE(bugprone-use-after-move)
        tests::compare("ForwardList12 vs std", list12, std_list12);

        // merging using non default compration argument

        std::forward_list<int> std_list13{ il_1 };
        std::forward_list<int> std_list14{ il_2 };
        std_list13.sort(std::greater<>());
        std_list14.sort(std::greater<>());
        std_list13.merge(std_list14, std::greater<>());
        tests::compare("ForwardList13 vs std", list13, std_list13);
        tests::compare("ForwardList14 vs std", list14, std_list14);

        std::forward_list<int> std_list15{ il_1 };
        std::forward_list<int> std_list16;
        std_list15.sort(std::greater<>());
        std_list16.sort(std::greater<>());
        std_list16.merge(std_list15, std::greater<>());
        tests::compare("ForwardList15 vs std", list15, std_list15);
        tests::compare("ForwardList16 vs std", list16, std_list16);

        std::forward_list<int> std_list17{ il_3 };
        std::forward_list<int> std_list18{ il_4 };
        std_list17.sort(std::greater<>());
        std_list18.sort(std::greater<>());
        std_list17.merge(std_list18, std::greater<>());
        tests::compare("ForwardList17 vs std", list17, std_list17);
        tests::compare("ForwardList18 vs std", list18, std_list18);

        std::forward_list<int> std_list19{ il_4 };
        std::forward_list<int> std_list20{ il_3 };
        std_list19.sort(std::greater<>());
        std_list20.sort(std::greater<>());
        std_list19.merge(std_list20, std::greater<>());
        tests::compare("ForwardList19 vs std", list19, std_list19);
        tests::compare("ForwardList20 vs std", list20, std_list20);

        std::forward_list<int> std_list21{ il_2 };
        std::forward_list<int> std_list22{ il_3 };
        std_list21.sort(std::greater<>());
        std_list22.sort(std::greater<>());
        std_list21.merge(std_list22, std::greater<>());
        tests::compare("ForwardList21 vs std", list21, std_list21);
        tests::compare("ForwardList22 vs std", list22, std_list22);

        std::forward_list<int> std_list23{ il_3 };
        std::forward_list<int> std_list24{ il_2 };
        std_list23.sort(std::greater<>());
        std_list24.sort(std::greater<>());
        std_list23.merge(std::move(std_list24), std::greater<>());
        tests::compare("ForwardList23 vs std", list23, std_list23);
        // NOLINTNEXTLINE(bugprone-use-after-move)
        tests::compare("ForwardList24 vs std", list24, std_list24);

        // self merge
        std::forward_list<int> std_list25{ il_1 };
        std_list25.merge(std_list25);
        tests::compare("ForwardList25 vs std", list25, std_list25);

        std::forward_list<int> std_list26;
        std_list26.merge(std_list26);
        tests::compare("ForwardList26 vs std", list26, std_list26);

        std::forward_list<std::string> std_list29{ "1a", "1b", "2a" };
        std::forward_list<std::string> std_list30{ "2b", "1c", "1d" };
        std_list29.sort();
        std_list30.sort();
        std_list29.merge(std_list30);
        tests::compare("ForwardList29 vs std", list29, std_list29);
        tests::compare("ForwardList30 vs std", list30, std_list30);

        std::forward_list<std::string> std_list31{ "1a", "1b", "2a" };
        std::forward_list<std::string> std_list32{ "2b", "1c", "1d" };
        std_list31.sort(std::less<>());
        std_list32.sort(std::less<>());
        std_list31.merge(std_list32, std::less<>());
        tests::compare("ForwardList31 vs std", list31, std_list31);
        tests::compare("ForwardList32 vs std", list32, std_list32);

        std::forward_list<std::string> std_list33{ "1a", "1b", "2a" };
        std::forward_list<std::string> std_list34{ "2b", "1c", "1d" };
        std_list33.sort(std::greater<>());
        std_list34.sort(std::greater<>());
        std_list33.merge(std_list34, std::greater<>());
        tests::compare("ForwardList33 vs std", list33, std_list33);
        tests::compare("ForwardList34 vs std", list34, std_list34);

        std::forward_list<std::string> std_list35{ "2a", "1a", "1b" };
        std::forward_list<std::string> std_list36{};
        std_list35.sort(std::less<>());
        std_list36.sort(std::less<>());
        std_list35.merge(std_list36, std::less<>());
        tests::compare("ForwardList35 vs std", list35, std_list35);
        tests::compare("ForwardList36 vs std", list36, std_list36);

        std::forward_list<std::string> std_list37{};
        std::forward_list<std::string> std_list38{ "2a", "1a", "1b" };
        std_list37.sort(std::less<>());
        std_list38.sort(std::less<>());
        std_list37.merge(std_list38, std::less<>());
        tests::compare("ForwardList37 vs std", list37, std_list37);
        tests::compare("ForwardList38 vs std", list38, std_list38);

        std::forward_list<std::string> std_list39{ "1a", "1b", "2a" };
        std::forward_list<std::string> std_list40{};
        std_list39.sort(std::greater<>());
        std_list40.sort(std::greater<>());
        std_list40.merge(std_list39, std::greater<>());
        tests::compare("ForwardList39 vs std", list39, std_list39);
        tests::compare("ForwardList40 vs std", list40, std_list40);

        std::forward_list<std::string> std_list41{};
        std::forward_list<std::string> std_list42{ "1a", "1b", "2a" };
        std_list41.sort(std::greater<>());
        std_list42.sort(std::greater<>());
        std_list42.merge(std_list41, std::greater<>());
        tests::compare("ForwardList41 vs std", list41, std_list41);
        tests::compare("ForwardList42 vs std", list42, std_list42);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
