void expressionQ(char *infix, Queue* qPtr)
{
    int length = strlen(infix);

    for(int i = 0; i < length; i++)
    {
        if (infix[i] == ' ')
        {
            continue;
        }
        else if (infix[i] >= 48 && infix[i] <= 57)
        {
            int number = 0;
            while (infix[i] >= 48 && infix[i] <= 57)
            { 
                number = number * 10 + ((int)(infix[i] - 48));
                i++;
            }
            i--;
            enqueue(qPtr, number, OPERAND);
        }

        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '%' || infix[i] == '(' || infix[i] == ')')
        {
            enqueue(qPtr, infix[i], OPT);
        }
    }
}
