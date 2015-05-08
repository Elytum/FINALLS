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

#include <time.h>

char		ft_any_file(t_file *head)
{
	t_file	*ptr;

	ptr = head;
	while (ptr)
	{
		// dprintf(1, "Test %s\n", ptr->name);
		if (S_ISREG(ptr->filestat.st_mode))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void		ft_manage_first(char **args, int flags)
{
	t_paths	*paths;
	char	**ptr;
	char	**p;
	t_file	*files;
	compare	f;
	t_times times;

	times.launchtime = time(NULL);
	times.timelimit = times.launchtime - 60 * 60 * 24 * 30 * 6;
	f = ft_get_function(flags);
	paths = NULL;
	files = NULL;
	ptr = args;
	while (*ptr)
		ft_addpath(&paths, *ptr++);
	ft_cleanpath(&paths);
	/**/ft_split_order_type(paths, &files, f);
	if (ft_any_file(files))
	{
		ft_putfiles(files, flags, times);
		ptr = ft_simple_extractpaths(files);
	}
	else if (files && !files->next)
	{
		ptr = (char **)malloc(sizeof(char *) * 2);
		*ptr = ft_strdup(files->name);
		*(ptr + 1) = NULL;
	}
	else
		ptr = ft_simple_extractpaths(files);
	ft_freefilestest(&files);

	if (!*(ptr + 1))
		flags |= SINGLE;
	// else
	// 	flags &= ~SINGLE;

	// dprintf(1, "*ptr = '%s' and *(ptr + 1) = '%s'\n", *ptr, *(ptr + 1));
	p = ptr;
	if (*p)
	{
		flags |= FIRST;
		// dprintf(1, "%s\n", *p);
		// dprintf(1, "\tFlags single = %i\n", flags & SINGLE);
		// if (p != ptr)
			// write(1, "\n", 1);
		while (*p)
		{
			ft_manage_directory(*p, f, flags, times);
			free(*p++);
			// flags &= ~SINGLE;
			flags &= ~FIRST;
		}
	}
	free(ptr);
}

void		ft_interact_flags(int *flags)
{
	if ((*flags) & LF_FLAG)
		(*flags) |= LA_FLAG;
}

int			main(int ac, char **av)
{
	int	flags;
	int		f;

	flags = 0;
	f = 0;
	av++;
	if (ac > 1 && (flags = ft_getflags(&av)) & ERROR)
		return (0);
	// ft_testflags(flags);
	ft_interact_flags(&flags);
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
	// while (42);
	return (0);
}
