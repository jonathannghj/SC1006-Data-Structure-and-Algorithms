#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    float item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

ListNode* findNode(ListNode *cur, int i);
int insertNode(ListNode **ptrHead, int i, float value);

ListNode *reverseSegment(ListNode* head, int start, int end);

int main()
{
    ListNode *head = NULL, *temp;
	float f = 0.0;
	int S, E;

	scanf("%d %d",&S, &E);

	while (scanf("%f", &f)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = f;
	}
	temp->next = NULL;

	head = reverseSegment(head,S,E);
	printList(head);
	deleteList(&head);
	return 0;

}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%.2f ",head->item);
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

ListNode *reverseSegment(ListNode* head, int start, int end)
{
// Write your code here

	int count = 0;
	int index = 0;
	ListNode *counter = NULL;
	ListNode *next = NULL;
	ListNode *reverse = NULL;
	counter = head;
	next = head;


	while(counter != NULL)
	{
		count++;
		counter = counter->next;
	}
	if (start < 0 || end > (count-1))
	{
		return head;
	}

	for (int i = 0; i < start; i++)
	{
		insertNode(&reverse, index, (findNode(head, i))->item);
		printList(reverse);
		index++;
	}

	for (int j = end; j >= start; j--)
	{
		insertNode(&reverse, index, (findNode(head, j))->item);
		printList(reverse);
		index++;
	}

	for (int k = end + 1; k < count; k++)
	{
		insertNode(&reverse, index, (findNode(head, k))->item);
        printList(reverse);
		index++;
	}
	return reverse;
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

int insertNode(ListNode **ptrHead, int i, float value)
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
