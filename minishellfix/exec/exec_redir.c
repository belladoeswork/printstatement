/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:15:45 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/03 16:21:34 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

int	ft_out(t_redir_node *redir_list, int *status)
{
	int	fd;

	if (!redir_list->value)
	{
		*status = ft_error_msg((t_error){GENERAL, AMBIGUOUS,
				redir_list->value});
		return (*status);
	}
	fd = open(&redir_list->value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		*status = ft_error_msg(ft_check_write(&redir_list->value[0]));
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}

int	ft_in(t_redir_node *redir_list, int *status)
{
	int	fd;

	if (!redir_list->value)
	{
		*status = ft_error_msg((t_error){GENERAL, AMBIGUOUS,
				redir_list->value});
		return (*status);
	}
	fd = open(redir_list->value, O_RDONLY, 0);
	if (fd == -1)
	{
		*status = ft_error_msg(ft_check_read(redir_list->value));
		return (*status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}

int	ft_append(t_redir_node *redir_list, int *status)
{
	int	fd;

	if (!redir_list->value)
	{
		*status = ft_error_msg((t_error){GENERAL, AMBIGUOUS,
				redir_list->value});
		return (*status);
	}
	fd = open(redir_list->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		*status = ft_error_msg(ft_check_write(redir_list->value));
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}
