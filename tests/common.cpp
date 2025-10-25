/**
 * @file common.cpp
 * @brief This file implements helper functions for tests
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"

#include <exception>
#include <iostream>
#include <new>
#include <optional>
#include <source_location>
#include <stdexcept>
#include <string>

namespace tests
{

    void print_err_msg(const std::string& message, const std::exception* exception)
    {
        std::cerr << message;
        if (static_cast<bool>(exception))
        {
            std::cerr << exception->what();
        }

        std::cerr << '\n';
    }

    auto handle_exception(const std::optional<std::exception_ptr>& exception,
        const std::source_location& location) -> int
    {
        std::cerr << '[' << location.file_name()
            << '(' << location.line() << ':' << location.column() << ")] "
            << '\'' << location.function_name() << '\'';

        if (exception.has_value())
        {
            try
            {
                std::rethrow_exception(*exception);
            }
            catch (const std::bad_alloc& exc)
            {
                tests::print_err_msg(" | Exception std::bad_alloc: ", &exc);
                return 1;
            }
            catch (const std::runtime_error& exc)
            {
                tests::print_err_msg(" | Exception std::runtime_error: ", &exc);
                return 2;
            }
            catch (const std::exception& exc)
            {
                tests::print_err_msg(" | Exception: ", &exc);
                return 3;
            }
            catch (...)
            {
                tests::print_err_msg(" | Unknown exception type");
                return 4;
            }
        }
        else
        {
            tests::print_err_msg(" | Nullopt exception");
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
            return 5;
        }
    }

}
