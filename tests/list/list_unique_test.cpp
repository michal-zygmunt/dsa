/**
 * @file list_unique_test.cpp
 * @brief This file tests functions checking values of List objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy "List
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/list.h"

#include <cmath>
#include <cstddef>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <list>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start list_unique_test:\n";

        dsa::List<int> list1 = dsa::List<int>({ 1, 2, 3, 4, 5 });
        auto removed1 = list1.unique();
        const std::initializer_list<int> expected1 = { 1, 2, 3, 4, 5 };
        tests::compare("List1", list1, expected1);
        tests::compare("List1 removed", removed1, size_t{ 0 });

        dsa::List<int> list2 = dsa::List<int>({ 1, 4, 2, 3, 2, 4, 3, 5, 1 });
        auto removed2 = list2.unique();
        const std::initializer_list<int> expected2 = { 1, 4, 2, 3, 2, 4, 3, 5, 1 };
        tests::compare("List2", list2, expected2);
        tests::compare("List2 removed", removed2, size_t{ 0 });

        dsa::List<int> list3 = dsa::List<int>({ 1, 1, 2, 4, 2, 1, 3, 1, 1 });
        auto removed3 = list3.unique();
        const std::initializer_list<int> expected3 = { 1, 2, 4, 2, 1, 3, 1 };
        tests::compare("List3", list3, expected3);
        tests::compare("List3 removed", removed3, size_t{ 2 });

        dsa::List<int> list4 = dsa::List<int>({ 1, 1, 1, 2, 2, 2, 1, 1, 1 });
        auto removed4 = list4.unique();
        const std::initializer_list<int> expected4 = { 1, 2, 1 };
        tests::compare("List4", list4, expected4);
        tests::compare("List4 removed", removed4, size_t{ 6 });

        dsa::List<int> list5 = dsa::List<int>({ 0, 0, 0, 0, 0, 0 });
        auto removed5 = list5.unique();
        const std::initializer_list<int> expected5 = { 0 };
        tests::compare("List5", list5, expected5);
        tests::compare("List5 removed", removed5, size_t{ 5 });

        dsa::List<int> list6 = dsa::List<int>();
        auto removed6 = list6.unique();
        const std::initializer_list<int> expected6 = { };
        tests::compare("List6", list6, expected6);
        tests::compare("List6 removed", removed6, size_t{ 0 });

        dsa::List<int> list7;
        auto removed7 = list7.unique();
        const std::initializer_list<int> expected7 = {};
        tests::compare("List7", list7, expected7);
        tests::compare("List7 removed", removed7, size_t{ 0 });

        // find unique values using predicate
        auto predicate = [](const int& input_a, const int& input_b)
            {
                return std::abs(input_a - input_b) <= 5;
            };

        dsa::List<int> list8 = dsa::List<int>({ 1, 5, 7, 15, 25 });
        auto removed8 = list8.unique(predicate);
        const std::initializer_list<int> expected8 = { 1, 7, 15, 25 };
        tests::compare("List8", list8, expected8);
        tests::compare("List8 removed", removed8, size_t{ 1 });

        dsa::List<int> list9 = dsa::List<int>({ 1, 4, 12, 13, 12, 14, 3, 15, 1 });
        auto removed9 = list9.unique(predicate);
        const std::initializer_list<int> expected9 = { 1, 12, 3, 15, 1 };
        tests::compare("List9", list9, expected9);
        tests::compare("List9 removed", removed9, size_t{ 4 });


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list1{ 1, 2, 3, 4, 5 };
        auto std_removed1 = std_list1.unique();
        tests::compare("List1 vs std", list1, std_list1);
        tests::compare("List1 removed vs std", removed1, std_removed1);

        std::list<int> std_list2{ 1, 4, 2, 3, 2, 4, 3, 5, 1 };
        auto std_removed2 = std_list2.unique();
        tests::compare("List2 vs std", list2, std_list2);
        tests::compare("List2 removed vs std", removed2, std_removed2);

        std::list<int> std_list3{ 1, 1, 2, 4, 2, 1, 3, 1, 1 };
        auto std_removed3 = std_list3.unique();
        tests::compare("List3 vs std", list3, std_list3);
        tests::compare("List3 removed vs std", removed3, std_removed3);

        std::list<int> std_list4{ 1, 1, 1, 2, 2, 2, 1, 1, 1 };
        auto std_removed4 = std_list4.unique();
        tests::compare("List4 vs std", list4, std_list4);
        tests::compare("List4 removed vs std", removed4, std_removed4);

        std::list<int> std_list5{ 0, 0, 0, 0, 0, 0 };
        auto std_removed5 = std_list5.unique();
        tests::compare("List5 vs std", list5, std_list5);
        tests::compare("List5 removed vs std", removed5, std_removed5);

        std::list<int> std_list6 = std::list<int>();
        auto std_removed6 = std_list6.unique();
        tests::compare("List6 vs std", list6, std_list6);
        tests::compare("List6 removed vs std", removed6, std_removed6);

        std::list<int> std_list7;
        auto std_removed7 = std_list7.unique();
        tests::compare("List7 vs std", list7, std_list7);
        tests::compare("List7 removed vs std", removed7, std_removed7);

        std::list<int> std_list8{ 1, 5, 7, 15, 25 };
        auto std_removed8 = std_list8.unique(predicate);
        tests::compare("List8 vs std", list8, std_list8);
        tests::compare("List8 removed vs std", removed8, std_removed8);

        std::list<int> std_list9{ 1, 4, 12, 13, 12, 14, 3, 15, 1 };
        auto std_removed9 = std_list9.unique(predicate);
        tests::compare("List9 vs std", list9, std_list9);
        tests::compare("List9 removed vs std", removed9, std_removed9);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
