/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:36:10 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/03 16:36:12 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

bool	ft_is_redir(t_token_type type)
{
	if (type == TOKEN_INPUT_REDIRECTION || type == TOKEN_OUTPUT_REDIRECTION
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND_OUTPUT_REDIRECTION)
		return (true);
	return (false);
}

bool	ft_join_args(char **args, t_minishell *minishell)
{
	char	*to_free;

	if (minishell->parse_error.type)
		return (false);
	if (!*args)
		*args = ft_strdup("");
	if (!*args)
		return (false);
	while (minishell->current_token
		&& minishell->current_token->type == TOKEN_WORD)
	{
		to_free = *args;
		*args = ft_strjoin_with(*args, minishell->current_token->value, ' ');
		if (!*args)
		{
			free(to_free);
			return (false);
		}
		free(to_free);
		ft_get_next_token(minishell);
	}
	return (true);
}

bool	ft_handle_redir_error(t_redir_node **redir_list, t_node *node)
{
	ft_clear_redir_list(redir_list);
	ft_set_parse_error(MALLOC_ERROR);
	if (node)
	{
		free(node->split_args);
		free(node);
	}
	return (false);
}

bool	ft_get_redir_list(t_redir_node **redir_list, t_minishell *minishell,
		t_node *node)
{
	t_token_type	redir_type;

	if (!ft_check_parse_error(minishell))
		return (false);
	while (minishell->current_token
		&& ft_is_redir(minishell->current_token->type))
	{
		redir_type = minishell->current_token->type;
		ft_get_next_token(minishell);
		if (!ft_check_current_token(minishell)
			|| !ft_check_token_type(minishell))
			return (false);
		if (!ft_create_and_append_redir_node(redir_list, minishell, redir_type))
			return (ft_handle_redir_error(redir_list, node));
		if (minishell->current_token)
			ft_get_next_token(minishell);
	}
	return (true);
}
