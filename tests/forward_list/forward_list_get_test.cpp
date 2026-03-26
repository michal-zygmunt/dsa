/**
 * @file forward_list_get_test.cpp
 * @brief This file tests accessing values of ForwardList Nodes
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
#include <initializer_list>
#include <iostream>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start forward_list_get_test:\n";

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>({ 0, 10, 20 });
        const std::initializer_list<int> expected1 = { 0, 10, 20 };
        const size_t list1_size = list1.size();
        for (size_t i = 0; i < list1_size; i++)
        {
            const int temp = list1.front();
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            tests::compare("ForwardList1", temp, expected1.begin()[i]);
            list1.pop_front();
        }

        const dsa::ForwardList<int> list2 = dsa::ForwardList<int>({ 20, 10, 0 });
        tests::compare("ForwardList2 front", list2.front(), 20);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
