#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int val;
  struct node *left;
  struct node *right;
} node;

typedef node * tree;

node *create_node(int val);
node *insert(tree T, int val);

void pre_order(tree T);
void zig_zag_order(tree T);

node *create_node(int val)
{
  node *new = (node *)malloc(sizeof(node));
  new->left = NULL;
  new->right = NULL;
  new->val = val;

  return new;
}

node *insert(tree T, int val)
{
  if (T == NULL)
    return create_node(val);
  
  if (val < T->val)
  {
    T->left = insert(T->left, val);
  }
  else if (val > T->val)
  {
    T->right = insert(T->right, val);
  }

  return T;
}

void pre_order(tree T)
{
  if (T == NULL)
    return;

  printf("%i ", T->val);
  pre_order(T->left);
  pre_order(T->right);
}

void zig_zag_order(tree T)
{
}

int main()
{
  tree T = NULL;
  T = insert(T, 20);
  T = insert(T, 10);
  T = insert(T, 25);
  T = insert(T, 5);
  T = insert(T, 15);
  T = insert(T, 23);
  T = insert(T, 30);
  pre_order(T);
  printf("\n");
  zig_zag_order(T);
  printf("\n");

  return 0;
}
