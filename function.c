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
    char* firstName;
    char* lastName;
    float income;
    size_t SIN;
    struct node* next;
} employee_t;

struct node_BST {
    char* firstName;
    char* lastName;
    float income;
    size_t SIN;
    BST_node* leftChild;
    BST_node* rightChild;
};

int count; 
char temp_BST[MAX_LEN];
//create a list function



// -------------------------------------- 
//display a list function

void listRecord(employee_t* head) {

    int no = 1;
    printf("===============List of Records:=================== \n");
    printf("SIN             First Name   Last Name    Annual Income \n");
    printf("----------------------------------------------------\n");

    if (head == NULL) {
        printf("Linked List is empty.\n");
    } else {
        employee_t* current = head;
        while (current != NULL) {
            
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", current->SIN, current->firstName, current->lastName, current->income);
            current = current->next;
        }
        printf("\n");
    }
}

//read data from file and load to the new node for each record
//return the pointer of the head of the linked list which is sorted by the annual income
//in descending order  
void readIn_LinkedList(employee_t** head) {
    FILE *frp;
    if ((frp = fopen(IN_FILE, "r")) == NULL) {
        perror("Could not open quotes file to input!\n");  
        exit(1);
    }
    char firstName[MAX_LEN];
    char lastName[MAX_LEN];
    float income;
    size_t SIN;
    employee_t* new_node = NULL;

    rewind(frp);

    char buf[10000];

    int field_count=0;
    
    while(fgets(buf, 10000, frp)) {
        printf("File to load records from:%s \n",IN_FILE);
        field_count=0;
        RMNR(buf);
        // reference from https://codingboost.com/parsing-csv-files-in-c
        char* field =strtok(buf, ",");
        while(field) {
            if (field_count %4== 0) {
                income = strtof(field, NULL);
            }
            if (field_count %4== 1) {
                SIN =strtol(field, NULL,0);
            }
            if (field_count %4== 2) {
                strcpy(firstName, field);
            }
            if (field_count %4 == 3) {
                strcpy(lastName, field);
            }
            FLUSH;

            field_count++;

           if (field_count%4==0 && field_count>1) {
                new_node = loadNode_LinkedList(income, SIN, firstName, lastName);
                if(*head==NULL) {
                    *head = new_node;
                } else {
                    insertNode_LinkedList(new_node, head);
                }
            }

            field = strtok(NULL, ",");
        }
        
        printf("\n");

    }
    fclose(frp);
}

//used inside of the readIn function to create a node for each record 
employee_t* loadNode_LinkedList(float income, size_t SIN, char firstName[], char lastName[]) {

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
// used inside of the readIn function to add the node to the linked list 
//this is a sorted linked list by descending the Annual income
void insertNode_LinkedList(employee_t* new_node, employee_t** head) {

    employee_t* current = *head;
    employee_t* insert = NULL;
   

    while (current != NULL) {
        if (new_node->income >= current->income && *head == current) {

            new_node->next = current;
            *head = new_node;
            current = *head;
            break;
        } else if (new_node->income < current->income && current->next == NULL) {

            current->next = new_node;
            new_node->next == NULL;
            current = *head;
            break;

        } else if (new_node->income >= current->income) {

            new_node->next = current;
            insert->next = new_node;
            current = *head;

            break;

        }
        insert = current;
        current = current->next;
    }
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

/*
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
            printf("Incorrect income. Please try again.\n");
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
            node->SIN = (size_t) strtol(SIN, NULL);

            node->next = NULL;
        }
    }
    return node;
}
*/

// --------------------------------------
//create a list function

/*
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

                insertNode(new_node, head);
            }
            printf("Add another record(Y/N)? ");
            fgets(readd, MAX_LEN, stdin);
            FLUSH;
            readd[strcspn(readd, "\n")] = 0;

        };
    } while (strcmp(readd, "N") > 0);
    //return head;
}
*/

// -------------------------------------- 


//insert a node function



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

// below functions for BST FIND operation 
void findOperation() {
    BST_node* root = NULL;
    
    int option;

    do {
    printf("Please select the attribute (1=SIN, 2 =First Name, 3=Last Name, 4=Annual Income: \n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);
    option =strtof(temp_BST, NULL);   
    
    } while(option >4 || option <1 );
    
    temp_BST == NULL; 
    
    switch (option) {
            case 1: 
                readIn_BST(&root);
                findBySin(root);
                break;
            case 2: 
                readIn_BST(&root);
                do{
                findByFirstName(root);
                } while(temp_BST !=NULL);
                do{
                printf("Save displayed records in the file(Eneter to skip):\n");
                } while(temp_BST !=NULL); 
                break;
            case 3:
               readIn_BST(&root); 
               findByLastName(root);
               break;
            case 4: 
               readIn_BST(&root);
               findByIncome(root);
               break;
            default: 
                printf("Error! operator is not correct");
        }
    
  
    
    
}

void findBySin(BST_node* root) {
   
    char temp_BST[MAX_LEN];
    do {
    printf("Please provide the SIN you want to find: \n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);
   
    if (strlen(temp_BST) != 9) {
            printf("Incorrect SIN. Please try again. \n");
        }
    } while(strlen(temp_BST) !=9); 
    
    size_t SIN = (size_t) strtol(temp_BST, NULL,0);
    count=0;
    printf("Displaying record(s) with SIN \"%zd\": \n", SIN);
    tree_traversalBySin(root, SIN);
    
    if(count==0) {
        printf("No records found!");
    }
 
    
}
void findByIncome(BST_node* root) {

    char temp_BST[MAX_LEN];
    float income;
    do {
    printf("Please provide the income you want to find: \n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);
    if (strlen(temp_BST) <=0) {
            printf("Incorrect income. Please try again. \n");
        }
    } while(strlen(temp_BST) <=0); 
    income = strtof(temp_BST, NULL);
    
    

    count=0;
    printf("Displaying record(s) with SIN \"%5.2f\": \n", income);
    tree_traversalByIncome(root, income);
    
    if(count==0) {
        printf("No records found!");
    }
 
    
}
void findByFirstName(BST_node* root) {
    
   
    do {
    printf("Please provide the first name you want to find: (Press enter to skip)\n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);
    if (strlen(temp_BST) <=0) {
            printf("First Name cannot be empty \n");
        }
    } while(strlen(temp_BST) <=0); 
  
    count=0;
    printf("Displaying record(s) with first name \"%s\": \n", temp_BST);
    tree_traversalByFirstName(root,temp_BST);
     if(count==0) {
        printf("No records found!");
    }
    
}
void findByLastName(BST_node* root) {
    
    
    do {
    printf("Please provide the last name you want to find: \n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);
    if (strlen(temp_BST) <=0) {
            printf("last Name cannot be empty \n");
        }
    } while(strlen(temp_BST) <=0); 
    count=0;
    printf("Displaying record(s) with last name \"%s\": \n", temp_BST);
    tree_traversalByLastName(root,temp_BST);
     if(count==0) {
        printf("No records found!");
    }
    
}


void readIn_BST(BST_node** root) {
    FILE *frp;
    if ((frp = fopen(IN_FILE, "r")) == NULL) {
        perror("Could not open quotes file to input!\n");  
        exit(1);
    }
    char firstName[MAX_LEN];
    char lastName[MAX_LEN];
    float income;
    size_t SIN;
    BST_node* new_node = NULL;

    rewind(frp);

    char buf[10000];

    int field_count=0;
    int row_count=0;
    
    while(fgets(buf, 10000, frp)) {
        
        field_count=0;
        RMNR(buf);
        // reference from https://codingboost.com/parsing-csv-files-in-c
        char* field =strtok(buf, ",");
        while(field) {
            if (field_count %4== 0) {
                income = strtof(field, NULL);
                printf("Income:\t %f\n", income);
            }
            if (field_count %4== 1) {
                SIN =strtol(field, NULL,0);
                printf("SIN:\t %zd\n", SIN);
            }
            if (field_count %4== 2) {
                strcpy(firstName, field);
                printf("First Name:\t %s\n", firstName);
            }
            if (field_count %4 == 3) {
                strcpy(lastName, field);
                printf("Last Name:\t %s\n", lastName);
            }
            FLUSH;

            field_count++;

           if (field_count%4==0 && field_count>1) {
                new_node = loadNode_BST(income, SIN, firstName, lastName);
                row_count++;
                if(*root==NULL) {
                    *root = new_node;
                } else {
                    insertNode_BST(root,new_node);
                }
            }
            printf("the filed count is %d: \n", field_count);
            field = strtok(NULL, ",");
        }
        
        printf("\n");

    }
    fclose(frp);
    printf("File to load records from:%s ... %d records loaded\n",IN_FILE, row_count);
}

BST_node* loadNode_BST(float income, size_t SIN, char firstName[], char lastName[]) {
     BST_node* bst = (BST_node*) malloc(sizeof (BST_node));
     bst->firstName = (char*)calloc(strlen(firstName)+1, sizeof(char));
     bst->lastName = (char*)calloc(strlen(lastName)+1, sizeof(char));
     
     
    if (bst == NULL || bst->firstName ==NULL || bst->lastName ==NULL) {
        printf("Cannot allocate memory for a node!\n");
        exit(-1);
    }
    
     bst->income = income;
     bst->SIN = SIN;
     strcpy(bst->firstName, firstName);
     strcpy(bst->lastName,lastName);

    bst->leftChild = NULL;
    bst->rightChild = NULL;

    return bst;

    
}

void insertNode_BST(BST_node** root, BST_node* node){
    BST_node * current;
    BST_node* parent;

        current = *root;
        parent = NULL;
        do {
            parent = current;
            //go left from parent
            if (node->income < parent->income) {
                current = current ->leftChild;
                if (current == NULL) {
                    parent->leftChild = node;
                }
            } else {
                current = current ->rightChild;
                if (current == NULL) {
                    parent->rightChild = node;
                }
            }
        } while (current != NULL);
    
}

void displayBST(BST_node* root) {

    printf("===============List of Records:=================== \n");
    printf("SIN             First Name   Last Name    Annual Income \n");
    printf("----------------------------------------------------\n");

    if (root == NULL) {
        printf("List of employee is empty.\n");
    } else {
        tree_traversal(root);
    }
}
//inorder 
void tree_traversal(BST_node* root) {
    if (root != NULL) {
        tree_traversal(root->leftChild);
        printf(" %zu      %-8s      %-8s      %-5.2f      \n", root->SIN, root->firstName, root->lastName, root->income);
        tree_traversal(root->rightChild);
    }
}

void tree_traversalBySin(BST_node* root, size_t SIN) {
     
    if (root != NULL) {

        if(root->SIN == SIN) {
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", root->SIN, root->firstName, root->lastName, root->income);
            count++;
        }
        tree_traversalBySin(root->leftChild, SIN);
        tree_traversalBySin(root->rightChild, SIN);
    }
    
}

void tree_traversalByIncome(BST_node* root, float income) {
     
    if (root != NULL) {

        if(root->income == income) {
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", root->SIN, root->firstName, root->lastName, root->income);
            count++;
        }
        tree_traversalByIncome(root->leftChild, income);
        tree_traversalByIncome(root->rightChild, income);
    }
    
}

void tree_traversalByFirstName(BST_node* root, char firstName[]) {

    if (root != NULL) {
        if(! strcmp(root->firstName, firstName)) {
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", root->SIN, root->firstName, root->lastName, root->income);
            count++;
        }

        tree_traversalByFirstName(root->leftChild, firstName);
        tree_traversalByFirstName(root->rightChild, firstName);
    }
}
void tree_traversalByLastName(BST_node* root, char lastName[]) {

    if (root != NULL) {
        if(! strcmp(root->lastName, lastName)) {
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", root->SIN, root->firstName, root->lastName, root->income);
            count++;
        }
        
        tree_traversalByLastName(root->leftChild, lastName);
        tree_traversalByLastName(root->rightChild, lastName);
    }
}
