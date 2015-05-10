/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
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

void			ft_cleanerror(t_paths **ptr, t_paths **past,
								char error, t_paths **paths)
{
	write(2, "ls: ", 4), write(2, (*ptr)->path, ft_strlen((*ptr)->path));
	if (error)
		write(2, ": File name too long\n", 21);
	else
		write(2, ": No such file or directory\n", 28);
	free((*ptr)->path);
	free (*ptr);
	if (!(*past))
	{
		*paths = (*paths)->next;
		(*ptr) = (*paths);
	}
	else
	{
		(*past)->next = (*past)->next->next,
		(*ptr) = (*past)->next;
	}
}

void			ft_cleanpath(t_paths **paths, int *flags)
{
	t_paths		*ptr;
	t_paths		*past;
	struct stat	statbuf;
	char		*p;
	char		error;

	ptr = *paths;
	past = NULL;
	while (ptr)
	{
		error = 0;
		if (!(p = ft_strrchr(ptr->path, '/')))
			p = ptr->path;
		if (ft_strlen(p) > 256)
			error = 1;
		if (error || (stat(ptr->path, &statbuf) == -1 &&
							lstat(ptr->path, &statbuf) == -1))
		{
			ft_cleanerror(&ptr, &past, error, paths);
			*flags |= REMOVED;
		}
		else
			past = ptr,
			ptr = ptr->next;
	}
}

static char		*ft_linktodirpath(char *path, int mode)
{
	struct stat	statbuf;
	char		*tmp;
	int			i;

	if (!S_ISLNK(mode))
		return (NULL);
	if (stat(path, &statbuf) == -1)
		return (NULL);
	if (S_ISDIR(statbuf.st_mode))
		return (ft_strdup(path));
	return (NULL);
}

char			**ft_simple_extractpaths_allocate(t_file *head, int flags)
{
	size_t		len;
	t_file		*ptr;
	char		**paths;

	len = 0;
	ptr = head;
	while (ptr)
	{
		if (S_ISDIR(ptr->filestat.st_mode) || (!(flags & LL_FLAG) &&
			ft_linktodirpath(ptr->path, ptr->filestat.st_mode)))
			len++;
		ptr = ptr->next;
	}
	if (!(paths = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	return (paths);
}

char			**ft_simple_extractpaths(t_file *head, int flags)
{
	t_file		*ptr;
	char		**paths;
	char		**p;
	char		*tmp;
	size_t		len;

	if (!(paths = ft_simple_extractpaths_allocate(head, flags)))
		return (NULL);
	p = paths;
	ptr = head;
	while (ptr)
	{
		if (S_ISDIR(ptr->filestat.st_mode))
			*p++ = ft_strdup(ptr->path);
		else if (!(flags & LL_FLAG) && (tmp = ft_linktodirpath(ptr->path,
												ptr->filestat.st_mode)))
			*p++ = tmp;
		ptr = ptr->next;
	}
	*p = NULL;
	return (paths);
}
