/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Luka Maletic
 *
 * Created on 14 September 2020, 10:40
 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include <winbase.h>
#include <windows.h>
#include <string.h>
#include "OSAL.h"
#include <io.h>
#include <fcntl.h>
/*
 * 
 */


int main(void){
    OSAL_APIInit();
    // primjer kreiranje fodlera "folder" u C:\Temp
    OSAL_CreateDirectory("", "folder");
    
    // primjer kreiranje fodlera "opet" u C:\Temp\folder
    OSAL_CreateDirectory("folder", "opet");
    
    // primjer kreiranje fajla "test.txt" u C:\Temp\folder\opet
    FILE* f = OSAL_Create("folder opet","test.txt", "r/w");
    
    // primjer zatvaranja fajla "test.txt" u C:\Temp\folder\opet
    OSAL_Close(f);
    
    // primjer otvaranja fajla "test.txt" u C:\Temp\folder\opet
    f = OSAL_Open("folder opet", "test.txt", "w");
    
    // primjer upisa i zatvaranja fajla "test.txt" u C:\Temp\folder\opet
    OSAL_Write(f, "test test test!");
    OSAL_Close(f);
    
    // primjer otvaranja, citanja i zatvaranja fajla "test.txt" u C:\Temp\folder\opet
    f = OSAL_Open("folder opet",  "test.txt", "r");
    char buffer[15];
    OSAL_Read(f, buffer, strlen("test test test!"), 2);
    OSAL_Printf(buffer);
    OSAL_Close(f);
    
    // primjer kreiranje foldera "brisi" u C:\Temp\folder\opet
    OSAL_CreateDirectory("folder opet" ,"brisi");
    
    // primjer kreiranje i zatvaranja fajla "test.txt" u C:\Temp\folder\opet\brisi
    f = OSAL_Create("folder opet brisi", "test.txt", "r/w");
    OSAL_Close(f);
    
    // primjer brisanja foldera "brisi" u C:\Temp\folder\opet\brisi
    OSAL_RemoveDirectory("folder opet", "brisi");
    
    // primjer kreiranja foldera "e" u C:\Temp\folder\opet
    OSAL_CreateDirectory("folder opet", "e");
    
    // primjer kreiranja i zatvaranja fajla "test.txt" u C:\Temp\folder\opet\e
    f = OSAL_Create("folder opet e","test.txt", "r/w");
    OSAL_Close(f);
    
    // primjer kreiranja foldera "oop" u C:\Temp\folder\opet\e
    OSAL_CreateDirectory("folder opet e", "oop");
    
    // primjer otvaranja fajla "test.txt" u konzoli iz C:\Temp\folder\opet\e
    OSAL_ConsoleFileOpen("folder opet e", "test.txt");
    return 0;
}

