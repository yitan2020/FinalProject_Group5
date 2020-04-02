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

#define RMNR(name) name[strcspn(name,"\r\n")]=0
#define FLUSH stdin=freopen(NULL,"r",stdin)
#define MAX_LEN 50

typedef struct node {
    //char name[MAX_LEN];
    char *firstName;
    char *lastName;
    float income;
    size_t SIN;
    struct node* next;
} student_t;

// --------------------------------------
student_t* createNode(); // function to create the node
student_t* createList(); // function to create the list
void listRecord(student_t*); // function to display the list
void addRecord(student_t**);
void readIn(student_t**);
student_t * loadNode(float, size_t, char[], char[]);
void writeOut(student_t*);
void insertNode(student_t**, student_t**); // function to insert node into the sorted list.
void removeList(student_t**); // function to delete the linked list

// --------------------------------------
#define IN_FILE "input.csv"
#define OUT_FILE "input.csv"

int main() {
    char operator[10];


    student_t *head = NULL;
    readIn(&head);
    while (1) {
        printf("Please select operation :");

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


    //student_t *head = createList();

    //readIn(&head);
    //displayList(head);

    //writeOut(head);
    //removeList(&head);

    return 0;
}

void readIn(student_t **head) {
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
    student_t *new_node = NULL, *current = NULL;
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

student_t * loadNode(float income, size_t SIN, char firstName[], char lastName[]) {

    student_t* node = NULL;
    node = (student_t*) malloc(sizeof (student_t));
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

void writeOut(student_t * head) {

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
    student_t* current = head;
    while (current != NULL) {

        fprintf(fwp, "%d,%9f,%u,%s,%s\n", no++, current->income, current->SIN, current->firstName, current->lastName);
        current = current->next;
    }
    fclose(fwp);


}


// Your code goes below!!
// Declare the functions according to prototypes.

//create a node function

student_t * createNode() {

    student_t* node = NULL;


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
            node = (student_t*) malloc(sizeof (student_t));
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

void addRecord(student_t **head) {
    //student_t *new_node = NULL, *current = NULL, *head = NULL, *insert = NULL;
    student_t *new_node = NULL, *current = NULL;
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
//display a list function

void listRecord(student_t * head) {

    int no = 1;
    printf("===============List of Records:=================== \n");
    printf("SIN        First Name   Last Name    Annual Income \n");
    printf("----------------------------------------------------\n");

    if (head == NULL) {
        printf("Linked List is empty.\n");
    } else {
        student_t* current = head;
        while (current != NULL) {
            
            printf(" %zu      %s         %s           %5.2f      \n", current->SIN,current->firstName, current->lastName,current->income);
            current = current->next;
        }
        printf("\n");
    }
}

//insert a node function

void insertNode(student_t** new_node, student_t** head) {

    student_t* current = *head;
    student_t* insert = NULL;

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

void removeList(student_t** head) {

    if (*head == NULL) {
        printf("List is already empty.\n");

    } else {
        student_t* current = *head;
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









