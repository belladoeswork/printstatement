/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appends.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 07:17:20 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/09 20:13:46 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

int	ft_append_separator(t_token_type type, char **line_ptr,
		t_token **token_list)
{
	t_token	*token;
	int		length;

	if (type == TOKEN_HEREDOC || type == TOKEN_APPEND_OUTPUT_REDIRECTION)
		length = 2;
	else
		length = 1;
	token = ft_new_token(ft_substr(*line_ptr, 0, length), type);
	if (!token)
		return (0);
	*line_ptr += length;
	return (ft_token_list_add_back(token_list, token), 1);
}

int	ft_append_word(char **line_ptr, t_token **token_list)
{
	t_integers	ints;
	char		*line;
	int			in_quotes;
	char		*word;

	line = *line_ptr;
	in_quotes = 0;
	word = malloc(ft_strlen(line) + 1);
	if (!word)
		return (0);
	ints.i = 0;
	ints.j = 0;
	word = ft_create_word(line, word, in_quotes, &ints);
	if (!ft_token_list_add_back(token_list, ft_new_token(word, TOKEN_WORD)))
	{
		free(word);
		return (0);
	}
	*line_ptr += ints.i;
	return (1);
}

int	create_and_add_quoted_token(char **line_ptr, char *start, char *end,
		t_token **token_list)
{
	char	*word;

	word = ft_substr(start, 0, end - start + 1);
	if (!word)
	{
		return (0);
	}
	if (!ft_token_list_add_back(token_list, ft_new_token(word, TOKEN_WORD)))
	{
		free(word);
		return (0);
	}
	*line_ptr = end + 1;
	return (1);
}
