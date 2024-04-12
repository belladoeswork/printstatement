/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:26:04 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/03 15:49:43 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

char	*ft_get_path(char **args)
{
	char	*path;

	if (args[0] == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			printf("cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (strcmp(args[0], "-") == 0)
	{
		path = getenv("OLDPWD");
		if (path == NULL)
		{
			printf("cd: OLDPWD not set\n");
			return (NULL);
		}
	}
	else
		path = args[0];
	return (path);
}

int	ft_cd(char **args)
{
	char	*path;

	path = ft_get_path(args);
	if (path == NULL)
		return (1);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
