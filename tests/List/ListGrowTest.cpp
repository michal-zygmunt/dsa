/**
 * @file ListGrow.cpp
 * @brief This file tests functions increasing List length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/List.h"

#include <cstddef>
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
        std::cout << "Start ListGrow test:\n";

        dsa::List<int> list1 = dsa::List<int>(1, 40);
        auto iterator = list1.insert(list1.cbegin(), 30);
        list1.insert(iterator, { 10, 20 });
        list1.push_front(0);
        list1.push_front(-10);
        // Try inserting nodes at invalid indexes
        auto indexes = { -1, 0, 4, 2, 100 };
        for (size_t i = 0; i < indexes.size(); i++)
        {
            const int idx_val = indexes.begin()[i];
            list1.insert(list1.cbegin()[static_cast<size_t>(idx_val)], idx_val);
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
        tests::compare("ForwardList7", list7, expected7);

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