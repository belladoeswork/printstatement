/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 00:33:43 by aguede            #+#    #+#             */
/*   Updated: 2024/04/03 16:31:32 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

char	*ft_fill_the_word(char *str, int end, char *lst)
{
	int	i;
	int	tmp;

	tmp = end;
	while (end > 0)
	{
		str--;
		end--;
	}
	i = 0;
	while (i < tmp)
	{
		lst[i] = str[i];
		i++;
	}
	(void)str;
	lst[i] = 0;
	return (lst);
}

char	**ft_allocate_memory(char *str, char c, t_token *tokens)
{
	char	**lst;
	char	*tmp;

	tmp = ft_strdup(str);
	lst = ft_calloc((ft_countword(str, c, tmp, tokens) + 1), sizeof(char *));
	if (!str || !lst)
		return (NULL);
	return (lst);
}

int	find_next_word_length(char *str, char c, t_token *tokens)
{
	int	reset;
	int	flag;

	reset = 0;
	flag = 0;
	while ((reset > 0 && *str != c) || reset == 0)
	{
		if (*str == c)
			flag = 1;
		if ((flag == 1 && (ft_isspace(*str) || equal(str, tokens)))
			|| (*str == '\0'))
			break ;
		else if (flag == 1 && ft_digit_or_q(str, c))
		{
			reset++;
			str++;
			break ;
		}
		str++;
		reset++;
	}
	return (reset);
}

int	ft_digit_or_q(char *str, char c)
{
	char	*tmp;

	tmp = str;
	if ((ft_isdigit(*tmp) || *tmp == '?') && *(tmp - 1) == c)
		return (1);
	else
		return (0);
}

int	ft_strlen_double(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		i++;
	}
	return (i);
}
