/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:42:19 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/14 21:23:48 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

bool	ft_is_delimiter(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	return (!*delimiter);
}

void	sighandler_heredoc(int numsig)
{
	if (numsig == SIGINT)
	{
		g_global.error_num = -1;
		exit(130);
	}
}

void	ft_heredoc(t_redir_node *redir, int p[2], t_minishell *minishell)
{
	char	*line;
	char	*quotes;

	(void)minishell;
	signal(SIGINT, sighandler_heredoc);
	quotes = redir->value;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_is_delimiter(redir->value, line))
		{
			ft_putstr_fd("\n", 1);
			break ;
		}
		ft_putstr_fd(line, p[1]);
		ft_putstr_fd("\n", p[1]);
		free(line);
	}
	close(p[1]);
	exit(0);
}
