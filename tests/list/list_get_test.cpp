/**
 * @file list_get_test.cpp
 * @brief This file tests accessing values of List Nodes
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

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start list_get_test:\n";

        dsa::List<int> list1 = dsa::List<int>({ 0, 10, 20 });
        const std::initializer_list<int> expected1 = { 0, 10, 20 };
        const size_t list1_size = list1.size();
        for (size_t i = 0; i < list1_size; i++)
        {
            const int temp = list1.front();
            tests::compare("List1", temp, *(std::next(expected1.begin(), static_cast<ptrdiff_t>(i))));
            list1.pop_front();
        }

        const dsa::List<int> list2 = dsa::List<int>({ 0, 10, 20 });
        tests::compare("List2 front", list2.front(), 0);
        tests::compare("List2 back", list2.back(), 20);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}