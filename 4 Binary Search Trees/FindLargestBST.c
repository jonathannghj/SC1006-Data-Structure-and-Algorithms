#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queueNode{
	BTNode *data;
	struct _queueNode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

typedef struct _stackNode{
	BTNode *data;
	struct _stackNode *next;
}StackNode;

typedef struct _stack
{
    int size;
	StackNode *top;
}Stack;

//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * data);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

BTNode* createNode(int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

//Prototypes of Interface functions for Stack structure
void push(Stack *sPtr, BTNode *data);
int pop(Stack *sPtr);
BTNode* peek(Stack s);
int isEmptyStack(Stack s);

void BSTCorrection(BTNode* root);

int main()
{
    BTNode* root = NULL;
    BTNode* temp = NULL;
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    int item;
    int flag=1;
    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
    {
        if(root==NULL)
        {
            if(item!=-1){
                root =createNode(item);
                enqueue(&q,root);
            }
        }
        else{
            while(!isEmptyQueue(q)){
                temp = getFront(q);
                if(flag){
                    if(item != -1){
                        temp->left = createNode(item);
                        enqueue(&q,temp->left);
                    }
                    flag = 0;
                    break;
                }
                else if(temp->right==NULL){
                    if(item!=-1){
                        temp->right = createNode(item);
                        enqueue(&q,temp->right);
                    }
                    dequeue(&q);
                    flag=1;
                    break;
                }
                else  dequeue(&q);
            }
        }
    }
    scanf("%*s");

    printf("The input binary search tree:\n");
    printBTNode(root,0,0);
    printf("\n");
    printf("The corrected binary search tree:\n");
    BSTCorrection(root);

    printBTNode(root,0,0);

    deleteTree(&root);

    return 0;
}
BTNode* createNode(int item)
{
    BTNode* node = (BTNode*) malloc(sizeof(BTNode));
	node->item = item;
	node->left = node->right = NULL;
	return node;
}

void printBTNode(BTNode *root,int space,int left){
      if (root != NULL)
      {

          int i;
          for (i = 0; i < space-1; i++)
                 printf("|\t");


          if(i<space){
            if(left==1)
              printf("|---");
            else
              printf("|___");
          }

          printf("%d\n", root->item);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

void deleteTree(BTNode **root){
    if (*root != NULL)
	{
		deleteTree(&((*root)->left));
		deleteTree(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}
void enqueue(Queue *qPtr, BTNode *data){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr){
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

BTNode* getFront(Queue q){
    return q.head->data;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
}

void push(Stack *sPtr, BTNode *data){
    StackNode *newNode;
    newNode= (StackNode *)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = sPtr->top;
    sPtr->top = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr==NULL || sPtr->top==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->top;
       sPtr->top = sPtr->top->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode* peek(Stack s){
    return s.top->data;
}

int isEmptyStack(Stack s){
     if(s.size==0) return 1;
     else return 0;
}

void BSTCorrection(BTNode* root)
{
    Stack tempS;
    tempS.size = 0;
    tempS.top = NULL;

    Queue arrangedQ;
    arrangedQ.size = 0;
    arrangedQ.head = NULL;
    arrangedQ.tail = NULL;

    BTNode *cur;
    cur = root;
    
    while (isEmptyStack(tempS) != 1 || cur != NULL)
    {
        if (cur != NULL)
        {
            push(&tempS, cur);
            cur = cur->left;
        }
        else 
        {
            cur = tempS.top->data;
            enqueue(&arrangedQ, cur);
            pop(&tempS);
            cur = cur->right;        
        }
    }
    int size = arrangedQ.size;
    int swapped = 0;
   
    // printf("%d ", current->item);
    // printf("%d ", compare->item);
    while(isEmptyQueue(arrangedQ) == 0)
    {   
        BTNode *current = getFront(arrangedQ);
        dequeue(&arrangedQ);
        
        for (int i = 0; i < size - 1; i++)
        {
            BTNode *compare = getFront(arrangedQ);
            dequeue(&arrangedQ);
            
            if (current->item > compare->item)
            {
                int temp = current->item;
                current->item = compare->item;
                compare->item = temp;
                enqueue(&arrangedQ, compare);
            }
            else 
            {
                enqueue(&arrangedQ, compare);
            }
        }
        size--;
    // printf("%d ", current->item);
    // printf("%d ", compare->item);
    }

}
