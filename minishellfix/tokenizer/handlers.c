/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:45:31 by aguede            #+#    #+#             */
/*   Updated: 2024/04/07 07:22:54 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

int	ft_handle_separator(char **line_ptr, t_token **token_list)
{
	int	length;

	length = 0;
	if (ft_handle_heredoc(line_ptr, token_list))
		length = 2;
	else if (ft_handle_append_output_redirection(line_ptr, token_list))
		length = 2;
	else if (ft_handle_input_redirection(line_ptr, token_list))
		length = 1;
	else if (ft_handle_output_redirection(line_ptr, token_list))
		length = 1;
	else if (ft_handle_pipe(line_ptr, token_list))
		length = 1;
	return (length);
}

char	*ft_create_word(char *line, char *word, int in_quotes, t_integers *ints)
{
	while (line[ints->i])
	{
		if (line[ints->i] == '"' || line[ints->i] == '\'')
		{
			if (in_quotes)
			{
				if (in_quotes == line[ints->i])
					in_quotes = 0;
			}
			else
				in_quotes = line[ints->i];
			word[ints->j++] = line[ints->i];
		}
		else if (!in_quotes && (line[ints->i] == '<' || line[ints->i] == '>'
				|| line[ints->i] == '|' || line[ints->i] == ' '))
			break ;
		else
			word[ints->j++] = line[ints->i];
		ints->i++;
	}
	return (word[ints->j] = '\0', word);
}
// t_token	*ft_tokenization_handler(char *line)
// {
// 	int		error;
// 	t_token	*token_list;

// 	error = 0;
// 	token_list = NULL;
// 	while (*line)
// 	{
// 		if (error)
// 		{
// 			ft_clear_token_list(&token_list);
// 			return (NULL);
// 		}
// 		if (ft_isspace(*line))
// 			ft_skip_spaces(&line);
// 		else if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
// 			|| !ft_strncmp(line, "|", 1))
// 			error = !ft_handle_separator(&line, &token_list);
// 		else
// 			error = !ft_append_word(&line, &token_list);
// 	}
// 	if (error)
// 		return (ft_clear_token_list(&token_list), NULL);
// 	return (token_list);
// }

// int	ft_handle_quotes(char **line_ptr, t_token **token_list)
// {
// 	char	*line;
// 	char	*start;
// 	char	*word;
// 	int		in_quotes;

// 	line = *line_ptr;
// 	start = line;
// 	word = NULL;
// 	in_quotes = *line;
// 	line++;
// 	while (*line && *line != in_quotes)
// 	{
// 		line++;
// 	}
// 	if (*line == in_quotes)
// 	{
// 		word = ft_substr(start, 0, line - start + 1);
// 		if (!word)
// 			return (0);
// 		if (!ft_token_list_add_back(token_list, ft_new_token(word, TOKEN_WORD)))
// 		{
// 			free(word);
// 			return (0);
// 		}
// 		*line_ptr = line + 1;
// 		return (1);
// 	}
// 	else
// 	{
// 		ft_quote_error(in_quotes);
// 		return (0);
// 	}
// }

char	*find_end_of_quoted_string(char *line, int in_quotes)
{
	char	*end;

	end = line;
	while (*end && *end != in_quotes)
	{
		end++;
	}
	return (end);
}

int	ft_handle_quotes(char **line_ptr, t_token **token_list)
{
	char	*end;
	char	*line;
	char	*start;
	int		in_quotes;

	line = *line_ptr;
	start = line;
	in_quotes = *line;
	line++;
	end = find_end_of_quoted_string(line, in_quotes);
	if (*end == in_quotes)
		return (create_and_add_quoted_token(line_ptr, start, end, token_list));
	else
	{
		ft_quote_error(in_quotes);
		return (0);
	}
}

t_token	*ft_tokenization_handler(char *line)
{
	int		error;
	t_token	*token_list;

	error = 0;
	token_list = NULL;
	while (*line)
	{
		if (error)
			return (ft_clear_token_list(&token_list), NULL);
		if (isspace(*line))
		{
			while (isspace(*line))
				line++;
		}
		else if (!strncmp(line, "<", 1) || !strncmp(line, ">", 1)
			|| !strncmp(line, "|", 1))
			error = !ft_handle_separator(&line, &token_list);
		else if (*line == '"' || *line == '\'')
			error = !ft_handle_quotes(&line, &token_list);
		else
			error = !ft_append_word(&line, &token_list);
	}
	if (error)
		return (ft_clear_token_list(&token_list), NULL);
	return (token_list);
}
