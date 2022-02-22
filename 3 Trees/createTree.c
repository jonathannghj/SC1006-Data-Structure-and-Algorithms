#include <stdio.h>
#include <stdlib.h>

#define MAX_N 120

typedef struct _btnode{
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode** node, char* preO, char* postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);

int main()
{
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s",preO);
    scanf("%s",postO);

    BTNode* root=NULL;
    buildTree(&root,preO,postO);
    if(root==NULL) printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}
void inOrder(BTNode *cur){
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c",cur->id);
    inOrder(cur->right);
}
void preOrder(BTNode *cur){
    if (cur == NULL)
        return;

    printf("%c",cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}
void postOrder(BTNode *cur){
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c",cur->id);
}



BTNode* constructTree(char* preO, char* postO);

BTNode* RecurseTree(char* preO, char* postO, int* pre, int left, int right)
{

    int length = 0;
    int j;
    
    for(int i = 0; preO[i] != '\0'; i++)
    {
        length++;
    }
    
    // NULL returned when there is no longer any characters to compare
    if (left > right)
    {
        return NULL;
    }

    // NULL returned when there is no longer any characters to compare
    if (*pre > length - 1)
    {
        return NULL;
    }
    
    // create every subsequent character from the first character will be the root node
    // nodes found to the left of the value of root node and found on the postorder from the right side including itself will be in the left subtree
    // nodes found to the right of the value of root node excluding found on the postorder from the right excluding itself will be the right subtree

    char rootValue = preO[*pre];
    BTNode *root = (BTNode*)(malloc(sizeof(BTNode)));
    root->id = rootValue;
    root->left = NULL;
    root->right = NULL;

    // always compare the subsequent character of the prefix string with the postfix string starting from end leftwards
    (*pre)++; 
    char targetValue = preO[(*pre)];

    if(left == right)
    {
        return root;
    }
    
    for(j = right + 1; j > 0; j--)
    {
        if(targetValue == postO[j])
        {
            break;
        }
    }
    
    // recursively call to form tree
    root->left = RecurseTree(preO, postO, pre, left, j);
    root->right = RecurseTree(preO, postO, pre, j+1, right-1);
    
    return root;
}

BTNode* constructTree(char* preO, char* postO)
{
    int pre = 0;
    int length = 0;
    for(int i = 0; preO[i] != '\0'; i++)
    {
        length++;
    }
    return RecurseTree(preO, postO, &pre, 0, length - 1);
}

void buildTree(BTNode** node, char* preO, char* postO)
{
    // Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
    // Write your code here
    *node = constructTree(preO, postO);
}
