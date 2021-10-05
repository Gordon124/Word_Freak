#include "bst.h"
#include "textMod.h"
#define BUFFSIZE 1024

int main(int argc, char* argv[]) {
  int openFile;
  char buf[BUFFSIZE];
  int readFile;
  int status;
  char delims[200] = " ~<>/-+?{}:;&@#$%^*|`()_!'*[]^1234567890.,\t\r\"\n";
  struct BST* wordTrees[26];
  int maxWordNum[2] = {0,0};
  int numDigits = 0;
  int fdClose;
  char* envFile;
  char splitWord[100]; // used to hold words that are split in terminal reading
  int splitCount= 0;   
  bool splitCheck = false;
  int bufCount = -1; 
 
  // fill all_letters array with leters from a to z
  // set all values of wordTree array to NULL
  for(int i = 0;i < 26; i++){
    wordTrees[i] = NULL;
  }

  //read from termimal
  while ((readFile = read(STDIN_FILENO,buf,BUFFSIZE))>0){
    // checks to see if this is the last read/ EOF
    if (readFile<BUFFSIZE){ 
      //change last byte in buff to null terminator
      buf[readFile] = '\0';
    }
     
    // checks to see if a word was cut off from last read/iteration
    if (splitCheck == true){
      // loops from the beginning of buffer
      for(int j = 0; j < BUFFSIZE; j++){
        //checks for a delimiter/non alphabet
        if(isalpha(buf[j])==0)
          break;
        //if char is a letter add it to splitword array which contains the first half of word
        //change char at buffer to blank and increment count
        splitWord[splitCount] = buf[j];
        buf[j] = ' ';
        splitCount+=1;
      } 
      splitCheck = false;
      // makes splitWord to lower case
      for(int i = 0; i < splitCount; i++){
        splitWord[i] = tolower(splitWord[i]);
      }
      
      // allocates memory for word
      // make node and insert to tree
      char* splitWordToken = strndup(splitWord,splitCount);
      struct BST* tempNode = makeBST(splitWordToken,1,NULL,NULL);
      //update max if word length and count is greater
      checkMax(maxWordNum, tempNode);
      if((wordTrees[letterToIndex(splitWordToken[0])] == NULL))
        wordTrees[letterToIndex(splitWordToken[0])] = tempNode;
      else
        insert(wordTrees[letterToIndex(splitWordToken[0])], tempNode, maxWordNum);     
      
      splitCount = 0;
    }
    //checks to see the last characters in buffer is cut off
    for(int j = BUFFSIZE-1; j >= 0; j--){
      if(isalpha(buf[j])==0){
        break;
      }
      // saves the value of first character of the word that is cutoff
      bufCount = j;     
    }
    //saves the word that is cutoff to splitWord array
    if (bufCount!=-1&& bufCount != BUFFSIZE-1){
      for (int i = bufCount; i < BUFFSIZE; i++){
        //add char to splitWord array and replace the char with blank in buffer
        splitWord[splitCount] = buf[i];
        buf[i] = ' ';
        // increment splitCount and set splitCheck to true
        // so rest of word in next read can be added
        splitCount+=1;
        splitCheck = true;
      }
      // reset bufCount
      bufCount = -1;
    }
    processLine(buf,wordTrees,delims,maxWordNum);
  }
  errorCheck(readFile);

  // checks to see if an enviroment variable WORD_FREAK exist
  if ((envFile = getenv("WORD_FREAK"))!=NULL){
    //open and read enviroment vaiable
    openFile = open(envFile, O_RDONLY);
    errorCheck(openFile);
    while ((readFile = read(openFile,buf,BUFFSIZE))>0){
      //check to make sure no words are cut off 
      //tokenize each word in buf and add to BST
      checkRead(readFile, openFile, buf, BUFFSIZE);
      processLine(buf,wordTrees,delims,maxWordNum);
    }
    // handle errors
    errorCheck(readFile);
    fdClose = close(openFile);
    errorCheck(fdClose);
  }

  //loops through and process each file given from the command line
  for (int i = 1; i < argc; i++){
    openFile = open(argv[i], O_RDONLY);
    errorCheck(openFile);
    while ((readFile = read(openFile,buf,BUFFSIZE))>0){ 
      //check to make sure no words are cut off 
      //tokenize each word in buf and add to BST
      checkRead(readFile, openFile, buf, BUFFSIZE);
      processLine(buf,wordTrees,delims,maxWordNum);   
    }
    // handle errors
    errorCheck(readFile);
    fdClose = close(openFile);
    errorCheck(fdClose);
  }
  // open output file
  int output = open("output.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
  errorCheck(output);
  
  //change the largest number found to its number of digits
  while(maxWordNum[1] != 0){
    maxWordNum[1] /= 10;
    numDigits+=1;
  }
  maxWordNum[1] = numDigits;

  // prints and free the tree
  for (int i = 0; i <26;i++){
    if(wordTrees[i] !=NULL){
      prtInorderBST(wordTrees[i],output,maxWordNum);
      freeBST(wordTrees[i]); 
    }  
  }

  // handle errors
  fdClose = close(output);
  errorCheck(fdClose);
}

