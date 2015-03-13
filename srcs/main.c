/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void		ft_manage_first(char **args, char flags)
{
	t_paths	*paths;
	char	**ptr;
	char	**p;
	t_file	*files;
	compare	f;

	f = ft_get_function(flags);
	paths = NULL;
	files = NULL;
	ptr = args;
	while (*ptr)
		ft_addpath(&paths, *ptr++);
	ft_cleanpath(&paths);
	/**/ft_split_order_type(paths, &files, f);
	ft_putfilesdebug(files, flags);
	ptr = ft_extractpaths(files);
// ft_freefilestest(&files);
	p = ptr;
	if (*p)
		write(1, "\n", 1);
	while (*p)
	{
		ft_manage_directory(*p, f, flags, ft_strlen(*p));
		free(*p);
		p++;
	}
// free(ptr);
}

int			main(int ac, char **av)
{
	char	flags;
	int		f;

	flags = 0;
	f = 0;
	av++;
	if (ac > 1 && (flags = ft_getflags(&av)) & ERROR)
		return (0);
	if (!*av)
	{
		av = (char **)malloc(sizeof(char *) * 2);
		*av = ft_strdup(".");
		*(av + 1) = NULL;
		f = 1;
	}
	ft_manage_first(av, flags);
	if (f)
		free(*av);
	return (0);
}
