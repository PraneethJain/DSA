#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int unique_elements_count = 0;

void swap(char *x, char *y)
{
  char temp = *x;
  *x = *y;
  *y = temp;
}

int ceil_log_10(int x)
{
  int res = 1;
  while (x)
  {
    x /= 10;
    res += 1;
  }
  return res;
}

char *int_to_str(int x)
{
  char *s = (char *)malloc((ceil_log_10(x)) * sizeof(char));
  sprintf(s, "%i", x);

  return s;
}

void reverseString(char *str, int length)
{
  for (int i = 0; i < length / 2; ++i)
  {
    swap(&str[i], &str[length - i - 1]);
  }
}

int *uniqueElements(int *arr, int length)
{
  int max = arr[0];
  for (int i = 1; i < length; ++i)
  {
    if (arr[i] > max)
    {
      max = arr[i];
    }
  }
  max++;
  int map[max];
  for (int i = 0; i < max; ++i)
  {
    map[i] = 0;
  }
  int *res = (int *)malloc(sizeof(int) * length);
  for (int i = 0; i < length; ++i)
  {
    map[arr[i]]++;
    if (map[arr[i]] == 1)
      res[unique_elements_count++] = arr[i];
  }

  return res;
}

char *compressString(char *str, int length)
{

  char prev = str[0];
  int cur_count = 1;
  char cur;
  char *num_str;
  char *compressed_string = (char *)malloc(sizeof(char) * (2 * length + 1));
  int compressed_string_length = 0;
  for (int i = 0; i < length; ++i)
  {
    cur = str[i];
    if (i == 0)
    {
      continue;
    }
    if (cur != prev)
    {
      compressed_string[compressed_string_length++] = prev;
      num_str = int_to_str(cur_count);
      for (int i = 0; i < ceil_log_10(cur_count) - 1; ++i)
      {
        compressed_string[compressed_string_length++] = num_str[i];
      }
      free(num_str);
      cur_count = 1;
    }
    else
    {
      cur_count++;
    }
    prev = cur;
  }

  compressed_string[compressed_string_length++] = cur;
  num_str = int_to_str(cur_count);
  for (int i = 0; i < ceil_log_10(cur_count) - 1; ++i)
  {
    compressed_string[compressed_string_length++] = num_str[i];
  }
  free(num_str);
  compressed_string[compressed_string_length++] = '\0';

  return compressed_string;
}

int **transpose(int **matrix, int NumRow, int NumCol)
{
  int **res = (int **)malloc(sizeof(int *) * NumCol);
  for (int i = 0; i < NumCol; ++i)
  {
    *(res + i) = (int *)malloc(sizeof(int) * NumRow);
  }
  for (int i = 0; i < NumCol; ++i)
  {
    for (int j = 0; j < NumRow; ++j)
    {
      res[i][j] = matrix[j][i];
    }
  }

  return res;
}

void print_matrix(int **matrix, int NumRow, int NumCol)
{
  for (int i = 0; i < NumRow; ++i)
  {
    for (int j = 0; j < NumCol; ++j)
    {
      printf("%i ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
