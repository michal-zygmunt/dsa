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

    bool res{};
    std::initializer_list<int> expected{ 0,10,20 };

    Stack<int> s1 = Stack<int>({ 20, 10, 0 });
    size_t s1_size = s1.size();
    std::cout << "Stack s1:\t";
    for (int i = 0; i < s1_size; i++)
    {
        auto temp = s1.top();
        if (temp)
        {
            std::cout << temp->value() << ' ';
            res = if_error(temp->value(), expected.begin()[i]);
            s1.pop();
        }
    }
    std::cout << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Stack<int> s2 = Stack<int>({ 20, 10, 0 });
    auto top = s2.top()->value();
    res = 0;
    if (if_error(top, expected.begin()[0]))
    {
        res = 1;
    }
    std::cout << "Stack s2 top: " << top << '\n';
    std::cout << "Expected top: " << expected.begin()[0] << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    const Stack<int> s3 = Stack<int>({ 20, 10, 0 });
    top = s3.top()->value();
    res = 0;
    if (if_error(top, expected.begin()[0]))
    {
        res = 1;
    }
    std::cout << "Stack s3 top: " << top << '\n';
    std::cout << "Expected top: " << expected.begin()[0] << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
