/**
 * @file forward_list_unique_test.cpp
 * @brief This file tests functions checking values of ForwardList objects
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
        std::cout << "Start forward_list_unique_test:\n";

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
        auto removed1 = list1.unique();
        const std::initializer_list<int> expected1 = { 1, 2, 3, 4, 5 };
        tests::compare("ForwardList1", list1, expected1);
        tests::compare("ForwardList1 removed", removed1, size_t{ 0 });

        dsa::ForwardList<int> list2 = dsa::ForwardList<int>({ 1, 4, 2, 3, 2, 4, 3, 5, 1 });
        auto removed2 = list2.unique();
        const std::initializer_list<int> expected2 = { 1, 4, 2, 3, 2, 4, 3, 5, 1 };
        tests::compare("ForwardList2", list2, expected2);
        tests::compare("ForwardList2 removed", removed2, size_t{ 0 });

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>({ 1, 1, 2, 4, 2, 1, 3, 1, 1 });
        auto removed3 = list3.unique();
        const std::initializer_list<int> expected3 = { 1, 2, 4, 2, 1, 3, 1 };
        tests::compare("ForwardList3", list3, expected3);
        tests::compare("ForwardList3 removed", removed3, size_t{ 2 });

        dsa::ForwardList<int> list4 = dsa::ForwardList<int>({ 1, 1, 1, 2, 2, 2, 1, 1, 1 });
        auto removed4 = list4.unique();
        const std::initializer_list<int> expected4 = { 1, 2, 1 };
        tests::compare("ForwardList4", list4, expected4);
        tests::compare("ForwardList4 removed", removed4, size_t{ 6 });

        dsa::ForwardList<int> list5 = dsa::ForwardList<int>({ 0, 0, 0, 0, 0, 0 });
        auto removed5 = list5.unique();
        const std::initializer_list<int> expected5 = { 0 };
        tests::compare("ForwardList5", list5, expected5);
        tests::compare("ForwardList5 removed", removed5, size_t{ 5 });

        dsa::ForwardList<int> list6 = dsa::ForwardList<int>();
        auto removed6 = list6.unique();
        const std::initializer_list<int> expected6 = { };
        tests::compare("ForwardList6", list6, expected6);
        tests::compare("ForwardList6 removed", removed6, size_t{ 0 });

        dsa::ForwardList<int> list7;
        auto removed7 = list7.unique();
        const std::initializer_list<int> expected7 = {};
        tests::compare("ForwardList7", list7, expected7);
        tests::compare("ForwardList7 removed", removed7, size_t{ 0 });


        std::cout << "Compare operations results with std container\n\n";

        std::forward_list<int> std_list1{ 1, 2, 3, 4, 5 };
        auto std_removed1 = std_list1.unique();
        tests::compare("ForwardList1 vs std", list1, std_list1);
        tests::compare("ForwardList1 removed vs std", removed1, std_removed1);

        std::forward_list<int> std_list2{ 1, 4, 2, 3, 2, 4, 3, 5, 1 };
        auto std_removed2 = std_list2.unique();
        tests::compare("ForwardList2 vs std", list2, std_list2);
        tests::compare("ForwardList2 removed vs std", removed2, std_removed2);

        std::forward_list<int> std_list3{ 1, 1, 2, 4, 2, 1, 3, 1, 1 };
        auto std_removed3 = std_list3.unique();
        tests::compare("ForwardList3 vs std", list3, std_list3);
        tests::compare("ForwardList3 removed vs std", removed3, std_removed3);

        std::forward_list<int> std_list4{ 1, 1, 1, 2, 2, 2, 1, 1, 1 };
        auto std_removed4 = std_list4.unique();
        tests::compare("ForwardList4 vs std", list4, std_list4);
        tests::compare("ForwardList4 removed vs std", removed4, std_removed4);

        std::forward_list<int> std_list5{ 0, 0, 0, 0, 0, 0 };
        auto std_removed5 = std_list5.unique();
        tests::compare("ForwardList5 vs std", list5, std_list5);
        tests::compare("ForwardList5 removed vs std", removed5, std_removed5);

        std::forward_list<int> std_list6 = std::forward_list<int>();
        auto std_removed6 = std_list6.unique();
        tests::compare("ForwardList6 vs std", list6, std_list6);
        tests::compare("ForwardList6 removed vs std", removed6, std_removed6);

        std::forward_list<int> std_list7;
        auto std_removed7 = std_list7.unique();
        tests::compare("ForwardList7 vs std", list7, std_list7);
        tests::compare("ForwardList7 removed vs std", removed7, std_removed7);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
