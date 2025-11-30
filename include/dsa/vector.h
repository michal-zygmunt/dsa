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
     *       and replace `bool&` with proxy objects. `dsa::Vector<bool>` behaves
     *       like a regular container, without bit-packing.
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
        constexpr Vector() = default;

        /**
         * @brief Construct a new Vector object of size \p count,
         *        using default value of type T
         *
         * @param[in] count element count
         */
        constexpr Vector(size_type count)
            : Vector(count, T())
        {
        }

        /**
         * @brief Construct a new Vector object of size \p count,
         * using provided \p value of type T
         *
         * @param[in] count element count
         * @param[in] value value for all elements
         */
        constexpr Vector(size_type count, const T& value)
        {
            for (size_t i = 0; i < count; i++)
            {
                push_back(value);
            }
        }

        /**
         * @brief Construct a new Vector object using elements from range [ \p first , \p last )
         *
         * @tparam InputIt
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         */
        template<typename InputIt>
            requires std::input_iterator<InputIt>
        constexpr Vector(InputIt first, InputIt last)
        {
            const size_type count = last - first;
            reserve(count);

            while (first != last)
            {
                push_back(*first);
                first++;
            }
        }

        /**
         * @brief Construct a new Vector object using copy constructor
         *
         * @param[in] other Vector object of type T
         */
        constexpr Vector(const Vector& other)
        {
            reserve(other.size());
            for (const auto& item : other)
            {
                push_back(item);
            }
        }

        /**
         * @brief Construct a new Vector object using move constructor
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other Vector object of type T
         */
        constexpr Vector(Vector&& other) noexcept
        {
            operator=(std::move(other));
        }

        /**
         * @brief Construct a new Vector object using initializer list
         *
         * @param[in] init_list initializer list of values of type T
         */
        constexpr Vector(std::initializer_list<T> init_list)
        {
            reallocate(init_list.size());

            for (auto const& item : init_list)
            {
                push_back(item);
            }
        }

        /**
         * @brief Destroy the Vector object
         */
        ~Vector()
        {
            clear_allocation();
        }

        /**
         * @brief Assign Vector object using copy assignment
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other Vector object of type T
         * @return Vector& reference to constructed Vector of type T
         */
        constexpr auto operator=(const Vector<T>& other) -> Vector<T>&
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

        /**
         * @brief Assign Vector object using move assignment
         * @details Content of other object will be taken by constructed object
         *
         * @param[in,out] other Vector object of type T
         * @return Vector& reference to constructed Vector of type T
         */
        constexpr auto operator=(Vector<T>&& other) noexcept -> Vector<T>&
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

        /**
         * @brief Assign Vector object from \p init_list elements
         *
         * @param[in] init_list values to replace Vector with
         * @return Vector& reference to constructed Vector of type T
         */
        constexpr auto operator=(std::initializer_list<T> init_list) -> Vector<T>&
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

        /**
         * @brief Function assign \p count , elements of \p value to Vector object
         *
         * @param[in] count new size of the container
         * @param[in] value value to initialize elements of the container with
         */
        constexpr void assign(size_type count, const T& value)
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

        /**
         * @brief Function assign elements from range [ \p first , \p last ) to Vector object
         *
         * @tparam InputIt
         * @param[in] first element defining range of elements to insert
         * @param[in] last element definig range of elements to insert
         */
        template<typename InputIt>
            requires std::input_iterator<InputIt>
        constexpr void assign(InputIt first, InputIt last)
        {
            const size_type count = last - first;

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

        /**
         * @brief Function assign values of \p init_list to Vector object
         *
         * @param[in] init_list initializer list of values of type T
         */
        constexpr void assign(std::initializer_list<T> init_list)
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

        /**
         * @brief Get the allocator object
         *
         * @return allocator_type type of memory allocator
         */
        [[nodiscard]] constexpr auto get_allocator() const -> allocator_type
        {
            return m_allocator;
        }

        /**
         * @brief Returns a reference to Vector element at \p pos index.
         *        If \p pos is outside of container range, an exception std::out_of_range is thrown.
         *
         * @param[in] pos index of element to return
         * @return reference to Vector element at \p pos index
         */
        [[nodiscard]] constexpr auto at(size_type pos) -> reference
        {
            if (pos >= m_size)
            {
                throw std::out_of_range("Pos argument outside of container range");
            }

            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return m_data[pos];
        }

        /**
         * @brief Returns a const_reference to Vector element at \p pos index.
         *        If \p pos is outside of container range, an exception std::out_of_range is thrown.
         *
         * @param[in] pos index of element to return
         * @return const_reference to Vector element at \p pos index
         */
        [[nodiscard]] constexpr auto at(size_type pos) const -> const_reference
        {
            if (pos >= m_size)
            {
                throw std::out_of_range("Pos argument outside of container range");
            }

            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return m_data[pos];
        }

        /**
         * @brief Returns a reference to Vector element at \p pos index.
         *        If \p pos is outside of container range, undefined behaviour occurs.
         *
         * @param[in] pos index of element to return
         * @return reference to Vector element
         */
        [[nodiscard]] constexpr auto operator[](size_type pos) -> reference
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return m_data[pos];
        }

        /**
         * @brief Returns a const_reference to Vector element at \p pos index.
         *        If \p pos is outside of container range, undefined behaviour occurs.
         *
         * @param[in] pos index of element to return
         * @return const_reference to Vector element
         */
        [[nodiscard]] constexpr auto operator[](size_type pos) const -> const_reference
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return m_data[pos];
        }

        /**
         * @brief Returns reference to first Arary element
         *
         * @return reference to first element
         */
        [[nodiscard]] constexpr auto front() -> reference
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return m_data[0];
        }

        /**
         * @brief Returns const_reference to first Arary element
         *
         * @return const_reference to first element
         */
        [[nodiscard]] constexpr auto front() const -> const_reference
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return m_data[0];
        }

        /**
         * @brief Returns reference to last Arary element
         *
         * @return reference to last element
         */
        [[nodiscard]] constexpr auto back() -> reference
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return m_data[m_size - 1];
        }

        /**
         * @brief Returns const_reference to last Arary element
         *
         * @return const_reference to last element
         */
        [[nodiscard]] constexpr auto back() const -> const_reference
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return m_data[m_size - 1];
        }

        /**
         * @brief Returns pointer to underlying data container
         *
         * @return pointer to underlaying data container
         */
        [[nodiscard]] constexpr auto data() noexcept -> pointer
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return &m_data[0];
        }

        /**
         * @brief Returns const_pointer to underlying data container
         *
         * @return const_pointer to underlaying data container
         */
        [[nodiscard]] constexpr auto data() const noexcept -> const_pointer
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return &m_data[0];
        }

        /**
         * @brief Returns iterator to first element
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return iterator to first element
         */
        [[nodiscard]] constexpr auto begin() noexcept -> iterator
        {
            return m_data;
        }

        /**
         * @brief Returns const_iterator to first element
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return const_iterator to first element
         */
        [[nodiscard]] constexpr auto begin() const noexcept -> const_iterator
        {
            return m_data;
        }

        /**
         * @brief Returns const_iterator to first element
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return const_iterator to first element
         */
        [[nodiscard]] constexpr auto cbegin() const noexcept -> const_iterator
        {
            return m_data;
        }

        /**
         * @brief Returns iterator past last element of underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return iterator past last element
         */
        [[nodiscard]] constexpr auto end() noexcept -> iterator
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return m_data + m_size;
        }

        /**
         * @brief Returns const_iterator past last element of underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return const_iterator past last element
         */
        [[nodiscard]] constexpr auto end() const noexcept -> const_iterator
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return m_data + m_size;
        }

        /**
         * @brief Returns const_iterator past last element of underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return const_iterator past last element
         */
        [[nodiscard]] constexpr auto cend() const noexcept -> const_iterator
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return m_data + m_size;
        }

        /**
         * @brief Returns reverse_iterator to the first element of reversed underlaying data structure
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return reverse_iterator to the first element
         */
        [[nodiscard]] constexpr auto rbegin() -> reverse_iterator
        {
            return reverse_iterator(end());
        }

        /**
         * @brief Returns const_reverse_iterator to the first element of reversed underlaying data structure
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return const_reverse_iterator to the first element
         */
        [[nodiscard]] constexpr auto rbegin() const -> const_reverse_iterator
        {
            return const_reverse_iterator(end());
        }

        /**
         * @brief Returns const_reverse_iterator to the first element of reversed underlaying data structure
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return const_reverse_iterator to the first element
         */
        [[nodiscard]] constexpr auto crbegin() const noexcept -> const_reverse_iterator
        {
            return const_reverse_iterator(end());
        }

        /**
         * @brief Returns reverse_iterator past the last element of reversed underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return reverse_iterator to the element after the last element
         */
        [[nodiscard]] constexpr auto rend() -> reverse_iterator
        {
            return reverse_iterator(begin());
        }

        /**
         * @brief Returns const_reverse_iterator past the last element of reversed underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return const_reverse_iterator to the element after the last element
         */
        [[nodiscard]] constexpr auto rend() const -> const_reverse_iterator
        {
            return const_reverse_iterator(begin());
        }

        /**
         * @brief Returns const_reverse_iterator past the last element of reversed underlaying data structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return const_reverse_iterator to the element after the last element
         */
        [[nodiscard]] constexpr auto crend() const noexcept -> const_reverse_iterator
        {
            return const_reverse_iterator(begin());
        }

        /**
         * @brief Checks if container has elements
         *
         * @return true if container is empty
         * @return false if container is not empty
         */
        [[nodiscard]] constexpr auto empty() const -> bool
        {
            return m_size == 0;
        }

        /**
         * @brief Returns number of elements in container
         *
         * @return size_type number of elements in container
         */
        [[nodiscard]] constexpr auto size() const noexcept -> size_type
        {
            return m_size;
        }

        /**
         * @brief Returns maximum number of elements container can hold
         *
         * @return size_type maximum number of elements
         */
        [[nodiscard]] constexpr auto max_size() const noexcept -> size_type
        {
            return std::allocator_traits<allocator_type>::max_size(get_allocator());
        }

        /**
         * @brief Increase the capacity of the container
         *
         * @param[in] new_cap new capacity of container, new number of elements the container can store
         */
        constexpr void reserve(size_type new_cap)
        {
            if (new_cap > capacity())
            {
                // strong exception guarantee by reallocate
                reallocate(new_cap);
            }
        }

        /**
         * @brief Returns the number of elements allocated for container
         *
         * @return size_type number of allocated elements
         */
        constexpr auto capacity() -> size_type
        {
            return m_capacity;
        }

        /**
         * @brief Request to remove of unused capacity
         *
         * @note If request is fulfilled and reallocation occurs, all iterators
         *       and all references to the container elements are invalidated
         */
        constexpr void shrink_to_fit()
        {
            if (m_capacity > m_size)
            {
                reallocate(m_size);
            }
        }

        /**
         * @brief Erases all elements of the container
         *        Does not affect container capacity.
         *
         * @note Operation invalidates all pointers and references
         */
        constexpr void clear()
        {
            iterator iter{ begin() };
            while (iter != end())
            {
                std::allocator_traits<allocator_type>::destroy(m_allocator, iter);
                ++iter;
            }
            m_size = 0;
        }

        /**
         * @brief Insert a copy of \p value before \p pos
         *
         * @param[in] pos iterator before which new element will be inserted
         * @param[in] value element to insert into container
         * @return iterator pointing to inserted element
         */
        constexpr auto insert(const_iterator pos, const T& value) -> iterator
        {
            return insert(pos, 1, value);
        }

        /**
         * @brief Insert \p value before \p pos possibly using move semantics
         *
         * @param[in] pos iterator before which new element will be inserted
         * @param[in] value element to insert into container
         * @return iterator pointing to inserted element
         */
        constexpr auto insert(const_iterator pos, T&& value) -> iterator
        {
            return insert(pos, 1, std::move(value));
        }

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
        constexpr auto insert(const_iterator pos, size_type count, const T& value) -> iterator
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

                // insert new elements
                new_pos = new_iter;
                for (size_t i = 0; i < count; i++)
                {
                    std::allocator_traits<allocator_type>::construct(m_allocator, new_iter, value);
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

                // create objects in range [pos, pos + count]
                for (size_t i = 0; i < count; i++)
                {
                    std::allocator_traits<allocator_type>::construct(m_allocator, iter, value);
                    ++iter;
                }

                m_size += count;
            }

            return new_pos;
        }

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
        constexpr auto insert(const_iterator pos, InputIt first, InputIt last) -> iterator
        {
            iterator new_pos{};
            const size_type count = last - first;

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

                // insert new elements
                new_pos = new_iter;
                while (first != last)
                {
                    std::allocator_traits<allocator_type>::construct(m_allocator, new_iter, *first);
                    ++new_iter;
                    ++first;
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

                // create objects in range [pos, pos + count]
                while (first != last)
                {
                    std::allocator_traits<allocator_type>::construct(m_allocator, iter, *first);
                    ++iter;
                    ++first;
                }

                m_size += count;
            }

            return new_pos;
        }

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
        constexpr auto insert(const_iterator pos, std::initializer_list<T> init_list) -> iterator
        {
            iterator new_pos{};
            const size_type count = init_list.size();

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

                // insert new elements
                new_pos = new_iter;
                for (const auto& value : init_list)
                {
                    std::allocator_traits<allocator_type>::construct(m_allocator, new_iter, value);
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

                // create objects in range [pos, pos + count]
                for (const auto& value : init_list)
                {
                    std::allocator_traits<allocator_type>::construct(m_allocator, iter, value);
                    ++iter;
                }

                m_size += count;
            }

            return new_pos;
        }

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
        constexpr auto emplace(const_iterator pos, Args&&... args) -> iterator
        {
            iterator new_pos{};
            const size_type count = 1;

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

                // insert new elements
                new_pos = new_iter;
                std::allocator_traits<allocator_type>::construct(m_allocator, new_iter, std::forward<Args>(args)...);
                ++new_iter;

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

                // create objects in range [pos, pos + count]
                std::allocator_traits<allocator_type>::construct(m_allocator, iter, std::forward<Args>(args)...);
                //++iter;

                m_size += count;
            }

            return new_pos;
        }

        /**
         * @brief Appends a copy of \p value at the end of the container
         *
         * @tparam Args
         * @param[in] args arguments to forward to the constructor of the element
         * @return reference to emplaced element
         */
        template<typename... Args>
        constexpr auto emplace_back(Args&&... args) -> reference
        {
            /*
            * If an exception is thrown for any reason, this function has no effect
            * strong exception guarantee by:
            * - reallocate
            * - if construction of new element fails, state of object does not change
            */

            if (m_size >= m_capacity)
            {
                reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
            }
            std::allocator_traits<allocator_type>::construct(m_allocator, end(), std::forward<Args>(args)...);
            ++m_size;

            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return m_data[m_size - 1];
        }

        /**
         * @brief Erases specified element from the container
         *
         * @param[in] pos iterator to the element to remove
         * @return iterator iterator to element after last erased element
         *
         * @note iterator \p pos must be valid and dereferencable
         *       iterators and references at and after \p pos are invalidated
         */
        constexpr auto erase(iterator pos) -> iterator
        {
            return erase(pos, pos + 1);
        }

        /**
         * @brief Erases specified element from the container
         *
         * @param[in] pos iterator to the element to remove
         * @return iterator iterator to element after last erased element
         *
         * @note iterator \p pos must be valid and dereferencable
         *       iterators and references at and after \p pos are invalidated
         */
        constexpr auto erase(const_iterator pos) -> iterator
        {
            return erase(pos, pos + 1);
        }

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
        constexpr auto erase(iterator first, iterator last) -> iterator
        {
            size_type count{};

            // destroy objects in range [first, last)
            iterator iter{ first };
            while (iter != last)
            {
                std::allocator_traits<allocator_type>::destroy(m_allocator, iter);
                ++iter;
                ++count;
            }

            // move remaining objects into empty space
            // this moves memory in range [last, end()] to addres pointed by `first`, that was already released
            // NOLINTNEXTLINE(readability-suspicious-call-argument)
            std::move(last, end(), first);

            m_size -= count;
            return first;
        }

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
        constexpr auto erase(const_iterator first, const_iterator last) -> iterator
        {
            return erase(const_cast<iterator>(first), const_cast<iterator>(last));
        }

        /**
         * @brief Appends a copy of \p value at the end of the container
         *
         * @param[in] value the value of the element to append
         */
        constexpr void push_back(const T& value)
        {
            if (m_size >= m_capacity)
            {
                reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
            }

            std::allocator_traits<allocator_type>::construct(m_allocator, end(), value);
            ++m_size;
        }

        /**
         * @brief Appends a copy of \p value at the end of the container
         *
         * @param[in] value the value of the element to append
         */
        constexpr void push_back(T&& value)
        {
            // Some implementations throw std::lengt_error when push_back causes a reallocation that exceeds mas_size()
            if (m_size >= m_capacity)
            {
                reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
            }

            std::allocator_traits<allocator_type>::construct(m_allocator, end(), std::move(value));
            ++m_size;
        }

        /**
         * @brief Removes the last element of the container
         *
         * @note iterators and references to the last element are invalidated
         */
        constexpr void pop_back()
        {
            if (m_size > 0)
            {
                std::allocator_traits<allocator_type>::destroy(m_allocator, end());
                --m_size;
            }
        }

        /**
         * @brief Resizez the container to contain \p count elements
         *        if \p count is equal to current size, does nothing
         *        if current size is greater than \p count , container size is reduced
         *        if current size is less than \p count , additional copies of T() are appended
         *
         * @param[in] count new size of the container
         */
        constexpr void resize(size_type count)
        {
            resize(count, T{});
        }

        /**
         * @brief Resizes the container to contain \p count elements
         *        if \p count is equal to current size, does nothing
         *        if current size is greater than \p count , container size is reduced
         *        if current size is less than \p count , additional copies of \p value are appended
         *
         * @param[in] count new size of the container
         * @param[in] value the value to initialize the new element with
         */
        constexpr void resize(size_type count, const value_type& value)
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

        /**
         * @brief Exchanges content of current container with \p other container
         *
         * @param[in] other container to exchange content with
         */
        constexpr void swap(dsa::Vector<T>& other) noexcept
        {
            std::swap(*this, other);
        }

    private:

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

        /**
         * @brief Function increase memory allocation of the container to hold \p new_cap number of elements
         *
         * @param[in] new_cap new capacity of container as maximum number of elements the container can store
         *
         * @note After reallocation all iterators and all references are invalidated
         */
        void reallocate(size_type new_cap)
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

        /**
         * @brief Destroys all objects in container and deallocates memory
         */
        void clear_allocation()
        {
            if (m_data)
            {
                //clear();
                iterator iter{ begin() };
                while (iter != end())
                {
                    std::allocator_traits<allocator_type>::destroy(m_allocator, iter);
                    ++iter;
                }
                std::allocator_traits<allocator_type>::deallocate(m_allocator, m_data, m_capacity);
                m_capacity = 0;
                //m_size = 0;
            }
        }
    };

    /**
     * @brief Exchanges content of two Vector containers
     *
     * @tparam T data type stored in containers
     * @param[in] vector1 container to swap content
     * @param[in] vector2 container to swap content
     */
    template<typename T>
    void swap(dsa::Vector<T>& vector1, dsa::Vector<T>& vector2) noexcept
    {
        if (vector1 != vector2)
        {
            std::swap(vector1, vector2);
        }
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
