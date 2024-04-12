NAME		:= lumumbash

CC			:= cc

CFLAGS		:= -g -Wall -Werror -Wextra

BUILTINS	:=	builtins/echo.c \
				builtins/exit.c \
				builtins/pwd.c \
				builtins/export.c \
				builtins/export_modif.c \
				builtins/unset.c \
				builtins/env.c \
				builtins/cd.c \
				builtins/export_utils.c \
				builtins/export_help.c \
				builtins/env_helpers.c \

CLEANERS	:=	cleaners/clean.c \
				cleaners/free.c \
				cleaners/clear.c \

EXEC		:=	exec/checks.c \
				exec/errors.c \
				exec/exec_redir.c \
				exec/exec_simple.c \
				exec/exec_utils.c \
				exec/exec.c \
				exec/pipes_exec.c \
				exec/tree.c \
				exec/signals.c \

EXPANDER    :=  expander/expander.c \
                expander/create_env_lists.c \
                expander/ft_frees.c \
                expander/new_ft_split.c \
                expander/tester_functions.c \
                expander/ft_split_double.c \
                expander/ft_split_bis.c \
                expander/expander_utils.c \
                expander/expand_assemble.c \
                expander/remove_wrong_env_var.c \
                expander/expand_tilde.c \
				expander/expander_helpers.c \
				expander/expander_utils_2.c \
				expander/expand_tilde_utils.c \
				expander/ft_no_quotes.c \


HELP		:=  help/echo_helpers.c \
				help/exec_helpers.c \
				help/exit_helpers.c \
				help/exphelp.c \
				help/libfthelp.c \
				help/tk_helpers.c \
				help/libfthelpers.c \
				help/parse_help.c \
				help/append_helpers.c \

PARSER		:=	parser/nodes.c \
				parser/parser_errors.c \
				parser/parser_helpers.c \
				parser/parser_utils.c \
				parser/parser.c \
				parser/redir_help.c \
				parser/parser_helper_2.c \

MINILIBFT	:=	minilibft/comp.c \
				minilibft/issomething.c \
				minilibft/str.c \


TOKENIZER	:=	tokenizer/tokenizer.c \
				tokenizer/handlers.c \
				tokenizer/appends.c \
				tokenizer/tokens_list.c \
				tokenizer/tokens_utils.c \
				tokenizer/tokenizer_utils.c \
				tokenizer/handlers_utils.c \
				tokenizer/ft_handle.c

SRCS		:=	$(BUILTINS)\
				$(HELP)\
				$(CLEANERS)\
				$(MINILIBFT)\
				$(EXEC)\
				$(EXPANDER)\
				$(PARSER)\
				$(TOKENIZER)\
				main.c

OBJS		:=	$(SRCS:.c=.o)

READLINE_PATH:=	/goinfre/homebrew/opt/readline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -Iincludes -I$(READLINE_PATH)/include
	@clear
all: $(NAME)


$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -L$(READLINE_PATH)/lib -lreadline

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
