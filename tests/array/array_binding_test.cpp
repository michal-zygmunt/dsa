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
        auto [array2_a, array2_b, array2_c] = array2;
        tests::compare("Array2 a", array2[0], array2_a);
        tests::compare("Array2 b", array2[1], array2_b);
        tests::compare("Array2 c", array2[2], array2_c);

        dsa::Array<int, 3> array3{ 30, 31, 32 };
        const auto& [array3_a, array3_b, array3_c] = array3;
        tests::compare("Array3 a", array3_a, array3[0]);
        tests::compare("Array3 b", array3_b, array3[1]);
        tests::compare("Array3 c", array3_c, array3[2]);

        dsa::Array<int, 3> array4{ 40, 41, 42 };
        auto&& [array4_a, array4_b, array4_c] = array4;
        tests::compare("Array4 a", array4[0], array4_a);
        tests::compare("Array4 b", array4[1], array4_b);
        tests::compare("Array4 c", array4[2], array4_c);

        // test const array

        const dsa::Array<int, 3> array5{ 50, 51, 52 };
        auto [array5_a, array5_b, array5_c] = array5;
        tests::compare("Array5 a", array5[0], array5_a);
        tests::compare("Array5 b", array5[1], array5_b);
        tests::compare("Array5 c", array5[2], array5_c);

        const dsa::Array<int, 3> array6{ 60, 61, 62 };
        const auto& [array6_a, array6_b, array6_c] = array6;
        tests::compare("Array6 a", array6_a, array6[0]);
        tests::compare("Array6 b", array6_b, array6[1]);
        tests::compare("Array6 c", array6_c, array6[2]);

        const dsa::Array<int, 3> array7{ 70, 71, 72 };
        auto&& [array7_a, array7_b, array7_c] = array7;
        tests::compare("Array7 a", array7[0], array7_a);
        tests::compare("Array7 b", array7[1], array7_b);
        tests::compare("Array7 c", array7[2], array7_c);

        const dsa::Array<int, 3> array8{ 80, 81, 82 };
        dsa::Array<int, 3> expected8 = array8;
        auto&& [array8_a, array8_b, array8_c] = std::move(array8);
        tests::compare("Array8 a", array8_a, expected8[0]);
        tests::compare("Array8 b", array8_b, expected8[1]);
        tests::compare("Array8 c", array8_c, expected8[2]);


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
        tests::compare("Array5 a vs std", array5_a, std_a5);
        tests::compare("Array5 b vs std", array5_b, std_b5);
        tests::compare("Array5 c vs std", array5_c, std_c5);

        const std::array<int, 3> std_array6{ 60, 61, 62 };
        const auto& [std_a6, std_b6, std_c6] = std_array6;
        tests::compare("Array6 a vs std", array6_a, std_a6);
        tests::compare("Array6 b vs std", array6_b, std_b6);
        tests::compare("Array6 c vs std", array6_c, std_c6);

        const std::array<int, 3> std_array7{ 70, 71, 72 };
        auto&& [std_a7, std_b7, std_c7] = std_array7;
        tests::compare("Array7 a vs std", array7_a, std_a7);
        tests::compare("Array7 b vs std", array7_b, std_b7);
        tests::compare("Array7 c vs std", array7_c, std_c7);

        const std::array<int, 3> std_array8{ 80, 81, 82 };
        auto&& [std_a8, std_b8, std_c8] = std::move(std_array8);
        tests::compare("Array8 a vs std", array8_a, std_a8);
        tests::compare("Array8 b vs std", array8_b, std_b8);
        tests::compare("Array8 c vs std", array8_c, std_c8);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
