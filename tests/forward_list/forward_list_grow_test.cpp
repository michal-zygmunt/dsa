/**
 * @file forward_list_grow_test.cpp
 * @brief This file tests functions increasing ForwardList length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/forward_list.h"

#include <cstddef>
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
        std::cout << "Start forward_list_grow_test:\n";

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>(1, 10);
        auto iterator = list1.insert_after(list1.cbegin(), 20);
        list1.insert_after(iterator, { 30, 40 });
        list1.push_front(0);
        list1.push_front(-10);
        // Try inserting nodes at invalid indexes
        auto indexes = { 0, 4, 2, 100 };
        for (size_t i = 0; i < indexes.size(); i++)
        {
            const int idx_val = indexes.begin()[i];
            list1.insert_after(list1.cbegin()[static_cast<size_t>(idx_val)], idx_val);
        }
        const std::initializer_list<int> expected1{ -10, 0, 0, 2, 10, 20, 4, 30, 40 };
        tests::compare("ForwardList1", list1, expected1);

        dsa::ForwardList<int> list2 = dsa::ForwardList<int>(1, 50);
        list2.push_front(40);
        list2.push_front(30);
        list2.push_front(20);
        list2.push_front(10);
        list2.insert_after(list2.cbegin(), 5, 5);
        const std::initializer_list<int> expected2 = { 10, 5, 5, 5, 5, 5, 20, 30, 40, 50 };
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>(1, 50);
        list3.push_front(40);
        list3.push_front(30);
        list3.push_front(10);
        iterator = list3.insert_after(list3.cbegin(), 20);
        list3.insert_after(iterator, { 1, 2, 3 });
        list3.insert_after(list3.cbegin()[list3.size() - 1], 60);
        const std::initializer_list<int> expected3 = { 10, 20, 1, 2, 3, 30, 40, 50, 60 };
        tests::compare("ForwardList3", list3, expected3);

        dsa::ForwardList<int> list4;
        list4.push_front(40);
        list4.push_front(30);
        list4.push_front(10);
        iterator = list4.insert_after(list4.cbegin(), 20);
        const std::initializer_list<int> expected4 = { 10, 20, 30, 40 };
        tests::compare("ForwardList4", list4, expected4);

        dsa::ForwardList<int> list5;
        list5.insert_after(list5.before_begin(), 40);
        list5.insert_after(list5.before_begin(), 30);
        list5.insert_after(list5.cbefore_begin(), 20);
        list5.insert_after(list5.cbefore_begin(), 10);
        const std::initializer_list<int> expected5 = { 10, 20, 30, 40 };
        tests::compare("ForwardList5", list5, expected5);

        dsa::ForwardList<int> list6{ 40 };
        list6.insert_after(list6.before_begin(), 30);
        list6.insert_after(list6.before_begin(), 20);
        list6.insert_after(list6.before_begin(), 10);
        const std::initializer_list<int> expected6 = { 10, 20, 30, 40 };
        tests::compare("ForwardList6", list6, expected6);

        dsa::ForwardList<int> list7{ 40 };
        list7.insert_after(list7.before_begin(), { 10, 20, 30 });
        const std::initializer_list<int> expected7 = { 10, 20, 30, 40 };
        tests::compare("ForwardList7", list7, expected7);


        std::cout << "Compare operations results with std container\n\n";

        std::forward_list<int> std_list5;
        std_list5.insert_after(std_list5.before_begin(), 40);
        std_list5.insert_after(std_list5.before_begin(), 30);
        std_list5.insert_after(std_list5.cbefore_begin(), 20);
        std_list5.insert_after(std_list5.cbefore_begin(), 10);
        tests::compare("ForwardList5 vs std", list5, std_list5);

        std::forward_list<int> std_list6{ 40 };
        std_list6.insert_after(std_list6.before_begin(), 30);
        std_list6.insert_after(std_list6.before_begin(), 20);
        std_list6.insert_after(std_list6.before_begin(), 10);
        tests::compare("ForwardList5 vs std", list5, std_list6);

        std::forward_list<int> std_list7{ 40 };
        std_list7.insert_after(std_list7.before_begin(), { 10, 20, 30 });
        tests::compare("ForwardList7 vs std", list7, std_list7);
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
