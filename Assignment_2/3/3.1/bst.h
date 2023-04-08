#ifndef __BST_H
#define __BST_H

typedef struct node
{
  int val;
  struct node *left;
  struct node *right;
} node;

typedef node *tree;

node *create_node(int val);
node *insert(tree T, int val);

void pre_order(tree T);
void in_order(tree T);
void zig_zag_order(tree T);

#endif
