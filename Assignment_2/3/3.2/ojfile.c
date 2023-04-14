#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int val;
  struct node *left;
  struct node *right;
} node;

typedef node *tree;

node *create_node(int val);
node *insert(tree T, int val);

typedef struct deq_node
{
  node *n;
  struct deq_node *next;
  struct deq_node *prev;
  int length;
} deq_node;

typedef deq_node *deq;

void push(deq head, node *n);
void push_start(deq head, node *n);
node *pop(deq head);
node *pop_rear(deq head);
void print(deq head);
void print_reverse(deq head);
int is_empty(deq head);

void push(deq head, node *n)
{
  deq_node *new = (deq_node *)malloc(sizeof(node));
  new->n = n;

  deq_node *old_last = head->prev;
  head->prev = new;
  new->next = head;
  new->prev = old_last;
  old_last->next = new;
  head->length++;
}

void push_start(deq head, node *n)
{
  deq_node *new = (deq_node *)malloc(sizeof(deq_node));
  new->n = n;
  deq_node *old_first = head->next;
  new->prev = head;
  new->next = old_first;
  old_first->prev = new;
  head->next = new;
  head->length++;
}

node *pop(deq head)
{
  deq_node *old_first = head->next;
  head->next = old_first->next;
  old_first->next->prev = head;
  node *n = old_first->n;
  free(old_first);
  head->length--;
  return n;
}

node *pop_rear(deq head)
{

  deq_node *old_last = head->prev;
  old_last->prev->next = head;
  head->prev = old_last->prev;
  node *n = old_last->n;
  head->length--;
  return n;
}

void print(deq head)
{
  if (head->next == head)
  {
    printf("-1");
  }
  else
  {
    deq cur = head->next;
    while (cur != head)
    {
      printf("%i ", cur->n->val);
      cur = cur->next;
    }
  }
  printf("\n");
}

void print_reverse(deq head)
{
  if (head->prev == head)
  {
    printf("-1");
  }
  else
  {
    deq cur = head->prev;
    while (cur != head)
    {
      printf("%i ", cur->n->val);
      cur = cur->prev;
    }
  }
  printf("\n");
}

int is_empty(deq head)
{
  return (head->length == 0);
}

void free_deq(deq head)
{
  deq cur = head->next;
  while (cur != head)
  {
    deq temp = head->next; 
    free(cur);
    cur = temp;
  }
  free(head);
}

node *create_node(int val)
{
  node *new = (node *)malloc(sizeof(node));
  new->left = NULL;
  new->right = NULL;
  new->val = val;

  return new;
}

void level_order(tree T)
{

  if (T == NULL)
    return;

  deq head = (deq)malloc(sizeof(deq_node));
  head->n = NULL;
  head->next = head;
  head->prev = head;
  head->length = 0;

  push(head, T);
  node *cur = NULL;
  while (!is_empty(head))
  {
    cur = pop(head);
    printf("%i ", cur->val);
    if (cur->left)
      push(head, cur->left);
    if (cur->right)
      push(head, cur->right);
  }
  printf("\n");
  free_deq(head);
}

void free_tree(tree T)
{
  if (T == NULL)
      return;

  free_tree(T->left);
  free_tree(T->right);
  free(T);
}

int pre_index = 0;
tree get_tree(int *inorder, int *preorder, int start, int end)
{

  if (start > end)
    return NULL;
  else if (start < end)
  {
    tree T = create_node(preorder[pre_index]);

    int cur = -1;
    for (int i = start; i <= end; ++i)
    {
      if (inorder[i] == preorder[pre_index])
      {
        cur = i;
        break;
      }
    }
    ++pre_index;
    T->left = get_tree(inorder, preorder, start, cur - 1);
    T->right = get_tree(inorder, preorder, cur + 1, end);

    return T;
  }
  else
  {
    return create_node(preorder[pre_index++]);
  }

  }

int main()
{
  int T;
  scanf("%i", &T);
  for (int i = 0; i < T; ++i)
  {
    int N;
    scanf("%i", &N);
    int *inorder = (int *)malloc(sizeof(int)*N);
    int *preorder = (int *)malloc(sizeof(int)*N);
    for (int j = 0; j < N; ++j)
      scanf("%i", &inorder[j]);

    for (int j = 0; j < N; ++j)
      scanf("%i", &preorder[j]);

    tree t = get_tree(inorder, preorder, 0, N - 1);

    level_order(t);
    free_tree(t);
    free(inorder);
    free(preorder);
  }

  return 0;
}
