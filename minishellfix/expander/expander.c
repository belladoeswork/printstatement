/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 00:25:44 by aguede            #+#    #+#             */
/*   Updated: 2024/04/07 23:57:39 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

typedef struct s_two_strings
{
	char	*to_keep;
	char	*to_verif;
}			t_two_strings;

int	ft_check_if_expand(char *str, char **p1)
{
	int	i;

	i = 0;
	if (str[0] == '$')
	{
		while (p1[i] != NULL)
		{
			if ((ft_strncmp(str + 1, p1[i], ft_strlen(p1[i])) == 0
					&& (ft_strlen(p1[i]) == (ft_strlen(str) - 1)))
				|| str[1] == '?')
			{
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	ft_check_dollar_word_expand(char **dollar_separated_str, char **p1)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dollar_separated_str[i] != NULL)
	{
		if (dollar_separated_str[i][0] == '$')
		{
			if (ft_check_if_expand(dollar_separated_str[i], p1))
				j++;
		}
		i++;
	}
	return (j);
}

int	ft_check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	expand_tokens(t_token *tokens, char **p1, char **p2)
{
	char	*expanded_tilde;
	char	**div_by_quote;
	char	**div_by_doll;
	char	**clean;

	while (tokens != NULL)
	{
		if (tokens->type == TOKEN_WORD)
		{
			expanded_tilde = ft_expand_tilde(tokens->value, p1, p2);
			if (ft_check_dollar(tokens->value))
			{
				div_by_quote = ft_new_ft_split(expanded_tilde, '\'');
				div_by_doll = ft_split_double(div_by_quote, '$', tokens);
				ft_free_double_d(div_by_quote);
				clean = ft_remove_wrong_env_var(div_by_doll, p1);
				tokens->value = ft_expand_assemble(clean, p1, p2);
				ft_free_double_d(clean);
			}
			else
				tokens->value = ft_strdup(expanded_tilde);
			free(expanded_tilde);
		}
		tokens = tokens->next;
	}
}

t_token	*ft_expander(t_token *tokens, char **env)
{
	t_lists_env	envi;
	t_token		*head;

	envi = ft_split_lists_env(env);
	head = tokens;
	expand_tokens(tokens, envi.p1, envi.p2);
	ft_free_envi(envi.p1, envi.p2);
	return (head);
}
