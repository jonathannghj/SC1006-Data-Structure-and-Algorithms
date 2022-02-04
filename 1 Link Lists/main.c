#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void reverseKNodes(ListNode** head, int K);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int K = 0;

	scanf("%d",&K);

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


	reverseKNodes(&head, K);
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

void reverseKNodes(ListNode** head, int K){
	ListNode *cur = NULL;
	ListNode *prev = NULL;
	ListNode *next = NULL;
	ListNode *temp = NULL;

    prev = (ListNode *)(malloc(sizeof(ListNode)));

	int counter = 0;

    cur =  *head;
    prev->next = cur;
	temp = *head;

	while (temp != NULL)
	{
		counter++;
		temp = temp->next;
	}

	if (counter < 1 || K> counter)
	{
		return;
	}

	temp = *head;

	// store the head of the reversed list
	for (int i = 0; i <  K  - 1; i++)
	{
		temp = temp->next;
	}




	while(counter >= K)
    {
        cur = prev->next;
        next = cur->next;
        for(int i = 0; i < K-1;  i++)
        {
            cur->next = next->next;
            next->next = prev->next;
            prev->next = next;
            next  =  cur->next;
        }
        prev = cur;
        counter -= K;

    }
    *head = temp;

}
