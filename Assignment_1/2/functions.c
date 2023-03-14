#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *IntersectionArray(int *Arr1, int *Arr2, int lenArr1, int lenArr2) {}

int countCharOccurences(const char *str, int length, char ch)
{
  int res = 0;
  for (int i = 0; i < length; ++i)
  {
    res += str[i] == ch;
  }

  return res;
}

char findFirstNonRepeatingChar(const char *str, int length)
{
  for (int i = 0; i < length; ++i)
  {
    int flag = 0;
    for (int j = 0; j < length; ++j)
    {
      if (i == j)
        continue;

      if (str[i] == str[j])
      {
        flag = 1;
        break;
      }
    }
    if (flag == 0)
    {
      return str[i];
    }
  }
  return ' ';
}

int length(const char *string)
{
  if (string[0] == '\0')
    return 0;
  else
  {
    int res = 0;
    while (string[++res] != '\0')
      ;
    return res;
  }
}

void concat(char *destination, const char *source)
{
  int len_destination = length(destination);
  int len_source = length(source);

  for (int i = len_destination; i <= len_destination + len_source; ++i)
  {
    destination[i] = source[i - len_destination];
  }
}

char *findLongestCommonPrefix(char **strs, int numStr, int maxLen)
{
  char *res = (char *)malloc(sizeof(char) * maxLen);
  int flag = 0;
  char c = 0;
  char c_string[2] = {c, '\0'};

  int minLen = maxLen;
  for (int i = 0; i < numStr; ++i)
  {
    int l = length(strs[i]);
    if (l < minLen)
    {
      minLen = l;
    }
  }

  for (int i = 0; i < minLen; ++i)
  {
    flag = 0;
    c = strs[0][i];
    for (int j = 0; j < numStr; ++j)
    {
      if (strs[j][i] != c)
      {
        flag = 1;
        break;
      }
    }
    if (flag)
      break;

    c_string[0] = c;
    concat(res, c_string);
  }
  return res;
}

int *MaxMin(int *Arr, int lenArr)
{
  int highest = 0, secondHighest = 0, lowest = 1000000, secondLowest = 1000000;
  int cur;

  for (int i = 0; i < lenArr; ++i)
  {
    cur = Arr[i];
    if (cur > highest)
    {
      secondHighest = highest;
      highest = cur;
    }
    else if (cur >= secondHighest)
    {
      secondHighest = cur;
    }

    if (cur < lowest)
    {
      secondLowest = lowest;
      lowest = cur;
    }
    else if (cur <= secondLowest)
    {
      secondLowest = cur;
    }
  }

  // printf("Highest: %i\n", highest);
  // printf("Second Highest: %i\n", secondHighest);
  // printf("Lowest: %i\n", lowest);
  // printf("Second Lowest: %i\n", secondLowest);
}
