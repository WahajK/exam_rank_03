/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:03:43 by muhakhan          #+#    #+#             */
/*   Updated: 2026/01/14 18:58:23 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print(char *str)
{
	write(STDOUT_FILENO, str, ft_strlen(str));
	write(1, "\n", 1);
}

void	dfs(char *str, char *buf, int i, int open, int rm_open, int rm_close)
{
	//BASE CASE
	if (str[i] == 0)
	{
		if (open == 0 && rm_open == 0 && rm_close == 0)
		{
			buf[i] = 0;
			print(buf);
		}
		return ;
	}
	//Do not include
	if (str[i] == '(' && rm_open > 0)
	{
		buf[i] = ' ';
		dfs(str, buf, i + 1, open, rm_open - 1, rm_close);
	}
	if (str[i] == ')' && rm_close > 0)
	{
		buf[i] = ' ';
		dfs(str, buf, i + 1, open, rm_open, rm_close - 1);
	}
	//Include
	buf[i] = str[i];
	if (str[i] == '(')
		dfs(str, buf, i + 1, open + 1, rm_open, rm_close);
	else if (str[i] == ')')
	{
		if (open > 0)
			dfs(str, buf, i + 1, open - 1, rm_open, rm_close);
	}
	else
		dfs(str, buf, i + 1, open, rm_open, rm_close);
}

void	rip(char *str)
{
	int i = 0;
	int rm_open = 0;
	int	rm_close = 0;
	char buffer[1024];

	while (str[i])
	{
		if (str[i] == '(')
			rm_open++;
		else if (str[i] == ')')
		{
			if (rm_open > 0)
				rm_open--;
			else
				rm_close++;
		}
		i++;
	}
	dfs(str, buffer, 0, 0, rm_open, rm_close);
}

int main(int ac, char *av[])
{
	if (ac == 2)
		rip(av[1]);
	return (0);
}