/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:50:56 by aguede            #+#    #+#             */
/*   Updated: 2024/04/14 20:31:57 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

void	process_word_token(t_minishell *minishell, t_node *node, int *i)
{
	char	*value;

	if (*i >= MAX_NUM_ARGS - 1)
	{
		ft_error_msg((t_error){.msg = TOO_MANY_ARGS});
		return ;
	}
	node->split_args[*i] = malloc((strlen(minishell->current_token->value) + 1)
			* sizeof(char));
	if (!node->split_args[*i])
	{
		perror("malloc");
		return ;
	}
	value = minishell->current_token->value;
	strcpy(node->split_args[*i], value);
	(*i)++;
	if (minishell->current_token)
		minishell->current_token = minishell->current_token->next;
}

void	process_redirection_token(t_minishell *minishell, t_node *node)
{
	if (!minishell->current_token->next
		|| minishell->current_token->next->type != TOKEN_WORD)
	{
		minishell->parse_error.type = SYNTAX_ERROR;
		return ;
	}
	if (!ft_get_redir_list(&(node->redir_list), minishell, node))
	{
		free(node->split_args);
		free(node);
		return ;
	}
}

void	ft_process_tokens(t_minishell *minishell, t_node *node, int *i)
{
	t_error	error;

	error.msg = TOO_MANY_ARGS;
	while (minishell->current_token
		&& (minishell->current_token->type == TOKEN_WORD
			|| ft_is_redir(minishell->current_token->type)))
	{
		if (minishell->parse_error.type == SYNTAX_ERROR)
			break ;
		if (minishell->current_token
			&& minishell->current_token->type == TOKEN_WORD)
			process_word_token(minishell, node, i);
		if (minishell->current_token
			&& ft_is_redir(minishell->current_token->type))
		{
			process_redirection_token(minishell, node);
			if (minishell->current_token
				&& minishell->current_token->type == TOKEN_WORD)
			{
				process_word_token(minishell, node, i);
			}
		}
	}
}
