/**
 * @file StackCtors.cpp
 * @brief This file tests Stack constructors
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
    std::cout << "Start StackCtors test:\n";

    bool res{};
    std::initializer_list<int> expected{ 20,10,0 };

    std::cout << "Default ctor\n";
    Stack<int> s1;
    s1.push(0);
    s1.push(10);
    s1.push(20);
    res = if_error(s1, expected);
    std::cout << "Stack s1:\t" << s1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Value ctor\n";
    Stack<int> s2(0);
    s2.push(10);
    s2.push(20);
    res = if_error(s2, expected);
    std::cout << "Stack s2:\t" << s2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Initializer list ctor\n";
    Stack<int> s3({ 0, 10, 20 });
    res = if_error(s3, expected);
    std::cout << "Stack s3:\t" << s3 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Copy ctor\n";
    Stack<int> s4{ s1 };
    res = if_error(s4, expected);
    std::cout << "Stack s4:\t" << s4 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Copy assignment ctor\n";
    Stack<int> s5;
    s5.push(1);
    s5.push(2);
    s5.push(3);
    s5.push(4);
    s5.push(5);
    s5 = s1;
    res = if_error(s5, expected);
    std::cout << "Stack s5:\t" << s5 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Move ctor\n";
    Stack<int> l6 = std::move(Stack<int>(s1));
    res = if_error(l6, expected);
    std::cout << "Stack l6:\t" << l6 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    std::cout << "Move assignment ctor\n";
    Stack<int> l7(0);
    l7 = std::move(Stack<int>(s1));
    res = if_error(l7, expected);
    std::cout << "Stack l7:\t" << l7 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
