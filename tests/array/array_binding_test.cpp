/**
 * @file array_binding_test.cpp
 * @brief This file tests Array structured binding
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/array.h"

#include <array>
#include <exception>
#include <iostream>
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start array_binding_test:\n";

        // test get<I>()
        constexpr dsa::Array<int, 3> array1{ 10, 11, 12 };
        constexpr int array1_a = get<0>(array1);
        constexpr int array1_b = get<1>(array1);
        constexpr int array1_c = get<2>(array1);
        static_assert(array1_a == 10 && array1_b == 11 && array1_c == 12, "get<I>() must work in constexpr");

        // test not const array

        dsa::Array<int, 3> array2{ 20, 21, 22 };
        auto [a2, b2, c2] = array2;
        tests::compare("Array2 a", array2[0], a2);
        tests::compare("Array2 b", array2[1], b2);
        tests::compare("Array2 c", array2[2], c2);

        dsa::Array<int, 3> array3{ 30, 31, 32 };
        const auto& [a3, b3, c3] = array3;
        tests::compare("Array3 a", a3, array3[0]);
        tests::compare("Array3 b", b3, array3[1]);
        tests::compare("Array3 c", c3, array3[2]);

        dsa::Array<int, 3> array4{ 40, 41, 42 };
        auto&& [a4, b4, c4] = array4;
        tests::compare("Array4 a", array4[0], a4);
        tests::compare("Array4 b", array4[1], b4);
        tests::compare("Array4 c", array4[2], c4);

        // test const array

        const dsa::Array<int, 3> array5{ 50, 51, 52 };
        auto [a5, b5, c5] = array5;
        tests::compare("Array5 a", array5[0], a5);
        tests::compare("Array5 b", array5[1], b5);
        tests::compare("Array5 c", array5[2], c5);

        const dsa::Array<int, 3> array6{ 60, 61, 62 };
        const auto& [a6, b6, c6] = array6;
        tests::compare("Array6 a", a6, array6[0]);
        tests::compare("Array6 b", b6, array6[1]);
        tests::compare("Array6 c", c6, array6[2]);

        const dsa::Array<int, 3> array7{ 70, 71, 72 };
        auto&& [a7, b7, c7] = array7;
        tests::compare("Array7 a", array7[0], a7);
        tests::compare("Array7 b", array7[1], b7);
        tests::compare("Array7 c", array7[2], c7);

        const dsa::Array<int, 3> array8{ 80, 81, 82 };
        dsa::Array<int, 3> expected8 = array8;
        auto&& [a8, b8, c8] = std::move(array8);
        tests::compare("Array8 a", a8, expected8[0]);
        tests::compare("Array8 b", b8, expected8[1]);
        tests::compare("Array8 c", c8, expected8[2]);


        std::cout << "Compare operations results with std container\n\n";

        // test get<I>()
        constexpr std::array<int, 3> std_array1{ 10, 11, 12 };
        constexpr int std_array1_a = get<0>(std_array1);
        constexpr int std_array1_b = get<1>(std_array1);
        constexpr int std_array1_c = get<2>(std_array1);
        static_assert(array1_a == std_array1_a && array1_b == std_array1_b && array1_c == std_array1_c,
            "get<I>() must work in constexpr");

        const std::array<int, 3> std_array5{ 50, 51, 52 };
        auto [std_a5, std_b5, std_c5] = std_array5;
        tests::compare("Array5 a vs std", a5, std_a5);
        tests::compare("Array5 b vs std", b5, std_b5);
        tests::compare("Array5 c vs std", c5, std_c5);

        const std::array<int, 3> std_array6{ 60, 61, 62 };
        const auto& [std_a6, std_b6, std_c6] = std_array6;
        tests::compare("Array6 a vs std", a6, std_a6);
        tests::compare("Array6 b vs std", b6, std_b6);
        tests::compare("Array6 c vs std", c6, std_c6);

        const std::array<int, 3> std_array7{ 70, 71, 72 };
        auto&& [std_a7, std_b7, std_c7] = std_array7;
        tests::compare("Array7 a vs std", a7, std_a7);
        tests::compare("Array7 b vs std", b7, std_b7);
        tests::compare("Array7 c vs std", c7, std_c7);

        const std::array<int, 3> std_array8{ 80, 81, 82 };
        auto&& [std_a8, std_b8, std_c8] = std::move(std_array8);
        tests::compare("Array8 a vs std", a8, std_a8);
        tests::compare("Array8 b vs std", b8, std_b8);
        tests::compare("Array8 c vs std", c8, std_c8);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
