/**
 * @file list_reverse_test.cpp
 * @brief This file tests reversing order of List Nodes
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

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start list_reverse_test:\n";

        dsa::List<int> list1 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
        auto iter1a = std::next(list1.begin());
        auto ref1a_front = list1.front();
        auto ref1a_back = list1.back();
        list1.reverse();
        auto iter1b = std::next(list1.begin(), 4);
        auto ref1b_front = list1.front();
        auto ref1b_back = list1.back();
        const std::initializer_list<int> expected1 = { 50, 40, 30, 20, 10, 0 };
        tests::compare("List1", list1, expected1);
        tests::compare("List1 iter", *iter1a, *iter1b);
        tests::compare("List1 ref front-back", ref1a_front, ref1b_back);
        tests::compare("List1 ref back-front", ref1a_back, ref1b_front);

        dsa::List<int> list2 = dsa::List<int>({ 0 });
        list2.reverse();
        const std::initializer_list<int> expected2{ 0 };
        tests::compare("List2", list2, expected2);

        dsa::List<int> list3;
        list3.reverse();
        const std::initializer_list<int> expected3{};
        tests::compare("List3", list3, expected3);


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list1{ 0, 10, 20, 30, 40, 50 };
        auto std_iter1a = std::next(std_list1.begin());
        auto std_ref1a_front = std_list1.front();
        auto std_ref1a_back = std_list1.back();
        std_list1.reverse();
        auto std_iter1b = std::next(std_list1.begin(), 4);
        auto std_ref1b_front = std_list1.front();
        auto std_ref1b_back = std_list1.back();
        tests::compare("List1 vs std", list1, std_list1);
        tests::compare("List1 iter1a vs std", *iter1a, *std_iter1a);
        tests::compare("List1 iter1b vs std", *iter1b, *std_iter1b);
        tests::compare("List1 ref front-back vs std", std_ref1a_front, std_ref1b_back);
        tests::compare("List1 ref back-front vs std", std_ref1a_back, std_ref1b_front);
        tests::compare("List1 ref front vs std", ref1b_front, std_ref1b_front);
        tests::compare("List1 ref back vs std", ref1b_back, std_ref1b_back);

        std::list<int> std_list2{ 0 };
        std_list2.reverse();
        tests::compare("List2 vs std", list2, std_list2);

        std::list<int> std_list3;
        std_list3.reverse();
        tests::compare("List3 vs std", list3, std_list3);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}