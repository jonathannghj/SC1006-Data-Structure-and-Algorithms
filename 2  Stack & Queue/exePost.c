#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 //The limit of expression length

typedef struct _stackNode{
    double item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, double item);
int pop(Stack *sPtr);
double peek(Stack s);
int isEmptyStack(Stack s);

double exePostfix(char*);
double evaluate(double operand1, char operation, double operand2);

int main()
{
    char postfix[SIZE];

    printf("Enter a postfix expression:\n");
    scanf("%[^\n]%*c",postfix);

    printf("The answer is %.2lf.\n",exePostfix(postfix));

    return 0;
}

void push(Stack *sPtr, double item){
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

double peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

double exePostfix(char* postfix)
{
 //Write your code here
    Stack sPtr;
    sPtr.size = 0;
    sPtr.head = NULL;

    double operand1 = 0;
    double operand2 = 0;
    double result = 0;

    int length = 0;
    length = strlen(postfix);

    double d = 0;
    for(int i = 0; i < length; i++)
    {
        if (48 <= postfix[i] && postfix[i]<=57)
        {
            d = (double)(postfix[i] - '0');
            push(&sPtr, d);
        }
        else
        {
            operand1 = peek(sPtr);
            pop(&sPtr);
            operand2 = peek(sPtr);
            pop(&sPtr);
            result = evaluate(operand2, postfix[i], operand1);
            push(&sPtr,result);
        }
    }
    return result;
}






double evaluate(double operand1, char operation, double operand2)
{
    double result = 0;
    if(operation == '+')
    {
        result = operand1 + operand2;
    }
    else if(operation == '-')
    {
        result = operand1 - operand2;
    }
    else if(operation == '*')
    {
        result = operand1 * operand2;
    }
    else if(operation == '/')
    {
        result = operand1 / operand2;
    }
    return (result);
}
