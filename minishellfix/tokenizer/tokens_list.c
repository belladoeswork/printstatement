/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:45:57 by aguede            #+#    #+#             */
/*   Updated: 2024/04/07 07:03:24 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

void	ft_clear_token_list(t_token **list)
{
	t_token	*current_node;
	t_token	*next;

	current_node = *list;
	while (current_node)
	{
		next = current_node->next;
		if (current_node->value)
		{
			free(current_node->value);
			current_node->value = NULL;
		}
		free(current_node);
		current_node = next;
	}
	*list = NULL;
}

// int	ft_token_list_add_back(t_token **lst, t_token *new_token)
// {
// 	t_token	*curr_node;
// 	int		counter;

// 	counter = 0;
// 	if (!new_token || new_token->next)
// 		return (0);
// 	if (!*lst)
// 	{
// 		*lst = new_token;
// 		return (1);
// 	}
// 	curr_node = *lst;
// 	while (curr_node->next)
// 	{
// 		curr_node = curr_node->next;
// 		counter++;
// 		if (counter > 1000 || !curr_node)
// 		{
// 			printf("Possible infinite loop detected in token_list_add_back\n");
// 			return (0);
// 		}
// 	}
// 	curr_node->next = new_token;
// 	new_token->prev = curr_node;
// 	return (1);
// }
int	ft_token_list_add_back(t_token **lst, t_token *new_token)
{
	t_token	*curr_node;

	if (!new_token || new_token->next)
	{
		return (0);
	}
	if (!*lst)
	{
		*lst = new_token;
		return (1);
	}
	curr_node = *lst;
	while (curr_node->next)
	{
		curr_node = curr_node->next;
	}
	curr_node->next = new_token;
	return (1);
}
