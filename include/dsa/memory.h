/**
 * @file memory.h
 * @brief This file contains implementation of memory functions
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <memory>

namespace dsa
{
    // custom implementation of make_unique for c++11
#if __cplusplus < 201402L

    // make_unique for single objects

    /**
     * @brief Creates T type object and wraps it std::unique_ptr
     *
     * Function implements std::make_unique from c++14 into c++11.
     * Will work only when T is NOT an array type object (T[])
     *
     * @tparam T type of object created by function
     * @tparam Args argument types for T object constructor
     * @param[in] args arguments used by T object ctor
     * @return std::unique_ptr<T> object of type T
     */
    template<typename T, typename... Args>
    auto make_unique(Args&&... args) -> typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

#else // c++14 and newer

    // use original implementation of std::make_unique when newer c++ version is used 
    // and prevent clang-tidy warning 
    // NOLINTNEXTLINE(misc-unused-using-decls)
    using std::make_unique;

#endif
}

#endif // !MEMORY_H
