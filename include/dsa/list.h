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

#include "memory.h"

#include <cstddef>
#include <cstdint>
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

    template<typename T>
    auto operator+(const List<T>& list1, const List<T>& list2) -> List<T>;

    /**
     * @brief Implements List using Node with pointer to adjacent
     *        element as internal base
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
            std::unique_ptr<NodeBase> m_next{};

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
            Node(T value)
                : m_value{ value }
            {
            }

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
            {
            }

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
                    m_current_node = m_current_node->m_next.get();
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
             * @brief Overload operator[] for ListIterator iterator access
             *
             * @param[in] index number of Node to move forward
             * @return ListIterator to Node pointed by \p index from List front
             * @retval valid ListIterator if index is valid
             * @retval nullptr if index is invalid
             */
            auto operator[](size_t index) -> ListIterator
            {
                NodeBase* temp{ m_current_node };

                for (size_t i = 0; i < index; i++)
                {
                    if (temp->m_next)
                    {
                        temp = temp->m_next.get();
                    }
                    else
                    {
                        return nullptr;
                    }
                }

                return temp;
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
         * @brief Alias for pointer to data type used in class
         *
         * @tparam T* pointer to data type
         */
        using pointer = T*;

        /**
         * @brief Alias for const pointer to data type used in class
         *
         * @tparam T* pointer to data type
         */
        using const_pointer = const T*;

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
         * @brief Alias for const iterator to data type used in class
         */
        using const_iterator = ListIterator<true>;

        /**
         * @brief Alias for iterator to data type used in class
         */
        using iterator = ListIterator<false>;

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
        List(size_t count);

        /**
         * @brief Construct a new List object of size \p count,
         * using provided \p value of type T
         *
         * @param[in] count element count
         * @param[in] value value for all nodes
         */
        List(size_t count, const T& value);

        /**
         * @brief Construct a new List object using initializer list
         *
         * @param[in] init_list initializer list of values of type T
         */
        List(const std::initializer_list<T>& init_list);

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
        auto operator=(List<T>&& other) noexcept -> List&;

        /**
         * @brief Destroy the List object
         */
        ~List();

        /**
         * @brief Function assign values to the List
         *
         * @param[in] count new size of the container
         * @param[in] value value to initialize elements of the container with
         */
        void assign(size_t count, const_reference value);

        /**
         * @brief Function assign values to the List
         *
         * @param[in] init_list values to replace List with
         */
        void assign(const std::initializer_list<T>& init_list);

        /// @todo add assign_range

        /// @todo add get_allocator

        /**
         * @brief Function returns reference to value stored in List first Node
         *
         * @return reference to data stored in List first Node
         */
        auto front() -> reference;

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
        auto back() -> reference;

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
        auto begin() -> iterator;

        /**
         * @brief Function returns const pointer to List first Node
         *
         * @return const_iterator const iterator to List first Node
         */
        auto begin() const -> const_iterator;

        /**
         * @brief Function returns const pointer to List first Node
         *
         * @return const_iterator const iterator to List first Node
         */
        [[nodiscard]] auto cbegin() const -> const_iterator;

        /**
         * @brief Function returns pointer to List last Node
         *
         * @return iterator iterator to List last Node
         */
        auto end() -> iterator;

        /**
         * @brief Function returns pointer to List last Node
         *
         * @return const_iterator const iterator to List last Node
         */
        auto end() const -> const_iterator;

        /**
         * @brief Function returns pointer to List last Node
         *
         * @return const_iterator const iterator to List last Node
         */
        [[nodiscard]] auto cend() const -> const_iterator;

        /// @todo add rbegin

        /// @todo add crbegin

        /// @todo add rend

        /// @todo add crend

        /**
         * @brief Function checks if container has no elements
         *
         * @retval true if container is empty
         * @retval false if container is not empty
         */
        [[nodiscard]] auto empty() const -> bool;

        /**
         * @brief Function returns List size
         *
         * @return size_t number of elements in container
         */
        [[nodiscard]] auto size() const -> size_t;

        /**
         * @brief Function returns maximum number of elements container can hold
         *
         * @return size_t maximum number of elements
         */
        [[nodiscard]] auto max_size() const -> size_t;

        /**
         * @brief Function removes all elements of List
         */
        void clear();

        /**
         * @brief Function inserts new Node before specified \p pos
         *
         * @param[in] pos const_iterator to insert element before
         * @param[in] value element of type T to be inserted before \p pos
         * @return pointer to List element
         * @retval iterator to inserted \p value
         * @retval pos if no element was inserted
         */
        auto insert(const const_iterator& pos, const_reference value) -> iterator;

        /**
         * @brief Function inserts new Node before specified \p pos
         *
         * @param[in] pos const_iterator to insert element before
         * @param[in] count number of elements to insert before \p pos
         * @param[in] value element of type T to be inserted
         * @return pointer to List element
         * @retval iterator to inserted \p value
         * @retval pos if no element was inserted
         */
        auto insert(const const_iterator& pos, size_t count, const_reference value) -> iterator;

        /**
         * @brief Function inserts new Node before specified \p pos
         *
         * @param[in] pos const_iterator to insert element before
         * @param[in] init_list initializer_list with elements to insert before \p pos
         * @return pointer to List element
         * @retval iterator to first inserted element
         * @retval pos if no element was inserted
         */
        auto insert(const const_iterator& pos, std::initializer_list<T> init_list) -> iterator;

        /// @todo add insert_range

        /// @todo add emplace

        /**
        * @brief Function erases Node object at specified \p pos
        *
        * @param[in] pos iterator to element to erase
        * @return iterator following erased element
        * @retval iterator to element following \p pos
        * @retval begin iterator if \p pos was first element prior to removal
        * @retval end iterator if \p pos was last element prior to removal
        */
        auto erase(iterator pos) -> iterator;

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
         * @retval last iterator if \p first to p\ last is empty range
         */
        auto erase(iterator first, iterator last) -> iterator;

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
         */
        void push_back(T value);

        /// @todo add emplace_back

        /// @todo add append_range

        /**
         * @brief Function removes last Node of List
         */
        void pop_back();

        /**
         * @brief Function adds new Node at the beginning of List
         *
         * @param[in] value element of type T
         */
        void push_front(T value);

        /// @todo add emplace_front

        /// @todo add prepend_range

        /**
         * @brief Function removes first Node of List
         */
        void pop_front();

        /**
         * @brief Function resize List to specified number of elements
         *
         * @param[in] count new size of container
         */
        void resize(size_t count);

        /**
         * @brief Function resize List to specified number of elements
         *
         * @param[in] count count new size of container
         * @param[in] value value to initialize new elements
         */
        void resize(size_t count, const_reference value);

        /**
         * @brief Function swaps content of two List objects
         *
         * @param[in,out] other object to swap content with
         */
        void swap(List<T>& other) noexcept;

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
         * @brief Function moves elements from other List object
         *
         * @param[in] pos const_iterator before which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @details Content of other object will be taken by constructed object
         */
        void splice(const const_iterator& pos, List<T>& other);

        /**
         * @brief Function moves elements from other List object
         *
         * @param[in] pos const_iterator before which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @details Content of other object will be taken by constructed object
         */
        void splice(const_iterator pos, List<T>&& other);

        /**
         * @brief Function moves elements from other List object
         *
         * @param[in] pos const_iterator before which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] iter const_iterator pointing to element to move
         * @details Content of other object will be taken by constructed object
         */
        void splice(const const_iterator& pos, List<T>& other, const const_iterator& iter);

        /**
         * @brief Function moves elements from other List object
         *
         * @param[in] pos const_iterator before which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] iter const_iterator pointing to element to move
         * @details Content of other object will be taken by constructed object
         */
        void splice(const_iterator pos, List<T>&& other, const_iterator iter);

        /**
         * @brief Function moves elements in range [first, last) from other List object
         *
         * @param[in] pos const_iterator before which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] first const_iterator pointing to first element to move
         * @param[in] last const_iterator pointing to element after last taken element
         * @details Content of other object will be taken by constructed object
         */
        void splice(const const_iterator& pos, List<T>& other, const const_iterator& first, const const_iterator& last);

        /**
         * @brief Function moves elements in range [first, last) from other List object
         *
         * @param[in] pos const_iterator before which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] first const_iterator pointing to first element to move
         * @param[in] last const_iterator pointing to element after last taken element
         * @details Content of other object will be taken by constructed object
         */
        void splice(const_iterator pos, List<T>&& other, const_iterator first, const_iterator last);

        /**
         * @brief Function removes all elements equal to \p value
         *
         * @param[in] value value of elements to remove
         */
        void remove(const_reference value);

        /// @todo add remove_if

        /**
         * @brief Function reverts in place Nodes of List
         */
        void reverse();

        /**
         * @brief Function removes consecutive duplicated elements
         * @details Only the first occurrence of given element in each group is preserved
         */
        void unique();

        /// @todo add sort

        /**
         * @brief Append elements of another List to base container
         *
         * @tparam T type of data stored in List Node
         * @param[in] other List to read elements from
         * @return List<T>&
         */
        auto operator+=(const List<T>& other) -> List<T>&
        {
            for (auto it = other.cbegin(); it != other.cend(); ++it)
            {
                push_back(*it);
            }

            return *this;
        }

        /**
         * @brief push_back elements of another List to base container
         *
         * @param[in] init_list initializer_list to read elements from
         * @return List<T>&
         */
        auto operator+=(const std::initializer_list<T> init_list) -> List<T>&
        {
            for (const auto& item : init_list)
            {
                push_back(item);
            }

            return *this;
        }

        /**
         * @brief Function returns pointer to specific Node of List
         *
         * @param[in] index index of element
         * @return Node*
         * @retval Node* if index is valid
         * @retval nullptr if invalid index
         */
        [[nodiscard]] auto get(size_t index) const -> Node*;

        /**
         * @brief Function sets value of specifed Node of List
         *
         * @param[in] index index of element to be modified
         * @param[in] value to overwrite Node at index
         * @return operation status
         * @retval true if value of Node was overwritten
         * @retval false if invalid index
         */
        auto set(size_t index, T value) -> bool;

    private:

        /**
         * @brief Construct new object based on two List objects
         *
         * Forward friend declaration of List operator+
         *
         * @tparam T type of data stored in List Node
         * @param[in] list1 input List
         * @param[in] list2 input List
         * @return List<T> List<T> with content of two input lists
         */
        friend auto operator+<>(const List<T>& list1, const List<T>& list2)->List<T>;

        /**
         * @brief Function add end node located just after last user created data
         * Node is used by iterators indicating end of container
         */
        void init_node()
        {
            if (m_head == nullptr)
            {
                m_head = std::make_unique<NodeBase>();
                m_tail = m_head.get();
            }
        }

        /**
         * @brief Function remove next element
         *
         * @param[in] iterator to element to which will be erased
         * @return iterator to element following \p pos
         */
        auto erase_element(iterator pos) -> iterator
        {
            if (!if_valid_iterator(pos))
            {
                return nullptr;
            }

            if (pos == begin())
            {
                pop_front();
                return iterator(begin());
            }

            if (pos == end() || pos == m_tail)
            {
                pop_back();
                return iterator(end());
            }

            NodeBase* temp{ pos.m_current_node->m_prev };
            NodeBase* to_remove{ temp->m_next.get() };

            temp->m_next = std::move(to_remove->m_next);
            temp->m_next->m_prev = temp;

            m_size--;
            return iterator(temp->m_next.get());
        }

        /**
        * @brief Function inserts new Node before specified List iterator
        *
        * @param[in] pos iterator to insert element before
        * @param[in] value element of type T to be inserted
        * @return iterator to list element
        * @retval iterator to inserted element
        * @retval iterator to \p pos if no element was inserted
        */
        auto insert_element_before(iterator pos, const_reference value) -> iterator
        {
            if (!if_valid_iterator(pos))
            {
                return nullptr;
            }

            if (pos == begin())
            {
                push_front(value);
                return begin();
            }

            if (pos == end())
            {
                push_back(value);
                return end().m_current_node->m_prev;
            }

            NodeBase* temp{ pos.m_current_node->m_prev };

            auto newNode = std::make_unique<Node>(value);
            newNode->m_next = std::move(temp->m_next);
            newNode->m_prev = temp;

            temp->m_next = std::move(newNode);
            temp->m_next->m_next->m_prev = temp->m_next.get();

            m_size++;
            return iterator(temp->m_next.get());
        }

        /**
         * @brief Function checks List contains iterator
         *
         * @param[in] pos iterator to check
         * @return bool \p pos iterator status
         * @return true if \p pos belong to List
         * @return false if otherwise
         */
        auto if_valid_iterator(const_iterator pos) -> bool
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

        /**
         * @brief Function calculate number of elements from first to last
         *
         * @tparam T type of input objects
         * @param[in] first const_iterator pointing first element
         * @param[in] last const_iterator pointing to last (inclusive) element
         * @return size_t number of elements between input elements
         */
        auto distance(const_iterator first, const const_iterator& last) -> size_t;

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

        std::unique_ptr<NodeBase> m_head{};
        NodeBase* m_tail{};
        size_t m_size{};
    };

    template<typename T>
    List<T>::List()
    {
        init_node();
    }

    template<typename T>
    List<T>::List(size_t count)
        : List(count, T{})
    {
    }

    template<typename T>
    List<T>::List(size_t count, const T& value)
    {
        init_node();

        for (size_t i = 0; i < count; i++)
        {
            push_front(value);
        }
    }

    template<typename T>
    List<T>::List(const std::initializer_list<T>& init_list)
    {
        for (const auto& item : init_list)
        {
            push_back(item);
        }
    }

    template<typename T>
    List<T>::List(const List<T>& other)
    {
        for (size_t i = 0; i < other.size(); i++)
        {
            push_back(other.get(i)->value());
        }
    }

    template<typename T>
    auto List<T>::operator=(const List<T>& other) -> List<T>&
    {
        if (&other != this)
        {
            while (m_head->m_next)
            {
                pop_front();
            }

            for (size_t i = 0; i < other.size(); i++)
            {
                push_back(other.get(i)->value());
            }
        }

        return *this;
    }

    template<typename T>
    List<T>::List(List<T>&& other) noexcept
    {
        operator=(std::move(other));
    }

    template<typename T>
    auto List<T>::operator=(List<T>&& other) noexcept -> List<T>&
    {
        if (&other != this)
        {
            clear();

            m_head = std::move(other.m_head);
            m_tail = std::move(other.m_tail);
            m_size = other.m_size;

            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0;
        }

        return *this;
    }

    template<typename T>
    List<T>::~List()
    {
        clear();
    }

    template<typename T>
    void List<T>::assign(size_t count, const_reference value)
    {
        clear();

        for (size_t i = 0; i < count; i++)
        {
            push_back(value);
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
    auto List<T>::begin() -> typename List<T>::iterator
    {
        return iterator(m_head.get());
    }

    template<typename T>
    auto List<T>::begin() const -> typename List<T>::const_iterator
    {
        return const_iterator(m_head.get());
    }

    template<typename T>
    auto List<T>::cbegin() const -> typename List<T>::const_iterator
    {
        return begin();
    }

    template<typename T>
    auto List<T>::end() -> typename List<T>::iterator
    {
        return iterator(m_tail);
    }

    template<typename T>
    auto List<T>::end() const -> typename List<T>::const_iterator
    {
        return const_iterator(m_tail);
    }

    template<typename T>
    auto List<T>::cend() const -> typename List<T>::const_iterator
    {
        return end();
    }

    template<typename T>
    auto List<T>::empty() const -> bool
    {
        return m_size == 0;
    }

    template<typename T>
    auto List<T>::size() const -> size_t
    {
        return m_size;
    }

    template<typename T>
    auto List<T>::max_size() const -> size_t
    {
        return std::numeric_limits<size_t>::max();
    }

    template<typename T>
    void List<T>::clear()
    {
        if (m_head && m_head->m_next)
        {
            while (m_head->m_next)
            {
                m_head = std::move(m_head->m_next);
            }

            m_size = 0;
            m_tail->m_prev = nullptr;
        }
    }

    template<typename T>
    auto List<T>::insert(const const_iterator& pos, const_reference value) -> typename List<T>::iterator
    {
        return insert(pos, 1, value);
    }

    template<typename T>
    auto List<T>::insert(const const_iterator& pos, size_t count, const_reference value) -> typename List<T>::iterator
    {
        iterator iter{ pos.m_current_node };

        if (!if_valid_iterator(pos))
        {
            return nullptr;
        }

        for (size_t i = 0; i < count; i++)
        {
            iter = insert_element_before(iter, value);
        }

        return iter;
    }

    template<typename T>
    auto List<T>::insert(const const_iterator& pos, std::initializer_list<T> init_list) -> typename List<T>::iterator
    {
        iterator iter(pos.m_current_node);

        if (!if_valid_iterator(pos))
        {
            return nullptr;
        }

        for (const auto& val : init_list)
        {
            iter = insert_element_before(iter, val);
            ++iter;
        }

        return iter;
    }

    template<typename T>
    auto List<T>::erase(iterator pos) -> typename List<T>::iterator
    {
        if (!if_valid_iterator(pos))
        {
            return nullptr;
        }

        return erase_element(pos);
    }

    template<typename T>
    auto List<T>::erase(iterator first, iterator last) -> typename List<T>::iterator
    {
        if (!if_valid_iterator(first) || !if_valid_iterator(last))
        {
            return nullptr;
        }

        const size_t dist = distance(first, last);
        if (dist == 0)
        {
            return last;
        }

        iterator iter(first.m_current_node);
        for (size_t i = 0; i < dist; i++)
        {
            iter = erase_element(iter);
        }

        return iter;
    }

    template<typename T>
    void List<T>::push_front(T value)
    {
        init_node();

        auto newNode = std::make_unique<Node>(value);
        if (!m_head->m_next)
        {
            newNode->m_next = std::move(m_head);
            m_head = std::move(newNode);
            m_tail->m_prev = m_head.get();
        }
        else
        {
            m_head->m_prev = newNode.get();
            newNode->m_next = std::move(m_head);
            m_head = std::move(newNode);
        }

        m_size++;
    }

    template<typename T>
    void List<T>::pop_front()
    {
        if (m_size == 0)
        {
            return;
        }

        if (m_size == 1)
        {
            m_head = std::move(m_head->m_next);
            m_tail->m_prev = nullptr;
        }
        else
        {
            m_head = std::move(m_head->m_next);
            m_head->m_prev = nullptr;
        }

        m_size--;
    }

    template<typename T>
    void List<T>::push_back(T value)
    {
        init_node();

        auto newNode = std::make_unique<Node>(value);

        if (!m_head->m_next) // only sentinel exists
        {
            newNode->m_next = std::move(m_head);
            m_head = std::move(newNode);
            m_tail->m_prev = m_head.get();
        }
        else
        {
            newNode->m_prev = m_tail->m_prev;
            newNode->m_next = std::move(m_tail->m_prev->m_next);
            m_tail->m_prev = newNode.get();
            m_tail->m_prev->m_prev->m_next = std::move(newNode);
        }

        m_size++;
    }

    template<typename T>
    void List<T>::pop_back()
    {
        if (m_size == 0)
        {
            return;
        }

        if (m_size == 1)
        {
            m_head = std::move(m_head->m_next);
            m_tail->m_prev = nullptr;
        }
        else
        {
            NodeBase* temp{ m_tail->m_prev->m_prev };
            m_tail->m_prev->m_prev->m_next = std::move(m_tail->m_prev->m_next);
            m_tail->m_prev = temp;
        }

        m_size--;
    }

    template<typename T>
    void List<T>::resize(size_t count)
    {
        resize(count, T{});
    }

    template<typename T>
    void List<T>::resize(size_t count, const_reference value)
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
    void List<T>::swap(List<T>& other) noexcept
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
    // transfers ownership of nodes, moving entire container is not necessary
    // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
    void List<T>::merge(List<T>&& other)
    {
        if (&other != this)
        {
            if (m_size != 0)
            {
                auto temp_head = std::make_unique<Node>(0);
                NodeBase* temp_tail = temp_head.get();

                std::unique_ptr<NodeBase> to_move{};
                std::unique_ptr<NodeBase> to_return{};

                std::unique_ptr<NodeBase> sentinel_this{ std::move(m_tail->m_prev->m_next) };
                const std::unique_ptr<NodeBase> sentinel_other{ std::move(other.m_tail->m_prev->m_next) };

                while (m_head && other.m_head)
                {
                    Node* node_this = dynamic_cast<Node*>(m_head.get());
                    Node* node_other = dynamic_cast<Node*>(other.m_head.get());

                    if (node_this && node_other)
                    {
                        if (node_this->value() <= node_other->value())
                        {
                            to_move = std::move(m_head);
                            to_move->m_prev = temp_tail;

                            to_return = std::move(to_move->m_next);
                            temp_tail->m_next = std::move(to_move);
                            m_head = std::move(to_return);
                        }
                        else
                        {
                            to_move = std::move(other.m_head);
                            to_move->m_prev = temp_tail;

                            to_return = std::move(to_move->m_next);
                            temp_tail->m_next = std::move(to_move);
                            other.m_head = std::move(to_return);
                        }

                        temp_tail = temp_tail->m_next.get();
                    }
                }

                NodeBase* last{};
                if (m_head == nullptr) // other.m_head attached at the end
                {
                    last = sentinel_other->m_prev;
                    other.m_head->m_prev = temp_tail;
                    temp_tail->m_next = std::move(other.m_head);
                }
                else // this.m_head attached at the end
                {
                    last = sentinel_this->m_prev;
                    m_head->m_prev = temp_tail;
                    temp_tail->m_next = std::move(m_head);
                }
                last->m_next = std::move(sentinel_this);
                last->m_next->m_prev = last;

                m_head = std::move(temp_head->m_next);
                m_head->m_prev = nullptr;

                m_size += other.m_size;
                other.m_size = 0;
            }
            else
            {
                swap(other);
            }
        }
    }

    template<typename T>
    auto List<T>::distance(const_iterator first, const const_iterator& last) -> size_t
    {
        size_t dist{};
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
            const size_t dist = distance(first, last);
            if (first == last || dist == 0)
            {
                return;
            }

            NodeBase* temp_prev{ pos.m_current_node->m_prev }; // to append to
            NodeBase* last_to_move{ last.m_current_node->m_prev };

            // select fragment from other

            std::unique_ptr<NodeBase> fragment{};
            std::unique_ptr<NodeBase> fragment_end{ std::move(last_to_move->m_next) };
            if (first == other.begin())
            {
                fragment = std::move(other.m_head);
                other.m_head = std::move(fragment_end);
                other.m_head->m_prev = nullptr;
            }
            else
            {
                fragment = std::move(first.m_current_node->m_prev->m_next);
                fragment->m_prev->m_next = std::move(fragment_end);
                fragment->m_prev->m_next->m_prev = first.m_current_node->m_prev;
                fragment->m_prev = nullptr;
            }

            // insert fragment into this

            if (pos == begin())
            {
                last_to_move->m_next = std::move(m_head);
                last_to_move->m_next->m_prev = last_to_move;
                m_head = std::move(fragment);
            }
            else
            {
                last_to_move->m_next = std::move(temp_prev->m_next);
                last_to_move->m_next->m_prev = last_to_move;
                temp_prev->m_next = std::move(fragment);
                temp_prev->m_next->m_prev = temp_prev;
            }

            m_size += dist;
            other.m_size -= dist;
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
        transfer(pos, std::move(other), iter, iter.m_current_node->m_next.get());
    }

    template<typename T>
    void List<T>::splice(const_iterator pos, List<T>&& other, const_iterator iter)
    {
        transfer(pos, std::move(other), iter, iter.m_current_node->m_next.get());
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
    void List<T>::remove(const_reference value)
    {
        NodeBase* temp{ m_head.get() };
        NodeBase* next{};

        while (temp->m_next.get())
        {
            next = temp->m_next.get();
            if (next == nullptr)
            {
                return;
            }

            if (Node* node = dynamic_cast<Node*>(m_head.get()))
            {
                if (node->value() == value)
                {
                    pop_front();
                    temp = m_head.get();
                    continue;
                }
            }

            if (next && next != m_tail && next->m_next != nullptr)
            {
                Node* node = dynamic_cast<Node*>(next);
                if (node->value() == value)
                {
                    erase(ListIterator<false>(node));
                    continue;
                }
            }

            temp = temp->m_next.get();
        }
    }

    template<typename T>
    void List<T>::reverse()
    {
        if (m_head->m_next == nullptr)
        {
            return;
        }

        NodeBase* new_back{ m_head.get() };
        std::unique_ptr<NodeBase> sentinel = std::move(m_tail->m_prev->m_next);

        std::unique_ptr<NodeBase> temp = std::move(m_head);
        std::unique_ptr<NodeBase> prev{};

        for (size_t i = 0; i < m_size; i++)
        {
            std::unique_ptr<NodeBase> next = std::move(temp->m_next);
            temp->m_next = std::move(prev);
            temp->m_prev = next.get();

            prev = std::move(temp);
            temp = std::move(next);
        }

        m_head = std::move(prev);
        m_tail->m_prev = new_back;
        m_tail->m_prev->m_next = std::move(sentinel);
    }

    template<typename T>
    void List<T>::unique()
    {
        NodeBase* temp{ m_head.get() };
        NodeBase* prev{};
        NodeBase* next{};
        while (temp)
        {
            prev = temp;

            while (prev)
            {
                next = prev->m_next.get();

                Node* node_next = dynamic_cast<Node*>(next);
                Node* node_temp = dynamic_cast<Node*>(temp);
                if (node_next && node_temp)
                {
                    if (node_next->value() == node_temp->value())
                    {
                        NodeBase* to_remove = next;

                        if (to_remove->m_next)
                        {
                            to_remove->m_next->m_prev = prev;
                        }
                        else // temp was last node
                        {
                            m_tail = prev;
                        }

                        prev->m_next = std::move(to_remove->m_next);

                        m_size--;
                        continue;
                    }
                }

                prev = prev->m_next.get();
                temp = temp->m_next.get();
            }
        }
    }

    template<typename T>
    auto List<T>::get(size_t index) const -> typename List<T>::Node*
    {
        if (index >= m_size)
        {
            return nullptr;
        }

        NodeBase* temp{};

        // select list end to look for selected index
        enum Mode : std::uint8_t { FRONT, BACK, AUTO };
        constexpr Mode mode = Mode::AUTO;


        if constexpr (mode == FRONT)
        {
            // count nodes from front
            temp = m_head.get();
            for (size_t i = 0; i < index; i++)
            {
                temp = temp->m_next.get();
            }
        }
        else if constexpr (mode == BACK)
        {
            // count nodes from back
            temp = m_tail->m_prev;
            for (size_t i = m_size - 1; i > index; i--)
            {
                temp = temp->m_prev;
            }
        }
        else // mode == AUTO
        {
            // optimize counting nodes from front or back
            if (index < m_size / 2)
            {
                temp = m_head.get();
                for (size_t i = 0; i < index; i++)
                {
                    temp = temp->m_next.get();
                }
            }
            else
            {
                temp = m_tail->m_prev;
                for (size_t i = m_size - 1; i > index; i--)
                {
                    temp = temp->m_prev;
                }
            }
        }

        return dynamic_cast<Node*>(temp);
    }

    template<typename T>
    auto List<T>::set(size_t index, T value) -> bool
    {
        Node* temp = get(index);
        if (temp)
        {
            temp->m_value = value;
            return true;
        }

        return false;
    }

    /**
     * @brief Construct new object based on two List objects
     *
     * @tparam T type of data stored in List Node
     * @param[in] list1 input List
     * @param[in] list2 input List
     * @return List<T> List<T> with content of two input lists
     */
    template<typename T>
    auto operator+(const List<T>& list1, const List<T>& list2) -> List<T>
    {
        List<T> temp(list1);

        for (auto iter = list2.cbegin(); iter != list2.cend(); ++iter)
        {
            T value = *iter;
            temp.push_back(value);
        }

        return temp;
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
        if (list.empty())
        {
            return out;
        }

        for (auto iter = list.cbegin(); iter != list.cend(); ++iter)
        {
            T value = *iter;
            out << value << ' ';
        }

        return out;
    }

    /**
     * @brief The relational operator compares two List objects
     *
     * @tparam T type of data stored in List
     * @param[in] list1 input container
     * @param[in] list2 input container
     * @retval true if containers are equal
     * @retval false if containers are not equal
     */
    template<typename T>
    auto operator==(const List<T>& list1, const List<T>& list2) -> bool
    {
        if (list1.size() != list2.size())
        {
            return false;
        }

        auto list1_iter = list1.cbegin();
        auto list2_iter = list2.cbegin();

        while (list1_iter != list1.cend() && list2_iter != list2.cend())
        {
            if (*list1_iter != *list2_iter)
            {
                return false;
            }

            list1_iter++;
            list2_iter++;
        }

        return true;
    }

    /**
     * @brief The relational operator compares two List objects
     *
     * @tparam T type of data stored in List
     * @param[in] list1 input container
     * @param[in] list2 input container
     * @retval true if containers are not equal
     * @retval false if containers are equal
     */
    template<typename T>
    auto operator!=(const List<T>& list1, const List<T>& list2) -> bool
    {
        return !(operator==(list1, list2));
    }

    /**
     * @brief The relational operator compares two List objects
     *
     * @tparam T type of data stored in List
     * @param[in] list1 input container
     * @param[in] list2 input container
     * @retval true if the content of \p list1 are lexicographically
     *         less than the content of \p list2
     * @retval false otherwise
     */
    template<typename T>
    auto operator<(const List<T>& list1, const List<T>& list2) -> bool
    {
        auto list1_iter = list1.cbegin();
        auto list2_iter = list2.cbegin();

        while (list1_iter != list1.cend() && list2_iter != list2.cend())
        {
            if (*list1_iter > *list2_iter)
            {
                return false;
            }
            if (*list1_iter < *list2_iter)
            {
                return true;
            }

            list1_iter++;
            list2_iter++;
        }

        // first n elements are equal
        // check sizes
        return list1.size() < list2.size();
    }

    /**
     * @brief The relational operator compares two List objects
     *
     * @tparam T type of data stored in List
     * @param[in] list1 input container
     * @param[in] list2 input container
     * @retval true if the content of \p list1 are lexicographically
     *         greater than the content of \p list2
     * @retval false otherwise
     */
    template<typename T>
    auto operator>(const List<T>& list1, const List<T>& list2) -> bool
    {
        return operator<(list2, list1);
    }

    /**
     * @brief The relational operator compares two List objects
     *
     * @tparam T type of data stored in List
     * @param[in] list1 input container
     * @param[in] list2 input container
     * @retval true if the content of \p list1 are lexicographically
     *         less or equal than the content of \p list2
     * @retval false otherwise
     */
    template<typename T>
    auto operator<=(const List<T>& list1, const List<T>& list2) -> bool
    {
        return !(operator>(list1, list2));
    }

    /**
     * @brief The relational operator compares two List objects
     *
     * @tparam T type of data stored in List
     * @param[in] list1 input container
     * @param[in] list2 input container
     * @retval true if the content of \p list1 are lexicographically
     *         greater or equal than the content of \p list2
     * @retval false otherwise
     */
    template<typename T>
    auto operator>=(const List<T>& list1, const List<T>& list2) -> bool
    {
        return !(operator<(list1, list2));
    }

    /// @todo implement non-member specialized swap function

    /// @todo implement non-member specialized erase function

    /// @todo implement non-member specialized erase_if function

}

// test std::ranges::bidirectional_range concept
static_assert(std::ranges::bidirectional_range<dsa::List<int>>);
static_assert(std::ranges::bidirectional_range<const dsa::List<int>>);

#endif // !LIST_H
