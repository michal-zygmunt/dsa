/**
 * @file forward_list_set_test.cpp
 * @brief This file tests setting values of ForwardList Nodes
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

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start forward_list_set_test:\n";

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>({ 0, 10, 20 });
        const std::initializer_list<int> expected1{ 0, 1, 2 };
        list1 = expected1;
        tests::compare("ForwardList1", list1, expected1);

        dsa::ForwardList<int> list2 = dsa::ForwardList<int>({ 0, 10, 20 });
        list2.assign(4, 1);
        const std::initializer_list<int> expected2 = { 1, 1, 1, 1 };
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>({ 0, 10, 20 });
        list3.assign(0, 1);
        const std::initializer_list<int> expected3 = {};
        tests::compare("ForwardList3", list3, expected3);

        dsa::ForwardList<int> list4 = dsa::ForwardList<int>({ 0, 10, 20 });
        const std::initializer_list<int> expected4 = { 1, 2, 3, 4 };
        list4.assign(expected4);
        tests::compare("ForwardList4", list4, expected4);

        dsa::ForwardList<int> list5 = dsa::ForwardList<int>({ 0, 10, 20 });
        dsa::ForwardList<int> temp5 = dsa::ForwardList<int>({ 0, 1, 2, 3, 4, 5 });
        list5.assign(std::next(temp5.begin(), 1), std::next(temp5.begin(), 4));
        const std::initializer_list<int> expected5 = { 1, 2, 3 };
        tests::compare("ForwardList5", list5, expected5);

        dsa::ForwardList<int> list6 = dsa::ForwardList<int>({ 0, 10, 20 });
        constexpr int new_value{ 50 };
        list6.front() = new_value;
        const std::initializer_list<int> expected6{ new_value, 10, 20 };
        tests::compare("ForwardList6", list6, expected6);

        dsa::ForwardList<int> list7 = dsa::ForwardList<int>({ 0, 10, 20 });
        const std::initializer_list<int> expected7 = {};
        list7.assign(expected7);
        tests::compare("ForwardList7", list7, expected7);


        std::cout << "Compare operations results with std container\n\n";

        std::forward_list<int> std_list1{ 0, 10, 20 };
        std_list1 = expected1;
        tests::compare("ForwardList1 vs std", list1, std_list1);

        std::forward_list<int> std_list2{ 0, 10, 20 };
        std_list2.assign(4, 1);
        tests::compare("ForwardList2 vs std", list2, std_list2);

        std::forward_list<int> std_list3{ 0, 10, 20 };
        std_list3.assign(0, 1);
        tests::compare("ForwardList3 vs std", list3, std_list3);

        std::forward_list<int> std_list4{ 0, 10, 20 };
        std_list4.assign(expected4);
        tests::compare("ForwardList4 vs std", list4, std_list4);

        std::forward_list<int> std_list5{ 0, 10, 20 };
        std_list5.assign(std::next(temp5.begin(), 1), std::next(temp5.begin(), 4));
        tests::compare("ForwardList5 vs std", list5, std_list5);

        std::forward_list<int> std_list6{ 0, 10, 20 };
        std_list6.front() = new_value;
        tests::compare("ForwardList6 vs std", list6, std_list6);

        std::forward_list<int> std_list7{ 0, 10, 20 };
        std_list7.assign(expected7);
        tests::compare("ForwardList7 vs std", list7, std_list7);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
