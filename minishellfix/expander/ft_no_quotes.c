/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:57:20 by aguede            #+#    #+#             */
/*   Updated: 2024/04/05 15:37:45 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

int	count_quotes(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && str[i - 1] != '\"')
			count++;
		i++;
	}
	return (count);
}

char	*ft_no_quotes(char *str, int num_quotes)
{
	char	*str_no_quotes;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str_no_quotes = ft_calloc(ft_strlen(str) - num_quotes + 1, sizeof(char));
	while (str[i] != '\0')
	{
		while (str[i] == '\"' && str[i - 1] != '\"')
			i++;
		if (str[i] != '\0')
		{
			str_no_quotes[j] = str[i];
			i++;
			j++;
		}
	}
	str_no_quotes[j] = '\0';
	return (str_no_quotes);
}
