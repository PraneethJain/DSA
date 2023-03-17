#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int T;
    scanf("%i", &T);

    char choice[10];
    int num;
    PtrNode Head = (PtrNode)malloc(sizeof(Node));
    Head->Element = 0;
    Head->NextNode = NULL;
    Head->PrevNode = NULL;
    for (int i = 0; i < T; ++i)
    {
        scanf("%s", choice);
        char x = choice[4];
        if (x == '1')
        {
            scanf("%i", &num);
            Insert(Head, num);
        }
        else if (x == '2')
        {
            scanf("%i", &num);
            Find(Head, num);
        }
        else if (x == '3')
        {
            Print(Head);
        }
    }

    return 0;
}