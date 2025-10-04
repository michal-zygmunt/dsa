/**
 * @file Stack.h
 * @brief This file contains implementation of Stack class
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#ifndef STACK_H
#define STACK_H

#include "List.h"

#include <initializer_list>
#include <iostream>
#include <utility>

namespace dsa
{

    /**
     * @brief Implements Stack class using Node with pointer to next element
     *
     * @tparam T type of data stored in Stack Node
     */
    template<typename T>
    class Stack
    {
    public:

        /**
         * @brief Alias for data type used in class
         *
         * @tparam T data type
         */
        using value_type = T;

        /**
         * @brief Alias for reference to data type used in class
         *
         * @tparam T& reference to data type
         */
        using reference = T&;

        /**
         * @brief Alias for const reference to data type used in class
         *
         * @tparam T& const reference to data type
         */
        using const_reference = const T&;

        /**
         * @brief Construct a new Stack object
         *
         */
        Stack() = default;

        /**
         * @brief Construct a new Stack object using value of type T
         *
         * @param[in] value of type T
         */
        Stack(T value);

        /**
         * @brief Construct a new Stack object using initializer list
         *
         * @param[in] init_list initializer list of values of type T
         */
        Stack(const std::initializer_list<T>& init_list);

        /**
         * @brief Construct a new Stack object using copy constructor
         *
         * @param[in] other Stack object of type T
         */
        Stack(const Stack<T>& other);

        /**
         * @brief Constructs Stack using copy assignment
         *
         * @param[in] other Stack object of type T
         * @return Stack& reference to Stack object
         */
        auto operator=(const Stack<T>& other) -> Stack&;

        /**
         * @brief Construct a new Stack object using move constructor
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other Stack object of type T
         */
        Stack(Stack<T>&& other) noexcept;

        /**
         * @brief Assign Stack object using move assignment
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other Stack object of type T
         * @return Stack& reference to Stack object
         */
        auto operator=(Stack<T>&& other) noexcept -> Stack&;

        /**
         * @brief Destroy the Stack object
         */
        ~Stack() = default;

        /**
         * @brief Function returns pointer to Stack top element
         *
         * @return T& reference to Stack top element
         */
        auto top() -> reference;

        /**
         * @brief Function returns pointer to Stack top element
         *
         * @return const T& const_reference to Stack top element
         */
        auto top() const -> const_reference;

        /**
         * @brief Function checks if container has no elements
         *
         * @retval true if container is empty
         * @retval false if container is not empty
         */
        auto empty() const -> bool;

        /**
         * @brief Function returns Stack size
         *
         * @return size_t number of elements in container
         */
        auto size() const -> size_t;

        /**
         * @brief Function add new element at the top of Stack
         *
         * @param[in] value element of type T
         */
        void push(T value);

        /**
         * @brief Function add range of elements at the top of Stack
         *
         * @param[in] init_list range of std::initializer_list elements of type T
         */
        void push_range(const std::initializer_list<T>& init_list);

        /**
         * @brief Function removes the top element of Stack
         */
        void pop();

        /**
         * @brief Function swaps content of two Stack objects
         *
         * @param[in,out] other object to swap content with
         */
        void swap(Stack<T>& other) noexcept;

    private:

        List<T> container{};
    };

    template<typename T>
    Stack<T>::Stack(T value)
    {
        container.push_back(value);
    }

    template<typename T>
    Stack<T>::Stack(const std::initializer_list<T>& init_list)
    {
        for (const auto& item : init_list)
        {
            container.push_back(item);
        }
    }

    template<typename T>
    Stack<T>::Stack(const Stack<T>& other)
    {
        if (other.size() >= 1)
        {
            for (const auto& item : other.container)
            {
                container.push_back(item);
            }
        }
    }

    template<typename T>
    auto Stack<T>::operator=(const Stack<T>& other) -> Stack<T>&
    {
        if (&other != this)
        {
            while (!container.empty())
            {
                container.pop_front();
            }

            for (const auto& item : other.container)
            {
                container.push_back(item);
            }
        }

        return *this;
    }

    template<typename T>
    Stack<T>::Stack(Stack<T>&& other) noexcept
    {
        std::swap(container, other.container);
    }

    template<typename T>
    auto Stack<T>::operator=(Stack<T>&& other) noexcept -> Stack<T>&
    {
        if (&other != this)
        {
            std::swap(container, other.container);
        }

        return *this;
    }

    template<typename T>
    auto Stack<T>::top() -> typename Stack<T>::reference
    {
        return container.back();
    }

    template<typename T>
    auto Stack<T>::top() const -> typename Stack<T>::const_reference
    {
        return container.back();
    }

    template<typename T>
    auto Stack<T>::empty() const -> bool
    {
        return container.size() == 0;
    }

    template<typename T>
    auto Stack<T>::size() const -> size_t
    {
        return container.size();
    }

    template<typename T>
    void Stack<T>::push(T value)
    {
        container.push_back(value);
    }

    template<typename T>
    void Stack<T>::push_range(const std::initializer_list<T>& init_list)
    {
        for (const auto& item : init_list)
        {
            push(item);
        }
    }

    template<typename T>
    void Stack<T>::pop()
    {
        container.pop_back();
    }

    template<typename T>
    void Stack<T>::swap(Stack<T>& other) noexcept
    {
        if (&other != this)
        {
            std::swap(container, other.container);
        }
    }

    /**
     * @brief Overloads operator to print all elements of Stack
     *
     * @tparam T type of initializer list elements
     * @param[in,out] out reference to output stream
     * @param[in] stack Stack to print
     * @return std::ostream& reference to std::ostream
     */
    template<typename T>
    auto operator<<(std::ostream& out, const Stack<T>& stack) -> std::ostream&
    {
        Stack<T> temp{ stack };

        while (!temp.empty())
        {
            out << temp.top() << ' ';
            temp.pop();
        }

        return out;
    }

    /**
     * @brief The relational operator compares two Stack objects
     *
     * @tparam T type of data stored in Stack
     * @param[in] stack1 input container
     * @param[in] stack2 input container
     * @retval true if containers are equal
     * @retval false if containers are not equal
     */
    template<typename T>
    auto operator==(const Stack<T>& stack1, const Stack<T>& stack2) -> bool
    {
        if (stack1.size() != stack2.size())
        {
            return false;
        }

        Stack<T> temp_1{ stack1 };
        Stack<T> temp_2{ stack2 };

        while (!temp_1.empty() && !temp_2.empty())
        {
            if (temp_1.top() != temp_2.top())
            {
                return false;
            }

            temp_1.pop();
            temp_2.pop();
        }

        return true;
    }

    /**
     * @brief The relational operator compares two Stack objects
     *
     * @tparam T type of data stored in Stack
     * @param[in] stack1 input container
     * @param[in] stack2 input container
     * @retval true if containers are not equal
     * @retval false if containers are equal
     */
    template<typename T>
    auto operator!=(const Stack<T>& stack1, const Stack<T>& stack2) -> bool
    {
        return !(operator==(stack1, stack2));
    }

    /**
     * @brief The relational operator compares two Stack objects
     *
     * @tparam T type of data stored in Stack
     * @param[in] stack1 input container
     * @param[in] stack2 input container
     * @retval true if the content of \p stack1 are lexicographically
     *         less than the content of \p stack2
     * @retval false otherwise
     */
    template<typename T>
    auto operator<(const Stack<T>& stack1, const Stack<T>& stack2) -> bool
    {
        Stack<T> temp_1{ stack1 };
        Stack<T> temp_2{ stack2 };

        while (!temp_1.empty() && !temp_2.empty())
        {
            if (temp_1.top() > temp_2.top())
            {
                return false;
            }
            if (temp_1.top() < temp_2.top())
            {
                return true;
            }

            temp_1.pop();
            temp_2.pop();
        }

        // first n elements are equal
        // check sizes
        return stack1.size() < stack1.size();
    }

    /**
     * @brief The relational operator compares two Stack objects
     *
     * @tparam T type of data stored in Stack
     * @param[in] stack1 input container
     * @param[in] stack2 input container
     * @retval true if the content of \p stack1 are lexicographically
     *         greater than the content of \p stack2
     * @retval false otherwise
     */
    template<typename T>
    auto operator>(const Stack<T>& stack1, const Stack<T>& stack2) -> bool
    {
        return operator<(stack2, stack1);
    }

    /**
     * @brief The relational operator compares two Stack objects
     *
     * @tparam T type of data stored in Stack
     * @param[in] stack1 input container
     * @param[in] stack2 input container
     * @retval true if the content of \p stack1 are lexicographically
     *         less or equal than the content of \p stack2
     * @retval false otherwise
     */
    template<typename T>
    auto operator<=(const Stack<T>& stack1, const Stack<T>& stack2) -> bool
    {
        return !(operator>(stack1, stack2));
    }

    /**
     * @brief The relational operator compares two Stack objects
     *
     * @tparam T type of data stored in Stack
     * @param[in] stack1 input container
     * @param[in] stack2 input container
     * @retval true if the content of \p s1 are lexicographically
     *         greater or equal than the content of \p s2
     * @retval false otherwise
     */
    template<typename T>
    auto operator>=(const Stack<T>& stack1, const Stack<T>& stack2) -> bool
    {
        return !(operator<(stack1, stack2));
    }

}
#endif // !STACK_H
