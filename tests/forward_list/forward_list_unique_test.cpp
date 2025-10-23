/**
 * @file forward_list_unique_test.cpp
 * @brief This file tests functions checking values of ForwardList objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/forward_list.h"

#include <exception>
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
        std::cout << "Start forward_list_unique_test:\n";

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
        list1.unique();
        const std::initializer_list<int> expected1 = { 1, 2, 3, 4, 5 };
        tests::compare("ForwardList1", list1, expected1);

        dsa::ForwardList<int> list2 = dsa::ForwardList<int>({ 1, 4, 2, 3, 2, 4, 3, 5, 1 });
        list2.unique();
        const std::initializer_list<int> expected2 = { 1, 4, 2, 3, 2, 4, 3, 5, 1 };
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>({ 1, 1, 2, 4, 2, 1, 3, 1, 1 });
        list3.unique();
        const std::initializer_list<int> expected3 = { 1, 2, 4, 2, 1, 3, 1 };
        tests::compare("ForwardList3", list3, expected3);

        dsa::ForwardList<int> list4 = dsa::ForwardList<int>({ 1, 1, 1, 2, 2, 2, 1, 1, 1 });
        list4.unique();
        const std::initializer_list<int> expected4 = { 1, 2, 1 };
        tests::compare("ForwardList4", list4, expected4);

        dsa::ForwardList<int> list5 = dsa::ForwardList<int>({ 0, 0, 0, 0, 0, 0 });
        list5.unique();
        const std::initializer_list<int> expected5 = { 0 };
        tests::compare("ForwardList5", list5, expected5);

        dsa::ForwardList<int> list6 = dsa::ForwardList<int>();
        list6.unique();
        const std::initializer_list<int> expected6 = { };
        tests::compare("ForwardList6", list6, expected6);

        dsa::ForwardList<int> list7;
        list7.unique();
        const std::initializer_list<int> expected7 = {};
        tests::compare("ForwardList7", list7, expected7);


        std::cout << "Compare operations results with std container\n\n";

        std::forward_list<int> std_list1{ 1, 2, 3, 4, 5 };
        std_list1.unique();
        tests::compare("ForwardList1 vs std", list1, std_list1);

        std::forward_list<int> std_list2{ 1, 4, 2, 3, 2, 4, 3, 5, 1 };
        std_list2.unique();
        tests::compare("ForwardList2 vs std", list2, std_list2);

        std::forward_list<int> std_list3{ 1, 1, 2, 4, 2, 1, 3, 1, 1 };
        std_list3.unique();
        tests::compare("ForwardList3 vs std", list3, std_list3);

        std::forward_list<int> std_list4{ 1, 1, 1, 2, 2, 2, 1, 1, 1 };
        std_list4.unique();
        tests::compare("ForwardList4 vs std", list4, std_list4);

        std::forward_list<int> std_list5{ 0, 0, 0, 0, 0, 0 };
        std_list5.unique();
        tests::compare("ForwardList5 vs std", list5, std_list5);

        std::forward_list<int> std_list6 = std::forward_list<int>();
        std_list6.unique();
        tests::compare("ForwardList6 vs std", list6, std_list6);

        std::forward_list<int> std_list7;
        std_list7.unique();
        tests::compare("ForwardList7 vs std", list7, std_list7);


        tests::print_stats();
    }
    catch (const std::bad_alloc& exception)
    {
        tests::print_err_msg("Caught std::bad_alloc: ", &exception);
        return 1;
    }
    catch (const std::runtime_error& exception)
    {
        tests::print_err_msg("Caught std::runtime_error: ", &exception);
        return 2;
    }
    catch (const std::exception& exception)
    {
        tests::print_err_msg("Caught exception: ", &exception);
        return 3;
    }
    catch (...)
    {
        tests::print_err_msg("Unhandled unknown exception");
        return 4;
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
