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
#include "List.h"
#include "Queue.h"
#include "Stack.h"

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
 * @brief Function compares two values
 *
 * @tparam T type of compared objects
 * @param[in] a input value
 * @param[in] b input value
 * @retval true if values are not equal
 * @retval false otherwise
 */
template<typename T>
bool if_error(T a, T b)
{
    bool res = a != b ? true : false;
    if (res)
    {
        std::cout << "Comparison error! Value " << a << " not equal to " << b << '\n';
        tests::failed++;
    }
    return res;
}

/**
 * @brief Function compares values of ForwardList and initializer list
 *
 * @tparam T type of elements to compare
 * @param[in] fl input ForwardList
 * @param[in] test_values input initializer list
 * @return true if compared containers are different
 * @return false if containers are equal
 */
template<typename T>
bool if_error(ForwardList<T> fl, const std::initializer_list<T>& test_values)
{
    if (if_error(fl.size(), test_values.size()))
    {
        std::cout << "Objects of different length!\n";
        return true;
    }

    for (int i = 0; i < test_values.size(); i++)
    {
        if (if_error(fl.front(), test_values.begin()[i]))
        {
            return true;
        }
        fl.pop_front();
    }

    return false;
}

/**
 * @brief Function compares values of List and initializer list
 *
 * @tparam T type of elements to compare
 * @param[in] ll input List
 * @param[in] test_values input initializer list
 * @return true if compared containers are different
 * @return false if containers are equal
 */
template<typename T>
bool if_error(List<T> ll, const std::initializer_list<T>& test_values)
{
    if (if_error(ll.size(), test_values.size()))
    {
        std::cout << "Objects of different length!\n";
        return true;
    }

    for (int i = 0; i < test_values.size(); i++)
    {
        if (if_error(ll.front(), test_values.begin()[i]))
        {
            return true;
        }
        ll.pop_front();
    }

    return false;
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
    if (if_error(queue.size(), test_values.size()))
    {
        std::cout << "Objects of different length!\n";
        return true;
    }

    for (int i = 0; i < test_values.size(); i++)
    {
        if (if_error(queue.front(), test_values.begin()[i]))
        {
            return true;
        }
        queue.pop();
    }

    return false;
}

/**
 * @brief Function compares values of Stack and initializer list
 *
 * @tparam T type of elements to compare
 * @param[in] stack input Stack
 * @param[in] test_values input initializer list
 * @return true if compared containers are different
 * @return false if containers are equal
 */
template<typename T>
bool if_error(Stack<T> stack, const std::initializer_list<T>& test_values)
{
    if (if_error(stack.size(), test_values.size()))
    {
        std::cout << "Objects of different length!\n";
        return true;
    }

    for (int i = 0; i < test_values.size(); i++)
    {
        if (if_error(stack.top(), test_values.begin()[i]))
        {
            return true;
        }
        stack.pop();
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
