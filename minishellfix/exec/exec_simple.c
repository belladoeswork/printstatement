/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:15:54 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/14 16:32:32 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

int	ft_exec_builtin(char **args, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args + 1));
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args + 1));
	if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(args[0], "export"))
		return (ft_export(args, &minishell, i));
	if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, &minishell));
	if (!ft_strcmp(args[0], "exit"))
	{
		ft_exit(args, minishell);
		return (0);
	}
	return (GENERAL);
}

int	ft_exec_builtin_cmd(t_node *node, bool piped, t_minishell *minishell)
{
	int	tmp_status;
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	tmp_status = ft_check_redir(node);
	if (tmp_status != SUCCESS)
	{
		ft_reset_stds(original_stdin, original_stdout, piped);
		return (GENERAL);
	}
	if (ft_strcmp(node->split_args[0], "env") == 0)
		tmp_status = ft_env(minishell->environ);
	else
		tmp_status = ft_exec_builtin(node->split_args, minishell);
	ft_reset_stds(original_stdin, original_stdout, piped);
	return (tmp_status);
}

int	ft_exec_non_builtin_cmd(t_node *node, bool piped, char **environ)
{
	int	tmp_status;
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	tmp_status = ft_check_redir(node);
	if (tmp_status != SUCCESS)
	{
		ft_reset_stds(original_stdin, original_stdout, piped);
		return (GENERAL);
	}
	tmp_status = ft_exec_child(node->split_args, environ);
	ft_reset_stds(original_stdin, original_stdout, piped);
	return (tmp_status);
}

int	ft_exec_simple_cmd(t_node *node, bool piped, t_minishell *minishell)
{
	int		tmp_status;
	char	*temp;

	if (!piped)
		ft_signals(2);
	if (node->split_args && node->split_args[0])
	{
		if (strcmp(node->split_args[0], "<") == 0 || strcmp(node->split_args[0],
				">") == 0)
		{
			temp = node->split_args[0];
			node->split_args[0] = node->split_args[1];
			node->split_args[1] = temp;
		}
		if (ft_is_builtin(node->split_args[0]))
			tmp_status = ft_exec_builtin_cmd(node, piped, minishell);
		else
		{
			tmp_status = ft_exec_non_builtin_cmd(node, piped,
					minishell->environ);
		}
		return (tmp_status);
	}
	else
		return (GENERAL);
}
