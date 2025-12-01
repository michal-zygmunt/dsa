/**
 * @file vector_operators_test.cpp
 * @brief This file tests overloading operators of vector
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
#include <iostream>
#include <vector>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start vector_operators_test:\n";

        const dsa::Vector<int> vector1({ 1, 2, 3 });
        const dsa::Vector<int> vector2({ 1, 2, 6 });
        const dsa::Vector<int> vector3({ 1, 2, 3, 4 });
        std::cout << "Vector1:\t" << vector1 << '\n';
        std::cout << "Vector2:\t" << vector2 << '\n';
        std::cout << "Vector3:\t" << vector3 << "\n\n";

        std::cout << "Compare operators for objects of the same size\n\n";

        // intentional self-comparison, an object should be equal to itself
        // NOLINTNEXTLINE(misc-redundant-expression)
        tests::compare("Vector1 == vector1", vector1 == vector1, true);

        tests::compare("Vector1 != vector2", vector1 != vector2, true);

        tests::compare("Vector1 < vector2", vector1 < vector2, true);
        tests::compare("Vector2 < vector1", vector2 < vector1, false);

        tests::compare("Vector1 > vector2", vector1 > vector2, false);
        tests::compare("Vector2 > vector1", vector2 > vector1, true);

        tests::compare("Vector1 <= vector2", vector1 <= vector2, true);
        tests::compare("Vector2 <= vector1", vector2 <= vector1, false);

        tests::compare("Vector1 >= vector2", vector1 >= vector2, false);
        tests::compare("Vector2 >= vector1", vector2 >= vector1, true);

        // test three way comparison

        tests::compare("Vector1 <=> vector2 !=", (vector1 <=> vector2) != 0, true);
        tests::compare("Vector1 <=> vector2 <", (vector1 <=> vector2) < 0, true);
        tests::compare("Vector1 <=> vector2 >", (vector1 <=> vector2) > 0, false);
        tests::compare("Vector1 <=> vector2 <=", (vector1 <=> vector2) <= 0, true);
        tests::compare("Vector1 <=> vector2 >=", (vector1 <=> vector2) >= 0, false);

        tests::compare("Vector1 <=> vector2 <", (vector1 <=> vector2) == std::weak_ordering::less, true);
        tests::compare("Vector1 <=> vector2 <>", (vector1 <=> vector2) != std::weak_ordering::equivalent, true);
        tests::compare("Vector1 <=> vector2 <=", (vector1 <=> vector2) != std::weak_ordering::greater, true);


        std::cout << "Compare operators for objects of different size\n\n";

        tests::compare("Vector1 == vector3", vector1 == vector3, false);
        tests::compare("Vector1 != vector3", vector1 != vector3, true);

        tests::compare("Vector1 < vector3", vector1 < vector3, true);
        tests::compare("Vector3 < vector1", vector3 < vector1, false);
        tests::compare("Vector2 < vector3", vector2 < vector3, false);
        tests::compare("Vector3 < vector2", vector3 < vector2, true);

        tests::compare("Vector1 > vector3", vector1 > vector3, false);
        tests::compare("Vector3 > vector1", vector3 > vector1, true);
        tests::compare("Vector2 > vector3", vector2 > vector3, true);
        tests::compare("Vector3 > vector2", vector3 > vector2, false);

        tests::compare("Vector1 <= vector3", vector1 <= vector3, true);
        tests::compare("Vector3 <= vector1", vector3 <= vector1, false);
        tests::compare("Vector2 <= vector3", vector2 <= vector3, false);
        tests::compare("Vector3 <= vector2", vector3 <= vector2, true);

        tests::compare("Vector1 >= vector3", vector1 >= vector3, false);
        tests::compare("Vector3 >= vector1", vector3 >= vector1, true);
        tests::compare("Vector2 >= vector3", vector2 >= vector3, true);
        tests::compare("Vector3 >= vector2", vector3 >= vector2, false);

        // test three way comparison

        tests::compare("Vector1 <=> vector3 ==", (vector1 <=> vector3) == 0, false);
        tests::compare("Vector1 <=> vector3 <", (vector1 <=> vector3) < 0, true);
        tests::compare("Vector1 <=> vector3 >", (vector1 <=> vector3) > 0, false);
        tests::compare("Vector1 <=> vector3 <=", (vector1 <=> vector3) <= 0, true);
        tests::compare("Vector1 <=> vector3 >=", (vector1 <=> vector3) >= 0, false);

        tests::compare("Vector1 <=> vector3 >=", (vector1 <=> vector3) != std::weak_ordering::less, false);
        tests::compare("Vector1 <=> vector3 ==", (vector1 <=> vector3) == std::weak_ordering::equivalent, false);
        tests::compare("Vector1 <=> vector3 <=", (vector1 <=> vector3) != std::weak_ordering::greater, true);


        std::cout << "Compare operations results with std container\n\n";

        const std::vector<int> std_vector1({ 1, 2, 3 });
        const std::vector<int> std_vector2({ 1, 2, 6 });
        const std::vector<int> std_vector3({ 1, 2, 3, 4 });

        // intentional self-comparison, an object should be equal to itself
        // NOLINTNEXTLINE(misc-redundant-expression)
        tests::compare("Vector1 == vector1 vs std", vector1 == vector1, std_vector1 == std_vector1);

        tests::compare("Vector1 != vector2 vs std", vector1 != vector2, std_vector1 != std_vector2);

        tests::compare("Vector1 < vector2 vs std", vector1 < vector2, std_vector1 < std_vector2);
        tests::compare("Vector2 < vector1 vs std", vector2 < vector1, std_vector2 < std_vector1);

        tests::compare("Vector1 > vector2 vs std", vector1 > vector2, std_vector1 > std_vector2);
        tests::compare("Vector2 > vector1 vs std", vector2 > vector1, std_vector2 > std_vector1);

        tests::compare("Vector1 <= vector2 vs std", vector1 <= vector2, std_vector1 <= std_vector2);
        tests::compare("Vector2 <= vector1 vs std", vector2 <= vector1, std_vector2 <= std_vector1);

        tests::compare("Vector1 >= vector2 vs std", vector1 >= vector2, std_vector1 >= std_vector2);
        tests::compare("Vector2 >= vector1 vs std", vector2 >= vector1, std_vector2 >= std_vector1);

        // test three way comparison

        tests::compare("Vector1 <=> vector2 vs std !=", (vector1 <=> vector2) != 0, (std_vector1 <=> std_vector2) != 0);
        tests::compare("Vector1 <=> vector2 vs std <", (vector1 <=> vector2) < 0, (std_vector1 <=> std_vector2) < 0);
        tests::compare("Vector1 <=> vector2 vs std >", (vector1 <=> vector2) > 0, (std_vector1 <=> std_vector2) > 0);
        tests::compare("Vector1 <=> vector2 vs std <=", (vector1 <=> vector2) <= 0, (std_vector1 <=> std_vector2) <= 0);
        tests::compare("Vector1 <=> vector2 vs std >=", (vector1 <=> vector2) >= 0, (std_vector1 <=> std_vector2) >= 0);

        tests::compare("Vector1 <=> vector2 vs std <",
            (vector1 <=> vector2) == std::weak_ordering::less, (std_vector1 <=> std_vector2) == std::weak_ordering::less);
        tests::compare("Vector1 <=> vector2 vs std <>",
            (vector1 <=> vector2) != std::weak_ordering::equivalent, (std_vector1 <=> std_vector2) != std::weak_ordering::equivalent);
        tests::compare("Vector1 <=> vector2 vs std <=",
            (vector1 <=> vector2) != std::weak_ordering::greater, (std_vector1 <=> std_vector2) != std::weak_ordering::greater);


        std::cout << "Compare operators for objects of different size\n\n";

        tests::compare("Vector1 == vector3 vs std", vector1 == vector3, std_vector1 == std_vector3);

        tests::compare("Vector1 != vector3 vs std", vector1 != vector3, std_vector1 != std_vector3);

        tests::compare("Vector1 < vector3 vs std", vector1 < vector3, std_vector1 < std_vector3);
        tests::compare("Vector3 < vector1 vs std", vector3 < vector1, std_vector3 < std_vector1);
        tests::compare("Vector2 < vector3 vs std", vector2 < vector3, std_vector2 < std_vector3);
        tests::compare("Vector3 < vector2 vs std", vector3 < vector2, std_vector3 < std_vector2);

        tests::compare("Vector1 > vector3 vs std", vector1 > vector3, std_vector1 > std_vector3);
        tests::compare("Vector3 > vector1 vs std", vector3 > vector1, std_vector3 > std_vector1);
        tests::compare("Vector2 > vector3 vs std", vector2 > vector3, std_vector2 > std_vector3);
        tests::compare("Vector3 > vector2 vs std", vector3 > vector2, std_vector3 > std_vector2);

        tests::compare("Vector1 <= vector3 vs std", vector1 <= vector3, std_vector1 <= std_vector3);
        tests::compare("Vector3 <= vector1 vs std", vector3 <= vector1, std_vector3 <= std_vector1);
        tests::compare("Vector2 <= vector3 vs std", vector2 <= vector3, std_vector2 <= std_vector3);
        tests::compare("Vector3 <= vector2 vs std", vector3 <= vector2, std_vector3 <= std_vector2);

        tests::compare("Vector1 >= vector3 vs std", vector1 >= vector3, std_vector1 >= std_vector3);
        tests::compare("Vector3 >= vector1 vs std", vector3 >= vector1, std_vector3 >= std_vector1);
        tests::compare("Vector2 >= vector3 vs std", vector2 >= vector3, std_vector2 >= std_vector3);
        tests::compare("Vector3 >= vector2 vs std", vector3 >= vector2, std_vector3 >= std_vector2);

        tests::compare("Vector1 <=> vector3 vs std ==", (vector1 <=> vector3) == 0, (std_vector1 <=> std_vector3) == 0);
        tests::compare("Vector1 <=> vector3 vs std <", (vector1 <=> vector3) < 0, (std_vector1 <=> std_vector3) < 0);
        tests::compare("Vector1 <=> vector3 vs std >", (vector1 <=> vector3) > 0, (std_vector1 <=> std_vector3) > 0);
        tests::compare("Vector1 <=> vector3 vs std <=", (vector1 <=> vector3) <= 0, (std_vector1 <=> std_vector3) <= 0);
        tests::compare("Vector1 <=> vector3 vs std >=", (vector1 <=> vector3) >= 0, (std_vector1 <=> std_vector3) >= 0);

        tests::compare("Vector1 <=> vector3 vs std >=",
            (vector1 <=> vector3) != std::weak_ordering::less, (std_vector1 <=> std_vector3) != std::weak_ordering::less);
        tests::compare("Vector1 <=> vector3 vs std ==",
            (vector1 <=> vector3) == std::weak_ordering::equivalent, (std_vector1 <=> std_vector3) == std::weak_ordering::equivalent);
        tests::compare("Vector1 <=> vector3 vs std <= ",
            (vector1 <=> vector3) != std::weak_ordering::greater, (std_vector1 <=> std_vector3) != std::weak_ordering::greater);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
