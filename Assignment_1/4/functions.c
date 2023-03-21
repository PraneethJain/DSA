#include <stdio.h>
#include <stdlib.h>

typedef struct cell
{
    int col;
    int row;
    int val;
    struct cell *next;
} cell;

cell *read_matrix(int num_elements)
{
    cell *head = (cell *)malloc(sizeof(cell));
    cell *prev = head;
    int x, y, val;
    for (int i = 0; i < num_elements; ++i)
    {
        cell *cur = (cell *)malloc(sizeof(cell));
        scanf("%i %i %i", &x, &y, &val);
        cur->row = x;
        cur->col = y;
        cur->val = val;
        cur->next = NULL;

        prev->next = cur;
        prev = cur;
    }

    return head;
}

int compare(cell *c1, cell *c2)
{
    if (c1->row > c2->row)
    {
        return 1;
    }
    else if (c1->row < c2->row)
    {
        return -1;
    }
    else
    {
        if (c1->col > c2->col)
        {
            return 1;
        }
        else if (c1->col < c2->col)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
}

cell *add_matrix(cell *head1, cell *head2)
{
    cell *res_head = (cell *)malloc(sizeof(cell));
    cell *prev = res_head;
    cell *node1 = head1->next;
    cell *node2 = head2->next;
    while (node1 != NULL && node2 != NULL)
    {
        int x = compare(node1, node2);
        cell *cur = (cell *)malloc(sizeof(cell));
        cur->next = NULL;
        if (x == 1)
        {
            cur->row = node2->row;
            cur->col = node2->col;
            cur->val = node2->val;
            node2 = node2->next;
        }
        else if (x == -1)
        {
            cur->row = node1->row;
            cur->col = node1->col;
            cur->val = node1->val;
            node1 = node1->next;
        }
        else
        {

            cur->row = node1->row;
            cur->col = node1->col;
            cur->val = node1->val + node2->val;
            node1 = node1->next;
            node2 = node2->next;
        }
        if (cur->val != 0)
        {
            prev->next = cur;
            prev = cur;
        }
    }

    if (node1 == NULL)
    {
        prev->next = node2;
    }
    else if (node2 == NULL)
    {
        prev->next = node1;
    }

    return res_head;
}

void print_matrix(cell *head)
{
    cell *cur = head->next;
    while (cur != NULL)
    {
        printf("%i %i %i\n", cur->row, cur->col, cur->val);
        cur = cur->next;
    }
}

int get_length(cell *head)
{
    cell *cur = head->next;
    int i = 0;
    while (cur != NULL)
    {
        ++i;
        cur = cur->next;
    }
    return i;
}

cell *transpose(cell *head)
{
    cell *res = (cell *)malloc(sizeof(cell));
    cell *cur = head->next;
    cell *prev = res;
    while (cur != NULL)
    {
        cell *new = (cell *)malloc(sizeof(cell));
        new->next = NULL;
        new->col = cur->row;
        new->row = cur->col;
        new->val = cur->val;

        prev->next = new;
        prev = new;
        cur = cur->next;
    }
    return res;
}

int main()
{
    char oper[100];
    scanf("%s", oper);
    char x = oper[0];
    if (x == 'A')
    {
        int n, m, k1, k2;
        scanf("%i %i %i %i", &n, &m, &k1, &k2);
        cell *head1 = read_matrix(k1);
        cell *head2 = read_matrix(k2);
        cell *res = add_matrix(head1, head2);
        printf("%i\n", get_length(res));
        print_matrix(res);
    }
    else if (x == 'M')
    {
    }
    else if (x == 'T')
    {
        int n, m, k;
        scanf("%i %i %i", &n, &m, &k);
        cell *head = read_matrix(k);
        cell *res = transpose(head);
        printf("%i\n", k);
        print_matrix(res);
    }
    return 0;
}