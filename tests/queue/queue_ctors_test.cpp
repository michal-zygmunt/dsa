/**
 * @file queue_ctors_test.cpp
 * @brief This file tests Queue constructors
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/list.h"
#include "dsa/queue.h"

#include <deque>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start queue_ctors_test:\n";

        const std::initializer_list<int> expected{ 0, 10, 20 };

        std::cout << "Default ctor\n";
        dsa::Queue<int> queue1;
        queue1.push(0);
        queue1.push(10);
        queue1.push(20);
        tests::compare("Queue1", queue1, expected);

        std::cout << "Value ctor\n";
        dsa::Queue<int> queue2({ 0 });
        queue2.push(10);
        queue2.push(20);
        tests::compare("Queue2", queue2, expected);

        std::cout << "Initializer list ctor\n";
        const dsa::Queue<int> queue3(expected);
        tests::compare("Queue3", queue3, expected);

        std::cout << "Copy ctor\n";
        const dsa::Queue<int> queue4{ queue1 };
        tests::compare("Queue4", queue4, expected);

        std::cout << "Copy assignment ctor\n";
        dsa::Queue<int> queue5;
        queue5.push(1);
        queue5.push(2);
        queue5.push(3);
        queue5.push(4);
        queue5.push(5);
        queue5 = queue1;
        tests::compare("Queue5", queue5, expected);

        std::cout << "Copy self assignment ctor\n";
        dsa::Queue<int> queue6{ dsa::List<int>({0, 10, 20}) };
        auto* pointer6 = &queue6;
        queue6 = *pointer6;
        tests::compare("Queue6", queue6, expected);

        std::cout << "Move ctor\n";
        dsa::Queue<int> temp_1(queue1);
        const dsa::Queue<int> queue7 = std::move(temp_1);
        tests::compare("Queue7", queue7, expected);

        std::cout << "Move assignment ctor\n";
        dsa::Queue<int> temp_2(queue1);
        dsa::Queue<int> queue8;
        queue8.push(0);
        queue8 = std::move(temp_2);
        tests::compare("Queue8", queue8, expected);

        std::cout << "Move self assignment ctor\n";
        dsa::Queue<int> queue9{ dsa::List<int>({0, 10, 20}) };
        auto* pointer9 = &queue9;
        queue9 = std::move(*pointer9);
        tests::compare("Queue9", queue9, expected);

        const dsa::Queue<int> queue10(dsa::List<int>(5));
        const std::initializer_list<int> expected10{ 0, 0, 0, 0, 0 };
        tests::compare("Queue10", queue10, expected10);

        std::cout << "Construct from List using copy ctor\n";
        const dsa::List<int> temp11 = { 10, 20, 30 };
        const dsa::Queue<int> queue11(temp11);
        const std::initializer_list<int> expected11{ 10, 20, 30 };
        tests::compare("Queue11", queue11, expected11);

        std::cout << "Construct from List using move assignment\n";
        dsa::List<int> temp12 = { 10, 20, 30 };
        const dsa::Queue<int> queue12(std::move(temp12));
        const std::initializer_list<int> expected12{ 10, 20, 30 };
        tests::compare("Queue12", queue12, expected12);


        std::cout << "Compare operations results with std container\n\n";

        std::queue<int> std_queue1;
        std_queue1.push(0);
        std_queue1.push(10);
        std_queue1.push(20);
        tests::compare("Queue1 vs std", queue1, std_queue1);

        std::queue<int> std_queue2({ 0 });
        std_queue2.push(10);
        std_queue2.push(20);
        tests::compare("Queue2 vs std", queue2, std_queue2);

        const std::queue<int> std_queue3(expected);
        tests::compare("Queue3 vs std", queue3, std_queue3);

        const std::queue<int> std_queue4{ std_queue1 };
        tests::compare("Queue4 vs std", queue4, std_queue4);

        std::queue<int> std_queue5{ std_queue1 };
        std_queue5.push(1);
        std_queue5.push(2);
        std_queue5.push(3);
        std_queue5.push(4);
        std_queue5.push(5);
        std_queue5 = std_queue1;
        tests::compare("Queue5 vs std", queue5, std_queue5);

        const std::queue<int> std_queue6(std::deque<int>({ 0, 10, 20 }));
        tests::compare("Queue6 vs std", queue6, std_queue6);

        std::queue<int> std_temp_2(std_queue1);
        const std::queue<int> std_queue7 = std::move(std_temp_2);
        tests::compare("Queue7 vs std", queue7, std_queue7);

        std::queue<int> std_temp_8(std_queue1);
        std::queue<int> std_queue8;
        std_queue8 = std::move(std_temp_8);
        tests::compare("Queue8 vs std", queue8, std_queue8);

        const std::queue<int> std_queue10(std::deque<int>(5));
        tests::compare("Queue10 vs std", queue10, std_queue10);

        const std::deque<int> std_temp11 = { 10, 20, 30 };
        const std::queue<int> std_queue11(std_temp11);
        tests::compare("Queue11 vs std", queue11, std_queue11);

        std::deque<int> std_temp12 = { 10, 20, 30 };
        const std::queue<int> std_queue12(std::move(std_temp12));
        tests::compare("Queue12 vs std", queue12, std_queue12);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
