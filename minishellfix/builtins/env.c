/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:26:35 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/09 20:41:05 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

char	**ft_split_path(char *path)
{
	int		i;
	int		j;
	char	**result;
	char	*path_copy;

	path_copy = ft_strdup(path);
	if (path_copy == NULL)
		exit_with_error("strdup");
	i = 0;
	j = 0;
	result = malloc((ft_count_colons(path_copy) + 1) * sizeof(char *));
	if (result == NULL)
		exit_with_error("malloc");
	result[j] = path_copy;
	while (path_copy[i] != '\0')
	{
		if (path_copy[i] == ':')
		{
			path_copy[i] = '\0';
			result[++j] = &path_copy[i + 1];
		}
		i++;
	}
	return (result[j + 1] = NULL, result);
}

char	*ft_find_command_path(const char *command, char **environ)
{
	t_lists_env	envi;
	char		*path;
	char		**directories;
	char		*full_path;

	if (access(command, F_OK) == 0)
		return (strdup(command));
	envi = ft_split_lists_env(environ);
	path = get_path_from_environ(envi);
	if (!path)
	{
		ft_free_lists_env(envi);
		return (NULL);
	}
	directories = ft_split_path(path);
	full_path = find_full_path(command, directories);
	ft_free_lists_env(envi);
	free(directories[0]);
	free(directories);
	free(path);
	return (full_path);
}

char	*get_path_from_environ(t_lists_env envi)
{
	int	k;

	k = 0;
	while (envi.p1[k] != NULL)
	{
		if (ft_strncmp("PATH", envi.p1[k], ft_strlen(envi.p1[k])) == 0)
			return (ft_strdup(envi.p2[k]));
		k++;
	}
	return (NULL);
}

// char	*find_full_path(const char *command, char **directories)
// {
// 	int		i;
// 	char	*full_path;

// 	i = 0;
// 	while (directories[i] != NULL)
// 	{
// 		full_path = malloc(ft_strlen(directories[i]) + ft_strlen(command) + 2);
// 		if (full_path == NULL)
// 			exit(EXIT_FAILURE);
// 		ft_strcpy(full_path, directories[i]);
// 		ft_strcat(ft_strcat(full_path, "/"), command);
// 		ft_putstr_fd("Checking directory: ", 1);
// 		ft_putstr_fd(directories[i], 1);
// 		ft_putstr_fd("\n", 1);
// 		if (access(full_path, X_OK) == 0)
// 		{
// 			ft_putstr_fd("Command found in directory: ", 1);
// 			ft_putstr_fd(directories[i], 1);
// 			ft_putstr_fd("\n", 1);
// 			return (full_path);
// 		}
// 		free(full_path);
// 		i++;
// 	}
// 	return (NULL);
// }

char	*find_full_path(const char *command, char **directories)
{
	int		i;
	char	*full_path;

	i = 0;
	while (directories[i] != NULL)
	{
		full_path = malloc(ft_strlen(directories[i]) + ft_strlen(command) + 2);
		if (full_path == NULL)
			exit(EXIT_FAILURE);
		ft_strcpy(full_path, directories[i]);
		ft_strcat(ft_strcat(full_path, "/"), command);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	ft_env(char **environ)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (1);
}
