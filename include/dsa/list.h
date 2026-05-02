/**
 * @file list.h
 * @brief This file contains implementation of List class
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <ranges>

namespace dsa
{

    template<typename T>
    class List;

    /**
     * @brief Implements List using Node with pointer to adjacent
     *        elements as internal base
     *
     * @tparam T type of data stored in List Node
     */
    template<typename T>
    class List
    {
    public:

        /**
         * @brief Struct implements base pointer used by List
         */
        class NodeBase
        {
        public:

            /**
             * @brief Construct a new NodeBase object
             */
            NodeBase() = default;

            /**
             * @brief Construct a new NodeBase object using copy constructor
             *
             * @param[in] other NodeBase object
             */
            NodeBase(const NodeBase& other) = default;

            /**
             * @brief Construct a new NodeBase object using copy assignment
             *
             * @param[in] other NodeBase object
             * @return NodeBase& reference to NodeBase object
             */
            auto operator=(const NodeBase& other) -> NodeBase & = default;

            /**
             * @brief Construct NodeBase object using move constructor
             * @details Content of other object will be taken by constructed object
             *
             * @param[in,out] other NodeBase object
             */
            NodeBase(NodeBase&& other) = default;

            /**
             * @brief Construct NodeBase object using move assignment
             * @details Content of other object will be taken by constructed object
             *
             * @param[in,out] other NodeBase object
             * @return NodeBase& reference to NodeBase object
             */
            auto operator=(NodeBase&& other) -> NodeBase & = default;

            /**
             * @brief Destroy the Node Base object
             */
            virtual ~NodeBase() = default;

        private:

            friend class List<T>;

            /**
             * @brief Pointer to next node
             */
            NodeBase* m_next{};

            /**
             * @brief Pointer to previous node
             */
            NodeBase* m_prev{};
        };

        /**
         * @brief Implements Node template class with pointer to adjacent elements
         */
        class Node : public NodeBase
        {
        public:

            /**
             * @brief Construct a new Node object with initial value
             *
             * @param[in] value to store in Node object
             */
            Node(const T& value)
                : m_value{ value }
            {}

            /**
             * @brief Construct a new Node object with initial value using move semantics
             * @details \p value will be taken by constructed object
             *
             * @param[in] value to store in Node object
             */
            Node(T&& value)
                : m_value{ std::move(value) }
            {}

            /**
             * @brief Function returns value stored in Node object
             *
             * @return T value stored in Node
             */
            auto value() -> T&
            {
                return m_value;
            }

            /**
             * @brief Function returns value stored in Node object
             *
             * @return T value stored in Node
             */
            [[nodiscard]] auto value() const -> T
            {
                return m_value;
            }

        private:

            /**
             * @brief Forward friend declaration of List
             */
            friend class List;

            T m_value{};
        };

        /**
         * @brief Implements ListIterator
         *
         * Class is used to generate iterator and const_iterator types.
         * Template variable \p IF_CONST control whether reference
         * or const reference is returned to underlying data type
         *
         * @tparam IF_CONST if \p true generate iterator with const reference to underlying data type
         * @tparam T type of data stored in Node
         */
        template<bool IF_CONST>
        class ListIterator
        {
        public:

            /**
             * @brief Alias for iterator type
             *
             * @tparam IF_CONST if \p true generate iterator with const reference to underlying data type
             * @tparam T data type
             */
            using iterator_type = std::conditional_t<IF_CONST, const T, T>;

            /**
             * @brief Alias for bidirectional iterator tag, define iterator direction
             *
             * Used by STL to define iterator features.
             * Bidirectional iterator allows iteration forward and backward directions.
             */
            using iterator_category = std::bidirectional_iterator_tag;

            /**
             * @brief Alias for pointer difference type
             *
             * Used by STL to define distance between two pointers
             */
            using difference_type = std::ptrdiff_t;

            /**
             * @brief Alias for data type used by iterator
             *
             * @tparam T iterated element type
             */
            using value_type = T;

            /**
             * @brief Alias for size type used in class
             *
             * @tparam T size type
             */
            using size_type = std::size_t;

            /**
             * @brief Alias for pointer to data type used by iterator
             *
             * @tparam T* pointer to data type
             */
            using pointer = iterator_type*;

            /**
             * @brief Alias for reference to type used by iterator
             */
            using reference = iterator_type&;

            /**
             * @brief Construct a new ListIterator object
             */
            ListIterator() noexcept = default;

            /**
             * @brief Construct a new ListIterator object
             *
             * @param[in] node input Node
             */
            ListIterator(NodeBase* node) noexcept
                : m_current_node{ node }
            {}

            /**
             * @brief Overload operator= to assign \p node to currently pointed ListIterator
             *
             * @param[in] node input Node
             * @return ListIterator& reference to updated Node
             */
            auto operator=(NodeBase* node) -> ListIterator&
            {
                this->m_current_node = node;
                return *this;
            }

            /**
             * @brief Overload pre-increment operator++ to point ListIterator at next Node
             *
             * @return ListIterator& reference to next Node
             */
            auto operator++() -> ListIterator&
            {
                if (m_current_node)
                {
                    m_current_node = m_current_node->m_next;
                }

                return *this;
            }

            /**
             * @brief Overload post-increment operator++ to point ListIterator at next Node
             *
             * @return ListIterator& reference to next ListIterator
             */
            auto operator++(int) -> ListIterator
            {
                const ListIterator iterator = *this;
                ++(*this);
                return iterator;
            }

            /**
             * @brief Overload pre-decrement operator-- to point ListIterator at previous Node
             *
             * @return ListIterator& reference to previous Node
             */
            auto operator--() -> ListIterator&
            {
                if (m_current_node)
                {
                    m_current_node = m_current_node->m_prev;
                }

                return *this;
            }

            /**
             * @brief Overload post-decrement operator-- to point ListIterator at previous Node
             *
             * @return ListIterator& reference to previous ListIterator
             */
            auto operator--(int) -> ListIterator
            {
                const ListIterator iterator = *this;
                --(*this);
                return iterator;
            }

            /**
             * @brief Overload operator!= for ListIterator objects comparison
             *
             * @param[in] other input ListIterator of \p other object
             * @return bool comparison result
             * @retval true if ListIterator objects are the same
             * @retval false if ListIterator objects are different
             */
            auto operator==(const ListIterator& other) const -> bool
            {
                return m_current_node == other.m_current_node;
            }

            /**
             * @brief Overload operator!= for ListIterator objects comparison
             *
             * @param[in] other input ListIterator of \p other object
             * @return bool comparison result
             * @retval true if ListIterator objects are different
             * @retval false if ListIterator objects are the same
             */
            auto operator!=(const ListIterator& other) const -> bool
            {
                return !operator==(other);
            }

            /**
             * @brief Overload operator* to dereference Node value / data
             *
             * @return T& reference or const reference to data stored in Node
             */
            auto operator*() const -> reference
            {
                if (Node* node = dynamic_cast<Node*>(m_current_node))
                {
                    return node->value();
                }
                throw std::runtime_error("Invalid iterator dereference");
            }

            /**
             * @brief Overload operator-> to get pointer to Node value / data
             *
             * @return T* pointer to data stored in Node
             */
            auto operator->() -> pointer
            {
                if (Node* node = dynamic_cast<Node*>(m_current_node))
                {
                    return &node->value();
                }
                throw std::runtime_error("Invalid iterator pointer");
            }

            /**
             * @brief convert ListIterator to Basic_const_iterator
             */
            operator ListIterator<true>()
            {
                return ListIterator<true>(m_current_node);
            }

        private:

            /**
             * @brief Forward friend declaration of List
             */
            friend class List;

            NodeBase* m_current_node{};
        };

        /**
         * @brief Alias for data type used in class
         *
         * @tparam T data type
         */
        using value_type = T;

        /**
         * @brief Alias for memory allocator
         */
        using allocator_type = std::allocator<value_type>;

        /**
         * @brief Alias for size type used in class
         *
         * @tparam T size type
         */
        using size_type = std::size_t;

        /**
         * @brief Alias for pointer difference type used in class
         *
         * @tparam T pointer size type
         */
        using difference_type = std::ptrdiff_t;

        /**
         * @brief Alias for pointer to data type used in class
         *
         * @tparam value_type* pointer to data type
         */
        using pointer = value_type*;

        /**
         * @brief Alias for const pointer to data type used in class
         *
         * @tparam value_type* const pointer to data type
         */
        using const_pointer = const value_type*;

        /**
         * @brief Alias for reference to data type used in class
         *
         * @tparam value_type& reference to data type
         */
        using reference = value_type&;

        /**
         * @brief Alias for const reference to data type used in class
         *
         * @tparam value_type& const reference to data type
         */
        using const_reference = const value_type&;

        /**
         * @brief Alias for iterator to data type used in class
         */
        using iterator = ListIterator<false>;

        /**
         * @brief Alias for const iterator to data type used in class
         */
        using const_iterator = ListIterator<true>;

        /**
         * @brief Alias for reverse_iterator to data type used in class
         */
        using reverse_iterator = std::reverse_iterator<iterator>;

        /**
         * @brief Alias for const reverse_iterator to data type used in class
         */
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        /**
         * @brief Construct a new List object
         */
        List();

        /**
         * @brief Construct a new List object of size \p count,
         * using default value of type T
         *
         * @param[in] count element count
         */
        List(size_type count);

        /**
         * @brief Construct a new List object of size \p count,
         * using provided \p value of type T
         *
         * @param[in] count element count
         * @param[in] value value for all nodes
         */
        List(size_type count, const T& value);

        /**
         * @brief Construct a new List object using elements from range [ \p first , \p last )
         *
         * @tparam InputIt
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         */
        template<typename InputIt>
            requires std::input_iterator<InputIt>
        List(InputIt first, InputIt last);

        /**
         * @brief Construct a new List object using initializer list
         *
         * @param[in] ilist initializer list of values of type T
         */
        List(const std::initializer_list<T>& ilist);

        /**
         * @brief Construct a new List object using copy constructor
         *
         * @param[in] other List object of type T
         */
        List(const List<T>& other);

        /**
         * @brief Constructs List using copy assignment
         *
         * @param[in] other List object of type T
         * @return List&
         */
        auto operator=(const List<T>& other) -> List&;

        /**
         * @brief Construct a new List object using move constructor
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other List object of type T
         */
        List(List<T>&& other) noexcept;

        /**
         * @brief Assign List object using move assignment
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other List object of type T
         * @return List&
         */
        auto operator=(List<T>&& other) noexcept(std::allocator_traits<allocator_type>::is_always_equal::value)->List&;

        /**
         * @brief Assign elements from initializer list to List object
         *
         * @param[in] ilist initializer list to copy elements from
         * @return List&
         */
        auto operator=(std::initializer_list<value_type> ilist) -> List&;

        /**
         * @brief Destroy the List object
         */
        ~List();

        /**
         * @brief Function assign values to the List
         *
         * @param[in] count new size of the container
         * @param[in] value value to initialize elements of the container with
         *
         * @note all iterators, pointers and references to the elements of the container are invalidated
         */
        void assign(size_type count, const_reference value);

        /**
         * @brief Function assign elements from range [ \p first , \p last ) to List object
         *
         * @tparam InputIt
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         *
         * @note all iterators, pointers and references to the elements of the container are invalidated
         */
        template<typename InputIt>
            requires std::input_iterator<InputIt>
        void assign(InputIt first, InputIt last);

        /**
         * @brief Function assign values to the List
         *
         * @param[in] init_list values to replace List with
         *
         * @note all iterators, pointers and references to the elements of the container are invalidated
         */
        void assign(const std::initializer_list<T>& init_list);

        /**
         * @brief Get the allocator object
         *
         * @return allocator_type type of memory allocator
         */
        [[nodiscard]] auto get_allocator() const noexcept -> allocator_type;

        /**
         * @brief Function returns reference to value stored in List first Node
         *
         * @return reference to data stored in List first Node
         */
        [[nodiscard]] auto front() -> reference;

        /**
         * @brief Function returns const reference value stored in List first Node
         *
         * @return const reference to data stored in List first Node
         */
        [[nodiscard]] auto front() const -> const_reference;

        /**
         * @brief Function returns reference to value stored in List last Node
         *
         * @return reference to data stored in List last Node
         */
        [[nodiscard]] auto back() -> reference;

        /**
         * @brief Function returns const reference value stored in List last Node
         *
         * @return const reference to data stored in List last Node
         */
        [[nodiscard]] auto back() const -> const_reference;

        /**
         * @brief Function returns pointer to List first Node
         *
         * @return iterator iterator to List first Node
         */
        [[nodiscard]] auto begin() noexcept -> iterator;

        /**
         * @brief Function returns const pointer to List first Node
         *
         * @return const_iterator const iterator to List first Node
         */
        [[nodiscard]] auto begin() const noexcept -> const_iterator;

        /**
         * @brief Function returns const pointer to List first Node
         *
         * @return const_iterator const iterator to List first Node
         */
        [[nodiscard]] auto cbegin() const noexcept -> const_iterator;

        /**
         * @brief Function returns pointer to List last Node
         *
         * @return iterator iterator to List last Node
         */
        [[nodiscard]] auto end() noexcept -> iterator;

        /**
         * @brief Function returns pointer to List last Node
         *
         * @return const_iterator const iterator to List last Node
         */
        [[nodiscard]] auto end() const noexcept -> const_iterator;

        /**
         * @brief Function returns pointer to List last Node
         *
         * @return const_iterator const iterator to List last Node
         */
        [[nodiscard]] auto cend() const noexcept -> const_iterator;

        /**
         * @brief Returns reverse_iterator to the first element of reversed underlaying data structure
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return reverse_iterator to the first element
         */
        [[nodiscard]] auto rbegin() noexcept -> reverse_iterator;

        /**
         * @brief Returns const_reverse_iterator to the first element of reversed underlaying data structure
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return const_reverse_iterator to the first element
         */
        [[nodiscard]] auto rbegin() const noexcept -> const_reverse_iterator;

        /**
         * @brief Returns const_reverse_iterator to the first element of reversed underlaying data structure
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return const_reverse_iterator to the first element
         */
        [[nodiscard]] auto crbegin() const noexcept -> const_reverse_iterator;

        /**
         * @brief Returns reverse_iterator past the last element of reversed underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return reverse_iterator to the element after the last element
         */
        [[nodiscard]] auto rend() noexcept -> reverse_iterator;

        /**
         * @brief Returns const_reverse_iterator past the last element of reversed underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return const_reverse_iterator to the element after the last element
         */
        [[nodiscard]] auto rend() const noexcept -> const_reverse_iterator;

        /**
         * @brief Returns const_reverse_iterator past the last element of reversed underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return const_reverse_iterator to the element after the last element
         */
        [[nodiscard]] auto crend() const noexcept -> const_reverse_iterator;

        /**
         * @brief Function checks if container has no elements
         *
         * @retval true if container is empty
         * @retval false if container is not empty
         */
        [[nodiscard]] auto empty() const noexcept -> bool;

        /**
         * @brief Function returns List size
         *
         * @return size_type number of elements in container
         */
        [[nodiscard]] auto size() const noexcept -> size_type;

        /**
         * @brief Function returns maximum number of elements container can hold
         *
         * @return size_type maximum number of elements
         */
        [[nodiscard]] auto max_size() const noexcept -> size_type;

        /**
         * @brief Function removes all elements of List
         */
        void clear() noexcept;

        /**
         * @brief Function inserts new Node before specified \p pos
         *
         * @param[in] pos const_iterator to insert element before
         * @param[in] value element of type T to be inserted before \p pos
         * @retval iterator to inserted element
         * @retval pos if no element was inserted
         */
        auto insert(const const_iterator& pos, const_reference value) -> iterator;

        /**
         * @brief Function inserts new Node before specified \p pos
         *
         * @param[in] pos const_iterator to insert element before
         * @param[in] value element of type T to be inserted before \p pos using move semantics
         * @retval iterator to inserted element
         * @retval pos if no element was inserted
         */
        auto insert(const const_iterator& pos, T&& value) -> iterator;

        /**
         * @brief Function inserts new Node before specified \p pos
         *
         * @param[in] pos const_iterator to insert element before
         * @param[in] count number of elements to insert before \p pos
         * @param[in] value element of type T to be inserted
         * @retval iterator to inserted element
         * @retval pos if no element was inserted
         */
        auto insert(const const_iterator& pos, size_type count, const_reference value) -> iterator;

        /**
         * @brief Function inserts elements in range [first, last) after \p pos
         *
         * @param[in] pos const_iterator to insert element after
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         * @return pointer to List element
         * @retval iterator pointer to last inserted element
         * @retval pos if no element was inserted
         */
        template<typename InputIt>
            requires std::input_iterator<InputIt>
        auto insert(const const_iterator& pos, InputIt first, InputIt last) -> iterator;

        /**
         * @brief Function inserts content of initializer list before specified \p pos
         *
         * @param[in] pos const_iterator to insert element before
         * @param[in] ilist initializer list with elements to insert before \p pos
         * @retval iterator to first inserted element
         * @retval pos if no element was inserted
         */
        auto insert(const const_iterator& pos, std::initializer_list<T> ilist) -> iterator;

        /**
         * @brief Insert new element into the container before \p pos
         *
         * @tparam ...Args
         * @param[in] pos iterator before which new element will be inserted
         * @param[in] ...args args arguments to forward to the constructor of the element
         * @return iterator pointing to the emplaced element
         *
         * @note no iterators or references are invalidated,
         *       if construction of new element fails or an exception is thrown for any reason
         *       state of the object does not change and this function has no effect
         */
        template<typename... Args>
        auto emplace(const_iterator pos, Args&&... args) -> iterator;

        /**
        * @brief Function erases Node object at specified \p pos
        *
        * @param[in] pos iterator to element to erase
        * @return iterator following erased element
        * @retval iterator to element following \p pos
        * @retval begin iterator if \p pos was first element prior to removal
        * @retval end iterator if \p pos was last element prior to removal
        */
        auto erase(const_iterator pos) -> iterator;

        /**
         * @brief Function erases Node objects in range [first, last)
         *
         * @param[in] first element to erase
         * @param[in] last element after last erased element
         * @return iterator following last erased element
         * @retval iterator to \p last
         * @retval end iterator if \p last was end element prior to removal
         * @retval last iterator if \p first to \p last is empty range
         */
        auto erase(const_iterator first, const_iterator last) -> iterator;

        /**
         * @brief Function adds new Node at the end of List
         *
         * @param[in] value element of type T
         *
         * @note no iterators or references are invalidated,
         *       if construction of new element fails or an exception is thrown for any reason
         *       state of the object does not change and this function has no effect
         */
        void push_back(const_reference value);

        /**
         * @brief Function adds new Node at the end of List using move semantics
         *
         * @param[in] value element of type T
         *
         * @note no iterators or references are invalidated,
         *       if construction of new element fails or an exception is thrown for any reason
         *       state of the object does not change and this function has no effect
         */
        void push_back(T&& value);

        /**
         * @brief Insert new element to the end of the container
         *
         * @tparam ...Args
         * @param[in] ...args args arguments to forward to the constructor of the element
         * @return reference to the emplaced element
         *
         * @note no iterators or references are invalidated,
         *       if construction of new element fails or an exception is thrown for any reason
         *       state of the object does not change and this function has no effect
         */
        template<typename... Args>
        auto emplace_back(Args&&... args) -> reference;

        /**
         * @brief Function removes last Node of List
         *
         * @note references and iterators to the erased element are invalidated
         */
        void pop_back();

        /**
         * @brief Function adds new Node at the beginning of List
         *
         * @param[in] value element of type T
         *
         * @note no iterators or references are invalidated,
         *       if construction of new element fails or an exception is thrown for any reason
         *       state of the object does not change and this function has no effect
         */
        void push_front(const_reference value);

        /**
         * @brief Function adds new Node at the beginning of List using move semantics
         *
         * @param[in] value element of type T
         *
         * @note no iterators or references are invalidated,
         *       if construction of new element fails or an exception is thrown for any reason
         *       state of the object does not change and this function has no effect
         */
        void push_front(T&& value);

        /**
         * @brief Insert new element at the beginning of the container
         *
         * @tparam ...Args
         * @param[in] ...args args arguments to forward to the constructor of the element
         * @return reference to the emplaced element
         *
         * @note no iterators or references are invalidated,
         *       if construction of new element fails or an exception is thrown for any reason
         *       state of the object does not change and this function has no effect
         */
        template<typename... Args>
        auto emplace_front(Args&&... args) -> reference;

        /**
         * @brief Function removes first Node of List
         *
         * @note references and iterators to the erased element are invalidated
         */
        void pop_front();

        /**
         * @brief Function resize List to specified number of elements
         *
         * @param[in] count new size of container
         */
        void resize(size_type count);

        /**
         * @brief Function resize List to specified number of elements
         *
         * @param[in] count count new size of container
         * @param[in] value value to initialize new elements
         */
        void resize(size_type count, const_reference value);

        /**
         * @brief Function swaps content of two List objects
         *
         * @param[in,out] other object to swap content with
         *
         * @note all iterators and references remain valid
         */
        void swap(List<T>& other) noexcept(std::allocator_traits<allocator_type>::is_always_equal::value);

        /**
         * @brief Function combines two sorted Lists into one sorted List
         *
         * @param[in,out] other container to take elements from
         * @details Content of other object will be taken by constructed object
         */
        void merge(List<T>& other);

        /**
         * @brief Function combines two sorted Lists into one sorted List
         *
         * @param[in,out] other container to take elements from
         * @details Content of other object will be taken by constructed object
         */
         // transfers ownership of nodes, moving entire container is not necessary
         // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
        void merge(List<T>&& other);

        /**
         * @brief Function combines two sorted Lists into one sorted List
         *
         * @param[in,out] other container to take elements from
         * @param[in] comp comparison function object
         * @details Content of other object will be taken by constructed object
         *
         * @note no iterators or references become invalidated,
         *       iterators or references of objects moved from \p other will
         *       refer to the same elements of \p this
         */
        template<typename Compare>
        void merge(List<T>& other, Compare comp);

        /**
         * @brief Function combines two sorted Lists into one sorted List
         *
         * @param[in,out] other container to take elements from
         * @param[in] comp comparison function object
         * @details Content of other object will be taken by constructed object
         *
         * @note no iterators or references become invalidated,
         *       iterators or references of objects moved from \p other will
         *       refer to the same elements of \p this
         */
        template<typename Compare>
        // transfers ownership of nodes, moving entire container is not necessary
        // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
        void merge(List<T>&& other, Compare comp);

        /**
         * @brief Function moves elements from other List object
         * @details Content of other object will be taken by constructed object
         *
         * @param[in] pos const_iterator before which content of other container will be inserted
         * @param[in,out] other container to take elements from
         *
         * @note no iterators or references become invalidated,
         *       iterators or references of objects moved from \p other will
         *       refer to the same elements of \p this
         */
        void splice(const const_iterator& pos, List<T>& other);

        /**
         * @brief Function moves elements from other List object
         * @details Content of other object will be taken by constructed object
         *
         * @param[in] pos const_iterator before which content of other container will be inserted
         * @param[in,out] other container to take elements from
         *
         * @note no iterators or references become invalidated,
         *       iterators or references of objects moved from \p other will
         *       refer to the same elements of \p this
         */
        void splice(const_iterator pos, List<T>&& other);

        /**
         * @brief Function moves elements from other List object
         * @details Content of other object will be taken by constructed object
         *
         * @param[in] pos const_iterator before which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] iter const_iterator pointing to element to move
         *
         * @note no iterators or references become invalidated,
         *       iterators or references of objects moved from \p other will
         *       refer to the same elements of \p this
         */
        void splice(const const_iterator& pos, List<T>& other, const const_iterator& iter);

        /**
         * @brief Function moves elements from other List object
         * @details Content of other object will be taken by constructed object
         *
         * @param[in] pos const_iterator before which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] iter const_iterator pointing to element to move
         *
         * @note no iterators or references become invalidated,
         *       iterators or references of objects moved from \p other will
         *       refer to the same elements of \p this
         */
        void splice(const_iterator pos, List<T>&& other, const_iterator iter);

        /**
         * @brief Function moves elements in range [first, last) from other List object
         * @details Content of other object will be taken by constructed object
         *
         * @param[in] pos const_iterator before which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] first const_iterator pointing to first element to move
         * @param[in] last const_iterator pointing to element after last taken element
         *
         * @note no iterators or references become invalidated,
         *       iterators or references of objects moved from \p other will
         *       refer to the same elements of \p this
         */
        void splice(const const_iterator& pos, List<T>& other, const const_iterator& first, const const_iterator& last);

        /**
         * @brief Function moves elements in range [first, last) from other List object
         * @details Content of other object will be taken by constructed object
         *
         * @param[in] pos const_iterator before which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] first const_iterator pointing to first element to move
         * @param[in] last const_iterator pointing to element after last taken element
         *
         * @note no iterators or references become invalidated,
         *       iterators or references of objects moved from \p other will
         *       refer to the same elements of \p this
         */
        void splice(const_iterator pos, List<T>&& other, const_iterator first, const_iterator last);

        /**
         * @brief Function removes all elements equal to \p value
         *
         * @param[in] value value of elements to remove
         * @return size_type number of elements removed
         *
         * @note invalidates only the iterators and references to the removed elements
         */
        auto remove(const_reference value) -> size_type;

        /**
         * @brief Function removes all elements for which \p predicate returns \p true
         *
         * @tparam UnaryPred
         * @param[in] predicate to remove elements
         * @return size_type number of elements removed
         *
         * @note invalidates only the iterators and references to the removed elements
         */
        template<typename UnaryPred>
        auto remove_if(UnaryPred predicate) -> size_type;

        /**
         * @brief Function reverts in place Nodes of List
         *
         * @note no iterators or references are invalidated
         */
        void reverse() noexcept;

        /**
         * @brief Function removes consecutive duplicated elements
         * @details Only the first occurrence of given element in each group is preserved
         *
         * @return size_type number of elements removed
         */
        auto unique() -> size_type;

        /**
         * @brief Function removes consecutive duplicated elements
         * @details Only the first occurrence of given element in each group is preserved
         *
         * @tparam BinaryPred
         * @param[in] predicate binary predicate which returns \p true if the element should be treated as equal
         * @return size_type number of elements removed
         */
        template<typename BinaryPred>
        auto unique(BinaryPred predicate) -> size_type;

        /**
         * @brief Function sorts the elements and preserves the order of equivalent elements
         *
         * @details elements are compared using \p operator<
         *
         * @note no iterators or references are invalidated,
         *       if an exception is thrown, the order of elements is unspecified
         */
        void sort();

        /**
         * @brief Function sorts the elements and preserves the order of equivalent elements
         *
         * @details elements are compared using \p comp
         *
         * @tparam Compare
         * @param[in] comp comparison function object, returns \p true if the first argument is less than second
         *
         * @note no iterators or references are invalidated,
         *       if an exception is thrown, the order of elements is unspecified
         */
        template<typename Compare>
        void sort(Compare comp);

    private:

        /**
         * @brief Function add end node located just after last user created data
         * Node is used by iterators indicating end of container
         */
        void init_node();

        /**
         * @brief Function remove next element
         *
         * @param[in] iterator to element to which will be erased
         * @return iterator to element following \p pos
         */
        auto erase_element(iterator pos) -> iterator;

        /**
         * @brief Function allocate and construct List node
         *
         * @tparam ...Args
         * @param[in] prev_ptr pointer to previous Node
         * @param[in] next_ptr pointer to next Node
         * @param[in] args element of type T to be inserted
         * @return pointer to created Node
         */
        template<typename... Args>
        auto construct_node(NodeBase* prev_ptr, NodeBase* next_ptr, Args&&... args) -> Node*;

        /**
         * @brief Function destroys and deallocates memory used by Node
         *
         * @param[in] node_to_destroy pointer to Node to delete
         */
        void destroy_node(NodeBase* node_to_destroy);

        /**
         * @brief Function checks List contains iterator
         *
         * @param[in] pos iterator to check
         * @return bool \p pos iterator status
         * @return true if \p pos belong to List
         * @return false if otherwise
         */
        auto if_valid_iterator(const_iterator pos) -> bool;

        /**
         * @brief Function calculate number of elements from first to last
         *
         * @tparam T type of input objects
         * @param[in] first const_iterator pointing first element
         * @param[in] last const_iterator pointing to last (inclusive) element
         * @return size_type number of elements between input elements
         */
        auto distance(const_iterator first, const const_iterator& last) -> size_type;

        /**
         * @brief Function moves elements from other List object
         *
         * @param[in] pos const_iterator after which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] first const_iterator after which elements of \p other will be taken
         * @param[in] last const_iterator until which elements of \p other will be taken
         * @details Content of other object will be taken by constructed object
         */
         // transfers ownership of nodes, moving entire container is not necessary
         // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
        void transfer(const_iterator pos, List<T>&& other, const_iterator first, const const_iterator& last);

        /**
         * @brief Function sorts nodes using merge sort algorithm
         * @details Sorting is implemented using recursive (top-down) algorithm
         *          Sorting is stable and inplace
         *
         * @tparam Compare
         * @param[in,out] source list to sort
         * @param[in] comp comparison function object
         * @return NodeBase* of sorted list using \p comp
         */
        template<typename Compare>
        auto merge_sort(NodeBase* source, Compare comp) -> NodeBase*;

        /**
         * @brief Helper function for merge_sort to merge two sub-lists
         * @details Merging of sorted sub-lists is performed recursively
         *
         * @tparam Compare
         * @param[in,out] left first input sub-list
         * @param[in,out] right second input sub-list
         * @param[in] comp comparison function object
         * @return NodeBase* containing elements from both input lists sorted using \p comp
         */
        template<typename Compare>
        auto merge(NodeBase* left, NodeBase* right, Compare comp) -> NodeBase*;

        NodeBase* m_head{};
        NodeBase* m_tail{};
        size_type m_size{};

        /**
         * @brief Allocator for memory management
         */
        allocator_type m_allocator{};

        /**
         * @brief Rebind allocator to create new objects of type Node
         */
        using node_allocator = typename std::allocator_traits<allocator_type>::template rebind_alloc<Node>;

        /**
         * @brief Setup allocator traits used for Node creation and deletion
         */
        using node_alloc_traits = std::allocator_traits<node_allocator>;

        /**
         * @brief Initialize allocator rebind to Node objects
         */
        node_allocator node_alloc{};
    };

    template<typename T>
    List<T>::List()
    {
        init_node();
    }

    template<typename T>
    List<T>::List(size_type count)
        : List(count, T{})
    {}

    template<typename T>
    List<T>::List(size_type count, const T& value)
        : List()
    {
        for (size_type i = 0; i < count; i++)
        {
            push_front(value);
        }
    }

    template<typename T>
    template<typename InputIt>
        requires std::input_iterator<InputIt>
    List<T>::List(InputIt first, InputIt last)
        : List()
    {
        assign(first, last);
    }

    template<typename T>
    List<T>::List(const std::initializer_list<T>& ilist)
        : List()
    {
        operator=(ilist);
    }

    template<typename T>
    List<T>::List(const List<T>& other)
        : List()
    {
        assign(other.begin(), other.end());
    }

    template<typename T>
    auto List<T>::operator=(const List<T>& other) -> List<T>&
    {
        if (&other != this)
        {
            assign(other.begin(), other.end());
        }

        return *this;
    }

    template<typename T>
    List<T>::List(List<T>&& other) noexcept
        : List()
    {
        operator=(std::move(other));
    }

    template<typename T>
    auto List<T>::operator=(List<T>&& other) noexcept(std::allocator_traits<allocator_type>::is_always_equal::value)
        ->List&
    {
        if (&other != this)
        {
            clear();
            NodeBase* temp{ m_head };

            m_head = other.m_head;
            m_tail = other.m_tail;
            m_size = other.m_size;

            other.m_head = temp;
            other.m_tail = other.m_head;
            other.m_size = 0;
        }

        return *this;
    }

    template<typename T>
    auto List<T>::operator=(std::initializer_list<value_type> ilist) -> List&
    {
        clear();

        for (const auto& item : ilist)
        {
            push_back(item);
        }

        return *this;
    }

    template<typename T>
    List<T>::~List()
    {
        clear();
        delete m_head;
    }

    template<typename T>
    void List<T>::assign(size_type count, const_reference value)
    {
        clear();

        for (size_type i = 0; i < count; i++)
        {
            push_back(value);
        }
    }

    template<typename T>
    template<typename InputIt>
        requires std::input_iterator<InputIt>
    void List<T>::assign(InputIt first, InputIt last)
    {
        clear();

        while (first != last)
        {
            push_back(*first);
            ++first;
        }
    }

    template<typename T>
    void List<T>::assign(const std::initializer_list<T>& init_list)
    {
        clear();

        for (const auto& item : init_list)
        {
            push_back(item);
        }
    }

    template<typename T>
    [[nodiscard]] auto List<T>::get_allocator() const noexcept -> allocator_type
    {
        return m_allocator;
    }

    template<typename T>
    auto List<T>::front() -> typename List<T>::reference
    {
        return *begin();
    }

    template<typename T>
    auto List<T>::front() const -> typename List<T>::const_reference
    {
        return *cbegin();
    }

    template<typename T>
    auto List<T>::back() -> typename List<T>::reference
    {
        return *(--end());
    }

    template<typename T>
    auto List<T>::back() const -> typename List<T>::const_reference
    {
        return *(--cend());
    }

    template<typename T>
    auto List<T>::begin() noexcept -> typename List<T>::iterator
    {
        return iterator(m_head);
    }

    template<typename T>
    auto List<T>::begin() const noexcept -> typename List<T>::const_iterator
    {
        return const_iterator(m_head);
    }

    template<typename T>
    auto List<T>::cbegin() const noexcept -> typename List<T>::const_iterator
    {
        return begin();
    }

    template<typename T>
    auto List<T>::end() noexcept -> typename List<T>::iterator
    {
        return iterator(m_tail);
    }

    template<typename T>
    auto List<T>::end() const noexcept -> typename List<T>::const_iterator
    {
        return const_iterator(m_tail);
    }

    template<typename T>
    auto List<T>::cend() const noexcept -> typename List<T>::const_iterator
    {
        return end();
    }

    template<typename T>
    auto List<T>::rbegin() noexcept -> reverse_iterator
    {
        return reverse_iterator(end());
    }

    template<typename T>
    auto List<T>::rbegin() const noexcept -> const_reverse_iterator
    {
        return const_reverse_iterator(end());
    }

    template<typename T>
    auto List<T>::crbegin() const noexcept -> const_reverse_iterator
    {
        return const_reverse_iterator(end());
    }

    template<typename T>
    auto List<T>::rend() noexcept -> reverse_iterator
    {
        return reverse_iterator(begin());
    }

    template<typename T>
    auto List<T>::rend() const noexcept -> const_reverse_iterator
    {
        return const_reverse_iterator(begin());
    }

    template<typename T>
    auto List<T>::crend() const noexcept -> const_reverse_iterator
    {
        return const_reverse_iterator(begin());
    }

    template<typename T>
    auto List<T>::empty() const noexcept -> bool
    {
        return m_size == 0;
    }

    template<typename T>
    auto List<T>::size() const noexcept -> size_type
    {
        return m_size;
    }

    template<typename T>
    auto List<T>::max_size() const noexcept -> size_type
    {
        return std::numeric_limits<size_type>::max();
    }

    template<typename T>
    void List<T>::clear() noexcept
    {
        NodeBase* temp{ m_head };
        while (temp->m_next)
        {
            m_head->m_prev = nullptr;
            m_head = temp->m_next;
            destroy_node(temp);
            temp = m_head;
        }

        m_size = 0;
        m_tail->m_prev = nullptr;
    }

    template<typename T>
    auto List<T>::insert(const const_iterator& pos, const_reference value) -> typename List<T>::iterator
    {
        return insert(pos, 1, value);
    }

    template<typename T>
    auto List<T>::insert(const const_iterator& pos, T&& value) -> typename List<T>::iterator
    {
        if (!if_valid_iterator(pos))
        {
            return pos.m_current_node;
        }

        iterator iter{ pos.m_current_node };
        iter = emplace(iter, std::move(value));

        return iter;
    }

    template<typename T>
    auto List<T>::insert(const const_iterator& pos, size_type count, const_reference value)
        -> typename List<T>::iterator
    {
        if (!if_valid_iterator(pos))
        {
            return pos.m_current_node;
        }

        iterator iter{ pos.m_current_node };
        for (size_type i = 0; i < count; i++)
        {
            iter = emplace(iter, value);
        }

        return iter;
    }

    template<typename T>
    template<typename InputIt>
        requires std::input_iterator<InputIt>
    auto List<T>::insert(const const_iterator& pos, InputIt first, InputIt last) -> typename List<T>::iterator
    {
        iterator iter{};
        while (first != last)
        {
            auto res = insert(pos.m_current_node, *first);
            if (!iter.m_current_node)
            {
                iter = res;
            }

            ++first;
        }

        return iter == nullptr ? pos.m_current_node : iter;
    }

    template<typename T>
    auto List<T>::insert(const const_iterator& pos, std::initializer_list<T> ilist) -> typename List<T>::iterator
    {
        return insert(pos, ilist.begin(), ilist.end());
    }

    template<typename T>
    template<typename... Args>
    auto List<T>::emplace(const_iterator pos, Args&&... args) -> iterator
    {
        const iterator current{ pos.m_current_node };

        Node* newNode{ construct_node(current.m_current_node->m_prev, current.m_current_node->m_next,
            std::forward<Args>(args)...) };

        if (pos == cbegin())
        {
            newNode->m_next = m_head;
            !m_head->m_next ? m_tail->m_prev = newNode : m_head->m_prev = newNode;
            m_head = newNode;
        }
        else
        {
            NodeBase* prev_pos{ pos.m_current_node->m_prev };
            NodeBase* next_pos{ prev_pos->m_next };

            prev_pos->m_next = newNode;
            newNode->m_prev = prev_pos;

            newNode->m_next = next_pos;
            next_pos->m_prev = newNode;
        }

        ++m_size;
        return iterator(newNode);
    }


    template<typename T>
    auto List<T>::erase(const_iterator pos) -> typename List<T>::iterator
    {
        if (!if_valid_iterator(pos))
        {
            return nullptr;
        }

        return erase_element(pos.m_current_node);
    }

    template<typename T>
    auto List<T>::erase(const_iterator first, const_iterator last) -> typename List<T>::iterator
    {
        if (!if_valid_iterator(first) || !if_valid_iterator(last))
        {
            return nullptr;
        }

        const size_type dist = distance(first, last);
        if (dist == 0)
        {
            return last.m_current_node;
        }

        iterator iter{ first.m_current_node };
        for (size_type i = 0; i < dist; i++)
        {
            iter = erase_element(iter);
        }

        return iter;
    }

    template<typename T>
    void List<T>::push_front(const_reference value)
    {
        emplace_front(value);
    }

    template<typename T>
    void List<T>::push_front(T&& value)
    {
        emplace_front(std::move(value));
    }

    template<typename T>
    template<typename... Args>
    auto List<T>::emplace_front(Args&&... args) -> reference
    {
        emplace(begin(), std::forward<Args>(args)...);
        return front();
    }

    template<typename T>
    void List<T>::pop_front()
    {
        if (m_size == 0)
        {
            return;
        }

        NodeBase* temp{ m_head };
        m_head = m_head->m_next;
        if (m_size == 1)
        {
            m_tail->m_prev = nullptr;
        }
        else
        {
            m_head->m_prev = nullptr;
        }
        destroy_node(temp);

        m_size--;
    }

    template<typename T>
    void List<T>::push_back(const_reference value)
    {
        emplace_back(value);
    }

    template<typename T>
    void List<T>::push_back(T&& value)
    {
        emplace_back(std::move(value));
    }

    template<typename T>
    template<typename... Args>
    auto List<T>::emplace_back(Args&&... args) -> reference
    {
        emplace(end(), std::forward<Args>(args)...);
        return back();
    }

    template<typename T>
    void List<T>::pop_back()
    {
        if (m_size == 0)
        {
            return;
        }

        NodeBase* temp{};
        if (m_size == 1)
        {
            temp = m_head;
            m_head = m_head->m_next;
            m_tail->m_prev = nullptr;
        }
        else
        {
            temp = m_tail->m_prev;
            temp->m_prev->m_next = temp->m_next;
            m_tail->m_prev = temp->m_prev;
        }
        destroy_node(temp);

        m_size--;
    }

    template<typename T>
    void List<T>::resize(size_type count)
    {
        resize(count, T{});
    }

    template<typename T>
    void List<T>::resize(size_type count, const_reference value)
    {
        if (count == m_size)
        {
            return;
        }

        if (m_size > count)
        {
            // container is reduced to its count elements
            while (m_size > count)
            {
                pop_back();
            }
        }

        if (m_size < count)
        {
            // additional copies of value are appended
            while (m_size < count)
            {
                push_back(value);
            }
        }
    }

    template<typename T>
    void List<T>::swap(List<T>& other) noexcept(std::allocator_traits<allocator_type>::is_always_equal::value)
    {
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
        std::swap(m_size, other.m_size);
    }

    template<typename T>
    void List<T>::merge(List<T>& other)
    {
        merge(std::move(other));
    }

    template<typename T>
    void List<T>::merge(List<T>&& other)
    {
        merge(std::move(other), std::less<>());
    }

    template<typename T>
    template<typename Compare>
    void List<T>::merge(List<T>& other, Compare comp)
    {
        merge(std::move(other), comp);
    }

    template<typename T>
    template<typename Compare>
    // transfers ownership of nodes, moving entire container is not necessary
    // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
    void List<T>::merge(List<T>&& other, Compare comp)
    {
        if (&other == this)
        {
            return;
        }

        if (m_size != 0)
        {
            // if temporary node could not be allocated do not modify
            // object state
            Node* temp_head{ construct_node(nullptr, nullptr, T{}) };

            NodeBase* temp_tail = temp_head;

            NodeBase* to_move{};
            NodeBase* to_return{};

            NodeBase* sentinel_this{ m_tail };
            NodeBase* sentinel_other{ other.m_tail };

            while (m_head->m_next && other.m_head->m_next)
            {
                Node* node_this = dynamic_cast<Node*>(m_head);
                Node* node_other = dynamic_cast<Node*>(other.m_head);

                if (node_this && node_other)
                {
                    // 2nd condition keeps correct order of equal elements
                    if (comp(node_this->value(), node_other->value()) ||
                        !comp(node_other->value(), node_this->value()))
                    {
                        to_move = m_head;
                        to_move->m_prev = temp_tail;

                        to_return = to_move->m_next;
                        temp_tail->m_next = to_move;
                        m_head = to_return;
                    }
                    else
                    {
                        to_move = other.m_head;
                        to_move->m_prev = temp_tail;

                        to_return = to_move->m_next;
                        temp_tail->m_next = to_move;
                        other.m_head = to_return;
                    }

                    temp_tail = temp_tail->m_next;
                }
            }

            NodeBase* last{};
            if (m_head->m_next == nullptr) // other.m_head attached at the end
            {
                last = sentinel_other->m_prev;
                other.m_head->m_prev = temp_tail;
                temp_tail->m_next = other.m_head;
            }
            else // this.m_head attached at the end
            {
                last = sentinel_this->m_prev;
                m_head->m_prev = temp_tail;
                temp_tail->m_next = m_head;
            }
            last->m_next = sentinel_this;
            last->m_next->m_prev = last;

            m_head = temp_head->m_next;
            m_head->m_prev = nullptr;
            destroy_node(temp_head);

            other.m_head = other.m_tail;
            other.m_head->m_next = nullptr;
            other.m_head->m_prev = nullptr;

            m_size += other.m_size;
            other.m_size = 0;
        }
        else
        {
            swap(other);
        }
    }

    template<typename T>
    void List<T>::splice(const const_iterator& pos, List<T>& other)
    {
        transfer(pos, std::move(other), other.begin(), other.end());
    }

    template<typename T>
    void List<T>::splice(const_iterator pos, List<T>&& other)
    {
        transfer(pos, std::move(other), other.begin(), other.end());
    }

    template<typename T>
    void List<T>::splice(const const_iterator& pos, List<T>& other, const const_iterator& iter)
    {
        transfer(pos, std::move(other), iter, iter.m_current_node->m_next);
    }

    template<typename T>
    void List<T>::splice(const_iterator pos, List<T>&& other, const_iterator iter)
    {
        transfer(pos, std::move(other), iter, iter.m_current_node->m_next);
    }

    template<typename T>
    void List<T>::splice(const const_iterator& pos, List<T>& other,
        const const_iterator& first, const const_iterator& last)
    {
        transfer(pos, std::move(other), first, last);
    }

    template<typename T>
    void List<T>::splice(const_iterator pos, List<T>&& other, const_iterator first, const_iterator last)
    {
        transfer(pos, std::move(other), first, last);
    }

    template<typename T>
    auto List<T>::remove(const_reference value) -> size_type
    {
        return remove_if([value](T node_val) { return node_val == value; });
    }

    template<typename T>
    template<typename UnaryPred>
    auto List<T>::remove_if(UnaryPred predicate) -> size_type
    {
        NodeBase* temp{ m_head };

        size_type removed_count{};

        while (temp)
        {
            if (Node* node = dynamic_cast<Node*>(temp))
            {
                if (predicate(node->value()))
                {
                    NodeBase* next{ node->m_next };
                    erase(ListIterator<false>(node));
                    temp = next;
                    removed_count++;
                    continue;
                }
            }

            temp = temp->m_next;
        }

        return removed_count;
    }

    template<typename T>
    void List<T>::reverse() noexcept
    {
        if (m_head->m_next == nullptr)
        {
            return;
        }

        NodeBase* new_back{ m_head };
        NodeBase* sentinel = m_tail->m_prev->m_next;

        NodeBase* temp = m_head;
        NodeBase* prev{};

        for (size_type i = 0; i < m_size; i++)
        {
            NodeBase* next = temp->m_next;
            temp->m_next = prev;
            temp->m_prev = next;

            prev = temp;
            temp = next;
        }

        m_head = prev;
        m_tail->m_prev = new_back;
        m_tail->m_prev->m_next = sentinel;
    }

    template<typename T>
    auto List<T>::unique() -> size_type
    {
        return unique(std::equal_to<>());
    }

    template<typename T>
    template<typename BinaryPred>
    auto List<T>::unique(BinaryPred predicate) -> size_type
    {
        NodeBase* temp{ m_head };
        NodeBase* prev{};
        NodeBase* next{};

        size_type removed_count{};

        while (temp)
        {
            prev = temp;

            while (prev)
            {
                next = prev->m_next;

                Node* node_next = dynamic_cast<Node*>(next);
                Node* node_temp = dynamic_cast<Node*>(temp);
                if (node_next && node_temp)
                {
                    if (predicate(node_next->value(), node_temp->value()))
                    {
                        NodeBase* to_remove = next;
                        to_remove->m_next->m_prev = prev;

                        prev->m_next = to_remove->m_next;
                        destroy_node(to_remove);

                        removed_count++;
                        m_size--;
                        continue;
                    }
                }

                prev = prev->m_next;
                temp = temp->m_next;
            }
        }

        return removed_count;
    }

    template<typename T>
    void List<T>::sort()
    {
        sort(std::less<>());
    }

    template<typename T>
    template<typename Compare>
    void List<T>::sort(Compare comp)
    {
        if (m_size == 0)
        {
            return;
        }

        // prevent sorting sentinel node
        m_tail->m_prev->m_next = nullptr;

        m_head = merge_sort(m_head, comp);

        // find last node to attach sentinel to
        NodeBase* last{ m_head };
        while (last->m_next)
        {
            last = last->m_next;
        }
        last->m_next = m_tail;
        m_tail->m_prev = last;
    }

    /**
     * @brief Overloads operator to print all elements of List
     *
     * @tparam T type of initializer list elements
     * @param[in,out] out reference to output stream
     * @param[in] list List to print
     * @return std::ostream&
     */
    template<typename T>
    auto operator<<(std::ostream& out, const List<T>& list) -> std::ostream&
    {
        for (auto iter = list.cbegin(); iter != list.cend(); ++iter)
        {
            const T& value = *iter;
            out << value << ' ';
        }

        return out;
    }

    /**
     * @brief The relational operator compares two List objects
     *
     * @tparam T type of data stored in List
     * @param[in] lhs input container
     * @param[in] rhs input container
     * @retval true if containers are equal
     * @retval false if containers are not equal
     */
    template<typename T>
    auto operator==(const List<T>& lhs, const List<T>& rhs)
        noexcept(noexcept(*lhs.begin() == *rhs.begin())) -> bool
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }

        auto lhs_iter = lhs.cbegin();
        auto rhs_iter = rhs.cbegin();

        while (lhs_iter != lhs.cend())
        {
            if (*lhs_iter != *rhs_iter)
            {
                return false;
            }

            lhs_iter++;
            rhs_iter++;
        }

        return true;
    }

    /**
     * @brief The relational operator compares two List objects
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
    auto operator<=>(const List<T>& lhs, const List<T>& rhs)
        noexcept(noexcept(*lhs.begin() == *rhs.begin()))->std::compare_three_way_result_t<T>
    {
        auto lhs_iter = lhs.cbegin();
        auto rhs_iter = rhs.cbegin();

        while (lhs_iter != lhs.cend() && rhs_iter != rhs.cend())
        {
            auto cmp = *lhs_iter <=> *rhs_iter;
            if (cmp != 0)
            {
                return cmp;
            }

            lhs_iter++;
            rhs_iter++;
        }

        // first n elements are equal
        // check sizes
        return lhs.size() <=> rhs.size();
    }

    /**
     * @brief Exchanges content of two List containers
     *
     * @tparam T data type stored in containers
     * @param[in] lhs container to swap content
     * @param[in] rhs container to swap content
     */
    template<typename T>
    void swap(List<T>& lhs, List<T>& rhs) noexcept(noexcept(lhs.swap(rhs)))
    {
        lhs.swap(rhs);
    }

    /**
     * @brief Function erases from container all elements that are equal to \p value
     *
     * @tparam T data type stored in containers
     * @tparam U data type of \p value
     * @param[in,out] container object to remove erase elements from
     * @param[in] value value to remove from \p container
     * @return size_type number of elements removed
     */
    template<typename T, typename U>
    auto erase(List<T>& container, const U& value) -> List<T>::size_type
    {
        return erase_if(container, [&value](U node_val) { return node_val == value; });
    }

    /**
     * @brief Function erases from container all elements that satisfy the predicate \p pred
     *
     * @tparam T data type stored in containers
     * @tparam Pred predicate to check if element should be erased
     * @param[in,out] container container object to remove erase elements from
     * @param[in] pred predicate which returns \p true if the element should be erased
     * @return size_type number of elements removed
     */
    template<typename T, typename Pred>
    auto erase_if(List<T>& container, Pred pred) -> List<T>::size_type
    {
        return container.remove_if(pred);
    }

    // definitions of private methods

    template<typename T>
    void List<T>::init_node()
    {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        m_head = new NodeBase;
        m_tail = m_head;
    }

    template<typename T>
    auto List<T>::erase_element(iterator pos) -> iterator
    {
        if (pos == begin())
        {
            pop_front();
            return iterator(begin());
        }

        if (pos == (--end()))
        {
            pop_back();
            return iterator(end());
        }

        NodeBase* temp{ pos.m_current_node->m_prev };
        NodeBase* to_remove{ temp->m_next };

        temp->m_next = to_remove->m_next;
        temp->m_next->m_prev = temp;
        destroy_node(to_remove);

        m_size--;
        return iterator(temp->m_next);
    }

    template<typename T>
    template<typename... Args>
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters,-warnings-as-errors)
    auto List<T>::construct_node(NodeBase* prev_ptr, NodeBase* next_ptr, Args&&... args) -> Node*
    {
        Node* newNode{};
        try
        {
            newNode = node_alloc_traits::allocate(node_alloc, 1);
            node_alloc_traits::construct(node_alloc, newNode, std::forward<Args>(args)...);
            newNode->m_prev = prev_ptr;
            newNode->m_next = next_ptr;
        }
        catch (...)
        {
            node_alloc_traits::deallocate(node_alloc, newNode, 1);
            throw;
        }

        return newNode;
    }

    template<typename T>
    void List<T>::destroy_node(NodeBase* node_to_destroy)
    {
        if (Node* node_dyn = dynamic_cast<Node*>(node_to_destroy))
        {
            node_alloc_traits::destroy(node_alloc, node_dyn);
            node_alloc_traits::deallocate(node_alloc, node_dyn, 1);
        }
    }

    template<typename T>
    auto List<T>::if_valid_iterator(const_iterator pos) -> bool
    {
        bool valid_iterator{};

        if (pos == cbegin() || pos == cend())
        {
            return true;
        }

        for (auto it = cbegin(); it != cend(); ++it)
        {
            if (it == pos)
            {
                valid_iterator = true;
                break;
            }
        }
        return valid_iterator;
    }

    template<typename T>
    auto List<T>::distance(const_iterator first, const const_iterator& last) -> size_type
    {
        size_type dist{};
        while (first != last)
        {
            ++first;
            ++dist;
        }

        return dist;
    }

    template<typename T>
    // transfers ownership of nodes, moving entire container is not necessary
    // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
    void List<T>::transfer(const_iterator pos, List<T>&& other, const_iterator first, const const_iterator& last)
    {
        if (&other != this && other.m_size > 0)
        {
            const size_type dist = distance(first, last);
            if (dist == 0)
            {
                return;
            }

            NodeBase* temp_prev{ pos.m_current_node->m_prev }; // to append to
            NodeBase* last_to_move{ last.m_current_node->m_prev };

            // select fragment from other

            NodeBase* fragment{};
            NodeBase* fragment_end{ last_to_move->m_next };
            if (first == other.begin())
            {
                fragment = other.m_head;
                other.m_head = fragment_end;
                other.m_head->m_prev = nullptr;
            }
            else
            {
                fragment = first.m_current_node->m_prev->m_next;
                fragment->m_prev->m_next = fragment_end;
                fragment->m_prev->m_next->m_prev = first.m_current_node->m_prev;
                fragment->m_prev = nullptr;
            }

            // insert fragment into this

            if (pos == begin())
            {
                last_to_move->m_next = m_head;
                last_to_move->m_next->m_prev = last_to_move;
                m_head = fragment;
            }
            else
            {
                last_to_move->m_next = temp_prev->m_next;
                last_to_move->m_next->m_prev = last_to_move;
                temp_prev->m_next = fragment;
                temp_prev->m_next->m_prev = temp_prev;
            }

            m_size += dist;
            other.m_size -= dist;
        }
    }

    template<typename T>
    template<typename Compare>
    // Intentional recursive call for sorting nodes in top-down algorithm implementation
    // NOLINTNEXTLINE(misc-no-recursion)
    auto List<T>::merge_sort(NodeBase* source, Compare comp) -> NodeBase*
    {
        // Stop condition, one element list is already sorted
        if (source == nullptr || source->m_next == nullptr)
        {
            return source;
        }

        // Divide list into equal-sized sublists consisting of first and second half of the list
        NodeBase* left{ source };
        NodeBase* right{};

        // Use slow and fast pointer to find half of list
        NodeBase* slow{ source };
        NodeBase* fast{ source->m_next };
        while (fast && fast->m_next)
        {
            slow = slow->m_next;
            fast = fast->m_next->m_next;
        }

        // Split input list into two halfs
        right = slow->m_next;
        right->m_prev = nullptr;
        slow->m_next = nullptr;

        // Recursively sort both sub-lists
        left = merge_sort(left, comp);
        right = merge_sort(right, comp);

        // Merge sorted sublists
        NodeBase* result{ merge(left, right, comp) };
        return result;
    }

    template<typename T>
    template<typename Compare>
    // Intentional recursive call for merging nodes in top-down merge_sort algorithm implementation
    // NOLINTNEXTLINE(misc-no-recursion)
    auto List<T>::merge(NodeBase* left, NodeBase* right, Compare comp) -> NodeBase*
    {
        // Stop condition, empty element list is already sorted
        if (left == nullptr)
        {
            return right;
        }
        if (right == nullptr)
        {
            return left;
        }

        NodeBase* result{};
        Node* node_left = dynamic_cast<Node*>(left);
        Node* node_right = dynamic_cast<Node*>(right);
        if (node_left && node_right)
        {
            // Recursively merge nodes
            if (comp(node_left->m_value, node_right->m_value))
            {
                result = left;
                result->m_next = merge(left->m_next, right, comp);
            }
            else
            {
                result = right;
                result->m_next = merge(left, right->m_next, comp);
            }
            result->m_next->m_prev = result;
        }

        return result;
    }
}

#endif // !LIST_H
