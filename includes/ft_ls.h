/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <stdlib.h>
# include <stdio.h>
# define BYPASS struct stat


#include "../includes/ft_ls.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>

typedef struct		s_paths
{
	char			*path;
	struct s_paths	*next;
}					t_paths;

typedef struct		s_file
{
	char			*permissions;
	char			*owner;
	char			*group;
	char			*name;
	char			*path;
	long long int	hard_links;
	long long int	size;
	int				date;
	char			*phard_links;
	char			*psize;
	char			*pdate;
	BYPASS			filestat;
	struct passwd	*pw;
	struct group	*gr;
	struct s_file	*next;
}					t_file;

typedef struct		s_info
{
	char			*name;
	char			*path;
}					t_info;

typedef struct		s_times
{
	unsigned int	launchtime;
	unsigned int	timelimit;
}					t_times;

typedef int			(*compare)(t_file *f1, t_file *f2);

size_t				ft_strlen(char *str);
char				*ft_strdup(char *str);
char				*ft_strndup(char *str, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_fillflag(char p, int *flags);
int					ft_getflags(char ***str);
void				ft_testflags(int flags);
void				ft_addpath(t_paths **paths, char *p);
void				ft_putpath(t_paths *paths);
void				ft_cleanpath(t_paths **paths);
char				*ft_itoa(int n);
char				*ft_ltoa(long long int n);
char				*ft_strrev(char *str);
int					ft_atoi(const char *str);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strcpyo(char *dst, const char *src);
char				*ft_strncpyo(char *dst, const char *src, size_t n);
char				ft_getsymbole(struct stat filestat);
char				*ft_get_permissions(struct stat filestat);
char				*ft_get_owner(struct stat filestat);
char				*ft_get_group(struct stat filestat);
int					ft_cmpname(t_file *s1, t_file *s2);
int					ft_cmprname(t_file *s1, t_file *s2);
int					ft_cmpdate(t_file *s1, t_file *s2);
int					ft_cmprdate(t_file *s1, t_file *s2);
compare				ft_get_function(int flags);
void				ft_putfilesdebug(t_file *head, int flags, t_times times);
void				ft_putfiles(t_file *head, int flags, t_times times);
void				ft_put_permission_denied(char *path);
void				ft_add_new_file2(t_file **first, t_info info, compare f, int flags);
void				ft_split_order_type(t_paths *paths, t_file **files,
									compare f);
void				ft_manage_directory(char *dir, compare f, int flags, t_times times);
char				**ft_extractpaths(t_file *head);
void				ft_freefiles(t_file **head);
void				ft_freefiles2(t_file **head, int flags);
void				ft_freefilestest(t_file **head);
void				ft_strclr(const char *s);
void				*ft_memalloc(size_t size);
int					ft_intlen(int n);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
char				**ft_simple_extractpaths(t_file *head);
void				ft_putsize_t(size_t n);

# define LL_FLAG 0b00000000000000000000000000000001
# define UR_FLAG 0b00000000000000000000000000000010
# define LA_FLAG 0b00000000000000000000000000000100
# define LR_FLAG 0b00000000000000000000000000001000
# define LT_FLAG 0b00000000000000000000000000010000

# define US_FLAG 0b00000000000000000000000000100000
# define UC_FLAG 0b00000000000000000000000001000000
# define UF_FLAG 0b00000000000000000000000010000000
# define LF_FLAG 0b00000000000000000000000100000000
# define LM_FLAG 0b00000000000000000000001000000000
# define LP_FLAG 0b00000000000000000000010000000000

# define LU_FLAG 0b00000000000000000000100000000000 // LAST ACCESS
# define UU_FLAG 0b00000000000000000001000000000000 // CREATION DATE

# define SINGLE  0b10000000000000000000000000000000
# define ERROR   0b10000000000000000000000000000000
# define FIRST   0b01000000000000000000000000000000
# define PAST    0b00100000000000000000000000000000
# define UNDEFIN 0b00010000000000000000000000000000

# define ILLEGAL_OPTION "ls: illegal option -- "
# define ILLEGAL_OPTION_SIZE 22
# define USAGE1 "\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1]"
# define USAGE2 " [file ...]\n"
# define USAGE USAGE1 USAGE2
# define USAGE_SIZE 63
# define LLERROR1 "ls: illegal option -- -\nusage: ls [-ABCFGHLOPRSTUWa"
# define LLERROR2 "bcdefghiklmnopqrstuwx1] [file ...]\n"
# define LLERROR LLERROR1 LLERROR2
# define LLERROR_SIZE 87
#endif
