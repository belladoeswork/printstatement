/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:51:19 by aguede            #+#    #+#             */
/*   Updated: 2024/04/07 21:42:33 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lumumbash.h"

void	ft_free_tmp(char *str, int c, int check)
{
	int	i;

	i = 0;
	if (check == 1 && str)
	{
		while (i < c)
		{
			str--;
			i++;
		}
	}
	free(str);
}

// int	ft_dollar(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '$')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_digit_or_q(char *str, char c)
// {
// 	char	*tmp;

// 	tmp = str;
// 	if ((ft_isdigit(*tmp) || *tmp == '?') && *(tmp - 1) == c)
// 		return (1);
// 	else
// 		return (0);
// }

// int	ft_strlen_double(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != NULL)
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// int	equal(char *tmp, t_token *tokens_original)
// {
// 	t_token	*tokens;

// 	tokens = tokens_original;
// 	if (*tmp == '\"')
// 		return (1);
// 	if (*tmp != '=')
// 		return (0);
// 	while (tokens != NULL)
// 	{
// 		if (ft_strcmp(tokens->value, "export") == 0)
// 			return (1);
// 		tokens = tokens->prev;
// 	}
// 	return (0);
// }

int	ft_countword(char *str, char c, char *tmp, t_token *tokens)
{
	int	i;
	int	n;
	int	flag;

	i = 1;
	n = 0;
	flag = 0;
	if (!ft_dollar(str))
		return (ft_free_tmp(tmp, ft_strlen(str), 0), 1);
	while (*tmp)
	{
		if (*tmp == c)
			flag = 1;
		if ((*tmp == c && n == 1) || (flag == 1 && ((ft_isspace(*tmp)
						|| ft_digit_or_q(tmp, c)) || equal(tmp, tokens))))
		{
			i++;
			n = 0;
			if (ft_isspace(*tmp) || equal(tmp, tokens))
				flag = 0;
		}
		n = 1;
		tmp++;
	}
	return (ft_free_tmp(tmp, ft_strlen(str), 1), i);
}

// char	*ft_fill_the_word(char *str, int end, char *lst)
// {
// 	int	i;
// 	int	tmp;

// 	tmp = end;
// 	while (end > 0)
// 	{
// 		str--;
// 		end--;
// 	}
// 	i = 0;
// 	while (i < tmp)
// 	{
// 		lst[i] = str[i];
// 		i++;
// 	}
// 	(void)str;
// 	lst[i] = 0;
// 	return (lst);
// }

// char	**ft_allocate_memory(char *str, char c)
// {
// 	char	**lst;
// 	char	*tmp;

// 	tmp = ft_strdup(str);
// 	lst = ft_calloc((ft_countword(str, c, tmp) + 1), sizeof(char *));
// 	if (!str || !lst)
// 		return (NULL);
// 	return (lst);
// }

// int	find_next_word_length(char *str, char c)
// {
// 	int	reset;
// 	int	flag;

// 	reset = 0;
// 	flag = 0;
// 	while ((reset > 0 && *str != c) || reset == 0)
// 	{
// 		if (*str == c)
// 			flag = 1;
// 		if ((flag == 1 && (isspace(*str))) || (*str == '\0'))
// 			break ;
// 		else if (flag == 1 && ft_digit_or_q(str, c))
// 		{
// 			reset++;
// 			str++;
// 			break ;
// 		}
// 		str++;
// 		reset++;
// 	}
// 	return (reset);
// }

char	*allocate_and_fill_word(char *str, int length)
{
	char	*word;
	int		i;

	word = calloc(length + 1, sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < length)
	{
		word[i] = str[i];
		i++;
	}
	return (word);
}

char	**ft_fill_array(char **lst, char *str, int n, t_token *tokens)
{
	int	j;
	int	word_length;

	j = 0;
	while (*str != '\0')
	{
		word_length = find_next_word_length(str, '$', tokens);
		lst[j] = allocate_and_fill_word(str, word_length);
		if (!lst[j])
			return (NULL);
		j++;
		if (j == n - 1)
			break ;
		str += word_length;
	}
	lst[j] = NULL;
	return (lst);
}

char	**ft_split_bis(char *str, char c, t_token *tokens)
{
	char	**lst;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(str);
	tmp2 = ft_strdup(str);
	lst = ft_allocate_memory(str, c, tokens);
	if (!lst)
		return (NULL);
	lst = ft_fill_array(lst, tmp, ft_countword(str, c, tmp2, tokens) + 1,
			tokens);
	free(tmp);
	return (lst);
}
