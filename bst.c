#include "bst.h"
#include "textMod.h"

struct BST* makeBST(char* data, int count, struct BST* left, struct BST* right){
  struct BST* newBST = (struct BST*) malloc(sizeof(struct BST));
  newBST -> word = data;
  newBST -> count = count;
  newBST -> left = left;
  newBST -> right = right;
  return newBST;
}

// write the values of BST word and count to output.txt
void prtInorderBST(struct BST* root, int output, int maxArr[2]){
  if(root == NULL)
    return;
  // go left
  prtInorderBST(root->left,output,maxArr);

  //make output buf array with size of 3 + size of word and count
  char output_buf[maxArr[0]+3+maxArr[1]];
  //fromat with sprintf and write to output.txt
  sprintf(output_buf,"%-*s : %*i\n",maxArr[0],root->word,maxArr[1],root->count);
  int fdWrite = write(output,output_buf,strlen(output_buf));
  errorCheck(fdWrite);

  // go right
  prtInorderBST(root->right,output,maxArr);
}

//insert addNode to BST
struct BST* insert(struct BST* root, struct BST* addNode, int maxArr[2]){
  // base case
  if(root == NULL){
    return addNode;
  } 
  //if equal
  if (BSTwordCompare(root,addNode->word) == 0){
    // increment count and compare with max[1]
    root->count +=1;
    checkMax(maxArr,root);  
    // free the word
    free(addNode->word);
    free(addNode);
  }
  // if less go left
  else if(BSTwordCompare(root,addNode->word) == -1){
    root -> left = insert(root->left,addNode, maxArr);
  }
  // if greater go right
  else if(BSTwordCompare(root,addNode->word) ==1){
    root -> right = insert(root->right,addNode, maxArr);
  }
  return root;
  
}

// compares the node->word and word
int BSTwordCompare(struct BST* curNode, char* word){
  int lenWord1 = strlen(curNode->word); 
  int lenWord2 = strlen(word);
  int check;
  // checks to see if curNode->word and word is equal 
  if (strcmp(curNode->word,word)==0)
   return 0;
  // loops through and compare each words letter
  for (int i = 0; i<lenWord1 || i <lenWord2; i++){
    //subtract the ascii value of the letters
    check = word[i]-(curNode->word)[i];
    
    // check is a negative number this means that the word is less than curNode->word
    if (check<0)
      return -1;
    // check is a postive number this means that the word is greaters than curNode->word
    if (check >0)
      return 1;
    // checks to see which word is shorter
    // example aa is less than aaa
    if (i + 1 >= lenWord1)
      return 1;
    if (i + 1 >= lenWord2)
      return -1;
  }
}

// free the bst
void freeBST(struct BST* root){
  if (root == NULL)
    return;
  // free tree inorder traversal
  freeBST(root->left);
  free(root->word);
  freeBST(root->right);
  free(root);
}
