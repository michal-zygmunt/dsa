/**
 * @file vector_set_test.cpp
 * @brief This file tests setting values of Vector elements
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
#include <vector>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start vector_set_test:\n";

        dsa::Vector<int> vector1 = dsa::Vector<int>({ 0, 10, 20 });
        const std::initializer_list<int> expected1{ 0, 1, 2 };
        vector1 = expected1;
        tests::compare("vector1", vector1, expected1);

        dsa::Vector<int> vector2 = dsa::Vector<int>({ 0, 10, 20 });
        vector2.assign(4, 1);
        const std::initializer_list<int> expected2 = { 1, 1, 1, 1 };
        tests::compare("vector2", vector2, expected2);

        dsa::Vector<int> vector3 = dsa::Vector<int>({ 0, 10, 20 });
        vector3.assign(0, 1);
        const std::initializer_list<int> expected3 = {};
        tests::compare("vector3", vector3, expected3);

        dsa::Vector<int> vector4 = dsa::Vector<int>({ 0, 10, 20 });
        const std::initializer_list<int> expected4 = { 1, 2, 3, 4 };
        vector4.assign(expected4);
        tests::compare("vector4", vector4, expected4);

        dsa::Vector<int> vector5 = dsa::Vector<int>({ 0, 10, 20 });
        dsa::Vector<int> temp5 = dsa::Vector<int>({ 0, 1, 2, 3, 4, 5 });
        vector5.assign(temp5.begin() + 1, temp5.begin() + 4);
        const std::initializer_list<int> expected5 = { 1, 2, 3 };
        tests::compare("vector5", vector5, expected5);


        std::cout << "Compare operations results with std container\n\n";

        std::vector<int> std_vector1 = std::vector<int>({ 0, 10, 20 });
        std_vector1 = expected1;
        tests::compare("vector1 vs std", vector1, std_vector1);

        std::vector<int> std_vector2 = std::vector<int>({ 0, 10, 20 });
        std_vector2.assign(4, 1);
        tests::compare("vector2 vs std", vector2, std_vector2);

        std::vector<int> std_vector3 = std::vector<int>({ 0, 10, 20 });
        std_vector3.assign(0, 1);
        tests::compare("vector3 vs std", vector3, std_vector3);

        std::vector<int> std_vector4 = std::vector<int>({ 0, 10, 20 });
        std_vector4.assign(expected4);
        tests::compare("vector4 vs std", vector4, std_vector4);

        std::vector<int> std_vector5 = std::vector<int>({ 0, 10, 20 });
        std_vector5.assign(temp5.begin() + 1, temp5.begin() + 4);
        tests::compare("vector5 vs std", vector5, std_vector5);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
