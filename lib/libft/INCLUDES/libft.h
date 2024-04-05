/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:55:59 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/26 12:01:43 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <math.h>

typedef int		t_bool;

# define FALSE 0
# define TRUE 1

# define INT_MIN -2147483648
# define INT_MAX 2147483647

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(char c);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlen(const char *s);
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_atoi(const char *nptr);
double			ft_atof(const char *str);
t_bool			is_decimal(char *arg);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *s);

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
long long		ft_abs(long long number);

# define HEXA_BASE_UP "0123456789ABCDEF"
# define HEXA_BASE_LOW "0123456789abcdef"

typedef struct s_struct {
	t_bool	hashtag;
	t_bool	zero;
	t_bool	minus;
	t_bool	space;
	t_bool	plus;
	t_bool	is_null;
	t_bool	isnegatif;
	int		width;
	int		precision;
	char	identifier;
	int		count;
}	t_struct;

void			print_parameter(t_struct *param, va_list *ptr);
int				ft_printf(const char *str, ...);
t_bool			isflag(char c);
void			reset(t_struct *param);
void			field_width(char c, int size, t_struct *param);
void			field_space_begin(t_struct *param, int size_printed,
					int number);
void			putnbr_unsigned_fd(unsigned int number, int fd);

int				print_percent(t_struct *param);
int				print_char(t_struct *param, va_list *ptr);
int				print_hexa(t_struct *param, va_list *ptr);
int				print_integer(t_struct *param, va_list *ptr);
int				print_unsigned(t_struct *param, va_list *ptr);
int				print_pointer(t_struct *param, va_list *ptr);
int				print_string(t_struct *param, va_list *ptr);
int				print_nil(t_struct *param, char *str);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

typedef struct s_dblist
{
	struct s_dblist	*prev;
	struct s_dblist	*next;
	void			*content;
}	t_dblist;

t_dblist		*ft_dblstnew(void *content);
t_dblist		*ft_dblstadd_after(t_dblist *actual, t_dblist *new);
t_dblist		*ft_dblstadd_before(t_dblist *actual, t_dblist *new);
void			ft_dblstdelone(t_dblist *dblst, void (*del)(void*));
void			ft_dblstclear(t_dblist **lst, void (*del)(void*));
t_dblist		*ft_dblstfirst(void *content);

typedef struct s_freeparam {
	t_bool	pointer;
	t_bool	split;
	t_bool	list;
	t_bool	dblist;
}	t_freeparam;

int				ft_free(const char *str, ...);
void			free_split(char **split);

typedef t_list	t_hash;

unsigned int	hash_int(char *key, int size);
void			init_htab(t_hash *htab, int size);
void			print_htab(t_hash *htab, int size);
void			destroy_htab(t_hash *htab, int size);
void			print_efficiency(t_hash *htab, int size);
int				handle_collision(t_hash *htab, char *key);
t_hash			*create_htab(int size, char *tab[],
					unsigned int (*hash_f)(char*, int));

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

char			*get_next_line(int fd);
char			*ft_strjoin_edited(char *s1, char const *s2);
char			*fill_line(int fd, char *line, char **stock);
t_bool			isline_over(char *str);
void			trim_begining(char *str);

#endif
