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

#include "dsa/array.h"
#include "dsa/forward_list.h"
#include "dsa/list.h"
#include "dsa/queue.h"
#include "dsa/stack.h"
#include "dsa/vector.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <exception>
#include <forward_list>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <list>
#include <optional>
#include <queue>
#include <ranges>
#include <source_location>
#include <stack>
#include <string>
#include <vector>

 /**
  * @brief Namespace with test results
  */
namespace tests
{
    constexpr size_t throwing_type_size_limit = 5;

    /**
     * @brief Class used to test exception handling
     */
    class ThrowingType
    {
    public:

        /**
         * @brief Default ctor of ThrowingType
         */
        ThrowingType()
        {
            conditional_exception("ThrowingType size limit reached in ctor");
        }

        /**
         * @brief Copy ctor of ThrowingType
         *
         * @param[in] other unused parameter
         */
        ThrowingType(const ThrowingType& /*other*/)
        {
            conditional_exception("ThrowingType size limit reached in copy ctor");
        }

        /**
         * @brief Move ctor of ThrowingType
         *
         * @param[in] other unused parameter
         */
         // move constructors intentionally throw exception
         // NOLINTNEXTLINE(cppcoreguidelines-noexcept-move-operations,performance-noexcept-move-constructor,bugprone-exception-escape)
        ThrowingType(ThrowingType&& /*other*/)
        {
            conditional_exception("ThrowingType size limit reached in move ctor");
        }

        /**
         * @brief Default dtor of ThrowingType
         */
        ~ThrowingType() = default;

        /**
         * @brief Copy assignment of ThrowingType
         *
         * @param[in] other unused parameter
         * @return source ThrowingType object
         */
        auto operator=(const ThrowingType& other) noexcept(false) -> ThrowingType&
        {
            // empty if statement silences clang-tidy warning for copy assignment operator in mock struct
            if (this != &other) {}
            return *this;
        }

        /**
         * @brief Move assignment of ThrowingType
         *
         * @param[in] other unused parameter
         * @return source ThrowingType object
         */
        auto operator=(ThrowingType&& /*other*/) noexcept(false) -> ThrowingType&
        {
            return *this;
        }

        /**
         * @brief Operator used to check if two objects of ThrowingType are equal
         *
         * @param[in] other unused parameter
         * @return true
         */
        auto operator==(const ThrowingType& /* other */) const -> bool
        {
            return true;
        }

        /**
         * @brief Operator used to compare two objects of ThrowingType
         *
         * @param[in] other unused parameter
         * @return std::strong_ordering::equal
         */
        auto operator<=>(const ThrowingType& /* other */) const noexcept(false)
        {
            return std::strong_ordering::equal;
        }

    private:

        /**
         * @brief Function throws exception
         *
         * @param[in] msg message to print to standard output
         */
        void conditional_exception(const std::string& msg) const
        {
            if (++m_counter >= m_size_limit)
            {
                m_counter = 0;
                throw std::runtime_error(msg);
            }
        }

        /**
         * @brief Internal counter for throwing exceptions
         */
        static inline size_t m_counter{ 0 };

        /**
         * @brief Internal size limit for throwing exceptions
         */
        size_t m_size_limit{ throwing_type_size_limit };
    };

    /**
     * @enum ExceptionCode
     * @brief Determines return codes for exceptions in tests
     *
     * @note all values are negative
     */
    enum class ExceptionCode : std::int8_t
    {
        BadAlloc = -1,          ///< Memory allocation error
        OutOfRange = -2,        ///< Accesing wrong range
        RuntimeError = -3,      ///< Exception generated during program execution
        LengthError = -4,       ///< Maximum allowed size exceeded
        Exception = -5,         ///< General exception, exception reason should be moved into separate catch block
        Unknown = -6,           ///< Unhandled exception from (...) block
        Nullopt = -7            ///< Optional exception is invalid
    };

    /**
     * @enum Status
     * @brief Determines return codes for functions in tests
     */
    enum class Status : std::int8_t
    {
        OK = 0,                 ///< Function executed sucessfully
        Error = -1              ///< Function returned error
    };

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
     * @brief Concept that checks if an object of type T allows calling public `front()` method
     *
     * @tparam T type checked agains the concept
     *
     * @see requires
     */
    template <typename T>
    concept has_front = requires(T type)
    {
        type.front();
    };

    /**
     * @brief Concept that checks if an object of type T allows calling public `pop()` method
     *
     * @tparam T type checked agains the concept
     *
     * @see requires
     */
    template <typename T>
    concept has_pop = requires(T type)
    {
        type.pop();
    };

    /**
     * @brief Concept that checks if an object of type T allows calling public `pop_front()` method
     *
     * @tparam T type checked agains the concept
     *
     * @see requires
     */
    template <typename T>
    concept has_pop_front = requires(T type)
    {
        type.pop_front();
    };

    /**
     * @brief Concept that checks if an object provide printable range for not-string-like types
     *
     * @tparam T type checked agains the concept
     *
     * @see requires
     */
    template <typename T>
    concept has_printable_range = std::ranges::range<T> &&
        !std::same_as<std::remove_cvref_t<T>, std::string> &&
        !std::same_as<std::remove_cvref_t<T>, std::string_view> &&
        !std::is_convertible_v<T, const char*>;

    /**
     * @brief Concept that defines the requirements of a type that allows iteration over elements
     *
     * Concept is satisfied if an object of type T provides an iterator and sentinel that denote
     * the elements of the range
     *
     * @tparam T type checked agains the concept
     */
    template <typename T>
    concept has_ranges = std::ranges::range<T>;

    /**
     * @brief Concept that checks if an object of type T allows calling public `size()` method
     *
     * @tparam T type checked agains the concept
     *
     * @see requires
     */
    template <typename T>
    concept has_size = requires(T type)
    {
        type.size();
    };

    /**
     * @brief Concept that checks if an object of type T allows calling public `top()` method
     *
     * @tparam T type checked agains the concept
     *
     * @see requires
     */
    template <typename T>
    concept has_top = requires(T type)
    {
        type.top();
    };

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
    auto if_error(const T& val1, const T& val2) -> Status
    {
        const Status res = val1 != val2 ? Status::Error : Status::OK;
        if (res != Status::OK)
        {
            std::cout << "Comparison error! Value " << val1 << " not equal to " << val2 << '\n';
            tests::failed_count()++;
        }
        return res;
    }

    /**
     * @brief Function checks size of two container
     *
     * @tparam T type of input container
     * @tparam U type of input container with expected content
     * @param[in] container input container
     * @param[in] test_values input container with expected content
     * @return flag if compared containers have different size
     */
    template<typename T, typename U>
    auto compare_size(const T& container, const U& test_values) -> Status
    {
        size_t size{};
        if constexpr (has_size<U>)
        {
            size = test_values.size();
        }
        else if constexpr (has_ranges<U>)
        {
            size = static_cast<size_t>(std::distance(test_values.begin(), test_values.end()));
        }

        tests::total_count() += static_cast<int>(size);

        if (if_error(container.size(), size) != Status::OK)
        {
            std::cout << "Objects of different size!\n";
            return Status::Error;
        }

        return Status::OK;
    }

    /**
     * @brief Function compares elements of two iterable container
     *
     * @tparam T type of input container
     * @tparam U type of input container with expected content
     * @param[in] container input container
     * @param[in] test_values input container with expected content
     * @return flag if compared containers have different size
     */
    template<typename T, typename U>
    auto compare_elements_ranges(const T& container, const U& test_values) -> Status
    {
        auto iter = container.begin();

        for (const auto& item : test_values)
        {
            if (if_error(*iter, item) != Status::OK)
            {
                return Status::Error;
            }

            ++iter;
        }

        return Status::OK;
    }

    /**
     * @brief Function compares elements of stack container
     *
     * @tparam T type of input container
     * @tparam U type of input container with expected content
     * @param[in] container input container
     * @param[in] test_values input container with expected content
     * @return flag if compared containers have different size
     */
    template<typename T, typename U>
    auto compare_elements_stack(const T& container, const U& test_values) -> Status
    {
        T container_copy{ container };
        if constexpr (has_ranges<U>)
        {
            // handle dsa::Stack and std::stack comparison

            for (const auto& item : test_values)
            {
                if (if_error(container_copy.top(), item) != Status::OK)
                {
                    return Status::Error;
                }
                container_copy.pop();
            }
        }
        else if constexpr (has_top<U> && has_pop<U>)
        {
            // handle dsa::Stack or std::stack and std::initializer_list comparison

            U test_values_copy{ test_values };
            for (size_t i = 0; i < test_values.size(); i++)
            {
                if (if_error(container_copy.top(), test_values_copy.top()) != Status::OK)
                {
                    return Status::Error;
                }
                container_copy.pop();
                test_values_copy.pop();
            }
        }
        else
        {
            std::cout << "No constexpr condition was used for elements comparison of stack\n";
            return Status::Error;
        }

        return Status::OK;
    }

    /**
     * @brief Function compares elements of queue container
     *
     * @tparam T type of input container
     * @tparam U type of input container with expected content
     * @param[in] container input container
     * @param[in] test_values input container with expected content
     * @return flag if compared containers have different size
     */
    template<typename T, typename U>
    auto compare_elements_queue(const T& container, const U& test_values) -> Status
    {
        T container_copy{ container };
        if constexpr (has_ranges<U>)
        {
            // handle dsa::Queue or std::queue and std::initializer_list comparison

            for (const auto& item : test_values)
            {
                if (if_error(container_copy.front(), item) != Status::OK)
                {
                    return Status::Error;
                }
                container_copy.pop();
            }
        }
        else if constexpr (has_front<U> && has_pop<U>)
        {
            // handle dsa::Queue and std::queue comparison

            U test_values_copy{ test_values };
            for (size_t i = 0; i < test_values.size(); i++)
            {
                if (if_error(container_copy.front(), test_values_copy.front()) != Status::OK)
                {
                    return Status::Error;
                }
                container_copy.pop();
                test_values_copy.pop();
            }
        }
        else
        {
            std::cout << "No constexpr condition was used for elements comparison of queue\n";
            return Status::Error;
        }

        return Status::OK;
    }

    /**
     * @brief Function iterates over input container elements to check if they are equal
     *
     * @tparam T type of input container
     * @tparam U type of input container with expected content
     * @param[in] container input container
     * @param[in] test_values input container with expected content
     * @return flag if elements of compared containers are equal
     */
    template<typename T, typename U>
    auto compare_elements(const T& container, const U& test_values) -> Status
    {
        if constexpr (has_ranges<T> && has_ranges<U>)
        {
            if (compare_elements_ranges(container, test_values) == Status::Error)
            {
                return Status::Error;
            }
        }
        else if constexpr (has_top<T> && has_pop<T>)
        {

            if (compare_elements_stack(container, test_values) == Status::Error)
            {
                return Status::Error;
            }
        }
        else if constexpr (has_front<T> && has_pop<T>)
        {
            if (compare_elements_queue(container, test_values) == Status::Error)
            {
                return Status::Error;
            }
        }
        else
        {
            std::cout << "No constexpr condition was used for elements comparison\n";
            return Status::Error;
        }

        return Status::OK;
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
    auto cmp(const T& val1, const T& val2) -> Status
    {
        tests::total_count()++;
        return if_error(val1, val2);
    }

    /**
     * @brief Function compares values of class supporting ranges iterators and initializer list.
     *        Both classes must use the same underlying data type.
     *
     * @tparam T type of class
     * @tparam U type of underlying data type
     * @param[in] container input list
     * @param[in] test_values input initializer list
     * @return true if compared containers are different
     * @return false if containers are equal
     */
    template<typename T, typename U>
    auto cmp(const T& container, const std::initializer_list<U>& test_values) -> Status
    {
        if (compare_size(container, test_values) != Status::OK)
        {
            return Status::Error;
        }

        if constexpr (std::ranges::bidirectional_range<T>)
        {
            std::vector<U> forward{};
            for (const auto& item : container)
            {
                forward.push_back(item);
            }

            std::vector<U> backward{};
            for (const auto& item : std::views::reverse(container))
            {
                backward.push_back(item);
            }

            std::reverse(backward.begin(), backward.end());
            if (forward == backward)
            {
                std::cout << "Forward and backward content OK\n";
            }
            if (forward != backward)
            {
                std::cout << "Forward and backward content of container is different!\n";
                return Status::Error;
            }
        }

        if (compare_elements(container, test_values) != Status::OK)
        {
            return Status::Error;
        }

        return Status::OK;
    }

    /**
     * @brief Function compares values of two classes
     *
     * @tparam T type of input container
     * @tparam U type of input container with expected content
     * @param[in] container input container
     * @param[in] test_values input container with expected content
     * @return true if compared containers are different
     * @return false if containers are equal
     */
    template<typename T, typename U>
    auto cmp(const T& container, const U& test_values) -> Status
    {
        if (compare_size(container, test_values) != Status::OK)
        {
            return Status::Error;
        }

        if constexpr (std::ranges::bidirectional_range<T>)
        {
            std::vector<T> forward{};
            for (const auto& item : container)
            {
                forward.push_back(item);
            }

            std::vector<T> backward{};
            for (const auto& item : std::views::reverse(container))
            {
                backward.push_back(item);
            }

            std::reverse(backward.begin(), backward.end());
            if (forward == backward)
            {
                std::cout << "Forward and backward content OK\n";
            }
            if (forward != backward)
            {
                std::cout << "Forward and backward content of container is different!\n";
                return Status::Error;
            }
        }

        if (compare_elements(container, test_values) != Status::OK)
        {
            return Status::Error;
        }

        return Status::OK;
    }

    /**
     * @brief Function compares values of Array and array
     *
     * @tparam T type of elements to compare
     * @tparam N number of elements in Array
     * @param[in] array input Array
     * @param[in] test_values input array
     * @return true if compared containers are different
     * @return false if containers are equal
     */
    template<typename T, size_t N>
    auto cmp(const dsa::Array<T, N>& array, const std::array<T, N>& test_values) -> Status
    {
        if (compare_size(array, test_values) != Status::OK)
        {
            return Status::Error;
        }

        if constexpr (std::ranges::bidirectional_range<dsa::Array<T, N>>)
        {
            std::vector<T> forward{};
            for (const auto& item : array)
            {
                forward.push_back(item);
            }

            std::vector<T> backward{};
            for (const auto& item : std::views::reverse(array))
            {
                backward.push_back(item);
            }

            std::reverse(backward.begin(), backward.end());
            if (forward == backward)
            {
                std::cout << "Forward and backward content OK\n";
            }
            if (forward != backward)
            {
                std::cout << "Forward and backward content of container is different!\n";
                return Status::Error;
            }
        }

        if (compare_elements(array, test_values) != Status::OK)
        {
            return Status::Error;
        }

        return Status::OK;
    }

    /**
     * @brief Function compares values of Array and vector
     *
     * @tparam T type of elements to compare
     * @tparam N number of elements in Array
     * @param[in] array input Array
     * @param[in] test_values input vector
     * @return true if compared containers are different
     * @return false if containers are equal
     */
    template<typename T, size_t N>
    auto cmp(const dsa::Array<T, N>& array, const std::vector<T>& test_values) -> Status
    {
        if (compare_size(array, test_values) != Status::OK)
        {
            return Status::Error;
        }

        if constexpr (std::ranges::bidirectional_range<dsa::Array<T, N>>)
        {
            std::vector<T> forward{};
            for (const auto& item : array)
            {
                forward.push_back(item);
            }

            std::vector<T> backward{};
            for (const auto& item : std::views::reverse(array))
            {
                backward.push_back(item);
            }

            std::reverse(backward.begin(), backward.end());
            if (forward == backward)
            {
                std::cout << "Forward and backward content OK\n";
            }
            if (forward != backward)
            {
                std::cout << "Forward and backward content of container is different!\n";
                return Status::Error;
            }
        }

        if (compare_elements(array, test_values) != Status::OK)
        {
            return Status::Error;
        }

        return Status::OK;
    }

    /**
     * @brief Function compares values of List and list
     *
     * @tparam T type of elements to compare
     * @param[in] list input container
     * @param[in] test_values input expected values
     * @return true if compared containers are different
     * @return false if containers are equal
     */
    template<typename T>
    auto cmp(const dsa::List<T>& list, const std::list<T>& test_values) -> Status
    {
        if (compare_size(list, test_values) != Status::OK)
        {
            return Status::Error;
        }

        if constexpr (std::ranges::bidirectional_range<dsa::List<T>>)
        {
            std::vector<T> forward{};
            for (const auto& item : list)
            {
                forward.push_back(item);
            }

            std::vector<T> backward{};
            for (const auto& item : std::views::reverse(list))
            {
                backward.push_back(item);
            }

            std::reverse(backward.begin(), backward.end());
            if (forward == backward)
            {
                std::cout << "Forward and backward content OK\n";
            }
            if (forward != backward)
            {
                std::cout << "Forward and backward content of container is different!\n";
                return Status::Error;
            }
        }

        if (compare_elements(list, test_values) != Status::OK)
        {
            return Status::Error;
        }

        return Status::OK;
    }

    /**
     * @brief Function compares values of Vector and vector
     *
     * @tparam T type of elements to compare
     * @param[in] vector input Vector
     * @param[in] test_values input vector
     * @return true if compared containers are different
     * @return false if containers are equal
     */
    template<typename T>
    auto cmp(const dsa::Vector<T>& vector, const std::vector<T>& test_values) -> Status
    {
        if (compare_size(vector, test_values) != Status::OK)
        {
            return Status::Error;
        }

        if constexpr (std::ranges::bidirectional_range<dsa::Vector<T>>)
        {
            std::vector<T> forward{};
            for (const auto& item : vector)
            {
                forward.push_back(item);
            }

            std::vector<T> backward{};
            for (const auto& item : std::views::reverse(vector))
            {
                backward.push_back(item);
            }

            std::reverse(backward.begin(), backward.end());
            if (forward == backward)
            {
                std::cout << "Forward and backward content OK\n";
            }
            if (forward != backward)
            {
                std::cout << "Forward and backward content of container is different!\n";
                return Status::Error;
            }
        }

        if (compare_elements(vector, test_values) != Status::OK)
        {
            return Status::Error;
        }

        return Status::OK;
    }

    /**
     * @brief Function overloads out operator to print all elements of iterable not-string-like type
     *
     * @tparam T type of not-string-like type
     * @param[in,out] out reference to output stream
     * @param[in] container input container of type T
     * @return std::ostream&
     */
    template<typename T>
        requires has_printable_range<T>
    auto operator<<(std::ostream& out, const T& container) -> std::ostream&
    {
        for (const auto& item : container)
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
     * @brief Function print PASS or FAIL message
     *
     * @param[in] status result of comparison containers or values
     */
    inline void print_status(Status status)
    {
        if (status == Status::OK)
        {
            std::cout << "PASS\n\n";
        }
        else
        {
            std::cout << "FAIL\n\n";
        }
    }

    /**
     * @brief Function handle tests results
     *
     * @param[in] status result of comparison containers or values
     */
    inline void result(Status status)
    {
        if (status != Status::OK)
        {
            tests::failed_count()++;
        }
        print_status(status);
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
    void compare(const std::string& container_name, const T& container, const U& expected)
    {
        print_containers(container_name, container, "Expected", expected);
        const Status res = cmp(container, expected);
        result(res);
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
        const Status res = cmp(container, expected);
        print_status(res);
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
        const Status res = cmp(val1, val2);
        print_status(res);
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
    auto compare(T val1, T val2) -> Status
    {
        return cmp(val1, val2);
    }
}

#endif // !COMMON_H
