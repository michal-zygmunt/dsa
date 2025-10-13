/**
 * @file ForwardListGrow.cpp
 * @brief This file tests functions merging ForwardList objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/ForwardList.h"

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
        std::cout << "Start ForwardListMerge test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };
        const std::initializer_list<int> il_3{ 1, 1, 3, 5, 7 };
        const std::initializer_list<int> il_4{ 1, 2, 4, 6, 9 };

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list2 = dsa::ForwardList<int>(il_2);
        list1.merge(list2);
        const std::initializer_list<int> expected1 = { 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
        tests::compare("ForwardList1", list1, expected1);
        const std::initializer_list<int> expected2 = {};
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list4;
        list4.merge(list3);
        const std::initializer_list<int> expected3 = { };
        tests::compare("ForwardList3", list3, expected3);
        const std::initializer_list<int> expected4 = il_1;
        tests::compare("ForwardList4", list4, expected4);

        dsa::ForwardList<int> list5 = dsa::ForwardList<int>(il_3);
        dsa::ForwardList<int> list6 = dsa::ForwardList<int>(il_4);
        list5.merge(list6);
        const std::initializer_list<int> expected5 = { 1, 1, 1, 2, 3, 4, 5, 6, 7, 9 };
        tests::compare("ForwardList5", list5, expected5);
        const std::initializer_list<int> expected6 = {};
        tests::compare("ForwardList6", list6, expected6);

        dsa::ForwardList<int> list7 = dsa::ForwardList<int>(il_4);
        dsa::ForwardList<int> list8 = dsa::ForwardList<int>(il_3);
        list7.merge(list8);
        const std::initializer_list<int> expected7 = { 1, 1, 1, 2, 3, 4, 5, 6, 7, 9 };
        tests::compare("ForwardList7", list7, expected7);
        const std::initializer_list<int> expected8 = {};
        tests::compare("ForwardList8", list8, expected8);

        dsa::ForwardList<int> list9 = dsa::ForwardList<int>(il_2);
        dsa::ForwardList<int> list10 = dsa::ForwardList<int>(il_3);
        list9.merge(list10);
        const std::initializer_list<int> expected9 = { 1, 1, 3, 5, 7, 10, 20, 30, 40, 50 };
        tests::compare("ForwardList9", list9, expected9);
        const std::initializer_list<int> expected10 = {};
        tests::compare("ForwardList10", list10, expected10);

        dsa::ForwardList<int> list11 = dsa::ForwardList<int>(il_3);
        dsa::ForwardList<int> list12 = dsa::ForwardList<int>(il_2);
        list11.merge(list12);
        const std::initializer_list<int> expected11 = { 1, 1, 3, 5, 7, 10, 20, 30, 40, 50 };
        tests::compare("ForwardList11", list11, expected11);
        const std::initializer_list<int> expected12 = {};
        tests::compare("ForwardList12", list12, expected12);


        std::cout << "Compare operations results with std container\n\n";

        std::forward_list<int> std_list1{ il_1 };
        std::forward_list<int> std_list2{ il_2 };
        std_list1.merge(std_list2);
        tests::compare("ForwardList1 vs std", list1, std_list1);
        tests::compare("ForwardList2 vs std", list2, std_list2);

        std::forward_list<int> std_list3{ il_1 };
        std::forward_list<int> std_list4;
        std_list4.merge(std_list3);
        tests::compare("ForwardList3 vs std", list3, std_list3);
        tests::compare("ForwardList4 vs std", list4, std_list4);

        std::forward_list<int> std_list5{ il_3 };
        std::forward_list<int> std_list6{ il_4 };
        std_list5.merge(std_list6);
        tests::compare("ForwardList5 vs std", list5, std_list5);
        tests::compare("ForwardList6 vs std", list6, std_list6);

        std::forward_list<int> std_list7{ il_4 };
        std::forward_list<int> std_list8{ il_3 };
        std_list7.merge(std_list8);
        tests::compare("ForwardList7 vs std", list7, std_list7);
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

    tests::print_stats();
    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
