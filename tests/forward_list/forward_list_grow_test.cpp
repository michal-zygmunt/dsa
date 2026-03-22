/**
 * @file forward_list_grow_test.cpp
 * @brief This file tests functions increasing ForwardList length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/forward_list.h"

#include <cstddef>
#include <exception>
#include <forward_list>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start forward_list_grow_test:\n";

        dsa::ForwardList<int> list1 = dsa::ForwardList<int>(1, 10);
        auto iterator = list1.insert_after(list1.cbegin(), 20);
        list1.insert_after(iterator, { 30, 40 });
        list1.push_front(0);
        list1.push_front(-10);
        // Try inserting nodes at invalid indexes
        for (const auto& item : { 0, 4, 2, 100 })
        {
            iterator = list1.begin();
            std::advance(iterator, item);
            list1.insert_after(iterator, item);
        }
        const std::initializer_list<int> expected1{ -10, 0, 0, 2, 10, 20, 4, 30, 40 };
        tests::compare("ForwardList1", list1, expected1);

        dsa::ForwardList<int> list2 = dsa::ForwardList<int>(1, 50);
        list2.push_front(40);
        list2.push_front(30);
        list2.push_front(20);
        list2.push_front(10);
        list2.insert_after(list2.cbegin(), 5, 5);
        const std::initializer_list<int> expected2 = { 10, 5, 5, 5, 5, 5, 20, 30, 40, 50 };
        tests::compare("ForwardList2", list2, expected2);

        dsa::ForwardList<int> list3 = dsa::ForwardList<int>(1, 50);
        list3.push_front(40);
        list3.push_front(30);
        list3.push_front(10);
        iterator = list3.insert_after(list3.cbegin(), 20);
        list3.insert_after(iterator, { 1, 2, 3 });
        list3.insert_after(std::next(list3.cbegin(), static_cast<ptrdiff_t>(list3.size() - 1)), 60);
        const std::initializer_list<int> expected3 = { 10, 20, 1, 2, 3, 30, 40, 50, 60 };
        tests::compare("ForwardList3", list3, expected3);

        dsa::ForwardList<int> list4;
        list4.push_front(40);
        list4.push_front(30);
        list4.push_front(10);
        iterator = list4.insert_after(list4.cbegin(), 20);
        const std::initializer_list<int> expected4 = { 10, 20, 30, 40 };
        tests::compare("ForwardList4", list4, expected4);

        dsa::ForwardList<int> list5;
        list5.insert_after(list5.before_begin(), 40);
        list5.insert_after(list5.before_begin(), 30);
        list5.insert_after(list5.cbefore_begin(), 20);
        list5.insert_after(list5.cbefore_begin(), 10);
        const std::initializer_list<int> expected5 = { 10, 20, 30, 40 };
        tests::compare("ForwardList5", list5, expected5);

        dsa::ForwardList<int> list6{ 40 };
        list6.insert_after(list6.before_begin(), 30);
        list6.insert_after(list6.before_begin(), 20);
        list6.insert_after(list6.before_begin(), 10);
        const std::initializer_list<int> expected6 = { 10, 20, 30, 40 };
        tests::compare("ForwardList6", list6, expected6);

        dsa::ForwardList<int> list7{ 40 };
        list7.insert_after(list7.before_begin(), { 10, 20, 30 });
        const std::initializer_list<int> expected7 = { 10, 20, 30, 40 };
        tests::compare("ForwardList7", list7, expected7);

        dsa::ForwardList<int> list8{ 1, 2, 3 };
        auto iter8 = list8.insert_after(list8.end(), { 4, 5, 6 });
        tests::compare("iter8 == nullptr", iter8 == nullptr, true);

        dsa::ForwardList<std::unique_ptr<int>> list9{};
        auto ptr9 = std::make_unique<int>(1);
        list9.insert_after(list9.before_begin(), std::move(ptr9));
        constexpr int expected9{ 1 };
        tests::compare("ForwardList9 front()", *list9.front(), expected9);
        tests::compare("ptr9 == nullptr", ptr9 == nullptr, true);

        dsa::ForwardList<int> list10{};
        const dsa::ForwardList<int> temp10{ 0, 10, 20, 30, 40, 50 };
        auto temp10_it = std::next(temp10.begin(), 3);
        auto list10_it = list10.insert_after(
            list10.before_begin(), std::next(temp10.begin(), 1), std::next(temp10.begin(), 4));
        const std::initializer_list<int> expected10{ 10, 20, 30 };
        tests::compare("ForwardList10", list10, expected10);
        tests::compare("ForwardList10 it", *list10_it, *temp10_it);

        dsa::ForwardList<int> list11{ 0, 10, 20 };
        const dsa::ForwardList<int> temp11{ 30, 40, 50 };
        auto temp11_it = std::next(temp11.begin(), 2);
        auto list11_it = list11.insert_after(std::next(list11.begin(), 2), temp11.begin(), temp11.end());
        const std::initializer_list<int> expected11{ 0, 10, 20, 30, 40, 50 };
        tests::compare("ForwardList11", list11, expected11);
        tests::compare("ForwardList11 it", *list11_it, *temp11_it);

        dsa::ForwardList<int> list12{};
        list12.emplace_front(30);
        list12.emplace_front(20);
        list12.emplace_front(10);
        list12.emplace_front(5);
        list12.emplace_front(0);
        const std::initializer_list<int> expected12 = { 0, 5, 10, 20, 30 };
        tests::compare("ForwardList12", list12, expected12);

        dsa::ForwardList<int> list13{ 0, 10, 20, 30 };
        list13.emplace_after(list13.before_begin(), -10);
        const std::initializer_list<int> expected13 = { -10, 0, 10, 20, 30 };
        tests::compare("ForwardList13", list13, expected13);

        dsa::ForwardList<int> list14{ 0, 10, 20, 30 };
        auto iter14 = list14.begin();
        std::advance(iter14, 2);
        list14.emplace_after(iter14, 25);
        const std::initializer_list<int> expected14 = { 0, 10, 20, 25, 30 };
        tests::compare("ForwardList14", list14, expected14);

        dsa::ForwardList<int> list15{ 0, 10, 20, 30 };
        auto iter15 = list15.begin();
        std::advance(iter15, 3);
        list15.emplace_after(iter15, 40);
        const std::initializer_list<int> expected15 = { 0, 10, 20, 30, 40 };
        tests::compare("ForwardList15", list15, expected15);

        dsa::ForwardList<std::unique_ptr<int>> list16{};
        auto ptr16 = std::make_unique<int>(1);
        list16.push_front(std::move(ptr16));
        constexpr int expected16{ 1 };
        tests::compare("ForwardList16", *list16.front(), expected16);
        tests::compare("ptr16 == nullptr", ptr16 == nullptr, true);

        try
        {
            for (size_t i = 0; i < tests::throwing_type_size_limit; i++)
            {
                const tests::ThrowingType throwing_type{};
            }

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error& exc)
        {
            std::cout << "Error: " << exc.what() << '\n';
            std::cout << "Runtime error exception handled correctly\n\n";
        }

        try
        {
            dsa::ForwardList<tests::ThrowingType> list17{};
            const tests::ThrowingType throwing_type{};
            for (size_t i = 0; i < tests::throwing_type_size_limit; i++)
            {
                list17.push_front(throwing_type);
            }

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error& exc)
        {
            std::cout << "Error: " << exc.what() << '\n';
            std::cout << "List17 runtime error exception handled correctly\n\n";
        }

        try
        {
            dsa::ForwardList<tests::ThrowingType> list18{};
            tests::ThrowingType throwing_type{};
            for (size_t i = 0; i < tests::throwing_type_size_limit; i++)
            {
                // intentional use of moved object
                // NOLINTNEXTLINE(bugprone-use-after-move)
                list18.push_front(std::move(throwing_type));
            }

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error& exc)
        {
            std::cout << "Error: " << exc.what() << '\n';
            std::cout << "list18 runtime error exception handled correctly\n\n";
        }

        try
        {
            dsa::ForwardList<tests::ThrowingType> list19{};
            const tests::ThrowingType throwing_type{};
            for (size_t i = 0; i < tests::throwing_type_size_limit; i++)
            {
                list19.emplace_after(list19.before_begin(), throwing_type);
            }

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error& exc)
        {
            std::cout << "Error: " << exc.what() << '\n';
            std::cout << "List19 runtime error exception handled correctly\n\n";
        }

        dsa::ForwardList<int> list20{ 0, 10, 20 };
        dsa::ForwardList<int> temp20{ 30, 40, 50 };
        auto list20_it = list20.insert_after(std::next(list20.end(), 1), temp20.begin(), temp20.end());
        const std::initializer_list<int> expected20{ 0, 10, 20 };
        tests::compare("ForwardList20", list20, expected20);
        tests::compare("ForwardList20 it", list20_it == nullptr, true);

        dsa::ForwardList<int> list21{ 0, 10, 20 };
        auto list21_it = list21.insert_after(std::next(list21.end(), 1), 30);
        const std::initializer_list<int> expected21{ 0, 10, 20 };
        tests::compare("ForwardList21", list21, expected21);
        tests::compare("ForwardList21 it", list21_it == nullptr, true);


        std::cout << "Compare operations results with std container\n\n";

        std::forward_list<int> std_list5;
        std_list5.insert_after(std_list5.before_begin(), 40);
        std_list5.insert_after(std_list5.before_begin(), 30);
        std_list5.insert_after(std_list5.cbefore_begin(), 20);
        std_list5.insert_after(std_list5.cbefore_begin(), 10);
        tests::compare("ForwardList5 vs std", list5, std_list5);

        std::forward_list<int> std_list6{ 40 };
        std_list6.insert_after(std_list6.before_begin(), 30);
        std_list6.insert_after(std_list6.before_begin(), 20);
        std_list6.insert_after(std_list6.before_begin(), 10);
        tests::compare("ForwardList5 vs std", list5, std_list6);

        std::forward_list<int> std_list7{ 40 };
        std_list7.insert_after(std_list7.before_begin(), { 10, 20, 30 });
        tests::compare("ForwardList7 vs std", list7, std_list7);

        std::forward_list<std::unique_ptr<int>> std_list9{};
        auto std_ptr9 = std::make_unique<int>(1);
        std_list9.insert_after(std_list9.before_begin(), std::move(std_ptr9));
        tests::compare("ForwardList9 front() vs std", *list9.front(), *std_list9.front());
        tests::compare("ptr9 == nullptr vs std", ptr9 == nullptr, std_ptr9 == nullptr);

        std::forward_list<int> std_list10{};
        const std::forward_list<int> std_temp10{ 0, 10, 20, 30, 40, 50 };
        auto std_temp10_it = std::next(std_temp10.begin(), 3);
        auto std_list10_it = std_list10.insert_after(
            std_list10.before_begin(), std::next(std_temp10.begin(), 1), std::next(std_temp10.begin(), 4));
        tests::compare("ForwardList10 vs std", list10, std_list10);
        tests::compare("ForwardList10 it vs std", *list10_it, *std_list10_it);
        tests::compare("ForwardList10 temp it vs std", *temp10_it, *std_temp10_it);

        std::forward_list<int> std_list11{ 0, 10, 20 };
        const std::forward_list<int> std_temp11{ 30, 40, 50 };
        auto std_temp11_it = std::next(std_temp11.begin(), 2);
        auto std_list11_it = std_list11.insert_after(
            std::next(std_list11.begin(), 2), std_temp11.begin(), std_temp11.end());
        tests::compare("ForwardList11 vs std", list11, std_list11);
        tests::compare("ForwardList11 it vs std", *list11_it, *std_list11_it);
        tests::compare("ForwardList11 temp it vs std", *temp11_it, *std_temp11_it);

        std::forward_list<std::unique_ptr<int>> std_list16{};
        auto std_ptr16 = std::make_unique<int>(1);
        std_list16.push_front(std::move(std_ptr16));
        tests::compare("ForwardList17 vs std", *list16.front(), expected16);
        tests::compare("ptr16 == nullptr vs std", ptr16 == nullptr, std_ptr16 == nullptr);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
