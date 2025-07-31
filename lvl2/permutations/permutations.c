// Assignment name : permutations

// Expected files : *.c *.h
// Allowed functions : puts, malloc, calloc, realloc, free, write
// ---------------------------------------------------------------

// Write a program that will print all the permutations of a string given as argument.

// The solutions must be given in alphabetical order.

// We will not try your program with strings containing duplicates (eg: 'abccd')

// For example this should work:
// $> ./permutations a | cat -e
// a$
// $> ./permutations ab | cat -e
// ab$
// ba$
// $> ./permutations abc | cat -e
// abc$
// acb$
// bac$
// bca$
// cab$
// cba$
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

//copy swap print sort
int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

char *ft_strdup(char *s1)
{
    int len = ft_strlen(s1);
    char *s2 = malloc (len + 1);
    if (!s2)
        return s2;
    int i = 0;
    while (s1[i])
    {
        s2[i] = s1[i];
        i++;
    }
    s2[i] = '\0';
    return s2;
}
void swap(char *a, char *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void sort_str(char *str, int len)
{
    int i, j;
    for (i = 0; i < len - 1; i++)
    {
        for (j = 0; j < len - i - 1; j++)
        {
            if (str[j] > str[j + 1])
                swap(&str[j], &str[j + 1]);
        }
    }
}
void sort(char *str)
{
    int i;
    int flag = 1;
    while (flag)
    {
        flag = 0;
        i = 0; 
        while (str[i +1])
        {
            if (str[i] > str[i + 1])
            {
                swap(&str[i], &str[i + 1]);
                flag = 1;
            }
            i++;
        }
    }
}


void print_solution(char *str)
{
    while (*str)
        write(1,&*str++,1);
    write(1,"\n",1);
}

void permutate_lex(char *str, int len, char *curr, int depth, int *used)
{
    if (depth == len)
        return print_solution(curr);
    int i = 0;
    while (i < len)
    {
        if (used[i])
        {
            i++;
            continue ;
        }
        used[i] = 1;
        curr[depth] = str[i];
        permutate_lex(str, len, curr, depth + 1, used);
        used[i] = 0;
        i++;
    }
}

int main (int argc, char **argv)
{
    if (argc != 2)
        return 1;
    char *copy = ft_strdup(argv[1]);
    int len = ft_strlen(copy);
    if (!copy)
        return 1;
    sort(copy);
    char *curr = malloc(len + 1);
    int *used = calloc(len, sizeof(int));
    if (!curr || !used)
        return (free(copy), free(curr), free(used), 1);
    permutate_lex(copy, len, curr, 0, used);
    return (free(copy), free(curr), free(used), 0);
}

/**/