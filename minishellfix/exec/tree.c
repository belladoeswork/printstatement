/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:19:10 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/14 21:24:45 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

void	ft_heredoc_wrapper(t_redir_node *redir, int p[2], t_minishell *mi)
{
	ft_heredoc(redir, p, mi);
}

static bool	ft_leave_leaf(int p[2], int *pid)
{
	int	status;

	waitpid(*pid, &status, 0);
	close(p[1]);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_global.error_num = 130;
		return (true);
	}
	return (false);
}

static void	ft_init_leaf(t_node *node, t_minishell *minishell)
{
	t_redir_node	*redir;
	int				p[2];
	int				pid;

	redir = node->redir_list;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			pipe(p);
			pid = fork();
			if (pid == 0)
			{
				ft_heredoc_wrapper(redir, p, minishell);
			}
			if (ft_leave_leaf(p, &pid))
				return ;
			redir->here_doc = p[0];
		}
		redir = redir->next;
	}
}

void	ft_init_tree(t_node *node, t_minishell *minishell)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		if (node->left)
			ft_init_tree(node->left, minishell);
		if (node->right)
			ft_init_tree(node->right, minishell);
	}
	else if (node->type != NODE_PIPE)
	{
		ft_init_leaf(node, minishell);
	}
}
