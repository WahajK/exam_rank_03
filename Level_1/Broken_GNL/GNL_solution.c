/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GNL_solution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:18:52 by muhakhan          #+#    #+#             */
/*   Updated: 2025/12/16 17:20:10 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// You can remove the old code and rewrite your own code, but this is how you fix the broken GNL

# include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	int i = 0;
	while (s && s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return s + i;
	else
		return NULL;
}

/* char *ft_strchr(char *s, int c)
{
	int i = 0;

	while (s && s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	return (NULL);
}

char *ft_strchr(const char *s, int c)
{
	while (s && *s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
	return ((char *)s);	
} */

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int i = 0;
	char *d = (char *)dest;
	const char *s = src;

	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t ret = 0;
	while (s && s[ret])
	{
		ret++;
	}
	return (ret);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return 0;
	ft_memcpy (tmp, *s1, size1);
	ft_memcpy (tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}

void	*ft_memmove (void *dest, const void *src, size_t n)
{
	int	i;
	char *d = (char *)dest;
	char *s = (const char *)src;
	if (d < s)
		return ft_memcpy(dest, src, n);
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			d[i] = s[i];
		}	
	}
	return dest;
}

char	*get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;

	char *tmp = NULL;
	while (!(tmp = ft_strchr(b, '\n'))) {
		if (*b && !str_append_str(&ret, b))
			return NULL;
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
		{
			free(ret);
			b[0] = '\0';
			return NULL;
		}
		if (read_ret == 0)
		{
			b[0] = '\0';
			return (ret);
		}
		b[read_ret] = '\0';
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
	return ret;
}