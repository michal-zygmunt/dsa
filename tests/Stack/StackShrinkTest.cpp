/**
 * @file StackShrink.cpp
 * @brief This file tests functions decreasing Stack length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/Stack.h"

#include <initializer_list>

int main()
{
    std::cout << "Start StackShrink test:\n";

    std::initializer_list<int> expected{};

    dsa::Stack<int> s1 = dsa::Stack<int>({ 0,10,20,30,40,50 });
    s1.pop();
    s1.pop();
    expected = { 30,20,10,0 };
    tests::compare("Stack s1", s1, expected);

    dsa::Stack<int> s2 = dsa::Stack<int>({ 0,10,20 });
    s2.pop();
    s2.pop();
    s2.pop();
    expected = std::initializer_list<int>{ };
    tests::compare("Stack s2", s2, expected);

    dsa::Stack<int> s3 = dsa::Stack<int>({ 0,10,20 });
    tests::compare("s3.size()", s3.size(), static_cast<size_t>(3));

    dsa::Stack<int> s4 = dsa::Stack<int>();
    s4.pop();
    tests::compare("s4.size()", s4.size(), static_cast<size_t>(0));

    dsa::Stack<int> s5;
    tests::compare("s5.size()", s5.size(), static_cast<size_t>(0));

    return tests::failed;
}