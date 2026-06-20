/**
 * @file vector_swap_test.cpp
 * @brief This file tests functions swapping Vector objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/vector.h"

#include <exception>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start vector_swap_test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };

        dsa::Vector<int> vector1 = dsa::Vector<int>(il_1);
        dsa::Vector<int> vector2 = dsa::Vector<int>(il_2);
        vector1.swap(vector2);
        const std::initializer_list<int> expected1 = { 10, 20, 30, 40, 50 };
        tests::compare("Vector1", vector1, expected1);
        const std::initializer_list<int> expected2 = { 1, 2, 3, 4, 5 };
        tests::compare("Vector2", vector2, expected2);

        dsa::Vector<int> vector3 = dsa::Vector<int>(il_1);
        dsa::Vector<int> vector4;
        vector3.swap(vector4);
        const std::initializer_list<int> expected3 = { };
        tests::compare("Vector3", vector3, expected3);
        const std::initializer_list<int> expected4 = { 1, 2, 3, 4, 5 };
        tests::compare("Vector4", vector4, expected4);

        // test swapping self
        dsa::Vector<int> vector5{ 1, 2, 3, 4 };
        vector5.swap(vector5);
        tests::compare("Vector5", vector5, { 1, 2, 3, 4 });

        const std::initializer_list<int> temp6{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> temp7{ 10, 20, 30 };
        dsa::Vector<int> vector6{ temp6 };
        dsa::Vector<int> vector7{ temp7 };
        dsa::swap(vector6, vector7);
        tests::compare("Vector6", vector6, temp7);
        tests::compare("Vector7", vector7, temp6);

        dsa::Vector<int> vector8 = dsa::Vector<int>(il_1);
        dsa::Vector<int> vector9;
        dsa::swap(vector8, vector9);
        const std::initializer_list<int> expected8 = { };
        tests::compare("Vector8", vector8, expected8);
        const std::initializer_list<int> expected9 = il_1;
        tests::compare("Vector9", vector9, expected9);

        // swap safe type
        static_assert(noexcept(swap(std::declval<dsa::Vector<int>&>(),
            std::declval<dsa::Vector<int>&>())));
        // swap throwing type
        static_assert(noexcept(swap(std::declval<dsa::Vector<tests::ThrowingType>&>(),
            std::declval<dsa::Vector<tests::ThrowingType>&>())));


        std::cout << "Compare operations results with std container\n\n";

        std::vector<int> std_vector1{ il_1 };
        std::vector<int> std_vector2{ il_2 };
        std_vector1.swap(std_vector2);
        tests::compare("Vector1 vs std", vector1, std_vector1);
        tests::compare("Vector2 vs std", vector2, std_vector2);

        std::vector<int> std_vector3{ il_1 };
        std::vector<int> std_vector4{};
        std_vector3.swap(std_vector4);
        tests::compare("Vector3 vs std", vector3, std_vector3);
        tests::compare("Vector4 vs std", vector4, std_vector4);

        std::vector<int> std_vector5{ 1, 2, 3, 4 };
        std_vector5.swap(std_vector5);
        tests::compare("vector5 vs std", vector5, std_vector5);

        const std::initializer_list<int> std_temp6{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> std_temp7{ 10, 20, 30 };
        std::vector<int> std_vector6{ std_temp6 };
        std::vector<int> std_vector7{ std_temp7 };
        std::swap(std_vector6, std_vector7);
        tests::compare("Vector6 vs std", vector6, std_vector6);
        tests::compare("Vector7 vs std", vector7, std_vector7);

        std::vector<int> std_vector8 = std::vector<int>(il_1);
        std::vector<int> std_vector9;
        std::swap(std_vector8, std_vector9);
        tests::compare("Vector8 vs std", vector8, std_vector8);
        tests::compare("Vector9 vs std", vector9, std_vector9);

        // swap safe type
        static_assert(noexcept(swap(std::declval<std::vector<int>&>(),
            std::declval<std::vector<int>&>())));
        // swap throwing type
        static_assert(noexcept(swap(std::declval<std::vector<tests::ThrowingType>&>(),
            std::declval<std::vector<tests::ThrowingType>&>())));


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
