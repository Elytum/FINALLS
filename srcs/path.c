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

char	*ft_strrchr(const char *s, int c)
{
	char	letter;
	int		i;

	i = 0;
	while (s[i])
		i++;
	letter = (char)c;
	while (i && s[i] != letter)
	{
		i--;
	}
	if (s[i] == letter)
		return ((char *)s + i);
	return (0);
}

char			*ft_linktodirpath(char *path, int mode)
{
	struct stat	statbuf;
	char		*tmp;
	int			i;

	// dprintf(1, "Testing %s\n", path);
	if (!S_ISLNK(mode))
		return (NULL);
	if (stat(path, &statbuf) == -1)
		return (NULL);
	// dprintf(1, "Alive %s\n", path);
	if (S_ISDIR(statbuf.st_mode))
	{
		// if (!(tmp = (char *)malloc(sizeof(char) * 1024)))
		// 	return (0);
		// dprintf(1, "Readlink of %s\n", path);
		// if ((i = readlink(path, tmp, 1024)))
		// {
		// 	tmp[i] = '\0';
			return (ft_strdup(path));
		// }
		// free(tmp);
	}
	// dprintf(1, "ISDIR %s\n", path);
	return (NULL);
}

void			ft_cleanpath(t_paths **paths, int *flags)
{
	t_paths		*ptr;
	t_paths		*past;
	struct stat	statbuf;
	char		*p;

	ptr = *paths;
	past = NULL;
	while (ptr)
	{
		*flags &= ~ERROR;
		if ((p = ft_strrchr(ptr->path, '/')))
			;
		else
			p = ptr->path;
		if (ft_strlen(p) > 256)
			*flags |= ERROR;
		if (*flags & ERROR || (stat(ptr->path, &statbuf) == -1 && lstat(ptr->path, &statbuf) == -1))
		{
			write(2, "ls: ", 4), write(2, ptr->path, ft_strlen(ptr->path));
			if (*flags & ERROR)
				write(2, ": File name too long\n", 21);
			else
				write(2, ": No such file or directory\n", 28);
			free(ptr->path), free(ptr);
			if (!past)
				*paths = (*paths)->next,
				ptr = (*paths);
			else
				past->next = past->next->next,
				ptr = past->next;
			*flags |= ERROR;
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
			*p++ = ft_strdup(ptr->path);
		ptr = ptr->next;
	}
	*p = NULL;
	return (paths);
}

char			**ft_simple_extractpaths(t_file *head, int flags)
{
	t_file		*ptr;
	char		**paths;
	char		**p;
	char		*tmp;
	size_t		len;

	len = 0;
	ptr = head;
	while (ptr)
	{
		if (S_ISDIR(ptr->filestat.st_mode) || (!(flags & LL_FLAG) && ft_linktodirpath(ptr->path, ptr->filestat.st_mode)))
			len++;
		ptr = ptr->next;
	}
	if (!(paths = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	p = paths;
	ptr = head;
	while (ptr)
	{
		if (S_ISDIR(ptr->filestat.st_mode))
			*p++ = ft_strdup(ptr->path);
		else if (!(flags & LL_FLAG) && (tmp = ft_linktodirpath(ptr->path, ptr->filestat.st_mode)))
			*p++ = tmp;
		ptr = ptr->next;
	}
	*p = NULL;
	return (paths);
}