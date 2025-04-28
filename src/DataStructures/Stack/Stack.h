/**
 * @file Stack.h
 * @brief This file contains implementation of Stack class
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#ifndef STACK_H
#define STACK_H

#include <initializer_list>
#include <iostream>

 /**
  * @brief Implements Stack class using Node with pointer to next element
  *
  * @tparam T type of data stored in Stack Node
  */
template<typename T>
class Stack
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
         * @return Node<T>* pointer to Node
         */
        Node<T>* next() const
        {
            return m_next;
        }

        /**
         * @brief Function returns pointer to previous Node object
         *
         * @return Node<T>* pointer to Node
         */
        Node<T>* prev() const
        {
            return m_prev;
        }

    private:

        /**
         * @brief Forward friend declaration of Stack
         *
         * @tparam T type of data stored in Node objects
         */
        template<typename T>
        friend class Stack;

        T m_value{};
        Node<T>* m_next{};
        Node<T>* m_prev{};
    };

    /**
     * @brief Construct a new Stack object
     *
     */
    Stack();

    /**
     * @brief Construct a new Stack object using value of type T
     *
     * @param[in] value of type T
     */
    Stack(T value);

    /**
     * @brief Construct a new Stack object using initializer list
     *
     * @param[in] il initializer list of values of type T
     */
    Stack(const std::initializer_list<T>& il);

    /**
     * @brief Construct a new Stack object using copy constructor
     *
     * @param[in] other Stack object of type T
     */
    Stack(const Stack<T>& other);

    /**
     * @brief Constructs Stack using copy assignment
     *
     * @param[in] other Stack object of type T
     * @return Stack& reference to Stack object
     */
    Stack& operator=(const Stack<T>& other);

    /**
     * @brief Construct a new Stack object using move constructor
     * @details Content of other object will be taken by constructed object
     *
     * @param[in,out] other Stack object of type T
     */
    Stack(Stack<T>&& other) noexcept;

    /**
     * @brief Assign Stack object using move assignment
     * @details Content of other object will be taken by constructed object
     *
     * @param[in,out] other Stack object of type T
     * @return Stack& reference to Stack object
     */
    Stack& operator=(Stack<T>&& other) noexcept;

    /**
     * @brief Destroy the Stack object
     */
    ~Stack();

    /**
     * @brief Function returns pointer to Stack top Node
     *
     * @return Node<T>* pointer to Stack top Node
     */
    Node<T>* top();

    /**
     * @brief Function returns pointer to Stack top Node
     *
     * @return Node<T>* pointer to Stack top Node
     */
    Node<T>* top() const;

    /**
     * @brief Function checks if container has no elements
     *
     * @retval true if container is empty
     * @retval false if container is not empty
     */
    bool empty() const;

    /**
     * @brief Function returns Stack size
     *
     * @return size_t number of elements in container
     */
    size_t size() const;

    /**
     * @brief Function add new element at the top of Stack
     *
     * @param[in] value element of type T
     */
    void push(T value);

    /**
     * @brief Function add range of elements at the top of Stack
     *
     * @param[in] il range of std::initializer_list elements of type T
     */
    void push_range(const std::initializer_list<T>& il);

    /**
     * @brief Function removes the top element of Stack
     */
    void pop();

    /**
     * @brief Function swaps content of two Stack objects
     *
     * @param[in,out] other object to swap content with
     */
    void swap(Stack<T>& other) noexcept;

    /**
     * @brief Function add range of elements at the top of Stack
     *
     * @param[in] other Stack to read elements from
     * @return Stack<T>& reference to Stack
     */
    Stack<T>& operator+=(const Stack<T>& other);

    /**
    * @brief Function add range of elements at the top of Stack
    *
    * @param[in] other std::initializer_list to read elements from
    * @return Stack<T>& reference to Stack
    */
    Stack<T>& operator+=(const std::initializer_list<T>& other);

    /**
     * @brief Construct new object based on two Stack objects
     *
     * @tparam T type of data stored in Stack Node
     * @param[in] s1 input Stack
     * @param[in] s2 input Stack
     * @return Stack<T>
     */
    friend Stack<T> operator+(const Stack<T>& s1, const Stack<T>& s2)
    {
        Stack<T> temp(s1);

        Stack<T>::Node<T>* node = s2.bottom();
        while (node)
        {
            temp.push(node->value());
            node = node->prev();
        }

        return temp;
    }

private:

    /**
     * @brief Function returns pointer to Stack bottom Node
     *
     * @return Node<T>* pointer to Stack bottom Node
     */
    Node<T>* bottom()
    {
        return m_bottom;
    }

    /**
     * @brief Function returns pointer to Stack bottom Node
     *
     * @return Node<T>* pointer to Stack bottom Node
     */
    Node<T>* bottom() const
    {
        return m_bottom;
    }

    Node<T>* m_top{};
    Node<T>* m_bottom{};
    size_t m_size{};
};

template<typename T>
Stack<T>::Stack()
{
}

template<typename T>
Stack<T>::Stack(T value)
{
    Node<T>* newNode = new Node<T>(value);
    m_top = newNode;
    m_bottom = newNode;
    m_size++;
}

template<typename T>
Stack<T>::Stack(const std::initializer_list<T>& il)
{
    for (const auto& item : il)
    {
        push(item);
    }
}

template<typename T>
Stack<T>::Stack(const Stack<T>& other)
{
    Stack<T>::Node<T>* temp = other.m_bottom;
    while (temp)
    {
        push(temp->value());
        temp = temp->m_prev;
    }
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    if (&other != this)
    {
        while (m_top)
        {
            pop();
        }

        Stack<T>::Node<T>* temp = other.m_bottom;
        while (temp)
        {
            push(temp->value());
            temp = temp->prev();
        }
    }

    return *this;
}

template<typename T>
Stack<T>::Stack(Stack<T>&& other) noexcept
{
    m_top = other.m_top;
    m_bottom = other.m_bottom;
    m_size = other.m_size;

    other.m_top = nullptr;
    other.m_bottom = nullptr;
    other.m_size = 0;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept
{
    if (&other != this)
    {
        m_top = other.m_top;
        m_bottom = other.m_bottom;
        m_size = other.m_size;

        other.m_top = nullptr;
        other.m_bottom = nullptr;
        other.m_size = 0;
    }

    return *this;
}

template<typename T>
Stack<T>::~Stack()
{
    Node<T>* temp = m_top;
    while (m_top)
    {
        m_top = m_top->m_next;
        delete temp;
        temp = m_top;

        m_size--;
    }
}

template<typename T>
Stack<T>::Node<T>* Stack<T>::top()
{
    return m_top;
}

template<typename T>
Stack<T>::Node<T>* Stack<T>::top() const
{
    return m_top;
}

template<typename T>
bool Stack<T>::empty() const
{
    return m_size == 0;
}

template<typename T>
size_t Stack<T>::size() const
{
    return m_size;
}

template<typename T>
void Stack<T>::push(T value)
{
    Node<T>* newNode = new Node<T>(value);

    if (!m_top)
    {
        m_top = newNode;
        m_bottom = newNode;
    }
    else
    {
        newNode->m_next = m_top;
        m_top->m_prev = newNode;
        m_top = newNode;
    }

    m_size++;
}

template<typename T>
void Stack<T>::push_range(const std::initializer_list<T>& il)
{
    for (const auto& item : il)
    {
        push(item);
    }
}

template<typename T>
void Stack<T>::pop()
{
    Node<T>* temp = m_top;

    if (m_top)
    {
        m_top = m_top->m_next;
        if (m_top)
        {
            m_top->m_prev = nullptr;
        }
        delete temp;
        m_size--;
    }

    if (!m_size)
    {
        m_bottom = nullptr;
    }
}

template<typename T>
void Stack<T>::swap(Stack<T>& other) noexcept
{
    if (&other != this)
    {
        /// @todo implement method as swap function

        Stack<T> temp;
        temp.m_top = m_top;
        temp.m_bottom = m_bottom;
        temp.m_size = m_size;

        m_top = other.m_top;
        m_bottom = other.m_bottom;
        m_size = other.m_size;

        other.m_top = temp.m_top;
        other.m_bottom = temp.m_bottom;
        other.m_size = temp.m_size;

        temp.m_top = nullptr;
        temp.m_bottom = nullptr;
        temp.m_size = 0;
    }
}

template<typename T>
Stack<T>& Stack<T>::operator+=(const Stack<T>& other)
{
    Node<T>* node = other.bottom();
    while (node)
    {
        (*this).push(node->value());
        node = node->prev();
    }

    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator+=(const std::initializer_list<T>& il)
{
    push_range(il);

    return *this;
}

/**
 * @brief Overloads operator to print all elements of Stack
 *
 * @tparam T type of initializer list elements
 * @param[in,out] out reference to output stream
 * @param[in] stack Stack to print
 * @return std::ostream& reference to std::ostream
 */
template<typename T>
std::ostream& operator<<(std::ostream& out, const Stack<T>& stack)
{
    Stack<T>::Node<T>* temp = stack.top();
    while (temp)
    {
        out << temp->value() << ' ';
        temp = temp->next();
    }

    return out;
}

/**
 * @brief The relational operator compares two Stack objects
 *
 * @tparam T type of data stored in Stack
 * @param[in] s1 input container
 * @param[in] s2 input container
 * @retval true if containers are equal
 * @retval false if containers are not equal
 */
template<typename T>
bool operator==(const Stack<T>& s1, const Stack<T>& s2)
{
    if (s1.size() != s2.size())
    {
        return false;
    }

    Stack<T>::Node<T>* node_1 = s1.top();
    Stack<T>::Node<T>* node_2 = s2.top();

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
 * @brief The relational operator compares two Stack objects
 *
 * @tparam T type of data stored in Stack
 * @param[in] s1 input container
 * @param[in] s2 input container
 * @retval true if containers are not equal
 * @retval false if containers are equal
 */
template<typename T>
bool operator!=(const Stack<T>& s1, const Stack<T>& s2)
{
    return !(operator==(s1, s2));
}

/**
 * @brief The relational operator compares two Stack objects
 *
 * @tparam T type of data stored in Stack
 * @param[in] s1 input container
 * @param[in] s2 input container
 * @retval true if the content of \p s1 are lexicographically
 *         less than the content of \p s2
 * @retval false otherwise
 */
template<typename T>
bool operator<(const Stack<T>& s1, const Stack<T>& s2)
{
    Stack<T>::Node<T>* node_1 = s1.top();
    Stack<T>::Node<T>* node_2 = s2.top();

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
 * @brief The relational operator compares two Stack objects
 *
 * @tparam T type of data stored in Stack
 * @param[in] s1 input container
 * @param[in] s2 input container
 * @retval true if the content of \p s1 are lexicographically
 *         greater than the content of \p s2
 * @retval false otherwise
 */
template<typename T>
bool operator>(const Stack<T>& s1, const Stack<T>& s2)
{
    return operator<(s2, s1);
}

/**
 * @brief The relational operator compares two Stack objects
 *
 * @tparam T type of data stored in Stack
 * @param[in] s1 input container
 * @param[in] s2 input container
 * @retval true if the content of \p s1 are lexicographically
 *         less or equal than the content of \p s2
 * @retval false otherwise
 */
template<typename T>
bool operator<=(const Stack<T>& s1, const Stack<T>& s2)
{
    return !(operator>(s1, s2));
}

/**
 * @brief The relational operator compares two Stack objects
 *
 * @tparam T type of data stored in Stack
 * @param[in] s1 input container
 * @param[in] s2 input container
 * @retval true if the content of \p s1 are lexicographically
 *         greater or equal than the content of \p s2
 * @retval false otherwise
 */
template<typename T>
bool operator>=(const Stack<T>& s1, const Stack<T>& s2)
{
    return !(operator<(s1, s2));
}

#endif // !STACK_H
