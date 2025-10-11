/**
 * @file ForwardListGrow.cpp
 * @brief This file tests functions resizing ForwardList objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/ForwardList.h"

#include <cstdint>
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
        std::cout << "Start ForwardListResize test:\n";

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
        list1.resize(3);
        const std::initializer_list<int> expected1 = { 1, 2, 3 };
        tests::compare("ForwardList1", list1, expected1);

        dsa::ForwardList<int> list2 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
        list2.resize(5);
        const std::initializer_list<int> expected2 = { 1, 2, 3, 4, 5 };
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
        list3.resize(8);
        const std::initializer_list<int> expected3 = { 1, 2, 3, 4, 5, 0, 0, 0 };
        tests::compare("ForwardList3", list3, expected3);

        dsa::ForwardList<int> list4;
        list4.resize(5);
        const std::initializer_list<int> expected4 = { 0, 0, 0, 0, 0 };
        tests::compare("ForwardList4", list4, expected4);

        dsa::ForwardList<int> list5 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
        list5.resize(3, 10);
        const std::initializer_list<int> expected5 = { 1, 2, 3 };
        tests::compare("ForwardList5", list5, expected5);

        dsa::ForwardList<int> list6 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
        list6.resize(5, 10);
        const std::initializer_list<int> expected6 = { 1, 2, 3, 4, 5 };
        tests::compare("ForwardList6", list6, expected6);

        dsa::ForwardList<int> list7 = dsa::ForwardList<int>({ 1, 2, 3, 4, 5 });
        list7.resize(8, 10);
        const std::initializer_list<int> expected7 = { 1, 2, 3, 4, 5, 10, 10, 10 };
        tests::compare("ForwardList7", list7, expected7);

        dsa::ForwardList<int> list8;
        list8.resize(5, 10);
        const std::initializer_list<int> expected8 = { 10, 10, 10, 10, 10 };
        tests::compare("ForwardList8", list8, expected8);

        const dsa::ForwardList<int> list9;
        tests::compare("max_size()", list9.max_size(), UINTMAX_MAX);


        std::cout << "Compare operations results with std container\n\n";

        std::forward_list<int> std_list1{ 1, 2, 3, 4, 5 };
        std_list1.resize(3);
        tests::compare("ForwardList1 vs std", list1, std_list1);

        std::forward_list<int> std_list2{ 1, 2, 3, 4, 5 };
        std_list2.resize(5);
        tests::compare("ForwardList2 vs std", list2, std_list2);

        std::forward_list<int> std_list3{ 1, 2, 3, 4, 5 };
        std_list3.resize(8);
        tests::compare("ForwardList3 vs std", list3, std_list3);

        std::forward_list<int> std_list4;
        std_list4.resize(5);
        tests::compare("ForwardList4 vs std", list4, std_list4);

        std::forward_list<int> std_list5{ 1, 2, 3, 4, 5 };
        std_list5.resize(3, 10);
        tests::compare("ForwardList5 vs std", list5, std_list5);

        std::forward_list<int> std_list6{ 1, 2, 3, 4, 5 };
        std_list6.resize(5, 10);
        tests::compare("ForwardList6 vs std", list6, std_list6);

        std::forward_list<int> std_list7{ 1, 2, 3, 4, 5 };
        std_list7.resize(8, 10);
        tests::compare("ForwardList7 vs std", list7, std_list7);

        std::forward_list<int> std_list8;
        std_list8.resize(5, 10);
        tests::compare("ForwardList8 vs std", list8, std_list8);
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
