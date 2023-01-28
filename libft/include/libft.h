/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:07:36 by tpolonen          #+#    #+#             */
/*   Updated: 2022/10/07 18:33:00 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# ifndef WIN
#  include <unistd.h>
# else
#  include <Windows.h>
# endif
# include <limits.h>
# define DINT_DEF_SIZE 10
# define GETLINE_BUFF_SIZE 128

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct s_dstr
{
	char			*str;
	size_t			alloced;
	size_t			len;
}				t_dstr;

typedef struct s_dintarr
{
	char			name[32];	
	int				*arr;
	size_t			alloced;
	size_t			len;
}				t_dintarr;

typedef struct s_buff
{
	int				fd;
	char			content[GETLINE_BUFF_SIZE];
	ssize_t			bytes;
	ssize_t			offset;
	struct s_buff	*next;
}				t_buff;

/*
 * Libc functions
 */

void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memrchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
size_t		ft_strlen(char const *str);
char		*ft_strdup(const char *str);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t len);
char		*ft_strcat(char *s1, const char *s2);
char		*ft_strncat(char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strchrnul(const char *s, int c);
char		*ft_strstr(const char *haystack, const char *needle);
long		ft_strtol(const char *nptr, char **endptr);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);
int			ft_abs(int n);
long long	ft_llabs(long long n);
size_t		ft_ssabs(ssize_t n);
double		ft_fabs(double n);
float		ft_fabsf(float n);
long double	ft_fabsl(long double n);
int			ft_max(int a, int b);
int			ft_min(int a, int b);
size_t		ft_smax(size_t a, size_t b);
size_t		ft_smin(size_t a, size_t b);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isspace(int c);
int			ft_isprint(int c);
int			ft_isupper(int c);
int			ft_islower(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);

/*
 * Additional functions
 */

void		*ft_memalloc(size_t size);
void		ft_memdel(void **ap);
char		*ft_strnew(size_t size);
void		ft_strdel(char **as);
void		ft_strclr(char *s);
void		ft_striter(char *s, void (*f) (char *));
void		ft_striteri(char *s, void (*f) (unsigned int, char *));
char		*ft_strmap(char const *s, char (*f) (char));
char		*ft_strmapi(char const *s, char (*f) (unsigned int, char));
int			ft_strequ(char const *s1, char const *s2);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s);
char		**ft_strsplit(char const *s, char c);
char		*ft_itoa(int n, int base);
char		*ft_tobase(int n, int base, char *buf);
size_t		ft_intlen(int n, int base);
size_t		ft_ssizelen(ssize_t n, int base);
size_t		ft_sizelen(size_t n, int base);
int			ft_putchar(char c);
int			ft_putstr(char const *str);
int			ft_putendl(char const *str);
int			ft_putnbr(int n);
int			ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(char const *str, int fd);
int			ft_putendl_fd(char const *s, int fd);
int			ft_putnbr_fd(int n, int fd);
int			ft_putmem(const char *ptr, size_t count);
int			ft_putbit(const void *ptr, size_t count);
int			ft_putset(int count, char c);
int			ft_putnum(size_t num, int base, int min_len, int all_caps);
int			ft_putnums(ssize_t num, int base, int min_len, int all_caps);
int			ft_getline(const int fd, char **line);

/*
 * List	functions
 */

t_list		*ft_lstnew(void const *content, size_t content_size);
void		ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void		ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void		ft_lstadd(t_list **alst, t_list *new);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
size_t		ft_lstcount(t_list *alst);
void		ft_lstprint(t_list *elem);

/*
 * Dynamic strings
 */

ssize_t		ft_dstraddc(t_dstr **ds, const char c);
ssize_t		ft_dstrnew(t_dstr **ds, size_t len);
ssize_t		ft_dstrbuild(t_dstr **ds, const char *str, size_t len);
ssize_t		ft_dstrclose(t_dstr **ds, char **target);

/*
 * Dynamic integer arrays
 */

ssize_t		ft_dintarr_create(t_dintarr **darr, size_t size, const char *name);
ssize_t		ft_dintarr_add(t_dintarr **darr, const int n);
ssize_t		ft_dintarr_close(t_dintarr **src, int **dst);
ssize_t		ft_dintarr_clear(t_dintarr **darr);

#endif
