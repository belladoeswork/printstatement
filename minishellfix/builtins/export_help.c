/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:44:45 by aguede            #+#    #+#             */
/*   Updated: 2024/04/05 19:38:41 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

void	skip_spaces(char *str, char **out, int last_space)
{
	while (*str)
	{
		if (isspace(*str))
		{
			if (!last_space)
			{
				*(*out)++ = ' ';
				last_space = 1;
			}
			str++;
		}
		else
		{
			*(*out)++ = *str++;
			last_space = 0;
		}
	}
	**out = '\0';
}

char	*ft_no_space(char *str)
{
	size_t	len;
	char	*new_str;
	char	*out;
	int		last_space;

	len = strlen(str);
	new_str = malloc(len + 1);
	if (new_str == NULL)
		return (NULL);
	out = new_str;
	last_space = 0;
	while (*str && isspace(*str))
	{
		str++;
		last_space = 0;
	}
	skip_spaces(str, &out, last_space);
	return (new_str);
}

int	ft_count_colons(char *path)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (path[i] != '\0')
	{
		if (path[i] == ':')
			count++;
		i++;
	}
	return (count);
}

void	ft_print_export(t_minishell *minishell)
{
	char	**str_dup;
	char	*str;
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (minishell->environ[i] != NULL)
		i++;
	str_dup = ft_calloc(i + 12 + 1, sizeof(char *));
	while (minishell->environ[n] != NULL)
	{
		str = ft_strdup(minishell->environ[n]);
		str_dup[n] = ft_strjoin("declare -x ", str);
		n++;
		free(str);
	}
	str_dup[n] = NULL;
	ft_print_double_d_f(str_dup);
	ft_free_double_d(str_dup);
}
