#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

//struct representing BST
struct BST{
  char* word;
  int count;
  struct BST* left;
  struct BST* right;
};


// goal create a BST* struct given the data, count, left, right
// param data: char* representing the word
// param count: int representing the the frequency of the word
// param left: struct BST pointer representing the left BST pointer
// param right: struct BST pointer representing the right BST pointer
// return: a BST struct pointer with the specified fields
struct BST* makeBST(char* data, int count, struct BST* left, struct BST* right);

// goal to write  the BST tree given the root to an output.txt file
// param root: BST struct pointer representing the root of the tree
// param output: represents the file descriptor for output.txt
// param maxArr: int array representing the max word length and number of digits
void prtInorderBST(struct BST* root, int output, int maxArr[2]);


// goal insert a node to a tree and update max word length and count if needed
// param root: struct BST* representing the root of the tree
// param addNode: struct BST* representing the node that will be added to the tree
// param maxArr: int array representing the max word length and number of digits
struct BST* insert(struct BST* root, struct BST* addNode, int maxArr[2]);


// goal compare and nodes word value with word
// param curNode: BST* struct representing the current node that word is being compared to
// param word: char* representing the word of a node being inserted to the tree
// return: an int representing if the word is less, greater or equal to the nodes word
int BSTwordCompare(struct BST* curNode, char* word);


// goal free all allocated memory in a tree
// param root: BST* struct representing the root of a tree
void freeBST(struct BST* root);
#endif
