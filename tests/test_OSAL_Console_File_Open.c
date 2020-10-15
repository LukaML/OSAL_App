/*
 * File:   test_OS_Open.c
 * Author: Luka Maletic
 *
 * Created on 22 Sep 2020, 09:34:01
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

void testOSAL_Console_File_Open_invalid_file() {
    char* name = "test4.txt";
    CU_ASSERT_EQUAL(OSAL_ConsoleFileOpen("", name), OSAL_FAIL);
}

void testOSAL_Console_File_Open_invalid_name_of_file() {
    char name[OSAL_FILE_NAME_MAX_LENGTH+1];
    int i = 0;
    while(OSAL_FILE_NAME_MAX_LENGTH + 1 > strlen(name))
    {
        name[i] = "a";
        i++;
    }
    CU_ASSERT_EQUAL(OSAL_ConsoleFileOpen("", name), OSAL_FAIL);
}

void testOSAL_Console_File_Open_empty_file_name() {
    char* name = "";
    CU_ASSERT_EQUAL(OSAL_ConsoleFileOpen("", name), OSAL_FAIL);
}

void testOSAL_Console_File_Open_read_file() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    HANDLE file = CreateFile(
        filePath,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    CloseHandle(file);
    CU_ASSERT_EQUAL(OSAL_ConsoleFileOpen("", OSAL_FILE_NAME), OSAL_OK);
    DeleteFileA(filePath);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_Console_File_Open", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_Console_File_Open_invalid_file", testOSAL_Console_File_Open_invalid_file))||
        (NULL == CU_add_test(pSuite, "testOSAL_Console_File_Open_invalid_name_of_file", testOSAL_Console_File_Open_invalid_name_of_file))||
        (NULL == CU_add_test(pSuite, "testOSAL_Console_File_Open_empty_file_name", testOSAL_Console_File_Open_empty_file_name))||
        (NULL == CU_add_test(pSuite, "testOSAL_Console_File_Open_read_file", testOSAL_Console_File_Open_read_file))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}