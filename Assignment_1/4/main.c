#include "functions.h"
#include <stdio.h>

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
    int n, m, k1, k2;
    scanf("%i %i %i %i", &n, &m, &k1, &k2);
    cell *head1 = read_other(k1);
    cell *head2 = read_other(k2);
    cell *res = add_other(head1, head2);
    printf("%i\n", get_length_other(res));
    print_other(res);
  }
  else if (x == 'M')
  {
    int n, m, l, k1, k2;
    scanf("%i %i %i %i %i", &n, &m, &l, &k1, &k2);
    row *head1 = read_matrix(k1);
    row *head2 = read_matrix(k2);
    row *product = multiply(head1, head2);
    printf("%i\n", product_size);
    print_matrix(product);
  }

  return 0;
}
