#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 1000 //The limit of expression length

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

void in2Post(char*, char*);

int main()
{
    char infix[SIZE];
    char postfix[SIZE];

    printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    in2Post(infix,postfix);
    printf("The postfix expression is \n");
    printf("%s\n",postfix);
    return 0;
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = (StackNode *) malloc(sizeof(StackNode));
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
}

void in2Post(char* infix, char* postfix)
{
    Stack S;
    S.head = NULL;
    S.size = 0;
 //Write your code here
    int length = strlen(infix);
    int index = 0;
    for (int i = 0; i < length; i++)
    {
        if (isalpha(infix[i])|| isdigit(infix[i]))
        {
            postfix[index] = infix[i];
            index++;
        }
        else if (infix[i] == '(')
        {
            push(&S, infix[i]);

        }
        else if (infix[i] == ')')
        {
            while(peek(S) != '(')
            {
                postfix[index] = peek(S);
                index++;
                pop(&S);
            }
            pop(&S);

        }
        else
        {
            while(isEmptyStack(S) == 0 && peek(S) != '(' && (precedence(peek(S)) >= precedence(infix[i])))
            {
                postfix[index] = peek(S);
                index++;
                pop(&S);
            }
            push(&S, infix[i]);
        }
    }

    while(isEmptyStack(S) == 0)
    {
        postfix[index] = peek(S);
        index++;
        pop(&S);
    }
    postfix[index] = '\0';




}
