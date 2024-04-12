/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:29:38 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/03 18:48:10 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

// void	ft_process_tokens(t_minishell *minishell, t_node *node, int *i)
// {
// 	while (minishell->current_token
// 		&& (minishell->current_token->type == TOKEN_WORD
// 			|| ft_is_redir(minishell->current_token->type)))
// 	{
// 		if (minishell->current_token
// 			&& minishell->current_token->type == TOKEN_WORD)
// 		{
// 			node->split_args[*i] = minishell->current_token->value;
// 			(*i)++;
// 		}
// 		else if (minishell->current_token
// 			&& ft_is_redir(minishell->current_token->type))
// 		{
// 			if (!ft_get_redir_list(&(node->redir_list), minishell, node))
// 			{
// 				free(node->split_args);
// 				free(node);
// 				return ;
// 			}
// 		}
// 		if (minishell->current_token)
// 			minishell->current_token = minishell->current_token->next;
// 	}
// }

char	**ft_allocate_split_args(void)
{
	char	**split_args;

	split_args = malloc(MAX_NUM_ARGS * sizeof(char *));
	if (!split_args)
	{
		ft_set_parse_error(MALLOC_ERROR);
		return (NULL);
	}
	return (split_args);
}

bool	ft_current_token_is_op(t_minishell *minishell)
{
	t_token_type	type;

	if (!minishell->current_token)
		return (false);
	type = minishell->current_token->type;
	if (type == TOKEN_PIPE)
		return (true);
	return (false);
}

void	ft_get_next_token(t_minishell *minishell)
{
	minishell->current_token = minishell->current_token->next;
}
