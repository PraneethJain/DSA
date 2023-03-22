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

row *read_matrix(int num_elements);
void print_matrix(row *head);
row *transpose(row *head);

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
  for (int k = 0;  k < num_elements; ++k)
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

void insert(row *head, node *to_insert)
{
  row *cur_row = head->next;
  row *prev_row = head;
  while (cur_row != NULL)
  {
    if (cur_row->row_num == to_insert->row_num)
    {
      node *cur_node = cur_row->first;
      node *prev_node = NULL;
      while (cur_node != NULL)
      {
        if (cur_node->col_num > to_insert->col_num)
        {
          if (prev_node == NULL)
          {
            cur_row->first = to_insert;
          }
          else
          {
            prev_node->next = to_insert;
          }
          to_insert->next = cur_node;
          return;
        }
        prev_node = cur_node;
        cur_node = cur_node->next;
      }
      to_insert->next = NULL;
      prev_node->next = to_insert;
      return;
    }
    else if (cur_row->row_num > to_insert->row_num)
    {
      row *to_insert_row = (row *)malloc(sizeof(row));
      to_insert->next = NULL;
      to_insert_row->next = cur_row;
      to_insert_row->row_num = to_insert->row_num;
      to_insert_row->first = to_insert;
      prev_row->next = to_insert_row;
      return;
    }
    prev_row = cur_row;
    cur_row = cur_row->next;
  }
  row *to_insert_row = (row *)malloc(sizeof(row));
  prev_row->next = to_insert_row;
  to_insert_row->row_num = to_insert->row_num;
  to_insert_row->next = NULL;
  to_insert_row->first = to_insert;
  to_insert->next = NULL;
}

row *transpose(row *head)
{
  row *res_head = (row *)malloc(sizeof(row));
  res_head->first = NULL;
  res_head->next = NULL;
  res_head->row_num = -1;
  row *cur_row = head->next;
  while (cur_row != NULL)
  {
    node *cur_node = cur_row->first;
    while (cur_node != NULL)
    {
      node *res_cur_node = (node *)malloc(sizeof(node));
      res_cur_node->row_num = cur_node->col_num;
      res_cur_node->col_num = cur_node->row_num;
      res_cur_node->val = cur_node->val;
      insert(res_head, res_cur_node);
      cur_node = cur_node->next;
    }
    cur_row = cur_row->next;
  }
  
  return res_head;
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
    row *head = read_matrix(num_elements);
    row *transposed = transpose(head);
    printf("%i\n", num_elements);
    print_matrix(transposed);
  }
  else if (x == 'A')
  {
    
  }
  else if (x == 'M')
  {
    
  }
  
  return 0;
}
