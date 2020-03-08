#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>

#define N 14
bool SOLUTION_EXISTS = false;

bool can_be_placed(int board[N][N], int row, int col);
void print_solution(int board[N][N]);
bool solve_NQueens(int board[N][N], int col);

bool can_be_placed(int board[N][N], int row, int col)
{
    int i, j;

    /* Check this row on left side */
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    /* Check upper diagonal on left side */
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    /* Check lower diagonal on left side */
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

void print_solution(int board[N][N])
{
    static int k = 1;
    printf("Solution #%d-\n", k++);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf(" %d ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

bool solve_NQueens(int board[N][N], int col)
{
    {
        if (col == N)
        {
            //print_solution(board);
            SOLUTION_EXISTS = true;
            return true;
        }
        for (int i = 0; i < N; i++)
        {
            if (can_be_placed(board, i, col))
            {
                #pragma omp task shared(SOLUTION_EXISTS, board)
                {
                    board[i][col] = 1;
                    bool soln_local = solve_NQueens(board, col + 1);

                    #pragma omp critical
                    SOLUTION_EXISTS = soln_local || SOLUTION_EXISTS;
                }
                board[i][col] = 0;
            }
        }
        #pragma omp taskwait
        return SOLUTION_EXISTS;
    }
}

int main()
{
    int board[N][N];
    memset(board, 0, sizeof(board));
    double time1 = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp single
        {
            solve_NQueens(board, 0);
        }
    }
    if (SOLUTION_EXISTS == false)
    {
        printf("No Solution Exits! \n");
    }
    printf("Elapsed time: %0.2lf\n", omp_get_wtime() - time1);
    return 0;
}