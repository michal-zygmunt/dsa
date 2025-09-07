/**
 * @file common.h
 * @brief This file defines helper functions for tests
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#ifndef COMMON_H
#define COMMON_H

#include "dsa/ForwardList.h"
#include "dsa/List.h"
#include "dsa/Queue.h"
#include "dsa/Stack.h"

#include <initializer_list>
#include <iostream>

 /**
  * @brief Namespace with test results
  */
namespace tests
{
    static int failed{};

    /**
     * @brief Function compares two values
     *
     * @tparam T type of compared objects
     * @param[in] val1 input value
     * @param[in] val2 input value
     * @retval true if values are not equal
     * @retval false otherwise
     */
    template<typename T>
    bool if_error(T val1, T val2)
    {
        const bool res = val1 != val2 ? true : false;
        if (res)
        {
            std::cout << "Comparison error! Value " << val1 << " not equal to " << val2 << '\n';
            tests::failed++;
        }
        return res;
    }

    /**
     * @brief Function compares values of ForwardList and initializer list
     *
     * @tparam T type of elements to compare
     * @param[in] container input ForwardList
     * @param[in] test_values input initializer list
     * @return true if compared containers are different
     * @return false if containers are equal
     */
    template<typename T>
    bool if_error(dsa::ForwardList<T> container, const std::initializer_list<T>& test_values)
    {
        if (if_error(container.size(), test_values.size()))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (size_t i = 0; i < test_values.size(); i++)
        {
            if (if_error(container.front(), test_values.begin()[i]))
            {
                return true;
            }
            container.pop_front();
        }

        return false;
    }

    /**
     * @brief Function compares values of List and initializer list
     *
     * @tparam T type of elements to compare
     * @param[in] container input List
     * @param[in] test_values input initializer list
     * @return true if compared containers are different
     * @return false if containers are equal
     */
    template<typename T>
    bool if_error(dsa::List<T> container, const std::initializer_list<T>& test_values)
    {
        if (if_error(container.size(), test_values.size()))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (size_t i = 0; i < test_values.size(); i++)
        {
            if (if_error(container.front(), test_values.begin()[i]))
            {
                return true;
            }
            container.pop_front();
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
    bool if_error(dsa::Queue<T> queue, const std::initializer_list<T>& test_values)
    {
        if (if_error(queue.size(), test_values.size()))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (size_t i = 0; i < test_values.size(); i++)
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
    bool if_error(dsa::Stack<T> stack, const std::initializer_list<T>& test_values)
    {
        if (if_error(stack.size(), test_values.size()))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (size_t i = 0; i < test_values.size(); i++)
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
     * @param[in] init_list input initializer list of type T
     * @return std::ostream&
     */
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const std::initializer_list<T>& init_list)
    {
        for (const auto& item : init_list)
        {
            out << item << ' ';
        }
        return out;
    }

    /**
     * @brief Function compares content of two containers
     *
     * @tparam T input container
     * @tparam U type of data stored in initializer list
     * @param[in] container_name container name to print
     * @param[in] container input container
     * @param[in] expected expected content of input container, stored as elements of initializer list
     */
    template<typename T, typename U>
    void compare(std::string container_name, const T& container, const std::initializer_list<U>& expected)
    {
        std::cout << container_name << ':' << '\t' << container << '\n';
        std::cout << "Expected:  \t" << expected << '\n';
        const bool res = if_error(container, expected);
        std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    }

    /**
     * @brief Function compares two values
     *
     * @tparam T type of compared objects
     * @param container_name container name to print
     * @param[in] val1 input value
     * @param[in] val2 input value
     */
    template<typename T>
    void compare(std::string container_name, const T& val1, const T& val2)
    {
        std::cout << container_name << ':' << '\t' << val1 << '\n';
        std::cout << "Expected:  \t" << val2 << '\n';
        const bool res = if_error(val1, val2);
        std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    }

    /**
     * @brief Function compares two values
     *
     * @tparam T type of compared objects
     * @param[in] val1 input value
     * @param[in] val2 input value
     * @retval true if values are not equal
     * @retval false otherwise
     */
    template<typename T>
    bool compare(T val1, T val2)
    {
        return if_error(val1, val2);
    }
}

#endif // !COMMON_H
