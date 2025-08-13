/*Assignment name: rip
Expected files: *.c *.h
Allowed functions: puts, write
--------------------------------------------------------------------------------
Write a program that will take as argument a string containing only parenthesis.
If parenthesis are unbalanced (for example "())") your program shall remove the
minimum number of parenthesis for the expression to be balanced.
By removing we mean replacing by spaces.
You will print all the solutions (can be more than one).
The order of the solutions is not important.
For example this should work:
(For readability reasons the '_' means space and the spaces are for readability only.)
$> ./rip '( ( )' | cat -e
_ ( ) $
( _ ) $
$> ./rip '( ( ( ) ( ) ( ) ) ( ) )' | cat -e
( ( ( ) ( ) ( ) ) ( ) ) $
$> ./rip '( ) ( ) ) ( )' | cat -e
( ) ( ) _ ( ) $
( ) ( _ ) ( ) $
( _ ( ) ) ( ) $
$> ./rip '( ( ) ( ( ) (' | cat -e
( ( ) _ _ ) _ $
( _ ) ( _ ) _ $
( _ ) _ ( ) _ $
_ ( ) ( _ ) _ $
_ ( ) _ ( ) _ $*/
#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *str) {
    int len = 0;
    while (str[len])
        len++;
    return len;
}

void ft_strcpy(char *dest, char *src) {
    int i = 0;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int is_balanced(char *str)
{
    int count = 0;
    int i = 0;
    while (str[i]) {
        if (str[i] == '(')
            count++;
        else if (str[i] == ')')
        {
            count--;
            if (count < 0) 
                return 0;
        }
        i++;
    }
    return count == 0;
}

int min_removals_needed(char *str)
{
    int open = 0, close = 0;
    int i = 0;
    while (str[i])
     {
        if (str[i] == '(')
            open++;
        else if (str[i] == ')')
        {
            if (open > 0)
                open--;
            else
                close++;
        }
        i++;
    }
    return (open + close);
}

void solve(char *buffer, int len , int pos, int removals_left)
{
    char original;
    
    if (pos == len)
    {
        if (removals_left == 0 && is_balanced(buffer))
            return (write(1, buffer, ft_strlen(buffer)), write(1, "\n", 1),(void) 0);
        return;
    }
    solve(buffer,len , pos + 1, removals_left);
    if (removals_left > 0)
    {
        original = buffer[pos];
        buffer[pos] = '_';
        solve(buffer, len,  pos + 1, removals_left - 1);
        buffer[pos] = original;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;
    int len = ft_strlen(argv[1]);
    char buffer[len + 1];
    ft_strcpy(buffer, argv[1]);
    int min_removals = min_removals_needed(buffer);
    solve(buffer, len , 0, min_removals);
    return 0;
}
