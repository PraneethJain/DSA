#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
	int val;
	struct node *left;
	struct node *right;
	int height;
} node;

typedef node *set;

set init_set()
{
	return NULL;
}

set init_node(int val)
{
	set s = (set)malloc(sizeof(node));
	s->val = val;
	s->left = NULL;
	s->right = NULL;
	s->height = 0;

	return s;
}

int max(int x, int y)
{
	return x > y ? x : y;
}

int abs(int x)
{
	return x < 0 ? -x : x;
}

int get_height(set s)
{
	return s == NULL ? -1 : s->height;
}

void update_height(set s)
{
	s->height = 1 + max(get_height(s->left), get_height(s->right));
}

set RR(set s)
{
	set r = s->right;
	s->right = r->left;
	r->left = s;
	update_height(s);
	update_height(r);
	return r;
}

set LL(set s)
{
	set l = s->left;
	s->left = l->right;
	l->right = s;
	update_height(s);
	update_height(l);
	return l;
}

set insert(set s, int val)
{
	if (!s)
		return init_node(val);

	if (val < s->val)
		s->left = insert(s->left, val);
	else
		s->right = insert(s->right, val);

	update_height(s);

	int left_height = get_height(s->left);
	int right_height = get_height(s->right);
	if (abs(left_height - right_height) > 1)
	{
		if (left_height - right_height == 2)
		{
			if (get_height(s->left->left) > get_height(s->left->right))
			{
				s = LL(s);
			}
			else
			{
				s->left = RR(s->left);
				s = LL(s);
			}
		}
		else 
		{
			if (get_height(s->right->right) > get_height(s->right->left))
			{
				s = RR(s);
			}
			else
			{
				s->right = LL(s->right);
				s = RR(s);
			}
		}
	}

	return s;
}

bool find(set s, int val)
{
	if (s == NULL)
		return false;

	if (val == s->val)
		return true;

	if (val > s->val)
		return find(s->right, val);

	return find(s->left, val);
}

void free_set(set s)
{
	if (s == NULL)
		return;

	free_set(s->left);
	free_set(s->right);
	free(s);
}

void pre_order(set s)
{
	if (!s)
		return;

	printf("%i ", s->val);
	pre_order(s->left);
	pre_order(s->right);
}

int main()
{
	set s = init_set();
	size_t n;
	scanf("%zu", &n);
	int cur;
	for (size_t i = 0; i < n; ++i)
	{
		scanf("%i", &cur);
		s = insert(s, cur);
	}

	pre_order(s);
	printf("\n");

	free_set(s);
	return 0;
}
