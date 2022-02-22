#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int nodeV;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queuenode{
    BTNode* node;
    struct _queuenode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

void printBTNode(BTNode *root, int space,int left);
//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * node);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2);

int main()
{
    BTNode* root = (BTNode*) malloc(sizeof(BTNode));

    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    BTNode* node;
    enqueue(&q,root);

    int nodeV;
    char opL, opR;

    while(!isEmptyQueue(q)){
            scanf("%d %c %c",&nodeV,&opL,&opR);
            node = getFront(q);dequeue(&q);
            node->nodeV = nodeV;

            if(opL != '@'){
                node->left = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->left);
            }
            else node->left =NULL;
            if(opR != '@'){
                node->right = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->right);
            }
            else
                node->right = NULL;
    }

    int v1,v2;
    scanf("%d %d",&v1,&v2);
    int cost = twoNodesCost(root,v1,v2);

    printBTNode(root,0,0);

    printf("Distance is %d\n",cost);
    return 0;
}

void enqueue(Queue *qPtr, BTNode *node){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->node = node;
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
    return q.head->node;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
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

          printf("%d\n", root->nodeV);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}



BTNode* LowestCommonAncestor(BTNode* root, int targetNode1, int targetNode2)
{
    if (root == NULL)
    {
        return NULL;
    }
    if(root->nodeV == targetNode1 || root->nodeV == targetNode2)
    {
        // printf("a%d", root->nodeV);
        // (*cost) += root->nodeV;
        return root;
    }
    BTNode *left = LowestCommonAncestor(root->left, targetNode1, targetNode2);
    BTNode *right = LowestCommonAncestor(root->right, targetNode1, targetNode2);

    if(left != NULL && right != NULL)
    {
        return root;
    }
    if(left == NULL && right == NULL)
    {
        return NULL;
    }
    if(left != NULL && right == NULL)
    {
        return left;
    }
    else if (right != NULL && left == NULL)
    {
        return right;
    }
    


}


// BTNode* computeCost(BTNode* node, int nodeV1, int nodeV2, int *cost)
// {
//     if(node == NULL)
//      {
//          return NULL;
//      }
//      if(node->nodeV == nodeV1 || node->nodeV == nodeV2)
//      {
//          return node;
//      }
//      BTNode *left = computeCost(node->left, nodeV1, nodeV2, cost);
//      BTNode *right = computeCost(node->right, nodeV1, nodeV2, cost);
    
//      if(left != NULL && right != NULL)
//      {

//          return node;
//      }
//     if(left == NULL && right == NULL)
//      {
//          return NULL;
//      }
//      if(left != NULL && right == NULL)
//      {
//         //  printf("a%d", left->nodeV);
//         //  (*cost) += left->nodeV;
//          return left;
//      }
//      else if (right != NULL && left == NULL)
//      {
//         //  printf("b%d", right->nodeV);
//         //  (*cost) += right->nodeV;
//          return right;
//     }
// }

int computeCost(BTNode *node, int nodeValue, int *cost)
{
    int leftCost = 0;
    int rightCost = 0;

    if (node == NULL)
    {
        return 0;
    }
    if (node->nodeV == nodeValue)
    {
        return node->nodeV;
    }
    if (node->left == NULL && node->right == NULL)
    {
        return 0;
    }

    leftCost = computeCost(node->left, nodeValue, cost);
    rightCost = computeCost(node->right, nodeValue, cost);

    if(leftCost == 0 && rightCost == 0)
    {
        return 0;
    }
    if(leftCost != 0) 
    {
        // printf("a%d", leftCost);
        *cost += leftCost;
        return node->nodeV;
    }
    
    if (rightCost != 0)
    {
        // printf("f%d", rightCost);
        *cost += rightCost;
        return node->nodeV;
    }


}

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2)
{
    

// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
    int cost = 0;
    BTNode *temp = (BTNode *)((malloc)(sizeof(BTNode)));
    temp->nodeV = -1;
    temp->left = NULL;
    temp->right = NULL;

    // BTNode *costNode = (BTNode *)((malloc)(sizeof(BTNode)));
    // costNode->nodeV = -1;
    // costNode->left = NULL;
    // costNode->right = NULL;

    temp = LowestCommonAncestor(node, nodeV1, nodeV2);
    // cost += temp->nodeV;
    // cost += temp->left->nodeV;
    // cost += temp->right->nodeV;
    
    computeCost(temp, nodeV1, &cost); 
    computeCost(temp, nodeV2, &cost); 
    cost += temp->nodeV;

    return cost;
}
