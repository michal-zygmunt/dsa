/**
 * @file List.h
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
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>

namespace dsa
{

    template<typename T>
    class List;

    template<typename T>
    List<T> operator+(const List<T>& list1, const List<T>& list2);

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
            Node(T value)
                : m_value{ value }
            {
            }

            /**
             * @brief Destroy the Node object
             */
            ~Node() = default;

            /**
             * @brief Function returns value stored in Node object
             *
             * @return T value stored in Node
             */
            T& value()
            {
                return m_value;
            }

            /**
             * @brief Function returns value stored in Node object
             *
             * @return T value stored in Node
             */
            T value() const
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
        class ListIterator : NodeBase
        {
        public:

            /**
             * @brief Alias for iterator type
             *
             * @tparam IF_CONST if \p true generate iterator with const reference to underlying data type
             * @tparam T data type
             */
            using iterator_type = typename std::conditional<IF_CONST, const T, T>::type;

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
            using pointer = T*;

            /**
             * @brief Alias for reference to type used by iterator
             */
            using reference = iterator_type&;

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
             * @brief Destroy the ListIterator object
             */
            ~ListIterator() = default;

            /**
             * @brief Overload operator= to assign \p node to currently pointed ListIterator
             *
             * @param[in] node input Node
             * @return ListIterator& reference to updated Node
             */
            ListIterator& operator=(NodeBase* node)
            {
                this->m_current_node = node;
                return *this;
            }

            /**
             * @brief Overload pre-increment operator++ to point ListIterator at next Node
             *
             * @return ListIterator& reference to next Node
             */
            ListIterator& operator++()
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
            ListIterator operator++(int)
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
            ListIterator& operator--()
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
            ListIterator operator--(int)
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
            bool operator==(const ListIterator<IF_CONST>& other)
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
            bool operator!=(const ListIterator<IF_CONST>& other)
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
            ListIterator operator[](size_t index)
            {
                NodeBase* temp{ m_current_node };

                for (size_t i = 0; i < index; i++)
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
            reference operator*() const
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
            pointer operator->()
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
         * @brief Construct a new List object using value of type T
         *
         * @param[in] value of type T
         */
        List(T value);

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
        List& operator=(const List<T>& other);

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
        List& operator=(List<T>&& other) noexcept;

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
        reference front();

        /**
         * @brief Function returns const reference value stored in List first Node
         *
         * @return const reference to data stored in List first Node
         */
        const_reference front() const;

        /**
         * @brief Function returns reference to value stored in List last Node
         *
         * @return reference to data stored in List last Node
         */
        reference back();

        /**
         * @brief Function returns const reference value stored in List last Node
         *
         * @return const reference to data stored in List last Node
         */
        const_reference back() const;

        /**
         * @brief Function returns pointer to List first Node
         *
         * @return iterator iterator to List first Node
         */
        iterator begin() noexcept;

        /**
         * @brief Function returns const pointer to List first Node
         *
         * @return const_iterator const iterator to List first Node
         */
        const_iterator begin() const noexcept;

        /**
         * @brief Function returns const pointer to List first Node
         *
         * @return const_iterator const iterator to List first Node
         */
        const_iterator cbegin() const noexcept;

        /**
         * @brief Function returns pointer to List last Node
         *
         * @return iterator iterator to List last Node
         */
        iterator end() noexcept;

        /**
         * @brief Function returns pointer to List last Node
         *
         * @return const_iterator const iterator to List last Node
         */
        const_iterator end() const noexcept;

        /**
         * @brief Function returns pointer to List last Node
         *
         * @return const_iterator const iterator to List last Node
         */
        const_iterator cend() const noexcept;

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
        bool empty() const;

        /**
         * @brief Function returns List size
         *
         * @return size_t number of elements in container
         */
        size_t size() const;

        /**
         * @brief Function returns maximum number of elements container can hold
         *
         * @return size_t maximum number of elements
         */
        size_t max_size() const noexcept;

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
        iterator insert(const_iterator pos, const_reference value);

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
        iterator insert(const_iterator pos, size_t count, const_reference value);

        /**
         * @brief Function inserts new Node before specified \p pos
         *
         * @param[in] pos const_iterator to insert element before
         * @param[in] init_list initializer_list with elements to insert before \p pos
         * @return pointer to List element
         * @retval iterator to first inserted element
         * @retval pos if no element was inserted
         */
        iterator insert(const_iterator pos, std::initializer_list<T> init_list);

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
        iterator erase(iterator pos);

        /**
        * @brief Function erases Node object at specified \p pos
        *
        * @param[in] pos iterator to element to erase
        * @return iterator following erased element
        * @retval iterator to element following \p pos
        * @retval begin iterator if \p pos was first element prior to removal
        * @retval end iterator if \p pos was last element prior to removal
        */
        iterator erase(const_iterator pos);

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
        iterator erase(iterator first, iterator last);

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
        iterator erase(const_iterator first, const_iterator last);

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
         * @brief Function combines two Lists
         *
         * @param[in,out] other container to take elements from
         * @details Content of other object will be taken by constructed object
         */
        void merge(List<T>& other);

        /**
         * @brief Function combines two Lists
         *
         * @param[in,out] other container to take elements from
         * @details Content of other object will be taken by constructed object
         */
        void merge(List<T>&& other);

        /**
         * @brief Function moves elements from other List object
         *
         * @param[in] pos const_iterator before which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @details Content of other object will be taken by constructed object
         */
        void splice(const_iterator pos, List<T>& other);

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
        void splice(const_iterator pos, List<T>& other, const_iterator iter);

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
        void splice(const_iterator pos, List<T>& other, const_iterator first, const_iterator last);

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
         * @brief Function removes duplicated elements
         * @details Only the first occurrence of given element is preserved
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
        List<T>& operator+=(const List<T>& other)
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
        List<T>& operator+=(const std::initializer_list<T> init_list)
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
        Node* get(size_t index) const;

        /**
         * @brief Function sets value of specifed Node of List
         *
         * @param[in] index index of element to be modified
         * @param[in] value to overwrite Node at index
         * @return operation status
         * @retval true if value of Node was overwritten
         * @retval false if invalid index
         */
        bool set(size_t index, T value);

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
        friend List<T> operator+<>(const List<T>& list1, const List<T>& list2);

        /**
         * @brief Function add end node located just after last user created data
         * Node is used by iterators indicating end of container
         */
        void init_node()
        {
            if (!m_back)
            {
                m_back = new NodeBase;
            }
        }

        /**
         * @brief Function remove next element
         *
         * @param[in] iterator to element to which will be erased
         * @return iterator to element following \p pos
         */
        iterator erase_element(iterator pos)
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

            if (pos == end() || pos == m_back)
            {
                pop_back();
                return iterator(end());
            }

            NodeBase* temp{ pos.m_current_node->m_prev };
            NodeBase* to_remove{ temp->m_next };

            temp->m_next = to_remove->m_next;
            temp->m_next->m_prev = temp;
            delete to_remove;

            m_size--;
            return iterator(temp->m_next);
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
        iterator insert_element_before(iterator pos, const_reference value)
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

            Node* newNode = new Node(value);
            newNode->m_next = temp->m_next;
            newNode->m_prev = temp;

            temp->m_next->m_prev = newNode;
            temp->m_next = newNode;

            m_size++;
            return iterator(newNode);
        }

        /**
         * @brief Function checks List contains iterator
         *
         * @param[in] pos iterator to check
         * @return bool \p pos iterator status
         * @return true if \p pos belong to List
         * @return false if otherwise
         */
        bool if_valid_iterator(const_iterator pos)
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
        size_t distance(const_iterator first, const_iterator last);

        /**
         * @brief Function moves elements from other List object
         *
         * @param[in] pos const_iterator after which content of other container will be inserted
         * @param[in,out] other container to take elements from
         * @param[in] first const_iterator after which elements of \p other will be taken
         * @param[in] last const_iterator until which elements of \p other will be taken
         * @details Content of other object will be taken by constructed object
         */
        void transfer(const_iterator pos, List<T>& other, const_iterator first, const_iterator last);

        NodeBase* m_front{};
        NodeBase* m_back{};
        size_t m_size{};
    };

    template<typename T>
    List<T>::List()
    {
        init_node();
    }

    template<typename T>
    List<T>::List(T value)
    {
        init_node();

        push_front(value);
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
    List<T>& List<T>::operator=(const List<T>& other)
    {
        if (&other != this)
        {
            while (m_front)
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
        operator=(other);
    }

    template<typename T>
    List<T>& List<T>::operator=(List<T>&& other) noexcept
    {
        if (&other != this)
        {
            clear();
            NodeBase* temp = m_back;

            m_front = other.m_front;
            m_back = other.m_back;
            m_size = other.m_size;

            other.m_front = nullptr;
            other.m_back = temp;
            other.m_size = 0;
        }

        return *this;
    }

    template<typename T>
    List<T>::~List()
    {
        clear();

        if (m_back)
        {
            delete m_back;
        }
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
    typename List<T>::reference List<T>::front()
    {
        return *begin();
    }

    template<typename T>
    typename List<T>::const_reference List<T>::front() const
    {
        return *cbegin();
    }

    template<typename T>
    typename List<T>::reference List<T>::back()
    {
        return *(--end());
    }

    template<typename T>
    typename List<T>::const_reference List<T>::back() const
    {
        return *(--cend());
    }

    template<typename T>
    typename List<T>::iterator List<T>::begin() noexcept
    {
        return iterator(m_front);
    }

    template<typename T>
    typename List<T>::const_iterator List<T>::begin() const noexcept
    {
        return const_iterator(m_front);
    }

    template<typename T>
    typename List<T>::const_iterator List<T>::cbegin() const noexcept
    {
        return begin();
    }

    template<typename T>
    typename List<T>::iterator List<T>::end() noexcept
    {
        return iterator(m_back);
    }

    template<typename T>
    typename List<T>::const_iterator List<T>::end() const noexcept
    {
        return const_iterator(m_back);
    }

    template<typename T>
    typename List<T>::const_iterator List<T>::cend() const noexcept
    {
        return end();
    }

    template<typename T>
    bool List<T>::empty() const
    {
        return m_size == 0;
    }

    template<typename T>
    size_t List<T>::size() const
    {
        return m_size;
    }

    template<typename T>
    size_t List<T>::max_size() const noexcept
    {
        return std::numeric_limits<size_t>::max();
    }

    template<typename T>
    void List<T>::clear()
    {
        if (m_front && m_front->m_next)
        {
            NodeBase* temp{ m_front };
            while (temp->m_next)
            {
                m_front->m_prev = nullptr;
                m_front = temp->m_next;
                delete temp;
                temp = m_front;
            }

            m_size = 0;
            m_back->m_prev = nullptr;
        }
    }

    template<typename T>
    typename List<T>::iterator List<T>::insert(const_iterator pos, const_reference value)
    {
        return insert(pos, 1, value);
    }

    template<typename T>
    typename List<T>::iterator List<T>::insert(const_iterator pos, size_t count, const_reference value)
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
    typename List<T>::iterator List<T>::insert(const_iterator pos, std::initializer_list<T> init_list)
    {
        iterator iter(pos.m_current_node);

        if (!if_valid_iterator(pos))
        {
            return nullptr;
        }

        const size_t list_size = init_list.size();
        for (size_t i = 0; i < list_size; i++)
        {
            iter = insert_element_before(iter, init_list.begin()[list_size - 1 - i]);
        }

        return iter;
    }

    template<typename T>
    typename List<T>::iterator List<T>::erase(iterator pos)
    {
        if (!if_valid_iterator(pos))
        {
            return nullptr;
        }

        return erase_element(pos);
    }

    template<typename T>
    typename List<T>::iterator List<T>::erase(iterator first, iterator last)
    {
        if (!if_valid_iterator(first) || !if_valid_iterator(last))
        {
            return nullptr;
        }

        const size_t dist = distance(first, last);
        if (!dist)
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

        Node* newNode = new Node(value);

        if (!m_front)
        {
            m_front = newNode;
            m_front->m_next = m_back;
            m_back->m_prev = newNode;
        }
        else
        {
            newNode->m_next = m_front;
            m_front->m_prev = newNode;
            m_front = newNode;
        }

        m_size++;
    }

    template<typename T>
    void List<T>::pop_front()
    {
        if (!m_front)
        {
            return;
        }

        NodeBase* temp{ m_front };
        if (m_size == 1)
        {
            m_front = nullptr;
            m_back->m_prev = nullptr;
        }
        else
        {
            m_front = m_front->m_next;
            m_front->m_prev = nullptr;
        }
        delete temp;
        m_size--;
    }

    template<typename T>
    void List<T>::push_back(T value)
    {
        init_node();

        Node* newNode = new Node(value);

        if (!m_size)
        {
            m_front = newNode;
            m_front->m_next = m_back;
            m_back->m_prev = newNode;
        }
        else
        {
            m_back->m_prev->m_next = newNode;
            newNode->m_prev = m_back->m_prev;
            newNode->m_next = m_back;
            m_back->m_prev = newNode;
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

        NodeBase* temp{ m_back->m_prev };
        if (m_size == 1)
        {
            // temp is m_front
            m_front = nullptr;
            m_back->m_prev = nullptr;
        }
        else
        {
            m_back->m_prev = temp->m_prev;
            temp->m_prev->m_next = m_back;
        }

        delete temp;
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
        if (&other != this)
        {
            NodeBase* temp_front{ m_front };
            NodeBase* temp_back{ m_back };
            size_t temp_size{ m_size };

            m_front = other.m_front;
            m_back = other.m_back;
            m_size = other.m_size;

            other.m_front = temp_front;
            other.m_back = temp_back;
            other.m_size = temp_size;

            temp_front = nullptr;
            temp_back = nullptr;
            temp_size = 0;
        }
    }

    template<typename T>
    void List<T>::merge(List<T>& other)
    {
        if (&other != this)
        {
            if (m_size)
            {
                m_back->m_prev->m_next = other.m_front;
                other.m_front->m_prev = m_back->m_prev;

                other.m_back->m_prev->m_next = m_back;
                m_back->m_prev = other.m_back->m_prev;
                m_size += other.m_size;

                // cleanup other list
                delete other.m_back;
                other.m_front = nullptr;
                other.m_back = nullptr;
                other.m_size = 0;
            }
            else
            {
                swap(other);
            }
        }
    }

    template<typename T>
    void List<T>::merge(List<T>&& other)
    {
        merge(other);
    }

    template<typename T>
    size_t List<T>::distance(const_iterator first, const_iterator last)
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
    void List<T>::transfer(const_iterator pos, List<T>& other, const_iterator first, const_iterator last)
    {
        if (&other != this && other.m_size > 0)
        {
            NodeBase* temp_prev{ pos.m_current_node->m_prev };
            NodeBase* temp_next{ pos.m_current_node };

            NodeBase* first_to_move{ first.m_current_node };
            NodeBase* last_to_move{ last.m_current_node->m_prev };

            const size_t dist = distance(first, last);

            if (first == other.begin())
            {
                other.m_front = last.m_current_node;
                last.m_current_node->m_prev = nullptr;
            }
            else
            {
                first.m_current_node->m_prev->m_next = last.m_current_node;
                last.m_current_node->m_prev = first.m_current_node->m_prev;
            }

            if (pos == m_front)
            {
                m_front = first_to_move;
                m_front->m_prev = temp_prev;

                last_to_move->m_next = temp_next;
                temp_next->m_prev = last_to_move;
            }
            else
            {
                temp_prev->m_next = first_to_move;
                first_to_move->m_prev = temp_prev;

                last_to_move->m_next = temp_next;
                temp_next->m_prev = last_to_move;
            }

            m_size += dist;
            other.m_size -= dist;
        }
    }

    template<typename T>
    void List<T>::splice(const_iterator pos, List<T>& other)
    {
        transfer(pos, other, other.begin(), other.end());
    }

    template<typename T>
    void List<T>::splice(const_iterator pos, List<T>&& other)
    {
        transfer(pos, other, other.begin(), other.end());
    }

    template<typename T>
    void List<T>::splice(const_iterator pos, List<T>& other, const_iterator iter)
    {
        transfer(pos, other, iter, iter.m_current_node->m_next);
    }

    template<typename T>
    void List<T>::splice(const_iterator pos, List<T>&& other, const_iterator iter)
    {
        transfer(pos, other, iter, iter.m_current_node->m_next);
    }

    template<typename T>
    void List<T>::splice(const_iterator pos, List<T>& other, const_iterator first, const_iterator last)
    {
        transfer(pos, other, first, last);
    }

    template<typename T>
    void List<T>::splice(const_iterator pos, List<T>&& other, const_iterator first, const_iterator last)
    {
        transfer(pos, other, first, last);
    }

    template<typename T>
    void List<T>::remove(const_reference value)
    {
        NodeBase* temp{ m_front };
        NodeBase* next{};
        while (temp)
        {
            next = temp->m_next;
            if (!next)
            {
                return;
            }

            if (Node* node = dynamic_cast<Node*>(m_front))
            {
                if (node->value() == value)
                {
                    pop_front();
                    temp = m_front;
                    continue;
                }
            }

            if (next && next != m_back && next->m_next != nullptr)
            {
                Node* node = dynamic_cast<Node*>(next);
                if (node->value() == value)
                {
                    NodeBase* to_remove = temp->m_next;
                    temp->m_next = to_remove->m_next;
                    to_remove->m_next->m_prev = temp;
                    delete to_remove;
                    m_size--;
                    continue;
                }
            }

            temp = temp->m_next;
        }
    }

    template<typename T>
    void List<T>::reverse()
    {
        NodeBase* temp{ m_front };
        NodeBase* temp_back{ m_back->m_prev };
        m_front = temp_back;
        temp_back = temp;

        NodeBase* prev{};
        NodeBase* next{};

        for (size_t i = 0; i < m_size; i++)
        {
            next = temp->m_next;
            temp->m_next = prev;
            temp->m_prev = next;

            prev = temp;
            temp = next;
        }

        m_front->m_prev = nullptr;
        temp_back->m_next = m_back;
        m_back->m_prev = temp_back;
    }

    template<typename T>
    void List<T>::unique()
    {
        NodeBase* temp{ m_front };
        NodeBase* prev{};
        NodeBase* next{};
        while (temp)
        {
            prev = temp;

            while (prev->m_next)
            {
                next = prev->m_next;

                Node* node_next = dynamic_cast<Node*>(next);
                Node* node_temp = dynamic_cast<Node*>(temp);
                if (next != m_back && node_next && node_temp)
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
                            m_back = prev;
                        }

                        prev->m_next = to_remove->m_next;

                        delete to_remove;
                        m_size--;
                        continue;
                    }
                }

                if (prev)
                {
                    prev = prev->m_next;
                }
            }

            temp = temp->m_next;
        }
    }

    template<typename T>
    typename List<T>::Node* List<T>::get(size_t index) const
    {
        if (index >= m_size)
        {
            return nullptr;
        }

        NodeBase* temp{};

        // select list end to look for selected index
        enum Mode { FRONT, BACK, AUTO };

#ifdef _MSC_VER
        // clang-tidy recommends the variable as const
        // but MSVC generates C4127 'conditional expression is constant' error
        // NOLINTNEXTLINE(misc-const-correctness)
        Mode mode = Mode::AUTO;
#else
        const Mode mode = Mode::AUTO;
#endif // !_MSC_VER

        if (mode == FRONT)
        {
            // count nodes from front
            temp = m_front;
            for (size_t i = 0; i < index; i++)
            {
                temp = temp->m_next;
            }
        }
        else if (mode == BACK)
        {
            // count nodes from back
            temp = m_back->m_prev;
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
                temp = m_front;
                for (size_t i = 0; i < index; i++)
                {
                    temp = temp->m_next;
                }
            }
            else
            {
                temp = m_back->m_prev;
                for (size_t i = m_size - 1; i > index; i--)
                {
                    temp = temp->m_prev;
                }
            }
        }

        return dynamic_cast<Node*>(temp);
    }

    template<typename T>
    bool List<T>::set(size_t index, T value)
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
    List<T> operator+(const List<T>& list1, const List<T>& list2)
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
    std::ostream& operator<<(std::ostream& out, const List<T>& list)
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
    bool operator==(const List<T>& list1, const List<T>& list2)
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
    bool operator!=(const List<T>& list1, const List<T>& list2)
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
    bool operator<(const List<T>& list1, const List<T>& list2)
    {
        auto list1_iter = list1.cbegin();
        auto list2_iter = list2.cbegin();

        while (list1_iter != list1.cend() && list2_iter != list2.cend())
        {
            if (*list1_iter >= *list2_iter)
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
     * @retval true if the content of \p list1 are lexicographically
     *         greater than the content of \p list2
     * @retval false otherwise
     */
    template<typename T>
    bool operator>(const List<T>& list1, const List<T>& list2)
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
    bool operator<=(const List<T>& list1, const List<T>& list2)
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
    bool operator>=(const List<T>& list1, const List<T>& list2)
    {
        return !(operator<(list1, list2));
    }

    /// @todo implement non-member specialized swap function

    /// @todo implement non-member specialized erase function

    /// @todo implement non-member specialized erase_if function

}
#endif // !LIST_H
