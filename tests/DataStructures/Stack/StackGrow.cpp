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

    std::initializer_list<int> expected{ 10, 20, 30, 40 };

    Stack<int> s1 = Stack<int>(40);
    s1.push(30);
    s1.push(20);
    s1.push(10);
    tests::compare("Stack s1", s1, expected);

    Stack<int> s2 = Stack<int>(40);
    s2.push_range({ 30, 20, 10 });
    tests::compare("Stack s2", s2, expected);

    return tests::failed;
}
