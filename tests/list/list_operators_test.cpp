/**
 * @file list_operators_test.cpp
 * @brief This file tests overloading operators of List
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/list.h"

#include <cassert>
#include <compare>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <list>
#include <type_traits>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start list_operators_test:\n";

        const dsa::List<int> list1({ 1, 2, 3 });
        const dsa::List<int> list2({ 1, 2, 6 });
        const dsa::List<int> list3({ 1, 2, 3, 4 });
        std::cout << "List1:\t" << list1 << '\n';
        std::cout << "List2:\t" << list2 << '\n';
        std::cout << "List3:\t" << list3 << "\n\n";

        const dsa::List<int> list4(list1 + list2);
        const std::initializer_list<int> expected4 = { 1, 2, 3, 1, 2, 6 };
        tests::compare("List4", list4, expected4);

        dsa::List<int> list5(1, 0);
        list5 += list2;
        const std::initializer_list<int> expected5 = { 0, 1, 2, 6 };
        tests::compare("List5", list5, expected5);

        dsa::List<int> list6(1, 0);
        list6 += { 1, 2, 6 };
        const std::initializer_list<int> expected6 = { 0, 1, 2, 6 };
        tests::compare("List6", list6, expected6);

        std::cout << "Compare operators for objects of the same size\n\n";

        // intentional self-comparison, an object should be equal to itself
        // NOLINTNEXTLINE(misc-redundant-expression)
        tests::compare("List1 == list1", list1 == list1, true);

        tests::compare("List1 != list2", list1 != list2, true);

        tests::compare("List1 < list2", list1 < list2, true);
        tests::compare("List2 < list1", list2 < list1, false);

        tests::compare("List1 > list2", list1 > list2, false);
        tests::compare("List2 > list1", list2 > list1, true);

        tests::compare("List1 <= list2", list1 <= list2, true);
        tests::compare("List2 <= list1", list2 <= list1, false);

        tests::compare("List1 >= list2", list1 >= list2, false);
        tests::compare("List2 >= list1", list2 >= list1, true);

        // test three way comparison

        tests::compare("list1 <=> list2 !=", (list1 <=> list2) != 0, (list1 <=> list2) != 0);
        tests::compare("list1 <=> list2 <", (list1 <=> list2) < 0, (list1 <=> list2) < 0);
        tests::compare("list1 <=> list2 >", (list1 <=> list2) > 0, (list1 <=> list2) > 0);
        tests::compare("list1 <=> list2 <=", (list1 <=> list2) <= 0, (list1 <=> list2) <= 0);
        tests::compare("list1 <=> list2 >=", (list1 <=> list2) >= 0, (list1 <=> list2) >= 0);

        tests::compare("list1 <=> list2 <", (list1 <=> list2) == std::weak_ordering::less, true);
        tests::compare("list1 <=> list2 <>", (list1 <=> list2) != std::weak_ordering::equivalent, true);
        tests::compare("list1 <=> list2 <=", (list1 <=> list2) != std::weak_ordering::greater, true);

        std::cout << "Compare operators for objects of different size\n\n";

        tests::compare("List1 == list3", list1 == list3, false);

        tests::compare("List1 != list3", list1 != list3, true);

        tests::compare("List1 < list3", list1 < list3, true);
        tests::compare("List3 < list1", list3 < list1, false);
        tests::compare("List2 < list3", list2 < list3, false);
        tests::compare("List3 < list2", list3 < list2, true);

        tests::compare("List1 > list3", list1 > list3, false);
        tests::compare("List3 > list1", list3 > list1, true);
        tests::compare("List2 > list3", list2 > list3, true);
        tests::compare("List3 > list2", list3 > list2, false);

        tests::compare("List1 <= list3", list1 <= list3, true);
        tests::compare("List3 <= list1", list3 <= list1, false);
        tests::compare("List2 <= list3", list2 <= list3, false);
        tests::compare("List3 <= list2", list3 <= list2, true);

        tests::compare("List1 >= list3", list1 >= list3, false);
        tests::compare("List3 >= list1", list3 >= list1, true);
        tests::compare("List2 >= list3", list2 >= list3, true);
        tests::compare("List3 >= list2", list3 >= list2, false);

        // test three way comparison

        tests::compare("list1 <=> list3 ==", (list1 <=> list3) == 0, false);
        tests::compare("list1 <=> list3 <", (list1 <=> list3) < 0, true);
        tests::compare("list1 <=> list3 >", (list1 <=> list3) > 0, false);
        tests::compare("list1 <=> list3 <=", (list1 <=> list3) <= 0, true);
        tests::compare("list1 <=> list3 >=", (list1 <=> list3) >= 0, false);

        tests::compare("list1 <=> list3 >=", (list1 <=> list3) != std::weak_ordering::less, false);
        tests::compare("list1 <=> list3 ==", (list1 <=> list3) == std::weak_ordering::equivalent, false);
        tests::compare("list1 <=> list3 <=", (list1 <=> list3) != std::weak_ordering::greater, true);

        // test comparison categories
        static_assert(std::is_same_v<std::compare_three_way_result_t<dsa::List<int>>, std::strong_ordering>,
            "Int list should support strong ordering");

        static_assert(std::is_same_v<std::compare_three_way_result_t<dsa::List<double>>, std::partial_ordering>,
            "Double list should support strong ordering");

        // test partial ordering
        const dsa::List<double> list7{ 1.0, 2.0, 3.0 };
        const dsa::List<double> list8{ 1.0, 2.0, std::numeric_limits<double>::quiet_NaN() };
        assert((list7 <=> list8) == std::partial_ordering::unordered);
        tests::compare("list7 <=> list8 weak ordering", (list7 <=> list8) != std::weak_ordering::less, true);

        // test noexcept

        // operators
        static_assert(!noexcept(dsa::List<tests::ThrowingType>{1} == dsa::List<tests::ThrowingType>{1}));
        static_assert(!noexcept(dsa::List<tests::ThrowingType>{1} <=> dsa::List<tests::ThrowingType>{1}));


        std::cout << "Compare operations results with std container\n\n";

        const std::list<int> std_list1({ 1, 2, 3 });
        const std::list<int> std_list2({ 1, 2, 6 });
        const std::list<int> std_list3({ 1, 2, 3, 4 });

        // intentional self-comparison, an object should be equal to itself
        // NOLINTNEXTLINE(misc-redundant-expression)
        tests::compare("List1 == list1 vs std", list1 == list1, std_list1 == std_list1);

        tests::compare("List1 != list2 vs std", list1 != list2, std_list1 != std_list2);

        tests::compare("List1 < list2 vs std", list1 < list2, std_list1 < std_list2);
        tests::compare("List2 < list1 vs std", list2 < list1, std_list2 < std_list1);

        tests::compare("List1 > list2 vs std", list1 > list2, std_list1 > std_list2);
        tests::compare("List2 > list1 vs std", list2 > list1, std_list2 > std_list1);

        tests::compare("List1 <= list2 vs std", list1 <= list2, std_list1 <= std_list2);
        tests::compare("List2 <= list1 vs std", list2 <= list1, std_list2 <= std_list1);

        tests::compare("List1 >= list2 vs std", list1 >= list2, std_list1 >= std_list2);
        tests::compare("List2 >= list1 vs std", list2 >= list1, std_list2 >= std_list1);

        // test three way comparison

        tests::compare("list1 <=> list2 vs std !=", (list1 <=> list2) != 0, (std_list1 <=> std_list2) != 0);
        tests::compare("list1 <=> list2 vs std <", (list1 <=> list2) < 0, (std_list1 <=> std_list2) < 0);
        tests::compare("list1 <=> list2 vs std >", (list1 <=> list2) > 0, (std_list1 <=> std_list2) > 0);
        tests::compare("list1 <=> list2 vs std <=", (list1 <=> list2) <= 0, (std_list1 <=> std_list2) <= 0);
        tests::compare("list1 <=> list2 vs std >=", (list1 <=> list2) >= 0, (std_list1 <=> std_list2) >= 0);

        tests::compare("list1 <=> list2 vs std <",
            (list1 <=> list2) == std::weak_ordering::less, (std_list1 <=> std_list2) == std::weak_ordering::less);
        tests::compare("list1 <=> list2 vs std <>",
            (list1 <=> list2) != std::weak_ordering::equivalent, (std_list1 <=> std_list2) != std::weak_ordering::equivalent);
        tests::compare("list1 <=> list2 vs std <=",
            (list1 <=> list2) != std::weak_ordering::greater, (std_list1 <=> std_list2) != std::weak_ordering::greater);

        std::cout << "Compare operators for objects of different size\n\n";

        tests::compare("List1 == list3 vs std", list1 == list3, std_list1 == std_list3);

        tests::compare("List1 != list3 vs std", list1 != list3, std_list1 != std_list3);

        tests::compare("List1 < list3 vs std", list1 < list3, std_list1 < std_list3);
        tests::compare("List3 < list1 vs std", list3 < list1, std_list3 < std_list1);
        tests::compare("List2 < list3 vs std", list2 < list3, std_list2 < std_list3);
        tests::compare("List3 < list2 vs std", list3 < list2, std_list3 < std_list2);

        tests::compare("List1 > list3 vs std", list1 > list3, std_list1 > std_list3);
        tests::compare("List3 > list1 vs std", list3 > list1, std_list3 > std_list1);
        tests::compare("List2 > list3 vs std", list2 > list3, std_list2 > std_list3);
        tests::compare("List3 > list2 vs std", list3 > list2, std_list3 > std_list2);

        tests::compare("List1 <= list3 vs std", list1 <= list3, std_list1 <= std_list3);
        tests::compare("List3 <= list1 vs std", list3 <= list1, std_list3 <= std_list1);
        tests::compare("List2 <= list3 vs std", list2 <= list3, std_list2 <= std_list3);
        tests::compare("List3 <= list2 vs std", list3 <= list2, std_list3 <= std_list2);

        tests::compare("List1 >= list3 vs std", list1 >= list3, std_list1 >= std_list3);
        tests::compare("List3 >= list1 vs std", list3 >= list1, std_list3 >= std_list1);
        tests::compare("List2 >= list3 vs std", list2 >= list3, std_list2 >= std_list3);
        tests::compare("List3 >= list2 vs std", list3 >= list2, std_list3 >= std_list2);

        // test three way comparison

        tests::compare("list1 <=> list3 vs std ==", (list1 <=> list3) == 0, (std_list1 <=> std_list3) == 0);
        tests::compare("list1 <=> list3 vs std <", (list1 <=> list3) < 0, (std_list1 <=> std_list3) < 0);
        tests::compare("list1 <=> list3 vs std >", (list1 <=> list3) > 0, (std_list1 <=> std_list3) > 0);
        tests::compare("list1 <=> list3 vs std <=", (list1 <=> list3) <= 0, (std_list1 <=> std_list3) <= 0);
        tests::compare("list1 <=> list3 vs std >=", (list1 <=> list3) >= 0, (std_list1 <=> std_list3) >= 0);

        tests::compare("list1 <=> list3 vs std >=",
            (list1 <=> list3) != std::weak_ordering::less, (std_list1 <=> std_list3) != std::weak_ordering::less);
        tests::compare("list1 <=> list3 vs std ==",
            (list1 <=> list3) == std::weak_ordering::equivalent, (std_list1 <=> std_list3) == std::weak_ordering::equivalent);
        tests::compare("list1 <=> list3 vs std <= ",
            (list1 <=> list3) != std::weak_ordering::greater, (std_list1 <=> std_list3) != std::weak_ordering::greater);

        // test comparison categories
        static_assert(std::is_same_v<std::compare_three_way_result_t<std::list<int>>, std::strong_ordering>,
            "Int list should support strong ordering");

        static_assert(std::is_same_v<std::compare_three_way_result_t<std::list<double>>, std::partial_ordering>,
            "Double list should support strong ordering");

        // test partial ordering
        const std::list<double> std_list7{ 1.0, 2.0, 3.0 };
        const std::list<double> std_list8{ 1.0, 2.0, std::numeric_limits<double>::quiet_NaN() };
        assert((std_list7 <=> std_list8) == std::partial_ordering::unordered);
        assert((list7 <=> list8) == (std_list7 <=> std_list8));
        tests::compare("std_list7 <=> std_list8 weak ordering",
            (std_list7 <=> std_list8) == std::partial_ordering::unordered, true);
        tests::compare("(list7 <=> list8) == (std_list7 <=> std_list8)",
            (list7 <=> list8) == (std_list7 <=> std_list8), true);

        // test noexcept

        // operators
        static_assert(!noexcept(std::list<tests::ThrowingType>{1} == std::list<tests::ThrowingType>{1}));
        static_assert(!noexcept(std::list<tests::ThrowingType>{1} <=> std::list<tests::ThrowingType>{1}));


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}