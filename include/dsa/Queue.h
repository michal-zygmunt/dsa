/**
 * @file Queue.h
 * @brief This file contains implementation of Queue class
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"

#include <initializer_list>
#include <iostream>
#include <utility>

namespace dsa
{

    /**
     * @brief Implements Queue class using List as underlaying data structore
     *
     * @tparam T type of data stored in Queue
     */
    template<typename T>
    class Queue
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
         * @brief Construct a new Queue object
         *
         */
        Queue() = default;

        /**
         * @brief Construct a new Queue object using value of type T
         *
         * @param[in] value of type T
         */
        Queue(T value);

        /**
         * @brief Construct a new Queue object using initializer list
         *
         * @param[in] il initializer list of values of type T
         */
        Queue(const std::initializer_list<T>& il);

        /**
         * @brief Construct a new Queue object using copy constructor
         *
         * @param[in] other Queue object of type T
         */
        Queue(const Queue<T>& other);

        /**
         * @brief Constructs Queue using copy assignment
         *
         * @param[in] other Queue object of type T
         * @return Queue& reference to Queue object
         */
        Queue& operator=(const Queue<T>& other);

        /**
         * @brief Construct a new Queue object using move constructor
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other Queue object of type T
         */
        Queue(Queue<T>&& other) noexcept;

        /**
         * @brief Assign Queue object using move assignment
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other Queue object of type T
         * @return Queue& reference to Queue object
         */
        Queue& operator=(Queue<T>&& other) noexcept;

        /**
         * @brief Destroy the Queue object
         */
        ~Queue() = default;

        /**
         * @brief Function returns pointer to Queue first object
         *
         * @return T& reference to Queue first object
         */
        reference front();

        /**
         * @brief Function returns pointer to Queue first object
         *
         * @return const T& const reference to Queue first object
         */
        const_reference front() const;

        /**
         * @brief Function returns pointer to Queue last object
         *
         * @return T& reference to Queue last object
         */
        reference back();

        /**
         * @brief Function returns pointer to Queue last object
         *
         * @return const T& const reference to Queue last object
         */
        const_reference back() const;

        /**
         * @brief Function checks if container has no elements
         *
         * @retval true if container is empty
         * @retval false if container is not empty
         */
        bool empty() const;

        /**
         * @brief Function returns Queue size
         *
         * @return size_t number of elements in container
         */
        size_t size() const;

        /**
         * @brief Function add new element at the end of Queue
         *
         * @param[in] value element of type T
         */
        void push(const_reference value);

        /**
         * @brief Function add new element at the end of Queue
         *
         * @param[in] value element of type T
         */
        void push(T&& value);

        /**
         * @brief Function add range of elements at the end of Queue
         *
         * @param[in] il range of std::initializer_list elements of type T
         */
        void push_range(const std::initializer_list<T>& il);

        /**
         * @brief Function removes the first element of Queue
         */
        void pop();

        /**
         * @brief Function swaps content of two Queue objects
         *
         * @param[in,out] other object to swap content with
         */
        void swap(Queue<T>& other) noexcept;

        /**
         * @brief Function add range of elements at the end of Queue
         *
         * @param[in] other Queue to read elements from
         * @return Queue<T>& reference to Queue
         */
        Queue<T>& operator+=(const Queue<T>& other);

        /**
        * @brief Function add range of elements at the end of Queue
        *
        * @param[in] other std::initializer_list to read elements from
        * @return Queue<T>& reference to Queue
        */
        Queue<T>& operator+=(const std::initializer_list<T>& other);

    private:

        List<T> container{};
    };

    template<typename T>
    Queue<T>::Queue(T value)
    {
        container.push_back(value);
    }

    template<typename T>
    Queue<T>::Queue(const std::initializer_list<T>& il)
    {
        for (const auto& item : il)
        {
            container.push_back(item);
        }
    }

    template<typename T>
    Queue<T>::Queue(const Queue<T>& other)
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
    Queue<T>& Queue<T>::operator=(const Queue<T>& other)
    {
        if (&other != this)
        {
            while (container.size())
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
    Queue<T>::Queue(Queue<T>&& other) noexcept
    {
        container = std::move(other.container);
    }

    template<typename T>
    Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept
    {
        if (&other != this)
        {
            container = std::move(other.container);
        }

        return *this;
    }

    template<typename T>
    typename Queue<T>::reference Queue<T>::front()
    {
        return container.front();
    }

    template<typename T>
    typename Queue<T>::const_reference Queue<T>::front() const
    {
        return container.front();
    }

    template<typename T>
    typename Queue<T>::reference Queue<T>::back()
    {
        return container.back();
    }

    template<typename T>
    typename Queue<T>::const_reference Queue<T>::back() const
    {
        return container.back();
    }

    template<typename T>
    bool Queue<T>::empty() const
    {
        return container.size() == 0;
    }

    template<typename T>
    size_t Queue<T>::size() const
    {
        return container.size();
    }

    template<typename T>
    void Queue<T>::push(const_reference value)
    {
        container.push_back(value);
    }

    template<typename T>
    void Queue<T>::push(T&& value)
    {
        container.push_back(std::move(value));
    }

    template<typename T>
    void Queue<T>::push_range(const std::initializer_list<T>& il)
    {
        for (const auto& item : il)
        {
            push(item);
        }
    }

    template<typename T>
    void Queue<T>::pop()
    {
        container.pop_front();
    }

    template<typename T>
    void Queue<T>::swap(Queue<T>& other) noexcept
    {
        if (&other != this)
        {
            std::swap(container, other.container);
        }
    }

    template<typename T>
    Queue<T>& Queue<T>::operator+=(const Queue<T>& other)
    {
        for (const auto& i : other.container)
        {
            push(i);
        }

        return *this;
    }

    template<typename T>
    Queue<T>& Queue<T>::operator+=(const std::initializer_list<T>& il)
    {
        push_range(il);

        return *this;
    }

    /**
     * @brief Overloads operator to print all elements of Queue
     *
     * @tparam T type of initializer list elements
     * @param[in,out] out reference to output stream
     * @param[in] queue Queue to print
     * @return std::ostream& reference to std::ostream
     */
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Queue<T>& queue)
    {
        Queue<T> temp{ queue };

        while (temp.size())
        {
            out << temp.front() << ' ';
            temp.pop();
        }

        return out;
    }

    /**
     * @brief The relational operator compares two Queue objects
     *
     * @tparam T type of data stored in Queue
     * @param[in] q1 input container
     * @param[in] q2 input container
     * @retval true if containers are equal
     * @retval false if containers are not equal
     */
    template<typename T>
    bool operator==(const Queue<T>& q1, const Queue<T>& q2)
    {
        if (q1.size() != q2.size())
        {
            return false;
        }

        Queue<T> temp_1{ q1 };
        Queue<T> temp_2{ q2 };

        while (temp_1.size() && temp_2.size())
        {
            if (temp_1.front() != temp_2.front())
            {
                return false;
            }

            temp_1.pop();
            temp_2.pop();
        }

        return true;
    }

    /**
     * @brief The relational operator compares two Queue objects
     *
     * @tparam T type of data stored in Queue
     * @param[in] q1 input container
     * @param[in] q2 input container
     * @retval true if containers are not equal
     * @retval false if containers are equal
     */
    template<typename T>
    bool operator!=(const Queue<T>& q1, const Queue<T>& q2)
    {
        return !(operator==(q1, q2));
    }

    /**
     * @brief The relational operator compares two Queue objects
     *
     * @tparam T type of data stored in Queue
     * @param[in] q1 input container
     * @param[in] q2 input container
     * @retval true if the content of \p q1 are lexicographically
     *         less than the content of \p q2
     * @retval false otherwise
     */
    template<typename T>
    bool operator<(const Queue<T>& q1, const Queue<T>& q2)
    {
        Queue<T> temp_1{ q1 };
        Queue<T> temp_2{ q2 };

        while (temp_1.size() && temp_2.size())
        {
            if (temp_1.front() >= temp_2.front())
            {
                return false;
            }

            temp_1.pop();
            temp_2.pop();
        }

        return true;
    }

    /**
     * @brief The relational operator compares two Queue objects
     *
     * @tparam T type of data stored in Queue
     * @param[in] q1 input container
     * @param[in] q2 input container
     * @retval true if the content of \p q1 are lexicographically
     *         greater than the content of \p q2
     * @retval false otherwise
     */
    template<typename T>
    bool operator>(const Queue<T>& q1, const Queue<T>& q2)
    {
        return operator<(q2, q1);
    }

    /**
     * @brief The relational operator compares two Queue objects
     *
     * @tparam T type of data stored in Queue
     * @param[in] q1 input container
     * @param[in] q2 input container
     * @retval true if the content of \p q1 are lexicographically
     *         less or equal than the content of \p q2
     * @retval false otherwise
     */
    template<typename T>
    bool operator<=(const Queue<T>& q1, const Queue<T>& q2)
    {
        return !(operator>(q1, q2));
    }

    /**
     * @brief The relational operator compares two Queue objects
     *
     * @tparam T type of data stored in Queue
     * @param[in] q1 input container
     * @param[in] q2 input container
     * @retval true if the content of \p q1 are lexicographically
     *         greater or equal than the content of \p q2
     * @retval false otherwise
     */
    template<typename T>
    bool operator>=(const Queue<T>& q1, const Queue<T>& q2)
    {
        return !(operator<(q1, q2));
    }

}
#endif // !QUEUE_H
