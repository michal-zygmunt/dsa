/**
 * @file forward_list_swap_test.cpp
 * @brief This file tests functions swapping ForwardList objects
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
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start forward_list_swap_test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list2 = dsa::ForwardList<int>(il_2);
        list1.swap(list2);
        const std::initializer_list<int> expected1 = il_2;
        tests::compare("ForwardList1", list1, expected1);
        const std::initializer_list<int> expected2 = il_1;
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list4;
        list3.swap(list4);
        const std::initializer_list<int> expected3 = { };
        tests::compare("ForwardList3", list3, expected3);
        const std::initializer_list<int> expected4 = il_1;
        tests::compare("ForwardList4", list4, expected4);

        dsa::ForwardList<int> list5 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list6 = dsa::ForwardList<int>(il_2);
        dsa::swap(list5, list6);
        const std::initializer_list<int> expected5 = il_2;
        tests::compare("ForwardList5", list5, expected5);
        const std::initializer_list<int> expected6 = il_1;
        tests::compare("ForwardList6", list6, expected6);

        dsa::ForwardList<int> list7 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list8;
        dsa::swap(list7, list8);
        const std::initializer_list<int> expected7 = { };
        tests::compare("ForwardList7", list7, expected7);
        const std::initializer_list<int> expected8 = il_1;
        tests::compare("ForwardList8", list8, expected8);

        struct ThrowingType
        {
            ThrowingType() = default;
            ~ThrowingType() = default;
            ThrowingType(const ThrowingType&) = default;
            ThrowingType(ThrowingType&&) = default;

            auto operator=(ThrowingType&& /*other*/) noexcept(false) -> ThrowingType&
            {
                return *this;
            }

            auto operator=(const ThrowingType& other) noexcept(false) -> ThrowingType&
            {
                // empty if statement silences clang-tidy warning for copy assignment operator in mock struct
                if (this != &other) {}
                return *this;
            }
        };

        // swap safe type
        static_assert(noexcept(swap(std::declval<dsa::ForwardList<int>&>(),
            std::declval<dsa::ForwardList<int>&>())));
        // swap throwing type
        static_assert(!noexcept(swap(std::declval<dsa::ForwardList<ThrowingType>&>(),
            std::declval<dsa::ForwardList<ThrowingType>&>())));


        std::cout << "Compare operations results with std container\n\n";

        std::forward_list<int> std_list1{ il_1 };
        std::forward_list<int> std_list2{ il_2 };
        std_list1.swap(std_list2);
        tests::compare("ForwardList1 vs std", list1, std_list1);
        tests::compare("ForwardList2 vs std", list2, std_list2);

        std::forward_list<int> std_list3{ il_1 };
        std::forward_list<int> std_list4{};
        std_list3.swap(std_list4);
        tests::compare("ForwardList3 vs std", list3, std_list3);
        tests::compare("ForwardList4 vs std", list4, std_list4);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
