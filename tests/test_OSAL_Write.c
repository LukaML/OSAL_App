/*
 * File:   test_FileSystem_Write.c
 * Author: Luka Maletic
 *
 * Created on 23 Sep 2020, 14:22:54
 */

#include "../OSALTestHeader.h"
#include "../Windows\OSALInit.h"
#include "../Windows\filesystem.h"


/*
 * CUnit Test Suite
 */



int init_suite(void) {
    OSAL_APIInit();
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testOSAL_Write_file_access_read() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    FILE* file = fopen(filePath, "w+");
    fclose(file);
    file = fopen(filePath, "r");
    CU_ASSERT_EQUAL(OSAL_Write(file, OSAL_WRITE_TEXT), OSAL_FAIL);
    fclose(file);
    remove(filePath);
}

void testOSAL_Write_empty_text_for_write() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    FILE* file = fopen(filePath, "w");
    CU_ASSERT_EQUAL(OSAL_Write(file, ""), OSAL_FAIL);
    fclose(file);
    remove(filePath);
}

void testOSAL_Write_file_with_write_access() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    FILE* file = fopen(filePath, "w");
    CU_ASSERT_EQUAL(OSAL_Write(file, OSAL_WRITE_TEXT), OSAL_OK);
    fclose(file);
    remove(filePath);
}

void testOSAL_Write_file_with_read_write_access() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    FILE* file = fopen(filePath, "a+");
    CU_ASSERT_EQUAL(OSAL_Write(file, OSAL_WRITE_TEXT), OSAL_OK);
    fclose(file);
    remove(filePath);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_Write", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_Write_file_access_read", testOSAL_Write_file_access_read))||
        (NULL == CU_add_test(pSuite, "testOSAL_Write_empty_text_for_write", testOSAL_Write_empty_text_for_write))||
        (NULL == CU_add_test(pSuite, "testOSAL_Write_file_with_write_access", testOSAL_Write_file_with_write_access))||
        (NULL == CU_add_test(pSuite, "testOSAL_Write_file_with_write_access", testOSAL_Write_file_with_write_access))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}