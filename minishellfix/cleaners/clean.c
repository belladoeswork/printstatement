/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:11:10 by tbella-n          #+#    #+#             */
/*   Updated: 2024/03/30 01:24:56 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;
	t_list	*curr;

	if (!lst || !*lst || !del)
		return ;
	curr = *lst;
	next = curr->next;
	while (curr && next)
	{
		del(curr->content);
		free(curr);
		curr = next;
		next = curr->next;
	}
	del(curr->content);
	free(curr);
	*lst = NULL;
}

void	ft_clean_shell(t_minishell *minishell)
{
	ft_collector(NULL, true);
	ft_clear_ast(&(minishell->ast), minishell);
	clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &(minishell->original_term));
}

static void	ft_del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	*ft_collector(void *ptr, bool clean)
{
	static t_list	*garbage_list;

	if (clean)
	{
		ft_lstclear(&garbage_list, ft_del);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&garbage_list, ft_lstnew(ptr));
		return (ptr);
	}
}
