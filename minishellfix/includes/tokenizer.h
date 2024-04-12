/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:47:16 by aguede            #+#    #+#             */
/*   Updated: 2024/04/07 07:25:09 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "lumumbash.h"
# include <stddef.h>

# define PROMPT "lumumbash$ "

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_SPACE,
	TOKEN_INPUT_REDIRECTION,
	TOKEN_OUTPUT_REDIRECTION,
	TOKEN_APPEND_OUTPUT_REDIRECTION,
	TOKEN_HEREDOC,
	TOKEN_NL
}					t_token_type;

typedef struct s_integers
{
	int				i;
	int				j;
}					t_integers;

typedef struct s_tokentypestrings
{
	char			*token_word;
	char			*token_pipe;
	char			*token_input_redirection;
	char			*token_output_redirection;
	char			*token_append_output_redirection;
	char			*token_heredoc;
	char			*token_nl;
}					t_tokentypestrings;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;
typedef enum e_error_msg
{
	CMD_NOT_FOUND,
	NO_SUCH_FILE,
	PERMISSION_DENIED,
	AMBIGUOUS,
	TOO_MANY_ARGS,
	NUMERIC_REQUIRED
}					t_error_msg;
typedef enum e_error_no
{
	SUCCESS,
	GENERAL,
	CANT_EXECUTE = 126,
	NOT_FOUND,
	ERROR_EXEC_255 = 255
}					t_error_no;
typedef struct s_err
{
	t_error_no		no;
	t_error_msg		msg;
	char			*cause;
}					t_error;
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isspace(char c);
void				ft_skip_spaces(char **line);
int					ft_is_quote(char c);
int					ft_is_separator(char *s);
int					ft_skip_quotes(char *str, size_t *i);
void				ft_putchar_fd(char c, int fd);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_putstr_fd(char *s, int fd);
void				ft_quote_error(char c);

void				ft_clear_token_list(t_token **lst);
int					ft_token_list_add_back(t_token **lst, t_token *new_token);

t_token				*ft_new_token(char *value, t_token_type type);
int					ft_append_separator(t_token_type type, char **line_ptr,
						t_token **token_list);
int					ft_handle_separator(char **line_ptr, t_token **token_list);
int					ft_append_word(char **line_ptr, t_token **token_list);
void				ft_free_token(t_token *token);
t_token				*ft_tokenization_handler(char *line);
int					ft_handle_space_or_separator(char **line,
						t_token **token_list);
int					ft_process_token(char **line, t_token **token_list);

t_token				*ft_tokenize(char *input_line);
int					ft_handle_quotes(char **line_ptr, t_token **token_list);
char				*find_end_of_quoted_string(char *line, int in_quotes);
char				*ft_create_word(char *line, char *word, int in_quotes,
						t_integers *ints);

int					create_and_add_quoted_token(char **line_ptr, char *start,
						char *end, t_token **token_list);

int					ft_append_separator(t_token_type type, char **line_ptr,
						t_token **token_list);
int					ft_handle_heredoc(char **line_ptr, t_token **token_list);
int					ft_handle_append_output_redirection(char **line_ptr,
						t_token **token_list);
int					ft_handle_input_redirection(char **line_ptr,
						t_token **token_list);
int					ft_handle_output_redirection(char **line_ptr,
						t_token **token_list);
int					ft_handle_pipe(char **line_ptr, t_token **token_list);
#endif