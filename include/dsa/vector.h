/**
 * @file vector.h
 * @brief This file contains implementation of Vector class
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>

namespace dsa
{

    /**
     * @brief Implements Vector class template for dynamic size container
     *
     * @tparam T type of data stored in container
     *
     * @note This template intentionally does not implement a bit-packed
     *       specialization for `bool`, as found in `std::vector<bool>`.
     *       The standard container's specialization breaks reference semantics
     *       and replaces `bool&` with proxy objects.
     *       `dsa::Vector<bool>` behaves like a regular container,
     *       without bit-packing. This design choice prioritizes correctness
     *       and predictable semantics over memory optimization.
     *
     * @todo add non-member specialized erase function
     * @todo add non-member specialized erase_if function
     */
    template<typename T>
    class Vector
    {
    public:

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
         * @brief Alias for pointer difference type
         *
         * Used by STL to define distance between two pointers
         */
        using difference_type = std::ptrdiff_t;

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
         * @brief Alias for iterator to data type used in class
         */
        using iterator = T*;

        /**
         * @brief Alias for const iterator to data type used in class
         */
        using const_iterator = const T*;

        /**
         * @brief Alias for reverse_iterator to data type used in class
         */
        using reverse_iterator = std::reverse_iterator<iterator>;

        /**
         * @brief Alias for const reverse_iterator to data type used in class
         */
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        /**
         * @brief Construct a new Vector object
         */
        constexpr Vector();

        /**
         * @brief Construct a new Vector object of size \p count,
         *        using default value of type T
         *
         * @param[in] count element count
         */
        constexpr Vector(size_type count);

        /**
         * @brief Construct a new Vector object of size \p count,
         * using provided \p value of type T
         *
         * @param[in] count element count
         * @param[in] value value for all elements
         */
        constexpr Vector(size_type count, const T& value);

        /**
         * @brief Construct a new Vector object using elements from range [ \p first , \p last )
         *
         * @tparam InputIt
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         */
        template<typename InputIt>
            requires std::input_iterator<InputIt>
        constexpr Vector(InputIt first, InputIt last);

        /**
         * @brief Construct a new Vector object using copy constructor
         *
         * @param[in] other Vector object of type T
         */
        constexpr Vector(const Vector<T>& other);

        /**
         * @brief Construct a new Vector object using move constructor
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other Vector object of type T
         */
        constexpr Vector(Vector<T>&& other) noexcept;

        /**
         * @brief Construct a new Vector object using initializer list
         *
         * @param[in] init_list initializer list of values of type T
         */
        constexpr Vector(std::initializer_list<T> init_list);

        /**
         * @brief Destroy the Vector object
         */
        ~Vector();

        /**
         * @brief Assign Vector object using copy assignment
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other Vector object of type T
         * @return Vector& reference to constructed Vector of type T
         */
        constexpr auto operator=(const Vector<T>& other) -> Vector<T>&;

        /**
         * @brief Assign Vector object using move assignment
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other Vector object of type T
         * @return Vector& reference to constructed Vector of type T
         */
        constexpr auto operator=(Vector<T>&& other) noexcept -> Vector<T>&;

        /**
         * @brief Assign Vector object from \p init_list elements
         *
         * @param[in] init_list values to replace Vector with
         * @return Vector& reference to constructed Vector of type T
         */
        constexpr auto operator=(std::initializer_list<T> init_list) -> Vector<T>&;

        /**
         * @brief Function assign \p count , elements of \p value to Vector object
         *
         * @param[in] count new size of the container
         * @param[in] value value to initialize elements of the container with
         */
        constexpr void assign(size_type count, const T& value);

        /**
         * @brief Function assign elements from range [ \p first , \p last ) to Vector object
         *
         * @tparam InputIt
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         */
        template<typename InputIt>
            requires std::input_iterator<InputIt>
        // do not use `last` as const reference to keep arguments the same as in std
        // NOLINTNEXTLINE(performance-unnecessary-value-param)
        constexpr void assign(InputIt first, InputIt last);

        /**
         * @brief Function assign values of \p init_list to Vector object
         *
         * @param[in] init_list initializer list of values of type T
         */
        constexpr void assign(std::initializer_list<T> init_list);

        /**
         * @brief Get the allocator object
         *
         * @return allocator_type type of memory allocator
         */
        [[nodiscard]] constexpr auto get_allocator() const -> allocator_type;

        /**
         * @brief Returns a reference to Vector element at \p pos index.
         *        If \p pos is outside of container range, an exception std::out_of_range is thrown.
         *
         * @param[in] pos index of element to return
         * @return reference to Vector element at \p pos index
         */
        [[nodiscard]] constexpr auto at(size_type pos) -> reference;

        /**
         * @brief Returns a const_reference to Vector element at \p pos index.
         *        If \p pos is outside of container range, an exception std::out_of_range is thrown.
         *
         * @param[in] pos index of element to return
         * @return const_reference to Vector element at \p pos index
         */
        [[nodiscard]] constexpr auto at(size_type pos) const -> const_reference;

        /**
         * @brief Returns a reference to Vector element at \p pos index.
         *        If \p pos is outside of container range, undefined behaviour occurs.
         *
         * @param[in] pos index of element to return
         * @return reference to Vector element
         */
        [[nodiscard]] constexpr auto operator[](size_type pos)->reference;

        /**
         * @brief Returns a const_reference to Vector element at \p pos index.
         *        If \p pos is outside of container range, undefined behaviour occurs.
         *
         * @param[in] pos index of element to return
         * @return const_reference to Vector element
         */
        [[nodiscard]] constexpr auto operator[](size_type pos) const->const_reference;

        /**
         * @brief Returns reference to first Arary element
         *
         * @return reference to first element
         */
        [[nodiscard]] constexpr auto front() -> reference;

        /**
         * @brief Returns const_reference to first Arary element
         *
         * @return const_reference to first element
         */
        [[nodiscard]] constexpr auto front() const -> const_reference;

        /**
         * @brief Returns reference to last Arary element
         *
         * @return reference to last element
         */
        [[nodiscard]] constexpr auto back() -> reference;

        /**
         * @brief Returns const_reference to last Arary element
         *
         * @return const_reference to last element
         */
        [[nodiscard]] constexpr auto back() const -> const_reference;

        /**
         * @brief Returns pointer to underlying data container
         *
         * @return pointer to underlaying data container
         */
        [[nodiscard]] constexpr auto data() noexcept -> pointer;

        /**
         * @brief Returns const_pointer to underlying data container
         *
         * @return const_pointer to underlaying data container
         */
        [[nodiscard]] constexpr auto data() const noexcept -> const_pointer;

        /**
         * @brief Returns iterator to first element
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return iterator to first element
         */
        [[nodiscard]] constexpr auto begin() noexcept -> iterator;

        /**
         * @brief Returns const_iterator to first element
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return const_iterator to first element
         */
        [[nodiscard]] constexpr auto begin() const noexcept -> const_iterator;

        /**
         * @brief Returns const_iterator to first element
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return const_iterator to first element
         */
        [[nodiscard]] constexpr auto cbegin() const noexcept -> const_iterator;

        /**
         * @brief Returns iterator past last element of underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return iterator past last element
         */
        [[nodiscard]] constexpr auto end() noexcept -> iterator;

        /**
         * @brief Returns const_iterator past last element of underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return const_iterator past last element
         */
        [[nodiscard]] constexpr auto end() const noexcept -> const_iterator;

        /**
         * @brief Returns const_iterator past last element of underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return const_iterator past last element
         */
        [[nodiscard]] constexpr auto cend() const noexcept -> const_iterator;

        /**
         * @brief Returns reverse_iterator to the first element of reversed underlaying data structure
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return reverse_iterator to the first element
         */
        [[nodiscard]] constexpr auto rbegin() -> reverse_iterator;

        /**
         * @brief Returns const_reverse_iterator to the first element of reversed underlaying data structure
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return const_reverse_iterator to the first element
         */
        [[nodiscard]] constexpr auto rbegin() const -> const_reverse_iterator;

        /**
         * @brief Returns const_reverse_iterator to the first element of reversed underlaying data structure
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return const_reverse_iterator to the first element
         */
        [[nodiscard]] constexpr auto crbegin() const noexcept -> const_reverse_iterator;

        /**
         * @brief Returns reverse_iterator past the last element of reversed underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return reverse_iterator to the element after the last element
         */
        [[nodiscard]] constexpr auto rend() -> reverse_iterator;

        /**
         * @brief Returns const_reverse_iterator past the last element of reversed underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return const_reverse_iterator to the element after the last element
         */
        [[nodiscard]] constexpr auto rend() const -> const_reverse_iterator;

        /**
         * @brief Returns const_reverse_iterator past the last element of reversed underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return const_reverse_iterator to the element after the last element
         */
        [[nodiscard]] constexpr auto crend() const noexcept -> const_reverse_iterator;

        /**
         * @brief Checks if container has elements
         *
         * @return true if container is empty
         * @return false if container is not empty
         */
        [[nodiscard]] constexpr auto empty() const -> bool;

        /**
         * @brief Returns number of elements in container
         *
         * @return size_type number of elements in container
         */
        [[nodiscard]] constexpr auto size() const noexcept -> size_type;

        /**
         * @brief Returns maximum number of elements container can hold
         *
         * @return size_type maximum number of elements
         */
        [[nodiscard]] constexpr auto max_size() const noexcept -> size_type;

        /**
         * @brief Increase the capacity of the container
         *
         * @param[in] new_cap new capacity of container, new number of elements the container can store
         */
        constexpr void reserve(size_type new_cap);

        /**
         * @brief Returns the number of elements allocated for container
         *
         * @return size_type number of allocated elements
         */
        constexpr auto capacity() -> size_type;

        /**
         * @brief Request to remove of unused capacity
         *
         * @note If request is fulfilled and reallocation occurs, all iterators
         *       and all references to the container elements are invalidated
         */
        constexpr void shrink_to_fit();

        /**
         * @brief Erases all elements of the container
         *        Does not affect container capacity.
         *
         * @note Operation invalidates all pointers and references
         */
        constexpr void clear();

        /**
         * @brief Insert a copy of \p value before \p pos
         *
         * @param[in] pos iterator before which new element will be inserted
         * @param[in] value element to insert into container
         * @return iterator pointing to inserted element
         */
        constexpr auto insert(const_iterator pos, const T& value) -> iterator;

        /**
         * @brief Insert \p value before \p pos possibly using move semantics
         *
         * @param[in] pos iterator before which new element will be inserted
         * @param[in] value element to insert into container
         * @return iterator pointing to inserted element
         */
        constexpr auto insert(const_iterator pos, T&& value) -> iterator;

        /**
         * @brief Insert \p count copies of \p value before \p pos
         *
         * @param[in] pos iterator before which new element will be inserted
         * @param[in] count number of copies to insert into container
         * @param[in] value element to insert into container
         * @return iterator pointing to the first inserted element, or \p pos if no element was inserted
         *
         * @note if no reallocation occurs, all iterators and references before \p pos remains valid
         *       if reallocation occurs, all iterators and references are invalidated
         */
        constexpr auto insert(const_iterator pos, size_type count, const T& value) -> iterator;

        /**
         * @brief Insert elements from range [ \p first , \p last ) befor \p pos
         *
         * @tparam InputIt
         * @param[in] pos iterator before which new element will be inserted
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         * @return iterator pointing to the first inserted element, or \p pos if no element was inserted
         *
         * @note if no reallocation occurs, all iterators and references before \p pos remains valid
         *       if reallocation occurs, all iterators and references are invalidated
         */
        template<typename InputIt>
            requires std::input_iterator<InputIt>
        constexpr auto insert(const_iterator pos, InputIt first, InputIt last) -> iterator;

        /**
         * @brief Insert constent of \p init_list before \p pos
         *
         * @param[in] pos iterator before which new element will be inserted
         * @param[in] init_list container to insert befor \p pos
         * @return iterator pointing to the first inserted element, or \p pos if no element was inserted
         *
         * @note if no reallocation occurs, all iterators and references before \p pos remains valid
         *       if reallocation occurs, all iterators and references are invalidated
         */
        constexpr auto insert(const_iterator pos, std::initializer_list<T> init_list) -> iterator;

        /**
         * @brief Insert new element into the container before \p pos
         *
         * @tparam Args
         * @param[in] pos iterator before which new element will be inserted
         * @param[in] args arguments to forward to the constructor of the element
         * @return iterator pointing to the emplaced element
         *
         * @note if no reallocation occurs, all iterators and references before \p pos remains valid
         *       if reallocation occurs, all iterators and references are invalidated
         */
        template<typename... Args>
        constexpr auto emplace(const_iterator pos, Args&&... args) -> iterator;

        /**
         * @brief Appends a copy of \p value at the end of the container
         *
         * @tparam Args
         * @param[in] args arguments to forward to the constructor of the element
         * @return reference to emplaced element
         */
        template<typename... Args>
        constexpr auto emplace_back(Args&&... args) -> reference;

        /**
         * @brief Erases specified element from the container
         *
         * @param[in] pos iterator to the element to remove
         * @return iterator iterator to element after last erased element
         *
         * @note iterator \p pos must be valid and dereferencable
         *       iterators and references at and after \p pos are invalidated
         */
        constexpr auto erase(iterator pos) -> iterator;

        /**
         * @brief Erases specified element from the container
         *
         * @param[in] pos iterator to the element to remove
         * @return iterator iterator to element after last erased element
         *
         * @note iterator \p pos must be valid and dereferencable
         *       iterators and references at and after \p pos are invalidated
         */
        constexpr auto erase(const_iterator pos) -> iterator;

        /**
         * @brief Erases elements in range [ \p first , \p last ) from the container
         *
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         * @return iterator iterator to element after last erased element
         *
         * @note iterator \p first does not need to be dereferencable
         *       iterators and references at and after \p first are invalidated
         */
        constexpr auto erase(iterator first, iterator last) -> iterator;

        /**
         * @brief Erases elements in range [ \p first , \p last ) from the container
         *
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         * @return iterator iterator to element after last erased element
         *
         * @note iterator \p first does not need to be dereferencable
         *       iterators and references at and after \p first are invalidated
         */
        constexpr auto erase(const_iterator first, const_iterator last) -> iterator;

        /**
         * @brief Appends a copy of \p value at the end of the container
         *
         * @param[in] value the value of the element to append
         */
        constexpr void push_back(const T& value);

        /**
         * @brief Appends a copy of \p value at the end of the container
         *
         * @param[in] value the value of the element to append
         */
        constexpr void push_back(T&& value);

        /**
         * @brief Removes the last element of the container
         *
         * @note iterators and references to the last element are invalidated
         */
        constexpr void pop_back();

        /**
         * @brief Resizez the container to contain \p count elements
         *        if \p count is equal to current size, does nothing
         *        if current size is greater than \p count , container size is reduced
         *        if current size is less than \p count , additional copies of T() are appended
         *
         * @param[in] count new size of the container
         */
        constexpr void resize(size_type count);

        /**
         * @brief Resizes the container to contain \p count elements
         *        if \p count is equal to current size, does nothing
         *        if current size is greater than \p count , container size is reduced
         *        if current size is less than \p count , additional copies of \p value are appended
         *
         * @param[in] count new size of the container
         * @param[in] value the value to initialize the new element with
         */
        constexpr void resize(size_type count, const value_type& value);

        /**
         * @brief Exchanges content of current container with \p other container
         *
         * @param[in] other container to exchange content with
         */
        constexpr void swap(Vector<T>& other) noexcept;

    private:

        /**
         * @brief Function calculate proposition of new capacity for the container
         *
         * @return size_type proposition of new capacity
         */
        auto calc_new_capacity() -> size_type;

        /**
         * @brief Function creates empty space for new elements during insert
         *
         * @param[in] pos iterator before which new element will be inserted
         * @param[in] count number of new elements to insert into container
         *
         * @return iterator to first empty space to insert new element
         */
        auto insert_make_space_for_new_elems(const_iterator pos, size_type count) -> iterator;

        /**
         * @brief Function increase memory allocation of the container to hold \p new_cap number of elements
         *
         * @param[in] new_cap new capacity of container as maximum number of elements the container can store
         *
         * @note After reallocation all iterators and all references are invalidated
         */
        void reallocate(size_type new_cap);

        /**
         * @brief Destroys all objects in container
         */
        void destroy_elements();

        /**
         * @brief Destroys all objects in container and deallocates memory
         */
        void clear_allocation();

        /**
         * @brief Underlaying dynamic size memory containing all elements
         */
        value_type* m_data{};

        /**
         * @brief Number of created elements
         */
        size_type m_size{};

        /**
         * @brief Number of elements that can be stored with corrent memory allocation
         */
        size_type m_capacity{};

        /**
         * @brief Allocator for memory management
         */
        allocator_type m_allocator{};
    };

    template<typename T>
    constexpr Vector<T>::Vector() = default;

    template<typename T>
    constexpr Vector<T>::Vector(size_type count)
        : Vector(count, T())
    {
    }

    template<typename T>
    constexpr Vector<T>::Vector(size_type count, const T& value)
    {
        for (size_t i = 0; i < count; i++)
        {
            push_back(value);
        }
    }

    template<typename T>
    template<typename InputIt>
        requires std::input_iterator<InputIt>
    constexpr Vector<T>::Vector(InputIt first, InputIt last)
    {
        // do not use const reference to keep arguments the same as in std
        // NOLINTNEXTLINE(performance-unnecessary-value-param)
        assign(first, last);
    }

    template<typename T>
    constexpr Vector<T>::Vector(const Vector<T>& other)
    {
        reserve(other.size());
        for (const auto& item : other)
        {
            push_back(item);
        }
    }

    template<typename T>
    constexpr Vector<T>::Vector(Vector<T>&& other) noexcept
    {
        operator=(std::move(other));
    }

    template<typename T>
    constexpr Vector<T>::Vector(std::initializer_list<T> init_list)
    {
        assign(init_list);
    }

    template<typename T>
    Vector<T>::~Vector()
    {
        clear_allocation();
    }

    template<typename T>
    constexpr auto Vector<T>::operator=(const Vector<T>& other) -> Vector<T>&
    {
        if (&other != this)
        {
            clear_allocation();
            m_capacity = 0;
            m_size = 0;

            m_data = allocator_type().allocate(other.size());
            for (const auto& item : other)
            {
                push_back(item);
            }
        }

        return *this;
    }

    template<typename T>
    constexpr auto Vector<T>::operator=(Vector<T>&& other) noexcept -> Vector<T>&
    {
        if (&other != this)
        {
            clear_allocation();

            m_data = other.m_data;
            m_capacity = other.m_capacity;
            m_size = other.m_size;

            other.m_data = nullptr;
            other.m_capacity = 0;
            other.m_size = 0;
        }

        return *this;
    }

    template<typename T>
    constexpr auto Vector<T>::operator=(std::initializer_list<T> init_list) -> Vector<T>&
    {
        clear_allocation();
        m_capacity = 0;
        m_size = 0;

        m_data = allocator_type().allocate(init_list.size());
        for (auto const& item : init_list)
        {
            push_back(item);
        }

        return *this;
    }

    template<typename T>
    constexpr void Vector<T>::assign(size_type count, const T& value)
    {
        clear_allocation();
        m_capacity = 0;
        m_size = 0;

        m_data = allocator_type().allocate(count);
        for (size_t i = 0; i < count; i++)
        {
            push_back(value);
        }
    }

    template<typename T>
    template<typename InputIt>
        requires std::input_iterator<InputIt>
    // do not use `last` as const reference to keep arguments the same as in std
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    constexpr void Vector<T>::assign(InputIt first, InputIt last)
    {
        const auto count = static_cast<size_type>(std::distance(first, last));

        clear_allocation();
        m_capacity = 0;
        m_size = 0;

        m_data = allocator_type().allocate(count);
        while (first != last)
        {
            push_back(*first);
            first++;
        }
    }

    template<typename T>
    constexpr void Vector<T>::assign(std::initializer_list<T> init_list)
    {
        clear_allocation();
        m_capacity = 0;
        m_size = 0;

        m_data = allocator_type().allocate(init_list.size());
        for (auto const& item : init_list)
        {
            push_back(item);
        }
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::get_allocator() const -> allocator_type
    {
        return m_allocator;
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::at(size_type pos) -> reference
    {
        if (pos >= m_size)
        {
            throw std::out_of_range("Pos argument outside of container range");
        }

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return m_data[pos];
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::at(size_type pos) const -> const_reference
    {
        if (pos >= m_size)
        {
            throw std::out_of_range("Pos argument outside of container range");
        }

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return m_data[pos];
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::operator[](size_type pos) -> reference
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return m_data[pos];
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::operator[](size_type pos) const -> const_reference
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return m_data[pos];
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::front() -> reference
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return m_data[0];
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::front() const -> const_reference
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return m_data[0];
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::back() -> reference
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return m_data[m_size - 1];
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::back() const -> const_reference
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return m_data[m_size - 1];
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::data() noexcept -> pointer
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return &m_data[0];
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::data() const noexcept -> const_pointer
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return &m_data[0];
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::begin() noexcept -> iterator
    {
        return m_data;
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::begin() const noexcept -> const_iterator
    {
        return m_data;
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::cbegin() const noexcept -> const_iterator
    {
        return m_data;
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::end() noexcept -> iterator
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return m_data + m_size;
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::end() const noexcept -> const_iterator
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return m_data + m_size;
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::cend() const noexcept -> const_iterator
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return m_data + m_size;
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::rbegin() -> reverse_iterator
    {
        return reverse_iterator(end());
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::rbegin() const -> const_reverse_iterator
    {
        return const_reverse_iterator(end());
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::crbegin() const noexcept -> const_reverse_iterator
    {
        return const_reverse_iterator(end());
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::rend() -> reverse_iterator
    {
        return reverse_iterator(begin());
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::rend() const -> const_reverse_iterator
    {
        return const_reverse_iterator(begin());
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::crend() const noexcept -> const_reverse_iterator
    {
        return const_reverse_iterator(begin());
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::empty() const -> bool
    {
        return m_size == 0;
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::size() const noexcept -> size_type
    {
        return m_size;
    }

    template<typename T>
    [[nodiscard]] constexpr auto Vector<T>::max_size() const noexcept -> size_type
    {
        return std::allocator_traits<allocator_type>::max_size(get_allocator());
    }

    template<typename T>
    constexpr void Vector<T>::reserve(size_type new_cap)
    {
        if (new_cap > capacity())
        {
            // strong exception guarantee by reallocate
            reallocate(new_cap);
        }
    }

    template<typename T>
    constexpr auto Vector<T>::capacity() -> size_type
    {
        return m_capacity;
    }

    template<typename T>
    constexpr void Vector<T>::shrink_to_fit()
    {
        if (m_capacity > m_size)
        {
            reallocate(m_size);
        }
    }

    template<typename T>
    constexpr void Vector<T>::clear()
    {
        destroy_elements();
        m_size = 0;
    }

    template<typename T>
    constexpr auto Vector<T>::insert(const_iterator pos, const T& value) -> iterator
    {
        return insert(pos, 1, value);
    }

    template<typename T>
    constexpr auto Vector<T>::insert(const_iterator pos, T&& value) -> iterator
    {
        return insert(pos, 1, std::move(value));
    }

    template<typename T>
    constexpr auto Vector<T>::insert(const_iterator pos, size_type count, const T& value) -> iterator
    {
        iterator new_pos{ insert_make_space_for_new_elems(pos, count) };

        // create objects in range [pos, pos + count]
        iterator new_iter{ new_pos };
        for (size_t i = 0; i < count; i++)
        {
            std::allocator_traits<allocator_type>::construct(m_allocator, new_iter, value);
            ++new_iter;
        }

        return new_pos;
    }

    template<typename T>
    template<typename InputIt>
        requires std::input_iterator<InputIt>
    constexpr auto Vector<T>::insert(const_iterator pos, InputIt first, InputIt last) -> iterator
    {
        const auto count = static_cast<size_type>(std::distance(first, last));
        iterator new_pos{ insert_make_space_for_new_elems(pos, count) };

        // create objects in range [pos, pos + count]
        iterator new_iter{ new_pos };
        while (first != last)
        {
            std::allocator_traits<allocator_type>::construct(m_allocator, new_iter, *first);
            ++new_iter;
            ++first;
        }

        return new_pos;
    }

    template<typename T>
    constexpr auto Vector<T>::insert(const_iterator pos, std::initializer_list<T> init_list) -> iterator
    {
        const size_type count = init_list.size();
        iterator new_pos{ insert_make_space_for_new_elems(pos, count) };

        // create objects in range [pos, pos + count]
        iterator new_iter{ new_pos };
        for (const auto& value : init_list)
        {
            std::allocator_traits<allocator_type>::construct(m_allocator, new_iter, value);
            ++new_iter;
        }

        return new_pos;
    }

    template<typename T>
    template<typename... Args>
    constexpr auto Vector<T>::emplace(const_iterator pos, Args&&... args) -> iterator
    {
        iterator new_pos{ insert_make_space_for_new_elems(pos, 1) };

        // emplace new element
        std::allocator_traits<allocator_type>::construct(m_allocator, new_pos, std::forward<Args>(args)...);

        return new_pos;
    }

    template<typename T>
    template<typename... Args>
    constexpr auto Vector<T>::emplace_back(Args&&... args) -> reference
    {
        /*
        * If an exception is thrown for any reason, this function has no effect
        * strong exception guarantee by:
        * - reallocate
        * - if construction of new element fails, state of object does not change
        */

        if (m_size >= m_capacity)
        {
            reallocate(calc_new_capacity());
        }
        std::allocator_traits<allocator_type>::construct(m_allocator, end(), std::forward<Args>(args)...);
        ++m_size;

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return m_data[m_size - 1];
    }

    template<typename T>
    constexpr auto Vector<T>::erase(iterator pos) -> iterator
    {
        return erase(pos, pos + 1);
    }

    template<typename T>
    constexpr auto Vector<T>::erase(const_iterator pos) -> iterator
    {
        return erase(pos, pos + 1);
    }

    template<typename T>
    constexpr auto Vector<T>::erase(iterator first, iterator last) -> iterator
    {
        return erase(static_cast<const_iterator>(first), static_cast<const_iterator>(last));
    }

    template<typename T>
    constexpr auto Vector<T>::erase(const_iterator first, const_iterator last) -> iterator
    {
        const auto offset_last = static_cast<size_type>(last - cbegin());
        const auto offset_first = static_cast<size_type>(first - cbegin());
        const size_type count{ offset_last - offset_first };

        // destroy objects in range [first, last)
        while (first != last)
        {
            std::allocator_traits<allocator_type>::destroy(m_allocator, first);
            ++first;
        }

        // move remaining objects into empty space
        // this moves memory in range [last, end()] to addres pointed by `first`, that was already released
        std::move(begin() + offset_last, end(), begin() + offset_first);

        m_size -= count;
        return begin() + offset_first;
    }

    template<typename T>
    constexpr void Vector<T>::push_back(const T& value)
    {
        if (m_size >= m_capacity)
        {
            reallocate(calc_new_capacity());
        }

        std::allocator_traits<allocator_type>::construct(m_allocator, end(), value);
        ++m_size;
    }

    template<typename T>
    constexpr void Vector<T>::push_back(T&& value)
    {
        // Some implementations throw std::lengt_error when push_back causes a reallocation that exceeds mas_size()
        if (m_size >= m_capacity)
        {
            reallocate(calc_new_capacity());
        }

        std::allocator_traits<allocator_type>::construct(m_allocator, end(), std::move(value));
        ++m_size;
    }

    template<typename T>
    constexpr void Vector<T>::pop_back()
    {
        if (m_size > 0)
        {
            std::allocator_traits<allocator_type>::destroy(m_allocator, end());
            --m_size;
        }
    }

    template<typename T>
    constexpr void Vector<T>::resize(size_type count)
    {
        resize(count, T{});
    }

    template<typename T>
    constexpr void Vector<T>::resize(size_type count, const value_type& value)
    {
        if (count >= max_size())
        {
            throw std::length_error("Capacity required by new vector would exceed maximum allowed size");
        }

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
    constexpr void Vector<T>::swap(Vector<T>& other) noexcept
    {
        std::swap(*this, other);
    }

    template<typename T>
    inline auto Vector<T>::calc_new_capacity() -> size_type
    {
        return m_capacity == 0 ? 1 : m_capacity * 2;
    }

    template<typename T>
    auto Vector<T>::insert_make_space_for_new_elems(const_iterator pos, size_type count) -> iterator
    {
        iterator new_pos{};

        if (size() + count > capacity())
        {
            // allocate memory to store new content
            const size_type new_capacity = m_capacity + count;
            pointer new_data = allocator_type().allocate(new_capacity);

            // use iterator to move all objects from original vector to new allocated memory
            iterator iter{ begin() };
            iterator new_iter = new_data;

            // move all objects before pos from original memory
            while (iter != pos)
            {
                std::allocator_traits<allocator_type>::construct(m_allocator, new_iter, std::move(*iter));
                ++iter;
                ++new_iter;
            }

            // make space for new elements
            new_pos = new_iter;
            for (size_t i = 0; i < count; i++)
            {
                ++new_iter;
            }

            // move all remaining objects from original memory
            while (iter != end())
            {
                std::allocator_traits<allocator_type>::construct(m_allocator, new_iter, std::move(*iter));
                ++iter;
                ++new_iter;
            }

            clear_allocation();
            m_data = new_data;
            m_capacity = new_capacity;
            m_size += count;
        }
        else
        {
            // store address to insert new elements
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
            iterator iter{ const_cast<iterator>(pos) };
            new_pos = iter;

            // move object to the right
            std::move(iter, end(), iter + count);

            m_size += count;
        }

        return new_pos;
    }

    template<typename T>
    void Vector<T>::reallocate(size_type new_cap)
    {
        /*
        * strong exception guarantee by:
        * - throwing exception in case container is too large
        * - using std::move_if_noexcept during reallocation
        */

        if (new_cap > max_size())
        {
            throw std::length_error("Pos argument outside of container range");
        }

        pointer new_data = allocator_type().allocate(new_cap);
        for (size_t i = 0; i < m_size; i++)
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            std::allocator_traits<allocator_type>::construct(m_allocator, new_data + i, std::move_if_noexcept(m_data[i]));
        }
        clear_allocation();
        m_data = new_data;
        m_capacity = new_cap;
        // m_size stay the same as before reallocation
    }

    template<typename T>
    void Vector<T>::destroy_elements()
    {
        iterator iter{ begin() };
        while (iter != end())
        {
            std::allocator_traits<allocator_type>::destroy(m_allocator, iter);
            ++iter;
        }
    }

    template<typename T>
    void Vector<T>::clear_allocation()
    {
        if (m_data)
        {
            destroy_elements();
            std::allocator_traits<allocator_type>::deallocate(m_allocator, m_data, m_capacity);
            m_capacity = 0;
        }
    }

    /**
     * @brief Exchanges content of two Vector containers
     *
     * @tparam T data type stored in containers
     * @param[in] vector1 container to swap content
     * @param[in] vector2 container to swap content
     */
    template<typename T>
    void swap(Vector<T>& vector1, Vector<T>& vector2) noexcept
    {
        vector1.swap(vector2);
    }

    /**
     * @brief Overloads operator to print all elements of Vector
     *
     * @tparam T data type stored in container
     * @param[in,out] out reference to output stream
     * @param[in] vector Vector to print
     * @return std::ostream&
     */
    template<typename T>
    auto operator<<(std::ostream& out, const Vector<T>& vector) -> std::ostream&
    {
        for (size_t i = 0; i < vector.size(); i++)
        {
            out << vector[i] << ' ';
        }

        return out;
    }

    /**
     * @brief The relational operator compares two Vector objects
     *
     * @tparam T type of data stored in container
     * @param[in] vector1 input container
     * @param[in] vector2 input container
     * @retval true if containers are equal
     * @retval false if containers are not equal
     */
    template<typename T>
    auto operator==(const Vector<T>& vector1, const Vector<T>& vector2) -> bool
    {
        if (vector1.size() != vector2.size())
        {
            return false;
        }

        auto vector1_iter = vector1.cbegin();
        auto vector2_iter = vector2.cbegin();

        // vectors have equal size, test condition for one vector
        while (vector1_iter != vector1.cend())
        {
            if (*vector1_iter != *vector2_iter)
            {
                return false;
            }

            vector1_iter++;
            vector2_iter++;
        }

        return true;
    }

    /**
     * @brief The relational operator compares two Vector objects
     *
     * @param[in] vector1 input container
     * @param[in] vector2 input container
     * @retval -1 if the content of \p vector1 is lexicographically lesser than the content of \p vector2
     * @retval  0 if the content of \p vector1 and \p vector2 is equal
     * @retval +1 if the content of \p vector1 is lexicographically greater than the content of \p vector2
     */
    template<typename T>
    constexpr auto operator<=>(const Vector<T>& vector1, const Vector<T>& vector2)
    {
        auto vector1_iter = vector1.cbegin();
        auto vector2_iter = vector2.cbegin();

        while (vector1_iter != vector1.cend() && vector2_iter != vector2.cend())
        {
            if (*vector1_iter < *vector2_iter)
            {
                return std::strong_ordering::less;
            }
            if (*vector1_iter > *vector2_iter)
            {
                return std::strong_ordering::greater;
            }

            vector1_iter++;
            vector2_iter++;
        }

        if (vector1.size() < vector2.size())
        {
            return std::strong_ordering::less;
        }
        if (vector1.size() > vector2.size())
        {
            return std::strong_ordering::greater;
        }

        return std::strong_ordering::equivalent;
    }
}

#endif // !VECTOR_H
