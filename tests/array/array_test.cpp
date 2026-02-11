/**
 * @file array_test.cpp
 * @brief This file tests Array class
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
#include <cstddef>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start array_test:\n";

        std::cout << "Default ctor\n";

        // Test aggregate initialization
        const dsa::Array<int, 3> array1{ 0, 1, 2 };
        tests::compare("Array1", array1, { 0, 1, 2 });

        const dsa::Array<int, 3> array2 = { 0, 10, 20 };
        tests::compare("Array2", array2, { 0, 10, 20 });

        dsa::Array<int, 3> array2b = { 0, 10, 20 };
        array2b = array1;
        tests::compare("Array2b = Array1", array2b, { 0, 1, 2 });

        // Test element access
        dsa::Array<int, 3> array3{ 10, 20, 30 };
        tests::compare("Array3 front()", array3.front(), 10);
        tests::compare("Array3[0]", array3[0], 10);
        tests::compare("Array3[1]", array3[1], 20);
        tests::compare("Array3 back()", array3.back(), 30);
        tests::compare("Array3 at(0)", array3.at(0), 10);
        tests::compare("Array3 at(1)", array3.at(1), 20);
        tests::compare("Array3 at(2)", array3.at(2), 30);
        const std::array<int, 3> expected3{ 10, 20, 30 };
        tests::compare("Array3()", array3, expected3);

        // Test data access
        int* ptr_d3 = array3.data();
        static_assert(std::is_same_v<decltype(array3.data()), int*>, "data() must return T*");
        tests::compare("Array3[0]", *ptr_d3, 10);

        // use lambda expression as workaround to prevent inlining call to const data()
        auto use_const_data = [](const auto& array)
            {
                const int* ptr = array.data();
                (void)ptr;
                return ptr;
            };
        const dsa::Array<int, 3> const_array3{ 10, 20, 30 };
        const auto* ptr_cd3 = use_const_data(const_array3);
        static_assert(std::is_same_v<decltype(expected3.data()), const int*>, "data() must return const T*");
        tests::compare("const Array3[0]", *ptr_cd3, 10);

        // Test throwing 'out of range' exception
        try
        {
            dsa::Array<int, 0> array4a{};
            tests::compare("Array4a at(0)", array4a.at(0), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Array4a out of range exception handled correctly\n\n";
        }

        try
        {
            dsa::Array<int, 0> array4b{};
            tests::compare("Array4b at(0)", array4b.at(0), 0);
            tests::compare("Array4b at(1)", array4b.at(1), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Array4b out of range exception handled correctly\n\n";
        }

        try
        {
            dsa::Array<int, 0> array4c{};
            tests::compare("Array4c at(2)", array4c.at(2), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Array4c out of range exception handled correctly\n\n";
        }

        try
        {
            dsa::Array<int, 1> array4d{ 1 };
            tests::compare("Array4d at(0)", array4d.at(0), 1);
            tests::compare("Array4d at(1)", array4d.at(1), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Array4d out of range exception handled correctly\n\n";
        }

        try
        {
            dsa::Array<int, 1> array4e{ 1 };
            tests::compare("Array4e at(0)", array4e.at(0), 1);
            tests::compare("Array4e at(2)", array4e.at(2), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Array4e out of range exception handled correctly\n\n";
        }

        try
        {
            dsa::Array<int, 2> array4f{ 1, 2 };
            tests::compare("Array4f at(0)", array4f.at(0), 1);
            tests::compare("Array4f at(1)", array4f.at(1), 2);
            tests::compare("Array4f at(2)", array4f.at(2), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Array4f out of range exception handled correctly\n\n";
        }

        try
        {
            dsa::Array<int, 2> array4g{ 1, 2 };
            tests::compare("Array4g at(0)", array4g.at(0), 1);
            tests::compare("Array4g at(1)", array4g.at(1), 2);
            tests::compare("Array4g at(10)", array4g.at(10), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Array4g out of range exception handled correctly\n\n";
        }

        try
        {
            dsa::Array<int, 5> array4h{ 1, 2 };
            tests::compare("Array4h at(0)", array4h.at(0), 1);
            tests::compare("Array4h at(1)", array4h.at(1), 2);
            tests::compare("Array4h at(2)", array4h.at(2), 0);
            tests::compare("Array4h at(10)", array4h.at(10), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Array4h out of range exception handled correctly\n\n";
        }

        try
        {
            dsa::Array<int, 5> array4i{};
            tests::compare("Array4i at(0)", array4i.at(0), 0);
            tests::compare("Array4i at(1)", array4i.at(1), 0);
            tests::compare("Array4i at(2)", array4i.at(2), 0);
            tests::compare("Array4i at(3)", array4i.at(3), 0);
            tests::compare("Array4i at(4)", array4i.at(4), 0);
            tests::compare("Array4i at(10)", array4i.at(10), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Array4i out of range exception handled correctly\n\n";
        }

        // Test throwing 'out of range' exception for const Array

        try
        {
            const dsa::Array<int, 0> array4a{};
            tests::compare("const Array4a at(0)", array4a.at(0), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "const Array4a out of range exception handled correctly\n\n";
        }

        try
        {
            const dsa::Array<int, 0> array4b{};
            tests::compare("const Array4b at(0)", array4b.at(0), 0);
            tests::compare("const Array4b at(1)", array4b.at(1), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "const Array4b out of range exception handled correctly\n\n";
        }

        try
        {
            const dsa::Array<int, 0> array4c{};
            tests::compare("const Array4c at(2)", array4c.at(2), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "const Array4c out of range exception handled correctly\n\n";
        }

        try
        {
            const dsa::Array<int, 1> array4d{ 1 };
            tests::compare("const Array4d at(0)", array4d.at(0), 1);
            tests::compare("const Array4d at(1)", array4d.at(1), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "const Array4d out of range exception handled correctly\n\n";
        }

        try
        {
            const dsa::Array<int, 1> array4e{ 1 };
            tests::compare("const Array4e at(0)", array4e.at(0), 1);
            tests::compare("const Array4e at(2)", array4e.at(2), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "const Array4e out of range exception handled correctly\n\n";
        }

        try
        {
            const dsa::Array<int, 2> array4f{ 1, 2 };
            tests::compare("const Array4f at(0)", array4f.at(0), 1);
            tests::compare("const Array4f at(1)", array4f.at(1), 2);
            tests::compare("const Array4f at(2)", array4f.at(2), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "const Array4f out of range exception handled correctly\n\n";
        }

        try
        {
            const dsa::Array<int, 2> array4g{ 1, 2 };
            tests::compare("const Array4g at(0)", array4g.at(0), 1);
            tests::compare("const Array4g at(1)", array4g.at(1), 2);
            tests::compare("const Array4g at(10)", array4g.at(10), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "const Array4g out of range exception handled correctly\n\n";
        }

        try
        {
            const dsa::Array<int, 5> array4h{ 1, 2 };
            tests::compare("const Array4h at(0)", array4h.at(0), 1);
            tests::compare("const Array4h at(1)", array4h.at(1), 2);
            tests::compare("const Array4h at(2)", array4h.at(2), 0);
            tests::compare("const Array4h at(10)", array4h.at(10), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "const Array4h out of range exception handled correctly\n\n";
        }

        try
        {
            const dsa::Array<int, 5> array4i{};
            tests::compare("const Array4i at(0)", array4i.at(0), 0);
            tests::compare("const Array4i at(1)", array4i.at(1), 0);
            tests::compare("const Array4i at(2)", array4i.at(2), 0);
            tests::compare("const Array4i at(3)", array4i.at(3), 0);
            tests::compare("const Array4i at(4)", array4i.at(4), 0);
            tests::compare("const Array4i at(10)", array4i.at(10), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "const Array4i out of range exception handled correctly\n\n";
        }

        // Test iterators traversal
        dsa::Array<int, 5> array5 = { 0, 10, 20, 30, 40 };
        const std::vector<int> vector5(array5.begin(), array5.end());
        tests::compare("Array5 begin()", *array5.begin(), 0);
        auto* iter5 = array5.begin();
        std::advance(iter5, 1);
        tests::compare("Array5 begin()++", *iter5, 10);
        iter5 = array5.end();
        std::advance(iter5, -1);
        tests::compare("Array5 end()--", *iter5, 40);
        tests::compare("Array5 end()-- == back()", *iter5, array5.back());
        tests::compare("Array5 iter", array5, vector5);

        // Test const iterator traversal
        const auto& array6 = array5;
        const std::vector<int> vector6(array6.cbegin(), array6.cend());
        tests::compare("Array6 cbegin()", *array6.cbegin(), 0);
        const auto* citer6 = array6.cbegin();
        std::advance(citer6, 1);
        tests::compare("Array6 cbegin()++", *citer6, 10);
        citer6 = array6.cend();
        std::advance(citer6, -1);
        tests::compare("Array6 cend()--", *citer6, 40);
        tests::compare("Array6 cend() == back()", *citer6, array6.back());
        tests::compare("Array6 const iter", array6, vector6);

        // Test reverse iterator traversal
        dsa::Array<int, 5> array7{ 0, 1, 2, 3, 4 };
        auto iter7 = array7.rend();
        std::advance(iter7, -1);
        tests::compare("Array7 rend()--", *iter7, 0);
        iter7 = array7.rbegin();
        std::advance(iter7, 1);
        tests::compare("Array7 rbegin()++", *iter7, 3);
        const std::vector<int> vector7(array7.rbegin(), array7.rend());
        const dsa::Array<int, 5> reversed7{ 4, 3, 2, 1, 0 };
        tests::compare("Array7 reverse iter", reversed7, vector7);

        // Test capacity
        const dsa::Array<int, 4> array8{ 1, 2, 3, 4 };
        tests::compare("Array8 size()", array8.size(), static_cast<std::size_t>(4));
        tests::compare("Array8 max_size()", array8.max_size(), static_cast<std::size_t>(4));
        tests::compare("Array8 empty()", array8.empty(), false);

        const dsa::Array<int, 0> array9;
        tests::compare("Array9 size()", array9.size(), static_cast<std::size_t>(0));
        tests::compare("Array9 max_size()", array9.max_size(), static_cast<std::size_t>(0));
        tests::compare("Array9 empty()", array9.empty(), true);

        // Test operations: fill, swap
        dsa::Array<int, 4> array10{ 1, 2, 3, 4 };
        array10.fill(5);
        tests::compare("Array10 fill(5)", array10, { 5, 5, 5, 5 });

        std::cout << "Swapping arrays\n";
        dsa::Array<int, 4> array11a{ 1, 2, 3, 4 };
        dsa::Array<int, 4> array12a{ 9, 8, 7, 6 };
        array11a.swap(array12a);
        tests::compare("Array11a", array11a, { 9, 8, 7, 6 });
        tests::compare("Array12a", array12a, { 1, 2, 3, 4 });

        dsa::Array<int, 4> array11b{ 1, 2, 3, 4 };
        dsa::Array<int, 4> array12b{ 9, 8, 7, 6 };
        dsa::swap(array11b, array12b);
        tests::compare("Array11b", array11b, { 9, 8, 7, 6 });
        tests::compare("Array12b", array12b, { 1, 2, 3, 4 });

        std::cout << "Swapping self\n";
        dsa::Array<int, 4> array13a{ 1, 2, 3, 4 };
        array13a.swap(array13a);
        tests::compare("Array13a", array13a, { 1, 2, 3, 4 });

        dsa::Array<int, 4> array13b{ 1, 2, 3, 4 };
        dsa::swap(array13b, array13b);
        tests::compare("Array13b", array13b, { 1, 2, 3, 4 });

        dsa::Array<int, 4> array13{ 1, 2, 3, 4 };
        array13.swap(array13);
        tests::compare("Array13", array13, { 1, 2, 3, 4 });

        // Test empty array
        dsa::Array<int, 0> array14;
        tests::compare("Array14 begin() == cbegin()", array14.begin() == array14.cbegin(), true);
        tests::compare("Array14 begin() == end()", array14.begin() == array14.end(), true);
        tests::compare("Array14 end() == cend()", array14.end() == array14.cend(), true);
        tests::compare("Array14 rbegin() == crbegin()", array14.rbegin() == array14.crbegin(), true);
        tests::compare("Array14 rbegin() == rend()", array14.rbegin() == array14.rend(), true);
        tests::compare("Array14 rend() == crend()", array14.rend() == array14.crend(), true);
        tests::compare("Array14 size()", array14.size(), static_cast<std::size_t>(0));
        tests::compare("Array14 max_size()", array14.max_size(), static_cast<std::size_t>(0));
        tests::compare("Array14 empty()", array14.empty(), true);

        const dsa::Array<int, 0> array14b;
        tests::compare("Array14 begin() == cbegin()", array14b.begin() == array14b.cbegin(), true);
        tests::compare("Array14 begin() == end()", array14b.begin() == array14b.end(), true);
        tests::compare("Array14 end() == cend()", array14b.end() == array14b.cend(), true);
        tests::compare("Array14 rbegin() == crbegin()", array14b.rbegin() == array14b.crbegin(), true);
        tests::compare("Array14 rbegin() == rend()", array14b.rbegin() == array14b.rend(), true);
        tests::compare("Array14 rend() == crend()", array14b.rend() == array14b.crend(), true);
        tests::compare("Array14 size()", array14b.size(), static_cast<std::size_t>(0));
        tests::compare("Array14 max_size()", array14b.max_size(), static_cast<std::size_t>(0));
        tests::compare("Array14 empty()", array14b.empty(), true);

        // Test constexpr-compatibility

        // default ctor
        constexpr dsa::Array<int, 3> array15{};
        const std::initializer_list<int> expected15{ 0, 0, 0 };
        tests::compare("Array15", array15, expected15);

        // aggregate initialization
        constexpr dsa::Array<int, 3> array16{ 10, 20, 30 };
        const std::initializer_list<int> expected16{ 10, 20, 30 };
        tests::compare("Array16", array16, expected16);

        // element access
        constexpr dsa::Array<int, 3> array17{ 10, 20, 30 };
        static_assert(array17[0] == 10);
        static_assert(array17[1] == 20);
        static_assert(array17[2] == 30);

        // test capacity
        constexpr dsa::Array<int, 3> array18{ 10, 20, 30 };
        static_assert(array18.size() == 3);
        static_assert(array18.front() == 10);
        static_assert(array18.back() == 30);
        tests::compare("Array18 size()", array18.size(), static_cast<std::size_t>(3));
        tests::compare("Array18 front()", array18.front(), 10);
        tests::compare("Array18 back()", array18.back(), 30);

        // test copy
        constexpr dsa::Array<int, 3> array19{ 10, 20, 30 };
        constexpr dsa::Array<int, 3> expected19 = array19;
        tests::compare("Array19", array19, expected19);

        // modyfing elements
        constexpr dsa::Array<int, 3> array20 = []
            {
                dsa::Array<int, 3> tmp = { 1, 2, 3 };
                tmp[0] = 100;
                return tmp;
            }();
        static_assert(array20[0] == 100);

        // Test to_array
        // Intentional use of C-style array
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
        const int temp21[] = { 1, 2, 3, 4 };
        const dsa::Array<int, 4> array21 = dsa::to_array(temp21);
        const std::initializer_list<int> expected21{ 1, 2, 3, 4 };
        tests::compare("Array21", array21, expected21);

        // Intentional use of C-style array
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
        const std::string temp22[] = { "A", "B", "C" };
        auto array22 = dsa::to_array(temp22);
        const std::initializer_list<std::string> expected22{ "A", "B", "C" };
        tests::compare("Array22", array22, expected22);

        auto array23 = dsa::to_array<std::string>({ std::string{"A"}, std::string{"B"}, std::string{"C"} });
        const std::initializer_list<std::string> expected23{ "A", "B", "C" };
        tests::compare("Array23", array23, expected23);

        // Intentional use of C-style arrays
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
        auto array24 = dsa::to_array<std::string>({ std::string{"A"}, std::string{"B"}, std::string{"C"} });
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
        std::string array25[] = { "X", "Y", "Z" };
        array24 = dsa::to_array(std::move(array25));
        const std::initializer_list<std::string> expected24{ "X", "Y", "Z" };
        const std::initializer_list<std::string> expected25{ "", "", "" };
        tests::compare("Array24", array24, expected24);
        tests::compare("Array25", dsa::to_array(array25), expected25);


        std::cout << "Compare operations results with std container\n\n";

        // Test aggregate initialization
        const std::array<int, 3> std_array1{ 0, 1, 2 };
        tests::compare("Array1 vs std", array1, std_array1);

        const std::array<int, 3> std_array2 = { 0, 10, 20 };
        tests::compare("Array2 vs std", array2, std_array2);

        std::array<int, 3> std_array2b = { 0, 10, 20 };
        std_array2b = std_array1;
        tests::compare("Array2b = Array1", array2b, std_array2b);

        // Test element access
        std::array<int, 3> std_array3{ 10, 20, 30 };
        tests::compare("Array3 front() vs std", array3.front(), std_array3.front());
        tests::compare("Array3[0] vs std", array3[0], std_array3[0]);
        tests::compare("Array3[1] vs std", array3[1], std_array3[1]);
        tests::compare("Array3 vs std at(1) ", array3.at(1), std_array3.at(1));
        tests::compare("Array3 vs std back()", array3.back(), std_array3.back());
        tests::compare("Array3() vs std", array3, std_array3);

        // Test throwing 'out of range' exception
        try
        {
            std::array<int, 5> std_array4{};
            tests::compare("std_array4 at(10)", std_array4.at(10), 0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "std_array4 out of range exception handled correctly\n\n";
        }

        // Test iterators traversal
        std::array<int, 5> std_array5 = { 0, 10, 20, 30, 40 };
        tests::compare("Array5 vs std begin()", *array5.begin(), *std_array5.begin());
        iter5 = array5.begin();
        // Prevent Ubuntu Clang / GCC recommending variable as auto*
        // Change cause compilation failure on Windows due to incompatible initializer type
        // NOLINTNEXTLINE(readability-qualified-auto)
        auto std_iter5 = std_array5.begin();
        std::advance(iter5, 1);
        std::advance(std_iter5, 1);
        tests::compare("Array5 vs std begin()++", *iter5, *std_iter5);
        iter5 = array5.end();
        std_iter5 = std_array5.end();
        std::advance(iter5, -1);
        std::advance(std_iter5, -1);
        tests::compare("Array5 vs std end()--", *iter5, *std_iter5);
        tests::compare("Array5 vs std end()-- == back()", *iter5 == array5.back(), *std_iter5 == std_array5.back());
        tests::compare("Array5 vs std iter", array5, std_array5);

        // Test const iterator traversal
        const auto& std_array6 = std_array5;
        tests::compare("Array6 vs std cbegin()", *array6.cbegin(), *std_array6.cbegin());
        citer6 = array6.cbegin();
        // Prevent Ubuntu Clang / GCC recommending variable as const auto*
        // Change cause compilation failure on Windows due to incompatible initializer type
        // NOLINTNEXTLINE(readability-qualified-auto)
        auto std_citer6 = std_array6.cbegin();
        std::advance(citer6, 1);
        std::advance(std_citer6, 1);
        tests::compare("Array6 vs std cbegin()++", *citer6, *std_citer6);
        citer6 = array6.cend();
        std_citer6 = std_array6.cend();
        std::advance(citer6, -1);
        std::advance(std_citer6, -1);
        tests::compare("Array6 vs std cend()--", *citer6, *std_citer6);
        tests::compare("Array6 vs std cend() == back()", *citer6 == array6.back(), *std_citer6 == array6.back());
        tests::compare("Array6 vs std const iter", array6, vector6);

        // Test reverse iterator traversal
        std::array<int, 5> std_array7{ 0, 1, 2, 3, 4 };
        iter7 = array7.rend();
        auto std_iter7 = std_array7.rend();
        std::advance(iter7, -1);
        std::advance(std_iter7, -1);
        tests::compare("Array7 vs std rend()--", *iter7, *std_iter7);
        iter7 = array7.rbegin();
        std_iter7 = std_array7.rbegin();
        std::advance(iter7, 1);
        std::advance(std_iter7, 1);
        tests::compare("Array7 vs std rbegin()++", *iter7, *std_iter7);

        // Test capacity
        const std::array<int, 4> std_array8{ 1, 2, 3, 4 };
        tests::compare("Array8 vs std size()", array8.size(), std_array8.size());
        tests::compare("Array8 vs std max_size()", array8.max_size(), std_array8.max_size());
        tests::compare("Array8 vs std empty()", array8.empty(), std_array8.empty());

        const std::array<int, 0> std_array9{};
        tests::compare("Array9 vs std size()", array9.size(), std_array9.size());
        tests::compare("Array9 vs std max_size()", array9.max_size(), std_array9.max_size());
        tests::compare("Array9 vs std empty()", array9.empty(), std_array9.empty());

        // Test operations: fill, swap
        std::array<int, 4> std_array10{ 1, 2, 3, 4 };
        std_array10.fill(5);
        tests::compare("Array10 vs std fill(5)", array10, std_array10);

        std::cout << "Swapping arrays\n";
        std::array<int, 4> std_array11a{ 1, 2, 3, 4 };
        std::array<int, 4> std_array12a{ 9, 8, 7, 6 };
        std_array11a.swap(std_array12a);
        tests::compare("Array11a vs std", array11a, std_array11a);
        tests::compare("Array12a vs std", array12a, std_array12a);

        std::array<int, 4> std_array11b{ 1, 2, 3, 4 };
        std::array<int, 4> std_array12b{ 9, 8, 7, 6 };
        std::swap(std_array11b, std_array12b);
        tests::compare("Array11b vs std", array11b, std_array11b);
        tests::compare("Array12b vs std", array12b, std_array12b);

        std::cout << "Swapping self\n";
        std::array<int, 4> std_array13a{ 1, 2, 3, 4 };
        std_array13a.swap(std_array13a);
        tests::compare("Array13a vs std", array13a, std_array13a);

        std::array<int, 4> std_array13b{ 1, 2, 3, 4 };
        std_array13b.swap(std_array13b);
        tests::compare("Array13b vs std", array13b, std_array13b);

        // Test empty array
        std::array<int, 0> std_array14{};
        tests::compare("Array14 vs std begin() == cbegin()",
            array14.begin() == array14.cbegin(), std_array14.begin() == std_array14.cbegin());
        tests::compare("Array14 vs std begin() == end()",
            array14.begin() == array14.end(), std_array14.begin() == std_array14.end());
        tests::compare("Array14 vs std end() == cend()",
            array14.end() == array14.cend(), std_array14.end() == std_array14.cend());
        tests::compare("Array14 vs std rbegin() == crbegin()",
            array14.rbegin() == array14.crbegin(), std_array14.rbegin() == std_array14.crbegin());
        tests::compare("Array14 vs std rbegin() == rend()",
            array14.rbegin() == array14.rend(), std_array14.rbegin() == std_array14.rend());
        tests::compare("Array14 vs std rend() == crend()",
            array14.rend() == array14.crend(), std_array14.rend() == std_array14.crend());
        tests::compare("Array14 vs std size()", array14.size(), std_array14.size());
        tests::compare("Array14 vs std max_size()", array14.max_size(), std_array14.max_size());
        tests::compare("Array14 vs std empty()", array14.empty(), std_array14.empty());

        // Test constexpr-compatibility

        // default ctor
        constexpr std::array<int, 3> std_array15{};
        tests::compare("Array15 vs std", array15, std_array15);

        // aggregate initialization
        constexpr std::array<int, 3> std_array16{ 10, 20, 30 };
        tests::compare("Array16 vs std", array16, std_array16);

        // element access
        constexpr std::array<int, 3> std_array17{ 10, 20, 30 };
        static_assert(array17[0] == std_array17[0]);
        static_assert(array17[1] == std_array17[1]);
        static_assert(array17[2] == std_array17[2]);

        // test capacity
        constexpr std::array<int, 3> std_array18{ 10, 20, 30 };
        static_assert(array18.size() == std_array18.size());
        static_assert(array18.front() == std_array18.front());
        static_assert(array18.back() == std_array18.back());
        tests::compare("Array18 vs std size()", array18.size(), std_array18.size());
        tests::compare("Array18 vs std front()", array18.front(), std_array18.front());
        tests::compare("Array18 vs std back()", array18.back(), std_array18.back());

        // test copy
        constexpr std::array<int, 3> std_array19{ 10, 20, 30 };
        constexpr std::array<int, 3> std_expected19 = std_array19;
        tests::compare("Array19 vs std", expected19, std_expected19);

        // modyfing elements
        constexpr std::array<int, 3> std_array20 = []
            {
                std::array<int, 3> std_tmp = { 1, 2, 3 };
                std_tmp[0] = 100;
                return std_tmp;
            }();
        static_assert(std_array20[0] == 100);

        // Test to_array
        const std::array<int, 4> std_array21 = std::to_array(temp21);
        tests::compare("Array21 vs std", array21, std_array21);

        auto std_array22 = std::to_array(temp22);
        tests::compare("Array22 vs std", array22, std_array22);

        auto std_array23 = std::to_array<std::string>({ std::string{"A"}, std::string{"B"}, std::string{"C"} });
        tests::compare("Array23 vs std", array23, std_array23);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
