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

typedef struct		s_paths
{
	char			*path;
	struct s_paths	*next;
}					t_paths;

size_t				ft_strlen(char *str);
char				*ft_strdup(char *str);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_fillflag(char p, char *flags);
char				ft_getflags(char ***str);
void				ft_testflags(char flags);
void				ft_addpath(t_paths **paths, char *p);
void				ft_putpath(t_paths *paths);
void				ft_cleanpath(t_paths **paths);

# define LL_FLAG 0b00000001
# define UR_FLAG 0b00000010
# define LA_FLAG 0b00000100
# define LR_FLAG 0b00001000
# define LT_FLAG 0b00010000
# define ERROR 0b10000000
# define ILLEGAL_OPTION "ls: illegal option -- "
# define ILLEGAL_OPTION_SIZE 22
# define USAGE1 "\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1]"
# define USAGE2 "[file ...]\n"
# define USAGE USAGE1 USAGE2
# define USAGE_SIZE 63
# define LLERROR1 "ls: illegal option -- -\nusage: ls [-ABCFGHLOPRSTUWa"
# define LLERROR2 "bcdefghiklmnopqrstuwx1] [file ...]\n"
# define LLERROR LLERROR1 LLERROR2
# define LLERROR_SIZE 87
#endif
