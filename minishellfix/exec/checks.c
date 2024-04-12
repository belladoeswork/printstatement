/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:15:08 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/03 16:48:10 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

t_error	ft_check_read(char *file)
{
	if (!*file)
		return ((t_error){GENERAL, NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK) == -1)
			return ((t_error){GENERAL, PERMISSION_DENIED, file});
		return ((t_error){SUCCESS, 42, NULL});
	}
	return ((t_error){NOT_FOUND, NO_SUCH_FILE, file});
}

t_error	ft_check_write(char *file)
{
	if (!*file)
		return ((t_error){GENERAL, NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return ((t_error){GENERAL, PERMISSION_DENIED, file});
		return ((t_error){SUCCESS, 42, NULL});
	}
	return ((t_error){NOT_FOUND, NO_SUCH_FILE, file});
}
