/**
 * @file ListGet.cpp
 * @brief This file tests accessing values of List Nodes
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
        std::cout << "Start ListGet test:\n";

        const dsa::List<int> list1 = dsa::List<int>({ 0, 10, 20 });
        // Try reading some nodes with invalid indexes
        const std::initializer_list<int> expected1 = { 0, 10, 20 };
        auto indexes = { -1, 0, 1, 2, 100 };
        for (size_t i = 0; i < indexes.size(); i++)
        {
            auto* temp = list1.get(i);
            if (static_cast<bool>(temp))
            {
                tests::compare(temp->value(), expected1.begin()[i]);
            }
        }
        tests::compare("List1", list1, expected1);

        const dsa::List<int> list2 = dsa::List<int>({ 20, 10, 0 });
        const std::initializer_list<int> expected2 = { 20, 10, 0 };
        for (size_t i = 0; i < indexes.size(); i++)
        {
            auto* temp = list2.get(i);
            if (static_cast<bool>(temp))
            {
                tests::compare(temp->value(), expected2.begin()[i]);
            }
        }
        tests::compare("List2", list2, expected2);

        const dsa::List<int> list3 = dsa::List<int>({ 0, 10, 20 });
        tests::compare("List3 front", list3.front(), 0);
        tests::compare("List3 back", list3.back(), 20);
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