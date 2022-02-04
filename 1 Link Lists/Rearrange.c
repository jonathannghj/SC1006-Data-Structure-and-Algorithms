#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

typedef struct _linkedList{
    ListNode *head;
    int size;
}LinkedList;

void printList(LinkedList ll);
void deleteList(LinkedList* llptr);

LinkedList rearrange (LinkedList ll);

int main()
{
    LinkedList ll;
    ll.head = NULL;
    ll.size = 0;

    ListNode* temp;

	int i = 0;

	while (scanf("%d", &i)){
		if (ll.head == NULL){
			ll.head = (ListNode*) malloc(sizeof(ListNode));
			temp = ll.head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
		ll.size++;
	}
	temp->next = NULL;

	ll = rearrange(ll);
	printList(ll);
    deleteList(&ll);
	return 0;
}

void printList(LinkedList ll){
    ListNode* temp = ll.head;

    while(temp !=NULL){
        printf("%d ",temp->item);
        temp = temp->next;
    }
    printf("\n");
}
void deleteList(LinkedList* llptr){
    ListNode *cur = llptr->head;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	llptr->head=NULL;
	llptr->size =0;
}

LinkedList rearrange (LinkedList ll)
{
	if (ll.head == NULL)
	{
		return ll;
	}
	if (ll.size == 1)
	{
		return ll;
	}
	// first rearrangement
	int right;
	right = 1;

	// create first rearranged LinkedList
	LinkedList Newll;
	Newll.head = NULL;
	Newll.size = ll.size;

	// declaring two pointers to split the ll into Left and Right lists
	ListNode *RightList = NULL;
	ListNode *LeftList = NULL;
	// temp is used to traverse the New ll
	ListNode *temp = NULL;

	// split into Left and Right Lists
	// Left list is ll.head
	// Right list is RightList
	RightList = ll.head;
	LeftList = ll.head;


    RightList = RightList->next;
	for (int i = 0; (i < ll.size/2 - 1); i++)
	{
		RightList = RightList->next;
		LeftList = LeftList->next;
	}
	LeftList->next = NULL;

	// creating ll.size number of new nodes
    for(int i = 0; i < ll.size; i++)
    {

        if (right == 1)
        {
			// for the first node
            if(Newll.head == NULL)
            {
				// point head to first node
                Newll.head = (ListNode *)(malloc(sizeof(ListNode)));
				// point temp to head
                temp = Newll.head;
				// place item from right list into the temp
                temp->item = RightList->item;
				// points to next node of right list
                RightList = RightList->next;
				// turns right into 0 to extract item from left list
                right = 0;
            }
			// for subsequent nodes taken from the right
            else
            {
				// creating a new node and placing into temp->next
                temp->next = (ListNode *)(malloc(sizeof(ListNode)));
				// shifting temp into the new node
                temp = temp->next;
				// place item from left node into temp
                temp->item = RightList->item;
				// points to next node of right list
                RightList = RightList->next;
				// turns right into 0 to extract item from left list
                right = 0;
            }
        }
		// for extracting items from left list
        else
        {
			// creating a new node and placing into temp->next
            temp->next = (ListNode *)(malloc(sizeof(ListNode)));
			// shifting temp into the new node
            temp = temp->next;
			// place item from left node into temp
            temp->item = ll.head->item;
			// points to next node of left list
            ll.head = ll.head->next;
			// turns right into 1 to extract item from right list
            right = 1;
        }
    }

    temp->next = NULL;




	// rearrange opposite way
	int left = 1;
	ListNode *temp2 = NULL;

	// create New LinkedList
	LinkedList Newll2;
	Newll2.head = NULL;
	Newll2.size = ll.size;

	// split into Left and Right Lists
	// Left list is Newll.head
	// Right list is RightList
	RightList = Newll.head;
	LeftList = Newll.head;

	// split n/2 left and n/2 or n/2 + 1 right
    RightList = RightList->next;
	for (int i = 0; (i < ll.size/2 - 1); i++)
	{
		RightList = RightList->next;
		LeftList = LeftList->next;
	}
	LeftList->next = NULL;
	LeftList = Newll.head;
	// creating ll.size number of new nodes
    for(int i = 0; i < ll.size; i++)
    {
        if (left == 1)
        {
			// for the first node
            if(Newll2.head == NULL)
            {
				// point head to first node
                Newll2.head = (ListNode *)(malloc(sizeof(ListNode)));
				// point temp2 to head
                temp2 = Newll2.head;
				// place item from left list into the temp2
                temp2->item = LeftList->item;
				// points to next node of left list
                LeftList = LeftList->next;
				// turns left into 0 to extract item from right list
                left = 0;
            }
			// for subsequent nodes taken from the left
            else
            {
                if (ll.size % 2 == 1 && i == ll.size -1)
                {
                    // creating a new node and placing into temp2->next
                    temp2->next = (ListNode *)(malloc(sizeof(ListNode)));
                    // shifting temp2 into the new node
                    temp2 = temp2->next;
                    // place item from right node into temp2
                    temp2->item = RightList->item;
                    // points to next node of right list
                    RightList = RightList->next;
                    // turns left into 1 to extract item from left list
                    left = 1;
                }
                else
                {
                    // creating a new node and placing into temp2->next
                    temp2->next = (ListNode *)(malloc(sizeof(ListNode)));
                    // shifting temp2 into the new node
                    temp2 = temp2->next;
                    // place item from left node into temp2
                    temp2->item = LeftList->item;
                    // points to next node of left list
                    LeftList = LeftList->next;
                    // turns left into 0 to extract item from right list
                    left = 0;
                }
            }
        }

		// for extracting items from right list
        else
        {
			// creating a new node and placing into temp2->next
            temp2->next = (ListNode *)(malloc(sizeof(ListNode)));
			// shifting temp2 into the new node
            temp2 = temp2->next;
			// place item from right node into temp2
            temp2->item = RightList->item;
			// points to next node of right list
            RightList = RightList->next;
			// turns left into 1 to extract item from left list
            left = 1;
        }
    }
	// after list created, set the next node to be NULL
    temp2->next = NULL;
	// return rearranged LinkedList
	return Newll2;
}
