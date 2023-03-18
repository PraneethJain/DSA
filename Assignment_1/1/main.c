#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int T;
  scanf("%i", &T);

  char choice[10];
  for (int i = 0; i < T; ++i)
  {
    scanf("%s", choice);
    char x = choice[4];
    if (x == '1')
    {

      int n;
      scanf("%i", &n);
      char s[n];
      scanf("%s", s);
      reverseString(s, n);
      printf("%s\n", s);
    }
    else if (x == '2')
    {

      int n;
      scanf("%i", &n);
      char s[n + 1];
      scanf("%s", s);
      char *compressedString = compressString(s, n);
      printf("%s\n", compressedString);
    }
    else if (x == '3')
    {

      int n;
      scanf("%i", &n);
      int arr[n];
      for (int i = 0; i < n; ++i)
      {
        scanf("%i", &arr[i]);
      }
      int *unique_arr = uniqueElements(arr, n);
      for (int i = 0; i < unique_elements_count; ++i)
      {
        printf("%i ", unique_arr[i]);
      }
      printf("\n");
    }
    else if (x == '4')
    {

      int R, C;
      scanf("%i %i", &R, &C);
      int **matrix = (int **)malloc(sizeof(int *) * R);
      for (int i = 0; i < R; ++i)
      {
        *(matrix + i) = (int *)malloc(sizeof(int) * C);
      }

      for (int i = 0; i < R; ++i)
      {
        for (int j = 0; j < C; ++j)
        {
          scanf("%i", &matrix[i][j]);
        }
      }

      int **transposed_matrix = transpose(matrix, R, C);
      for (int i = 0; i < C; ++i)
      {
        for (int j = 0; j < R; ++j)
        {
          printf("%i ", transposed_matrix[i][j]);
        }
        printf("\n");
      }
    }
  }

  return 0;
}
