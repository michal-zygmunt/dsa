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
#include "Stack.h"

#include <initializer_list>

int main()
{
    std::cout << "Start StackShrink test:\n";

    bool res{};
    std::initializer_list<int> expected{};

    Stack<int> s1 = Stack<int>({ 0,10,20,30,40,50 });
    s1.pop();
    s1.pop();
    expected = { 30,20,10,0 };
    res = if_error(s1, expected);
    std::cout << "Stack:\t\t" << s1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Stack<int> s2 = Stack<int>({ 0,10,20 });
    s2.pop();
    s2.pop();
    s2.pop();
    expected = std::initializer_list<int>{ };
    res = if_error(s2, expected);
    std::cout << "Stack:\t" << s2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Stack<int> s3 = Stack<int>({ 0,10,20 });
    res = if_error(static_cast<int>(s3.size()), 3);
    std::cout << "Stack size:\t" << s2.size() << '\n';
    std::cout << "Expected:\t" << 0 << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Stack<int> s4 = Stack<int>();
    s4.pop();
    res = if_error(static_cast<int>(s4.size()), 0);
    std::cout << "Stack size:\t" << s4.size() << '\n';
    std::cout << "Expected:\t" << 0 << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    Stack<int> s5;
    res = if_error(s5.empty(), true);
    std::cout << "Stack size:\t" << s5.size() << '\n';
    std::cout << "Expected:\t" << 0 << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}