/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:19:10 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/12 13:40:51 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lumumbash.h"

// bool	ft_is_delimiter(char *delimiter, char *str)
// {
// 	while (*str)
// 	{
// 		if (*delimiter == '"' || *delimiter == '\'')
// 		{
// 			delimiter++;
// 			continue ;
// 		}
// 		else if (*str == *delimiter)
// 		{
// 			str++;
// 			delimiter++;
// 		}
// 		else
// 			return (false);
// 	}
// 	while (*delimiter == '"' || *delimiter == '\'')
// 		delimiter++;
// 	return (!*delimiter);
// }

// void	sighandler_heredoc(int numsig)
// {
// 	if (numsig == SIGINT)
// 	{
// 		close(STDIN_FILENO);
// 		exit(130);
// 	}
// }

// void	ft_heredoc(t_redir_node *redir, int p[2], t_minishell *minishell)
// {
// 	char	*line;
// 	char	*quotes;

// 	(void)minishell;
// 	signal(SIGINT, sighandler_heredoc);
// 	quotes = redir->value;
// 	while (*quotes && *quotes != '"' && *quotes != '\'')
// 		quotes++;
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 		{
// 			ft_putstr_fd("\n", 1);
// 			break ;
// 		}
// 		if (ft_is_delimiter(redir->value, line))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		ft_putstr_fd(line, p[1]);
// 		ft_putstr_fd("\n", p[1]);
// 		free(line);
// 	}
// 	close(p[1]);
// 	redir->here_doc = p[0];
	
// }

// void	ft_heredoc_wrapper(t_redir_node *redir, int p[2], t_minishell *mi)
// {

// 	ft_heredoc(redir, p, mi);
// 	exit(0);
// }



// static bool	ft_leave_leaf(int p[2], int *pid)
// {
// 	int	status;

// 	waitpid(*pid, &status, 0);
// 	close(p[1]);
// 	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
// 	{
// 		close(p[0]);
// 		g_global.error_num = 130;
// 		return (true);
// 	}
// 	return (false);
// }

// static void	ft_init_leaf(t_node *node, t_minishell *minishell)
// {
// 	t_redir_node	*redir;
// 	int				p[2];
// 	int				pid;

// 	redir = node->redir_list;
// 	while (redir)
// 	{
// 		if (redir->type == REDIR_HEREDOC)
// 		{
// 			pipe(p);
// 			pid = fork();
// 			if (pid == 0)
// 				ft_heredoc_wrapper(redir, p, minishell);
// 			if (ft_leave_leaf(p, &pid))
// 			{
// 				rl_on_new_line();
// 				rl_replace_line("", 0);
// 				rl_redisplay();
// 				return ;
// 			}
// 			redir->here_doc = p[0];
// 		}
// 		redir = redir->next;
// 	}
// }

// void	ft_init_tree(t_node *node, t_minishell *minishell)
// {
// 	if (!node)
// 		return ;
// 	if (node->type == NODE_PIPE)
// 	{
// 		if (node->left)
// 			ft_init_tree(node->left, minishell);
// 		if (node->right)
// 			ft_init_tree(node->right, minishell);
// 	}
// 	else
// 		ft_init_leaf(node, minishell);
// }

bool ft_is_delimiter(char *delimiter, char *str)
{
    while (*str)
    {
        if (*delimiter == '"' || *delimiter == '\'')
        {
            delimiter++;
            continue;
        }
        else if (*str == *delimiter)
        {
            str++;
            delimiter++;
        }
        else
            return (false);
    }
    while (*delimiter == '"' || *delimiter == '\'')
        delimiter++;
    return (!*delimiter);
}

void sighandler_heredoc(int numsig)
{
    if (numsig == SIGINT)
    {
        ft_putstr_fd("\n", 1);
        rl_on_new_line();
        close(STDIN_FILENO);
        exit(130);
    }
}

void ft_heredoc(t_redir_node *redir, int p[2], t_minishell *minishell)
{
    char *line;
    char *quotes;

    (void)minishell;
    signal(SIGINT, sighandler_heredoc);
    quotes = redir->value;
    while (*quotes && *quotes != '"' && *quotes != '\'')
        quotes++;
    while (1)
    {
        line = readline("> ");
		printf("inside loop ft_heredoc\n");
        if (!line || ft_is_delimiter(redir->value, line))
        {
            if (line)
                free(line);
            break;
        }
        ft_putstr_fd(line, p[1]);
        ft_putstr_fd("\n", p[1]);
        free(line);
    }
	printf("we close p[1] ft_heredoc\n");
	close(p[1]);
    exit(0);
}

void ft_heredoc_wrapper(t_redir_node *redir, int p[2], t_minishell *mi)
{
    ft_heredoc(redir, p, mi);
	// exit(0);
}

static bool ft_leave_leaf(int p[2], int *pid)
{
    int status;

    waitpid(*pid, &status, 0);
	printf("inside ft_leave_leaf pid is %d\n", *pid);
	printf("inside ft_leave_leaf status is %d \n", status);
    close(p[1]);
	printf("g_global.error_num is : %d\n", g_global.error_num);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
        // close(p[0]);
		printf("inside ft_leave_leaf received ctrl c \n");
        g_global.error_num = 130;
        return (true);
    }
	printf("inside ft_leave_leaf we return false \n");
    return (false);
}

static void ft_init_leaf(t_node *node, t_minishell *minishell)
{
    t_redir_node *redir;
    int p[2];
    int pid;

    redir = node->redir_list;
    while (redir)
    {
        if (redir->type == REDIR_HEREDOC)
        {
			printf("inside ft_init_leaf\n");
			pipe(p);
			pid = fork();
            if (pid == 0)
			{
				printf("inside ft_init_leaf and pid is 0\n");
                ft_heredoc_wrapper(redir, p, minishell);
			}
            if (ft_leave_leaf(p, &pid))
			{
				printf("inside ft_init_leaf and pid is : %d\n", pid);
                return;
			}
			printf("inside ft_init_leaf and redir->here_doc = p[0]\n");
            redir->here_doc = p[0];
        }
		printf("inside ft_init_leaf and we go to next redir\n");
        redir = redir->next;
    }
}

void ft_init_tree(t_node *node, t_minishell *minishell)
{
    if (!node)
        return;
    if (node->type == NODE_PIPE)
    {
        if (node->left)
            ft_init_tree(node->left, minishell);
        if (node->right)
            ft_init_tree(node->right, minishell);
    }
    else
        ft_init_leaf(node, minishell);
}









