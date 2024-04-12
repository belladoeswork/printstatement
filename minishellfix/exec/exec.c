/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:16:27 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/11 11:56:56 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

int	ft_get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static void	child_process_left(t_node *tree, int *pfds, t_minishell *minishell)
{
	close(pfds[0]);
	dup2(pfds[1], STDOUT_FILENO);
	signal(SIGQUIT, sighandler_child_coredumped);
	close(pfds[1]);
	ft_exec_node(tree->left, true, minishell);
	exit(g_global.error_num);
}

static void	child_process_right(t_node *tree, int *pfds, t_minishell *minishell)
{
	signal(SIGINT, sighandler_child);
	close(pfds[1]);
	dup2(pfds[0], STDIN_FILENO);
	ft_exec_node(tree->right, true, minishell);
	close(pfds[0]);
	exit(g_global.error_num);
}

static int	ft_exec_pipeline(t_node *tree, t_minishell *minishell)
{
	int	status;
	int	pfds[2];
	int	pid_left;
	int	pid_right;

	pipe(pfds);
	pid_left = fork();
	if (pid_left == 0)
	{
		signal(SIGINT, sighandler_child);
		child_process_left(tree, pfds, minishell);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		signal(SIGINT, sighandler_child);
		child_process_right(tree, pfds, minishell);
	}
	close(pfds[0]);
	close(pfds[1]);
	signal(SIGINT, sighandler_child);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	return (ft_get_exit_status(status));
}

int	ft_exec_node(t_node *tree, bool piped, t_minishell *minishell)
{
	if (!tree)
		return (1);
	if (tree->type == NODE_PIPE)
		return (ft_exec_pipeline(tree, minishell));
	else
		return (ft_exec_simple_cmd(tree, piped, minishell));
	return (GENERAL);
}
