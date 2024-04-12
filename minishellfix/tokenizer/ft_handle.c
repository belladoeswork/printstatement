/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:42:33 by aguede            #+#    #+#             */
/*   Updated: 2024/04/03 16:42:40 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

int	ft_handle_heredoc(char **line_ptr, t_token **token_list)
{
	if (!ft_strncmp(*line_ptr, "<<", 2))
		return (ft_append_separator(TOKEN_HEREDOC, line_ptr, token_list) && 1);
	return (0);
}

int	ft_handle_append_output_redirection(char **line_ptr, t_token **token_list)
{
	if (!ft_strncmp(*line_ptr, ">>", 2))
		return (ft_append_separator(TOKEN_APPEND_OUTPUT_REDIRECTION, line_ptr,
				token_list) && 1);
	return (0);
}

int	ft_handle_input_redirection(char **line_ptr, t_token **token_list)
{
	if (!ft_strncmp(*line_ptr, "<", 1))
		return (ft_append_separator(TOKEN_INPUT_REDIRECTION, line_ptr,
				token_list) && 1);
	return (0);
}

int	ft_handle_output_redirection(char **line_ptr, t_token **token_list)
{
	if (!ft_strncmp(*line_ptr, ">", 1))
		return (ft_append_separator(TOKEN_OUTPUT_REDIRECTION, line_ptr,
				token_list) && 1);
	return (0);
}

int	ft_handle_pipe(char **line_ptr, t_token **token_list)
{
	if (!ft_strncmp(*line_ptr, "|", 1))
		return (ft_append_separator(TOKEN_PIPE, line_ptr, token_list) && 1);
	return (0);
}
