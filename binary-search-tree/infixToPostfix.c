#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct nd
{
    char c;
    struct nd *next;
} node;

node *top = NULL;

void push(char x)
{
    node *n = malloc(sizeof(node));
    n->next = top;
    top = n;
    n->c = x;
}

char pop()
{
    char p;
    node *n = top;
    top = top->next;
    p = n->c;
    free(n);
    return p;
}

char stacktop()
{
    if (top == NULL)
        return '\0';
    else
        return top->c;
}

// check operator
int checkpr(char temp)
{
    int pr;
    if (temp == '^')
        pr = 3;
    else if (temp == '*' || temp == '/')
        pr = 2;
    else if (temp == '+' || temp == '-')
        pr = 1;
    else
        pr = -1;
    return pr;
}

void checkoper(char ck)
{
    if (stacktop() == '\0')
        push(ck);
    else
    {
        if (checkpr(ck) <= checkpr(stacktop()))
            while ((checkpr(ck) <= checkpr(stacktop())) && (stacktop() != '\0'))
                printf("%c", pop());
        push(ck);
    }
}

void intopost(char *infix)
{
    char ch;
    int i = 0;
    while ((ch = infix[i++]) != '\0' && ch != '\n')
    {
        if (isalnum(ch))
        {
            printf("%c", ch);
        }
        else if (ch == '(')
        {
            push(ch);
        }
        else if (ch == ')')
        {
            while (stacktop() != '(')
            {
                printf("%c", pop());
            }
            pop(); // Pop '(' from stack
        }
        else
        {
            checkoper(ch);
        }
    }

    while (stacktop() != '\0')
    {
        printf("%c", pop());
    }
    printf("\n");
}

int main()
{
    char infix[100];
    printf("---------------------------\n");
    printf("\n");
    printf("Enter the infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    printf("\n");
    printf("The postfix expression: ");
    intopost(infix);
    printf("\n");
    printf("---------------------------\n");
    return 0;
}