void reverseString(char *string)
{   
    int length = 0;
    for(int i = 0; string[i]!= '\0';i++)
    {
        if (string[i] == '(')
        {
            string[i] = ')';
        }
        else if (string[i] == ')')
        {
            string[i] = '(';
        }
        length++;
    }
    char temp;

    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        temp = string[start];
        string[start] = string[end];
        string[end] = temp;
        start++;
        end--;
    }
    
}
int precedence(char c)
{
    if (c == '+' || c == '-')
    {
        return 1;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    else 
    {
        return 0;
    }
}

void in2PreLL(char* infix, LinkedList *inExpLL)
{
    Stack S;
    S.size = 0;
    S.head = NULL;

    LinkedList tempList;
    tempList.size = 0;
    tempList.head = NULL;

    
    int length = 0;
    for(int i = 0; infix[i] != '\0'; i++)
    {
        length++;
    }

    for(int i = 0; i < length; i++)
    {
        if (infix[i] >= 48 && infix[i] <= 57)
        {
            int number = 0;
            while (infix[i] >= 48 && infix[i] <= 57)
            { 
                number = number * 10 + ((int)(infix[i] - 48));
                i++;
            }
            i--;
            insertNode(&tempList, number, OPERAND);
        }

        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '%')
        {
            insertNode(&tempList, infix[i], OPT);
        }
        else if (infix[i] == '(')
        {
            insertNode(&tempList, ')', OPT);
        } 
        else if (infix[i] == ')')
        {
            insertNode(&tempList, '(', OPT);
        }
    }

    ListNode *temp = NULL;
    temp = tempList.head;

    for (int i = 0; i < tempList.size; i++)
    {
        if (temp->type == OPERAND)
        {
            insertNode(inExpLL, temp->item, OPERAND);
        }
        else if (temp->item == '(')
        {
            push(&S, temp->item);
        }
        else if (temp->item == ')')
        {
            while(peek(S) != '(')
            {
                insertNode(inExpLL, peek(S), OPT);
                pop(&S);
                
            }
            pop(&S);
        }
        else
        {   
            while(isEmptyStack(S) == 0 && peek(S) != '(' && (precedence(peek(S)) > precedence(temp->item)))
            {
                insertNode(inExpLL, peek(S), OPT);
                pop(&S);
            }
            push(&S, temp->item);
        }
        temp = temp->next;
    }
    while(isEmptyStack(S) == 0)
    {
        insertNode(inExpLL, peek(S), OPT);
        pop(&S);
    }

}
