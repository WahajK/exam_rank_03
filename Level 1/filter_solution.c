/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:25:23 by muhakhan          #+#    #+#             */
/*   Updated: 2025/12/01 18:31:50 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 10001

int ft_strncmp(char *s1, char *s2, int n)
{
    int i = 0;
    while (i < n && s1[i] == s2[i])
        i++;
    if (i == n)
        return 1;
    else 
        return 0;
}

int main(int argc, char *argv[])
{
	char	*input;
	char	ch;
	size_t	bytes_read = 0;
	int		i = 0;

	if (argc != 2 || argv[1] == NULL || strlen(argv[1]) == 0)
		return (1);
	input = malloc(BUFFER_SIZE);
	if (!input)
		return (printf("Error: "), perror(""), 1);
	while((bytes_read = read(STDIN_FILENO, &ch, 1)) > 0)
	{
		if (i >= BUFFER_SIZE - 1)
			break ;
		input[i++] = ch;
	}
	if (bytes_read == -1)
		return (printf("Error: "), perror(""), free(input), 1);
	input[i] = 0;
	int	j = 0;
	while (input[j] != 0)
	{
		if (j + strlen(argv[1]) <= i && ft_strncmp(&input[j], argv[1], strlen(argv[1])))
		{
			for (int k = 0; k < strlen(argv[1]); k++)
				write(STDOUT_FILENO, "*", 1);
			j += strlen(argv[1]);
		}
		else
		{
			write(STDOUT_FILENO, &input[j], 1);
			j++;
		}
	}
	free(input);
	return (0);
}