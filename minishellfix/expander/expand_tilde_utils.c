/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:57:12 by aguede            #+#    #+#             */
/*   Updated: 2024/04/03 16:29:55 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

int	count_tildes(char *str)
{
	int		count;
	int		i;
	char	*strdup;

	count = 0;
	strdup = ft_strdup(str);
	i = 0;
	if (strdup[i] == '~' && ((ft_isspace(strdup[i + 1])) || strdup[i + 1] == ':'
			|| strdup[i + 1] == '/' || strdup[i + 1] == '\0'))
	{
		count++;
		i++;
	}
	while (strdup[i] != '\0')
	{
		if (strdup[i] == '~' && ((ft_isspace(strdup[i]) || strdup[i] == ':'
					|| strdup[i] == '/' || strdup[i] == '\0'))
			&& ft_isspace(strdup[i]))
			count++;
		i++;
	}
	return (free(strdup), count);
}

int	check_char1(char *str)
{
	if (*str == '~' && ((ft_isspace(*(str + 1)) || *(str + 1) == ':' || *(str
					+ 1) == '/' || *(str + 1) == '\0')))
		return (1);
	else
		return (0);
}

int	check_next_chars(char *str)
{
	if (*str == '~' && ((ft_isspace(*(str + 1)) || *(str + 1) == ':' || *(str
					+ 1) == '/' || *(str + 1) == '\0')) && (ft_isspace(*(str
					- 1))))
		return (1);
	else
		return (0);
}
