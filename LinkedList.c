#include <stdio.h>
// to access malloc function
#include <stdlib.h>


//create linked list struct with values and pointer links
typedef  struct node{
    int value;
    struct node *next;
}LinkList;

// functions
// prints the elements in the linked list, returns void coz print
void printList(LinkList *cur);
// finds the node of a particular index and returns it
LinkList* findList(LinkList *cur, int i);
// inserts a node of specified value into particular index, returns 1 if success, returns 0 if otherwise.
int insertNode (LinkList **ptrHead, int i, int value);
// deletes a node at particular index, returns 1 if success, returns 0 if otherwise.
int deleteNode (LinkList **ptrHead, int i);


int main()
{
    // create struct pointer variables head and temp
    // head is used to contain the address of the first node
    // temp is used to update the values of subsequent nodes
    LinkList *head = NULL, *temp;
    int i;

    // iterates while user inputs an integer and stores it in nodes, exits the loop when non integer is being input
    while(scanf("%d", &i))
    {
        // if head pointer is NULL, means the ll is not initialized
        // this if statement will be executed once when creating a ll
        if (head == NULL)
        {
            // creating a node using (struct_pointer *)(malloc(sizeof(struct_pointer))) and pointing the head to it
            head = (LinkList *)(malloc(sizeof(LinkList)));
            // points the temp to the same location as the head was pointed
            temp = head;
        }
        // after 1st iteration, head will no longer be NULL, this else loop will be executed
        else
        {
            // likewise, creating a node using (struct_pointer *)(malloc(sizeof(struct_pointer))) and pointing it using temp->next
            temp->next = (LinkList *)(malloc(sizeof(LinkList))) ;
            // temp is then assigned to the new node, the head stays at the first node
            temp = temp->next;
        }
        // assigns the scanned value into the ->item
        temp->value = i;
    }
    // when garbage value is scanned, the while loop terminates and its the end of the linked list
    temp->next = NULL;
    // printList(head);
    insertNode(&head, 0, 99);
    printList(head);
    printf("\n");
    // note: if using **ptrHead, need to pass the address of head (&head) instead of head
    deleteNode(&head, 0);
    printList(head);
    // always remember to free up the ll!
    free(head);
    free(temp);
    return 0;
}

// prints out the values in all the nodes of the linked list
void printList(LinkList *cur)
{
    // while the (not the link, but the address of the node)address of the current node is not NULL,
    //it will print the value stored in that node and moves onto the next node
    while(cur != NULL)
    {
        printf("%d\n", cur->value);
        // traverses into the next node
        cur =  cur->next;
    }
}

LinkList* findList(LinkList *cur, int  i)
{
    // if the current node is NULL or the index is not valid, returns a NULL  pointer
    if (cur == NULL || i < 0)
    {
        return NULL;
    }
    // while loop  iterates i times, and traverses to the ith index
    // if NULL, means the end of the ll, and the node is not found; return NULL if so.
    while (i > 0)
    {
        cur = cur->next;
        if (cur == NULL)
        {
            return NULL;
        }
        i--;
    }
    return cur;
}


// inserts a new node into particular index
int insertNode (LinkList **ptrHead, int i, int value)
{
    // cur is the i-1 th node, NewNode is the node to be inserted
    LinkList *cur, *NewNode;
    // adds to the front
    if (i == 0)
    {
        NewNode = (LinkList *)(malloc(sizeof(LinkList)));
        // always assign the new value to the new node
        NewNode->value = value;
        // change the pointing
        // 1. point the new node to the ith node (in this case its the (*ptrHead)
        // 2. point the  i-1th->next to the new node
        NewNode->next = *ptrHead;
        *ptrHead = NewNode;
        return 1;
    }
    // adds to the middle/back
    else if ((cur = findList(*ptrHead, i - 1)) != NULL)
    {
        NewNode = (LinkList *)(malloc(sizeof(LinkList)));
        NewNode->value = value;
        // always  assign the new value to the new  node
        // 1. point the new node to the ith node (in this case its cur->next(since cur is the i-1th node)
        // 2. point the i-1th -> next to the new node
        NewNode->next = cur->next;
        cur->next = NewNode;
        return 1;
    }
    return 0;
}

// deletes node at particular index
int deleteNode (LinkList **ptrHead, int i)
{
    // idea  is to point  the i-1th node (prv) to the node after the ith node (cur->next)
    LinkList *prv, *cur;
    if (*ptrHead == NULL)
    {
        return  0;
    }
    // cur is the ith node
    cur = findList(*ptrHead, i);
    // if 1st node is to be deleted, use *ptrHead as the prv node
    if (i == 0)
    {

        *ptrHead = cur->next;
    }
    // if middle/last node is to be deleted, use prv node (i-1th node)
    else
    {
        prv =  findList(*ptrHead, i-1);
        prv->next = cur->next;
    }
    // ith->next to be freed and set as NULL
    cur->next = NULL;
    return 1;
}
