/**
 * @file list_swap_test.cpp
 * @brief This file tests functions swapping List objects
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
#include <list>
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start list_swap_test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };

        dsa::List<int> list1 = dsa::List<int>(il_1);
        dsa::List<int> list2 = dsa::List<int>(il_2);
        list1.swap(list2);
        const std::initializer_list<int> expected1 = { 10, 20, 30, 40, 50 };
        tests::compare("List1", list1, expected1);
        const std::initializer_list<int> expected2 = { 1, 2, 3, 4, 5 };
        tests::compare("List2", list2, expected2);

        dsa::List<int> list3 = dsa::List<int>(il_1);
        dsa::List<int> list4;
        list3.swap(list4);
        const std::initializer_list<int> expected3 = { };
        tests::compare("List3", list3, expected3);
        const std::initializer_list<int> expected4 = { 1, 2, 3, 4, 5 };
        tests::compare("List4", list4, expected4);

        dsa::List<int> list5 = dsa::List<int>(il_1);
        dsa::List<int> list6 = dsa::List<int>(il_2);
        dsa::swap(list5, list6);
        const std::initializer_list<int> expected5 = il_2;
        tests::compare("List5", list5, expected5);
        const std::initializer_list<int> expected6 = il_1;
        tests::compare("List6", list6, expected6);

        dsa::List<int> list7 = dsa::List<int>(il_1);
        dsa::List<int> list8;
        dsa::swap(list7, list8);
        const std::initializer_list<int> expected7 = { };
        tests::compare("List7", list7, expected7);
        const std::initializer_list<int> expected8 = il_1;
        tests::compare("List8", list8, expected8);

        // swap safe type
        static_assert(noexcept(swap(std::declval<dsa::List<int>&>(),
            std::declval<dsa::List<int>&>())));
        // swap throwing type
        static_assert(noexcept(swap(std::declval<dsa::List<tests::ThrowingType>&>(),
            std::declval<dsa::List<tests::ThrowingType>&>())));


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list1{ il_1 };
        std::list<int> std_list2{ il_2 };
        std_list1.swap(std_list2);
        tests::compare("List1 vs std", list1, std_list1);
        tests::compare("List2 vs std", list2, std_list2);

        std::list<int> std_list3{ il_1 };
        std::list<int> std_list4{};
        std_list3.swap(std_list4);
        tests::compare("List3 vs std", list3, std_list3);
        tests::compare("List4 vs std", list4, std_list4);

        std::list<int> std_list5(il_1);
        std::list<int> std_list6(il_2);
        std::swap(std_list5, std_list6);
        tests::compare("List5 vs std", list5, std_list5);
        tests::compare("List6 vs std", list6, std_list6);

        std::list<int> std_list7(il_1);
        std::list<int> std_list8;
        std::swap(std_list7, std_list8);
        tests::compare("List7 vs std", list7, std_list7);
        tests::compare("List8 vs std", list8, std_list8);

        // swap safe type
        static_assert(noexcept(swap(std::declval<std::list<int>&>(),
            std::declval<std::list<int>&>())));
        // swap throwing type
        static_assert(noexcept(swap(std::declval<std::list<tests::ThrowingType>&>(),
            std::declval<std::list<tests::ThrowingType>&>())));


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
