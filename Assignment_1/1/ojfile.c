#include <stdio.h>
#include <stdlib.h>

void swap(char *x, char *y);
void reverseString(char *str, int length);
int *uniqueElements(int *arr, int length);
char *compressString(char *str, int length);
int **transpose(int **matrix, int NumRow, int NumCol);
int ceil_log_10(int x);
char *int_to_str(int x);

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
      free(compressedString);
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
      free(unique_arr);
      unique_elements_count = 0;
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

      for (int i = 0; i < R; ++i)
      {
        free(matrix[i]);
      }
      free(matrix);

      for (int i = 0; i < C; ++i)
      {
        free(transposed_matrix[i]);
      }
      free(transposed_matrix);
    }
  }
  return 0;
}
