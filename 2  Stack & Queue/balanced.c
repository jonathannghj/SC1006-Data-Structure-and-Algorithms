#include <stdio.h>
#include <stdlib.h>


#define MAX 1000
typedef struct _listnode{
    char letter;
    struct _listnode *next;
}ListNode;
typedef ListNode StackNode;

typedef struct _linkedlist{
    int size;
    ListNode *head;
}LinkedList;
typedef LinkedList Stack;

int isEmptyStack(Stack S);
char peek(Stack S);
void push(Stack *S, char c);
int pop(Stack *S);

int balanced(char *expression);
int checkBalance(char opening, char closing);

int main()
{
    char string[MAX], *p;
    printf("Enter an expression, terminated by a newline:\n");
    fgets(string,  80, stdin);
    if(p = strchr(string, '\n'))  *p = '\0';

    if(balanced(string) == 0)
    {
        printf("The expression is not balanced.");
    }
    else
    {
        printf("The expression is balanced.");
    }
    return 0;
}

char peek(Stack S)
{
    return S.head->letter;
}

int isEmptyStack(Stack S)
{
    if(S.size==0) return 1;
    else return 0;
}

void push(Stack *S, char c)
{
    StackNode *NewNode;
    NewNode = (StackNode *)(malloc(sizeof(StackNode)));
    NewNode->letter = c;
    NewNode->next = S->head;

    S->head = NewNode;
    S->size++;
}

int pop(Stack *S)
{
    if (S == NULL  || S->head == NULL)
    {
        return 0;
    }
    else
    {
        StackNode *temp = S->head;
        S->head = S->head->next;
        free(temp);
        S->size--;
        return 1;
    }
}
int balanced(char *expression)
{
    Stack sPtr;
    sPtr.size = 0;
    sPtr.head = NULL;

    int balanced = 1;
    int length = strlen(expression);
    for (int i = 0; i < length; i++)
    {
        if(expression[i] == 40 || expression[i] == 91 || expression[i] == 123 )
        {
            push(&sPtr, expression[i]);
        }
        else if(expression[i] == 41 || expression[i] == 93 || expression[i] == 125)
        {

            if(isEmptyStack(sPtr) || checkBalance(peek(sPtr), expression[i]) ==  0)
            {
                balanced = 0;
                return balanced;
            }
            else
            {
                 pop(&sPtr);
            }
        }
    }
    if(isEmptyStack(sPtr))
    {
        return balanced;
    }
    else
    {
        balanced = 0;
        return balanced;
    }

}
int checkBalance(char opening, char closing)
{
    if(opening == 40  && closing == 41 || opening == 91 && closing == 93 || opening == 123 && closing == 125)
    {
        return 1;
    }
    return 0;
}
