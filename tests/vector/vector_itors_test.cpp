/**
 * @file vector_itors_test.cpp
 * @brief This file tests Vector iterators
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
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <vector>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start vector_itors_test:\n";

        std::cout << "Explicit iterator\n";
        dsa::Vector<int> vector1{ 0, 10, 20 };
        // NOLINTNEXTLINE(modernize-loop-convert)
        for (dsa::Vector<int>::iterator iterator = vector1.begin(); iterator != vector1.end(); iterator++)
        {
            *iterator += 100;
            std::cout << *iterator << '\t';
        }
        std::cout << '\n';
        const std::initializer_list<int> expected1 = { 100, 110, 120 };
        tests::compare("Vector1", vector1, expected1);

        std::cout << "Auto iterator\n";
        dsa::Vector<int> vector2{ 0, 25, 50 };
        for (auto& item : vector2)
        {
            item += 100;
            std::cout << item << '\t';
        }
        std::cout << '\n';
        const std::initializer_list<int> expected2 = { 100, 125, 150 };
        tests::compare("Vector2", vector2, expected2);

        std::cout << "Explicit const_iterator\n";
        const dsa::Vector<int> vector3{ 0, 10, 20 };
        // NOLINTNEXTLINE(modernize-loop-convert)
        for (dsa::Vector<int>::const_iterator iterator = vector3.cbegin(); iterator != vector3.cend(); iterator++)
        {
            std::cout << (*iterator) << '\t';
        }
        std::cout << '\n';
        const std::initializer_list<int> expected3 = { 0, 10, 20 };
        tests::compare("Vector3", vector3, expected3);

        std::cout << "Auto const_iterator\n";
        const dsa::Vector<int> vector4{ 0, 25, 50 };
        for (const auto& item : vector4)
        {
            std::cout << item << '\t';
        }
        std::cout << '\n';
        const std::initializer_list<int> expected4 = { 0, 25, 50 };
        tests::compare("Vector4", vector4, expected4);

        // Check iterator of one element
        dsa::Vector<int> vector5 = dsa::Vector<int>(1, 0);
        auto* iterator = vector5.insert(vector5.cbegin(), 10);
        int val = *iterator;
        const int expectedval5 = 10;
        tests::compare("Vector5 iterator", val, expectedval5);
        const std::initializer_list<int> expected5 = { 10, 0 };
        tests::compare("Vector5", vector5, expected5);

        // Check iterator after inserting 0 elements
        dsa::Vector<int> vector6 = dsa::Vector<int>(1, 30);
        vector6.push_back(40);
        vector6.push_back(50);
        iterator = vector6.insert(vector6.cbegin(), 0, 5);
        val = *iterator;
        const int expectedval6 = 30;
        tests::compare("Vector6 iterator", val, expectedval6);
        const std::initializer_list<int> expected6 = { 30, 40, 50 };
        tests::compare("Vector6", vector6, expected6);

        // Range based loop
        const std::initializer_list<int> expected7 = { 10, 20, 30, 40, 50 };
        std::initializer_list<int>::iterator il_iterator{};
        const dsa::Vector<int> vector7 = dsa::Vector<int>{ 10, 20, 30, 40, 50 };
        std::cout << "List7 vs std::initializer_list:\n";
        il_iterator = expected7.begin();
        for (const auto& item : vector7)
        {
            std::cout << item << ' ' << *il_iterator << ' ';
            tests::compare(item, *(il_iterator++));
        }
        std::cout << '\n';
        il_iterator = expected7.begin();
        for (const auto& item : vector7)
        {
            std::cout << item << ' ' << *il_iterator << ' ';
            tests::compare(item, *(il_iterator++));
        }
        std::cout << '\n';
        il_iterator = expected7.begin();
        for (const auto& item : vector7)
        {
            std::cout << item << ' ' << *il_iterator << ' ';
            tests::compare(item, *(il_iterator++));
        }
        std::cout << '\n';
        il_iterator = expected7.begin();
        for (const auto& item : vector7)
        {
            std::cout << item << ' ' << *il_iterator << ' ';
            tests::compare(item, *(il_iterator++));
        }
        std::cout << "\n\n";

        // Compare elements based on range loops
        const std::initializer_list<int> expected8 = { 10, 20, 30, 40, 50 };
        const dsa::Vector<int> vector8 = dsa::Vector<int>{ 10, 20, 30, 40, 50 };
        std::cout << "List8 vs std::initializer_list:\n";
        il_iterator = expected8.begin();
        for (const auto& item : vector8)
        {
            std::cout << item << ' ' << *il_iterator << ' ';
            tests::compare(item, *(il_iterator++));
        }
        std::cout << '\n';
        il_iterator = expected8.begin();
        for (const auto& item : vector8)
        {
            std::cout << item << ' ' << *il_iterator << ' ';
            tests::compare(item, *(il_iterator++));
        }
        std::cout << '\n';
        il_iterator = expected8.begin();
        for (const auto& item : vector8)
        {
            std::cout << item << ' ' << *il_iterator << ' ';
            tests::compare(item, *(il_iterator++));
        }
        std::cout << '\n';
        il_iterator = expected8.begin();
        for (const auto& item : vector8)
        {
            std::cout << item << ' ' << *il_iterator << ' ';
            tests::compare(item, *(il_iterator++));
        }
        std::cout << "\n\n";

        // std library operation on custom iterators
        dsa::Vector<int> vector9 = dsa::Vector<int>{ 10, 20, 30, 40, 50 };
        // use classic iterator based algorithms, separate test was added to test std::ranges based algorithms
        // NOLINTNEXTLINE(modernize-use-ranges)
        std::fill(vector9.begin(), vector9.end(), 10);
        const std::initializer_list<int> expected9 = { 10, 10, 10, 10, 10 };
        tests::compare("Vector9", vector9, expected9);

        // check const_iterator for const object
        dsa::Vector<int> vector10 = dsa::Vector<int>{ 10, 20, 30 };
        auto* const iter10b = vector10.begin();
        tests::compare("iter10b", *iter10b, 10);
        *iter10b = 1;
        const auto* const citer10b = vector10.cbegin();
        tests::compare("citer10b", *citer10b, 1);

        auto* iter10e = vector10.end();
        tests::compare("iter10e", *std::prev(iter10e), 30);

        const auto* citer10e = vector10.cend();
        tests::compare("citer10e", *std::prev(citer10e), 30);

        const dsa::Vector<int> vector11 = dsa::Vector<int>{ 10, 20, 30 };
        const auto* const iter11b = vector11.begin();
        tests::compare("iter11b", *iter11b, 10);

        const auto* citer11b = vector11.cbegin();
        tests::compare("citer11b", *citer11b, 10);

        const auto* iter11e = vector11.end();
        tests::compare("iter11e", *std::prev(iter11e), 30);

        const auto* citer11e = vector11.cend();
        tests::compare("citer11e", *std::prev(citer11e), 30);

        // increment iterator
        dsa::Vector<int> vector12 = dsa::Vector<int>{ 10, 20, 30 };
        std::cout << "List12\t" << vector12 << '\n';
        auto* it_12 = vector12.begin();
        tests::compare("it_12", *it_12, 10);
        std::advance(it_12, 1);
        tests::compare("it_12", *it_12, 20);
        std::advance(it_12, 1);
        tests::compare("it_12", *it_12, 30);
        std::cout << '\n';

        // increment const_iterator
        const dsa::Vector<int> vector13 = dsa::Vector<int>{ 10, 20, 30 };
        std::cout << "List13\t" << vector13 << '\n';

        const auto* cit_13 = vector13.cbegin();
        tests::compare("cit_13", *cit_13, 10);
        std::advance(cit_13, 1);
        tests::compare("cit_13", *cit_13, 20);
        std::advance(cit_13, 1);
        tests::compare("cit_13", *cit_13, 30);
        std::cout << '\n';

        // decrement iterator
        dsa::Vector<int> vector14 = dsa::Vector<int>{ 10, 20, 30 };
        std::cout << "List14\t" << vector14 << '\n';
        auto* it_14 = vector14.end();
        std::advance(it_14, -1);
        tests::compare("it_14", *it_14, 30);
        std::advance(it_14, -1);
        tests::compare("it_14", *it_14, 20);
        std::advance(it_14, -1);
        tests::compare("it_14", *it_14, 10);
        std::cout << '\n';

        // decrement const_iterator
        const dsa::Vector<int> vector15 = dsa::Vector<int>{ 10, 20, 30 };
        std::cout << "List15\t" << vector15 << '\n';
        const auto* cit_15 = vector15.cend();
        std::advance(cit_15, -1);
        tests::compare("cit_15", *cit_15, 30);
        std::advance(cit_15, -1);
        tests::compare("cit_15", *cit_15, 20);
        std::advance(cit_15, -1);
        tests::compare("cit_15", *cit_15, 10);

        // test iterators traversal
        dsa::Vector<int> vector16 = { 0, 10, 20, 30, 40 };
        const std::vector<int> temp16(vector16.begin(), vector16.end());
        tests::compare("vector16 begin()", *vector16.begin(), 0);
        auto* iter16 = vector16.begin();
        std::advance(iter16, 1);
        tests::compare("vector16 begin()++", *iter16, 10);
        iter16 = vector16.end();
        std::advance(iter16, -1);
        tests::compare("vector16 end()--", *iter16, 40);
        tests::compare("vector16 end()-- == back()", *iter16, vector16.back());
        tests::compare("vector16 iter", vector16, temp16);

        // test const iterator traversal
        const auto& vector17 = vector16;
        const std::vector<int> temp17(vector17.cbegin(), vector17.cend());
        tests::compare("vector17 cbegin()", *vector17.cbegin(), 0);
        const auto* citer17 = vector17.cbegin();
        std::advance(citer17, 1);
        tests::compare("vector17 cbegin()++", *citer17, 10);
        citer17 = vector17.cend();
        std::advance(citer17, -1);
        tests::compare("vector17 cend()--", *citer17, 40);
        tests::compare("vector17 cend() == back()", *citer17, vector17.back());
        tests::compare("vector17 const iter", vector17, temp17);

        // test reverse iterator traversal
        dsa::Vector<int> vector18{ 0, 1, 2, 3, 4 };
        auto iter18 = vector18.rend();
        std::advance(iter18, -1);
        tests::compare("vector18 rend()--", *iter18, 0);
        iter18 = vector18.rbegin();
        std::advance(iter18, 1);
        tests::compare("vector18 rbegin()++", *iter18, 3);
        const std::vector<int> temp18(vector18.rbegin(), vector18.rend());
        const dsa::Vector<int> reversed18{ 4, 3, 2, 1, 0 };
        tests::compare("vector18 reverse iter", reversed18, temp18);

        // test empty vector
        dsa::Vector<int> vector19;
        tests::compare("vector19 begin() == cbegin()", vector19.begin() == vector19.cbegin(), true);
        tests::compare("vector19 begin() == end()", vector19.begin() == vector19.end(), true);
        tests::compare("vector19 end() == cend()", vector19.end() == vector19.cend(), true);
        tests::compare("vector19 rbegin() == crbegin()", vector19.rbegin() == vector19.crbegin(), true);
        tests::compare("vector19 rbegin() == rend()", vector19.rbegin() == vector19.rend(), true);
        tests::compare("vector19 rend() == crend()", vector19.rend() == vector19.crend(), true);
        tests::compare("vector19 size()", vector19.size(), static_cast<std::size_t>(0));
        tests::compare("vector19 max_size()", vector19.max_size(), std::numeric_limits<std::size_t>::max() / sizeof(int));
        tests::compare("vector19 empty()", vector19.empty(), true);

        // test element access
        dsa::Vector<int> vector20{ 10, 20, 30 };
        tests::compare("vector20 front()", vector20.front(), 10);
        tests::compare("vector20[0]", vector20[0], 10);
        tests::compare("vector20[1]", vector20[1], 20);
        tests::compare("vector20 at(1)", vector20.at(1), 20);
        tests::compare("vector20 back()", vector20.back(), 30);
        const std::vector<int> expected20{ 10, 20, 30 };
        tests::compare("vector20()", vector20, expected20);

        // test data access
        int* ptr_vector20 = vector20.data();
        static_assert(std::is_same_v<decltype(vector20.data()), int*>, "data() must return T*");
        tests::compare("vector20[0]", *ptr_vector20, 10);

        // test throwing 'out of range' exception
        try
        {
            dsa::Vector<int> vector21{};
            tests::compare("vector21 at(10)", vector21.at(10), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "vector21 out of range exception handled correctly\n\n";
        }

        // test element access
        const dsa::Vector<int> vector22{ 10, 20, 30 };
        tests::compare("vector22 front()", vector22.front(), 10);
        tests::compare("vector22[0]", vector22[0], 10);
        tests::compare("vector22[1]", vector22[1], 20);
        tests::compare("vector22 at(1)", vector22.at(1), 20);
        tests::compare("vector22 back()", vector22.back(), 30);
        const std::vector<int> expected22{ 10, 20, 30 };
        tests::compare("vector22()", vector22, expected22);

        // test const data access
        const int* ptr_vector22 = vector22.data();
        static_assert(std::is_same_v<decltype(vector22.data()), const int*>, "data() must return T*");
        tests::compare("vector21[0]", *ptr_vector22, 10);

        // use lambda expression as workaround to prevent inlining call to const data()
        auto use_const_data = [](const auto& vector)
            {
                const int* ptr = vector.data();
                (void)ptr;
                return ptr;
            };
        const dsa::Vector<int> vector23{ 10, 20, 30 };
        const auto* ptr_vector23 = use_const_data(vector23);
        static_assert(std::is_same_v<decltype(vector23.data()), const int*>, "data() must return const T*");
        tests::compare("vector23[0]", *ptr_vector23, 10);

        // test throwing 'out of range' exception
        try
        {
            const dsa::Vector<int> vector24{};
            tests::compare("vector24 at(10)", vector24.at(10), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "vector24 out of range exception handled correctly\n\n";
        }


        std::cout << "Compare operations results with std container\n\n";

        std::vector<int> std_vector1{ 0, 10, 20 };
        // NOLINTNEXTLINE(modernize-loop-convert, modernize-use-auto)
        for (std::vector<int>::iterator std_iter = std_vector1.begin(); std_iter != std_vector1.end(); std_iter++)
        {
            *std_iter += 100;
            std::cout << *std_iter << "\t\n";
        }
        tests::compare("Vector1 vs std", vector1, std_vector1);

        std::vector<int> std_vector2{ 0, 25, 50 };
        for (auto& item : std_vector2)
        {
            item += 100;
            std::cout << item << "\t\n";
        }
        tests::compare("Vector2 vs std", vector2, std_vector2);

        const std::vector<int> std_vector3{ 0, 10, 20 };
        // NOLINTNEXTLINE(modernize-loop-convert, modernize-use-auto)
        for (std::vector<int>::const_iterator std_iter = std_vector3.cbegin(); std_iter != std_vector3.cend(); std_iter++)
        {
            std::cout << (*std_iter) << '\t';
        }
        std::cout << '\n';
        tests::compare("Vector3 vs std", vector3, std_vector3);

        const std::vector<int> std_vector4{ 0, 25, 50 };
        for (const auto& item : std_vector4)
        {
            std::cout << item << '\t';
        }
        std::cout << '\n';
        tests::compare("Vector4 vs std", vector4, std_vector4);

        std::vector<int> std_vector5 = std::vector<int>(1, 0);
        auto std_iterator = std_vector5.insert(std_vector5.cbegin(), 10);
        val = *std_iterator;
        tests::compare("Vector5 iterator vs std", expectedval5, val);
        tests::compare("Vector5 vs std", vector5, expected5);

        std::vector<int>std_vector6 = std::vector<int>(1, 30);
        std_vector6.push_back(40);
        std_vector6.push_back(50);
        std_iterator = std_vector6.insert(std_vector6.cbegin(), 0, 5);
        val = *std_iterator;
        tests::compare("Vector6 iterator vs std", expectedval6, val);
        tests::compare("Vector6 vs std", vector6, std_vector6);

        std::vector<int>std_vector9 = std::vector<int>{ 10, 20, 30, 40, 50 };
        // use classic iterator based algorithms, separate test was added to test std::ranges based algorithms
        // NOLINTNEXTLINE(modernize-use-ranges)
        std::fill(std_vector9.begin(), std_vector9.end(), 10);
        tests::compare("Vector9 vs std", vector9, std_vector9);

        std::vector<int>std_vector10 = std::vector<int>{ 10, 20, 30 };
        auto std_iter10b = std_vector10.begin();
        *std_iter10b = 1;
        auto std_citer10b = std_vector10.cbegin();
        tests::compare("citer10b vs std", *citer10b, *std_citer10b);

        const std::vector<int>std_vector11 = std::vector<int>{ 10, 20, 30 };
        auto std_iter11b = std_vector11.begin();
        tests::compare("iter11b vs std", *iter11b, *std_iter11b);

        auto std_citer11b = std_vector11.cbegin();
        tests::compare("citer11b vs std", *citer11b, *std_citer11b);

        // test iterators traversal
        std::vector<int> std_vector16 = { 0, 10, 20, 30, 40 };
        tests::compare("vector16 vs std begin()", *vector16.begin(), *std_vector16.begin());
        iter16 = vector16.begin();
        auto std_iter16 = std_vector16.begin();
        std::advance(iter16, 1);
        std::advance(std_iter16, 1);
        tests::compare("vector16 vs std begin()++", *iter16, *std_iter16);
        iter16 = vector16.end();
        std_iter16 = std_vector16.end();
        std::advance(iter16, -1);
        std::advance(std_iter16, -1);
        tests::compare("vector16 vs std end()--", *iter16, *std_iter16);
        tests::compare("vector16 vs std end()-- == back()", *iter16 == vector16.back(), *std_iter16 == std_vector16.back());
        tests::compare("vector16 vs std iter", vector16, std_vector16);

        // test const iterator traversal
        const auto& std_vector17 = std_vector16;
        tests::compare("vector17 vs std cbegin()", *vector17.cbegin(), *std_vector17.cbegin());
        citer17 = vector17.cbegin();
        auto std_citer17 = std_vector17.cbegin();
        std::advance(citer17, 1);
        std::advance(std_citer17, 1);
        tests::compare("vector17 vs std cbegin()++", *citer17, *std_citer17);
        citer17 = vector17.cend();
        std_citer17 = std_vector17.cend();
        std::advance(citer17, -1);
        std::advance(std_citer17, -1);
        tests::compare("vector6 vs std cend()--", *citer17, *std_citer17);
        tests::compare("vector6 vs std cend() == back()", *citer17 == vector17.back(), *std_citer17 == vector17.back());

        // test reverse iterator traversal
        std::vector<int> std_vector18{ 0, 1, 2, 3, 4 };
        iter18 = vector18.rend();
        auto std_iter18 = std_vector18.rend();
        std::advance(iter18, -1);
        std::advance(std_iter18, -1);
        tests::compare("std_vector18 vs std rend()--", *iter18, *std_iter18);
        iter18 = vector18.rbegin();
        std_iter18 = std_vector18.rbegin();
        std::advance(iter18, 1);
        std::advance(std_iter18, 1);
        tests::compare("std_vector18 vs std rbegin()++", *iter18, *std_iter18);

        // test empty vector
        std::vector<int> std_vector19{};
        tests::compare("vector19 vs std begin() == cbegin()",
            vector19.begin() == vector19.cbegin(), std_vector19.begin() == std_vector19.cbegin());
        tests::compare("vector19 vs std begin() == end()",
            vector19.begin() == vector19.end(), std_vector19.begin() == std_vector19.end());
        tests::compare("vector19 vs std end() == cend()",
            vector19.end() == vector19.cend(), std_vector19.end() == std_vector19.cend());
        tests::compare("vector19 vs std rbegin() == crbegin()",
            vector19.rbegin() == vector19.crbegin(), std_vector19.rbegin() == std_vector19.crbegin());
        tests::compare("vector19 vs std rbegin() == rend()",
            vector19.rbegin() == vector19.rend(), std_vector19.rbegin() == std_vector19.rend());
        tests::compare("vector19 vs std rend() == crend()",
            vector19.rend() == vector19.crend(), std_vector19.rend() == std_vector19.crend());

        // test element access
        std::vector<int> std_vector20{ 10, 20, 30 };
        tests::compare("vector20 front() vs std", vector20.front(), std_vector20.front());
        tests::compare("vector20[0] vs std", vector20[0], std_vector20[0]);
        tests::compare("vector20[1] vs std", vector20[1], std_vector20[1]);
        tests::compare("vector20 vs std at(1) ", vector20.at(1), std_vector20.at(1));
        tests::compare("vector20 vs std back()", vector20.back(), std_vector20.back());
        tests::compare("vector20() vs std", vector20, std_vector20);

        const std::vector<int> std_vector22{ 10, 20, 30 };
        tests::compare("vector22 front() vs std", vector22.front(), std_vector22.front());
        tests::compare("vector22[0] vs std", vector22[0], std_vector22[0]);
        tests::compare("vector22[1] vs std", vector22[1], std_vector22[1]);
        tests::compare("vector22 vs std at(1) ", vector22.at(1), std_vector22.at(1));
        tests::compare("vector22 vs std back()", vector22.back(), std_vector22.back());
        tests::compare("vector22() vs std", vector22, std_vector22);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
