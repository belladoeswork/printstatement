/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:16:43 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/12 13:51:06 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

void	ft_execute_child_process(char **split_args, char **environ)
{
	char	*full_path;

	printf("pid was == o and we execute child process and this is split_args[0] %s\n", split_args[0]);
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
	printf("no error in execve execute child");
	free(full_path);
}

int	ft_wait_for_child(pid_t pid)
{
	int	tmp_status;

	waitpid(pid, &tmp_status, WUNTRACED);
	while (!WIFEXITED(tmp_status) && !WIFSIGNALED(tmp_status))
		waitpid(pid, &tmp_status, WUNTRACED);
	printf("the return value of ft_wait_for_child : %d\n", WEXITSTATUS(tmp_status));
	return (WEXITSTATUS(tmp_status));
}

int	ft_exec_child(char **split_args, char **environ)
{
	int		status;
	pid_t	pid;

	printf("in exec child\n");
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
		printf("in ft exec child else condition\n");
		return (ft_wait_for_child(pid));
		g_global.error_num = ft_get_exit_status(status);
		printf("in ft_exec_child else cond g_global.error_num : %d\n", g_global.error_num);
	}
	return (1);
}
