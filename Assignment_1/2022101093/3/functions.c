#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

void Insert(PtrNode Head, int num)
{
    PtrNode new = (PtrNode)malloc(sizeof(Node));
    new->Element = num;
    new->NextNode = Head->NextNode;
    Head->NextNode = new;
}

PtrNode Find(PtrNode Head, int num)
{
    PtrNode cur = Head->NextNode;
    PtrNode prev = Head;
    while (cur != Head)
    {
        if (cur->Element == num)
        {
            prev->NextNode = cur->NextNode;
            cur->NextNode = Head->NextNode;
            Head->NextNode = cur;

            return cur;
        }

        prev = cur;
        cur = cur->NextNode;
    }

    return NULL;
}

void Print(PtrNode Head)
{
    PtrNode cur = Head->NextNode;
    while (cur != Head)
    {
        printf("%i ", cur->Element);
        cur = cur->NextNode;
    }
    printf("\n");
}