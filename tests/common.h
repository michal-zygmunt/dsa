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

#include "dsa/forward_list.h"
#include "dsa/list.h"
#include "dsa/queue.h"
#include "dsa/stack.h"

#include <forward_list>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <list>
#include <optional>
#include <queue>
#include <source_location>
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
     * @brief Function return total number of comparisons
     *
     * @return int& reference to total comparison count
     */
    inline auto total_count() -> int&
    {
        static int total{};
        return total;
    }

    /**
     * @brief Function print error message
     *
     * @param[in] message text describing error
     * @param[in] exception exception to handle
     */
    void print_err_msg(const std::string& message, const std::exception* exception = nullptr);

    /**
     * @brief Helper function to handle exceptions
     *
     * @param[in] exception exception to handle
     * @param[in] location struct containing information about called file / line / function
     */
    auto handle_exception(const std::optional<std::exception_ptr>& exception = std::nullopt,
        const std::source_location& location = std::source_location::current()) -> int;

    /**
     * @brief Function compares two values
     *
     * @tparam T type of compared values
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
     * @brief Function compares two values
     *
     * @tparam T type of compared objects
     * @param[in] val1 input value
     * @param[in] val2 input value
     * @retval true if values are not equal
     * @retval false otherwise
     */
    template<typename T>
    auto cmp(const T& val1, const T& val2) -> bool
    {
        tests::total_count()++;
        return if_error(val1, val2);
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
    auto cmp(dsa::ForwardList<T> container, const std::initializer_list<T>& test_values) -> bool
    {
        const auto size{ (test_values.size()) };
        tests::total_count() += static_cast<int>(size);

        if (if_error(container.size(), size))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (const auto& item : test_values)
        {
            if (if_error(container.front(), item))
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
    auto cmp(dsa::List<T> container, const std::initializer_list<T>& test_values) -> bool
    {
        const auto size{ (test_values.size()) };
        tests::total_count() += static_cast<int>(size);

        if (if_error(container.size(), size))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (const auto& item : test_values)
        {
            if (if_error(container.front(), item))
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
    auto cmp(dsa::Queue<T> queue, const std::initializer_list<T>& test_values) -> bool
    {
        const auto size{ (test_values.size()) };
        tests::total_count() += static_cast<int>(size);

        if (if_error(queue.size(), size))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (const auto& item : test_values)
        {
            if (if_error(queue.front(), item))
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
    auto cmp(dsa::Stack<T> stack, const std::initializer_list<T>& test_values) -> bool
    {
        const auto size{ (test_values.size()) };
        tests::total_count() += static_cast<int>(size);

        if (if_error(stack.size(), size))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (const auto& item : test_values)
        {
            if (if_error(stack.top(), item))
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
    auto cmp(dsa::ForwardList<T> container, std::forward_list<T> test_values) -> bool
    {
        const auto size{ static_cast<size_t>(std::distance(test_values.begin(), test_values.end())) };
        tests::total_count() += static_cast<int>(size);

        if (if_error(container.size(), size))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (size_t i = 0; i < size; i++)
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
    auto cmp(dsa::List<T> container, std::list<T> test_values) -> bool
    {
        const auto size{ static_cast<size_t>(std::distance(test_values.begin(), test_values.end())) };
        tests::total_count() += static_cast<int>(size);

        if (if_error(container.size(), size))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (size_t i = 0; i < size; i++)
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
    auto cmp(dsa::Queue<T> queue, std::queue<T>& test_values) -> bool
    {
        const auto size{ (test_values.size()) };
        tests::total_count() += static_cast<int>(size);

        if (if_error(queue.size(), size))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (size_t i = 0; i < size; i++)
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
    auto cmp(dsa::Stack<T> stack, std::stack<T> test_values) -> bool
    {
        const auto size{ (test_values.size()) };
        tests::total_count() += static_cast<int>(size);

        if (if_error(stack.size(), size))
        {
            std::cout << "Objects of different length!\n";
            return true;
        }

        for (size_t i = 0; i < size; i++)
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
     * @brief Function print number of passed and failed comparisons
     */
    inline auto print_stats() -> void
    {
        std::cout << total_count() - failed_count() << "/" << total_count() << " PASS, "
            << failed_count() << " FAIL\n";
    }

    /**
     * @brief Function prints content of compared containers
     *
     * @tparam T type of data stored in forst container
     * @tparam U type of data stored in second container
     * @param[in] name_1 first container name to print
     * @param[in] container_1 first input container
     * @param[in] name_2 second container name to print
     * @param[in] container_2 second input container
     */
    template<typename T, typename U>
    auto print_containers(const std::string& name_1, const T& container_1,
        const std::string& name_2, const U& container_2) -> void
    {
        const int size{ static_cast<int>(std::max(name_1.length(), name_2.length())) };
        std::cout << std::setw(size) << std::left << name_1 << ": " << container_1 << '\n';
        std::cout << std::setw(size) << std::left << name_2 << ": " << container_2 << '\n';
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
        print_containers(container_name, container, "Expected", expected);
        const bool res = cmp(container, expected);
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
        print_containers(container_name, container, "Expected", expected);
        const bool res = cmp(container, expected);
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
        print_containers(container_name, container, "Expected", expected);
        const bool res = cmp(container, expected);
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
        print_containers(container_name, container, "Expected", expected);
        const bool res = cmp(container, expected);
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
        print_containers(container_name, container, "Expected", expected);
        const bool res = cmp(container, expected);
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
        print_containers(container_name, val1, "Expected", val2);
        const bool res = cmp(val1, val2);
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
        return cmp(val1, val2);
    }
}

#endif // !COMMON_H
