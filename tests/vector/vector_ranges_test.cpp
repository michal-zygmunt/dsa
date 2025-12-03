/**
 * @file vector_ranges_test.cpp
 * @brief This file tests Vector compatibility with std::ranges
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/vector.h"

#include <algorithm>
#include <cstddef>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
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
        std::cout << "Start vector_ranges_test:\n";

        using vector_t = dsa::Vector<int>;
        using const_vector_t = const dsa::Vector<int>;

        // test if class satisfies range concepts
        static_assert(std::ranges::range<vector_t>);
        static_assert(std::ranges::range<const_vector_t>);

        // test forward / bidirectional / input range / output range
        static_assert(std::ranges::forward_range<vector_t>);
        static_assert(std::ranges::forward_range<const_vector_t>);

        static_assert(std::ranges::bidirectional_range<vector_t>);
        static_assert(std::ranges::bidirectional_range<const_vector_t>);

        static_assert(std::ranges::input_range<vector_t>);
        static_assert(std::ranges::input_range<const_vector_t>);

        static_assert(std::ranges::output_range<vector_t, int>);
        static_assert(!std::ranges::output_range<const_vector_t, int>);

        // test contiguous range
        static_assert(std::ranges::contiguous_range<vector_t>);
        static_assert(std::ranges::contiguous_range<const_vector_t>);

        static_assert(std::contiguous_iterator<vector_t::iterator>);
        static_assert(std::contiguous_iterator<const_vector_t::iterator>);

        // test borrowed range
        static_assert(!std::ranges::borrowed_range<vector_t>);
        static_assert(!std::ranges::borrowed_range<const_vector_t>);

        // test random access range
        static_assert(std::ranges::random_access_range<vector_t>);
        static_assert(std::ranges::random_access_range<const_vector_t>);

        // test viewble range
        static_assert(std::ranges::viewable_range<vector_t&>);
        static_assert(std::ranges::viewable_range<const_vector_t&>);

        // test sortable range
        static_assert(std::sortable<vector_t::iterator>);
        static_assert(std::sortable<const_vector_t::iterator>);

        // test sized range
        static_assert(std::ranges::sized_range<vector_t>);
        static_assert(std::ranges::sized_range<const_vector_t>);

        // test common range
        static_assert(std::ranges::common_range<vector_t>);
        static_assert(std::ranges::common_range<const_vector_t>);

        // test view range
        static_assert(!std::ranges::view<vector_t>);
        static_assert(!std::ranges::view<const_vector_t>);

        // test if iterator satisfies bidirectional_iterator concept
        static_assert(std::bidirectional_iterator<vector_t::iterator>);
        static_assert(std::bidirectional_iterator<vector_t::const_iterator>);

        static_assert(std::bidirectional_iterator<const_vector_t::iterator>);
        static_assert(std::bidirectional_iterator<const_vector_t::const_iterator>);

        // test if iterator satisfies bidirectional_iterator concept
        static_assert(std::forward_iterator<vector_t::iterator>);
        static_assert(std::forward_iterator<vector_t::const_iterator>);

        static_assert(std::forward_iterator<const_vector_t::iterator>);
        static_assert(std::forward_iterator<const_vector_t::const_iterator>);

        // test if iterator allows reading
        static_assert(std::input_iterator<vector_t::iterator>);
        static_assert(std::input_iterator<vector_t::const_iterator>);

        static_assert(std::input_iterator<const_vector_t::iterator>);
        static_assert(std::input_iterator<const_vector_t::const_iterator>);

        // test if iterator satisfies bidirectional_iterator concept
        static_assert(std::ranges::bidirectional_range<vector_t>);
        static_assert(std::ranges::bidirectional_range<const_vector_t>);

        // test if range can be read
        static_assert(std::ranges::input_range<vector_t>);
        static_assert(std::ranges::input_range<const_vector_t>);

        // test if begin() and end() have the same type
        static_assert(std::ranges::common_range<vector_t>);
        static_assert(std::ranges::common_range<const_vector_t>);

        // test if iterators are indirectly readable 
        static_assert(std::indirectly_readable<vector_t::iterator>);
        static_assert(std::indirectly_readable<vector_t::const_iterator>);

        static_assert(std::indirectly_readable<const_vector_t::iterator>);
        static_assert(std::indirectly_readable<const_vector_t::const_iterator>);

        // test if sentinel and iterators are comparable
        static_assert(std::sentinel_for<vector_t::iterator, vector_t::iterator>);
        static_assert(std::sentinel_for<vector_t::const_iterator, vector_t::const_iterator>);

        static_assert(std::sentinel_for<const_vector_t::iterator, const_vector_t::iterator>);
        static_assert(std::sentinel_for<const_vector_t::const_iterator, const_vector_t::const_iterator>);

        // test iterator properties
        static_assert(std::is_same_v<std::ranges::iterator_t<vector_t>, int*>);
        static_assert(std::is_same_v<std::ranges::iterator_t<const_vector_t>, const int*>);

        // test sentinel properties
        static_assert(std::is_same_v<std::ranges::sentinel_t<vector_t>, int*>);
        static_assert(std::is_same_v<std::ranges::sentinel_t<const_vector_t>, const int*>);

        // test iterator forward and backward traversal and dereference correctness
        dsa::Vector<int> vector1{ 10, 20, 30 };
        auto* vector1_iter = vector1.begin();
        tests::compare("Vector1 iter == 10", *vector1_iter, 10);
        std::advance(vector1_iter, 1);
        tests::compare("Vector1 iter == 20", *vector1_iter, 20);
        std::advance(vector1_iter, 1);
        tests::compare("Vector1 iter == 30", *vector1_iter, 30);
        std::advance(vector1_iter, 1);
        tests::compare("Vector1 iter == end()", vector1_iter == vector1.end(), true);

        std::advance(vector1_iter, -1);
        tests::compare("Vector1 iter == 30", *vector1_iter, 30);
        std::advance(vector1_iter, -1);
        tests::compare("Vector1 iter == 20", *vector1_iter, 20);
        std::advance(vector1_iter, -1);
        tests::compare("Vector1 iter == 10", *vector1_iter, 10);
        tests::compare("Vector1 iter == begin()", vector1_iter == vector1.begin(), true);

        // test order correctness for push_front and push_back
        dsa::Vector<int> vector2;
        vector2.push_back(20);
        vector2.push_back(30);
        vector2.insert(vector2.begin(), 10);
        const std::initializer_list<int> expected2{ 10, 20, 30 };
        tests::compare("Vector2 equal()", std::ranges::equal(vector2, expected2), true);
        tests::compare("Vector2 front()", vector2.front(), 10);
        tests::compare("Vector2 back()", vector2.back(), 30);

        // test std::ranges algorithms compatibility
        dsa::Vector<int> vector3{ 30, 10, 40 };
        tests::compare("Vector3 min", std::ranges::min(vector3), 10);
        tests::compare("Vector3 max", std::ranges::max(vector3), 40);
        const int sum = std::accumulate(vector3.begin(), vector3.end(), 0);
        tests::compare("Vector3 sum", sum, 80);
        std::list<int> expected3;
        std::ranges::for_each(vector3, [&](int item) {expected3.push_back(item); });
        tests::compare("Vector3 for_each() equal()",
            std::ranges::equal(expected3, std::list{ 30, 10, 40 }), true);

        // test std::ranges::reverse_viev
        const dsa::Vector<int> vector4{ 10, 20, 30 };
        auto reversed4 = std::ranges::reverse_view(vector4);
        const std::list<int> vector4_reversed(reversed4.begin(), reversed4.end());
        tests::compare("Vector4 reverse_view", vector4_reversed == std::list{ 30, 20, 10 }, true);

        // test copy constructor and assignment, create deep copies
        dsa::Vector<int> vector5{ 10, 20, 30 };
        dsa::Vector<int> vector6 = vector5;
        tests::compare("Vector5 equal()", std::ranges::equal(vector5, vector6), true);
        vector5.at(0) = 0;
        tests::compare("Vector6 equal()", std::ranges::equal(vector5, vector6), false);

        // test copy constructor
        const dsa::Vector<int> expected7{ 10, 20, 30 };
        dsa::Vector<int> vector7 = expected7;
        tests::compare("Vector7 empty()", vector7.empty(), false);
        tests::compare("Vector7 equal()", std::ranges::equal(vector7, std::list{ 10, 20, 30 }), true);

        // test if const_iterator works correctly
        const dsa::Vector<int> vector8{ 10, 20, 30 };
        const auto* vector8_iter = vector8.begin();
        tests::compare("Vector8 iter == 1", *vector8_iter, 10);
        std::advance(vector8_iter, 1);
        tests::compare("Vector8 iter == 2", *vector8_iter, 20);
        std::advance(vector8_iter, 1);
        tests::compare("Vector8 iter == 3", *vector8_iter, 30);

        // test std::ranges::subrange
        dsa::Vector<int> vector9{ 10, 20, 30, 40 };
        auto* vector9_begin_iter = vector9.begin();
        auto* vector9_end_iter = vector9.end();
        std::advance(vector9_begin_iter, 1);
        std::advance(vector9_end_iter, -1);
        auto sub9 = std::ranges::subrange(vector9_begin_iter, vector9_end_iter);
        const std::list<int> expected9{ sub9.begin(), sub9.end() };
        tests::compare("Vector9 subrange()", expected9 == std::list{ 20, 30 }, true);
        auto sub9_reversed = std::ranges::reverse_view(sub9);
        tests::compare("Vector9 reverse_view()", std::ranges::equal(sub9_reversed, std::list{ 30, 20 }), true);

        // test empty vector iterator and algorithms
        dsa::Vector<int> vector10;
        tests::compare("Vector10 empty()", vector10.empty(), true);
        tests::compare("Vector10 begin() == end()", vector10.begin() == vector10.end(), true);
        tests::compare("Vector10 distance == 0", std::ranges::distance(vector10) == 0, true);

        // test single element access
        dsa::Vector<int> vector11(3);
        vector11.at(0) = 10;
        const std::initializer_list<int> expected11{ 10, 0, 0 };
        tests::compare("Vector11", vector11, expected11);
        tests::compare("Vector11 empty()", vector11.empty(), false);
        tests::compare("Vector11 front() == back()", vector11.front() == vector11.back(), false);
        tests::compare("Vector11 distance == 3", std::ranges::distance(vector11) == 3, true);

        // test if works with ranges algoritms
        dsa::Vector<int> vector12{ 40, 30, 20, 10 };
        std::ranges::sort(vector12);
        tests::compare("Vector12 sort()", vector12, { 10, 20, 30, 40 });

        // test std library ranges operation on custom iterators
        dsa::Vector<int> vector13{ 10, 20, 30, 40, 50 };
        std::ranges::fill(vector13, 10);
        const std::initializer_list<int> expected13 = { 10, 10, 10, 10, 10 };
        tests::compare("Vector13", vector13, expected13);

        dsa::Vector<int> vector14 = dsa::Vector<int>({ 0, 10, 0, 0, 40, 0 });
        auto it14 = std::ranges::remove(vector14, 0);
        vector14.erase(it14.begin(), vector14.end());
        const std::initializer_list<int> expected14 = { 10, 40 };
        tests::compare("vector14", vector14, expected14);

        dsa::Vector<int> vector15 = dsa::Vector<int>({ 0, 0, 0, 0, 0, 0 });
        auto it15 = std::ranges::remove(vector15, 0);
        vector15.erase(it15.begin(), vector15.end());
        const std::initializer_list<int> expected15 = { };
        tests::compare("vector15", vector15, expected15);

        // test std::ranges::begin and ::end
        dsa::Vector<int> vector16;
        tests::compare("Vector16 begin()", std::ranges::begin(vector16) == vector16.begin(), true);
        tests::compare("Vector16 end()", std::ranges::end(vector16) == vector16.end(), true);

        dsa::Vector<int> vector17{ 10, 20, 30, 40, 50 };
        auto* vector17_begin{ std::ranges::begin(vector17) };
        auto* vector17_end{ std::ranges::end(vector17) };
        tests::compare("Vector17 begin()", *vector17_begin, 10);
        tests::compare("Vector17", static_cast<size_t>(vector17_end - vector17_begin), vector17.size());

        // test std::view
        dsa::Vector<int> vector18 = { 10, 20, 30, 40, 50, 60 };
        const std::initializer_list<int> expected18 = { 10, 20, 30, 40, 50, 60 };
        const dsa::Vector<int> vector19 = { 20, 40, 60 };
        auto even = vector18 | std::views::filter([](int item) { return item % 20 == 0; });
        std::vector<int> expected19;
        for (const int& item : even)
        {
            expected19.push_back(item);
        }
        tests::compare("Vector18", vector18, expected18);
        tests::compare("Vector19", vector19, expected19);

        // test contiguous_range semantics
        dsa::Vector<int> vector20;
        for (size_t i = 0; i < 5; i++)
        {
            vector20.push_back(static_cast<int>(i));
        }
        auto* vector20_ptr = std::to_address(std::ranges::begin(vector20));
        tests::compare("Vector20 ptr", vector20_ptr != nullptr, true);
        for (size_t i = 0; i < 5; i++)
        {
            tests::compare("Vector20", *vector20_ptr, static_cast<int>(i));
            std::advance(vector20_ptr, 1);
        }

        // test modification by output iterator
        dsa::Vector<int> vector21;
        vector21.resize(3);
        auto* it21 = std::ranges::begin(vector21);
        *it21 = 10;
        std::advance(it21, 1);
        *it21 = 20;
        std::advance(it21, 1);
        *it21 = 30;
        tests::compare("Vector21[0]", vector21[0], 10);
        tests::compare("Vector21[1]", vector21[1], 20);
        tests::compare("Vector21[2]", vector21[2], 30);

        // test random access iterator
        dsa::Vector<int> vector22{ 10, 20, 30, 40 };
        tests::compare("Vector22[0]", vector22[0], 10);
        tests::compare("Vector22[1]", vector22[1], 20);
        tests::compare("Vector22[2]", *std::next(vector22.begin(), 2), 30);
        tests::compare("Vector22[3]", *std::next(vector22.begin(), 3), 40);


        std::cout << "Compare operations results with std container\n\n";

        std::vector<int> std_vector2{};
        std_vector2.push_back(20);
        std_vector2.push_back(30);
        std_vector2.insert(std_vector2.begin(), 10);
        tests::compare("Vector2 vs std equal()", std::ranges::equal(vector2, std_vector2), true);
        tests::compare("Vector2 vs std front()", vector2.front(), std_vector2.front());
        tests::compare("Vector2 vs std back()", vector2.back(), std_vector2.back());

        std::vector<int> std_vector5{ 10, 20, 30 };
        std::vector<int> std_vector6 = std_vector5;
        std_vector5.at(0) = 0;
        tests::compare("Vector5 vs std equal()", std::ranges::equal(vector5, std_vector5), true);
        tests::compare("Vector6 vs std equal()", std::ranges::equal(vector6, std_vector6), true);

        const std::vector<int> std_vector7{ 10, 20, 30 };
        std::vector<int> std_vector8 = std_vector7;
        tests::compare("Vector7 vs std empty()", vector8.empty(), std_vector8.empty());
        tests::compare("Vector8 vs std equal()", std::ranges::equal(vector8, std_vector8), true);

        std::vector<int> std_vector10{};
        tests::compare("Vector10 vs std empty()", vector10.empty(), std_vector10.empty());
        tests::compare("Vector10 vs std begin() == end()",
            vector10.begin() == vector10.end(), std_vector10.begin() == std_vector10.end());
        tests::compare("Vector10 vs std distance",
            std::ranges::distance(vector10), std::ranges::distance(vector10));

        std::vector<int> std_vector11(3);
        std_vector11.at(0) = 10;
        tests::compare("Vector11 vs std empty()", vector11.empty(), std_vector11.empty());
        tests::compare("Vector11 vs std front() == back()", vector11.front(), std_vector11.front());
        tests::compare("Vector11 vs std front() == back()", vector11.back(), std_vector11.back());
        tests::compare("Vector11 vs std distance",
            std::ranges::distance(vector11), std::ranges::distance(std_vector11));

        std::vector<int> std_vector12{ 40, 30, 20, 10 };
        std::ranges::sort(std_vector12);
        tests::compare("Vector12 vs std sort()", vector12, std_vector12);

        std::vector<int> std_vector13{ 10, 20, 30, 40, 50 };
        std::ranges::fill(std_vector13, 10);
        tests::compare("Vector13 vs std", vector13, std_vector13);

        std::vector<int> std_vector14 = std::vector<int>({ 0, 10, 0, 0, 40, 0 });
        auto std_it14 = std::ranges::remove(std_vector14, 0);
        std_vector14.erase(std_it14.begin(), std_vector14.end());
        tests::compare("vector14 vs std", vector14, std_vector14);

        std::vector<int> std_vector15 = std::vector<int>({ 0, 0, 0, 0, 0, 0 });
        auto std_it15 = std::ranges::remove(std_vector15, 0);
        std_vector15.erase(std_it15.begin(), std_vector15.end());
        tests::compare("vector15 vs std", vector15, std_vector15);

        std::vector<int> std_vector16{};
        tests::compare("Vector16 vs std begin()",
            std::ranges::begin(vector16) == vector16.begin(), std::ranges::begin(std_vector16) == std_vector16.begin());
        tests::compare("Vector16 vs std end()",
            std::ranges::end(vector16) == vector16.end(), std::ranges::end(std_vector16) == std_vector16.end());

        std::vector<int> std_vector17{ 10, 20, 30, 40, 50 };
        auto std_vector17_begin{ std::ranges::begin(std_vector17) };
        auto std_vector17_end{ std::ranges::end(std_vector17) };
        tests::compare("Vector17 vs std", vector17_end - vector17_begin, std_vector17_end - std_vector17_begin);

        std::vector<int> std_vector21;
        std_vector21.resize(3);
        auto std_it21 = std::ranges::begin(std_vector21);
        *std_it21 = 10;
        std::advance(std_it21, 1);
        *std_it21 = 20;
        std::advance(std_it21, 1);
        *std_it21 = 30;
        tests::compare("Vector21 vs std", vector21, std_vector21);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
