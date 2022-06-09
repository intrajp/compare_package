/*
 *  compare_package.c - compare package version 
 *  This file contains the contents of VULN_MASTER_AUTOMATE.
 * 
 *  Copyright (C) 2022 Shintaro Fujiwara
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301 USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "global.h"

/* Brief Print help for this application. */
static void __print_help(void)
{
    printf("\n VERSION %d.%d.%d\n", PROGRAM_VERSION, PROGRAM_RELEASE, PROGRAM_SUB_RELEASE);
    puts("\n Usage:\n");
    puts("   ./compare_package <package-a> <package-b>\n");
    puts("   Ex. ./compare_package 2.6.1 3.0.1");
    puts("   Ex. ./compare_package 2.6-1.5 2.6-2.1\n");
}

/* This static convert el related strings to a number. */
static char* __convert_el_related_strings_to_number(char* token)
{
    if (
            (strcmp(token, "x86_64") == 0) ||
            (strcmp(token, "noarch") == 0) ||
            (strcmp(token, "module") == 0))
        token = "";
    if (strcmp(token, "el5") == 0)
        token = "0";
    if (strcmp(token, "el5_1") == 0)
        token = "1";
    if (strcmp(token, "el5_2") == 0)
        token = "2";
    if (strcmp(token, "el5_3") == 0)
        token = "3";
    if (strcmp(token, "el5_4") == 0)
        token = "4";
    if (strcmp(token, "el5_5") == 0)
        token = "5";
    if (strcmp(token, "el5_6") == 0)
        token = "6";
    if (strcmp(token, "el5_7") == 0)
        token = "7";
    if (strcmp(token, "el5_8") == 0)
        token = "8";
    if (strcmp(token, "el5_9") == 0)
        token = "9";
    if (strcmp(token, "el6") == 0)
        token = "0";
    if (strcmp(token, "el6_1") == 0)
        token = "1";
    if (strcmp(token, "el6_2") == 0)
        token = "2";
    if (strcmp(token, "el6_3") == 0)
        token = "3";
    if (strcmp(token, "el6_4") == 0)
        token = "4";
    if (strcmp(token, "el6_5") == 0)
        token = "5";
    if (strcmp(token, "el6_6") == 0)
        token = "6";
    if (strcmp(token, "el6_7") == 0)
        token = "7";
    if (strcmp(token, "el6_8") == 0)
        token = "8";
    if (strcmp(token, "el6_9") == 0)
        token = "9";
    if (strcmp(token, "el7") == 0)
        token = "0";
    if (strcmp(token, "el7_1") == 0)
        token = "1";
    if (strcmp(token, "el7_2") == 0)
        token = "2";
    if (strcmp(token, "el7_3") == 0)
        token = "3";
    if (strcmp(token, "el7_4") == 0)
        token = "4";
    if (strcmp(token, "el7_5") == 0)
        token = "5";
    if (strcmp(token, "el7_6") == 0)
        token = "6";
    if (strcmp(token, "el7_7") == 0)
        token = "7";
    if (strcmp(token, "el7_8") == 0)
        token = "8";
    if (strcmp(token, "el7_9") == 0)
        token = "9";
    if (strcmp(token, "el8") == 0)
        token = "0";
    if (strcmp(token, "el8_1") == 0)
        token = "1";
    if (strcmp(token, "el8_2") == 0)
        token = "2";
    if (strcmp(token, "el8_3") == 0)
        token = "3";
    if (strcmp(token, "el8_4") == 0)
        token = "4";
    if (strcmp(token, "el8_5") == 0)
        token = "5";
    if (strcmp(token, "el8_6") == 0)
        token = "6";
    if (strcmp(token, "el8_7") == 0)
        token = "7";
    if (strcmp(token, "el8_8") == 0)
        token = "8";
    if (strcmp(token, "el8_9") == 0)
        token = "9";

    return token;
}

/* This static function sets delimitered strings into an given array. */
static void __set_token_to_arr(char* str_c, char arr[MAX_ARR_LENGTH][MAX_FILE_NAME_LENGTH], const char delim[2])
{
    char comp_c[MAX_FILE_NAME_LENGTH]= "";
    strncpy(comp_c, str_c,
         MAX_FILE_NAME_LENGTH - 1);
    char* token = ""; /* compare string would be set into this variable in while loop */
    int i = 0;

    /* get the first token */
    token = strtok(comp_c, delim);
    token = __convert_el_related_strings_to_number(token);
    //printf("first_token:%s\n", token);
    strncpy(arr[i], token,
        MAX_FILE_NAME_LENGTH - 1);

    i = i +1;
    /* walk throuth other tokens */
    while (token != NULL) {
        token = strtok(NULL, delim);
        if (token == NULL)
            break;
        token = __convert_el_related_strings_to_number(token);
        strncpy(arr[i], token,
            MAX_FILE_NAME_LENGTH - 1);
        //printf("%s\n", token);
        i++;
    }
}

/* This static function compares package version strings and returns number. */
static int __compare_package_strings(char arr_a[MAX_ARR_LENGTH][MAX_FILE_NAME_LENGTH], char arr_b[MAX_ARR_LENGTH][MAX_FILE_NAME_LENGTH])
{
    //Refer:https://www.enseignement.polytechnique.fr/informatique/INF478/docs/Cpp/en/c/string/byte/strtol.html
    int i = 0;
    // Base 36 
    int base = 36;
    char* endptr;
    long long num_a = 0;
    long long num_b = 0;
    int compared = 0;
    while (i < MAX_ARR_LENGTH) {
        if ((strcmp(arr_a[i], "") == 0) && (strcmp(arr_b[i], "") == 0))
            break;
        if ((strstr(arr_a[i], "-") == 0) && (strstr(arr_b[i], "-") == 0)) {
            num_a = strtoll(arr_a[i], &endptr, base);
            num_b = strtoll(arr_b[i], &endptr, base);
            //printf("arr_a[%d]:%s\n", i, arr_a[i]);
            //printf("arr_b[%d]:%s\n", i, arr_b[i]);
            //printf("num_a:%lld\n", num_a);
            //printf("num_b:%lld\n", num_b);
            if (num_a == num_b) {
                i++;
                continue;
            } else if (num_a > num_b)
                return 11;
            else if (num_a < num_b)
                return 12;
        } else {
            //puts("hyphen");
            const char delim_hyphen[2]= "-"; /* this is the delimiter period */
            char arr_a2[MAX_ARR_LENGTH][MAX_FILE_NAME_LENGTH];
            char arr_b2[MAX_ARR_LENGTH][MAX_FILE_NAME_LENGTH];
            __set_token_to_arr(arr_a[i], arr_a2, delim_hyphen);
            __set_token_to_arr(arr_b[i], arr_b2, delim_hyphen);
            compared = __compare_package_strings(arr_a2, arr_b2);
	    if (compared == 0) {
                i++;
                continue;
            }
	    return compared;
        }
        i++;
    }
    return 0;
}

/* Main function */
int main(int argc, char* argv[])
{
    char comp_a[MAX_FILE_NAME_LENGTH]= "";
    char comp_b[MAX_FILE_NAME_LENGTH]= "";
    if (argc != 3) {
        __print_help();
        return 0;
    }
    const char* str_null = "";
    if ((strcmp(argv[1], str_null) == 0) || (strcmp(argv[2], str_null) == 0)){
        //printf("argv[1]:%s\n", argv[1]);
        //printf("argv[2]:%s\n", argv[2]);
        __print_help();
        return 0;
    } else {
        strncpy(comp_a, argv[1],
                MAX_FILE_NAME_LENGTH - 1);
        strncpy(comp_b, argv[2],
                MAX_FILE_NAME_LENGTH - 1);
        char arr_a[MAX_ARR_LENGTH][MAX_FILE_NAME_LENGTH];
        char arr_b[MAX_ARR_LENGTH][MAX_FILE_NAME_LENGTH];
        int i = 0;
        while (i < MAX_ARR_LENGTH) {
            memset(arr_a[i], '\0', sizeof(arr_a[i][MAX_FILE_NAME_LENGTH]));
            memset(arr_b[i], '\0', sizeof(arr_b[i][MAX_FILE_NAME_LENGTH]));
            i++;
        }
        int compared = 0;
        const char delim_period[2]= "."; /* this is the delimiter period */
        __set_token_to_arr(comp_a, arr_a, delim_period);
        __set_token_to_arr(comp_b, arr_b, delim_period);
        compared = __compare_package_strings(arr_a, arr_b);
        if (compared == 0)
            return 0;
        else if (compared == 11)
            return 11;
        else if (compared == 12)
            return 12;
        else
            return 0;
    }
    __print_help();
    return 0;
}
