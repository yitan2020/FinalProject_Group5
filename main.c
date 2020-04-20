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

int main() {
    char operator[10];


    employee_t *head = NULL;
    BST_node* root = NULL;


    printf("Please select operations :\n");
    printf("1. List records\n");
    printf("2. Sort records\n");
    printf("3. Find records\n");
    printf("4. Add records \n");
    printf("5. Delete records \n");

    fgets(operator, 10, stdin);
    FLUSH;
    operator[strcspn(operator, "\n")] = 0;
    int i;
    i = strtol(operator, NULL, 0);
    switch (i) {
        case 1:
            readIn_LinkedList(&head);
            listRecord(head);
            break;
        case 2:
            sortOperation();
            break;
        case 3:
            findOperation();
            break;
        case 4:
            addOperation();
            break;
        case 5:
            deleteOperation(); 
            break;
        default:
            printf("2");

    }



    //employee_t *head = createList();

    //readIn(&head);
    //displayList(head);

    //writeOut(head);
    //removeList(&head);

    return 0;
}











