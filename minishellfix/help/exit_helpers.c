/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:29:12 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/03 16:29:14 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

void	ft_skip_spaces_and_get_sign(char *s, int *i, int *sign)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

void	ft_check_number_and_exit(char *s, int i, t_minishell *minishell)
{
	int	exit_s;

	if (!ft_isnumber(s + i))
	{
		exit_s = ft_error_msg((t_error){ERROR_EXEC_255, NUMERIC_REQUIRED, s});
		ft_clean_shell(minishell);
		exit(exit_s);
	}
}

unsigned long long	ft_calculate_result(char *s, int *i)
{
	unsigned long long	result;

	result = 0;
	while (s[*i])
	{
		result = (result * 10) + (s[*i] - '0');
		(*i)++;
	}
	return (result);
}

void	ft_check_result_and_exit(unsigned long long result, char *s,
		t_minishell *minishell)
{
	int	exit_s;

	if (result > LONG_MAX)
	{
		exit_s = ft_error_msg((t_error){ERROR_EXEC_255, NUMERIC_REQUIRED, s});
		ft_clean_shell(minishell);
		exit(exit_s);
	}
}
