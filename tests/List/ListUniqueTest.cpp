/**
 * @file ListGrow.cpp
 * @brief This file tests functions checking values of List objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/List.h"

#include <initializer_list>
#include <iostream>
#include <new>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start ListUnique test:\n";

        dsa::List<int> list1 = dsa::List<int>({ 1, 2, 3, 4, 5 });
        list1.unique();
        const std::initializer_list<int> expected1 = { 1, 2, 3, 4, 5 };
        tests::compare("list1", list1, expected1);

        dsa::List<int> list2 = dsa::List<int>({ 1, 4, 2, 3, 2, 4, 3, 5, 1 });
        list2.unique();
        const std::initializer_list<int> expected2 = { 1, 4, 2, 3, 2, 4, 3, 5, 1 };
        tests::compare("list2", list2, expected2);

        dsa::List<int> list3 = dsa::List<int>({ 1, 1, 2, 4, 2, 1, 3, 1, 1 });
        list3.unique();
        const std::initializer_list<int> expected3 = { 1, 2, 4, 2, 1, 3, 1 };
        tests::compare("list3", list3, expected3);

        dsa::List<int> list4 = dsa::List<int>({ 1, 1, 1, 2, 2, 2, 1, 1, 1 });
        list4.unique();
        const std::initializer_list<int> expected4 = { 1, 2, 1 };
        tests::compare("list4", list4, expected4);

        dsa::List<int> list5 = dsa::List<int>({ 0, 0, 0, 0, 0, 0 });
        list5.unique();
        const std::initializer_list<int> expected5 = { 0 };
        tests::compare("list5", list5, expected5);

        dsa::List<int> list6 = dsa::List<int>();
        list6.unique();
        const std::initializer_list<int> expected6 = { };
        tests::compare("list6", list6, expected6);

        dsa::List<int> list7;
        list7.unique();
        const std::initializer_list<int> expected7 = {};
        tests::compare("list7", list7, expected7);

    }
    catch (const std::bad_alloc& exception)
    {
        std::cerr << "Caught std::bad_alloc: " << exception.what() << '\n';
        return 1;
    }
    catch (const std::runtime_error& exception)
    {
        std::cerr << "Caught std::runtime_error: " << exception.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unhandled unknown exception\n";
        return 1;
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
