/**
 * @file ForwardList.h
 * @brief This file contains implementation of ForwardList class
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <initializer_list>
#include <iostream>
#include <limits>

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
     * @brief Implements Node template class with pointer to next element
     *
     * @tparam T type of data stored in Node
     */
    template<typename T>
    class Node
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
        ~Node()
        {
        }

        /**
         * @brief Function returns value stored in Node object
         *
         * @return T to value stored in Node
         */
        T& value()
        {
            return m_value;
        }

        /**
         * @brief Function returns value stored in Node object
         *
         * @return T to value stored in Node
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
            return m_next;
        }

    private:

        /**
         * @brief Forward friend declaration of ForwardList
         *
         * @tparam T type of data stored in Node objects
         */
        template<typename T>
        friend class ForwardList;

        T m_value{};
        Node<T>* m_next{};
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
    class Basic_Iterator
    {
    public:

        using iterator_type = typename std::conditional<IF_CONST, const T, T>::type;

        /**
         * @brief Construct a new Basic_Iterator object
         *
         * @param[in] node input Node
         */
        Basic_Iterator(Node<T>* node) noexcept
            : m_current_node{ node }
        {
        }

        /**
         * @brief Destroy the Basic_Iterator object
         */
        ~Basic_Iterator()
        {
        }

        /**
         * @brief Overload operator= to assign \p node to currently pointed Basic_Iterator
         *
         * @param[in] node input Node
         * @return Basic_Iterator& reference to updated Node
         */
        Basic_Iterator& operator=(Node<T>* node)
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
         * @return Basic_Iterator to Node pointed by \p index from ForwardList front
         * @retval valid Basic_Iterator if index is valid
         * @retval nullptr if index is invalid
         */
        Basic_Iterator operator[](size_t index)
        {
            Node<T>* temp{};
            if (index >= 0)
            {
                temp = m_current_node;

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
            return m_current_node->value();
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
        friend class ForwardList;

        Node<T>* m_current_node{};
    };

    using Const_Iterator = Basic_Iterator<true, T>;
    using Iterator = Basic_Iterator<false, T>;

    /**
     * @brief Construct a new ForwardList object
     */
    ForwardList();

    /**
     * @brief Construct a new ForwardList object using value of type T
     *
     * @param[in] value of type T
     */
    ForwardList(T value);

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
    ForwardList& operator=(const ForwardList<T>& other);

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
    ForwardList& operator=(ForwardList<T>&& other) noexcept;

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
    void assign(size_t count, const T& value);

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
    T& front();

    /**
     * @brief Function returns const reference value stored in ForwardList first Node
     *
     * @return const reference to data stored in ForwardList first Node
     */
    const T& front() const;

    /// @todo add before_begin

    /// @todo add const before_begin

    /**
     * @brief Function returns pointer to ForwardList first Node
     *
     * @return Iterator Iterator to ForwardList first Node
     */
    Iterator begin() noexcept;

    /**
     * @brief Function returns const pointer to ForwardList first Node
     *
     * @return Const_Iterator const Iterator to ForwardList first Node
     */
    Const_Iterator begin() const noexcept;

    /**
     * @brief Function returns const pointer to ForwardList first Node
     *
     * @return Const_Iterator const Iterator to ForwardList first Node
     */
    Const_Iterator cbegin() const noexcept;

    /**
     * @brief Function returns pointer to ForwardList last Node
     *
     * @return Iterator Iterator to ForwardList last Node
     */
    Iterator end() noexcept;

    /**
     * @brief Function returns pointer to ForwardList last Node
     *
     * @return Const_Iterator const Iterator to ForwardList last Node
     */
    Const_Iterator end() const noexcept;

    /**
     * @brief Function returns pointer to ForwardList last Node
     *
     * @return Const_Iterator const Iterator to ForwardList last Node
     */
    Const_Iterator cend() const noexcept;

    /**
     * @brief Function checks if container has no elements
     *
     * @retval true if container is empty
     * @retval false if container is not empty
     */
    bool empty() const;

    /// @todo add max_size()

    /**
     * @brief Function removes all elements of ForwardList
     */
    void clear();

    /**
     * @brief Function inserts new Node after specified ForwardList Const_Iterator
     *
     * @param[in] pos Const_Iterator to insert element after
     * @param[in] value element of type T to be inserted after \p pos
     * @return pointer to inserted element
     * @retval Const_Iterator* pointer to inserted element
     * @retval nullptr if invalid inputIterator
     */
    Iterator* insert_after(Const_Iterator pos, const T& value);

    /**
     * @brief Function inserts new Node after specified ForwardList Const_Iterator
     *
     * @param[in] pos Const_Iterator to insert element after
     * @param[in] count number of elements to insert after \p pos
     * @param[in] value element of type T to be inserted
     * @return pointer to the last inserted element
     * @retval 1Const_Iterator* pointer to last inserted element
     * @retval nullptr if invalid input Iterator
     */
    Iterator* insert_after(Const_Iterator pos, size_t count, const T& value);

    /**
     * @brief Function inserts new Node after specified ForwardList Const_Iterator
     *
     * @param[in] pos Const_Iterator to insert element after
     * @param[in] std::initializer_list to insert after \p pos
     * @return pointer to the last inserted element
     * @retval Iterator* pointer to last inserted element
     * @retval nullptr if invalid input Iterator
     */
    Iterator* insert_after(Const_Iterator pos, std::initializer_list<T> init_list);

    /// @todo add emplace_after

    /**
    * @brief Function erases Node after specified ForwardList Const_Iterator
    *
    * @param[in] pos Const_Iterator after which element will be erased
    * @return pointer to element after deleted Iterator
    * @retval Iterator* pointer to element after deleted element
    * @retval nullptr if invalid Iterator
    */
    Iterator* erase_after(Const_Iterator pos);

    /**
     * @brief Function erases Node between specified ForwardList Const_Iterators
     *
     * @param[in] first element after which element will be erased
     * @param[in] last element after last erased element
     * @return pointer to element after last deleted element
     * @retval Const_Iterator* pointer to element after deleted element
     * @retval nullptr if invalid Iterator
     */
    Iterator* erase_after(Const_Iterator first, Const_Iterator last);

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
    void resize(size_t count, const T& value);

    /**
     * @brief Function swaps content of two ForwardList objects
     *
     * @param[in,out] other object to swap content with
     */
    void swap(ForwardList<T>& other) noexcept;

    /**
     * @brief Function combines two ForwardLists
     *
     * @param[in,out] other container to take elements from
     * @details Content of other object will be taken by constructed object
     */
    void merge(ForwardList<T>& other);

    /**
     * @brief Function combines two ForwardLists
     *
     * @param[in,out] other container to take elements from
     * @details Content of other object will be taken by constructed object
     */
    void merge(ForwardList<T>&& other);

    /**
     * @brief Function moves elements from other ForwardList object
     *
     * @param[in] pos Const_Iterator after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @details Content of other object will be taken by constructed object
     */
    void splice_after(Const_Iterator pos, ForwardList<T>& other);

    /**
     * @brief Function moves elements from other ForwardList object
     *
     * @param[in] pos Const_Iterator after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @details Content of other object will be taken by constructed object
     */
    void splice_after(Const_Iterator pos, ForwardList<T>&& other);

    /**
     * @brief Function moves elements from other ForwardList object
     *
     * @param[in] pos Const_Iterator after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] it Const_Iterator after which elements of \p other will be taken
     * @details Content of other object will be taken by constructed object
     */
    void splice_after(Const_Iterator pos, ForwardList<T>& other, Const_Iterator it);

    /**
     * @brief Function moves elements from other ForwardList object
     *
     * @param[in] pos Const_Iterator after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] it Const_Iterator after which elements of \p other will be taken
     * @details Content of other object will be taken by constructed object
     */
    void splice_after(Const_Iterator pos, ForwardList<T>&& other, Const_Iterator it);

    /**
     * @brief Function moves elements from other ForwardList object
     *
     * @param[in] pos Const_Iterator after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] first Const_Iterator after which elements of \p other will be taken
     * @param[in] last Const_Iterator until which elements of \p other will be taken
     * @details Content of other object will be taken by constructed object
     */
    void splice_after(Const_Iterator pos, ForwardList<T>& other, Const_Iterator first, Const_Iterator last);

    /**
     * @brief Function moves elements from other ForwardList object
     *
     * @param[in] pos Const_Iterator after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] first Const_Iterator after which elements of \p other will be taken
     * @param[in] last Const_Iterator until which elements of \p other will be taken
     * @details Content of other object will be taken by constructed object
     */
    void splice_after(Const_Iterator pos, ForwardList<T>&& other, Const_Iterator first, Const_Iterator last);

    /**
     * @brief Function removes all elements equal to \p value
     *
     * @param[in] value value of elements to remove
     */
    void remove(const T& value);

    /// @todo add remove_if

    /**
     * @brief Function reverts in place Nodes of ForwardList
     */
    void reverse();

    /**
     * @brief Function removes duplicated elements
     * @details Only the first occurrence of given element is preserved
     */
    void unique();

    /// @todo add sort

    /**
     * @brief push_back elements of another ForwardList to base container
     *
     * @param[in] other ForwardList to read elements from
     * @return ForwardList<T>&
     */
    template<typename T>
    ForwardList<T>& operator+=(const ForwardList<T>& other)
    {
        for (auto it = other.cbegin(); it != other.cend(); ++it)
        {
            auto value = *it;
            push_back(value);
        }

        return *this;
    }

    /**
     * @brief push_back elements of another ForwardList to base container
     *
     * @param[in] other ForwardList to read elements from
     * @return ForwardList<T>&
     */
    template<typename T>
    ForwardList<T>& operator+=(const std::initializer_list<T> il)
    {
        for (const auto& item : il)
        {
            push_back(item);
        }

        return *this;
    }

    /**
     * @brief Function returns pointer to specific Node of ForwardList
     *
     * @param[in] index index of element
     * @return Node<T>*
     * @retval Node<T>* if index is valid
     * @retval nullptr if invalid index
     */
    Node<T>* get(int index) const
    {
        if (index < 0 || index > m_size)
        {
            return nullptr;
        }

        Node<T>* temp = m_front;
        for (int i = 0; i < index; i++)
        {
            temp = temp->m_next;
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
    bool set(int index, T value)
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
     * @brief Function returns ForwardList size
     *
     * @return size_t number of elements in container
     */
    size_t size() const
    {
        return m_size;
    }

private:

    template<typename T>
    friend ForwardList<T> operator+(const ForwardList<T>& l1, const ForwardList<T>& l2);

    /**
     * @brief Function remove next element
     *
     * @param[in] pos Iterator after which element will be erased
     * @return Iterator* pointer to Iterator to input element
     */
    Iterator* erase_element_after(Iterator pos)
    {
        if (!if_valid_iterator(pos))
        {
            return nullptr;
        }

        Node<T>* temp = pos.m_current_node;
        Node<T>* to_remove = temp->m_next;

        temp->m_next = to_remove->m_next;
        delete to_remove;

        m_size--;
        return &Iterator(temp);
    }

    /**
    * @brief Function inserts new Node after specified ForwardList Iterator
    *
    * @param[in] pos Iterator to insert element after
    * @param[in] value element of type T to be inserted
    * @return pointer to next element
    * @retval Iterator* pointer to Iterator inserted after \pos
    * @retval nullptr if invalid Iterator
    */
    Iterator* insert_element_after(Iterator pos, const T& value)
    {
        if (!if_valid_iterator(pos))
        {
            return nullptr;
        }

        Node<T>* temp = pos.m_current_node;

        Node<T>* newNode = new Node<T>(value);
        newNode->m_next = temp->m_next;

        temp->m_next = newNode;
        m_size++;
        return &Iterator(newNode);
    }

    /**
     * @brief Function checks ForwardList contains Iterator
     *
     * @param[in] pos Iterator to check
     * @return bool \p pos iterator status
     * @return true if \p pos belong to ForwardList
     * @return false if otherwise
     */
    bool if_valid_iterator(Const_Iterator pos)
    {
        bool valid_iterator{};
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
     * @param[in] value element of type T
     */
    void push_back(T value)
    {
        Node<T>* newNode = new Node<T>(value);

        if (!m_front)
        {
            m_front = newNode;
            m_back = newNode;
        }
        else
        {
            m_back->m_next = newNode;
            m_back = newNode;
        }

        m_size++;
    }

    /**
     * @brief Function removes last Node of ForwardList
     */
    void pop_back()
    {
        if (m_size == 0)
        {
            return;
        }

        Node<T>* temp = m_front;
        if (m_size == 1)
        {
            m_front = nullptr;
            m_back = nullptr;
        }
        else
        {
            Node<T>* prev = temp;

            while (temp->m_next)
            {
                prev = temp;
                temp = temp->m_next;
            }
            m_back = prev;
            m_back->m_next = nullptr;
        }

        delete temp;
        m_size--;
    }

    /**
     * @brief Function moves elements from other ForwardList object
     *
     * @param[in] pos Const_Iterator after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] first Const_Iterator after which elements of \p other will be taken
     * @param[in] last Const_Iterator until which elements of \p other will be taken
     * @details Content of other object will be taken by constructed object
     */
    void transfer(Const_Iterator pos, ForwardList<T>& other, Const_Iterator first, Const_Iterator last);

    Node<T>* m_front{};
    Node<T>* m_back{};
    size_t m_size{};
};

template<typename T>
ForwardList<T>::ForwardList()
{
}

template<typename T>
ForwardList<T>::ForwardList(T value)
{
    Node<T>* newNode = new Node<T>(value);
    m_front = newNode;
    m_back = newNode;
    m_size++;
}

template<typename T>
ForwardList<T>::ForwardList(const std::initializer_list<T>& init_list)
{
    for (const auto& item : init_list)
    {
        push_back(item);
    }
}

template<typename T>
ForwardList<T>::ForwardList(const ForwardList<T>& other)
{
    for (int i = 0; i < other.size(); i++)
    {
        push_back(other.get(i)->value());
    }
}

template<typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& other)
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
ForwardList<T>::ForwardList(ForwardList<T>&& other) noexcept
{
    m_front = other.m_front;
    m_back = other.m_back;
    m_size = other.m_size;

    other.m_front = nullptr;
    other.m_back = nullptr;
    other.m_size = 0;
}

template<typename T>
ForwardList<T>& ForwardList<T>::operator=(ForwardList<T>&& other) noexcept
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
ForwardList<T>::~ForwardList()
{
    clear();
}

template<typename T>
void ForwardList<T>::assign(size_t count, const T& value)
{
    clear();

    for (size_t i = 0; i < count; i++)
    {
        push_back(value);
    }
}

template<typename T>
void ForwardList<T>::assign(const std::initializer_list<T>& init_list)
{
    clear();

    for (const auto& item : init_list)
    {
        push_back(item);
    }
}

template<typename T>
T& ForwardList<T>::front()
{
    return *begin();
}

template<typename T>
const T& ForwardList<T>::front() const
{
    return *cbegin();
}

template<typename T>
typename ForwardList<T>::Iterator ForwardList<T>::begin() noexcept
{
    return Iterator(m_front);
}

template<typename T>
typename ForwardList<T>::Const_Iterator ForwardList<T>::begin() const noexcept
{
    return Const_Iterator(m_front);
}

template<typename T>
typename ForwardList<T>::Const_Iterator ForwardList<T>::cbegin() const noexcept
{
    return begin();
}

template<typename T>
typename ForwardList<T>::Iterator ForwardList<T>::end() noexcept
{
    return Iterator(nullptr);
}

template<typename T>
typename ForwardList<T>::Const_Iterator ForwardList<T>::end() const noexcept
{
    return Const_Iterator(nullptr);
}

template<typename T>
typename ForwardList<T>::Const_Iterator ForwardList<T>::cend() const noexcept
{
    return end();
}


template<typename T>
bool ForwardList<T>::empty() const
{
    return m_size == 0;
}

template<typename T>
void ForwardList<T>::clear()
{
    Node<T>* temp = m_front;
    while (m_front)
    {
        m_front = m_front->m_next;
        delete temp;
        temp = m_front;
    }

    m_size = 0;
    m_front = nullptr;
    m_back = nullptr;
}

template<typename T>
typename ForwardList<T>::Iterator* ForwardList<T>::insert_after(Const_Iterator pos, const T& value)
{
    return insert_after(pos, 1, value);
}

template<typename T>
typename ForwardList<T>::Iterator* ForwardList<T>::insert_after(Const_Iterator pos, size_t count, const T& value)
{
    if (!if_valid_iterator(pos))
    {
        return nullptr;
    }

    Iterator copy{ pos.m_current_node };
    Iterator* it{ &copy };
    for (size_t i = 0; i < count; i++)
    {
        it = insert_element_after(*it, value);
    }

    return it;
}

template<typename T>
typename ForwardList<T>::Iterator* ForwardList<T>::insert_after(Const_Iterator pos, std::initializer_list<T> init_list)
{
    if (!if_valid_iterator(pos))
    {
        return nullptr;
    }

    Iterator copy(pos.m_current_node);
    Iterator* it{ &copy };
    for (size_t i = 0; i < init_list.size(); i++)
    {
        it = insert_element_after(*it, init_list.begin()[i]);
    }

    return it;
}

template<typename T>
typename ForwardList<T>::Iterator* ForwardList<T>::erase_after(Const_Iterator pos)
{
    if (!if_valid_iterator(pos))
    {
        return nullptr;
    }

    Iterator copy(pos.m_current_node);
    Iterator* it{ &copy };
    it = erase_element_after(*it);

    return it;
}

template<typename T>
typename ForwardList<T>::Iterator* ForwardList<T>::erase_after(Const_Iterator first, Const_Iterator last)
{
    if (!if_valid_iterator(first) || !if_valid_iterator(last))
    {
        return nullptr;
    }

    Iterator copy(first.m_current_node);
    Iterator* it{ &copy };
    size_t dist = distance(first, last);
    for (size_t i = 0; i < dist - 1; i++)
    {
        it = erase_element_after(*it);
    }

    return it;
}

template<typename T>
void ForwardList<T>::push_front(T value)
{
    Node<T>* newNode = new Node<T>(value);
    if (!m_front)
    {
        m_front = newNode;
        m_back = newNode;
    }
    else
    {
        newNode->m_next = m_front;
        m_front = newNode;
    }

    m_size++;
}

template<typename T>
void ForwardList<T>::pop_front()
{
    if (!m_front)
    {
        return;
    }

    Node<T>* temp = m_front;
    if (m_size == 1)
    {
        m_front = nullptr;
        m_back = nullptr;
    }
    else
    {
        m_front = m_front->m_next;
    }
    delete temp;
    m_size--;
}

template<typename T>
void ForwardList<T>::resize(size_t count)
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
        // additional default-inserted elements are appended
        while (m_size < count)
        {
            push_back(T());
        }
    }
}

template<typename T>
void ForwardList<T>::resize(size_t count, const T& value)
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
void ForwardList<T>::swap(ForwardList<T>& other) noexcept
{
    if (&other != this)
    {
        ForwardList<T> temp;
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
void ForwardList<T>::merge(ForwardList<T>& other)
{
    if (&other != this)
    {
        if (m_size)
        {
            m_back->m_next = other.m_front;
            m_back = other.m_back;
            m_size += other.m_size;

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
void ForwardList<T>::merge(ForwardList<T>&& other)
{
    merge(other);
}

template<typename T>
size_t ForwardList<T>::distance(Const_Iterator first, Const_Iterator last)
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
void ForwardList<T>::transfer(Const_Iterator pos, ForwardList<T>& other, Const_Iterator first, Const_Iterator last)
{
    if (&other != this && other.m_size > 0)
    {
        Node<T>* temp_prev = pos.m_current_node;    // to append to
        Node<T>* temp_next = first.m_current_node;  // does not move

        Node<T>* first_to_move = temp_next->m_next;
        Node<T>* last_to_move = temp_next;
        size_t ctr = 0;
        size_t dist = distance(first, last);
        for (size_t i = 0; i < dist; i++)
        {
            if (last_to_move)
            {
                last_to_move = last_to_move->m_next;
                ctr++;
            }
        }

        temp_next->m_next = last_to_move->m_next;
        last_to_move->m_next = temp_prev->m_next;
        temp_prev->m_next = first_to_move;

        if (!last_to_move->m_next)
        {
            other.m_back = nullptr;
        }
        m_size += ctr;
        other.m_size -= ctr;
    }
}

template<typename T>
void ForwardList<T>::splice_after(Const_Iterator pos, ForwardList<T>& other)
{
    if (&other != this && other.m_size > 0)
    {
        Node<T>* temp = pos.m_current_node;
        other.m_back->m_next = temp->m_next;
        temp->m_next = other.m_front;
        m_size += other.m_size;

        other.m_front = nullptr;
        other.m_back = nullptr;
        other.m_size = 0;
    }
}

template<typename T>
void ForwardList<T>::splice_after(Const_Iterator pos, ForwardList<T>&& other)
{
    splice_after(pos, other);
}

template<typename T>
void ForwardList<T>::splice_after(Const_Iterator pos, ForwardList<T>& other, Const_Iterator it)
{
    transfer(pos, other, it, it.m_current_node->next());
}

template<typename T>
void ForwardList<T>::splice_after(Const_Iterator pos, ForwardList<T>&& other, Const_Iterator it)
{
    transfer(pos, other, it, it.m_current_node->next());
}

template<typename T>
void ForwardList<T>::splice_after(Const_Iterator pos, ForwardList<T>& other, Const_Iterator first, Const_Iterator last)
{
    transfer(pos, other, first, last);
}

template<typename T>
void ForwardList<T>::splice_after(Const_Iterator pos, ForwardList<T>&& other, Const_Iterator first, Const_Iterator last)
{
    transfer(pos, other, first, last);
}

template<typename T>
void ForwardList<T>::remove(const T& value)
{
    Node<T>* temp = m_front;
    Node<T>* next{};
    while (temp)
    {
        next = temp->m_next;

        if (m_front->value() == value)
        {
            pop_front();
            temp = m_front;
            continue;
        }

        if (next && next->value() == value)
        {
            Node<T>* to_remove = temp->m_next;
            temp->m_next = to_remove->m_next;
            delete to_remove;
            m_size--;
            continue;
        }

        temp = temp->m_next;
    }

    if (m_size == 0)
    {
        m_front = nullptr;
        m_back = nullptr;
    }
}

template<typename T>
void ForwardList<T>::reverse()
{
    Node<T>* temp = m_front;
    m_front = m_back;
    m_back = temp;

    Node<T>* prev{};
    Node<T>* next{};

    for (int i = 0; i < m_size; i++)
    {
        next = temp->m_next;
        temp->m_next = prev;

        prev = temp;
        temp = next;
    }
}

template<typename T>
void ForwardList<T>::unique()
{
    Node<T>* temp = m_front;
    Node<T>* prev{};
    Node<T>* next{};
    while (temp)
    {
        prev = temp;

        while (prev)
        {
            next = prev->m_next;

            if (next && next->value() == temp->value())
            {
                Node<T>* to_remove = next;
                prev->m_next = to_remove->m_next;
                delete to_remove;
                m_size--;
                continue;
            }

            if (prev)
            {
                prev = prev->m_next;
            }
        }

        temp = temp->m_next;
    }
}

/**
 * @brief Construct new object based on two ForwardList objects
 *
 * @tparam T type of data stored in ForwardList Node
 * @param[in] l1 input ForwardList
 * @param[in] l2 input ForwardList
 * @return ForwardList<T>
 */
template<typename T>
ForwardList<T> operator+(const ForwardList<T>& l1, const ForwardList<T>& l2)
{
    ForwardList<T> temp(l1);

    for (auto it = l2.cbegin(); it != l2.cend(); ++it)
    {
        T value = *it;
        temp.push_back(value);
    }

    return temp;
}

/**
 * @brief Overloads operator to print all elements of ForwardList
 *
 * @tparam T type of initializer list elements
 * @param[in,out] out reference to output stream
 * @param[in] ll ForwardList to print
 * @return std::ostream&
 */
template<typename T>
std::ostream& operator<<(std::ostream& out, const ForwardList<T>& ll)
{
    for (auto it = ll.cbegin(); it != ll.cend(); ++it)
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
 * @param[in] l1 input container
 * @param[in] l2 input container
 * @retval true if containers are equal
 * @retval false if containers are not equal
 */
template<typename T>
bool operator==(const ForwardList<T>& l1, const ForwardList<T>& l2)
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
 * @brief The relational operator compares two ForwardList objects
 *
 * @tparam T type of data stored in ForwardList
 * @param[in] l1 input container
 * @param[in] l2 input container
 * @retval true if containers are not equal
 * @retval false if containers are equal
 */
template<typename T>
bool operator!=(const ForwardList<T>& l1, const ForwardList<T>& l2)
{
    return !(operator==(l1, l2));
}

/**
 * @brief The relational operator compares two ForwardList objects
 *
 * @tparam T type of data stored in ForwardList
 * @param[in] l1 input container
 * @param[in] l2 input container
 * @retval true if the content of \p l1 are lexicographically
 *         less than the content of \p l2
 * @retval false otherwise
 */
template<typename T>
bool operator<(const ForwardList<T>& l1, const ForwardList<T>& l2)
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
 * @brief The relational operator compares two ForwardList objects
 *
 * @tparam T type of data stored in ForwardList
 * @param[in] l1 input container
 * @param[in] l2 input container
 * @retval true if the content of \p l1 are lexicographically
 *         greater than the content of \p l2
 * @retval false otherwise
 */
template<typename T>
bool operator>(const ForwardList<T>& l1, const ForwardList<T>& l2)
{
    return operator<(l2, l1);
}

/**
 * @brief The relational operator compares two ForwardList objects
 *
 * @tparam T type of data stored in ForwardList
 * @param[in] l1 input container
 * @param[in] l2 input container
 * @retval true if the content of \p l1 are lexicographically
 *         less or equal than the content of \p l2
 * @retval false otherwise
 */
template<typename T>
bool operator<=(const ForwardList<T>& l1, const ForwardList<T>& l2)
{
    return !(operator>(l1, l2));
}

/**
 * @brief The relational operator compares two ForwardList objects
 *
 * @tparam T type of data stored in ForwardList
 * @param[in] l1 input container
 * @param[in] l2 input container
 * @retval true if the content of \p l1 are lexicographically
 *         greater or equal than the content of \p l2
 * @retval false otherwise
 */
template<typename T>
bool operator>=(const ForwardList<T>& l1, const ForwardList<T>& l2)
{
    return !(operator<(l1, l2));
}

/// @todo implement non-member specialized swap function

/// @todo implement non-member specialized erase function

/// @todo implement non-member specialized erase_if function

#endif // !FORWARD_LIST_H
