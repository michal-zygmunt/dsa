/**
 * @file ForwardListShrink.cpp
 * @brief This file tests functions decreasing ForwardList length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/ForwardList.h"

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
        std::cout << "Start ForwardListShrink test:\n";

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
        list1.erase_after(list1.begin()[list1.size() - 2]);
        list1.pop_front();
        auto indexes = { 100, 5, 2, 0, -1 };
        for (const auto& item : indexes)
        {
            list1.erase_after(list1.begin()[static_cast<size_t>(item)]);
        }
        const std::initializer_list<int> expected1 = { 10, 30 };
        tests::compare("ForwardList1", list1, expected1);

        dsa::ForwardList<int> list2 = dsa::ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
        list2.erase_after(list2.begin()[1], list2.begin()[3]);
        const std::initializer_list<int> expected2 = { 0, 10, 30, 40, 50 };
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
        list3.erase_after(list3.begin()[1]);
        list3.erase_after(list3.begin()[1], list3.begin()[3]);
        const std::initializer_list<int> expected3 = { 0, 10, 40, 50 };
        tests::compare("ForwardList3", list3, expected3);

        dsa::ForwardList<int> list4 = dsa::ForwardList<int>({ 0, 10, 20, 30, 40, 50 });
        list4.erase_after(list4.begin()[1]);
        list4.erase_after(list4.begin()[1], list4.begin()[4]);
        const std::initializer_list<int> expected4 = { 0, 10, 50 };
        tests::compare("ForwardList4", list4, expected4);

        dsa::ForwardList<int> list5 = dsa::ForwardList<int>({ 0, 10, 0, 0, 40, 0 });
        list5.remove(0);
        const std::initializer_list<int> expected5 = { 10, 40 };
        tests::compare("ForwardList5", list5, expected5);

        dsa::ForwardList<int> list6 = dsa::ForwardList<int>({ 0, 0, 0, 0, 0, 0 });
        list6.remove(0);
        const std::initializer_list<int> expected6 = { };
        tests::compare("ForwardList6", list6, expected6);

        dsa::ForwardList<int> list7 = dsa::ForwardList<int>({ 0 });
        tests::compare(list7.empty(), false);
        list7.clear();
        tests::compare(list7.empty(), true);
        const std::initializer_list<int> expected7 = { };
        tests::compare("ForwardList7", list7, expected7);

        dsa::ForwardList<int> list8 = dsa::ForwardList<int>({ 10, 20, 30 });
        list8.pop_front();
        list8.pop_front();
        list8.pop_front();
        list8.pop_front();
        const std::initializer_list<int> expected8 = { };
        tests::compare("ForwardList8", list8, expected8);

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