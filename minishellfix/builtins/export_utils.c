/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:52:01 by aguede            #+#    #+#             */
/*   Updated: 2024/04/10 23:02:26 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

int	ft_strlen_double_pers(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

int	ft_key_check(char *key, t_minishell *minishell)
{
	int			i;
	t_lists_env	envi;

	envi = ft_split_lists_env(minishell->environ);
	i = 0;
	while (envi.p1[i] != NULL)
	{
		if (ft_strcmp(key, envi.p1[i]) == 0)
		{
			ft_free_double_d(envi.p1);
			ft_free_double_d(envi.p2);
			return (1);
		}
		i++;
	}
	ft_free_double_d(envi.p1);
	ft_free_double_d(envi.p2);
	return (0);
}

void	ft_free_lists_env(t_lists_env envi)
{
	ft_free_double_d(envi.p1);
	ft_free_double_d(envi.p2);
}

char	**duplicate_environ(char **minishellenviron, char *key_update,
		char *value)
{
	char	**new_environ;
	int		k;

	k = 0;
	new_environ = ft_calloc(ft_strlen_double_pers(minishellenviron) + 2,
			sizeof(char *));
	while (minishellenviron[k] != NULL)
	{
		new_environ[k] = ft_strdup(minishellenviron[k]);
		k++;
	}
	new_environ[k] = ft_strjoin(key_update, value);
	k++;
	new_environ[k] = NULL;
	k = 0;
	return (new_environ);
}

char	*ft_create_new_key(char *key)
{
	int		j;
	char	*new_key;

	j = 0;
	new_key = ft_calloc(ft_strlen(key) + 2, sizeof(char));
	if (!new_key)
		exit(EXIT_FAILURE);
	while (key[j] != 0)
	{
		new_key[j] = key[j];
		j++;
	}
	new_key[j] = '=';
	j++;
	new_key[j] = 0;
	return (new_key);
}
