/*
Yi Tan <tan5@sheridan.desire2learn.com>
----------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "function.h"

typedef struct node {
    //char name[MAX_LEN];
    char* firstName;
    char* lastName;
    float income;
    size_t SIN;
    struct node* next;
} employee_t;

//create a list function



// -------------------------------------- 
//display a list function

void listRecord(employee_t* head) {

    int no = 1;
    printf("===============List of Records:=================== \n");
    printf("SIN        First Name   Last Name    Annual Income \n");
    printf("----------------------------------------------------\n");

    if (head == NULL) {
        printf("Linked List is empty.\n");
    } else {
        employee_t* current = head;
        while (current != NULL) {
            
            printf(" %zu      %s         %s           %5.2f      \n", current->SIN,current->firstName, current->lastName,current->income);
            current = current->next;
        }
        printf("\n");
    }
}


void readIn(employee_t **head) {
    FILE *frp;
    if ((frp = fopen(IN_FILE, "r")) == NULL) {
        perror("Could not open quotes file to input!\n");
        exit(1);
    }
    char firstName[MAX_LEN];
    char lastName[MAX_LEN];
    int no;
    float income;
    size_t SIN;
    employee_t *new_node = NULL, *current = NULL;
    current = *head;

    
    rewind(frp);
    while (!feof(frp)) {
        fscanf(frp, "%d,%f,%u,%[^,],%s\n", &no, &income, &SIN, firstName, lastName);
        
         if ((new_node = loadNode(income, SIN, firstName, lastName)) != NULL) {

            if (current == NULL) {
                *head = new_node;
                current = new_node;
            } else {

                insertNode(&new_node, head);
            }
         }
        
    }
    //}
    printf("File to load records from:%s \n",IN_FILE);

    fclose(frp);
}

employee_t* loadNode(float income, size_t SIN, char firstName[], char lastName[]) {

    employee_t* node = NULL;
    node = (employee_t*) malloc(sizeof (employee_t));
    node->firstName = (char*) calloc(strlen(firstName) + 1, sizeof (char));
    strcpy(node->firstName, firstName);
    node->lastName = (char*) calloc(strlen(lastName) + 1, sizeof (char));
    strcpy(node->lastName, lastName);
    node->income = income;
    //node->income = strtof(income, NULL);
    node->SIN = SIN;
    //node->SIN = (size_t) strtof(SIN, NULL);

    node->next = NULL;
    return node;
}

void writeOut(employee_t * head) {

    int no = 1;
    FILE *fwp;
    char save[MAX_LEN];
    char override[MAX_LEN];

    printf("Save all records in the file(Enter to skip):");
    fgets(save, MAX_LEN, stdin);
    FLUSH;
    save[strcspn(save, "\n")] = 0;


    //if a file exits or not
    if ((fwp = fopen(save, "r")) != NULL) {
        printf("File %s already exit. Do you want to override it?(Y/N):", save);

        fgets(override, MAX_LEN, stdin);
        FLUSH;
        override[strcspn(override, "\n")] = 0;
        if (strcmp(override, "N") > 0) {
            fwp = fopen(save, "w+");
            printf("Data saved in the file %s \n", save);
        } else {
            exit(1);
        }
    } else {

        fwp = fopen(save, "w");
        printf("Data saved in the file %s \n", save);
    }

    //save data to the file
    employee_t* current = head;
    while (current != NULL) {

        fprintf(fwp, "%d,%9f,%u,%s,%s\n", no++, current->income, current->SIN, current->firstName, current->lastName);
        current = current->next;
    }
    fclose(fwp);


}


// Your code goes below!!
// Declare the functions according to prototypes.

//create a node function

employee_t * createNode() {

    employee_t* node = NULL;


    char firstName[MAX_LEN] = {0};
    char lastName[MAX_LEN] = {0};
    char income[MAX_LEN] = {0};
    char SIN[MAX_LEN] = {0};


    do {
        printf("SIN: ");
        fgets(SIN, MAX_LEN, stdin);
        FLUSH;
        SIN[strcspn(SIN, "\n")] = 0;

        if (strlen(SIN) != 9) {
            printf("Incorrect SIN. Please try again. \n");

        }
    } while (strlen(SIN) != 9);

    do {
        printf("First Name:");
        fgets(firstName, MAX_LEN, stdin);
        FLUSH;
        firstName[strcspn(firstName, "\n")] = 0;

        if (strlen(firstName) < 1) {
            printf("First Name cannot be empty \n");
        }
    } while (strlen(firstName) < 1);

    do {

        printf("Last Name:");
        fgets(lastName, MAX_LEN, stdin);
        FLUSH;
        lastName[strcspn(lastName, "\n")] = 0;
        if (strlen(lastName) < 1) {
            printf("Last Name cannot be empty \n");
        }
    } while (strlen(lastName) < 1);

    do {
        printf("Annual Income:");
        fgets(income, MAX_LEN, stdin);
        FLUSH;
        income[strcspn(income, "\n")] = 0;

        if (!(strtof(income, NULL) > 0)) {
            printf("Incorrect value of GPA! Ignore student input!\n");
        }
    } while (!(strtof(income, NULL) > 0));

    if (strlen(firstName) > 1) {
        if (strtof(income, NULL) >= 0) {
            node = (employee_t*) malloc(sizeof (employee_t));
            if (node == NULL) {

                printf("Cannot allocate memory for a student!");
                exit(1);
            }
            node->firstName = (char*) calloc(strlen(firstName) + 1, sizeof (char));
            strcpy(node->firstName, firstName);
            node->lastName = (char*) calloc(strlen(lastName) + 1, sizeof (char));
            strcpy(node->lastName, lastName);
            node->income = strtof(income, NULL);
            node->SIN = (size_t) strtof(SIN, NULL);

            node->next = NULL;
        }
    }
    return node;
}

// --------------------------------------
//create a list function

void addRecord(employee_t **head) {
    //employee_t *new_node = NULL, *current = NULL, *head = NULL, *insert = NULL;
    employee_t *new_node = NULL, *current = NULL;
    current = *head;
    char readd[1];
    do {
        if ((new_node = createNode()) != NULL) {

            if (current == NULL) {
                *head = new_node;
                current = new_node;
            } else {

                insertNode(&new_node, head);
            }
            printf("Add another record(Y/N)? ");
            fgets(readd, MAX_LEN, stdin);
            FLUSH;
            readd[strcspn(readd, "\n")] = 0;

        };
    } while (strcmp(readd, "N") > 0);
    //return head;
}

// -------------------------------------- 


//insert a node function

void insertNode(employee_t** new_node, employee_t** head) {

    employee_t* current = *head;
    employee_t* insert = NULL;

    while (current != NULL) {
        if ((*new_node)->income >= current->income && *head == current) {

            (*new_node)->next = current;
            *head = *new_node;
            current = *head;
            break;
        } else if ((*new_node)->income < current->income && current->next == NULL) {

            current->next = *new_node;
            (*new_node)->next == NULL;
            current = *head;
            break;

        } else if ((*new_node)->income >= current->income) {

            (*new_node)->next = current;
            insert->next = *new_node;
            current = *head;

            break;

        }
        insert = current;
        current = current->next;
    }
}

//remove a list function

void removeList(employee_t** head) {

    if (*head == NULL) {
        printf("List is already empty.\n");

    } else {
        employee_t* current = *head;
        while (current->next != NULL) {

            *head = current->next;
            free(current->firstName);
            free(current);
            current = *head;
        }
        if ((*head)->next == NULL) {

            free((*head)->firstName);
            free(*head);
            *head = NULL;
        }
    }
}