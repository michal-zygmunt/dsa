/**
 * @file common.h
 * @brief This file defines helper functions for tests
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#ifndef COMMON_H
#define COMMON_H

#include "ForwardList.h"

#include <initializer_list>
#include <iostream>

 /**
  * @brief Namespace with test results
  */
namespace tests
{
    static int failed{};
}

/**
 * @brief Function compares values of ForwardList and initializer list
 *
 * @tparam T type of elements to compare
 * @param[in] ll input ForwardList
 * @param[in] test_values input initializer list
 * @return true if compared containers are different
 * @return false if containers are equal
 */
template<typename T>
bool if_error(const ForwardList<T>& ll, const std::initializer_list<T>& test_values)
{
    if (ll.size() != test_values.size())
    {
        std::cout << "Objects of different length!\n";
        tests::failed++;
        return true;
    }

    for (int i = 0; i < test_values.size(); i++)
    {
        if (ll.get(i)->value() != test_values.begin()[i])
        {
            std::cout << "Comparison error! ll value " << ll.get(i)->value()
                << " not equal to " << test_values.begin()[i] << '\n';
            tests::failed++;
            return true;
        }
    }

    return false;
}

/**
 * @brief Function overloads out operator to print all elements of initializer list
 *
 * @tparam T type of initializer list elements
 * @param[in,out] out reference to output stream
 * @param[in] il input initializer list of type T
 * @return std::ostream&
 */
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::initializer_list<T>& il)
{
    for (const auto& i : il)
    {
        out << i << ' ';
    }
    return out;
}

#endif // !COMMON_H
