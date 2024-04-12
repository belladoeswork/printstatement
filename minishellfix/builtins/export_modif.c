/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_modif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:52:24 by aguede            #+#    #+#             */
/*   Updated: 2024/04/03 18:16:16 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

char	*ft_update(char *key_update, char *value)
{
	char	*p1;
	char	*p2;
	char	*updated;

	p1 = ft_strdup(key_update);
	p2 = ft_strdup(value);
	updated = ft_strjoin(p1, p2);
	free(p1);
	free(p2);
	return (updated);
}

char	**ft_modify_env_var(char **minishellenviron, char *key, char *value)
{
	char		*key_update;
	char		**str;
	char		*updated;
	t_lists_env	list_env;

	list_env = ft_split_lists_env(minishellenviron);
	key_update = ft_create_new_key(key);
	updated = ft_update(key_update, value);
	str = populate_str(minishellenviron, key, updated, list_env);
	free(key_update);
	free(updated);
	return (str);
}

int	ft_q(char *val, char c)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (val[i] != 0)
	{
		if (val[i] == c)
			n++;
		i++;
	}
	return (n);
}

char	*ft_remove_ft_q(char *val)
{
	int		i;
	int		j;
	int		n;
	char	*str;

	i = 0;
	n = ft_q(val, '\"') + ft_q(val, '\'');
	j = 0;
	if (n >= 2 && (ft_q(val, '\"') % 2 == 0) && (ft_q(val, '\'') % 2 == 0))
		str = ft_calloc(ft_strlen(val) - n + 2, sizeof(char));
	else if (n != 0 && ((ft_q(val, '\"') % 2 != 0) || (ft_q(val, '\'')
				% 2 != 0)))
		exit(EXIT_FAILURE);
	else
		return (str = ft_strdup(val));
	while (val[i] != '\0')
	{
		if (val[i] == '\"' || val[i] == '\'')
			i++;
		str[j] = val[i];
		j++;
		if (val[i])
			i++;
	}
	return (str[j] = '\0', str);
}
