/*
Yi Tan <tan5@sheridan.desire2learn.com>
----------------------------------------------------------------------
 */

/* 
 * File:   main.c
 * Author: Yi Tan <tan5@sheridan.desire2learn.com>
 *  Author: Bin Chen <chbi@sheridancollege.com>
 *
 * Created on April 2, 2020, 11:51 a.m.
 */

/*
Bin Chen <chbi@sheridancollege.com>
----------------------------------------------------------------------
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "function.h"


#define RMNR(name) name[strcspn(name,"\r\n")]=0
#define FLUSH stdin=freopen(NULL,"r",stdin)
#define MAX_LEN 50





// --------------------------------------
#define IN_FILE "input.csv"
#define OUT_FILE "input.csv"

int main() {
    char operator[10];


    employee_t *head = NULL;
    readIn(&head);
    while (1) {
        printf("Please select operations :");

        fgets(operator, 10, stdin);
        FLUSH;
        operator[strcspn(operator, "\n")] = 0;
        int i;
        i = strtof(operator, NULL);
        switch (i) {
            case 1:
                listRecord(head);
                break;
            case 2:
                printf("2");
                break;
            case 3:
                printf("3");
                break;
            case 4:
            {
                addRecord(&head);
                writeOut(head);
            }
                break;
            case 5:
                printf("5");
                break;
            default:
                printf("2");

        }
    }


    //employee_t *head = createList();

    //readIn(&head);
    //displayList(head);

    //writeOut(head);
    //removeList(&head);

    return 0;
}











