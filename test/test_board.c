#include "board.c"
#include "ctest.h"
#include <stdlib.h>

CTEST(figure_suite, pawn) {
    int t = pawn(1, 0, 3, 0);
    int f = pawn(4, 5, 5, 5);
    ASSERT_EQUAL(t, 1);
    ASSERT_NOT_EQUAL(f, 1);
}
CTEST(figure_suite, queen) {
    int t = queen(1, 6, 3, 4);
    int f = queen(4, 5, 6, 6);
    ASSERT_EQUAL(t, 1);
    ASSERT_NOT_EQUAL(f, 1);
}
CTEST(figure_suite, king) {
    int t = king(1, 0, 2, 0);
    int f = king(4, 5, 1, 5);
    ASSERT_EQUAL(t, 1);
    ASSERT_NOT_EQUAL(f, 1);
}
CTEST(figure_suite, bishop) {
    int t = bishop(4, 1, 3, 0);
    int f = bishop(6, 5, 5, 7);
    ASSERT_EQUAL(t, 1);
    ASSERT_NOT_EQUAL(f, 1);
}
CTEST(figure_suite, knight) {
    int t = knight(8, 0, 6, 1);
    int f = knight(4, 5, 5, 5);
    ASSERT_EQUAL(t, 1);
    ASSERT_NOT_EQUAL(f, 1);
}
CTEST(figure_suite, rook) {
    int t = rook(1, 0, 3, 0);
    int f = rook(4, 6, 5, 5);
    ASSERT_EQUAL(t, 1);
    ASSERT_NOT_EQUAL(f, 1);
}