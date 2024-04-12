/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:26:12 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/12 07:46:11 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

void	handle_quoted_argument(char *arg)
{
	size_t	len;
	char	*p;

	len = ft_strlen(arg);
	if ((arg[0] == '"' || arg[0] == '\'') && arg[0] == arg[len - 1])
	{
		arg[len - 1] = '\0';
		ft_putstr_fd(arg + 1, 1);
	}
	else if ((arg[0] == '"' || arg[0] == '\'') && arg[0] != arg[len - 1])
	{
		ft_putstr_fd("lumumbash: Error: No matching terminating quote", 2);
	}
	else
	{
		p = arg;
		while (*p)
		{
			if (*p != '"' && *p != '\'')
			{
				ft_putchar_fd(*p, 1);
			}
			p++;
		}
	}
}

void	handle_unquoted_argument(char *arg)
{
	if (arg[0] == ' ')
	{
		ft_putchar_fd(' ', 1);
	}
	else
	{
		ft_putstr_fd(arg, 1);
	}
}

// void	ft_handle_arguments(char **args, int start_index)
// {
// 	int	i;

// 	i = start_index;
// 	while (args[i])
// 	{
// 		if (strchr(args[i], '"') || strchr(args[i], '\''))
// 		{
// 			handle_quoted_argument(args[i]);
// 		}
// 		else
// 		{
// 			handle_unquoted_argument(args[i]);
// 		}
// 		if (args[i + 1])
// 		{
// 			ft_putstr_fd(" ", 1);
// 		}
// 		i++;
// 	}
// }

void	ft_handle_arguments(char **args, int start_index)
{
	int	i;
	int	j;
	int	quote;
	i = start_index;
	while (args[i])
	{
		j = 0;
		quote = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\\' && args[i][j + 1])
				j++;
			else if (args[i][j] == '\'' || args[i][j] == '"')
				quote = (quote + 1) % 2;
			if (!quote)
				ft_putchar_fd(args[i][j], 1);
			j++;
		}
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
}

int	ft_echo(char **args)
{
	int	start_index;

	start_index = ft_handle_flags(args);
	ft_handle_arguments(args, start_index);
	if (start_index == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
