/**
 * @file list_resize_test.cpp
 * @brief This file tests functions resizing List objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/list.h"

#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <list>
#include <new>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start list_resize_test:\n";

        dsa::List<int> list1 = dsa::List<int>({ 1, 2, 3, 4, 5 });
        list1.resize(3);
        const std::initializer_list<int> expected1 = { 1, 2, 3 };
        tests::compare("List1", list1, expected1);

        dsa::List<int> list2 = dsa::List<int>({ 1, 2, 3, 4, 5 });
        list2.resize(5);
        const std::initializer_list<int> expected2 = { 1, 2, 3, 4, 5 };
        tests::compare("List2", list2, expected2);

        dsa::List<int> list3 = dsa::List<int>({ 1, 2, 3, 4, 5 });
        list3.resize(8);
        const std::initializer_list<int> expected3 = { 1, 2, 3, 4, 5, 0, 0, 0 };
        tests::compare("List3", list3, expected3);

        dsa::List<int> list4;
        list4.resize(5);
        const std::initializer_list<int> expected4 = { 0, 0, 0, 0, 0 };
        tests::compare("List4", list4, expected4);

        dsa::List<int> list5 = dsa::List<int>({ 1, 2, 3, 4, 5 });
        list5.resize(3, 10);
        const std::initializer_list<int> expected5 = { 1, 2, 3 };
        tests::compare("List5", list5, expected5);

        dsa::List<int> list6 = dsa::List<int>({ 1, 2, 3, 4, 5 });
        list6.resize(5, 10);
        const std::initializer_list<int> expected6 = { 1, 2, 3, 4, 5 };
        tests::compare("List6", list6, expected6);

        dsa::List<int> list7 = dsa::List<int>({ 1, 2, 3, 4, 5 });
        list7.resize(8, 10);
        const std::initializer_list<int> expected7 = { 1, 2, 3, 4, 5, 10, 10, 10 };
        tests::compare("List7", list7, expected7);

        dsa::List<int> list8;
        list8.resize(5, 10);
        const std::initializer_list<int> expected8 = { 10, 10, 10, 10, 10 };
        tests::compare("List8", list8, expected8);

        const dsa::List<int> list9;
        tests::compare("max_size()", list9.max_size(), UINTMAX_MAX);

        dsa::List<int> list10 = dsa::List<int>({ 1, 2, 3, 4, 5 });
        list10.resize(0);
        const std::initializer_list<int> expected10 = { };
        tests::compare("List10", list10, expected10);

        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list1{ 1, 2, 3, 4, 5 };
        std_list1.resize(3);
        tests::compare("List1 vs std", list1, std_list1);

        std::list<int> std_list2{ 1, 2, 3, 4, 5 };
        std_list2.resize(5);
        tests::compare("List2 vs std", list2, std_list2);

        std::list<int> std_list3{ 1, 2, 3, 4, 5 };
        std_list3.resize(8);
        tests::compare("List3 vs std", list3, std_list3);

        std::list<int> std_list4;
        std_list4.resize(5);
        tests::compare("List4 vs std", list4, std_list4);

        std::list<int> std_list5{ 1, 2, 3, 4, 5 };
        std_list5.resize(3, 10);
        tests::compare("List5 vs std", list5, std_list5);

        std::list<int> std_list6{ 1, 2, 3, 4, 5 };
        std_list6.resize(5, 10);
        tests::compare("List6 vs std", list6, std_list6);

        std::list<int> std_list7{ 1, 2, 3, 4, 5 };
        std_list7.resize(8, 10);
        tests::compare("List7 vs std", list7, std_list7);

        std::list<int> std_list8;
        std_list8.resize(5, 10);
        tests::compare("List8 vs std", list8, std_list8);

        std::list<int> std_list10{ 1, 2, 3, 4, 5 };
        std_list10.resize(0);
        tests::compare("List10 vs std", list10, std_list10);
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

    tests::print_stats();
    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
