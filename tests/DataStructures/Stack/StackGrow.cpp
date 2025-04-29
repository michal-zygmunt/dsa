/**
 * @file StackGrow.cpp
 * @brief This file tests functions increasing Stack length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "Stack.h"

int main()
{
    std::cout << "Start StackGrow test:\n";

    bool res{};
    std::initializer_list<int> expected{ 10, 20, 30, 40 };

    Stack<int> s1 = Stack<int>(40);
    s1.push(30);
    s1.push(20);
    s1.push(10);
    res = if_error(s1, expected);
    std::cout << "Stack:\t\t" << s1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Stack<int> s2 = Stack<int>(40);
    s2.push_range({ 30, 20, 10 });
    res = if_error(s2, expected);
    std::cout << "Stack:\t\t" << s2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
