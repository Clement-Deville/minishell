NAME = $(BIN_DIR)minishell

NAME_B = $(BIN_DIR)minishell_bonus

CC = cc

FLAGS = -Wall -Wextra -Werror

VAL_HIDE := readline.hide

VAL_FLAGS := --leak-check=full --show-leak-kinds=all -s --track-fds=yes  --trace-children=yes --suppressions=$(VAL_HIDE)

DEBUG = -g

SRC = main $(COMPUTE_FILES) $(ENV_FILES) $(EXEC_FILES) $(PARSING_FILES) $(REDIRECTIONS_FILES) $(UTILS_FILES) $(WILDCARDS_FILES)

SRCS_FILES =	main	\
				$(addprefix compute/, $(COMPUTE_FILES))	\
				$(addprefix env/, $(ENV_FILES))	\
				$(addprefix exec/, $(EXEC_FILES))	\
				$(addprefix parsing/, $(PARSING_FILES))	\
				$(addprefix redirections/, $(REDIRECTIONS_FILES))	\
				$(addprefix utils/, $(UTILS_FILES))	\
				$(addprefix wildcards/, $(WILDCARDS_FILES))	\

COMPUTE_FILES =	compute_cmds	\
				compute_alloc	\
				compute_check_quotes	\
				compute_handle_arg	\
				compute_pre_expand	\
				compute_split_args_utils	\
				compute_split_args	\
				compute_utils	\
				compute_wildcards_thereisasterix	\
				compute_re_node_wildcards	\
				compute_wildcards_utils	\
				compute_wildcards	\

ENV_FILES =		clean_env	\
				env	\
				env_utils	\

EXEC_FILES = 	exec	\
				do	\
				exec_pipeline	\
				pipe_fd_utils	\
				pipe_utils	\
				echo	\
				pwd	\
				export	\
				exec_here_doc_expand	\
				exec_here_doc	\
				exec_sub	\
				exec_standard	\
				exec_utils	\
				exec_no_cmd	\
				exec_builtin	\
				unset	\
				exit	\
				cd	\

PARSING_FILES =	clean_parsing	\
				convert_token	\
				lst_token_add_back	\
				tokens_helper	\
				parser	\
				parser_check_sub	\
				parser_utils_nodes	\
				parser_utils_tokens	\
				parser_init	\
				parser_utils_error	\
				token_finder	\
				tokenization	\
				ft_strip_quotes	\

REDIRECTIONS_FILES =	access_utils	\
						get_path	\
						access	\
						path	\
						path_utils	\
						process_here_doc	\
						redirections	\
						dir	\
						init_here_doc	\
						init_here_doc_utils	\

UTILS_FILES =	balise	\
				variable	\
				variable_utils	\
				print_export	\
				signals	\
				signal_handlers	\
				utils	\
				init_minishell	\
				error_msg	\

WILDCARDS_FILES =	asterisk	\
					wildcard	\

SRCS_FILES_BONUS =	main_bonus	\

INCLUDES_FILES = minishell


SOURCE_DIR =	./src/mandatory/
SOURCE_BONUS_DIR = ./src/bonus/
INCLUDES_DIR =	./include/
OBJS_DIR =		./obj/
OBJS_BONUS_DIR = ./obj/
BIN_DIR =		./bin/
LIB_DIR =		./lib/
TEST_DIR =		./test/
MANDATORY_DIR =	mandatory/

LIBFT_DIR = $(LIB_DIR)/libft

SOURCES =	$(addprefix $(SOURCE_DIR), $(addsuffix .c, $(SRCS_FILES)))
INCLUDES =	$(addprefix $(INCLUDES_DIR), $(addsuffix .h, $(INCLUDES_FILES)))
OBJS =		$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))
OBJS_B =	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES_BONUS)))

.PHONY: all clean fclean re bonus norminette

all: $(NAME)

val: $(NAME)
	valgrind $(VAL_FLAGS) ./$(NAME)

bonus: $(NAME_B)

$(OBJS_DIR)%.o : $(SOURCE_DIR)%.c
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(DEBUG) -I./lib/libft/INCLUDES -I$(INCLUDES_DIR) -c $< -o $@

$(OBJS_BONUS_DIR)%.o : $(SOURCE_BONUS_DIR)%.c
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) $(DEBUG) -I./lib/libft/INCLUDES -I$(INCLUDES_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@echo "\e[0;32m\nGenerating libft...\n\e[0m"
	make -C $(LIBFT_DIR)
	@echo "\e[0;32m\nLinking executable:\n\e[0m"
	$(CC) $(FLAGS) $(OBJS) $(DEBUG) -lft -L$(LIBFT_DIR) -lreadline -o $(NAME)
	@echo "\e[0;32m\nMandatory part compiled !\n\e[0m"

$(NAME_B): $(OBJS_B)
	@echo "\e[0;32m\nGenerating libft...\n\e[0m"
	make -C $(LIBFT_DIR)
	@echo "\e[0;32m\nLinking executable:\n\e[0m"
	$(CC) $(FLAGS) $(OBJS_B) $(DEBUG) -lft -L$(LIBFT_DIR) -o $(NAME_B)
	@echo "\e[0;32m\nBonus Compiled !\e[0m"

clean:
	@echo "\e[0;31m\nDeleting objects\n\e[0m"
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	@echo "\e[0;31m\nDeleting executable\n\e[0m"
	rm -rf $(BIN_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all

norminette:
			@echo "\e[0;32m\nChecking .c norme:\n\e[0m"
			norminette ./src
			@echo "\e[0;32m\nChecking .h norme:\n\e[0m"
			norminette ./include
