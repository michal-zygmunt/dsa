/**
 * @file Queue.h
 * @brief This file contains implementation of Queue class
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <initializer_list>
#include <iostream>

 /**
  * @brief Implements Queue class using Node with pointer to next element
  *
  * @tparam T type of data stored in Queue Node
  */
template<typename T>
class Queue
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
            return m_next;
        }

    private:

        /**
         * @brief Forward friend declaration of Queue
         *
         * @tparam T type of data stored in Node objects
         */
        template<typename T>
        friend class Queue;

        T m_value{};
        Node<T>* m_next{};
    };

    /**
     * @brief Construct a new Queue object
     *
     */
    Queue();

    /**
     * @brief Construct a new Queue object using value of type T
     *
     * @param[in] value of type T
     */
    Queue(T value);

    /**
     * @brief Construct a new Queue object using initializer list
     *
     * @param[in] il initializer list of values of type T
     */
    Queue(const std::initializer_list<T>& il);

    /**
     * @brief Construct a new Queue object using copy constructor
     *
     * @param[in] other Queue object of type T
     */
    Queue(const Queue<T>& other);

    /**
     * @brief Constructs Queue using copy assignment
     *
     * @param[in] other Queue object of type T
     * @return Queue& reference to Queue object
     */
    Queue& operator=(const Queue<T>& other);

    /**
     * @brief Construct a new Queue object using move constructor
     * @details Content of other object will be taken by constructed object
     *
     * @param[in,out] other Queue object of type T
     */
    Queue(Queue<T>&& other) noexcept;

    /**
     * @brief Assign Queue object using move assignment
     * @details Content of other object will be taken by constructed object
     *
     * @param[in,out] other Queue object of type T
     * @return Queue& reference to Queue object
     */
    Queue& operator=(Queue<T>&& other) noexcept;

    /**
     * @brief Destroy the Queue object
     */
    ~Queue();

    /**
     * @brief Function returns pointer to Queue first Node
     *
     * @return Node<T>* pointer to Queue first Node
     */
    Node<T>* front();

    /**
     * @brief Function returns pointer to Queue first Node
     *
     * @return Node<T>* pointer to Queue first Node
     */
    Node<T>* front() const;

    /**
     * @brief Function returns pointer to Queue last Node
     *
     * @return Node<T>* pointer to Queue last Node
     */
    Node<T>* back();

    /**
     * @brief Function returns pointer to Queue last Node
     *
     * @return Node<T>* pointer to Queue last Node
     */
    Node<T>* back() const;

    /**
     * @brief Function checks if container has no elements
     *
     * @retval true if container is empty
     * @retval false if container is not empty
     */
    bool empty() const;

    /**
     * @brief Function returns Queue size
     *
     * @return size_t number of elements in container
     */
    size_t size() const;

    /**
     * @brief Function add new element at the end of Queue
     *
     * @param[in] value element of type T
     */
    void push(T value);

    /**
     * @brief Function add range of elements at the end of Queue
     *
     * @param[in] il range of std::initializer_list elements of type T
     */
    void push_range(const std::initializer_list<T>& il);

    /**
     * @brief Function removes the first element of Queue
     */
    void pop();

    /**
     * @brief Function swaps content of two Queue objects
     *
     * @param[in,out] other object to swap content with
     */
    void swap(Queue<T>& other) noexcept;

    /**
     * @brief Function add range of elements at the end of Queue
     *
     * @param[in] other Queue to read elements from
     * @return Queue<T>& reference to Queue
     */
    Queue<T>& operator+=(const Queue<T>& other);

    /**
    * @brief Function add range of elements at the end of Queue
    *
    * @param[in] other std::initializer_list to read elements from
    * @return Queue<T>& reference to Queue
    */
    Queue<T>& operator+=(const std::initializer_list<T>& other);

private:
    Node<T>* m_front{};
    Node<T>* m_back{};
    size_t m_size{};
};

template<typename T>
Queue<T>::Queue()
{
}

template<typename T>
Queue<T>::Queue(T value)
{
    Node<T>* newNode = new Node<T>(value);
    m_front = newNode;
    m_back = newNode;
    m_size++;
}

template<typename T>
Queue<T>::Queue(const std::initializer_list<T>& il)
{
    for (const auto& item : il)
    {
        push(item);
    }
}

template<typename T>
Queue<T>::Queue(const Queue<T>& other)
{
    Queue<T>::Node<T>* temp = other.m_front;
    while (temp)
    {
        push(temp->value());
        temp = temp->m_next;
    }
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    if (&other != this)
    {
        while (m_front)
        {
            pop();
        }

        Queue<T>::Node<T>* temp = other.m_front;
        while (temp)
        {
            push(temp->value());
            temp = temp->next();
        }
    }

    return *this;
}

template<typename T>
Queue<T>::Queue(Queue<T>&& other) noexcept
{
    m_front = other.m_front;
    m_back = other.m_back;
    m_size = other.m_size;

    other.m_front = nullptr;
    other.m_back = nullptr;
    other.m_size = 0;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept
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
Queue<T>::~Queue()
{
    Node<T>* temp = m_front;
    while (m_front)
    {
        m_front = m_front->m_next;
        delete temp;
        temp = m_front;

        m_size--;
    }
}

template<typename T>
Queue<T>::Node<T>* Queue<T>::front()
{
    return m_front;
}

template<typename T>
Queue<T>::Node<T>* Queue<T>::front() const
{
    return m_front;
}

template<typename T>
Queue<T>::Node<T>* Queue<T>::back()
{
    return m_back;
}

template<typename T>
Queue<T>::Node<T>* Queue<T>::back() const
{
    return m_back;
}

template<typename T>
bool Queue<T>::empty() const
{
    return m_size == 0;
}

template<typename T>
size_t Queue<T>::size() const
{
    return m_size;
}

template<typename T>
void Queue<T>::push(T value)
{
    Node<T>* newNode = new Node<T>(value);

    if (!m_back)
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

template<typename T>
void Queue<T>::push_range(const std::initializer_list<T>& il)
{
    for (const auto& item : il)
    {
        push(item);
    }
}

template<typename T>
void Queue<T>::pop()
{
    Node<T>* temp = m_front;

    if (m_front)
    {
        m_front = m_front->m_next;
        delete temp;
        m_size--;
    }

    if (!m_size)
    {
        m_back = nullptr;
    }
}

template<typename T>
void Queue<T>::swap(Queue<T>& other) noexcept
{
    if (&other != this)
    {
        /// @todo implement method as swap function

        Queue<T> temp;
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

/**
 * @brief Construct new object based on two Queue objects
 *
 * @tparam T type of data stored in Queue Node
 * @param[in] q1 input Queue
 * @param[in] q2 input Queue
 * @return Queue<T>
 */
template<typename T>
Queue<T> operator+(const Queue<T>& q1, const Queue<T>& q2)
{
    Queue<T> temp(q1);

    Queue<T>::Node<T>* node = q2.front();
    while (node)
    {
        temp.push(node->value());
        node = node->next();
    }

    return temp;
}

template<typename T>
Queue<T>& Queue<T>::operator+=(const Queue<T>& other)
{
    Node<T>* node = other.front();
    while (node)
    {
        (*this).push(node->value());
        node = node->next();
    }

    return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator+=(const std::initializer_list<T>& il)
{
    push_range(il);

    return *this;
}

/**
 * @brief Overloads operator to print all elements of Queue
 *
 * @tparam T type of initializer list elements
 * @param[in,out] out reference to output stream
 * @param[in] queue Queue to print
 * @return std::ostream& reference to std::ostream
 */
template<typename T>
std::ostream& operator<<(std::ostream& out, const Queue<T>& queue)
{
    Queue<T>::Node<T>* temp = queue.front();
    while (temp)
    {
        out << temp->value() << ' ';
        temp = temp->next();
    }

    return out;
}

/**
 * @brief The relational operator compares two Queue objects
 *
 * @tparam T type of data stored in Queue
 * @param[in] q1 input container
 * @param[in] q2 input container
 * @retval true if containers are equal
 * @retval false if containers are not equal
 */
template<typename T>
bool operator==(const Queue<T>& q1, const Queue<T>& q2)
{
    if (q1.size() != q2.size())
    {
        return false;
    }

    Queue<T>::Node<T>* node_1 = q1.front();
    Queue<T>::Node<T>* node_2 = q2.front();

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
 * @brief The relational operator compares two Queue objects
 *
 * @tparam T type of data stored in Queue
 * @param[in] q1 input container
 * @param[in] q2 input container
 * @retval true if containers are not equal
 * @retval false if containers are equal
 */
template<typename T>
bool operator!=(const Queue<T>& q1, const Queue<T>& q2)
{
    return !(operator==(q1, q2));
}

/**
 * @brief The relational operator compares two Queue objects
 *
 * @tparam T type of data stored in Queue
 * @param[in] q1 input container
 * @param[in] q2 input container
 * @retval true if the content of \p q1 are lexicographically
 *         less than the content of \p q2
 * @retval false otherwise
 */
template<typename T>
bool operator<(const Queue<T>& q1, const Queue<T>& q2)
{
    Queue<T>::Node<T>* node_1 = q1.front();
    Queue<T>::Node<T>* node_2 = q2.front();

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
 * @brief The relational operator compares two Queue objects
 *
 * @tparam T type of data stored in Queue
 * @param[in] q1 input container
 * @param[in] q2 input container
 * @retval true if the content of \p q1 are lexicographically
 *         greater than the content of \p q2
 * @retval false otherwise
 */
template<typename T>
bool operator>(const Queue<T>& q1, const Queue<T>& q2)
{
    return operator<(q2, q1);
}

/**
 * @brief The relational operator compares two Queue objects
 *
 * @tparam T type of data stored in Queue
 * @param[in] q1 input container
 * @param[in] q2 input container
 * @retval true if the content of \p q1 are lexicographically
 *         less or equal than the content of \p q2
 * @retval false otherwise
 */
template<typename T>
bool operator<=(const Queue<T>& q1, const Queue<T>& q2)
{
    return !(operator>(q1, q2));
}

/**
 * @brief The relational operator compares two Queue objects
 *
 * @tparam T type of data stored in Queue
 * @param[in] q1 input container
 * @param[in] q2 input container
 * @retval true if the content of \p q1 are lexicographically
 *         greater or equal than the content of \p q2
 * @retval false otherwise
 */
template<typename T>
bool operator>=(const Queue<T>& q1, const Queue<T>& q2)
{
    return !(operator<(q1, q2));
}

#endif // !QUEUE_H
