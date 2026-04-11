/**
 * @file list_sort_test.cpp
 * @brief This file tests functions sorting List objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2026 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/list.h"

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
        std::cout << "Start list_sort_test:\n";

        const std::initializer_list<int> il_1{ 1, 10, 2, 20, 3, 30, 4, 40, 5, 50 };
        const std::initializer_list<int> il_2{ 1, 10, 1, 20, 1, 30, 1, 40, 1, 50 };

        dsa::List<int> list1 = dsa::List<int>(il_1);
        list1.sort();
        const std::initializer_list<int> expected1{ 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
        tests::compare("List1", list1, expected1);

        dsa::List<int> list2 = dsa::List<int>(il_2);
        list2.sort();
        const std::initializer_list<int> expected2{ 1, 1, 1, 1, 1, 10, 20, 30, 40, 50 };
        tests::compare("List2", list2, expected2);


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list1{ il_1 };
        std_list1.sort();
        tests::compare("List1 vs std", list1, std_list1);

        std::list<int> std_list2{ il_2 };
        std_list2.sort();
        tests::compare("List2 vs std", list2, std_list2);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
