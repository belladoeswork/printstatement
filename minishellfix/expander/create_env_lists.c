/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_lists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:45:45 by aguede            #+#    #+#             */
/*   Updated: 2024/03/26 16:26:33 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lumumbash.h"
#include <ctype.h>

void	ft_create_lists(char ***list_before_equal, char ***list_after_equal,
		char **env)
{
	int		i;
	char	*equal_sign;
	size_t	len;

	i = 0;
	while (env[i] != NULL)
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign != NULL)
		{
			len = equal_sign - env[i];
			(*list_before_equal)[i] = malloc((len + 1) * sizeof(char));
			if ((*list_before_equal)[i] == NULL)
				exit(EXIT_FAILURE);
			ft_strncpy((*list_before_equal)[i], env[i], len);
			(*list_before_equal)[i][len] = '\0';
			(*list_after_equal)[i] = ft_strdup(equal_sign + 1);
			if ((*list_after_equal)[i] == NULL)
				exit(EXIT_FAILURE);
		}
		i++;
	}
	(*list_before_equal)[i] = NULL;
	(*list_after_equal)[i] = NULL;
}

t_lists_env	ft_split_lists_env(char **env)
{
	t_lists_env	list_to_give_back;
	char		**list_before_equal;
	char		**list_after_equal;
	int			count;

	count = 0;
	while (env[count] != NULL)
		count++;
	list_before_equal = ft_calloc(count + 1, sizeof(char *));
	list_after_equal = ft_calloc(count + 1, sizeof(char *));
	if (list_before_equal == NULL || list_after_equal == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	ft_create_lists(&list_before_equal, &list_after_equal, env);
	list_to_give_back.p1 = list_before_equal;
	list_to_give_back.p2 = list_after_equal;
	return (list_to_give_back);
}
