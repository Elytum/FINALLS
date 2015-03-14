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

// void			ft_putpath(t_paths *paths)
// {
// 	t_paths		*ptr;
// 	struct stat	statbuf;

// 	ptr = paths;
// 	while (ptr)
// 	{
// 		stat(ptr->path, &statbuf);
// 		if (S_ISREG(statbuf.st_mode))
// 			dprintf(1, "%s is a file\n", ptr->path);
// 		else if (S_ISDIR(statbuf.st_mode))
// 			dprintf(1, "%s is a directory\n", ptr->path);
// 		ptr = ptr->next;
// 	}
// }

void			ft_cleanpath(t_paths **paths)
{
	t_paths		*ptr;
	t_paths		*past;
	struct stat	statbuf;

	ptr = *paths;
	past = NULL;
	while (ptr)
	{
		if (stat(ptr->path, &statbuf) == -1 && lstat(ptr->path, &statbuf) == -1)
		{
			write(1, "ls: ", 4), write(1, ptr->path, ft_strlen(ptr->path));
			write(1, ": No such file or directory\n", 28);
			free(ptr->path), free(ptr);
			if (!past)
				*paths = (*paths)->next,
				ptr = (*paths);
			else
				past->next = past->next->next,
				ptr = past->next;
		}
		else
			past = ptr,
			ptr = ptr->next;
	}
}

void			ft_addpath(t_paths **paths, char *p)
{
	t_paths		*ptr;
	t_paths		*newp;

	if (!(newp = (t_paths *)malloc(sizeof(t_paths))))
		return ;
	newp->path = ft_strdup(p);
	newp->next = NULL;
	if (!*paths)
		*paths = newp;
	else if (ft_strcmp(p, (*paths)->path) < 0)
	{
		newp->next = *paths;
		*paths = newp;
	}
	else
	{
		ptr = *paths;
		while (ptr->next && ft_strcmp(p, ptr->next->path) > 0)
			ptr = ptr->next;
		newp->next = ptr->next;
		ptr->next = newp;
	}
}

size_t			ft_nbofpaths(t_file *head)
{
	t_file		*ptr;
	size_t		len;

	len = 0;
	ptr = head;
	while (ptr)
	{
		if (S_ISDIR(ptr->filestat.st_mode) &&
			!((ptr->name[0] == '.' && !(ptr->name[1])) ||
			(ptr->name[0] == '.' && ptr->name[1] == '.' && !ptr->name[2])))
			len++;
		ptr = ptr->next;
	}
	return (len);
}

char			**ft_extractpaths(t_file *head)
{
	t_file		*ptr;
	char		**paths;
	char		**p;

	if (!(paths = (char **)malloc(sizeof(char *) * (ft_nbofpaths(head) + 1))))
		return (NULL);
	p = paths;
	ptr = head;
	while (ptr)
	{
		if (S_ISDIR(ptr->filestat.st_mode) &&
			!((ptr->name[0] == '.' && !(ptr->name[1])) ||
			(ptr->name[0] == '.' && ptr->name[1] == '.' && !ptr->name[2])))
		{
			*p++ = ft_strdup(ptr->path);
		}
		ptr = ptr->next;
	}
	*p = NULL;
	return (paths);
}

char			**ft_simple_extractpaths(t_file *head)
{
	t_file		*ptr;
	char		**paths;
	char		**p;
	size_t		len;

	len = 0;
	ptr = head;
	while (ptr)
	{
		len++;
		ptr = ptr->next;
	}
	if (!(paths = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	p = paths;
	ptr = head;
	while (ptr)
	{
		*p++ = ft_strdup(ptr->path);
		ptr = ptr->next;
	}
	*p = NULL;
	return (paths);
}