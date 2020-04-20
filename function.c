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
                new_node = createNode_LinkedList(income, SIN, firstName, lastName);
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

//used inside of the readIn function to create a node for each record in the file
employee_t* createNode_LinkedList(float income, size_t SIN, char firstName[], char lastName[]) {

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
// used inside of the readIn function to add the node to the front of linked list 
void insertNode_LinkedList(employee_t* new_node, employee_t** head) {

    employee_t* current = *head;
    employee_t* insert = NULL;
    
    new_node->next = *head;
    *head = new_node;
   
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

// this function collect input from console and then create a new node of employee_t for the linked list
employee_t * createNewNode() {

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
            node->SIN = (size_t) strtol(SIN, NULL,0);

            node->next = NULL;
        }
    }
    return node;
}


void addOperation() {
    employee_t* head = NULL;
    readIn_LinkedList(&head);
    
    employee_t* newNode = createNewNode();
    insertNode_LinkedList(newNode,  &head);
    
     listRecord(head);
    
    
}

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

void deleteOperation() {
    int option;
    employee_t* head = NULL;
    count = 0;
    size_t SIN;
    float income;
    char* firstName;
    char* lastName;

    printf("Please select the attribute (1=SIN, 2 =First Name, 3=Last Name, 4=Annual Income: \n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);
    option = strtol(temp_BST, NULL, 0);
    temp_BST == NULL;

    readIn_LinkedList(&head);

    switch (option) {
        case 1:
            SIN = getSin();
            printf("Deleting record(s) with SIN \"%zd\": \n", SIN);
            count = 0;
            deleteNodeBySIN(&head, SIN);
            if(count==0) {
                printf("no matching record! no deletion!\n");
            }
            break;
        case 2:
            firstName = getFirstName();
            printf("Deleting record(s) with first name \"%s\": \n", firstName);
            count=0;
            deleteNodeByFirstName(&head, firstName);
            if(count==0) {
                printf("no matching record! no deletion!\n");
            }
            free(firstName);
            break;
        case 3:
            lastName = getLastName();
            printf("Deleting record(s) with last name \"%s\": \n", lastName);
            count=0;
            deleteNodeByLastName(&head, lastName);
            if(count==0) {
                printf("no matching record! no deletion!\n");
            }
            free(lastName);
            break;
        case 4:
            income = getIncome();
            printf("Deleting record(s) with income \"%f\": \n", income);
            count = 0;
            deleteNodeByIncome(&head, income);
            if(count==0) {
                printf("no matching record! no deletion!\n");
            }
            break;
        default:
            printf("Error! operator is not correct");
    }

    listRecord(head);



}

void deleteNodeBySIN(employee_t** head, size_t SIN) {

    //if the list has only one node and this node is the one needed to be deleted
    while ((*head)->SIN == SIN) {
        if ((*head)->next != NULL) {
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", (*head)->SIN, (*head)->firstName, (*head)->lastName, (*head)->income);
            removeFirst(head);
            count++;
        }
    }

    employee_t* current = *head;
    while (current->next != NULL) {
        current = current ->next;
    }
    if (current->SIN == SIN) {
        printf(" %zu      %-8s      %-8s      %-5.2f      \n", current->SIN, current->firstName, current->lastName, current->income);
        removeLast(head);
        count++;
    }

    current = *head;
    employee_t* temp = NULL;
    while (current->next != NULL) {
        if (current->next ->SIN == SIN) {
            temp = current->next;
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", temp->SIN, temp->firstName, temp->lastName, temp->income);
            current->next = current->next->next;
            free(temp);
            count++;
        }
        current = current ->next;

    }

}

void deleteNodeByIncome(employee_t** head, float income) {

    //if the list has only one node and this node is the one needed to be deleted
    while ((*head)->income == income) {
        if ((*head)->next != NULL) {
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", (*head)->SIN, (*head)->firstName, (*head)->lastName, (*head)->income);
            removeFirst(head);
            count++;
        }
    }

    employee_t* current = *head;
    while (current->next != NULL) {
        current = current ->next;
    }
    if (current->income == income) {
        current = *head;
        printf(" %zu      %-8s      %-8s      %-5.2f      \n", current->SIN, current->firstName, current->lastName, current->income);
        removeLast(head);
        count++;
    }

    current = *head;
    employee_t* temp = NULL;
    while (current->next != NULL) {
        if (current->next ->income == income) {
            temp = current->next;
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", temp->SIN, temp->firstName, temp->lastName, temp->income);
            current->next = current->next->next;
            free(temp);
            count++;
        }
        current = current ->next;
    }

}

void deleteNodeByFirstName(employee_t** head, char* firstName) {
    //if the list has only one node and this node is the one needed to be deleted
    while (strcmp((*head)->firstName, firstName) == 0) {
        if ((*head)->next != NULL) {
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", (*head)->SIN, (*head)->firstName, (*head)->lastName, (*head)->income);
            removeFirst(head);
            count++;
        }
    }
    // delete the last node 
    employee_t* current = *head;
    while (current->next != NULL) {
        current = current ->next;
    }
    if (strcmp(current->firstName, firstName) == 0) {
        printf(" %zu      %-8s      %-8s      %-5.2f      \n", current->SIN, current->firstName, current->lastName, current->income);
        removeLast(head);
        count++;
    }

    current = *head;
    employee_t* temp = NULL;
    while (current->next != NULL) {
        if (strcmp(current->next ->firstName, firstName) == 0) {
            temp = current->next;
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", temp->SIN, temp->firstName, temp->lastName, temp->income);
            current->next = current->next->next;
            free(temp);
            count++;
        }
        current = current ->next;
    }


}

void deleteNodeByLastName(employee_t** head, char* lastName) {
    //if the list has only one node and this node is the one needed to be deleted
    while (strcmp((*head)->lastName, lastName) == 0) {
        if ((*head)->next != NULL) {
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", (*head)->SIN, (*head)->firstName, (*head)->lastName, (*head)->income);
            removeFirst(head);
            count++;
        }
    }
    // delete the last node 
    employee_t* current = *head;
    while (current->next != NULL) {
        current = current ->next;
    }
    if (strcmp(current->lastName, lastName) == 0) {
        printf(" %zu      %-8s      %-8s      %-5.2f      \n", current->SIN, current->firstName, current->lastName, current->income);
        removeLast(head);
        count++;
    }

    current = *head;
    employee_t* temp = NULL;
    while (current->next != NULL) {
        if (strcmp(current->next ->lastName, lastName) == 0) {
            temp = current->next;
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", temp->SIN, temp->firstName, temp->lastName, temp->income);
            current->next = current->next->next;
            free(temp);
            count++;
        }
        current = current ->next;
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
            if (node->SIN < parent->SIN) {
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

// below functions for BST FIND operation 
void findOperation() {
    BST_node* root = NULL;
    
    int option;
    count=0;
    size_t SIN;
    float income;
    char* firstName;
    char* lastName;

    
    printf("Please select the attribute (1=SIN, 2 =First Name, 3=Last Name, 4=Annual Income: \n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);
    option =strtol(temp_BST, NULL,0);   
    temp_BST == NULL; 
    readIn_BST(&root);  

 
    switch (option) {
            case 1: 
                SIN = getSin();
                printf("Displaying record(s) with SIN \"%zd\": \n", SIN);
                count=0;
                tree_traversalBySin(root, SIN);                 
                break;
            case 2: 
                count=0;
                firstName = getFirstName();
                printf("Displaying record(s) with first name \"%s\": \n", firstName);
                tree_traversalByFirstName(root,firstName); 
                free(firstName);
                break;
            case 3:
               count=0;
                lastName = getLastName();
                printf("Displaying record(s) with last name \"%s\": \n", lastName);
                tree_traversalByLastName(root,lastName); 
                free(lastName);
               break;
            case 4: 
                income=getIncome();
                printf("Displaying record(s) with income \"%5.2f\": \n", income);
                count=0;
                tree_traversalByIncome(root,income);
                break;
            default: 
                printf("Error! operator is not correct");
        }
    
    if(count==0) {
                printf("No records found!\n");
            }

      displayBST(root);
    
    
}

//get the input of SIN from console
size_t getSin() {
    size_t SIN;
    do {
    printf("Please provide the SIN: \n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);
   
    
    if (strlen(temp_BST) != 9) {
            printf("Incorrect SIN. Please try again. \n");
        }

    } while(strlen(temp_BST) <9); 
    
    SIN = (size_t) strtol(temp_BST, NULL,0);
    
    
    return SIN;
}

//get the input of SIN from console
size_t getIncome() {
    char temp_BST[MAX_LEN];
    float income;
    //do {
    printf("Please provide the income: \n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);
/*
    if (strlen(temp_BST) <=0) {
            printf("Incorrect income. Please try again. \n");
        }
*/
    //} while(strlen(temp_BST) <=0); 
    income = strtof(temp_BST, NULL);
    
    return income;
}

//get the input of first name from console
char* getFirstName() {
   // do {
    printf("Please provide the first name: (Press enter to skip)\n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);
/*
    if (strlen(temp_BST) <0) {
            printf("First Name cannot be empty \n");
        }
*/
    //} while(strlen(temp_BST) <0); 

    char* firstName = (char*) malloc((strlen(temp_BST)+1)*sizeof(char));
    strcpy(firstName, temp_BST);
    

    return firstName;
    
 
}
//get the input of the last name from console
char* getLastName() {
    //do {
    printf("Please provide the last name: (Press enter to skip)\n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);
/*
    if (strlen(temp_BST) <0) {
            printf("First Name cannot be empty \n");
        }
*/
    //} while(strlen(temp_BST) <0); 

    char* lastName = (char*) malloc((strlen(temp_BST)+1)*sizeof(char));
    strcpy(lastName, temp_BST);
    

    return lastName;
    
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

void tree_traversalByFirstName(BST_node* root, char* firstName) {

    if (root != NULL) {
        if(! strcmp(root->firstName, firstName)) {
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", root->SIN, root->firstName, root->lastName, root->income);
            count++;
        }

        tree_traversalByFirstName(root->leftChild, firstName);
        tree_traversalByFirstName(root->rightChild, firstName);
    }
}
void tree_traversalByLastName(BST_node* root, char* lastName) {

    if (root != NULL) {
        if(! strcmp(root->lastName, lastName)) {
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", root->SIN, root->firstName, root->lastName, root->income);
            count++;
        }
        
        tree_traversalByLastName(root->leftChild, lastName);
        tree_traversalByLastName(root->rightChild, lastName);
    }
}

void removeFirst(employee_t **head) {
    if (*head == NULL) {
        printf("Linked List is already empty!");
    } else {
        employee_t *toDelete = *head;
        //*head=(*head)->next;
        *head = toDelete->next;
        free(toDelete);
    }
}

void removeLast(employee_t ** head) {
    if (*head == NULL) {
        printf("Linked List is already empty!");
    } else if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    } else {
        employee_t * current = *head;
        while (current->next->next != NULL) {

            current = current ->next;
        }
        free(current->next);
        current->next = NULL;

    }

}

void sortOperation() {
    
    BST_node* root = NULL;
    int option;
    //read the record in the file and create a linked list 
    printf("Please select the attribute (1=SIN, 2 =First Name, 3=Last Name, 4=Annual Income: \n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);
    option =strtol(temp_BST, NULL,0);   
    temp_BST == NULL;
    
    printf("Please select order(1=Ascending, 2=Descending): \n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);
    
    switch (option) {
        case 1: 
            readIn_BSTForSort(&root, 1);
            if(strtol(temp_BST, NULL, 0)==1) {
                printf("Displaying records sorted by SIN in ascending order: \n");
               sortByAscending(root);
            } else {
                printf("Displaying records sorted by SIN in descending order: \n");
                sortByDescending(root);
            }
            break;
        case 2: 
            readIn_BSTForSort(&root, 2);
            if(strtol(temp_BST, NULL, 0)==1) {
                printf("Displaying records sorted by first name in ascending order: \n");
               sortByAscending(root);
            } else {
                printf("Displaying records sorted by first name in descending order: \n");
                sortByDescending(root);
            }
            break;
        case 3:
            readIn_BSTForSort(&root, 3);
            if(strtol(temp_BST, NULL, 0)==1) {
                printf("Displaying records sorted by income in ascending order: \n");
               sortByAscending(root);
            } else {
                printf("Displaying records sorted by income in descending order: \n");
                sortByDescending(root);
            }
            break;
        case 4:
            readIn_BSTForSort(&root, 4);
            if(strtol(temp_BST, NULL, 0)==1) {
                printf("Displaying records sorted by income in ascending order: \n");
               sortByAscending(root);
            } else {
                printf("Displaying records sorted by income in descending order: \n");
                sortByDescending(root);
            }
            break;
        default:
            printf("Error! operator is not correct");
    }
    
}
void insertNode_BSTByFirstNameForSort(BST_node** root, BST_node* node) {
    BST_node * current;
    BST_node* parent;

        current = *root;
        parent = NULL;
        do {
            parent = current;
            //go left from parent
            if (node->firstName <= parent->firstName) {
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
void insertNode_BSTByLastNameForSort(BST_node** root, BST_node* node) {
    BST_node * current;
    BST_node* parent;

        current = *root;
        parent = NULL;
        do {
            parent = current;
            //go left from parent
            if (strcmp(node->lastName, parent->lastName)<=0) {
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
void insertNode_BSTBySinForSort(BST_node** root, BST_node* node) {
    BST_node * current;
    BST_node* parent;

        current = *root;
        parent = NULL;
        do {
            parent = current;
            //go left from parent
            if (node->SIN < parent->SIN) {
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
void insertNode_BSTByIncomeForSort(BST_node** root, BST_node* node) {
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
void sortByAscending(BST_node* root) {
    if (root != NULL) {
        sortByAscending(root->leftChild);
        printf(" %zu      %-8s      %-8s      %-5.2f      \n", root->SIN, root->firstName, root->lastName, root->income);
        sortByAscending(root->rightChild);
    }
}
void sortByDescending(BST_node* root) {
    if (root != NULL) {
        sortByDescending(root->rightChild);
        printf(" %zu      %-8s      %-8s      %-5.2f      \n", root->SIN, root->firstName, root->lastName, root->income);
        sortByDescending(root->leftChild);
    }
}
void readIn_BSTForSort(BST_node** root, int option) {
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
                    switch (option) {
                        case 1: 
                            insertNode_BSTBySinForSort(root,new_node);
                            break;
                        case 2: 
                            insertNode_BSTByFirstNameForSort(root,new_node);
                            break;
                        case 3: 
                            insertNode_BSTByLastNameForSort(root,new_node);
                            break;
                        case 4: 
                            insertNode_BSTByIncomeForSort(root,new_node);
                            break;
                    }
                    
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