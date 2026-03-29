/**
 * @file list_grow_test.cpp
 * @brief This file tests functions increasing List length
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
#include <iterator>
#include <list>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start list_grow_test:\n";

        dsa::List<int> list1 = dsa::List<int>(1, 40);
        auto iterator = list1.insert(list1.cbegin(), 30);
        list1.insert(iterator, { 10, 20 });
        list1.push_front(0);
        list1.push_front(-10);
        // Try inserting nodes at invalid indexes
        for (const auto& item : { -1, 0, 4, 2, 100 })
        {
            iterator = list1.begin();
            std::advance(iterator, item);
            list1.insert(iterator, item);
        }
        const std::initializer_list<int> expected1 = { 0, -10, 2, 0, 10, 4, 20, 30, 40 };
        tests::compare("List1", list1, expected1);

        dsa::List<int> list2 = dsa::List<int>(1, 50);
        list2.push_front(40);
        list2.push_front(30);
        list2.push_front(20);
        list2.push_front(10);
        list2.insert(list2.cbegin(), 5, 5);
        const std::initializer_list<int> expected2 = { 5, 5, 5, 5, 5, 10, 20, 30, 40, 50 };
        tests::compare("List2", list2, expected2);

        dsa::List<int> list3 = dsa::List<int>(1, 50);
        list3.push_front(40);
        list3.push_front(30);
        list3.push_front(20);
        iterator = list3.insert(list3.cbegin(), 10);
        list3.insert(iterator, { 1, 2, 3 });
        list3.insert(list3.cbegin()[list3.size() - 1], 60);
        const std::initializer_list<int> expected3 = { 1, 2, 3, 10, 20, 30, 40, 60, 50 };
        tests::compare("List3", list3, expected3);

        dsa::List<int> list4;
        list4.push_back(20);
        list4.push_back(30);
        list4.push_back(40);
        iterator = list4.insert(list4.cbegin(), 10);
        const std::initializer_list<int> expected4 = { 10, 20, 30, 40 };
        tests::compare("List4", list4, expected4);

        dsa::List<int> list5{ 10, 20, 30 };
        list5.insert(list5.end(), 40);
        const std::initializer_list<int> expected5 = { 10, 20, 30, 40 };
        tests::compare("List5", list5, expected5);

        dsa::List<int> list6{ 10, 20, 30 };
        list6.insert(list6.end(), { 40, 50, 60 });
        const std::initializer_list<int> expected6 = { 10, 20, 30, 40, 50, 60 };
        tests::compare("List6", list6, expected6);

        dsa::List<int> list7{ 40 };
        list7.insert(list7.begin(), { 10, 20, 30 });
        const std::initializer_list<int> expected7 = { 10, 20, 30, 40 };
        tests::compare("List7", list7, expected7);

        dsa::List<int> list8{};
        auto iter8 = list8.end();
        std::advance(iter8, 1);
        iter8 = list8.insert(iter8, { 10, 20, 30 });
        tests::compare("iter8 == nullptr", iter8 == nullptr, true);

        dsa::List<int> list9;
        auto ref9 = list9.emplace_front(30);
        tests::compare("List9 ref", ref9, list9.front());
        ref9 = list9.emplace_front(20);
        tests::compare("List9 ref", ref9, list9.front());
        list9.emplace_front(10);
        list9.emplace_front(5);
        list9.emplace_front(0);
        const std::initializer_list<int> expected9 = { 0, 5, 10, 20, 30 };
        tests::compare("List9", list9, expected9);

        dsa::List<int> list10{ 0, 10, 20, 30 };
        auto iter10 = list10.emplace(list10.begin(), -10);
        tests::compare("List10 iter", *iter10, *list10.begin());
        const std::initializer_list<int> expected10 = { -10, 0, 10, 20, 30 };
        tests::compare("List10", list10, expected10);

        dsa::List<int> list11{ 0, 10, 20, 30 };
        auto iter11 = list11.emplace(list11.end(), 40);
        tests::compare("List11 iter", *iter11, *(--list11.end()));
        const std::initializer_list<int> expected11 = { 0, 10, 20, 30, 40 };
        tests::compare("List11", list11, expected11);

        dsa::List<int> list12{ 0, 10, 20, 30 };
        auto ref12 = list12.emplace_back(40);
        tests::compare("List12 ref", ref12, list12.back());
        const std::initializer_list<int> expected12 = { 0, 10, 20, 30, 40 };
        tests::compare("List12", list12, expected12);

        dsa::List<int> list13;
        list13.emplace_back(10);
        list13.emplace_back(20);
        list13.emplace_back(30);
        const std::initializer_list<int> expected13 = { 10, 20, 30 };
        tests::compare("List13", list13, expected13);


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list5{ 10, 20, 30 };
        std_list5.insert(std_list5.end(), 40);
        tests::compare("List5 vs std", list5, std_list5);

        std::list<int> std_list6{ 10, 20, 30 };
        std_list6.insert(std_list6.end(), { 40, 50, 60 });
        tests::compare("List6 vs std", list6, std_list6);

        dsa::List<int> std_list7{ 40 };
        std_list7.insert(std_list7.begin(), { 10, 20, 30 });
        tests::compare("List7 vs std", list7, std_list7);

        std::list<int> std_list9;
        std_list9.emplace_front(30);
        auto std_ref9 = std_list9.emplace_front(20);
        tests::compare("List9 ref vs std", ref9, std_ref9);
        std_list9.emplace_front(10);
        std_list9.emplace_front(5);
        std_list9.emplace_front(0);
        tests::compare("List9 vs std", list9, std_list9);

        std::list<int> std_list10{ 0, 10, 20, 30 };
        auto std_iter10 = std_list10.emplace(std_list10.begin(), -10);
        tests::compare("List10 iter vs std", *iter10, *std_iter10);
        tests::compare("List10 vs std", list10, std_list10);

        std::list<int> std_list11{ 0, 10, 20, 30 };
        auto std_iter11 = std_list11.emplace(std_list11.end(), 40);
        tests::compare("List11 iter vs std", *std_iter11, *(--std_list11.end()));
        tests::compare("List11 vs std", list11, std_list11);

        std::list<int> std_list12{ 0, 10, 20, 30 };
        auto std_ref12 = std_list12.emplace_back(40);
        tests::compare("List12 ref vs std", ref12, std_ref12);
        tests::compare("List12 vs std", list12, std_list12);

        std::list<int> std_list13;
        std_list13.emplace_back(10);
        std_list13.emplace_back(20);
        std_list13.emplace_back(30);
        tests::compare("List13 vs std", list13, std_list13);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}