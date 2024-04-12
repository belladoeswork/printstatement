/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:17:02 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/12 08:35:33 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

// void	sighandler_child(int numsig)
// {
// 	g_global.error_num = 130;
// 	ft_putstr_fd("\n", 1);
// 	g_global.error_num = 130;
// 	(void)numsig;
// }

void	sighandler_child(int numsig)
{
	g_global.error_num = 130;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	g_global.error_num = 130;
	(void)numsig;
}

// void	ft_signal_ctrl_d(int numsig)
// {
// 	// g_global.error_num = 130;
// 	// printf("\nCtrl+C pressed. Exiting heredoc.\n");
	
// 	(void)numsig;
// 	// exit(EXIT_SUCCESS);
// 	g_global.error_num = 130;
// 	// return ;
// 	exit(SIGINT);
// }

// void	ft_signal_ctrl_d(int numsig)
// {	
// 	(void)numsig;
// 	g_global.error_num = 130;
// 	exit(SIGINT);
// }

// void	sighandler_child_coredumped(int numsig)
// {
// 	if (isatty(fileno(stdin)))
// 	{
// 		g_global.error_num = 131;
// 		ft_putstr_fd("Quit (core dumped)\n", 2);
// 		if (rl_line_buffer[0] != '\0')
// 			rl_replace_line("", 0);
// 		rl_on_new_line();
// 		g_global.error_num = 131;
// 		(void)numsig;
// 	}
// }

void	sighandler_child_coredumped(int numsig)
{
	if (isatty(fileno(stdin)))
	{
		g_global.error_num = 131;
		ft_putstr_fd("Quit (core dumped)\n", 2);
		if (rl_line_buffer[0] != '\0')
			rl_on_new_line();
		g_global.error_num = 131;
		(void)numsig;
	}
	g_global.error_num = 131;
}

// void	ft_signal_ctrl_c(int numsig)
// {
// 	if (numsig == SIGINT)
// 	{
// 		if (isatty(fileno(stdin)))
// 		{
// 			g_global.error_num = 130;
// 			ft_putstr_fd("\n", 1);
// 			if (rl_line_buffer[0] != '\0')
// 				rl_replace_line("", 0);
// 			rl_on_new_line();
// 			rl_redisplay();
// 		}
// 		else if (!isatty(fileno(stdin)))
// 		{
// 			g_global.error_num = 130;
// 			close(STDIN_FILENO);
// 		}
// 		else
// 		{
// 			rl_on_new_line();
// 			write(STDOUT_FILENO, "\n", 1);
// 			g_global.error_num = 130;
// 		}
// 	}
// 	return ;
// }

void	ft_signal_ctrl_c(int numsig)
{
	if (numsig == SIGINT)
	{
		if (isatty(fileno(stdin)))
		{
			g_global.error_num = 130;
			ft_putstr_fd("\n", 1);
			if (rl_line_buffer[0] != '\0')
				rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else if (!isatty(fileno(stdin)))
		{
			g_global.error_num = 130;
			close(STDIN_FILENO);
		}
		else
		{
			rl_on_new_line();
			write(STDOUT_FILENO, "\n", 1);
			g_global.error_num = 130;
		}
	}
	return ;
}

void	ft_signals(int i)
{
	if (i == 1)
	{
		signal(SIGINT, ft_signal_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 2)
	{
		signal(SIGQUIT, sighandler_child_coredumped);
		signal(SIGINT, sighandler_child);
	}
}

// void	set_signal(void)
// {
// 	signal(SIGQUIT, sighandler_child_coredumped);
// 	signal(SIGINT, sighandler_child);
// }
