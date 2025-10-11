/**
 * @file ListReverse.cpp
 * @brief This file tests reversing order of List Nodes
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
#include <list>
#include <new>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start ListReverse test:\n";

        dsa::List<int> list1 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
        list1.reverse();
        const std::initializer_list<int> expected1 = { 50, 40, 30, 20, 10, 0 };
        tests::compare("List1", list1, expected1);

        dsa::List<int> list2 = dsa::List<int>({ 0 });
        list2.reverse();
        const std::initializer_list<int> expected2{ 0 };
        tests::compare("List2", list2, expected2);

        dsa::List<int> list3;
        list3.reverse();
        const std::initializer_list<int> expected3{};
        tests::compare("List3", list3, expected3);


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list1{ 0, 10, 20, 30, 40, 50 };
        std_list1.reverse();
        tests::compare("List1 vs std", list1, std_list1);

        std::list<int> std_list2{ 0 };
        std_list2.reverse();
        tests::compare("List2 vs std", list2, std_list2);

        std::list<int> std_list3;
        std_list3.reverse();
        tests::compare("List3 vs std", list3, std_list3);
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