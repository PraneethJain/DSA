#include <stdio.h>
#include <stdlib.h>

int *intersectionArray(int *Arr1, int *Arr2, int lenArr1, int lenArr2);
int countCharOccurences(const char *str, int length, char ch);
char findFirstNonRepeatingChar(const char *str, int length);
char *findLongestCommonPrefix(char **str, int numStr, int maxLen);
int *maxMin(int *Arr, int lenArr);
char *removeSubstring(char *str, int strLength, const char *substr, int substrLength);

int max_min_array_size = 0;
int intersection_array_size = 0;

int min(int x, int y) { return x > y ? y : x; }
int max(int x, int y) { return x > y ? x : y; }

int max_in_array(int *arr, int length)
{
    int max = arr[0];
    for (int i = 0; i < length; ++i)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int *intersectionArray(int *Arr1, int *Arr2, int lenArr1, int lenArr2)
{
    int len_f1 = max_in_array(Arr1, lenArr1) + 1;
    int f1[len_f1];
    for (int i = 0; i < len_f1; ++i)
    {
        f1[i] = 0;
    }
    int len_f2 = max_in_array(Arr2, lenArr2) + 1;
    int f2[len_f2];
    for (int i = 0; i < len_f2; ++i)
    {
        f2[i] = 0;
    }

    for (int i = 0; i < lenArr1; ++i)
    {
        ++f1[Arr1[i]];
    }
    for (int i = 0; i < lenArr2; ++i)
    {
        ++f2[Arr2[i]];
    }

    int res[lenArr1];
    for (int i = 0; i < min(len_f1, len_f2); ++i)
    {
        for (int j = 0; j < min(f1[i], f2[i]); ++j)
        {
            res[intersection_array_size++] = i;
        }
    }
    int *intersection_array = (int *)malloc(sizeof(int) * intersection_array_size);
    for (int i = 0; i < intersection_array_size; ++i)
    {
        intersection_array[i] = res[i];
    }
    return intersection_array;
}

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
    return -1;
}

char *findLongestCommonPrefix(char **str, int numStr, int maxLen)
{
    char *res = (char *)malloc(sizeof(char) * maxLen);
    int flag = 0;
    char c = 0;
    int res_len = 0;

    for (int i = 0; i < maxLen; ++i)
    {
        flag = 0;
        c = str[0][i];
        for (int j = 0; j < numStr; ++j)
        {
            if (str[j][i] != c)
            {
                flag = 1;
                break;
            }
        }
        if (flag)
            break;

        res[res_len++] = c;
    }
    return res;
}

int *maxMin(int *Arr, int lenArr)
{
    int runningMax[lenArr];
    int runningMinRev[lenArr];

    runningMax[0] = 0;
    for (int i = 1; i < lenArr; ++i)
    {
        runningMax[i] = max(runningMax[i - 1], Arr[i - 1]);
    }

    runningMinRev[lenArr - 1] = 1000001;
    for (int i = lenArr - 2; i >= 0; --i)
    {
        runningMinRev[i] = min(runningMinRev[i + 1], Arr[i + 1]);
    }

    int *res = (int *)malloc(sizeof(int) * lenArr);
    for (int i = 0; i < lenArr; ++i)
    {
        if (Arr[i] > runningMax[i] && Arr[i] < runningMinRev[i])
        {
            res[max_min_array_size++] = i;
        }
    }
    return res;
}

char *removeSubstring(char *str, int strLength, const char *substr, int substrLength)
{
    int is_equal;
    int cur_res_length = 0;
    char *res = (char *)malloc(sizeof(char) * strLength);
    for (int i = 0; i < strLength; ++i)
    {
        is_equal = 1;
        if (i + substrLength > strLength)
        {
            is_equal = 0;
        }
        else
        {
            for (int j = 0; j < substrLength; ++j)
            {
                if (str[i + j] != substr[j])
                {
                    is_equal = 0;
                    break;
                }
            }
        }
        if (!is_equal)
        {
            res[cur_res_length++] = str[i];
        }
        else
        {
            i += substrLength - 1;
        }
    }
    return res;
}

int main()
{
    int T;
    scanf("%i", &T);
    char choice[100];
    for (int i = 0; i < T; ++i)
    {
        scanf("%s", choice);
        char x = choice[4];
        if (x == '1')
        {

            int n1, n2;
            scanf("%i %i", &n1, &n2);
            int arr1[n1];
            int arr2[n2];
            for (int i = 0; i < n1; ++i)
            {
                scanf("%i", &arr1[i]);
            }
            for (int i = 0; i < n2; ++i)
            {
                scanf("%i", &arr2[i]);
            }
            int *res = intersectionArray(arr1, arr2, n1, n2);

            for (int i = 0; i < intersection_array_size; ++i)
            {
                printf("%i ", res[i]);
            }
            free(res);
            intersection_array_size = 0;
            printf("\n");
        }
        else if (x == '2')
        {
            int n;
            scanf("%i", &n);
            char str[n];
            scanf("%s", str);
            char c;
            scanf("%c", &c);
            scanf("%c", &c);
            printf("%i\n", countCharOccurences(str, n, c));
        }
        else if (x == '3')
        {
            int n;
            scanf("%i", &n);
            char str[n];
            scanf("%s", str);
            char res = findFirstNonRepeatingChar(str, n);
            if (res == -1)
            {
                printf("-1");
            }
            else
            {
                printf("%c", res);
            }
            printf("\n");
        }
        else if (x == '4')
        {

            int n;
            scanf("%i", &n);
            char **strings = (char **)malloc(sizeof(char *) * n);
            for (int i = 0; i < n; ++i)
            {
                *(strings + i) =
                    (char *)malloc(sizeof(char) * 100); // Max size of string is 100
            }
            int cur;
            int min_len = 100;
            for (int i = 0; i < n; ++i)
            {
                scanf("%i %s", &cur, strings[i]);
                if (min_len < cur)
                {
                    min_len = cur;
                }
            }

            char *prefix = findLongestCommonPrefix(strings, n, min_len);
            if (prefix[0] == '\0')
            {
                printf("-1");
            }
            else
            {
                printf("%s", prefix);
            }
            free(prefix);
            printf("\n");
        }
        else if (x == '5')
        {

            int n;
            scanf("%i", &n);
            int arr[n];
            for (int i = 0; i < n; ++i)
            {
                scanf("%i", &arr[i]);
            }

            int *indices = maxMin(arr, n);
            if (max_min_array_size == 0)
            {
                printf("-1");
            }
            else
            {
                for (int i = 0; i < max_min_array_size; ++i)
                {
                    printf("%i ", indices[i]);
                }
            }
            free(indices);
            max_min_array_size = 0;
            printf("\n");
        }
        else if (x == '6')
        {
            int n, m;
            scanf("%i %i", &n, &m);
            char string[n];
            scanf("%s", string);
            char substring[m];
            scanf("%s", substring);

            char *res = removeSubstring(string, n, substring, m);
            if (res[0] == '\0')
            {
                printf("-1");
            }
            else
            {
                printf("%s", res);
            }
            printf("\n");
        }
    }

    return 0;
}
