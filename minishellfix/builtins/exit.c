/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:27:00 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/03 15:49:21 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

static int	ft_exittoi(char *s, t_minishell *minishell)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	ft_skip_spaces_and_get_sign(s, &i, &sign);
	ft_check_number_and_exit(s, i, minishell);
	result = ft_calculate_result(s, &i);
	ft_check_result_and_exit(result, s, minishell);
	return ((result * sign) % 256);
}

void	ft_exit(char **args, t_minishell *minishell)
{
	int	exit_s;

	exit_s = g_global.error_num;
	if (args[1])
	{
		if (args[2] && ft_isnumber(args[1]))
		{
			exit_s = ft_error_msg((t_error){GENERAL, TOO_MANY_ARGS, NULL});
			ft_clean_shell(minishell);
			exit(exit_s);
		}
		else
			exit_s = ft_exittoi(args[1], minishell);
	}
	ft_clean_shell(minishell);
	exit(exit_s);
}
