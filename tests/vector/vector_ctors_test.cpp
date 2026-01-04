/**
 * @file vector_ctors_test.cpp
 * @brief This file tests Vector constructors
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
        std::cout << "Start vector_ctors_test:\n";

        const std::initializer_list<int> expected{ 0, 10, 20 };

        std::cout << "Default ctor\n";
        dsa::Vector<int> vector1;
        vector1.push_back(0);
        vector1.push_back(10);
        vector1.push_back(20);
        tests::compare("Vector1", vector1, expected);

        std::cout << "Value ctor\n";
        dsa::Vector<int> vector2(1, 10);
        vector2.push_back(20);
        vector2.insert(vector2.cbegin(), 0);
        tests::compare("Vector2", vector2, expected);

        std::cout << "Initializer vector ctor\n";
        const dsa::Vector<int> vector3(expected);
        tests::compare("Vector3", vector3, expected);

        std::cout << "Copy ctor\n";
        const dsa::Vector<int> vector4{ vector1 };
        tests::compare("Vector4", vector4, expected);

        std::cout << "Copy assignment ctor\n";
        dsa::Vector<int> vector5;
        vector5.push_back(1);
        vector5.push_back(2);
        vector5.push_back(3);
        vector5.push_back(4);
        vector5.push_back(5);
        vector5 = vector1;
        tests::compare("Vector5", vector5, expected);

        std::cout << "Copy self assignment ctor\n";
        dsa::Vector<int> vector6{ 0, 10, 20 };
        auto* pointer6 = &vector6;
        vector6 = *pointer6;
        tests::compare("Vector6", vector6, expected);

        std::cout << "Move ctor\n";
        dsa::Vector<int> temp_1(vector1);
        const dsa::Vector<int> vector7 = std::move(temp_1);
        tests::compare("Vector7", vector7, expected);

        std::cout << "Move assignment ctor\n";
        dsa::Vector<int> temp_2(vector1);
        dsa::Vector<int> vector8(1, 0);
        vector8 = std::move(temp_2);
        tests::compare("Vector8", vector8, expected);

        std::cout << "Move self assignment ctor\n";
        dsa::Vector<int> vector9{ 0, 10, 20 };
        auto* pointer9 = &vector9;
        vector9 = std::move(*pointer9);
        tests::compare("Vector9", vector9, expected);

        std::cout << "Initializer list ctor\n";
        const dsa::Vector<int> vector10{ 0, 10, 20 };
        tests::compare("Vector10", vector10, expected);

        const dsa::Vector<int> vector11 = { 0, 10, 20 };
        tests::compare("Vector11", vector11, expected);

        std::cout << "Construct from other Vector\n";
        dsa::Vector<int> temp12 = { 0, 10, 20, 30, 40, 50 };
        const dsa::Vector<int> vector12(temp12.begin() + 1, temp12.begin() + 4);
        const std::initializer_list<int> expected12{ 10, 20, 30 };
        tests::compare("Vector12", vector12, expected12);


        std::cout << "Compare operations results with std container\n\n";

        std::vector<int> std_vector1;
        std_vector1.push_back(0);
        std_vector1.push_back(10);
        std_vector1.push_back(20);
        tests::compare("Vector1 vs std", vector1, std_vector1);

        std::vector<int> std_vector2(1, 10);
        std_vector2.push_back(20);
        std_vector2.insert(std_vector2.cbegin(), 0);
        tests::compare("Vector2 vs std", vector2, std_vector2);

        const std::vector<int> std_vector3(expected);
        tests::compare("Vector3 vs std", vector3, std_vector3);

        const std::vector<int> std_vector4{ std_vector1 };
        tests::compare("Vector4 vs std", vector4, std_vector4);

        std::vector<int> std_vector5;
        std_vector5.push_back(1);
        std_vector5.push_back(2);
        std_vector5.push_back(3);
        std_vector5.push_back(4);
        std_vector5.push_back(5);
        std_vector5 = std_vector1;
        tests::compare("Vector5 vs std", vector5, expected);

        std::vector<int> std_temp_1(std_vector1);
        const std::vector<int> std_vector6 = std::move(std_temp_1);
        tests::compare("Vector6 vs std", vector6, expected);

        std::vector<int> std_temp_2(std_vector1);
        std::vector<int> std_vector7(1, 0);
        std_vector7 = std::move(std_temp_2);
        tests::compare("Vector7 vs std", vector7, expected);

        const std::vector<int> std_vector10{ 0, 10, 20 };
        tests::compare("Vector10 vs std", vector10, std_vector10);

        const std::vector<int> std_vector11 = { 0, 10, 20 };
        tests::compare("Vector11 vs std", vector11, std_vector11);

        const std::vector<int> std_temp12 = { 0, 10, 20, 30, 40, 50 };
        const dsa::Vector<int> std_vector12(std_temp12.begin() + 1, std_temp12.begin() + 4);
        tests::compare("Vector12 vs std", vector12, std_vector12);

        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
