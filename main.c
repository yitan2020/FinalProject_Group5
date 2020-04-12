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
    
    while (1) {
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
        i = strtol(operator, NULL,0);
        switch (i) {
            case 1:
                readIn_LinkedList(&head);
                listRecord(head);
                break;
            case 2:  
                printf("2");
                break;
            case 3:  
                //can find and display the search result but cannot save the result yet 
                //after each search, cannot go back to repeat the same attribute search 
                findOperation();
                break;
            case 4:
            {
                //addRecord(&head);
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











