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

#include <cstddef>
#include <functional>
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

    /**
     * @brief Implements ForwardList using Node with pointer to next element
     *        as internal base
     *
     * @tparam T type of data stored in ForwardList Node
     *
     * @todo remove public functions / operators not supported by std::forward_list
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
            NodeBase* m_next{};
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
                    m_current_node = m_current_node->m_next;
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
            auto operator[](size_type index) -> ForwardListIterator
            {
                NodeBase* temp{ m_current_node };

                for (size_type i = 0; i < index; i++)
                {
                    if (temp->m_next)
                    {
                        temp = temp->m_next;
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
        ForwardList(size_type count);

        /**
         * @brief Construct a new ForwardList object of size \p count,
         * using provided \p value of type T
         *
         * @param[in] count element count
         * @param[in] value value for all nodes
         */
        ForwardList(size_type count, const T& value);

        /**
         * @brief Construct a new ForwardList object using elements from range [ \p first , \p last )
         *
         * @tparam InputIt
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         */
        template<typename InputIt>
            requires std::input_iterator<InputIt>
        ForwardList(InputIt first, InputIt last);

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
        void assign(size_type count, const_reference value);

        /**
         * @brief Function assign elements from range [ \p first , \p last ) to ForwardList object
         *
         * @tparam InputIt
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         */
        template<typename InputIt>
            requires std::input_iterator<InputIt>
        void assign(InputIt first, InputIt last);

        /**
         * @brief Function assign values to the ForwardList
         *
         * @param[in] init_list values to replace ForwardList with
         */
        void assign(const std::initializer_list<T>& init_list);

        /**
         * @brief Get the allocator object
         *
         * @return allocator_type type of memory allocator
         */
        [[nodiscard]] constexpr auto get_allocator() const -> allocator_type;

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
         * @return size_type maximum number of elements
         */
        [[nodiscard]] auto max_size() const noexcept -> size_type;

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
        auto insert_after(const const_iterator& pos, size_type count, const_reference value) -> iterator;

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

        /**
         * @brief Insert new element into the container after \p pos
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
        auto emplace_after(const_iterator pos, Args&&... args) -> iterator;

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

        /**
         * @brief Inserts a new element to the beginning of the container
         *
         * @tparam ...Args
         * @param[in] ...args arguments to forward to the constructor of the element
         * @return reference to emplaced element
         *
         * @note no iterators or references are invalidated,
         *       if construction of new element fails or an exception is thrown for any reason
         *       state of the object does not change and this function has no effect
         */
        template<typename... Args>
        auto emplace_front(Args&&... args) -> reference;

        /**
         * @brief Function removes first Node of ForwardList
         */
        void pop_front();

        /**
         * @brief Function resize ForwardList to specified number of elements
         *
         * @param[in] count new size of container
         */
        void resize(size_type count);

        /**
         * @brief Function resize ForwardList to specified number of elements
         *
         * @param[in] count count new size of container
         * @param[in] value value to initialize new elements
         */
        void resize(size_type count, const_reference value);

        /**
         * @brief Function swaps content of two ForwardList objects
         *
         * @param[in,out] other object to swap content with
         */
        void swap(ForwardList<T>& other) noexcept(std::is_nothrow_swappable_v<T>);

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
         * @brief Function reverts in place Nodes of ForwardList
         */
        void reverse();

        /**
         * @brief Function removes consecutive duplicated elements
         * @details Only the first occurrence of given element in each group is preserved
         */
        void unique();

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

        /**
         * @brief Function returns ForwardList size
         *
         * @return size_type number of elements in container
         */
        [[nodiscard]] auto size() const -> size_type
        {
            return m_size;
        }

    private:

        /**
         * @brief Function initialize ForwardList pointer located just before user added data
         * It is used be before begin iterator
         */
        void init_node()
        {
            if (m_head == nullptr)
            {
                // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
                m_head = new NodeBase;
            }
        }

        /**
         * @brief Function iterates ForwardList to find iterator to Node before last one
         *
         * @return iterator to Node before last one
         */
        auto find_iter_before_last() -> iterator
        {
            NodeBase* temp{ m_head->m_next };
            while (temp && temp->m_next && temp->m_next->m_next)
            {
                temp = temp->m_next;
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
            NodeBase* to_remove{ temp->m_next };

            temp->m_next = to_remove->m_next;
            destroy_node(to_remove);

            m_size--;
            return iterator(temp->m_next);
        }

        /**
         * @brief Function allocate and construct ForwardList node
         *
         * @param[in] value element of type T to be inserted
         * @param[in] next_ptr pointer to next Node
         * @return pointer to created Node
         */
        auto construct_node(const_reference value, NodeBase* next_ptr = nullptr) -> Node*
        {
            Node* newNode = node_alloc_traits::allocate(node_alloc, 1);
            try
            {
                node_alloc_traits::construct(node_alloc, newNode, Node(value));
            }
            catch (...)
            {
                node_alloc_traits::deallocate(node_alloc, newNode, 1);
                throw;
            }

            newNode->m_next = next_ptr;

            return newNode;
        }

        /**
         * @brief Function destroys and deallocates memory used by Node
         *
         * @param[in] node_to_destroy pointer to Node to delete
         */
        void destroy_node(NodeBase* node_to_destroy)
        {
            Node* node_dyn = dynamic_cast<Node*>(node_to_destroy);
            if (node_dyn)
            {
                node_alloc_traits::destroy(node_alloc, node_dyn);
                node_alloc_traits::deallocate(node_alloc, node_dyn, 1);
            }
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
            NodeBase* temp{ pos.m_current_node };
            Node* newNode = construct_node(value, temp->m_next);
            temp->m_next = newNode;
            m_size++;
            return iterator(newNode);
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
         * @return size_type number of elements between input elements
         */
        auto distance(const_iterator first, const const_iterator& last) -> size_type;

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

        /**
         * @brief Function sorts nodes using merge sort algorithm
         * @details Sorting is implemented using recursive (top-down) algorithm
         *          Sorting is stable and inplace
         *
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
         * @param[in,out] left first input sub-list
         * @param[in,out] right second input sub-list
         * @param[in] comp comparison function object
         * @return NodeBase* containing elements from both input lists sorted using \p comp
         */
        template<typename Compare>
        auto merge(NodeBase* left, NodeBase* right, Compare comp) -> NodeBase*;

        NodeBase* m_head{};
        size_type m_size{};

        /**
         * @brief Allocator for memory management
         */
        allocator_type m_allocator{};

        /**
         * @brief Rebind allocator to create new objects of type Node
         */
        using node_allocator = typename std::allocator_traits<std::allocator<T>>::template rebind_alloc<Node>;

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
    ForwardList<T>::ForwardList()
    {
        init_node();
    }

    template<typename T>
    ForwardList<T>::ForwardList(size_type count)
        : ForwardList(count, T{})
    {
    }

    template<typename T>
    ForwardList<T>::ForwardList(size_type count, const T& value)
    {
        init_node();

        for (size_type i = 0; i < count; i++)
        {
            push_front(value);
        }
    }

    template<typename T>
    template<typename InputIt>
        requires std::input_iterator<InputIt>
    ForwardList<T>::ForwardList(InputIt first, InputIt last)
    {
        init_node();

        assign(first, last);
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

            m_head->m_next = other.m_head->m_next;
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
        delete m_head;
    }

    template<typename T>
    void ForwardList<T>::assign(size_type count, const_reference value)
    {
        while (m_head->m_next)
        {
            pop_front();
        }

        auto iter = before_begin();
        for (size_type i = 0; i < count; i++)
        {
            iter = insert_after(iter, value);
        }
    }

    template<typename T>
    template<typename InputIt>
        requires std::input_iterator<InputIt>
    void ForwardList<T>::assign(InputIt first, InputIt last)
    {
        clear();

        auto iter = before_begin();
        while (first != last)
        {
            iter = insert_after(iter, *first);
            first++;
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
    [[nodiscard]] constexpr auto ForwardList<T>::get_allocator() const -> allocator_type
    {
        return m_allocator;
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
        return iterator(m_head);
    }

    template<typename T>
    auto ForwardList<T>::before_begin() const noexcept -> typename ForwardList<T>::const_iterator
    {
        return const_iterator(m_head);
    }

    template<typename T>
    auto ForwardList<T>::cbefore_begin() const noexcept -> typename ForwardList<T>::const_iterator
    {
        return before_begin();
    }

    template<typename T>
    auto ForwardList<T>::begin() noexcept -> typename ForwardList<T>::iterator
    {
        return iterator(m_head->m_next);
    }

    template<typename T>
    auto ForwardList<T>::begin() const noexcept -> typename ForwardList<T>::const_iterator
    {
        return const_iterator(m_head->m_next);
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
    auto ForwardList<T>::max_size() const noexcept -> size_type
    {
        return std::numeric_limits<size_type>::max();
    }

    template<typename T>
    void ForwardList<T>::clear()
    {
        if (m_head && m_head->m_next)
        {
            NodeBase* temp{ m_head->m_next };
            while (temp)
            {
                m_head->m_next = temp->m_next;
                destroy_node(temp);
                temp = m_head->m_next;
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
    auto ForwardList<T>::insert_after(const const_iterator& pos, size_type count, const_reference value)
        -> typename ForwardList<T>::iterator
    {
        if (!if_valid_iterator(pos))
        {
            return nullptr;
        }

        iterator iter{ pos.m_current_node };
        for (size_type i = 0; i < count; i++)
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
    template<typename... Args>
    auto ForwardList<T>::emplace_after(const_iterator pos, Args&&... args) -> iterator
    {
        const iterator current{ pos.m_current_node };

        Node* newNode = node_alloc_traits::allocate(node_alloc, 1);
        try
        {
            node_alloc_traits::construct(node_alloc, newNode, std::forward<Args>(args)...);
            newNode->m_next = current.m_current_node->m_next;
        }
        catch (...)
        {
            node_alloc_traits::deallocate(node_alloc, newNode, 1);
            throw;
        }

        current.m_current_node->m_next = newNode;
        ++m_size;
        return iterator(newNode);
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
        const size_type dist = distance(first, last);
        for (size_type i = 0; i < dist - 1; i++)
        {
            erase_element_after(iter);
        }

        return first.m_current_node->m_next;
    }

    template<typename T>
    void ForwardList<T>::push_front(T value)
    {
        Node* newNode = construct_node(value);
        if (!m_head->m_next)
        {
            m_head->m_next = newNode;
        }
        else
        {
            newNode->m_next = m_head->m_next;
            m_head->m_next = newNode;
        }

        m_size++;
    }

    template<typename T>
    template<typename... Args>
    auto ForwardList<T>::emplace_front(Args&&... args) -> reference
    {
        emplace_after(before_begin(), std::forward<Args>(args)...);
        return front();
    }

    template<typename T>
    void ForwardList<T>::pop_front()
    {
        if (!m_head->m_next)
        {
            return;
        }

        NodeBase* temp{ m_head->m_next };
        if (m_size == 1)
        {
            m_head->m_next = nullptr;
        }
        else
        {
            m_head->m_next = temp->m_next;
        }
        destroy_node(temp);

        m_size--;
    }

    template<typename T>
    void ForwardList<T>::resize(size_type count)
    {
        resize(count, T{});
    }

    template<typename T>
    void ForwardList<T>::resize(size_type count, const_reference value)
    {
        init_node();

        if (count == m_size)
        {
            return;
        }

        if (m_size > count)
        {
            auto iter = begin();
            for (size_type i = 0; i < count - 1; i++)
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
    void ForwardList<T>::swap(ForwardList<T>& other) noexcept(std::is_nothrow_swappable_v<T>)
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
                Node* temp_head = construct_node(0);
                NodeBase* temp_tail = temp_head;

                NodeBase* to_move{};
                NodeBase* to_return{};

                while (m_head->m_next && other.m_head->m_next)
                {
                    Node* node_this = dynamic_cast<Node*>(m_head->m_next);
                    Node* node_other = dynamic_cast<Node*>(other.m_head->m_next);

                    if (node_this && node_other)
                    {
                        if (node_this->value() <= node_other->value())
                        {
                            to_move = m_head->m_next;
                            to_return = to_move->m_next;
                            temp_tail->m_next = to_move;
                            m_head->m_next = to_return;
                        }
                        else
                        {
                            to_move = other.m_head->m_next;
                            to_return = to_move->m_next;
                            temp_tail->m_next = to_move;
                            other.m_head->m_next = to_return;
                        }

                        temp_tail = temp_tail->m_next;
                    }
                }

                if (m_head->m_next == nullptr)
                {
                    temp_tail->m_next = other.m_head->m_next;
                    other.m_head->m_next = nullptr;
                }
                else
                {
                    temp_tail->m_next = m_head->m_next;
                    m_head->m_next = nullptr;
                }

                m_head->m_next = temp_head->m_next;
                destroy_node(temp_head);

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
    auto ForwardList<T>::distance(const_iterator first, const const_iterator& last) -> size_type
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
    void ForwardList<T>::transfer(const const_iterator& pos, ForwardList<T>&& other, const const_iterator& iter)
    {
        if (&other != this && other.m_size > 0)
        {
            NodeBase* temp_prev{ pos.m_current_node };  // to append to
            NodeBase* temp_next{ iter.m_current_node }; // does not move

            NodeBase* to_move{ temp_next->m_next };

            if (to_move)
            {
                temp_next->m_next = to_move->m_next;
                to_move->m_next = temp_prev->m_next;
                temp_prev->m_next = to_move;

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
            const size_type dist = distance(first, last) - 1;

            if (first == last || dist == 0)
            {
                return;
            }

            NodeBase* temp_prev{ pos.m_current_node };     // to append to
            NodeBase* temp_next{ first.m_current_node };   // does not move

            NodeBase* first_to_move{ temp_next->m_next };
            NodeBase* last_to_move{ temp_next };
            for (size_type i = 0; i < dist; i++)
            {
                if (last_to_move)
                {
                    last_to_move = last_to_move->m_next;
                }
            }

            if (temp_next)
            {
                temp_next->m_next = last_to_move->m_next;
                last_to_move->m_next = temp_prev->m_next;
                temp_prev->m_next = first_to_move;

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
    auto ForwardList<T>::remove(const_reference value) -> size_type
    {
        return remove_if([value](T node_val) { return node_val == value; });
    }

    template<typename T>
    template<typename UnaryPred>
    auto ForwardList<T>::remove_if(UnaryPred predicate) -> size_type
    {
        NodeBase* temp{ m_head };
        NodeBase* next{};

        size_type removed_count{};

        while (temp)
        {
            next = temp->m_next;

            if (Node* node = dynamic_cast<Node*>(next))
            {
                if (predicate(node->value()))
                {
                    NodeBase* to_remove = temp->m_next;
                    temp->m_next = to_remove->m_next;
                    destroy_node(to_remove);

                    removed_count++;
                    m_size--;
                    continue;
                }
            }

            temp = temp->m_next;
        }

        return removed_count;
    }

    template<typename T>
    void ForwardList<T>::reverse()
    {
        NodeBase* temp{ m_head->m_next };

        auto iter = find_iter_before_last();
        NodeBase* last{ iter.m_current_node->m_next };

        m_head->m_next = last;
        last = temp;

        NodeBase* prev{};
        NodeBase* next{};

        for (size_type i = 0; i < m_size; i++)
        {
            next = temp->m_next;
            temp->m_next = prev;

            prev = temp;
            temp = next;
        }

        m_head->m_next = std::move(prev);
    }

    template<typename T>
    void ForwardList<T>::unique()
    {
        NodeBase* temp{ m_head };
        NodeBase* prev{};
        NodeBase* next{};
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
                    if (node_next->value() == node_temp->value())
                    {
                        NodeBase* to_remove = next;
                        prev->m_next = to_remove->m_next;
                        destroy_node(to_remove);

                        m_size--;
                        continue;
                    }
                }

                if (prev)
                {
                    prev = prev->m_next;
                }

                temp = temp->m_next;
            }
        }
    }

    template<typename T>
    template<typename Compare>
    // Intentional recursive call for sorting nodes in top-down algorithm implementation
    // NOLINTNEXTLINE(misc-no-recursion)
    auto ForwardList<T>::merge_sort(NodeBase* source, Compare comp) -> NodeBase*
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
    auto ForwardList<T>::merge(NodeBase* left, NodeBase* right, Compare comp) -> NodeBase*
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
            //if (node_left->m_value <= node_right->m_value)
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
        }

        return result;
    }

    template<typename T>
    void ForwardList<T>::sort()
    {
        m_head->m_next = merge_sort(m_head->m_next, std::less<>());
    }

    template<typename T>
    template<typename Compare>
    void ForwardList<T>::sort(Compare comp)
    {
        m_head->m_next = merge_sort(m_head->m_next, comp);
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
     * @param[in] lhs input container
     * @param[in] rhs input container
     * @retval true if containers are equal
     * @retval false if containers are not equal
     */
    template<typename T>
    [[nodiscard]] auto operator==(const ForwardList<T>& lhs, const ForwardList<T>& rhs)
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
     * @brief The relational operator compares two ForwardList objects
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
    [[nodiscard]] auto operator<=>(const ForwardList<T>& lhs, const ForwardList<T>& rhs)
        noexcept(noexcept(*lhs.begin() == *rhs.begin())) -> std::compare_three_way_result_t<T>
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
     * @brief Exchanges content of two ForwardList containers
     *
     * @tparam T data type stored in containers
     * @param[in] lhs container to swap content
     * @param[in] rhs container to swap content
     */
    template<typename T>
    void swap(ForwardList<T>& lhs, ForwardList<T>& rhs) noexcept(noexcept(lhs.swap(rhs)))
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
    auto erase(ForwardList<T>& container, const U& value) -> ForwardList<T>::size_type
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
    auto erase_if(ForwardList<T>& container, Pred pred) -> ForwardList<T>::size_type
    {
        return container.remove_if(pred);
    }
}

#endif // !FORWARD_LIST_H
