/**
 * @file ListGrow.cpp
 * @brief This file tests functions swapping List objects
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
        std::cout << "Start ListSwap test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };

        dsa::List<int> list1 = dsa::List<int>(il_1);
        dsa::List<int> list2 = dsa::List<int>(il_2);
        list1.swap(list2);
        const std::initializer_list<int> expected1 = { 10, 20, 30, 40, 50 };
        tests::compare("List1", list1, expected1);
        const std::initializer_list<int> expected2 = { 1, 2, 3, 4, 5 };
        tests::compare("List2", list2, expected2);

        dsa::List<int> list3 = dsa::List<int>(il_1);
        dsa::List<int> list4;
        list3.swap(list4);
        const std::initializer_list<int> expected3 = { };
        tests::compare("List3", list3, expected3);
        const std::initializer_list<int> expected4 = { 1, 2, 3, 4, 5 };
        tests::compare("List4", list4, expected4);


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list1{ il_1 };
        std::list<int> std_list2{ il_2 };
        std_list1.swap(std_list2);
        tests::compare("List1 vs std", list1, std_list1);
        tests::compare("List2 vs std", list2, std_list2);

        std::list<int> std_list3{ il_1 };
        std::list<int> std_list4{};
        std_list3.swap(std_list4);
        tests::compare("List3 vs std", list3, std_list3);
        tests::compare("List4 vs std", list4, std_list4);
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
