/**
 * @file StackOperators.cpp
 * @brief This file tests overloading operators of Stack
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/Stack.h"

int main()
{
    std::cout << "Start StackOperators test:\n";

    dsa::Stack<int> s1({ 1,2,3 });
    dsa::Stack<int> s2({ 4,5,6 });
    dsa::Stack<int> s3({ 1, 2, 3, 4 });
    std::cout << "Stack s1:\t" << s1 << '\n';
    std::cout << "Stack s2:\t" << s2 << '\n';
    std::cout << "Stack s3:\t" << s3 << "\n\n";

    std::cout << "Compare operators for objects of the same size\n\n";

    tests::compare("Operator ==", s1 == s1, true);

    tests::compare("Operator !=", s1 != s2, true);

    tests::compare("Operator <", s1 < s2, true);

    tests::compare("Operator >", s2 > s1, true);

    tests::compare("Operator <=", s1 <= s2, true);

    tests::compare("Operator <=", s2 >= s1, true);

    std::cout << "Compare operators for objects of different size\n\n";

    tests::compare("Operator ==", s1 == s3, false);

    tests::compare("Operator !=", s1 != s3, true);

    tests::compare("Operator <", s3 < s2, true);

    tests::compare("Operator >", s3 > s1, true);

    tests::compare("Operator <=", s1 <= s3, true);

    tests::compare("Operator >=", s2 >= s3, true);

    return tests::failed;
}
