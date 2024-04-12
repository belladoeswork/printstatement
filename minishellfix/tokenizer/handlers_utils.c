/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:45:43 by aguede            #+#    #+#             */
/*   Updated: 2024/04/10 00:02:08 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

// int	ft_handle_space_or_separator(char **line, t_token **token_list)
// {
// 	if (ft_isspace(**line))
// 	{
// 		ft_append_separator(TOKEN_SPACE, line, token_list);
// 		return (0);
// 	}
// 	else if (!ft_strncmp(*line, "<", 1) || !ft_strncmp(*line, ">", 1)
// 		|| !ft_strncmp(*line, "|", 1))
// 		return (!ft_handle_separator(line, token_list));
// 	return (0);
// }

// int	ft_process_token(char **line, t_token **token_list)
// {
// 	int	error;

// 	error = 0;
// 	while (*line && !error)
// 	{
// 		error = ft_handle_space_or_separator(line, token_list);
// 		if (!error)
// 			error = !ft_append_word(line, token_list);
// 	}
// 	return (error);
// }
