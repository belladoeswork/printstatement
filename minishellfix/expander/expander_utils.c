/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:36:23 by aguede            #+#    #+#             */
/*   Updated: 2024/03/26 23:31:14 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lumumbash.h"

size_t	ft_strncpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	i = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	while (i < size && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < size)
	{
		dst[i] = '\0';
		i++;
	}
	return (src_len);
}

char	*ft_strdup(const char *s1)
{
	char	*nouveau;
	int		i;
	int		longueur;

	i = 0;
	longueur = ft_strlen(s1);
	nouveau = ft_calloc((longueur + 1), sizeof(char));
	if (!nouveau)
	{
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		nouveau[i] = s1[i];
		i++;
	}
	nouveau[i] = '\0';
	return (nouveau);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	len;
	size_t	j;

	j = 0;
	len = ft_strlen(s);
	if (s[j] == (char)c)
	{
		return ((char *)&s[j]);
	}
	while (s[j] != (char)c && j < len)
	{
		j++;
		if (s[j] == (char)c)
		{
			return ((char *)&s[j]);
		}
	}
	return (NULL);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	number;
	int		i;

	number = n;
	i = ft_my_strlen(number);
	result = ft_calloc((i + 1), sizeof(char));
	if (!result)
		return (NULL);
	result[i--] = '\0';
	if (number == 0)
	{
		result[0] = 48;
	}
	if (number < 0)
	{
		number *= -1;
		result[0] = '-';
	}
	while (number > 0)
	{
		result[i--] = (number % 10) + '0';
		number = number / 10;
	}
	return (result);
}
