/**
 * @file array_ranges_test.cpp
 * @brief This file tests array compatibility with std::ranges
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/array.h"

#include <algorithm>
#include <array>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <ranges>
#include <type_traits>
#include <vector>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        using array_t = dsa::Array<int, 3>;
        using const_array_t = const dsa::Array<int, 3>;

        // test if class satisfies range concepts
        static_assert(std::ranges::range<array_t>);
        static_assert(std::ranges::range<const_array_t>);

        // test forward / bidirectional / input range
        static_assert(std::ranges::forward_range<array_t>);
        static_assert(std::ranges::forward_range<const_array_t>);

        static_assert(std::ranges::bidirectional_range<array_t>);
        static_assert(std::ranges::bidirectional_range<const_array_t>);

        static_assert(std::ranges::input_range<array_t>);
        static_assert(std::ranges::input_range<const_array_t>);

        // test contiguous range
        static_assert(std::ranges::contiguous_range<array_t>);
        static_assert(std::ranges::contiguous_range<const_array_t>);

        // test borrowed range
        static_assert(std::ranges::borrowed_range<array_t>);
        static_assert(std::ranges::borrowed_range<const_array_t>);

        // test random access range
        static_assert(std::ranges::random_access_range<array_t>);
        static_assert(std::ranges::random_access_range<const_array_t>);

        // test viewble range
        static_assert(std::ranges::viewable_range<array_t>);
        static_assert(std::ranges::viewable_range<const_array_t>);

        // test sized range
        static_assert(std::ranges::sized_range<array_t>);
        static_assert(std::ranges::sized_range<const_array_t>);

        // test common range
        static_assert(std::ranges::common_range<array_t>);
        static_assert(std::ranges::common_range<const_array_t>);

        // test view range
        static_assert(std::ranges::view<array_t>);
        static_assert(!std::ranges::view<const_array_t>);


        // test constexpt access via iterators
        constexpr array_t array{ 1, 2, 3 };
        static_assert(*array.begin() == 1);
        static_assert(*(array.end() - 1) == 3);
        static_assert(std::ranges::size(array) == 3);

        // test structured binding / tuple interface
        static_assert(std::tuple_size<array_t>::value == 3);
        static_assert(std::is_same_v<std::tuple_element<0, array_t>::type, int>);
        static_assert(get<0>(array) == 1);
        static_assert(get<1>(array) == 2);
        static_assert(get<2>(array) == 3);

        // test if iterator satisfies bidirectional_iterator concept
        static_assert(std::bidirectional_iterator<array_t::iterator>);
        static_assert(std::bidirectional_iterator<array_t::const_iterator>);

        static_assert(std::bidirectional_iterator<const_array_t::iterator>);
        static_assert(std::bidirectional_iterator<const_array_t::const_iterator>);

        // test if iterator satisfies bidirectional_iterator concept
        static_assert(std::forward_iterator<array_t::iterator>);
        static_assert(std::forward_iterator<array_t::const_iterator>);

        static_assert(std::forward_iterator<const_array_t::iterator>);
        static_assert(std::forward_iterator<const_array_t::const_iterator>);

        // test if iterator allows reading
        static_assert(std::input_iterator<array_t::iterator>);
        static_assert(std::input_iterator<array_t::const_iterator>);

        static_assert(std::input_iterator<const_array_t::iterator>);
        static_assert(std::input_iterator<const_array_t::const_iterator>);

        // test if iterator satisfies bidirectional_iterator concept
        static_assert(std::ranges::bidirectional_range<array_t>);
        static_assert(std::ranges::bidirectional_range<const_array_t>);

        // test if range can be read
        static_assert(std::ranges::input_range<array_t>);
        static_assert(std::ranges::input_range<const_array_t>);

        // test if begin() and end() have the same type
        static_assert(std::ranges::common_range<array_t>);
        static_assert(std::ranges::common_range<const_array_t>);

        // test if iterators are indirectly readable 
        static_assert(std::indirectly_readable<array_t::iterator>);
        static_assert(std::indirectly_readable<array_t::const_iterator>);

        static_assert(std::indirectly_readable<const_array_t::iterator>);
        static_assert(std::indirectly_readable<const_array_t::const_iterator>);

        // test if sentinel and iterators are comparable
        static_assert(std::sentinel_for<array_t::iterator, array_t::iterator>);
        static_assert(std::sentinel_for<array_t::const_iterator, array_t::const_iterator>);

        static_assert(std::sentinel_for<const_array_t::iterator, const_array_t::iterator>);
        static_assert(std::sentinel_for<const_array_t::const_iterator, const_array_t::const_iterator>);

        // test iterator properties
        static_assert(std::is_same_v<std::ranges::iterator_t<array_t>, int*>);
        static_assert(std::is_same_v<std::ranges::iterator_t<const_array_t>, const int*>);

        // test sentinel properties
        static_assert(std::is_same_v<std::ranges::sentinel_t<array_t>, int*>);
        static_assert(std::is_same_v<std::ranges::sentinel_t<const_array_t>, const int*>);

        // test iterator forward and backward traversal and dereference correctness
        dsa::Array<int, 3> array1{ 10, 20, 30 };
        auto* array1_iter = array1.begin();
        tests::compare("Array1 iter == 10", *array1_iter, 10);
        std::advance(array1_iter, 1);
        tests::compare("Array1 iter == 20", *array1_iter, 20);
        std::advance(array1_iter, 1);
        tests::compare("Array1 iter == 30", *array1_iter, 30);
        std::advance(array1_iter, 1);
        tests::compare("Array1 iter == end()", array1_iter == array1.end(), true);

        std::advance(array1_iter, -1);
        tests::compare("Array1 iter == 30", *array1_iter, 30);
        std::advance(array1_iter, -1);
        tests::compare("Array1 iter == 20", *array1_iter, 20);
        std::advance(array1_iter, -1);
        tests::compare("Array1 iter == 10", *array1_iter, 10);
        tests::compare("Array1 iter == begin()", array1_iter == array1.begin(), true);

        // test order correctness for push_front and push_back
        dsa::Array<int, 3> array2;
        array2[0] = 10;
        array2[1] = 20;
        array2[2] = 30;
        const std::initializer_list<int> expected2{ 10, 20, 30 };
        tests::compare("Array2 equal()", std::ranges::equal(array2, expected2), true);
        tests::compare("Array2 front()", array2.front(), 10);
        tests::compare("Array2 back()", array2.back(), 30);

        // test std::ranges algorithms compatibility
        dsa::Array<int, 3> array3{ 30, 10, 40 };
        tests::compare("Array3 min", std::ranges::min(array3), 10);
        tests::compare("Array3 max", std::ranges::max(array3), 40);
        const int sum = std::accumulate(array3.begin(), array3.end(), 0);
        tests::compare("Array3 sum", sum, 80);
        std::list<int> expected3;
        std::ranges::for_each(array3, [&](int item) { expected3.push_back(item); });
        tests::compare("Array3 for_each() equal()",
            std::ranges::equal(expected3, std::list{ 30, 10, 40 }), true);

        // test std::ranges::reverse_viev
        const dsa::Array<int, 3> array4{ 10, 20, 30 };
        auto reversed4 = std::ranges::reverse_view(array4);
        const std::list<int> array4_reversed(reversed4.begin(), reversed4.end());
        tests::compare("Array4 reverse_view", array4_reversed == std::list{ 30, 20, 10 }, true);

        // test copy constructor and assignment, create deep copies
        dsa::Array<int, 3> array5{ 10, 20, 30 };
        dsa::Array<int, 3> array6 = array5;
        tests::compare("Array5 equal()", std::ranges::equal(array5, array6), true);
        array5.at(0) = 0;
        tests::compare("Array6 equal()", std::ranges::equal(array5, array6), false);

        // test copy constructor
        const dsa::Array<int, 3> expected7{ 10, 20, 30 };
        dsa::Array<int, 3> array7 = expected7;
        tests::compare("Array7 empty()", array7.empty(), false);
        tests::compare("Array7 equal()", std::ranges::equal(array7, std::list{ 10, 20, 30 }), true);

        // test if const_iterator works correctly
        const dsa::Array<int, 3> array8{ 10, 20, 30 };
        const auto* array8_iter = array8.begin();
        tests::compare("Array8 iter == 1", *array8_iter, 10);
        std::advance(array8_iter, 1);
        tests::compare("Array8 iter == 2", *array8_iter, 20);
        std::advance(array8_iter, 1);
        tests::compare("Array8 iter == 3", *array8_iter, 30);

        // test std::ranges::subrange
        dsa::Array<int, 4> array9{ 10, 20, 30, 40 };
        auto* array9_begin_iter = array9.begin();
        auto* array9_end_iter = array9.end();
        std::advance(array9_begin_iter, 1);
        std::advance(array9_end_iter, -1);
        auto sub9 = std::ranges::subrange(array9_begin_iter, array9_end_iter);
        const std::list<int> expected9{ sub9.begin(), sub9.end() };
        tests::compare("Array9 subrange()", expected9 == std::list{ 20, 30 }, true);
        auto sub9_reversed = std::ranges::reverse_view(sub9);
        tests::compare("Array9 reverse_view()", std::ranges::equal(sub9_reversed, std::list{ 30, 20 }), true);

        // test empty array iterator and algorithms
        dsa::Array<int, 0> array10;
        tests::compare("Array10 empty()", array10.empty(), true);
        tests::compare("Array10 begin() == end()", array10.begin() == array10.end(), true);
        tests::compare("Array10 distance == 0", std::ranges::distance(array10) == 0, true);

        // test single element array
        dsa::Array<int, 3> array11;
        array11.at(0) = 10;
        const std::initializer_list<int> expected11{ 10, 0, 0 };
        tests::compare("Array11", array11, expected11);
        tests::compare("Array11 empty()", array11.empty(), false);
        tests::compare("Array11 front() == back()", array11.front() == array11.back(), false);
        tests::compare("Array11 distance == 1", std::ranges::distance(array11) == 3, true);

        // test if works with ranges algoritms via conversion
        dsa::Array<int, 4> array12{ 40, 30, 20, 10 };
        std::vector<int> vector12{ std::ranges::begin(array12), std::ranges::end(array12) };
        std::ranges::sort(vector12);
        tests::compare("Array12 sort()", vector12 == std::vector{ 10, 20, 30, 40 }, true);

        // test std library ranges operation on custom iterators
        dsa::Array<int, 5> array13{ 10, 20, 30, 40, 50 };
        std::ranges::fill(array13, 10);
        const std::initializer_list<int> expected13 = { 10, 10, 10, 10, 10 };
        tests::compare("Array13", array13, expected13);

        // test std::ranges::begin and ::end
        dsa::Array<int, 3> array14;
        tests::compare("Array14 begin()", std::ranges::begin(array14) == array14.begin(), true);
        tests::compare("Array14 end()", std::ranges::end(array14) == array14.end(), true);

        // test std::view
        const dsa::Array<int, 6> array15 = { 10, 20, 30, 40, 50, 60 };
        const std::initializer_list<int> expected15 = { 10, 20, 30, 40, 50, 60 };
        std::vector<int> expected16;
        const dsa::Array<int, 3> array16 = { 20, 40, 60 };
        auto even = array15 | std::views::filter([](int item) { return item % 20 == 0; });
        for (const int& item : even)
        {
            expected16.push_back(item);
        }
        tests::compare("Array15", array15, expected15);
        tests::compare("Array16", array16, expected16);


        std::cout << "Compare operations results with std container\n\n";

        std::array<int, 3> std_array2{};
        std_array2[0] = 10;
        std_array2[1] = 20;
        std_array2[2] = 30;
        tests::compare("Array2 vs std equal()", std::ranges::equal(array2, std_array2), true);
        tests::compare("Array2 vs std front()", array2.front(), std_array2.front());
        tests::compare("Array2 vs std back()", array2.back(), std_array2.back());

        std::array<int, 3> std_array5{ 10, 20, 30 };
        std::array<int, 3> std_array6 = std_array5;
        std_array5.at(0) = 0;
        tests::compare("Array5 vs std equal()", std::ranges::equal(array5, std_array5), true);
        tests::compare("Array6 vs std equal()", std::ranges::equal(array6, std_array6), true);

        const std::array<int, 3> std_array7{ 10, 20, 30 };
        std::array<int, 3> std_array8 = std_array7;
        tests::compare("Array7 vs std empty()", array8.empty(), std_array8.empty());
        tests::compare("Array8 vs std equal()", std::ranges::equal(array8, std_array8), true);

        std::array<int, 0> std_array10{};
        tests::compare("Array10 vs std empty()", array10.empty(), std_array10.empty());
        tests::compare("Array10 vs std begin() == end()",
            array10.begin() == array10.end(), std_array10.begin() == std_array10.end());
        tests::compare("Array10 vs std distance == 0",
            std::ranges::distance(array10) == 0, std::ranges::distance(array10) == 0);

        std::array<int, 3> std_array11{};
        std_array11.at(0) = 10;
        tests::compare("Array11 vs std empty()", array11.empty(), std_array11.empty());
        tests::compare("Array11 vs std front() == back()", array11.front(), std_array11.front());
        tests::compare("Array11 vs std front() == back()", array11.back(), std_array11.back());
        tests::compare("Array11 vs std distance == 1",
            std::ranges::distance(array11) == 1, std::ranges::distance(std_array11) == 1);

        std::array<int, 5> std_array13{ 10, 20, 30, 40, 50 };
        std::ranges::fill(std_array13, 10);
        tests::compare("Array13", array13, std_array13);

        std::array<int, 3> std_array14{};
        tests::compare("Array14 vs begin()",
            std::ranges::begin(array14) == array14.begin(), std::ranges::begin(std_array14) == std_array14.begin());
        tests::compare("Array14 vs end()",
            std::ranges::end(array14) == array14.end(), std::ranges::end(std_array14) == std_array14.end());


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
