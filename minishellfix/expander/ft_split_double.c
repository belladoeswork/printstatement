/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:54:32 by aguede            #+#    #+#             */
/*   Updated: 2024/04/03 16:34:09 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lumumbash.h"

// char	**ft_double_strdup(char **str)
// {
// 	int		i;
// 	int		n;
// 	char	**str_dup;

// 	i = 0;
// 	n = 0;
// 	while (str[i] != NULL)
// 		i++;
// 	str_dup = ft_calloc(i + 1, sizeof(char *));
// 	while (str[n] != NULL)
// 	{
// 		str_dup[n] = ft_strdup(str[n]);
// 		n++;
// 	}
// 	str_dup[n] = NULL;
// 	return (str_dup);
// }

char	**ft_all_in_one(char **final_strings, char ***new_str_str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (new_str_str[i] != NULL)
	{
		j = 0;
		while (new_str_str[i][j] != NULL)
		{
			final_strings[k] = ft_strdup(new_str_str[i][j]);
			k++;
			j++;
		}
		i++;
	}
	final_strings[k] = NULL;
	return (final_strings);
}

// char	**ft_string_to_double_d(char *str)
// {
// 	char	**str_double;

// 	str_double = ft_calloc(2, sizeof(char *));
// 	if (!str_double)
// 		return (NULL);
// 	str_double[0] = ft_strdup(str);
// 	str_double[1] = NULL;
// 	return (str_double);
// }

char	***ft_allocate_and_populate_new_str_str(char **str, char c,
		int *total_words, t_token *tokens)
{
	int		i;
	int		j;
	char	***new_str_str;

	i = 0;
	j = 0;
	while (str[i] != NULL)
		i++;
	new_str_str = ft_calloc(i + 1, sizeof(char **));
	if (!new_str_str)
		return (NULL);
	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] != '\'')
			new_str_str[j] = ft_split_bis(str[i], c, tokens);
		else
			new_str_str[j] = ft_string_to_double_d(str[i]);
		i++;
		j++;
	}
	new_str_str[j] = NULL;
	*total_words = j;
	return (new_str_str);
}

char	**ft_create_final_strings(char ***new_str_str, int total)
{
	int		total_words;
	char	**final_strings;

	(void)total;
	total_words = ft_count_number_of_words(new_str_str);
	final_strings = ft_calloc(total_words + 1, sizeof(char *));
	if (!final_strings)
		return (NULL);
	final_strings = ft_all_in_one(final_strings, new_str_str);
	return (final_strings);
}

void	ft_free_new_str_str(char ***new_str_str)
{
	int		i;
	char	**current_array;

	if (new_str_str)
	{
		i = 0;
		while (new_str_str[i] != NULL)
		{
			if (new_str_str[i])
			{
				current_array = new_str_str[i];
				ft_free_double_d(current_array);
			}
			i++;
		}
		free(new_str_str);
	}
}

char	**ft_split_double(char **str, char c, t_token *tokens)
{
	int		total_words;
	char	***new_str_str;
	char	**final_strings;

	new_str_str = ft_allocate_and_populate_new_str_str(str, c, &total_words,
			tokens);
	if (!new_str_str)
		return (NULL);
	final_strings = ft_create_final_strings(new_str_str, total_words);
	ft_free_new_str_str(new_str_str);
	return (final_strings);
}
