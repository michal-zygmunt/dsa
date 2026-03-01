/**
 * @file forward_list_sort_test.cpp
 * @brief This file tests functions sorting ForwardList objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2026 Michal Zygmunt
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

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start forward_list_sort_test:\n";

        const std::initializer_list<int> il_1{ 1, 10, 2, 20, 3, 30, 4, 40, 5, 50 };
        const std::initializer_list<int> il_2{ 1, 10, 1, 20, 1, 30, 1, 40, 1, 50 };

        // ascending
        dsa::ForwardList<int> list1 = dsa::ForwardList<int>(il_1);
        list1.sort();
        const std::initializer_list<int> expected1{ 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
        tests::compare("ForwardList1", list1, expected1);

        dsa::ForwardList<int> list2 = dsa::ForwardList<int>(il_2);
        list2.sort();
        const std::initializer_list<int> expected2{ 1, 1, 1, 1, 1, 10, 20, 30, 40, 50 };
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>(il_1);
        list3.sort(std::less<>());
        const std::initializer_list<int> expected3{ 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
        tests::compare("ForwardList3", list3, expected3);

        dsa::ForwardList<int> list4 = dsa::ForwardList<int>(il_2);
        list4.sort(std::less<>());
        const std::initializer_list<int> expected4{ 1, 1, 1, 1, 1, 10, 20, 30, 40, 50 };
        tests::compare("ForwardList4", list4, expected4);

        // descending
        dsa::ForwardList<int> list5 = dsa::ForwardList<int>(il_1);
        list5.sort(std::greater<>());
        const std::initializer_list<int> expected5{ 50, 40, 30, 20, 10, 5, 4, 3, 2, 1 };
        tests::compare("ForwardList5", list5, expected5);

        dsa::ForwardList<int> list6 = dsa::ForwardList<int>(il_2);
        list6.sort(std::greater<>());
        const std::initializer_list<int> expected6{ 50, 40, 30, 20, 10, 1, 1, 1, 1, 1 };
        tests::compare("ForwardList6", list6, expected6);


        std::cout << "Compare operations results with std container\n\n";

        std::forward_list<int> std_list1{ il_1 };
        std_list1.sort();
        tests::compare("ForwardList1 vs std", list1, std_list1);

        std::forward_list<int> std_list2{ il_2 };
        std_list2.sort();
        tests::compare("ForwardList2 vs std", list2, std_list2);

        std::forward_list<int> std_list3{ il_1 };
        std_list3.sort(std::less<>());
        tests::compare("ForwardList3", list3, std_list3);

        std::forward_list<int> std_list4{ il_2 };
        std_list4.sort(std::less<>());
        tests::compare("ForwardList4", list4, std_list4);

        // descending
        std::forward_list<int> std_list5{ il_1 };
        std_list5.sort(std::greater<>());
        tests::compare("ForwardList5", list5, std_list5);

        std::forward_list<int> std_list6{ il_2 };
        std_list6.sort(std::greater<>());
        tests::compare("ForwardList6", list6, std_list6);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
