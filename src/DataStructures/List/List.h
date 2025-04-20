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
  * @brief Implementation of Node<T> with pointer to prev and next elements
  * @tparam T type of stored data
  */

  /**
   * @brief Implements Node template class with pointer to adjacent elements
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

    /**
     * @brief Function returns pointer to previous Node object
     *
     * @return Node<T>* pointer to value stored in Node
     */
    Node<T>* prev() const
    {
        return m_prev;
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
    Node<T>* m_next{};
    Node<T>* m_prev{};

};

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
     * @brief Function returns pointer to List first Node
     *
     * @return Node<T>*
     */
    Node<T>* head() const
    {
        return m_head;
    }

    /**
     * @brief Function returns pointer to List last Node
     *
     * @return Node<T>*
     */
    Node<T>* tail() const
    {
        return m_tail;
    }

    /**
     * @brief Function returns List size
     *
     * @return size_t number of elements in container
     */
    size_t size() const
    {
        return m_size;
    }

    /**
     * @brief Function prints values stored in each List node
     */
    void print();

    /**
     * @brief Function adds new Node at the end of List
     *
     * @param[in] value element of type T
     */
    void push_back(T value);

    /**
     * @brief Function adds new Node at the beginning of List
     *
     * @param[in] value element of type T
     */
    void push_front(T value);

    /**
     * @brief Function inserts new Node at specified index of List
     *
     * @param[in] index index to insert element at
     * @param[in] value element of type T to be inserted
     * @return operation result
     * @retval true if new Node was inserted at specified index
     * @retval false if invalid index
     */
    bool insert(int index, T value);

    /**
     * @brief Function removes last Node of List
     */
    void pop_back();

    /**
     * @brief Function removes first Node of List
     */
    void pop_front();

    /**
     * @brief Function erases Node from specified index of List
     *
     * @param[in] index index of element to be erased
     * @return operation result
     * @retval true if Node was erased from specified index
     * @retval false if invalid index
     */
    bool erase(int index);

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

    /**
     * @brief Function reverts in place Nodes of List
     */
    void reverse();

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
List<T>::List()
{
}

template<typename T>
List<T>::List(T value)
{
    Node<T>* newNode = new Node<T>(value);
    m_head = newNode;
    m_tail = newNode;
    m_size++;
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
List<T>::List(List<T>&& other) noexcept
{
    m_head = other.m_head;
    m_tail = other.m_tail;
    m_size = other.m_size;

    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& other) noexcept
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
List<T>::~List()
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
void List<T>::print()
{
    Node<T>* temp = m_head;
    while (temp)
    {
        std::cout << temp->m_value << ' ';
        temp = temp->m_next;
    }
}

template<typename T>
void List<T>::push_back(T value)
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
        newNode->m_prev = m_tail;
        m_tail = newNode;
    }

    m_size++;
}

template<typename T>
void List<T>::push_front(T value)
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
        m_head->m_prev = newNode;
        m_head = newNode;
    }

    m_size++;
}

template<typename T>
bool List<T>::insert(int index, T value)
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
    newNode->m_prev = temp;

    temp->m_next->m_prev = newNode;
    temp->m_next = newNode;

    m_size++;
    return true;
}

template<typename T>
void List<T>::pop_back()
{
    if (m_size == 0)
    {
        return;
    }

    Node<T>* temp = m_tail;
    if (m_size == 1)
    {
        m_head = nullptr;
        m_tail = nullptr;
    }
    else
    {
        m_tail = temp->m_prev;
        m_tail->m_next = nullptr;
    }

    delete temp;
    m_size--;
}

template<typename T>
bool List<T>::erase(int index)
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
    temp->m_next->m_prev = temp;
    delete to_remove;

    m_size--;
    return true;
}

template<typename T>
void List<T>::pop_front()
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
        m_head->m_prev = nullptr;
    }
    delete temp;
    m_size--;
}

template<typename T>
Node<T>* List<T>::get(int index) const
{
    if (index < 0 || index > m_size)
    {
        return nullptr;
    }

    Node<T>* temp{};
    if (index < m_size / 2)
    {
        temp = m_head;
        for (size_t i = 0; i < index; i++)
        {
            temp = temp->m_next;
        }
    }
    else
    {
        temp = m_tail;
        for (size_t i = m_size - 1; i > index; i--)
        {
            temp = temp->m_prev;
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

template<typename T>
void List<T>::reverse()
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
        temp->m_prev = next;

        prev = temp;
        temp = next;
    }
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

    //Node<T>* node = l2.head();
    auto node = l2.head();
    for (size_t i = 0; i < l2.size(); i++)
    {
        temp.push_back(node->value());
        node = node->next();
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
    Node<T>* temp = ll.head();
    while (temp)
    {
        out << temp->value() << ' ';
        temp = temp->next();
    }
    return out;
}

#endif // !LIST_H
