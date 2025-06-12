/**
 * @file List.h
 * @brief This file contains implementation of List class
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <iostream>

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
    struct NodeBase
    {
        virtual ~NodeBase() = default;
        NodeBase* m_next{};
        NodeBase* m_prev{};
    };

    /**
     * @brief Implements Node template class with pointer to adjacent elements
     *
     * @tparam T type of data stored in Node
     */
    template<typename T>
    class Node : NodeBase
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

        /**
         * @brief Function returns pointer to next Node object
         *
         * @return Node<T>* pointer to value stored in Node
         */
        Node<T>* next() const
        {
            return static_cast<Node<T>*>(NodeBase::m_next);
        }

        /**
         * @brief Function returns pointer to previous Node object
         *
         * @return Node<T>* pointer to value stored in Node
         */
        Node<T>* prev() const
        {
            return static_cast<Node<T>*>(NodeBase::m_prev);
        }

    private:

        /**
         * @brief Forward friend declaration of List
         *
         * @tparam T type of data stored in Node/List objects
         */
        template<typename T>
        friend class List;

        T m_value{};
    };

    /**
     * @brief Implements Basic_Iterator
     *
     * Class is used to generate Iterator and Const_Iterator types.
     * Template variable \p IF_CONST control whether reference
     * or const reference is returned to underlying data type
     *
     * @tparam IF_CONST if \p true generate class with const reference to underlying data type
     * @tparam T type of data stored in Node
     */
    template<bool IF_CONST, typename T>
    class Basic_Iterator : NodeBase
    {
    public:

        using iterator_type = typename std::conditional<IF_CONST, const T, T>::type;

        /**
         * @brief Construct a new Basic_Iterator object
         *
         * @param[in] node input Node
         */
        Basic_Iterator(NodeBase* node) noexcept
            : m_current_node{ node }
        {
        }

        /**
         * @brief Destroy the Basic_Iterator object
         */
        ~Basic_Iterator() = default;

        /**
         * @brief Overload operator= to assign \p node to currently pointed Basic_Iterator
         *
         * @param[in] node input Node
         * @return Basic_Iterator& reference to updated Node
         */
        Basic_Iterator& operator=(NodeBase* node)
        {
            this->m_current_node = node;
            return *this;
        }

        /**
         * @brief Overload pre-increment operator++ to point Basic_Iterator at next Node
         *
         * @return Basic_Iterator& reference to next Node
         */
        Basic_Iterator& operator++()
        {
            if (m_current_node)
            {
                m_current_node = m_current_node->m_next;
            }

            return *this;
        }

        /**
         * @brief Overload post-increment operator++ to point Basic_Iterator at next Node
         *
         * @return Basic_Iterator& reference to next Basic_Iterator
         */
        Basic_Iterator operator++(int)
        {
            Basic_Iterator<IF_CONST, T> Basic_Iterator = *this;
            ++(*this);
            return Basic_Iterator;
        }

        /**
         * @brief Overload pre-decrement operator-- to point Basic_Iterator at previous Node
         *
         * @return Basic_Iterator& reference to previous Node
         */
        Basic_Iterator& operator--()
        {
            if (m_current_node)
            {
                m_current_node = m_current_node->m_prev;
            }

            return *this;
        }

        /**
         * @brief Overload post-decrement operator-- to point Basic_Iterator at previous Node
         *
         * @return Basic_Iterator& reference to previous Basic_Iterator
         */
        Basic_Iterator operator--(int)
        {
            Basic_Iterator<IF_CONST, T> Basic_Iterator = *this;
            --(*this);
            return Basic_Iterator;
        }

        /**
         * @brief Overload operator!= for Basic_Iterator objects comparison
         *
         * @param[in] other input Basic_Iterator of \p other object
         * @return bool comparison result
         * @retval true if Basic_Iterator objects are the same
         * @retval false if Basic_Iterator objects are different
         */
        bool operator==(const Basic_Iterator<IF_CONST, T>& other)
        {
            return m_current_node == other.m_current_node;
        }

        /**
         * @brief Overload operator!= for Basic_Iterator objects comparison
         *
         * @param[in] other input Basic_Iterator of \p other object
         * @return bool comparison result
         * @retval true if Basic_Iterator objects are different
         * @retval false if Basic_Iterator objects are the same
         */
        bool operator!=(const Basic_Iterator<IF_CONST, T>& other)
        {
            return !operator==(other);// m_current_node != other.m_current_node;
        }

        /**
         * @brief Overload operator[] for Basic_Iterator iterator access
         *
         * @param[in] index number of Node to move forward
         * @return Basic_Iterator to Node pointed by \p index from List front
         * @retval valid Basic_Iterator if index is valid
         * @retval nullptr if index is invalid
         */
        Basic_Iterator operator[](size_t index)
        {
            Node<T>* temp{ static_cast<Node<T>*>(m_current_node) };

            if (index >= 0)
            {
                for (size_t i = 0; i < index; i++)
                {
                    if (temp->m_next)
                    {
                        temp = temp->next();
                    }
                    else
                    {
                        return nullptr;
                    }
                }
            }
            else
            {
                for (size_t i = 0; i < index; i++)
                {
                    if (temp->m_prev)
                    {
                        temp = temp->prev();
                    }
                    else
                    {
                        return nullptr;
                    }
                }
            }

            return temp;
        }

        /**
         * @brief Overload operator* to dereference Node value / data
         *
         * @return T& reference or const reference to data stored in Node
         */
        iterator_type& operator*() const noexcept
        {
            return static_cast<Node<T>*>(m_current_node)->value();
        }

        /**
         * @brief Overload operator-> to get pointer to Node value / data
         *
         * @return T* pointer to data stored in Node
         */
        T* operator->()
        {
            return &static_cast<Node<T>*>(m_current_node)->value();
        }

        /**
         * @brief convert Basic_Iterator to Basic_Const_Iterator
         */
        operator Basic_Iterator<true, T>()
        {
            return Basic_Iterator<true, T>(m_current_node);
        }

    private:

        template<typename T>
        friend class List;

        NodeBase* m_current_node{};
    };

    using Const_Iterator = Basic_Iterator<true, T>;
    using Iterator = Basic_Iterator<false, T>;

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
    void assign(size_t count, const T& value);

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
    T& front();

    /**
     * @brief Function returns const reference value stored in List first Node
     *
     * @return const reference to data stored in List first Node
     */
    const T& front() const;

    /**
     * @brief Function returns reference to value stored in List last Node
     *
     * @return reference to data stored in List last Node
     */
    T& back();

    /**
     * @brief Function returns const reference value stored in List last Node
     *
     * @return const reference to data stored in List last Node
     */
    const T& back() const;

    /**
     * @brief Function returns pointer to List first Node
     *
     * @return Iterator Iterator to List first Node
     */
    Iterator begin() noexcept;

    /**
     * @brief Function returns const pointer to List first Node
     *
     * @return Const_Iterator const Iterator to List first Node
     */
    Const_Iterator begin() const noexcept;

    /**
     * @brief Function returns const pointer to List first Node
     *
     * @return Const_Iterator const Iterator to List first Node
     */
    Const_Iterator cbegin() const noexcept;

    /**
     * @brief Function returns pointer to List last Node
     *
     * @return Iterator Iterator to List last Node
     */
    Iterator end() noexcept;

    /**
     * @brief Function returns pointer to List last Node
     *
     * @return Const_Iterator const Iterator to List last Node
     */
    Const_Iterator end() const noexcept;

    /**
     * @brief Function returns pointer to List last Node
     *
     * @return Const_Iterator const Iterator to List last Node
     */
    Const_Iterator cend() const noexcept;

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
     * @param[in] \p pos Const_Iterator to insert element before
     * @param[in] value element of type T to be inserted before \p pos
     * @return Iterator to list element
     * @retval Iterator to inserted element
     * @retval Iterator to \p pos if no element is inserted
     */
    Iterator insert(Const_Iterator pos, const T& value);

    /**
     * @brief Function inserts new Node before specified \p pos
     *
     * @param[in] pos Const_Iterator to insert element before
     * @param[in] count number of elements to insert before \p pos
     * @param[in] value element of type T to be inserted
     * @return Iterator to list element
     * @retval Iterator to first inserted element
     * @retval Iterator to \p pos if no element is inserted
     */
    Iterator insert(Const_Iterator pos, size_t count, const T& value);

    /**
     * @brief Function inserts new Node before specified \p pos
     *
     * @param[in] pos Const_Iterator to insert element before
     * @param[in] std::initializer_list to insert before \p pos
     * @return Iterator to list element
     * @retval Iterator to first inserted element
     * @retval Iterator to \p pos if no element is inserted
     */
    Iterator insert(Const_Iterator pos, std::initializer_list<T> init_list);

    /// @todo add insert_range

    /// @todo add emplace

    /**
    * @brief Function erases Node object at specified \pos
    *
    * @param[in] \p pos Iterator to element to erase
    * @return Iterator following erased element
    * @retval Iterator to element following \p pos
    * @retval begin Iterator if \p pos was first element prior to removal
    * @retval end Iterator if \p pos was last element prior to removal
    */
    Iterator erase(Iterator pos);

    /**
    * @brief Function erases Node object at specified \pos
    *
    * @param[in] \p pos Iterator to element to erase
    * @return Iterator following erased element
    * @retval Iterator to element following \p pos
    * @retval begin Iterator if \p pos was first element prior to removal
    * @retval end Iterator if \p pos was last element prior to removal
    */
    Iterator erase(Const_Iterator pos);

    /**
     * @brief Function erases Node objects in range [first, last)
     *
     * @param[in] first element to erase
     * @param[in] last element after last erased element
     * @return Iterator following last erased element
     * @retval Iterator to \p last
     * @retval end Iterator if \p last was end element prior to removal
     * @retval last Iterator if \p first to \last is empty range
     */
    Iterator erase(Iterator first, Iterator last);

    /**
     * @brief Function erases Node objects in range [first, last)
     *
     * @param[in] first element to erase
     * @param[in] last element after last erased element
     * @return Iterator following last erased element
     * @retval Iterator to \p last
     * @retval end Iterator if \p last was end element prior to removal
     * @retval last Iterator if \p first to \last is empty range
     */
    Iterator erase(Const_Iterator first, Const_Iterator last);

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
    void resize(size_t count, const T& value);

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
     * @param[in] pos Const_Iterator before which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @details Content of other object will be taken by constructed object
     */
    void splice(Const_Iterator pos, List<T>& other);

    /**
     * @brief Function moves elements from other List object
     *
     * @param[in] pos Const_Iterator before which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @details Content of other object will be taken by constructed object
     */
    void splice(Const_Iterator pos, List<T>&& other);

    /**
     * @brief Function moves elements from other List object
     *
     * @param[in] pos Const_Iterator before which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] it Const_Iterator pointing to element to move
     * @details Content of other object will be taken by constructed object
     */
    void splice(Const_Iterator pos, List<T>& other, Const_Iterator it);

    /**
     * @brief Function moves elements from other List object
     *
     * @param[in] pos Const_Iterator before which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] it Const_Iterator pointing to element to move
     * @details Content of other object will be taken by constructed object
     */
    void splice(Const_Iterator pos, List<T>&& other, Const_Iterator it);

    /**
     * @brief Function moves elements in range [first, last) from other List object
     *
     * @param[in] pos Const_Iterator before which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] first Const_Iterator pointing to first element to move
     * @param[in] last Const_Iterator pointing to element after last taken element
     * @details Content of other object will be taken by constructed object
     */
    void splice(Const_Iterator pos, List<T>& other, Const_Iterator first, Const_Iterator last);

    /**
     * @brief Function moves elements in range [first, last) from other List object
     *
     * @param[in] pos Const_Iterator before which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] first Const_Iterator pointing to first element to move
     * @param[in] last Const_Iterator pointing to element after last taken element
     * @details Content of other object will be taken by constructed object
     */
    void splice(Const_Iterator pos, List<T>&& other, Const_Iterator first, Const_Iterator last);

    /**
     * @brief Function removes all elements equal to \p value
     *
     * @param[in] value value of elements to remove
     */
    void remove(const T& value);

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
    template<typename T>
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
     * @param[in] other List to read elements from
     * @return List<T>&
     */
    template<typename T>
    List<T>& operator+=(const std::initializer_list<T> il)
    {
        for (const auto& item : il)
        {
            push_back(item);
        }

        return *this;
    }

    /**
     * @brief Function returns pointer to specific Node of List
     *
     * @param[in] index index of element
     * @return Node<T>*
     * @retval Node<T>* if index is valid
     * @retval nullptr if invalid index
     */
    Node<T>* get(int index) const;

    /**
     * @brief Function sets value of specifed Node of List
     *
     * @param[in] index index of element to be modified
     * @param[in] value to overwrite Node at index
     * @return operation status
     * @retval true if value of Node was overwritten
     * @retval false if invalid index
     */
    bool set(int index, T value);

private:

    template<typename T>
    friend List<T> operator+(const List<T>& l1, const List<T>& l2);

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
     * @param[in] Iterator to element to which will be erased
     * @return Iterator to element following \p pos
     */
    Iterator erase_element(Iterator pos)
    {
        if (!if_valid_iterator(pos))
        {
            return nullptr;
        }

        if (pos == begin())
        {
            pop_front();
            return Iterator(begin());
        }

        if (pos == end() || pos == m_back)
        {
            pop_back();
            return Iterator(end());
        }

        Node<T>* temp = static_cast<Node<T>*>(pos.m_current_node->m_prev);
        Node<T>* to_remove = static_cast<Node<T>*>(temp->m_next);

        temp->m_next = to_remove->m_next;
        temp->m_next->m_prev = temp;
        delete to_remove;

        m_size--;
        return Iterator(temp->m_next);
    }

    /**
    * @brief Function inserts new Node before specified List Iterator
    *
    * @param[in] pos Iterator to insert element before
    * @param[in] value element of type T to be inserted
    * @return Iterator to list element
    * @retval Iterator to inserted element
    * @retval Iterator to \p pos if no element was inserted
    */
    Iterator insert_element_before(Iterator pos, const T& value)
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

        Node<T>* temp = static_cast<Node<T>*>(pos.m_current_node->m_prev);

        Node<T>* newNode = new Node<T>(value);
        newNode->m_next = temp->m_next;
        newNode->m_prev = temp;

        temp->m_next->m_prev = newNode;
        temp->m_next = newNode;

        m_size++;
        return Iterator(newNode);
    }

    /**
     * @brief Function checks List contains Iterator
     *
     * @param[in] pos Iterator to check
     * @return bool \p pos iterator status
     * @return true if \p pos belong to List
     * @return false if otherwise
     */
    bool if_valid_iterator(Const_Iterator pos)
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
     * @param[in] first Const_Iterator pointing first element
     * @param[in] last Const_Iterator pointing to last (inclusive) element
     * @return size_t number of elements between input elements
     */
    size_t distance(Const_Iterator first, Const_Iterator last);

    /**
     * @brief Function moves elements from other List object
     *
     * @param[in] pos Const_Iterator after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] first Const_Iterator after which elements of \p other will be taken
     * @param[in] last Const_Iterator until which elements of \p other will be taken
     * @details Content of other object will be taken by constructed object
     */
    void transfer(Const_Iterator pos, List<T>& other, Const_Iterator first, Const_Iterator last);

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
    for (int i = 0; i < other.size(); i++)
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

        for (int i = 0; i < other.size(); i++)
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
        m_front = other.m_front;
        m_back = other.m_back;
        m_size = other.m_size;

        other.m_front = nullptr;
        other.m_back = nullptr;
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
void List<T>::assign(size_t count, const T& value)
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
T& List<T>::front()
{
    return *begin();
}

template<typename T>
const T& List<T>::front() const
{
    return *cbegin();
}

template<typename T>
T& List<T>::back()
{
    return *(--end());
}

template<typename T>
const T& List<T>::back() const
{
    return *(--cend());
}

template<typename T>
typename List<T>::Iterator List<T>::begin() noexcept
{
    return Iterator(m_front);
}

template<typename T>
typename List<T>::Const_Iterator List<T>::begin() const noexcept
{
    return Const_Iterator(m_front);
}

template<typename T>
typename List<T>::Const_Iterator List<T>::cbegin() const noexcept
{
    return begin();
}

template<typename T>
typename List<T>::Iterator List<T>::end() noexcept
{
    return Iterator(m_back);
}

template<typename T>
typename List<T>::Const_Iterator List<T>::end() const noexcept
{
    return Const_Iterator(m_back);
}

template<typename T>
typename List<T>::Const_Iterator List<T>::cend() const noexcept
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
    Node<T>* temp = static_cast<Node<T>*>(m_front);
    while (m_front)
    {
        m_front = m_front->m_next;
        delete temp;
        temp = static_cast<Node<T>*>(m_front);
    }

    m_size = 0;
    m_front = nullptr;
    m_back = nullptr;
}

template<typename T>
typename List<T>::Iterator List<T>::insert(Const_Iterator pos, const T& value)
{
    return insert(pos, 1, value);
}

template<typename T>
typename List<T>::Iterator List<T>::insert(Const_Iterator pos, size_t count, const T& value)
{
    Iterator it{ pos.m_current_node };

    if (!if_valid_iterator(pos))
    {
        return nullptr;
    }

    for (size_t i = 0; i < count; i++)
    {
        it = insert_element_before(it, value);
    }

    return it;
}

template<typename T>
typename List<T>::Iterator List<T>::insert(Const_Iterator pos, std::initializer_list<T> init_list)
{
    Iterator it(pos.m_current_node);

    if (!if_valid_iterator(pos))
    {
        return nullptr;
    }

    size_t list_size = init_list.size();
    for (size_t i = 0; i < list_size; i++)
    {
        it = insert_element_before(it, init_list.begin()[list_size - 1 - i]);
    }

    return it;
}

template<typename T>
typename List<T>::Iterator List<T>::erase(Iterator pos)
{
    if (!if_valid_iterator(pos))
    {
        return nullptr;
    }

    return erase_element(pos);
}

template<typename T>
typename List<T>::Iterator List<T>::erase(Iterator first, Iterator last)
{
    if (!if_valid_iterator(first) || !if_valid_iterator(last))
    {
        return nullptr;
    }

    size_t dist = distance(first, last);
    if (!dist)
    {
        return last;
    }

    Iterator it(first.m_current_node);
    for (size_t i = 0; i < dist; i++)
    {
        it = erase_element(it);
    }

    return it;
}

template<typename T>
void List<T>::push_front(T value)
{
    init_node();

    Node<T>* newNode = new Node<T>(value);

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

    Node<T>* temp = static_cast<Node<T>*>(m_front);
    if (m_size == 1)
    {
        m_front = nullptr;
        m_back = nullptr;
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

    Node<T>* newNode = new Node<T>(value);

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

    Node<T>* temp = static_cast<Node<T>*>(m_back);
    if (m_size == 1)
    {
        m_front = nullptr;
        m_back = nullptr;
    }
    else
    {
        m_back = temp->m_prev;
        m_back->m_next = nullptr;
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
void List<T>::resize(size_t count, const T& value)
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
        List<T> temp;
        temp.m_front = m_front;
        temp.m_back = m_back;
        temp.m_size = m_size;

        m_front = other.m_front;
        m_back = other.m_back;
        m_size = other.m_size;

        other.m_front = temp.m_front;
        other.m_back = temp.m_back;
        other.m_size = temp.m_size;

        temp.m_front = nullptr;
        temp.m_back = nullptr;
        temp.m_size = 0;
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
size_t List<T>::distance(Const_Iterator first, Const_Iterator last)
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
void List<T>::transfer(Const_Iterator pos, List<T>& other, Const_Iterator first, Const_Iterator last)
{
    if (&other != this && other.m_size > 0)
    {
        Node<T>* temp_prev = static_cast<Node<T>*>(pos.m_current_node);    // to append to
        Node<T>* temp_next = static_cast<Node<T>*>(first.m_current_node);  // does not move

        Node<T>* first_to_move = static_cast<Node<T>*>(temp_next->m_next);
        Node<T>* last_to_move = temp_next;
        size_t ctr = 0;
        size_t dist = distance(first, last);
        for (size_t i = 0; i < dist; i++)
        {
            if (last_to_move)
            {
                last_to_move = static_cast<Node<T>*>(last_to_move->m_next);
                ctr++;
            }
        }

        temp_next->m_next = last_to_move->m_next;
        if (last_to_move->m_next)
        {
            last_to_move->m_next->m_prev = temp_next;
        }
        else // last_to_move was last list object
        {
            other.m_back = temp_next;
        }

        last_to_move->m_next = temp_prev->m_next;
        if (!last_to_move->m_next)
        {
            m_back = last_to_move;
        }

        if (temp_prev->m_next)
        {
            temp_prev->m_next->m_prev = last_to_move;
        }

        temp_prev->m_next = first_to_move;
        first_to_move->m_prev = temp_prev;

        m_size += ctr;
        other.m_size -= ctr;
    }
}

template<typename T>
void List<T>::splice(Const_Iterator pos, List<T>& other)
{
    if (&other != this && other.m_size > 0)
    {
        Node<T>* temp = static_cast<Node<T>*>(pos.m_current_node);
        Node<T>* temp_next = static_cast<Node<T>*>(temp->m_next);

        temp->m_next = other.m_front;
        other.m_front->m_prev = temp;

        if (temp_next)
        {
            temp_next->m_prev = other.m_back->m_prev;
        }
        else
        {
            m_back->m_prev = other.m_back->m_prev;
        }
        other.m_back->m_prev->m_next = temp_next;

        m_size += other.m_size;

        // cleanup other list
        delete other.m_back;
        other.m_front = nullptr;
        other.m_back = nullptr;
        other.m_size = 0;
    }
}

template<typename T>
void List<T>::splice(Const_Iterator pos, List<T>&& other)
{
    splice(pos, other);
}

template<typename T>
void List<T>::splice(Const_Iterator pos, List<T>& other, Const_Iterator it)
{
    transfer(pos, other, it, it.m_current_node->m_next);
}

template<typename T>
void List<T>::splice(Const_Iterator pos, List<T>&& other, Const_Iterator it)
{
    transfer(pos, other, it, it.m_current_node->m_next);
}

template<typename T>
void List<T>::splice(Const_Iterator pos, List<T>& other, Const_Iterator first, Const_Iterator last)
{
    transfer(pos, other, first, last);
}

template<typename T>
void List<T>::splice(Const_Iterator pos, List<T>&& other, Const_Iterator first, Const_Iterator last)
{
    transfer(pos, other, first, last);
}

template<typename T>
void List<T>::remove(const T& value)
{
    Node<T>* temp = static_cast<Node<T>*>(m_front);
    Node<T>* next{};
    while (temp)
    {
        next = temp->next();

        if (static_cast<Node<T>*>(m_front)->value() == value)
        {
            pop_front();
            temp = static_cast<Node<T>*>(m_front);
            continue;
        }

        if (next && next->value() == value)
        {
            Node<T>* to_remove = temp->next();
            temp->m_next = to_remove->next();
            delete to_remove;
            m_size--;
            continue;
        }

        temp = temp->next();
    }

    if (m_size == 0)
    {
        m_front = nullptr;
        m_back = nullptr;
    }
}

template<typename T>
void List<T>::reverse()
{
    Node<T>* temp = static_cast<Node<T>*>(m_front);
    Node<T>* temp_back = static_cast<Node<T>*>(m_back->m_prev);
    m_front = temp_back;
    temp_back = temp;

    Node<T>* prev{};
    Node<T>* next{};

    for (int i = 0; i < m_size; i++)
    {
        next = static_cast<Node<T>*>(temp->m_next);
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
    Node<T>* temp = static_cast<Node<T>*>(m_front);
    Node<T>* prev{};
    Node<T>* next{};
    while (temp)
    {
        prev = temp;

        while (prev)
        {
            next = static_cast<Node<T>*>(prev->m_next);

            if (next && next->value() == temp->value() && next != m_back)
            {
                Node<T>* to_remove = next;

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

            if (prev)
            {
                prev = static_cast<Node<T>*>(prev->m_next);
            }
        }

        temp = static_cast<Node<T>*>(temp->m_next);
    }
}

template<typename T>
List<T>::Node<T>* List<T>::get(int index) const
{
    if (index < 0 || index >= m_size)
    {
        return nullptr;
    }

    Node<T>* temp{};

    constexpr int ver = 1;
    if (ver == 0)
    {
        // count nodes from front
        temp = static_cast<Node<T>*>(m_front);
        for (size_t i = 0; i < index; i++)
        {
            temp = static_cast<Node<T>*>(temp->m_next);
        }
    }
    else if (ver == 1)
    {
        // optimize counting nodes from front or back
        if (index < m_size / 2)
        {
            temp = static_cast<Node<T>*>(m_front);
            for (size_t i = 0; i < index; i++)
            {
                temp = static_cast<Node<T>*>(temp->m_next);
            }
        }
        else
        {
            temp = static_cast<Node<T>*>(m_back->m_prev);
            for (size_t i = m_size - 1; i > index; i--)
            {
                temp = static_cast<Node<T>*>(temp->m_prev);
            }
        }
    }
    else
    {
        // count nodes from back
        temp = static_cast<Node<T>*>(m_back->m_prev);
        for (size_t i = m_size - 1; i > index; i--)
        {
            temp = static_cast<Node<T>*>(temp->m_prev);
        }
    }

    return temp;
}

template<typename T>
bool List<T>::set(int index, T value)
{
    Node<T>* temp = get(index);
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
 * @param[in] l1 input List
 * @param[in] l2 input List
 * @return List<T>
 */
template<typename T>
List<T> operator+(const List<T>& l1, const List<T>& l2)
{
    List<T> temp(l1);

    for (auto it = l2.cbegin(); it != l2.cend(); ++it)
    {
        T value = *it;
        temp.push_back(value);
    }

    return temp;
}

/**
 * @brief Overloads operator to print all elements of List
 *
 * @tparam T type of initializer list elements
 * @param[in,out] out reference to output stream
 * @param[in] ll List to print
 * @return std::ostream&
 */
template<typename T>
std::ostream& operator<<(std::ostream& out, const List<T>& ll)
{
    if (ll.empty())
    {
        return out;
    }

    for (auto it = ll.cbegin(); it != ll.cend(); ++it)
    {
        T value = *it;
        out << value << ' ';
    }

    return out;
}

/**
 * @brief The relational operator compares two List objects
 *
 * @tparam T type of data stored in List
 * @param[in] l1 input container
 * @param[in] l2 input container
 * @retval true if containers are equal
 * @retval false if containers are not equal
 */
template<typename T>
bool operator==(const List<T>& l1, const List<T>& l2)
{
    if (l1.size() != l2.size())
    {
        return false;
    }

    auto l1_it = l1.cbegin();
    auto l2_it = l2.cbegin();

    while (l1_it != l1.cend() && l2_it != l2.cend())
    {
        if (*l1_it != *l2_it)
        {
            return false;
        }

        l1_it++;
        l2_it++;
    }

    return true;
}

/**
 * @brief The relational operator compares two List objects
 *
 * @tparam T type of data stored in List
 * @param[in] l1 input container
 * @param[in] l2 input container
 * @retval true if containers are not equal
 * @retval false if containers are equal
 */
template<typename T>
bool operator!=(const List<T>& l1, const List<T>& l2)
{
    return !(operator==(l1, l2));
}

/**
 * @brief The relational operator compares two List objects
 *
 * @tparam T type of data stored in List
 * @param[in] l1 input container
 * @param[in] l2 input container
 * @retval true if the content of \p l1 are lexicographically
 *         less than the content of \p l2
 * @retval false otherwise
 */
template<typename T>
bool operator<(const List<T>& l1, const List<T>& l2)
{
    auto l1_it = l1.cbegin();
    auto l2_it = l2.cbegin();

    while (l1_it != l1.cend() && l2_it != l2.cend())
    {
        if (*l1_it >= *l2_it)
        {
            return false;
        }

        l1_it++;
        l2_it++;
    }

    return true;
}

/**
 * @brief The relational operator compares two List objects
 *
 * @tparam T type of data stored in List
 * @param[in] l1 input container
 * @param[in] l2 input container
 * @retval true if the content of \p l1 are lexicographically
 *         greater than the content of \p l2
 * @retval false otherwise
 */
template<typename T>
bool operator>(const List<T>& l1, const List<T>& l2)
{
    return operator<(l2, l1);
}

/**
 * @brief The relational operator compares two List objects
 *
 * @tparam T type of data stored in List
 * @param[in] l1 input container
 * @param[in] l2 input container
 * @retval true if the content of \p l1 are lexicographically
 *         less or equal than the content of \p l2
 * @retval false otherwise
 */
template<typename T>
bool operator<=(const List<T>& l1, const List<T>& l2)
{
    return !(operator>(l1, l2));
}

/**
 * @brief The relational operator compares two List objects
 *
 * @tparam T type of data stored in List
 * @param[in] l1 input container
 * @param[in] l2 input container
 * @retval true if the content of \p l1 are lexicographically
 *         greater or equal than the content of \p l2
 * @retval false otherwise
 */
template<typename T>
bool operator>=(const List<T>& l1, const List<T>& l2)
{
    return !(operator<(l1, l2));
}

/// @todo implement non-member specialized swap function

/// @todo implement non-member specialized erase function

/// @todo implement non-member specialized erase_if function


#endif // !LIST_H
