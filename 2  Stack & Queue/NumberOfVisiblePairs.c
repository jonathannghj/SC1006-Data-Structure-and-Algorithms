
int numMountainPairs(CDblLinkedList CDLL)
{
// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
    

// Write your code here
    
    int pairs = CDLL.size - 1;
    if(CDLL.size == 2)
    {
        return 1;
    }
    else if (CDLL.size < 2)
    {
        return 0;
    }
    CDblListNode *headPtr = NULL;
    CDblListNode *start = NULL;
    CDblListNode *end = NULL;

    CDblListNode *leftPtr = NULL;
    CDblListNode *rightPtr = NULL;

    start = CDLL.head;
    headPtr = CDLL.head;

    int length = CDLL.size;
    int left_visible = 1;
    int right_visible = 1;

    for (int i = 0; i < length - 2; i++)
    {
         end = start->next;
         end = end->next;

        while(end != headPtr)
        {
            if (start->item >= end->item)
            {
                leftPtr = end->pre;
                rightPtr = end->next;
                while (leftPtr != start)
                {
                    if (leftPtr->item > end->item)
                    {
                        left_visible = 0;
                    }
                    leftPtr = leftPtr->pre; 
                }
                while (rightPtr != start)
                {
                    if(rightPtr->item > end->item)
                    {
                        right_visible = 0;
                    }
                    rightPtr = rightPtr->next;
                }
            }
            else 
            {
                leftPtr = start->pre;
                rightPtr = start->next;
                while (leftPtr != end)
                {
                    if (leftPtr->item > start->item)
                    {
                        left_visible = 0;
                    }
                    leftPtr = leftPtr->pre; 
                }
                while (rightPtr != end)
                {
                    if(rightPtr->item > start->item)
                    {
                        right_visible = 0;
                    }
                    rightPtr = rightPtr->next;
                }
            }
        
            if(left_visible == 1 || right_visible == 1)
            {
                pairs++;
            }
            left_visible = 1;
            right_visible = 1;
            end = end->next;
        }
        start = start->next;
    }
    return pairs;
}
