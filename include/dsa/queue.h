/**
 * @file queue.h
 * @brief This file contains implementation of Queue class
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

#include <initializer_list>
#include <iostream>
#include <utility>

namespace dsa
{
    template<typename T>
    class Queue;

    template<typename T>
    auto operator==(const Queue<T>& lhs, const Queue<T>& rhs) -> bool;

    template<typename T>
    auto operator<=>(const Queue<T>& lhs, const Queue<T>& rhs)->std::compare_three_way_result_t<T>;

    /**
     * @brief Implements Queue class
     *
     * @tparam T type of data stored in Queue
     *
     * @todo add non-member specialized swap function
     */
    template<typename T>
    class Queue
    {
    public:

        /**
         * @brief Alias for underlying container type used in class
         *
         * @tparam T data type
         */
        using Container = List<T>;

        /**
         * @brief Alias for data type used in class
         *
         * @tparam T data type
         */
        using value_type = Container::value_type;

        /**
         * @brief Alias for size type used in class
         *
         * @tparam T size type
         */
        using size_type = Container::size_type;

        /**
         * @brief Alias for reference to data type used in class
         *
         * @tparam T& reference to data type
         */
        using reference = Container::reference;

        /**
         * @brief Alias for const reference to data type used in class
         *
         * @tparam T& const reference to data type
         */
        using const_reference = Container::const_reference;

        /**
         * @brief Construct a new Queue object
         *
         */
        Queue();

        /**
         * @brief Construct a new Queue object from base Container using copy constructor
         *
         * @param[in] cont object of type Container
         */
        explicit Queue(const Container& cont);

        /**
         * @brief Construct a new Queue object from base Container using move constructor
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] cont Queue object of type Container
         */
        explicit Queue(Container&& cont) noexcept;

        /**
         * @brief Construct a new Queue object using copy constructor
         *
         * @param[in] other Queue object of type T
         */
        Queue(const Queue<T>& other);

        /**
         * @brief Construct a new Queue object using move constructor
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other Queue object of type T
         */
        Queue(Queue<T>&& other) noexcept;

        /**
         * @brief Constructs Queue using copy assignment
         *
         * @param[in] other Queue object of type T
         * @return Queue& reference to Queue object
         */
        auto operator=(const Queue<T>& other) -> Queue&;

        /**
         * @brief Assign Queue object using move assignment
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other Queue object of type T
         * @return Queue& reference to Queue object
         */
        auto operator=(Queue<T>&& other) noexcept -> Queue&;

        /**
         * @brief Destroy the Queue object
         */
        ~Queue() = default;

        /**
         * @brief Function returns pointer to Queue first object
         *
         * @return T& reference to Queue first object
         */
        auto front() -> reference;

        /**
         * @brief Function returns pointer to Queue first object
         *
         * @return const T& const reference to Queue first object
         */
        [[nodiscard]] auto front() const -> const_reference;

        /**
         * @brief Function returns pointer to Queue last object
         *
         * @return T& reference to Queue last object
         */
        auto back() -> reference;

        /**
         * @brief Function returns pointer to Queue last object
         *
         * @return const T& const reference to Queue last object
         */
        [[nodiscard]] auto back() const -> const_reference;

        /**
         * @brief Function checks if container has no elements
         *
         * @retval true if container is empty
         * @retval false if container is not empty
         */
        [[nodiscard]] auto empty() const -> bool;

        /**
         * @brief Function returns Queue size
         *
         * @return size_t number of elements in container
         */
        [[nodiscard]] auto size() const -> size_t;

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
        void push(value_type&& value);

        /**
         * @brief Insert new element to the end of the container
         * @details The element is constructed in-place, i.e. no copy or move operations are performed
         *
         * @tparam ...Args
         * @param[in] ...args args arguments to forward to the constructor of the element
         * @return reference to the emplaced element
         */
        template<typename... Args>
        auto emplace(Args&&... args) -> decltype(auto);

        /**
         * @brief Function removes the first element of Queue
         */
        void pop();

        /**
         * @brief Function swaps content of two Queue objects
         *
         * @param[in,out] other object to swap content with
         */
        void swap(Queue<T>& other) noexcept(std::is_nothrow_swappable_v<Container>);

        /**
         * @brief Function add range of elements at the end of Queue
         *
         * @param[in] other Queue to read elements from
         * @return Queue<T>& reference to Queue
         */
        auto operator+=(const Queue<T>& other) -> Queue<T>&;

        /**
        * @brief Function add range of elements at the end of Queue
        *
        * @param[in] init_list std::initializer_list to read elements from
        * @return Queue<T>& reference to Queue
        */
        auto operator+=(const std::initializer_list<T>& init_list) -> Queue<T>&;

    private:

        /**
         * @brief Forward friend declaration to access internal container comparison operator
         */
        friend auto operator==<T>(const Queue<T>& lhs, const Queue<T>& rhs) -> bool;

        /**
         * @brief Forward friend declaration to access internal container comparison operator
         */
        friend auto operator<=><T>(const Queue<T>& lhs, const Queue<T>& rhs)->std::compare_three_way_result_t<T>;

        Container container{};
    };

    template<typename T>
    Queue<T>::Queue()
        : Queue(Container())
    {}

    template<typename T>
    Queue<T>::Queue(const Container& cont)
    {
        for (const auto& item : cont)
        {
            container.push_back(item);
        }
    }

    template<typename T>
    Queue<T>::Queue(Container&& cont) noexcept
        : container{ std::move(cont) }
    {}

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
    Queue<T>::Queue(Queue<T>&& other) noexcept
        : container{ std::move(other.container) }
    {}

    template<typename T>
    auto Queue<T>::operator=(const Queue<T>& other) -> Queue<T>&
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
    auto Queue<T>::operator=(Queue<T>&& other) noexcept -> Queue<T>&
    {
        if (&other != this)
        {
            container = std::move(other.container);
        }

        return *this;
    }

    template<typename T>
    auto Queue<T>::front() -> typename Queue<T>::reference
    {
        return container.front();
    }

    template<typename T>
    auto Queue<T>::front() const -> typename Queue<T>::const_reference
    {
        return container.front();
    }

    template<typename T>
    auto Queue<T>::back() -> typename Queue<T>::reference
    {
        return container.back();
    }

    template<typename T>
    auto Queue<T>::back() const -> typename Queue<T>::const_reference
    {
        return container.back();
    }

    template<typename T>
    auto Queue<T>::empty() const -> bool
    {
        return container.size() == 0;
    }

    template<typename T>
    auto Queue<T>::size() const -> size_t
    {
        return container.size();
    }

    template<typename T>
    void Queue<T>::push(const_reference value)
    {
        container.push_back(value);
    }

    template<typename T>
    void Queue<T>::push(value_type&& value)
    {
        container.push_back(std::move(value));
    }

    template<typename T>
    template<typename... Args>
    auto Queue<T>::emplace(Args&&... args) -> decltype(auto)
    {
        container.emplace_back(std::forward<Args>(args)...);
        return back();
    }

    template<typename T>
    void Queue<T>::pop()
    {
        container.pop_front();
    }

    template<typename T>
    void Queue<T>::swap(Queue<T>& other) noexcept(std::is_nothrow_swappable_v<Container>)
    {
        std::swap(container, other.container);
    }

    template<typename T>
    auto Queue<T>::operator+=(const Queue<T>& other) -> Queue<T>&
    {
        for (const auto& item : other.container)
        {
            push(item);
        }

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
    auto operator<<(std::ostream& out, const Queue<T>& queue) -> std::ostream&
    {
        Queue<T> temp{ queue };

        while (!temp.empty())
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
     * @param[in] lhs input container
     * @param[in] rhs input container
     * @retval true if containers are equal
     * @retval false if containers are not equal
     */
    template<typename T>
    auto operator==(const Queue<T>& lhs, const Queue<T>& rhs) -> bool
    {
        return lhs.container == rhs.container;
    }

    /**
     * @brief The relational operator compares two Queue objects
     *
     * Depending on type T, function returns one of following objects:
     * std::strong_ordering::less / equal / greater
     * std::weak_ordering::less / equivalent / greater
     * std::partial_ordering::less / equivalent / greater / unordered
     * It is best to compare results with 0 to determine if lhs is <, >, or == to rhs
     *
     * @param[in] lhs input container
     * @param[in] rhs input container
     * @return three way comparison result type
     */
    template<typename T>
    auto operator<=>(const Queue<T>& lhs, const Queue<T>& rhs) -> std::compare_three_way_result_t<T>
    {
        return lhs.container <=> rhs.container;
    }
}
#endif // !QUEUE_H
