/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exphelp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:58:38 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/03 16:27:07 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

char	*ft_extract_key(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_collector(ft_substr(str, 0, i), false));
		i++;
	}
	return (ft_strdup(str));
}

bool	ft_env_entry_exists(char *key, t_minishell *minishell)
{
	t_env	*envlst;

	envlst = minishell->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
		{
			printf("");
			return (true);
		}
		envlst = envlst->next;
	}
	return (false);
}

int	ft_keycheck(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_' && *str != '$')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_alphanum(str[i]) && str[i] != '_' && str[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

void	ft_envlst_back(t_env *new, t_minishell *minishell)
{
	t_env	*curr;

	if (!minishell->envlst)
	{
		minishell->envlst = new;
		return ;
	}
	curr = minishell->envlst;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}

char	*ft_extract_val(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (ft_collector(ft_substr(str, i, ft_strlen(str) - i), false));
		}
		i++;
	}
	return (NULL);
}
