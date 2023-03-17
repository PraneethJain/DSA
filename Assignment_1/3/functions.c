#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

void Insert(PtrNode Head, int num)
{
    PtrNode new_node = (PtrNode)malloc(sizeof(Node));
    new_node->Element = num;
    if (Head->PrevNode == NULL && Head->NextNode == NULL)
    {
        Head->PrevNode = new_node;
        Head->NextNode = new_node;
        new_node->NextNode = Head;
        new_node->PrevNode = Head;
    }
    else
    {
        new_node->PrevNode = Head->PrevNode;
        new_node->NextNode = Head;
        Head->PrevNode->NextNode = new_node;
        Head->PrevNode = new_node;
    }
}

PtrNode Find(PtrNode Head, int num)
{
    PtrNode cur = Head->NextNode;
    while (cur != Head)
    {
        if (cur->Element == num)
        {
            cur->NextNode->PrevNode = cur->PrevNode;
            cur->PrevNode->NextNode = cur->NextNode;

            Head->PrevNode->NextNode = cur;

            cur->NextNode = Head;
            cur->PrevNode = Head->PrevNode;

            Head->PrevNode = cur;

            return cur;
        }
        cur = cur->NextNode;
    }
    return NULL;
}

void Print(PtrNode Head)
{
    PtrNode cur = Head->PrevNode;
    while (cur != Head)
    {
        printf("%i ", cur->Element);
        cur = cur->PrevNode;
    }
    printf("\n");
}
