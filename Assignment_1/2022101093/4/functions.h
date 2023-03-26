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

#endif