/**
 * @file ForwardListGrow.cpp
 * @brief This file tests functions splicing ForwardList objects
 * @author Michal Zygmunt
 *
 * @copyright Copyright (c) 2025 Michal Zygmunt
 * @license Distributed under the MIT License.
 * See accompanying LICENSE.txt file or obtain copy at
 * https://opensource.org/license/mit
 */

#include "common.h"
#include "ForwardList.h"

int main()
{
    std::cout << "Start ForwardListSplice test:\n";

    std::initializer_list<int> expected{};
    std::initializer_list<int> expected_1{ 1, 2, 3, 4, 5 };
    std::initializer_list<int> expected_2{ 10, 20, 30, 40, 50 };


    std::cout << "Testing moving other list\n\n";

    dsa::ForwardList<int> l1 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l2 = dsa::ForwardList<int>(expected_2);
    l1.splice_after(l1.begin(), l2);
    expected = { 1, 10, 20, 30, 40, 50, 2, 3, 4, 5 };
    tests::compare("ForwardList l1", l1, expected);
    expected = {};
    tests::compare("ForwardList l2", l2, expected);

    dsa::ForwardList<int> l3 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l4 = dsa::ForwardList<int>(expected_2);
    l3.splice_after(l3.begin()[3], l4);
    expected = { 1, 2, 3, 4, 10, 20, 30, 40, 50, 5 };
    tests::compare("ForwardList l3", l3, expected);
    expected = {};
    tests::compare("ForwardList l4", l4, expected);

    dsa::ForwardList<int> l5 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l6 = dsa::ForwardList<int>(expected_2);
    l5.splice_after(l5.begin()[l5.size() - 1], l6);
    expected = { 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
    tests::compare("ForwardList l5", l5, expected);
    expected = {};
    tests::compare("ForwardList l6", l6, expected);

    std::cout << "Testing moving empty list\n\n";

    dsa::ForwardList<int> l7 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l8;
    l7.splice_after(l7.begin()[l7.size() - 1], l8);
    expected = expected_1;
    tests::compare("ForwardList l7", l7, expected);
    expected = {};
    tests::compare("ForwardList l8", l8, expected);

    std::cout << "Testing moving one element from other list\n\n";

    dsa::ForwardList<int> l9 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l10 = dsa::ForwardList<int>(expected_2);
    l9.splice_after(l9.begin(), l10, l10.begin());
    expected = { 1, 20, 2, 3, 4, 5 };
    tests::compare("ForwardList l9", l9, expected);
    expected = { 10, 30, 40, 50 };
    tests::compare("ForwardList l10", l10, expected);

    dsa::ForwardList<int> l11 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l12 = dsa::ForwardList<int>(expected_2);
    l11.splice_after(l11.begin(), l12, l12.begin()[2]);
    expected = { 1, 40, 2, 3, 4, 5 };
    tests::compare("ForwardList l11", l11, expected);
    expected = { 10, 20, 30, 50 };
    tests::compare("ForwardList l12", l12, expected);

    dsa::ForwardList<int> l13 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l14 = dsa::ForwardList<int>(expected_2);
    l13.splice_after(l13.begin(), l14, l14.begin()[l14.size() - 2]);
    expected = { 1, 50, 2, 3, 4, 5 };
    tests::compare("ForwardList l13", l13, expected);
    expected = { 10, 20, 30, 40 };
    tests::compare("ForwardList l14", l14, expected);

    dsa::ForwardList<int> l15 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l16 = dsa::ForwardList<int>(expected_2);
    l15.splice_after(l15.begin()[3], l16, l16.begin());
    expected = { 1, 2, 3, 4, 20, 5 };
    tests::compare("ForwardList l15", l15, expected);
    expected = { 10, 30, 40, 50 };
    tests::compare("ForwardList l16", l16, expected);

    dsa::ForwardList<int> l17 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l18 = dsa::ForwardList<int>(expected_2);
    l17.splice_after(l17.begin()[3], l18, l18.begin()[2]);
    expected = { 1, 2, 3, 4, 40, 5 };
    tests::compare("ForwardList l17", l17, expected);
    expected = { 10, 20, 30, 50 };
    tests::compare("ForwardList l18", l18, expected);

    dsa::ForwardList<int> l19 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l20 = dsa::ForwardList<int>(expected_2);
    l19.splice_after(l19.begin()[3], l20, l20.begin()[l20.size() - 2]);
    expected = { 1, 2, 3, 4, 50, 5 };
    tests::compare("ForwardList l19", l19, expected);
    expected = { 10, 20, 30, 40 };
    tests::compare("ForwardList l20", l20, expected);


    dsa::ForwardList<int> l21 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l22 = dsa::ForwardList<int>(expected_2);
    l21.splice_after(l21.begin()[l21.size() - 1], l22, l22.begin());
    expected = { 1, 2, 3, 4, 5, 20 };
    tests::compare("ForwardList l21", l21, expected);
    expected = { 10, 30, 40, 50 };
    tests::compare("ForwardList l22", l22, expected);

    dsa::ForwardList<int> l23 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l24 = dsa::ForwardList<int>(expected_2);
    l23.splice_after(l23.begin()[l23.size() - 1], l24, l24.begin()[3]);
    expected = { 1, 2, 3, 4, 5, 50 };
    tests::compare("ForwardList l23", l23, expected);
    expected = { 10, 20, 30, 40 };
    tests::compare("ForwardList l24", l24, expected);

    dsa::ForwardList<int> l25 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l26 = dsa::ForwardList<int>(expected_2);
    l25.splice_after(l25.begin()[l25.size() - 1], l26, l26.begin()[l26.size() - 2]);
    expected = { 1, 2, 3, 4, 5, 50 };
    tests::compare("ForwardList l25", l25, expected);
    expected = { 10, 20, 30, 40 };
    tests::compare("ForwardList l26", l26, expected);


    std::cout << "Testing moving range of element from other list\n\n";

    dsa::ForwardList<int> l27 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l28 = dsa::ForwardList<int>(expected_2);
    l27.splice_after(l27.begin(), l28, l28.begin(), l28.begin()[1]);
    expected = { 1, 2, 3, 4, 5 };
    tests::compare("ForwardList l27", l27, expected);
    expected = { 10, 20, 30, 40, 50 };
    tests::compare("ForwardList l28", l28, expected);

    dsa::ForwardList<int> l29 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l30 = dsa::ForwardList<int>(expected_2);
    l29.splice_after(l29.begin(), l30, l30.begin()[1], l30.begin()[3]);
    expected = { 1, 30, 2, 3, 4, 5 };
    tests::compare("ForwardList l29", l29, expected);
    expected = { 10, 20, 40, 50 };
    tests::compare("ForwardList l30", l30, expected);

    dsa::ForwardList<int> l31 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l32 = dsa::ForwardList<int>(expected_2);
    l31.splice_after(l31.begin(), l32, l32.begin(), l32.begin()[l32.size() - 1]);
    expected = { 1, 20, 30, 40, 2, 3, 4, 5 };
    tests::compare("ForwardList l31", l31, expected);
    expected = { 10, 50 };
    tests::compare("ForwardList l32", l32, expected);


    dsa::ForwardList<int> l33 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l34 = dsa::ForwardList<int>(expected_2);
    l33.splice_after(l33.begin()[2], l34, l34.begin(), l34.begin()[1]);
    expected = { 1, 2, 3, 4, 5 };
    tests::compare("ForwardList l33", l33, expected);
    expected = { 10, 20, 30, 40, 50 };
    tests::compare("ForwardList l34", l34, expected);

    dsa::ForwardList<int> l35 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l36 = dsa::ForwardList<int>(expected_2);
    l35.splice_after(l35.begin()[2], l36, l36.begin()[1], l36.begin()[3]);
    expected = { 1, 2, 3, 30, 4, 5 };
    tests::compare("ForwardList l35", l35, expected);
    expected = { 10, 20, 40, 50 };
    tests::compare("ForwardList l36", l36, expected);

    dsa::ForwardList<int> l37 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l38 = dsa::ForwardList<int>(expected_2);
    l37.splice_after(l37.begin()[2], l38, l38.begin(), l38.begin()[l38.size() - 1]);
    expected = { 1, 2, 3, 20, 30, 40, 4, 5 };
    tests::compare("ForwardList l37", l37, expected);
    expected = { 10, 50 };
    tests::compare("ForwardList l38", l38, expected);


    dsa::ForwardList<int> l39 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l40 = dsa::ForwardList<int>(expected_2);
    l39.splice_after(l39.begin()[l39.size() - 1], l40, l40.begin(), l40.begin()[1]);
    expected = { 1, 2, 3, 4, 5 };
    tests::compare("ForwardList l39", l39, expected);
    expected = { 10, 20, 30, 40, 50 };
    tests::compare("ForwardList l40", l40, expected);

    dsa::ForwardList<int> l41 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l42 = dsa::ForwardList<int>(expected_2);
    l41.splice_after(l41.begin()[l41.size() - 1], l42, l42.begin()[1], l42.begin()[3]);
    expected = { 1, 2, 3, 4, 5, 30 };
    tests::compare("ForwardList l41", l41, expected);
    expected = { 10, 20, 40, 50 };
    tests::compare("ForwardList l42", l42, expected);

    dsa::ForwardList<int> l43 = dsa::ForwardList<int>(expected_1);
    dsa::ForwardList<int> l44 = dsa::ForwardList<int>(expected_2);
    l43.splice_after(l43.begin()[l43.size() - 1], l44, l44.begin(), l44.begin()[l44.size() - 1]);
    expected = { 1, 2, 3, 4, 5, 20, 30, 40 };
    tests::compare("ForwardList l43", l43, expected);
    expected = { 10, 50 };
    tests::compare("ForwardList l44", l44, expected);

    return tests::failed;
}
