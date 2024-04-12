/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:48:14 by aguede            #+#    #+#             */
/*   Updated: 2024/04/09 22:08:43 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

void	ft_free_double_d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	if (str)
	{
		while (str[i] != NULL)
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	ft_free_envi(char **part1, char **part2)
{
	ft_free_double_d(part1);
	ft_free_double_d(part2);
}
