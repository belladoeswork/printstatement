/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lumumbash.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:40:32 by tbella-n          #+#    #+#             */
/*   Updated: 2024/04/14 20:37:25 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMUMBASH_H
# define LUMUMBASH_H

# include "expander.h"
# include "global.h"
# include "parser.h"
# include "tokenizer.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define MAX_NUM_ARGS 100

typedef enum e_ast_direction
{
	TD_LEFT,
	TD_RIGHT
}					t_ast_direction;

// minilibft
bool				ft_isnumber(char *s);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strcpy(char *dest, const char *src);
// builtins
int					ft_echo(char **args);
void				ft_handle_arguments(char **args, int start_index);
void				ft_exit(char **args, t_minishell *minishell);
int					ft_pwd(void);
char				**ft_split_path(char *path);
int					ft_count_colons(char *path);
int					ft_cd(char **args);
void				handle_quoted_argument(char *arg);
void				handle_unquoted_argument(char *arg);
char				**allocate_result_array(char *path_copy);
void				split_path_into_parts(char *path_copy, char **result);
void				ft_handle_single_argument(char *arg);
// export_help.c
void				skip_spaces(char *str, char **out, int last_space);
char				*ft_no_space(char *str);
int					ft_env(char **environ);
int					ft_unset(char **args, t_minishell **minishell);
// // export_utils.c
int					ft_strlen_double_pers(char **str);
void				ft_print_export(t_minishell *minishell);
// help
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_alphanum(int c);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*ft_strdup(const char *s1);
char				*ft_extract_key(char *str);
bool				ft_env_entry_exists(char *key, t_minishell *minishell);
int					ft_keycheck(char *str);
void				ft_envlst_back(t_env *new, t_minishell *minishell);
char				*ft_extract_val(char *str);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_clean_shell(t_minishell *minishell);
void				*ft_collector(void *ptr, bool clean);
void				ft_free_char2(char **tofree);
void				ft_check_result_and_exit(unsigned long long result, char *s,
						t_minishell *minishell);
char				*ft_get_path(char **args);
void				ft_skip_spaces_and_get_sign(char *s, int *i, int *sign);
void				ft_check_number_and_exit(char *s, int i,
						t_minishell *minishell);
unsigned long long	ft_calculate_result(char *s, int *i);
int					ft_append_char_to_word(char *word, int *j, char c);
int					ft_check_special_char(char c);
int					ft_add_word_to_token_list(t_token **token_list, char *word);
int					ft_allocate_word(char **word, char *line);
void				ft_process_tokens(t_minishell *minishell, t_node *node,
						int *i);
char				**ft_allocate_split_args(void);
bool				ft_current_token_is_op(t_minishell *minishell);
void				ft_get_next_token(t_minishell *minishell);
void				exit_with_error(const char *message);

/// newly added:
int					ft_handle_flags(char **args);
void				ft_signal_ctrl_d(int numsig);
// tree.c
void				ft_init_tree(t_node *node, t_minishell *minishell);
bool				ft_is_delimiter(char *delimiter, char *str);
void				ft_heredoc(t_redir_node *redir, int p[2],
						t_minishell *minishell);

// pipes_exec.c
int					ft_exec_child(char **split_args, char **environ);
char				*ft_find_command_path(const char *command, char **environ);
void				ft_execute_child_process(char **split_args, char **environ);
int					ft_wait_for_child(pid_t pid);
// exec.c
int					ft_get_exit_status(int status);
int					ft_exec_node(t_node *tree, bool piped,
						t_minishell *minishell);
// exec_utils.c
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstnew(void *content);
int					ft_check_redir(t_node *node);
// exec_simple.c
void				ft_reset_stds(int original_stdin, int original_stdout,
						bool piped);
bool				ft_is_builtin(char *arg);
int					ft_exec_simple_cmd(t_node *node, bool piped,
						t_minishell *minishell);
int					ft_exec_builtin_cmd(t_node *node, bool piped,
						t_minishell *minishell);
int					ft_exec_non_builtin_cmd(t_node *node, bool piped,
						char **environ);
// errors.c
int					ft_error_msg(t_error error);
// checks.c
t_error				ft_check_exec(char *file, bool cmd);
t_error				ft_check_read(char *file);
t_error				ft_check_write(char *file);
// exec_redir.c
int					ft_out(t_redir_node *redir_list, int *status);
int					ft_in(t_redir_node *redir_list, int *status);
int					ft_append(t_redir_node *redir_list, int *status);
// expander.c
t_token				*ft_expander(t_token *tokenized_tokens, char **env);
// signals.c
void				ft_signals(int i);
void				sighandler_child_coredumped(int numsig);
void				ft_signal_ctrl_c(int numsig);
void				sighandler_child(int numsig);
void				ft_free_split_args(char **split_args);
char				*ft_find_command_path(const char *command, char **environ);
char				*find_full_path(const char *command, char **directories);
// void				ft_signal_ctrl_d(t_minishell *minishell);

// void				set_signal(void);
#endif