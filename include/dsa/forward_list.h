/**
 * @file forward_list.h
 * @brief This file contains implementation of ForwardList class
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include "memory.h"

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <ranges>
#include <utility>

namespace dsa
{

    template<typename T>
    class ForwardList;

    template<typename T>
    auto operator+(const ForwardList<T>& list1, const ForwardList<T>& list2) -> ForwardList<T>;

    /**
     * @brief Implements ForwardList using Node with pointer to next element
     *        as internal base
     *
     * @tparam T type of data stored in ForwardList Node
     */
    template<typename T>
    class ForwardList
    {
    public:

        /**
         * @brief Struct implements base pointer used by ForwardList
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

            friend class ForwardList<T>;

            /**
             * @brief Pointer to next node
             */
            std::unique_ptr<NodeBase> m_next{};
        };

        /**
         * @brief Implements Node class with user data
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
             * @return T& reference to value stored in Node
             */
            auto value() -> T&
            {
                return m_value;
            }

            /**
             * @brief Function returns value stored in Node object
             *
             * @return T to value stored in Node
             */
            [[nodiscard]] auto value() const -> T
            {
                return m_value;
            }

        private:

            /**
             * @brief Forward friend declaration of ForwardList
             */
            friend class ForwardList;

            T m_value{};
        };

        /**
         * @brief Implements ForwardListIterator
         *
         * Class is used to generate iterator and const_iterator types.
         * Template variable \p IF_CONST control whether reference
         * or const reference is returned to underlying data type
         *
         * @tparam IF_CONST if \p true generate iterator with const reference to underlying data type
         */
        template<bool IF_CONST>
        class ForwardListIterator
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
             * @brief Alias for forward iterator tag, define iterator direction
             *
             * Used by STL to define iterator features.
             * Forward iterator allows iteration only in forward direction.
             */
            using iterator_category = std::forward_iterator_tag;

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
             * @brief Construct a new ForwardListIterator object
             */
            ForwardListIterator() noexcept = default;

            /**
             * @brief Construct a new ForwardListIterator object
             *
             * @param[in] node input Node
             */
            ForwardListIterator(NodeBase* node) noexcept
                : m_current_node{ node }
            {
            }

            /**
             * @brief Overload operator= to assign \p node to currently pointed ForwardListIterator
             *
             * @param[in] node input Node
             * @return ForwardListIterator& reference to updated Node
             */
            auto operator=(NodeBase* node) -> ForwardListIterator&
            {
                this->m_current_node = node;
                return *this;
            }

            /**
             * @brief Overload pre-increment operator++ to point ForwardListIterator at next Node
             *
             * @return ForwardListIterator& reference to next Node
             */
            auto operator++() -> ForwardListIterator&
            {
                if (m_current_node)
                {
                    m_current_node = m_current_node->m_next.get();
                }

                return *this;
            }

            /**
             * @brief Overload post-increment operator++ to point ForwardListIterator at next Node
             *
             * @return ForwardListIterator& reference to next ForwardListIterator
             */
            auto operator++(int) -> ForwardListIterator
            {
                const ForwardListIterator iterator = *this;
                ++(*this);
                return iterator;
            }

            /**
             * @brief Overload operator!= for ForwardListIterator objects comparison
             *
             * @param[in] other input ForwardListIterator of \p other object
             * @return bool comparison result
             * @retval true if ForwardListIterator objects are the same
             * @retval false if ForwardListIterator objects are different
             */
            auto operator==(const ForwardListIterator<IF_CONST>& other) const -> bool
            {
                return m_current_node == other.m_current_node;
            }

            /**
             * @brief Overload operator!= for ForwardListIterator objects comparison
             *
             * @param[in] other input ForwardListIterator of \p other object
             * @return bool comparison result
             * @retval true if ForwardListIterator objects are different
             * @retval false if ForwardListIterator objects are the same
             */
            auto operator!=(const ForwardListIterator<IF_CONST>& other) const -> bool
            {
                return !operator==(other);
            }

            /**
             * @brief Overload operator[] for ForwardListIterator iterator access
             *
             * @param[in] index number of Node to move forward
             * @return ForwardListIterator to Node pointed by \p index from ForwardList front
             * @retval valid ForwardListIterator if index is valid
             * @retval nullptr if index is invalid
             */
            auto operator[](size_t index) -> ForwardListIterator
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
             * @brief convert ForwardListIterator to Basic_Const_Iterator
             */
            operator ForwardListIterator<true>()
            {
                return ForwardListIterator<true>(m_current_node);
            }

        private:

            /**
             * @brief Forward friend declaration of ForwardList
             */
            friend class ForwardList;

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
        using const_iterator = ForwardListIterator<true>;

        /**
         * @brief Alias for iterator to data type used in class
         */
        using iterator = ForwardListIterator<false>;

        /**
         * @brief Construct a new ForwardList object
         */
        ForwardList();

        /**
         * @brief Construct a new ForwardList object of size \p count,
         * using default value of type T
         *
         * @param[in] count element count
         */
        ForwardList(size_t count);

        /**
         * @brief Construct a new ForwardList object of size \p count,
         * using provided \p value of type T
         *
         * @param[in] count element count
         * @param[in] value value for all nodes
         */
        ForwardList(size_t count, const T& value);

        /**
         * @brief Construct a new ForwardList object using initializer list
         *
         * @param[in] init_list initializer list of values of type T
         */
        ForwardList(const std::initializer_list<T>& init_list);

        /**
         * @brief Construct a new ForwardList object using copy constructor
         *
         * @param[in] other ForwardList object of type T
         */
        ForwardList(const ForwardList<T>& other);

        /**
         * @brief Constructs ForwardList using copy assignment
         *
         * @param[in] other ForwardList object of type T
         * @return ForwardList& reference to ForwardList object
         */
        auto operator=(const ForwardList<T>& other) -> ForwardList&;

        /**
         * @brief Construct a new ForwardList object using move constructor
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other ForwardList object of type T
         */
        ForwardList(ForwardList<T>&& other) noexcept;

        /**
         * @brief Assign ForwardList object using move assignment
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other ForwardList object of type T
         * @return ForwardList& reference to ForwardList object
         */
        auto operator=(ForwardList<T>&& other) noexcept -> ForwardList&;

        /**
         * @brief Destroy the ForwardList object
         */
        ~ForwardList();

        /**
         * @brief Function assign values to the ForwardList
         *
         * @param[in] count new size of the container
         * @param[in] value value to initialize elements of the container with
         */
        void assign(size_t count, const_reference value);

        /**
         * @brief Function assign values to the ForwardList
         *
         * @param[in] init_list values to replace ForwardList with
         */
        void assign(const std::initializer_list<T>& init_list);

        /**
         * @brief Function returns reference to value stored in ForwardList first Node
         *
         * @return reference to data stored in ForwardList first Node
         */
        auto front() -> reference;

        /**
         * @brief Function returns const reference value stored in ForwardList first Node
         *
         * @return const reference to data stored in ForwardList first Node
         */
        [[nodiscard]] auto front() const -> const_reference;

        /**
         * @brief Function returns iterator just before ForwardList first Node
         *
         * @return iterator iterator just before ForwardList first Node
         */
        auto before_begin() noexcept -> iterator;

        /**
         * @brief Function returns const_iterator just before ForwardList first Node
         *
         * @return const_iterator iterator just before ForwardList first Node
         */
        [[nodiscard]] auto before_begin() const noexcept -> const_iterator;

        /**
         * @brief Function returns const_iterator just before ForwardList first Node
         *
         * @return const_iterator iterator just before ForwardList first Node
         */
        [[nodiscard]] auto cbefore_begin() const noexcept -> const_iterator;

        /**
         * @brief Function returns pointer to ForwardList first Node
         *
         * @return iterator iterator to ForwardList first Node
         */
        auto begin() noexcept -> iterator;

        /**
         * @brief Function returns const pointer to ForwardList first Node
         *
         * @return const_iterator const iterator to ForwardList first Node
         */
        auto begin() const noexcept -> const_iterator;

        /**
         * @brief Function returns const pointer to ForwardList first Node
         *
         * @return const_iterator const iterator to ForwardList first Node
         */
        [[nodiscard]] auto cbegin() const noexcept -> const_iterator;

        /**
         * @brief Function returns pointer to ForwardList last Node
         *
         * @return iterator iterator to ForwardList last Node
         */
        auto end() noexcept -> iterator;

        /**
         * @brief Function returns pointer to ForwardList last Node
         *
         * @return const_iterator const iterator to ForwardList last Node
         */
        auto end() const noexcept -> const_iterator;

        /**
         * @brief Function returns pointer to ForwardList last Node
         *
         * @return const_iterator const iterator to ForwardList last Node
         */
        [[nodiscard]] auto cend() const noexcept -> const_iterator;

        /**
         * @brief Function checks if container has no elements
         *
         * @retval true if container is empty
         * @retval false if container is not empty
         */
        [[nodiscard]] auto empty() const -> bool;

        /**
         * @brief Function returns maximum number of elements container can hold
         *
         * @return size_t maximum number of elements
         */
        [[nodiscard]] auto max_size() const noexcept -> size_t;

        /**
         * @brief Function removes all elements of ForwardList
         */
        void clear();

        /**
         * @brief Function inserts new Node after specified ForwardList iterator
         *
         * @param[in] pos const_iterator to insert element after
         * @param[in] value element of type T to be inserted after \p pos
         * @return pointer to ForwardList element
         * @retval iterator to inserted \p value
         * @retval pos if no element was inserted
         */
        auto insert_after(const const_iterator& pos, const_reference value) -> iterator;

        /**
         * @brief Function inserts new Node after specified ForwardList const_iterator
         *
         * @param[in] pos const_iterator to insert element after
         * @param[in] count number of elements to insert after \p pos
         * @param[in] value element of type T to be inserted
         * @return pointer to ForwardList element
         * @retval iterator pointer to last inserted element
         * @retval pos if no element was inserted
         */
        auto insert_after(const const_iterator& pos, size_t count, const_reference value) -> iterator;

        /**
         * @brief Function inserts new Node after specified ForwardList const_iterator
         *
         * @param[in] pos const_iterator to insert element after
         * @param[in] init_list initializer_list with elements to insert after \p pos
         * @return pointer to the last inserted element
         * @retval iterator to last inserted element
         * @retval pos if no element was inserted
         */
        auto insert_after(const const_iterator& pos, std::initializer_list<T> init_list) -> iterator;

        /// @todo add emplace_after

        /**
        * @brief Function erases Node after specified ForwardList const_iterator
        *
        * @param[in] pos const_iterator after which element will be erased
        * @return pointer to element after deleted iterator
        * @retval iterator element after deleted element
        * @retval nullptr if invalid iterator
        */
        auto erase_after(const const_iterator& pos) -> iterator;

        /**
         * @brief Function erases Node between specified ForwardList Const_Iterators
         *
         * @param[in] first element after which element will be erased
         * @param[in] last element after last erased element
         * @return pointer to element after last deleted element
         * @retval iterator to element after last deleted element
         * @retval nullptr if invalid iterator
         */
        auto erase_after(const const_iterator& first, const const_iterator& last) -> iterator;

        /**
         * @brief Function adds new Node at the beginning of ForwardList
         *
         * @param[in] value element of type T
         */
        void push_front(T value);

        /// @todo add emplace_front

        /**
         * @brief Function removes first Node of ForwardList
         */
        void pop_front();

        /**
         * @brief Function resize ForwardList to specified number of elements
         *
         * @param[in] count new size of container
         */
        void resize(size_t count);

        /**
         * @brief Function resize ForwardList to specified number of elements
         *
         * @param[in] count count new size of container
         * @param[in] value value to initialize new elements
         */
        void resize(size_t count, const_reference value);

        /**
         * @brief Function swaps content of two ForwardList objects
         *
         * @param[in,out] other object to swap content with
         */
        void swap(ForwardList<T>& other) noexcept;

        /**
         * @brief Function combines two sorted ForwardLists into one sorted ForwardList
         *
         * @param[in,out] other container to take elements from
         * @details Content of other object will be taken by constructed object
         */
        void merge(ForwardList<T>& other);

        /**
         * @brief Function combines two sorted ForwardLists into one sorted ForwardList
         *
         * @param[in,out] other container to take elements from
         * @details Content of other object will be taken by constructed object
         */
         // transfers ownership of nodes, moving entire container is not necessary
         // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
        void merge(ForwardList<T>&& other);

        /**
         * @brief Function moves elements from other ForwardList object
         *
         * @param[in] pos const_iterator after which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @details Content of other object will be taken by constructed object
         */
        void splice_after(const const_iterator& pos, ForwardList<T>& other);

        /**
         * @brief Function moves elements from other ForwardList object
         *
         * @param[in] pos const_iterator after which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @details Content of other object will be taken by constructed object
         */
        void splice_after(const_iterator pos, ForwardList<T>&& other);

        /**
         * @brief Function moves elements from other ForwardList object
         *
         * @param[in] pos const_iterator after which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] iter const_iterator after which elements of \p other will be taken
         * @details Content of other object will be taken by constructed object
         */
        void splice_after(const const_iterator& pos, ForwardList<T>& other, const const_iterator& iter);

        /**
         * @brief Function moves elements from other ForwardList object
         *
         * @param[in] pos const_iterator after which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] iter const_iterator after which elements of \p other will be taken
         * @details Content of other object will be taken by constructed object
         */
        void splice_after(const_iterator pos, ForwardList<T>&& other, const_iterator iter);

        /**
         * @brief Function moves elements from other ForwardList object
         *
         * @param[in] pos const_iterator after which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] first const_iterator after which elements of \p other will be taken
         * @param[in] last const_iterator until which elements of \p other will be taken
         * @details Content of other object will be taken by constructed object
         */
        void splice_after(const const_iterator& pos, ForwardList<T>& other,
            const const_iterator& first, const const_iterator& last);

        /**
         * @brief Function moves elements from other ForwardList object
         *
         * @param[in] pos const_iterator after which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] first const_iterator after which elements of \p other will be taken
         * @param[in] last const_iterator until which elements of \p other will be taken
         * @details Content of other object will be taken by constructed object
         */
        void splice_after(const_iterator pos, ForwardList<T>&& other, const_iterator first, const_iterator last);

        /**
         * @brief Function removes all elements equal to \p value
         *
         * @param[in] value value of elements to remove
         */
        void remove(const_reference value);

        /// @todo add remove_if

        /**
         * @brief Function reverts in place Nodes of ForwardList
         */
        void reverse();

        /**
         * @brief Function removes consecutive duplicated elements
         * @details Only the first occurrence of given element in each group is preserved
         */
        void unique();

        /// @todo add sort

        /**
         * @brief push elements of another ForwardList to base container back
         *
         * @param[in] other ForwardList to read elements from
         * @return ForwardList<T>&
         */
        auto operator+=(const ForwardList<T>& other) -> ForwardList<T>&
        {
            auto before_last = find_iter_before_last();

            for (auto it = other.cbegin(); it != other.cend(); ++it)
            {
                T value = *it;
                before_last = insert_after(before_last, value);
            }

            return *this;
        }

        /**
         * @brief push elements of another ForwardList to base container back
         *
         * @param[in] init_list initializer_list to read elements from
         * @return ForwardList<T>&
         */
        auto operator+=(const std::initializer_list<T> init_list) -> ForwardList<T>&
        {
            auto before_last = find_iter_before_last();

            for (const auto& item : init_list)
            {
                before_last = insert_after(before_last, item);
            }

            return *this;
        }

        /**
         * @brief Function returns pointer to specific Node of ForwardList
         *
         * @param[in] index index of element
         * @return Node*
         * @retval Node* if index is valid
         * @retval nullptr if invalid index
         */
        [[nodiscard]] auto get(size_t index) const -> Node*
        {
            if (index > m_size)
            {
                return nullptr;
            }

            Node* temp = dynamic_cast<Node*>(m_head->m_next.get());
            for (size_t i = 0; i < index; i++)
            {
                temp = dynamic_cast<Node*>(temp->m_next.get());
                if (temp == nullptr)
                {
                    break;
                }
            }

            return temp;
        }

        /**
         * @brief Function sets value of specified Node of ForwardList
         *
         * @param[in] index index of element to be modified
         * @param[in] value to overwrite Node at index
         * @return operation status
         * @retval true if value of Node was overwritten
         * @retval false if invalid index
         */
        auto set(size_t index, T value) -> bool
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
         * @brief Function returns ForwardList size
         *
         * @return size_t number of elements in container
         */
        [[nodiscard]] auto size() const -> size_t
        {
            return m_size;
        }

    private:

        /**
         * @brief Construct new object based on two ForwardList objects
         *
         * Forward friend declaration of ForwardList operator+
         *
         * @tparam T type of data stored in ForwardList Node
         * @param[in] list1 input ForwardList
         * @param[in] list2 input ForwardList
         * @return ForwardList<T> with content of two input lists
         */
        friend auto operator+<>(const ForwardList<T>& list1, const ForwardList<T>& list2)->ForwardList<T>;

        /**
         * @brief Function initialize ForwardList pointer located just before user added data
         * It is used be before begin iterator
         */
        void init_node()
        {
            if (m_head == nullptr)
            {
                m_head = std::make_unique<NodeBase>();
            }
        }

        /**
         * @brief Function iterates ForwardList to find iterator to Node before last one
         *
         * @return iterator to Node before last one
         */
        auto find_iter_before_last() -> iterator
        {
            NodeBase* temp{ m_head->m_next.get() };
            while (temp && temp->m_next && temp->m_next->m_next)
            {
                temp = temp->m_next.get();
            }

            auto iter = iterator(temp);
            if (!iter.m_current_node)
            {
                iter = before_begin();
            }

            return iter;
        }

        /**
         * @brief Function remove next element
         *
         * @param[in] pos iterator after which element will be erased
         * @return iterator to element following deleted one
         */
        auto erase_element_after(iterator pos) -> iterator
        {
            NodeBase* temp{ pos.m_current_node };
            NodeBase* to_remove{ temp->m_next.get() };

            temp->m_next = std::move(to_remove->m_next);


            m_size--;
            return iterator(temp->m_next.get());
        }

        /**
        * @brief Function inserts new Node after specified ForwardList iterator
        *
        * @param[in] pos iterator to insert element after
        * @param[in] value element of type T to be inserted
        * @return pointer to next element
        * @retval iterator to iterator inserted after \pos
        * @retval nullptr if invalid iterator
        */
        auto insert_element_after(iterator& pos, const_reference value) -> iterator
        {
            auto newNode = std::make_unique<Node>(value);
            newNode->m_next = std::move(pos.m_current_node->m_next);
            pos.m_current_node->m_next = std::move(newNode);

            m_size++;
            return iterator(pos.m_current_node->m_next.get());
        }

        /**
         * @brief Function checks ForwardList contains iterator
         *
         * @param[in] pos iterator to check
         * @return bool \p pos iterator status
         * @return true if \p pos belong to ForwardList
         * @return false if otherwise
         */
        auto if_valid_iterator(const const_iterator& pos) -> bool
        {
            bool valid_iterator{};
            for (auto it = cbefore_begin(); it != cend(); ++it)
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
         * @brief Function moves elements from other ForwardList object
         *
         * @param[in] pos const_iterator after which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] iter const_iterator after which elements of \p other will be taken
         * @details Content of other object will be taken by constructed object
         */
         // transfers ownership of nodes, moving entire container is not necessary
         // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
        void transfer(const const_iterator& pos, ForwardList<T>&& other, const const_iterator& iter);

        /**
         * @brief Function moves elements from other ForwardList object
         *
         * @param[in] pos const_iterator after which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] first const_iterator after which elements of \p other will be taken
         * @param[in] last const_iterator until which elements of \p other will be taken
         * @details Content of other object will be taken by constructed object
         */
         // transfers ownership of nodes, moving entire container is not necessary
         // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
        void transfer(const const_iterator& pos, ForwardList<T>&& other,
            const const_iterator& first, const const_iterator& last);

        std::unique_ptr<NodeBase> m_head{};
        size_t m_size{};
    };

    template<typename T>
    ForwardList<T>::ForwardList()
    {
        init_node();
    }

    template<typename T>
    ForwardList<T>::ForwardList(size_t count)
        : ForwardList(count, T{})
    {
    }

    template<typename T>
    ForwardList<T>::ForwardList(size_t count, const T& value)
    {
        init_node();

        for (size_t i = 0; i < count; i++)
        {
            push_front(value);
        }
    }

    template<typename T>
    ForwardList<T>::ForwardList(const std::initializer_list<T>& init_list)
    {
        init_node();

        auto iter = before_begin();
        for (const auto& item : init_list)
        {
            iter = insert_after(iter, item);
        }
    }

    template<typename T>
    ForwardList<T>::ForwardList(const ForwardList<T>& other)
    {
        init_node();

        auto iter = before_begin();
        for (const auto& item : other)
        {
            iter = insert_after(iter, item);
        }
    }

    template<typename T>
    auto ForwardList<T>::operator=(const ForwardList<T>& other) -> ForwardList<T>&
    {
        init_node();

        if (&other != this)
        {
            while (m_head->m_next)
            {
                pop_front();
            }

            auto iter = before_begin();
            for (const auto& item : other)
            {
                iter = insert_after(iter, item);
            }
        }

        return *this;
    }

    template<typename T>
    ForwardList<T>::ForwardList(ForwardList<T>&& other) noexcept
    {
        operator=(std::move(other));
    }

    template<typename T>
    auto ForwardList<T>::operator=(ForwardList<T>&& other) noexcept -> ForwardList<T>&
    {
        if (&other != this)
        {
            clear();
            init_node();

            m_head->m_next = std::move(other.m_head->m_next);
            m_size = other.m_size;

            other.m_head->m_next = nullptr;
            other.m_size = 0;
        }

        return *this;
    }

    template<typename T>
    ForwardList<T>::~ForwardList()
    {
        clear();
    }

    template<typename T>
    void ForwardList<T>::assign(size_t count, const_reference value)
    {
        while (m_head->m_next)
        {
            pop_front();
        }

        auto iter = before_begin();
        for (size_t i = 0; i < count; i++)
        {
            iter = insert_after(iter, value);
        }
    }

    template<typename T>
    void ForwardList<T>::assign(const std::initializer_list<T>& init_list)
    {
        while (m_head->m_next)
        {
            pop_front();
        }

        auto iter = before_begin();
        for (const auto& item : init_list)
        {
            iter = insert_after(iter, item);
        }
    }

    template<typename T>
    auto ForwardList<T>::front() -> typename ForwardList<T>::reference
    {
        return *begin();
    }

    template<typename T>
    auto ForwardList<T>::front() const -> typename ForwardList<T>::const_reference
    {
        return *cbegin();
    }

    template<typename T>
    auto ForwardList<T>::before_begin() noexcept -> typename ForwardList<T>::iterator
    {
        return iterator(m_head.get());
    }

    template<typename T>
    auto ForwardList<T>::before_begin() const noexcept -> typename ForwardList<T>::const_iterator
    {
        return const_iterator(m_head.get());
    }

    template<typename T>
    auto ForwardList<T>::cbefore_begin() const noexcept -> typename ForwardList<T>::const_iterator
    {
        return before_begin();
    }

    template<typename T>
    auto ForwardList<T>::begin() noexcept -> typename ForwardList<T>::iterator
    {
        return iterator(m_head->m_next.get());
    }

    template<typename T>
    auto ForwardList<T>::begin() const noexcept -> typename ForwardList<T>::const_iterator
    {
        return const_iterator(m_head->m_next.get());
    }

    template<typename T>
    auto ForwardList<T>::cbegin() const noexcept -> typename ForwardList<T>::const_iterator
    {
        return begin();
    }

    template<typename T>
    auto ForwardList<T>::end() noexcept -> typename ForwardList<T>::iterator
    {
        return iterator(nullptr);
    }

    template<typename T>
    auto ForwardList<T>::end() const noexcept -> typename ForwardList<T>::const_iterator
    {
        return const_iterator(nullptr);
    }

    template<typename T>
    auto ForwardList<T>::cend() const noexcept -> typename ForwardList<T>::const_iterator
    {
        return end();
    }


    template<typename T>
    auto ForwardList<T>::empty() const -> bool
    {
        return m_size == 0;
    }

    template<typename T>
    auto ForwardList<T>::max_size() const noexcept -> size_t
    {
        return std::numeric_limits<size_t>::max();
    }

    template<typename T>
    void ForwardList<T>::clear()
    {
        if (m_head && m_head->m_next)
        {
            NodeBase* temp{ m_head->m_next.get() };
            while (temp)
            {
                m_head->m_next = std::move(temp->m_next);
                temp = m_head->m_next.get();
            }

            m_size = 0;
            m_head->m_next = nullptr;
        }
    }

    template<typename T>
    auto ForwardList<T>::insert_after(const const_iterator& pos, const_reference value)
        -> typename ForwardList<T>::iterator
    {
        return insert_after(pos, 1, value);
    }

    template<typename T>
    auto ForwardList<T>::insert_after(const const_iterator& pos, size_t count, const_reference value)
        -> typename ForwardList<T>::iterator
    {
        if (!if_valid_iterator(pos))
        {
            return nullptr;
        }

        iterator iter{ pos.m_current_node };
        for (size_t i = 0; i < count; i++)
        {
            iter = insert_element_after(iter, value);
        }

        return iter;
    }

    template<typename T>
    auto ForwardList<T>::insert_after(const const_iterator& pos, std::initializer_list<T> init_list)
        -> typename ForwardList<T>::iterator
    {
        if (!if_valid_iterator(pos))
        {
            return nullptr;
        }

        iterator iter{ pos.m_current_node };
        for (const auto val : init_list)
        {
            iter = insert_element_after(iter, val);
        }

        return iter;
    }

    template<typename T>
    auto ForwardList<T>::erase_after(const const_iterator& pos) -> typename ForwardList<T>::iterator
    {
        if (!if_valid_iterator(pos))
        {
            return nullptr;
        }

        iterator iter{ pos.m_current_node };
        iter = erase_element_after(iter);

        return iter;
    }

    template<typename T>
    auto ForwardList<T>::erase_after(const const_iterator& first,
        const const_iterator& last) -> typename ForwardList<T>::iterator
    {
        if (!if_valid_iterator(first) || !if_valid_iterator(last))
        {
            return nullptr;
        }

        const iterator iter(first.m_current_node);
        const size_t dist = distance(first, last);
        for (size_t i = 0; i < dist - 1; i++)
        {
            erase_element_after(iter);
        }

        return first.m_current_node->m_next.get();
    }

    template<typename T>
    void ForwardList<T>::push_front(T value)
    {
        auto newNode = std::make_unique<Node>(value);
        if (!m_head->m_next)
        {
            m_head->m_next = std::move(newNode);
        }
        else
        {
            newNode->m_next = std::move(m_head->m_next);
            m_head->m_next = std::move(newNode);
        }

        m_size++;
    }

    template<typename T>
    void ForwardList<T>::pop_front()
    {
        if (!m_head->m_next)
        {
            return;
        }

        NodeBase* temp{ m_head->m_next.get() };
        if (m_size == 1)
        {
            m_head->m_next = nullptr;
        }
        else
        {
            m_head->m_next = std::move(temp->m_next);
        }

        m_size--;
    }

    template<typename T>
    void ForwardList<T>::resize(size_t count)
    {
        resize(count, T{});
    }

    template<typename T>
    void ForwardList<T>::resize(size_t count, const_reference value)
    {
        init_node();

        if (count == m_size)
        {
            return;
        }

        if (m_size > count)
        {
            auto iter = begin();
            for (size_t i = 0; i < count - 1; i++)
            {
                ++iter;
            }

            while (m_size > count)
            {
                erase_after(iter);
            }
        }

        if (m_size < count)
        {
            auto iter = find_iter_before_last();
            if (iter != before_begin())
            {
                ++iter;
            }

            while (m_size < count)
            {
                iter = insert_after(iter, value);
            }
        }
    }

    template<typename T>
    void ForwardList<T>::swap(ForwardList<T>& other) noexcept
    {
        std::swap(m_head->m_next, other.m_head->m_next);
        std::swap(m_size, other.m_size);
    }

    template<typename T>
    void ForwardList<T>::merge(ForwardList<T>& other)
    {
        merge(std::move(other));
    }

    template<typename T>
    // transfers ownership of nodes, moving entire container is not necessary
    // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
    void ForwardList<T>::merge(ForwardList<T>&& other)
    {
        if (&other != this)
        {
            if (m_size != 0)
            {
                auto temp_head = std::make_unique<Node>(0);
                NodeBase* temp_tail = temp_head.get();

                std::unique_ptr<NodeBase> to_move{};
                std::unique_ptr<NodeBase> to_return{};

                while (m_head->m_next && other.m_head->m_next)
                {
                    Node* node_this = dynamic_cast<Node*>(m_head->m_next.get());
                    Node* node_other = dynamic_cast<Node*>(other.m_head->m_next.get());

                    if (node_this && node_other)
                    {
                        if (node_this->value() <= node_other->value())
                        {
                            to_move = std::move(m_head->m_next);
                            to_return = std::move(to_move->m_next);
                            temp_tail->m_next = std::move(to_move);
                            m_head->m_next = std::move(to_return);
                        }
                        else
                        {
                            to_move = std::move(other.m_head->m_next);
                            to_return = std::move(to_move->m_next);
                            temp_tail->m_next = std::move(to_move);
                            other.m_head->m_next = std::move(to_return);
                        }

                        temp_tail = temp_tail->m_next.get();
                    }
                }
                temp_tail->m_next =
                    (m_head->m_next == nullptr) ? std::move(other.m_head->m_next) : std::move(m_head->m_next);

                m_head->m_next = std::move(temp_head->m_next);

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
    auto ForwardList<T>::distance(const_iterator first, const const_iterator& last) -> size_t
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
    void ForwardList<T>::transfer(const const_iterator& pos, ForwardList<T>&& other, const const_iterator& iter)
    {
        if (&other != this && other.m_size > 0)
        {
            NodeBase* temp_prev{ pos.m_current_node };  // to append to
            NodeBase* temp_next{ iter.m_current_node }; // does not move

            std::unique_ptr<NodeBase> to_move{ std::move(temp_next->m_next) };

            if (to_move)
            {
                temp_next->m_next = std::move(to_move->m_next);
                to_move->m_next = std::move(temp_prev->m_next);
                temp_prev->m_next = std::move(to_move);

                m_size += 1;
                other.m_size -= 1;
            }
        }
    }

    template<typename T>
    // transfers ownership of nodes, moving entire container is not necessary
    // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
    void ForwardList<T>::transfer(const const_iterator& pos, ForwardList<T>&& other,
        const const_iterator& first, const const_iterator& last)
    {
        if (&other != this && other.m_size > 0)
        {
            const size_t dist = distance(first, last) - 1;

            if (first == last || dist == 0)
            {
                return;
            }

            NodeBase* temp_prev{ pos.m_current_node };     // to append to
            std::unique_ptr<NodeBase> to_append_to{ std::move(pos.m_current_node->m_next) };
            NodeBase* temp_next{ first.m_current_node };   // does not move

            NodeBase* last_to_move{ temp_next };
            for (size_t i = 0; i < dist; i++)
            {
                if (last_to_move)
                {
                    last_to_move = last_to_move->m_next.get();
                }
            }

            if (temp_next)
            {
                std::unique_ptr<NodeBase> to_move{ std::move(temp_next->m_next) };
                temp_next->m_next = std::move(last_to_move->m_next);
                last_to_move->m_next = std::move(to_append_to);
                temp_prev->m_next = std::move(to_move);

                m_size += dist;
                other.m_size -= dist;
            }
        }
    }

    template<typename T>
    void ForwardList<T>::splice_after(const const_iterator& pos, ForwardList<T>& other)
    {
        transfer(pos, std::move(other), other.before_begin(), other.end());
    }

    template<typename T>
    void ForwardList<T>::splice_after(const_iterator pos, ForwardList<T>&& other)
    {
        transfer(pos, std::move(other), other.before_begin(), other.end());
    }

    template<typename T>
    void ForwardList<T>::splice_after(const const_iterator& pos, ForwardList<T>& other, const const_iterator& iter)
    {
        transfer(pos, std::move(other), iter);
    }

    template<typename T>
    void ForwardList<T>::splice_after(const_iterator pos, ForwardList<T>&& other, const_iterator iter)
    {
        transfer(pos, std::move(other), iter);
    }

    template<typename T>
    void ForwardList<T>::splice_after(const const_iterator& pos, ForwardList<T>& other,
        const const_iterator& first, const const_iterator& last)
    {
        transfer(pos, std::move(other), first, last);
    }

    template<typename T>
    void ForwardList<T>::splice_after(const_iterator pos, ForwardList<T>&& other, const_iterator first, const_iterator last)
    {
        transfer(pos, std::move(other), first, last);
    }

    template<typename T>
    void ForwardList<T>::remove(const_reference value)
    {
        NodeBase* temp{ m_head.get() };
        NodeBase* next{};

        while (temp)
        {
            next = temp->m_next.get();

            if (Node* node = dynamic_cast<Node*>(next))
            {
                if (node->value() == value)
                {
                    NodeBase* to_remove = std::move(temp->m_next.get());
                    temp->m_next = std::move(to_remove->m_next);

                    m_size--;
                    continue;
                }
            }

            temp = std::move(temp->m_next.get());
        }
    }

    template<typename T>
    void ForwardList<T>::reverse()
    {
        std::unique_ptr<NodeBase> temp = std::move(m_head->m_next);
        std::unique_ptr<NodeBase> prev{};

        for (size_t i = 0; i < m_size; i++)
        {
            std::unique_ptr<NodeBase> next = std::move(temp->m_next);
            temp->m_next = std::move(prev);

            prev = std::move(temp);
            temp = std::move(next);
        }

        m_head->m_next = std::move(prev);
    }

    template<typename T>
    void ForwardList<T>::unique()
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
                        NodeBase* to_remove = std::move(next);
                        prev->m_next = std::move(to_remove->m_next);

                        m_size--;
                        continue;
                    }
                }

                if (prev)
                {
                    prev = prev->m_next.get();
                }

                temp = temp->m_next.get();
            }
        }
    }

    /**
     * @brief Construct new object based on two ForwardList objects
     *
     * @tparam T type of data stored in ForwardList Node
     * @param[in] list1 input ForwardList
     * @param[in] list2 input ForwardList
     * @return ForwardList<T> with content of two input lists
     */
    template<typename T>
    auto operator+(const ForwardList<T>& list1, const ForwardList<T>& list2) -> ForwardList<T>
    {
        ForwardList<T> temp(list1);
        auto before_last = temp.find_iter_before_last();
        ++before_last;

        for (auto iter = list2.cbegin(); iter != list2.cend(); ++iter)
        {
            T value = *iter;
            before_last = temp.insert_after(before_last, value);
        }

        return temp;
    }

    /**
     * @brief Overloads operator to print all elements of ForwardList
     *
     * @tparam T type of initializer list elements
     * @param[in,out] out reference to output stream
     * @param[in] list ForwardList to print
     * @return std::ostream&
     */
    template<typename T>
    auto operator<<(std::ostream& out, const ForwardList<T>& list) -> std::ostream&
    {
        if (list.empty())
        {
            return out;
        }

        for (auto it = list.cbegin(); it != list.cend(); ++it)
        {
            T value = *it;
            out << value << ' ';
        }

        return out;
    }

    /**
     * @brief The relational operator compares two ForwardList objects
     *
     * @tparam T type of data stored in ForwardList
     * @param[in] list1 input container
     * @param[in] list2 input container
     * @retval true if containers are equal
     * @retval false if containers are not equal
     */
    template<typename T>
    auto operator==(const ForwardList<T>& list1, const ForwardList<T>& list2) -> bool
    {
        if (list1.size() != list2.size())
        {
            return false;
        }

        auto list1_iter = list1.cbegin();
        auto list2_iter = list2.cbegin();

        while (list1_iter != list1.cend())
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
     * @brief The relational operator compares two ForwardList objects
     *
     * @tparam T type of data stored in ForwardList
     * @param[in] list1 input container
     * @param[in] list2 input container
     * @retval true if containers are not equal
     * @retval false if containers are equal
     */
    template<typename T>
    auto operator!=(const ForwardList<T>& list1, const ForwardList<T>& list2) -> bool
    {
        return !(operator==(list1, list2));
    }

    /**
     * @brief The relational operator compares two ForwardList objects
     *
     * @tparam T type of data stored in ForwardList
     * @param[in] list1 input container
     * @param[in] list2 input container
     * @retval true if the content of \p list1 are lexicographically
     *         less than the content of \p list2
     * @retval false otherwise
     */
    template<typename T>
    auto operator<(const ForwardList<T>& list1, const ForwardList<T>& list2) -> bool
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
     * @brief The relational operator compares two ForwardList objects
     *
     * @tparam T type of data stored in ForwardList
     * @param[in] list1 input container
     * @param[in] list2 input container
     * @retval true if the content of \p list1 are lexicographically
     *         greater than the content of \p list2
     * @retval false otherwise
     */
    template<typename T>
    auto operator>(const ForwardList<T>& list1, const ForwardList<T>& list2) -> bool
    {
        return operator<(list2, list1);
    }

    /**
     * @brief The relational operator compares two ForwardList objects
     *
     * @tparam T type of data stored in ForwardList
     * @param[in] list1 input container
     * @param[in] list2 input container
     * @retval true if the content of \p list1 are lexicographically
     *         less or equal than the content of \p list2
     * @retval false otherwise
     */
    template<typename T>
    auto operator<=(const ForwardList<T>& list1, const ForwardList<T>& list2) -> bool
    {
        return !(operator>(list1, list2));
    }

    /**
     * @brief The relational operator compares two ForwardList objects
     *
     * @tparam T type of data stored in ForwardList
     * @param[in] list1 input container
     * @param[in] list2 input container
     * @retval true if the content of \p list1 are lexicographically
     *         greater or equal than the content of \p list2
     * @retval false otherwise
     */
    template<typename T>
    auto operator>=(const ForwardList<T>& list1, const ForwardList<T>& list2) -> bool
    {
        return !(operator<(list1, list2));
    }

    /// @todo implement non-member specialized swap function

    /// @todo implement non-member specialized erase function

    /// @todo implement non-member specialized erase_if function

}

// test std::ranges::forward_range concept
static_assert(std::ranges::forward_range<dsa::ForwardList<int>>);
static_assert(std::ranges::forward_range<const dsa::ForwardList<int>>);

#endif // !FORWARD_LIST_H
