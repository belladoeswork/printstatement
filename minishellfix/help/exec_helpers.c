/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:30:08 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/03 16:26:31 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

void	ft_reset_stds(int original_stdin, int original_stdout, bool piped)
{
	if (piped)
		return ;
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

bool	ft_is_builtin(char *arg)
{
	if (!arg)
		return (false);
	if (!ft_strcmp(arg, "echo") || !ft_strcmp(arg, "exit") || !ft_strcmp(arg,
			"pwd") || !ft_strcmp(arg, "export") || !ft_strcmp(arg, "unset")
		|| !ft_strcmp(arg, "env") || !ft_strcmp(arg, "cd"))
		return (true);
	return (false);
}
