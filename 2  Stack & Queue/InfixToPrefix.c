#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
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

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void reverseString(char *string)
{   
    int length = 0;
    for(int i = 0; string[i]!= '\0';i++)
    {
        if (string[i] == '(')
        {
            string[i] = ')';
        }
        else if (string[i] == ')')
        {
            string[i] = '(';
        }
        length++;
    }
    char temp;

    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        temp = string[start];
        string[start] = string[end];
        string[end] = temp;
        start++;
        end--;
    }
    
}
int precedence(char c)
{
    if (c == '+' || c == '-')
    {
        return 1;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    else 
    {
        return 0;
    }
}

void in2PreLL(char* infix, LinkedList *inExpLL)
{
    Stack S;
    S.size = 0;
    S.head = NULL;

    LinkedList tempList;
    tempList.size = 0;
    tempList.head = NULL;

    
    int length = 0;
    for(int i = 0; infix[i] != '\0'; i++)
    {
        length++;
    }

    for(int i = 0; i < length; i++)
    {
        if (infix[i] >= 48 && infix[i] <= 57)
        {
            int number = 0;
            while (infix[i] >= 48 && infix[i] <= 57)
            { 
                number = number * 10 + ((int)(infix[i] - 48));
                i++;
            }
            i--;
            insertNode(&tempList, number, OPERAND);
        }

        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '%')
        {
            insertNode(&tempList, infix[i], OPT);
        }
        else if (infix[i] == '(')
        {
            insertNode(&tempList, ')', OPT);
        } 
        else if (infix[i] == ')')
        {
            insertNode(&tempList, '(', OPT);
        }
    }

    ListNode *temp = NULL;
    temp = tempList.head;

    for (int i = 0; i < tempList.size; i++)
    {
        if (temp->type == OPERAND)
        {
            insertNode(inExpLL, temp->item, OPERAND);
        }
        else if (temp->item == '(')
        {
            push(&S, temp->item);
        }
        else if (temp->item == ')')
        {
            while(peek(S) != '(')
            {
                insertNode(inExpLL, peek(S), OPT);
                pop(&S);
                
            }
            pop(&S);
        }
        else
        {   
            while(isEmptyStack(S) == 0 && peek(S) != '(' && (precedence(peek(S)) > precedence(temp->item)))
            {
                insertNode(inExpLL, peek(S), OPT);
                pop(&S);
            }
            push(&S, temp->item);
        }
        temp = temp->next;
    }
    while(isEmptyStack(S) == 0)
    {
        insertNode(inExpLL, peek(S), OPT);
        pop(&S);
    }

}







