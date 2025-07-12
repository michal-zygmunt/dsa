/**
 * @file ListGrow.cpp
 * @brief This file tests functions splicing List objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "dsa/List.h"

int main()
{
    std::cout << "Start ListSplice test:\n";

    std::initializer_list<int> expected{};
    std::initializer_list<int> expected_1{ 1, 2, 3, 4, 5 };
    std::initializer_list<int> expected_2{ 10, 20, 30, 40, 50 };


    std::cout << "Testing moving other list\n\n";

    dsa::List<int> l1 = dsa::List<int>(expected_1);
    dsa::List<int> l2 = dsa::List<int>(expected_2);
    l1.splice(l1.begin(), l2);
    expected = { 10, 20, 30, 40, 50, 1, 2, 3, 4, 5 };
    tests::compare("List l1", l1, expected);
    expected = {};
    tests::compare("List l2", l2, expected);

    dsa::List<int> l3 = dsa::List<int>(expected_1);
    dsa::List<int> l4 = dsa::List<int>(expected_2);
    l3.splice(l3.begin()[3], l4);
    expected = { 1, 2, 3, 10, 20, 30, 40, 50, 4, 5 };
    tests::compare("List l3", l3, expected);
    expected = {};
    tests::compare("List l4", l4, expected);

    dsa::List<int> l5 = dsa::List<int>(expected_1);
    dsa::List<int> l6 = dsa::List<int>(expected_2);
    l5.splice(l5.begin()[l5.size() - 1], l6);
    expected = { 1, 2, 3, 4, 10, 20, 30, 40, 50, 5 };
    tests::compare("List l5", l5, expected);
    expected = {};
    tests::compare("List l6", l6, expected);


    std::cout << "Testing moving empty list\n\n";

    dsa::List<int> l7 = dsa::List<int>(expected_1);
    dsa::List<int> l8;
    l7.splice(l7.begin()[l7.size() - 1], l8);
    expected = expected_1;
    tests::compare("List l7", l7, expected);
    expected = {};
    tests::compare("List l8", l8, expected);


    std::cout << "Testing moving one element from other list\n\n";

    dsa::List<int> l9 = dsa::List<int>(expected_1);
    dsa::List<int> l10 = dsa::List<int>(expected_2);
    l9.splice(l9.begin(), l10, l10.begin());
    expected = { 10, 1, 2, 3, 4, 5 };
    tests::compare("List l9", l9, expected);
    expected = { 20, 30, 40, 50 };
    tests::compare("List l10", l10, expected);

    dsa::List<int> l11 = dsa::List<int>(expected_1);
    dsa::List<int> l12 = dsa::List<int>(expected_2);
    l11.splice(l11.begin(), l12, l12.begin()[2]);
    expected = { 30, 1, 2, 3, 4, 5 };
    tests::compare("List l11", l11, expected);
    expected = { 10, 20, 40, 50 };
    tests::compare("List l12", l12, expected);

    dsa::List<int> l13 = dsa::List<int>(expected_1);
    dsa::List<int> l14 = dsa::List<int>(expected_2);
    l13.splice(l13.begin(), l14, l14.begin()[l14.size() - 2]);
    expected = { 40, 1, 2, 3, 4, 5 };
    tests::compare("List l13", l13, expected);
    expected = { 10, 20, 30, 50 };
    tests::compare("List l14", l14, expected);


    dsa::List<int> l15 = dsa::List<int>(expected_1);
    dsa::List<int> l16 = dsa::List<int>(expected_2);
    l15.splice(l15.begin()[3], l16, l16.begin());
    expected = { 1, 2, 3, 10, 4, 5 };
    tests::compare("List l15", l15, expected);
    expected = { 20, 30, 40, 50 };
    tests::compare("List l16", l16, expected);

    dsa::List<int> l17 = dsa::List<int>(expected_1);
    dsa::List<int> l18 = dsa::List<int>(expected_2);
    l17.splice(l17.begin()[3], l18, l18.begin()[2]);
    expected = { 1, 2, 3, 30, 4, 5 };
    tests::compare("List l17", l17, expected);
    expected = { 10, 20, 40, 50 };
    tests::compare("List l18", l18, expected);

    dsa::List<int> l19 = dsa::List<int>(expected_1);
    dsa::List<int> l20 = dsa::List<int>(expected_2);
    l19.splice(l19.begin()[3], l20, l20.begin()[l20.size() - 2]);
    expected = { 1, 2, 3, 40, 4, 5 };
    tests::compare("List l19", l19, expected);
    expected = { 10, 20, 30, 50 };
    tests::compare("List l20", l20, expected);


    dsa::List<int> l21 = dsa::List<int>(expected_1);
    dsa::List<int> l22 = dsa::List<int>(expected_2);
    l21.splice(l21.begin()[l21.size() - 1], l22, l22.begin());
    expected = { 1, 2, 3, 4, 10, 5 };
    tests::compare("List l21", l21, expected);
    expected = { 20, 30, 40, 50 };
    tests::compare("List l22", l22, expected);

    dsa::List<int> l23 = dsa::List<int>(expected_1);
    dsa::List<int> l24 = dsa::List<int>(expected_2);
    l23.splice(l23.begin()[l23.size() - 1], l24, l24.begin()[3]);
    expected = { 1, 2, 3, 4, 40, 5 };
    tests::compare("List l23", l23, expected);
    expected = { 10, 20, 30, 50 };
    tests::compare("List l24", l24, expected);

    dsa::List<int> l25 = dsa::List<int>(expected_1);
    dsa::List<int> l26 = dsa::List<int>(expected_2);
    l25.splice(l25.begin()[l25.size() - 1], l26, l26.begin()[l26.size() - 2]);
    expected = { 1, 2, 3, 4, 40, 5 };
    tests::compare("List l25", l25, expected);
    expected = { 10, 20, 30, 50 };
    tests::compare("List l26", l26, expected);


    std::cout << "Testing moving range of element from other list\n\n";

    dsa::List<int> l27 = dsa::List<int>(expected_1);
    dsa::List<int> l28 = dsa::List<int>(expected_2);
    l27.splice(l27.begin(), l28, l28.begin(), l28.begin()[1]);
    expected = { 10, 1, 2, 3, 4, 5 };
    tests::compare("List l27", l27, expected);
    expected = { 20, 30, 40, 50 };
    tests::compare("List l28", l28, expected);

    dsa::List<int> l29 = dsa::List<int>(expected_1);
    dsa::List<int> l30 = dsa::List<int>(expected_2);
    l29.splice(l29.begin(), l30, l30.begin()[1], l30.begin()[3]);
    expected = { 20, 30, 1, 2, 3, 4, 5 };
    tests::compare("List l29", l29, expected);
    expected = { 10, 40, 50 };
    tests::compare("List l30", l30, expected);

    dsa::List<int> l31 = dsa::List<int>(expected_1);
    dsa::List<int> l32 = dsa::List<int>(expected_2);
    l31.splice(l31.begin(), l32, l32.begin(), l32.begin()[l32.size() - 1]);
    expected = { 10, 20, 30, 40, 1, 2, 3, 4, 5 };
    tests::compare("List l31", l31, expected);
    expected = { 50 };
    tests::compare("List l32", l32, expected);


    dsa::List<int> l33 = dsa::List<int>(expected_1);
    dsa::List<int> l34 = dsa::List<int>(expected_2);
    l33.splice(l33.begin()[2], l34, l34.begin(), l34.begin()[1]);
    expected = { 1, 2, 10, 3, 4, 5 };
    tests::compare("List l33", l33, expected);
    expected = { 20, 30, 40, 50 };
    tests::compare("List l34", l34, expected);

    dsa::List<int> l35 = dsa::List<int>(expected_1);
    dsa::List<int> l36 = dsa::List<int>(expected_2);
    l35.splice(l35.begin()[2], l36, l36.begin()[1], l36.begin()[3]);
    expected = { 1, 2, 20, 30, 3, 4, 5 };
    tests::compare("List l35", l35, expected);
    expected = { 10, 40, 50 };
    tests::compare("List l36", l36, expected);

    dsa::List<int> l37 = dsa::List<int>(expected_1);
    dsa::List<int> l38 = dsa::List<int>(expected_2);
    l37.splice(l37.begin()[2], l38, l38.begin(), l38.begin()[l38.size() - 1]);
    expected = { 1, 2, 10, 20, 30, 40, 3, 4, 5 };
    tests::compare("List l37", l37, expected);
    expected = { 50 };
    tests::compare("List l38", l38, expected);


    dsa::List<int> l39 = dsa::List<int>(expected_1);
    dsa::List<int> l40 = dsa::List<int>(expected_2);
    l39.splice(l39.begin()[l39.size() - 1], l40, l40.begin(), l40.begin()[1]);
    expected = { 1, 2, 3, 4, 10, 5 };
    tests::compare("List l39", l39, expected);
    expected = { 20, 30, 40, 50 };
    tests::compare("List l40", l40, expected);

    dsa::List<int> l41 = dsa::List<int>(expected_1);
    dsa::List<int> l42 = dsa::List<int>(expected_2);
    l41.splice(l41.begin()[l41.size() - 1], l42, l42.begin()[1], l42.begin()[3]);
    expected = { 1, 2, 3, 4, 20, 30, 5 };
    tests::compare("List l41", l41, expected);
    expected = { 10, 40, 50 };
    tests::compare("List l42", l42, expected);

    dsa::List<int> l43 = dsa::List<int>(expected_1);
    dsa::List<int> l44 = dsa::List<int>(expected_2);
    l43.splice(l43.begin()[l43.size() - 1], l44, l44.begin(), l44.begin()[l44.size() - 1]);
    expected = { 1, 2, 3, 4, 10, 20, 30, 40, 5 };
    tests::compare("List l43", l43, expected);
    expected = { 50 };
    tests::compare("List l44", l44, expected);

    return tests::failed;
}
