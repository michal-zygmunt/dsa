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
#include <string>

namespace tests
{

    void print_err_msg(const std::string& message, const std::exception* exception)
    {
        std::cerr << message;
        if (static_cast<bool>(exception))
        {
            std::cerr << " | " << exception->what();
        }

        std::cerr << '\n';
    }

}
