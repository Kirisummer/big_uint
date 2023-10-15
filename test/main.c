#include "tinytest.h"

#include "bitwise.h"
#include "hex.h"
#include "init.h"

TINYTEST_START_MAIN();
    TINYTEST_RUN_SUITE(BuiBitwise);
    TINYTEST_RUN_SUITE(BuiHex);
    TINYTEST_RUN_SUITE(BuiInit);
TINYTEST_END_MAIN();
