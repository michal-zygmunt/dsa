/**
 * @file ListOperators.cpp
 * @brief This file tests overloading operators of List
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * This project is distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/List.h"

#include <initializer_list>
#include <iostream>
#include <list>
#include <new>
#include <stdexcept>

int main() // NOLINT(modernize-use-trailing-return-type)
{
    // tests are based on hardcoded magic numbers for comparison of container content
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    try
    {
        std::cout << "Start ListOperators test:\n";

        const dsa::List<int> list1({ 1, 2, 3 });
        const dsa::List<int> list2({ 4, 5, 6 });
        const dsa::List<int> list3({ 1, 2, 3, 4 });
        std::cout << "List1:\t" << list1 << '\n';
        std::cout << "List2:\t" << list2 << '\n';
        std::cout << "List3:\t" << list3 << "\n\n";

        const dsa::List<int> list4(list1 + list2);
        const std::initializer_list<int> expected4 = { 1,2,3,4,5,6 };
        tests::compare("ForwardList4", list4, expected4);

        dsa::List<int> list5(1, 0);
        list5 += list2;
        const std::initializer_list<int> expected5 = { 0,4,5,6 };
        tests::compare("ForwardList5", list5, expected5);

        dsa::List<int> list6(1, 0);
        list6 += { 4, 5, 6 };
        const std::initializer_list<int> expected6 = { 0,4,5,6 };
        tests::compare("ForwardList6", list6, expected6);

        std::cout << "Compare operators for objects of the same size\n\n";

        // intentional self-comparison, an object should be equal to itself
        // NOLINTNEXTLINE(misc-redundant-expression)
        tests::compare("List1 == list1", list1 == list1, true);

        tests::compare("List1 != list2", list1 != list2, true);

        tests::compare("List1 < list2", list1 < list2, true);
        tests::compare("List2 < list1", list2 < list1, false);

        tests::compare("List1 > list2", list1 > list2, false);
        tests::compare("List2 > list1", list2 > list1, true);

        tests::compare("List1 <= list2", list1 <= list2, true);
        tests::compare("List2 <= list1", list2 <= list1, false);

        tests::compare("List1 >= list2", list1 >= list2, false);
        tests::compare("List2 >= list1", list2 >= list1, true);

        std::cout << "Compare operators for objects of different size\n\n";

        tests::compare("List1 == list3", list1 == list3, false);

        tests::compare("List1 != list3", list1 != list3, true);

        tests::compare("List1 < list3", list1 < list3, true);
        tests::compare("List3 < list1", list3 < list1, false);
        tests::compare("List2 < list3", list2 < list3, false);
        tests::compare("List3 < list2", list3 < list2, true);

        tests::compare("List1 > list3", list1 > list3, false);
        tests::compare("List3 > list1", list3 > list1, true);
        tests::compare("List2 > list3", list2 > list3, true);
        tests::compare("List3 > list2", list3 > list2, false);

        tests::compare("List1 <= list3", list1 <= list3, true);
        tests::compare("List3 <= list1", list3 <= list1, false);
        tests::compare("List2 <= list3", list2 <= list3, false);
        tests::compare("List3 <= list2", list3 <= list2, true);

        tests::compare("List1 >= list3", list1 >= list3, false);
        tests::compare("List3 >= list1", list3 >= list1, true);
        tests::compare("List2 >= list3", list2 >= list3, true);
        tests::compare("List3 >= list2", list3 >= list2, false);


        std::cout << "Compare operations results with std container\n\n";

        const std::list<int> std_list1({ 1, 2, 3 });
        const std::list<int> std_list2({ 4, 5, 6 });
        const std::list<int> std_list3({ 1, 2, 3, 4 });

        // intentional self-comparison, an object should be equal to itself
        // NOLINTNEXTLINE(misc-redundant-expression)
        tests::compare("List1 == list1 vs std", list1 == list1, std_list1 == std_list1);

        tests::compare("List1 != list2 vs std", list1 != list2, std_list1 != std_list2);

        tests::compare("List1 < list2 vs std", list1 < list2, std_list1 < std_list2);
        tests::compare("List2 < list1 vs std", list2 < list1, std_list2 < std_list1);

        tests::compare("List1 > list2 vs std", list1 > list2, std_list1 > std_list2);
        tests::compare("List2 > list1 vs std", list2 > list1, std_list2 > std_list1);

        tests::compare("List1 <= list2 vs std", list1 <= list2, std_list1 <= std_list2);
        tests::compare("List2 <= list1 vs std", list2 <= list1, std_list2 <= std_list1);

        tests::compare("List1 >= list2 vs std", list1 >= list2, std_list1 >= std_list2);
        tests::compare("List2 >= list1 vs std", list2 >= list1, std_list2 >= std_list1);

        std::cout << "Compare operators for objects of different size\n\n";

        tests::compare("List1 == list3 vs std", list1 == list3, std_list1 == std_list3);

        tests::compare("List1 != list3 vs std", list1 != list3, std_list1 != std_list3);

        tests::compare("List1 < list3 vs std", list1 < list3, std_list1 < std_list3);
        tests::compare("List3 < list1 vs std", list3 < list1, std_list3 < std_list1);
        tests::compare("List2 < list3 vs std", list2 < list3, std_list2 < std_list3);
        tests::compare("List3 < list2 vs std", list3 < list2, std_list3 < std_list2);

        tests::compare("List1 > list3 vs std", list1 > list3, std_list1 > std_list3);
        tests::compare("List3 > list1 vs std", list3 > list1, std_list3 > std_list1);
        tests::compare("List2 > list3 vs std", list2 > list3, std_list2 > std_list3);
        tests::compare("List3 > list2 vs std", list3 > list2, std_list3 > std_list2);

        tests::compare("List1 <= list3 vs std", list1 <= list3, std_list1 <= std_list3);
        tests::compare("List3 <= list1 vs std", list3 <= list1, std_list3 <= std_list1);
        tests::compare("List2 <= list3 vs std", list2 <= list3, std_list2 <= std_list3);
        tests::compare("List3 <= list2 vs std", list3 <= list2, std_list3 <= std_list2);

        tests::compare("List1 >= list3 vs std", list1 >= list3, std_list1 >= std_list3);
        tests::compare("List3 >= list1 vs std", list3 >= list1, std_list3 >= std_list1);
        tests::compare("List2 >= list3 vs std", list2 >= list3, std_list2 >= std_list3);
        tests::compare("List3 >= list2 vs std", list3 >= list2, std_list3 >= std_list2);
    }
    catch (const std::bad_alloc& exception)
    {
        std::cerr << "Caught std::bad_alloc: " << exception.what() << '\n';
        return 1;
    }
    catch (const std::runtime_error& exception)
    {
        std::cerr << "Caught std::runtime_error: " << exception.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unhandled unknown exception\n";
        return 1;
    }

    return tests::failed_count();

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}