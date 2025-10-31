/**
 * @file list_ranges_test.cpp
 * @brief This file tests List compatibility with std::ranges
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/list.h"

#include <algorithm>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <ranges>
#include <utility>
#include <vector>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        // test if class satisfies range concepts
        static_assert(std::ranges::range<dsa::List<int>>);
        static_assert(std::ranges::forward_range<dsa::List<int>>);
        static_assert(std::ranges::bidirectional_range<dsa::List<int>>);
        static_assert(!std::ranges::random_access_range<dsa::List<int>>);
        static_assert(std::ranges::common_range<dsa::List<int>>);
        static_assert(std::ranges::viewable_range<dsa::List<int>>);
        static_assert(std::ranges::sized_range<dsa::List<int>>);

        // test if iterator satisfies bidirectional_iterator concept
        static_assert(std::bidirectional_iterator<dsa::List<int>::iterator>);
        static_assert(std::bidirectional_iterator<dsa::List<int>::const_iterator>);

        // test if iterator satisfies bidirectional_iterator concept
        static_assert(std::forward_iterator<dsa::List<int>::iterator>);
        static_assert(std::forward_iterator<dsa::List<int>::const_iterator>);

        // test if iterator allows reading
        static_assert(std::input_iterator<dsa::List<int>::iterator>);
        static_assert(std::input_iterator<dsa::List<int>::const_iterator>);

        // test if iterator satisfies bidirectional_iterator concept
        static_assert(std::ranges::bidirectional_range<dsa::List<int>>);
        static_assert(std::ranges::bidirectional_range<dsa::List<int>>);

        // test if range can be read
        static_assert(std::ranges::input_range<dsa::List<int>>);
        static_assert(std::ranges::input_range<const dsa::List<int>>);

        // test if begin() and end() have the same type
        static_assert(std::ranges::common_range<dsa::List<int>>);
        static_assert(std::ranges::common_range<const dsa::List<int>>);

        // test if iterators are indirectly readable 
        static_assert(std::indirectly_readable<dsa::List<int>::iterator>);
        static_assert(std::indirectly_readable<dsa::List<int>::const_iterator>);

        // test if sentinel and iterators are comparable
        static_assert(std::sentinel_for<dsa::List<int>::iterator, dsa::List<int>::iterator>);
        static_assert(std::sentinel_for<dsa::List<int>::const_iterator, dsa::List<int>::const_iterator>);


        // test iterator forward and backward traversal and dereference correctness
        dsa::List<int> list1{ 10, 20, 30 };
        auto list1_iter = list1.begin();
        tests::compare("List1 iter == 10", *list1_iter, 10);
        ++list1_iter;
        tests::compare("List1 iter == 20", *list1_iter, 20);
        ++list1_iter;
        tests::compare("List1 iter == 30", *list1_iter, 30);
        ++list1_iter;
        tests::compare("List1 iter == end()", list1_iter == list1.end(), true);

        --list1_iter;
        tests::compare("List1 iter == 30", *list1_iter, 30);
        --list1_iter;
        tests::compare("List1 iter == 20", *list1_iter, 20);
        --list1_iter;
        tests::compare("List1 iter == 10", *list1_iter, 10);
        tests::compare("List1 iter == begin()", list1_iter == list1.begin(), true);

        // test order correctness for push_front and push_back
        dsa::List<int> list2;
        list2.push_back(20);
        list2.push_front(10);
        list2.push_back(30);
        const std::initializer_list<int> expected2{ 10, 20, 30 };
        tests::compare("List2 equal()", std::ranges::equal(list2, expected2), true);
        tests::compare("List2 front()", list2.front(), 10);
        tests::compare("List2 back()", list2.back(), 30);

        // test insert after and erase_after
        dsa::List<int> list3{ 10, 30, 40 };
        auto list3_iter = list3.begin();
        ++list3_iter;
        list3.insert(list3_iter, 20);
        const std::initializer_list<int> expected3a{ 10, 20, 30, 40 };
        tests::compare("List3a equal()", std::ranges::equal(list3, expected3a), true);

        list3_iter = list3.begin();
        ++list3_iter;
        list3.erase(list3_iter);
        const std::initializer_list<int> expected3b{ 10, 30, 40 };
        tests::compare("List3b equal()", std::ranges::equal(list3, expected3b), true);

        // test std::ranges algorithms compatibility
        dsa::List<int> list4{ 30, 10, 40 };
        tests::compare("List4 min", std::ranges::min(list4), 10);
        tests::compare("List4 max", std::ranges::max(list4), 40);
        const int sum = std::accumulate(list4.begin(), list4.end(), 0);
        tests::compare("List4 sum", sum, 80);
        std::list<int> expected4;
        std::ranges::for_each(list4, [&](int item) {expected4.push_back(item); });
        tests::compare("List4 for_each() equal()",
            std::ranges::equal(expected4, std::list{ 30, 10, 40 }), true);

        // test std::ranges::reverse_viev
        dsa::List<int> list5{ 10, 20, 30 };
        auto reversed5 = std::ranges::reverse_view(list5);
        const std::list<int> list5_reversed(reversed5.begin(), reversed5.end());
        tests::compare("List5 reverse_view", list5_reversed == std::list{ 30, 20, 10 }, true);

        // test copy constructor and assignment, create deep copies
        dsa::List<int> list6{ 10, 20, 30 };
        dsa::List<int> list7 = list6;
        tests::compare("List6 equal()", std::ranges::equal(list6, list7), true);
        list6.push_front(0);
        tests::compare("List7 equal()", std::ranges::equal(list6, list7), false);

        // test move constructor and assignment leave source empty
        dsa::List<int> list8{ 10, 20, 30 };
        dsa::List<int> list9 = std::move(list8);
        // intentional use of moved object
        // NOLINTNEXTLINE(bugprone-use-after-move)
        tests::compare("List8 empty()", list8.empty(), true);
        tests::compare("List9 equal()", std::ranges::equal(list9, std::list{ 10, 20, 30 }), true);

        // test if const_iterator works correctly
        const dsa::List<int> list10{ 10, 20, 30 };
        auto list10_iter = list10.begin();
        tests::compare("List10 iter == 1", *list10_iter, 10);
        ++list10_iter;
        tests::compare("List10 iter == 2", *list10_iter, 20);
        ++list10_iter;
        tests::compare("List10 iter == 3", *list10_iter, 30);

        // test std::ranges::subrange
        dsa::List<int> list11{ 10, 20, 30, 40 };
        auto list11_begin_iter = list11.begin();
        auto list11_end_iter = list11.end();
        std::advance(list11_begin_iter, 1);
        std::advance(list11_end_iter, -1);
        auto sub11 = std::ranges::subrange(list11_begin_iter, list11_end_iter);
        const std::list<int> expected11{ sub11.begin(), sub11.end() };
        tests::compare("List11 subrange()", expected11 == std::list{ 20, 30 }, true);
        auto sub11_reversed = std::ranges::reverse_view(sub11);
        tests::compare("List11 reverse_view()", std::ranges::equal(sub11_reversed, std::list{ 30, 20 }), true);

        // test empty list iterator and algorithms
        dsa::List<int> list12;
        tests::compare("List12 empty()", list12.empty(), true);
        tests::compare("List12 begin() == end()", list12.begin() == list12.end(), true);
        tests::compare("List12 distance == 0", std::ranges::distance(list12) == 0, true);

        // test single element list
        dsa::List<int> list13;
        list13.push_front(10);
        tests::compare("List13 empty()", list13.empty(), false);
        tests::compare("List13 front() == back()", list13.front(), list13.back());
        tests::compare("List13 distance == 1", std::ranges::distance(list13) == 1, true);

        // test if works with ranges algoritms via conversion
        dsa::List<int> list14{ 40, 30, 20, 10 };
        std::vector<int> vector14{ std::ranges::begin(list14), std::ranges::end(list14) };
        std::ranges::sort(vector14);
        tests::compare("List14 sort()", vector14 == std::vector{ 10, 20, 30, 40 }, true);

        // test std library ranges operation on custom iterators
        dsa::List<int> list15{ 10, 20, 30, 40, 50 };
        std::ranges::fill(list15, 10);
        const std::initializer_list<int> expected15 = { 10, 10, 10, 10, 10 };
        tests::compare("List15", list15, expected15);

        // test std::ranges::begin and ::end
        dsa::List<int> list16;
        tests::compare("List16 begin()", std::ranges::begin(list16) == list16.begin(), true);
        tests::compare("List16 end()", std::ranges::end(list16) == list16.end(), true);

        // test std::view
        dsa::List<int> list17 = { 10, 20, 30, 40, 50, 60 };
        const std::initializer_list<int> expected17 = { 10, 20, 30, 40, 50, 60 };
        dsa::List<int> list18;
        const std::initializer_list<int> expected18 = { 20, 40, 60 };
        auto even = list17 | std::views::filter([](int item) { return item % 20 == 0; });
        auto list18_iter = list18.begin();
        for (const int& item : even)
        {
            list18.insert(list18_iter, item);
        }
        tests::compare("List17", list17, expected17);
        tests::compare("List18", list18, expected18);


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list2;
        std_list2.push_back(20);
        std_list2.push_front(10);
        std_list2.push_back(30);
        tests::compare("List2 vs std equal()", std::ranges::equal(list2, std_list2), true);
        tests::compare("List2 vs std front()", list2.front(), std_list2.front());
        tests::compare("List2 vs std back()", list2.back(), std_list2.back());

        std::list<int> std_list6{ 10, 20, 30 };
        std::list<int> std_list7 = std_list6;
        std_list6.push_front(0);
        tests::compare("List6 vs std equal()", std::ranges::equal(list6, std_list6), true);
        tests::compare("List7 vs std equal()", std::ranges::equal(list7, std_list7), true);

        std::list<int> std_list8{ 10, 20, 30 };
        std::list<int> std_list9 = std::move(std_list8);
        // intentional use of moved object
        // NOLINTNEXTLINE(bugprone-use-after-move)
        tests::compare("List8 vs std empty()", list8.empty(), std_list8.empty());
        tests::compare("List9 vs std equal()", std::ranges::equal(list9, std_list9), true);

        std::list<int> std_list12;
        tests::compare("List12 vs std empty()", list12.empty(), std_list12.empty());
        tests::compare("List12 vs std begin() == end()",
            list12.begin() == list12.end(), std_list12.begin() == std_list12.end());
        tests::compare("List12 vs std distance == 0",
            std::ranges::distance(list12) == 0, std::ranges::distance(list12) == 0);

        std::list<int> std_list13;
        std_list13.push_front(10);
        tests::compare("List13 vs std empty()", list13.empty(), std_list13.empty());
        tests::compare("List13 vs std front() == back()", list13.front(), std_list13.back());
        tests::compare("List13 vs std front() == back()", list13.back(), std_list13.back());
        tests::compare("List13 vs std distance == 1",
            std::ranges::distance(list13) == 1, std::ranges::distance(std_list13) == 1);

        std::list<int> std_list15{ 10, 20, 30, 40, 50 };
        std::ranges::fill(std_list15, 10);
        tests::compare("List15", list15, std_list15);

        std::list<int> std_list16;
        tests::compare("List16 vs begin()",
            std::ranges::begin(list16) == list16.begin(), std::ranges::begin(std_list16) == std_list16.begin());
        tests::compare("List16 vs end()",
            std::ranges::end(list16) == list16.end(), std::ranges::end(std_list16) == std_list16.end());


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
