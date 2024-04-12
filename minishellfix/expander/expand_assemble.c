/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_assemble.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:47:05 by aguede            #+#    #+#             */
/*   Updated: 2024/04/07 21:50:19 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lumumbash.h"

char	*ft_assemble(char **strings_to_assemble)
{
	char	*assembled_string;
	int		total_n;
	int		i;
	int		offset;

	total_n = 0;
	i = 0;
	while (strings_to_assemble[i] != NULL)
	{
		total_n += ft_strlen(strings_to_assemble[i]);
		i++;
	}
	assembled_string = ft_calloc(total_n + 1, sizeof(char));
	if (assembled_string == NULL)
		return (NULL);
	i = 0;
	offset = 0;
	while (strings_to_assemble[i] != NULL)
	{
		ft_strcat(assembled_string + offset, strings_to_assemble[i]);
		offset += ft_strlen(strings_to_assemble[i]);
		i++;
	}
	ft_free_double_d(strings_to_assemble);
	return (assembled_string);
}

int	ft_my_strlen(long number)
{
	int	returnv;

	returnv = 0;
	if (number < 0)
	{
		number = number * -1;
		returnv++;
	}
	if (number == 0)
	{
		return (1);
	}
	while (number > 0)
	{
		number = number / 10;
		returnv++;
	}
	return (returnv);
}

char	*ft_indeed_expand(char *to_expand, char *b_equal[], char **a_equal)
{
	int		k;
	char	*str;

	k = 0;
	if (to_expand[1] == '?')
	{
		str = ft_itoa(g_global.error_num);
		return (str);
	}
	while (b_equal[k] != NULL)
	{
		if (ft_strncmp(to_expand + 1, b_equal[k], ft_strlen(b_equal[k])) == 0)
			break ;
		k++;
	}
	return (ft_strdup(a_equal[k]));
}

int	double_quote(int i, char *str)
{
	int	n;

	if (str[i] != '\'')
		return (1);
	n = 0;
	while (i != 0)
	{
		if (str[i] == '\"')
			n++;
		i--;
	}
	if (str[0] == '\"')
		n++;
	if ((n % 2) == 1)
		return (1);
	else
		return (0);
}

// char	*ft_rem_quote(char *str)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != '\'' || (str[i] == '\'' && double_quote(i, str)))
// 		{
// 			str[j++] = str[i];
// 		}
// 		i++;
// 	}
// 	str[j] = '\0';
// 	return (str);
// }

char	*ft_expand_assemble(char **str, char **b_equal, char **a_equal)
{
	int		i;
	int		n;
	char	**expanded_str;
	char	*assembled_expanded_str;
	char	*noquotes;

	i = 0;
	n = 0;
	while (str[n] != NULL)
		n++;
	expanded_str = ft_calloc(n + 1, sizeof(char *));
	if (!expanded_str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if ((ft_check_if_expand(str[i], b_equal)))
			expanded_str[i] = ft_indeed_expand(str[i], b_equal, a_equal);
		else
			expanded_str[i] = ft_strdup(str[i]);
		i++;
	}
	expanded_str[i] = NULL;
	assembled_expanded_str = ft_assemble(expanded_str);
	return (noquotes = ft_rem_quote(assembled_expanded_str), noquotes);
}
