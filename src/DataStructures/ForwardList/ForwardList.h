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
     * @brief Function returns pointer to ForwardList first Node
     *
     * @return Node<T>* pointer to ForwardList first Node
     */
    Node<T>* head() const
    {
        return m_head;
    }

    /**
     * @brief Function returns pointer to ForwardList last Node
     *
     * @return Node<T>*
     */
    Node<T>* tail() const
    {
        return m_tail;
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

    /**
     * @brief Function prints values stored in each ForwardList node
     */
    void print();

    /**
     * @brief Function adds new element at the end of ForwardList
     *
     * @param[in] value element of type T
     */
    void push_back(T value);

    /**
     * @brief Function adds new Node at the beginning of ForwardList
     *
     * @param[in] value element of type T
     */
    void push_front(T value);


    /**
     * @brief Function inserts new Node at specified index of ForwardList
     *
     * @param[in] index index to insert element at
     * @param[in] value element of type T to be inserted
     * @return operation result
     * @retval true if new Node was inserted at specified index
     * @retval false if invalid index
     */
    bool insert(int index, T value);

    /**
     * @brief Function removes last Node of ForwardList
     */
    void pop_back();

    /**
     * @brief Function removes first Node of ForwardList
     */
    void pop_front();

    /**
     * @brief Function erases Node from specified index of ForwardList
     *
     * @param[in] index index of element to be erased
     * @return operation result
     * @retval true if Node was erased from specified index
     * @retval false if invalid index
     */
    bool erase(int index);

    /**
     * @brief Function returns pointer to specific Node of ForwardList
     *
     * @param[in] index index of element
     * @return Node<T>*
     * @retval Node<T>* if index is valid
     * @retval nullptr if invalid index
     */
    Node<T>* get(int index) const;

    /**
     * @brief Function sets value of specifed Node of ForwardList
     *
     * @param[in] index index of element to be modified
     * @param[in] value to overwrite Node at index
     * @return operation status
     * @retval true if value of Node was overwritten
     * @retval false if invalid index
     */
    bool set(int index, T value);

    /**
     * @brief Function reverts in place Nodes of ForwardList
     */
    void reverse();

    /**
     * @brief push_back elements of another ForwardList to base container
     *
     * @param[in] other ForwardList to read elements from
     * @return ForwardList<T>&
     */
    template<typename T>
    ForwardList<T>& operator+=(const ForwardList<T>& other)
    {
        Node<T>* node = other.head();
        for (size_t i = 0; i < other.size(); i++)
        {
            (*this).push_back(node->value());
            node = node->next();
        }

        return *this;
    }

private:

    Node<T>* m_head{};
    Node<T>* m_tail{};
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
    m_head = newNode;
    m_tail = newNode;
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
        while (m_head)
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
    m_head = other.m_head;
    m_tail = other.m_tail;
    m_size = other.m_size;

    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
}

template<typename T>
ForwardList<T>& ForwardList<T>::operator=(ForwardList<T>&& other) noexcept
{
    if (&other != this)
    {
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;

        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    return *this;
}

template<typename T>
ForwardList<T>::~ForwardList()
{
    Node<T>* temp = m_head;
    while (m_head)
    {
        m_head = m_head->m_next;
        delete temp;
        temp = m_head;
    }
}

template<typename T>
void ForwardList<T>::print()
{
    Node<T>* temp = m_head;
    while (temp)
    {
        std::cout << temp->m_value << ' ';
        temp = temp->m_next;
    }
}

template<typename T>
void ForwardList<T>::push_back(T value)
{
    Node<T>* newNode = new Node<T>(value);

    if (!m_head)
    {
        m_head = newNode;
        m_tail = newNode;
    }
    else
    {
        m_tail->m_next = newNode;
        m_tail = newNode;
    }

    m_size++;
}

template<typename T>
void ForwardList<T>::push_front(T value)
{
    Node<T>* newNode = new Node<T>(value);

    if (!m_head)
    {
        m_head = newNode;
        m_tail = newNode;
    }
    else
    {
        newNode->m_next = m_head;
        m_head = newNode;
    }

    m_size++;
}

template<typename T>
bool ForwardList<T>::insert(int index, T value)
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

template<typename T>
void ForwardList<T>::pop_back()
{
    if (m_size == 0)
    {
        return;
    }

    Node<T>* temp = m_head;
    if (m_size == 1)
    {
        m_head = nullptr;
        m_tail = nullptr;
    }
    else
    {
        Node<T>* prev = temp;

        while (temp->m_next)
        {
            prev = temp;
            temp = temp->m_next;
        }
        m_tail = prev;
        m_tail->m_next = nullptr;
    }

    delete temp;
    m_size--;
}

template<typename T>
bool ForwardList<T>::erase(int index)
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

template<typename T>
void ForwardList<T>::pop_front()
{
    if (!m_head)
    {
        return;
    }

    Node<T>* temp = m_head;
    if (m_size == 1)
    {
        m_head = nullptr;
        m_tail = nullptr;
    }
    else
    {
        m_head = m_head->m_next;
    }
    delete temp;
    m_size--;
}

template<typename T>
ForwardList<T>::Node<T>* ForwardList<T>::get(int index) const
{
    if (index < 0 || index > m_size)
    {
        return nullptr;
    }

    Node<T>* temp = m_head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->m_next;

    }

    return temp;
}

template<typename T>
bool ForwardList<T>::set(int index, T value)
{
    Node<T>* temp = get(index);
    if (temp)
    {
        temp->m_value = value;
        return true;
    }

    return false;
}

template<typename T>
void ForwardList<T>::reverse()
{
    Node<T>* temp = m_head;
    m_head = m_tail;
    m_tail = temp;

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

    ForwardList<T>::Node<T>* node = l2.head();
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
    ForwardList<T>::Node<T>* temp = ll.head();
    while (temp)
    {
        out << temp->value() << ' ';
        temp = temp->next();
    }
    return out;
}

#endif // !FORWARD_LIST_H
