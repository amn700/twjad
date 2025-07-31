#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_context {
	int  *nums;       // array of input integers
	int   size;       // size of nums[]
	int  *subset;     // current subset being built
	int   depth;      // how many numbers are in subset
	int   sum;        // current sum of subset
	int   target;     // target sum
} t_context;

void back_tracking(t_context context, int index)
{
    if (index == context.size)
	{
		if (context.sum == context.target)
		{
			for (int i = 0; i < context.depth; i++)
				printf("%d ", context.subset[i]);
			printf("\n");
		}
		return;
	}

    context.subset[context.depth] = context.nums[index];
    context.sum += context.nums[index];
    context.depth += 1;
    back_tracking(context, index + 1);
	context.sum -= context.nums[index];
	context.depth -= 1;
    back_tracking(context, index + 1);

}

int main (int argc, char **argv)
{
    if (argc < 2)
        return 1;
    t_context context;
    context.size = argc - 2;
    context.nums = malloc (context.size * sizeof (int));
    if (!context.nums)
        return 1;
	context.subset = malloc(context.size * sizeof(int));
	if (!context.subset)
		return 1;
    context.depth = 0;
    context.sum = 0;
    context.target = atoi(argv[1]);
    int i = 0;
    while (i < argc - 2)
    {
        context.nums[i] = atoi(argv[2 + i]);
        i++;
    }
    back_tracking(context, 0);
}


/*Assignment name : powerset
Expected files : *.c *.h
Allowed functions : atoi, printf, malloc, calloc, realloc, free.
---------------------------------------------------------------

Write a program that will take as argument an integer n follow by a set of integers,
your program should display all the subsets of whose sum of elements is n.

In case of a malloc error your program will exit with the code 1.
We will not test invalid test(for example '1 1 2')
hint: the empty set is a subset of anyset.


For example this should work:
$> ./powerset 3 1 0 2 4 5 3 | cat -e
3$
0 3$
1 2$
1 0 2$
$> ./powerset 12 5 2 1 8 4 3 7 11 | cat -e
8 4$
1 11$
1 4 7$
2 3 7$
5 4 3$
5 7$
5 2 1 4$
$> ./powerset 7 3 8 2| cat -e
$
$> ./powerset 0 1 -1| cat -e
1 -1$

The order of lines is not important, but the order of the element in a subset is.
You must not have any duplicates (for example 2 1, 1 2)
$> ./powerset 5 1 2 3 4 5| cat -e
valid:
1 4$
2 3$
5$

or:
2 3$
5$
1 4$
not valid:
4 1$
3 2$
5$*/
