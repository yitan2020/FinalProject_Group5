/*
Yi Tan <tan5@sheridan.desire2learn.com>
----------------------------------------------------------------------
 */

/* 
 * File:   function.h
 * Author: Yi Tan <tan5@sheridan.desire2learn.com>
 *
 * Created on April 11, 2020, 12:06 a.m.
 */

#ifndef FUNCTION_H
#define FUNCTION_H

#define RMNR(name) name[strcspn(name,"\r\n")]=0
#define FLUSH stdin=freopen(NULL,"r",stdin)

#define MAX_LEN 50

// --------------------------------------
#define IN_FILE "input.txt"
#define OUT_FILE "input.csv"

typedef struct node employee_t;

typedef struct node_BST BST_node;
//functions for getting input from console
size_t getSin();
size_t getIncome();
char* getFirstName();
char* getLastName();

//functions for linked list 
employee_t* createNode(); // function to create the node
employee_t* createList(); // function to create the list
void listRecord(employee_t*); // function to display the list
void addRecord(employee_t**);
void readIn_LinkedList(employee_t**); //read data from file and created a linked list
employee_t * createNode_LinkedList(float, size_t, char[], char[]);
void writeOutForLinkedList(employee_t * head);
void insertNode_LinkedList(employee_t*, employee_t**); // function to insert node into the sorted linked list.
void removeList(employee_t**); // function to delete the linked list

void addOperation(); //function used to implement add operation
void deleteOperation(); //function to delete a node
void deleteNodeBySIN(employee_t**, size_t);// used inside of the deleteOperation() to remove the node
void deleteNodeByIncome(employee_t**, float);
void deleteNodeByFirstName(employee_t**, char*);
void deleteNodeByLastName(employee_t**, char*);
void removeLast(employee_t **);
void removeFirst(employee_t **);

//functions for BST 
void readIn_BST(BST_node**); 
void insertNode_BST(BST_node**, BST_node*);
BST_node* loadNode_BST(float, size_t, char[], char[]);
void displayBST(BST_node* root);  // just for testing purpose 
void tree_traversal(BST_node*);
void findOperation();
void tree_traversalBySin(BST_node*, size_t);
void tree_traversalByFirstName(BST_node*, char*);
void tree_traversalByLastName(BST_node* , char*);
void tree_traversalByIncome(BST_node*, float);
void searchByAttribute(BST_node*, int);
void sortByAscendingForWriteout(BST_node*, FILE*);
void sortByDescendingForWriteout(BST_node*, FILE*);
void writeOutForBST(BST_node*, int);

//functions for sort
void sortOperation();
void insertNode_BSTBySinForSort(BST_node**, BST_node*);
void insertNode_BSTByIncomeForSort(BST_node**, BST_node* ); 
void insertNode_BSTByFirstNameForSort(BST_node**, BST_node* );
void insertNode_BSTByLastNameForSort(BST_node**, BST_node* );
void sortByAscending(BST_node*);
void sortByDescending(BST_node*);
void readIn_BSTForSort(BST_node**, int);

#endif /* FUNCTION_H */

