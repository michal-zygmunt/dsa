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

    bool res{};
    std::initializer_list<int> expected{ 50,10,0 };

    Stack<int> s1 = Stack<int>({ 0,10,20 });
    s1.top() = 50;
    res = if_error(s1, expected);
    std::cout << "Stack:\t\t" << s1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Stack<int> s2 = Stack<int>({ 0,10,20 });
    Stack<int> s3 = Stack<int>({ 0,10,50 });
    s2.swap(s3);
    res = if_error(s2, expected);
    std::cout << "Stack:\t\t" << s2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Stack<int> s4 = Stack<int>({ 0,10,50 });
    s4.swap(s4);
    res = if_error(s4, expected);
    std::cout << "Stack:\t\t" << s4 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
