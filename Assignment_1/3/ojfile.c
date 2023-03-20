#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int Element;
    struct Node *NextNode;
} Node;

typedef struct Node *PtrNode;

void Insert(PtrNode Head, int num);
PtrNode Find(PtrNode Head, int num);
void Print(PtrNode Head);

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

int main()
{
    PtrNode Head = (PtrNode)malloc(sizeof(Node));
    Head->Element = 0;
    Head->NextNode = Head;

    int T;
    scanf("%i", &T);
    char choice[10];
    int num;
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