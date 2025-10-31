/**
 * @file forward_list_ranges_test.cpp
 * @brief This file tests ForwardList compatibility with std::ranges
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/forward_list.h"

#include <algorithm>
#include <exception>
#include <forward_list>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <ranges>
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        // test if class satisfies range concepts
        static_assert(std::ranges::range<dsa::ForwardList<int>>);
        static_assert(std::ranges::forward_range<dsa::ForwardList<int>>);
        static_assert(!std::ranges::bidirectional_range<dsa::ForwardList<int>>);
        static_assert(!std::ranges::random_access_range<dsa::ForwardList<int>>);
        static_assert(std::ranges::common_range<dsa::ForwardList<int>>);

        static_assert(std::ranges::viewable_range<dsa::ForwardList<int>>);
        // sized_range is tested because of size() method in ForwardList class
        // std::forward_list do not satisfy this condition
        static_assert(std::ranges::sized_range<dsa::ForwardList<int>>);

        // test if iterators satisfies forward_iterator concept
        static_assert(std::forward_iterator<dsa::ForwardList<int>::iterator>);
        static_assert(std::forward_iterator<dsa::ForwardList<int>::const_iterator>);

        // test if iterator allows reading
        static_assert(std::input_iterator<dsa::ForwardList<int>::iterator>);
        static_assert(std::input_iterator<dsa::ForwardList<int>::const_iterator>);

        // test if iterator allows writing
        static_assert(std::output_iterator<dsa::ForwardList<int>::iterator, int>);
        static_assert(!std::output_iterator<dsa::ForwardList<int>::const_iterator, int>);

        // test if range can be read
        static_assert(std::ranges::input_range<dsa::ForwardList<int>>);
        static_assert(std::ranges::input_range<const dsa::ForwardList<int>>);

        // test if begin() and end() have the same type
        static_assert(std::ranges::common_range<dsa::ForwardList<int>>);
        static_assert(std::ranges::common_range<const dsa::ForwardList<int>>);

        // test if iterators are indirectly readable 
        static_assert(std::indirectly_readable<dsa::ForwardList<int>::iterator>);
        static_assert(std::indirectly_readable<dsa::ForwardList<int>::const_iterator>);

        // test if sentinel and iterators are comparable
        static_assert(std::sentinel_for<dsa::ForwardList<int>::iterator, dsa::ForwardList<int>::iterator>);
        static_assert(std::sentinel_for<dsa::ForwardList<int>::const_iterator, dsa::ForwardList<int>::const_iterator>);


        // test iterator traversal and dereference correctness
        dsa::ForwardList<int> list1{ 10, 20, 30 };
        auto list1_iter = list1.begin();
        tests::compare("ForwardList1 iter == 10", *list1_iter, 10);
        ++list1_iter;
        tests::compare("ForwardList1 iter == 20", *list1_iter, 20);
        ++list1_iter;
        tests::compare("ForwardList1 iter == 30", *list1_iter, 30);
        ++list1_iter;
        tests::compare("ForwardList1 iter == end()", list1_iter == list1.end(), true);

        // test order correctness
        dsa::ForwardList<int> list2;
        list2.push_front(30);
        list2.push_front(20);
        list2.push_front(10);
        const std::initializer_list<int> expected2{ 10, 20, 30 };
        tests::compare("ForwardList2 equal()", std::ranges::equal(list2, expected2), true);

        // test insert after and erase_after
        dsa::ForwardList<int> list3{ 10, 20, 40 };
        auto list3_iter = list3.begin();
        list3.insert_after(list3_iter, 30);
        const std::initializer_list<int> expected3a{ 10, 30, 20, 40 };
        tests::compare("ForwardList3a equal()", std::ranges::equal(list3, expected3a), true);

        list3.erase_after(list3.begin());
        const std::initializer_list<int> expected3b{ 10, 20, 40 };
        tests::compare("ForwardList3b equal()", std::ranges::equal(list3, expected3b), true);

        // test std::ranges algorithms compatibility
        dsa::ForwardList<int> list4{ 30, 10, 40 };
        tests::compare("ForwardList4 min", std::ranges::min(list4), 10);
        const int sum = std::accumulate(list4.begin(), list4.end(), 0);
        tests::compare("ForwardList4 sum", sum, 80);
        std::list<int> expected4;
        std::ranges::for_each(list4, [&](int item) {expected4.push_back(item); });
        tests::compare("ForwardList4 for_each() equal()", std::ranges::equal(expected4, std::list{ 30, 10, 40 }), true);

        // test copy constructor and assignment, create deep copies
        dsa::ForwardList<int> list5{ 10, 20, 30 };
        dsa::ForwardList<int> list6 = list5;
        tests::compare("ForwardList5 equal()", std::ranges::equal(list5, list6), true);
        list5.push_front(0);
        tests::compare("ForwardList6 equal()", std::ranges::equal(list5, list6), false);

        // test move constructor and assignment leave source empty
        dsa::ForwardList<int> list7{ 10, 20, 30 };
        dsa::ForwardList<int> list8 = std::move(list7);
        // intentional use of moved object
        // NOLINTNEXTLINE(bugprone-use-after-move)
        tests::compare("ForwardList7 empty()", list7.empty(), true);
        tests::compare("ForwardList8 equal()", std::ranges::equal(list8, std::list{ 10, 20, 30 }), true);

        // test if const_iterator works correctly
        const dsa::ForwardList<int> list9{ 10, 20, 30 };
        auto list9_iter = list9.begin();
        tests::compare("ForwardList9 iter == 1", *list9_iter, 10);
        ++list9_iter;
        tests::compare("ForwardList9 iter == 2", *list9_iter, 20);

        // test std::ranges::subrange
        const dsa::ForwardList<int> list10{ 10, 20, 30 };
        auto sub = std::ranges::subrange(list10.begin(), list10.end());
        const std::list<int> expected10(sub.begin(), sub.end());
        tests::compare("ForwardList10", expected10 == std::list{ 10, 20, 30 }, true);

        // test empty list iterator and algorithms
        dsa::ForwardList<int> list11;
        tests::compare("ForwardList11 empty()", list11.empty(), true);
        tests::compare("ForwardList11 begin() == end()", list11.begin() == list11.end(), true);
        tests::compare("ForwardList11 distance == 0", std::ranges::distance(list11) == 0, true);

        // test single element list
        dsa::ForwardList<int> list12;
        list12.push_front(10);
        tests::compare("ForwardList12 empty", list12.empty(), false);
        tests::compare("ForwardList12 begin() == end()", *list12.begin() == 10, true);
        tests::compare("ForwardList12 distance == 1", std::ranges::distance(list12) == 1, true);

        // test std library ranges operation on custom iterators
        dsa::ForwardList<int> list13{ 10, 20, 30, 40, 50 };
        std::ranges::fill(list13, 10);
        const std::initializer_list<int> expected13 = { 10, 10, 10, 10, 10 };
        tests::compare("ForwardList13", list13, expected13);

        // test std::ranges::begin and ::end
        dsa::ForwardList<int> list14;
        tests::compare("ForwardList14 begin()", std::ranges::begin(list14) == list14.begin(), true);
        tests::compare("ForwardList14 end()", std::ranges::end(list14) == list14.end(), true);

        // test std::view
        dsa::ForwardList<int> list15 = { 10, 20, 30, 40, 50, 60 };
        const std::initializer_list<int> expected15 = { 10, 20, 30, 40, 50, 60 };
        dsa::ForwardList<int> list16;
        const std::initializer_list<int> expected16 = { 20, 40, 60 };
        auto even = list15 | std::views::filter([](int item) { return item % 20 == 0; });
        auto list16_iter = list16.before_begin();
        for (const int& item : even)
        {
            list16.insert_after(list16_iter, item);
            ++list16_iter;
        }
        tests::compare("ForwardList15", list15, expected15);
        tests::compare("ForwardList16", list16, expected16);


        std::cout << "Compare operations results with std container\n\n";

        std::forward_list<int> std_list2;
        std_list2.push_front(30);
        std_list2.push_front(20);
        std_list2.push_front(10);
        tests::compare("ForwardList2 vs std equal()", std::ranges::equal(list2, std_list2), true);

        std::forward_list<int> std_list5{ 10, 20, 30 };
        std::forward_list<int> std_list6 = std_list5;
        std_list5.push_front(0);
        tests::compare("ForwardList5 vs std equal()", std::ranges::equal(list5, std_list5), true);
        tests::compare("ForwardList6 vs std equal()", std::ranges::equal(list6, std_list6), true);

        std::forward_list<int> std_list7{ 10, 20, 30 };
        std::forward_list<int> std_list8 = std::move(std_list7);
        // intentional use of moved object
        // NOLINTNEXTLINE(bugprone-use-after-move)
        tests::compare("ForwardList7 vs std", list7.empty(), std_list7.empty());
        tests::compare("ForwardList8 vs std equal()", std::ranges::equal(list8, std_list8), true);

        std::forward_list<int> std_list11;
        tests::compare("ForwardList11 vs std empty()", list11.empty(), std_list11.empty());
        tests::compare("ForwardList11 vs std begin() == end()",
            list11.begin() == list11.end(), std_list11.begin() == std_list11.end());
        tests::compare("ForwardList11 vs std distance",
            std::ranges::distance(list11), std::ranges::distance(std_list11));

        std::forward_list<int> std_list12;
        std_list12.push_front(10);
        tests::compare("ForwardList12 vs std empty()", list12.empty(), std_list12.empty());
        tests::compare("ForwardList12 vs std begin() == end()", *list12.begin(), *std_list12.begin());
        tests::compare("ForwardList12 vs std distance",
            std::ranges::distance(list12), std::ranges::distance(std_list12));

        std::forward_list<int> std_list13{ 10, 20, 30, 40, 50 };
        std::ranges::fill(std_list13, 10);
        tests::compare("ForwardList13 vs std", list13, std_list13);

        // test std::ranges::begin and ::end
        dsa::ForwardList<int> std_list14;
        tests::compare("ForwardList14 vs begin()",
            std::ranges::begin(list14) == list14.begin(), std::ranges::begin(std_list14) == std_list14.begin());
        tests::compare("ForwardList14 vs end()",
            std::ranges::end(list14) == list14.end(), std::ranges::end(std_list14) == std_list14.end());


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
