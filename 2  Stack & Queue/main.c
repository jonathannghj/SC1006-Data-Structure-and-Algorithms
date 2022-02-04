#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX  1000

typedef struct _listnode{
    char letter;
    struct _listnode *next;
}ListNode;

typedef ListNode QueueNode;
typedef struct _queue{
    int size;
    ListNode  *head;
    ListNode  *tail;
} Queue;
int isEmptyQueue(Queue q);
char getFront(Queue q);
void enqueue(Queue *q, char c);
int dequeue(Queue *q);

int palindrome(Queue* wordPtr, Queue* wordPtr2);

int main()
{
    Queue qPtr;
    qPtr.size = 0;
    qPtr.head = NULL;
    qPtr.tail = NULL;

    Queue qPtr2;
    qPtr2.size = 0;
    qPtr2.head = NULL;
    qPtr2.tail = NULL;
    char string[MAX], *p;

    printf("Enter a string of characters, terminated by a new value\n");
    fgets(string, 80, stdin);
    if(p=strchr(string, '\n')) *p = '\0';
    printf("%s\n",string);
    int length = strlen(string);
    printf("%d", length);
    for(int i = 0; i< length; i++)
    {
        if(string[i] == 32)
        {
            continue;
        }
        else
        {
        enqueue(&qPtr, string[i]);
        }
    }
    for(int i = length - 1; i >=0 ; i--)
    {
        if(string[i] == 32)
        {
            continue;
        }
        else
        {
        enqueue(&qPtr2, string[i]);
        }
    }
//    printf("%c", getFront(qPtr));
//    dequeue(&qPtr);
//    printf("%c", getFront(qPtr2));
//    dequeue(&qPtr2);
//    printf("%c", getFront(qPtr));
//    dequeue(&qPtr);
//    printf("%c", getFront(qPtr2));
//    dequeue(&qPtr2);
//    printf("%c", getFront(qPtr));
//    dequeue(&qPtr);
//    printf("%c", getFront(qPtr2));
//    dequeue(&qPtr2);
    if (palindrome(&qPtr, &qPtr2)  == 1)
    {
        printf("The string is a palindrome.");
    }
    else
    {
        printf("The string is not a palindrome.");
    }
    return 0;
}

char getFront(Queue q)
{
    return q.head->letter;
}

int isEmptyQueue(Queue q)
{
    if(q.size==0) return 1;
    else return 0;
}

void enqueue(Queue *q, char c)
{
    QueueNode *NewNode;
    NewNode = (QueueNode *)(malloc(sizeof(QueueNode)));
    NewNode->letter = c;
    NewNode->next = NULL;

    if (isEmptyQueue(*q))
    {
        q->head = NewNode;
    }
    else
    {
        q->tail->next = NewNode;
    }
    q->tail = NewNode;
    q->size++;
}

int dequeue(Queue *q)
{
    if (q == NULL  || q->head == NULL)
    {
        return 0;
    }
    else
    {
        QueueNode *temp = q->head;
        q->head = q->head->next;
        free(temp);
        if(q->head == NULL)
        {
            q->tail = NULL;
        }
        q->size--;
        return 1;
    }
}

int palindrome(Queue* wordPtr, Queue* wordPtr2)
{
    int palindrome = 1;
    for (int i = 0; i < wordPtr->size; i++)
    {
        if(tolower(getFront(*wordPtr)) == tolower(getFront(*wordPtr2)))
        {
            continue;
        }
        else
        {
            palindrome = 0;
            return palindrome;
        }
    }
    return palindrome;
}
