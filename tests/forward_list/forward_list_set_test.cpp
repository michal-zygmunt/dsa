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

#include <cstddef>
#include <exception>
#include <forward_list>
#include <initializer_list>
#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start forward_list_set_test:\n";

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>({ 0, 10, 20 });
        // Try setting values for nodes with invalid indexes
        constexpr int new_value{ 50 };
        list1.set(static_cast<size_t>(-1), new_value);
        list1.set(1, new_value);
        list1.set(100, new_value);
        const std::initializer_list<int> expected1{ 0, 50, 20 };
        tests::compare("ForwardList1", list1, expected1);

        dsa::ForwardList<int> list2 = dsa::ForwardList<int>({ 0, 10, 20 });
        list2.assign(4, 1);
        const std::initializer_list<int> expected2 = { 1, 1, 1, 1 };
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>({ 0, 10, 20 });
        const std::initializer_list<int> expected3 = { 1, 2, 3, 4 };
        list3.assign(expected3);
        tests::compare("ForwardList3", list3, expected3);


        std::cout << "Compare operations results with std container\n\n";

        std::forward_list<int> std_list2{ 0, 10, 20 };
        std_list2.assign(4, 1);
        tests::compare("ForwardList2 vs std", list2, std_list2);

        std::forward_list<int> std_list3{ 0, 10, 20 };
        std_list3.assign(expected3);
        tests::compare("ForwardList3 vs std", list3, std_list3);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
