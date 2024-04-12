/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:32:08 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/09 20:18:19 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

void	ft_set_parse_error(t_parse_error_type type)
{
	t_minishell	*minishell;

	minishell = NULL;
	if (minishell)
		minishell->parse_error.type = type;
}

char	*ft_get_token_string(t_token_type token_type)
{
	t_tokentypestrings	types;

	types.token_word = "TOKEN_WORD";
	types.token_pipe = "|";
	types.token_input_redirection = "<";
	types.token_output_redirection = ">";
	types.token_append_output_redirection = ">>";
	types.token_heredoc = "<<";
	types.token_nl = "newline";
	if (token_type == TOKEN_WORD)
		return (types.token_word);
	else if (token_type == TOKEN_PIPE)
		return (types.token_pipe);
	else if (token_type == TOKEN_INPUT_REDIRECTION)
		return (types.token_input_redirection);
	else if (token_type == TOKEN_OUTPUT_REDIRECTION)
		return (types.token_output_redirection);
	else if (token_type == TOKEN_APPEND_OUTPUT_REDIRECTION)
		return (types.token_append_output_redirection);
	else if (token_type == TOKEN_HEREDOC)
		return (types.token_heredoc);
	else if (token_type == TOKEN_NL)
		return (types.token_nl);
	return (NULL);
}
// char			*token_word;
// char			*token_pipe;
// char			*token_input_redirection;
// char			*token_output_redirection;
// char			*token_append_output_redirection;
// char			*token_heredoc;
// char			*token_nl;

void	ft_handle_parse_error(t_minishell *minishell)
{
	t_token_type	token_type;
	char			*type_str;

	if (minishell == NULL || minishell->parse_error.type == 0)
		return ;
	if (minishell->parse_error.type == SYNTAX_ERROR)
	{
		if (minishell->current_token == NULL)
			token_type = TOKEN_NL;
		else
			token_type = minishell->current_token->type;
		type_str = ft_get_token_string(token_type);
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(type_str, 2);
		ft_putstr_fd("'\n", 2);
		g_global.error_num = 258;
	}
	ft_clear_ast(&(minishell->ast), minishell);
	ft_bzero(&(minishell->parse_error), sizeof(t_parse_error));
}

void	ft_print_syntax_error(t_token_type token_type)
{
	char	*type;

	if (token_type == TOKEN_WORD)
		type = "TOKEN_WORD";
	else if (token_type == TOKEN_INPUT_REDIRECTION)
		type = "<";
	else if (token_type == TOKEN_OUTPUT_REDIRECTION)
		type = ">";
	else if (token_type == TOKEN_HEREDOC)
		type = "<<";
	else if (token_type == TOKEN_APPEND_OUTPUT_REDIRECTION)
		type = ">>";
	else if (token_type == TOKEN_PIPE)
		type = "|";
	else
		type = "\n";
	ft_putstr_fd("lumumbash: syntax error near unexpected token `", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd("'\n", 2);
	g_global.error_num = 258;
}

t_token_type	ft_determine_token_type(t_minishell *minishell)
{
	t_token_type	token_type;

	if (minishell->current_token == NULL)
		token_type = TOKEN_NL;
	else
		token_type = minishell->current_token->type;
	return (token_type);
}
