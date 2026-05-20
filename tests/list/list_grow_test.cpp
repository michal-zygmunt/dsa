/**
 * @file list_grow_test.cpp
 * @brief This file tests functions increasing List length
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/list.h"

#include <cstddef>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <stdexcept>
#include <utility>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start list_grow_test:\n";

        dsa::List<int> list1 = dsa::List<int>(1, 40);
        auto iterator = list1.insert(list1.cbegin(), 30);
        list1.insert(iterator, { 10, 20 });
        list1.push_front(0);
        list1.push_front(-10);
        // Try inserting nodes at invalid indexes
        for (const auto& item : { -1, 0, 4, 2, 100 })
        {
            iterator = list1.begin();
            std::advance(iterator, item);
            list1.insert(iterator, item);
        }
        const std::initializer_list<int> expected1 = { 0, -10, 2, 0, 10, 4, 20, 30, 40 };
        tests::compare("List1", list1, expected1);

        dsa::List<int> list2 = dsa::List<int>(1, 50);
        list2.push_front(40);
        list2.push_front(30);
        list2.push_front(20);
        list2.push_front(10);
        auto list2_it = list2.insert(list2.cbegin(), 5, 5);
        const std::initializer_list<int> expected2 = { 5, 5, 5, 5, 5, 10, 20, 30, 40, 50 };
        tests::compare("List2", list2, expected2);
        tests::compare("List2 it", *list2_it, *list2.begin());
        tests::compare("List2 it", *std::next(list2_it), *std::next(list2.begin()));

        dsa::List<int> list3 = dsa::List<int>(1, 50);
        list3.push_front(40);
        list3.push_front(30);
        list3.push_front(20);
        iterator = list3.insert(list3.cbegin(), 10);
        list3.insert(iterator, { 1, 2, 3 });
        list3.insert(std::next(list3.cbegin(), static_cast<ptrdiff_t>(list3.size() - 1)), 60);
        const std::initializer_list<int> expected3 = { 1, 2, 3, 10, 20, 30, 40, 60, 50 };
        tests::compare("List3", list3, expected3);

        dsa::List<int> list4;
        list4.push_back(20);
        list4.push_back(30);
        list4.push_back(40);
        iterator = list4.insert(list4.cbegin(), 10);
        const std::initializer_list<int> expected4 = { 10, 20, 30, 40 };
        tests::compare("List4", list4, expected4);

        dsa::List<int> list5{ 10, 20, 30 };
        list5.insert(list5.end(), 40);
        const std::initializer_list<int> expected5 = { 10, 20, 30, 40 };
        tests::compare("List5", list5, expected5);

        dsa::List<int> list6{ 10, 20, 30 };
        list6.insert(list6.end(), { 40, 50, 60 });
        const std::initializer_list<int> expected6 = { 10, 20, 30, 40, 50, 60 };
        tests::compare("List6", list6, expected6);

        dsa::List<int> list7{ 40 };
        list7.insert(list7.begin(), { 10, 20, 30 });
        const std::initializer_list<int> expected7 = { 10, 20, 30, 40 };
        tests::compare("List7", list7, expected7);

        dsa::List<int> list8{};
        auto iter8 = list8.end();
        std::advance(iter8, 1);
        iter8 = list8.insert(iter8, { 10, 20, 30 });
        tests::compare("iter8 == nullptr", iter8 == nullptr, true);

        dsa::List<std::unique_ptr<int>> list9{};
        auto ptr9 = std::make_unique<int>(1);
        list9.insert(list9.begin(), std::move(ptr9));
        constexpr int expected9{ 1 };
        tests::compare("List9 front()", *list9.front(), expected9);
        tests::compare("ptr9 == nullptr", ptr9 == nullptr, true);

        dsa::List<int> list10{};
        const dsa::List<int> temp10{ 0, 10, 20, 30, 40, 50 };
        auto temp10_it = std::next(temp10.begin(), 1);
        auto list10_it = list10.insert(
            list10.begin(), std::next(temp10.begin(), 1), std::next(temp10.begin(), 4));
        const std::initializer_list<int> expected10{ 10, 20, 30 };
        tests::compare("List10", list10, expected10);
        tests::compare("List10 it", *list10_it, *temp10_it);

        dsa::List<int> list11{ 0, 10, 20 };
        const dsa::List<int> temp11{ 30, 40, 50 };
        auto temp11_it = temp11.begin();
        auto list11_it = list11.insert(std::next(list11.begin(), 2), temp11.begin(), temp11.end());
        const std::initializer_list<int> expected11{ 0, 10, 30, 40, 50, 20 };
        tests::compare("List11", list11, expected11);
        tests::compare("List11 it", *list11_it, *temp11_it);

        dsa::List<int> list12;
        auto ref12 = list12.emplace_front(30);
        tests::compare("List12 ref", ref12, list12.front());
        ref12 = list12.emplace_front(20);
        tests::compare("List12 ref", ref12, list12.front());
        list12.emplace_front(10);
        list12.emplace_front(5);
        list12.emplace_front(0);
        const std::initializer_list<int> expected12 = { 0, 5, 10, 20, 30 };
        tests::compare("List12", list12, expected12);

        dsa::List<int> list13{ 0, 10, 20, 30 };
        auto iter13 = list13.emplace(list13.begin(), -10);
        tests::compare("List13 iter", *iter13, *list13.begin());
        const std::initializer_list<int> expected13 = { -10, 0, 10, 20, 30 };
        tests::compare("List13", list13, expected13);

        dsa::List<int> list14{ 0, 10, 20, 30 };
        auto iter14 = list14.emplace(list14.end(), 40);
        tests::compare("List14 iter", *iter14, *(--list14.end()));
        const std::initializer_list<int> expected14 = { 0, 10, 20, 30, 40 };
        tests::compare("List14", list14, expected14);

        dsa::List<int> list15{ 0, 10, 20, 30 };
        auto ref15 = list15.emplace_back(40);
        tests::compare("List15 ref", ref15, list15.back());
        const std::initializer_list<int> expected15 = { 0, 10, 20, 30, 40 };
        tests::compare("List15", list15, expected15);

        dsa::List<int> list16;
        list16.emplace_back(10);
        list16.emplace_back(20);
        list16.emplace_back(30);
        const std::initializer_list<int> expected16 = { 10, 20, 30 };
        tests::compare("List16", list16, expected16);

        dsa::List<std::unique_ptr<int>> list17{};
        auto ptr17 = std::make_unique<int>(1);
        list17.push_back(std::move(ptr17));
        constexpr int expected17{ 1 };
        tests::compare("List17 front", *list17.front(), expected17);
        tests::compare("List17 back", *list17.back(), expected17);
        tests::compare("ptr17 == nullptr", ptr17 == nullptr, true);

        dsa::List<std::unique_ptr<int>> list18{};
        auto ptr18 = std::make_unique<int>(1);
        list18.push_front(std::move(ptr18));
        constexpr int expected18{ 1 };
        tests::compare("List18 front", *list18.front(), expected18);
        tests::compare("List18 back", *list18.back(), expected18);
        tests::compare("ptr18 == nullptr", ptr18 == nullptr, true);

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
            dsa::List<tests::ThrowingType> list19{};
            const tests::ThrowingType throwing_type{};
            for (size_t i = 0; i < tests::throwing_type_size_limit; i++)
            {
                list19.push_front(throwing_type);
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

        try
        {
            dsa::List<tests::ThrowingType> list20{};
            tests::ThrowingType throwing_type{};
            for (size_t i = 0; i < tests::throwing_type_size_limit; i++)
            {
                // intentional use of moved object
                // NOLINTNEXTLINE(bugprone-use-after-move)
                list20.push_front(std::move(throwing_type));
            }

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error& exc)
        {
            std::cout << "Error: " << exc.what() << '\n';
            std::cout << "list20 runtime error exception handled correctly\n\n";
        }

        try
        {
            dsa::List<tests::ThrowingType> list21{};
            const tests::ThrowingType throwing_type{};
            for (size_t i = 0; i < tests::throwing_type_size_limit; i++)
            {
                list21.push_back(throwing_type);
            }

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error& exc)
        {
            std::cout << "Error: " << exc.what() << '\n';
            std::cout << "List21 runtime error exception handled correctly\n\n";
        }

        try
        {
            dsa::List<tests::ThrowingType> list22{};
            tests::ThrowingType throwing_type{};
            for (size_t i = 0; i < tests::throwing_type_size_limit; i++)
            {
                // intentional use of moved object
                // NOLINTNEXTLINE(bugprone-use-after-move)
                list22.push_back(std::move(throwing_type));
            }

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error& exc)
        {
            std::cout << "Error: " << exc.what() << '\n';
            std::cout << "list22 runtime error exception handled correctly\n\n";
        }

        try
        {
            dsa::List<tests::ThrowingType> list23{};
            const tests::ThrowingType throwing_type{};
            for (size_t i = 0; i < tests::throwing_type_size_limit; i++)
            {
                list23.emplace(list23.begin(), throwing_type);
            }

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error& exc)
        {
            std::cout << "Error: " << exc.what() << '\n';
            std::cout << "List23 runtime error exception handled correctly\n\n";
        }

        try
        {
            dsa::List<tests::ThrowingType> list24{};
            tests::ThrowingType throwing_type{};
            for (size_t i = 0; i < tests::throwing_type_size_limit; i++)
            {
                // intentional use of moved object
                // NOLINTNEXTLINE(bugprone-use-after-move)
                list24.emplace(list24.begin(), std::move(throwing_type));
            }

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error& exc)
        {
            std::cout << "Error: " << exc.what() << '\n';
            std::cout << "List24 runtime error exception handled correctly\n\n";
        }

        try
        {
            dsa::List<tests::ThrowingType> list24{};
            const tests::ThrowingType throwing_type{};
            for (size_t i = 0; i < tests::throwing_type_size_limit; i++)
            {
                list24.emplace_front(throwing_type);
            }

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error& exc)
        {
            std::cout << "Error: " << exc.what() << '\n';
            std::cout << "List24 runtime error exception handled correctly\n\n";
        }

        try
        {
            dsa::List<tests::ThrowingType> list25{};
            tests::ThrowingType throwing_type{};
            for (size_t i = 0; i < tests::throwing_type_size_limit; i++)
            {
                // intentional use of moved object
                // NOLINTNEXTLINE(bugprone-use-after-move)
                list25.emplace_front(std::move(throwing_type));
            }

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error& exc)
        {
            std::cout << "Error: " << exc.what() << '\n';
            std::cout << "List25 runtime error exception handled correctly\n\n";
        }

        try
        {
            dsa::List<tests::ThrowingType> list26{};
            const tests::ThrowingType throwing_type{};
            for (size_t i = 0; i < tests::throwing_type_size_limit; i++)
            {
                list26.emplace_back(throwing_type);
            }

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error& exc)
        {
            std::cout << "Error: " << exc.what() << '\n';
            std::cout << "List26 runtime error exception handled correctly\n\n";
        }

        try
        {
            dsa::List<tests::ThrowingType> list27{};
            tests::ThrowingType throwing_type{};
            for (size_t i = 0; i < tests::throwing_type_size_limit; i++)
            {
                // intentional use of moved object
                // NOLINTNEXTLINE(bugprone-use-after-move)
                list27.emplace_back(std::move(throwing_type));
            }

            // command should not be reached
            tests::failed_count()++;
            std::cout << "ThrowingType should throw error\n\n";
        }
        catch (const std::runtime_error& exc)
        {
            std::cout << "Error: " << exc.what() << '\n';
            std::cout << "List27 runtime error exception handled correctly\n\n";
        }

        dsa::List<int> list28{ 0, 10, 20 };
        dsa::List<int> temp28{ 30, 40, 50 };
        auto list28_it = list28.insert(std::next(list28.end(), 1), temp28.begin(), temp28.end());
        const std::initializer_list<int> expected28{ 0, 10, 20 };
        tests::compare("List28", list28, expected28);
        tests::compare("List28 it", list28_it == nullptr, true);

        dsa::List<int> list29{ 0, 10, 20 };
        auto list29_it = list29.insert(std::next(list29.end(), 1), 30);
        const std::initializer_list<int> expected29{ 0, 10, 20 };
        tests::compare("List29", list29, expected29);
        tests::compare("List29 it", list29_it == nullptr, true);

        dsa::List<std::unique_ptr<int>> list30{};
        auto ptr30 = std::make_unique<int>(1);
        auto list30_it = list30.insert(list30.end(), std::move(ptr30));
        tests::compare("List30 it", *list30_it, list30.front());

        dsa::List<std::unique_ptr<int>> list31{};
        auto ptr31 = std::make_unique<int>(1);
        list31.insert(std::next(list31.end()), std::move(ptr31));
        tests::compare("List31 size", list31.size(), static_cast<std::size_t>(0));

        dsa::List<int> list32{ 0, 10, 20 };
        dsa::List<int> list33{ 30, 40, 50 };
        auto list32_it = list32.insert(list32.begin(), list33.begin(), std::next(list33.begin()));
        const std::initializer_list<int> expected32{ 30, 0, 10, 20 };
        const std::initializer_list<int> expected33{ 30, 40, 50 };
        tests::compare("List32", list32, expected32);
        tests::compare("List32 it", *list32_it, list33.front());
        tests::compare("List33", list33, expected33);

        dsa::List<int> list34{ 0, 10, 20 };
        const dsa::List<int> temp34{ 30, 40, 50 };
        auto list34_it = list34.insert(std::next(list34.begin(), 2), temp34.begin(), temp34.begin());
        const std::initializer_list<int> expected34{ 0, 10, 20 };
        tests::compare("List34", list34, expected34);
        tests::compare("List34 it", *list34_it, *(std::next(list34.begin(), 2)));


        std::cout << "Compare operations results with std container\n\n";

        std::list<int> std_list5{ 10, 20, 30 };
        std_list5.insert(std_list5.end(), 40);
        tests::compare("List5 vs std", list5, std_list5);

        std::list<int> std_list6{ 10, 20, 30 };
        std_list6.insert(std_list6.end(), { 40, 50, 60 });
        tests::compare("List6 vs std", list6, std_list6);

        std::list<int> std_list7{ 40 };
        std_list7.insert(std_list7.begin(), { 10, 20, 30 });
        tests::compare("List7 vs std", list7, std_list7);

        std::list<std::unique_ptr<int>> std_list9{};
        auto std_ptr9 = std::make_unique<int>(1);
        std_list9.insert(std_list9.begin(), std::move(std_ptr9));
        tests::compare("List9 front() vs std", *list9.front(), *std_list9.front());
        tests::compare("ptr19 == nullptr", ptr9 == std_ptr9, true);

        std::list<int> std_list10{};
        const std::list<int> std_temp10{ 0, 10, 20, 30, 40, 50 };
        auto std_list10_it = std_list10.insert(
            std_list10.begin(), std::next(std_temp10.begin(), 1), std::next(std_temp10.begin(), 4));
        tests::compare("List10 vs std", list10, std_list10);
        tests::compare("List10 it vs std", *list10_it, *std_list10_it);

        std::list<int> std_list11{ 0, 10, 20 };
        const std::list<int> std_temp11{ 30, 40, 50 };
        auto std_list11_it = std_list11.insert(std::next(std_list11.begin(), 2), std_temp11.begin(), std_temp11.end());
        tests::compare("List11 vs std", list11, std_list11);
        tests::compare("List11 it vs std", *list11_it, *std_list11_it);

        std::list<int> std_list12;
        std_list12.emplace_front(30);
        auto std_ref12 = std_list12.emplace_front(20);
        tests::compare("List12 ref vs std", ref12, std_ref12);
        std_list12.emplace_front(10);
        std_list12.emplace_front(5);
        std_list12.emplace_front(0);
        tests::compare("List12 vs std", list12, std_list12);

        std::list<int> std_list13{ 0, 10, 20, 30 };
        auto std_iter13 = std_list13.emplace(std_list13.begin(), -10);
        tests::compare("List13 iter vs std", *iter13, *std_iter13);
        tests::compare("List13 vs std", list13, std_list13);

        std::list<int> std_list14{ 0, 10, 20, 30 };
        auto std_iter14 = std_list14.emplace(std_list14.end(), 40);
        tests::compare("List14 iter vs std", *std_iter14, *(--std_list14.end()));
        tests::compare("List14 vs std", list14, std_list14);

        std::list<int> std_list15{ 0, 10, 20, 30 };
        auto std_ref15 = std_list15.emplace_back(40);
        tests::compare("List15 ref vs std", ref15, std_ref15);
        tests::compare("List15 vs std", list15, std_list15);

        std::list<int> std_list16;
        std_list16.emplace_back(10);
        std_list16.emplace_back(20);
        std_list16.emplace_back(30);
        tests::compare("List16 vs std", list16, std_list16);

        std::list<std::unique_ptr<int>> std_list17{};
        auto std_ptr17 = std::make_unique<int>(1);
        std_list17.push_back(std::move(std_ptr17));
        tests::compare("List17 front vs std", *list17.front(), *std_list17.front());
        tests::compare("List17 back vs std", *list17.back(), *std_list17.back());
        tests::compare("ptr17 == nullptr vs std", ptr17 == nullptr, std_ptr17 == nullptr);

        std::list<std::unique_ptr<int>> std_list18{};
        auto std_ptr18 = std::make_unique<int>(1);
        std_list18.push_front(std::move(std_ptr18));
        tests::compare("List18 front vs std", *list18.front(), *std_list18.front());
        tests::compare("List18 backvs std", *list18.back(), *std_list18.back());
        tests::compare("ptr18 == nullptr vs std", ptr18 == std_ptr18, true);


        tests::print_stats();
    }
    catch (...)
    {
        return tests::handle_exception(std::current_exception());
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}