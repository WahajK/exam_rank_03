/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_gnl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:53:33 by muhakhan          #+#    #+#             */
/*   Updated: 2025/11/26 19:36:13 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char *ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

char *ft_strncpy(char *src, char *dest, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char *ft_strndup(char *src, int n)
{
	char *ptr;

	ptr = malloc(n + 1);
	if (!ptr)
		return (NULL);
	ft_strncpy(src, ptr, n);
	return (ptr);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strjoin(char *str1, char *str2)
{
	char *ptr;

	ptr = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!ptr)
		return (NULL);
	ft_strncpy(str1, ptr, ft_strlen(str1));
	ft_strncpy(str2, ptr + ft_strlen(str1), ft_strlen(str2));
	return (ptr);
}

char *ft_substr(char *s, int start, int len)
{
	char	*ptr;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
		return (NULL);
	else
	{
		s += start;
		if (len > ft_strlen(s))
			len = ft_strlen(s);
		ptr = ft_strndup(s, len);
	}
	return (ptr);
}

void	set_line(int fd, char *buffer, char **line)
{
	int		i;
	char	*temp;
	if (!*line || !ft_strchr(*line, '\n'))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i <= 0)
			return (free(buffer));
		while (i > 0)
		{
			buffer[i] = 0;
			if (!*line)
				*line = ft_substr(buffer, 0, i);
			else
			{
				temp = *line;
				*line = ft_strjoin(*line, buffer);
				free(temp);
			}
			if (!ft_strchr(*line, '\n'))
				break ;
			i = read(fd, buffer, BUFFER_SIZE);
		}
	}
	free(buffer);
}

char *get_line(char **line)
{
	int		i;
	int		j;
	char	*temp;
	char	*ret;

	if (!*line)
		return (NULL);
	if (!ft_strchr(*line, '\n'))
	{
		ret = ft_substr(*line, 0, ft_strlen(*line));
		free(*line);
		*line = 0;
		return (ret);
	}
	i = ft_strlen(*line);
	j = ft_strlen(ft_strchr(*line, '\n'));
	ret = ft_substr(*line, 0, i - j + 1);
	temp = *line;
	*line = ft_substr(ft_strchr(*line, '\n'), 1, j - 1);
	free (temp);
	return (ret);
}

char *get_next_line(int fd)
{
	char *buffer;
	static char *line;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (fd == -1 || read(fd, buffer, 0) == -1 || BUFFER_SIZE < 1)
		return (NULL);
	set_line(fd, buffer, &line);
	return (get_line(&line));
}

#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int     fd;
    char    *line;

    if (argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return (1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}