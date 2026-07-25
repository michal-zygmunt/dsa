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
#include "vector.h"

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
    auto operator<=>(const Queue<T>& lhs, const Queue<T>& rhs) -> std::compare_three_way_result_t<T>;

    /**
     * @brief Implements Queue class
     *
     * @tparam T type of data stored in Queue
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
        [[nodiscard]] auto front() -> reference;

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
        [[nodiscard]] auto back() -> reference;

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

    private:

        /**
         * @brief Forward friend declaration to access internal container comparison operator
         */
        friend auto operator== <T>(const Queue<T>& lhs, const Queue<T>& rhs) -> bool;

        /**
         * @brief Forward friend declaration to access internal container comparison operator
         */
        friend auto operator<=> <T>(const Queue<T>& lhs, const Queue<T>& rhs) -> std::compare_three_way_result_t<T>;

        Container container{};
    };

    template<typename T>
    Queue<T>::Queue()
        : Queue(Container())
    {
    }

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
    {
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
    Queue<T>::Queue(Queue<T>&& other) noexcept
        : container{ std::move(other.container) }
    {
    }

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
    auto Queue<T>::front() -> Queue<T>::reference
    {
        return container.front();
    }

    template<typename T>
    auto Queue<T>::front() const -> Queue<T>::const_reference
    {
        return container.front();
    }

    template<typename T>
    auto Queue<T>::back() -> Queue<T>::reference
    {
        return container.back();
    }

    template<typename T>
    auto Queue<T>::back() const -> Queue<T>::const_reference
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

    /**
     * @brief Exchanges content of two Queue containers
     *
     * @tparam T data type stored in containers
     * @param[in] lhs container to swap content
     * @param[in] rhs container to swap content
     */
    template<typename T>
    void swap(Queue<T>& lhs, Queue<T>& rhs) noexcept(noexcept(lhs.swap(rhs)))
    {
        lhs.swap(rhs);
    }
} // namespace dsa

namespace dsa
{
    /**
     * @brief Implements PriorityQueue class
     *
     * @tparam T type of data stored in PriorityQueue
     * @tparam Container type of underlying container used in class
     * @tparam Compare type of comparison used in class
     */
    template<typename T, typename Container = dsa::Vector<T>,
        typename Compare = std::less<typename Container::value_type>>
    class PriorityQueue
    {
    public:

        /**
         * @brief Alias for underlying container type used in class
         *
         * @tparam T data type
         */
        using container_type = Container;

        /**
         * @brief Alias for comparison type used in class
         *
         * @tparam T data type
         */
        using value_compare = Compare;

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
         * @brief Construct a new PriorityQueue object
         *
         */
        PriorityQueue();

        /**
         * @brief Construct a new PriorityQueue object from base Container using copy constructor
         *
         * @param[in] cont object of type Container
         */
        explicit PriorityQueue(const Compare& compare);

        /**
         * @brief Construct a new PriorityQueue object from base Container using move constructor
         *
         * @param[in,out] cont PriorityQueue object of type Container
         */
        PriorityQueue(const Compare& compare, const Container& cont);

        /**
         * @brief Construct a new PriorityQueue object from base Container using move constructor
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] cont PriorityQueue object of type Container
         */
        PriorityQueue(const Compare& compare, Container&& cont) noexcept;

        /**
         * @brief Construct a new PriorityQueue object using copy constructor
         *
         * @param[in] other PriorityQueue object of type T
         */
        PriorityQueue(const PriorityQueue& other);

        /**
         * @brief Construct a new PriorityQueue object using move constructor
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other PriorityQueue object of type T
         */
        PriorityQueue(PriorityQueue&& other) noexcept;

        /**
         * @brief Construct a new PriorityQueue object using elements from range [ \p first , \p last )
         *
         * @tparam InputIt
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         * @param[in] compare comparison function object
         */
        template<typename InputIt>
            requires std::input_iterator<InputIt>
        PriorityQueue(InputIt first, InputIt last, const Compare& compare = Compare());

        /**
         * @brief Construct a new PriorityQueue object using \p cont and elements from range [ \p first , \p last )
         *
         * @tparam InputIt
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         * @param[in] compare comparison function object
         * @param[in] cont source container to which elements in range [\p first, \p last) will be inserted
         */
        template<typename InputIt>
            requires std::input_iterator<InputIt>
        PriorityQueue(InputIt first, InputIt last, const Compare& compare, const Container& cont);

        /**
         * @brief Construct a new PriorityQueue object using \p cont and elements from range [ \p first , \p last )
         * @details Content of \p cont object will be taken by constructed object
         *
         * @tparam InputIt
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         * @param[in] compare comparison function object
         * @param[in] cont source container to which elements in range [\p first, \p last) will be inserted
         */
        template<typename InputIt>
            requires std::input_iterator<InputIt>
        PriorityQueue(InputIt first, InputIt last, const Compare& compare, Container&& cont);

        /**
         * @brief Constructs PriorityQueue using copy assignment
         *
         * @param[in] other PriorityQueue object of type T
         * @return PriorityQueue& reference to PriorityQueue object
         */
        auto operator=(const PriorityQueue& other) -> PriorityQueue&;

        /**
         * @brief Assign PriorityQueue object using move assignment
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other PriorityQueue object of type T
         * @return PriorityQueue& reference to PriorityQueue object
         */
        auto operator=(PriorityQueue&& other) noexcept -> PriorityQueue&;

        /**
         * @brief Destroy the PriorityQueue object
         */
        ~PriorityQueue() = default;

        /**
         * @brief Function returns pointer to PriorityQueue top element
         *
         * @return const T& const_reference to PriorityQueue top element
         */
        [[nodiscard]] auto top() const -> const_reference;

        /**
         * @brief Function checks if container has no elements
         *
         * @retval true if container is empty
         * @retval false if container is not empty
         */
        [[nodiscard]] auto empty() const -> bool;

        /**
         * @brief Function returns PriorityQueue size
         *
         * @return size_t number of elements in container
         */
        [[nodiscard]] auto size() const -> size_type;

        /**
         * @brief Function add new element at the end of PriorityQueue
         *
         * @param[in] value element of type T
         */
        void push(const_reference value);

        /**
         * @brief Function add new element at the end of PriorityQueue
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
         */
        template<typename... Args>
        void emplace(Args&&... args);

        /**
         * @brief Function removes the first element of PriorityQueue
         */
        void pop();

        /**
         * @brief Function swaps content of two PriorityQueue objects
         *
         * @param[in,out] other object to swap content with
         */
        void swap(PriorityQueue& other) noexcept(
            std::is_nothrow_swappable_v<Container> && std::is_nothrow_swappable_v<Compare>);

    private:

        Compare comp{};

        Container container{};
    };

    template<typename T, typename Container, typename Compare>
    PriorityQueue<T, Container, Compare>::PriorityQueue()
        : PriorityQueue(Compare(), Container())
    {
    }

    template<typename T, typename Container, typename Compare>
    PriorityQueue<T, Container, Compare>::PriorityQueue(const Compare& compare)
        : PriorityQueue(compare, Container())
    {
    }

    template<typename T, typename Container, typename Compare>
    PriorityQueue<T, Container, Compare>::PriorityQueue(const Compare& compare, const Container& cont)
        : comp{ compare }
    {
        for (const auto& item : cont)
        {
            container.push_back(item);
        }
        std::make_heap(container.begin(), container.end(), comp);
    }

    template<typename T, typename Container, typename Compare>
    PriorityQueue<T, Container, Compare>::PriorityQueue(const Compare& compare, Container&& cont) noexcept
        : comp{ compare },
          container{ std::move(cont) }
    {
    }

    template<typename T, typename Container, typename Compare>
    PriorityQueue<T, Container, Compare>::PriorityQueue(const PriorityQueue& other)
        : PriorityQueue(Compare(), other.container)
    {
    }

    template<typename T, typename Container, typename Compare>
    PriorityQueue<T, Container, Compare>::PriorityQueue(PriorityQueue<T, Container, Compare>&& other) noexcept
        : PriorityQueue(Compare(), std::move(other.container))
    {
    }

    template<typename T, typename Container, typename Compare>
    template<typename InputIt>
        requires std::input_iterator<InputIt>
    PriorityQueue<T, Container, Compare>::PriorityQueue(InputIt first, InputIt last, const Compare& compare)
        : comp{ compare }
    {
        container.assign(first, last);
        std::make_heap(container.begin(), container.end(), comp);
    }

    template<typename T, typename Container, typename Compare>
    template<typename InputIt>
        requires std::input_iterator<InputIt>
    PriorityQueue<T, Container, Compare>::PriorityQueue(InputIt first, InputIt last, const Compare& compare,
        const Container& cont)
        : comp{ compare },
          container{ std::move(cont) }
    {
        container.insert(container.end(), first, last);
        std::make_heap(container.begin(), container.end(), comp);
    }

    template<typename T, typename Container, typename Compare>
    template<typename InputIt>
        requires std::input_iterator<InputIt>
    PriorityQueue<T, Container, Compare>::PriorityQueue(InputIt first, InputIt last, const Compare& compare,
        Container&& cont)
        : comp{ compare },
          container{ std::move(cont) }
    {
        container.insert(container.end(), first, last);
        std::make_heap(container.begin(), container.end(), comp);
    }

    template<typename T, typename Container, typename Compare>
    auto PriorityQueue<T, Container, Compare>::operator=(const PriorityQueue& other) -> PriorityQueue&
    {
        if (&other != this)
        {
            comp = other.comp;
            container = other.container;
        }

        return *this;
    }

    template<typename T, typename Container, typename Compare>
    auto PriorityQueue<T, Container, Compare>::operator=(PriorityQueue&& other) noexcept -> PriorityQueue&
    {
        if (&other != this)
        {
            comp = std::move(other.comp);
            container = std::move(other.container);
        }

        return *this;
    }

    template<typename T, typename Container, typename Compare>
    auto PriorityQueue<T, Container, Compare>::top() const -> PriorityQueue::const_reference
    {
        return container.front();
    }

    template<typename T, typename Container, typename Compare>
    auto PriorityQueue<T, Container, Compare>::empty() const -> bool
    {
        return container.size() == 0;
    }

    template<typename T, typename Container, typename Compare>
    auto PriorityQueue<T, Container, Compare>::size() const -> size_type
    {
        return container.size();
    }

    template<typename T, typename Container, typename Compare>
    void PriorityQueue<T, Container, Compare>::push(const_reference value)
    {
        container.push_back(value);
        std::push_heap(container.begin(), container.end(), comp);
    }

    template<typename T, typename Container, typename Compare>
    void PriorityQueue<T, Container, Compare>::push(value_type&& value)
    {
        container.push_back(std::move(value));
        std::push_heap(container.begin(), container.end(), comp);
    }

    template<typename T, typename Container, typename Compare>
    template<typename... Args>
    void PriorityQueue<T, Container, Compare>::emplace(Args&&... args)
    {
        container.emplace_back(std::forward<Args>(args)...);
        std::push_heap(container.begin(), container.end(), comp);
    }

    template<typename T, typename Container, typename Compare>
    void PriorityQueue<T, Container, Compare>::pop()
    {
        std::pop_heap(container.begin(), container.end(), comp);
        container.pop_back();
    }

    template<typename T, typename Container, typename Compare>
    void PriorityQueue<T, Container, Compare>::swap(PriorityQueue& other) noexcept(
        std::is_nothrow_swappable_v<Container> && std::is_nothrow_swappable_v<Compare>)
    {
        std::swap(container, other.container);
        std::swap(comp, other.comp);
    }

    /**
     * @brief Overloads operator to print all elements of PriorityQueue
     *
     * @tparam T type of initializer list elements
     * @param[in,out] out reference to output stream
     * @param[in] PriorityQueue PriorityQueue to print
     * @return std::ostream& reference to std::ostream
     */
    template<typename T, typename Container, typename Compare>
    auto operator<<(std::ostream& out, const PriorityQueue<T, Container, Compare>& priorityQueue) -> std::ostream&
    {
        auto temp{ priorityQueue };

        while (!temp.empty())
        {
            out << temp.top() << ' ';
            temp.pop();
        }

        return out;
    }

    /**
     * @brief Exchanges content of two PriorityQueue containers
     *
     * @tparam T data type stored in containers
     * @param[in] lhs container to swap content
     * @param[in] rhs container to swap content
     */
    template<typename T, typename Container, typename Compare>
    void swap(PriorityQueue<T, Container, Compare>& lhs, PriorityQueue<T, Container, Compare>& rhs) noexcept(
        noexcept(lhs.swap(rhs)))
    {
        lhs.swap(rhs);
    }
} // namespace dsa

#endif // !QUEUE_H
