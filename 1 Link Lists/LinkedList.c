#include <stdio.h>
// stdlib.h is used to access malloc() function
#include <stdlib.h>

// typedef the struct for easy usage of struct
typedef struct node{
    // value of node
    int item;
    // add another node pointer into the struct to link to other nodes
    struct node *next;
} ListNode;

void printList(ListNode *cur);
int insertNode(ListNode **ptrHead, int i, int item);

int main()
{
    // initialize the head struct pointer to first node and temp struct pointer to access every next node
    ListNode *head = NULL, *temp;
    int i;
    // scan whatever desired input
    while (scanf("%d", &i))
    {
        // head will be NULL before being assigned to a node, thus this will be executed once
        // after assigned to the first node, head is no longer NULL
        if (head == NULL)
        {
            // creating a node using (struct_pointer *)(malloc(sizeof(struct_pointer))) and pointing the head to it
            head = (ListNode *)(malloc(sizeof(ListNode)));
            // points the temp to the same location as the head was pointed
            temp = head;
        }
        // after 1st iteration, head will no longer be NULL, this else loop will be executed
        else
        {
            // likewise, creating a node using (struct_pointer *)(malloc(sizeof(struct_pointer))) and pointing it using temp->next
            temp->next = (ListNode *)(malloc(sizeof(ListNode)));
            // temp is then assigned to the new node, the head stays at the first node
            temp = temp->next;
        }

        // assigns the scanned value into the ->item
        temp->item = i;
    }
    // when garbage value is scanned, the while loop terminates and its the end of the linked list
    temp->next = NULL;
    printList(head);
    // always remember to free up the
    free(head);
    free(temp);
    return;
}

// prints out the values in all the nodes of the linked list
void printList(ListNode *cur)
{
    // while the (not the link, but the address of the node)address of the current node is not NULL, it will print the value stored in that node and moves onto the next node
    while (cur != NULL)
    {
        printf("%d\n", cur->item);
        // traverses into the next node
        cur = cur->next;
    }
}

int insertNode(ListNode **ptrHead, int i, int item);

