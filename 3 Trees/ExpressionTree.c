#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    //printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    // printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    //printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    //printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void push(Stack *sPtr, BTNode *item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}
void createExpTree(BTNode** root,char* prefix)
{
 //Write your code here
    Stack tempStack;
    tempStack.head = NULL;
    tempStack.size = 0;

    int counter = 0;
    int node_count = 0;
    for(int i = 0; prefix[i] != '\0'; i++)
    {
        counter++;
    }
    
    for (int i = 0; i < counter; i++)
    {
        if(prefix[i] <= 57 && prefix[i] >= 48)
        {
            int number = 0;
            while (prefix[i] >= 48 && prefix[i] <= 57)
            {
                number = number * 10 + (int)(prefix[i] - 48);
                i++;
            }
            
            BTNode *node = (BTNode*)(malloc(sizeof(BTNode)));
            node->item = number;
            node->left = node->right = NULL;
            
            push(&tempStack, node);
            node_count++;
            
        }
        else if(prefix[i] == '+' || prefix[i] == '-' || prefix[i] == '*' || prefix[i] == '/' || prefix[i] == '%' || prefix[i] == '(' || prefix[i] == ')')
        {
            int num = 0;
            num = (int)(prefix[i]);
            
            BTNode *node = (BTNode*)(malloc(sizeof(BTNode)));
            BTNode *node2 = (BTNode*)(malloc(sizeof(BTNode)));
            
            node->item = num;
            node->left = node->right = node2;
            
            push(&tempStack, node);
            node_count++;
        }
    }
    // if(peek(tempStack)->left != NULL)
    // {
    // printf("%d\n", peek(tempStack)->item);
    // }
    // pop(&tempStack);
    // if(peek(tempStack)->left != NULL)
    // {
    // printf("%d\n", peek(tempStack)->item);
    // }
    // pop(&tempStack);
    // if(peek(tempStack)->left != NULL)
    // {
    // printf("%d\n", peek(tempStack)->item);
    // }
    // pop(&tempStack);
    // if(peek(tempStack)->left != NULL)
    // {
    // printf("%d\n", peek(tempStack)->item);
    // }
    // pop(&tempStack);
    // if(peek(tempStack)->left != NULL)
    // {
    // printf("%d\n", peek(tempStack)->item);
    // }
    // pop(&tempStack);
    // if(peek(tempStack)->left != NULL)
    // {
    // printf("%d\n", peek(tempStack)->item);
    // }
    // pop(&tempStack);
    // if(peek(tempStack)->left != NULL)
    // {
    // printf("%d\n", peek(tempStack)->item);
    // }
    // pop(&tempStack);
    // if(peek(tempStack)->left != NULL)
    // {
    // printf("%d\n", peek(tempStack)->item);
    // }
    // pop(&tempStack);
    // if(peek(tempStack)->left != NULL)
    // {
    // printf("%d\n", peek(tempStack)->item);
    // }
    // pop(&tempStack);
    // pop(&tempStack);
    // printf("%d\n", peek(tempStack)->item);
    // pop(&tempStack);
    // printf("%d\n", peek(tempStack)->item);
    // pop(&tempStack);
    // printf("%d\n", peek(tempStack)->item);
    // pop(&tempStack);
    // printf("%d\n", peek(tempStack)->item);
    // pop(&tempStack);
    // printf("%d\n", peek(tempStack)->item);
    // pop(&tempStack);
    // printf("%d\n", peek(tempStack)->item);
    // pop(&tempStack);
    // printf("%d\n", peek(tempStack)->item);
    // pop(&tempStack);
    // printf("%d\n", peek(tempStack)->item);
    // pop(&tempStack);
    // printf("%d\n", peek(tempStack)->item);
    // pop(&tempStack);
    // printf("%d\n", peek(tempStack)->item);
    // pop(&tempStack);
    // printf("%d\n", peek(tempStack)->item);
    // pop(&tempStack);
    // printf("%d\n", peek(tempStack)->item);
    // pop(&tempStack);
    
    // printf("%d\n", node_count);
    
    Stack TreeStack;
    TreeStack.size = 0;
    TreeStack.head = NULL;
    
    for(int i = 0; i < node_count; i++)
    {
        // if(peek(tempStack)->item == 40 && peek(tempStack)->left != NULL)
        // {
        //     // push(&TreeStack, peek(tempStack));
        //     pop(&tempStack);
        // }
        // else if(peek(tempStack)->item == 41 && peek(tempStack)->left != NULL)
        // {
        //     // push(&TreeStack, peek(tempStack));
        //     pop(&tempStack);
        // }
        if(peek(tempStack)->left == NULL)
        {
            push(&TreeStack, peek(tempStack));
            pop(&tempStack);
        }
        else if (peek(tempStack)->left != NULL)
        {
            peek(tempStack)->left = peek(TreeStack);
            pop(&TreeStack);
            peek(tempStack)->right = peek(TreeStack);
            pop(&TreeStack);
            push(&TreeStack, peek(tempStack));
            pop(&tempStack);
        }
    }
    *root = peek(TreeStack);

}

void printTree(BTNode *node){
    //Write your code here
    if(node == NULL)
        return;
    
    printTree(node->left);
    if(node->left == NULL && node->right == NULL)
    {
        printf("%d ", node->item);
    }
    else
    {
        char c;
        c = (char)(node->item);
        printf("%c ", c);
    }
    printTree(node->right);    
}


void printTreePostfix(BTNode *node){
    //Write your code here
    if(node == NULL)
        return;
    
    printTreePostfix(node->left);
    printTreePostfix(node->right); 
    if(node->left == NULL && node->right == NULL)
    {
        printf("%d ", node->item);
    }
    else
    {
        char c;
        c = (char)(node->item);
        printf("%c ", c);
    } 
}
double computeTree(BTNode *node){
//Write your code here
    double answer = 0;
    if(node->left == NULL && node->right == NULL)
    {
        return node->item;
    }
    
    double operand1 = computeTree(node->left);
    double operand2 = computeTree(node->right);

    char c;
    c = (char)(node->item);

    if(c == '+')
    {
        return(operand1 + operand2);
    }
    else if(c == '-')
    {
        return(operand1 - operand2);
    }
    else if(c == '*')
    {
        return(operand1 * operand2);
    }
    else
    {
        return(operand1 / operand2);
    }

}

