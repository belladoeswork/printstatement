/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:26:12 by aguede            #+#    #+#             */
/*   Updated: 2024/04/14 20:36:54 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*ft_search(char **p1, char **p2, char *str)
{
	int	k;

	k = 0;
	while (p1[k] != NULL)
	{
		if (ft_strncmp(str, p1[k], ft_strlen(p1[k])) == 0
			&& (ft_strlen(p1[k]) == (ft_strlen(str))))
		{
			break ;
		}
		k++;
	}
	if (p1[k] == NULL)
		return (NULL);
	return (ft_strdup(p2[k]));
}

// int	count_tildes(char *str)
// {
// 	int		count;
// 	int		j;
// 	int		i;
// 	char	*strdup;

// 	count = 0;
// 	strdup = ft_strdup(str);
// 	j = 0;
// 	i = 0;
// 	if (strdup[i] == '~' && ((ft_isspace(strdup[i + 1])) || strdup[i + 1] == ':'
// 			|| strdup[i + 1] == '/' || strdup[i + 1] == '\0'))
// 	{
// 		count++;
// 		i++;
// 		;
// 	}
// 	while (strdup[i] != '\0')
// 	{
// 		if (strdup[i] == '~' && ((ft_isspace(strdup[i]) || strdup[i] == ':'
// 					|| strdup[i] == '/' || strdup[i] == '\0'))
// 			&& ft_isspace(strdup[i]))
// 			count++;
// 		i++;
// 	}
// 	return (free(strdup), count);
// }

// int	check_char1(char *str)
// {
// 	if (*str == '~' && ((ft_isspace(*(str + 1)) || *(str + 1) == ':' || *(str
// 					+ 1) == '/' || *(str + 1) == '\0')))
// 		return (1);
// 	else
// 		return (0);
// }

// int	check_next_chars(char *str)
// {
// 	if (*str == '~' && ((ft_isspace(*(str + 1)) || *(str + 1) == ':' || *(str
// 					+ 1) == '/' || *(str + 1) == '\0')) && (ft_isspace(*(str
// 					- 1))))
// 		return (1);
// 	else
// 		return (0);
// }

char	*ft_replace(char *str, char *str_tilde, char *str_expanded)
{
	int	l;
	int	k;

	l = 0;
	k = 0;
	if (check_char1(str))
	{
		while (str_tilde[k] != '\0')
			str_expanded[l++] = str_tilde[k++];
		k = 0;
		str++;
	}
	while (*str != '\0')
	{
		if (check_next_chars(str))
		{
			k = 0;
			while (str_tilde[k] != '\0')
				str_expanded[l++] = str_tilde[k++];
			str++;
		}
		str_expanded[l++] = *str++;
	}
	return (str_expanded);
}

char	*expand_tilde(char *str, char **p1, char **p2)
{
	char	*str_tilde;
	int		expanded_len;
	char	*str_expanded;

	str_tilde = ft_search(p1, p2, "HOME");
	if (!str_tilde)
		return (str);
	expanded_len = (ft_strlen(str_tilde) * count_tildes(str)) + ft_strlen(str)
		- count_tildes(str) + 1;
	str_expanded = ft_calloc(expanded_len, sizeof(char));
	str_expanded = ft_replace(str, str_tilde, str_expanded);
	return (free(str_tilde), str_expanded);
}

// char	*ft_no_quotes(char *str)
// {
// 	int		i;
// 	int		n;
// 	char	*strdup;

// 	i = 0;
// 	n = 0;
// 	while (str[i] != 0)
// 	{
// 		if (str[i] == '\"')
// 			n++;
// 		i++;
// 	}
// 	if (n >= 1)
// 	{
// 		strdup = ft_calloc(ft_strlen(str) - n + 1, sizeof(char));
// 		i = 0;
// 		n = 0;
// 		while (str[i] != 0)
// 		{
// 			if (str[i] == '\"')
// 				i++;
// 			if (str[i] != 0)
// 			{
// 				strdup[n] = str[i];
// 				n++;
// 				i++;
// 			}
// 		}
// 		strdup[n] = '\0';
// 		return (strdup);
// 	}
// 	else
// 		return (str);
// }

// int	count_quotes(char *str)
// {
// 	int	count;
// 	int	i;

// 	count = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\"')
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// char	*ft_no_quotes(char *str, int num_quotes)
// {
// 	char	*str_no_quotes;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	str_no_quotes = ft_calloc(ft_strlen(str) - num_quotes + 1, sizeof(char));
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\"')
// 			i++;
// 		if (str[i] != '\0')
// 		{
// 			str_no_quotes[j] = str[i];
// 			i++;
// 			j++;
// 		}
// 	}
// 	str_no_quotes[j] = '\0';
// 	return (str_no_quotes);
// }

// char	*ft_expand_tilde(char *str, char **p1, char **p2)
// {
// 	int		n;
// 	char	*str_no_quotes;

// 	str_no_quotes = ft_no_quotes(str, count_quotes(str));
// 	n = count_tildes(str_no_quotes);
// 	if (n == 0)
// 		return (str_no_quotes);
// 	else
// 		return (expand_tilde(str_no_quotes, p1, p2));
// }

char	*ft_expand_tilde(char *str, char **p1, char **p2)
{
	int	n;

	n = count_tildes(str);
	if (n == 0)
		return (str);
	else
		return (expand_tilde(str, p1, p2));
}
