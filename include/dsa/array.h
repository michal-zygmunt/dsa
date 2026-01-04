/**
 * @file array.h
 * @brief This file contains implementation of Array class
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <iterator>

namespace dsa
{

    /**
     * @brief Implements Array class template for fixed size container
     *
     * @tparam T type of data stored in container
     * @tparam N number of elements in container
     *
     * @todo add non-member to_array()
     */
    template<typename T, std::size_t N>
    struct Array
    {
        /**
         * @brief Alias for data type used in class
         *
         * @tparam T data type
         */
        using value_type = T;

        /**
         * @brief Alias for size type used in class
         *
         * @tparam T size type
         */
        using size_type = std::size_t;

        /**
         * @brief Alias for pointer to data type used in class
         *
         * @tparam T* pointer to data type
         */
        using pointer = value_type*;

        /**
         * @brief Alias for const pointer to data type used in class
         *
         * @tparam T* pointer to data type
         */
        using const_pointer = const value_type*;

        /**
         * @brief Alias for reference to data type used in class
         *
         * @tparam T& reference to data type
         */
        using reference = value_type&;

        /**
         * @brief Alias for const reference to data type used in class
         *
         * @tparam T& const reference to data type
         */
        using const_reference = const value_type&;

        /**
         * @brief Alias for iterator to data type used in class
         */
        using iterator = value_type*;

        /**
         * @brief Alias for const iterator to data type used in class
         */
        using const_iterator = const value_type*;

        /**
         * @brief Alias for reverse_iterator to data type used in class
         */
        using reverse_iterator = std::reverse_iterator<iterator>;

        /**
         * @brief Alias for const reverse_iterator to data type used in class
         */
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        /**
         * @brief Returns a reference to Array element at \p pos index.
         *        If \p pos is outside of container range, an exception std::out_of_range is thrown.
         *
         * @param[in] pos index of element to return
         * @return reference to Array element at \p pos index
         */
        [[nodiscard]] constexpr auto at(size_type pos) -> reference
        {
            if (pos >= N)
            {
                throw std::out_of_range("Pos argument outside of container range");
            }

            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
            return m_data[pos];
        }

        /**
         * @brief Returns a const_reference to Array element at \p pos index.
         *        If \p pos is outside of container range, an exception std::out_of_range is thrown.
         *
         * @param[in] pos index of element to return
         * @return const_reference to Array element at \p pos index
         */
        [[nodiscard]] constexpr auto at(size_type pos) const -> const_reference
        {
            if (pos >= N)
            {
                throw std::out_of_range("Pos argument outside of container range");
            }

            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
            return m_data[pos];
        }

        /**
         * @brief Returns a reference to Array element at \p pos index.
         *        If \p pos is outside of container range, undefined behaviour occurs.
         *
         * @param[in] pos index of element to return
         * @return reference to Array element
         */
        [[nodiscard]] constexpr auto operator[](size_type pos) -> reference
        {
            // Same semantics as std::array::operator[], no bounds checking
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
            return m_data[pos];
        }

        /**
         * @brief Returns a const_reference to Array element at \p pos index.
         *        If \p pos is outside of container range, undefined behaviour occurs.
         *
         * @param[in] pos index of element to return
         * @return const_reference to Array element
         */
        [[nodiscard]] constexpr auto operator[](size_type pos) const -> const_reference
        {
            // Same semantics as std::array::operator[], no bounds checking
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
            return m_data[pos];
        }

        /**
         * @brief Returns reference to first Arary element
         *
         * @return reference to first element
         */
        [[nodiscard]] constexpr auto front() -> reference
        {
            return m_data[0];
        }

        /**
         * @brief Returns const_reference to first Arary element
         *
         * @return const_reference to first element
         */
        [[nodiscard]] constexpr auto front() const -> const_reference
        {
            return m_data[0];
        }

        /**
         * @brief Returns reference to last Arary element
         *
         * @return reference to last element
         */
        [[nodiscard]] constexpr auto back() -> reference
        {
            return m_data[N - 1];
        }

        /**
         * @brief Returns const_reference to last Arary element
         *
         * @return const_reference to last element
         */
        [[nodiscard]] constexpr auto back() const -> const_reference
        {
            return m_data[N - 1];
        }

        /**
         * @brief Returns pointer to underlying array container
         *
         * @return pointer to underlaying array container
         */
        [[nodiscard]] constexpr auto data() noexcept -> pointer
        {
            return &m_data[0];
        }

        /**
         * @brief Returns const_pointer to underlying array container
         *
         * @return const_pointer to underlaying array container
         */
        [[nodiscard]] constexpr auto data() const noexcept -> const_pointer
        {
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
            return &m_data[0];
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
            return &m_data[0];
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
            return &m_data[0];
        }

        /**
         * @brief Returns iterator past last element of underlaying array structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return iterator past last element
         */
        [[nodiscard]] constexpr auto end() noexcept -> iterator
        {
            return &m_data[N];
        }

        /**
         * @brief Returns const_iterator past last element of underlaying array structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return const_iterator past last element
         */
        [[nodiscard]] constexpr auto end() const noexcept -> const_iterator
        {
            return &(m_data[N]);
        }

        /**
         * @brief Returns const_iterator past last element of underlaying array structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return const_iterator past last element
         */
        [[nodiscard]] constexpr auto cend() const noexcept -> const_iterator
        {
            return &(m_data[N]);
        }

        /**
         * @brief Returns reverse_iterator to the first element of reversed underlaying array structure
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return reverse_iterator to the first element
         */
        [[nodiscard]] constexpr auto rbegin() noexcept -> reverse_iterator
        {
            return reverse_iterator(end());
        }

        /**
         * @brief Returns const_reverse_iterator to the first element of reversed underlaying array structure
         *
         * @note If container is empty, returned iterator will be equal to end()
         *
         * @return const_reverse_iterator to the first element
         */
        [[nodiscard]] constexpr auto rbegin() const noexcept -> const_reverse_iterator
        {
            return const_reverse_iterator(end());
        }

        /**
         * @brief Returns const_reverse_iterator to the first element of reversed underlaying array structure
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
         * @brief Returns reverse_iterator past the last element of reversed underlaying array structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return reverse_iterator to the element after the last element
         */
        [[nodiscard]] constexpr auto rend() noexcept -> reverse_iterator
        {
            return reverse_iterator(begin());
        }

        /**
         * @brief Returns const_reverse_iterator past the last element of reversed underlaying array structure
         *
         * @note Iterator act as a sentinel, it is not guaranteed to be dereferencable
         *
         * @return const_reverse_iterator to the element after the last element
         */
        [[nodiscard]] constexpr auto rend() const noexcept -> const_reverse_iterator
        {
            return const_reverse_iterator(begin());
        }

        /**
         * @brief Returns const_reverse_iterator past the last element of reversed underlaying array structure
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
        [[nodiscard]] constexpr auto empty() const noexcept -> bool
        {
            return N == 0;
        }

        /**
         * @brief Returns number of elements in container
         *
         * @return size_type number of elements in container
         */
        [[nodiscard]] constexpr auto size() const noexcept -> size_type
        {
            return N;
        }

        /**
         * @brief Returns maximum number of elements container can hold
         *
         * @return size_type maximum number of elements
         */
        [[nodiscard]] constexpr auto max_size() const noexcept -> size_type
        {
            return N;
        }

        /**
         * @brief Assigns \p value to all elements of the container
         *
         * @param[in] value to assign to all elements of container
         */
        void fill(const value_type& value)
        {
            for (size_type i = 0; i < size(); i++)
            {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
                m_data[i] = value;
            }
        }

        /**
         * @brief Exchanges content of current container with \p other container
         *
         * @param[in] other container to exchange content with
         */
        constexpr void swap(Array<T, N>& other) noexcept
        {
            if (*this != other)
            {
                std::swap(m_data, other.m_data);
            }
        }

        /**
         * @brief Underlaying fixed size array containing all elements
         *        Conditional size is used to handle zero sized array without template specialization
         */
         // Public for aggregate initialization, same as std::array
         // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays, modernize-avoid-c-arrays, misc-non-private-member-variables-in-classes)
        value_type m_data[N == 0 ? 1 : N]{};
    };

    /**
     * @brief Provide access to Ith element of an array
     *
     * @tparam I index of element in container
     * @tparam T data type stored in container
     * @tparam N number of elements in container
     * @param[in] array container to extract element from
     * @return T& reference to Ith element of array container
     */
    template<std::size_t I, typename T, std::size_t N>
    constexpr auto get(Array<T, N>& array) noexcept -> T&
    {
        static_assert(I < N, "Index out of range in dsa::Array::get");
        return array[I];
    }

    /**
     * @brief Provide access to Ith element of an array
     *
     * @tparam I index of element in container
     * @tparam T data type stored in container
     * @tparam N number of elements in container
     * @param[in] array container to extract element from
     * @return const T& reference to Ith element of array container
     */
    template<std::size_t I, typename T, std::size_t N>
    constexpr auto get(const Array<T, N>& array) noexcept -> const T&
    {
        static_assert(I < N, "Index out of range in dsa::Array::get");
        return array[I];
    }

    /**
     * @brief Provide access to Ith element of an array
     *
     * Intentionally not moving entire parameter array.
     * This overload of get<I>(dsa::Array&&) returns an rvalue reference to an element,
     * matching the behaviour of std::get<I>(std::array&&) in C++ standard library.
     * Only the selected element is moved from std::move(array[I]), not the whole array.
     *
     * @tparam I index of element in container
     * @tparam T data type stored in container
     * @tparam N number of elements in container
     * @param[in] array container to extract element from
     * @return T&& reference to Ith element of array container
     */
    template<std::size_t I, typename T, std::size_t N>
    // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
    constexpr auto get(Array<T, N>&& array) noexcept -> T&&
    {
        static_assert(I < N, "Index out of range in dsa::Array::get");
        return std::move(array[I]);
    }

    /**
     * @brief Provide access to Ith element of an array
     *
     * @tparam I index of element in container
     * @tparam T data type stored in container
     * @tparam N number of elements in container
     * @param[in] array container to extract element from
     * @return const T&& reference to Ith element of array container
     */
    template<std::size_t I, typename T, std::size_t N>
    constexpr auto get(const Array<T, N>&& array) noexcept -> const T&&
    {
        static_assert(I < N, "Index out of range in dsa::Array::get");
        return std::move(array[I]);
    }

    /**
     * @brief Exchanges content of two Array containers
     *
     * @tparam T data type stored in containers
     * @tparam N number of elements in containers
     * @param[in] array1 container to swap content
     * @param[in] array2 container to swap content
     */
    template<typename T, std::size_t N>
    void swap(Array<T, N>& array1, Array<T, N>& array2) noexcept
    {
        array1.swap(array2);
    }

    /**
     * @brief Overloads operator to print all elements of Array
     *
     * @tparam T data type stored in container
     * @param[in,out] out reference to output stream
     * @param[in] array Array to print
     * @return std::ostream&
     */
    template<typename T, std::size_t N>
    auto operator<<(std::ostream& out, const Array<T, N>& array) -> std::ostream&
    {
        for (size_t i = 0; i < N; i++)
        {
            out << array[i] << ' ';
        }

        return out;
    }

    /**
     * @brief The relational operator compares two Array objects
     *
     * @param[in] array1 input container
     * @param[in] array2 input container
     * @retval true if containers are equal
     * @retval false if containers are not equal
     */
    template<typename T, std::size_t N>
    auto operator==(const Array<T, N>& array1, const Array<T, N>& array2) -> bool
    {
        auto array1_iter = array1.cbegin();
        auto array2_iter = array2.cbegin();

        for (size_t i = 0; i < N; i++)
        {
            if (*array1_iter != *array2_iter)
            {
                return false;
            }

            array1_iter++;
            array2_iter++;
        }

        return true;
    }

    /**
     * @brief The relational operator compares two Array objects
     *
     * @param[in] array1 input container
     * @param[in] array2 input container
     * @retval -1 if the content of \p array1 is lexicographically lesser than the content of \p array2
     * @retval  0 if the content of \p array1 and \p array2 is equal
     * @retval +1 if the content of \p array1 is lexicographically greater than the content of \p array2
     */
    template<typename T, std::size_t N>
    auto operator<=>(const Array<T, N>& array1, const Array<T, N>& array2)
    {
        auto array1_iter = array1.cbegin();
        auto array2_iter = array2.cbegin();

        for (size_t i = 0; i < N; i++)
        {
            if (*array1_iter < *array2_iter)
            {
                return std::strong_ordering::less;
            }
            if (*array1_iter > *array2_iter)
            {
                return std::strong_ordering::greater;
            }

            array1_iter++;
            array2_iter++;
        }

        return std::strong_ordering::equivalent;
    }
}

namespace std
{
    /*
    * These are explicit specializations of standard templates 'tuple_size' and 'tuple_element'
    * for a user-defined type dsa::Array. This is allowed by C++ standard and required
    * to enable structured bindings and tuple-like behaviour.
    *
    * No new symbols or modification of standard library behaviour was introduced,
    * only providing valid specialization for user-defined type.
    */
    // NOLINTBEGIN(cert-dcl58-cpp)

    /// @cond SPECIALIZATION
    /**
     * @brief Provides compile-time access to the number of elements in an dsa::Array
     *
     * @tparam T data type stored in container
     * @tparam N number of elements in container
     *
     * @see https://en.cppreference.com/w/cpp/container/array/tuple_size.html
     */
    template<typename T, std::size_t N>
    struct tuple_size <dsa::Array<T, N>> : std::integral_constant<std::size_t, N>
    {
    };
    /// @endcond

    /// @cond SPECIALIZATION
    /**
     * @brief Provides compile-time access to the indexes of the elements in dsa::Array
     *
     * @tparam I index of element in container
     * @tparam T data type stored in container
     * @tparam N number of elements in container
     *
     * @see https://en.cppreference.com/w/cpp/container/array/tuple_element.html
     */
    template<std::size_t I, typename T, std::size_t N>
    struct tuple_element<I, dsa::Array<T, N>>
    {
        /**
         * @brief Data type of element stored in container
         *        Required to assign template type to member field of std::tuple_element<I,T>::type
         */
        using type = T;
    };
    /// @endcond

    namespace ranges
    {
        /*
        * These are explicit specializations of range semantics for a user-defined type dsa::Array
        * specifically to be recognized as 'borrowed range' or 'view'
        */

        /// @cond SPECIALIZATION
        /**
         * @brief Specialization of std::ranges::enable_borrowed_range for dsa::Array
         *
         * Declaring type as a borrowed range require the iterators to remain usable
         * even after the original object has been moved away
         *
         * @tparam T data type stored in container
         * @tparam N number of elements in container
         *
         * @see https://en.cppreference.com/w/cpp/ranges/borrowed_range.html
         */
        template<typename T, std::size_t N>
        inline constexpr bool enable_borrowed_range<dsa::Array<T, N>> = true;
        /// @endcond

        /// @cond SPECIALIZATION
        /**
         * @brief Specialization of std::ranges::enable_view for dsa::Array
         *
         * Declaring type as a view allows it to be used with std::views pipelines
         *
         * @tparam T data type stored in container
         * @tparam N number of elements in container
         *
         * @see https://en.cppreference.com/w/cpp/ranges/view.html
         */
        template<typename T, std::size_t N>
        inline constexpr bool enable_view<dsa::Array<T, N>> = true;
        /// @endcond

        /// @cond SPECIALIZATION
        /**
         * @brief Specialization of std::ranges::enable_view for dsa::Array
         *
         * Declaring type as a view allows it to be used with std::views pipelines
         *
         * @tparam T data type stored in container
         * @tparam N number of elements in container
         *
         * @see https://en.cppreference.com/w/cpp/ranges/view.html
         */
        template<typename T, std::size_t N>
        inline constexpr bool enable_view<const dsa::Array<T, N>> = true;
        /// @endcond
    }

    // NOLINTEND(cert-dcl58-cpp)
}

#endif // !ARRAY_H
