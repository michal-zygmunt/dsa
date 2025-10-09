/**
 * @file ForwardListGrow.cpp
 * @brief This file tests functions swapping ForwardList objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/ForwardList.h"

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
        std::cout << "Start ForwardListSwap test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> il_2{ 10, 20, 30, 40, 50 };

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list2 = dsa::ForwardList<int>(il_2);
        list1.swap(list2);
        const std::initializer_list<int> expected1 = il_2;
        tests::compare("ForwardList1", list1, expected1);
        const std::initializer_list<int> expected2 = il_1;
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>(il_1);
        dsa::ForwardList<int> list4;
        list3.swap(list4);
        const std::initializer_list<int> expected3 = { };
        tests::compare("ForwardList3", list3, expected3);
        const std::initializer_list<int> expected4 = il_1;
        tests::compare("ForwardList4", list4, expected4);

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
