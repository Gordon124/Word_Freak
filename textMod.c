#include "textMod.h"
#include "bst.h"

//check errors of file descriptor and writes them to stderr
void errorCheck(int fd){
  if (fd == -1){
    //write errno message to stderr
    write(STDERR_FILENO,("%s \n",strerror(errno)),strlen(strerror(errno)));
    write(STDERR_FILENO,"\n",1);
  }
}

void checkRead(int readFile, int openFile, char buf[], int bufSize){
  //add null terminator to the last char in buffer
  if (readFile<bufSize)
    buf[readFile] = '\0';
  // subtract one from offset till the non alphabet is found 
  // change buff index to blank to prevent it from counting twice
  for(int j = bufSize-1; j >= 0; j--){
    if(isalpha(buf[j])==0)
      break;
    lseek(openFile,-1,SEEK_CUR);
    buf[j] = ' ';
  }
}
void processLine(char buf[],struct BST* BSTArr[26], char delims[], int maxArr[2]){
  char* curToken;
  bool delimCheck = false;
  char* tokenCheck;
  
  // tokenize buffer
  curToken = strtok(buf,delims);
  while (curToken !=NULL){
    // allocates memory for a copy of curToken
    char* newToken = strdup(curToken);
  
    // make token lowercase and checks to see if there is a new delim
    // add to delim array and skip iteration so a delim isnt lowercased   
    for(int i = 0; i < strlen(newToken); i++){ 
       // checks if there is a delim and if it doesnt exist in delim array
      if(isalpha(newToken[i]) == 0 &&strchr(delims,newToken[i]) == NULL){
        char invalidToken[2];
        invalidToken[0] = curToken[i];
        strcat(delims,invalidToken);
        delimCheck = true;
        continue;
      }
      newToken[i] = tolower(newToken[i]); 
    }
     
    // rerun token on word with new delim array
    if (delimCheck== true){
     char* reCheckWord = newToken;
      //tokenize word with strsep
      while ((tokenCheck = strsep(&reCheckWord,delims))!=NULL){
        //strsep returns "" when muitlple delimiters are in a row
        if(strcmp(tokenCheck, "") == 0)
          continue;
  
        // allocate memory for word and insert to tree
        char* tokenDupe = strdup(tokenCheck);
        struct BST* tempNode = makeBST(tokenDupe,1,NULL,NULL);
        // compare nodes word length with current max word length
        checkMax(maxArr, tempNode);
 
        // checks to see node should be root
        if((BSTArr[letterToIndex(tokenDupe[0])] == NULL))
          BSTArr[letterToIndex(tokenDupe[0])] = tempNode;     
        // insert normally  
        else
          insert(BSTArr[letterToIndex(tokenDupe[0])], tempNode, maxArr); 
      }
      free(newToken);
      delimCheck = false;
      curToken = strtok(NULL,delims);
      continue;
    }
    // make node and insert to tree
    struct BST* tempNode = makeBST(newToken,1,NULL,NULL);
    checkMax(maxArr, tempNode);
    // check to see if node should be the root
    if((BSTArr[letterToIndex(newToken[0])] == NULL))
      BSTArr[letterToIndex(newToken[0])] = tempNode;
    // insert normally
    else
      insert(BSTArr[letterToIndex(newToken[0])], tempNode, maxArr);
    curToken = strtok(NULL,delims);
  }
}

int letterToIndex(char firstLetter){
  // subtracts 97 from  a letters ascii value to get index 
  return (firstLetter-97);
}

void checkMax(int maxArr[2], struct BST* node){
  // updates max[1] and max[2] if node word or  count are greater
  maxArr[0] = (strlen(node->word) > maxArr[0]) ? strlen(node->word) : maxArr[0];
  maxArr[1] = (node->count > maxArr[1]) ? node->count : maxArr[1];
}


