/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ft_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:32:54 by aguede            #+#    #+#             */
/*   Updated: 2024/04/07 21:47:21 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"
#include <ctype.h>

int	ft_count_words(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			count++;
		}
		else if (str[i] != '\'')
		{
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			count++;
		}
	}
	return (count);
}

char	*ft_single_quote(char *str, int i)
{
	int		tmp;
	int		j;
	char	*splitted_str;

	tmp = i;
	j = 0;
	i++;
	while (str[i] != '\'')
		i++;
	splitted_str = ft_calloc(i - tmp + 2, sizeof(char));
	splitted_str[j] = '\'';
	j++;
	tmp++;
	while (str[tmp] != '\'')
	{
		splitted_str[j] = str[tmp];
		j++;
		tmp++;
	}
	splitted_str[j++] = '\'';
	splitted_str[j] = '\0';
	return (splitted_str);
}

char	*ft_until_single_quote(char *str, int i)
{
	int		tmp;
	int		j;
	char	*splitted_str;

	tmp = i;
	j = 0;
	while (str[i] != '\'' && str[i] != '\0')
		i++;
	splitted_str = ft_calloc(i - tmp + 1, sizeof(char));
	if (!splitted_str)
		return (NULL);
	while (str[tmp] != '\'' && str[tmp] != '\0')
	{
		splitted_str[j] = str[tmp];
		j++;
		tmp++;
	}
	splitted_str[j] = '\0';
	return (splitted_str);
}

char	**ft_simple_double_d(char *str)
{
	char	**double_d;

	double_d = ft_calloc(2, sizeof(char *));
	double_d[0] = ft_strdup(str);
	double_d[1] = NULL;
	return (double_d);
}

char	**ft_new_ft_split(char *str, char c)
{
	int		i;
	int		j;
	char	**str_return ;

	i = 0;
	j = 0;
	if (str[i] == '\"')
		return (ft_simple_double_d(str));
	str_return = ft_calloc(ft_count_words(str) + 1, sizeof(char *));
	if (!str_return)
		return (NULL);
	while (str[i] != 0)
	{
		if (str[i] == c)
			str_return[j] = ft_single_quote(str, i);
		else
			str_return[j] = ft_until_single_quote(str, i);
		i += ft_strlen(str_return[j]);
		j++;
	}
	str_return[j] = NULL;
	return (str_return);
}
