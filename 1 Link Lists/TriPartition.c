#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);
ListNode* findNode(ListNode *cur, int i);
int insertNode(ListNode **ptrHead, int i, int value);
void triPartition(ListNode** head, int pivot);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int pivot = 0;

	scanf("%d",&pivot);

	while (scanf("%d", &i)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
	}
	temp->next = NULL;


	triPartition(&head, pivot);
	printList(head);
	deleteList(&head);

	return 0;
}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%d ",head->item);
        head = head->next;
    }
    printf("\n");
}

void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	*ptrHead=NULL;
}

void triPartition(ListNode** head, int pivot){


    ListNode *temp = NULL;
    ListNode *tempstart = NULL;
    ListNode *tempmiddle = NULL;
    ListNode *tempend = NULL;


    ListNode *start = NULL;
    ListNode *middle = NULL;
    ListNode *end = NULL;

    int startCount = 0;
    int middleCount = 0;
    int endCount = 0;

    temp = *head;

    while(temp != NULL)
    {
        {
            if (temp->item < pivot)
            {
                insertNode(&start, startCount, temp->item);
                startCount++;
            }
            else if (temp->item == pivot)
            {
                insertNode(&middle, middleCount, temp->item);
                middleCount++;
            }
            else
            {
                insertNode(&end, endCount, temp->item);
                endCount++;
            }
            temp = temp->next;
        }
    }



        if (middle == NULL && end == NULL)
        {
            *head = start;
        }
        else if (start == NULL && end == NULL)
        {
            *head = middle;
        }
        else if (start == NULL && middle == NULL)
        {
            *head = end;
        }
        else if (middle == NULL)
        {
            temp = start;
            for (int i = 1; i < startCount; i++)
            {
                temp = temp->next;
            }
            temp->next = end;
            *head = start;
        }
        else if (start == NULL)
        {
            temp = middle;
            for (int i = 1; i < middleCount; i++)
            {
                temp = temp->next;
            }
            temp->next = end;
            *head = middle;
        }
        else
        {
            temp = start;
            for (int i = 1; i < startCount; i++)
            {
                temp = temp->next;
            }
            temp->next = middle;
            temp = temp->next;


            for (int i = 1; i < middleCount; i++)
            {
                temp = temp->next;
            }
            temp->next = end;
            *head = start;
        }



    }





ListNode* findNode(ListNode *cur, int i)
{
	if (cur == NULL || i < 0)
	{
		return NULL;
	}
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

int insertNode(ListNode **ptrHead, int i, int value)
{
	ListNode *cur = NULL;
	ListNode *NewNode = NULL;

	if(i == 0)
	{
		NewNode = (ListNode *)(malloc(sizeof(ListNode)));
		NewNode->item = value;
		NewNode->next = *ptrHead;
		*ptrHead = NewNode;
		return 1;
	}

	else if ((cur = findNode(*ptrHead, i-1)) != NULL)
	{
		NewNode = (ListNode *)(malloc(sizeof(ListNode)));
		NewNode->item = value;
		NewNode->next = cur->next;
		cur->next = NewNode;
		return 1;
	}
	return 0;
}
