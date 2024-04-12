/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:06:35 by aguede            #+#    #+#             */
/*   Updated: 2024/04/12 11:38:17 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

static int	ft_export_error_msg(char *identifier)
{
	ft_putstr_fd("lumumbash: export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

void	ft_modif_env_var(t_lists_env envi, char *key, char *val,
		t_minishell *minishell)
{
	int		i;
	char	*key_update;
	char	**new_environ;

	i = 0;
	key_update = ft_create_new_key(key);
	while (envi.p1[i] != NULL)
	{
		if (ft_strncmp(key, envi.p1[i], ft_strlen(envi.p1[i])) == 0)
			break ;
		i++;
	}
	new_environ = duplicate_environ(minishell->environ, key_update, val);
	ft_free_double_d(minishell->environ);
	minishell->environ = new_environ;
	free(key_update);
}

char	**populate_str(char **minishellenviron, char *key, char *update,
		t_lists_env list_env)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_calloc(ft_strlen_double_pers(minishellenviron) + 2,
			sizeof(char *));
	if (!str)
		return (NULL);
	while (minishellenviron[i] != NULL)
	{
		if (ft_strncmp(list_env.p1[i], key, ft_strlen(key)) == 0)
		{
			str[i] = ft_strdup(update);
			if (list_env.p1[i + 1] != NULL)
				i++;
			else
				break ;
		}
		str[i] = ft_strdup(minishellenviron[i]);
		i++;
	}
	i++;
	ft_free_lists_env(list_env);
	return (str[i] = NULL, str);
}

void	ft_add_env_var(char *key, char *val, int true_or_false,
		t_minishell *minishell)
{
	t_lists_env	list_env;
	char		**str;
	char		*val_update;
	char		*no_space;

	if (val == NULL)
	{
		free(key);
		return ;
	}
	no_space = ft_no_space(val);
	val_update = ft_remove_ft_q(no_space);
	list_env = ft_split_lists_env(minishell->environ);
	if (true_or_false == 1)
	{
		str = ft_modify_env_var(minishell->environ, key, val_update);
		ft_free_double_d(minishell->environ);
		minishell->environ = str;
	}
	else if (true_or_false == 0)
		ft_modif_env_var(list_env, key, val_update, minishell);
	free(val_update);
	free(no_space);
	ft_free_lists_env(list_env);
}

// void	ft_print_export(t_minishell *minishell)
// {
// 	char	**str_dup;
// 	char	*str;
// 	int		i;
// 	int		n;

// 	i = 0;
// 	n = 0;
// 	while (minishell->environ[i] != NULL)
// 		i++;
// 	str_dup = ft_calloc(i + 12 + 1, sizeof(char *));
// 	while (minishell->environ[n] != NULL)
// 	{
// 		str = ft_strdup(minishell->environ[n]);
// 		str_dup[n] = ft_strjoin("declare -x ", str);
// 		n++;
// 		free(str);
// 	}
// 	str_dup[n] = NULL;
// 	ft_print_double_d_f(str_dup);
// 	ft_free_double_d(str_dup);
// }

int	ft_export(char **argv, t_minishell **minishell, int exit_s)
{
	int		i;
	char	*key;

	exit_s = 0;
	i = 1;
	while (argv[i] != NULL)
		i++;
	if (i == 1)
		return (ft_print_export(*minishell), exit_s);
	i = 1;
	while (argv[i])
	{
		if (ft_keycheck(argv[i]) == 0)
			exit_s = ft_export_error_msg(argv[i]);
		else
		{
			key = ft_extract_key(argv[i]);
			if (!ft_key_check(key, *minishell))
				ft_add_env_var(key, ft_extract_val(argv[i]), 0, *minishell);
			else
				ft_add_env_var(key, ft_extract_val(argv[i]), 1, *minishell);
		}
		i++;
	}
	return (exit_s);
}
