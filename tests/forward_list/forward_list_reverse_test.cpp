/**
 * @file forward_list_reverse_test.cpp
 * @brief This file tests reversing order of ForwardList Nodes
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/forward_list.h"

#include <forward_list>
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
        std::cout << "Start forward_list_reverse_test:\n";

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
        list1.reverse();
        const std::initializer_list<int> expected1{ 50, 40, 30, 20, 10, 0 };
        tests::compare("ForwardList1", list1, expected1);

        dsa::ForwardList<int> list2 = dsa::ForwardList<int>({ 0 });
        list2.reverse();
        const std::initializer_list<int> expected2{ 0 };
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3;
        list3.reverse();
        const std::initializer_list<int> expected3{};
        tests::compare("ForwardList3", list3, expected3);


        std::cout << "Compare operations results with std container\n\n";

        std::forward_list<int> std_list1{ 0, 10, 20, 30, 40, 50 };
        std_list1.reverse();
        tests::compare("ForwardList1 vs std", list1, std_list1);

        std::forward_list<int> std_list2{ 0 };
        std_list2.reverse();
        tests::compare("ForwardList2 vs std", list2, std_list2);

        std::forward_list<int> std_list3;
        std_list3.reverse();
        tests::compare("ForwardList3 vs std", list3, std_list3);
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
