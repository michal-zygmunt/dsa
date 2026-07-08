/**
 * @file priority_queue_swap_test.cpp
 * @brief This file tests functions swapping PriorityQueue objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2026 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/queue.h"
#include "dsa/vector.h"

#include <exception>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start priority_queue_swap_test:\n";

        const std::initializer_list<int> il_1{ 1, 2, 5, 4, 3 };
        const std::initializer_list<int> il_2{ 10, 20, 50, 40, 30 };

        const std::initializer_list<int> il_1_desc{ 5, 4, 3, 2, 1 };
        const std::initializer_list<int> il_2_desc{ 50, 40, 30, 20, 10 };

        const std::initializer_list<int> il_1_asc{ 1, 2, 3, 4, 5 };
        const std::initializer_list<int> il_2_asc{ 10, 20, 30, 40, 50 };


        dsa::PriorityQueue<int> priority_queue1(il_1.begin(), il_1.end());
        dsa::PriorityQueue<int> priority_queue2(il_2.begin(), il_2.end());
        priority_queue1.swap(priority_queue2);
        const std::initializer_list<int> expected1 = il_2_desc;
        tests::compare("PriorityQueue1", priority_queue1, expected1);
        const std::initializer_list<int> expected2 = il_1_desc;
        tests::compare("PriorityQueue2", priority_queue2, expected2);

        dsa::PriorityQueue<int> priority_queue3 = dsa::PriorityQueue<int>(il_1.begin(), il_1.end());
        dsa::PriorityQueue<int> priority_queue4;
        priority_queue3.swap(priority_queue4);
        const std::initializer_list<int> expected3 = { };
        tests::compare("PriorityQueue3", priority_queue3, expected3);
        const std::initializer_list<int> expected4 = il_1_desc;
        tests::compare("PriorityQueue4", priority_queue4, expected4);

        dsa::PriorityQueue<int> priority_queue5 = dsa::PriorityQueue<int>(il_1.begin(), il_1.end());
        dsa::PriorityQueue<int> priority_queue6 = dsa::PriorityQueue<int>(il_2.begin(), il_2.end());
        dsa::swap(priority_queue5, priority_queue6);
        const std::initializer_list<int> expected5 = il_2_desc;
        tests::compare("PriorityQueue5", priority_queue5, expected5);
        const std::initializer_list<int> expected6 = il_1_desc;
        tests::compare("PriorityQueue6", priority_queue6, expected6);

        dsa::PriorityQueue<int> priority_queue7 = dsa::PriorityQueue<int>(il_1.begin(), il_1.end());
        dsa::PriorityQueue<int> priority_queue8;
        dsa::swap(priority_queue7, priority_queue8);
        const std::initializer_list<int> expected7 = { };
        tests::compare("PriorityQueue7", priority_queue7, expected7);
        const std::initializer_list<int> expected8 = il_1_desc;
        tests::compare("PriorityQueue8", priority_queue8, expected8);

        // descending order

        dsa::PriorityQueue<int, dsa::Vector<int>, std::less<>> priority_queue9(il_1.begin(), il_1.end(), std::less<>());
        dsa::PriorityQueue<int, dsa::Vector<int>, std::less<>> priority_queue10(il_2.begin(), il_2.end(), std::less<>());
        priority_queue9.swap(priority_queue10);
        const std::initializer_list<int> expected9 = il_2_desc;
        tests::compare("PriorityQueue9", priority_queue9, expected9);
        const std::initializer_list<int> expected10 = il_1_desc;
        tests::compare("PriorityQueue10", priority_queue10, expected10);

        dsa::PriorityQueue<int, dsa::Vector<int>, std::less<>> priority_queue11(il_1.begin(), il_1.end(), std::less<>());
        dsa::PriorityQueue<int, dsa::Vector<int>, std::less<>> priority_queue12;
        priority_queue11.swap(priority_queue12);
        const std::initializer_list<int> expected11 = { };
        tests::compare("PriorityQueue11", priority_queue11, expected11);
        const std::initializer_list<int> expected12 = il_1_desc;
        tests::compare("PriorityQueue12", priority_queue12, expected12);

        dsa::PriorityQueue<int, dsa::Vector<int>, std::less<>> priority_queue13(il_1.begin(), il_1.end(), std::less<>());
        dsa::PriorityQueue<int, dsa::Vector<int>, std::less<>> priority_queue14(il_2.begin(), il_2.end(), std::less<>());
        dsa::swap(priority_queue13, priority_queue14);
        const std::initializer_list<int> expected13 = il_2_desc;
        tests::compare("PriorityQueue13", priority_queue13, expected13);
        const std::initializer_list<int> expected14 = il_1_desc;
        tests::compare("PriorityQueue14", priority_queue14, expected14);

        dsa::PriorityQueue<int, dsa::Vector<int>, std::less<>> priority_queue15(il_1.begin(), il_1.end(), std::less<>());
        dsa::PriorityQueue<int, dsa::Vector<int>, std::less<>> priority_queue16;
        dsa::swap(priority_queue15, priority_queue16);
        const std::initializer_list<int> expected15 = { };
        tests::compare("PriorityQueue15", priority_queue15, expected15);
        const std::initializer_list<int> expected16 = il_1_desc;
        tests::compare("PriorityQueue16", priority_queue16, expected16);

        // ascending order

        dsa::PriorityQueue<int, dsa::Vector<int>, std::greater<>> priority_queue17(il_1.begin(), il_1.end(), std::greater<>());
        dsa::PriorityQueue<int, dsa::Vector<int>, std::greater<>> priority_queue18(il_2.begin(), il_2.end(), std::greater<>());
        priority_queue17.swap(priority_queue18);
        const std::initializer_list<int> expected17 = il_2_asc;
        tests::compare("PriorityQueue17", priority_queue17, expected17);
        const std::initializer_list<int> expected18 = il_1_asc;
        tests::compare("PriorityQueue18", priority_queue18, expected18);

        dsa::PriorityQueue<int, dsa::Vector<int>, std::greater<>> priority_queue19(il_1.begin(), il_1.end(), std::greater<>());
        dsa::PriorityQueue<int, dsa::Vector<int>, std::greater<>> priority_queue20;
        priority_queue19.swap(priority_queue20);
        const std::initializer_list<int> expected19 = { };
        tests::compare("PriorityQueue19", priority_queue19, expected19);
        const std::initializer_list<int> expected20 = il_1_asc;
        tests::compare("PriorityQueue20", priority_queue20, expected20);

        dsa::PriorityQueue<int, dsa::Vector<int>, std::greater<>> priority_queue21(il_1.begin(), il_1.end(), std::greater<>());
        dsa::PriorityQueue<int, dsa::Vector<int>, std::greater<>> priority_queue22(il_2.begin(), il_2.end(), std::greater<>());
        dsa::swap(priority_queue21, priority_queue22);
        const std::initializer_list<int> expected21 = il_2_asc;
        tests::compare("PriorityQueue21", priority_queue21, expected21);
        const std::initializer_list<int> expected22 = il_1_asc;
        tests::compare("PriorityQueue22", priority_queue22, expected22);

        dsa::PriorityQueue<int, dsa::Vector<int>, std::greater<>> priority_queue23(il_1.begin(), il_1.end(), std::greater<>());
        dsa::PriorityQueue<int, dsa::Vector<int>, std::greater<>> priority_queue24;
        dsa::swap(priority_queue23, priority_queue24);
        const std::initializer_list<int> expected23 = { };
        tests::compare("PriorityQueue23", priority_queue23, expected23);
        const std::initializer_list<int> expected24 = il_1_asc;
        tests::compare("PriorityQueue24", priority_queue24, expected24);

        // swap safe type
        static_assert(noexcept(swap(std::declval<dsa::PriorityQueue<int>&>(),
            std::declval<dsa::PriorityQueue<int>&>())));
        // swap throwing type
        static_assert(noexcept(swap(std::declval<dsa::PriorityQueue<tests::ThrowingType>&>(),
            std::declval<dsa::PriorityQueue<tests::ThrowingType>&>())));


        std::cout << "Compare operations results with std container\n\n";

        std::priority_queue<int> std_priority_queue1(il_1.begin(), il_1.end());
        std::priority_queue<int> std_priority_queue2(il_2.begin(), il_2.end());
        std_priority_queue1.swap(std_priority_queue2);
        tests::compare("Queue1 vs std", priority_queue1, std_priority_queue1);
        tests::compare("Queue2 vs std", priority_queue2, std_priority_queue2);

        std::priority_queue<int> std_priority_queue3(il_1.begin(), il_1.end());
        std::priority_queue<int> std_priority_queue4;
        std_priority_queue3.swap(std_priority_queue4);
        tests::compare("Queue3 vs std", priority_queue3, std_priority_queue3);
        tests::compare("Queue4 vs std", priority_queue4, std_priority_queue4);

        std::priority_queue<int> std_priority_queue5(il_1.begin(), il_1.end());
        std::priority_queue<int> std_priority_queue6(il_2.begin(), il_2.end());
        std::swap(std_priority_queue5, std_priority_queue6);
        tests::compare("Queue5 vs std", priority_queue5, std_priority_queue5);
        tests::compare("Queue6 vs std", priority_queue6, std_priority_queue6);

        std::priority_queue<int> std_priority_queue7(il_1.begin(), il_1.end());
        std::priority_queue<int> std_priority_queue8;
        std::swap(std_priority_queue7, std_priority_queue8);
        tests::compare("Queue7 vs std", priority_queue7, std_priority_queue7);
        tests::compare("Queue8 vs std", priority_queue8, std_priority_queue8);

        // descending order

        std::priority_queue<int, std::vector<int>, std::less<>> std_priority_queue9(il_1.begin(), il_1.end(), std::less<>());
        std::priority_queue<int, std::vector<int>, std::less<>> std_priority_queue10(il_2.begin(), il_2.end(), std::less<>());
        std_priority_queue9.swap(std_priority_queue10);
        tests::compare("PriorityQueue9 vs std", priority_queue9, std_priority_queue9);
        tests::compare("PriorityQueue10 vs std", priority_queue10, std_priority_queue10);

        std::priority_queue<int, std::vector<int>, std::less<>> std_priority_queue11(il_1.begin(), il_1.end(), std::less<>());
        std::priority_queue<int, std::vector<int>, std::less<>> std_priority_queue12;
        std_priority_queue11.swap(std_priority_queue12);
        tests::compare("PriorityQueue11 vs std", priority_queue11, std_priority_queue11);
        tests::compare("PriorityQueue12 vs std", priority_queue12, std_priority_queue12);

        std::priority_queue<int, std::vector<int>, std::less<>> std_priority_queue13(il_1.begin(), il_1.end(), std::less<>());
        std::priority_queue<int, std::vector<int>, std::less<>> std_priority_queue14(il_2.begin(), il_2.end(), std::less<>());
        std::swap(std_priority_queue13, std_priority_queue14);
        tests::compare("PriorityQueue13 vs std", priority_queue13, std_priority_queue13);
        tests::compare("PriorityQueue14 vs std", priority_queue14, std_priority_queue14);

        std::priority_queue<int, std::vector<int>, std::less<>> std_priority_queue15(il_1.begin(), il_1.end(), std::less<>());
        std::priority_queue<int, std::vector<int>, std::less<>> std_priority_queue16;
        std::swap(std_priority_queue15, std_priority_queue16);
        tests::compare("PriorityQueue15 vs std", priority_queue15, std_priority_queue15);
        tests::compare("PriorityQueue16 vs std", priority_queue16, std_priority_queue16);

        // ascending order

        std::priority_queue<int, std::vector<int>, std::greater<>> std_priority_queue17(il_1.begin(), il_1.end(), std::greater<>());
        std::priority_queue<int, std::vector<int>, std::greater<>> std_priority_queue18(il_2.begin(), il_2.end(), std::greater<>());
        std_priority_queue17.swap(std_priority_queue18);
        tests::compare("PriorityQueue17 vs std", priority_queue17, std_priority_queue17);
        tests::compare("PriorityQueue18 vs std", priority_queue18, std_priority_queue18);

        std::priority_queue<int, std::vector<int>, std::greater<>> std_priority_queue19(il_1.begin(), il_1.end(), std::greater<>());
        std::priority_queue<int, std::vector<int>, std::greater<>> std_priority_queue20;
        std_priority_queue19.swap(std_priority_queue20);
        tests::compare("PriorityQueue19 vs std", priority_queue19, std_priority_queue19);
        tests::compare("PriorityQueue20 vs std", priority_queue20, std_priority_queue20);

        std::priority_queue<int, std::vector<int>, std::greater<>> std_priority_queue21(il_1.begin(), il_1.end(), std::greater<>());
        std::priority_queue<int, std::vector<int>, std::greater<>> std_priority_queue22(il_2.begin(), il_2.end(), std::greater<>());
        std::swap(std_priority_queue21, std_priority_queue22);
        tests::compare("PriorityQueue21 vs std", priority_queue21, std_priority_queue21);
        tests::compare("PriorityQueue22 vs std", priority_queue22, std_priority_queue22);

        std::priority_queue<int, std::vector<int>, std::greater<>> std_priority_queue23(il_1.begin(), il_1.end(), std::greater<>());
        std::priority_queue<int, std::vector<int>, std::greater<>> std_priority_queue24;
        std::swap(std_priority_queue23, std_priority_queue24);
        tests::compare("PriorityQueue23 vs std", priority_queue23, std_priority_queue23);
        tests::compare("PriorityQueue24 vs std", priority_queue24, std_priority_queue24);

        // swap safe type
        static_assert(noexcept(swap(std::declval<std::priority_queue<int>&>(),
            std::declval<std::priority_queue<int>&>())));
        // swap throwing type
        static_assert(noexcept(swap(std::declval<std::priority_queue<tests::ThrowingType>&>(),
            std::declval<std::priority_queue<tests::ThrowingType>&>())));


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
