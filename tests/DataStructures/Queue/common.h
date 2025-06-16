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

#include "Queue.h"

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
 * @brief Function compares values of Queue and initializer list
 *
 * @tparam T type of elements to compare
 * @param[in] queue input Queue
 * @param[in] test_values input initializer list
 * @return true if compared containers are different
 * @return false if containers are equal
 */
template<typename T>
bool if_error(Queue<T> queue, const std::initializer_list<T>& test_values)
{
    if (queue.size() != test_values.size())
    {
        std::cout << "Objects of different length!\n";
        tests::failed++;
        return true;
    }

    for (int i = 0; i < test_values.size(); i++)
    {
        bool not_eq = queue.front() != test_values.begin()[i];
        if (not_eq )
        {
            std::cout << "Comparison error! queue value " << queue.front()
                << " not equal to " << test_values.begin()[i] << '\n';
            tests::failed++;
            return true;
        }
        queue.pop();
    }

    return false;
}

/**
 * @brief Function compares values of two objects
 *
 * @tparam T type of compared objects
 * @param[in] a input object
 * @param[in] b input object
 * @retval true if objests are not equal
 * @retval false otherwise
 */
template<typename T>
bool if_error(T a, T b)
{
    bool res = a != b ? true : false;
    if (res)
    {
        tests::failed++;
    }
    return res;
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
