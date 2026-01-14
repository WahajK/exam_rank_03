/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nqueens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:11:14 by muhakhan          #+#    #+#             */
/*   Updated: 2026/01/14 19:14:17 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

static void write_number(int n)
{
    char c;

    if (n >= 10)
        write_number(n / 10);
    c = (n % 10) + '0';
    write(1, &c, 1);
}

void print_solution(int *pos, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        write_number(pos[i]);
        if (i + 1 < n)
            write(1, " ", 1);
        i++;
    }
    write(1, "\n", 1);
}

int is_safe(int col, int row, int *pos)
{
    int i;

    i = 0;
    while (i < col)
    {
        if (pos[i] == row)
            return (0);
        if (pos[i] - i == row - col)
            return (0);
        if (pos[i] + i == row + col)
            return (0);
        i++;
    }
    return (1);
}

void backtrack(int col, int n, int *pos)
{
    int row;

    if (col == n)
    {
        print_solution(pos, n);
        return;
    }
    row = 0;
    while (row < n)
    {
        if (is_safe(col, row, pos))
        {
            pos[col] = row;
            backtrack(col + 1, n, pos);
        }
        row++;
    }
}

void solve_n_queens(int n)
{
    int *pos;

    pos = (int *)malloc(sizeof(int) * n);
    if (!pos)
        return;
    backtrack(0, n, pos);
    free(pos);
}

int main(int argc, char **argv)
{
    int n;

    if (argc != 2)
        return (0);
    n = atoi(argv[1]);
    if (n <= 0)
        return (0);
    solve_n_queens(n);
    return (0);
}
