/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:20:54 by aguede            #+#    #+#             */
/*   Updated: 2024/04/14 16:32:43 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lumumbash.h"

t_global	g_global;

static void	ft_init_minishell(t_minishell *minishell, char **env)
{
	memset(minishell, 0, sizeof(t_minishell));
	minishell->environ = ft_double_strdup(env);
	minishell->line = NULL;
	tcgetattr(STDIN_FILENO, &(minishell->original_term));
}

static void	ft_start_execution(t_minishell *minishell)
{
	ft_init_tree(minishell->ast, minishell);
	g_global.error_num = ft_exec_node(minishell->ast, false, minishell);
	ft_clear_ast((&minishell->ast), minishell);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_minishell	minishell;
// 	t_token		*new_tokens;

// 	((void)argc, (void)argv);
// 	ft_signals();
// 	ft_init_minishell(&minishell, env);
// 	while (1)
// 	{
// 		minishell.line = readline(PROMPT);
// 		if (!minishell.line)
// 		{
// 			break ;
// 			(ft_clean_shell(&minishell), ft_putstr_fd("exit\n", 1),
// 				exit(g_global.error_num));
// 		}
// 		if (minishell.line[0])
// 			add_history(minishell.line);
// 		minishell.tokens = ft_tokenize(minishell.line);
// 		if (!minishell.tokens)
// 			continue ;
// 		new_tokens = minishell.tokens;
// 		new_tokens->prev = NULL;
// 		minishell.tokens = ft_expander(new_tokens, minishell.environ);
// 		minishell.ast = ft_parse(&minishell);
// 		if (minishell.parse_error.type)
// 		{
// 			ft_handle_parse_error(&minishell);
// 			continue ;
// 		}
// 		ft_start_execution(&minishell);
// 	}
// 	ft_putstr_fd("exit\n", 1);
// 	ft_free_double_d(minishell.environ);
// 	ft_collector(NULL, true);
// 	return (ft_clean_shell(&minishell), g_global.error_num);
// }

// void	ft_clean_exit(t_minishell *minishell)
// {
// 	ft_putstr_fd("exit\n", 1);
// 	ft_free_double_d(minishell->environ);
// 	ft_collector(NULL, true);
// 	ft_clean_shell(minishell);
// 	if (minishell->line)
// 		free(minishell->line);
// 	exit(g_global.error_num);
// }

// void	ft_clean_exit(t_minishell *minishell)
// {
// 	ft_putstr_fd("exit\n", 1);
// 	ft_free_double_d(minishell->environ);
// 	ft_collector(NULL, true);
// 	ft_clean_shell(minishell);
// 	if (minishell->line)
// 		free(minishell->line);
// 	exit(g_global.error_num);
// }

void	ft_clean_exit(t_minishell *minishell)
{
	ft_putstr_fd("exit\n", 1);
	ft_free_double_d(minishell->environ);
	ft_collector(NULL, true);
	if (minishell->ast)
	{
		ft_recursive_clear_ast(minishell->ast);
		minishell->ast = NULL;
	}
	ft_clean_shell(minishell);
	if (minishell->line)
		free(minishell->line);
	exit(g_global.error_num);
}

// void printListReverse(t_token *head)
// {
//     t_token *current = head;
//     int i;

// 	i = 0;
//     // Traverse to the last node
//     while (current->next != NULL) {
//         current = current->next;
// 		i++;
//     }
// 	printf("i is %d\n", i);
//     // Print the value of the last node
//     printf("%s\n", current->value);

// 	int j =0;
//     // Traverse back to the head while printing values in reverse order
//     while (current->prev != NULL) {
//         current = current->prev;
//         printf("%s\n", current->value);
// 		j++;
//     }
// 	printf("j is %d\n", j);
//     printf("\n");
// }

void	main_loop(t_minishell *minishell)
{
	while (1)
	{
		ft_signals(1);
		minishell->line = readline(PROMPT);
		if (!minishell->line)
			break ;
		if (minishell->line[0])
			add_history(minishell->line);
		minishell->tokens = ft_tokenize(minishell->line);
		if (minishell->line)
			free(minishell->line);
		if (!minishell->tokens)
			continue ;
		minishell->tokens = ft_expander(minishell->tokens, minishell->environ);
		minishell->ast = ft_parse(minishell);
		if (minishell->parse_error.type)
		{
			ft_handle_parse_error(minishell);
			ft_clear_ast((&minishell->ast), minishell);
			continue ;
		}
		ft_start_execution(minishell);
		ft_clear_ast((&minishell->ast), minishell);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	((void)argc, (void)argv);
	setbuf(stdout, NULL);
	ft_init_minishell(&minishell, env);
	main_loop(&minishell);
	ft_clean_exit(&minishell);
}
