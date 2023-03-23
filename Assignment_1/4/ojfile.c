#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int row_num;
  int col_num;
  int val;
  struct node *next;
} node;

typedef struct row
{
  int row_num;
  node *first;
  struct row *next;
} row;

typedef struct cell
{
  int col;
  int row;
  int val;
  struct cell *next;
} cell;

int smaller(cell *x, cell *y);
struct cell *merge(struct cell *cell1, struct cell *cell2);
void split(struct cell *source, struct cell **front, struct cell **back);
void merge_sort(struct cell **head);

cell *add_read(int num_elements);
int add_compare(cell *head1, cell *head2);
void add_print(cell *head);
cell *add(cell *head1, cell *head2);
int get_length(cell *head);
cell *transpose_read(int num_elements);
void transpose(cell *head);
void print_cell(cell *head);

row *read_matrix(int num_elements);
void print_matrix(row *head);

row *multiply(row *head1, cell *head2);
row *convert(cell *inp);

int smaller(cell *x, cell *y)
{
  if (x->row < y->row)
    return 1;
  else if (x->row > y->row)
    return 0;
  else
    return (x->col < y->col);
}

struct cell *merge(struct cell *cell1, struct cell *cell2)
{
  struct cell *result = NULL;

  if (cell1 == NULL)
    return cell2;
  if (cell2 == NULL)
    return cell1;

  if (smaller(cell1, cell2))
  {
    result = cell1;
    result->next = merge(cell1->next, cell2);
  }
  else
  {
    result = cell2;
    result->next = merge(cell1, cell2->next);
  }

  return result;
}

void split(struct cell *source, struct cell **front, struct cell **back)
{
  struct cell *slow = source;
  struct cell *fast = source->next;

  while (fast != NULL)
  {
    fast = fast->next;
    if (fast != NULL)
    {
      slow = slow->next;
      fast = fast->next;
    }
  }

  *front = source;
  *back = slow->next;
  slow->next = NULL;
}

void merge_sort(struct cell **head)
{
  struct cell *temp = *head;
  struct cell *a;
  struct cell *b;

  if (temp == NULL || temp->next == NULL)
  {
    return;
  }

  split(temp, &a, &b);

  merge_sort(&a);
  merge_sort(&b);

  *head = merge(a, b);
}

cell *add_read(int num_elements)
{
  cell *head = (cell *)malloc(sizeof(cell));
  cell *prev = head;
  int x, y, val;
  for (int i = 0; i < num_elements; ++i)
  {
    cell *cur = (cell *)malloc(sizeof(cell));
    scanf("%i %i %i", &x, &y, &val);
    cur->row = x;
    cur->col = y;
    cur->val = val;
    cur->next = NULL;

    prev->next = cur;
    prev = cur;
  }

  return head;
}

cell *transpose_read(int num_elements)
{
  cell *head = (cell *)malloc(sizeof(cell));
  cell *prev = NULL;
  int x, y, val;
  for (int i = 0; i < num_elements; ++i)
  {
    cell *cur;
    if (i == 0)
    {
      cur = head;
    }
    else
    {
      cur = (cell *)malloc(sizeof(cell));
    }
    scanf("%i %i %i", &x, &y, &val);
    cur->row = x;
    cur->col = y;
    cur->val = val;
    cur->next = NULL;

    if (prev != NULL)
    {
      prev->next = cur;
    }
    prev = cur;
  }

  return head;
}

int add_compare(cell *c1, cell *c2)
{
  if (c1->row > c2->row)
  {
    return 1;
  }
  else if (c1->row < c2->row)
  {
    return -1;
  }
  else
  {
    if (c1->col > c2->col)
    {
      return 1;
    }
    else if (c1->col < c2->col)
    {
      return -1;
    }
    else
    {
      return 0;
    }
  }
}

void transpose(cell *head)
{
  cell *cur = head;
  int temp;
  while (cur != NULL)
  {
    temp = cur->row;
    cur->row = cur->col;
    cur->col = temp;
    cur = cur->next;
  }
}

cell *add(cell *head1, cell *head2)
{
  cell *res_head = (cell *)malloc(sizeof(cell));
  cell *prev = res_head;
  cell *node1 = head1->next;
  cell *node2 = head2->next;
  while (node1 != NULL && node2 != NULL)
  {
    int x = add_compare(node1, node2);
    cell *cur = (cell *)malloc(sizeof(cell));
    cur->next = NULL;
    if (x == 1)
    {
      cur->row = node2->row;
      cur->col = node2->col;
      cur->val = node2->val;
      node2 = node2->next;
    }
    else if (x == -1)
    {
      cur->row = node1->row;
      cur->col = node1->col;
      cur->val = node1->val;
      node1 = node1->next;
    }
    else
    {
      cur->row = node1->row;
      cur->col = node1->col;
      cur->val = node1->val + node2->val;
      node1 = node1->next;
      node2 = node2->next;
    }
    if (cur->val != 0)
    {
      prev->next = cur;
      prev = cur;
    }
  }

  if (node1 == NULL)
  {
    prev->next = node2;
  }
  else if (node2 == NULL)
  {
    prev->next = node1;
  }

  return res_head;
}

void add_print(cell *head)
{
  cell *cur = head->next;
  while (cur != NULL)
  {
    printf("%i %i %i\n", cur->row, cur->col, cur->val);
    cur = cur->next;
  }
}

void print_cell(cell *head)
{
  cell *cur = head;
  while (cur != NULL)
  {
    printf("%i %i %i\n", cur->row, cur->col, cur->val);
    cur = cur->next;
  }
}

int get_length(cell *head)
{
  cell *cur = head->next;
  int i = 0;
  while (cur != NULL)
  {
    ++i;
    cur = cur->next;
  }
  return i;
}

row *read_matrix(int num_elements)
{
  row *head = (row *)malloc(sizeof(row));
  head->row_num = -1;
  head->first = NULL;
  head->next = NULL;
  row *prev_row = head;
  node *prev_node;
  row *cur_row;
  int i, j, val;
  for (int k = 0; k < num_elements; ++k)
  {
    scanf("%i %i %i", &i, &j, &val);
    node *cur_node = (node *)malloc(sizeof(node));
    cur_node->row_num = i;
    cur_node->col_num = j;
    cur_node->val = val;
    cur_node->next = NULL;
    if (k == 0)
    {
      cur_row = (row *)malloc(sizeof(row));
      cur_row->row_num = cur_node->row_num;
      cur_row->next = NULL;
      cur_row->first = cur_node;
      prev_row->next = cur_row;
      prev_row = cur_row;
    }
    else
    {
      if (cur_node->row_num == cur_row->row_num)
      {
        prev_node->next = cur_node;
      }
      else if (cur_node->row_num > cur_row->row_num)
      {
        prev_row = cur_row;
        cur_row = (row *)malloc(sizeof(row));
        cur_row->row_num = cur_node->row_num;
        cur_row->next = NULL;
        cur_row->first = cur_node;
        prev_row->next = cur_row;
      }
    }
    prev_node = cur_node;
  }

  return head;
}

void print_matrix(row *head)
{
  row *cur_row = head->next;
  while (cur_row != NULL)
  {
    node *cur_node = cur_row->first;
    while (cur_node != NULL)
    {
      printf("%i %i %i\n", cur_node->row_num, cur_node->col_num, cur_node->val);
      cur_node = cur_node->next;
    }
    cur_row = cur_row->next;
  }
}

row *convert(cell *inp)
{
  cell *cur = inp;
  row *head = (row *)malloc(sizeof(row));
  head->row_num = -1;
  head->first = NULL;
  head->next = NULL;
  row *prev_row = head;
  node *prev_node;
  row *cur_row;
  int k = 0;
  while (cur != NULL)
  {
    node *cur_node = (node *)malloc(sizeof(node));
    cur_node->row_num = cur->row;
    cur_node->col_num = cur->col;
    cur_node->val = cur->val;
    cur_node->next = NULL;
    if (k == 0)
    {
      cur_row = (row *)malloc(sizeof(row));
      cur_row->row_num = cur_node->row_num;
      cur_row->next = NULL;
      cur_row->first = cur_node;
      prev_row->next = cur_row;
      prev_row = cur_row;
    }
    else
    {
      if (cur_node->row_num == cur_row->row_num)
      {
        prev_node->next = cur_node;
      }
      else if (cur_node->row_num > cur_row->row_num)
      {
        prev_row = cur_row;
        cur_row = (row *)malloc(sizeof(row));
        cur_row->row_num = cur_node->row_num;
        cur_row->next = NULL;
        cur_row->first = cur_node;
        prev_row->next = cur_row;
      }
    }
    prev_node = cur_node;
    cur = cur->next;
    k += 1;
  }

  return head;
}

int product_size = 0;
row *multiply(row *head1, cell *head2)
{
  row *res = (row *)malloc(sizeof(row));
  res->first = NULL;
  res->next = NULL;
  res->row_num = -1;
  row *res_prev_row = res;

  transpose(head2);
  merge_sort(&head2);
  row *thead2 = convert(head2);
  row *rowa = head1->next;
  while (rowa != NULL)
  {
    int flag = 1;
    row *res_cur_row = (row *)malloc(sizeof(row));
    res_cur_row->first = NULL;
    res_cur_row->next = NULL;
    res_cur_row->row_num = rowa->row_num;
    row *rowb = thead2->next;
    node *res_prev_node = NULL;
    while (rowb != NULL)
    {
      int value = 0;
      node *n1 = rowa->first;
      node *n2 = rowb->first;
      while (n1 != NULL && n2 != NULL)
      {
        if (n1->col_num > n2->col_num)
        {
          n2 = n2->next;
        }
        else if (n1->col_num < n2->col_num)
        {
          n1 = n1->next;
        }
        else
        {
          value += n1->val * n2->val;
          n1 = n1->next;
          n2 = n2->next;
        }
      }
      if (value != 0)
      {
        flag = 0;
        product_size++;
        node *res_cur_node = (node *)malloc(sizeof(node));
        res_cur_node->row_num = rowa->row_num;
        res_cur_node->col_num = rowb->row_num;
        res_cur_node->val = value;
        res_cur_node->next = NULL;
        if (res_prev_node == NULL)
        {
          res_cur_row->first = res_cur_node;
        }
        else
        {
          res_prev_node->next = res_cur_node;
        }
        res_prev_node = res_cur_node;
      }
      rowb = rowb->next;
    }
    if (!flag)
    {
      res_prev_row->next = res_cur_row;
      res_prev_row = res_cur_row;
    }
    rowa = rowa->next;
  }

  return res;
}

int main()
{

  char opt[100];
  scanf("%s", opt);
  char x = opt[0];
  if (x == 'T')
  {
    int num_rows, num_cols, num_elements;
    scanf("%i %i %i", &num_rows, &num_cols, &num_elements);
    cell *head = transpose_read(num_elements);
    transpose(head);
    merge_sort(&head);
    printf("%i\n", num_elements);
    print_cell(head);
  }
  else if (x == 'A')
  {
    int n, m, k1, k2;
    scanf("%i %i %i %i", &n, &m, &k1, &k2);
    cell *head1 = add_read(k1);
    cell *head2 = add_read(k2);
    cell *res = add(head1, head2);
    printf("%i\n", get_length(res));
    add_print(res);
  }
  else if (x == 'M')
  {
    int n, m, l, k1, k2;
    scanf("%i %i %i %i %i", &n, &m, &l, &k1, &k2);
    row *head1 = read_matrix(k1);
    cell *head2 = transpose_read(k2);
    row *product = multiply(head1, head2);
    printf("%i\n", product_size);
    print_matrix(product);
  }

  return 0;
}
