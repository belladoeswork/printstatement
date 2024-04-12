/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:33:54 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/10 19:26:00 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

bool	ft_check_parse_error(t_minishell *minishell)
{
	t_parse_error_type	parse_error_type;

	parse_error_type = minishell->parse_error.type;
	if (parse_error_type)
		return (false);
	return (true);
}

bool	ft_check_current_token(t_minishell *minishell)
{
	if (!minishell->current_token)
	{
		ft_set_parse_error(SYNTAX_ERROR);
		return (false);
	}
	return (true);
}

// t_node	*ft_parse(t_minishell *minishell)
// {
// 	t_node	*ast;

// 	if (minishell->tokens != NULL)
// 		minishell->current_token = minishell->tokens;
// 	ast = ft_expression(minishell);
// 	if (minishell->current_token)
// 	{
// 		ft_set_parse_error(SYNTAX_ERROR);
// 		return (ast);
// 	}
// 	return (ast);
// }

t_node	*ft_parse(t_minishell *minishell)
{
	t_node	*ast;

	if (minishell->tokens != NULL)
		minishell->current_token = minishell->tokens;
	ast = ft_expression(minishell);
	if (minishell->current_token)
	{
		ft_set_parse_error(SYNTAX_ERROR);
		ft_clear_ast(&ast, minishell);
		return (NULL);
	}
	return (ast);
}
