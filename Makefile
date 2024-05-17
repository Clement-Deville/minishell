NAME = $(BIN_DIR)minishell

NAME_B = $(BIN_DIR)minishell_bonus

CC = cc

FLAGS = -Wall -Wextra -Werror

DEBUG = -g

SRCS_FILES =	main	\
				echo	\
				pwd	\
				export	\
				unset	\
				exit	\
				cd	\
				dir	\
				variable	\
				print_export	\
				asterisk	\
				signals	\
				env	\
				utils	\
				tokenization	\
				init_minishell 	\
				lst_token_add_back	\
				tokens_helper \
				parser \
				compute_cmds \
				wildcard \
				init_here_doc \
				clean_ms \
				exec \
				exec_red \
				exec_builtin \
				error_msg \
				get_path \
				exec_pipeline \

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

bonus: $(NAME_B)

$(OBJS_DIR)%.o : $(SOURCE_DIR)%.c
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJS_DIR)
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
