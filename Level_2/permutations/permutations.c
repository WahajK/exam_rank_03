/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:57:49 by muhakhan          #+#    #+#             */
/*   Updated: 2025/12/16 19:07:43 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i = 0;
	while (*str++)
		i++;
	return (i);
}

int	fact(int len)
{
	if (len == 1)
		return (1);
	return (len * fact(len - 1));
}

void	ft_strcpy(char *src, char *dest)
{
    int i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}


void	make_perms(int length, char *str, char **all_perms, int index, int *perms_index)
{
	if (index == length)
	{
		ft_strcpy(str, all_perms[*perms_index]);
		(*perms_index)++;
		return ;
	}
	for (int i = index; i < length; i++)
	{
		char temp = str[i];
		str[i] = str[index];
		str[index] = temp;
		make_perms(length, str, all_perms, index + 1, perms_index);
		temp = str[i];
		str[i] = str[index];
		str[index] = temp;
	}
}

char *ft_strdup(char *src)
{
	char *ret = malloc (ft_strlen(src) + 1);
	if (!ret)
		return (NULL);
	ft_strcpy(src, ret);
	return (ret);
}

int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (s1[i] - s2[i]);
}


void	sort_perms(int len, char **perms)
{
	char *temp;
	for (int i = 0; i < len; i++)
	{
		for (int j = i; j < len; j++)
		{
			if (ft_strcmp(perms[i], perms[j]) > 0)
			{
				temp = perms[i];
				perms[i] = perms[j];
				perms[j] = temp;
			}
		}
	}
}

int	main(int ac, char *av[])
{
	int	length;
	int	total_perms;
	int	perms_index = 0;
	if (ac != 2)
		return (1);
	char *str = ft_strdup(av[1]);
	length = ft_strlen(av[1]);
	if (length < 1)
		return (0);
	if (length  == 1)
		return (write(STDOUT_FILENO, av[1], length));
	total_perms = fact(length);
	char **all_perms = malloc (sizeof(char *) * total_perms);
	for (int i = 0; i < total_perms; i++)
    	all_perms[i] = calloc(length + 1, sizeof(char));
	make_perms(length, str, all_perms, 0, &perms_index);
	sort_perms(total_perms, all_perms);
	for (int i = 0; i < total_perms; i ++)
	{
		printf("%s\n", all_perms[i]);
		free(all_perms[i]);
	}
	free(all_perms);
	free(str);
	return (0);
}