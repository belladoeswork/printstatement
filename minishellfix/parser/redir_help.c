/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:34:02 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/03 16:34:06 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

bool	ft_check_token_type(t_minishell *minishell)
{
	t_token_type	token_type;

	token_type = minishell->current_token->type;
	if (token_type != TOKEN_WORD)
	{
		ft_set_parse_error(SYNTAX_ERROR);
		return (false);
	}
	return (true);
}

bool	ft_create_and_append_redir_node(t_redir_node **redir_list,
		t_minishell *minishell, t_token_type redir_type)
{
	t_redir_node	*tmp_redir_node;

	tmp_redir_node = ft_new_redir_node(redir_type,
			minishell->current_token->value);
	if (!tmp_redir_node)
	{
		ft_clear_redir_list(redir_list);
		ft_set_parse_error(MALLOC_ERROR);
		return (false);
	}
	ft_append_redir_node(redir_list, tmp_redir_node);
	return (true);
}
