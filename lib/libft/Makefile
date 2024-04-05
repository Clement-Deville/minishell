SRCS_FILES =		ft_memset	\
					ft_bzero	\
					ft_memcpy	\
					ft_memmove	\
					ft_memchr	\
					ft_memcmp	\
					ft_strlen	\
					ft_isalpha	\
					ft_isdigit	\
					ft_isalnum	\
					ft_isascii	\
					ft_isprint	\
					ft_toupper	\
					ft_tolower	\
					ft_strchr	\
					ft_strrchr	\
					ft_striteri	\
					ft_strncmp	\
					ft_strlcpy	\
					ft_strlcat	\
					ft_strnstr	\
					ft_atoi	\
					ft_atof	\
					is_decimal	\
					ft_calloc	\
					ft_strdup	\
					ft_substr	\
					ft_strjoin	\
					ft_strtrim	\
					ft_split	\
					ft_itoa	\
					ft_strmapi	\
					ft_putchar_fd	\
					ft_putstr_fd	\
					ft_putendl_fd	\
					ft_putnbr_fd	\
					ft_lstnew_bonus	\
					ft_lstadd_front_bonus	\
					ft_lstsize_bonus		\
					ft_lstlast_bonus		\
					ft_lstadd_back_bonus	\
					ft_lstclear_bonus		\
					ft_lstdelone_bonus	\
					ft_lstiter_bonus		\
					ft_lstmap_bonus		\
					ft_dblstadd_after \
					ft_dblstadd_before \
					ft_dblstfirst \
					ft_dblstnew \
					ft_dblstdelone	\
					ft_dblstclear	\
					ft_printf			\
					field_width		\
					isflag			\
					print_char		\
					print_hexa		\
					print_integer		\
					print_parameters	\
					print_percent		\
					print_pointer		\
					print_string		\
					print_unsigned	\
					print_nil			\
					reset		\
					putnbr_unsigned_fd	\
					ft_free	\
					free_split	\
					destroy_htab	\
					hash_tab_utils	\
					hash_tab	\
					hash	\
					print_htab	\
					ft_abs	\
					get_next_line	\
					get_next_line_utils	\

INCLUDES_FILES =	libft	\

SOURCE_DIR =	./SOURCES/
INCLUDES_DIR =	./INCLUDES/
OBJS_DIR =		./OBJECTS/

SOURCES =	$(addprefix $(SOURCE_DIR), $(addsuffix .c, $(SRCS_FILES)))
INCLUDES =	$(addprefix $(INCLUDES_DIR), $(addsuffix .h, $(INCLUDES_FILES)))
OBJS =		$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))

NAME = libft.a

CC = cc

CC_FLAGS = -Wall -Wextra -Werror -g

$(OBJS_DIR)%.o : $(SOURCE_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@cc $(CC_FLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJS)
	@ar r $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)
	$(RM) -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

norminette : $(SOURCES) $(INCLUDES)
	norminette $(SOURCES) $(INCLUDES)

.PHONY: all clean fclean re norminette
