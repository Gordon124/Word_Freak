#ifndef TEXTMOD_H
#define TEXTMOD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>
#include "bst.h"

// goal print any errors from file descriptor
// param fd: int representing the fiel descriptor
void errorCheck(int fd);

// goal check to see if read is reading less than the set amount of bytes and if words are cut off
// param readFile: int representing the file descriptor for file being read
// param openFile: int representing the file descriptor for file being opened
// param buf[]: char array buffer that contains what is read
// param bufSize: int representing size of buffer
void checkRead(int readFile, int openFile, char buf[], int bufSize);

// goal make BST nodes  with tokenize words as data from the buffer and insert them to the tree 
// param buf[]: buffer that contains the bytes from read 
// param BSTArr: 
// param buf[]: buffer that contains what is read
// param bufSize: size of buffer
void processLine(char buf[],struct BST* BSTArr[26], char delims[], int maxArr[2]);

// goal return the corresponding index for the BST struct pointer array given letter
// param firstLetter: char representing the first letter of the data in a node
// return the index of BST* array given a letter
int letterToIndex(char firstLetter);

// goal compares the nodes data and count with the arrays current max update max if nodes values are greater
// param maxArr: int array representing the current max word length and max frequency
// param node: BST* struct pointer representing the node data and count being compared with maxArr
void checkMax(int maxArr[2], struct BST* node);

#endif
