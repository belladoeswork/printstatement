/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:11:52 by aguede            #+#    #+#             */
/*   Updated: 2024/04/08 00:02:35 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

static void	ft_unset_helper(t_minishell *minishell, char *key)
{
	int			i;
	int			j;
	char		**str;
	t_lists_env	envi;

	i = 0;
	j = 0;
	str = ft_calloc(ft_strlen_double_pers(minishell->environ) + 1,
			sizeof(char *));
	envi = ft_split_lists_env(minishell->environ);
	while (minishell->environ[j] != NULL)
	{
		if (ft_strcmp(key, envi.p1[j]) == 0)
			j++;
		if (minishell->environ[j] != NULL)
			str[i] = ft_strdup(minishell->environ[j]);
		else
			break ;
		i++;
		j++;
	}
	str[i] = NULL;
	ft_free_double_d(minishell->environ);
	minishell->environ = str;
	ft_free_lists_env(envi);
}

int	ft_unset(char **args, t_minishell **minishell)
{
	int		i;
	bool	err;

	i = 1;
	if (!args[1])
		return (0);
	err = false;
	while (args[i])
	{
		if (!ft_keycheck(args[i]))
		{
			ft_putstr_fd("lumumbash: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			err = true;
		}
		else
			ft_unset_helper(*minishell, ft_collector(ft_extract_key(args[i]),
					false));
		i++;
	}
	return (err);
}
