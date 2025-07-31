#include <stdio.h>
#include <stdlib.h>

int safe(int *board, int col)
{
    int i = 0;
    while (i < col)
    {
        if (board[i] == board[col]
            || (board[i] - i) == (board[col] - col)
            || (board[i] + i) == (board[col] + col))
            return 0;
        i++;
    }
    return 1;
}

void print_solution(int *board, int n)
{
    int i = 0;
    while (i < n)
    {
        fprintf(stdout, "%i",board[i]);
        if (i != n - 1)
            fprintf(stdout, " ");
        i++;
    }
    fprintf(stdout, "\n");
}

void solve(int *board, int n, int col)
{
    if (col == n)
        return (print_solution(board, n));
    int row  = 0;
    while (row < n)
    {
        board[col] = row;
        if (safe(board, col))
            solve(board, n, col + 1);
        row++;
    }
}

int main (int argc, char **argv)
{
    if (argc != 2)
        return 1;
    int n = atoi(argv[1]);
    int board[n];
    solve(board, n , 0);
}