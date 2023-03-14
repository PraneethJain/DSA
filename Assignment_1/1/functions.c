#include "functions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int unique_elements_count = 0;

void swap(char *x, char *y) {
  char temp = *x;
  *x = *y;
  *y = temp;
}

void reverseString(char *str, int length) {
  for (int i = 0; i < length / 2; ++i) {
    swap(&str[i], &str[length - i - 1]);
  }
}

int *uniqueElements(int *arr, int length) {
  int map[1000001] = {0};
  int *res = (int *)malloc(sizeof(int) * length);
  for (int i = 0; i < length; ++i) {
    map[arr[i]]++;
    if (map[arr[i]] == 1)
      res[unique_elements_count++] = arr[i];
  }

  return res;
}

int ceil_log_10(int x) {
  int res = 1;
  while (x) {
    x /= 10;
    res += 1;
  }
  return res;
}

char *int_to_str(int x) {
  char *s = (char *)malloc((ceil_log_10(x)) * sizeof(char));
  sprintf(s, "%i", x);

  return s;
}

int length(const char *string) {
  if (string[0] == '\0')
    return 0;
  else {
    int res = 0;
    while (string[++res] != '\0')
      ;
    return res;
  }
}

void concat(char *destination, const char *source) {
  int len_destination = length(destination);
  int len_source = length(source);

  for (int i = len_destination; i <= len_destination + len_source; ++i) {
    destination[i] = source[i - len_destination];
  }
}

char *compressString(char *str, int length) {

  char prev[2] = {str[0], '\0'};
  int cur_count = 1;
  char cur;
  char *res = (char *)malloc(sizeof(char) * (2 * length + 1));
  for (int i = 0; i < length; ++i) {
    cur = str[i];
    if (i == 0) {
      continue;
    }
    if (cur != prev[0]) {
      concat(res, prev);
      concat(res, int_to_str(cur_count));
      cur_count = 1;
    } else {
      cur_count++;
    }
    prev[0] = cur;
  }
  char cur_string[2] = {cur, '\0'};
  concat(res, cur_string);
  concat(res, int_to_str(cur_count));

  return res;
}

int **transpose(int **matrix, int NumRow, int NumCol) {
  int **res = (int **)malloc(sizeof(int *) * NumCol);
  for (int i = 0; i < NumCol; ++i) {
    *(res + i) = (int *)malloc(sizeof(int) * NumRow);
  }
  for (int i = 0; i < NumCol; ++i) {
    for (int j = 0; j < NumRow; ++j) {
      res[i][j] = matrix[j][i];
    }
  }

  return res;
}

void print_matrix(int **matrix, int NumRow, int NumCol) {
  for (int i = 0; i < NumRow; ++i) {
    for (int j = 0; j < NumCol; ++j) {
      printf("%i ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

// int main()
// {
//   int n;
//   scanf("%i", &n);
//   int arr[n];
//   for (int i = 0; i < n; ++i)
//   {
//     scanf("%i", &arr[i]);
//   }
//   int *unique_arr = uniqueElements(arr, n);
//   for (int i = 0; i < unique_elements_count; ++i)
//   {
//     printf("%i ", unique_arr[i]);
//   }
//   printf("\n");
// }
// int main() {
//   int R, C;
//   scanf("%i %i", &R, &C);
//   int **matrix = (int **)malloc(sizeof(int *) * R);
//   for (int i = 0; i < R; ++i) {
//     *(matrix + i) = (int *)malloc(sizeof(int) * C);
//   }
//   for (int i = 0; i < R; ++i) {
//     for (int j = 0; j < C; ++j) {
//       scanf("%i", &matrix[i][j]);
//     }
//   }
//   printf("\n");
//   print_matrix(matrix, R, C);
//   int **t = transpose(matrix, R, C);
//   print_matrix(t, C, R);
//   return 0;
// }
