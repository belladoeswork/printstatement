/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:16:43 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/14 21:00:08 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

void	ft_execute_child_process(char **split_args, char **environ)
{
	char	*full_path;

	full_path = ft_find_command_path(split_args[0], environ);
	if (full_path == NULL)
	{
		printf("Command '%s' not found\n", split_args[0]);
		exit(NOT_FOUND);
	}
	if (execve(full_path, split_args, environ) == -1)
	{
		perror("execve");
		free(full_path);
		exit(CANT_EXECUTE);
	}
	free(full_path);
}

int	ft_wait_for_child(pid_t pid)
{
	int	tmp_status;

	waitpid(pid, &tmp_status, WUNTRACED);
	while (!WIFEXITED(tmp_status) && !WIFSIGNALED(tmp_status))
		waitpid(pid, &tmp_status, WUNTRACED);
	return (WEXITSTATUS(tmp_status));
}

int	ft_exec_child(char **split_args, char **environ)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == 0)
		ft_execute_child_process(split_args, environ);
	else if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else
	{
		return (ft_wait_for_child(pid));
		g_global.error_num = ft_get_exit_status(status);
	}
	return (1);
}
