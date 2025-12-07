/**
 * @file vector_grow_test.cpp
 * @brief This file tests functions increasing Vector length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/vector.h"

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
        std::cout << "Start vector_grow_test:\n";

        dsa::Vector<int> vector1 = dsa::Vector<int>(1, 40);
        auto* iter1 = vector1.insert(vector1.cbegin(), 30);
        vector1.insert(iter1, { 10, 20 });
        for (const auto& item : { 0, 4, 2 })
        {
            iter1 = vector1.begin();
            std::advance(iter1, item);
            vector1.insert(iter1, item);
        }
        const std::initializer_list<int> expected1 = { 0, 10, 2, 20, 30, 4, 40 };
        tests::compare("Vector1", vector1, expected1);

        dsa::Vector<int> vector2 = dsa::Vector<int>(1, 10);
        vector2.push_back(20);
        vector2.push_back(30);
        vector2.push_back(40);
        vector2.push_back(50);
        vector2.insert(vector2.cbegin(), 5, 5);
        const std::initializer_list<int> expected2 = { 5, 5, 5, 5, 5, 10, 20, 30, 40, 50 };
        tests::compare("Vector2", vector2, expected2);

        dsa::Vector<int> vector3 = dsa::Vector<int>(1, 20);
        vector3.push_back(30);
        vector3.push_back(40);
        vector3.push_back(50);
        auto* iter3 = vector3.insert(vector3.cbegin(), 10);
        iter3 = vector3.insert(iter3, { 1, 2, 3 });
        tests::compare("Vector3 iter", *iter3, 1);
        vector3.insert(std::next(vector3.begin(), static_cast<int>(vector3.size())), 60);
        const std::initializer_list<int> expected3 = { 1, 2, 3, 10, 20, 30, 40, 50, 60 };
        tests::compare("Vector3", vector3, expected3);

        dsa::Vector<int> vector4;
        vector4.push_back(20);
        vector4.push_back(30);
        vector4.push_back(40);
        auto* iter4 = vector4.insert(vector4.cbegin(), 10);
        tests::compare("Vector4 iter", *iter4, 10);
        const std::initializer_list<int> expected4 = { 10, 20, 30, 40 };
        tests::compare("Vector4", vector4, expected4);

        dsa::Vector<int> vector5{ 10, 20, 30 };
        vector5.insert(vector5.end(), 40);
        const std::initializer_list<int> expected5 = { 10, 20, 30, 40 };
        tests::compare("Vector5", vector5, expected5);

        dsa::Vector<int> vector6{ 10, 20, 30 };
        vector6.insert(vector6.end(), { 40, 50, 60 });
        const std::initializer_list<int> expected6 = { 10, 20, 30, 40, 50, 60 };
        tests::compare("Vector6", vector6, expected6);

        dsa::Vector<int> vector7{ 40 };
        vector7.insert(vector7.begin(), { 10, 20, 30 });
        const std::initializer_list<int> expected7 = { 10, 20, 30, 40 };
        tests::compare("Vector7", vector7, expected7);

        dsa::Vector<int> vector8{ 40 };
        vector8.reserve(10);
        vector8.insert(vector8.begin(), { 10, 20, 30 });
        const std::initializer_list<int> expected8 = { 10, 20, 30, 40 };
        tests::compare("Vector8", vector8, expected8);

        dsa::Vector<int> vector9 = dsa::Vector<int>({ 0, 10, 20 });
        dsa::Vector<int> temp9 = dsa::Vector<int>({ 0, 1, 2, 3, 4, 5 });
        vector9.insert(vector9.begin() + 1, temp9.begin() + 1, temp9.begin() + 4);
        const std::initializer_list<int> expected9 = { 0, 1, 2, 3, 10, 20 };
        tests::compare("Vector9", vector9, expected9);

        dsa::Vector<int> vector10 = dsa::Vector<int>({ 0, 10, 20 });
        vector10.reserve(10);
        dsa::Vector<int> temp10 = dsa::Vector<int>({ 0, 1, 2, 3, 4, 5 });
        vector10.insert(vector10.begin() + 1, temp10.begin() + 1, temp10.begin() + 4);
        const std::initializer_list<int> expected10 = { 0, 1, 2, 3, 10, 20 };
        tests::compare("Vector10", vector10, expected10);

        // test size / capacity
        dsa::Vector<int> vector11;
        vector11.clear();
        tests::compare("Vector11 size()", vector11.size(), static_cast<std::size_t>(0));
        tests::compare("Vector11 capacity()", vector11.capacity(), static_cast<std::size_t>(0));
        std::vector<int> expected11{ 1, 2, 4, 4, 8 };
        for (size_t i = 0; i < expected11.size(); i++)
        {
            vector11.push_back(static_cast<int>(i));
            tests::compare("Vector11 size()", vector11.size(), i + 1);
            tests::compare("Vector11 capacity()", vector11.capacity(), static_cast<std::size_t>(expected11[i]));
        }
        vector11.resize(0);
        tests::compare("Vector11 size()", vector11.size(), static_cast<std::size_t>(0));
        tests::compare("Vector11 capacity()", vector11.capacity(), static_cast<std::size_t>(8));

        dsa::Vector<int> vector12{ 0, 10, 20, 30 };
        vector12.emplace(vector12.begin() + 1, 5);
        const std::initializer_list<int> expected12 = { 0, 5, 10, 20, 30 };
        tests::compare("Vector12", vector12, expected12);

        dsa::Vector<int> vector13{ 0, 10, 20, 30 };
        vector13.reserve(10);
        vector13.emplace(vector13.begin(), -10);
        const std::initializer_list<int> expected13 = { -10, 0, 10, 20, 30 };
        tests::compare("Vector13", vector13, expected13);

        dsa::Vector<int> vector14{ 0, 10, 20, 30 };
        vector14.emplace_back(40);
        const std::initializer_list<int> expected14 = { 0, 10, 20, 30, 40 };
        tests::compare("Vector14", vector14, expected14);

        dsa::Vector<int> vector15{ 0, 10, 20, 30 };
        vector15.reserve(10);
        vector15.emplace_back(40);
        const std::initializer_list<int> expected15 = { 0, 10, 20, 30, 40 };
        tests::compare("Vector15", vector15, expected15);


        std::cout << "Compare operations results with std container\n\n";

        std::vector<int> std_vector5{ 10, 20, 30 };
        std_vector5.insert(std_vector5.end(), 40);
        tests::compare("Vector5 vs std", vector5, std_vector5);

        std::vector<int> std_vector6{ 10, 20, 30 };
        std_vector6.insert(std_vector6.end(), { 40, 50, 60 });
        tests::compare("Vector6 vs std", vector6, std_vector6);

        std::vector<int> std_vector7{ 40 };
        std_vector7.insert(std_vector7.begin(), { 10, 20, 30 });
        tests::compare("Vector7 vs std", vector7, std_vector7);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
