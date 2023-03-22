#ifndef __MATRIX
#define MATRIX

extern int product_size;

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

cell *read_other(int num_elements);
int compare_other(cell *c1, cell *c2);
cell *add_other(cell *head1, cell *head2);
void print_other(cell *head);
int get_length_other(cell *head);

row *read_matrix(int num_elements);
void print_matrix(row *head);
row *transpose(row *head);
row *multiply(row *head1, row *head2);

#endif