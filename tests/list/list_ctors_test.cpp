/**
 * @file list_ctors_test.cpp
 * @brief This file tests List constructors
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/list.h"

#include <exception>
#include <initializer_list>
#include <iostream>
#include <list>
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start list_ctors_test:\n";

        const std::initializer_list<int> expected{ 0, 10, 20 };

        std::cout << "Default ctor\n";
        dsa::List<int> list1;
        list1.push_front(20);
        list1.push_front(10);
        list1.push_front(0);
        tests::compare("List1", list1, expected);

        std::cout << "Value ctor\n";
        dsa::List<int> list2(1, 20);
        list2.push_front(10);
        list2.insert(list2.cbegin(), 0);
        tests::compare("List2", list2, expected);

        std::cout << "Initializer list ctor\n";
        const dsa::List<int> list3(expected);
        tests::compare("List3", list3, expected);

        std::cout << "Copy ctor\n";
        const dsa::List<int> list4{ list1 };
        tests::compare("List4", list4, expected);

        std::cout << "Copy assignment ctor\n";
        dsa::List<int> list5;
        list5.push_front(5);
        list5.push_front(4);
        list5.push_front(3);
        list5.push_front(2);
        list5.push_front(1);
        list5 = list1;
        tests::compare("List5", list5, expected);

        std::cout << "Move ctor\n";
        dsa::List<int> temp_1(list1);
        const dsa::List<int> list6 = std::move(temp_1);
        tests::compare("List6", list6, expected);

        std::cout << "Move assignment ctor\n";
        dsa::List<int> temp_2(list1);
        dsa::List<int> list7(1, 0);
        list7 = std::move(temp_2);
        tests::compare("List7", list7, expected);


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list1;
        std_list1.push_front(20);
        std_list1.push_front(10);
        std_list1.push_front(0);
        tests::compare("List1 vs std", list1, std_list1);

        std::list<int> std_list2(1, 20);
        std_list2.push_front(10);
        std_list2.insert(std_list2.cbegin(), 0);
        tests::compare("List2 vs std", list2, std_list2);

        const std::list<int> std_list3(expected);
        tests::compare("List3 vs std", list3, std_list3);

        const std::list<int> std_list4{ std_list1 };
        tests::compare("List4 vs std", list4, std_list4);

        std::list<int> std_list5;
        std_list5.push_front(5);
        std_list5.push_front(4);
        std_list5.push_front(3);
        std_list5.push_front(2);
        std_list5.push_front(1);
        std_list5 = std_list1;
        tests::compare("List5 vs std", list5, expected);

        std::list<int> std_temp_1(std_list1);
        const std::list<int> std_list6 = std::move(std_temp_1);
        tests::compare("List6 vs std", list6, expected);

        std::list<int> std_temp_2(std_list1);
        std::list<int> std_list7(1, 0);
        std_list7 = std::move(std_temp_2);
        tests::compare("List7 vs std", list7, expected);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}