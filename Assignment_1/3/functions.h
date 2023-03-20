#ifndef __LINKED_LIST
#define __LINKED_LIST

typedef struct Node
{
    int Element;
    struct Node *NextNode;
} Node;

typedef struct Node *PtrNode;

void Insert(PtrNode Head, int num);
PtrNode Find(PtrNode Head, int num);
void Print(PtrNode Head);

#endif