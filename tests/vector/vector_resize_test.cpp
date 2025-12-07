/**
 * @file vector_resize_test.cpp
 * @brief This file tests functions resizing Vector objects
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
#include <limits>
#include <memory>
#include <stdexcept>
#include <vector>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start vector_resize_test:\n";

        dsa::Vector<int> vector1 = dsa::Vector<int>({ 1, 2, 3, 4, 5 });
        vector1.resize(3);
        const std::initializer_list<int> expected1 = { 1, 2, 3 };
        tests::compare("Vector1", vector1, expected1);

        dsa::Vector<int> vector2 = dsa::Vector<int>({ 1, 2, 3, 4, 5 });
        vector2.resize(5);
        const std::initializer_list<int> expected2 = { 1, 2, 3, 4, 5 };
        tests::compare("Vector2", vector2, expected2);

        dsa::Vector<int> vector3 = dsa::Vector<int>({ 1, 2, 3, 4, 5 });
        vector3.resize(8);
        const std::initializer_list<int> expected3 = { 1, 2, 3, 4, 5, 0, 0, 0 };
        tests::compare("Vector3", vector3, expected3);

        dsa::Vector<int> vector4;
        vector4.resize(5);
        const std::initializer_list<int> expected4 = { 0, 0, 0, 0, 0 };
        tests::compare("Vector4", vector4, expected4);

        dsa::Vector<int> vector5 = dsa::Vector<int>({ 1, 2, 3, 4, 5 });
        vector5.resize(3, 10);
        const std::initializer_list<int> expected5 = { 1, 2, 3 };
        tests::compare("Vector5", vector5, expected5);

        dsa::Vector<int> vector6 = dsa::Vector<int>({ 1, 2, 3, 4, 5 });
        vector6.resize(5, 10);
        const std::initializer_list<int> expected6 = { 1, 2, 3, 4, 5 };
        tests::compare("Vector6", vector6, expected6);

        dsa::Vector<int> vector7 = dsa::Vector<int>({ 1, 2, 3, 4, 5 });
        vector7.resize(8, 10);
        const std::initializer_list<int> expected7 = { 1, 2, 3, 4, 5, 10, 10, 10 };
        tests::compare("Vector7", vector7, expected7);

        dsa::Vector<int> vector8;
        vector8.resize(5, 10);
        const std::initializer_list<int> expected8 = { 10, 10, 10, 10, 10 };
        tests::compare("Vector8", vector8, expected8);

        const dsa::Vector<int> vector9;
        tests::compare("max_size()", vector9.max_size(), std::numeric_limits<std::size_t>::max() / sizeof(int));

        dsa::Vector<int> vector10 = dsa::Vector<int>({ 1, 2, 3, 4, 5 });
        vector10.resize(0);
        const std::initializer_list<int> expected10 = { };
        tests::compare("Vector10", vector10, expected10);

        // test empty vector
        const dsa::Vector<int> vector11;
        tests::compare("vector11 empty()", vector11.empty(), true);
        tests::compare("vector11 size()", vector11.size(), static_cast<std::size_t>(0));
        tests::compare("vector11 max_size()", vector11.max_size(), std::numeric_limits<std::size_t>::max() / sizeof(int));

        // test throwing 'length_error' exception from resize
        try
        {
            dsa::Vector<int> vector12{};
            vector12.resize(vector12.max_size() + 1);
        }
        catch (const std::length_error&)
        {
            std::cout << "vector12 length error exception handled correctly for resize\n\n";
        }

        // test throwing 'length_error' exception from reserve
        try
        {
            dsa::Vector<int> vector13{};
            vector13.reserve(vector13.max_size() + 1);
        }
        catch (const std::length_error&)
        {
            std::cout << "vector13 length error exception handled correctly for reserve\n\n";
        }


        std::cout << "Compare operations results with std container\n\n";

        std::vector<int> std_vector1{ 1, 2, 3, 4, 5 };
        std_vector1.resize(3);
        tests::compare("Vector1 vs std", vector1, std_vector1);

        std::vector<int> std_vector2{ 1, 2, 3, 4, 5 };
        std_vector2.resize(5);
        tests::compare("Vector2 vs std", vector2, std_vector2);

        std::vector<int> std_vector3{ 1, 2, 3, 4, 5 };
        std_vector3.resize(8);
        tests::compare("Vector3 vs std", vector3, std_vector3);

        std::vector<int> std_vector4;
        std_vector4.resize(5);
        tests::compare("Vector4 vs std", vector4, std_vector4);

        std::vector<int> std_vector5{ 1, 2, 3, 4, 5 };
        std_vector5.resize(3, 10);
        tests::compare("Vector5 vs std", vector5, std_vector5);

        std::vector<int> std_vector6{ 1, 2, 3, 4, 5 };
        std_vector6.resize(5, 10);
        tests::compare("Vector6 vs std", vector6, std_vector6);

        std::vector<int> std_vector7{ 1, 2, 3, 4, 5 };
        std_vector7.resize(8, 10);
        tests::compare("Vector7 vs std", vector7, std_vector7);

        std::vector<int> std_vector8;
        std_vector8.resize(5, 10);
        tests::compare("Vector8 vs std", vector8, std_vector8);

        std::vector<int> std_vector10{ 1, 2, 3, 4, 5 };
        std_vector10.resize(0);
        tests::compare("Vector10 vs std", vector10, std_vector10);

        // test capacity
        const std::vector<int> std_vector11;
        const std::allocator<int> alloc;
        const std::size_t std_vector11_max_size = std::allocator_traits<decltype(alloc)>::max_size(alloc);
        tests::compare("vector11 vs std empty()", vector11.empty(), std_vector11.empty());
        tests::compare("vector11 vs std size()", vector11.size(), std_vector11.size());
        tests::compare("vector11 vs std max_size()", vector11.max_size(), std_vector11_max_size);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
