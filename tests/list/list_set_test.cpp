/**
 * @file list_set_test.cpp
 * @brief This file tests setting values of List Nodes
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
        std::cout << "Start list_set_test:\n";

        dsa::List<int> list1 = dsa::List<int>({ 0, 10, 20 });
        const std::initializer_list<int> expected1{ 0, 1, 2 };
        list1 = expected1;
        tests::compare("List1", list1, expected1);

        dsa::List<int> list2 = dsa::List<int>({ 0, 10, 20 });
        list2.assign(4, 1);
        const std::initializer_list<int> expected2 = { 1, 1, 1, 1 };
        tests::compare("List2", list2, expected2);

        dsa::List<int> list3 = dsa::List<int>({ 0, 10, 20 });
        const std::initializer_list<int> expected3 = { 1, 2, 3, 4 };
        list3.assign(expected3);
        tests::compare("List3", list3, expected3);

        const std::initializer_list<int> expected4{ 1, 2, 3, 4 };
        const dsa::List<int> list4 = expected4;
        tests::compare("List4", list4, expected4);

        const std::initializer_list<int> expected5{ 1, 2, 3, 4 };
        dsa::List<int> list5{ 10, 20, 30 };
        list5 = expected5;
        tests::compare("List5", list5, expected5);

        dsa::List<int> list6 = dsa::List<int>({ 0, 10, 20 });
        dsa::List<int> temp6 = dsa::List<int>({ 0, 1, 2, 3, 4, 5 });
        list6.assign(std::next(temp6.begin(), 1), std::next(temp6.begin(), 4));
        const std::initializer_list<int> expected6 = { 1, 2, 3 };
        tests::compare("List6", list6, expected6);


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list1{ 0, 10, 20 };
        std_list1 = expected1;
        tests::compare("List1 vs std", list1, std_list1);

        std::list<int> std_list2{ 0, 10, 20 };
        std_list2.assign(4, 1);
        tests::compare("List2 vs std", list2, std_list2);

        std::list<int> std_list3{ 0, 10, 20 };
        std_list3.assign(expected3);
        tests::compare("List3 vs std", list3, std_list3);

        const std::list<int> std_list4 = expected4;
        tests::compare("List4 vs std", list4, std_list4);

        std::list<int> std_list5{ 10, 20, 30 };
        std_list5 = expected5;
        tests::compare("List5 vs std", list5, std_list5);

        std::list<int> std_list6{ 0, 10, 20 };
        std_list6.assign(std::next(temp6.begin(), 1), std::next(temp6.begin(), 4));
        tests::compare("List6 vs std", list6, std_list6);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}