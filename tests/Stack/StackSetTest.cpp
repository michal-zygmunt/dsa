/**
 * @file StackSet.cpp
 * @brief This file tests setting values of Stack
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
    std::cout << "Start StackSet test:\n";

    std::initializer_list<int> expected{ 50,10,0 };

    dsa::Stack<int> s1 = dsa::Stack<int>({ 0,10,20 });
    s1.top() = 50;
    tests::compare("Stack s1", s1, expected);

    dsa::Stack<int> s2 = dsa::Stack<int>({ 0,10,20 });
    dsa::Stack<int> s3 = dsa::Stack<int>({ 0,10,50 });
    s2.swap(s3);
    tests::compare("Stack s2", s2, { 50,10,0 });
    tests::compare("Stack s3", s3, { 20,10,0 });

    dsa::Stack<int> s4 = dsa::Stack<int>({ 0,10,50 });
    s4.swap(s4);
    tests::compare("Stack s4", s4, expected);

    return tests::failed;
}
