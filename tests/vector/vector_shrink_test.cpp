/**
 * @file vector_shrink_test.cpp
 * @brief This file tests functions decreasing Vector length
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
#include <vector>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start vector_shrink_test:\n";

        dsa::Vector<int> vector1 = dsa::Vector<int>({ 0, 10, 20, 30, 40, 50 });
        auto* iter1 = vector1.begin();
        std::advance(iter1, vector1.size() - 1);
        vector1.erase(iter1);
        auto indexes = { 3, 2, 0 };
        for (const auto& idx : indexes)
        {
            iter1 = vector1.begin();
            std::advance(iter1, idx);
            vector1.erase(iter1);
        }
        const std::initializer_list<int> expected1 = { 10, 40 };
        tests::compare("Vector1", vector1, expected1);

        dsa::Vector<int> vector2 = dsa::Vector<int>({ 0, 10, 20, 30, 40, 50 });
        auto* vector2_it = vector2.erase(std::next(vector2.begin(), 1), std::next(vector2.begin(), 3));
        const std::initializer_list<int> expected2 = { 0, 30, 40, 50 };
        tests::compare("Vector2", vector2, expected2);

        dsa::Vector<int> vector3 = dsa::Vector<int>({ 0, 10, 20, 30, 40, 50 });
        vector3.erase(std::next(vector3.begin(), 0), std::next(vector3.begin(), 3));
        const std::initializer_list<int> expected3 = { 30, 40, 50 };
        tests::compare("Vector3", vector3, expected3);

        dsa::Vector<int> vector4 = dsa::Vector<int>({ 0, 10, 20, 30, 40, 50 });
        vector4.erase(std::next(vector4.begin(), 0), std::next(vector4.begin(), 6));
        const std::initializer_list<int> expected4 = {};
        tests::compare("Vector4", vector4, expected4);

        dsa::Vector<int> vector5 = dsa::Vector<int>({ 0, 10, 0, 0, 40, 0 });
        // use classic iterator based algorithms, separate test was added to test std::ranges based algorithms
        // NOLINTNEXTLINE(modernize-use-ranges)
        auto* it5 = std::remove(vector5.begin(), vector5.end(), 0);
        vector5.erase(it5, vector5.end());
        const std::initializer_list<int> expected5 = { 10, 40 };
        tests::compare("Vector5", vector5, expected5);

        dsa::Vector<int> vector6 = dsa::Vector<int>({ 0, 0, 0, 0, 0, 0 });
        // use classic iterator based algorithms, separate test was added to test std::ranges based algorithms
        // NOLINTNEXTLINE(modernize-use-ranges)
        auto* it6 = std::remove(vector6.begin(), vector6.end(), 0);
        vector6.erase(it6, vector6.end());
        const std::initializer_list<int> expected6 = { };
        tests::compare("Vector6", vector6, expected6);

        dsa::Vector<int> vector7 = dsa::Vector<int>({ 0 });
        tests::compare(vector7.empty(), false);
        vector7.clear();
        tests::compare(vector7.empty(), true);
        vector7.clear();
        const std::initializer_list<int> expected7 = { };
        tests::compare("Vector7", vector7, expected7);

        dsa::Vector<int> vector8 = dsa::Vector<int>({ 10, 20, 30 });
        vector8.erase(vector8.cbegin());
        vector8.erase(vector8.begin());
        vector8.erase(vector8.begin());
        const std::initializer_list<int> expected8 = { };
        tests::compare("Vector8", vector8, expected8);
        tests::compare("Vector8 size()", vector8.size(), static_cast<std::size_t>(0));

        dsa::Vector<int> vector9{ 10, 20, 30, 40, 50 };
        vector9.erase(vector9.cbegin() + 1, vector9.cbegin() + 3);
        const std::initializer_list<int> expected9 = { 10, 40, 50 };
        tests::compare("Vector9", vector9, expected9);
        tests::compare("Vector9 size()", vector9.size(), static_cast<std::size_t>(3));

        dsa::Vector<int> vector10 = dsa::Vector<int>({ 10, 20, 30 });
        vector10.pop_back();
        vector10.pop_back();
        vector10.pop_back();
        vector10.pop_back();
        const std::initializer_list<int> expected10 = { };
        tests::compare("Vector10", vector10, expected10);
        tests::compare("Vector10 size()", vector10.size(), static_cast<std::size_t>(0));

        dsa::Vector<int> vector11{ 0, 1, 2, 3 };
        vector11.shrink_to_fit();
        tests::compare("Vector11 size()", vector11.size(), static_cast<std::size_t>(4));
        tests::compare("Vector11 capacity()", vector11.capacity(), static_cast<std::size_t>(4));
        vector11.push_back(5);
        tests::compare("Vector11 size()", vector11.size(), static_cast<std::size_t>(5));
        tests::compare("Vector11 capacity()", vector11.capacity(), static_cast<std::size_t>(8));
        vector11.shrink_to_fit();
        tests::compare("Vector11 size()", vector11.size(), static_cast<std::size_t>(5));
        tests::compare("Vector11 capacity()", vector11.capacity(), static_cast<std::size_t>(5));

        dsa::Vector<int> vector12 = dsa::Vector<int>({ 0, 10, 0, 0, 40, 0 });
        auto cnt12 = dsa::erase(vector12, 0);
        const std::initializer_list<int> expected12 = { 10, 40 };
        tests::compare("Vector12", vector12, expected12);
        tests::compare("Vector12 removed count", cnt12, std::size_t{ 4 });

        dsa::Vector<int> vector13 = dsa::Vector<int>({ 0, 0, 0, 0, 0, 0 });
        auto cnt13 = dsa::erase(vector13, 0);
        const std::initializer_list<int> expected13 = { };
        tests::compare("Vector13", vector13, expected13);
        tests::compare("Vector13 erase count", cnt13, std::size_t{ 6 });

        dsa::Vector<int> vector14 = dsa::Vector<int>({ 0, 10, 0, 0, 40, 0 });
        auto cnt14 = dsa::erase_if(vector14, [](int val) { return val == 0; });
        const std::initializer_list<int> expected14 = { 10, 40 };
        tests::compare("Vector14", vector14, expected14);
        tests::compare("Vector14 erase count", cnt14, std::size_t{ 4 });

        dsa::Vector<int> vector15 = dsa::Vector<int>({ 0, 0, 0, 0, 0, 0 });
        auto cnt15 = dsa::erase_if(vector15, [](int val) { return val == 0; });
        const std::initializer_list<int> expected15 = { };
        tests::compare("Vector15", vector15, expected15);
        tests::compare("Vector15 erase_if count", cnt15, std::size_t{ 6 });

        dsa::Vector<int> vector16 = dsa::Vector<int>({ 0, 1, 2, 3, 4, 5 });
        auto cnt16 = dsa::erase_if(vector16, [](int val) { return val % 2 == 0; });
        const std::initializer_list<int> expected16 = { 1, 3, 5 };
        tests::compare("Vector16", vector16, expected16);
        tests::compare("Vector16 erase_if count", cnt16, std::size_t{ 3 });

        dsa::Vector<int> vector17 = dsa::Vector<int>({ 0, 10, 2, 5, 7, 9 });
        auto cnt17 = dsa::erase_if(vector17, [](int val) { return val <= 5; });
        const std::initializer_list<int> expected17 = { 10, 7, 9 };
        tests::compare("Vector17", vector17, expected17);
        tests::compare("Vector17 erase_if count", cnt17, std::size_t{ 3 });


        std::cout << "Compare operations results with std container\n\n";

        std::vector<int> std_vector2{ 0, 10, 20, 30, 40, 50 };
        auto std_vector2_it = std_vector2.erase(std::next(std_vector2.begin(), 1), std::next(std_vector2.begin(), 3));
        tests::compare("Vector2 vs std", vector2, std_vector2);
        tests::compare("Vector2 vs std iter", *vector2_it, *std_vector2_it);

        std::vector<int> std_vector3{ 0, 10, 20, 30, 40, 50 };
        std_vector3.erase(std::next(std_vector3.begin(), 0), std::next(std_vector3.begin(), 3));
        tests::compare("Vector3 vs std", vector3, std_vector3);

        std::vector<int> std_vector4{ 0, 10, 20, 30, 40, 50 };
        std_vector4.erase(std::next(std_vector4.begin(), 0), std::next(std_vector4.begin(), 6));
        tests::compare("Vector4 vs std", vector4, std_vector4);

        std::vector<int> std_vector5 = std::vector<int>({ 0, 10, 0, 0, 40, 0 });
        // use classic iterator based algorithms, separate test was added to test std::ranges based algorithms
        // NOLINTNEXTLINE(modernize-use-ranges)
        auto std_it5 = std::remove(std_vector5.begin(), std_vector5.end(), 0);
        std_vector5.erase(std_it5, std_vector5.end());
        tests::compare("Vector5 vs std", vector5, std_vector5);

        std::vector<int> std_vector6 = std::vector<int>({ 0, 0, 0, 0, 0, 0 });
        // use classic iterator based algorithms, separate test was added to test std::ranges based algorithms
        // NOLINTNEXTLINE(modernize-use-ranges)
        auto std_it6 = std::remove(std_vector6.begin(), std_vector6.end(), 0);
        std_vector6.erase(std_it6, std_vector6.end());
        tests::compare("Vector6 vs std", vector6, std_vector6);

        std::vector<int> std_vector12 = std::vector<int>({ 0, 10, 0, 0, 40, 0 });
        auto std_cnt12 = std::erase(std_vector12, 0);
        tests::compare("Vector12 vs std", vector12, std_vector12);
        tests::compare("Vector12 vs std removed count", cnt12, std_cnt12);

        std::vector<int> std_vector13 = std::vector<int>({ 0, 0, 0, 0, 0, 0 });
        auto std_cnt13 = std::erase(std_vector13, 0);
        tests::compare("Vector13 vs std", vector13, std_vector13);
        tests::compare("Vector13 vs std erase count", cnt13, std_cnt13);

        std::vector<int> std_vector14 = std::vector<int>({ 0, 10, 0, 0, 40, 0 });
        auto std_cnt14 = std::erase_if(std_vector14, [](int val) { return val == 0; });
        tests::compare("Vector14 vs std", vector14, std_vector14);
        tests::compare("Vector14 vs std erase count", cnt14, std_cnt14);

        std::vector<int> std_vector15 = std::vector<int>({ 0, 0, 0, 0, 0, 0 });
        auto std_cnt15 = std::erase_if(std_vector15, [](int val) { return val == 0; });
        tests::compare("Vector15 vs std", vector15, std_vector15);
        tests::compare("Vector15 vs std erase_if count", cnt15, std_cnt15);

        std::vector<int> std_vector16 = std::vector<int>({ 0, 1, 2, 3, 4, 5 });
        auto std_cnt16 = std::erase_if(std_vector16, [](int val) { return val % 2 == 0; });
        tests::compare("Vector16 vs std", vector16, std_vector16);
        tests::compare("Vector16 vs std erase_if count", cnt16, std_cnt16);

        std::vector<int> std_vector17 = std::vector<int>({ 0, 10, 2, 5, 7, 9 });
        auto std_cnt17 = std::erase_if(std_vector17, [](int val) { return val <= 5; });
        tests::compare("Vector17 vs std", vector17, std_vector17);
        tests::compare("Vector17 vs std erase_if count", cnt17, std_cnt17);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
