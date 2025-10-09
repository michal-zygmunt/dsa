/**
 * @file ListGrow.cpp
 * @brief This file tests functions merging List objects
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
        std::cout << "Start ListMerge test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };
        const std::initializer_list<int> il_3{ 1, 1, 3, 5, 7 };
        const std::initializer_list<int> il_4{ 1, 2, 4, 6, 9 };

        dsa::List<int> list1 = dsa::List<int>(il_1);
        dsa::List<int> list2 = dsa::List<int>(il_2);
        list1.merge(list2);
        const std::initializer_list<int> expected1 = { 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
        tests::compare("List1", list1, expected1);
        const std::initializer_list<int> expected2 = {};
        tests::compare("List2", list2, expected2);

        dsa::List<int> list3 = dsa::List<int>(il_1);
        dsa::List<int> list4;
        list4.merge(list3);
        const std::initializer_list<int> expected3 = { };
        tests::compare("List3", list3, expected3);
        const std::initializer_list<int> expected4 = il_1;
        tests::compare("List4", list4, expected4);

        dsa::List<int> list5 = dsa::List<int>(il_3);
        dsa::List<int> list6 = dsa::List<int>(il_4);
        list5.merge(list6);
        const std::initializer_list<int> expected5 = { 1, 1, 1, 2, 3, 4, 5, 6, 7, 9 };
        tests::compare("List5", list5, expected5);
        const std::initializer_list<int> expected6 = {};
        tests::compare("List6", list6, expected6);

        dsa::List<int> list7 = dsa::List<int>(il_4);
        dsa::List<int> list8 = dsa::List<int>(il_3);
        list7.merge(list8);
        const std::initializer_list<int> expected7 = { 1, 1, 1, 2, 3, 4, 5, 6, 7, 9 };
        tests::compare("List7", list7, expected7);
        const std::initializer_list<int> expected8 = {};
        tests::compare("List8", list8, expected8);

        dsa::List<int> list9 = dsa::List<int>(il_2);
        dsa::List<int> list10 = dsa::List<int>(il_3);
        list9.merge(list10);
        const std::initializer_list<int> expected9 = { 1, 1, 3, 5, 7, 10, 20, 30, 40, 50 };
        tests::compare("List9", list9, expected9);
        const std::initializer_list<int> expected10 = {};
        tests::compare("List10", list10, expected10);

        dsa::List<int> list11 = dsa::List<int>(il_3);
        dsa::List<int> list12 = dsa::List<int>(il_2);
        list11.merge(list12);
        const std::initializer_list<int> expected11 = { 1, 1, 3, 5, 7, 10, 20, 30, 40, 50 };
        tests::compare("List11", list11, expected11);
        const std::initializer_list<int> expected12 = {};
        tests::compare("List12", list12, expected12);

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
