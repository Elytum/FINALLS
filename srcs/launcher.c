/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 04:49:41 by achazal           #+#    #+#             */
/*   Updated: 2014/11/25 22:54:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char		ft_any_file(t_file *head, int flags)
{
	t_file		*ptr;
	DIR			*dir;

	ptr = head;
	while (ptr)
	{
		if (S_ISLNK(ptr->filestat.st_mode))
		{
			if (flags & LL_FLAG)
				return (1);
			if (!(dir = opendir(ptr->path)))
				return (1);
			else
				closedir(dir);
		}
		if (S_ISREG(ptr->filestat.st_mode))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

static t_file	*ft_init_first(int *flags, char **args,
									compare f, t_times times)
{
	char		**ptr;
	t_paths		*paths;
	t_file		*files;

	paths = NULL;
	ptr = args;
	while (*ptr)
		ft_addpath(&paths, *ptr++);
	ft_cleanpath(&paths, flags);
	files = NULL;
	ft_split_order_type(paths, &files, f);
	return (files);
}

static void		ft_end_first(char **ptr, compare f, int flags, t_times times)
{
	char		**p;

	if (*(ptr + 1))
		flags &= ~SINGLE;
	p = ptr;
	if (flags & REMOVED)
	{
		flags &= ~REMOVED;
		flags &= ~SINGLE;
	}
	while (*p)
	{
		ft_manage_directory(*p, f, flags, times);
		free(*p++);
		flags &= ~SINGLE;
		flags &= ~FIRST;
	}
	free(ptr);
}

void			ft_manage_first(char **args, compare f,
									int flags, t_times times)
{
	char		**ptr;
	char		**p;
	t_file		*files;

	files = ft_init_first(&flags, args, f, times);
	if (ft_any_file(files, flags))
	{
		flags &= ~FIRST;
		ft_putfiles(files, flags, times);
		ptr = ft_simple_extractpaths(files, flags);
	}
	else if (files && !files->next)
	{
		ptr = (char **)malloc(sizeof(char *) * 2);
		*ptr = ft_strdup(files->name);
		*(ptr + 1) = NULL;
	}
	else
		ptr = ft_simple_extractpaths(files, flags);
	ft_freefilestest(&files);
	ft_end_first(ptr, f, flags, times);
}
