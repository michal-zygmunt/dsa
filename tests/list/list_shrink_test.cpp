/**
 * @file list_shrink_test.cpp
 * @brief This file tests functions decreasing List length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/list.h"

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <new>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start list_shrink_test:\n";

        dsa::List<int> list1 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
        list1.erase(list1.begin()[list1.size() - 1]);
        list1.pop_front();
        auto indexes = { 100, 5, 2, 0 };
        for (const auto& idx : indexes)
        {
            list1.erase(list1.begin()[static_cast<size_t>(idx)]);
        }
        const std::initializer_list<int> expected1 = { 20, 40 };
        tests::compare("List1", list1, expected1);

        dsa::List<int> list2 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
        list2.erase(list2.begin()[1], list2.begin()[3]);
        const std::initializer_list<int> expected2 = { 0, 30, 40, 50 };
        tests::compare("List2", list2, expected2);

        dsa::List<int> list3 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
        list3.erase(list3.begin()[1]);
        list3.erase(list3.begin()[1], list3.begin()[3]);
        const std::initializer_list<int> expected3 = { 0, 40, 50 };
        tests::compare("List3", list3, expected3);

        dsa::List<int> list4 = dsa::List<int>({ 0, 10, 20, 30, 40, 50 });
        list4.erase(list4.begin()[1]);
        list4.erase(list4.begin()[1], list4.begin()[4]);
        const std::initializer_list<int> expected4 = { 0, 50 };
        tests::compare("List4", list4, expected4);

        dsa::List<int> list5 = dsa::List<int>({ 0, 10, 0, 0, 40, 0 });
        list5.remove(0);
        const std::initializer_list<int> expected5 = { 10, 40 };
        tests::compare("List5", list5, expected5);

        dsa::List<int> list6 = dsa::List<int>({ 0, 0, 0, 0, 0, 0 });
        list6.remove(0);
        const std::initializer_list<int> expected6 = { };
        tests::compare("List6", list6, expected6);

        dsa::List<int> list7 = dsa::List<int>({ 0 });
        tests::compare(list7.empty(), false);
        list7.clear();
        tests::compare(list7.empty(), true);
        const std::initializer_list<int> expected7 = { };
        tests::compare("List7", list7, expected7);

        dsa::List<int> list8 = dsa::List<int>({ 10, 20, 30 });
        list8.pop_front();
        list8.pop_front();
        list8.pop_front();
        list8.pop_front();
        const std::initializer_list<int> expected8 = { };
        tests::compare("List8", list8, expected8);

        dsa::List<int> list9 = dsa::List<int>({ 10, 20, 30 });
        list9.pop_back();
        list9.pop_back();
        list9.pop_back();
        list9.pop_back();
        const std::initializer_list<int> expected9 = { };
        tests::compare("List9", list9, expected9);


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list2{ 0, 10, 20, 30, 40, 50 };
        auto iter_start_2 = std_list2.begin();
        auto iter_end_2 = std_list2.begin();
        std::advance(iter_start_2, 1);
        std::advance(iter_end_2, 3);
        std_list2.erase(iter_start_2, iter_end_2);
        tests::compare("List2 vs std", list2, std_list2);

        std::list<int> std_list3{ 0, 10, 20, 30, 40, 50 };
        auto iter_start_3 = std_list3.begin();
        auto iter_end_3 = std_list3.begin();
        std::advance(iter_start_3, 1);
        std_list3.erase(iter_start_3);
        iter_start_3 = std_list3.begin();
        std::advance(iter_start_3, 1);
        std::advance(iter_end_3, 3);
        std_list3.erase(iter_start_3, iter_end_3);
        tests::compare("List3 vs std", list3, std_list3);

        std::list<int> std_list4{ 0, 10, 20, 30, 40, 50 };
        auto iter_start_4 = std_list4.begin();
        auto iter_end_4 = std_list4.begin();
        std::advance(iter_start_4, 1);
        std_list4.erase(iter_start_4);
        iter_start_4 = std_list4.begin();
        iter_end_4 = std_list4.begin();
        std::advance(iter_start_4, 1);
        std::advance(iter_end_4, 4);
        std_list4.erase(iter_start_4, iter_end_4);
        tests::compare("List4 vs std", list4, std_list4);

        std::list<int> std_list5{ 0, 10, 0, 0, 40, 0 };
        std_list5.remove(0);
        tests::compare("List5 vs std", list5, std_list5);

        std::list<int> std_list6{ 0, 0, 0, 0, 0, 0 };
        std_list6.remove(0);
        tests::compare("List6 vs std", list6, std_list6);
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