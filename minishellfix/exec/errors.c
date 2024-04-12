/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:15:33 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/02 17:26:43 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

int	ft_error_msg(t_error error)
{
	if (error.msg == CMD_NOT_FOUND)
		return (ft_putstr_fd("lumumbash: ", 2), ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": command not found\n", 2), error.no);
	else if (error.msg == NO_SUCH_FILE)
		return (ft_putstr_fd("lumumbash: ", 2), ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": No such file or directory\n", 2), error.no);
	else if (error.msg == PERMISSION_DENIED)
		return (ft_putstr_fd("lumumbash: ", 2), ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": Permission denied\n", 2), error.no);
	else if (error.msg == AMBIGUOUS)
		return (ft_putstr_fd("lumumbash: ", 2), ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": ambiguous redirect\n", 2), error.no);
	else if (error.msg == TOO_MANY_ARGS)
		return (ft_putstr_fd("lumumbash: exit: too many arguments\n", 2),
			error.no);
	else if (error.msg == NUMERIC_REQUIRED)
		return (ft_putstr_fd("lumumbash: exit: ", 2), ft_putstr_fd(error.cause,
				2), ft_putstr_fd(": numeric argument required\n", 2), error.no);
	g_global.error_num = error.no;
	return (0);
}
