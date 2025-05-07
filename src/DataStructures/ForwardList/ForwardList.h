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
        T value()
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
     * @return Node<T>* pointer to ForwardList first Node
     */
    Node<T>* front();

    /**
     * @brief Function returns const reference value stored in ForwardList first Node
     *
     * @return Node<T>* pointer to ForwardList first Node
     */
    Node<T>* front() const;

    /// @todo add before_begin

    /// @todo add const before_begin

    /**
     * @brief Function returns pointer to ForwardList first Node
     *
     * @return Node<T>* pointer to ForwardList first Node
     */
    Node<T>* begin();

    /**
     * @brief Function returns const pointer to ForwardList first Node
     *
     * @return Node<T>* const pointer to ForwardList first Node
     */
    Node<T>* cbegin() const;

    /**
     * @brief Function returns pointer to ForwardList last Node
     *
     * @return Node<T>* pointer to ForwardList last Node
     */
    Node<T>* end();

    /**
     * @brief Function returns pointer to ForwardList last Node
     *
     * @return Node<T>* const pointer to ForwardList last Node
     */
    Node<T>* cend() const;

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
     * @brief Function inserts new Node after specified index of ForwardList
     *
     * @param[in] index index to insert element after
     * @param[in] value element of type T to be inserted
     * @return pointer to inserted element
     * @retval Node<T>* pointer to next Node inserted after specified index
     * @retval nullptr if invalid index
     */
    Node<T>* insert_after(int index, const T& value);

    /**
     * @brief Function inserts new Node after specified index of ForwardList
     *
     * @param[in] index index to insert element after specified index
     * @param[in] count number of elements to insert after specified index
     * @param[in] value element of type T to be inserted
     * @return pointer to the last inserted element
     * @retval Node<T>* pointer to last Node inserted after specified index
     * @retval nullptr if invalid index
     */
    Node<T>* insert_after(int index, size_t count, const T& value);

    /**
     * @brief Function inserts new Node after specified index of ForwardList
     *
     * @param[in] index index to insert element after
     * @param[in] std::initializer_list to be inserted after specified index
     * @return pointer to the last inserted element
     * @retval Node<T>* pointer to last Node inserted after specified index
     * @retval nullptr if invalid index
     */
    Node<T>* insert_after(int index, std::initializer_list<T> init_list);

    /// @todo add emplace_after

    /**
    * @brief Function erases Node from specified index of ForwardList
    *
    * @param[in] index index of element to be erased
    * @return pointer to element after deleted index
    * @retval Node<T>* pointer to element after deleted index
    * @retval nullptr if invalid index
    */
    Node<T>* erase_after(size_t index);

    /**
     * @brief Function erases Node from specified index of ForwardList
     *
     * @param[in] start_index start index of element to be erased
     * @param[in] end_index end index of element to be erased
     * @return pointer to element after last deleted element
     * @retval Node<T>* pointer to element after deleted index
     * @retval nullptr if invalid index
     */
    Node<T>* erase_after(size_t start_index, size_t end_index);

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
     * @param[in] index index after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @details Content of other object will be taken by constructed object
     */
    void splice_after(int index, ForwardList<T>& other);

    /**
     * @brief Function moves elements from other ForwardList object
     *
     * @param[in] index index after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @details Content of other object will be taken by constructed object
     */
    void splice_after(int index, ForwardList<T>&& other);

    /**
     * @brief Function moves elements from other ForwardList object
     *
     * @param[in] index index after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] it index from which elements of \p other will be taken
     * @details Content of other object will be taken by constructed object
     */
    void splice_after(int index, ForwardList<T>& other, int it);

    /**
     * @brief Function moves elements from other ForwardList object
     *
     * @param[in] index index after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] it index after which elements of \p other will be taken
     * @details Content of other object will be taken by constructed object
     */
    void splice_after(int index, ForwardList<T>&& other, int it);

    /**
     * @brief Function moves elements from other ForwardList object
     *
     * @param[in] index index after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] first index after which elements of \p other will be taken
     * @param[in] last index until which elements of \p other will be taken
     * @details Content of other object will be taken by constructed object
     */
    void splice_after(int index, ForwardList<T>& other, int first, int last);

    /**
     * @brief Function moves elements from other ForwardList object
     *
     * @param[in] index index after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] first index after which elements of \p other will be taken
     * @param[in] last index until which elements of \p other will be taken
     * @details Content of other object will be taken by constructed object
     */
    void splice_after(int index, ForwardList<T>&& other, int first, int last);

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
        Node<T>* node = other.front();
        for (size_t i = 0; i < other.size(); i++)
        {
            push_back(node->value());
            node = node->next();
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
     * @brief Function sets value of specifed Node of ForwardList
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

    Node<T>* erase_element_after(int index)
    {
        if (index < 0 || index >= m_size)
        {
            return nullptr;
        }

        Node<T>* temp = get(index);
        Node<T>* to_remove = temp->m_next;

        temp->m_next = to_remove->m_next;
        delete to_remove;

        m_size--;
        return temp;
    }

    /**
    * @brief Function inserts new Node at specified index of ForwardList
    *
    * @param[in] index index to insert element at
    * @param[in] value element of type T to be inserted
    * @return operation result
    * @retval true if new Node was inserted at specified index
    * @retval false if invalid index
    */
    bool insert(int index, T value)
    {
        if (index < 0 || index > m_size)
        {
            return false;
        }

        if (index == 0)
        {
            push_front(value);
            return true;
        }

        if (index == m_size)
        {
            push_back(value);
            return true;
        }

        Node<T>* temp = get(index - 1);

        Node<T>* newNode = new Node<T>(value);
        newNode->m_next = temp->m_next;

        temp->m_next = newNode;
        m_size++;
        return true;
    }

    /**
    * @brief Function inserts new Node after specified index of ForwardList
    *
    * @param[in] index index to insert element after
    * @param[in] value element of type T to be inserted
    * @return pointer to next element
    * @retval Node<T>* pointer to next Node inserted after specified index
    * @retval nullptr if invalid index
    */
    Node<T>* insert_element_after(int index, const T& value)
    {
        if (index < 0 || index > m_size)
        {
            return nullptr;
        }

        Node<T>* temp = get(index);

        Node<T>* newNode = new Node<T>(value);
        newNode->m_next = temp->m_next;

        temp->m_next = newNode;
        m_size++;
        return newNode;
    }

    /**
     * @brief Function adds new element at the end of ForwardList
     *
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
     * @brief Function erases Node from specified index of ForwardList
     *
     * @param[in] index index of element to be erased
     * @return operation result
     * @retval true if Node was erased from specified index
     * @retval false if invalid index
     */
    bool erase(int index)
    {
        if (index < 0 || index >= m_size)
        {
            return false;
        }

        if (index == 0)
        {
            pop_front();
            return true;
        }

        if (index == m_size - 1)
        {
            pop_back();
            return true;
        }

        Node<T>* temp = get(index - 1);
        Node<T>* to_remove = temp->m_next;

        temp->m_next = to_remove->m_next;
        delete to_remove;

        m_size--;
        return true;
    }

    /**
     * @brief Function moves elements from other ForwardList object
     *
     * @param[in] index index after which content of other container will be inserted
     * @param[in,out] other container to take elements from
     * @param[in] first index after which elements of \p other will be taken
     * @param[in] last index until which elements of \p other will be taken
     * @details Content of other object will be taken by constructed object
     */
    void transfer(int index, ForwardList<T>& other, int first, int last);

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
ForwardList<T>::Node<T>* ForwardList<T>::front()
{
    return m_front;
}

template<typename T>
ForwardList<T>::Node<T>* ForwardList<T>::front() const
{
    return m_front;
}

template<typename T>
ForwardList<T>::Node<T>* ForwardList<T>::begin()
{
    return m_front;
}

template<typename T>
ForwardList<T>::Node<T>* ForwardList<T>::cbegin() const
{
    return m_front;
}

template<typename T>
ForwardList<T>::Node<T>* ForwardList<T>::end()
{
    return m_back;
}

template<typename T>
ForwardList<T>::Node<T>* ForwardList<T>::cend() const
{
    return m_back;
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
ForwardList<T>::Node<T>* ForwardList<T>::insert_after(int index, const T& value)
{
    if (index < 0 || index > m_size)
    {
        return nullptr;
    }

    Node<T>* newNode = insert_element_after(index, value);

    return newNode;
}

template<typename T>
ForwardList<T>::Node<T>* ForwardList<T>::insert_after(int index, size_t count, const T& value)
{
    if (index < 0 || index > m_size)
    {
        return nullptr;
    }

    Node<T>* newNode{};
    for (size_t i = 0; i < count; i++)
    {
        newNode = insert_element_after(index + i, value);
    }

    return newNode;
}

template<typename T>
ForwardList<T>::Node<T>* ForwardList<T>::insert_after(int index, std::initializer_list<T> init_list)
{
    if (index < 0 || index > m_size)
    {
        return false;
    }

    Node<T>* newNode{};
    for (size_t i = 0; i < init_list.size(); i++)
    {
        newNode = insert_element_after(index + i, init_list.begin()[i]);
    }

    return newNode;
}

template<typename T>
ForwardList<T>::Node<T>* ForwardList<T>::erase_after(size_t index)
{
    if (index < 0 || index > m_size)
    {
        return nullptr;
    }

    Node<T>* newNode = erase_element_after(index);

    return newNode;
}

template<typename T>
ForwardList<T>::Node<T>* ForwardList<T>::erase_after(size_t start_index, size_t end_index)
{
    if (start_index < 0 || start_index > m_size ||
        end_index < 0 || end_index > m_size)
    {
        return nullptr;
    }

    Node<T>* newNode{};
    for (size_t i = start_index; i < end_index; i++)
    {
        newNode = erase_element_after(start_index);
    }

    if (newNode)
    {
        return newNode->m_next;
    }
    else
    {
        return newNode;
    }
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
void ForwardList<T>::transfer(int index, ForwardList<T>& other, int first, int last)
{
    if (last <= first)
    {
        return;
    }

    if (&other != this && other.m_size > 0)
    {
        Node<T>* temp_prev = get(index);        // to append to
        Node<T>* temp_next = other.get(first);  // does not move

        //Node<T>* first_to_move = temp_next->m_next;
        Node<T>* first_to_move = temp_next->m_next;
        Node<T>* last_to_move = temp_next;
        int ctr = 0;
        for (int i = 0; i < (last - first); i++)
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

        /// @todo verify with iterators
        if (!last_to_move->m_next)
        {
            other.m_back = nullptr;
        }
        m_size += ctr;
        other.m_size -= ctr;
    }
}

template<typename T>
void ForwardList<T>::splice_after(int index, ForwardList<T>& other)
{
    if (&other != this && other.m_size > 0)
    {
        Node<T>* temp = get(index);
        other.m_back->m_next = temp->m_next;
        temp->m_next = other.m_front;
        m_size += other.m_size;

        other.m_front = nullptr;
        other.m_back = nullptr;
        other.m_size = 0;
    }
}

template<typename T>
void ForwardList<T>::splice_after(int index, ForwardList<T>&& other)
{
    splice_after(index, other);
}

template<typename T>
void ForwardList<T>::splice_after(int index, ForwardList<T>& other, int it)
{
    transfer(index, other, it, it + 1);
}

template<typename T>
void ForwardList<T>::splice_after(int index, ForwardList<T>&& other, int it)
{
    transfer(index, other, it, it + 1);
}

template<typename T>
void ForwardList<T>::splice_after(int index, ForwardList<T>& other, int first, int last)
{
    transfer(index, other, first, last);
}

template<typename T>
void ForwardList<T>::splice_after(int index, ForwardList<T>&& other, int first, int last)
{
    transfer(index, other, first, last);
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

    ForwardList<T>::Node<T>* node = l2.front();
    for (size_t i = 0; i < l2.size(); i++)
    {
        temp.push_back(node->value());
        node = node->next();
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
    ForwardList<T>::Node<T>* temp = ll.front();
    while (temp)
    {
        out << temp->value() << ' ';
        temp = temp->next();
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

    ForwardList<T>::Node<T>* node_1 = l1.front();
    ForwardList<T>::Node<T>* node_2 = l2.front();

    while (node_1 && node_2)
    {
        if (node_1->value() != node_2->value())
        {
            return false;
        }

        node_1 = node_1->next();
        node_2 = node_2->next();
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
    ForwardList<T>::Node<T>* node_1 = l1.front();
    ForwardList<T>::Node<T>* node_2 = l2.front();

    while (node_1 && node_2)
    {
        if (node_1->value() >= node_2->value())
        {
            return false;
        }

        node_1 = node_1->next();
        node_2 = node_2->next();
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
