/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:38:48 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/08 21:22:40 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include "lumumbash.h"

typedef struct s_global
{
	int			error_num;
}				t_global;

extern t_global	g_global;

#endif