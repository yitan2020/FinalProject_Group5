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
    int rowCount = 0;

    rewind(frp);
    employee_t* current = *head;
    while (!feof(frp)) {

        fscanf(frp, "%f,%zu,%[^,],%s\n", &income, &SIN, firstName, lastName);
        if ((new_node = createNode_LinkedList(income, SIN, firstName, lastName)) != NULL) {

            if (current == NULL) {
                *head = new_node;
                current = new_node;
            } else {

                insertNode_LinkedList(new_node, head);
            }
        }
        rowCount++;

    }
    //}
    printf("File to load records from:%s ...%d records loaded \n", IN_FILE, rowCount);

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

void writeOutForLinkedList(employee_t * head) {

    int no = 1;
    FILE *fwp;
    char save[MAX_LEN];
    char override[MAX_LEN];

    printf("Save all records into file(Enter to skip):");
    fgets(save, MAX_LEN, stdin);
    FLUSH;
    save[strcspn(save, "\n")] = 0;

    if (!strlen(save)) {
        printf("Data was not saved");
        return;
    }


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

        fprintf(fwp, "%9f,%u,%s,%s\n", current->income, current->SIN, current->firstName, current->lastName);
        current = current->next;
    }
    fclose(fwp);


}

void writeOutForBST(BST_node* root, int option) {

    int no = 1;
    FILE* fwp;
    char save[MAX_LEN];
    char override[MAX_LEN];

    printf("Save all records into file(Enter to skip):");
    fgets(save, MAX_LEN, stdin);
    FLUSH;
    save[strcspn(save, "\n")] = 0;

    if (!strlen(save)) {
        printf("Data was not saved");
        return;
    }

    //if a file exits or not
    if ((fwp = fopen(save, "r")) != NULL) {
        printf("File %s already exist. Do you want to override it?(Y/N):", save);

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
    if (option == 1) {
        sortByAscendingForWriteout(root, fwp);
    } else {
        sortByDescendingForWriteout(root, fwp);
    }
    fclose(fwp);


}

void sortByAscendingForWriteout(BST_node* root, FILE* fwp) {
    if (root != NULL) {
        sortByAscendingForWriteout(root->leftChild, fwp);
        fprintf(fwp, "%9f,%u,%s,%s\n", root->income, root->SIN, root->firstName, root->lastName);
        sortByAscendingForWriteout(root->rightChild, fwp);
    }
}

void sortByDescendingForWriteout(BST_node* root, FILE* fwp) {
    if (root != NULL) {
        sortByDescendingForWriteout(root->rightChild, fwp);
        fprintf(fwp, "%9f,%u,%s,%s\n", root->income, root->SIN, root->firstName, root->lastName);
        sortByDescendingForWriteout(root->leftChild, fwp);
    }
}

// this function collect input from console and then create a new node of employee_t for the linked list

employee_t * createNewNode() {

    employee_t* node = NULL;
    
    size_t sin;
    do {
        sin = getSin();
    if (sin<100000000) {
            printf("Incorrect SIN. Please try again. \n");
        }
    } while (sin<100000000);
    char* firstName= NULL;
    do{
        firstName = getFirstName();
        if (strlen(firstName) == 0) {
            printf("First Name cannot be empty \n");
        }
    } while (strlen(firstName) ==0);
    
    char* lastName =NULL;
    do{
        lastName = getLastName();
        if (strlen(lastName) == 0) {
            printf("Last Name cannot be empty \n");
        }
    } while (strlen(lastName) ==0);
    float income = getIncome();
    
    node = (employee_t*) malloc(sizeof (employee_t));
    node->firstName = (char*) calloc(strlen(firstName) + 1, sizeof (char));
    strcpy(node->firstName, firstName);
    node->lastName = (char*) calloc(strlen(lastName) + 1, sizeof (char));
    strcpy(node->lastName, lastName);
    node->income = income;

    node->SIN = sin;

    node->next = NULL;
        //}
    //}
    return node;
    
}

void addOperation() {
    employee_t* head = NULL;
    readIn_LinkedList(&head);
    do {
    employee_t* newNode = createNewNode();
    if(head==NULL) {
        head = newNode;
    } else {
    insertNode_LinkedList(newNode, &head);
    }
    temp_BST == NULL;
    printf("Add another record(Y/N)? \n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);
    if (!(strcmp(temp_BST, "N"))) {
        break;
    }
    } while (1);
   

    writeOutForLinkedList(head);
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
            count = 0;
            do {
                SIN = getSin();
                if(SIN==0) {
                    break;
                }
                printf("Deleting record(s) with SIN \"%zd\": \n", SIN);
                deleteNodeBySIN(&head, SIN);
                if (count == 0) {
                    printf("no matching record! no deletion!\n");
                }
            } while (1);
            writeOutForLinkedList(head);
            break;
        case 2:
            count = 0;
            do {
                firstName = getFirstName();
                if(!(strcmp(firstName, ""))) {
                    break;
                }
                printf("Deleting record(s) with first name \"%s\": \n", firstName);
                deleteNodeByFirstName(&head, firstName);
                if (count == 0) {
                    printf("no matching record! no deletion!\n");
                }
            } while (1);
            free(firstName);
            writeOutForLinkedList(head);
            break;
        case 3:
            count = 0;
            do {
                lastName = getLastName();
                if(!(strcmp(lastName, ""))) {
                    break;
                }
                printf("Deleting record(s) with last name \"%s\": \n", lastName);

                deleteNodeByLastName(&head, lastName);
                if (count == 0) {
                    printf("no matching record! no deletion!\n");
                }
            } while (1);
            free(lastName);
            writeOutForLinkedList(head);
            break;
        case 4:
            count = 0;
            
            do {
                income = getIncome();
                if(income<0) {
                    break;
                }
                printf("Deleting record(s) with income \"%f\": \n", income);
                deleteNodeByIncome(&head, income);
                if (count == 0) {
                    printf("no matching record! no deletion!\n");
                }
            } while (1);
            writeOutForLinkedList(head);
            break;
        default:
            printf("Error! operator is not correct");
    }


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
    //delete the head， using the while loop for nodes that have the same value 
    while (!(strcmp((*head)->firstName, firstName))) {
        if ((*head)->next != NULL) {
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", (*head)->SIN, (*head)->firstName, (*head)->lastName, (*head)->income);
            removeFirst(head);
            count++;
        }
    }

    employee_t* current = *head;
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

    // delete the last node 
    current = *head;
    while (current->next != NULL) {
        current = current ->next;
    }
    if (!(strcmp(current->firstName, firstName))) {
        printf(" %zu      %-8s      %-8s      %-5.2f      \n", current->SIN, current->firstName, current->lastName, current->income);
        removeLast(head);
        count++;
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

BST_node* loadNode_BST(float income, size_t SIN, char firstName[], char lastName[]) {
    BST_node* bst = (BST_node*) malloc(sizeof (BST_node));
    bst->firstName = (char*) calloc(strlen(firstName) + 1, sizeof (char));
    bst->lastName = (char*) calloc(strlen(lastName) + 1, sizeof (char));


    if (bst == NULL || bst->firstName == NULL || bst->lastName == NULL) {
        printf("Cannot allocate memory for a node!\n");
        exit(-1);
    }

    bst->income = income;
    bst->SIN = SIN;
    strcpy(bst->firstName, firstName);
    strcpy(bst->lastName, lastName);

    bst->leftChild = NULL;
    bst->rightChild = NULL;

    return bst;


}

void insertNode_BST(BST_node** root, BST_node* node) {
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
    BST_node* root_result = NULL;

    int option;
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
    readIn_BST(&root);

    switch (option) {
        case 1:
            count=0;
            do {
                SIN = getSin();
                if(SIN==0) {
                    break;
                }
                printf("Displaying record(s) with SIN \"%zd\": \n", SIN);
                tree_traversalBySin(root, SIN, &root_result);
                if (count == 0) {
                    printf("no record found!\n");
                }
            } while (1);
            writeOutForBST(root_result, 1);
            break;
        case 2:
            count=0;
            do {
                firstName = getFirstName();
                if(!(strcmp(firstName, ""))) {
                    break;
                }
                printf("Displaying record(s) with first name \"%s\": \n", firstName);
                tree_traversalByFirstName(root, firstName, &root_result);
                if (count == 0) {
                    printf("no record found! \n");
                }
            } while (1);
            writeOutForBST(root_result, 1);
            free(firstName);
            break;
        case 3:
            count=0;
            do {
                lastName = getLastName();
                if(!(strcmp(lastName, ""))) {
                    break;
                }
                printf("Displaying record(s) with last name \"%s\": \n", lastName);
                tree_traversalByLastName(root, lastName, &root_result);
                if (count==0) {
                    printf("no record found!\n");
                }
            } while (1);
            writeOutForBST(root_result, 1);
            free(lastName);
            break;
        case 4:
            count=0;
            do {
                income = getIncome();
                if(income<0) {
                    break;
                }                
                printf("Displaying record(s) with income \"%5.2f\": \n", income);
                tree_traversalByIncome(root, income, &root_result);
                if (count==0) {
                    printf("no record found!\n");
                }
            } while (1);
            writeOutForBST(root_result, 1);
            break;
        default:
            printf("Error! operator is not correct");
    }



    displayBST(root);

}

//get the input of SIN from console

size_t getSin() {
    size_t SIN;
 
        printf("Please provide the SIN: \n");
        fgets(temp_BST, MAX_LEN, stdin);
        FLUSH;
        RMNR(temp_BST);

    SIN = (size_t) strtol(temp_BST, NULL, 0);


    return SIN;
}

//get the input of SIN from console

float getIncome() {
    char temp_BST[MAX_LEN];
    float income;

        printf("Please provide the income: (negative to skip) \n");
        fgets(temp_BST, MAX_LEN, stdin);
        FLUSH;
        RMNR(temp_BST);
        income = strtof(temp_BST, NULL);

    return income;
}

//get the input of first name from console

char* getFirstName() {

        printf("Please provide the first name: \n");
        fgets(temp_BST, MAX_LEN, stdin);
        FLUSH;
        RMNR(temp_BST);

    char* firstName = (char*) malloc((strlen(temp_BST) + 1) * sizeof (char));
    strcpy(firstName, temp_BST);

    return firstName;

}
//get the input of the last name from console

char* getLastName() {

        printf("Please provide the last name: \n");
        fgets(temp_BST, MAX_LEN, stdin);
        FLUSH;
        RMNR(temp_BST);

    char* lastName = (char*) malloc((strlen(temp_BST) + 1) * sizeof (char));
    strcpy(lastName, temp_BST);

    return lastName;

}

void tree_traversalBySin(BST_node* root, size_t SIN, BST_node** root_result) {

    BST_node* current = root;
    while (current != NULL && current->SIN != SIN) {
        current = (current->SIN > SIN) ? current->leftChild : current->rightChild;
    }
    if (current != NULL) {
        printf(" %zu      %-8s      %-8s      %-5.2f      \n", current->SIN, current->firstName, current->lastName, current->income);
        BST_node* newNode = loadNode_BST(current->income, current->SIN, current->firstName, current->lastName);
        if (*root_result == NULL) {
            *root_result = newNode;
        } else {
            insertNode_BST(root_result, newNode);
        }
        count++;
    }

}

void tree_traversalByIncome(BST_node* root, float income, BST_node** root_result) {

    if (root != NULL) {

        if (root->income == income) {
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", root->SIN, root->firstName, root->lastName, root->income);
            BST_node* newNode = loadNode_BST(root->income, root->SIN, root->firstName, root->lastName);
            if (*root_result == NULL) {
                *root_result = newNode;
            } else {
                insertNode_BST(root_result, newNode);
            }
            count++;
        }
        tree_traversalByIncome(root->leftChild, income, root_result);
        tree_traversalByIncome(root->rightChild, income, root_result);
    }

}

void tree_traversalByFirstName(BST_node* root, char* firstName, BST_node** root_result) {

    if (root != NULL) {
        if (!strcmp(root->firstName, firstName)) {
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", root->SIN, root->firstName, root->lastName, root->income);
            BST_node* newNode = loadNode_BST(root->income, root->SIN, root->firstName, root->lastName);
            if (*root_result == NULL) {
                *root_result = newNode;
            } else {
                insertNode_BST(root_result, newNode);
            }
            count++;
        }

        tree_traversalByFirstName(root->leftChild, firstName, root_result);
        tree_traversalByFirstName(root->rightChild, firstName, root_result);
    }
}

void tree_traversalByLastName(BST_node* root, char* lastName, BST_node** root_result) {

    if (root != NULL) {
        if (!strcmp(root->lastName, lastName)) {
            printf(" %zu      %-8s      %-8s      %-5.2f      \n", root->SIN, root->firstName, root->lastName, root->income);
            BST_node* newNode = loadNode_BST(root->income, root->SIN, root->firstName, root->lastName);
            if (*root_result == NULL) {
                *root_result = newNode;
            } else {
                insertNode_BST(root_result, newNode);
            }
            count++;
        }

        tree_traversalByLastName(root->leftChild, lastName, root_result);
        tree_traversalByLastName(root->rightChild, lastName, root_result);
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
    option = strtol(temp_BST, NULL, 0);
    temp_BST == NULL;

    printf("Please select order(1=Ascending, 2=Descending): \n");
    fgets(temp_BST, MAX_LEN, stdin);
    FLUSH;
    RMNR(temp_BST);

    switch (option) {
        case 1:
            readIn_BSTForSort(&root, 1);
            if (strtol(temp_BST, NULL, 0) == 1) {
                printf("Displaying records sorted by SIN in ascending order: \n");
                sortByAscending(root);
            } else {
                printf("Displaying records sorted by SIN in descending order: \n");
                sortByDescending(root);
            }
            break;
        case 2:
            readIn_BSTForSort(&root, 2);
            if (strtol(temp_BST, NULL, 0) == 1) {
                printf("Displaying records sorted by first name in ascending order: \n");
                sortByAscending(root);
            } else {
                printf("Displaying records sorted by first name in descending order: \n");
                sortByDescending(root);
            }
            break;
        case 3:
            readIn_BSTForSort(&root, 3);
            if (strtol(temp_BST, NULL, 0) == 1) {
                printf("Displaying records sorted by income in ascending order: \n");
                sortByAscending(root);
            } else {
                printf("Displaying records sorted by income in descending order: \n");
                sortByDescending(root);
            }
            break;
        case 4:
            readIn_BSTForSort(&root, 4);
            if (strtol(temp_BST, NULL, 0) == 1) {
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
        if (strcmp(node->firstName, parent->firstName) <= 0) {
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
        if (strcmp(node->lastName, parent->lastName) <= 0) {
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
    int rowCount = 0;

    rewind(frp);
    BST_node* current = *root;
    while (!feof(frp)) {

        fscanf(frp, "%f,%u,%[^,],%s\n", &income, &SIN, firstName, lastName);
        if ((new_node = loadNode_BST(income, SIN, firstName, lastName)) != NULL) {

            if (current == NULL) {
                *root = new_node;
                current = new_node;
            } else {

                insertNode_BST(root, new_node);
            }
        }
        rowCount++;

    }
    //}
    printf("File to load records from:%s ...%d records loaded \n", IN_FILE, rowCount);

    fclose(frp);
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
    int rowCount = 0;

    rewind(frp);
    BST_node* current = *root;
    while (!feof(frp)) {

        fscanf(frp, "%f,%u,%[^,],%s\n", &income, &SIN, firstName, lastName);
        if ((new_node = loadNode_BST(income, SIN, firstName, lastName)) != NULL) {

            if (current == NULL) {
                *root = new_node;
                current = new_node;
            } else {
                switch (option) {
                    case 1:
                        insertNode_BSTBySinForSort(root, new_node);
                        break;
                    case 2:
                        insertNode_BSTByFirstNameForSort(root, new_node);
                        break;
                    case 3:
                        insertNode_BSTByLastNameForSort(root, new_node);
                        break;
                    case 4:
                        insertNode_BSTByIncomeForSort(root, new_node);
                        break;
                }
            }
            rowCount++;

        }
        }
        printf("File to load records from:%s ...%d records loaded \n", IN_FILE, rowCount);

        fclose(frp);


    }
