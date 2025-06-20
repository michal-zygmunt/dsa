/**
 * @file StackGet.cpp
 * @brief This file tests accessing values of Stack Nodes
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
    std::cout << "Start StackGet test:\n";

    std::initializer_list<int> expected{ 0,10,20 };

    Stack<int> s1 = Stack<int>({ 20, 10, 0 });
    auto top = s1.top();
    tests::compare("Stack s1 top", top, expected.begin()[0]);
    tests::compare("Stack s1", s1, expected);

    Stack<int> s2 = Stack<int>({ 20, 10, 0 });
    top = s2.top();
    tests::compare("Stack s2 top", top, expected.begin()[0]);
    tests::compare("Stack s2", s2, expected);

    const Stack<int> s3 = Stack<int>({ 20, 10, 0 });
    top = s3.top();
    tests::compare("Stack s3 top", top, expected.begin()[0]);
    tests::compare("Stack s3", s3, expected);

    return tests::failed;
}
