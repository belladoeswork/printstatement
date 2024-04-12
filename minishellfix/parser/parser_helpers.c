/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:32:53 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/11 11:49:10 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

// t_node	*ft_create_node(void)
// {
// 	t_node	*node;

// 	node = ft_new_node(NODE_CMD);
// 	if (!node)
// 	{
// 		free(node);
// 		return (NULL);
// 	}
// 	return (node);
// }

// t_node	*ft_get_simple_cmd(t_minishell *minishell)
// {
// 	t_node	*node;
// 	char	**split_args;
// 	int		i;

// 	if (minishell->parse_error.type)
// 		return (NULL);
// 	node = ft_create_node();
// 	if (!node)
// 		return (NULL);
// 	split_args = ft_allocate_split_args();
// 	if (!split_args)
// 	{
// 		free(node);
// 		return (NULL);
// 	}
// 	node->split_args = split_args;
// 	i = 0;
// 	ft_process_tokens(minishell, node, &i);
// 	node->split_args[i] = NULL;
// 	return (node);
// }

t_node	*ft_get_simple_cmd(t_minishell *minishell)
{
	t_node	*node;
	char	**split_args;
	int		i;

	if (minishell->parse_error.type)
		return (NULL);
	node = ft_new_node(NODE_CMD);
	if (!node)
	{
		return (ft_set_parse_error(MALLOC_ERROR), NULL);
	}
	split_args = ft_allocate_split_args();
	if (!split_args)
	{
		ft_clear_cmd_node(node);
		ft_set_parse_error(MALLOC_ERROR);
		return (NULL);
	}
	node->split_args = split_args;
	i = 0;
	ft_process_tokens(minishell, node, &i);
	node->split_args[i] = NULL;
	return (node);
}

// 	split_args = ft_allocate_split_args();
// 	if (!split_args)
// 	{
// 		free(node);
// 		return (NULL);
// 	}
// 	node->split_args = split_args;
// 	i = 0;
// 	ft_process_tokens(minishell, node, &i);
// 	node->split_args[i] = NULL;
// 	return (node);
// }

t_node	*ft_term(t_minishell *minishell)
{
	if (minishell->parse_error.type)
		return (NULL);
	if (ft_current_token_is_op(minishell))
	{
		ft_set_parse_error(SYNTAX_ERROR);
		return (NULL);
	}
	else
		return (ft_get_simple_cmd(minishell));
}

t_node	*ft_combine(t_token_type op, t_node *left, t_node *right,
		t_minishell *minishell)
{
	t_node	*node;

	if (minishell->parse_error.type)
		return (NULL);
	node = ft_new_node(ft_get_node_type(op));
	if (!node)
		return (ft_set_parse_error(MALLOC_ERROR), NULL);
	node->left = left;
	node->right = right;
	return (node);
}

// t_node	*ft_expression(t_minishell *minishell)
// {
// 	t_node			*left;
// 	t_node			*right;
// 	t_token_type	op;

// 	if (minishell->parse_error.type || !minishell->current_token)
// 		return (NULL);
// 	left = ft_term(minishell);
// 	if (!left)
// 		return (NULL);
// 	while (ft_current_token_is_op(minishell))
// 	{
// 		op = minishell->current_token->type;
// 		ft_get_next_token(minishell);
// 		if (!minishell->current_token)
// 			return (ft_set_parse_error(SYNTAX_ERROR), left);
// 		right = ft_expression(minishell);
// 		if (!right)
// 			return (left);
// 		left = ft_combine(op, left, right, minishell);
// 		if (!left)
// 			return (ft_clear_ast(&left, minishell), ft_clear_ast(&right,
// 					minishell), NULL);
// 	}
// 	return (left);
// }

t_node	*ft_expression(t_minishell *minishell)
{
	t_node			*left;
	t_node			*right;
	t_token_type	op;

	if (minishell->parse_error.type || !minishell->current_token)
		return (NULL);
	left = ft_term(minishell);
	if (!left)
		return (NULL);
	while (ft_current_token_is_op(minishell))
	{
		op = minishell->current_token->type;
		ft_get_next_token(minishell);
		if (!minishell->current_token)
			return (ft_set_parse_error(SYNTAX_ERROR), left);
		right = ft_expression(minishell);
		if (!right)
			return (left);
		left = ft_combine(op, left, right, minishell);
		if (!left)
			return (ft_clear_ast(&left, minishell), ft_clear_ast(&right,
					minishell), NULL);
	}
	return (left);
}
