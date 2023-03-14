#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int T;
  scanf("%i", &T);

  char choice[10];
  for (int i = 0; i < T; ++i) {
    scanf("%s", choice);
    if (strcmp(choice, "OPER1") == 0) {

      int n;
      scanf("%i", &n);
      char s[n];
      scanf("%s", s);
      reverseString(s, n);
      printf("%s\n", s);

    } else if (strcmp(choice, "OPER2") == 0) {

      int n;
      scanf("%i", &n);
      char s[n + 1];
      scanf("%s", s);
      char *compressedString = compressString(s, n);
      printf("%s\n", compressedString);

    } else if (strcmp(choice, "OPER3") == 0) {

      int n;
      scanf("%i", &n);
      int arr[n];
      for (int i = 0; i < n; ++i) {
        scanf("%i", &arr[i]);
      }
      int *unique_arr = uniqueElements(arr, n);
      for (int i = 0; i < unique_elements_count; ++i) {
        printf("%i ", unique_arr[i]);
      }
      printf("\n");

    } else if (strcmp(choice, "OPER4") == 0) {

      int R, C;
      scanf("%i %i", &R, &C);
      int **matrix = (int **)malloc(sizeof(int *) * R);
      for (int i = 0; i < R; ++i) {
        *(matrix + i) = (int *)malloc(sizeof(int) * C);
      }

      for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
          scanf("%i", &matrix[i][j]);
        }
      }

      int **transposed_matrix = transpose(matrix, R, C);
      for (int i = 0; i < C; ++i) {
        for (int j = 0; j < R; ++j) {
          printf("%i ", transposed_matrix[i][j]);
        }
        printf("\n");
      }
    }
  }

  return 0;
}
