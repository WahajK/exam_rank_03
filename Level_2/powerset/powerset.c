/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:26:31 by muhakhan          #+#    #+#             */
/*   Updated: 2025/12/16 19:26:49 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void print_subset(int *subset, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (i > 0)
            printf(" ");
        printf("%d", subset[i]);
    }
    printf("\n");
}

void dfs(int *arr, int n, int len, int index, int current_sum, int *subset, int subset_len)
{
    if (index == len)
    {
        if (current_sum == n)
            print_subset(subset, subset_len);
        return;
    }
    dfs(arr, n, len, index + 1, current_sum, subset, subset_len);
    subset[subset_len] = arr[index];
    dfs(arr, n, len, index + 1, current_sum + arr[index], subset, subset_len + 1);
}

int main(int ac, char **av)
{
    int n;
    int *arr;
    int *subset;
    int len;

    if (ac < 2)
        return (0);

    n = atoi(av[1]);
    len = ac - 2;

    arr = malloc(sizeof(int) * len);
    subset = malloc(sizeof(int) * len);
    if (!arr || !subset)
        return (1);

    for (int i = 0; i < len; i++)
        arr[i] = atoi(av[i + 2]);

    dfs(arr, n, len, 0, 0, subset, 0);

    free(arr);
    free(subset);
    return (0);
}
