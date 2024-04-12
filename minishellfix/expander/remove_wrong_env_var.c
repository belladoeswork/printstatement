/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_wrong_env_var.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:51:52 by aguede            #+#    #+#             */
/*   Updated: 2024/04/07 23:57:00 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lumumbash.h"

int	ft_non_char_or_digit(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (0);
	else
		return (1);
}

char	**ft_fill_the_double_d(int n, char **before_equal, char **str)
{
	int		i;
	int		k;
	char	**removed_wrong_env_var;

	removed_wrong_env_var = ft_calloc(n + 1, sizeof(char *));
	if (!removed_wrong_env_var)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i] != NULL)
	{
		if (!(str[i][0] == '$' && !ft_check_if_expand(str[i], before_equal))
			|| (str[i][0] == '$' && ft_non_char_or_digit(str[i][1])))
		{
			removed_wrong_env_var[k] = ft_strdup(str[i]);
			k++;
		}
		i++;
	}
	removed_wrong_env_var[k] = NULL;
	return (removed_wrong_env_var);
}

char	**ft_remove_wrong_env_var(char **str, char **before_equal)
{
	int		i;
	int		j;
	int		tmp;
	char	**removed_wrong_env_var;

	i = 0;
	j = 0;
	while (str[i] != NULL)
	{
		if ((str[i][0] == '$' && !ft_check_if_expand(str[i], before_equal))
			|| (str[i][0] == '$' && !ft_non_char_or_digit(str[i][1])))
			j++;
		i++;
	}
	tmp = i + 1;
	removed_wrong_env_var = ft_fill_the_double_d(tmp, before_equal, str);
	ft_free_double_d(str);
	return (removed_wrong_env_var);
}
