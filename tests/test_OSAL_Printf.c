/*
 * File:   test_OS_printf.c
 * Author: Luka Maletic
 *
 * Created on 14 Sep 2020, 13:39:21
 */

#include "../OSALTestHeader.h"
#include "../Windows\OSALInit.h"
#include "../Windows\console.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testOSAL_Printf_enable() {
    OSAL_PrintfEnable();
    char name[] = OSAL_PRINTF_STRING;
    CU_ASSERT_EQUAL(OSAL_Printf(name), OSAL_OK);
}

void testOSAL_Printf_disable() {
    OSAL_PrintfDisable();
    char name[] = OSAL_PRINTF_STRING;
    CU_ASSERT_EQUAL(OSAL_Printf(name), OSAL_FAIL);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_Printf", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_Printf_enable", testOSAL_Printf_enable))||
        (NULL == CU_add_test(pSuite, "testOSAL_Printf_disable", testOSAL_Printf_disable))    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}