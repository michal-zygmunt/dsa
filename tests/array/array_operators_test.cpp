/**
 * @file array_operators_test.cpp
 * @brief This file tests overloading operators of Array
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

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start array_operators_test:\n";

        const dsa::Array<int, 3> Array1({ 1, 2, 3 });
        const dsa::Array<int, 3> Array2({ 1, 2, 6 });
        std::cout << "Array1:\t" << Array1 << '\n';
        std::cout << "Array2:\t" << Array2 << '\n';

        std::cout << "Compare operators for objects of the same size\n\n";

        // intentional self-comparison, an object should be equal to itself
        // NOLINTNEXTLINE(misc-redundant-expression)
        tests::compare("Array1 == Array1", Array1 == Array1, true);

        tests::compare("Array1 != Array2", Array1 != Array2, true);

        tests::compare("Array1 < Array2", Array1 < Array2, true);
        tests::compare("Array2 < Array1", Array2 < Array1, false);

        tests::compare("Array1 > Array2", Array1 > Array2, false);
        tests::compare("Array2 > Array1", Array2 > Array1, true);

        tests::compare("Array1 <= Array2", Array1 <= Array2, true);
        tests::compare("Array2 <= Array1", Array2 <= Array1, false);

        tests::compare("Array1 >= Array2", Array1 >= Array2, false);
        tests::compare("Array2 >= Array1", Array2 >= Array1, true);


        std::cout << "Compare operations results with std container\n\n";

        const std::array<int, 3> std_Array1({ 1, 2, 3 });
        const std::array<int, 3> std_Array2({ 1, 2, 6 });

        // intentional self-comparison, an object should be equal to itself
        // NOLINTNEXTLINE(misc-redundant-expression)
        tests::compare("Array1 == Array1 vs std", Array1 == Array1, std_Array1 == std_Array1);

        tests::compare("Array1 != Array2 vs std", Array1 != Array2, std_Array1 != std_Array2);

        tests::compare("Array1 < Array2 vs std", Array1 < Array2, std_Array1 < std_Array2);
        tests::compare("Array2 < Array1 vs std", Array2 < Array1, std_Array2 < std_Array1);

        tests::compare("Array1 > Array2 vs std", Array1 > Array2, std_Array1 > std_Array2);
        tests::compare("Array2 > Array1 vs std", Array2 > Array1, std_Array2 > std_Array1);

        tests::compare("Array1 <= Array2 vs std", Array1 <= Array2, std_Array1 <= std_Array2);
        tests::compare("Array2 <= Array1 vs std", Array2 <= Array1, std_Array2 <= std_Array1);

        tests::compare("Array1 >= Array2 vs std", Array1 >= Array2, std_Array1 >= std_Array2);
        tests::compare("Array2 >= Array1 vs std", Array2 >= Array1, std_Array2 >= std_Array1);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}