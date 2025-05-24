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
#include "List.h"

int main()
{
    std::cout << "Start ListSplice test:\n";

    bool res{};
    std::initializer_list<int> expected{};
    std::initializer_list<int> expected_1{ 1, 2, 3, 4, 5 };
    std::initializer_list<int> expected_2{ 10, 20, 30, 40, 50 };


    std::cout << "Testing moving other list\n\n";

    List<int> l1 = List<int>(expected_1);
    List<int> l2 = List<int>(expected_2);
    l1.splice(l1.begin(), l2);
    expected = { 1, 10, 20, 30, 40, 50, 2, 3, 4, 5 };
    res = if_error(l1, expected);
    std::cout << "List l1:\t" << l1 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = {};
    res = if_error(l2, expected);
    std::cout << "List l2:\t" << l2 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l3 = List<int>(expected_1);
    List<int> l4 = List<int>(expected_2);
    l3.splice(l3.begin()[3], l4);
    expected = { 1, 2, 3, 4, 10, 20, 30, 40, 50, 5 };
    res = if_error(l3, expected);
    std::cout << "List l3:\t" << l3 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = {};
    res = if_error(l4, expected);
    std::cout << "List l4:\t" << l4 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l5 = List<int>(expected_1);
    List<int> l6 = List<int>(expected_2);
    l5.splice(l5.begin()[l5.size() - 1], l6);
    expected = { 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 };
    res = if_error(l5, expected);
    std::cout << "List l5:\t" << l5 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = {};
    res = if_error(l6, expected);
    std::cout << "List l6:\t" << l6 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";


    std::cout << "Testing moving empty list\n\n";

    List<int> l7 = List<int>(expected_1);
    List<int> l8;
    l7.splice(l7.begin()[l7.size() - 1], l8);
    expected = expected_1;
    res = if_error(l7, expected);
    std::cout << "List l7:\t" << l7 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = {};
    res = if_error(l8, expected);
    std::cout << "List l8:\t" << l8 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";


    std::cout << "Testing moving one element from other list\n\n";

    List<int> l9 = List<int>(expected_1);
    List<int> l10 = List<int>(expected_2);
    l9.splice(l9.begin(), l10, l10.begin());
    expected = { 1, 20, 2, 3, 4, 5 };
    res = if_error(l9, expected);
    std::cout << "List l9:\t" << l9 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 30, 40, 50 };
    res = if_error(l10, expected);
    std::cout << "List l10:\t" << l10 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l11 = List<int>(expected_1);
    List<int> l12 = List<int>(expected_2);
    l11.splice(l11.begin(), l12, l12.begin()[2]);
    expected = { 1, 40, 2, 3, 4, 5 };
    res = if_error(l11, expected);
    std::cout << "List l11:\t" << l11 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 20, 30, 50 };
    res = if_error(l12, expected);
    std::cout << "List l12:\t" << l12 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l13 = List<int>(expected_1);
    List<int> l14 = List<int>(expected_2);
    l13.splice(l13.begin(), l14, l14.begin()[l14.size() - 2]);
    expected = { 1, 50, 2, 3, 4, 5 };
    res = if_error(l13, expected);
    std::cout << "List l13:\t" << l13 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 20, 30, 40 };
    res = if_error(l14, expected);
    std::cout << "List l14:\t" << l14 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";


    List<int> l15 = List<int>(expected_1);
    List<int> l16 = List<int>(expected_2);
    l15.splice(l15.begin()[3], l16, l16.begin());
    expected = { 1, 2, 3, 4, 20, 5 };
    res = if_error(l15, expected);
    std::cout << "List l15:\t" << l15 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 30, 40, 50 };
    res = if_error(l16, expected);
    std::cout << "List l16:\t" << l16 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l17 = List<int>(expected_1);
    List<int> l18 = List<int>(expected_2);
    l17.splice(l17.begin()[3], l18, l18.begin()[2]);
    expected = { 1, 2, 3, 4, 40, 5 };
    res = if_error(l17, expected);
    std::cout << "List l17:\t" << l17 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 20, 30, 50 };
    res = if_error(l18, expected);
    std::cout << "List l18:\t" << l18 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l19 = List<int>(expected_1);
    List<int> l20 = List<int>(expected_2);
    l19.splice(l19.begin()[3], l20, l20.begin()[l20.size() - 2]);
    expected = { 1, 2, 3, 4, 50, 5 };
    res = if_error(l19, expected);
    std::cout << "List l19:\t" << l19 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 20, 30, 40 };
    res = if_error(l20, expected);
    std::cout << "List l20:\t" << l20 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";


    List<int> l21 = List<int>(expected_1);
    List<int> l22 = List<int>(expected_2);
    l21.splice(l21.begin()[l21.size() - 1], l22, l22.begin());
    expected = { 1, 2, 3, 4, 5, 20 };
    res = if_error(l21, expected);
    std::cout << "List l21:\t" << l21 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 30, 40, 50 };
    res = if_error(l22, expected);
    std::cout << "List l22:\t" << l12 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l23 = List<int>(expected_1);
    List<int> l24 = List<int>(expected_2);
    l23.splice(l23.begin()[l23.size() - 1], l24, l24.begin()[3]);
    expected = { 1, 2, 3, 4, 5, 50 };
    res = if_error(l23, expected);
    std::cout << "List l23:\t" << l23 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 20, 30, 40 };
    res = if_error(l24, expected);
    std::cout << "List l24:\t" << l24 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l25 = List<int>(expected_1);
    List<int> l26 = List<int>(expected_2);
    l25.splice(l25.begin()[l25.size() - 1], l26, l26.begin()[l26.size() - 2]);
    expected = { 1, 2, 3, 4, 5, 50 };
    res = if_error(l25, expected);
    std::cout << "List l25:\t" << l25 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 20, 30, 40 };
    res = if_error(l26, expected);
    std::cout << "List l26:\t" << l26 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";


    std::cout << "Testing moving range of element from other list\n\n";

    List<int> l27 = List<int>(expected_1);
    List<int> l28 = List<int>(expected_2);
    l27.splice(l27.begin(), l28, l28.begin(), l28.begin()[1]);
    expected = { 1, 20, 2, 3, 4, 5 };
    res = if_error(l27, expected);
    std::cout << "List l27:\t" << l27 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 30, 40, 50 };
    res = if_error(l28, expected);
    std::cout << "List l28:\t" << l28 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l29 = List<int>(expected_1);
    List<int> l30 = List<int>(expected_2);
    l29.splice(l29.begin(), l30, l30.begin()[1], l30.begin()[3]);
    expected = { 1, 30, 40, 2, 3, 4, 5 };
    res = if_error(l29, expected);
    std::cout << "List l29:\t" << l29 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 20, 50 };
    res = if_error(l30, expected);
    std::cout << "List l30:\t" << l30 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l31 = List<int>(expected_1);
    List<int> l32 = List<int>(expected_2);
    l31.splice(l31.begin(), l32, l32.begin(), l32.begin()[l32.size() - 1]);
    expected = { 1, 20, 30, 40, 50, 2, 3, 4, 5 };
    res = if_error(l31, expected);
    std::cout << "List l31:\t" << l31 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10 };
    res = if_error(l32, expected);
    std::cout << "List l32:\t" << l32 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";


    List<int> l33 = List<int>(expected_1);
    List<int> l34 = List<int>(expected_2);
    l33.splice(l33.begin()[2], l34, l34.begin(), l34.begin()[1]);
    expected = { 1, 2, 3, 20, 4, 5 };
    res = if_error(l33, expected);
    std::cout << "List l33:\t" << l33 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 30, 40, 50 };
    res = if_error(l34, expected);
    std::cout << "List l34:\t" << l34 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l35 = List<int>(expected_1);
    List<int> l36 = List<int>(expected_2);
    l35.splice(l35.begin()[2], l36, l36.begin()[1], l36.begin()[3]);
    expected = { 1, 2, 3, 30, 40, 4, 5 };
    res = if_error(l35, expected);
    std::cout << "List l35:\t" << l35 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 20, 50 };
    res = if_error(l36, expected);
    std::cout << "List l36:\t" << l36 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l37 = List<int>(expected_1);
    List<int> l38 = List<int>(expected_2);
    l37.splice(l37.begin()[2], l38, l38.begin(), l38.begin()[l38.size() - 1]);
    expected = { 1, 2, 3, 20, 30, 40, 50, 4, 5 };
    res = if_error(l37, expected);
    std::cout << "List l37:\t" << l37 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10 };
    res = if_error(l38, expected);
    std::cout << "List l38:\t" << l38 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";


    List<int> l39 = List<int>(expected_1);
    List<int> l40 = List<int>(expected_2);
    //l39.splice(l40.size() - 1, l40, 0, 1);
    l39.splice(l39.begin()[l39.size() - 1], l40, l40.begin(), l40.begin()[1]);
    expected = { 1, 2, 3, 4, 5, 20 };
    res = if_error(l39, expected);
    std::cout << "List l39:\t" << l39 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 30, 40, 50 };
    res = if_error(l40, expected);
    std::cout << "List l40:\t" << l40 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l41 = List<int>(expected_1);
    List<int> l42 = List<int>(expected_2);
    l41.splice(l41.begin()[l41.size() - 1], l42, l42.begin()[1], l42.begin()[3]);
    expected = { 1, 2, 3, 4, 5, 30, 40 };
    res = if_error(l41, expected);
    std::cout << "List l41:\t" << l41 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10, 20, 50 };
    res = if_error(l42, expected);
    std::cout << "List l42:\t" << l42 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    List<int> l43 = List<int>(expected_1);
    List<int> l44 = List<int>(expected_2);
    l43.splice(l43.begin()[l43.size() - 1], l44, l44.begin(), l44.begin()[l44.size() - 1]);
    expected = { 1, 2, 3, 4, 5, 20, 30, 40, 50 };
    res = if_error(l43, expected);
    std::cout << "List l43:\t" << l43 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";
    expected = { 10 };
    res = if_error(l44, expected);
    std::cout << "List l44:\t" << l44 << '\n';
    std::cout << "Expected:\t" << expected << '\n';
    std::cout << (res == 0 ? "PASS" : "FAIL") << "\n\n";

    return tests::failed;
}
