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

#include <forward_list>
#include <initializer_list>
#include <iostream>
#include <list>
#include <queue>
#include <stack>

 /**
  * @brief Namespace with test results
  */
namespace tests
{
    /**
     * @brief Function return number of failed comparisons
     *
     * @return int& reference to failed comparison count
     */
    inline auto failed_count() -> int&
    {
        static int failed{};
        return failed;
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
    auto if_error(const T& val1, const T& val2) -> bool
    {
        const bool res = val1 != val2;
        if (res)
        {
            std::cout << "Comparison error! Value " << val1 << " not equal to " << val2 << '\n';
            tests::failed_count()++;
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
    auto if_error(dsa::ForwardList<T> container, const std::initializer_list<T>& test_values) -> bool
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
    auto if_error(dsa::List<T> container, const std::initializer_list<T>& test_values) -> bool
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
    auto if_error(dsa::Queue<T> queue, const std::initializer_list<T>& test_values) -> bool
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
    auto if_error(dsa::Stack<T> stack, const std::initializer_list<T>& test_values) -> bool
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
     * @brief Function compares values of ForwardList and forward_list
     *
     * @tparam T type of elements to compare
     * @param[in] container input ForwardList
     * @param[in] test_values input forward_list
     * @return true if compared containers are different
     * @return false if containers are equal
     */
    template<typename T>
    auto if_error(dsa::ForwardList<T> container, std::forward_list<T> test_values) -> bool
    {
        auto test_values_size = static_cast<size_t>(std::distance(test_values.begin(), test_values.end()));

        if (if_error(container.size(), test_values_size))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (size_t i = 0; i < test_values_size; i++)
        {
            if (if_error(container.front(), test_values.front()))
            {
                return true;
            }
            container.pop_front();
            test_values.pop_front();
        }

        return false;
    }

    /**
     * @brief Function compares values of List and list
     *
     * @tparam T type of elements to compare
     * @param[in] container input List
     * @param[in] test_values input list
     * @return true if compared containers are different
     * @return false if containers are equal
     */
    template<typename T>
    auto if_error(dsa::List<T> container, std::list<T> test_values) -> bool
    {
        auto test_values_size = static_cast<size_t>(std::distance(test_values.begin(), test_values.end()));

        if (if_error(container.size(), test_values_size))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (size_t i = 0; i < test_values_size; i++)
        {
            if (if_error(container.front(), test_values.front()))
            {
                return true;
            }
            container.pop_front();
            test_values.pop_front();
        }

        return false;
    }

    /**
     * @brief Function compares values of Queue and queue
     *
     * @tparam T type of elements to compare
     * @param[in] container input Queue
     * @param[in] test_values input queue
     * @return true if compared containers are different
     * @return false if containers are equal
     */
    template<typename T>
    auto if_error(dsa::Queue<T> queue, std::queue<T>& test_values) -> bool
    {
        if (if_error(queue.size(), test_values.size()))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (size_t i = 0; i < test_values.size(); i++)
        {
            if (if_error(queue.front(), test_values.front()))
            {
                return true;
            }
            queue.pop();
            test_values.pop();
        }

        return false;
    }

    /**
     * @brief Function compares values of Stack and stack
     *
     * @tparam T type of elements to compare
     * @param[in] container input Stack
     * @param[in] test_values input stack
     * @return true if compared containers are different
     * @return false if containers are equal
     */
    template<typename T>
    auto if_error(dsa::Stack<T> stack, std::stack<T> test_values) -> bool
    {
        if (if_error(stack.size(), test_values.size()))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (size_t i = 0; i < test_values.size(); i++)
        {
            if (if_error(stack.top(), test_values.top()))
            {
                return true;
            }
            stack.pop();
            test_values.pop();
        }

        return false;
    }

    /**
     * @brief Function overloads out operator to print all elements of initializer list
     *
     * @tparam T type of initializer list elements
     * @param[in,out] out reference to output stream
     * @param[in] std_init_list input container of type T
     * @return std::ostream&
     */
    template<typename T>
    auto operator<<(std::ostream& out, const std::initializer_list<T>& std_init_list) -> std::ostream&
    {
        for (const auto& item : std_init_list)
        {
            out << item << ' ';
        }
        return out;
    }

    /**
     * @brief Function overloads out operator to print all elements of initializer list
     *
     * @tparam T type of initializer list elements
     * @param[in,out] out reference to output stream
     * @param[in] std_forward_list input container of type T
     * @return std::ostream&
     */
    template<typename T>
    auto operator<<(std::ostream& out, const std::forward_list<T>& std_forward_list) -> std::ostream&
    {
        for (const auto& item : std_forward_list)
        {
            out << item << ' ';
        }
        return out;
    }

    /**
     * @brief Function overloads out operator to print all elements of list
     *
     * @tparam T type of list elements
     * @param[in,out] out reference to output stream
     * @param[in] std_list input container of type T
     * @return std::ostream&
     */
    template<typename T>
    auto operator<<(std::ostream& out, const std::list<T>& std_list) -> std::ostream&
    {
        for (const auto& item : std_list)
        {
            out << item << ' ';
        }
        return out;
    }

    /**
     * @brief Function overloads out operator to print all elements of queue
     *
     * @tparam T type of queue elements
     * @param[in,out] out reference to output stream
     * @param[in] std_queue input container of type T
     * @return std::ostream&
     */
    template<typename T>
    auto operator<<(std::ostream& out, std::queue<T> std_queue) -> std::ostream&
    {
        while (!std_queue.empty())
        {
            out << std_queue.front() << ' ';
            std_queue.pop();
        }
        return out;
    }

    /**
     * @brief Function overloads out operator to print all elements of stack
     *
     * @tparam T type of stack elements
     * @param[in,out] out reference to output stream
     * @param[in] std_stack input container of type T
     * @return std::ostream&
     */
    template<typename T>
    auto operator<<(std::ostream& out, std::stack<T> std_stack) -> std::ostream&
    {
        while (!std_stack.empty())
        {
            out << std_stack.top() << ' ';
            std_stack.pop();
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
    void compare(const std::string& container_name, const T& container, const std::initializer_list<U>& expected)
    {
        std::cout << container_name << ':' << '\t' << container << '\n';
        std::cout << "Expected:  \t" << expected << '\n';
        const bool res = if_error(container, expected);
        std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    }

    /**
     * @brief Function compares content of two containers
     *
     * @tparam T input container
     * @tparam U type of data stored in forward_list
     * @param[in] container_name container name to print
     * @param[in] container input container
     * @param[in] expected expected content of input container, stored as forward_list
     */
    template<typename T, typename U>
    void compare(const std::string& container_name, const T& container, const std::forward_list<U>& expected)
    {
        std::cout << container_name << ':' << '\t' << container << '\n';
        std::cout << "Expected:  \t" << expected << '\n';
        const bool res = if_error(container, expected);
        std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    }

    /**
     * @brief Function compares content of two containers
     *
     * @tparam T input container
     * @tparam U type of data stored in list
     * @param[in] container_name container name to print
     * @param[in] container input container
     * @param[in] expected expected content of input container, stored as list
     */
    template<typename T, typename U>
    void compare(const std::string& container_name, const T& container, const std::list<U>& expected)
    {
        std::cout << container_name << ':' << '\t' << container << '\n';
        std::cout << "Expected:  \t" << expected << '\n';
        const bool res = if_error(container, expected);
        std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    }

    /**
     * @brief Function compares content of two containers
     *
     * @tparam T input container
     * @tparam U type of data stored in queue
     * @param[in] container_name container name to print
     * @param[in] container input container
     * @param[in] expected expected content of input container, stored as queue
     */
    template<typename T, typename U>
    void compare(const std::string& container_name, const T& container, std::queue<U> expected)
    {
        std::cout << container_name << ':' << '\t' << container << '\n';
        std::cout << "Expected:  \t" << expected << '\n';
        const bool res = if_error(container, expected);
        std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    }

    /**
     * @brief Function compares content of two containers
     *
     * @tparam T input container
     * @tparam U type of data stored in stack
     * @param[in] container_name container name to print
     * @param[in] container input container
     * @param[in] expected expected content of input container, stored as stack
     */
    template<typename T, typename U>
    void compare(const std::string& container_name, const T& container, const std::stack<U>& expected)
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
    void compare(const std::string& container_name, const T& val1, const T& val2)
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
    auto compare(T val1, T val2) -> bool
    {
        return if_error(val1, val2);
    }
}

#endif // !COMMON_H
